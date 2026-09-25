#!/usr/bin/env python3
"""tools/devsurface/validate.py -- verify the Development Surface database.

Checks, in order:

  1. structural/schema checks over every symbol record (required fields, enum
     vocabularies, id formula, uncertainty rules),
  2. cross-file checks (page coverage TSV column count, shard placement, source
     registry references, ABI facts),
  3. optional verbatim verification: the stored declaration must still be found
     in the page it was read from.

Errors are fatal (exit status 1). A run that reports "OK" states that the
database is internally consistent -- not that the documentation is complete.

Usage:
  python3 tools/devsurface/validate.py
  python3 tools/devsurface/validate.py --verify-declarations 2000
  python3 tools/devsurface/validate.py --verify-declarations all
"""

from __future__ import annotations

import argparse
import glob
import hashlib
import json
import os
import re
import sys
from concurrent.futures import ProcessPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import extract as E  # noqa: E402
import vocab  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SYMBOLS = os.path.join(ROOT, "devsurface", "data", "symbols")
PAGES = os.path.join(ROOT, "devsurface", "data", "pages")
SOURCES = os.path.join(ROOT, "devsurface", "data", "sources.json")
ABI = os.path.join(ROOT, "devsurface", "data", "abi", "abi-facts.jsonl")
MANIFEST = os.path.join(ROOT, "devsurface", "data", "manifest.json")

REQUIRED = [
    "schema_version", "id", "symbol", "kind", "declaration", "declaration_origin",
    "documentation_role",
    "parse", "header", "libraries", "module", "export", "calling_convention",
    "version_availability", "uncertainty", "source", "evidence", "extraction",
    "compaction",
]
KIND_VALUES = set(vocab.KINDS)

ERRORS = []
WARNINGS = []


def error(message):
    ERRORS.append(message)


def warn(message):
    WARNINGS.append(message)


DOCUMENTATION_ROLES = set(vocab.DOCUMENTATION_ROLES)
PAGE_CLASS_VALUES = set(vocab.PAGE_CLASSES)


def check_record(record, shard_name):
    for field in REQUIRED:
        if field not in record:
            error("%s: missing field %s" % (record.get("id", "?"), field))
            return
    if record["schema_version"] != vocab.SCHEMA_VERSION:
        error("%s: schema_version %r" % (record["id"], record["schema_version"]))
    if record["kind"] not in KIND_VALUES:
        error("%s: kind %r not in vocabulary" % (record["id"], record["kind"]))
    if record.get("page_class") not in PAGE_CLASS_VALUES:
        error("%s: page_class %r not in vocabulary" % (record["id"], record.get("page_class")))
    if record.get("documentation_role") not in DOCUMENTATION_ROLES:
        error("%s: documentation_role %r not in vocabulary"
              % (record["id"], record.get("documentation_role")))
    parse_status = record["parse"]["status"]
    if parse_status not in ("parsed", "partial", "no_declaration_documented", "unsupported"):
        error("%s: parse.status %r" % (record["id"], parse_status))
    page_path = record["source"]["page_path"]
    if not os.path.exists(os.path.join(ROOT, page_path)):
        error("%s: page_path does not exist: %s" % (record["id"], page_path))
    if record["source"]["source_id"] not in vocab.SOURCES:
        error("%s: unknown source_id %s" % (record["id"], record["source"]["source_id"]))
    if not record.get("evidence"):
        error("%s: no evidence entry" % record["id"])
    # id formula
    expected = "sym-" + hashlib.sha1((
        "%s|%s|%s|%s" % (record["source"]["source_id"], record["source"]["page_id"],
                         record["symbol"], (record["declaration"] or "")[:400])
    ).encode("utf-8")).hexdigest()[:16]
    if expected != record["id"]:
        error("%s: id does not match its content (expected %s)" % (record["id"], expected))
    # uncertainty rules: a listed unknown field must be empty in the record
    unknown = set(record["uncertainty"]["unknown_fields"])
    if not unknown:
        warn("%s: no unknown fields listed" % record["id"])
    if "calling_convention" in unknown and record["calling_convention"]["value"] is not None:
        error("%s: calling_convention listed unknown but carries a value" % record["id"])
    if "export.name" in unknown and record["export"]["name"] is not None:
        error("%s: export.name listed unknown but carries a value" % record["id"])
    if "module" in unknown and record["module"]:
        error("%s: module listed unknown but carries a value" % record["id"])
    if "library" in unknown and record["libraries"]:
        error("%s: library listed unknown but carries a value" % record["id"])
    if "header" in unknown and record["header"]:
        error("%s: header listed unknown but carries a value" % record["id"])
    if "declaration" in unknown and record["declaration"]:
        error("%s: declaration listed unknown but carries a value" % record["id"])
    # version statements: a mapped statement must resolve to a known version id
    known_ids = {entry["version_id"] for entry in vocab.VERSION_VOCAB.values()}
    for statement in record["version_availability"]["statements"]:
        normalized = statement.get("normalized") or {}
        if normalized.get("status") == "mapped" and normalized.get("version_id") not in known_ids:
            error("%s: mapped version statement without a vocabulary id: %r"
                  % (record["id"], normalized.get("version_id")))
        if normalized.get("status") == "unmapped" and normalized.get("version_id"):
            error("%s: unmapped statement carries a version id" % record["id"])
        if statement["field"] not in ("os_versions", "platform", "header", "include",
                                      "library", "module", "namespace", "assembly",
                                      "compatibility"):
            error("%s: statement field %r" % (record["id"], statement["field"]))
    # shard placement
    expected_shard = vocab.record_shard(record)
    if expected_shard != shard_name:
        error("%s: stored in shard %s but its header maps to %s"
              % (record["id"], shard_name, expected_shard))
    # ABI must stay empty unless a page stated it
    abi = record["abi"]
    if abi.get("evidence_status") != "unknown":
        if not abi.get("architecture") and not abi.get("data_model") \
                and not abi.get("packing") and not abi.get("structure_layout"):
            error("%s: abi.evidence_status is not unknown but no abi value is set" % record["id"])
    # interface_method records must name a scope
    if record["kind"] == "interface_method" and not record.get("scope"):
        warn("%s: interface_method without scope" % record["id"])


