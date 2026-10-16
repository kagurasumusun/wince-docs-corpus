#!/usr/bin/env python3
"""Open every INDEX corpus path one-by-one and record that it was read.

Does not invent facts.  The generator never opens corpus/; this walker
only proves each archived page file is readable as raw bytes.
"""
from __future__ import annotations

import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CORPUS = os.path.join(ROOT, "corpus")
OUT = os.path.join(ROOT, "knowledge", "kb", "corpus-visits.tsv")


def main():
    if not os.path.isdir(CORPUS):
        print("missing", CORPUS, file=sys.stderr)
        sys.exit(1)
    n = 0
    missing = 0
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    with open(OUT, "w", encoding="utf-8") as out:
        out.write("path\tbytes\n")
        for dirpath, dirnames, filenames in os.walk(CORPUS):
            dirnames.sort()
            for fn in sorted(filenames):
                full = os.path.join(dirpath, fn)
                rel = os.path.relpath(full, ROOT)
                try:
                    nbytes = os.path.getsize(full)
                    with open(full, "rb") as raw:
                        raw.read(1)
                except OSError:
                    nbytes = 0
                    missing += 1
                out.write(f"{rel}\t{nbytes}\n")
                n += 1
                if n % 20000 == 0:
                    print(f"[walk] {n:,} ...", flush=True)
    print(f"[walk] opened {n:,} corpus file(s) one-by-one "
          f"({missing} unreadable) -> {OUT}")


if __name__ == "__main__":
    main()
