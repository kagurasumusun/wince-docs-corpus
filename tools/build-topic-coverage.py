#!/usr/bin/env python3
"""tools/build-topic-coverage.py -- how much of a subject area is collected.

``data/reports/missing-pages.tsv`` answers "is every catalogued page in the
corpus?"; this tool answers the narrower collection question a subject raises:
"how much of <subject> does the corpus hold?"  It matches a regular expression
against the official catalog titles of the four catalogued CE sets and reports,
per set, how many of the matching pages are in the corpus and which are not.

    python3 tools/build-topic-coverage.py --pattern "Platform Builder"
    python3 tools/build-topic-coverage.py \
        --pattern "Platform Builder|OAL|BSP|Boot Loader" \
        --out data/reports/platform-builder-coverage.tsv

    subject <TAB> catalog <TAB> set <TAB> catalog_pages <TAB> in_corpus <TAB>
    missing <TAB> examples

``missing`` is the number of matching catalog entries whose page is not in the
corpus; ``examples`` lists up to five of them (id: title) so the next harvest
run can be aimed at them.  With ``--out`` the report is written and the tool
prints the per-subject totals; without it, the same table goes to stdout.

Only the four sets with an official catalog can be measured this way.  The
sets without one (CE 1.0/2.0 Books Online, the MSDN Library mirrors, the
DevCon '99 disc, the KnowledgeBase) are covered by their own provenance notes;
``tools/audit-sources.py`` says where each medium went.
"""

import argparse
import collections
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CATALOGS = os.path.join(ROOT, "data", "catalogs")

# The same mapping tools/build-gap-report.py uses: a catalogue page may live in
# more than one corpus tree, so check them all.
SETS = {
    "windows-ce-3.0": ["chm/windows-ce-3.0"],
    "windows-ce-5.0": ["learn/windows-ce-5.0"],
    "windows-ce-net-4x": ["learn/windows-ce-net-4x"],
    "windows-embedded-ce-6.0": ["learn/windows-embedded-ce-6.0"],
}
EXAMPLE_LIMIT = 5


def read_catalog(name):
    rows = []
    path = os.path.join(CATALOGS, name + ".tsv")
    if not os.path.isfile(path):
        return rows
    with open(path, encoding="utf-8", errors="replace") as fh:
        for line in fh:
            line = line.rstrip("\n")
            if not line or line.startswith("#"):
                continue
            parts = line.split("\t")
            if len(parts) >= 2 and parts[0]:
                rows.append((parts[0], parts[1]))
    return rows


def corpus_ids(subdirs):
    ids = set()
    for subdir in subdirs:
        base = os.path.join(ROOT, "corpus", subdir)
        for _dirpath, _dirnames, filenames in os.walk(base):
            for name in filenames:
                if name.endswith(".html"):
                    ids.add(name[:-5])
    return ids


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--pattern", required=True,
                    help="regular expression over the catalog titles")
    ap.add_argument("--subject", help="name to write in the first column "
                                      "(default: the pattern)")
    ap.add_argument("--out", help="write the TSV here (and print a summary)")
    args = ap.parse_args()

    subject = args.subject or args.pattern
    regex = re.compile(args.pattern, re.I)
    rows = []
    for set_name, subdirs in sorted(SETS.items()):
        catalog = read_catalog(set_name)
        present = corpus_ids(subdirs)
        matched = [(pid, title) for pid, title in catalog
                   if regex.search(title or "")]
        missing = [(pid, title) for pid, title in matched
                   if pid not in present]
        examples = "; ".join(f"{pid}: {title}" for pid, title in
                             missing[:EXAMPLE_LIMIT])
        rows.append((subject, set_name, len(matched), len(matched) -
                     len(missing), len(missing), examples))

    header = ("subject\tcatalog\tset\tcatalog_pages\tin_corpus\tmissing\t"
              "examples")
    lines = [header] + ["\t".join(str(c) for c in row) for row in rows]
    if args.out:
        os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)
        with open(args.out, "w", encoding="utf-8") as fh:
            fh.write("\n".join(lines) + "\n")
        total = sum(row[2] for row in rows)
        held = sum(row[3] for row in rows)
        print(f"{args.out}: {subject!r} -- {held:,} of {total:,} catalogued "
              f"page(s) in the corpus")
        for row in rows:
            print(f"  {row[1]:26s} {row[3]:6,}/{row[2]:<6,}  missing "
                  f"{row[4]:,}")
    else:
        print("\n".join(lines))
    return 0


if __name__ == "__main__":
    sys.exit(main())
