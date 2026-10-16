#!/usr/bin/env python3
"""Assign extra defines to headers using the shared header map and KB pages.

Output: knowledge/kb/defines-by-header/<header>.defines.json
        knowledge/kb/defines-by-header/_unassigned.defines.json
"""

from __future__ import annotations

import csv
import gzip
import json
import os
import sys
from collections import defaultdict
from pathlib import Path

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import header_map  # noqa: E402
import quality_filters  # noqa: E402

KB = Path(ROOT) / "knowledge" / "kb"


def load_page_headers():
    page_to_headers = defaultdict(set)
    with gzip.open(KB / "entities.jsonl.gz", "rt", encoding="utf-8") as fh:
        for line in fh:
            entity = json.loads(line)
            headers = entity.get("headers") or []
            if not headers:
                continue
            for page in (entity.get("ce_pages") or []) + (entity.get("win32_pages") or []):
                for header in headers:
                    files = header_map.canonical_header(header.split(",")[0])
                    if files:
                        page_to_headers[page].add(files)
    req_path = KB / "requirements.jsonl.gz"
    if req_path.exists():
        with gzip.open(req_path, "rt", encoding="utf-8") as fh:
            for line in fh:
                rec = json.loads(line)
                if rec.get("field") != "header":
                    continue
                page = (rec.get("source") or {}).get("path") or ""
                value = rec.get("value") or ""
                if page and value:
                    for tok in value.replace(",", " ").split():
                        if "." in tok and tok.lower().split(".")[-1] in (
                                "h", "hpp", "hh", "hxx", "idl", "inc"):
                            page_to_headers[page].add(
                                header_map.canonical_header(tok))
    return page_to_headers


def main():
    extra_path = KB / "extra-defines.tsv"
    extra_defines = []
    with open(extra_path, encoding="utf-8") as fh:
        reader = csv.DictReader(fh, delimiter="\t")
        for row in reader:
            extra_defines.append(row)
    print(f"Loaded {len(extra_defines)} extra defines")

    page_to_headers = load_page_headers()
    print(f"Page-to-header map: {len(page_to_headers)} pages")

    header_defines = defaultdict(list)
    unassigned = []
    for define in extra_defines:
        best = quality_filters.pick_best_define([define])
        if not best:
            continue
        source = best.get("source") or ""
        name = best.get("name") or ""
        headers = set(page_to_headers.get(source) or ())
        if not headers:
            mapped = header_map.header_for_constant(name)
            if mapped:
                headers = {mapped}
        if headers:
            # one primary header -- prefer the mapped one if present
            mapped = header_map.header_for_constant(name)
            if mapped and mapped.lower() in {h.lower() for h in headers}:
                chosen = mapped
            else:
                chosen = sorted(headers, key=str.lower)[0]
            header_defines[chosen.lower()].append(best)
        else:
            unassigned.append(best)

    print(f"Assigned: {sum(len(v) for v in header_defines.values())}")
    print(f"Unassigned: {len(unassigned)}")
    print(f"Headers: {len(header_defines)}")

    out_dir = KB / "defines-by-header"
    out_dir.mkdir(exist_ok=True)
    for existing in out_dir.glob("*.defines.json"):
        existing.unlink()
    for header, defines in sorted(header_defines.items()):
        # keep original casing from first row's assignment
        with open(out_dir / f"{header}.defines.json", "w", encoding="utf-8") as fh:
            json.dump(defines, fh, indent=2, ensure_ascii=False)
    with open(out_dir / "_unassigned.defines.json", "w", encoding="utf-8") as fh:
        json.dump(unassigned, fh, indent=2, ensure_ascii=False)
    print(f"Wrote {out_dir}/")
    for header, defines in sorted(header_defines.items(),
                                  key=lambda x: -len(x[1]))[:20]:
        print(f"  {header}: {len(defines)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
