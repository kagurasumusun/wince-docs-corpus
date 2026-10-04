#!/usr/bin/env python3
"""tools/check-policy.py -- is corpus/ still only Windows CE documentation?

The corpus has one rule: it holds the documentation Microsoft published for
Windows CE and its derivatives, **plus** the part of the Win32 documentation
that Windows CE shares (``tools/ce_api_names.py``), **plus** the open-source
documentation pages named in ``queues/oss-docs.tsv`` and nowhere else.
Everything else - source code, samples, another product's documentation, a
vendor's marketing pages, the paperwork a web server left on a CD - is out of
scope.

This checker makes that rule executable, so a harvest, an import or a re-run of
the Win32 import cannot quietly widen the corpus.  It is run by the workflows
after every collection step.

    python3 tools/check-policy.py            # summary; exit 1 on a violation
    python3 tools/check-policy.py --json     # machine readable

Checks
  * The corpus trees are the declared ones: the CE trees (``learn``, ``chm``,
    ``mvb``, ``msdn-library``, ``kb``), the separate ``dotnet`` tree for the
    .NET-family sets of the same namespace, and ``win32`` for the shared
    surface.  A new top-level tree has to be added here deliberately.
  * corpus/win32/ holds **only** CE-shared API reference pages: every markdown
    page must be a ``<kind>-<module>-<name>.md`` sdk-api page whose name
    Windows CE documents, and its module must not be in
    ``data/win32-exclude.tsv``.  No ``guide/`` tree: the Win32 programming
    guides are desktop documentation (``tools/fetch-upstream.py guides`` can
    extract them outside the repository).
  * No source code, binaries or images anywhere under corpus/.
  * No web-server or installer leftovers: ``_vti_cnf``/``_vti_pvt``/``_derived``
    (FrontPage metadata), ``Code Samples/``, vendor ``Sponsors/`` trees.
  * The top-level corpus directories are the known ones (a new top-level tree
    has to be added here deliberately).
"""

import argparse
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import ce_api_names  # noqa: E402

ROOT = ce_api_names.ROOT
CORPUS = os.path.join(ROOT, "corpus")

# Documentation pages.  Everything else under corpus/ is a violation.
PAGE_EXT = (".html", ".htm", ".md")
PAPERWORK = {"README.md", "PROVENANCE.md"}

# The corpus trees that may exist.
TOP_LEVEL = {"README.md", "learn", "dotnet", "chm", "mvb", "msdn-library", "kb",
             "site", "win32", "oss"}

# Windows CE product history, documented in ``corpus/win32/README.md``: these
# are the sections whose pages make up the CE-specific half.  ``dotnet`` is
# the documented-elsewhere tree: the .NET-family sets that shipped in the same
# namespace (POS for .NET, .NET Compact Framework, .NET Micro Framework).  They
# are Windows-Embedded documentation of a *layer on top of* CE, kept separate
# from the OS/SDK material that an include/def database is built from.
CE_SECTIONS = {"learn", "chm", "mvb", "msdn-library", "kb", "site"}
OTHER_SECTIONS = {"dotnet", "oss"}

# Things that must not come back (a CD image's or a web server's leftovers, not
# documentation of the product).
JUNK = re.compile(
    r"(^|/)(_vti_cnf|_vti_pvt|_derived|_private|Code Samples|qworks|Sponsors|"
    r"MPLAYER2|MPSUPP|ACCESSIB|Handhelds|"
    r"Windows_CE_Developers_Conference_DevCon_99_Conference_CD)(/|$)",
    re.IGNORECASE)

# Detector only - a source file in the corpus is a policy violation.
SOURCE_EXT = (".c", ".h", ".cpp", ".cxx", ".hpp", ".cs", ".vb", ".java",
              ".rc", ".def", ".asm", ".s", ".inc", ".mak", ".dsp", ".dsw",
              ".vbp", ".vcp", ".vcproj", ".sln", ".py", ".js", ".ps1", ".sh",
              ".lib", ".obj", ".dll", ".exe", ".sys", ".pdb", ".ocx", ".cab",
              ".zip", ".iso", ".hlp", ".chm")


def rel(path):
    return os.path.relpath(path, ROOT).replace(os.sep, "/")


def walk():
    for dirpath, dirnames, filenames in os.walk(CORPUS):
        dirnames.sort()
        for name in sorted(filenames):
            yield os.path.join(dirpath, name)


def check_win32(problems, checked):
    """corpus/win32/ may only hold CE-shared sdk-api pages."""
    base = os.path.join(CORPUS, "win32")
    if not os.path.isdir(base):
        return
    names = ce_api_names.load_names()
    excluded = ce_api_names.load_excluded()
    shared = 0
    for path in walk():
        if not path.startswith(base + os.sep):
            continue
        page = rel(path)
        name = os.path.basename(path)
        if not path.endswith(".md") or name in PAPERWORK:
            continue
        if page.startswith("corpus/win32/guide/"):
            problems.append(
                ("desktop-guide", page,
                 "the Win32 programming guides are desktop documentation; "
                 "extract them outside the corpus "
                 "(tools/fetch-upstream.py guides --out DIR)"))
            continue
        match = ce_api_names.SDK_PAGE.match(name)
        if not match:
            problems.append(("not-an-api-page", page,
                             "not a <kind>-<module>-<name>.md sdk-api page"))
            continue
        _kind, module, api_name = match.groups()
        if ce_api_names.module_excluded(module, excluded):
            problems.append(("excluded-module", page,
                             f"module {module} is in data/win32-exclude.tsv"))
            continue
        hit = ce_api_names.documented(ce_api_names.normalize(api_name), names)
        if not hit:
            problems.append(
                ("not-ce-shared", page,
                 f"Windows CE does not document {api_name!r}; the page is "
                 "desktop-only context, not Win32-common material"))
            continue
        shared += 1
    checked["win32_shared_pages"] = shared


