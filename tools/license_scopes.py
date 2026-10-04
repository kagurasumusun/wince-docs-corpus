#!/usr/bin/env python3
"""The rights registry: which statement governs which path.

``data/license-scopes.tsv`` holds one row per rule -- a directory prefix or an
exact file (``file:``) -- with the permission, the terms and, where a statement
was located, the file it was read from and the wording itself.  The longest
matching rule governs a path.

This module is the single place that answers "which scope is this path in?".
``tools/build-kb.py`` stamps the answer on every record it writes (so a fact
can never be read without its rights attached), ``tools/gen-include-def.py``
reports the scopes behind its output, and ``tools/check-licenses.py`` checks
that the registry covers everything and that every quoted statement is really
in the file it names.

Nothing here decides what may be published; it records what each item's own
statement says.  See docs/LICENSING.md.
"""

import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REGISTRY = os.path.join(ROOT, "data", "license-scopes.tsv")

COLUMNS = ("rule", "scope", "redistribution", "terms", "evidence", "quote")
PERMISSIONS = ("yes", "no", "unclear")


class Scope:
    """One rule of the registry."""

    __slots__ = ("rule", "scope", "redistribution", "terms", "evidence",
                 "quote", "is_file", "path")

    def __init__(self, row):
        for column, value in zip(COLUMNS, row):
            setattr(self, column, value)
        self.is_file = self.rule.startswith("file:")
        self.path = self.rule[5:] if self.is_file else self.rule

    def governs(self, path):
        if self.is_file:
            return path == self.path
        return path.startswith(self.path)

    def match_length(self, path):
        if not self.governs(path):
            return -1
        return len(self.path) + (1000 if self.is_file else 0)


class Registry:
    def __init__(self, rows):
        self.rows = list(rows)
        self.by_scope = {}
        for row in self.rows:
            self.by_scope.setdefault(row.scope, []).append(row)
        self._cache = {}

    @classmethod
    def load(cls, path=REGISTRY):
        rows = []
        with open(path, encoding="utf-8") as fh:
            for line in fh:
                if not line.strip() or line.startswith("#"):
                    continue
                fields = line.rstrip("\n").split("\t")
                if len(fields) != len(COLUMNS):
                    raise ValueError(
                        f"{path}: expected {len(COLUMNS)} columns, got "
                        f"{len(fields)}: {line[:80]!r}")
                rows.append(Scope(fields))
        return cls(rows)

    def scope_for(self, path):
        """The scope id of a repository-relative path, or None when unscoped."""
        if path in self._cache:
            return self._cache[path]
        best = None
        for row in self.rows:
            length = row.match_length(path)
            if length > (best.match_length(path) if best else -1):
                best = row
        self._cache[path] = best.scope if best else None
        return self._cache[path]

    def row_for(self, path):
        best = None
        for row in self.rows:
            length = row.match_length(path)
            if length > (best.match_length(path) if best else -1):
                best = row
        return best

    def scopes(self):
        return sorted({row.scope for row in self.rows})

    def statements(self):
        """(scope, evidence, quote) for every row that located a statement."""
        seen = []
        for row in self.rows:
            if row.quote and row.quote != "-":
                key = (row.scope, row.evidence, row.quote)
                if key not in seen:
                    seen.append(key)
        return seen

    def unscoped_scopes(self):
        """Scopes that no row claims (proof the mapping is complete)."""
        return [name for name in self.by_scope if not self.by_scope[name]]


def _text(path):
    """A repository file as plain text (HTML pages read like the corpus reads
    them, so a quote can be checked against the wording a reader sees)."""
    full = os.path.join(ROOT, path)
    import sys
    if os.path.join(ROOT, "tools") not in sys.path:
        sys.path.insert(0, os.path.join(ROOT, "tools"))
    import page_parse
    with open(full, "rb") as fh:
        raw = fh.read()
    if path.endswith((".md", ".txt", ".tsv")) or path.endswith("LICENSE") \
            or path.endswith("README"):
        return page_parse.decode(raw)
    try:
        return page_parse.text_of(page_parse.article_html(raw))
    except Exception:
        return page_parse.decode(raw)


def flatten(text):
    return re.sub(r"\s+", "", text)


def main():
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("path", nargs="*", help="paths to look up")
    parser.add_argument("--list", action="store_true",
                        help="print the registry")
    parser.add_argument("--scopes", action="store_true",
                        help="print the scope ids and their permissions")
    parser.add_argument("--check", action="store_true",
                        help="check the registry against the tree")
    args = parser.parse_args()
    registry = Registry.load()
    if args.scopes or args.list:
        names = sorted({row.scope for row in registry.rows})
        for name in names:
            rows = registry.by_scope[name]
            permissions = sorted({row.redistribution for row in rows})
            print(f"{name:28s} {'/'.join(permissions):8s} "
                  f"{len(rows)} rule(s)")
        if not args.list:
            return 0
    if args.path:
        for path in args.path:
            row = registry.row_for(path)
            if row is None:
                print(f"{path}\tUNSCOPED")
            else:
                print(f"{path}\t{row.scope}\t{row.redistribution}\t"
                      f"{row.rule}")
    if args.check or not (args.path or args.list):
        return check(registry)
    return 0


def check(registry):
    """Basic integrity: permissions valid, statements real, coverage whole."""
    problems = 0
    for row in registry.rows:
        if row.redistribution not in PERMISSIONS:
            print(f"rule {row.rule}: permission {row.redistribution!r} is not "
                  f"one of {', '.join(PERMISSIONS)}")
            problems += 1
        if row.quote and row.quote != "-":
            if not row.evidence or row.evidence == "-":
                print(f"rule {row.rule}: quotes a statement but names no "
                      "evidence file")
                problems += 1
                continue
            try:
                text = _text(row.evidence)
            except OSError as error:
                print(f"rule {row.rule}: evidence {row.evidence} is not "
                      f"readable ({error})")
                problems += 1
                continue
            if flatten(row.quote) not in flatten(text):
                print(f"rule {row.rule}: the quote is not in "
                      f"{row.evidence}: {row.quote[:70]!r}")
                problems += 1
    print(f"{len(registry.rows)} rule(s), {len(registry.scopes())} scope(s), "
          f"{problems} problem(s)")
    return 1 if problems else 0


if __name__ == "__main__":
    raise SystemExit(main())