# devsurface/data/pages/<book>.tsv column count (see build_index.PAGE_HEADER and
# devsurface/METHODOLOGY.md section 6). A short row means the book was extracted
# with an older tools/devsurface/extract.py; re-run it with --force.
PAGE_COLUMNS_EXPECTED = 15


def check_pages():
    """Page coverage rows: column count and page_class vocabulary."""
    for name in sorted(os.listdir(PAGES)):
        if not name.endswith(".tsv"):
            continue
        header = None
        with open(os.path.join(PAGES, name), encoding="utf-8") as handle:
            for number, line in enumerate(handle, start=1):
                if line.startswith("#"):
                    header = len(line.rstrip("\n").split("\t"))
                    if header != PAGE_COLUMNS_EXPECTED:
                        error("%s: header has %d columns, expected %d -- re-run "
                              "tools/devsurface/extract.py --book %s --force"
                              % (name, header, PAGE_COLUMNS_EXPECTED, name[:-4]))
                    continue
                fields = line.rstrip("\n").split("\t")
                if len(fields) != PAGE_COLUMNS_EXPECTED:
                    error("%s:%d: %d columns, expected %d -- re-run "
                          "tools/devsurface/extract.py --book %s --force"
                          % (name, number, len(fields), PAGE_COLUMNS_EXPECTED, name[:-4]))
                    break
                if fields[4] not in PAGE_CLASS_VALUES:
                    error("%s:%d: page_class %r not in vocabulary"
                          % (name, number, fields[4]))
                    break


def check_sources():
    document = json.loads(open(SOURCES, encoding="utf-8").read())
    ids = [record["id"] for record in document["records"]]
    if len(ids) != len(set(ids)):
        error("sources.json: duplicate source ids")
    for source_id in vocab.SOURCES:
        if source_id not in ids:
            error("sources.json: missing %s" % source_id)
    manifest = json.loads(open(MANIFEST, encoding="utf-8").read())
    if manifest.get("records", 0) <= 0:
        error("manifest.json: no records recorded")
    return document


