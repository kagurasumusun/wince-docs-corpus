#!/usr/bin/env python3
"""tools/import-site.py -- import the HTML page trees kept under sources/.

Some documentation never came out of a CHM, a Help book or a crawl: it is the
Microsoft site that shipped *on* the medium as a directory of HTML pages (the
CE 2.0 Technical Information CD carries the "Windows CE Developer" site mirror,
the CE 4.2/5.0/6.0 media carry their release notes and What's New pages).  Those
pages sit in ``sources/`` for provenance; the corpus should hold them as pages
like everything else, which is what this tool does.

    python3 tools/import-site.py --list        # the configured trees
    python3 tools/import-site.py --dry-run     # what it would write
    python3 tools/import-site.py               # do it
    python3 tools/import-site.py --once windows-ce-2.0

The trees are listed in ``queues/site-sets.tsv``:

    name <TAB> source directory <TAB> corpus directory <TAB> exclude regex

Rules (the same as every other importer):

* pages only -- ``.htm``/``.html``; images, scripts and stylesheets are
  assets, not documentation, and are skipped;
* the FrontPage metadata directories are refused for every tree
  (``_vti_cnf``/``_vti_pvt``/``_derived``/``_private``);
* a byte-order mark or a declared charset is honoured, the page is written as
  UTF-8 (``tools/import-media.py``'s decoder, reused);
* a page that ``data/index/aliases.tsv`` already collapsed elsewhere is
  skipped, so a resolved duplicate cannot come back;
* a page the receipt already recorded is not imported twice (``--force``);
* the receipt is ``data/reports/site-imported.tsv``:
  ``name <TAB> source <TAB> corpus_path <TAB> title``.
"""

import argparse
import importlib.util
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CONFIG = os.path.join(ROOT, "queues", "site-sets.tsv")
RECEIPT = os.path.join(ROOT, "data", "reports", "site-imported.tsv")
EXCLUDED = os.path.join(ROOT, "data", "reports", "site-excluded.tsv")
PAGE_EXT = (".htm", ".html")
DEFAULT_EXCLUDE = (r"(^|/)(_vti_cnf|_vti_pvt|_derived|_private)(/|\\)"
                   r"|(^|/)~")  # FrontPage leftovers and its temporary copies
TITLE_RE = re.compile(r"<title>(.*?)</title>", re.S | re.I)
MAX_TITLE = 300


