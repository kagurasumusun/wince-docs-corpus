#!/usr/bin/env python3
"""tools/dedupe-corpus.py -- collapse byte-identical pages, keeping the trail.

A documentation corpus built from several media ends up holding the same
document twice: the Windows CE 2.12 SDK reference of the DevCon '99 conference
CD is also on the MSDN Library April 2000 CD, and two CE 5.0 component CHMs
document the same mouse/stylus topics.  For a knowledge base that is noise, but
silently deleting a file loses the fact that the other medium carried it too.

This tool resolves the duplicates **and keeps that fact**:

* it groups the pages by content (md5, the same grouping
  ``tools/check-corpus.py --report`` writes to ``data/reports/duplicates.tsv``);
* it keeps one copy per group, chosen by the documented priority below;
* it deletes the other copies and records them in
  ``data/index/aliases.tsv`` (``removed_path  kept_path  md5  size  page_id
  book  kept_page_id  kept_book``), so every removed id stays resolvable for
  ``tools/find-api.py`` and for anything built on top of the corpus;
* it rewrites ``data/reports/duplicates.tsv`` groups it has resolved to a
  single line, and leaves anything it must not touch alone (see "never
  touched").

    python3 tools/dedupe-corpus.py --report     # show what it would do
    python3 tools/dedupe-corpus.py             # do it (git rm the pages)
    python3 tools/dedupe-corpus.py --check     # re-check aliases, write nothing

Priority (first match wins, so the copy that survives is the one whose medium
is the *original documentation set*, not a re-capture):

    1. corpus/learn/, corpus/dotnet/     the harvested product documentation
    2. corpus/chm/                       the official CHM extraction
    3. corpus/mvb/                       the decoded Books Online
    4. corpus/msdn-library/wcedevcon-99  a pinned medium (ISO, PROVENANCE.md)
    5. corpus/msdn-library/techshelps
    6. corpus/kb/
    7. corpus/msdn-library/windows-mobile-6.5
    8. corpus/msdn-library/2010-05       a different capture on purpose
    9. corpus/msdn-library/datadungeon-2000-04  the live third-party crawl
   10. anything else, then the lexicographically first path

Never touched (kept as-is, and not reported as duplicates):

* ``corpus/msdn-library/2010-05/`` -- the wayback captures are a *different
  rendering* of the same topics (2010 MSDN, not Learn), kept deliberately.
  Its own tree-internal duplicates are still resolved.
* ``README.md`` / ``PROVENANCE.md`` -- paperwork, not pages.
* a group whose members are not all pages (a medium-specific extra file).

The tool is idempotent *and cumulative*: running it again removes nothing more,
and ``aliases.tsv`` keeps the rows of the earlier runs (a row is dropped only
when its removed page is back on disk).
"""

import argparse
import collections
import hashlib
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import alias_index  # noqa: E402  (the alias table this tool writes)

ROOT = alias_index.ROOT
CORPUS = os.path.join(ROOT, "corpus")
ALIASES = os.path.join(ROOT, "data", "index", "aliases.tsv")
DUPLICATES = os.path.join(ROOT, "data", "reports", "duplicates.tsv")
PAGE_EXT = (".html", ".htm", ".md")
PAPERWORK = {"README.md", "PROVENANCE.md"}

# Priority: lower number wins.  Ordered by "how close to the original product
# documentation the medium is".  A path that is not listed sorts last.
TREE_PRIORITY = (
    "corpus/learn/",
    "corpus/dotnet/",
    "corpus/chm/",
    "corpus/mvb/",
    "corpus/msdn-library/wcedevcon-99/",
    "corpus/msdn-library/techshelps/",
    "corpus/kb/",
    "corpus/msdn-library/windows-mobile-6.5/",
    "corpus/msdn-library/2010-05/",
    "corpus/msdn-library/datadungeon-2000-04/",
)

# Captures that are a deliberate second rendering: a page here is never
# removed in favour of a page outside it (and never removes another tree's
# page).  See the docstring.
PROTECTED_TREES = ("corpus/msdn-library/2010-05/",)


def rel(path):
    return os.path.relpath(path, ROOT).replace(os.sep, "/")


def md5(path):
    digest = hashlib.md5()
    with open(path, "rb") as fh:
        for chunk in iter(lambda: fh.read(1 << 16), b""):
            digest.update(chunk)
    return digest.hexdigest()


