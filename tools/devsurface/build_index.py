#!/usr/bin/env python3
"""tools/devsurface/build_index.py -- build the Development Surface database.

Inputs (produced by tools/devsurface/extract.py):
  devsurface/data/_work/symbols-<book>.ndjson   one record per line
  devsurface/data/pages/<book>.tsv              one coverage row per page

Outputs:
  devsurface/data/symbols/<header>.jsonl        symbol records sharded by header
  devsurface/data/sources.json                  source registry
  devsurface/data/abi/abi-facts.jsonl           ABI statements quoted from the corpus
  devsurface/index/devsurface.sqlite3           query index (symbols, params, ...)
  devsurface/index/symbols-across-books.tsv     one row per symbol per book
  devsurface/index/version-differences.tsv      documented statements that differ
  devsurface/COVERAGE.md                        generated coverage and gap report
  devsurface/GAPS.md                            generated list of unverified fields
  devsurface/index/*.md                         generated human-readable indexes

Usage:
  python3 tools/devsurface/build_index.py [--skip-sqlite] [--skip-crossbook]
"""

from __future__ import annotations

import argparse
import collections
import datetime as dt
import json
import os
import re
import sqlite3
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import vocab  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
WORK = os.path.join(ROOT, "devsurface", "data", "_work")
PAGES = os.path.join(ROOT, "devsurface", "data", "pages")
SYMBOLS = os.path.join(ROOT, "devsurface", "data", "symbols")
DATA = os.path.join(ROOT, "devsurface", "data")
INDEX = os.path.join(ROOT, "devsurface", "index")
COVERAGE_MD = os.path.join(ROOT, "devsurface", "COVERAGE.md")
GAPS_MD = os.path.join(ROOT, "devsurface", "GAPS.md")

PAGE_HEADER = ["page_id", "source_id", "path", "title", "page_class", "symbol_count",
               "kind", "symbol", "declaration_origin", "header", "library",
               "os_versions_raw", "declaration_status", "duplicate_of", "source_url"]


# --------------------------------------------------------------------------
# loading
# --------------------------------------------------------------------------

def book_files(pattern="symbols-%s.ndjson"):
    books = []
    if not os.path.isdir(WORK):
        return books
    for name in sorted(os.listdir(WORK)):
        if name.startswith("symbols-") and name.endswith(".ndjson"):
            books.append(name[len("symbols-"):-len(".ndjson")])
    return books


def load_symbols(book):
    path = os.path.join(WORK, "symbols-%s.ndjson" % book)
    with open(path, encoding="utf-8") as handle:
        for line in handle:
            line = line.strip()
            if line:
                yield json.loads(line)


def load_pages(book, strict=True):
    """Read a page coverage TSV.

    A row whose column count does not match PAGE_HEADER means the TSV was
    written by an older extractor; that is an error, not something to skip.
    """
    path = os.path.join(PAGES, "%s.tsv" % book)
    if not os.path.exists(path):
        return []
    rows, bad = [], 0
    with open(path, encoding="utf-8") as handle:
        for line in handle:
            if line.startswith("#"):
                continue
            fields = line.rstrip("\n").split("\t")
            if len(fields) == len(PAGE_HEADER):
                rows.append(dict(zip(PAGE_HEADER, fields)))
            else:
                bad += 1
    if bad:
        message = ("%s has %d rows with %d columns; expected %d (re-run "
                   "tools/devsurface/extract.py --force for this source)"
                   % (path, bad, len(fields), len(PAGE_HEADER)))
        if strict:
            raise SystemExit("ERROR: " + message)
        print("WARNING: " + message, file=sys.stderr)
    return rows


# --------------------------------------------------------------------------
# merge into header-sharded JSONL
# --------------------------------------------------------------------------

def field_value(entry):
    if not entry:
        return None
    return entry.get("value") or (entry.get("values") or [None])[0]


COMPACTION_RULES = [
    "version statements drop the duplicated `raw`/`normalized_text` copies of `value_raw`",
    "the constant `derived: true` marker is dropped from version statements (documented)",
    "`documented_in_books` is dropped; index/symbols-across-books.tsv carries collection coverage",
    "`extraction.tool`, `extraction.method` and `verbatim_declaration` are dropped from records; "
    "they are constants recorded in devsurface/data/manifest.json",
    "`source.book_path` and `source.page_title` are dropped; both are in devsurface/data/pages/*.tsv "
    "and in devsurface/data/sources.json",
    "the `evidence[0]` copy of source_id/page_path is dropped (same values as `source`)",
    "`uncertainty.declaration_parse_is_mechanical` is dropped (constant, documented)",
    "`parse.derived_fields` is dropped (constant: kind, return_type, parameters, members, "
    "enumerators and derived_tags are always derived from the declaration)",
]


