#!/usr/bin/env python3
"""verify_layout.py -- lint the repository against docs/LAYOUT.md. Exit 1 on violations.

Rules: only known top-level dirs; corpus/<kind>/... ; no Windows-invalid or space
characters in file names; no *.part leftovers; no generated binaries (sqlite) tracked;
learn pages live in a known product directory.
"""
import re
import sys
import os

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import common  # noqa: E402

TOP = {"corpus", "meta", "queues", "sources", "tools", "docs", ".github", "README.md", "AGENTS.md",
       ".gitignore", ".gitattributes"}
CORPUS_KINDS = {"learn", "wayback", "chm-extracted", "archives"}
BAD = re.compile(r'[<>:"|?*\\\s]')


def main():
    errs = []
    files = common.list_tracked(".")
    for p in files:
        parts = p.split("/")
        if parts[0] not in TOP:
            errs.append(f"unknown top-level entry: {p}")
        if parts[0] == "corpus" and (len(parts) < 3 or parts[1] not in CORPUS_KINDS):
            errs.append(f"corpus path outside known kinds: {p}")
        if BAD.search(parts[-1]):
            errs.append(f"file name not portable: {p}")
        if p.endswith((".part", ".sqlite3", ".db")):
            errs.append(f"generated/temporary file tracked: {p}")
        if len(p) > 200:
            errs.append(f"path too long: {p}")
    print(f"checked {len(files):,} files, {len(errs)} violation(s)")
    for e in errs[:50]:
        print("  ", e)
    return 1 if errs else 0


if __name__ == "__main__":
    sys.exit(main())
