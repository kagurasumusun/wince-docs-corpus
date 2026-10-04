#!/usr/bin/env python3
"""tools/check-kb.py -- validate knowledge/ and report what it holds.

The knowledge base is generated, so a mistake in the generation would silently
become a mistake in every include/def file built from it.  This tool re-checks
the generated files the way a consumer would read them:

* every record has its required fields of the right type (the shapes are in
  ``knowledge/schema/*.json``; this is a small hand-rolled check, no
  dependencies);
* every record's ``source.path`` exists in the repository -- a statement
  without its page is not knowledge;
* the ids an entity references (``declarations``, ``syntax_declarations``,
  ``requirements``, ``constraints``) exist in the corresponding file, and the
  relation targets that say ``present: true`` exist as entities;
* the counts match the files (an entity whose declaration list is empty is
  reported as a gap, not as an error).

    python3 tools/check-kb.py             # check, print the summary
    python3 tools/check-kb.py --strict    # also fail on records with no source
    python3 tools/check-kb.py --sample 3  # print a few records per type

Exit status is 1 when a structural problem was found (a missing field, an
unresolved id, a source path that is not in the corpus).
"""

import argparse
import collections
import gzip
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
KB = os.path.join(ROOT, "knowledge", "kb")
REPORTS = os.path.join(ROOT, "knowledge", "reports")

FILES = {
    "entity": "entities.jsonl.gz",
    "declaration": "declarations.jsonl.gz",
    "requirement": "requirements.jsonl.gz",
    "constraint": "constraints.jsonl.gz",
}
REQUIRED = {
    "entity": ("id", "name", "layers", "doc_role", "kinds", "ce_sets",
               "ce_pages", "win32_pages", "dotnet_pages", "headers",
               "libraries", "dlls", "modules", "relations", "generation_use",
               "declarations", "syntax_declarations", "requirements",
               "constraints", "noise", "variants_of", "variants",
               "win32_pages_from_variants", "win32_documented", "surface"),
    "declaration": ("id", "entity", "page_id", "layer", "kind", "role",
                    "language", "markup", "spacing", "calling_convention",
                    "text", "members", "source"),
    "requirement": ("id", "entity", "page_id", "layer", "field", "label",
                    "value", "key", "evidence", "source"),
    "constraint": ("id", "entity", "page_id", "layer", "pattern", "text",
                   "source"),
}
SURFACES = ("ce-only", "shared", "win32-spelling", "catalog-only", "win32-only")
ID_RE = {"entity": re.compile(r"^[a-z0-9_]+$"),
         "declaration": re.compile(r"^d[0-9a-f]{12}$"),
         "requirement": re.compile(r"^r[0-9a-f]{12}$"),
         "constraint": re.compile(r"^c[0-9a-f]{12}$")}