def compact(record):
    """Drop fields that are duplicated elsewhere or are constant per corpus."""
    record = dict(record)
    for key in ("documented_in_books",):
        record.pop(key, None)
    extraction = dict(record.get("extraction") or {})
    extraction.pop("verbatim_declaration", None)
    extraction.pop("tool", None)
    extraction.pop("method", None)
    record["extraction"] = extraction
    source = dict(record.get("source") or {})
    source.pop("book_path", None)
    source.pop("page_title", None)
    record["source"] = source
    evidence = []
    for entry in record.get("evidence") or []:
        entry = dict(entry)
        entry.pop("source_id", None)
        entry.pop("page_path", None)
        evidence.append(entry)
    record["evidence"] = evidence
    parse = dict(record.get("parse") or {})
    parse.pop("derived_fields", None)
    record["parse"] = parse
    uncertainty = dict(record.get("uncertainty") or {})
    uncertainty.pop("declaration_parse_is_mechanical", None)
    record["uncertainty"] = uncertainty
    availability = dict(record.get("version_availability") or {})
    statements = []
    for entry in availability.get("statements") or []:
        entry = dict(entry)
        entry.pop("derived", None)
        normalized = dict(entry.get("normalized") or {})
        normalized.pop("raw", None)
        normalized.pop("normalized_text", None)
        entry["normalized"] = normalized
        statements.append(entry)
    availability["statements"] = statements
    record["version_availability"] = availability
    record["compaction"] = "v1"
    return record


def shard_of(record):
    return vocab.record_shard(record)


# A shard larger than this is written as `<shard>.part-NN.jsonl`. The record's
# own `shard` field keeps the unsplit name, so the split is a file-layout detail
# only; it keeps every committed file well below hosting limits.
SHARD_SPLIT_BYTES = 20 * 1024 * 1024


def merge_shards(log):
    os.makedirs(SYMBOLS, exist_ok=True)
    for stale in os.listdir(SYMBOLS):
        if stale.endswith(".jsonl"):
            os.remove(os.path.join(SYMBOLS, stale))
    buckets = collections.defaultdict(list)
    total = 0
    for book in book_files():
        for record in load_symbols(book):
            buckets[shard_of(record)].append(compact(record))
            total += 1
    manifest = []
    for shard in sorted(buckets):
        rows = sorted(buckets[shard],
                      key=lambda r: ((r.get("symbol") or "").lower(), r["source"]["source_id"], r["source"]["page_id"]))
        lines = [json.dumps(record, ensure_ascii=False, sort_keys=True) + "\n" for record in rows]
        if sum(len(line) for line in lines) <= SHARD_SPLIT_BYTES:
            parts = [("%s.jsonl" % shard, lines)]
        else:
            parts, current, current_bytes = [], [], 0
            for line in lines:
                if current and current_bytes + len(line) > SHARD_SPLIT_BYTES:
                    parts.append((current, None))
                    current, current_bytes = [], 0
                current.append(line)
                current_bytes += len(line)
            if current:
                parts.append((current, None))
            parts = [("%s.part-%02d.jsonl" % (shard, index + 1), part)
                     for index, (part, _) in enumerate(parts)]
        for filename, part in parts:
            with open(os.path.join(SYMBOLS, filename), "w", encoding="utf-8") as handle:
                handle.writelines(part)
            manifest.append((shard, filename, len(part)))
    revision = "unknown"
    for shard_rows in buckets.values():
        if shard_rows:
            revision = (shard_rows[0].get("extraction") or {}).get("corpus_revision", "unknown")
            break
    manifest_document = {
        "schema_version": vocab.SCHEMA_VERSION,
        "generated_on": dt.date.today().isoformat(),
        "tool": "tools/devsurface/build_index.py",
        "tool_version": vocab.TOOL_VERSION,
        "extraction_tool": "tools/devsurface/extract.py",
        "extraction_method": "mechanical_document_extraction",
        "declarations_are_verbatim": True,
        "corpus_revision": revision,
        "records": total,
        "shards": len(buckets),
        "compaction": "v1",
        "compaction_rules": COMPACTION_RULES,
    }
    with open(os.path.join(DATA, "manifest.json"), "w", encoding="utf-8") as handle:
        json.dump(manifest_document, handle, ensure_ascii=False, indent=1, sort_keys=True)
        handle.write("\n")
    with open(os.path.join(INDEX, "shards.tsv"), "w", encoding="utf-8") as handle:
        handle.write("#shard\trecords\tpath\n")
        for shard, filename, count in manifest:
            handle.write("%s\t%d\tdevsurface/data/symbols/%s\n" % (shard, count, filename))
    log("merged %d records into %d shards (%d files)"
        % (total, len({entry[0] for entry in manifest}), len(manifest)))
    return manifest


# --------------------------------------------------------------------------
# source registry
# --------------------------------------------------------------------------

