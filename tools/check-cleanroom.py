#!/usr/bin/env python3
"""Check the knowledge base against the clean-room invariants.

The definition, the cases and the reasoning are in ``docs/clean-room.md``.
This tool is the machine-checkable half: it asks the six questions that decide
whether ``knowledge/`` is a *specification* a second party could implement
from without the original pages, and whether the generator actually restricts
itself to that specification.

1. **No fact without a document.**  Every record's ``source.path`` -- and every
   page an entity lists -- exists in ``corpus/``.
2. **Quotes are faithful.**  The characters of a quoted declaration, a
   requirement value, a constraint sentence, a layout-table row or a
   constant-table row, in order and whitespace aside, are on the page the
   record names (1 in N by default, ``--all`` for every record).
3. **Documented members are on their page.**  Every ``documented_fields`` name
   occurs in one of the pages that document the entity (an A/W pair documents
   one structure).
4. **Sample code stays out of the declarations.**  No entity's
   ``syntax_declarations`` points at a ``role: "example"`` record, and no
   ``role: "syntax"`` record is implementation code.
5. **The generator reads the specification only.**  A real
   ``gen-include-def.py`` run reports zero pages read under ``corpus/``.
6. (Reported beside 4.) How many ``role: "example"`` blocks are implementation
   code and are therefore quarantined: kept as evidence, never emitted.

Usage::

    python3 tools/check-cleanroom.py            # sample 1 in 25 for quotes
    python3 tools/check-cleanroom.py --all      # every record
    python3 tools/check-cleanroom.py --no-generator --list 20
"""

import argparse
import collections
import gzip
import html
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

import page_parse  # noqa: E402

KB = os.path.join(ROOT, "knowledge", "kb")
REPORTS = os.path.join(ROOT, "knowledge", "reports")

FILES = {
    "entity": "entities.jsonl.gz",
    "declaration": "declarations.jsonl.gz",
    "declaration_dotnet": "declarations-dotnet.jsonl.gz",
    "requirement": "requirements.jsonl.gz",
    "constraint": "constraints.jsonl.gz",
    "abi_offset": "abi-offsets.jsonl.gz",
    "constant": "constants.jsonl.gz",
}

# A statement form in a *declaration* would mean the extractor took a line of
# code into the interface material.  The extractor's own test is the source of
# truth (page_parse.is_implementation); this pattern is only used to point at
# the offending word in a report line.
STATEMENT = re.compile(
    r"\b(return|if|for|while|switch|goto|break|continue)\b")


class Pages:
    """Corpus pages as text, read once and remembered (LRU by insertion)."""

    def __init__(self, limit=4000):
        self.limit = limit
        self.cache = collections.OrderedDict()

    def text(self, path):
        if path in self.cache:
            return self.cache[path]
        full = os.path.join(ROOT, path)
        try:
            with open(full, "rb") as fh:
                raw = fh.read()
        except OSError:
            return None
        # Read the page the way the knowledge base read it: the raw markdown
        # for a .md page, the article HTML with its tags removed for a .html
        # page.  Nothing else is changed (decoding the entities again here
        # would turn &param1 into the paragraph sign and break the compare).
        if path.endswith(".md"):
            text = page_parse.decode(raw)
        else:
            text = page_parse.text_of(page_parse.article_html(raw))
        text = re.sub(r"\s+", " ", text).strip()
        self.cache[path] = text
        while len(self.cache) > self.limit:
            self.cache.popitem(last=False)
        return text


def load_records(reports=None):
    records = {}
    for kind, filename in FILES.items():
        records[kind] = [json.loads(line) for line in _lines(filename)]
    if reports is not None:
        reports.append((filename, len(records[kind])))
    return records


def _lines(filename):
    path = os.path.join(KB, filename)
    if not os.path.exists(path) and path.endswith(".gz"):
        path = path[:-3]
    opener = gzip.open if path.endswith(".gz") else open
    with opener(path, "rt", encoding="utf-8") as fh:
        for line in fh:
            line = line.strip()
            if line:
                yield line


def sample(records, every):
    if every <= 1:
        return records
    return [r for i, r in enumerate(records) if i % every == 0]


def flat(text):
    return re.sub(r"\s+", "", text or "")


def check_sources(records):
    """Every record names a page that is in the corpus."""
    checked = 0
    missing = []
    for kind in ("declaration", "declaration_dotnet", "requirement",
                 "constraint", "abi_offset", "constant"):
        for record in records[kind]:
            path = (record.get("source") or {}).get("path")
            checked += 1
            if not path or not os.path.exists(os.path.join(ROOT, path)):
                missing.append(f"{kind} {record.get('id')}: "
                               f"source {path!r} is not in the repository")
    for entity in records["entity"]:
        pages = [p for field in ("ce_pages", "win32_pages", "dotnet_pages",
                                 "win32_pages_from_variants")
                 for p in entity.get(field, ())]
        checked += len(pages)
        if not pages:
            missing.append(f"entity {entity['id']}: lists no page")
        for path in pages:
            if not os.path.exists(os.path.join(ROOT, path)):
                missing.append(f"entity {entity['id']}: page {path} is not in "
                               "the repository")
    return checked, missing


