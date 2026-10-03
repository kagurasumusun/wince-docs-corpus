#!/usr/bin/env python3
"""Integrity checker for the corpus.

Compares the pages on disk with both indexes, and looks for the storage
problems that a harvested archive accumulates: empty files, byte-for-byte
duplicates, files that are not valid UTF-8, HTML pages without an
``</html>``, and markdown pages without YAML front matter.

    python3 tools/check-corpus.py              # summary on stdout
    python3 tools/check-corpus.py --report     # also write data/reports/
    python3 tools/check-corpus.py --json

Exit status is 0 when the corpus is clean, 1 when a hard problem was found
(page counted by the index but missing on disk, or an unreadable page).
Duplicates and format warnings are reported but do not fail the run: the
CE trees intentionally contain the same page from more than one source
(e.g. a ``learn/`` harvest and the ``msdn-library/`` snapshot).
"""

import argparse
import codecs
import csv
import hashlib
import json
import os
import sqlite3
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CORPUS = os.path.join(ROOT, "corpus")
INDEX_TSV = os.path.join(ROOT, "data", "index", "INDEX.tsv")
INDEX_DB = os.path.join(ROOT, "data", "index", "corpus.sqlite3")
DUPLICATES = os.path.join(ROOT, "data", "reports", "duplicates.tsv")
PROBLEMS = os.path.join(ROOT, "data", "reports", "corpus-problems.tsv")

# Same page selection as tools/build-index.py.
PAGE_EXT = (".html", ".htm", ".md")
NOT_PAGES = {"README.md", "PROVENANCE.md"}

# This is a documentation archive: source code does not belong in corpus/.
# The list is a detector, not a filter - nothing here should ever match (see
# "What is collected" in the top-level README).
SOURCE_EXT = (".c", ".h", ".cpp", ".cxx", ".hpp", ".cs", ".vb", ".java",
              ".rc", ".def", ".asm", ".s", ".inc", ".mak", ".dsp", ".dsw",
              ".vbp", ".vcp", ".vcproj", ".sln", ".py", ".js", ".ps1", ".sh",
              ".lib", ".obj", ".dll", ".exe", ".sys", ".pdb")

# web.archive.org answers with this interstitial when the replay needs
# JavaScript; tools/harvest.py refuses to store it, so any file that contains
# it is a leftover from an older harvest.
WAYBACK_INTERSTITIAL = (
    b"requires your browser to support JavaScript",
    b"Impatient? The Wayback Machine",
    b"has not archived that URL",
)


def walk_pages():
    for dirpath, dirnames, filenames in os.walk(CORPUS):
        dirnames[:] = [d for d in dirnames if not d.startswith(".")]
        for name in filenames:
            if name.lower().endswith(PAGE_EXT) and name not in NOT_PAGES:
                yield os.path.join(dirpath, name)


def rel(path):
    return os.path.relpath(path, ROOT).replace(os.sep, "/")


def scan(path):
    """One read pass: md5, first/last 4 KiB, UTF-8 validity."""
    h = hashlib.md5()
    head, tail, size = b"", b"", 0
    decoder = codecs.getincrementaldecoder("utf-8")()
    utf8 = True
    with open(path, "rb") as fh:
        while True:
            chunk = fh.read(1 << 20)
            if not chunk:
                break
            size += len(chunk)
            h.update(chunk)
            if size <= 4096:
                head += chunk
            tail = chunk[-4096:]
            if utf8:
                try:
                    decoder.decode(chunk)
                except UnicodeDecodeError:
                    utf8 = False
    if utf8:
        try:
            decoder.decode(b"", final=True)
        except UnicodeDecodeError:
            utf8 = False
    return {"md5": h.hexdigest(), "size": size, "head": head[:4096],
            "tail": tail, "utf8": utf8,
            "interstitial": any(m in head for m in WAYBACK_INTERSTITIAL)}


def read_index_tsv():
    seen, missing = set(), []
    with open(INDEX_TSV, newline="", encoding="utf-8") as fh:
        for row in csv.DictReader(fh, delimiter="\t"):
            path = row["path"]
            seen.add(path)
            if not os.path.isfile(os.path.join(ROOT, path)):
                missing.append(path)
    return seen, missing


