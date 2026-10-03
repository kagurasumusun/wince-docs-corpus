#!/usr/bin/env python3
"""Take URLs a crawled mirror no longer needs out of its frontier.

A mirror crawl (``tools/crawl-mirror.py``) is the slow, request-hungry way to
collect documentation.  When the same pages arrive from a medium that a runner
can download once - a CD image, a CHM set - the mirror should not be asked for
them again, both because it is somebody else's server and because the frontier
is finite work.

This tool compares the pages a corpus tree already holds (``--tree``) with the
frontier and the collected pages of a crawl (``--state``, ``--crawl-tree``).
Every *book* is judged on two numbers:

* **coverage** - the share of the book's page ids (queued and collected) that
  the tree holds at all;
* **similarity** - normalised-text similarity of the pages both sides already
  have, sampled per book.

A book is taken out of the frontier only when both are high.  That second
number is the point of this tool: **a matching page id is not proof that it is
the same page**.  Two MSDN editions number, split and revise their topics
differently - ``corpus/msdn-library/techshelps/`` holds
``wcemfc/methods_79.htm`` for one topic while the April 2000 mirror's
``wcemfc/methods_79.htm`` is another topic (0% similar: refused), and the two
editions' glossaries chunk one glossary into different pages (also refused,
although 92% of the ids match).  The DevCon '99 CD passes for the SDK books
because editions of the same SDK documentation differ only in a word here and
there ("this chapter" / "this section"), which is why 4,978 queued URLs could
be dropped while the mirror is still asked for 3,990 URLs of books the disc
does not carry (`wcemfc`, `wceatl`, `vbce`, `_toc`, ...).

    python3 tools/mark-crawl-covered.py \\
        --state data/crawl/datadungeon-ce.json \\
        --crawl-tree corpus/msdn-library/datadungeon-2000-04 \\
        --tree corpus/msdn-library/wcedevcon-99 --reason wcedevcon-99

``--dry-run`` prints the decision per book without touching anything;
``--force`` prunes without the check (only for a tree whose provenance is
known to be the very same documentation).
"""

import argparse
import difflib
import json
import os
import random
import re
import sys
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REPORT = os.path.join(ROOT, "data", "reports", "crawl-covered.tsv")


def page_ids(tree):
    """id -> (path relative to ROOT, book) for every page under a tree."""
    pages = {}
    root = os.path.join(ROOT, tree)
    for dirpath, dirnames, filenames in os.walk(root):
        dirnames.sort()
        rel_dir = os.path.relpath(dirpath, root)
        book = "" if rel_dir == "." else rel_dir.split(os.sep)[0]
        for name in sorted(filenames):
            if not name.lower().endswith((".htm", ".html", ".md")):
                continue
            stem = re.sub(r"\.content$", "", os.path.splitext(name)[0])
            pages.setdefault(stem, (os.path.join(dirpath, name), book))
    return pages


def normalised_text(path):
    with open(path, "rb") as fh:
        body = fh.read().decode("utf-8", "replace")
    body = re.sub(r"<script.*?</script>|<style.*?</style>", " ", body,
                  flags=re.S | re.I)
    body = re.sub(r"<[^>]+>", " ", body).replace("&nbsp;", " ")
    return re.sub(r"\s+", " ", body).strip().lower()


def similarity(left, right):
    """How alike two pages are, ignoring markup (0 = unrelated, 1 = equal)."""
    return difflib.SequenceMatcher(
        None, normalised_text(left)[:4000],
        normalised_text(right)[:4000]).ratio()


def page_id_of(url):
    return re.sub(r"\.content$", "",
                  os.path.splitext(os.path.basename(url))[0])


def book_of(url, books):
    """The book (tree directory) a crawled URL belongs to."""
    parts = [seg for seg in url.split("/") if seg]
    return next((seg for seg in parts if seg in books), None)


def judge(ids, crawl_tree, book_of_id, sample, seed):
    """book -> (coverage, mean similarity, sampled pages) for a candidate tree."""
    local = page_ids(crawl_tree)
    by_book = defaultdict(list)
    for stem, (tree_path, book) in ids.items():
        if stem in local:
            by_book[book].append((tree_path, local[stem][0]))
    random.seed(seed)
    verdicts = {}
    for book in sorted(set(book_of_id.values())):
        wanted = {stem for stem, b in book_of_id.items() if b == book}
        known = {stem for stem in ids if ids[stem][1] == book}
        coverage = len(wanted & known) / max(len(wanted), 1)
        found = by_book.get(book, [])
        random.shuffle(found)
        chosen = found[:sample]
        sims = [similarity(left, right) for left, right in chosen]
        mean = sum(sims) / len(sims) if sims else None
        verdicts[book] = (coverage, mean, len(sims))
    return verdicts


