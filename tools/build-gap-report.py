#!/usr/bin/env python3
"""tools/build-gap-report.py -- regenerate data/reports/missing-pages.tsv.

For every catalogued set, compare the official catalog in ``data/catalogs/``
with the files actually present in ``corpus/`` and list the pages that are
still missing:

    page_id <TAB> title <TAB> catalog

``page_id`` keeps the ``(v=...)`` version tag of the catalog entry, so a row
can be fed straight back into ``tools/harvest.py`` (see ``queues/``).

Sets and the corpus directory a page may live in:

    windows-ce-3.0          -> corpus/chm/windows-ce-3.0
    windows-ce-5.0          -> corpus/learn/windows-ce-5.0
    windows-ce-net-4x       -> corpus/learn/windows-ce-net-4x
    windows-embedded-ce-6.0 -> corpus/learn/windows-embedded-ce-6.0

Run with a single ``--set`` to print the missing ids for that set only.
"""
import argparse
import os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

SETS = {
    "windows-ce-3.0": ["chm/windows-ce-3.0"],
    "windows-ce-5.0": ["learn/windows-ce-5.0"],
    "windows-ce-net-4x": ["learn/windows-ce-net-4x"],
    "windows-embedded-ce-6.0": ["learn/windows-embedded-ce-6.0"],
}


def read_catalog(path):
    rows = []
    with open(path, encoding="utf-8", errors="replace") as fh:
        for line in fh:
            line = line.rstrip("\n")
            if not line or line.startswith("#"):
                continue
            parts = line.split("\t")
            if parts[0] and len(parts) >= 2:
                rows.append((parts[0], parts[1]))
    return rows


def corpus_ids(subdir):
    ids = set()
    base = os.path.join(ROOT, "corpus", subdir)
    for dirpath, _dirnames, filenames in os.walk(base):
        for fn in filenames:
            if fn.endswith(".html"):
                ids.add(fn[:-5])
    return ids


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--set", choices=sorted(SETS))
    ap.add_argument("--out", default=os.path.join(
        ROOT, "data", "reports", "missing-pages.tsv"))
    args = ap.parse_args()

    sets = [args.set] if args.set else sorted(SETS)
    missing = []
    for name in sets:
        catalog = os.path.join(ROOT, "data", "catalogs", name + ".tsv")
        present = set()
        for subdir in SETS[name]:
            present |= corpus_ids(subdir)
        rows = read_catalog(catalog)
        gone = [(pid, title) for pid, title in rows if pid not in present]
        print(f"{name}: catalog={len(rows):,} present={len(rows) - len(gone):,} "
              f"missing={len(gone):,}")
        missing += [(pid, title, name) for pid, title in gone]

    if args.set:
        for pid, title, _ in missing:
            print(f"{pid}\t{title}")
        return
    os.makedirs(os.path.dirname(args.out), exist_ok=True)
    with open(args.out, "w", encoding="utf-8") as fh:
        fh.write("page_id\ttitle\tsource_catalog\n")
        for row in missing:
            fh.write("\t".join(x.replace("\t", " ") for x in row) + "\n")
    print(f"{args.out}: {len(missing):,} rows")


if __name__ == "__main__":
    main()