def write_sources(log):
    records = []
    for source_id, source in sorted(vocab.SOURCES.items()):
        records.append({
            "id": source_id,
            "kind": source["kind"],
            "publisher": source["publisher"],
            "collection": source["collection"],
            "book_path": source["book_path"],
            "version_scope": source["version_scope"],
            "locator_template": source["locator_template"],
            "rights_status": source["rights"],
            "out_of_scope_reason": source.get("out_of_scope"),
            "scope": "catalogued_only" if source.get("out_of_scope") else "extracted",
        })
    for path, versions, locator in vocab.ARCHIVE_MEDIA:
        records.append({
            "id": "media-" + os.path.basename(path),
            "kind": "archived_official_media",
            "publisher": "Microsoft Corporation",
            "collection": "Windows CE documentation media retained in this corpus",
            "book_path": path,
            "version_scope": versions,
            "locator_template": locator,
            "rights_status": "archived-copy-rights-unknown",
            "out_of_scope_reason": None,
            "scope": "media_manifest_only",
        })
    document = {
        "schema_version": 1,
        "generated_on": dt.date.today().isoformat(),
        "purpose": ("Provenance registry for every Windows CE documentation collection the "
                    "Development Surface database draws on, plus the scope decision taken for each."),
        "records": records,
    }
    path = os.path.join(DATA, "sources.json")
    with open(path, "w", encoding="utf-8") as handle:
        json.dump(document, handle, ensure_ascii=False, indent=1, sort_keys=True)
        handle.write("\n")
    log("wrote %s (%d source records)" % (os.path.relpath(path, ROOT), len(records)))
    return records


# --------------------------------------------------------------------------
# SQLite
# --------------------------------------------------------------------------

SCHEMA = """
CREATE TABLE symbols (
  id TEXT PRIMARY KEY, symbol TEXT NOT NULL, kind TEXT, scope TEXT,
  declaration TEXT, declaration_origin TEXT, declaration_status TEXT,
  documentation_role TEXT,
  return_type TEXT, parse_status TEXT, kind_basis TEXT,
  header TEXT, header_label TEXT, library TEXT, library_all TEXT, module TEXT,
  source_id TEXT, book_path TEXT, page_id TEXT, page_path TEXT, page_title TEXT,
  source_url TEXT, document_last_updated TEXT,
  title_symbol TEXT, title_match INTEGER,
  version_raw TEXT, version_min TEXT, version_min_id TEXT, version_generation TEXT,
  version_qualifier TEXT, version_status TEXT,
  deprecation_count INTEGER, derived_tags TEXT, unknown_fields TEXT,
  page_class TEXT, extraction_on TEXT, corpus_revision TEXT, shard TEXT, shard_line INTEGER
);
CREATE TABLE parameters (
  symbol_id TEXT, position INTEGER, name TEXT, type TEXT, direction TEXT,
  description TEXT, documented_values TEXT, evidence_status TEXT, declaration_match INTEGER
);
CREATE TABLE members (symbol_id TEXT, idx INTEGER, text_raw TEXT, bitfield_width_raw TEXT);
CREATE TABLE enumerators (symbol_id TEXT, idx INTEGER, name TEXT, value_raw TEXT);
CREATE TABLE version_statements (
  symbol_id TEXT, field TEXT, label_raw TEXT, value_raw TEXT, version_number TEXT,
  version_id TEXT, generation TEXT, qualifier TEXT, status TEXT, family_id TEXT
);
CREATE TABLE pages (
  page_id TEXT, source_id TEXT, path TEXT, title TEXT, page_class TEXT,
  symbol_count INTEGER, kind TEXT, symbol TEXT, declaration_origin TEXT,
  header TEXT, library TEXT, os_versions_raw TEXT, declaration_status TEXT,
  duplicate_of TEXT, source_url TEXT
);
CREATE TABLE sources (
  id TEXT PRIMARY KEY, kind TEXT, publisher TEXT, collection TEXT, book_path TEXT,
  version_scope TEXT, locator_template TEXT, rights_status TEXT,
  out_of_scope_reason TEXT, scope TEXT
);
CREATE TABLE abi_facts (
  id TEXT PRIMARY KEY, topic TEXT, statement TEXT, source_id TEXT, page_path TEXT,
  page_title TEXT, source_url TEXT, evidence_status TEXT, note TEXT
);
CREATE INDEX idx_symbols_symbol ON symbols(symbol);
CREATE INDEX idx_symbols_header ON symbols(header);
CREATE INDEX idx_symbols_library ON symbols(library);
CREATE INDEX idx_symbols_source ON symbols(source_id);
CREATE INDEX idx_symbols_kind ON symbols(kind);
CREATE INDEX idx_symbols_version ON symbols(version_min_id);
CREATE INDEX idx_params_symbol ON parameters(symbol_id, position);
CREATE INDEX idx_version_symbol ON version_statements(symbol_id);
CREATE INDEX idx_pages_class ON pages(page_class);
"""


_SHARD_LINE = {}


def index_shard_lines(log):
    """Map record id -> line number inside its shard file (for record lookup)."""
    for name in sorted(os.listdir(SYMBOLS)):
        if not name.endswith(".jsonl"):
            continue
        with open(os.path.join(SYMBOLS, name), encoding="utf-8") as handle:
            for number, line in enumerate(handle, start=1):
                if not line.strip():
                    continue
                try:
                    _SHARD_LINE[json.loads(line)["id"]] = number
                except (ValueError, KeyError):
                    continue
    log("indexed %d shard lines" % len(_SHARD_LINE))