def check_sections(problems, checked):
    """Count the CE trees separately from the documented-elsewhere tree."""
    counts = {}
    for path in walk():
        page = rel(path)
        if not page.startswith("corpus/"):
            continue
        section = page.split("/")[1]
        if os.path.splitext(path)[1].lower() not in PAGE_EXT:
            continue
        if os.path.basename(path) in PAPERWORK:
            continue
        counts[section] = counts.get(section, 0) + 1
    checked["section_pages"] = counts
    ce = sum(counts.get(s, 0) for s in CE_SECTIONS)
    other = sum(counts.get(s, 0) for s in OTHER_SECTIONS)
    checked["ce_pages"] = ce
    checked["other_pages"] = other


def check_junk(problems, checked):
    pages = sources = 0
    for path in walk():
        page = rel(path)
        if JUNK.search(page):
            problems.append(("junk-path", page,
                             "leftover of a medium or a web server, not "
                             "documentation of the product"))
            continue
        name = os.path.basename(path)
        if name in PAPERWORK:
            continue
        ext = os.path.splitext(name)[1].lower()
        if ext in SOURCE_EXT:
            sources += 1
            problems.append(("source-or-binary", page,
                             "the corpus is documentation only"))
        elif ext not in PAGE_EXT:
            problems.append(("not-a-page", page,
                             "only .html/.htm/.md pages belong in corpus/"))
        else:
            pages += 1
    checked["pages"] = pages


def check_oss(problems, checked):
    """corpus/oss/ may hold only the pages named in queues/oss-docs.tsv.

    The list is the door.  A page that is not on it, or a listed page that is
    not a documentation page, is a violation.  Source extensions are already
    refused by check_junk; this check refuses a document that was never
    accepted.
    """
    listed = os.path.join(ROOT, "queues", "oss-docs.tsv")
    allowed = set()
    if os.path.isfile(listed):
        with open(listed, encoding="utf-8") as fh:
            for line in fh:
                if not line.strip() or line.startswith("#"):
                    continue
                path = line.split("\t", 1)[0].strip()
                if path:
                    allowed.add(path)
    base = os.path.join(CORPUS, "oss")
    found = set()
    if os.path.isdir(base):
        for path in walk():
            if not path.startswith(base + os.sep):
                continue
            page = rel(path)
            name = os.path.basename(path)
            if name in PAPERWORK:
                continue
            found.add(page)
            if page not in allowed:
                problems.append((
                    "oss-not-allowlisted", page,
                    "not in queues/oss-docs.tsv; open-source documentation is "
                    "collected only by that list, and source trees are not "
                    "collected"))
    for page in sorted(allowed - found):
        problems.append((
            "oss-missing", page,
            "named in queues/oss-docs.tsv but not in corpus/"))
    checked["oss_pages"] = len(found)


def check_top_level(problems, checked):
    found = set()
    for entry in sorted(os.listdir(CORPUS)):
        found.add(entry)
        if entry not in TOP_LEVEL:
            problems.append(("unknown-tree", "corpus/" + entry,
                             "add it to TOP_LEVEL only when it really is a "
                             "Windows CE documentation tree"))
    checked["trees"] = sorted(found)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args()

    problems = []
    checked = {}
    check_top_level(problems, checked)
    check_sections(problems, checked)
    check_junk(problems, checked)
    check_win32(problems, checked)
    check_oss(problems, checked)

    if args.json:
        print(json.dumps({"problems": problems, "checked": checked},
                         indent=2, ensure_ascii=False))
    else:
        print(f"corpus/            {checked.get('pages', 0):,} pages in "
              f"{len(checked.get('trees', []))} trees")
        print(f"  CE trees         {checked.get('ce_pages', 0):,} pages "
              f"({', '.join(sorted(CE_SECTIONS))})")
        print(f"  other layers     {checked.get('other_pages', 0):,} "
              f"pages ({', '.join(sorted(OTHER_SECTIONS))}; "
              f"oss allowlist {checked.get('oss_pages', 0):,})")
        print(f"corpus/win32/api/  {checked.get('win32_shared_pages', 0):,} "
              f"CE-shared API pages")
        if not problems:
            print("policy             OK - CE documentation, the shared Win32 "
                  "surface, the separate .NET layer, and the allowlisted "
                  "open-source documentation")
            return 0
        kinds = {}
        for kind, _path, _why in problems:
            kinds[kind] = kinds.get(kind, 0) + 1
        print("policy             %d violation(s): %s"
              % (len(problems),
                 ", ".join(f"{k} x{v}" for k, v in sorted(kinds.items()))))
        for kind, path, why in problems[:50]:
            print(f"  {kind:16s} {path}\n{'':19s}{why}")
        if len(problems) > 50:
            print(f"  ... {len(problems) - 50} more")
        return 1

    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