def check_abi():
    if not os.path.exists(ABI):
        warn("no abi facts file")
        return 0
    count = 0
    for line in open(ABI, encoding="utf-8"):
        if not line.strip():
            continue
        fact = json.loads(line)
        count += 1
        if fact.get("evidence_status") != "documented":
            error("%s: abi fact without documented status" % fact.get("id"))
        if not os.path.exists(os.path.join(ROOT, fact["page_path"])):
            error("%s: abi fact page does not exist" % fact.get("id"))
        if not fact.get("statement"):
            error("%s: abi fact without statement" % fact.get("id"))
    return count


# --------------------------------------------------------------------------
# verbatim declaration verification
# --------------------------------------------------------------------------

def verify_one(job):
    page_path, declaration, record_id = job
    full = os.path.join(ROOT, page_path)
    try:
        with open(full, encoding="utf-8", errors="replace") as handle:
            html = handle.read()
    except OSError as error_:
        return record_id, "page unreadable: %s" % error_
    soup = E.load_soup(html)
    text = E.node_text(E.prune(E.content_root(soup)))
    needle = E.ws(declaration)[:200]
    if needle and needle in text:
        return record_id, None
    # The page may normalise differently (e.g. the glued-identifier forms):
    # compare with all whitespace removed as a fallback.
    compact_page = "".join(text.split())
    compact_needle = "".join(needle.split())
    if compact_needle and compact_needle in compact_page:
        return record_id, None
    return record_id, "declaration not found in page"


def verify_declarations(limit):
    jobs = []
    for path in sorted(glob.glob(os.path.join(SYMBOLS, "*.jsonl"))):
        with open(path, encoding="utf-8") as handle:
            for line in handle:
                record = json.loads(line)
                if not record.get("declaration"):
                    continue
                jobs.append((record["source"]["page_path"], record["declaration"], record["id"]))
    if limit != "all":
        limit = int(limit)
        if len(jobs) > limit:
            jobs = [job for job in jobs
                    if int(hashlib.sha1(job[2].encode()).hexdigest(), 16) % len(jobs) < limit][:limit]
    print("verifying %d declarations against their pages" % len(jobs))
    checked = failed = 0
    with ProcessPoolExecutor(max_workers=max(1, min(4, os.cpu_count() or 1))) as pool:
        for record_id, problem in pool.map(verify_one, jobs, chunksize=16):
            checked += 1
            if problem:
                failed += 1
                if failed <= 20:
                    error("%s: %s" % (record_id, problem))
    print("declaration verification: %d checked, %d not found" % (checked, failed))
    return failed


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--verify-declarations", default="0",
                        help="0, a sample size, or 'all'")
    parser.add_argument("--jobs", type=int, default=max(1, min(4, os.cpu_count() or 1)))
    arguments = parser.parse_args()

    records = 0
    for path in sorted(glob.glob(os.path.join(SYMBOLS, "*.jsonl"))):
        # A shard larger than SHARD_SPLIT_BYTES is written as <shard>.part-NN.jsonl;
        # the record's own `shard` field always carries the unsplit name.
        shard = re.sub(r"\.part-\d+$", "", os.path.basename(path)[:-len(".jsonl")])
        with open(path, encoding="utf-8") as handle:
            for line in handle:
                line = line.strip()
                if not line:
                    continue
                records += 1
                check_record(json.loads(line), shard)
    print("checked %d symbol records" % records)
    check_pages()
    sources = check_sources()
    abi_count = check_abi()
    print("checked %d sources, %d abi facts" % (len(sources["records"]), abi_count))
    if arguments.verify_declarations != "0":
        verify_declarations(arguments.verify_declarations)
    for message in WARNINGS[:20]:
        print("WARN: %s" % message)
    if len(WARNINGS) > 20:
        print("WARN: ... %d more warnings" % (len(WARNINGS) - 20))
    if ERRORS:
        for message in ERRORS[:40]:
            print("ERROR: %s" % message)
        if len(ERRORS) > 40:
            print("ERROR: ... %d more errors" % (len(ERRORS) - 40))
        print("FAILED: %d errors, %d warnings" % (len(ERRORS), len(WARNINGS)))
        return 1
    print("OK: %d records validated, %d warnings" % (records, len(WARNINGS)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