def symbol_row(record):
    statements = record.get("version_availability", {}).get("statements", [])
    os_statements = [s for s in statements if s.get("field") == "os_versions"
                     and s.get("normalized", {}).get("version_number")]
    os_statements.sort(key=lambda s: [_number(p) for p in s["normalized"]["version_number"].split(".")])
    best = os_statements[0] if os_statements else None
    header = record.get("header") or {}
    libraries = record.get("libraries") or []
    return {
        "id": record["id"],
        "symbol": record.get("symbol"),
        "kind": record.get("kind"),
        "scope": record.get("scope"),
        "declaration": record.get("declaration"),
        "declaration_origin": record.get("declaration_origin"),
        "declaration_status": record.get("declaration_status"),
        "documentation_role": record.get("documentation_role"),
        "return_type": record.get("return_type"),
        "parse_status": record.get("parse", {}).get("status"),
        "kind_basis": record.get("kind_evidence", {}).get("basis"),
        "header": header.get("value"),
        "header_label": header.get("label_raw"),
        "library": libraries[0]["value"] if libraries else None,
        "library_all": ",".join(sorted({value for entry in libraries
                                        for value in entry.get("values", [])})) or None,
        "module": (record.get("module") or {}).get("value") if isinstance(record.get("module"), dict) else None,
        "source_id": record["source"]["source_id"],
        "book_path": record["source"]["book_path"],
        "page_id": record["source"]["page_id"],
        "page_path": record["source"]["page_path"],
        "page_title": record["source"]["page_title"],
        "source_url": record["source"]["source_url"],
        "document_last_updated": record["source"].get("document_last_updated"),
        "title_symbol": record.get("title_symbol"),
        "title_match": 1 if record.get("title_symbol_matches_declaration", True) else 0,
        "version_raw": best["value_raw"] if best else None,
        "version_min": best["normalized"]["version_number"] if best else None,
        "version_min_id": best["normalized"]["version_id"] if best else None,
        "version_generation": best["normalized"]["generation"] if best else None,
        "version_qualifier": best["normalized"]["qualifier"] if best else None,
        "version_status": best["normalized"]["status"] if best else "unknown",
        "deprecation_count": len(record.get("deprecation_statements") or []),
        "derived_tags": ",".join(record.get("derived_tags") or []),
        "unknown_fields": ",".join(record.get("uncertainty", {}).get("unknown_fields", [])),
        "page_class": record.get("page_class"),
        "extraction_on": record.get("extraction", {}).get("extracted_on"),
        "corpus_revision": record.get("extraction", {}).get("corpus_revision"),
        "shard": shard_of(record),
        "shard_line": _SHARD_LINE.get(record["id"]),
    }


def _number(text):
    try:
        return int(re.sub(r"\D", "", text) or 0)
    except ValueError:
        return 0


SYMBOL_COLUMNS = ["id", "symbol", "kind", "scope", "declaration", "declaration_origin",
                  "declaration_status", "documentation_role", "return_type", "parse_status", "kind_basis",
                  "header", "header_label", "library", "library_all", "module",
                  "source_id", "book_path", "page_id", "page_path", "page_title",
                  "source_url", "document_last_updated", "title_symbol", "title_match",
                  "version_raw", "version_min", "version_min_id", "version_generation",
                  "version_qualifier", "version_status", "deprecation_count",
                  "derived_tags", "unknown_fields", "page_class", "extraction_on",
                  "corpus_revision", "shard", "shard_line"]


