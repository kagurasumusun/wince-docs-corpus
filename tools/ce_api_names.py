#!/usr/bin/env python3
"""tools/ce_api_names.py -- the API names Windows CE documents.

This module is the single source of truth for the "Win32-common" half of the
corpus: a Win32 API page belongs in ``corpus/win32/`` only when Windows CE's own
documentation documents that API name.  Three tools read it:

* ``tools/fetch-upstream.py``  decides which sdk-api pages are imported;
* ``tools/build-win32-map.py`` annotates the imported pages;
* ``tools/build-ce-api-names.py`` writes the reviewable report
  ``data/reports/ce-api-names.tsv`` (the evidence behind every name).

Where the names come from
-------------------------

1. **The official catalogs of the harvested sets** (``data/catalogs/*.tsv``):
   the page titles of the Windows CE 3.0 / 5.0 / .NET 4.x / Embedded CE 6.0
   product documentation, normalised: ``CreateFile (Windows CE 5.0)`` ->
   ``createfile``, ``IDirectDrawVideo::CanUseOverlayStretch (Windows CE 5.0)``
   -> ``idirectdrawvideocanuseoverlaystretch``.  These four sets are the
   reference-bearing ones, and their titles cover interfaces and methods that
   the generic index extractor misses.

2. **The CE sets that have no catalog** (the names the index extracted from the
   pages themselves, ``data/index/corpus.sqlite3``, see
   ``tools/build-index-sql.py``): CE 1.0/2.0 Books Online (``mvb/``), the MSDN
   Library CE sets (``msdn-library/techshelps/``, ``msdn-library/
   datadungeon-2000-04/``), the CE 2.12 SDK on the DevCon '99 disc
   (``msdn-library/wcedevcon-99/``), the 2010-05 capture, Windows Mobile 6.5,
   the KnowledgeBase and the CE 4.2/5.0 CHM trees.

   The .NET object documentation is deliberately **not** mined
   (``corpus/dotnet/``: POS for .NET, the Compact Framework, the Micro
   Framework, and the ``VBCE``/``vbce``/``adoce`` sets of the MSDN Library):
   its class and property names (``Font``, ``Image``, ``CheckColors``) collide
   with unrelated Win32 pages.

3. Names and modules listed in ``data/win32-exclude.tsv`` are removed again:
   a CE page and a Win32 page can share a name and document different things
   (CE's ``Run (Windows Media Player)`` vs. the ``RUN`` printer-driver struct),
   and a handful of sdk-api modules (Windows Runtime, Direct2D, Core Audio,
   display cloning) document APIs Windows CE never had.

Nothing here decides *which pages* exist - ``tools/fetch-upstream.py`` does
that, together with the ANSI/Unicode rule that ``CreateFileA``/``CreateFileW``
belong to a CE-documented ``CreateFile``.
"""

import glob
import os
import re
import sqlite3

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CATALOG_DIR = os.path.join(ROOT, "data", "catalogs")
DB_PATH = os.path.join(ROOT, "data", "index", "corpus.sqlite3")
EXCLUDE_PATH = os.path.join(ROOT, "data", "win32-exclude.tsv")

# The four catalogs whose titles alone decide membership: these are the sets
# whose product documentation is an API reference (CE 3.0/5.0/.NET 4.x/6.0).
CATALOGED_SETS = (
    "chm/windows-ce-3.0",
    "learn/windows-ce-5.0",
    "learn/windows-ce-net-4x",
    "learn/windows-embedded-ce-6.0",
)

# Sets mined from the index instead (no catalog exists for them).  Prefixes.
# ``corpus/site/`` is deliberately absent: those pages are the CE-era
# whitepapers/product pages (the Win32 model, porting notes), not an API
# reference, so they contribute no names.
MINE_SECTIONS = (
    "mvb/",
    "msdn-library/techshelps/",
    "msdn-library/datadungeon-2000-04/",
    "msdn-library/wcedevcon-99/",
    "msdn-library/2010-05/",
    "msdn-library/windows-mobile-6.5/",
    "kb/",
    "chm/windows-ce-4.2/",
    "chm/windows-ce-5.0/",
    "learn/unclassified/",
)

# ... minus the object-model documentation of the .NET products, whose member
# names are not Win32 API names (see the docstring).
MINE_EXCLUDE = (
    "msdn-library/techshelps/VBCE",
    "msdn-library/datadungeon-2000-04/vbce",
    "msdn-library/datadungeon-2000-04/adoce",
    "dotnet/",
)

