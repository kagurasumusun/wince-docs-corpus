#!/usr/bin/env python3
"""tools/build-win32-coverage.py -- the review list for the shared surface.

The rule of this repository is that the ``win32`` tree holds only those
Microsoft Win32 API pages that a Windows CE document also documents (see
docs/COLLECTION-POLICY.md).  The rule cuts both ways, so the review question
is: which names do the CE documents present as Win32-style APIs
(``Winbase.h``/``Winuser.h``/``Windows.h``/... -- a header of the shared
surface) while the corpus has *no* Win32 page for them?

    data/reports/win32-coverage.tsv
        name <TAB> kind <TAB> doc_role <TAB> ce_sets <TAB> headers <TAB>
        underscore_candidate <TAB> example_page

The rows are *candidates for review*, not findings: a CE-only name such as an
interlocked intrinsic or a macro that CE documents in ``winnt.h`` legitimately
has no Win32 page, and a name printed with underscores may be the CE spelling
of a Win32 name (``ACM_Open`` / ``acmOpen``) -- ``underscore_candidate``
records that possibility only when dropping the underscores finds a name the
KB knows on the Win32 side, so a reviewer can decide.

Input is the knowledge base (``knowledge/kb/``), so run ``build-kb.py`` first.
"""

import argparse
import collections
import gzip
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
KB = os.path.join(ROOT, "knowledge", "kb")
OUT = os.path.join(ROOT, "data", "reports", "win32-coverage.tsv")

# Headers that belong to the shared Win32 surface.  A CE-only name below one
# of these was proposed to the CE reader as a Win32-style API.
SHARED_HEADERS = {
    "windows.h", "winbase.h", "windef.h", "winuser.h", "winnls.h", "winreg.h",
    "winnt.h", "wingdi.h", "winerror.h", "winsock.h", "winsock2.h", "wininet.h",
    "winmm.h", "mmsystem.h", "commctrl.h", "commdlg.h", "shellapi.h",
    "shlobj.h", "objbase.h", "ole2.h", "oleauto.h", "winsvc.h", "wintrust.h",
    "winver.h", "wincon.h", "wtypes.h", "winspool.h", "winscard.h",
    "winusb.h", "winbase.h",
}


def read_kb(which):
    path = os.path.join(KB, which)
    opener = gzip.open if path.endswith(".gz") else open
    with opener(path, "rt", encoding="utf-8") as fh:
        for line in fh:
            line = line.strip()
            if line:
                yield json.loads(line)


def normalize(name):
    """The KB's name key: lower case, letters and digits only."""
    return "".join(ch for ch in name.lower() if ch.isalnum())


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--quiet", action="store_true")
    args = ap.parse_args()

    entities = list(read_kb("entities.jsonl.gz"))
    by_norm = collections.defaultdict(list)
    for entity in entities:
        by_norm[normalize(entity["name"])].append(entity)

    win32_known = {e["name"] for e in entities if "win32" in e["layers"]}
    win32_norm = {normalize(n) for n in win32_known}

    rows = []
    for entity in entities:
        # ``win32_documented`` covers the pages of the Unicode/ANSI variant
        # spellings (CreateSemaphoreW documents the CE name CreateSemaphore),
        # so a name the Win32 reference does document is not listed here.
        if entity["win32_documented"] or "dotnet" in entity["layers"]:
            continue
        headers = sorted({h.lower() for h in entity.get("headers", [])})
        if not headers or not (set(headers) & SHARED_HEADERS):
            continue
        # A message, a notification or a macro: ``wb``-style spellings are
        # documented by the CE pages themselves, and sdk-api is a reference
        # for functions, structures and interfaces -- it has no page per
        # message constant.  The KB says which of the two a row is, so a
        # reviewer does not have to guess.
        macro_style = entity["name"].isupper() and "_" in entity["name"]
        candidate = ""
        if "_" in entity["name"] and not macro_style:
            flat = normalize(entity["name"])
            if flat in win32_norm and flat != normalize(entity["name"]):
                candidate = ", ".join(sorted(
                    e["name"] for e in entities
                    if normalize(e["name"]) == flat and "win32" in e["layers"]))
        rows.append((
            entity["name"],
            ", ".join(entity.get("kinds") or []),
            entity.get("doc_role", ""),
            ", ".join(entity.get("ce_sets") or []),
            ", ".join(sorted(set(entity.get("headers") or []))),
            candidate,
            entity["ce_pages"][0] if entity.get("ce_pages") else "",
            "message-or-macro" if macro_style else "",
        ))

    rows.sort(key=lambda r: (not r[6], r[3], r[0].lower()))
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    with open(OUT, "w", encoding="utf-8") as fh:
        fh.write("name\tkind\tdoc_role\tce_sets\theaders\t"
                 "underscore_candidate\texample_page\treason\n")
        for row in rows:
            fh.write("\t".join(row) + "\n")

    print(f"{os.path.relpath(OUT, ROOT)}: {len(rows):,} name(s) a CE document "
          "presents under a shared-surface header")
    if not args.quiet:
        per_set = collections.Counter()
        for row in rows:
            for s in (row[3] or "(none)").split(", "):
                per_set[s] += 1
        for name, count in per_set.most_common(12):
            print(f"  {count:6,}  {name}")
        print(f"  message/notification/macro spellings (sdk-api has no page "
              f"per constant): {sum(1 for r in rows if r[7]):,}")
        names = [row for row in rows if row[5]]
        print(f"\n  {len(names)} name(s) whose underscored spelling matches a "
              "Win32 name:")
        for row in names[:20]:
            print(f"    {row[0]:32s} -> {row[5]}")
        print(f"\n  functions: "
              f"{sum(1 for r in rows if 'function' in r[1]):,}, "
              f"macros: {sum(1 for r in rows if 'macro' in r[1]):,}, "
              f"structs/enums: "
              f"{sum(1 for r in rows if 'struct' in r[1] or 'enum' in r[1]):,}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
