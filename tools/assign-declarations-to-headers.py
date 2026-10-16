#!/usr/bin/env python3
"""Assign extra declarations to headers using the shared header map and KB.

Output: knowledge/kb/declarations-by-header/<header>.declarations.json
        knowledge/kb/declarations-by-header/_unassigned.declarations.json
"""

from __future__ import annotations

import gzip
import json
import os
import re
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
                    page_to_headers[page].add(
                        header_map.canonical_header(header.split(",")[0]))
    return page_to_headers


def main():
    extra_path = KB / "extra-declarations.jsonl"
    extra = []
    with open(extra_path, encoding="utf-8") as fh:
        for line in fh:
            extra.append(json.loads(line))
    print(f"Loaded {len(extra)} extra declarations")

    page_to_headers = load_page_headers()
    print(f"Page-to-header map: {len(page_to_headers)} pages")

    header_decls = defaultdict(list)
    unassigned = []
    for decl in extra:
        cleaned = quality_filters.sanitize_declaration(
            decl.get("declaration") or "",
            decl.get("name") or "",
            decl.get("type") or "",
        )
        if not cleaned:
            continue
        decl = dict(decl)
        decl["declaration"] = cleaned
        source = decl.get("source") or ""
        name = decl.get("name") or ""
        headers = set(page_to_headers.get(source) or ())
        if not headers:
            mapped = header_map.header_for_entity(name, [decl.get("type") or ""])
            if mapped:
                headers = {mapped}
        if headers:
            mapped = header_map.header_for_entity(name, [decl.get("type") or ""])
            if mapped and mapped.lower() in {h.lower() for h in headers}:
                chosen = mapped
            else:
                chosen = sorted(headers, key=str.lower)[0]
            header_decls[chosen.lower()].append(decl)
        else:
            unassigned.append(decl)

    print(f"Assigned: {sum(len(v) for v in header_decls.values())}")
    print(f"Unassigned: {len(unassigned)}")
    print(f"Headers: {len(header_decls)}")

    out_dir = KB / "declarations-by-header"
    out_dir.mkdir(exist_ok=True)
    for existing in out_dir.glob("*.declarations.json"):
        existing.unlink()
    for header, decls in sorted(header_decls.items()):
        seen = set()
        unique = []
        for d in decls:
            key = (d.get("type"), d.get("name"))
            if key in seen:
                continue
            seen.add(key)
            unique.append(d)
        safe = re.sub(r'[<>:"/\\|?*]', "_", header)
        with open(out_dir / f"{safe}.declarations.json", "w",
                  encoding="utf-8") as fh:
            json.dump(unique, fh, indent=2, ensure_ascii=False)
    with open(out_dir / "_unassigned.declarations.json", "w",
              encoding="utf-8") as fh:
        json.dump(unassigned, fh, indent=2, ensure_ascii=False)
    print(f"Wrote {out_dir}/")
    for header, decls in sorted(header_decls.items(),
                                key=lambda x: -len(x[1]))[:20]:
        print(f"  {header}: {len(decls)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