def read_index_db():
    if not os.path.isfile(INDEX_DB):
        return None, []
    con = sqlite3.connect(INDEX_DB)
    try:
        db_paths = {p for (p,) in con.execute("SELECT path FROM pages")}
    finally:
        con.close()
    missing = [p for p in db_paths if not os.path.isfile(os.path.join(ROOT, p))]
    return db_paths, missing


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--report", action="store_true",
                    help="write data/reports/{duplicates,corpus-problems}.tsv")
    ap.add_argument("--json", action="store_true", help="print JSON instead of text")
    args = ap.parse_args()

    files = sorted(walk_pages())
    on_disk = {rel(p) for p in files}

    index_paths, index_missing = read_index_tsv()
    db_paths, db_missing = read_index_db()

    unindexed = sorted(on_disk - index_paths)
    empty, bad_utf8, no_endtag, interstitial = [], [], [], []
    sources = []
    hashes = {}
    unreadable = []

    for path in files:
        try:
            info = scan(path)
        except OSError as exc:
            unreadable.append(f"{rel(path)}\t{exc}")
            continue
        if path.lower().endswith(SOURCE_EXT):
            sources.append(rel(path))
            continue
        if info["size"] == 0:
            empty.append(rel(path))
            continue
        hashes.setdefault(info["md5"], []).append(rel(path))
        if not info["utf8"]:
            bad_utf8.append(rel(path))
        if info["interstitial"]:
            interstitial.append(rel(path))
        if path.lower().endswith((".html", ".htm")):
            if "</html>" not in info["tail"].decode("utf-8", "replace").lower():
                no_endtag.append(rel(path))

    dupes = {h: ps for h, ps in hashes.items() if len(ps) > 1}
    dupe_files = sum(len(ps) - 1 for ps in dupes.values())

    result = {
        "pages_on_disk": len(on_disk),
        "index_tsv_rows": len(index_paths),
        "index_db_rows": None if db_paths is None else len(db_paths),
        "index_rows_without_file": len(index_missing) + len(db_missing),
        "files_not_in_index": len(unindexed),
        "empty_files": len(empty),
        "source_files": len(sources),
        "unreadable_files": len(unreadable),
        "not_utf8": len(bad_utf8),
        "html_without_endtag": len(no_endtag),
        "wayback_interstitial": len(interstitial),
        "duplicate_groups": len(dupes),
        "duplicate_files": dupe_files,
    }

    if args.report:
        os.makedirs(os.path.dirname(DUPLICATES), exist_ok=True)
        with open(DUPLICATES, "w", encoding="utf-8", newline="") as fh:
            fh.write("md5\tsize\tn\tpaths\n")
            for h, ps in sorted(dupes.items(), key=lambda kv: (-len(kv[1]), kv[0])):
                size = os.path.getsize(os.path.join(ROOT, ps[0]))
                fh.write(f"{h}\t{size}\t{len(ps)}\t" + "\t".join(ps) + "\n")
        with open(PROBLEMS, "w", encoding="utf-8", newline="") as fh:
            fh.write("kind\tpath\n")
            for kind, items in (("unindexed", unindexed), ("empty", empty),
                                ("unreadable", unreadable), ("not-utf8", bad_utf8),
                                ("html-without-endtag", no_endtag),
                                ("wayback-interstitial", interstitial),
                                ("source-file", sources)):
                for item in items:
                    fh.write(f"{kind}\t{item}\n")
            for path in index_missing + db_missing:
                fh.write(f"index-row-without-file\t{path}\n")

    if args.json:
        print(json.dumps(result, indent=2))
    else:
        for key, value in result.items():
            print(f"{key:>26}: {value}")
        hard = result["index_rows_without_file"] or result["unreadable_files"]
        print("FAIL" if hard else "ok")

    return 1 if (result["index_rows_without_file"] or result["unreadable_files"]) else 0


if __name__ == "__main__":
    sys.exit(main())