def check_quotes(records, pages, every):
    """The record's characters, in order, are on the page it names."""
    checked = not_found = 0
    details = []
    for kind, field in (("declaration", "text"), ("requirement", "value"),
                        ("constraint", "text"), ("abi_offset", "row"),
                        ("constant", "row")):
        for record in sample(records[kind], every):
            text = record.get(field) or ""
            if not text.strip():
                continue
            path = (record.get("source") or {}).get("path")
            page = pages.text(path) if path else None
            checked += 1
            if page is None or flat(text) not in flat(page):
                not_found += 1
                if len(details) < 10:
                    details.append(f"{kind} {record.get('id')}: {text[:60]!r} "
                                   f"not on {path}")
    return checked, not_found, details


def check_module_rows(pages):
    """Each kb/modules-ce.tsv row quotes the module page it names.

    The module table is a TSV, so it is not in ``load_records``; the same
    two invariants apply to it -- the page exists, and the quoted row is on
    that page.
    """
    path = os.path.join(KB, "modules-ce.tsv")
    checked = bad = 0
    details = []
    if not os.path.exists(path):
        return checked, bad, details
    with open(path, encoding="utf-8") as fh:
        header = fh.readline().rstrip("\n").split("\t")
        try:
            page_column = header.index("page")
            quote_column = header.index("quote")
            value_column = header.index("value")
        except ValueError:
            return checked, 1, ["modules-ce.tsv: unexpected columns"]
        for line in fh:
            cells = line.rstrip("\n").split("\t")
            if len(cells) <= max(page_column, quote_column, value_column):
                continue
            page_path = cells[page_column]
            text = pages.text(page_path)
            checked += 1
            if text is None:
                bad += 1
                if len(details) < 10:
                    details.append(f"modules-ce.tsv: page {page_path} is not "
                                   "in the repository")
                continue
            for field in (quote_column, value_column):
                if cells[field] and flat(cells[field]) not in flat(text):
                    bad += 1
                    if len(details) < 10:
                        details.append(f"modules-ce.tsv: {cells[field][:50]!r} "
                                       f"not on {page_path}")
                    break
    return checked, bad, details


def check_documented_fields(records, pages):
    """A documented member name is on one of the pages that documents it."""
    checked = not_found = 0
    details = []
    for entity in records["entity"]:
        if not entity.get("documented_fields"):
            continue
        candidate_pages = entity.get("documented_fields_pages") or [
            entity.get("documented_fields_page")]
        texts = [pages.text(path) for path in candidate_pages if path]
        texts = [text for text in texts if text is not None]
        checked += len(entity["documented_fields"])
        if not texts:
            not_found += len(entity["documented_fields"])
            continue
        for name in entity["documented_fields"]:
            token = re.compile(r"\b" + re.escape(name) + r"\b")
            if not any(token.search(text) or name in text for text in texts):
                not_found += 1
                if len(details) < 10:
                    details.append(f"entity {entity['id']}: member {name!r} "
                                   f"not on {', '.join(candidate_pages)}")
    return checked, not_found, details


def check_separation(records):
    """Sample code stays out of the declarations; declarations are declarations."""
    bad_role = []
    declarations = records["declaration"] + records["declaration_dotnet"]
    by_id = {r["id"]: r for r in declarations}
    for entity in records["entity"]:
        for rid in entity.get("syntax_declarations", ()):
            record = by_id.get(rid)
            if record is None:
                bad_role.append(f"entity {entity['id']}: {rid} missing")
            elif record["role"] != "syntax":
                bad_role.append(f"entity {entity['id']}: {rid} has role "
                                f"{record['role']!r}")
            elif record.get("implementation"):
                bad_role.append(f"entity {entity['id']}: {rid} is "
                                "implementation code")
    statements = []
    quarantined = 0
    for record in declarations:
        text = record.get("text") or ""
        if not text.strip() or record.get("kind") == "macro":
            continue
        implementation = record.get("implementation")
        if implementation:
            if record.get("role") != "example":
                statements.append(f"declaration {record['id']}: "
                                  "implementation code with role "
                                  f"{record.get('role')!r}")
            else:
                quarantined += 1
            continue
        match = STATEMENT.search(text)
        if match and page_parse.is_implementation(text):
            statements.append(f"declaration {record['id']}: "
                              f"{match.group(1)!r} in {text[:50]!r}")
    return bad_role, statements, quarantined