def write_sqlite(source_records, log):
    os.makedirs(INDEX, exist_ok=True)
    path = os.path.join(INDEX, "devsurface.sqlite3")
    if os.path.exists(path):
        os.remove(path)
    index_shard_lines(log)
    connection = sqlite3.connect(path)
    connection.executescript(SCHEMA)
    count = 0
    for book in book_files():
        for record in load_symbols(book):
            row = symbol_row(record)
            connection.execute(
                "INSERT OR REPLACE INTO symbols (%s) VALUES (%s)"
                % (",".join(SYMBOL_COLUMNS), ",".join("?" * len(SYMBOL_COLUMNS))),
                [row[key] for key in SYMBOL_COLUMNS])
            for entry in record.get("parameters") or []:
                connection.execute(
                    "INSERT INTO parameters VALUES (?,?,?,?,?,?,?,?,?)",
                    (record["id"], entry.get("position"), entry.get("name"), entry.get("type"),
                     entry.get("direction"), entry.get("description"),
                     json.dumps(entry.get("documented_values") or [], ensure_ascii=False),
                     entry.get("evidence_status"),
                     0 if entry.get("declaration_match") is False else 1))
            for index, entry in enumerate(record.get("members") or []):
                connection.execute("INSERT INTO members VALUES (?,?,?,?)",
                                   (record["id"], index, entry.get("text_raw"),
                                    entry.get("bitfield_width_raw")))
            for index, entry in enumerate(record.get("enumerators") or []):
                connection.execute("INSERT INTO enumerators VALUES (?,?,?,?)",
                                   (record["id"], index, entry.get("name"), entry.get("value_raw")))
            for entry in record.get("version_availability", {}).get("statements", []):
                normalized = entry.get("normalized", {})
                connection.execute(
                    "INSERT INTO version_statements VALUES (?,?,?,?,?,?,?,?,?,?)",
                    (record["id"], entry.get("field"), entry.get("label_raw"),
                     entry.get("value_raw"), normalized.get("version_number"),
                     normalized.get("version_id"), normalized.get("generation"),
                     normalized.get("qualifier"), normalized.get("status"),
                     normalized.get("family_id")))
            count += 1
    for record in source_records:
        connection.execute(
            "INSERT OR REPLACE INTO sources VALUES (?,?,?,?,?,?,?,?,?,?)",
            (record["id"], record["kind"], record["publisher"], record["collection"],
             record["book_path"], json.dumps(record["version_scope"], ensure_ascii=False),
             record["locator_template"], record["rights_status"],
             record["out_of_scope_reason"], record["scope"]))
    page_rows = 0
    for name in sorted(os.listdir(PAGES)):
        if not name.endswith(".tsv"):
            continue
        for row in load_pages(name[:-4]):
            connection.execute(
                "INSERT INTO pages VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)",
                (row["page_id"], row["source_id"], row["path"], row["title"],
                 row["page_class"], int(row["symbol_count"] or 0), row["kind"], row["symbol"],
                 row["declaration_origin"], row["header"], row["library"],
                 row["os_versions_raw"], row["declaration_status"], row["duplicate_of"],
                 row["source_url"]))
            page_rows += 1
    abi_path = os.path.join(DATA, "abi", "abi-facts.jsonl")
    abi_rows = 0
    if os.path.exists(abi_path):
        with open(abi_path, encoding="utf-8") as handle:
            for line in handle:
                line = line.strip()
                if not line:
                    continue
                fact = json.loads(line)
                connection.execute(
                    "INSERT OR REPLACE INTO abi_facts VALUES (?,?,?,?,?,?,?,?,?)",
                    (fact["id"], fact.get("topic"),
                     " || ".join(fact.get("statement") or []),
                     fact.get("source_id"), fact.get("page_path"), fact.get("page_title"),
                     fact.get("source_url"), fact.get("evidence_status"), fact.get("note")))
                abi_rows += 1
    connection.commit()
    for statement in ("symbols", "parameters", "pages", "version_statements", "sources", "abi_facts"):
        total = connection.execute("SELECT COUNT(*) FROM %s" % statement).fetchone()[0]
        log("sqlite: %-18s %d rows" % (statement, total))
    connection.execute("VACUUM")
    connection.close()
    log("wrote %s (%d symbol records, %d page rows, %d abi facts)"
        % (os.path.relpath(path, ROOT), count, page_rows, abi_rows))
    return count


# --------------------------------------------------------------------------
# cross-book views
# --------------------------------------------------------------------------

def version_text_key(raw):
    """Comparison key for a documented version statement.

    Punctuation and case are not version information: the CE 3.0 collection
    writes "1.0 and later" where the CE 5.0 collection writes
    "Windows CE 1.0 and later.". Comparing the raw text alone would report
    thousands of "differences" that are typing differences. The raw text is
    still kept, and reported separately, because the wording itself is evidence
    (it shows which collection names the product family explicitly).
    """
    text = re.sub(r"\s+", " ", raw or "").strip().rstrip(".").strip()
    return text.lower()


