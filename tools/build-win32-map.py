#!/usr/bin/env python3
"""tools/build-win32-map.py -- map the Win32-shared API surface.

Joins the Windows CE catalogs (``data/catalogs/*.tsv``) with the Win32 pages
imported into ``corpus/win32/api/`` and writes two reports:

  data/reports/win32-shared.tsv
      one row per shared API name
      name <TAB> ce_sets <TAB> ce_page_ids <TAB> win32_pages
      * name          normalised API name (``CreateFile``)
      * ce_sets       CE sets the name appears in (``;`` separated)
      * ce_page_ids   catalog page ids documenting it (``;`` separated;
                      ``id(v=tag)`` for Learn pages, ``_wcesdk_*`` for the
                      CE 3.0 CHM)
      * win32_pages   corpus-relative path(s) of the Win32 page(s)
                      (``;`` separated; ``A``/``W`` variants are listed under
                      the base name)

  data/reports/win32-imported.tsv
      one row per imported Win32 page
      path <TAB> module <TAB> kind <TAB> name <TAB> ce_shared <TAB> ce_sets
      * ce_shared     ``yes`` when the page name (or its base name) is in a
                      CE catalog, ``no`` for pages that are in the corpus only
                      as context of a CE-shared module

The first report is the answer to "which part of Win32 does Windows CE
share?"; the second one says which of the imported pages are CE-shared and
which are only there because their module is.
"""
import collections
import glob
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CORPUS = os.path.join(ROOT, "corpus")
REPORTS = os.path.join(ROOT, "data", "reports")
SDK_PAGE = re.compile(r"^(nf|ns|ne|nc|ni|nn|nl|na)-([^-]+)-(.+)\.md$")


def normalize(text):
    text = text.lower()
    text = re.sub(r"\(.*?\)", "", text)
    text = re.sub(r"\s+", "", text)
    return re.sub(r"[^a-z0-9_]", "", text)


def load_catalogs():
    """name -> {sets}, name -> [page ids]"""
    sets = collections.defaultdict(set)
    ids = collections.defaultdict(list)
    for path in sorted(glob.glob(os.path.join(ROOT, "data", "catalogs", "*.tsv"))):
        book = os.path.basename(path)[:-4]
        with open(path, encoding="utf-8", errors="replace") as fh:
            for line in fh:
                parts = line.rstrip("\n").split("\t")
                if len(parts) < 2:
                    continue
                name = normalize(parts[1])
                if not name:
                    continue
                sets[name].add(book)
                if parts[0] not in ids[name]:
                    ids[name].append(parts[0])
    return sets, ids


def load_win32():
    """name -> [(path, module, kind, page name)], and page count."""
    pages = collections.defaultdict(list)
    total = 0
    for dirpath, dirnames, filenames in os.walk(os.path.join(CORPUS, "win32",
                                                             "api")):
        dirnames.sort()
        module = os.path.basename(dirpath)
        for fn in sorted(filenames):
            if not fn.endswith(".md"):
                continue
            match = SDK_PAGE.match(fn)
            if not match:
                continue
            kind, mod, name = match.groups()
            rel = os.path.relpath(os.path.join(dirpath, fn), ROOT)
            pages[normalize(name)].append((rel, mod or module, kind, name))
            total += 1
    return pages, total


def base_name(name):
    """createfilew -> createfile (only when that is what CE documents)."""
    return name[:-1] if name.endswith(("a", "w")) else name


def main():
    ce_sets, ce_ids = load_catalogs()
    pages, total = load_win32()
    os.makedirs(REPORTS, exist_ok=True)

    shared_names = set()
    for name in pages:
        base = base_name(name)
        if name in ce_sets:
            shared_names.add(name)
        elif base in ce_sets:
            shared_names.add(name)

    shared_rows = []
    for name in sorted(shared_names):
        base = base_name(name)
        ce_name = name if name in ce_sets else base
        win = ";".join(sorted(p for p, _m, _k, _n in pages[name]))
        shared_rows.append((
            ce_name,
            ";".join(sorted(ce_sets[ce_name])),
            ";".join(ce_ids[ce_name]),
            win,
        ))
    out = os.path.join(REPORTS, "win32-shared.tsv")
    with open(out, "w", encoding="utf-8") as fh:
        fh.write("name\tce_sets\tce_page_ids\twin32_pages\n")
        for row in shared_rows:
            fh.write("\t".join(x.replace("\t", " ") for x in row) + "\n")

    imported_rows = []
    for name in sorted(pages):
        base = base_name(name)
        ce_name = name if name in ce_sets else (base if base in ce_sets else "")
        for rel, module, kind, page_name in pages[name]:
            imported_rows.append((
                rel, module, kind, page_name,
                "yes" if ce_name else "no",
                ";".join(sorted(ce_sets.get(ce_name, ()))) if ce_name else "",
            ))
    out2 = os.path.join(REPORTS, "win32-imported.tsv")
    with open(out2, "w", encoding="utf-8") as fh:
        fh.write("path\tmodule\tkind\tname\tce_shared\tce_sets\n")
        for row in imported_rows:
            fh.write("\t".join(x.replace("\t", " ") for x in row) + "\n")

    shared_pages = sum(1 for r in imported_rows if r[4] == "yes")
    modules = {r[1] for r in imported_rows}
    print(f"CE API names:            {len(ce_sets):,}")
    print(f"Win32 pages imported:    {total:,} ({len(modules)} modules)")
    print(f"  CE-shared pages:       {shared_pages:,} "
          f"({shared_pages / total:.0%})")
    print(f"  module-context pages:  {total - shared_pages:,}")
    print(f"shared API names:        {len(shared_names):,} "
          f"({len(shared_names) / len(ce_sets):.0%} of CE names have a page)")
    print(f"{out2}: {len(imported_rows):,} rows")
    print(f"{out}: {len(shared_rows):,} rows")


if __name__ == "__main__":
    main()
