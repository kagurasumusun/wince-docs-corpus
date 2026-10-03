#!/usr/bin/env python3
"""tools/alias_index.py -- the duplicate-page alias table.

``data/index/aliases.tsv`` records every page that ``tools/dedupe-corpus.py``
collapsed: the path that was removed, the identical path that was kept, and
both page ids.  Two things use it:

* the collection tools (``harvest.py``, ``crawl-mirror.py``, ``extract-chm.py``,
  ``import-media.py``) consult it before writing a page, so a re-run of the
  collection that produced a collapsed page does not put it back -- the
  duplicate is *known*, not an error to fix again;
* anything that has to resolve a page id (``tools/find-api.py`` and the
  knowledge base build) can follow the alias to the copy that still exists.

    import alias_index
    alias_index.load()                  # {removed_relpath: kept_relpath}
    alias_index.kept_for("corpus/chm/windows-ce-5.0/wcestylus5/html/x.html")
"""

import os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ALIASES = os.path.join(ROOT, "data", "index", "aliases.tsv")

_CACHE = None


def load(path=ALIASES):
    """{removed_path: kept_path} (repository-relative, ``/`` separators)."""
    global _CACHE
    aliases = {}
    if os.path.isfile(path):
        with open(path, encoding="utf-8") as fh:
            for line in fh:
                if line.startswith("#") or not line.strip():
                    continue
                parts = line.rstrip("\n").split("\t")
                if len(parts) >= 2:
                    aliases[parts[0]] = parts[1]
    if os.path.abspath(path) == os.path.abspath(ALIASES):
        _CACHE = aliases
    return aliases


def table():
    """The cached table (loads it on first use)."""
    global _CACHE
    if _CACHE is None:
        load()
    return _CACHE


def to_rel(path):
    """Absolute or corpus-relative path -> repository-relative ``/`` path."""
    if os.path.isabs(path):
        path = os.path.relpath(path, ROOT)
    return path.replace(os.sep, "/")


def kept_for(path):
    """The surviving copy of ``path``, or None when it is not an alias."""
    return table().get(to_rel(path))


def is_aliased(path):
    """True when ``path`` was collapsed into another copy by dedupe-corpus.

    A collection tool about to write ``path`` must skip it: the same document
    is already in the corpus under the recorded path.
    """
    return to_rel(path) in table()


def append(removed_relpath, kept_relpath, digest, size, page_id="",
           book="", kept_page_id="", kept_book=""):
    """Add one alias row (used when an importer collapses a page itself)."""
    row = "\t".join((removed_relpath, kept_relpath, digest, str(size), page_id,
                     book, kept_page_id, kept_book))
    need_header = not os.path.isfile(ALIASES)
    os.makedirs(os.path.dirname(ALIASES), exist_ok=True)
    with open(ALIASES, "a", encoding="utf-8") as fh:
        if need_header:
            fh.write("# removed_path\tkept_path\tmd5\tsize\tpage_id\tbook\t"
                     "kept_page_id\tkept_book\n")
        fh.write(row + "\n")
    if _CACHE is not None:
        _CACHE[removed_relpath] = kept_relpath
