#!/usr/bin/env python3
"""Check the rights registry against the collection, and audit what is published.

Three questions, all answerable from the repository itself:

1. **Coverage** -- does every page in the corpus and every file Git tracks
   resolve to exactly one rule of ``data/license-scopes.tsv``?  A path that
   resolves to nothing is a violation: it would mean an item whose terms
   nobody has looked at.
2. **Statements** -- is every quoted statement really in the file the registry
   says it was read from?  The quote is compared with the file's text (HTML
   pages read the way the corpus reads them, whitespace aside).
3. **Publication** -- what does the repository actually publish, counted by
   permission and by scope?  That is the number that matters for a public
   repository; ``--fail-on-restricted`` turns it into a gate.

The result is written to ``knowledge/reports/license-audit.tsv`` (report only;
what to do about a restricted scope is the owner's decision, see
docs/LICENSING.md).

Usage::

    python3 tools/check-licenses.py                  # coverage + statements
    python3 tools/check-licenses.py --tracked         # audit what Git tracks
    python3 tools/check-licenses.py --tracked --fail-on-restricted
    python3 tools/check-licenses.py --list 20         # show paths per scope
"""

import argparse
import collections
import os
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import license_scopes  # noqa: E402

ROOT = license_scopes.ROOT
REPORTS = os.path.join(ROOT, "knowledge", "reports")
INDEX = os.path.join(ROOT, "data", "index", "INDEX.tsv")


def corpus_pages():
    """Every page the index knows, as repository-relative paths."""
    pages = []
    with open(INDEX, encoding="utf-8") as fh:
        for line in fh:
            if line.startswith("#") or not line.strip():
                continue
            fields = line.rstrip("\n").split("\t")
            if len(fields) >= 3:
                pages.append(fields[2])
    return pages


def tracked_files():
    result = subprocess.run(["git", "ls-files"], cwd=ROOT, check=True,
                            capture_output=True, text=True)
    return [line for line in result.stdout.splitlines() if line]


def check_coverage(registry, pages, tracked, quiet=False):
    """Every corpus page and every tracked file must be governed by a rule."""
    unscoped_pages = [p for p in pages if registry.scope_for(p) is None]
    unscoped_files = [p for p in tracked if registry.scope_for(p) is None]
    if not quiet:
        print(f"corpus pages: {len(pages):,}  "
              f"unscoped: {len(unscoped_pages):,}")
        print(f"git-tracked files: {len(tracked):,}  "
              f"unscoped: {len(unscoped_files):,}")
        for path in unscoped_pages[:10]:
            print(f"    unscoped page: {path}")
        for path in unscoped_files[:10]:
            print(f"    unscoped file: {path}")
    return unscoped_pages, unscoped_files


def check_statements(registry):
    """The registry's own statements must be verifiable (see Scope.quote)."""
    return license_scopes.check(registry)


def audit(registry, tracked, list_limit):
    """Count published files by scope and permission; write the report."""
    per_scope = collections.Counter()
    per_permission = collections.Counter()
    details = collections.defaultdict(list)
    for path in tracked:
        row = registry.row_for(path)
        if row is None:
            continue
        per_scope[row.scope] += 1
        per_permission[row.redistribution] += 1
        if len(details[row.scope]) < list_limit:
            details[row.scope].append(path)

    rows = []
    for name in sorted(per_scope, key=lambda s: (-per_scope[s], s)):
        first = registry.by_scope[name][0]
        rows.append((name, first.redistribution, per_scope[name],
                     first.evidence,
                     first.terms.replace("\t", " ")))
    os.makedirs(REPORTS, exist_ok=True)
    out = os.path.join(REPORTS, "license-audit.tsv")
    with open(out, "w", encoding="utf-8") as fh:
        fh.write("# scope\tredistribution\ttracked_files\tstatement_file\tterms\n")
        for name, permission, count, evidence, terms in rows:
            fh.write(f"{name}\t{permission}\t{count}\t{evidence}\t{terms}\n")
        fh.write("# totals by permission\n")
        for permission in ("yes", "no", "unclear"):
            fh.write(f"{permission}\t{per_permission.get(permission, 0)}\n")
    return rows, per_permission, out


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--tracked", action="store_true",
                        help="audit the files Git tracks (publication)")
    parser.add_argument("--fail-on-restricted", action="store_true",
                        help="exit 1 when a published file may not be "
                             "published (redistribution != yes)")
    parser.add_argument("--report-only", action="store_true",
                        help="never fail on a permission, only on a broken "
                             "registry")
    parser.add_argument("--list", type=int, default=0,
                        help="print this many paths per scope in the audit")
    args = parser.parse_args()

    registry = license_scopes.Registry.load()
    pages = corpus_pages()
    tracked = tracked_files()

    unscoped_pages, unscoped_files = check_coverage(registry, pages, tracked)
    problems = len(unscoped_pages) + len(unscoped_files)
    problems += check_statements(registry)

    if args.tracked:
        rows, per_permission, out = audit(registry, tracked, args.list)
        print(f"\npublished (git-tracked) files by redistribution: "
              + ", ".join(f"{k} {per_permission.get(k, 0):,}"
                          for k in ("yes", "no", "unclear")))
        print(f"  {'scope':28s} {'may publish':11s} {'files':>8s}  terms")
        for name, permission, count, evidence, terms in rows:
            print(f"  {name:28s} {permission:11s} {count:8,d}  "
                  f"{terms[:80]}")
            if args.list:
                for path in sorted(_paths_for(registry, tracked, name))[
                        :args.list]:
                    print(f"      {path}")
        print(f"report written to {os.path.relpath(out, ROOT)}")
        if args.fail_on_restricted and not args.report_only:
            restricted = per_permission.get("no", 0) + per_permission.get(
                "unclear", 0)
            if restricted:
                print(f"\n{restricted:,} tracked file(s) are not licensed for "
                      "redistribution; this repository may not be published "
                      "as it is (docs/LICENSING.md).")
                problems += 1

    print(f"\n{problems} problem(s)")
    return 1 if problems else 0


def _paths_for(registry, tracked, scope):
    for path in tracked:
        row = registry.row_for(path)
        if row is not None and row.scope == scope:
            yield path


if __name__ == "__main__":
    raise SystemExit(main())