def write_crossbook(log):
    """One row per symbol: which collections document it, and how.

    Two difference counts are reported, because both are documented facts:
      * `mapped` counts symbols whose *normalised* version ids differ between
        collections (the coarse signal),
      * `text`  counts symbols whose raw documented version text differs
        (the same generation can be written "1.0 and later" in one collection
        and "Windows CE 1.0 and later." in another, so text differences are
        not automatically generation differences).
    """
    symbols = collections.defaultdict(dict)
    for book in book_files():
        for record in load_symbols(book):
            name = record.get("symbol") or ""
            symbols[name.lower()].setdefault(name, {})[record["source"]["source_id"]] = record

    rows, mapped_differences, text_differences, text_only = [], [], [], []
    for key in sorted(symbols):
        per_name = symbols[key]
        name = sorted(per_name)[0]
        per_book = per_name[name]
        books = sorted(per_book)
        columns = []
        per_book_versions = []
        distinct_mapped, distinct_text = set(), set()
        for book in books:
            record = per_book[book]
            statements = [s for s in record.get("version_availability", {}).get("statements", [])
                          if s.get("field") == "os_versions"]
            raw_texts = sorted({s["value_raw"] for s in statements})
            text_keys = sorted({version_text_key(t) for t in raw_texts})
            mapped_ids = sorted({(s.get("normalized", {}).get("version_id")
                                 or "unmapped:" + s["value_raw"]) for s in statements})
            if raw_texts:
                distinct_text.update(text_keys)
            if mapped_ids:
                distinct_mapped.update(mapped_ids)
            os_text = "; ".join(raw_texts)
            per_book_versions.append((book, ", ".join(mapped_ids) or "(no statement)", os_text))
            header = (record.get("header") or {}).get("value") or ""
            libraries = ",".join(sorted({v for entry in record.get("libraries") or []
                                         for v in (entry.get("values") or [])}))
            columns.append("%s|%s|%s|%s" % (book, record.get("kind") or "", header, libraries))
        rows.append("\t".join([name, str(len(books))] + columns))
        if len(distinct_mapped) > 1:
            mapped_differences.append((name, len(distinct_mapped), per_book_versions))
        if len(distinct_text) > 1:
            text_differences.append((name, len(distinct_text), per_book_versions))
            if len(distinct_mapped) <= 1:
                text_only.append((name, len(distinct_text), per_book_versions))
    with open(os.path.join(INDEX, "symbols-across-books.tsv"), "w", encoding="utf-8") as handle:
        handle.write("#symbol\tbook_count\tper_book(book|kind|header|library)\n")
        for row in rows:
            handle.write(row + "\n")
    def write_differences(path, header_lines, entries):
        with open(os.path.join(INDEX, path), "w", encoding="utf-8") as handle:
            handle.write("#symbol\tcount\tbook: mapped_version_ids (raw documented text)\n")
            for line in header_lines:
                handle.write("#" + line + "\n")
            for name, count, per_book_versions in entries:
                handle.write("%s\t%d\t%s\n" % (
                    name, count,
                    " ;; ".join("%s: %s (%s)" % (b, mapped, raw or "(no statement)")
                                for b, mapped, raw in per_book_versions)))
    write_differences(
        "version-differences-normalized.tsv",
        ["%d symbols whose normalised version ids differ between collections." % len(mapped_differences),
         "This is the primary difference list: the collections disagree about which",
         "version the symbol is documented for."],
        mapped_differences)
    write_differences(
        "version-differences.tsv",
        ["%d symbols whose documented version text differs after punctuation/case" % len(text_differences),
         "normalisation. A difference here can be wording only (one collection",
         "writes '1.0 and later', another 'Windows CE 1.0 and later.'), so this",
         "list must be read together with version-differences-normalized.tsv."],
        text_differences)
    write_differences(
        "version-differences-text-only.tsv",
        ["%d symbols whose version ids agree but whose wording differs between" % len(text_only),
         "collections. Not a generation difference; evidence about how each",
         "collection names the product family."],
        text_only)
    multi = sum(1 for row in rows if row.split("\t")[1] != "1")
    log("cross-book: %d symbols, %d documented in more than one collection, "
        "%d with differing normalised version ids (primary), %d with differing text, "
        "%d of those wording-only"
        % (len(rows), multi, len(mapped_differences), len(text_differences), len(text_only)))
    return rows, {"text": text_differences, "mapped": mapped_differences,
                  "text_only": text_only}


# --------------------------------------------------------------------------
# Markdown reports
# --------------------------------------------------------------------------

def pct(part, total):
    return "%.1f%%" % (100.0 * part / total) if total else "n/a"


