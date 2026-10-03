#!/usr/bin/env python3
"""tools/build-win32-map.py -- map the Win32-shared API surface.

Joins the API names Windows CE documents (``tools/ce_api_names.py``, the
evidence report ``data/reports/ce-api-names.tsv``) with the Win32 pages that
were imported into ``corpus/win32/api/`` and writes two reports:

  data/reports/win32-shared.tsv
      one row per shared API name
      name <TAB> ce_sets <TAB> ce_page_ids <TAB> win32_pages
      * name          normalised API name (``CreateFile``)
      * ce_sets       CE sets that document it (``;`` separated)
      * ce_page_ids   catalog page ids documenting it (``;`` separated;
                      ``id(v=tag)`` for Learn pages, ``_wcesdk_*`` for the
                      CE 3.0 CHM, ``AB238C`` for the CE 1.0 Books Online, ...)
      * win32_pages   corpus-relative path(s) of the Win32 page(s)
                      (``;`` separated; ``A``/``W`` variants are listed under
                      the base name)

  data/reports/win32-imported.tsv
      one row per page in ``corpus/win32/api/``
      path <TAB> module <TAB> kind <TAB> name <TAB> ce_sets <TAB> ce_page_ids
      * ce_sets       CE sets that document the page's API name
      * ce_page_ids   the CE page(s) that document it - this is the evidence
                      that the page belongs in the corpus at all, so a reader
                      can check any page against the CE documentation

The first report is the answer to "which part of Win32 does Windows CE
share?"; the second one is the per-page provenance of the imported half.
"""

import collections
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import ce_api_names  # noqa: E402

ROOT = ce_api_names.ROOT
CORPUS = os.path.join(ROOT, "corpus")
REPORTS = os.path.join(ROOT, "data", "reports")


def set_name(section):
    """``msdn-library/techshelps/WCEMFC`` -> ``techshelps/WCEMFC``."""
    parts = section.split("/")
    if parts[0] == "dotnet":
        return "dotnet/" + (parts[1] if len(parts) > 1 else parts[0])
    if parts[0] == "learn":
        return parts[1] if len(parts) > 1 else parts[0]
    if parts[0] == "msdn-library":
        return "/".join(parts[1:3]) if len(parts) > 2 else parts[-1]
    if parts[0] in ("chm", "mvb"):
        return "/".join(parts[1:]) if len(parts) > 1 else parts[0]
    return section


def load_ce():
    """name -> (sets, page ids), from tools/ce_api_names.py."""
    sets = collections.defaultdict(set)
    ids = collections.defaultdict(list)
    for name, entry in ce_api_names.load_names().items():
        for page_id, _title, book in sorted(entry.get("catalog", ())):
            sets[name].add(book)
            if page_id not in ids[name]:
                ids[name].append(page_id)
        for page_id, _title, section in sorted(entry.get("corpus", ())):
            sets[name].add(set_name(section))
            if page_id not in ids[name]:
                ids[name].append(page_id)
    return sets, ids


def load_win32():
    """name -> [(path, module, kind, page name)], and the total page count."""
    pages = collections.defaultdict(list)
    total = 0
    api_dir = os.path.join(CORPUS, "win32", "api")
    for dirpath, dirnames, filenames in os.walk(api_dir):
        dirnames.sort()
        for fn in sorted(filenames):
            if not fn.endswith(".md"):
                continue
            match = ce_api_names.SDK_PAGE.match(fn)
            if not match:
                continue
            kind, module, name = match.groups()
            rel = os.path.relpath(os.path.join(dirpath, fn), ROOT)
            pages[ce_api_names.normalize(name)].append((rel, module, kind,
                                                        name))
            total += 1
    return pages, total


def main():
    ce_sets, ce_ids = load_ce()
    pages, total = load_win32()
    os.makedirs(REPORTS, exist_ok=True)

    imported_rows = []
    for name in sorted(pages):
        ce_name = ce_api_names.documented(name, ce_sets) or name
        sets = ";".join(sorted(ce_sets.get(ce_name, ())))
        ids = ";".join(ce_ids.get(ce_name, ()))
        for path, module, kind, page_name in sorted(pages[name]):
            imported_rows.append((path, module, kind, page_name, sets, ids))

    out = os.path.join(REPORTS, "win32-imported.tsv")
    with open(out, "w", encoding="utf-8") as fh:
        fh.write("path\tmodule\tkind\tname\tce_sets\tce_page_ids\n")
        for row in imported_rows:
            fh.write("\t".join(row) + "\n")
    print(f"{os.path.relpath(out, ROOT)}: {len(imported_rows):,} pages")

    shared_rows = []
    for name in sorted(pages):
        ce_name = ce_api_names.documented(name, ce_sets)
        if not ce_name:
            continue
        win = ";".join(sorted(p for p, _m, _k, _n in pages[name]))
        shared_rows.append((ce_name,
                            ";".join(sorted(ce_sets[ce_name])),
                            ";".join(ce_ids[ce_name]),
                            win))
    out = os.path.join(REPORTS, "win32-shared.tsv")
    with open(out, "w", encoding="utf-8") as fh:
        fh.write("name\tce_sets\tce_page_ids\twin32_pages\n")
        for row in shared_rows:
            fh.write("\t".join(row) + "\n")
    print(f"{os.path.relpath(out, ROOT)}: {len(shared_rows):,} shared names "
          f"({total:,} pages)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