def main():
    ap = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--state", required=True, help="data/crawl/<name>.json")
    ap.add_argument("--tree", required=True, action="append",
                    help="corpus tree that already holds the pages "
                         "(repeatable)")
    ap.add_argument("--crawl-tree", action="append", default=[],
                    help="the tree the crawl itself stores into, for the "
                         "per-book check (repeatable)")
    ap.add_argument("--reason", default="", help="label for the report")
    ap.add_argument("--report", default=REPORT)
    ap.add_argument("--min-coverage", type=float, default=0.95,
                    help="a book is covered when this share of its page ids "
                         "is in the tree")
    ap.add_argument("--min-similarity", type=float, default=0.9,
                    help="... and the sampled pages that both sides hold are "
                         "at least this similar")
    ap.add_argument("--sample", type=int, default=12,
                    help="pages sampled per book")
    ap.add_argument("--force", action="store_true",
                    help="prune without the per-book check")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    with open(os.path.join(ROOT, args.state), encoding="utf-8") as fh:
        state = json.load(fh)

    ids = {}
    for tree in args.tree:
        ids.update(page_ids(tree))
    books = {book for _path, book in ids.values()}

    # every id this crawl knows about (queued or collected), by book
    book_of_id = {}
    for url in list(state.get("pending", [])) + list(state.get("done", [])):
        book = book_of(url, books)
        if book:
            book_of_id[page_id_of(url)] = book
    print(f"{len(book_of_id):,} crawl page ids fall in books of the tree "
          f"({', '.join(sorted(books))})")

    covered = set()
    if args.force:
        covered = set(books)
        print("[check] skipped (--force)")
    else:
        if not args.crawl_tree:
            print("no --crawl-tree given: nothing can be verified; pass "
                  " --force to prune anyway")
            return 1
        verdicts = judge(ids, args.crawl_tree[0], book_of_id,
                         args.sample, seed=7)
        for book in sorted(verdicts, key=lambda b: -len(
                [1 for stem, bb in book_of_id.items() if bb == b])):
            coverage, mean, sampled = verdicts[book]
            why = []
            if coverage >= args.min_coverage:
                why.append(f"{coverage:.0%} of ids present")
            else:
                why.append(f"only {coverage:.0%} of ids present")
            if mean is None:
                why.append("no pages held by both sides")
            else:
                why.append(f"{mean:.0%} similar over {sampled} sampled")
            ok = (coverage >= args.min_coverage and mean is not None
                  and mean >= args.min_similarity)
            print(f"    {book:38s} {'covered' if ok else 'kept   '} "
                  f"({', '.join(why)})")
            if ok:
                covered.add(book)

    pending = sorted(state.get("pending", []))
    rows, left = [], Counter()
    taken = 0
    for url in pending:
        book = book_of(url, covered)
        if book:
            taken += 1
            rows.append((url, page_id_of(url), args.reason or args.tree[0],
                         book))
        else:
            parts = [seg for seg in url.split("/") if seg]
            left["/".join(parts[3:-1]) or "/"] += 1

    print(f"{len(pending):,} pending; {taken:,} covered by "
          f"{', '.join(args.tree)}; {len(pending) - taken:,} left")
    for book, number in left.most_common(12):
        print(f"    {book:28s} {number:6,d} still to crawl")

    if args.dry_run:
        print("[dry-run] nothing written")
        return 0

    done = set(state.get("done", []))
    done.update(url for url, *_rest in rows)
    state["done"] = sorted(done)
    state["pending"] = [u for u in pending
                        if u not in {url for url, *_rest in rows}]
    with open(os.path.join(ROOT, args.state), "w", encoding="utf-8") as fh:
        json.dump(state, fh, indent=1, sort_keys=True)
        fh.write("\n")

    path = os.path.join(ROOT, args.report)
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="utf-8", newline="") as fh:
        fh.write("url\tpage_id\treason\tbook\n")
        for row in rows:
            fh.write("\t".join(row) + "\n")
    print(f"[crawl] {taken:,} URLs moved to done; report: "
          f"{os.path.relpath(path, ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
