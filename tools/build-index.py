#!/usr/bin/env python3
"""tools/build-index.py -- regenerate data/index/INDEX.tsv from the corpus tree.

Walks every page under ``corpus/`` -- ``.html`` (harvested/extracted pages),
``.htm`` (documentation mirrors keep their original ``.htm`` names) and
``.md`` (the Win32 material imported from MicrosoftDocs, see
``corpus/win32/README.md``) -- and writes:

    # id <TAB> book <TAB> path <TAB> title

  id     page id -- the file name without ``.html``.  For Microsoft Learn
         harvests this is the last segment of the page's canonical URL
         (``aa450192(v=msdn.10)``); for the official CHM extraction and
         the Wayback snapshot it is the original topic file name.
  book   corpus-relative directory of the page, i.e. ``<source>/<set>``
         (``learn/windows-ce-5.0``, ``chm/windows-ce-3.0``, ...).
  path   repository-relative path of the HTML file.
  title  the page's ``<title>`` (HTML) or the ``title:`` field of its
         front matter (markdown), with the ``| Microsoft Learn`` suffix
         stripped, falling back to the official TOC catalogs in
         ``data/catalogs/``.

Regenerate with::

    python3 tools/build-index.py
"""
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CORPUS = os.path.join(ROOT, "corpus")
TITLE = re.compile(r"<title>(.*?)</title>", re.S)
MD_TITLE = re.compile(r"^title:\s*(.+?)\s*$", re.M)
PAGE_SUFFIXES = (".html", ".htm", ".md")   # matched case-insensitively
# Repository paperwork, not documentation pages.
NOT_PAGES = {"README.md", "PROVENANCE.md"}


def bare(page_id):
    """``aa450192(v=msdn.10)`` -> ``aa450192``"""
    i = page_id.find("(v=")
    return page_id[:i] if i > 0 else page_id


def cat_titles():
    """id -> title, from the official catalogs in data/catalogs/."""
    titles = {}
    catalog_dir = os.path.join(ROOT, "data", "catalogs")
    for fn in sorted(os.listdir(catalog_dir)):
        if not fn.endswith(".tsv") or fn.startswith("."):
            continue
        with open(os.path.join(catalog_dir, fn), encoding="utf-8",
                  errors="replace") as fh:
            for line in fh:
                if not line.strip() or line.startswith("#"):
                    continue
                parts = line.rstrip("\n").split("\t")
                if len(parts) >= 2:
                    titles.setdefault(bare(parts[0]), parts[1])
                    titles.setdefault(parts[0], parts[1])
    return titles


def page_title(path):
    # Some archived pages (the 2010-05 MSDN Library snapshot) carry the
    # Wayback Machine banner before the document, so <title> can sit far below
    # the first few KiB; scan the first 128 KiB instead of 8 KiB.
    try:
        with open(path, encoding="utf-8", errors="replace") as fh:
            head = fh.read(8000 if path.endswith(".md") else 131072)
    except OSError:
        return ""
    if path.endswith(".md"):
        match = MD_TITLE.search(head)
        return match.group(1).strip() if match else ""
    match = TITLE.search(head)
    if not match:
        return ""
    return re.sub(r"\s*\|\s*Microsoft Learn\s*$", "",
                  match.group(1).strip())


def main():
    cats = cat_titles()
    rows = []
    for dirpath, dirnames, filenames in os.walk(CORPUS):
        dirnames.sort()
        book = os.path.relpath(dirpath, CORPUS).replace(os.sep, "/")
        for fn in sorted(filenames):
            if not fn.lower().endswith(PAGE_SUFFIXES) or fn in NOT_PAGES:
                continue
            full = os.path.join(dirpath, fn)
            page_id = os.path.splitext(fn)[0]
            title = page_title(full) or cats.get(page_id, "") \
                or cats.get(bare(page_id), "")
            rows.append((page_id, book, os.path.relpath(full, ROOT), title))

    out = os.path.join(ROOT, "data", "index", "INDEX.tsv")
    with open(out, "w", encoding="utf-8") as fh:
        fh.write("# id\tbook\tpath\ttitle\n")
        for row in rows:
            fh.write("\t".join(x.replace("\t", " ") for x in row) + "\n")
    print(f"{out}: {len(rows)} rows")


if __name__ == "__main__":
    main()
