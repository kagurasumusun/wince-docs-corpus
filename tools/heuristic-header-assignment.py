#!/usr/bin/env python3
"""Heuristic header assignment for entities without a stated header.

Writes knowledge/kb/heuristic-headers.tsv -- it does NOT mutate
entities.jsonl.gz (that file is produced only by tools/build-kb.py).
tools/gen-include-def.py consumes the TSV as a marked fallback.
"""

from __future__ import annotations

import gzip
import json
import os
import sys
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import header_map  # noqa: E402

KB = os.path.join(ROOT, "knowledge", "kb")


def main():
    entities = []
    with gzip.open(os.path.join(KB, "entities.jsonl.gz"), "rt",
                   encoding="utf-8") as fh:
        for line in fh:
            entities.append(json.loads(line))
    print(f"Loaded {len(entities)} entities")

    lib_to_headers = defaultdict(Counter)
    for entity in entities:
        headers = entity.get("headers") or []
        libs = (entity.get("libraries") or []) + (entity.get("dlls") or [])
        if not headers or not libs:
            continue
        for lib in libs:
            stem = lib.lower().replace(".lib", "").replace(".dll", "")
            stem = stem.split("\\")[-1].split("/")[-1]
            for header in headers:
                lib_to_headers[stem][header] += 1

    rows = []
    pattern_counts = Counter()
    for entity in entities:
        if entity.get("headers"):
            continue
        if not entity.get("ce_pages"):
            continue
        name = entity.get("name") or ""
        header = header_map.header_for_entity(name, entity.get("kinds") or [])
        source = "name-pattern" if header else ""
        if not header:
            libs = (entity.get("libraries") or []) + (entity.get("dlls") or [])
            for lib in libs:
                mapped = header_map.header_for_library(lib)
                if mapped:
                    header = mapped
                    source = "library-map"
                    break
                stem = lib.lower().replace(".lib", "").replace(".dll", "")
                stem = stem.split("\\")[-1].split("/")[-1]
                counts = lib_to_headers.get(stem)
                if counts and len(counts) == 1:
                    header = next(iter(counts))
                    source = "library-unique"
                    break
        if not header:
            continue
        pattern_counts[source] += 1
        rows.append((name, header, source, entity.get("id") or ""))

    out = os.path.join(KB, "heuristic-headers.tsv")
    with open(out, "w", encoding="utf-8") as fh:
        fh.write("name\theader\tsource\tentity\n")
        for row in sorted(rows, key=lambda r: r[0].lower()):
            fh.write("\t".join(row) + "\n")
    print(f"Wrote {len(rows)} assignments to {out}")
    print("By source:", dict(pattern_counts))
    remaining = sum(1 for e in entities
                    if not e.get("headers") and e.get("ce_pages"))
    print(f"Entities still without a header: {remaining - len(rows)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