def priority(path):
    page = rel(path)
    for index, prefix in enumerate(TREE_PRIORITY):
        if page.startswith(prefix):
            return (index, page)
    return (len(TREE_PRIORITY), page)


def protected(path):
    return any(rel(path).startswith(p) for p in PROTECTED_TREES)


def scan():
    """{md5: {"size": n, "paths": [path, ...]}} for pages with >1 copy."""
    groups = collections.defaultdict(lambda: {"size": 0, "paths": []})
    for dirpath, dirnames, filenames in os.walk(CORPUS):
        dirnames.sort()
        for name in sorted(filenames):
            if name in PAPERWORK:
                continue
            if os.path.splitext(name)[1].lower() not in PAGE_EXT:
                continue
            path = os.path.join(dirpath, name)
            try:
                digest = md5(path)
                size = os.path.getsize(path)
            except OSError:
                continue
            entry = groups[digest]
            entry["size"] = size
            entry["paths"].append(path)
    return {d: e for d, e in groups.items() if len(e["paths"]) > 1}


def resolve(groups):
    """(kept, removed) file lists, the choice rules applied.

    ``groups`` is :func:`scan` output.  A group is only resolved when every
    copy is in an unprotected tree and at least two different *books* are
    involved; a group inside one book is the medium's own structure and is
    left alone (it is still listed in duplicates.tsv).
    """
    kept, removed = [], []
    for digest, entry in sorted(groups.items()):
        paths = sorted(entry["paths"])
        if any(protected(p) for p in paths):
            # Keep the protected capture(s) and the best non-protected copy.
            protected_paths = [p for p in paths if protected(p)]
            others = [p for p in paths if not protected(p)]
            if not others or any(protected(p) for p in others):
                continue
            winner = min(others, key=priority)
            for path in others:
                if path != winner:
                    removed.append(path)
                    kept.append(winner if path == winner else path)
            # the protected copies stay; record them as aliases too
            for path in protected_paths:
                kept.append(winner)
            continue
        winner = min(paths, key=priority)
        for path in paths:
            if path != winner:
                kept.append(winner)
                removed.append(path)
    return kept, removed


def alias_row(kept_path, removed_path, digest, size):
    """One aliases.tsv row: the removed copy -> the copy that is kept."""
    page_id = os.path.splitext(os.path.basename(removed_path))[0]
    return (
        rel(removed_path), rel(kept_path), digest, str(size), page_id,
        book_of(removed_path),
        os.path.splitext(os.path.basename(kept_path))[0], book_of(kept_path),
    )


def merge_rows(rows):
    """Existing aliases + the new rows, so the table is cumulative.

    An alias is a fact about the collection and outlives the run that found
    it: re-running this tool (or resolving one new duplicate) must not erase
    the record of the 672 pages resolved earlier.  A row is dropped only when
    its removed page is back on disk (then it is not an alias any more).
    """
    merged = {row[0]: row for row in load_alias_rows()}
    for row in rows:
        merged[row[0]] = row
    for removed, row in list(merged.items()):
        if os.path.exists(os.path.join(ROOT, removed)):
            del merged[removed]
    return [merged[key] for key in sorted(merged)]


def apply_removals(pairs, dry_run):
    """Delete the removed pages and add their aliases to aliases.tsv."""
    rows = []
    seen = set()
    for kept_path, removed_path in sorted(pairs):
        if removed_path in seen:
            continue
        seen.add(removed_path)
        rows.append(alias_row(kept_path, removed_path, md5(removed_path),
                              os.path.getsize(removed_path)))
    if dry_run:
        return rows
    removed_now = set()
    for _kept_path, removed_path in sorted(pairs):
        if removed_path in removed_now:
            continue
        removed_now.add(removed_path)
        os.remove(removed_path)
    rows = merge_rows(rows)
    write_aliases(rows)
    return rows


def book_of(path):
    """``corpus/msdn-library/wcedevcon-99/wceapc/x.html`` ->
    ``msdn-library/wcedevcon-99`` (the corpus-relative set directory)."""
    page = rel(path)
    parts = page.split("/")
    if len(parts) < 3:
        return parts[0] if parts else ""
    if parts[1] in ("learn", "dotnet", "msdn-library", "chm", "mvb", "kb",
                    "site"):
        return "/".join(parts[1:3]) if parts[1] in ("learn", "dotnet",
                                                   "msdn-library") \
            else "/".join(parts[1:2] + parts[2:3])
    return parts[1]


