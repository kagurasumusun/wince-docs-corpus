#!/usr/bin/env python3
"""tools/build-win32-coverage.py -- the Win32 review worklist.

The corpus keeps only the part of Win32 that Windows CE itself documents
(``tools/ce_api_names.py`` and the rule in ``docs/COLLECTION-POLICY.md``).  This
report is the other direction of that review: which names the CE documentation
describes **as Win32 APIs** -- the page states a Win32 header such as
``Winbase.h``/``Winuser.h``/``Windows.h`` -- but for which ``corpus/win32/`` has
no page.

Reading it
----------

Most rows are *expected* and are not collection gaps:

* compiler intrinsics and their underscore spellings (``__emul``,
  ``_InterruptEnable``) -- the Win32 SDK has no page for a compiler builtin;
* Windows CE extensions and CE-only spellings of a Win32 call
  (``ACM_Open``, ``CeSetThreadPriority``) -- the SDK documentation has no page
  because the API is CE's;
* macros, window messages and flags that sdk-api does not give a page of their
  own.

What a row *is* worth checking for is a name whose Win32 page exists under a
different spelling: ``candidate_win32_name`` lists those, matched by comparing
the names with all non-alphanumeric characters and case removed
(``_InterlockedIncrement`` -> ``InterlockedIncrement``).  A candidate is a
*lead*, not a claim -- confirm it by reading both pages before importing
anything.

    python3 tools/build-win32-coverage.py            # write the report
    python3 tools/build-win32-coverage.py --summary  # print, write nothing
    python3 tools/build-win32-coverage.py --candidates   # only rows with a lead

Columns: name <TAB> kinds <TAB> doc_role <TAB> ce_sets <TAB> headers <TAB>
         candidate_win32_name <TAB> example_page

Header, CE set and page columns come from the knowledge base, so run
``python3 tools/build-kb.py`` first (the report is a view of
``knowledge/kb/entities.jsonl.gz``, not a second extraction).
"""

import argparse
import collections
import gzip
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
KB = os.path.join(ROOT, "knowledge", "kb", "entities.jsonl.gz")
OUT = os.path.join(ROOT, "data", "reports", "win32-coverage.tsv")

# The headers a page states when it means "this is a Windows API".  A CE-only
# API can state one of these too (CE's Winbase.h is a real header), so this is
# a filter for review, not a statement about the API's origin.
WIN_HEADERS = {
    "winbase.h", "winuser.h", "windows.h", "winnt.h", "windef.h",
    "winerror.h", "winreg.h", "winnls.h", "wingdi.h", "wincon.h",
    "winioctl.h", "winsock.h", "winsock2.h", "commctrl.h", "ole2.h",
    "objbase.h", "shellapi.h", "shlobj.h", "winmm.h", "mmsystem.h",
    "wininet.h", "winsvc.h", "wtypes.h", "unknwn.h", "objidl.h",
}


def squash(name):
    return re.sub(r"[^a-z0-9]", "", name.lower())


def load_entities():
    path = KB if os.path.exists(KB) else KB[:-3]
    if not os.path.exists(path):
        sys.exit(f"{os.path.relpath(KB, ROOT)} not found -- run "
                 "python3 tools/build-kb.py first")
    opener = gzip.open if path.endswith(".gz") else open
    with opener(path, "rt", encoding="utf-8") as fh:
        for line in fh:
            try:
                yield json.loads(line)
            except ValueError:
                continue


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--summary", action="store_true",
                    help="print the counts, write no file")
    ap.add_argument("--candidates", action="store_true",
                    help="print only the rows that have a candidate")
    args = ap.parse_args()

    entities = list(load_entities())

    # Every Win32 spelling that is already imported, keyed loosely.
    win32_name = {}
    for entity in entities:
        if entity["win32_pages"]:
            win32_name.setdefault(squash(entity["name"]), set()).add(
                entity["name"])
    win32_name = {k: sorted(v) for k, v in win32_name.items()}

    rows = []
    for entity in entities:
        if entity["win32_pages"] or not entity["ce_pages"]:
            continue
        if entity["doc_role"] == "topic":
            continue
        heads = {h.lower().rstrip(".") for h in entity["headers"]}
        if not heads & WIN_HEADERS:
            continue
        # A lead: a Win32 name that matches this one once case and punctuation
        # are removed, but is spelled differently (an exact same spelling would
        # already have been joined by tools/ce_api_names.py).
        candidate = ";".join(
            other for other in win32_name.get(squash(entity["name"]), ())
            if other.lower() != entity["name"].lower())
        rows.append((entity["name"], ",".join(entity["kinds"]),
                     entity["doc_role"], ";".join(entity["ce_sets"]),
                     ",".join(sorted(entity["headers"])), candidate,
                     entity["ce_pages"][0]))

    by_set = collections.Counter()
    for name, _k, _r, sets, _h, _c, _p in rows:
        for book in sets.split(";"):
            if book:
                by_set["/".join(book.split("/")[:2])] += 1
    candidates = [r for r in rows if r[5]]

    print(f"CE-documented names with a Win32 header and no Win32 page: "
          f"{len(rows):,}")
    print(f"  of those, with a possible Win32 spelling elsewhere: "
          f"{len(candidates):,}")
    for book, count in by_set.most_common():
        print(f"    {book:38s} {count:,}")

    if args.summary:
        for row in (candidates if args.candidates else rows):
            print("\t".join(row))
        return 0

    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    with open(OUT, "w", encoding="utf-8") as fh:
        fh.write("name\tkinds\tdoc_role\tce_sets\theaders\t"
                 "candidate_win32_name\texample_page\n")
        for row in rows:
            fh.write("\t".join(row) + "\n")
    print(f"{os.path.relpath(OUT, ROOT)}: {len(rows):,} rows")
    return 0


if __name__ == "__main__":
    sys.exit(main())