def write_coverage(rows, differences, source_records, log):
    pages_by_book = collections.defaultdict(list)
    for name in sorted(os.listdir(PAGES)):
        if name.endswith(".tsv"):
            pages_by_book[name[:-4]] = load_pages(name[:-4])
    records_by_book = collections.Counter()
    kinds = collections.Counter()
    parse_status = collections.Counter()
    for book in book_files():
        for record in load_symbols(book):
            records_by_book[book] += 1
            kinds[record["kind"]] += 1
            parse_status[record.get("parse", {}).get("status")] += 1

    total_pages = sum(len(rows_) for rows_ in pages_by_book.values())
    classes = collections.Counter()
    for rows_ in pages_by_book.values():
        for row in rows_:
            classes[row["page_class"]] += 1

    lines = []
    lines.append("# Development Surface database — coverage and gaps")
    lines.append("")
    lines.append("Generated by `tools/devsurface/build_index.py` on %s." % dt.date.today().isoformat())
    lines.append("")
    lines.append("This report is generated. It states what has been extracted, what each page")
    lines.append("was classified as, and which evidence is still missing. Nothing here is an")
    lines.append("estimate: every number is a count over the records in `devsurface/data/`.")
    lines.append("")
    lines.append("## Pages processed")
    lines.append("")
    lines.append("| source id | pages | symbol pages | other pages | symbol records |")
    lines.append("|---|---:|---:|---:|---:|")
    for book in sorted(pages_by_book):
        rows_ = pages_by_book[book]
        symbol_pages = sum(1 for row in rows_ if row["page_class"] == "symbol_page")
        lines.append("| `%s` | %d | %d | %d | %d |" % (
            book, len(rows_), symbol_pages, len(rows_) - symbol_pages,
            records_by_book.get(book, 0)))
    lines.append("| **total** | **%d** | | | **%d** |" % (
        total_pages, sum(records_by_book.values())))
    lines.append("")
    lines.append("## Page classification")
    lines.append("")
    lines.append("| page class | pages | meaning |")
    lines.append("|---|---:|---|")
    meanings = {
        "symbol_page": "a symbol record was extracted from this page",
        "concept_or_overview": "prose topic (overview, how-to, guide); no symbol documented",
        "identifier_title_no_requirements": "identifier-looking title, but the page carries no requirements block",
        "identifier_title_no_declaration": "identifier-looking title, requirements present, no declaration found",
        "declaration_candidate_mismatch": "a declaration-shaped block exists whose identifier differs from the page title (kept as a gap)",
        "out_of_scope_managed_surface": "managed/.NET reference page: outside the include/def/lib surface",
        "deprecation_notice": "page whose title marks a deprecated symbol",
        "example_code_page": "diagnostic topic (compiler/linker/make error) whose code blocks are examples, not declarations",
        "duplicate_page": "second copy of a page already parsed under its canonical file name",
    }
    for name, count in classes.most_common():
        lines.append("| `%s` | %d | %s |" % (name, count, meanings.get(name, "")))
    lines.append("")
    lines.append("## Symbol records")
    lines.append("")
    lines.append("| kind | records |")
    lines.append("|---|---:|")
    for name, count in kinds.most_common():
        lines.append("| `%s` | %d |" % (name, count))
    lines.append("| **total** | **%d** |" % sum(kinds.values()))
    lines.append("")
    lines.append("| declaration parse status | records |")
    lines.append("|---|---:|")
    for name, count in parse_status.most_common():
        lines.append("| `%s` | %d |" % (name, count))
    lines.append("")
    lines.append("## Version statements")
    lines.append("")
    lines.append("| what differs | symbols | list |")
    lines.append("|---|---:|---|")
    lines.append("| normalised version ids (primary) | %d | `devsurface/index/version-differences-normalized.tsv` |"
                 % len(differences.get("mapped", [])))
    lines.append("| documented text after punctuation normalisation | %d | `devsurface/index/version-differences.tsv` |"
                 % len(differences.get("text", [])))
    lines.append("| wording only (same version ids) | %d | `devsurface/index/version-differences-text-only.tsv` |"
                 % len(differences.get("text_only", [])))
    lines.append("")
    lines.append("Both are documented differences between collections. A raw-text difference")
    lines.append("is not automatically a generation difference (one collection writes")
    lines.append("`1.0 and later`, another `Windows CE 1.0 and later.`). Conversely two")
    lines.append("identical texts in different collections are not evidence that the")
    lines.append("interface was available in both -- only that both topics say the same thing.")
    lines.append("")
    lines.append("Symbols documented in more than one collection: see")
    lines.append("`devsurface/index/symbols-across-books.tsv`.")
    lines.append("")
    lines.append("## Not covered by this database")
    lines.append("")
    for line in [
        "Values that the documentation never states, and that therefore stay `unknown`:",
        "",
        "* export names, ordinals and decorated symbol names,",
        "* import-library membership per module (a lower bound only: `Link Library` is what a",
        "  topic says, not what an import library actually exports),",
        "* DLL/module names (`DLL`/`Module` labels appear on very few topics),",
        "* calling conventions and ABI/layout facts (only macro tokens printed inside a",
        "  declaration are recorded, never an ABI conclusion),",
        "* structure offsets, packing and alignment (member lists are recorded, offsets are not),",
        "",
        "Collections catalogued but not parsed for symbols:",
        "",
        "| collection | reason |",
        "|---|---|",
    ]:
        lines.append(line)
    for record in source_records:
        if record["scope"] != "extracted":
            lines.append("| `%s` | %s |" % (record["id"], record["out_of_scope_reason"] or record["scope"]))
    lines.append("")
    lines.append("## Open extraction gaps inside the covered collections")
    lines.append("")
    gaps = collections.Counter()
    for rows_ in pages_by_book.values():
        for row in rows_:
            if row["page_class"] != "symbol_page" and row["symbol"]:
                gaps[row["page_class"]] += 1
    for name, count in gaps.most_common():
        lines.append("* `%s`: %d pages — see `devsurface/index/gap-pages.tsv`." % (name, count))
    lines.append("")
    lines.append("Every page row carries the raw `os_versions_raw`, `header`, `library` and")
    lines.append("`declaration_status` values, so a gap can be traced back to the page.")
    lines.append("")
    with open(COVERAGE_MD, "w", encoding="utf-8") as handle:
        handle.write("\n".join(lines))
    log("wrote %s" % os.path.relpath(COVERAGE_MD, ROOT))


