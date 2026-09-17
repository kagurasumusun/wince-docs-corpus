#!/usr/bin/env python3
"""tools/make-index.py -- regenerate data/index/INDEX.tsv from the corpus tree.

Columns: id <TAB> book <TAB> path <TAB> title
Titles come from each page's <title> (Microsoft Learn suffix stripped),
falling back to the official TOC catalogs in data/catalogs/.
"""
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TITLE = re.compile(r"<title>(.*?)</title>", re.S)


def cat_titles():
    t = {}
    d = os.path.join(ROOT, "data/catalogs")
    for fn in sorted(os.listdir(d)):
        with open(os.path.join(d, fn), encoding="utf-8", errors="replace") as f:
            for line in f:
                m = re.match(r"([A-Za-z0-9_]+)(?:\(v=[a-z0-9.]+\))?\t(.*)$",
                             line.rstrip("\n"))
                if m:
                    t.setdefault(m.group(1), m.group(2))
    return t


def page_title(path):
    try:
        with open(path, encoding="utf-8", errors="replace") as f:
            m = TITLE.search(f.read(8000))
        return re.sub(r"\s*\|\s*Microsoft Learn\s*$", "", m.group(1).strip()) if m else ""
    except OSError:
        return ""


def main():
    cats = cat_titles()
    rows = []
    for section, subdir in (("mslearn", "docs/mslearn"),
                            ("wayback-msdn-2010", "docs/wayback-msdn/2010-05"),
                            ("chm-windows-ce-3.0", "docs/chm/windows-ce-3.0")):
        base = os.path.join(ROOT, subdir)
        if not os.path.isdir(base):
            continue
        books = (sorted(os.listdir(base)) if section == "mslearn" else [""])
        for book in books:
            d = os.path.join(base, book) if book else base
            if not os.path.isdir(d):
                continue
            for fn in sorted(os.listdir(d)):
                if not fn.endswith(".html"):
                    continue
                pid = fn[:-5]
                rel = os.path.relpath(os.path.join(d, fn), ROOT)
                title = page_title(os.path.join(d, fn)) or cats.get(pid, "")
                rows.append((pid, book or section, rel, title))
    out = os.path.join(ROOT, "data/index/INDEX.tsv")
    with open(out, "w", encoding="utf-8") as f:
        f.write("# id\tbook\tpath\ttitle\n")
        for r in rows:
            f.write("\t".join(x.replace("\t", " ") for x in r) + "\n")
    print(f"{out}: {len(rows)} rows")


if __name__ == "__main__":
    main()