# sdk-api page file names: ``nf-fileapi-createfilew.md``.
# nf=function ns=struct ne=enum nc=callback ni=IOCTL/other interface code
# nn=interface nl=class/library na=attribute
SDK_PAGE = re.compile(r"^(nf|ns|ne|nc|ni|nn|nl|na)-([^-]+)-(.+)\.md$")

# What a page title has to look like to contribute a name: the index stores the
# page's own title (``title``) and, for markdown, the API name of its file
# (``api``).  Prototypes/structs/constants printed *inside* pages are not used:
# they also pick up sample code and header artifacts.
MINE_KINDS = ("title", "api")

MIN_LEN = 3                      # drop one/two-letter fragments


def normalize(text):
    """``CreateFile (Windows CE 5.0)`` -> ``createfile``.

    Also ``IDirectDrawVideo::CanUseOverlayStretch (Windows CE 5.0)`` ->
    ``idirectdrawvideocanuseoverlaystretch``.
    """
    text = text.lower()
    text = re.sub(r"\(.*?\)", "", text)
    text = re.sub(r"\s+", "", text)
    return re.sub(r"[^a-z0-9_]", "", text)


def base_name(name):
    """``createfilew`` -> ``createfile`` (the A/W variant of a shared name)."""
    return name[:-1] if name.endswith(("a", "w")) else name


def load_excluded(path=EXCLUDE_PATH):
    """``data/win32-exclude.tsv`` -> {'name': {...}, 'module': {...}}."""
    excluded = {"name": set(), "module": set()}
    if not os.path.isfile(path):
        return excluded
    with open(path, encoding="utf-8", errors="replace") as fh:
        for line in fh:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            parts = line.split("\t")
            if len(parts) < 2:
                continue
            kind, value = parts[0].strip(), parts[1].strip()
            if kind in excluded and value:
                excluded[kind].add(normalize(value))
    return excluded


def load_catalogs():
    """{name: {(page_id, title, set)}} from the four official catalogs."""
    entries = {}
    for path in sorted(glob.glob(os.path.join(CATALOG_DIR, "*.tsv"))):
        book = os.path.basename(path)[:-4]
        with open(path, encoding="utf-8", errors="replace") as fh:
            for line in fh:
                parts = line.rstrip("\n").split("\t")
                if len(parts) < 2:
                    continue
                name = normalize(parts[1])
                if name:
                    entries.setdefault(name, set()).add(
                        (parts[0], parts[1], book))
    return entries


def load_mined(db_path=DB_PATH):
    """{name: {(page_id, title, section)}} from the uncatalogued CE sets."""
    entries = {}
    if not os.path.isfile(db_path):
        return entries
    con = sqlite3.connect(db_path)
    try:
        rows = con.execute(
            "SELECT n.name, p.section, p.page_id, p.title, n.kind"
            " FROM names n JOIN pages p ON p.page_id = n.page_id")
        for name, section, page_id, title, kind in rows:
            if kind not in MINE_KINDS:
                continue
            if section.startswith("win32"):
                continue
            if section.startswith(CATALOGED_SETS):
                continue
            if not section.startswith(MINE_SECTIONS):
                continue
            if section.startswith(MINE_EXCLUDE):
                continue
            normalised = normalize(name)
            if len(normalised) < MIN_LEN:
                continue
            entries.setdefault(normalised, set()).add(
                (page_id, title or name, section))
    finally:
        con.close()
    return entries


def load_names(db_path=DB_PATH):
    """The CE-documented API names.

    Returns ``{name: {"catalog": {(id, title, set)},
                      "corpus":  {(id, title, section)}}}`` with the review
    exceptions already applied.
    """
    names = {}
    for name, entries in load_catalogs().items():
        names.setdefault(name, {})["catalog"] = entries
    for name, entries in load_mined(db_path).items():
        names.setdefault(name, {})["corpus"] = entries

    excluded = load_excluded()
    for name in excluded["name"]:
        names.pop(name, None)
    return names


def documented(name, names):
    """True when CE documents ``name`` (or, for A/W variants, its base name).

    ``names`` is a mapping as returned by :func:`load_names`.
    """
    if name in names:
        return name
    base = base_name(name)
    if base != name and base in names:
        return base
    return None


def module_excluded(module, excluded=None):
    excluded = excluded if excluded is not None else load_excluded()
    return normalize(module) in excluded["module"]