def write_gaps(log):
    unknown = collections.Counter()
    total = 0
    for book in book_files():
        for record in load_symbols(book):
            total += 1
            for name in record.get("uncertainty", {}).get("unknown_fields", []):
                unknown[name] += 1
    lines = ["# Unverified fields (generated)", "",
             "Counts are over %d symbol records. A field listed here has no documented" % total,
             "value in the corpus; it is recorded as `unknown` rather than filled in.", "",
             "| field | records without a documented value |", "|---|---:|"]
    for name, count in unknown.most_common():
        lines.append("| `%s` | %d |" % (name, count))
    lines.append("")
    lines.append("## What would close each gap")
    lines.append("")
    lines.append("| field | evidence that could establish it |")
    lines.append("|---|---|")
    lines.append("| `calling_convention` | a rights-cleared header or a compiled artifact that "
                 "prints the convention; never inferable from the API name |")
    lines.append("| `export.name` / `export.ordinal` / `export.decorated_name` | a module's export "
                 "table (observed) or a rights-cleared `.def` |")
    lines.append("| `module` | a topic that states the DLL, or an observed import table |")
    lines.append("| `header` / `library` | a topic with a Requirements block; many topics omit it |")
    lines.append("| `abi.*` | a document that states the data model, packing or layout for the "
                 "target CPU |")
    lines.append("")
    with open(GAPS_MD, "w", encoding="utf-8") as handle:
        handle.write("\n".join(lines))
    log("wrote %s" % os.path.relpath(GAPS_MD, ROOT))


def write_index_pages(source_records, shard_manifest, log):
    """shard_manifest rows are (shard_name, filename, record_count)."""
    os.makedirs(INDEX, exist_ok=True)
    # gap pages
    with open(os.path.join(INDEX, "gap-pages.tsv"), "w", encoding="utf-8") as handle:
        handle.write("#page_class\tpage_id\tsource_id\ttitle\tdeclaration_status\tpath\n")
        for name in sorted(os.listdir(PAGES)):
            if not name.endswith(".tsv"):
                continue
            for row in load_pages(name[:-4]):
                if row["page_class"] != "symbol_page":
                    handle.write("%s\t%s\t%s\t%s\t%s\t%s\n" % (
                        row["page_class"], row["page_id"], row["source_id"], row["title"],
                        row["declaration_status"], row["path"]))
    # index navigation
    lines = ["# Index navigation (generated)", "",
             "| file | contents |", "|---|---|",
             "| `devsurface.sqlite3` | all tables (symbols, parameters, members, enumerators, version_statements, pages, sources, abi_facts) |",
             "| `shards.tsv` | header shard files and record counts |",
             "| `symbols-across-books.tsv` | one row per symbol with per-collection kind/header/library |",
             "| `version-differences-normalized.tsv` | symbols whose normalised version ids differ per collection (primary) |",
             "| `version-differences.tsv` | symbols whose documented version text differs after punctuation normalisation |",
             "| `version-differences-text-only.tsv` | same version ids, different wording |",
             "| `by-header.md` | headers with record counts and example symbols |",
             "| `by-library.md` | link libraries with record counts |",
             "| `by-book.md` | records per collection |",
             "| `gap-pages.tsv` | every page that produced no symbol record, with its classification |",
             "", "## Header shards", "",
             "| shard | records |", "|---|---:|"]
    for shard, filename, count in shard_manifest:
        lines.append("| `devsurface/data/symbols/%s` | %d |" % (filename, count))
    lines.append("")
    with open(os.path.join(INDEX, "INDEX.md"), "w", encoding="utf-8") as handle:
        handle.write("\n".join(lines))

    counters = {
        "by-header.md": ("Headers", "header"),
        "by-library.md": ("Link libraries", "library"),
        "by-book.md": ("Collections", "source_id"),
    }
    for filename, (title, key) in counters.items():
        counts = collections.Counter()
        examples = collections.defaultdict(list)
        for book in book_files():
            for record in load_symbols(book):
                if key == "header":
                    value = (record.get("header") or {}).get("value")
                elif key == "library":
                    values = [v for entry in record.get("libraries") or []
                              for v in (entry.get("values") or [])]
                    value = values[0] if values else None
                else:
                    value = record["source"]["source_id"]
                if not value:
                    value = "(not documented)"
                counts[value] += 1
                if len(examples[value]) < 6:
                    examples[value].append(record.get("symbol"))
        lines = ["# %s (generated)" % title, "",
                 "| %s | records | example symbols |" % key, "|---|---:|---|"]
        for value, count in counts.most_common():
            lines.append("| `%s` | %d | %s |" % (
                value, count, ", ".join("`%s`" % e for e in examples[value] if e)))
        lines.append("")
        with open(os.path.join(INDEX, filename), "w", encoding="utf-8") as handle:
            handle.write("\n".join(lines))
    log("wrote index pages under %s" % os.path.relpath(INDEX, ROOT))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--skip-sqlite", action="store_true")
    parser.add_argument("--skip-crossbook", action="store_true")
    args = parser.parse_args()

    def log(message):
        print(message, flush=True)

    os.makedirs(INDEX, exist_ok=True)
    shard_manifest = merge_shards(log)
    source_records = write_sources(log)
    crossbook_rows, differences = [], {}
    if not args.skip_crossbook:
        crossbook_rows, differences = write_crossbook(log)
    if not args.skip_sqlite:
        write_sqlite(source_records, log)
    write_coverage(crossbook_rows, differences, source_records, log)
    write_gaps(log)
    write_index_pages(source_records, shard_manifest, log)


if __name__ == "__main__":
    main()
