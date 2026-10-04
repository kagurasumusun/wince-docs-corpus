#!/usr/bin/env python3
"""tools/build-chm-inventory.py -- every CHM under sources/ and where it went.

The first collection question a medium raises is "is its documentation
actually in the corpus?".  For the CHM media this is answered here: every
``*.CHM``/``*.chm`` file kept under ``sources/`` is listed with the queue entry
that extracts it and the corpus directory the pages landed in.

    data/reports/chm-inventory.tsv
        medium <TAB> chm <TAB> bytes <TAB> queue_set <TAB> corpus_dir <TAB>
        pages <TAB> state

    state
      extracted   the component directory is in the corpus and holds pages
      queued      a queue entry matches the CHM, no corpus directory yet
      unmapped    no queue entry matches it -- the report exists for these

The component directory is what ``tools/extract-chm.py`` writes:
``corpus/chm/<release>/<component>/<path inside the CHM>``, where
``<component>`` is the CHM's file name without its ``P<nnn>_`` inventory
prefix.  A CHM inside an archive (the CE 3.0 documentation archive is a zip
holding one CHM) is listed as ``<archive>!<entry>``.

Run it after adding a medium; an ``unmapped`` row means either the queue entry
is missing or the CHM is documentation the corpus does not hold yet.  Nothing
is fetched here -- this is the inventory, the collection happens through
``queues/chm-sets.tsv`` and its workflow.
"""

import argparse
import collections
import fnmatch
import os
import re
import sys
import tarfile
import zipfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SOURCES = os.path.join(ROOT, "sources")
CONFIG = os.path.join(ROOT, "queues", "chm-sets.tsv")
OUT = os.path.join(ROOT, "data", "reports", "chm-inventory.tsv")
PAGE_EXT = (".htm", ".html")
COMPONENT_PREFIX = re.compile(r"^P\d+_")
ARCHIVES = (".zip", ".tar.gz", ".tgz")


def read_config():
    entries = []
    with open(CONFIG, encoding="utf-8") as fh:
        for line in fh:
            line = line.rstrip("\n")
            if not line.strip() or line.lstrip().startswith("#"):
                continue
            parts = [p.strip() for p in line.split("\t")]
            if len(parts) != 3:
                continue
            entries.append({"set": parts[0], "out": parts[1],
                            "globs": [g.strip() for g in parts[2].split(",")
                                      if g.strip()]})
    return entries


def match_entry(rel, entries):
    for entry in entries:
        for pattern in entry["globs"]:
            if fnmatch.fnmatch(rel, pattern):
                return entry
    return None


def component_of(chm_name):
    stem = os.path.splitext(os.path.basename(chm_name))[0]
    return COMPONENT_PREFIX.sub("", stem).lower()


def page_count(directory):
    if not os.path.isdir(directory):
        return 0
    total = 0
    for _dirpath, _dirnames, filenames in os.walk(directory):
        total += sum(1 for name in filenames
                     if os.path.splitext(name)[1].lower() in PAGE_EXT)
    return total


def archive_members(path):
    """(entry name, size) of the help files inside an archive, if readable."""
    try:
        if path.lower().endswith(".zip"):
            with zipfile.ZipFile(path) as zf:
                return [(info.filename, info.file_size)
                        for info in zf.infolist()
                        if os.path.splitext(info.filename)[1].lower()
                        in (".chm", ".hlp", ".mvb")]
        with tarfile.open(path) as tf:
            return [(member.name, member.size) for member in tf.getmembers()
                    if os.path.splitext(member.name)[1].lower()
                    in (".chm", ".hlp", ".mvb")]
    except (OSError, tarfile.TarError, zipfile.BadZipFile):
        return []


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--quiet", action="store_true")
    args = ap.parse_args()

    entries = read_config()
    rows = []
    for dirpath, dirnames, filenames in os.walk(SOURCES):
        dirnames.sort()
        for name in sorted(filenames):
            full = os.path.join(dirpath, name)
            rel = os.path.relpath(full, ROOT).replace(os.sep, "/")
            medium = os.path.relpath(full, SOURCES).split(os.sep)[0]
            size = os.path.getsize(full)
            if name.lower().endswith((".chm", ".hlp", ".mvb")):
                candidates = [(rel, name, size)]
            elif name.lower().endswith(ARCHIVES):
                candidates = [(f"{rel}!{member}", member, member_size)
                              for member, member_size in archive_members(full)]
            else:
                continue
            for label, member, member_size in candidates:
                entry = match_entry(label.split("!")[0], entries)
                component = component_of(member)
                queue_set = entry["set"] if entry else ""
                if entry and "!*" in entry["globs"][0]:
                    pass
                corpus_dir = ""
                pages = 0
                if entry:
                    corpus_dir = os.path.normpath(
                        os.path.join(entry["out"], component))
                    pages = page_count(os.path.join(ROOT, corpus_dir))
                elif member.lower().endswith(".chm"):
                    # an archive whose extraction was done outside a queue
                    # entry: the CE 3.0 documentation archive.  Look for the
                    # component directory under the set hinted by the file.
                    hint = os.path.join("corpus", "chm", medium)
                    corpus_dir = os.path.normpath(os.path.join(hint, component))
                    pages = page_count(os.path.join(ROOT, corpus_dir))
                state = ("extracted" if pages else
                         "queued" if queue_set else "unmapped")
                rows.append((medium, label, member_size, queue_set,
                             corpus_dir, pages, state))

    rows.sort(key=lambda r: (r[0], r[1]))
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    with open(OUT, "w", encoding="utf-8") as fh:
        fh.write("medium\tchm\tbytes\tqueue_set\tcorpus_dir\tpages\tstate\n")
        for row in rows:
            fh.write("\t".join(str(c) for c in row) + "\n")

    states = collections.Counter(row[6] for row in rows)
    pages = sum(row[5] for row in rows)
    print(f"{os.path.relpath(OUT, ROOT)}: {len(rows):,} help file(s), "
          f"{pages:,} page(s) in the corpus")
    for state, count in states.most_common():
        print(f"  {state:10s} {count:6,}")
    todo = [row for row in rows if row[6] == "unmapped"]
    if todo and not args.quiet:
        print("\nnot matched by queues/chm-sets.tsv:")
        for row in todo[:20]:
            print(f"  {row[1]}  (corpus pages: {row[5]:,})")
    grouped = collections.defaultdict(lambda: [0, 0])
    for row in rows:
        grouped[row[3] or "(no queue entry)"][0] += 1
        grouped[row[3] or "(no queue entry)"][1] += row[5]
    print("\nper queue set:")
    for name, (count, page_total) in sorted(grouped.items()):
        print(f"  {name:20s} {count:4d} help file(s)  {page_total:8,} page(s)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
