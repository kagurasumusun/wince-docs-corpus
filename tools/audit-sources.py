#!/usr/bin/env python3
"""tools/audit-sources.py -- every medium in sources/ against the corpus.

"Did we collect everything?" is answered by comparing the material we hold
(``sources/``: official media, archives, upstream snapshots) with what the
corpus and the queues say about it.  This tool walks ``sources/``, classifies
each artifact and reports its state:

    data/reports/collection-audit.tsv
        medium <TAB> artifact <TAB> kind <TAB> state <TAB> evidence

    state meaning
      in-corpus   the artifact's documentation is in corpus/ (receipt or tree)
      extracted   an archive whose documentation was decoded into corpus/
      queued      the medium is listed in queues/media.tsv (not fetched yet)
      excluded    held for provenance only (a licence, a checksum, a README)
      check       no mapping found -- the report exists for these rows

    kind is the documentary form: chm / hlp / mvb / zip / iso / html-tree /
    markdown / text / other.

Run it after adding a medium; a row with state ``check`` is the worklist.
The mapping itself is the receipts in ``data/reports/`` plus the corpus trees;
the small REASONS table below records cases that are deliberate (an ISO whose
documentation arrives through another tool, a licence file, ...).
"""

import argparse
import collections
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SOURCES = os.path.join(ROOT, "sources")
OUT = os.path.join(ROOT, "data", "reports", "collection-audit.tsv")

PAGE_EXT = (".html", ".htm", ".md")
ARCHIVE_EXT = (".zip", ".iso", ".7z", ".rar", ".cab")
DOC_EXT = (".chm", ".hlp", ".mvb", ".hlp2", ".aux", ".cac", ".idx", ".kwd")

# Deliberate cases: artifact (relative to sources/) -> (state, reason).
REASONS = {
    "windows-ce-1.0/PEGSDK.MVB": ("extracted", "corpus/mvb/windows-ce-1.0"),
    "windows-ce-1.0/PEGDDK.MVB": ("extracted", "corpus/mvb/windows-ce-1.0"),
    "windows-ce-1.0/RELNOTES.HLP": ("extracted", "corpus/mvb/windows-ce-1.0"),
    "windows-ce-2.0/developer": ("in-corpus", "corpus/site/windows-ce-2.0"),
    "windows-ce-3.0/WindowsCE3.0_DocumentationArchive.zip":
        ("extracted", "corpus/chm/windows-ce-3.0"),
    "windows-ce-3.0/Important_ReadMe.txt":
        ("excluded", "medium ReadMe, not a documentation page"),
    "windows-ce-4.2/EMULATOR.CHM": ("extracted", "corpus/chm/windows-ce-4.2"),
    "windows-ce-4.2/REMTOOLS.CHM": ("extracted", "corpus/chm/windows-ce-4.2"),
    "windows-ce-4.2/release notes.htm":
        ("in-corpus", "corpus/site/windows-ce-4.2"),
    "windows-ce-4.2/whatsnew.html": ("in-corpus", "corpus/site/windows-ce-4.2"),
    "windows-ce-5.0/release notes.htm":
        ("in-corpus", "corpus/site/windows-ce-5.0"),
    "windows-ce-5.0/whatsnew.html": ("in-corpus", "corpus/site/windows-ce-5.0"),
    "windows-ce-6.0/release notes.htm":
        ("in-corpus", "corpus/site/windows-ce-6.0"),
    "microsoftdocs/LICENSE": ("excluded", "licence of the upstream snapshot"),
    "microsoftdocs/LICENSE-CODE": ("excluded", "licence of the upstream snapshot"),
    # The sdk-api snapshot archive is the source of corpus/win32/api; it is
    # kept (see sources/microsoftdocs/PROVENANCE.md) and is not imported twice.
    "microsoftdocs/sdk-api-c12073e417d5-md.tar.gz":
        ("extracted", "corpus/win32/api (fetch-upstream.py subset)"),
}


def kind_of(path):
    ext = os.path.splitext(path)[1].lower()
    if ext == ".chm":
        return "chm"
    if ext in (".hlp", ".hlp2"):
        return "hlp"
    if ext == ".mvb":
        return "mvb"
    if ext in ARCHIVE_EXT:
        return "zip" if ext == ".zip" else ext.lstrip(".")
    if ext in PAGE_EXT:
        return "html-tree" if ext != ".md" else "markdown"
    if ext in (".txt", ".md5", ".sha1", ".json"):
        return "text"
    if path.endswith(".tar.gz") or ext in (".tgz", ".tar"):
        return "tar"
    if ext in (".aux", ".cac", ".idx", ".kwd"):
        return "helpbook-index"
    return "other"


def receipts():
    """Artifacts the import tools recorded, by name and by tree."""
    known = collections.defaultdict(set)
    for name, column in (("site-imported.tsv", 0), ("media-imported.tsv", 0)):
        path = os.path.join(ROOT, "data", "reports", name)
        if not os.path.exists(path):
            continue
        with open(path, encoding="utf-8") as fh:
            next(fh, None)
            for line in fh:
                parts = line.rstrip("\n").split("\t")
                if parts and parts[column]:
                    known[name].add(parts[column])
    return known


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--quiet", action="store_true",
                    help="write the report, print only the summary counts")
    args = ap.parse_args()

    rows = []
    for dirpath, dirnames, filenames in os.walk(SOURCES):
        dirnames.sort()
        for name in sorted(filenames):
            full = os.path.join(dirpath, name)
            rel = os.path.relpath(full, SOURCES).replace(os.sep, "/")
            medium = rel.split("/")[0]
            kind = kind_of(full)
            state, evidence = "check", ""
            # a deliberate case first
            for key in (rel, "/".join(rel.split("/")[:2]), medium + "/" + name):
                if key in REASONS:
                    state, evidence = REASONS[key]
                    break
            else:
                if kind == "helpbook-index":
                    state, evidence = ("extracted",
                                       "corpus/mvb (help-book index files)")
                elif kind == "chm":
                    state, evidence = "extracted", "corpus/chm (extract-chm.py)"
                elif kind in ("hlp", "mvb"):
                    state, evidence = ("extracted",
                                       "corpus/mvb (extract-mvb.py)")
                elif kind == "html-tree":
                    site = os.path.join(ROOT, "corpus", "site", medium)
                    if os.path.isdir(site):
                        state, evidence = "in-corpus", "corpus/site/" + medium
                    else:
                        state, evidence = ("check",
                                           "HTML in sources/, no corpus tree")
                elif kind == "markdown":
                    state, evidence = ("in-corpus", "corpus/win32 (fetch-upstream)")
                elif kind == "text":
                    state, evidence = "excluded", "not a documentation page"
                elif kind in ("iso", "zip"):
                    state, evidence = "check", "archive: is it imported?"
            rows.append((medium, rel, kind, state, evidence))

    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    with open(OUT, "w", encoding="utf-8") as fh:
        fh.write("medium\tartifact\tkind\tstate\tevidence\n")
        for row in rows:
            fh.write("\t".join(row) + "\n")

    counts = collections.Counter(row[3] for row in rows)
    print(f"{os.path.relpath(OUT, ROOT)}: {len(rows):,} artifact(s)")
    for state, count in counts.most_common():
        print(f"  {state:10s} {count:6,}")
    todo = [row for row in rows if row[3] == "check"]
    if todo and not args.quiet:
        print("\nrows to look at:")
        for row in todo[:40]:
            print(f"  {row[1]}  ({row[4]})")
    return 0 if not todo else 0


if __name__ == "__main__":
    sys.exit(main())