def _tool_module(name):
    """Import a tools/ module by path (``import-media.py`` has a hyphen)."""
    path = os.path.join(os.path.dirname(os.path.abspath(__file__)), name + ".py")
    spec = importlib.util.spec_from_file_location(name.replace("-", "_"), path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


alias_index = _tool_module("alias_index")
media = _tool_module("import-media")


def read_config(path):
    entries = []
    with open(path, encoding="utf-8") as fh:
        for line in fh:
            line = line.rstrip("\n")
            if not line or line.startswith("#"):
                continue
            parts = line.split("\t")
            if len(parts) < 3:
                sys.exit(f"{path}: need name, source, corpus (got {line!r})")
            entries.append({
                "name": parts[0],
                "source": parts[1],
                "corpus": parts[2],
                "exclude": parts[3] if len(parts) > 3 and parts[3] else DEFAULT_EXCLUDE,
            })
    return entries


def pages_of(entry):
    """(full, rel, excluded) of one configured tree, in walk order.

    ``excluded`` is True for a page the tree's exclude regex refuses: it is
    reported (``data/reports/site-excluded.tsv``) but never written.
    """
    exclude = re.compile(entry["exclude"]) if entry["exclude"] else None
    base = os.path.join(ROOT, entry["source"])
    for dirpath, dirnames, filenames in os.walk(base):
        dirnames.sort()
        for name in sorted(filenames):
            if os.path.splitext(name)[1].lower() not in PAGE_EXT:
                continue
            full = os.path.join(dirpath, name)
            rel = os.path.relpath(full, base).replace(os.sep, "/")
            yield full, rel, bool(exclude and exclude.search(rel))


def load_receipt():
    done = set()
    if os.path.isfile(RECEIPT):
        with open(RECEIPT, encoding="utf-8") as fh:
            next(fh, None)
            for line in fh:
                parts = line.rstrip("\n").split("\t")
                if parts and parts[0]:
                    done.add((parts[0], parts[1]))
    return done


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--config", default=CONFIG,
                    help="the tree table to read (default queues/site-sets.tsv)")
    ap.add_argument("--list", action="store_true", help="list the trees")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--force", action="store_true",
                    help="import again even when the receipt says done")
    ap.add_argument("--once", help="import a single entry by name")
    args = ap.parse_args()

    entries = read_config(args.config)
    if args.once:
        entries = [e for e in entries if e["name"] == args.once]
        if not entries:
            sys.exit(f"no entry named {args.once!r} in {CONFIG}")

    if args.list:
        for entry in entries:
            pages = list(pages_of(entry))
            kept = sum(1 for _f, _r, excluded in pages if not excluded)
            print(f"{entry['name']:24s} {kept:4d} page(s) imported, "
                  f"{len(pages) - kept:3d} excluded  "
                  f"{entry['source']} -> {entry['corpus']}")
        return 0

    done = load_receipt()
    rows = []
    excluded_rows = []
    for entry in entries:
        imported = skipped = aliased = excluded = 0
        for full, rel, is_excluded in pages_of(entry):
            if is_excluded:
                excluded += 1
                excluded_rows.append((entry["name"], rel, entry["exclude"]))
                continue
            # The corpus keeps one extension for site pages (.html), so a
            # source .htm and a source .html of the same page do not become
            # two corpus pages.  The receipt keeps the path as it is on disk.
            source_rel = rel
            rel = os.path.splitext(rel)[0] + ".html"
            target_rel = os.path.join(entry["corpus"], rel)
            target = os.path.join(ROOT, target_rel)
            if (entry["name"], source_rel) in done and not args.force:
                skipped += 1
                continue
            if alias_index.is_aliased(target_rel.replace(os.sep, "/")):
                aliased += 1
                continue
            raw = open(full, "rb").read()
            body = media.to_utf8(raw)
            if media.PLACEHOLDER.search(body[:2000]):
                skipped += 1
                continue
            if args.dry_run:
                rows.append((entry["name"], source_rel, target_rel, ""))
                imported += 1
                continue
            os.makedirs(os.path.dirname(target), exist_ok=True)
            with open(target, "wb") as fh:
                fh.write(body)
            match = TITLE_RE.search(body.decode("utf-8", "replace"))
            title = re.sub(r"\s+", " ", match.group(1)).strip()[:MAX_TITLE] \
                if match else ""
            rows.append((entry["name"], source_rel, target_rel, title))
            imported += 1
        print(f"{entry['name']:24s} imported={imported:4d} "
              f"already={skipped:4d} aliased={aliased:3d} "
              f"excluded={excluded:3d}")

    if args.dry_run:
        print(f"would import {len(rows)} page(s); nothing written")
        return 0

    os.makedirs(os.path.dirname(EXCLUDED), exist_ok=True)
    with open(EXCLUDED, "w", encoding="utf-8") as fh:
        fh.write("name\tsource\treason\n")
        for row in sorted(excluded_rows):
            fh.write(f"{row[0]}\t{row[1]}\trefused by the tree's exclude "
                     "regex\n")
    print(f"refused {len(excluded_rows)} page(s); "
          f"{os.path.relpath(EXCLUDED, ROOT)}")

    os.makedirs(os.path.dirname(RECEIPT), exist_ok=True)
    new = not os.path.exists(RECEIPT)
    with open(RECEIPT, "a" if not new else "w", encoding="utf-8") as fh:
        if new:
            fh.write("name\tsource\tcorpus_path\ttitle\n")
        for row in rows:
            fh.write("\t".join(row) + "\n")
    print(f"wrote {len(rows)} page(s); receipt {os.path.relpath(RECEIPT, ROOT)}")
    print("next: python3 tools/build-index.py && "
          "python3 tools/build-index-sql.py && python3 tools/check-policy.py")
    return 0


if __name__ == "__main__":
    sys.exit(main())