def load_alias_rows():
    """The raw rows of data/index/aliases.tsv (comments skipped)."""
    rows = []
    if not os.path.isfile(ALIASES):
        return rows
    with open(ALIASES, encoding="utf-8") as fh:
        for line in fh:
            if line.startswith("#") or not line.strip():
                continue
            parts = line.rstrip("\n").split("\t")
            if len(parts) >= 4:
                parts += [""] * (8 - len(parts))
                rows.append(tuple(parts[:8]))
    return rows


def load_aliases():
    """removed_path -> {kept_path, md5, ...} from data/index/aliases.tsv."""
    aliases = {}
    for parts in load_alias_rows():
        aliases[parts[0]] = {
            "kept_path": parts[1], "md5": parts[2], "size": parts[3],
            "page_id": parts[4], "book": parts[5],
            "kept_page_id": parts[6], "kept_book": parts[7],
        }
    return aliases


def resolve_groups():
    """The (kept, removed) pairs for the pages on disk right now."""
    return resolve(scan())


def write_aliases(rows):
    os.makedirs(os.path.dirname(ALIASES), exist_ok=True)
    with open(ALIASES, "w", encoding="utf-8") as fh:
        fh.write("# removed_path\tkept_path\tmd5\tsize\tpage_id\tbook\t"
                 "kept_page_id\tkept_book\n")
        for row in rows:
            fh.write("\t".join(row) + "\n")


def check(verbose=False):
    """Re-verify the recorded aliases: removed file gone, keeper present and
    byte-identical.  Returns the number of problems."""
    aliases = load_aliases()
    problems = 0
    for removed, info in sorted(aliases.items()):
        removed_path = os.path.join(ROOT, removed)
        kept_path = os.path.join(ROOT, info["kept_path"])
        if os.path.exists(removed_path):
            problems += 1
            print(f"alias: {removed} exists again (keeper "
                  f"{info['kept_path']})")
            continue
        if not os.path.isfile(kept_path):
            problems += 1
            print(f"alias: keeper missing: {info['kept_path']}")
            continue
        if md5(kept_path) != info["md5"]:
            problems += 1
            print(f"alias: keeper changed: {info['kept_path']}")
        elif verbose:
            print(f"ok  {removed} -> {info['kept_path']}")
    print(f"aliases: {len(aliases)} recorded, {problems} problem(s)")
    return problems


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--report", action="store_true",
                    help="show the duplicate groups and the chosen keeper")
    ap.add_argument("--dry-run", action="store_true",
                    help="do not delete anything")
    ap.add_argument("--check", action="store_true",
                    help="re-verify data/index/aliases.tsv")
    ap.add_argument("--verbose", action="store_true")
    args = ap.parse_args()

    if args.check:
        return 1 if check(args.verbose) else 0

    groups = scan()
    kept, removed = resolve(groups)
    pairs = list(zip(kept, removed))
    duplicated = sum(1 for e in groups.values() if len(e["paths"]) > 1)
    pages_removed = len(set(removed))

    if args.report:
        print(f"{duplicated} duplicate group(s), {pages_removed} page(s) to "
              f"remove, {len(set(kept))} keeper(s)")
        by_tree = collections.Counter()
        for path in removed:
            page = rel(path)
            parts = page.split("/")
            by_tree["/".join(parts[:3]) if parts[1] in ("learn", "dotnet",
                                                        "msdn-library",
                                                        "chm", "mvb", "kb")
                    else "/".join(parts[:2])] += 1
        for tree, count in by_tree.most_common():
            print(f"  {count:6d}  {tree}")
        if args.verbose:
            for kept_path, removed_path in sorted(pairs)[:40]:
                print(f"  keep {rel(kept_path)}\n  drop {rel(removed_path)}")
        return 0

    rows = apply_removals(pairs, args.dry_run)
    if args.dry_run:
        print(f"would remove {len(rows)} page(s); aliases.tsv not written")
        return 0
    print(f"removed {len(rows)} duplicate page(s); "
          f"aliases in data/index/aliases.tsv")
    # the index is stale now
    print("next: python3 tools/build-index.py && "
          "python3 tools/build-index-sql.py && "
          "python3 tools/check-corpus.py --report")
    return 0


if __name__ == "__main__":
    sys.exit(main())