def check_generator(use_generator):
    """A real generation run must read zero pages under corpus/."""
    if not use_generator:
        return None, []
    out = tempfile.mkdtemp(prefix="cleanroom-")
    try:
        result = subprocess.run(
            [sys.executable, os.path.join(ROOT, "tools", "gen-include-def.py"),
             "--set", "learn/windows-ce-5.0", "--limit", "300",
             "--out", out],
            cwd=ROOT, capture_output=True, text=True)
        report = os.path.join(out, "report.md")
        if result.returncode != 0 or not os.path.exists(report):
            return 0, [f"gen-include-def.py failed: "
                       f"{(result.stderr or result.stdout).strip()[:200]}"]
        with open(report, encoding="utf-8") as fh:
            text = fh.read()
    finally:
        shutil.rmtree(out, ignore_errors=True)
    reads = 0
    problems = []
    match = re.search(r"corpus pages read by this generator:\s*\*\*(\d+)\*\*",
                      text)
    if not match:
        problems.append("the generator report does not state the corpus reads")
    else:
        reads = int(match.group(1))
        if reads:
            problems.append(f"the generator read {reads} corpus page(s)")
    if "implementation code" in text:
        problems.append("the generator report lists implementation-code skips: "
                        "the extractor should have caught them")
    return reads, problems


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    parser.add_argument("--all", action="store_true",
                        help="check every quote, not a sample")
    parser.add_argument("--every", type=int, default=25,
                        help="quote sampling step (default 25)")
    parser.add_argument("--no-generator", action="store_true",
                        help="skip the generator run")
    parser.add_argument("--list", type=int, default=10,
                        help="how many violation details to print")
    args = parser.parse_args()

    records = load_records()
    pages = Pages()
    every = 1 if args.all else max(1, args.every)

    sources_checked, missing = check_sources(records)
    quotes_checked, quotes_bad, quote_details = check_quotes(records, pages,
                                                             every)
    fields_checked, fields_bad, field_details = check_documented_fields(
        records, pages)
    modules_checked, modules_bad, module_details = check_module_rows(pages)
    bad_role, statement_details, quarantined = check_separation(records)
    reads, generator_problems = check_generator(not args.no_generator)

    rows = [
        ("no fact without a document", sources_checked, len(missing),
         "every record's source.path (an entity: every page it lists) exists "
         "in corpus/"),
        ("quotes are faithful (whitespace aside)", quotes_checked, quotes_bad,
         "the record's characters, in order, are on the page it names "
         f"({'all records' if args.all else f'1 in {every}'})"),
        ("documented members are on their page", fields_checked, fields_bad,
         "each documented_fields name occurs in one of the pages that "
         "document the entity (an A/W pair documents one structure)"),
        ("module rows quote their module page", modules_checked, modules_bad,
         "each kb/modules-ce.tsv row names a page in corpus/ and its quoted "
         "row and value are on that page"),
        ("sample code stays out of the declarations",
         sum(len(e.get("syntax_declarations", ()))
             for e in records["entity"]), len(bad_role),
         "no syntax_declarations record is a role 'example' or implementation "
         "record"),
        ("syntax blocks are declarations", None, len(statement_details),
         "no role='syntax' text is implementation code; kept as role 'example' "
         f"and never emitted: {quarantined:,}"),
        ("the generator reads the specification only", reads,
         len(generator_problems),
         "a real gen-include-def.py run reports zero corpus reads "
         f"({'skipped' if args.no_generator else 'run'})"),
    ]
    os.makedirs(REPORTS, exist_ok=True)
    with open(os.path.join(REPORTS, "cleanroom.tsv"), "w",
              encoding="utf-8") as fh:
        fh.write("# invariant\tchecked\tviolations\tnote\n")
        for name, checked, violations, note in rows:
            fh.write(f"{name}\t{'' if checked is None else checked}\t"
                     f"{violations}\t{note}\n")

    problems = 0
    print("clean-room invariants (docs/clean-room.md):")
    for name, checked, violations, note in rows:
        shown = "-" if checked is None else f"{checked:,}"
        print(f"  {name:44s} checked {shown:>9s}  violations {violations:,}")
        problems += violations
    for label, details in (("source", missing), ("quote", quote_details),
                           ("member", field_details),
                           ("module", module_details),
                           ("role", bad_role[:args.list]),
                           ("statement", statement_details[:args.list]),
                           ("generator", generator_problems)):
        for detail in details[:args.list]:
            print(f"    {label}: {detail}")
    print(f"cleanroom.tsv written; {problems} violation(s)")
    return 1 if problems else 0


if __name__ == "__main__":
    raise SystemExit(main())