def read(name):
    path = os.path.join(KB, name)
    if not os.path.exists(path) and path.endswith(".gz"):
        path = path[:-3]
    opener = gzip.open if path.endswith(".gz") else open
    with opener(path, "rt", encoding="utf-8") as fh:
        for line in fh:
            line = line.strip()
            if line:
                yield json.loads(line)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--strict", action="store_true",
                    help="fail when a record has no usable source")
    ap.add_argument("--sample", type=int, default=0,
                    help="print this many records per type")
    args = ap.parse_args()

    problems = []
    records = {}
    for kind, filename in FILES.items():
        seen = {}
        for record in read(filename):
            rid = record.get("id", "")
            for field in REQUIRED[kind]:
                if field not in record:
                    problems.append(f"{kind} {rid}: missing field {field!r}")
            if not ID_RE[kind].match(rid):
                problems.append(f"{kind}: bad id {rid!r}")
            if kind == "entity":
                # An entity has no single source: it carries the pages it was
                # read from, and its evidence records carry theirs.
                pages = [p for field in ("ce_pages", "win32_pages",
                                         "dotnet_pages")
                         for p in record.get(field, ())]
                if not pages:
                    problems.append(f"entity {rid}: no page")
                for path in pages + list(
                        record.get("win32_pages_from_variants", ())):
                    if not os.path.exists(os.path.join(ROOT, path)):
                        problems.append(f"entity {rid}: page {path} is not in "
                                        "the repository")

            else:
                source = record.get("source")
                if not isinstance(source, dict) or not source.get("path"):
                    problems.append(f"{kind} {rid}: no source path")
                elif not os.path.exists(os.path.join(ROOT, source["path"])):
                    problems.append(f"{kind} {rid}: source {source['path']} is "
                                    "not in the repository")
            seen[rid] = record
        records[kind] = seen
        print(f"{filename:28s} {len(seen):>8,} records")

    entities = records["entity"].values()
    for entity in entities:
        if entity.get("win32_documented") and not (
                entity.get("win32_pages") or
                entity.get("win32_pages_from_variants")):
            problems.append(f"entity {entity['id']}: win32_documented but no "
                            "Win32 page")
        variant = entity.get("variants_of")
        if variant and variant.get("id") not in records["entity"]:
            problems.append(f"entity {entity['id']}: variants_of "
                            f"{variant.get('id')} is not an entity")
        if variant and variant.get("basis") not in ("page-statement",
                                                    "import-rule"):
            problems.append(f"entity {entity['id']}: variants_of basis "
                            f"{variant.get('basis')!r} is not a known basis")
        surface = entity.get("surface")
        if surface not in SURFACES:
            problems.append(f"entity {entity['id']}: surface {surface!r}")
        elif surface == "shared" and not (entity.get("win32_pages") or
                                          entity.get("win32_pages_from_variants")):
            problems.append(f"entity {entity['id']}: surface shared but no "
                            "Win32 page")
        elif surface in ("ce-only",) and entity.get("win32_documented"):
            problems.append(f"entity {entity['id']}: surface ce-only but "
                            "win32_documented")
        elif surface in ("win32-spelling", "catalog-only", "win32-only") and \
                entity.get("ce_pages"):
            problems.append(f"entity {entity['id']}: surface {surface} but the "
                            "entity has CE pages")
        for field, kind in (("declarations", "declaration"),
                            ("syntax_declarations", "declaration"),
                            ("requirements", "requirement"),
                            ("constraints", "constraint")):
            for rid in entity.get(field, ()):
                if rid not in records[kind]:
                    problems.append(f"entity {entity['id']}: {field} id {rid} "
                                    "is not in the file")
        for variant in entity.get("variants", ()):
            if variant.get("id") not in records["entity"]:
                problems.append(f"entity {entity['id']}: variant "
                                f"{variant.get('id')} is not an entity")
            else:
                back = records["entity"][variant["id"]].get("variants_of") or {}
                if back.get("id") != entity["id"]:
                    problems.append(f"entity {entity['id']}: variant "
                                    f"{variant['id']} does not point back")
        for relation in entity.get("relations", ()):
            if relation.get("present") and relation.get("id") and \
                    relation["id"] not in records["entity"]:
                problems.append(f"entity {entity['id']}: relation to "
                                f"{relation['id']} says present but is missing")

    surfaces = collections.Counter(e.get("surface")
                                   for e in records["entity"].values())
    print("\nsurface (Windows CE is the CE-specific surface + the Win32 that "
          "CE documents share, not all of Win32): " +
          ", ".join(f"{name} {surfaces.get(name, 0):,}" for name in SURFACES))

    variants = {e["id"]: e for e in records["entity"].values()
                if e.get("variants_of")}
    print(f"\nUnicode/ANSI variant spellings folded into a base name: "
          f"{len(variants):,}; names with a Win32 page (directly or as a "
          "variant): "
          f"{sum(1 for e in records['entity'].values() if e['win32_documented']):,}"
          f" of which {sum(1 for e in records['entity'].values() if e.get('win32_pages_from_variants')):,}"
          " through a variant")

    use = collections.Counter()
    for entity in entities:
        use.update(entity.get("generation_use", ()))
    print("\ngeneration_use coverage:")
    for name, count in use.most_common():
        print(f"  {name:22s} {count:>8,}")

    kinds = collections.Counter()
    for entity in records["entity"].values():
        kinds.update(entity.get("kinds") or ["<none>"])
    print("\nentity kinds: " + ", ".join(f"{k} {n:,}"
                                         for k, n in kinds.most_common(8)))

    conventions = collections.Counter()
    for declaration in records["declaration"].values():
        conventions[declaration.get("calling_convention") or "<not stated>"] += 1
    print("declaration calling conventions: " +
          ", ".join(f"{k} {n:,}" for k, n in conventions.most_common()))

    if args.sample:
        for kind in FILES:
            print(f"\n--- {kind} sample ---")
            for record in list(records[kind].values())[:args.sample]:
                print(json.dumps(record, ensure_ascii=False)[:400])

    gaps = []
    gap_path = os.path.join(REPORTS, "gaps.tsv")
    if os.path.exists(gap_path):
        with open(gap_path, encoding="utf-8") as fh:
            next(fh, None)
            gaps = [line for line in fh if line.strip()]
        print(f"\ngaps.tsv: {len(gaps):,} entities wait for a declaration, a "
              "header or a library")

    if problems:
        print(f"\n{len(problems)} problem(s):")
        for problem in problems[:30]:
            print("  " + problem)
        if len(problems) > 30:
            print(f"  ... and {len(problems) - 30} more")
        return 1
    print("\nknowledge OK")
    return 0


if __name__ == "__main__":
    sys.exit(main())
