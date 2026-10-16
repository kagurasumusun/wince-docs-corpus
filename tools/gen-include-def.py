#!/usr/bin/env python3
"""tools/gen-include-def.py -- knowledge/ -> include/def material.

This is the first consumer of the knowledge base, and it exists to prove the
pipeline end to end: take the machine-readable statements in ``knowledge/`` and
write the material an include/def generator would be built from.

    python3 tools/gen-include-def.py --out winsur
                                     # THE product: ONE tree for every CE
                                     # generation (the default build)
    python3 tools/gen-include-def.py --unified --out build/generated/wince
                                     # the same, --unified spelled out
    python3 tools/gen-include-def.py --set learn/windows-ce-5.0 \
        --out build/generated/wince50       # per-generation build, for
                                            # comparison only -- never the
                                            # product
    python3 tools/gen-include-def.py --set chm/windows-ce-3.0 --out ... \
        --no-borrow            # only declarations from that set's own pages
    python3 tools/gen-include-def.py --list      # sets that can be generated

The **default (unified)** build answers "what is the include/def surface of
Windows CE as a whole?": a single tree, never one tree per generation.  Where
generations differ the tree carries a derived ``#if defined(_WIN32_WCE) &&
...`` branch (``_WIN32_WCE`` is the version macro the documentation itself
prints -- the CE .NET pages write ``#if (_WIN32_WCE < 300)``).  The
Win32-shared half of the surface lives in the SAME tree, marked as the
desktop reference wherever it is the only statement -- never a second tree.
A constant's derived ``#define`` is filed into the header the linkage table
assigns it (``kb/constant-headers.tsv``), with its evidence and the strength
of the linkage printed beside it; the weakest ranks (the pinvoke weak
auxiliary hint, the pinned reference headers) are marked loudly.  Values
that differ per CE generation pool into shared ``#if``/``#elif`` chains;
disagreements within one generation are conflicts -- each keeps a CONFLICT
block, and only a reviewed resolution (``kb/constant-conflicts.tsv``, the
review in ``data/constant-value-review.tsv``) writes the reviewed print the
pages themselves state.  Each fragment is laid out for reading: constants
first, then the macro blocks, the types (structures and enums, plus derived
member outlines for structures whose body no page prints) and the functions.

What it writes (nothing is added to the repository -- ``--out`` is yours):

    include/<Header>.h.fragment   the declarations of that header, verbatim,
                                  each with the page it was read from
    link/<Module>.def             EXPORTS material per library/DLL, with the
                                  source of every name (a *worklist*, see the
                                  warning the file itself carries)
    manifest.tsv                  entity <-> header files/libraries <-> declaration
                                  id <-> source page, for traceability
    report.md                     what was generated, what was skipped and why

Honesty rules (the same ones the knowledge base keeps):

* the declaration text is quoted verbatim; nothing is reformatted, completed
  or repaired.  A ``collapsed`` declaration is still written (with the flag in
  the manifest).  When ``--borrow`` is on, another CE page's copy is used
  instead only when, whitespace aside, it is the same text and that page kept
  the spaces.  A copy that also adds a calling convention, a parameter name
  or a different type is not a spacing repair, and the collapsed text stays;
* a declaration is borrowed from another corpus set only when the same entity
  is documented there, and the borrowing is recorded per declaration in
  ``manifest.tsv`` (``borrowed_from``) and in the fragment's comment.  A
  fallback to a Win32 reference page is used only when no CE set prints the
  declaration, and it is marked as such: those pages document the shared
  surface as *desktop* Windows, while Windows CE is not the whole of Win32;
* a header and a library are taken from the version being built.  Another
  CE set's statement is used only when this version's pages state none, and
  it is marked (``header_from`` / ``library_from``).  A Win32 reference
  header (``processthreadsapi.h``, ``windows.h``) is a marked fallback, never
  passed off as a Windows CE header.  Within the chosen statement, a page
  that names ``Wilhelm.h, Otto.h`` has the declaration written into each of
  those files, because that is what the page says.  A library cell that
  names several files (``Ole32.lib, Uuid.lib``, ``A.lib or B.lib``) likewise
  writes the export into each of those worklists.  ``Shell32.dll (version
  4.0 or later)`` names one file; the ``or`` is version prose and is not a
  second library.  A value that names no file at all (``Library: Developer
  Implemented``) is *not* turned into a file name, it is counted in
  ``report.md`` and stays visible in ``knowledge/reports/filtered-values.tsv``;
* a numbered constant is a table row the page prints (``kb/constants.jsonl``).
  The fragment quotes that row and, below it, a ``#define`` whose keyword the
  page did not print -- the comment says so.  Pages that disagree on the
  number produce a CONFLICT block and, without a reviewed resolution, no
  ``#define``; a resolved conflict writes only a print the pages themselves
  state, with the verdict quoted above it.  A number stated only by the
  Win32 reference is not borrowed: desktop and Windows CE values are
  not assumed to match, and no number is ever taken from the pinned
  reference headers under ``sources/`` (they may state which header
  defines a name -- never what it equals);
* a library and a DLL are kept apart (``coredll.lib`` in the library field,
  ``coredll.dll`` in the DLL field) and the worklist file is named after the
  module both spellings refer to, with the spellings it was stated as printed
  at the top.  Only functions and callbacks become export lines -- a struct,
  a typedef or a C++/COM member (``Interface::Method``,
  ``MSMQMessage.Priority``) is not an export.  The page printed
  ``get_Priority`` inside the quoted prototype; that quote is not split
  into an export name the page did not print as one;
* everything the documents do not state is left out and listed in
  ``report.md``: no header, no declaration, no library -> a gap to collect,
  never a guess;
* symbol decoration (the ``_Name@N`` spelling of an exported stdcall function)
  and the export table of a real library are *not* in the documentation, so
  the ``.def`` output says so at the top instead of pretending to be complete.
  Ordinals are written **only** where a page prints them: the 94 rows of
  ``kb/export-ordinals.tsv`` (the floating point C run-time library) become
  ``name @ordinal`` with the page in the comment, and every other line is a
  name with no ordinal, because no document gives it one.
"""

import argparse
import collections
import csv
import gzip
import json
import os
import re
import shutil
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
# Splits a requirement *value* already stored in knowledge/.  It does not
# read a corpus page.  The generator still refuses corpus paths below.
import page_parse  # noqa: E402
import html_clean  # noqa: E402
import header_map  # noqa: E402
import quality_filters  # noqa: E402
import w32api_gaps  # noqa: E402
import pinvoke_gaps  # noqa: E402

KB = os.path.join(ROOT, "knowledge", "kb")

# The clean-room wall (docs/clean-room.md): this generator reads the
# *specification* (knowledge/), never the corpus pages the specification was
# built from.  Anything that reaches into corpus/ is counted and refused, so a
# build of a generated header cannot depend on a page a reader may not take.
CORPUS_READS = []

# Constants a Windows CE page states are not supported; filled in main().
UNSUPPORTED = {}


def is_corpus(path):
    rel = os.path.relpath(path, ROOT)
    return rel == "corpus" or rel.startswith("corpus" + os.sep)


def check_spec_path(path):
    """Refuse a corpus path: the generator reads knowledge/ only."""
    if is_corpus(path):
        CORPUS_READS.append(os.path.relpath(path, ROOT))
        raise RuntimeError(f"{os.path.relpath(path, ROOT)} is a corpus page: "
                           "the generator reads knowledge/ only "
                           "(docs/clean-room.md)")


def read_text(path):
    """Open a text file, refusing the corpus (the specification only)."""
    check_spec_path(path)
    with open(path, "r", encoding="utf-8") as fh:
        return fh.read()

DECLARATIONS = os.path.join(KB, "declarations.jsonl.gz")
ENTITIES = os.path.join(KB, "entities.jsonl.gz")
REQUIREMENTS = os.path.join(KB, "requirements.jsonl.gz")
CONSTANTS = os.path.join(KB, "constants.jsonl.gz")
UNIFIED_DIR = os.path.join(ROOT, "knowledge", "unified")
UNIFIED_CONSTANTS = os.path.join(UNIFIED_DIR, "constants.jsonl")
UNIFIED_DECLARATIONS = os.path.join(UNIFIED_DIR, "declarations.jsonl")
CONSTANT_HEADERS = os.path.join(KB, "constant-headers.tsv")
CONSTANT_CONFLICTS = os.path.join(KB, "constant-conflicts.tsv")
PINVOKE_APIS = os.path.join(ROOT, "knowledge", "aux",
                            "pinvoke-apis.jsonl.gz")
PINVOKE_CONSTANTS = os.path.join(ROOT, "knowledge", "aux",
                                 "pinvoke-constants.jsonl.gz")
BASE_TYPES = os.path.join(KB, "base-types.tsv")
EXTRA_DEFINES = os.path.join(KB, "extra-defines.tsv")

# The documentation prints header and library names as they are; these pull
# the file names out of a value and leave the prose alone.
HEADER_FILE = re.compile(r"[\w.+-]*\.(?:h|hpp|hh|hxx|idl|inc)\b", re.I)
MODULE_FILE = re.compile(r"(?P<base>[\w.+-]+?)\.(?P<ext>lib|dll|drv|sys|ocx|tlb)\b",
                         re.I)
EXPORTABLE = ("function", "callback")

def heuristic_entity_header(entity, lib_to_header=None, heuristic_rows=None):
    """Assign a header to an entity from naming conventions / library map.

    Returns the header name if a pattern matches, None otherwise.  Marked
    ``heuristic-prefix`` by the caller -- never passed off as a page statement.
    """
    name = entity.get("name") or ""
    if not name:
        return None
    if heuristic_rows and name in heuristic_rows:
        return heuristic_rows[name]
    header = header_map.header_for_entity(name, entity.get("kinds") or [])
    if header:
        return header
    libs = (entity.get("libraries") or []) + (entity.get("dlls") or [])
    for lib in libs:
        mapped = header_map.header_for_library(lib)
        if mapped:
            return mapped
        if lib_to_header:
            stem = (module_of(lib) or (lib.lower(), ""))[0].lower()
            if stem in lib_to_header:
                return lib_to_header[stem]
    return None


def looks_like_c_declaration(text):
    return quality_filters.looks_like_c_declaration(text or "")


def load_heuristic_headers():
    """kb/heuristic-headers.tsv -> {name: header}."""
    path = os.path.join(KB, "heuristic-headers.tsv")
    out = {}
    if not os.path.exists(path):
        return out
    with open(path, encoding="utf-8") as fh:
        header = fh.readline().rstrip("\n").split("\t")
        for line in fh:
            cells = line.rstrip("\n").split("\t")
            if len(cells) < 2:
                continue
            row = dict(zip(header, cells)) if header else {}
            name = row.get("name") or cells[0]
            hdr = row.get("header") or cells[1]
            if name and hdr:
                out[name] = hdr
    return out


def load_modules_ce_headers():
    """kb/modules-ce.tsv -> {module_stem: header} for rows with field=header."""
    path = os.path.join(KB, "modules-ce.tsv")
    out = {}
    if not os.path.exists(path):
        return out
    with open(path, encoding="utf-8") as fh:
        header = fh.readline().rstrip("\n").split("\t")
        for line in fh:
            cells = line.rstrip("\n").split("\t")
            if len(cells) < len(header):
                continue
            row = dict(zip(header, cells))
            if (row.get("field") or "").lower() != "header":
                continue
            module = (row.get("module") or "").strip()
            value = row.get("value") or ""
            files = header_files([value])
            if module and files:
                out.setdefault(module.lower(), files[0])
    return out


def build_lib_to_unique_header(entities):
    """library stem -> header when every entity of that lib names one header."""
    counts = collections.defaultdict(collections.Counter)
    for entity in entities:
        headers = header_files(entity.get("headers") or [])
        libs = (entity.get("libraries") or []) + (entity.get("dlls") or [])
        if not headers or not libs:
            continue
        for lib in libs:
            parsed = module_of(lib)
            stem = (parsed[0] if parsed else lib).lower()
            for h in headers:
                counts[stem][h] += 1
    out = {}
    for stem, ctr in counts.items():
        if len(ctr) == 1:
            out[stem] = next(iter(ctr))
        else:
            mapped = header_map.header_for_library(stem)
            if mapped:
                out[stem] = mapped
    return out


def load_extra_surface():
    """Load extra-defines / extra-declarations, quality-filtered.

    Returns (defines, declarations) -- each item already sanitised.
    """
    defines = []
    by_name = collections.defaultdict(list)
    for row in load_extra_defines():
        by_name[row.get("name") or ""].append(row)
    for name, rows in by_name.items():
        best = quality_filters.pick_best_define(rows)
        if best:
            defines.append(best)
    decls = []
    seen = set()
    for fname in ("extra-declarations.jsonl", "harvest-declarations.jsonl"):
        extra_path = os.path.join(KB, fname)
        if not os.path.exists(extra_path):
            continue
        with open(extra_path, encoding="utf-8") as fh:
            for line in fh:
                rec = json.loads(line)
                name = rec.get("name") or ""
                if not name or name in seen:
                    continue
                cleaned = quality_filters.sanitize_declaration(
                    rec.get("declaration") or "",
                    name,
                    rec.get("type") or "",
                )
                if not cleaned:
                    continue
                rec = dict(rec)
                rec["declaration"] = cleaned
                decls.append(rec)
                seen.add(name)
    return defines, decls


def load(path):
    check_spec_path(path)
    if not os.path.exists(path) and path.endswith(".gz"):
        path = path[:-3]
    if not os.path.exists(path):
        sys.exit(f"{os.path.relpath(path, ROOT)} not found -- run "
                 "python3 tools/build-kb.py first")
    opener = gzip.open if path.endswith(".gz") else open
    with opener(path, "rt", encoding="utf-8") as fh:
        for line in fh:
            line = line.strip()
            if line:
                yield json.loads(line)


def safe_name(value, extension=""):
    """A header/library value -> a file name.

    ``Winbase.h.`` -> ``Winbase.h``, and when the name already carries the
    extension the output adds (``Coredll.lib`` -> ``coredll.def``), it is
    dropped first so the file name is not doubled.
    """
    name = re.sub(r"[^A-Za-z0-9_.+-]", "_", value.strip().rstrip(". ")) \
        or "unnamed"
    if extension and name.lower().endswith(extension.lower()):
        name = name[:-len(extension)]
    return name or "unnamed"


def header_files(headers):
    """The file names inside the stated ``Header`` values, in stated order."""
    files = []
    for value in headers:
        for match in HEADER_FILE.findall(value):
            name = match.split("/")[-1].split("\\")[-1]
            if name and name.lower() not in [f.lower() for f in files]:
                files.append(name)
    return files


def module_of(value):
    """(module, extension) of a stated library/DLL value, or None."""
    match = MODULE_FILE.search(value or "")
    if not match:
        return None
    return match.group("base"), match.group("ext").lower()


CODE_SKIPPED = collections.Counter()


def grouped_keys(records, fields, target):
    """Requirement keys of one entity, split by who stated them.

    ``own`` is a page of the version being built.  ``ce`` is another Windows
    CE set.  ``win32`` is the desktop reference.  The first set that stated a
    key is kept, so a borrow can be named.  A key is the file name the
    requirement record already derived; a value that names no file has an
    empty key and never arrives here.  A library/DLL value that names
    several files contributes each of them: the derived key keeps only the
    first, and dropping the rest would omit a library the page assigned.
    """
    groups = {"own": [], "ce": [], "win32": []}
    sets = {"own": "", "ce": "", "win32": ""}
    for record in records:
        if record.get("field") not in fields or not record.get("key"):
            continue
        book = (record.get("source") or {}).get("set") or ""
        if book == target or book.startswith(target + "/"):
            slot = "own"
        elif record.get("layer") == "win32":
            slot = "win32"
        elif record.get("layer") == "ce":
            slot = "ce"
        else:
            continue
        names = [record["key"]]
        if record.get("field") in ("library", "dll"):
            stated = page_parse.assigned_files(record.get("value") or "")
            if stated:
                names = stated
        for name in names:
            if name.lower() not in [key.lower() for key in groups[slot]]:
                groups[slot].append(name)
                if not sets[slot]:
                    sets[slot] = book
    return groups, sets


def choose_keys(groups, sets, borrow):
    """(keys, borrowed_from) -- the version's own statement, or a marked borrow.

    A desktop header (``processthreadsapi.h``, ``windows.h``) is never treated
    as a Windows CE statement: it is used only when no CE page states a file,
    and the caller marks it ``win32-reference``.
    """
    if groups["own"]:
        return groups["own"], ""
    if borrow and groups["ce"]:
        return groups["ce"], "ce-set:" + sets["ce"]
    if borrow and groups["win32"]:
        return groups["win32"], "win32-reference"
    return [], ""


def choose_declarations(entity, declarations_of, target, borrow):
    """Declarations for one entity, best evidence first.

    Windows CE is the CE-specific surface plus the Win32 that CE documents
    share -- it is **not** all of Win32 -- so the order is deliberate:

    1. a declaration printed by the target CE set (the version being built);
    2. a declaration printed by another CE set in the corpus;
    3. a declaration from the Win32 reference (the shared surface, documented
       as desktop Windows: a fallback, and it is *marked*, never passed off as
       a CE statement).

    Returns (chosen, alternatives, borrowed_from) where ``borrowed_from`` is
    ``""``, ``"ce-set:<set>"`` or ``"win32-reference"``.  A win32 fallback is
    only used when the CE pages print no declaration for the entity at all.
    """
    records = [declarations_of[did] for did in entity["syntax_declarations"]
               if did in declarations_of]
    # Belt and braces: a record the extractor marked as implementation code is
    # never emitted, even if some older knowledge base still lists it (it may
    # still be *read* as evidence by a human -- it is simply not inlined here).
    sample_code = [r for r in records if r.get("implementation")]
    if sample_code:
        for record in sample_code:
            CODE_SKIPPED["declaration text is implementation code"] += 1
    def in_target(record):
        book = record["source"]["set"]
        return book == target or book.startswith(target + "/")

    def spaced_first(rows):
        return sorted(rows, key=lambda r: (
            r.get("spacing") != "preserved", r["source"]["path"]))

    def collapsed(record):
        return re.sub(r"\s+", "", record.get("text") or "")

    own = [r for r in records if in_target(r)]
    other_ce = [r for r in records
                if r not in own and r.get("layer") == "ce"]
    win32 = [r for r in records
             if r not in own and r not in other_ce and r.get("layer") == "win32"]
    rest = [r for r in records if r not in own and r not in other_ce
            and r not in win32]
    other = other_ce + win32 + rest
    # The version's own text wins.  Another CE page is used only when this
    # page lost the spaces and that page kept them, and the two texts are the
    # same once whitespace is removed.  A copy that also prints a calling
    # convention, a different type or a different parameter name is a different
    # quotation, not a spacing repair, so the collapsed text stays.
    if own:
        own = spaced_first(own)
        if own[0].get("spacing") == "preserved" or not borrow:
            return own, other, ""
        flat = collapsed(own[0])
        match = [r for r in other_ce
                 if r.get("spacing") == "preserved" and collapsed(r) == flat]
        if match:
            match = spaced_first(match)
            rest_ce = [r for r in other_ce if r is not match[0]]
            return [match[0]], own + rest_ce + win32 + rest, \
                "ce-set:" + match[0]["source"]["set"] + "|spacing"
        return own, other, ""
    if borrow and other_ce:
        other_ce = spaced_first(other_ce)
        return other_ce[:1], other_ce[1:] + win32 + rest, \
            "ce-set:" + other_ce[0]["source"]["set"]
    if borrow and win32:
        return win32[:1], win32[1:] + rest, "win32-reference"
    return [], other, ""


def write_includes(out, by_header, generated):
    include_dir = os.path.join(out, "include")
    os.makedirs(include_dir, exist_ok=True)
    for header, entries in sorted(by_header.items(), key=lambda kv: kv[0].lower()):
        path = os.path.join(include_dir, safe_name(header, ".h") +
                            ".h.fragment")
        lines = [
            f"/* {header} -- declarations documented for {generated['set']}",
            " *",
            " * Generated by tools/gen-include-def.py from wince-docs-corpus.",
            " * Every block below is quoted verbatim from the page named above",
            " * it; nothing here is written, completed or reformatted by the",
            " * generator.  This file is a *fragment*: include guards, include",
            " * order and the parts of the header the documentation does not",
            " * describe are the job of the generator built on top.",
            f" * {len(entries)} declaration(s).",
            " */",
        ]
        for entry in entries:
            entity, declaration = entry[0], entry[1]
            header_from = entry[2] if len(entry) > 2 else ""
            stated_libs = entry[3] if len(entry) > 3 else (
                entity["libraries"] or entity["dlls"])
            libs = ", ".join(stated_libs) or "-"
            lines += [
                "",
                "/*" + "-" * 68,
                f" * {entity['name']}  [{', '.join(entity['kinds']) or '?'}]",
                f" * library: {libs}",
                f" * source: {declaration['source']['path']}",
            ]
            for item in (item for item in entity.get("unicode_only") or []
                         if item.get("scope") == "this-api"):
                # quoted, because this is the sentence that forbids an A form
                lines.append(f" * {item['text']}  [{item['page']}]")
            if header_from.startswith("win32"):
                lines.append(
                    " * header borrowed from: the Win32 reference -- NOT a "
                    "header a Windows CE page states for this name")
            elif header_from.startswith("ce-set:"):
                lines.append(
                    f" * header borrowed from: {header_from[len('ce-set:'):]} "
                    "(this version's pages state no header file)")
            decl_from = entry[4] if len(entry) > 4 else ""
            if not declaration["source"]["set"].startswith(generated["set"]):
                if declaration.get("layer") == "win32":
                    lines.append(
                        " * borrowed from: the Win32 reference -- NOT from a "
                        "Windows CE page")
                    lines.append(
                        " *   (this name is on the shared surface; the CE "
                        "documents print no declaration for it, and the Win32 "
                        "page documents desktop Windows -- verify against the "
                        "CE SDK)")
                else:
                    lines.append(
                        f" * borrowed from: {declaration['source']['set']} "
                        "(another CE set declares it)")
                    if decl_from.endswith("|spacing"):
                        lines.append(
                            " *   (this version's page lost the spaces between "
                            "tokens; the declaration below is the other page's "
                            "text, quoted as printed, and it is the same text "
                            "once whitespace is removed)")
            if declaration["spacing"] != "preserved":
                lines.append(" * NOTE: the page lost the spaces in this "
                             "declaration (spacing: collapsed) -- prefer "
                             "another page's copy")
            lines.append(" */")
            lines.append(declaration["text"])
        with open(path, "w", encoding="utf-8") as fh:
            fh.write("\n".join(lines) + "\n")
    return include_dir


def load_base_types():
    """Load base type definitions from kb/base-types.tsv.
    
    Returns a dict mapping header name (lowercase) to list of type definitions.
    Each type definition is a dict with keys: type, definition, header,
    ce_specific, ce_note, ce_value_note, source.
    """
    by_header = collections.defaultdict(list)
    if not os.path.exists(BASE_TYPES):
        return by_header
    with open(BASE_TYPES, encoding="utf-8") as fh:
        header = fh.readline().rstrip("\n").split("\t")
        for line in fh:
            cells = line.rstrip("\n").split("\t")
            if len(cells) < len(header):
                continue
            row = dict(zip(header, cells))
            by_header[row["header"].lower()].append(row)
    return by_header


def load_extra_defines():
    """Load extra #define macros from kb/extra-defines.tsv.
    
    These are macros found by scanning CE corpus pages that the main
    parser may have missed. Returns a list of define dicts.
    """
    defines = []
    if not os.path.exists(EXTRA_DEFINES):
        return defines
    with open(EXTRA_DEFINES, encoding="utf-8") as fh:
        header = fh.readline().rstrip("\n").split("\t")
        for line in fh:
            cells = line.rstrip("\n").split("\t")
            if len(cells) < len(header):
                continue
            row = dict(zip(header, cells))
            # Clean HTML entities from definition
            defn = row.get("definition", "")
            defn = defn.replace("&gt;", ">").replace("&lt;", "<")
            defn = defn.replace("&amp;", "&").replace("&quot;", '"')
            row["definition"] = defn
            defines.append(row)
    return defines


def load_assigned_defines():
    """Load defines assigned to specific headers from kb/defines-by-header/.
    
    Returns a dict mapping header name (lowercase) to list of define dicts.
    """
    assigned = collections.defaultdict(list)
    defines_dir = os.path.join(KB, "defines-by-header")
    if not os.path.exists(defines_dir):
        return assigned
    
    for filename in os.listdir(defines_dir):
        if filename.endswith('.defines.json') and not filename.startswith('_'):
            header = filename.replace('.defines.json', '')
            filepath = os.path.join(defines_dir, filename)
            with open(filepath, encoding="utf-8") as fh:
                defines = json.load(fh)
                assigned[header.lower()] = defines
    
    return assigned


def load_unassigned_defines():
    """Load defines that could not be assigned to any specific header.
    
    Returns a list of define dicts from kb/defines-by-header/_unassigned.defines.json.
    Filters out entries with missing definitions.
    """
    unassigned_path = os.path.join(KB, "defines-by-header", "_unassigned.defines.json")
    if not os.path.exists(unassigned_path):
        return []
    
    with open(unassigned_path, encoding="utf-8") as fh:
        defines = json.load(fh)
        # Filter out entries with missing definitions
        return [d for d in defines if d.get("definition")]


def load_unassigned_declarations():
    """Load declarations that could not be assigned to any specific header.
    
    Returns a list of declaration dicts from kb/declarations-by-header/_unassigned.declarations.json.
    """
    unassigned_path = os.path.join(KB, "declarations-by-header", "_unassigned.declarations.json")
    if not os.path.exists(unassigned_path):
        return []
    
    with open(unassigned_path, encoding="utf-8") as fh:
        return json.load(fh)


def load_assigned_declarations():
    """Load declarations from KB and group by header.
    
    Uses the main KB declarations (declarations.jsonl.gz) and groups them
    by header based on entity header assignments.
    """
    # Load declarations
    declarations = [json.loads(line) for line in gzip.open(DECLARATIONS, 'rt')]
    
    # Load entities to get header assignments
    entities = [json.loads(line) for line in gzip.open(ENTITIES, 'rt')]
    entity_by_id = {e['id']: e for e in entities}
    
    # Group declarations by header
    decls_by_header = collections.defaultdict(list)
    for decl in declarations:
        entity_id = decl.get('entity')
        if not entity_id:
            continue
        
        entity = entity_by_id.get(entity_id)
        if not entity or not entity.get('headers'):
            continue
        
        # Add to all headers for this entity
        for header in entity['headers']:
            header_lower = header.lower()
            decls_by_header[header_lower].append({
                'type': decl.get('kind', 'function'),
                'name': decl.get('name', entity.get('name', '')),
                'declaration': decl.get('text', ''),
                'source': decl.get('source', {}).get('path', ''),
            })
    
    # Deduplicate by name and type
    for header in decls_by_header:
        seen = set()
        unique = []
        for d in decls_by_header[header]:
            key = (d['type'], d['name'])
            if key not in seen:
                seen.add(key)
                unique.append(d)
        decls_by_header[header] = unique
    
    return decls_by_header


def load_ordinal_rows():
    """The rows of ``kb/export-ordinals.tsv`` as dicts, in file order."""
    path = os.path.join(KB, "export-ordinals.tsv")
    if not os.path.exists(path):
        return []
    with open(path, encoding="utf-8") as fh:
        header = fh.readline().rstrip("\n").split("\t")
        return [dict(zip(header, line.rstrip("\n").split("\t")))
                for line in fh if line.strip()]


def write_ordinal_defs(out, target):
    """One ``.def`` per DLL whose export table a page of this set prints.

    These names reach the file from the printed ``Export | Ordinal`` table,
    not from a Requirements block, so they would otherwise never appear: no
    API page in the corpus states ``Fpcrt.dll``.  The table is the document's
    own export list, which is exactly what a module-definition file is, so it
    is written as one -- with the page on every line and no name added to it.
    """
    rows = [row for row in load_ordinal_rows()
            if in_set(row.get("set") or "", target)]
    if not rows:
        return 0, 0
    link_dir = os.path.join(out, "link")
    os.makedirs(link_dir, exist_ok=True)
    by_dll = collections.defaultdict(list)
    for row in rows:
        by_dll[row["dll"]].append(row)
    for dll, items in sorted(by_dll.items()):
        stem = safe_name(re.sub(r"(?i)\.(dll|lib|exe)$", "", dll))
        path = os.path.join(link_dir, stem + ".ordinals.def")
        pages = sorted({row["page"] for row in items})
        lines = [
            f"; {dll} -- EXPORTS read from the export table the documentation",
            "; prints for this DLL (name and ordinal both as printed).",
            ";",
            "; Generated by tools/gen-include-def.py from wince-docs-corpus.",
            "; Unlike the other .def files here this one is not a worklist",
            "; built from Requirements blocks: the page below lists the",
            "; exports of the library itself.  No name, ordinal or alias is",
            "; added to the list, and the documentation states that the",
            "; ordinal is the part that must match.",
            ";",
        ]
        lines += [f"; source: {page}" for page in pages]
        lines += [f"; {len(items)} name(s)", "EXPORTS"]
        for row in sorted(items, key=lambda r: int(r["ordinal"])):
            lines.append(f"    {row['name'] + ' @' + row['ordinal']:32s}"
                         f"; printed in table {row['table']}")
        with open(path, "w", encoding="utf-8") as fh:
            fh.write("\n".join(lines) + "\n")
    return len(by_dll), len(rows)


def load_ordinals():
    """``kb/export-ordinals.tsv`` -> {(dll stem, name lower): (ordinal, page)}.

    The only ordinals in the corpus.  Keyed by the DLL the page names, so a
    name is given an ordinal only in the module the document printed it for.
    """
    path = os.path.join(KB, "export-ordinals.tsv")
    out = {}
    if not os.path.exists(path):
        return out
    with open(path, encoding="utf-8") as fh:
        header = fh.readline().rstrip("\n").split("\t")
        for line in fh:
            cells = line.rstrip("\n").split("\t")
            row = dict(zip(header, cells))
            dll = (row.get("dll") or "").lower()
            stem = dll[:-4] if dll.endswith(".dll") else dll
            out[(stem, (row.get("name") or "").lower())] = (
                row.get("ordinal") or "", row.get("page") or "")
    return out


def load_reference_exports():
    """module -> [(name, def_member)] from kb/reference-exports.tsv: the
    export-list MEMBERSHIP of the pinned CeGCC reference's .def files.
    Names only -- ordinals were never taken.  Marked leads for the .def
    worklists, not documentation: every line printed from this file
    carries the reference mark."""
    path = os.path.join(ROOT, "knowledge", "kb", "reference-exports.tsv")
    out = {}
    if not os.path.exists(path):
        return out
    with open(path, encoding="utf-8") as fh:
        reader = csv.DictReader(fh, delimiter="\t")
        for row in reader:
            out.setdefault(row["module"].lower(), []).append(
                (row["name"], row["def_member"]))
    return out


def write_defs(out, by_module, generated, ordinals=None,
               reference_exports=None):
    link_dir = os.path.join(out, "link")
    os.makedirs(link_dir, exist_ok=True)
    for module, worklist in sorted(by_module.items()):
        entries = worklist["entries"]
        path = os.path.join(link_dir, safe_name(module) + ".def")
        lines = [
            f"; {module} -- EXPORTS worklist for {generated['set']}",
            ";",
            "; Generated by tools/gen-include-def.py from wince-docs-corpus:",
            "; one line per function or callback whose page states this",
            "; module, with the page behind every name.  The name is the",
            "; documented name -- NOT the decorated symbol: the documentation",
            "; does not state the _Name@N spelling or the export table of the",
            "; real library, so verify each line against the SDK before",
            "; linking.  An @ordinal appears only where a page prints one.",
            ";",
            f"; stated as: {', '.join(worklist['stated'])}",
            f"; {len(entries)} name(s)",
            "EXPORTS",
        ]
        module_stem = safe_name(module).lower()
        known = {entry[0]["name"].lower() for entry in entries}
        leads = [(name, member) for name, member in
                 (reference_exports or {}).get(module_stem, [])
                 if name.lower() not in known]
        if leads:
            if not args.minimal_comments:
                lines += [
                    ";",
                    f"; reference-export leads ({len(leads)}): names the pinned",
                    "; CeGCC reference's .def export list claims for this module",
                    "; but no CE page documents.  MEMBERSHIP ONLY -- the name is",
                    "; claimed by the given list; ordinals and decoration were",
                    "; never taken (values: never).  Each name is a REVIEW LEAD:",
                    "; verify it against the CE SDK export table before linking,",
                    "; and confirm any A-sounding spelling page by page (CE is",
                    "; W-side basically).",
                    ";",
                ]
            for name, member in leads:
                if not args.minimal_comments:
                    lines.append(f";   {name:38s}; lead  {member}")
        for entry in entries:
            entity, declaration = entry[0], entry[1]
            library_from = entry[2] if len(entry) > 2 else ""
            page = declaration["source"]["path"] if declaration else "-"
            kind = (entity["kinds"] or ["?"])[0]
            if declaration and declaration.get("layer") == "win32":
                page += "  [Win32 ref: verify against the CE SDK]"
            if library_from.startswith("win32"):
                page += "  [library: Win32 ref, not a CE page]"
            elif library_from.startswith("ce-set:"):
                page += "  [library borrowed from " + library_from[len("ce-set:"):] + "]"
            ordinal, ordinal_page = (ordinals or {}).get(
                (module_stem, entity["name"].lower()), ("", ""))
            if ordinal:
                # printed by the document, never derived from a position
                name_field = f"{entity['name']} @{ordinal}"
                page += f"  [ordinal printed by {ordinal_page}]"
            else:
                name_field = entity["name"]
            lines.append(f"    {name_field:32s}; {kind}  {page}")
        if leads:
            lines.append(";")
            lines.append(f"; {len(entries)} documented name(s) above; "
                         f"{len(leads)} reference-export lead(s) in "
                         f"comment")
        with open(path, "w", encoding="utf-8") as fh:
            fh.write("\n".join(lines) + "\n")
    return link_dir


def in_set(book, target):
    return book == target or book.startswith(target + "/")


def load_unsupported():
    """``kb/unsupported-constants.tsv`` -> {name: [row, ...]}.

    A constant a CE page lists as not supported is still *documented* -- the
    number is on another page -- so it is written with the sentence that
    takes it away rather than silently dropped.  Which CE version said it
    matters, so the set is kept: a statement by the version being built
    comments the ``#define`` out, a statement by another CE version is
    printed as a note above a line that stays.
    """
    path = os.path.join(KB, "unsupported-constants.tsv")
    out = collections.defaultdict(list)
    if not os.path.exists(path):
        return out
    with open(path, encoding="utf-8") as fh:
        header = fh.readline().rstrip("\n").split("\t")
        for line in fh:
            row = dict(zip(header, line.rstrip("\n").split("\t")))
            if row.get("status") != "not-supported":
                continue
            out[row["name"]].append(row)
    return out


def write_constants(out, constants, target, borrow):
    """The numbers a page prints, grouped by the header that same page names.

    A ``#define`` line is *derived*: the page printed a table row, not a
    ``#define``.  The row is quoted above the line, and a row whose pages
    disagree on the number is listed and not turned into a ``#define``.  A
    constant whose page names no header stays in ``constants.tsv`` only -- it
    is not assigned a file.  A number stated only by the Win32 reference is
    not borrowed: desktop and Windows CE values are not assumed to match.
    """
    own = [c for c in constants
           if c.get("layer") == "ce" and in_set(c["source"]["set"], target)]
    own_names = {c["name"] for c in own}
    borrowed = []
    if borrow:
        for record in constants:
            if record.get("layer") != "ce":
                continue
            if in_set(record["source"]["set"], target):
                continue
            if record["name"] in own_names:
                continue
            borrowed.append(record)
    selected = [(c, "") for c in own] + [
        (c, "ce-set:" + c["source"]["set"]) for c in borrowed]

    by_key = collections.defaultdict(list)
    no_header = []
    for record, origin in selected:
        headers = record.get("headers") or []
        if not headers:
            no_header.append((record, origin))
            continue
        for header in headers:
            by_key[(header, record["name"])].append((record, origin))

    conflicts = 0
    written = 0
    unsupported_written = 0
    include_dir = os.path.join(out, "include")
    os.makedirs(include_dir, exist_ok=True)
    by_header = collections.defaultdict(list)
    for (header, name), rows in by_key.items():
        values = {row["value"] for row, _origin in rows}
        if len(values) > 1:
            conflicts += 1
        by_header[header].append((name, rows, len(values) > 1))
    for header, items in by_header.items():
        path = os.path.join(include_dir, safe_name(header, ".h") +
                            ".h.constants")
        lines = [
            f"/* {header} -- numbers documented for {target}",
            " *",
            " * Each block quotes a table row a page prints (name and value in",
            " * separate columns).  The #define line below a block is derived",
            " * from that row: the page did not print a #define, so the keyword",
            " * is marked as derived and a row whose pages disagree on the",
            " * number is not turned into one.",
            " */",
        ]
        for name, rows, conflict in sorted(items, key=lambda item: item[0].lower()):
            lines.append("")
            lines.append(f"/* {name}")
            for record, origin in rows:
                borrowed_note = f"  borrowed from {origin[len('ce-set:'):]}" \
                    if origin.startswith("ce-set:") else ""
                # Clean HTML from quoted rows for readability
                cleaned_row = html_clean.format_evidence_row(record['row'], max_length=100)
                lines.append(f" * row: {cleaned_row}")
                lines.append(f" * source: {record['source']['path']}"
                             f"{borrowed_note}")
            if conflict:
                lines.append(" * CONFLICT: the pages do not agree on the "
                             "number -- no #define is written")
                lines.append(" */")
                continue
            taken_away = UNSUPPORTED.get(name) or []
            here = [row for row in taken_away if in_set(row["set"], target)]
            elsewhere = [row for row in taken_away if row not in here]
            for row in here:
                lines.append(f" * NOT SUPPORTED: {row['statement']}")
                lines.append(f" * source: {row['page']}")
            for row in elsewhere:
                lines.append(f" * not supported in {row['set']}: "
                             f"{row['statement']}")
                lines.append(f" * source: {row['page']}")
            if here:
                # this version's own page takes the value away: both facts
                # are printed and the #define is commented out rather than
                # quietly emitted
                lines.append(" */")
                record = rows[0][0]
                lines.append(f"/* #define {record['name']} "
                             f"{record['value']} */")
                unsupported_written += 1
                continue
            lines.append(" * derived: the #define keyword is not on the page")
            lines.append(" */")
            record = rows[0][0]
            lines.append(f"#define {record['name']} {record['value']}")
            written += 1
        with open(path, "w", encoding="utf-8") as fh:
            fh.write("\n".join(lines) + "\n")

    # Constants whose pages state NO header are still documented numbers
    # ("定数は全て使った状態に"): they go to one honest catch-all file
    # whose name invents no header.  The comment says exactly that -- the
    # value is documented, its home header is not; check the CE SDK.
    if no_header:
        by_name = collections.defaultdict(list)
        for record, origin in no_header:
            by_name[record["name"]].append((record, origin))
        path = os.path.join(include_dir, "NoStatedHeader.h.constants")
        lines = [
            "/* NoStatedHeader -- numbers a page prints without naming a header",
            " *",
            " * Each block quotes a table row a page prints.  No collected page",
            " * states the header these names live in, so no header file is",
            " * invented for them: the value is documented, its home header is",
            " * not.  Check the CE SDK for the real header before use.  The",
            " * #define line below a block is derived from the row (the page",
            " * did not print a #define); rows whose pages disagree are listed",
            " * and not turned into one.",
            " */",
        ]
        nohdr_written = 0
        for name, rows in sorted(by_name.items(),
                                 key=lambda item: item[0].lower()):
            values = {row["value"] for row, _origin in rows}
            lines.append("")
            lines.append(f"/* {name}")
            for record, origin in rows:
                borrowed_note = f"  borrowed from {origin[len('ce-set:'):]} \
" if origin.startswith("ce-set:") else ""
                lines.append(f" * row: {record['row']}")
                lines.append(f" * source: {record['source']['path']}"
                             f"{borrowed_note}")
            if len(values) > 1:
                lines.append(" * CONFLICT: the pages do not agree on the "
                             "number -- no #define is written")
                lines.append(" */")
                continue
            lines.append(" * derived: the #define keyword is not on the page")
            lines.append(" */")
            record = rows[0][0]
            lines.append(f"#define {record['name']} {record['value']}")
            nohdr_written += 1
        with open(path, "w", encoding="utf-8") as fh:
            fh.write("\n".join(lines) + "\n")
        written += nohdr_written

    with open(os.path.join(out, "constants.tsv"), "w", encoding="utf-8") as fh:
        fh.write("name\tvalue\tdecimal\theaders\tborrowed_from\tpage\trow\t"
                 "conflict\n")
        seen_conflict = set()
        for (header, name), rows in by_key.items():
            values = {row["value"] for row, _origin in rows}
            conflict = "yes" if len(values) > 1 else ""
            if conflict:
                seen_conflict.add(name)
            for record, origin in rows:
                fh.write("\t".join((
                    record["name"], record["value"], record["decimal"] or "",
                    header, origin, record["source"]["path"], record["row"],
                    conflict)) + "\n")
        for record, origin in no_header:
            fh.write("\t".join((
                record["name"], record["value"], record["decimal"] or "",
                "", origin, record["source"]["path"], record["row"],
                "")) + "\n")
    return {
        "unsupported": unsupported_written,
        "rows": len(selected),
        "defines": written,
        "conflicts": conflicts,
        "no_header": len(no_header),
        "headers": len(by_header),
    }


def split_libraries(entity):
    """(libraries, dlls, modules, unstated) for one entity.

    ``modules`` maps the lower-case module name to the spellings the pages
    state (``coredll.lib`` and ``coredll.dll`` are one module).  ``unstated``
    counts values that name no file -- they are not a library, so they never
    become a worklist file.
    """
    modules = {}
    unstated = 0
    for value in entity["libraries"]:
        parsed = module_of(value)
        if parsed:
            modules.setdefault(parsed[0].lower(), set()).add(value)
        else:
            unstated += 1
    for value in entity["dlls"]:
        parsed = module_of(value)
        if parsed:
            modules.setdefault(parsed[0].lower(), set()).add(value)
        else:
            unstated += 1
    return modules, unstated


# ------------------------------------------------------------------ #
# Unified tree: one include/def surface for every Windows CE version  #
#                                                                     #
# The generation-specific build above answers "what does CE 5.0       #
# document?"  The unified build answers a different question: "what   #
# is the include/def surface of Windows CE as a whole?" -- one tree   #
# where differences between CE generations are carried by             #
# ``#if defined(_WIN32_WCE) && ...`` branches, not by duplicating the #
# tree.  ``_WIN32_WCE`` is the version macro the documentation itself #
# prints (the VCCE SDK pages define it; the CE .NET pages write       #
# ``#if (_WIN32_WCE < 300)``).  The mapping from a corpus set to its  #
# version interval is generator wiring, printed here and in every     #
# report -- it is derived structure, not a page quotation, exactly    #
# like the ``#define`` keyword above a quoted table row.              #
# ------------------------------------------------------------------ #

# corpus set (book prefix) -> [lo, hi) interval of _WIN32_WCE values the
# set's documentation covers.  Stored as decimal 100, 200, 300, 500;
# emitted as the SDK hex the headers actually test (CE 5.0 -> 0x500).
# CE 1.0 -> 0x100, CE 2.11 -> 0x211, CE 3.0 -> 0x300, CE 4.x -> 0x400,
# CE 5.0 -> 0x500, Embedded CE 6.0 -> 0x600, Compact 7 -> 0x700.
SET_WCE_INTERVAL = (
    ("mvb/windows-ce-1.0/", 100, 200),
    ("msdn-library/techshelps/CEGUIDE/", 100, 200),
    ("mvb/windows-ce-2.0-sdk/", 200, 210),
    ("msdn-library/techshelps/", 200, 210),      # the CE 2.0-era sets
    ("msdn-library/wcedevcon-99/", 211, 213),    # CE 2.11/2.12 SDK
    ("msdn-library/datadungeon-2000-04/", 212, 400),  # the 2.12/3.0 library
    ("chm/windows-ce-3.0/", 300, 400),
    ("chm/windows-ce-4.2/", 420, 500),
    ("learn/windows-ce-net-4x/", 400, 500),
    ("learn/windows-ce-5.0/", 500, 600),
    ("chm/windows-ce-5.0/", 500, 600),
    ("msdn-library/2010-05/windows-ce-5.0/", 500, 600),
    ("learn/windows-embedded-ce-6.0/", 600, 700),
    ("learn/windows-embedded-compact-7/", 700, 800),
    ("booklet/", None, None),
)
WCE_FIRST, WCE_LAST = 100, 800

# CE-layer sets that carry no version statement an include file could
# branch on: the KB article tree (each article names its own versions in
# prose, not reliably), the developer web sites, the harvested pages the
# harvester could not classify, and the Windows Mobile add-on library (a
# layer on top of the OS, not an OS version).
WCE_NEUTRAL_PREFIXES = ("kb/", "site/", "learn/unclassified",
                        "msdn-library/windows-mobile-6.5")


def wce_interval(book):
    """[lo, hi) interval of a corpus set, or None when the set is neutral."""
    if not book:
        return None
    for prefix in WCE_NEUTRAL_PREFIXES:
        if book == prefix or book.startswith(prefix.rstrip("/") + "/"):
            return None
    best = None
    for prefix, lo, hi in SET_WCE_INTERVAL:
        if lo is None:
            continue
        if book == prefix.rstrip("/") or book.startswith(prefix):
            if best is None or len(prefix) > len(best[0]):
                best = (prefix, lo, hi)
    return (best[1], best[2]) if best else None


def merge_intervals(intervals):
    """Union of [lo, hi) intervals, sorted; adjacent ranges merge."""
    merged = []
    for lo, hi in sorted(i for i in intervals if i):
        if merged and lo <= merged[-1][1]:
            merged[-1][1] = max(merged[-1][1], hi)
        else:
            merged.append([lo, hi])
    return merged


def wce_guard(sets):
    """``#if`` condition for the versions the sets cover, or None.

    ``sets`` are the CE sets that document the item.  A version-neutral
    set neither proves nor denies a generation, so it does not widen the
    condition; it is named by the caller in a comment instead.  Coverage
    of every generation the corpus documents produces no guard at all.
    """
    merged = merge_intervals([wce_interval(s) for s in sets])
    if not merged:
        return None, []
    everywhere = merged[0][0] <= WCE_FIRST and merged[-1][1] >= WCE_LAST
    conds = []
    for lo, hi in merged:
        lo_s, hi_s = f"0x{lo}", f"0x{hi}"
        if hi >= WCE_LAST:
            conds.append(f"_WIN32_WCE >= {lo_s}")
        elif lo <= WCE_FIRST:
            conds.append(f"_WIN32_WCE < {hi_s}")
        else:
            conds.append(f"_WIN32_WCE >= {lo_s} && _WIN32_WCE < {hi_s}")
    return None if everywhere else "defined(_WIN32_WCE) && (" + \
        " || ".join(f"({c})" for c in conds) + ")", merged


# A _WIN32_WCE boundary value -> the generation a reader calls it.
WCE_VERSION_NAMES = {100: "1.0", 200: "2.0", 210: "2.10", 211: "2.11",
                     212: "2.12", 300: "3.0", 400: "4.0", 410: "4.1",
                     420: "4.2", 500: "5.0", 600: "6.0",
                     700: "Compact 7"}


def wce_range_comment(merged):
    """Human-readable version list of merged intervals (for comments)."""
    parts = []
    for lo, hi in merged:
        lo_name = WCE_VERSION_NAMES.get(lo, str(lo))
        if hi >= WCE_LAST:
            parts.append(f">= {lo_name}")
            continue
        hi_name = WCE_VERSION_NAMES.get(hi - 1, str(hi - 1))
        parts.append(lo_name if lo_name == hi_name else
                     f"{lo_name}..{hi_name}")
    return ", ".join(parts)


def load_ce_documented_names():
    """The names that are part of the CE surface: one a CE page lists
    (``kb/constant-names.tsv``, pages outside ``corpus/win32/``) or one
    the CE-adapted reference headers define (``kb/reference-names.tsv``,
    membership only -- w32api-cegcc is the CE toolchain's own winuser.h
    & co., so a name it defines is Win32-shared CE surface).  This set is
    the gate for using a Win32-shared *value* in the same tree.  A name
    the shared reference alone documents is desktop surface -- Windows CE
    is not all of Win32.
    """
    names = set()
    path = os.path.join(KB, "constant-names.tsv")
    if os.path.exists(path):
        with open(path, encoding="utf-8") as fh:
            header = fh.readline().rstrip("\n").split("\t")
            try:
                name_i = header.index("name")
                page_i = header.index("page")
            except ValueError:
                name_i = page_i = None
            if name_i is not None:
                for line in fh:
                    cells = line.rstrip("\n").split("\t")
                    if len(cells) > page_i and \
                            not cells[page_i].startswith("corpus/win32/"):
                        names.add(cells[name_i])
    ref = os.path.join(KB, "reference-names.tsv")
    if os.path.exists(ref):
        with open(ref, encoding="utf-8") as fh:
            fh.readline()
            for line in fh:
                cells = line.rstrip("\n").split("\t")
                if cells and cells[0]:
                    names.add(cells[0])
    harvest = os.path.join(KB, "harvest-declarations.jsonl")
    if os.path.exists(harvest):
        import json as _json
        with open(harvest, encoding="utf-8") as fh:
            for line in fh:
                line = line.strip()
                if not line:
                    continue
                rec = _json.loads(line)
                text = rec.get("declaration") or rec.get("text") or ""
                for bound in re.findall(r"\[([A-Z][A-Z0-9_]{1,40})\]", text):
                    names.add(bound)
    return names


_LINK_RANK = {
    "own-page": 0,
    "entity-page": 1,
    "constant-entity": 2,
    "reference-header": 3,
    "heuristic-prefix": 4,
    "win32-reference": 5,
    "co-mention": 6,
    "pinvoke-weak": 7,
}


def pick_constant_targets(name, targets):
    """One primary header for a numbered constant.

    CE documentation ranks first.  A weak win32-reference that disagrees
    with the shared name map is not used (ERROR_FILE_NOT_FOUND must not
    follow a crypto page into wincrypt.h).  A reference-header (raserror.h
    for RAS ERROR_*) outranks the name map.  Among equal ranks prefer the
    public ``.h`` over an internal ``.hpp`` / ``.idl``.
    """
    mapped = header_map.header_for_constant(name)
    if not targets:
        if mapped:
            return [{"header": mapped, "strength": "heuristic-prefix",
                     "statements": 0, "example_page": "-"}]
        return []
    if mapped:
        for t in targets:
            if (t.get("header") or "").lower() == mapped.lower():
                return [t]
    by_rank = collections.defaultdict(list)
    for t in targets:
        rank = _LINK_RANK.get(t.get("strength") or "", 99)
        by_rank[rank].append(t)
    best = min(by_rank)
    if mapped and best >= _LINK_RANK["win32-reference"]:
        return [{"header": mapped, "strength": "heuristic-prefix",
                 "statements": 0, "example_page": "-"}]
    cands = by_rank[best]

    def sort_key(t):
        h = t.get("header") or ""
        hl = h.lower()
        return (
            0 if mapped and hl == mapped.lower() else 1,
            1 if hl.endswith(".hpp") else 0,
            1 if hl.endswith(".idl") else 0,
            -int(t.get("statements") or 0 or 0),
            hl,
        )
    return [sorted(cands, key=sort_key)[0]]


def load_unified_constants():
    """``knowledge/unified/constants.jsonl`` -> {name: rec}."""
    out = {}
    if not os.path.exists(UNIFIED_CONSTANTS):
        return out
    check_spec_path(UNIFIED_CONSTANTS)
    with open(UNIFIED_CONSTANTS, encoding="utf-8") as fh:
        for line in fh:
            line = line.strip()
            if not line:
                continue
            rec = json.loads(line)
            name = rec.get("name")
            if name:
                out[name] = rec
    return out


def apply_unified_constants(const_rows, unified):
    """Keep only the CE-preferred value the unified KB chose.

    Correspondence-table numbers (charset → code page) and a Win32 value
    that a CE page contradicts are dropped.  A name only the extra
    extractors numbered is injected.
    """
    if not unified:
        return 0
    applied = 0
    for name, rec in unified.items():
        value = rec.get("value")
        if not value:
            continue
        source = rec.get("source") if isinstance(rec.get("source"), dict) else {}
        source = dict(source)
        source.setdefault("path", source.get("path") or "knowledge/unified/constants.jsonl")
        # One value for the whole CE surface -- do not version-gate
        # TRUE/MAX_PATH behind the single generation that printed it.
        source["set"] = "unified"
        source.setdefault("layer", rec.get("layer") or "ce")
        source.setdefault("title", name)
        source.setdefault("page_id", source.get("page_id") or "")
        synthetic = {
            "id": "unified:" + name,
            "name": name,
            "value": value,
            "decimal": rec.get("decimal"),
            "origin": rec.get("origin") or "unified",
            "headers": [rec["header"]] if rec.get("header") else [],
            "layer": rec.get("layer") or "ce",
            "row": f"{name} {value}",
            "license": rec.get("license") or "?",
            "source": source,
        }
        # One unguarded #define: version-sliced CE table hits were putting
        # TRUE/MAX_PATH behind a single-generation #if.
        const_rows[name] = {"unified": synthetic}
        applied += 1
    return applied


def load_constant_links():
    """``kb/constant-headers.tsv`` -> {name: [{header, strength, sets}]}.

    The linkage table the knowledge base derives (best rank per name);
    the generator consumes it to file derived ``#define`` lines under a
    header, always with the rank printed beside it.
    """
    out = collections.defaultdict(list)
    if not os.path.exists(CONSTANT_HEADERS):
        return out
    with open(CONSTANT_HEADERS, encoding="utf-8") as fh:
        header = fh.readline().rstrip("\n").split("\t")
        for line in fh:
            cells = line.rstrip("\n").split("\t")
            if len(cells) < len(header):
                continue
            row = dict(zip(header, cells))
            out[row["name"]].append({
                "header": row["header"], "strength": row.get("strength"),
                "statements": row.get("statements"),
                "example_page": row.get("example_page"),
                "sets": [s for s in (row.get("sets") or "").split(";") if s],
            })
    return out


def load_constant_conflicts():
    """``kb/constant-conflicts.tsv`` -> {name: row dict}.

    The examined value disagreements, with the reviewed category and --
    where the review resolved the case -- the value the pages themselves
    print and the verdict explaining why.  A conflict with no resolution
    still gets no ``#define``; a resolved one gets the reviewed print
    with the whole disagreement quoted above it.
    """
    out = {}
    if not os.path.exists(CONSTANT_CONFLICTS):
        return out
    with open(CONSTANT_CONFLICTS, encoding="utf-8") as fh:
        header = fh.readline().rstrip("\n").split("\t")
        for line in fh:
            cells = line.rstrip("\n").split("\t")
            if len(cells) < len(header):
                continue
            row = dict(zip(header, cells))
            out[row["name"]] = row
    return out


def member_outline(entity, variants):
    """The documented member list of an entity no page gives a body for.

    Members a page documents *without* printing a declaration body: the
    fragment carries them as a derived outline (marked as derived), so a
    structure whose body no page prints is no longer missing from its
    header fragment.  The A/W spelling pages of the entity contribute
    their member lists too (each member is credited to the spelling that
    documented it).
    """
    outline = []
    seen = set()
    owners = [(entity, entity.get("documented_fields") or [])]
    owners += [(v, v.get("documented_fields") or []) for v in variants]
    for owner, fields in owners:
        pages_map = owner.get("documented_field_pages") or {}
        fallback = owner.get("documented_fields_page") or ""
        for field in fields:
            if not field or field in seen:
                continue
            seen.add(field)
            outline.append({"field": field,
                            "page": pages_map.get(field) or fallback,
                            "spelling": owner.get("name") or ""})
    return outline


def load_pinvoke_aux(path):
    """The isolated weak-auxiliary pinvoke material, when harvested."""
    if not os.path.exists(path) and path.endswith(".gz"):
        path = path[:-3]
    if not os.path.exists(path):
        return []
    check_spec_path(path)
    return list(load(path))


def load_unified_declarations():
    """knowledge/unified/declarations.jsonl -- one chosen quote per name."""
    out = []
    if not os.path.exists(UNIFIED_DECLARATIONS):
        return out
    check_spec_path(UNIFIED_DECLARATIONS)
    with open(UNIFIED_DECLARATIONS, encoding="utf-8") as fh:
        for line in fh:
            line = line.strip()
            if line:
                out.append(json.loads(line))
    return out


def _keepable_c_decl(text, name, kind):
    text = (text or "").replace("\\n", "\n")
    # Derived punctuation: a syntax PRE that prints the prototype but
    # drops ';' is still that page's declaration.
    if kind in ("function", "callback") and "(" in text and not text.rstrip().endswith(";"):
        if re.search(r"\)\s*$", text.rstrip()):
            text = text.rstrip() + ";"
    if quality_filters.is_cpp_or_managed(text, name):
        return ""
    if quality_filters.is_broken_c(text):
        return ""
    if quality_filters.decl_unusable_for_c(text, name):
        return ""
    if kind in ("function", "callback") and not looks_like_c_declaration(text):
        return ""
    return text if text and text.strip() else ""


def overlay_unified_surface(by_header, printed_forms, by_module, all_entities):
    """Emit keepable unified/harvest quotes the entity loop dropped.

    No header files are copied.  Quotes already in knowledge/ only.
    """
    have = set()
    have_app = set()
    for hdr, infos in by_header.items():
        for info in infos:
            decl = info.get("declaration") or {}
            text = decl.get("text") if isinstance(decl, dict) else ""
            if text and str(text).strip() and not quality_filters.is_broken_c(text):
                n = info["entity"]["name"]
                have.add(n)
                if hdr.lower() in _APP_OVERLAY_HEADERS:
                    have_app.add(n)
    have_exp = set()
    for wl in by_module.values():
        for e in wl.get("entries") or []:
            have_exp.add(e["entity"]["name"])
    name_to_header = {}
    name_to_libs = {}
    for ent in all_entities:
        n = ent.get("name")
        if not n:
            continue
        hs = header_files(ent.get("headers") or [])
        if hs:
            name_to_header.setdefault(n, hs[0])
        libs = list(ent.get("libraries") or []) + list(ent.get("dlls") or [])
        if libs:
            name_to_libs.setdefault(n, libs)
    added = 0
    for rec in load_unified_declarations():
        name = rec.get("name") or ""
        kind = rec.get("kind") or "function"
        text = (rec.get("text") or "").replace("\\n", "\n")
        if not name:
            continue
        if name in have_app:
            continue
        if name in have and name not in _OVERLAY_NAMED:
            continue
        text = _keepable_c_decl(text, name, kind)
        if not text:
            continue
        if kind == "function" and name.isupper() \
                and not name.startswith(("READ_", "WRITE_")):
            continue
        if name.startswith(("CBase", "CAgg", "CAM")):
            continue
        hdr = rec.get("header") or name_to_header.get(name)
        if not hdr or hdr.lower() in ("windows.h",):
            mapped = header_map.header_for_entity(name, [kind])
            hdr = mapped or hdr
        if not hdr or hdr.lower() in ("windows.h",):
            continue
        hl = hdr.lower()
        if hl in DESKTOP_SPLIT_HEADERS:
            hdr = "Winbase.h"
            hl = "winbase.h"
        if kind == "macro" or text.lstrip().startswith("#"):
            continue
        if not _want_overlay(name, kind, text, hl):
            continue
        entity = {
            "id": "unified:" + name, "name": name, "kinds": [kind],
            "surface": rec.get("surface") or "ce-only",
            "ce_sets": [], "unicode_only": [],
        }
        chosen = {
            "id": "unified:" + name, "text": text,
            "source": rec.get("source") if isinstance(rec.get("source"), dict)
            else {"path": "knowledge/unified/declarations.jsonl",
                  "set": "unified", "layer": rec.get("layer") or "ce",
                  "title": name, "page_id": ""},
        }
        printed_forms.setdefault(hdr.lower(), hdr)
        by_header[hdr.lower()].append({
            "entity": entity, "declaration": chosen, "outline": [],
            "name_only": False, "borrowed_from": "unified-kb",
            "guard": None, "merged": [], "versions": set(),
            "neutral_ce": [], "header_mark": "unified-kb",
            "alternates": [], "modules": {}, "lib_mark": "",
            "variants": [],
        })
        have.add(name)
        added += 1
        if kind in EXPORTABLE and "::" not in name and "." not in name:
            libs = rec.get("libraries") or name_to_libs.get(name) or []
            for lib in libs:
                parsed = module_of(lib)
                if not parsed:
                    continue
                stem = parsed[0].lower()
                if name in have_exp:
                    continue
                by_module[stem]["stated"].add(lib)
                by_module[stem]["entries"].append({
                    "entity": entity, "declaration": chosen,
                    "lib_mark": "unified-kb", "guard": None,
                    "merged": [], "neutral_ce": [],
                    "borrowed_from": "unified-kb"})
                have_exp.add(name)
    harvest_path = os.path.join(KB, "harvest-declarations.jsonl")
    if os.path.exists(harvest_path):
        check_spec_path(harvest_path)
        with open(harvest_path, encoding="utf-8") as fh:
            for line in fh:
                line = line.strip()
                if not line:
                    continue
                rec = json.loads(line)
                name = rec.get("name") or ""
                kind = rec.get("type") or rec.get("kind") or "function"
                text = (rec.get("declaration") or rec.get("text") or "").replace("\\n", "\n")
                if not name:
                    continue
                if name in have_app:
                    continue
                if name in have and name not in _OVERLAY_NAMED:
                    continue
                text = _keepable_c_decl(text, name, kind)
                if not text:
                    continue
                if kind == "function" and name.isupper() \
                        and not name.startswith(("READ_", "WRITE_")):
                    continue
                hdr = rec.get("header") or name_to_header.get(name)
                if not hdr or hdr.lower() in ("windows.h",):
                    mapped = header_map.header_for_entity(name, [kind])
                    hdr = mapped or hdr
                if not hdr or hdr.lower() in ("windows.h",):
                    continue
                hl = hdr.lower()
                if hl in DESKTOP_SPLIT_HEADERS:
                    hdr = "Winbase.h"
                    hl = "winbase.h"
                if kind == "macro" or text.lstrip().startswith("#"):
                    continue
                if not _want_overlay(name, kind, text, hl):
                    continue
                entity = {
                    "id": "harvest:" + name, "name": name, "kinds": [kind],
                    "surface": "ce-only", "ce_sets": [], "unicode_only": [],
                }
                chosen = {
                    "id": "harvest:" + name, "text": text,
                    "source": {"path": rec.get("source") or harvest_path,
                               "set": "harvest", "layer": "ce",
                               "title": name, "page_id": rec.get("page_id") or ""},
                }
                printed_forms.setdefault(hdr.lower(), hdr)
                by_header[hdr.lower()].append({
                    "entity": entity, "declaration": chosen, "outline": [],
                    "name_only": False, "borrowed_from": "harvest-kb",
                    "guard": None, "merged": [], "versions": set(),
                    "neutral_ce": [], "header_mark": "harvest-kb",
                    "alternates": [], "modules": {}, "lib_mark": "",
                    "variants": [],
                })
                have.add(name)
                added += 1
    return added


def unified_scope(all_entities):
    """The entities of the unified tree, with A/W variants folded.

    Everything a Windows CE page documents (``ce_sets``), plus the
    Win32-spelling pages of those names, belongs to the one surface --
    not a per-generation slice, and not a separate Win32 output.  A
    name the CE documents never claim (desktop-only) stays out even
    here.  Variant spellings (``CreateSemaphoreW``) are folded into
    their base entity as documented-spelling comments: a *copy* of the
    API, never a second entry.
    """
    variants = collections.defaultdict(list)
    by_id = {e["id"]: e for e in all_entities}
    for entity in all_entities:
        base = (entity.get("variants_of") or {}).get("name")
        if base:
            variants[base.lower()].append(entity)
    scope, folded = [], collections.Counter()
    for entity in all_entities:
        if entity.get("noise"):
            continue
        if (entity.get("variants_of") or {}).get("name"):
            continue          # folded into the base entry
        if entity.get("dotnet_pages") and not entity.get("ce_sets") \
                and not entity.get("win32_pages"):
            continue          # the .NET layer is a separate tree
        if not entity.get("ce_sets") and not entity.get("win32_pages"):
            continue
        if not entity.get("ce_sets") and \
                (entity.get("surface") or "") not in (
                    "shared", "win32-spelling"):
            continue          # desktop-only: not part of Windows CE
        folded[entity["id"]] = variants.get(entity["name"].lower(), [])
        scope.append(entity)
    return scope, folded


def unified_versions(entity, declarations_of, reqs_of):
    """The CE sets that document the entity with interface material.

    A set counts when it prints a syntax declaration of the name or a
    header/library/DLL requirement for it -- the evidence a generated
    include/def entry rests on.  A page that merely mentions the name
    does not version-gate it.
    """
    sets = set()
    for did in entity.get("syntax_declarations") or []:
        record = declarations_of.get(did)
        if record and record.get("layer") == "ce" and \
                record.get("role") == "syntax":
            sets.add(record["source"]["set"])
    for record in reqs_of.get(entity["id"], ()):
        if record.get("layer") == "ce" and record.get("field") in (
                "header", "library", "dll"):
            sets.add((record.get("source") or {}).get("set") or "")
    return sets


def choose_unified_declaration(entity, declarations_of, borrow):
    """One representative declaration for the whole-of-CE tree.

    Order: a spacing-preserved CE copy (newest documented generation
    first), then a collapsed CE copy (repaired across sets by the same
    whitespace-only rule the per-version build uses), then -- marked --
    the Win32 reference.  Nothing is ever written that a page did not
    print; the choice between printed copies is recorded in
    ``borrowed_from`` exactly as before.
    """
    records = [d for d in
               (declarations_of.get(did) for did in
                entity["syntax_declarations"])
               if d and not d.get("implementation")]
    ce = [r for r in records if r.get("layer") == "ce"
          and r.get("role") == "syntax"]
    win32 = [r for r in records if r.get("layer") == "win32"
             and r.get("role") == "syntax"]

    def set_age(record):
        interval = wce_interval(record["source"]["set"])
        return -(interval[0] if interval else 0)

    spaced = sorted([r for r in ce if r.get("spacing") == "preserved"],
                    key=lambda r: (set_age(r), r["source"]["path"]))
    if spaced:
        return spaced[0], "", ce, win32
    if ce:
        chosen = sorted(ce, key=lambda r: (set_age(r), r["source"]["path"]))[0]
        if borrow:
            flat = re.sub(r"\s+", "", chosen.get("text") or "")
            match = [r for r in spaced
                     if re.sub(r"\s+", "", r.get("text") or "") == flat]
            if match:
                return match[0], "ce-set:" + \
                    match[0]["source"]["set"] + "|spacing", ce, win32
        return chosen, "", ce, win32
    if borrow and win32:
        chosen = sorted(win32, key=lambda r: r["source"]["path"])[0]
        message = "win32-reference" if chosen.get("layer") == "win32" else ""
        return chosen, message, ce, win32
    return None, "", ce, win32


def _strip_c_suffix(text):
    """A trailing C number suffix (``L``/``UL``/``f``), never hex digits.

    ``0xFFFFFFFF`` keeps its F's; ``0x0001UL`` loses ``UL``; ``1.0f``
    loses the float suffix.
    """
    text = re.sub(r"[uUlL]+$", "", text)
    if re.search(r"\d[.eE]", text) or re.match(r"^-?\d+\.\d*", text):
        text = re.sub(r"[fF]$", "", text)
    return text

def _int_of(value):
    """Numeric value of a printed constant, without reformatting it.

    Used for *grouping* printed rows that state the same number
    (``0x01`` and ``0x0001``) and for detecting genuine conflicts.  The
    text emitted is always a printed form, never a recomputed one.
    """
    try:
        text = _strip_c_suffix(str(value).strip())
        if text.lower().startswith("0x") or text.lower().startswith("-0x"):
            return int(text, 16)
        return int(text, 10)
    except (ValueError, TypeError):
        return None


_ORIGIN_RANK = {"define": 0, "enum": 1, "table": 2, "cell": 3, "prose": 4}


def constant_value_groups(rows):
    """Group one constant's CE rows by the number they state.

    Each group: the number (for comparison), the printed forms, the CE
    sets stating it, the rows as evidence, and whether some rows of a
    *different* number overlap its versions -- a documentation conflict
    the generator lists instead of guessing.
    """
    groups = {}
    for record in rows:
        key = _int_of(record.get("value"))
        if key is None:
            # a float or other printed number: grouped by its printed
            # text, never dropped (DBL_EPSILON is a number, too)
            text_key = _strip_c_suffix(str(record.get("value") or "").strip())
            if not text_key:
                continue
            key = text_key
        slot = groups.setdefault(key, {"forms": collections.Counter(),
                                       "sets": set(), "rows": [],
                                       "license": set()})
        slot["sets"].add(record["source"]["set"])
        slot["forms"][(record["value"], _ORIGIN_RANK.get(
            record.get("origin"), 9))] += 1
        slot["license"].add(record.get("license") or "?")
        quote = (record["row"], record["source"]["path"],
                 record.get("origin") or "table")
        if quote not in slot["rows"]:
            slot["rows"].append(quote)
    out = []
    for key in sorted(groups, key=lambda k: -len(groups[k]["rows"])):
        slot = groups[key]
        best = sorted(slot["forms"].items(),
                      key=lambda kv: (kv[0][1], -kv[1], kv[0][0]))[0]
        out.append({
            "number": key,
            "print": best[0][0],
            "sets": slot["sets"],
            "merged": merge_intervals(wce_interval(s) for s in slot["sets"]),
            "neutral": sorted(s for s in slot["sets"]
                              if wce_interval(s) is None),
            "rows": slot["rows"],
            "license": slot["license"],
        })
    return out


def groups_conflict(groups):
    """Two values for one constant whose documented versions overlap.

    Disjoint intervals are version branches (``#if``/``#elif``); the same
    set stating two numbers, or overlapping intervals with two numbers,
    is a conflict -- the pages disagree and no ``#define`` is written.
    """
    mine = [g for g in groups]
    for i, first in enumerate(mine):
        for second in mine[i + 1:]:
            if first["sets"] & second["sets"]:
                return True
            for lo1, hi1 in first["merged"]:
                for lo2, hi2 in second["merged"]:
                    if lo1 < hi2 and lo2 < hi1:
                        return True
    return False


def wrap_comment(prefix, text, width=64):
    """One comment paragraph, word-wrapped -- long review verdicts read
    as comment lines instead of one endless one."""
    words = text.split()
    lines, current = [], prefix
    for word in words:
        if len(current) + len(word) + 1 > width and current.strip() != prefix.strip():
            lines.append(current.rstrip())
            current = " *   "
        current += (" " if current and not current.endswith(" ") else "") + word
    if current.strip() and current.strip() != "*":
        lines.append(current.rstrip())
    return lines


_WINDOWS_UMBRELLA = (
    "WinDef.h", "WinNT.h", "winerror.h", "Winbase.h", "Winuser.h",
    "Wingdi.h", "Winreg.h", "Commdlg.h", "Winnls.h",
    "Tlhelp32.h", "shellapi.h", "Mmsystem.h", "Aygshell.h",
    "Storemgr.h", "winioctl.h", "Notify.h", "Dbgapi.h",
    "Fsdmgr.h", "Halether.h", "Fwapi.h",
    "Pm.h", "Sipapi.h", "Htmlctrl.h",
    "Service.h", "connmgr.h", "gpsapi.h",
    "getdeviceuniqueid.h", "Cred.h", "Tapi.h",
)

# Pages often name Windows.h (the umbrella) or a desktop-split SDK
# header.  Prefer the CE header the same entity also names.
# Keepable unified/harvest quotes filed into app headers only for
# these names (driver headers take every keepable C quote).
_OVERLAY_NAMED = {
    "GetMessage", "PeekMessage", "BeginPaint", "EndPaint",
    "ReadFile", "WriteFile", "DeviceIoControl",
    "InitializeCriticalSection", "EnterCriticalSection",
    "LeaveCriticalSection", "DeleteCriticalSection",
    "wsprintf", "wvsprintf", "lstrlen", "lstrcpy", "lstrcmp",
    "lstrcat", "lstrcmpi",
    "HalGetBusData", "HalGetBusDataByOffset", "HalSetBusData",
    "HalSetBusDataByOffset", "HalTranslateBusAddress",
    "READ_PORT_UCHAR", "READ_PORT_USHORT", "READ_PORT_ULONG",
    "WRITE_PORT_UCHAR", "WRITE_PORT_USHORT", "WRITE_PORT_ULONG",
    "READ_REGISTER_UCHAR", "READ_REGISTER_USHORT", "READ_REGISTER_ULONG",
    "WRITE_REGISTER_UCHAR", "WRITE_REGISTER_USHORT", "WRITE_REGISTER_ULONG",
    "READ_PORT_BUFFER_UCHAR", "READ_PORT_BUFFER_USHORT",
    "READ_PORT_BUFFER_ULONG", "WRITE_PORT_BUFFER_UCHAR",
    "WRITE_PORT_BUFFER_USHORT", "WRITE_PORT_BUFFER_ULONG",
    "MmUnmapIoSpace", "PAINTSTRUCT", "BUS_DATA_TYPE", "INTERFACE_TYPE",
    "LOGFONT", "WNDCLASS", "TranslateMessage", "DispatchMessage",
    "DefWindowProc", "PostQuitMessage", "RegisterClass", "CreateWindowEx",
    "ShowWindow", "UpdateWindow", "GetClientRect", "InvalidateRect",
    "EndPaint", "DrawText", "CreateProcess", "CopyFileEx", "VirtualQuery",
    "SetTimer", "SetSysColors", "SetScrollInfo", "SetMenuItemInfo",
    "TrackPopupMenuEx", "SendInput", "CheckDlgButton", "CreateDialog",
    "DialogBox", "CreateFontIndirect", "CreateDIBSection", "SelectPalette",
    "SetPaletteEntries", "SetTextAlign", "StretchDIBits", "SetDIBitsToDevice",
    "CreateBitmapIndirect", "CreateBrushIndirect", "SetCommState",
    "WaitForDebugEvent", "SystemIdleTimerReset", "AdvertiseInterface",
    "RequestDeviceNotifications", "DllMain", "WinMain",
    "FindFirstFile", "FindNextFile", "WIN32_FIND_DATA", "WIN32_FIND_DATAW",
    "LOGFONT", "LOGFONTW", "TIMERPROC",
    "GetCPInfo", "SelectPalette",
    "GetOpenFileName", "GetSaveFileName", "ChooseColor", "ChooseFont",
    "OPENFILENAME", "CHOOSECOLOR", "CreateDialogIndirectParam",
    "AppendMenu", "CreateDialogParam",
    "EnumWindows", "EnumFontFamilies", "EnumFonts", "TEXTMETRIC",
    "WAVEFORMATEX",
    "DCB", "GetCommState", "SetCommState",
    "STORE_INFORMATION", "GetStoreInformation",
    "ULARGE_INTEGER", "GetDiskFreeSpaceEx",
    "COMMTIMEOUTS", "GetCommTimeouts", "SetCommTimeouts",
    "SCROLLINFO", "GetScrollInfo",
    "PALETTEENTRY", "GetPaletteEntries",
    "MEMORY_BASIC_INFORMATION",
    "BITMAP", "GetObject",
    "COMSTAT", "LOGBRUSH", "LOGPEN",
    "ABC", "GetCharABCWidths",
    "ACCEL",
    "BLENDFUNCTION", "AlphaBlend",
    "SetEvent", "ResetEvent", "DebugBreak",
    "GetCurrentProcess", "GetCurrentProcessId",
    "GetCurrentThread", "GetCurrentThreadId",
    "ExitProcess", "GlobalDeleteAtom",
    "FindClosePartition", "FindCloseStore",
    "FormatMessage", "SetFilePointer",
    "CommDlgExtendedError",
    "RegCopyFile", "RegRestoreFile",
    "RedrawWindow", "ExtTextOut",
    "GetSystemInfo", "SYSTEM_INFO",
    "FindCloseUrlCache",
    "GetACP", "GetOEMCP", "IsDBCSLeadByte", "IsDBCSLeadByteEx",
    "CreateToolhelp32Snapshot", "Process32First", "Process32Next",
    "Module32First", "Module32Next", "CloseToolhelp32Snapshot",
    "PROCESSENTRY32", "MODULEENTRY32",
    "SHGetSpecialFolderPath", "ShellExecuteEx", "SHELLEXECUTEINFO",
    "PlaySound", "sndPlaySound", "timeGetTime",
    "waveInGetNumDevs", "waveOutGetNumDevs",
    "SHCreateMenuBar", "SHFullScreen", "SHSipInfo",
    "OpenStore", "FormatStore", "FindCloseStore", "FindClosePartition",
    "CeSetUserNotification", "CeSetUserNotificationEx",
    "CeClearUserNotification", "WriteDebugLED", "NKDbgPrintfW",
    "AdjustWindowRectEx", "GetDoubleClickTime",
    "FSDMGR_CachedRead", "FSDMGR_CachedWrite",
    "GetSystemPowerState", "SetSystemPowerState",
    "SipShowIM", "SipGetInfo", "InitHTMLControl",
    "GetServiceHandle", "ActivateService",
    "ConnMgrApiReadyEvent",
    "GPSOpenDevice", "GPSCloseDevice", "GPSGetPosition",
    "GetDeviceUniqueID", "CredFree",
    "phoneConfigDialog",
}

_OVERLAY_HEADERS = {
    "windef.h", "winnt.h", "winbase.h", "winuser.h", "wingdi.h",
    "winreg.h", "winerror.h", "winioctl.h", "mmsystem.h", "imm.h",
    "winnls.h", "windbase.h", "dbgapi.h", "commdlg.h",
    "aygshell.h", "tlhelp32.h", "shellapi.h", "storemgr.h",
    "notify.h", "dbgapi.h", "fsdmgr.h", "halether.h", "fwapi.h",
    "pm.h", "sipapi.h", "htmlctrl.h", "service.h", "connmgr.h",
    "gpsapi.h", "getdeviceuniqueid.h", "cred.h", "tapi.h",
}
_APP_OVERLAY_HEADERS = {
    "windef.h", "winnt.h", "winerror.h", "winbase.h", "winuser.h",
    "wingdi.h", "winreg.h", "commdlg.h",
}
_DDK_HEADERS = {
    "ceddk.h", "pkfuncs.h", "kfuncs.h", "nkintr.h", "winddi.h",
}


def _want_overlay(name, kind, text, hl):
    if hl in _DDK_HEADERS:
        return True
    if hl not in _OVERLAY_HEADERS:
        return False
    return name in _OVERLAY_NAMED

CE_CORE_HEADERS = {
    "windef.h", "winnt.h", "basetsd.h", "winbase.h", "winuser.h",
    "wingdi.h", "winerror.h", "winreg.h", "winioctl.h", "commctrl.h",
    "commdlg.h", "winsock.h", "winsock2.h", "ceddk.h", "winddi.h",
    "pkfuncs.h", "kfuncs.h", "excpt.h", "pwinuser.h", "nkintr.h",
    "shellapi.h", "aygshell.h", "tlhelp32.h", "windev.h",
}
DESKTOP_SPLIT_HEADERS = {
    "processthreadsapi.h", "fileapi.h", "errhandlingapi.h",
    "minwinbase.h", "gdiplustypes.h", "libloaderapi.h", "sysinfoapi.h",
    "synchapi.h", "memoryapi.h", "handleapi.h", "timezoneapi.h",
    "stringapiset.h", "debugapi.h", "fibersapi.h", "ioapiset.h",
    "namedpipeapi.h", "securitybaseapi.h", "heapapi.h", "jobapi.h",
    "processenv.h", "profileapi.h", "realtimeapiset.h",
    "threadpoollegacyapiset.h", "wow64apiset.h", "interlockedapi.h",
    "wtypesbase.h", "minwindef.h", "winnt.h.bak",
}


def header_preference(key):
    """Lower is better for the file a C compiler should actually include."""
    k = (key or "").lower()
    if k in ("windows.h",):
        return 50
    if k.endswith(".idl") or k.endswith(".hpp") or ".idl." in k:
        return 40
    if k in DESKTOP_SPLIT_HEADERS:
        return 20
    if k in CE_CORE_HEADERS:
        return 0
    return 10


# Desktop windows-data-types.md also prints the 64-bit spelling.
# Windows CE is 32-bit; use the 32-bit row of the same page family.
_CE_PTR_TYPES = {
    "LONG_PTR": "typedef long LONG_PTR;",
    "ULONG_PTR": "typedef unsigned long ULONG_PTR;",
    "UINT_PTR": "typedef unsigned long UINT_PTR;",
    "DWORD_PTR": "typedef unsigned long DWORD_PTR;",
    "INT_PTR": "typedef long INT_PTR;",
    "HALF_PTR": "typedef short HALF_PTR;",
    "UHALF_PTR": "typedef unsigned short UHALF_PTR;",
}

# windows-data-types.md (CC-BY) + CE Unicode notes.  Not copied from
# any SDK/w32api file.  TCHAR follows UNICODE, which this tree defines.
_CORE_TYPEDEFS = (
    ("UCHAR", "typedef unsigned char UCHAR;"),
    ("USHORT", "typedef unsigned short USHORT;"),
    ("PVOID", "typedef void *PVOID;"),
    ("LPVOID", "typedef void *LPVOID;"),
    ("LPCVOID", "typedef CONST void *LPCVOID;"),
    ("LPSTR", "typedef CHAR *LPSTR;"),
    ("LPCSTR", "typedef CONST CHAR *LPCSTR;"),
    ("TCHAR", "typedef WCHAR TCHAR;"),
    ("LPTSTR", "typedef LPWSTR LPTSTR;"),
    ("LPCTSTR", "typedef LPCWSTR LPCTSTR;"),
    ("PTSTR", "typedef LPWSTR PTSTR;"),
    ("PCTSTR", "typedef LPCWSTR PCTSTR;"),
    ("LONGLONG", "typedef __int64 LONGLONG;"),
    ("ULONGLONG", "typedef unsigned __int64 ULONGLONG;"),
    ("HRESULT", "typedef LONG HRESULT;"),
    ("NTSTATUS", "typedef LONG NTSTATUS;"),
    ("SIZE_T", "typedef ULONG_PTR SIZE_T;"),
    ("SSIZE_T", "typedef LONG_PTR SSIZE_T;"),
    ("WNDPROC",
     "typedef LRESULT (CALLBACK *WNDPROC)(HWND, UINT, WPARAM, LPARAM);"),
    ("FARPROC", "typedef INT_PTR (WINAPI *FARPROC)(void);"),
    ("NEARPROC", "typedef INT_PTR (WINAPI *NEARPROC)(void);"),
    ("PROC", "typedef INT_PTR (WINAPI *PROC)(void);"),
    ("SECURITY_ATTRIBUTES",
     "typedef struct _SECURITY_ATTRIBUTES SECURITY_ATTRIBUTES, "
     "*PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;"),
    ("FILETIME",
     "typedef struct _FILETIME { DWORD dwLowDateTime; DWORD dwHighDateTime; } "
     "FILETIME, *PFILETIME, *LPFILETIME;"),
    ("SYSTEMTIME",
     "typedef struct _SYSTEMTIME { WORD wYear; WORD wMonth; WORD wDayOfWeek; "
     "WORD wDay; WORD wHour; WORD wMinute; WORD wSecond; WORD wMilliseconds; } "
     "SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;"),
    ("CEOID", "typedef DWORD CEOID;"),
    ("PCEOID", "typedef CEOID *PCEOID;"),
    ("CEPROPID", "typedef DWORD CEPROPID;"),
    ("PPVOID", "typedef PVOID *PPVOID;"),
    ("LPTHREAD_START_ROUTINE",
     "typedef DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID);"),
    ("LARGE_INTEGER",
     "typedef union _LARGE_INTEGER { struct { DWORD LowPart; LONG HighPart; } u; "
     "LONGLONG QuadPart; } LARGE_INTEGER, *PLARGE_INTEGER;"),
    ("PHYSICAL_ADDRESS",
     "typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;"),
    ("CRITICAL_SECTION",
     "typedef struct _CRITICAL_SECTION CRITICAL_SECTION, "
     "*PCRITICAL_SECTION, *LPCRITICAL_SECTION;"),
    ("STARTUPINFOW",
     "typedef struct _STARTUPINFOW STARTUPINFOW, *LPSTARTUPINFOW;"),
    ("STARTUPINFO",
     "typedef STARTUPINFOW STARTUPINFO, *LPSTARTUPINFO;"),
    ("PROCESS_INFORMATION",
     "typedef struct _PROCESS_INFORMATION PROCESS_INFORMATION, "
     "*LPPROCESS_INFORMATION, *PPROCESS_INFORMATION;"),
    ("TIMERPROC",
     "typedef void (CALLBACK *TIMERPROC)(HWND, UINT, UINT, DWORD);"),
    ("DLGPROC",
     "typedef INT_PTR (CALLBACK *DLGPROC)(HWND, UINT, WPARAM, LPARAM);"),
    ("BITMAPINFOHEADER",
     "typedef struct tagBITMAPINFOHEADER BITMAPINFOHEADER, "
     "*PBITMAPINFOHEADER, *LPBITMAPINFOHEADER;"),
    ("BITMAPINFO",
     "typedef struct tagBITMAPINFO BITMAPINFO, *PBITMAPINFO, *LPBITMAPINFO;"),
    ("CHOOSECOLOR",
     "typedef struct tagCHOOSECOLOR CHOOSECOLOR, *LPCHOOSECOLOR;"),
    ("CHOOSEFONT",
     "typedef struct tagCHOOSEFONT CHOOSEFONT, *LPCHOOSEFONT;"),
    ("OPENFILENAME",
     "typedef struct tagOPENFILENAME OPENFILENAME, *LPOPENFILENAME;"),
    ("DLGTEMPLATE",
     "typedef struct tagDLGTEMPLATE DLGTEMPLATE, *LPDLGTEMPLATE, "
     "*LPCDLGTEMPLATE;"),
    ("LCID", "typedef DWORD LCID;"),
    ("PDWORD", "typedef DWORD *PDWORD;"),
    ("PUINT", "typedef UINT *PUINT;"),
    ("LPINT", "typedef int *LPINT;"),
    ("PINT", "typedef int *PINT;"),
    ("PUSHORT", "typedef USHORT *PUSHORT;"),
    ("PLONG", "typedef LONG *PLONG;"),
    ("PULONG", "typedef ULONG *PULONG;"),
    ("SYSTEM_INFO",
     "typedef struct _SYSTEM_INFO SYSTEM_INFO, *LPSYSTEM_INFO;"),
    ("WNDENUMPROC",
     "typedef BOOL (CALLBACK *WNDENUMPROC)(HWND, LPARAM);"),
    ("WNDENUMPROCW",
     "typedef BOOL (CALLBACK *WNDENUMPROCW)(HWND, LPARAM);"),
    ("FONTENUMPROC",
     "typedef int (CALLBACK *FONTENUMPROC)(ENUMLOGFONT FAR *, "
     "TEXTMETRIC FAR *, int, LPARAM);"),
    ("FONTENUMPROCW",
     "typedef int (CALLBACK *FONTENUMPROCW)(ENUMLOGFONT FAR *, "
     "TEXTMETRIC FAR *, int, LPARAM);"),
    ("LPLOGFONT",
     "typedef struct tagLOGFONT *PLOGFONT, *LPLOGFONT;"),
    ("TEXTMETRIC",
     "typedef struct tagTEXTMETRIC TEXTMETRIC, *PTEXTMETRIC, *LPTEXTMETRIC;"),
    ("ENUMLOGFONT",
     "typedef struct tagENUMLOGFONT ENUMLOGFONT, *PENUMLOGFONT, "
     "*LPENUMLOGFONT;"),
    ("WAVEFORMATEX",
     "typedef struct tWAVEFORMATEX WAVEFORMATEX, *PWAVEFORMATEX, "
     "*LPWAVEFORMATEX;"),
    ("ULARGE_INTEGER",
     "typedef struct ULARGE_INTEGER { ULONGLONG QuadPart; } "
     "ULARGE_INTEGER, *PULARGE_INTEGER;"),
    # GetCharABCWidths PRE names LPABC; ABC PRE only prints *PABC.
    ("LPABC", "typedef struct _ABC *LPABC;"),
)

_WINDEF_NEED = (
    "BYTE", "WORD", "DWORD", "BOOL", "UINT", "INT", "LONG", "ULONG",
    "SHORT", "CHAR", "FLOAT", "WCHAR", "PVOID", "LPVOID", "HANDLE",
    "HWND", "HINSTANCE", "HMODULE", "HDC", "HMENU", "HKEY", "HBITMAP",
    "HFONT", "HPEN", "HBRUSH", "HRGN", "HICON", "HCURSOR",
    "LPSTR", "LPCSTR", "LPWSTR", "LPCWSTR", "LPTSTR", "LPCTSTR",
    "LONG_PTR", "UINT_PTR", "ULONG_PTR", "DWORD_PTR",
    "WPARAM", "LPARAM", "LRESULT", "ATOM", "COLORREF", "TCHAR",
)


def _ident_tokens(text):
    return set(re.findall(r"\b[A-Z][A-Z0-9_]*\b", text or ""))


_C_KNOWN_TYPES = {
    "DWORD", "BOOL", "BYTE", "WORD", "UINT", "INT", "LONG", "ULONG", "SHORT",
    "CHAR", "WCHAR", "TCHAR", "FLOAT", "VOID", "CONST", "HANDLE", "HWND",
    "HDC", "HINSTANCE", "HMODULE", "HMENU", "HICON", "HBITMAP", "HBRUSH",
    "HFONT", "HPEN", "HRGN", "HKEY", "PVOID", "LPVOID", "LPCVOID", "LPSTR",
    "LPCSTR", "LPWSTR", "LPCWSTR", "LPTSTR", "LPCTSTR", "LPARAM", "WPARAM",
    "LRESULT", "UINT_PTR", "LONG_PTR", "ULONG_PTR", "DWORD_PTR", "INT_PTR",
    "SIZE_T", "SSIZE_T", "HRESULT", "NTSTATUS", "ATOM", "COLORREF",
    "FILETIME", "SYSTEMTIME", "RECT", "POINT", "SIZE", "MSG", "UCHAR",
    "USHORT", "LONGLONG", "ULONGLONG", "CEOID", "CEPROPID",
    "SECURITY_ATTRIBUTES", "LPSECURITY_ATTRIBUTES", "PSECURITY_ATTRIBUTES",
    "WNDPROC", "FARPROC", "NEARPROC", "PROC", "LPBYTE", "LPDWORD", "LPWORD",
    "LPLONG", "LPBOOL", "LPHANDLE", "DWORD64", "UINT64", "LONG64", "INT64",
    "BOOLEAN", "LPTHREAD_START_ROUTINE", "PFILETIME", "LPFILETIME",
    "PRECT", "LPRECT", "LPCRECT", "PPOINT", "LPPOINT", "PSIZE", "LPSIZE",
    "HCURSOR", "HACCEL", "HRSRC", "HGLOBAL", "HLOCAL", "HDWP", "HGDIOBJ",
    "LARGE_INTEGER", "PLARGE_INTEGER", "PHYSICAL_ADDRESS", "PPHYSICAL_ADDRESS",
    "INTERFACE_TYPE", "BOOLEAN", "HKEY", "PHKEY", "PUCHAR", "PULONG",
    "LPMSG", "PMSG", "LPPAINTSTRUCT", "PPAINTSTRUCT",
    "LPOVERLAPPED", "POVERLAPPED", "OVERLAPPED",
    "LPCRITICAL_SECTION", "PCRITICAL_SECTION", "CRITICAL_SECTION",
    "LPSECURITY_ATTRIBUTES",
    "STARTUPINFOW", "LPSTARTUPINFOW", "STARTUPINFO", "LPSTARTUPINFO",
    "PROCESS_INFORMATION", "LPPROCESS_INFORMATION", "PPROCESS_INFORMATION",
    "TIMERPROC", "DLGPROC",
    "WIN32_FIND_DATA", "LOGFONT", "LOGFONTW", "LPLOGFONT",
    "HPALETTE", "HGDIOBJ", "HKL", "HMONITOR", "HHOOK",
    "BITMAPINFOHEADER", "PBITMAPINFOHEADER", "LPBITMAPINFOHEADER",
    "BITMAPINFO", "PBITMAPINFO", "LPBITMAPINFO",
    "CHOOSECOLOR", "LPCHOOSECOLOR",
    "CHOOSEFONT", "LPCHOOSEFONT",
    "OPENFILENAME", "LPOPENFILENAME",
    "DLGTEMPLATE", "LPDLGTEMPLATE", "LPCDLGTEMPLATE",
    "LCID", "PDWORD", "PUINT", "LPINT", "PINT", "PUSHORT", "PBYTE",
    "PLONG", "PULONG",
    "SYSTEM_INFO", "LPSYSTEM_INFO",
    "PROCESSENTRY32", "LPPROCESSENTRY32", "PPROCESSENTRY32",
    "MODULEENTRY32", "LPMODULEENTRY32", "PMODULEENTRY32",
    "SHELLEXECUTEINFO", "LPSHELLEXECUTEINFO",
    "BLENDFUNCTION", "PBLENDFUNCTION", "LPBLENDFUNCTION",
    "WNDENUMPROC", "FONTENUMPROC",
    "TEXTMETRIC", "PTEXTMETRIC", "LPTEXTMETRIC",
    "ENUMLOGFONT", "PENUMLOGFONT", "LPENUMLOGFONT",
    "WAVEFORMATEX", "PWAVEFORMATEX", "LPWAVEFORMATEX",
    "ULARGE_INTEGER", "PULARGE_INTEGER",
    "DCB", "LPDCB", "PDCB",
    "STORE_INFORMATION", "LPSTORE_INFORMATION",
    "MEMORY_BASIC_INFORMATION", "PMEMORY_BASIC_INFORMATION",
    "ABC", "PABC", "LPABC",
    "COMMTIMEOUTS", "LPCOMMTIMEOUTS",
    "SCROLLINFO", "LPSCROLLINFO",
    "PAINTSTRUCT", "LPPAINTSTRUCT",
    "PALETTEENTRY", "LPPALETTEENTRY",
    "BITMAP", "PBITMAP", "LPBITMAP",
    "COMSTAT", "LPCOMSTAT",
    "LOGBRUSH", "LPLOGBRUSH",
    "LOGPEN", "LPLOGPEN",
    "ACCEL", "LPACCEL",
}


def order_type_infos(items):
    """Emit structure bodies after the types they mention in this header."""
    by = {}
    unnamed = []
    for info in items:
        name = (info.get("entity") or {}).get("name")
        if name:
            by[name] = info
        else:
            unnamed.append(info)
    pending = list(by)
    emitted, known = [], set()
    skip = {"TYPEDEF", "STRUCT", "UNION", "ENUM", "CONST", "VOID", "INT",
            "CHAR", "SHORT", "LONG", "UNSIGNED", "SIGNED", "FLOAT"}
    while pending:
        rest, progress = [], False
        for name in pending:
            decl = by[name].get("declaration") or {}
            text = decl.get("text") if isinstance(decl, dict) else ""
            deps = _ident_tokens(text) - {name} - skip
            if all(d in known or d not in by for d in deps):
                emitted.append(by[name])
                known.add(name)
                progress = True
            else:
                rest.append(name)
        if not progress:
            emitted.extend(by[n] for n in rest)
            break
        pending = rest
    return unnamed + emitted


# Scalars / handles: ``LPUINT`` is not automatically a type just because
# UINT is.  Pointer aliases follow structure names (LPMSG, LPRECT).
_SCALAR_OR_HANDLE = {
    "DWORD", "BOOL", "BYTE", "WORD", "UINT", "INT", "LONG", "ULONG", "SHORT",
    "CHAR", "WCHAR", "TCHAR", "FLOAT", "VOID", "HANDLE", "HWND", "HDC",
    "HINSTANCE", "HMODULE", "HMENU", "HICON", "HBITMAP", "HBRUSH", "HFONT",
    "HPEN", "HRGN", "HKEY", "HCURSOR", "HACCEL", "HRSRC", "HGLOBAL", "HLOCAL",
    "HDWP", "HGDIOBJ", "HPALETTE", "HKL", "HMONITOR", "HHOOK", "HDESK",
    "HRESULT", "NTSTATUS", "ATOM", "COLORREF", "UCHAR", "USHORT",
    "LONGLONG", "ULONGLONG", "CEOID", "CEPROPID", "BOOLEAN", "SIZE_T",
    "SSIZE_T", "UINT_PTR", "LONG_PTR", "ULONG_PTR", "DWORD_PTR", "INT_PTR",
}


def _type_token_known(tok, local_names):
    if tok in _C_KNOWN_TYPES or tok in local_names:
        return True
    # LPMSG / PMSG follow MSG; LPOVERLAPPED follows OVERLAPPED.
    # Not LPUINT -- that typedef is a separate printed fact.
    for prefix in ("LP", "P"):
        if tok.startswith(prefix) and len(tok) > len(prefix) + 1:
            base = tok[len(prefix):]
            if base in _SCALAR_OR_HANDLE:
                continue
            if base in _C_KNOWN_TYPES or base in local_names:
                return True
    return False


def type_mentions_unknown(text, local_names, self_name=None, macros=None):
    """True if a struct/function names a type this header does not define.

    Enumerator names inside ``typedef enum`` are values, not types.
    The identifier being declared (``READ_PORT_UCHAR(``) is not a type.
    Array bounds are constants: keep the quote only when that name is a
    #define this tree actually emits (MAX_PATH, LF_FACESIZE, ...).
    """
    body = text or ""
    if re.search(r"\btypedef\s+enum\b|\benum\s+\w+\s*\{", body):
        return False
    if body.lstrip().startswith("#"):
        return False
    known_macros = set(macros or ()) | set(local_names or ())
    for bound in re.findall(r"\[([A-Z][A-Z0-9_]{1,40})\]", body):
        if bound not in known_macros:
            return True
    # Array bounds ([MAX_PATH], [LF_FACESIZE]) are constants, not types.
    body = re.sub(r"\[[^\]]*\]", " ", body)
    skip = {"TYPEDEF", "STRUCT", "UNION", "ENUM", "CONST", "VOID", "INT",
            "CHAR", "SHORT", "LONG", "UNSIGNED", "SIGNED", "FLOAT", "DOUBLE",
            "IN", "OUT", "OPTIONAL", "FAR", "NEAR", "PASCAL", "WINAPI",
            "CALLBACK", "APIENTRY", "WINGDIAPI", "WINOLEAPI", "STDAPI",
            "CDECL", "STDCALL", "WINAPIV", "WINAPI_INLINE"}
    if self_name:
        skip.add(self_name)
    skip.update(re.findall(r"\b([A-Z][A-Z0-9_]*)\s*\(", body))
    # Incomplete structs cannot be non-pointer fields.
    if "{" in body:
        for inc in ("BITMAPINFOHEADER", "BITMAPINFO", "CRITICAL_SECTION",
                    "SECURITY_ATTRIBUTES", "STARTUPINFOW", "STARTUPINFO",
                    "PROCESS_INFORMATION", "CHOOSECOLOR", "OPENFILENAME",
                    "DLGTEMPLATE"):
            if re.search(r"\b" + inc + r"\s+[A-Za-z_]\w*\s*;", body):
                return True
    for tok in _ident_tokens(body) - skip:
        if _type_token_known(tok, local_names):
            continue
        if re.match(r"^[A-Z][A-Z0-9_]+$", tok) and len(tok) >= 3:
            return True
        if re.match(r"^[A-Z][A-Za-z0-9]+$", tok) and tok.endswith(
                ("INFO", "STRUCT", "HEADER", "ENTRY", "PROC", "INPUT")):
            return True
    return False


def order_base_types(rows):
    """Emit typedefs so a name is defined before it is used."""
    by_name = {}
    for row in rows:
        by_name[row["type"]] = row
    pending = list(by_name)
    emitted, known = [], set()
    skip = {"TYPEDEF", "STRUCT", "UNION", "ENUM", "CONST", "VOID", "INT",
            "CHAR", "SHORT", "LONG", "UNSIGNED", "SIGNED", "FLOAT",
            "DOUBLE", "UNICODE", "IFDEF", "IFNDEF", "ENDIF", "ELSE",
            "DEFINED", "INCLUDE"}
    while pending:
        rest, progress = [], False
        for name in pending:
            deps = _ident_tokens(by_name[name]["definition"]) - {name} - skip
            if all(d in known or d not in by_name for d in deps):
                emitted.append(by_name[name])
                known.add(name)
                progress = True
            else:
                rest.append(name)
        if not progress:
            for name in rest:
                emitted.append(by_name[name])
            break
        pending = rest
    return emitted


def enrich_windef_base_types(base_types_by_header):
    """WinDef.h is included first; pull HANDLE and friends into it."""
    all_rows = {}
    for rows in base_types_by_header.values():
        for row in rows:
            all_rows.setdefault(row["type"], row)
    windef = list(base_types_by_header.get("windef.h") or [])
    have = {r["type"] for r in windef}
    for name in _WINDEF_NEED:
        if name not in have and name in all_rows:
            windef.append(all_rows[name])
            have.add(name)
    for name, defn in _CE_PTR_TYPES.items():
        if name not in have:
            windef.append({
                "type": name, "definition": defn, "header": "WinDef.h",
                "ce_specific": "yes",
                "ce_note": "32-bit CE pointer-sized integer",
                "ce_value_note": "",
                "source": "win32/common/windows-data-types.md (32-bit row)",
            })
            have.add(name)
    for name, defn in _CORE_TYPEDEFS:
        row = {
            "type": name, "definition": defn, "header": "WinDef.h",
            "ce_specific": "yes",
            "ce_note": "CE Unicode / 32-bit data-types row",
            "ce_value_note": "",
            "source": "win32/common/windows-data-types.md",
        }
        if name not in have:
            windef.append(row)
            have.add(name)
        else:
            for existing in windef:
                if existing["type"] == name and (
                        existing.get("definition", "").startswith("#ifdef")
                        or "\\n" in (existing.get("definition") or "")):
                    existing.update(row)
    base_types_by_header["windef.h"] = windef


def _write_windows_umbrella(include_dir):
    """Replace Windows.h with an include of the core CE headers.

    Declarations a page filed only under Windows.h are kept as
    WindowsApis.h and pulled in at the end, so the umbrella does not
    delete MessageBox / MSG.
    """
    existing = os.path.join(include_dir, "Windows.h")
    leftover = os.path.join(include_dir, "WindowsApis.h")
    if os.path.isfile(existing):
        text = read_text(existing)
        if "Windows CE unified surface" in text:
            text = text.replace("Windows.h --", "WindowsApis.h --", 1)
            text = text.replace("#ifndef _WINDOWS_", "#ifndef _WINDOWSAPIS_", 1)
            text = text.replace("#define _WINDOWS_", "#define _WINDOWSAPIS_", 1)
            text = text.replace("#endif /* _WINDOWS_ */",
                                "#endif /* _WINDOWSAPIS_ */", 1)
            _write_lines(leftover, text.splitlines())
        os.remove(existing)
    present = {name.lower(): name for name in os.listdir(include_dir)
               if name.lower().endswith(".h")}
    includes = []
    for name in _WINDOWS_UMBRELLA:
        hit = present.get(name.lower())
        if hit:
            includes.append(hit)
    # WindowsApis.h is the leftover dump of pages that only named
    # Windows.h.  It is not included here: it redeclares core types.
    if not includes:
        return
    lines = [
        "/* Windows.h -- Windows CE unified umbrella",
        " *",
        " * #include this file.  It pulls in the core CE headers this",
        " * tree actually generated.  Values stay in those headers.",
        " * Drivers also #include \"CEDDK.h\" (not part of the app umbrella).",
        " */",
        "#ifndef _WINDOWS_",
        "#define _WINDOWS_",
        "",
    ]
    for hit in includes:
        lines.append(f'#include "{hit}"')
    lines += ["", "#endif /* _WINDOWS_ */", ""]
    _write_lines(os.path.join(include_dir, "Windows.h"), lines)


def run_unified(args):
    """One include/def tree for every Windows CE generation at once."""
    declarations_of = {d["id"]: d for d in load(DECLARATIONS)}
    reqs_of = collections.defaultdict(list)
    for record in load(REQUIREMENTS):
        if record.get("entity"):
            reqs_of[record["entity"]].append(record)
    constants = list(load(CONSTANTS)) if os.path.exists(CONSTANTS) else []
    all_entities = list(load(ENTITIES))
    UNSUPPORTED.update(load_unsupported())
    links = load_constant_links()
    conflict_rows = load_constant_conflicts()
    pinvoke_apis = load_pinvoke_aux(PINVOKE_APIS)
    pinvoke_consts = load_pinvoke_aux(PINVOKE_CONSTANTS)
    base_types_by_header = load_base_types()
    enrich_windef_base_types(base_types_by_header)
    extra_defines, extra_declarations = load_extra_surface()
    heuristic_rows = load_heuristic_headers()
    modules_ce_headers = load_modules_ce_headers()
    lib_to_header = build_lib_to_unique_header(all_entities)
    page_to_headers = collections.defaultdict(set)
    for ent in all_entities:
        hs = header_files(ent.get("headers") or [])
        if not hs:
            continue
        for page in (ent.get("ce_pages") or []) + (ent.get("win32_pages") or []):
            for h in hs:
                page_to_headers[page].add(h)
    leftover_kb_decls = []
    borrow = not args.no_borrow

    entities, variants = unified_scope(all_entities)
    if args.limit:
        entities = entities[:args.limit]

    # The tree is rebuilt wholesale: drop leftovers from previous runs so
    # no stale fragment survives a case-fix or a removed header.
    for subtree in (os.path.join(args.out, "include"),
                    os.path.join(args.out, "link")):
        shutil.rmtree(subtree, ignore_errors=True)
        os.makedirs(subtree, exist_ok=True)
    by_header = collections.defaultdict(list)
    printed_forms = {}
    by_module = collections.defaultdict(
        lambda: {"entries": [], "stated": set()})
    skipped = collections.Counter()
    borrowed = collections.Counter()
    pages = set()
    manifest = []
    by_id = {e["id"]: e for e in all_entities}

    for entity in sorted(entities, key=lambda e: e["name"].lower()):
        chosen, borrowed_from, ce_recs, win32_recs = \
            choose_unified_declaration(entity, declarations_of, borrow)
        if chosen and (not looks_like_c_declaration(chosen.get("text") or "")
                       or quality_filters.is_define_only_block(
                           chosen.get("text") or "")
                       or quality_filters.is_glued_prototype(
                           chosen.get("text") or "")
                       or quality_filters.is_broken_c(
                           chosen.get("text") or "")
                       or quality_filters.is_cpp_or_managed(
                           chosen.get("text") or "",
                           entity.get("name") or "")
                       or quality_filters.decl_unusable_for_c(
                           chosen.get("text") or "",
                           entity.get("name") or "")):
            skipped["declaration is not a C declaration"] += 1
            chosen = None
            borrowed_from = ""
        page_decl = chosen["source"]["path"] if chosen else ""
        if chosen:
            pages.add(chosen["source"]["path"])
        if borrowed_from:
            borrowed[borrowed_from.split(":")[0].split("|")[0]] += 1
            if "|spacing" in borrowed_from:
                borrowed["spacing"] += 1

        versions = unified_versions(entity, declarations_of, reqs_of)
        neutral_ce = sorted(s for s in entity.get("ce_sets") or ()
                            if wce_interval(s) is None)

        # -- headers: every CE statement across the generations; the primary
        # file is the statement of the newest documented generation, the
        # rest are listed beside it (never dropped, never invented).
        header_stmts = collections.defaultdict(set)
        win32_headers = []
        for record in reqs_of.get(entity["id"], ()):
            if record.get("field") != "header":
                continue
            files = header_files([record.get("value") or ""])
            if record.get("layer") == "ce":
                for name in files:
                    book = (record.get("source") or {}).get("set") or ""
                    header_stmts[name.lower()].add(book)
                    header_stmts[name.lower()].add(name)
            elif record.get("layer") == "win32":
                for name in files:
                    if name.lower() not in [h.lower() for h in win32_headers]:
                        win32_headers.append(name)
        header_cands = {}
        for key, items in header_stmts.items():
            books = {b for b in items if "/" in b}
            # deterministic display spelling: longest, then ASCII order --
            # a set max() tie used to flip the fragment filename casing
            # from run to run (PYTHONHASHSEED-dependent iteration).
            spellings = sorted((i for i in items if "/" not in i),
                               key=lambda s: (-len(s), s))
            printed = spellings[0] if spellings else key
            newest = max((wce_interval(b) or (0, 0))[0] for b in books)
            header_cands[key] = {"printed": printed, "sets": books,
                                 "newest": newest}
        header_mark = ""
        if header_cands:
            primary_key = sorted(
                header_cands, key=lambda k: (
                    header_preference(k),
                    -header_cands[k]["newest"], -len(header_cands[k]["sets"]),
                    k))[0]
            primary = header_cands[primary_key]["printed"]
            alternates = [(c["printed"], c["sets"]) for k, c in
                          sorted(header_cands.items()) if k != primary_key]
        elif entity.get("headers"):
            files = header_files(entity.get("headers") or [])
            files = sorted(files, key=lambda h: (
                header_preference(h.lower()), h.lower()))
            # Never file a prototype into the umbrella Windows.h.
            files = [h for h in files if h.lower() not in
                     ("windows.h", "windowsapis.h")] or files
            primary = files[0] if files else ""
            alternates = [(h, set()) for h in files[1:]]
            header_mark = "entity-headers" if primary else ""
        elif borrow and win32_headers:
            primary = win32_headers[0]
            alternates = [(h, set()) for h in win32_headers[1:]]
            header_mark = "win32-reference"
            borrowed["header win32-reference"] += 1
        else:
            primary = ""
            alternates = []

        # -- libraries/modules: the CE statements first (Win32 as marked
        # fallback); a CE statement for every generation the union of.
        lib_sets = collections.defaultdict(set)
        win32_mods = {}
        for record in reqs_of.get(entity["id"], ()):
            if record.get("field") not in ("library", "dll"):
                continue
            for name in page_parse.assigned_files(record.get("value") or "") \
                    or ([record["key"]] if record.get("key") else []):
                parsed = module_of(name)
                if not parsed:
                    continue
                book = (record.get("source") or {}).get("set") or ""
                if record.get("layer") == "ce":
                    lib_sets[parsed[0].lower()].add(book)
                    lib_sets[parsed[0].lower()].add(name)
                elif record.get("layer") == "win32":
                    win32_mods.setdefault(parsed[0].lower(), set()).add(name)
        lib_mark = ""
        modules = {}
        if lib_sets:
            for stem, items in sorted(lib_sets.items()):
                names = {i for i in items if "/" not in i}
                modules[stem] = names
        elif borrow and win32_mods:
            modules = {stem: names for stem, names in win32_mods.items()}
            lib_mark = "win32-reference"
            borrowed["library win32-reference"] += 1

        # Members a page documents without printing a declaration body:
        # the fragment carries them as a derived outline instead of
        # leaving the structure out of the header entirely.
        outline = member_outline(entity, variants.get(entity["id"], [])) \
            if not chosen else []
        if not chosen and not outline:
            skipped["no declaration in the corpus"] += 1
        name_only = False
        # Heuristic header assignment for entities without headers
        if not primary:
            heuristic_header = heuristic_entity_header(
                entity, lib_to_header=lib_to_header,
                heuristic_rows=heuristic_rows)
            if not heuristic_header:
                for lib in (entity.get("libraries") or []) + (
                        entity.get("dlls") or []):
                    parsed = module_of(lib)
                    stem = (parsed[0] if parsed else lib).lower()
                    if stem in modules_ce_headers:
                        heuristic_header = modules_ce_headers[stem]
                        break
            if not heuristic_header:
                votes = collections.Counter()
                for page in entity.get("ce_pages") or ():
                    for h in page_to_headers.get(page) or ():
                        votes[h] += 1
                if votes:
                    heuristic_header = votes.most_common(1)[0][0]
            if heuristic_header:
                primary = heuristic_header
                alternates = []
                header_mark = "heuristic-prefix"
        if not primary:
            mapped = header_map.header_for_entity(
                entity.get("name") or "", entity.get("kinds") or [])
            if mapped:
                primary = mapped
                header_mark = "heuristic-prefix"
        if primary and primary.lower() in ("windows.h", "windowsapis.h"):
            mapped = header_map.header_for_entity(
                entity.get("name") or "", entity.get("kinds") or [])
            if mapped and mapped.lower() not in ("windows.h", "windowsapis.h"):
                primary = mapped
                header_mark = (header_mark or "") + "+not-umbrella"
        if not primary:
            skipped["no header stated"] += 1
            if chosen:
                leftover_kb_decls.append({
                    "type": (entity.get("kinds") or ["function"])[0],
                    "name": entity.get("name") or "",
                    "declaration": chosen.get("text") or "",
                    "source": ((chosen.get("source") or {}).get("path") or ""),
                })
        guard, merged = wce_guard(versions)
        kinds_now = set(entity.get("kinds") or [])
        # Types and macros are the same C on every CE generation; gating
        # them behind one book's _WIN32_WCE made HIWORD/TCHAR vanish.
        if kinds_now & {"struct", "enum", "typedef", "macro", "union"}:
            guard, merged = None, []
        if not versions and not neutral_ce:
            skipped["no CE version evidence"] += 1
        if primary and not chosen and not outline:
            n = entity.get("name") or ""
            kinds = entity.get("kinds") or []
            # ALL-CAPS names are constants/macros already filed as #define;
            # a name-only function stub is noise in a development header.
            if "macro" in kinds and not (n.isupper() and "_" in n):
                name_only = True
            elif "struct" in kinds or "enum" in kinds or "typedef" in kinds \
                    or "interface" in kinds:
                name_only = True
        if primary and (chosen or outline or name_only):
            printed_forms[primary.lower()] = primary
            by_header[primary.lower()].append(
                {"entity": entity, "declaration": chosen,
                 "outline": outline, "name_only": name_only,
                 "borrowed_from": borrowed_from, "guard": guard,
                 "merged": merged, "versions": versions,
                 "neutral_ce": neutral_ce, "header_mark": header_mark,
                 "alternates": alternates, "modules": modules,
                 "lib_mark": lib_mark,
                 "variants": variants.get(entity["id"], [])})
        kinds = entity["kinds"] or []
        # Determine if this entity should be exported in DEF files
        # Standard check: kind is function or callback
        exportable = bool(kinds and kinds[0] in EXPORTABLE and
                          "::" not in entity["name"] and
                          "." not in entity["name"] and
                          " " not in entity["name"])
        # Heuristic: entities with unknown kind but library requirement
        # and function-like names (PascalCase, not all caps, no underscores)
        # AND a syntax declaration are likely functions that should be exported
        if not exportable and modules and not kinds and chosen:
            name = entity["name"]
            # Function-like: PascalCase, no underscores, not all caps
            # Exclude: interfaces (I*), all-caps constants, names with ::
            # Require: has a declaration (syntax)
            if (not name.startswith("I") and
                not name.isupper() and
                "_" not in name and
                "::" not in name and
                "." not in name and
                " " not in name and
                len(name) > 3 and
                name[0].isupper() and
                any(c.islower() for c in name) and
                # Additional check: declaration looks like a function
                # (has parentheses or starts with a type)
                (("(" in (chosen.get("text", "") or "")) or
                 (chosen.get("text", "") or "").lstrip().startswith(("WINAPI", "STDAPI", "HRESULT", "BOOL", "DWORD", "HANDLE", "void", "int", "LONG")))):
                exportable = True
        for stem, names in modules.items():
            worklist = by_module[stem]
            worklist["stated"] |= names
            if exportable and chosen:
                worklist["entries"].append(
                    {"entity": entity, "declaration": chosen,
                     "lib_mark": lib_mark, "guard": guard,
                     "merged": merged, "neutral_ce": neutral_ce,
                     "borrowed_from": borrowed_from})
        manifest.append((
            entity["id"], entity["name"], ";".join(kinds),
            entity.get("surface") or "",
            wce_range_comment(merged) if merged else "",
            ";".join(sorted(neutral_ce)),
            primary or "", ";".join(p for p, _s in alternates),
            ";".join(sorted(modules)),
            chosen["id"] if chosen else "", page_decl, borrowed_from,
            ";".join(v["name"] for v in variants.get(entity["id"], [])),
            header_mark, lib_mark))

    overlay_unified_surface(by_header, printed_forms, by_module, all_entities)

    # ---- constants: every numbered constant the CE documents quote,
    # filed under the header the linkage table names for it.  Entries are
    # collected structured; the fragment writer batches several constants
    # under ONE version guard (the old one-guard-per-constant output was
    # unreadable) and keeps one compact comment per constant instead of a
    # wall of repeated row quotes.
    const_rows = collections.defaultdict(dict)
    win32_shared = collections.defaultdict(dict)
    win32_only = collections.Counter()
    ce_documented = load_ce_documented_names()
    surfaces = {e["id"]: e.get("surface") for e in all_entities}

    def shared_surface_name(record):
        """A name of the CE surface: a CE page lists it, or the API it
        belongs to is one the CE documents (surface is not win32-only).
        Desktop-only feature areas stay out (Windows CE is not all of
        Win32)."""
        if record["name"] in ce_documented:
            return True
        surface = surfaces.get(record.get("page_entity") or "")
        return bool(surface) and surface != "win32-only"

    shared_values = 0
    for record in constants:
        if record.get("layer") == "ce":
            const_rows[record["name"]][record["id"]] = record
        else:
            win32_only[record["name"]] += 1
            # The Win32-shared half of the surface lives in this SAME
            # tree (round-3 model: wince固有部分 + w32共通部分 +
            # w32共通(ce固有値)部分).  A number the shared reference
            # prints may fill in a gap only for a name of the CE surface
            # -- never a desktop-only one -- and only when no CE page
            # numbers the name anywhere (a CE print always wins).  The
            # value is marked for SDK verification.
            if shared_surface_name(record):
                win32_shared[record["name"]][record["id"]] = record
    for name, records in win32_shared.items():
        if name in const_rows:
            continue
        const_rows[name] = records
        shared_values += 1
    unified_consts = load_unified_constants()
    apply_unified_constants(const_rows, unified_consts)
    bad_null = const_rows.get("NULL")
    if bad_null:
        vals = [str(r.get("value") or "").strip() for r in bad_null.values()]
        if not any(v in ("0", "0L", "0l", "NULL") for v in vals):
            const_rows.pop("NULL", None)
            unified_consts.pop("NULL", None)
    ce_named = load_ce_documented_names()
    already = set(const_rows)
    def _gap_into(name, rec, tag, origin, license_id):
        unified_consts[name] = rec
        source = rec.get("source") or {}
        const_rows[name] = {"gap": {
            "id": tag + ":" + name,
            "name": name,
            "value": rec["value"],
            "decimal": None,
            "origin": origin,
            "headers": [rec["header"]] if rec.get("header") else [],
            "layer": "ce",
            "row": f"{name} {rec['value']}",
            "license": license_id,
            "source": source if isinstance(source, dict) else {
                "path": tag, "set": tag,
                "layer": "reference", "title": name, "page_id": ""},
        }}

    for name, rec in w32api_gaps.parse_defines(ce_named, already).items():
        _gap_into(name, rec, "w32api", "w32api-cegcc-public-domain",
                  "w32api-public-domain")
        already.add(name)
    for name, rec in pinvoke_gaps.parse_constants(ce_named, already).items():
        _gap_into(name, rec, "pinvoke", "dotnet-pinvoke-mit",
                  "dotnet-pinvoke-mit")
        already.add(name)
    defines = conflicts = unsupported_written = no_header = 0
    conflicts_resolved = 0
    const_entries = collections.defaultdict(list)   # header lower -> [entry]
    for name in sorted(const_rows, key=str.lower):
        groups = constant_value_groups(list(const_rows[name].values()))
        unsupported = UNSUPPORTED.get(name) or []
        if not groups:
            continue
        if quality_filters.is_language_runtime_constant(name):
            no_header += 1
            continue
        if name in w32api_gaps.NEVER and name != "MAX_PATH":
            continue
        unified_rec = unified_consts.get(name) or {}
        if unified_rec.get("header"):
            targets = [{"header": unified_rec["header"],
                        "strength": "unified-kb",
                        "statements": 1,
                        "example_page": (unified_rec.get("source") or {}).get("path") or "-"}]
        else:
            targets = pick_constant_targets(name, links.get(name) or [])
        if not targets:
            no_header += 1
            printed_forms.setdefault("nostatedheader.h", "NoStatedHeader.h")
            targets = [{"header": "NoStatedHeader.h",
                        "strength": "no header stated by any page",
                        "statements": 0, "example_page": "-"}]
        conflict = groups_conflict(groups)
        if conflict:
            conflicts += 1
        taken_away = [row for row in unsupported if row["set"]]
        for target in targets:
            header = target["header"]
            const_entries[header.lower()].append({
                "name": name,
                "win32_value": all(
                    r.get("layer") != "ce"
                    for r in const_rows[name].values()),
                "strength": target["strength"] or "?",
                "statements": target.get("statements") or 1,
                "example_page": target.get("example_page") or "-",
                "other_headers": [h["header"] for h in targets
                                  if h["header"] != header],
                "groups": groups,
                "conflict": conflict,
                "review": conflict_rows.get(name) or {},
                "taken_away": taken_away,
            })

    # ---- extra macros / declarations from the corpus scan, quality-filtered
    # and filed by the shared header map.  Names already emitted from the
    # knowledge base are not duplicated.
    emitted_names = set()
    for key, entries in const_entries.items():
        for e in entries:
            emitted_names.add(e["name"])
    for key, infos in by_header.items():
        for info in infos:
            emitted_names.add(info["entity"]["name"])
    page_to_headers = collections.defaultdict(set)
    name_to_header = {}
    for ent in all_entities:
        hs = header_files(ent.get("headers") or [])
        if not hs:
            continue
        if ent.get("name"):
            name_to_header.setdefault(ent["name"], hs[0])
        for page in (ent.get("ce_pages") or []) + (ent.get("win32_pages") or []):
            for h in hs:
                page_to_headers[page].add(h)

    extra_macros_by_header = collections.defaultdict(list)
    extra_decls_by_header = collections.defaultdict(list)
    leftover_defines = []
    leftover_decls = []

    def _pick_header_for_extra(name, source, kinds=None):
        # Macros from sample pages must not ride a page's Header into an
        # API fragment.  The shared name map is the only extra-macro filing.
        if kinds and "macro" in kinds:
            if quality_filters.is_sample_source(source or ""):
                return None
            return header_map.header_for_entity(name, kinds)
        if quality_filters.is_sample_source(source or ""):
            return None
        mapped = header_map.header_for_entity(name, kinds or [])
        if mapped:
            return mapped
        headers = page_to_headers.get(source) or set()
        if headers:
            return sorted(headers, key=str.lower)[0]
        return None

    for d in extra_defines:
        name = d.get("name") or ""
        if name in emitted_names:
            continue
        if quality_filters.is_sample_source(d.get("source") or ""):
            continue
        if name.startswith(("IDC_", "IDI_")) and name not in header_map.EXACT_TO_HEADER:
            leftover_defines.append(d)
            continue
        hdr = _pick_header_for_extra(name, d.get("source") or "", ["macro"])
        if hdr and hdr.lower() in CE_CORE_HEADERS:
            leftover_defines.append(d)
            continue
        if hdr:
            printed_forms.setdefault(hdr.lower(), hdr)
            extra_macros_by_header[hdr.lower()].append(d)
            emitted_names.add(name)
        else:
            leftover_defines.append(d)

    for d in extra_declarations:
        name = d.get("name") or ""
        if name in emitted_names:
            continue
        if quality_filters.is_sample_source(d.get("source") or ""):
            continue
        hdr = _pick_header_for_extra(name, d.get("source") or "",
                                     [d.get("type") or ""])
        if not hdr:
            hdr = name_to_header.get(name)
        text = d.get("declaration") or ""
        keep = quality_filters.is_c_toolchain_declaration(
            text, name, d.get("type") or "") \
            and not quality_filters.decl_unusable_for_c(text, name)
        # Junk stays out of WinDef/Winuser.  Keepable C (MmMapIoSpace) may
        # fill a hole in a core header from harvest, not from a copied file.
        if hdr and hdr.lower() in CE_CORE_HEADERS | {"windows.h", "windowsapis.h"}:
            if keep and hdr.lower() in {"ceddk.h", "pkfuncs.h", "kfuncs.h"}:
                printed_forms.setdefault(hdr.lower(), hdr)
                extra_decls_by_header[hdr.lower()].append(d)
                emitted_names.add(name)
            else:
                leftover_decls.append(d)
            continue
        if hdr and keep:
            printed_forms.setdefault(hdr.lower(), hdr)
            extra_decls_by_header[hdr.lower()].append(d)
            emitted_names.add(name)
        else:
            leftover_decls.append(d)

    leftover_names = {d.get("name") for d in leftover_decls}
    for d in leftover_kb_decls:
        name = d.get("name") or ""
        if not name or name in emitted_names or name in leftover_names:
            continue
        leftover_decls.append(d)
        leftover_names.add(name)
        emitted_names.add(name)

    extra_keys = set(extra_macros_by_header) | set(extra_decls_by_header)

    out = os.path.abspath(args.out)
    os.makedirs(out, exist_ok=True)
    include_dir = os.path.join(out, "include")
    link_dir = os.path.join(out, "link")
    os.makedirs(include_dir, exist_ok=True)
    os.makedirs(link_dir, exist_ok=True)

    # ---- one fragment per header: constants first, then the
    # declarations.  The tree is single: no per-generation copies.
    # Constants that share one _WIN32_WCE guard are batched under one #if
    # region (sorted by guard, then name); the same for declarations --
    # one guard per line made the old fragments unreadable walls.
    header_files_written = 0

    def guard_sort_key(merged):
        return tuple((lo, hi) for lo, hi in (merged or ()))

    def open_guard(lines, guard, merged):
        if guard:
            lines.append(f"#if {guard}"
                         + (f" /* CE {wce_range_comment(merged)} */"
                            if merged else ""))

    def close_guard(lines, guard):
        if guard:
            lines.append("#endif /* _WIN32_WCE */")

    def short_evidence(text):
        """The long pinned-tarball paths, named briefly but exactly."""
        if text.startswith("sources/dotnet-pinvoke/"):
            return "the pinned dotnet/pinvoke snapshot (sources/dotnet-pinvoke/)"
        match = re.search(r"sources/(w32api-cegcc)/[^!]*!.*[/\\]"
                          r"([^/\\]+)$", text)
        if match:
            return f"w32api-cegcc reference {match.group(2)}"
        return text

    def const_note(entry, group, quote_cap=1):
        """Compact evidence comment for one constant."""
        name = entry["name"]
        strength = entry["strength"]
        # Short rank labels
        rank_labels = {
            "own-page": "ce",
            "entity-page": "entity",
            "constant-entity": "const",
            "win32-reference": "w32",
            "reference-header": "ref",
            "co-mention": "co",
            "heuristic-prefix": "prefix",
            "pinvoke-weak": "pinvoke",
        }
        label = rank_labels.get(strength, strength)
        
        # Build concise one-line comment
        meta = [label]
        if entry.get("win32_value"):
            meta.append("verify")
        if entry["other_headers"]:
            meta.append("+" + str(len(entry["other_headers"])))
        
        comment = f"/* {name} = {group['print']}  [{', '.join(meta)}] */"
        return [comment]

    global_fn_names = set()
    global_fn_from = {}
    for key in sorted(set(by_header) | set(const_entries) | extra_keys):
        display = safe_name(printed_forms.get(key) or key, ".h")
        def entry_sort(e):
            if e["conflict"] or len(e["groups"]) != 1:
                return (1, (), e["name"].lower())   # self-contained, batched last
            _g_guard, g_merged = wce_guard(e["groups"][0]["sets"])
            return (0,
                    guard_sort_key(g_merged) if g_merged else ((0, 0),),
                    e["name"].lower())

        entries = sorted(const_entries.get(key, []), key=entry_sort)
        decls = sorted(by_header.get(key, []),
                       key=lambda e: (guard_sort_key(e["merged"]),
                                      e["entity"]["name"].lower()))
        enum_members = set()
        for info_item in decls:
            decl = info_item.get("declaration") or {}
            text = decl.get("text") if isinstance(decl, dict) else ""
            if text and "enum" in text:
                enum_members.update(re.findall(
                    r"\b([A-Z][A-Za-z0-9_]*)\s*=", text))
        if enum_members:
            entries = [e for e in entries if e["name"] not in enum_members]
        if key.lower() in {
                "stdarg.h", "stdio.h", "stdlib.h", "string.h", "stddef.h",
                "ctype.h", "malloc.h", "memory.h", "assert.h", "time.h",
                "math.h", "setjmp.h", "signal.h", "locale.h", "errno.h",
                "limits.h", "float.h", "iso646.h", "wchar.h", "wctype.h"}:
            continue
        if not entries and not decls and not extra_macros_by_header.get(key) \
                and not extra_decls_by_header.get(key) \
                and not base_types_by_header.get(key.lower()):
            continue
        # A page whose syntax block prints `#define NAME <value>` already
        # carries the line verbatim below; the derived line adds nothing
        # but noise, so it is suppressed (marked in the constant comment).
        printed_defines = {}
        for info_item in decls:
            if info_item["declaration"] is None:
                continue
            for match in re.finditer(
                    r"(?m)^#define\s+([A-Za-z_]\w*)\s+(\S+)",
                    info_item["declaration"]["text"]):
                printed_defines.setdefault(
                    (match.group(1), re.sub(r"\s+", "",
                                            match.group(2))), True)

        guard_name = safe_name(printed_forms.get(key) or key, '.h').upper().replace('.', '_') + "_"
        n_consts = len(entries)
        n_decls = sum(1 for d in decls if d['declaration'] is not None)
        n_outlines = sum(1 for d in decls if d['declaration'] is None)
        n_base_types = len(base_types_by_header.get(key.lower(), []))
        n_extra_macros = len(extra_macros_by_header.get(key.lower(), []))
        n_extra_decls = len(extra_decls_by_header.get(key.lower(), []))
        lines = [
            f"/* {printed_forms.get(key) or key} -- Windows CE unified surface",
            " *",
            " * ONE tree for every CE generation.  Version differences use",
            " * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.",
            " * Win32-shared entries are marked 'win32-ref'.",
            " * Generated from wince-docs-corpus knowledge/ by",
            " * tools/gen-include-def.py --unified.",
            f" * {n_consts} constants, {n_decls} declarations, "
            f"{n_outlines} outlines, {n_base_types} base types, "
            f"{n_extra_macros} extra macros, {n_extra_decls} extra decls",
            " */",
            f"#ifndef _{guard_name}",
            f"#define _{guard_name}",
            "",
        ]
        if key.lower() == "windef.h":
            lines += [
                "#include <stddef.h>",
                "/* CE's Win32 API surface is Unicode (LPWSTR). */",
                "#ifndef UNICODE",
                "#define UNICODE",
                "#endif",
                "#ifndef _UNICODE",
                "#define _UNICODE",
                "#endif",
                "",
                "/* compiler surface: empty 16-bit keywords + SAL, GCC __int64.",
                " * These expand to nothing / long long.  Not copied from an SDK.",
                " * stdarg.h is ISO C (va_list on FormatMessage). */",
                "#include <stdarg.h>",
                "#ifndef CONST",
                "#define CONST const",
                "#endif",
                "#ifndef FAR",
                "#define FAR",
                "#endif",
                "#ifndef NEAR",
                "#define NEAR",
                "#endif",
                "#ifndef far",
                "#define far",
                "#endif",
                "#ifndef near",
                "#define near",
                "#endif",
                "#ifndef PASCAL",
                "#define PASCAL",
                "#endif",
                "#ifndef IN",
                "#define IN",
                "#endif",
                "#ifndef OUT",
                "#define OUT",
                "#endif",
                "#ifndef OPTIONAL",
                "#define OPTIONAL",
                "#endif",
                "#ifndef UNALIGNED",
                "#define UNALIGNED",
                "#endif",
                "#ifndef __nullterminated",
                "#define __nullterminated",
                "#endif",
                "#ifndef __nullnullterminated",
                "#define __nullnullterminated",
                "#endif",
                "#ifndef _MSC_VER",
                "#ifndef __int64",
                "#define __int64 long long",
                "#endif",
                "#ifndef __stdcall",
                "#define __stdcall",
                "#endif",
                "#ifndef __cdecl",
                "#define __cdecl",
                "#endif",
                "#ifndef _cdecl",
                "#define _cdecl",
                "#endif",
                "#ifndef __fastcall",
                "#define __fastcall",
                "#endif",
                "#ifndef __declspec",
                "#define __declspec(x)",
                "#endif",
                "#endif /* _MSC_VER */",
                "#ifndef WINAPI",
                "#define WINAPI __stdcall",
                "#endif",
                "#ifndef CALLBACK",
                "#define CALLBACK __stdcall",
                "#endif",
                "#ifndef APIENTRY",
                "#define APIENTRY WINAPI",
                "#endif",
                "#ifndef TEXT",
                "#define TEXT(s) L ## s",
                "#endif",
                "#ifndef __TEXT",
                "#define __TEXT(s) L ## s",
                "#endif",
                "#ifndef _T",
                "#define _T(s) TEXT(s)",
                "#endif",
                "",
            ]

        if entries:
            lines += ["", "/* " + "=" * 66,
                      " * constants (one evidence comment per #define; the",
                      " * #if of a batch covers every #define in it; values",
                      " * that differ per generation pool into #if/#elif",
                      " * chains with the evidence after the #endif)",
                      " * " + "=" * 64 + " */"]
            # Non-conflicting multi-value constants whose branch guards
            # are identical are pooled into one shared #if/#elif chain
            # after the plain batches; conflicts stay self-contained.
            chain_members = collections.defaultdict(list)
            main_entries = []
            for cand in entries:
                if not cand["conflict"] and len(cand["groups"]) > 1:
                    chain_members[tuple(
                        wce_guard(group["sets"])[0] or "(undecided)"
                        for group in cand["groups"])].append(cand)
                else:
                    main_entries.append(cand)
            open_guard_now = None
            for entry in main_entries:
                if entry["conflict"]:
                    # self-contained block: the pages do not agree on the
                    # number.  A reviewed resolution (kb/constant-conflicts.tsv)
                    # writes the reviewed print below the block; without one
                    # no #define is written.
                    if open_guard_now is not None:
                        close_guard(lines, open_guard_now)
                        open_guard_now = None
                    lines.append("")
                    lines.append(f"/* {entry['name']} | CONFLICT")
                    for group in entry["groups"]:
                        g_merged = group["merged"]
                        rc = wce_range_comment(g_merged) if g_merged \
                            else "version not established"
                        lines.append(f" *   {group['print']}  in CE "
                                     f"{rc} ({len(group['rows'])} row(s))")
                    review = entry.get("review") or {}
                    if review.get("verdict"):
                        tag = review.get("reviewed_category") or "reviewed"
                        lines.extend(wrap_comment(
                            " * reviewed [" + tag + "]: ",
                            review["verdict"]))
                    resolved = re.sub(
                        r"\s+", "", (review.get("resolved_value") or ""))
                    picked = [g for g in entry["groups"]
                              if re.sub(r"\s+", "", g["print"]) == resolved] \
                        if resolved else []
                    if picked:
                        group = picked[0]
                        union = set()
                        for g in entry["groups"]:
                            union |= g["sets"]
                        g_guard, g_merged = wce_guard(union)
                        lines.append(
                            " * resolution: #define " + entry["name"] + " " +
                            group["print"] + " -- the reviewed print, one "
                            "the pages themselves state")
                        lines.append(" */")
                        lines.append("")
                        open_guard(lines, g_guard, g_merged)
                        lines.append(f"#define {entry['name']} "
                                     f"{group['print']}")
                        defines += 1
                        conflicts_resolved += 1
                        close_guard(lines, g_guard)
                        continue
                    lines.append(" * the pages do not agree on the "
                                 "number -- no #define is written */")
                    continue
                group = entry["groups"][0]
                g_guard, g_merged = wce_guard(group["sets"])
                if g_guard != open_guard_now:
                    if open_guard_now is not None:
                        close_guard(lines, open_guard_now)
                    if not args.minimal_comments:
                        lines.append("")
                    open_guard(lines, g_guard, g_merged)
                    open_guard_now = g_guard
                if not args.minimal_comments:
                    lines.append("")
                for row in entry["taken_away"]:
                    lines.append(f"/* NOT SUPPORTED per {row['set']}: "
                                 f"{row['statement']} [{row['page']}] */")
                    unsupported_written += 1
                printed = (entry["name"],
                           re.sub(r"\s+", "", group["print"])) in \
                    printed_defines
                if printed:
                    continue
                if entry["name"] == "NULL" and str(group["print"]).strip() not in (
                        "0", "0L", "0l", "NULL"):
                    continue
                if str(group["print"]).count('"') % 2 != 0:
                    continue
                if not args.no_const_comments:
                    lines.extend(const_note(entry, group))
                if entry["name"] == "NULL":
                    lines.append("#ifndef NULL")
                    lines.append(f"#define NULL {group['print']}")
                    lines.append("#endif")
                else:
                    lines.append(f"#define {entry['name']} {group['print']}")
                defines += 1
            if open_guard_now is not None:
                close_guard(lines, open_guard_now)
            for chain in sorted(chain_members, key=lambda c: (len(c), c)):
                members = sorted(chain_members[chain],
                                 key=lambda e: e["name"].lower())
                lines.append("")
                lines.append("/* " + "=" * 66)
                lines.append(f" * {len(members)} constant(s) share the "
                             "branch structure below: every name gets one")
                lines.append(" * #define per branch; per-name evidence "
                             "follows the #endif.")
                lines.append(" * " + "=" * 62 + " */")
                for gi in range(len(chain)):
                    cond = chain[gi]
                    if cond == "(undecided)":
                        cond = "(/* versions below undecided */ 1)"
                    lines.append(("#if " if gi == 0 else "#elif ") + cond)
                    for e in members:
                        lines.append(
                            "#define %s %s"
                            % (e["name"], e["groups"][gi]["print"]))
                lines.append("#else")
                lines.append("/* this configuration documents none of the "
                             f"{len(members)} name(s) above */")
                lines.append("#endif")
                lines.append("/* per-name evidence:")
                for e in members:
                    bits = "; ".join(
                        "%r: %d row(s) e.g. %s"
                        % (g["print"], len(g["rows"]),
                           min((rv[1] for rv in g["rows"]), key=len))
                        for g in e["groups"])
                    lines.append(" *   %s -- %s [linkage: %s]"
                                 % (e["name"], bits, e["strength"]))
                lines.append(" */")
                defines += len(members)
        # Base types section: typedef definitions for fundamental Windows types
        # These are critical for CE development as some have CE-specific values
        visible_macros = {e["name"] for e in const_entries.get("windef.h", [])}
        visible_macros.update(e["name"] for e in const_entries.get(key.lower(), []))
        emitted_type_names = set()
        base_types_for_header = base_types_by_header.get(key.lower(), [])
        if base_types_for_header:
            lines.append("")
            lines.append("/* " + "=" * 66)
            lines.append(" * base types -- fundamental Windows type definitions")
            lines.append(" * CE-specific types are marked; verify sizes for your platform")
            lines.append(" * " + "=" * 64 + " */")
            for bt in order_base_types(base_types_for_header):
                tname = bt["type"]
                if tname in emitted_type_names:
                    continue
                emitted_type_names.add(tname)
                lines.append("")
                ce_mark = " [CE-SPECIFIC]" if bt["ce_specific"] == "yes" else ""
                lines.append(f"/* {bt['type']}{ce_mark}")
                if bt["ce_note"]:
                    lines.append(f" * {bt['ce_note']}")
                if bt["ce_value_note"]:
                    lines.append(f" * {bt['ce_value_note']}")
                defn = bt["definition"]
                if tname in _CE_PTR_TYPES:
                    defn = _CE_PTR_TYPES[tname]
                    lines.append(" * CE is 32-bit: pointer-sized integer")
                lines.append(f" * source: {bt['source']} */")
                defn_lines = defn.split("\\n")
                for defn_line in defn_lines:
                    lines.append(defn_line)
        # Extra macros filed into this header (quality-filtered, not
        # already numbered as constants above).  Object-like first, then
        # function-like, so the two kinds are not mixed.
        extra_macs = extra_macros_by_header.get(key.lower(), [])
        if extra_macs:
            obj_macros = [d for d in extra_macs if d.get("type") != "function-like"]
            func_macros = [d for d in extra_macs if d.get("type") == "function-like"]
            lines.append("")
            lines.append("/* " + "=" * 66)
            lines.append(" * macros -- supplementary #define from CE pages")
            lines.append(" * " + "=" * 64 + " */")
            for d in sorted(obj_macros, key=lambda x: x["name"]):
                lines.append(d["definition"])
            if func_macros:
                if obj_macros:
                    lines.append("")
                for d in sorted(func_macros, key=lambda x: x["name"]):
                    lines.append(d["definition"])
        # The declarations, in reading order: the macro blocks the pages
        # print (verbatim #define / macro syntax), then the types (structs,
        # enums, typedefs, interfaces, and the derived member outlines for
        # structures whose body no page prints), then the functions and
        # callbacks.  Macros and constants used to be one undifferentiated
        # wall; the sections keep each kind together.  Within a section
        # the same batching rule applies: one _WIN32_WCE guard per batch,
        # never one guard per line.
        def decl_bucket(info):
            if info.get("name_only"):
                return "macros"
            if info["declaration"] is None:
                return "types"          # derived member outline
            kinds = set(info["entity"]["kinds"] or [])
            text = info["declaration"].get("text") or ""
            if text.lstrip().startswith("#") or "macro" in kinds:
                return "macros"
            if kinds & {"struct", "enum", "interface"} or \
                    re.match(r"(?s)\s*(typedef|struct|enum|union|interface)"
                             r"\b", text):
                return "types"
            return "functions"

        sections = (
            ("macros", "macros -- the macro/#define blocks the pages print "
                       "(verbatim)"),
            ("types", "types -- structures, enumerations and typedefs; the "
                      "member outlines marked DERIVED below document a "
                      "structure whose declaration body no page prints"),
            ("functions", "functions and callbacks"),
        )
        buckets = collections.defaultdict(list)
        for info in decls:
            buckets[decl_bucket(info)].append(info)
        extra_type_ds = []
        already_decl_pre = {
            (info.get("entity") or {}).get("name") for info in decls
        }
        already_decl_pre.discard(None)
        for d in extra_decls_by_header.get(key.lower(), []):
            name = d.get("name") or ""
            kind = d.get("type") or "function"
            text = (d.get("declaration") or "").replace("\\n", "\n")
            if not name or name in already_decl_pre:
                continue
            if name.startswith("LP") and name[2:] in already_decl_pre:
                continue
            if name.startswith("P") and name[1:] in already_decl_pre:
                continue
            if kind not in ("typedef", "enum", "struct"):
                continue
            if not quality_filters.is_c_toolchain_declaration(text, name, kind):
                continue
            if quality_filters.decl_unusable_for_c(text, name):
                continue
            if type_mentions_unknown(text, set(_C_KNOWN_TYPES), name):
                continue
            extra_type_ds.append(d)
        open_decl_guard = None
        for bucket_key, bucket_title in sections:
            items = buckets.get(bucket_key) or []
            if bucket_key == "functions":
                local = set(emitted_type_names)
                local.update(n for n, _d in _CORE_TYPEDEFS)
                filtered, seen_fn = [], set()
                for info in items:
                    ename = (info.get("entity") or {}).get("name")
                    text = ((info.get("declaration") or {}).get("text") or "")
                    cname = (ename or "").lstrip("_")
                    if not (text or "").strip():
                        continue
                    if ename and ename in seen_fn:
                        continue
                    prev = global_fn_from.get(ename) or (
                        global_fn_from.get(cname) if cname else None)
                    if prev:
                        if prev in _APP_OVERLAY_HEADERS:
                            continue
                        if key.lower() not in _APP_OVERLAY_HEADERS:
                            continue
                    if type_mentions_unknown(text, local, ename, visible_macros):
                        continue
                    filtered.append(info)
                    if ename:
                        seen_fn.add(ename)
                        global_fn_names.add(ename)
                        global_fn_from[ename] = key.lower()
                        if cname:
                            global_fn_names.add(cname)
                            global_fn_from.setdefault(cname, key.lower())
                items = filtered
            if bucket_key == "types":
                items = order_type_infos(items)
                with_body, outlines = [], []
                for info in items:
                    decl = info.get("declaration") or {}
                    text = decl.get("text") if isinstance(decl, dict) else ""
                    if text and not quality_filters.is_broken_c(text):
                        with_body.append(info)
                    else:
                        outlines.append(info)
                kept = with_body
                while True:
                    local = {(i.get("entity") or {}).get("name")
                             for i in kept}
                    local.discard(None)
                    new = []
                    for info in kept:
                        text = ((info.get("declaration") or {}).get("text")
                                or "")
                        if type_mentions_unknown(text, local,
                                (info.get("entity") or {}).get("name"),
                                visible_macros):
                            continue
                        new.append(info)
                    if len(new) == len(kept):
                        break
                    kept = new
                items = kept + outlines
            if not items:
                continue
            if open_decl_guard is not None:
                close_guard(lines, open_decl_guard)
                open_decl_guard = None
            lines.append("")
            lines.append("/* " + "=" * 66)
            for piece in re.findall(r".{1,64}(?:\s|$)", bucket_title):
                lines.append(" * " + piece.rstrip())
            lines.append(" * " + "=" * 64 + " */")
            for info in items:
                entity = info["entity"]
                ename = entity.get("name")
                declaration = info["declaration"]
                _dt = declaration.get("text") if isinstance(declaration, dict) else ""
                if bucket_key == "macros" and _dt:
                    if _dt.lstrip().startswith("#define") and \
                            quality_filters.sanitize_define_line(_dt, ename) is None:
                        continue
                    if quality_filters.is_broken_c(_dt):
                        continue
                aliases = set()
                if ename:
                    aliases.add(ename)
                if _dt and "}" in _dt:
                    _tail_skip = {
                        "FAR", "NEAR", "CONST", "const", "volatile",
                        "struct", "union", "enum", "typedef", "WINAPI",
                        "CALLBACK", "STDCALL", "PASCAL",
                    }
                    aliases.update(
                        tok for tok in re.findall(
                            r"[A-Za-z_][A-Za-z0-9_]*",
                            _dt.rsplit("}", 1)[-1])
                        if tok not in _tail_skip)
                if aliases & emitted_type_names:
                    continue
                if key.lower() != "windef.h" and ename in {
                        n for n, _d in _CORE_TYPEDEFS}:
                    continue
                if bucket_key == "types" and aliases:
                    emitted_type_names.update(aliases)
                libs = ", ".join(
                    name for names in info["modules"].values()
                    for name in sorted(names)) or "-"
                if info["guard"] != open_decl_guard:
                    if open_decl_guard is not None:
                        close_guard(lines, open_decl_guard)
                    lines.append("")
                    open_guard(lines, info["guard"], info["merged"])
                    open_decl_guard = info["guard"]
                bits = [", ".join(entity["kinds"]) or "?",
                        entity.get("surface") or "?"]
                if info["merged"]:
                    bits.append("CE " + wce_range_comment(info["merged"]))
                if libs and libs != "-":
                    bits.append(libs)
                if info["header_mark"]:
                    bits.append(info["header_mark"])
                if info["lib_mark"]:
                    bits.append("lib:" + info["lib_mark"])
                bf = info["borrowed_from"] or ""
                if bf:
                    bits.append(bf.split("|")[0])
                variants = [v["name"] for v in info["variants"]]
                if variants:
                    bits.append("A/W " + ",".join(variants)
                                + " (CE is W-side)")
                head = ["", f"/* {entity['name']}  [{'; '.join(bits)}] */"]
                for item in (item for item in entity.get("unicode_only") or []
                             if item.get("scope") == "this-api"):
                    head.append(f"/* {item['text']} */")
                if declaration is not None:
                    txt = declaration["text"] or ""
                    if "(" in txt and not txt.rstrip().endswith(";"):
                        if re.search(r"\)\s*$", txt.rstrip()):
                            txt = txt.rstrip() + ";"
                    head.append(txt)
                    if bucket_key == "types" and ename:
                        body = declaration.get("text") or ""
                        if re.search(r"\btypedef\s+(struct|union|enum)\b", body) \
                                and re.search(r"\b" + re.escape(ename) + r"\s*;", body) \
                                and ("LP" + ename) not in body:
                            head.append(
                                f"typedef {ename} *P{ename}, *LP{ename};")
                elif info.get("name_only"):
                    pass  # comment above is the whole record
                else:
                    outline = info["outline"]
                    head.append("/* DERIVED member outline -- documented order,"
                                " types/offsets not stated */")
                    for member in outline:
                        head.append(f"/*   {member['field']} */")
                lines.extend(head)
            if bucket_key == "types" and extra_type_ds:
                if open_decl_guard is not None:
                    close_guard(lines, open_decl_guard)
                    open_decl_guard = None
                for d in extra_type_ds:
                    if d.get("name") in emitted_type_names:
                        continue
                    text = (d.get("declaration") or "").replace("\\n", "\n")
                    lines.append("")
                    lines.append(
                        f"/* {d.get('name')}  [extra {d.get('type')}] */")
                    lines.append(text)
                    if d.get("name"):
                        emitted_type_names.add(d.get("name"))
        if open_decl_guard is not None:
            close_guard(lines, open_decl_guard)
        # Extra declarations filed into this header (not already emitted).
        already_decl_names = emitted_type_names | {
            (info.get("entity") or {}).get("name") for info in decls
        }
        extra_ds = [
            d for d in extra_decls_by_header.get(key.lower(), [])
            if d.get("name") not in already_decl_names
            and (d.get("type") or "function") not in ("typedef", "enum", "struct")
            and quality_filters.is_c_toolchain_declaration(
                d.get("declaration") or "", d.get("name") or "",
                d.get("type") or "")
            and not quality_filters.decl_unusable_for_c(
                d.get("declaration") or "", d.get("name") or "")
            and not type_mentions_unknown(
                d.get("declaration") or "", already_decl_names,
                d.get("name") or "", visible_macros)
        ]
        if extra_ds:
            by_type = collections.defaultdict(list)
            for d in extra_ds:
                by_type[d.get("type") or "function"].append(d)
            lines.append("")
            lines.append("/* " + "=" * 66)
            lines.append(" * extra declarations -- corpus pages the main")
            lines.append(" * parser did not turn into an entity declaration")
            lines.append(" * " + "=" * 64 + " */")
            for decl_type in ("typedef", "enum", "struct", "callback",
                              "function"):
                group = by_type.get(decl_type) or []
                if not group:
                    continue
                lines.append("")
                lines.append(f"/* {decl_type} */")
                for d in sorted(group, key=lambda x: x.get("name") or ""):
                    text = d.get("declaration") or ""
                    if text:
                        lines.append(text)
        if key.lower() == "windef.h":
            lines += [
                "typedef RECT *PRECT, *LPRECT;",
                "typedef CONST RECT *LPCRECT;",
                "typedef POINT *PPOINT, *LPPOINT;",
                "typedef SIZE *PSIZE, *LPSIZE;",
            ]
        # Close the include guard
        lines.append("")
        lines.append(f"#endif /* _{guard_name} */")
        path = os.path.join(include_dir, display + ".h")
        _write_lines(path, lines)
        header_files_written += 1

    # ---- leftover extra defines: quality-filtered macros that still have
    # no header.  Assigned macros are already in their header fragments.
    leftover_defines = [
        d for d in leftover_defines
        if quality_filters.is_keepable_unassigned_macro(
            d.get("name") or "", d.get("value") or "",
            d.get("definition") or "")]
    unassigned_defines = leftover_defines
    if unassigned_defines:
        extra_path = os.path.join(include_dir, "ExtraDefines.h")
        if args.minimal_comments:
            extra_lines = [
                "/* ExtraDefines.h -- supplementary macro definitions",
                f" * {len(unassigned_defines)} unassigned macros",
                f" * ({sum(1 for d in unassigned_defines if d['type'] == 'function-like')} function-like, "
                f"{sum(1 for d in unassigned_defines if d['type'] == 'object-like')} object-like)",
                " */",
                "#ifndef _EXTRADEFINES_H_",
                "#define _EXTRADEFINES_H_",
                "",
            ]
        else:
            extra_lines = [
                "/* ExtraDefines.h -- supplementary macro definitions",
                " *",
                " * These #define macros were found in Windows CE corpus pages",
                " * by tools/extract-missing-defines.py.  They supplement the",
                " * macros already extracted by the main parser.",
                " *",
                " * These are the macros that could not be assigned to a specific",
                " * header.  Macros assigned to headers are in their respective",
                " * header fragments.",
                f" * {len(unassigned_defines)} unassigned macros",
                f" * ({sum(1 for d in unassigned_defines if d['type'] == 'function-like')} function-like, "
                f"{sum(1 for d in unassigned_defines if d['type'] == 'object-like')} object-like)",
                " */",
                "#ifndef _EXTRADEFINES_H_",
                "#define _EXTRADEFINES_H_",
                "",
            ]
        # Group by type
        func_macros = [d for d in unassigned_defines if d["type"] == "function-like"]
        obj_macros = [d for d in unassigned_defines if d["type"] == "object-like"]
        if obj_macros:
            if not args.minimal_comments:
                extra_lines.append("/* " + "=" * 66)
                extra_lines.append(" * object-like macros (simple #define NAME value)")
                extra_lines.append(" * " + "=" * 64 + " */")
            for d in sorted(obj_macros, key=lambda x: x["name"]):
                if not args.minimal_comments:
                    extra_lines.append(f"/* source: {d['source']} */")
                extra_lines.append(d["definition"])
                if not args.minimal_comments:
                    extra_lines.append("")
        if func_macros:
            if not args.minimal_comments:
                extra_lines.append("/* " + "=" * 66)
                extra_lines.append(" * function-like macros (#define NAME(args) ...)")
                extra_lines.append(" * " + "=" * 64 + " */")
            for d in sorted(func_macros, key=lambda x: x["name"]):
                if not args.minimal_comments:
                    extra_lines.append(f"/* source: {d['source']} */")
                extra_lines.append(d["definition"])
                if not args.minimal_comments:
                    extra_lines.append("")
        extra_lines.append("#endif /* _EXTRADEFINES_H_ */")
        _write_lines(extra_path, extra_lines)
        header_files_written += 1

    # ---- extra declarations: declarations found in CE corpus pages that
    # could not be assigned to a specific header.  These go to ExtraDeclarations.h.
    unassigned_declarations = leftover_decls
    if unassigned_declarations:
        extra_decl_path = os.path.join(include_dir, "ExtraDeclarations.h")
        extra_decl_lines = []
        if args.minimal_comments:
            extra_decl_lines = [
                "/* ExtraDeclarations.h -- declarations without header assignment",
                f" * {len(unassigned_declarations)} unassigned declarations",
                " */",
                "#ifndef _EXTRADECLARATIONS_H_",
                "#define _EXTRADECLARATIONS_H_",
                "",
            ]
        else:
            extra_decl_lines = [
                "/* ExtraDeclarations.h -- declarations without header assignment",
                " *",
                " * These declarations were found in Windows CE corpus pages",
                " * but could not be assigned to a specific header file.",
                " * They may belong to internal or undocumented headers.",
                " *",
                f" * {len(unassigned_declarations)} unassigned declarations",
                " */",
                "#ifndef _EXTRADECLARATIONS_H_",
                "#define _EXTRADECLARATIONS_H_",
                "",
            ]
        
        # Group by type
        by_type = collections.defaultdict(list)
        for decl in unassigned_declarations:
            dtype = decl.get('type', 'function')
            by_type[dtype].append(decl)
        
        # Output by type
        for dtype in sorted(by_type.keys()):
            decls = by_type[dtype]
            if not args.minimal_comments:
                extra_decl_lines.append(f"/* {len(decls)} {dtype}(s) */")
                extra_decl_lines.append("")
            
            for decl in decls:
                decl_text = decl.get('declaration', '').strip()
                if decl_text and quality_filters.is_c_toolchain_declaration(
                        decl_text, decl.get("name") or "", dtype):
                    extra_decl_lines.append(decl_text)
                    if not args.minimal_comments:
                        extra_decl_lines.append("")
        
        extra_decl_lines.append("#endif /* _EXTRADECLARATIONS_H_ */")
        _write_lines(extra_decl_path, extra_decl_lines)
        header_files_written += 1

    # Windows.h is the umbrella developers actually #include.
    _write_windows_umbrella(include_dir)

    # ---- module .def worklists (one per module, annotated per line: the
    # .def grammar itself has no version conditional).
    ordinal_rows = load_ordinal_rows()
    ord_map = load_ordinals()
    reference_exports = load_reference_exports()
    for stem, worklist in sorted(by_module.items()):
        entries = sorted(worklist["entries"],
                         key=lambda e: e["entity"]["name"].lower())
        if args.minimal_comments:
            ch = [f"; {stem} -- EXPORTS",
                  f"; {len(entries)} name(s)",
                  "EXPORTS"]
        else:
            ch = [f"; {stem} -- EXPORTS worklist for the whole of Windows CE",
                  "; (one tree across generations; see include/ for the rest).",
                  ";",
                  "; The version range of a line is a COMMENT -- the .def",
                  "; grammar has no conditionals: filter the line for the",
                  "; version you target with the range printed beside it.",
                  "; Names are the documented names, not the _Name@N",
                  "; decorated symbols the documentation does not print.",
                  ";",
                  f"; stated as: {', '.join(sorted(worklist['stated']))}",
                  f"; {len(entries)} name(s)", "EXPORTS"]
        known = {info["entity"]["name"].lower() for info in entries}
        leads = [(name, member) for name, member in
                 (reference_exports or {}).get(safe_name(stem).lower(), [])
                 if name.lower() not in known]
        for info in entries:
            entity = info["entity"]
            ordinal, ordinal_page = ord_map.get(
                (stem, entity["name"].lower()), ("", ""))
            name_field = (f"{entity['name']} @{ordinal}"
                          if ordinal else entity["name"])
            if args.minimal_comments:
                ch.append(f"    {name_field}")
            else:
                tag = ""
                if info["lib_mark"] == "win32-reference":
                    tag += " [module: Win32 reference only]"
                if info["borrowed_from"] == "win32-reference":
                    tag += " [declaration: Win32 reference]"
                ver = wce_range_comment(info["merged"]) if info["merged"] \
                    else "version not established"
                ch.append(f"    {name_field:32s}; "
                          f"{(entity['kinds'] or ['?'])[0]}  CE {ver}  "
                          f"{info['declaration']['source']['path']}{tag}"
                          + (f"  [ordinal printed by {ordinal_page}]"
                             if ordinal else ""))
        if leads and not args.minimal_comments:
            ch += [
                ";",
                f"; {len(leads)} undocumented reference-export lead(s) omitted",
                ";",
            ]
        _write_lines(os.path.join(link_dir, safe_name(stem) + ".def"), ch)

    # ---- export ordinals: the one family that prints them, across sets
    ordinal_files = ordinal_names = 0
    by_dll = collections.defaultdict(list)
    for row in ordinal_rows:
        by_dll[row["dll"]].append(row)
    for dll, items in sorted(by_dll.items()):
        stem_dll = safe_name(re.sub(r"(?i)\.(dll|lib|exe)$", "", dll))
        ch = [f"; {dll} -- exports as printed by the documentation",
              "; (unified across every CE set whose pages print the table)",
              "EXPORTS"]
        for row in sorted(items, key=lambda r: int(r["ordinal"])):
            ch.append(f"    {row['name'] + ' @' + row['ordinal']:32s}"
                      f"; {row['set']} {row['page']}")
        _write_lines(os.path.join(link_dir, stem_dll + ".ordinals.def"), ch)
        ordinal_files += 1
        ordinal_names += len(items)

    # ---- worklists and reports
    with open(os.path.join(out, "constants.tsv"), "w",
              encoding="utf-8") as fh:
        fh.write("name\tvalue\tsets\theader\tlink_strength\trow\tpage\n")
        for name in sorted(const_rows, key=str.lower):
            targets = links.get(name) or []
            link = (";".join(t["header"] for t in targets),
                    ";".join(t["strength"] or "?" for t in targets))
            for record in const_rows[name].values():
                fh.write("\t".join((
                    name, record["value"],
                    record["source"]["set"], link[0], link[1],
                    record["row"].replace("\t", " "),
                    record["source"]["path"])) + "\n")
        for name, _n in sorted(win32_only.items(), key=lambda kv: kv[0].lower()):
            fh.write("\t".join((name, "", "(Win32 reference pages only --"
                                " Windows CE values are never taken from"
                                " the desktop reference)", "", "")) + "\n")

    with open(os.path.join(out, "manifest.tsv"), "w", encoding="utf-8") as fh:
        fh.write("entity\tname\tkinds\tsurface\tversions\tneutral_sets\t"
                 "header_file\tother_headers\tmodules\tdeclaration\t"
                 "source_page\tborrowed_from\tvariant_spellings\t"
                 "header_from\tlibrary_from\n")
        for row in manifest:
            fh.write("\t".join(row) + "\n")

    outlines = sum(1 for items in by_header.values() for info in items
                   if info["declaration"] is None)
    report = _unified_report(
        args, entities, by_header, by_module, header_files_written,
        defines, conflicts, unsupported_written, no_header,
        ordinal_files, ordinal_names, borrowed, skipped, pages,
        links, pinvoke_apis, pinvoke_consts, win32_only,
        conflicts_resolved=conflicts_resolved, outlines=outlines,
        conflict_rows=conflict_rows, shared_values=shared_values)
    _write_lines(os.path.join(out, "report.md"), report)
    print(f"unified tree: {header_files_written:,} header fragments "
          f"({sum(len(v) for v in by_header.values()):,} declarations/"
          f"outlines, {defines:,} #define lines, {conflicts_resolved:,} "
          f"reviewed conflict resolution(s)), {len(by_module):,} module "
          f".def worklists, written to {out} (see report.md)")
    return 0


def _write_lines(path, lines):
    with open(path, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines) + "\n")


def _unified_report(args, entities, by_header, by_module, header_files,
                    defines, conflicts, unsupported_written, no_header,
                    ordinal_files, ordinal_names, borrowed, skipped, pages,
                    links, pinvoke_apis, pinvoke_consts, win32_only,
                    conflicts_resolved=0, outlines=0, conflict_rows=None,
                    shared_values=0):
    surfaces = collections.Counter(e.get("surface") for e in entities)
    strengths = collections.Counter()
    for name, targets in links.items():
        for target in targets:
            strengths[target.get("strength") or "?"] += 1
    lines = [
        "# Unified include/def surface -- report",
        "",
        "ONE tree for every Windows CE generation.  Per-generation trees are",
        "not written anywhere in this build: where generations differ, the",
        "tree carries a derived `_WIN32_WCE` branch (the version macro the",
        "documentation itself prints; the set -> interval wiring is",
        "documented in tools/gen-include-def.py and is derived structure,",
        "not a quotation).  The Win32-shared half of the surface lives in",
        "the SAME tree, marked 'Win32 reference' -- never a second tree.",
        "",
        "## What was generated",
        "",
        f"* entities in scope: **{len(entities):,}** (by surface: " +
        ", ".join(f"`{k}` {v:,}" for k, v in sorted(
            surfaces.items(), key=lambda kv: str(kv[0]))) + ")",
        f"* header fragments: **{header_files:,}** under `include/`, each",
        "  with its documented constants first, then the macros, the types",
        "  and the functions; quoted text is verbatim, the `#define`",
        "  keyword and the header/constant filing are derived and say so",
        f"* derived `#define` lines written: **{defines:,}**",
        f"* derived member outlines (structures whose body no page prints):",
        f"  **{outlines:,}** -- marked DERIVED in the fragment",
        f"* constants whose pages disagree / overlap: "
        f"**{len(conflict_rows or {}):,}** name(s) examined in "
        "`kb/constant-conflicts.tsv`",
        f"  ({conflicts:,} of them reach a header fragment in this build;",
        f"  **{conflicts_resolved:,}** resolved by the review in",
        "  `data/constant-value-review.tsv` to a print the pages themselves",
        "  state, the rest get no `#define` -- every one keeps its",
        "  CONFLICT block with the verdict)",
        f"* constants with no header linkage at all: **{no_header:,}**",
        "  (worklist only -- they stay in `constants.tsv`)",
        f"* module `.def` worklists: **{len(by_module):,}** under `link/`",
        "  (per-line version range is a comment; `.def` has no",
        "  conditionals)",
        f"* printed export ordinals: {ordinal_files} file(s),",
        f"  {ordinal_names} name(s)",
        f"* declarations taken from the Win32 reference because no CE page",
        f"  prints one: **{borrowed.get('win32-reference', 0):,}** -- every",
        "  one marked in the fragment and the manifest; CE and desktop",
        "  values are never assumed equal",
        f"* constants numbered only by the Win32 shared reference (and only",
        f"  for names a CE page documents): **{shared_values:,}** -- same",
        "  tree, every one marked 'verify against the CE SDK'; a number a",
        "  CE page prints always wins",
        f"* spacing-only repairs across CE generations: "
        f"**{borrowed.get('spacing', 0):,}**",
        f"* pages behind this output: {len(pages):,}",
        "",
        "## Constant/header linkage (kb/constant-headers.tsv)",
        "",
        "Ranks consumed by this build (best rank per name: the CE",
        "documentation always outranks the Win32 desktop reference, which",
        "outranks the co-mention evidence and the pinned reference",
        "headers, and everything outranks the pinvoke weak auxiliary",
        "hint):",
        "",
        "| rank | link rows |",
        "|------|----------:|",
    ]
    for rank in ("own-page", "entity-page", "constant-entity",
                 "win32-reference", "co-mention",
                 "reference-header",
                 "heuristic-prefix",
                 "pinvoke-weak"):
        lines.append(f"| {rank} | {strengths.get(rank, 0):,} |")
    lines += [
        "",
        "The reference-header ranks come from the pinned, licence-vetted",
        "public references under `sources/`: their header files *define*",
        "the name (the row quotes tarball!member), so they say which",
        "header the name sits in.  No value is ever taken from them --",
        "every `#define` number above is a CE documentation quotation.",
    ]
    lines += [
        "",
        "## The isolated weak-auxiliary pinvoke reference",
        "",
        f"* aux API rows: **{len(pinvoke_apis):,}**, aux constant rows:",
        f"  **{len(pinvoke_consts):,}** (`knowledge/aux/`, isolated from",
        "  the specification; accept paths: the pinned dotnet/pinvoke",
        "  snapshot under `sources/dotnet-pinvoke/` and, not yet harvested,",
        "  the user wiki under `corpus/pinvoke/`)",
        "* what they are used for: ONLY the weakest constant/header",
        "  linkage rank above, consumed so that the gap between official",
        "  documentation and community reference is reviewable;",
        f"  **{strengths.get('pinvoke-weak', 0):,}** linkage rows rest on",
        "  them directly, each loudly marked in its header comment, and",
        "  `reports/constant-pinvoke-review.tsv` compares every such",
        "  community value with the documented CE value",
        "* what they are never used for: no value ever comes from the",
        "  pinvoke material (values are CE-page quotations only), no",
        "  entity, no declaration, no requirement is minted from it, and",
        "  no pinvoke statement overrides a documented one",
        f"* Win32-only numbers seen but not used: **{len(win32_only):,}**",
        "  constants (CE and desktop values are not assumed to match)",
        "",
        "## The wall this generator keeps",
        "",
        f"* the corpus pages read by this generator: **{len(CORPUS_READS)}**",
        "  (the generator reads `knowledge/` only; see docs/clean-room.md)",
        "",
        "## What was skipped",
        "",
        "| reason | entities |",
        "|--------|----------|",
    ]
    for reason, count in skipped.most_common():
        lines.append(f"| {reason} | {count:,} |")
    lines += [
        "",
        "The skipped entities are the collection worklist, same as in the",
        "per-version build: `knowledge/reports/gaps.tsv` has the per-entity",
        "rows, and `constants.tsv` here lists every numbered constant whose",
        "header linkage is still missing.",
    ]
    return lines


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--set", dest="target",
                    help="corpus set to generate for (learn/windows-ce-5.0)")
    ap.add_argument("--unified", action="store_true",
                    help="generate ONE include/def tree for every Windows "
                         "CE version: no per-generation trees, the "
                         "differences are carried by #if defined(_WIN32_WCE) "
                         "branches, and the Win32 shared surface is part of "
                         "the same tree (marked)")
    ap.add_argument("--out", help="output directory (outside the repository)")
    ap.add_argument("--no-borrow", action="store_true",
                    help="do not use a declaration from another corpus set")
    ap.add_argument("--include-win32", action="store_true",
                    help="also emit entities the Win32 reference documents")
    ap.add_argument("--no-const-comments", action="store_true",
                    help="omit evidence comments for constants (cleaner output)")
    ap.add_argument("--minimal-comments", action="store_true",
                    help="minimize all comments (only keep essential section headers)")
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--list", action="store_true",
                    help="list the corpus sets and their entity counts")
    args = ap.parse_args()

    if args.list:
        counts = collections.Counter()
        for entity in load(ENTITIES):
            for book in entity["ce_sets"]:
                counts[book] += 1
        for book, count in sorted(counts.items()):
            print(f"{book:44s} {count:7,} entities")
        return 0

    # The default build is the unified one: ONE include/def tree for the
    # whole of Windows CE, version differences carried by _WIN32_WCE
    # branches, the Win32-shared half merged in the same tree.  The
    # per-generation build (--set) stays available for comparison, but
    # it is never the product.
    if args.unified or not args.target:
        if not args.out:
            ap.error("the unified build needs --out")
        args.minimal_comments = True
        args.no_const_comments = True
        return run_unified(args)
    if not args.out:
        ap.error("--set needs --out")

    declarations_of = {d["id"]: d for d in load(DECLARATIONS)}
    reqs_of = collections.defaultdict(list)
    for record in load(REQUIREMENTS):
        if record.get("entity"):
            reqs_of[record["entity"]].append(record)
    constants = list(load(CONSTANTS)) if os.path.exists(CONSTANTS) else []
    
    # Build a mapping of base names to their A/W variants
    all_entities = list(load(ENTITIES))
    base_to_variants = {}
    for e in all_entities:
        vo = e.get("variants_of")
        if vo and isinstance(vo, dict):
            base_name = vo.get("name")
            if base_name:
                if base_name not in base_to_variants:
                    base_to_variants[base_name] = []
                base_to_variants[base_name].append(e)
    
    # Filter entities: CE entities + their A/W variants
    entities = []
    for e in all_entities:
        if e.get("noise"):
            continue
        # Include if it's in the target CE set
        if args.target in e.get("ce_sets", []):
            entities.append(e)
        # Include if it's a Win32 entity with --include-win32
        elif args.include_win32 and e.get("win32_pages"):
            entities.append(e)
        # Include if it's an A/W variant of a CE entity
        elif e.get("surface") == "win32-spelling":
            vo = e.get("variants_of")
            if vo and isinstance(vo, dict):
                base_name = vo.get("name")
                # Check if the base name is a CE entity
                if base_name:
                    base_id = base_name.lower()
                    is_ce_base = any(
                        ce.get("id") == base_id or 
                        ce.get("name", "").lower() == base_id
                        for ce in all_entities
                        if args.target in ce.get("ce_sets", [])
                    )
                    if is_ce_base:
                        entities.append(e)
    
    if args.limit:
        entities = entities[:args.limit]

    by_header = collections.defaultdict(list)
    by_module = collections.defaultdict(
        lambda: {"entries": [], "stated": set()})
    manifest = []
    skipped = collections.Counter()
    borrowed = collections.Counter()
    pages = set()
    exports = 0
    # Names whose CE page states that only the Unicode form exists.  The A
    # spelling of such a name is documented by the Win32 reference only,
    # i.e. by the desktop, so it is not emitted for the device.  The CE
    # page's own sentence is the authority and is quoted in the output.
    unicode_only = {}
    for record in load(ENTITIES):
        stated = [item for item in record.get("unicode_only") or ()
                  if item.get("scope") == "this-api"]
        if stated:
            unicode_only[record["name"].lower()] = (stated[0]["text"],
                                                    stated[0]["page"])
    denied_ansi = 0

    for entity in sorted(entities, key=lambda e: e["name"].lower()):
        base = (entity.get("variants_of") or {}).get("name", "")
        if (entity.get("variants_of") or {}).get("kind") == "ansi" and \
                base.lower() in unicode_only:
            skipped["ANSI spelling denied by a CE page (Unicode only)"] += 1
            denied_ansi += 1
            continue
        CODE_SKIPPED.clear()
        chosen, alternatives, borrowed_from = choose_declarations(
            entity, declarations_of, args.target, not args.no_borrow)
        skipped.update(CODE_SKIPPED)
        declaration = chosen[0] if chosen else None
        if borrowed_from:
            borrowed[borrowed_from.split(":")[0]] += 1
            if borrowed_from.endswith("|spacing"):
                borrowed["spacing"] += 1
        for record in chosen + alternatives:
            pages.add(record["source"]["path"])

        header_groups, header_sets = grouped_keys(
            reqs_of.get(entity["id"], ()), ("header",), args.target)
        header_keys, header_from = choose_keys(
            header_groups, header_sets, not args.no_borrow)
        lib_groups, lib_sets = grouped_keys(
            reqs_of.get(entity["id"], ()), ("library", "dll"), args.target)
        lib_keys, library_from = choose_keys(
            lib_groups, lib_sets, not args.no_borrow)
        
        # DirectShow helper classes: infer Streams.h header
        if not header_keys and "::" in entity["name"]:
            class_name = entity["name"].split("::")[0]
            directshow_prefixes = (
                'CBase', 'CDirect', 'CAgg', 'CRenderer', 'CSource', 'CMsg',
                'CPull', 'COutput', 'CInput', 'CVideo', 'CAudio', 'CMedia',
                'CFilter', 'CPin', 'CAllocator', 'CProperty', 'CControl',
                'CAM', 'CAsync', 'CDispatch', 'CStream',
                'CTransform', 'CTransInPlace',
                'CAuto', 'CCrit', 'CEnum', 'CDisp',
                'CBasic', 'CFactory', 'CGeneric',
                'CGuid', 'CLoad', 'CMem', 'COA', 'CPos', 'CQueue', 'CRef',
                'CSystem', 'CUnknown',
            )
            if class_name.startswith(directshow_prefixes) or class_name == 'FOURCCMap':
                header_keys = ["Streams.h"]
                header_from = "inferred:directshow-helper"
        
        # DirectShow functions/types: infer Dshow.h header
        if not header_keys:
            name = entity["name"]
            directshow_patterns = (
                'AMGet', 'AMovie', 'AM_SAMPLE', 'AM_MEDIA',
                'EC_STREAM', 'IAMovie', 'IBaseFilter', 'IFilterGraph',
                'IFilterMapper', 'IMediaControl', 'IMediaEvent',
                'IMediaSeeking', 'IMediaPosition', 'IMediaFilter',
            )
            if any(pattern in name for pattern in directshow_patterns):
                header_keys = ["Dshow.h"]
                header_from = "inferred:directshow-api"
        
        # DirectShow event codes: infer Streams.h header
        if not header_keys and entity["name"].startswith("EC_"):
            header_keys = ["Streams.h"]
            header_from = "inferred:directshow-event"
        
        # Processor-specific macros: infer appropriate headers
        if not header_keys:
            name = entity["name"]
            if name.startswith("_SH3") or name.startswith("_SH4"):
                header_keys = ["Mipsintr.h"]
                header_from = "inferred:processor-macro"
            elif name.startswith("DDHAL_"):
                header_keys = ["Ddrawhal.h"]
                header_from = "inferred:ddhal-macro"
            elif name.startswith("DISK_IOCTL_"):
                header_keys = ["Diskio.h"]
                header_from = "inferred:diskio-ioctl"
        
        if header_from:
            borrowed["header " + header_from.split(":")[0]] += 1
        if library_from:
            borrowed["library " + library_from.split(":")[0]] += 1
        headers = header_files(header_keys)
        # A .lib and a .dll of the same stem are one module; a key that names
        # no file is a statement, not a worklist, and stays counted.
        stated_libs = [key for key in lib_keys if module_of(key)]
        modules, unstated = split_libraries(
            {"libraries": stated_libs, "dlls": []})
        unstated += sum(1 for key in lib_keys if not module_of(key))
        if not declaration:
            skipped["no declaration in the corpus"] += 1
        elif not header_keys:
            skipped["no header stated by a CE page of this version"
                    if args.no_borrow else
                    "no header stated"] += 1
        elif not headers:
            skipped["header value names no header file"] += 1
        else:
            for header in headers:
                by_header[header].append(
                    (entity, declaration, header_from, stated_libs,
                     borrowed_from))
        if unstated:
            skipped["library stated but naming no file"] += unstated

        # A C++/COM member (``Interface::Method``, ``MSMQMessage.Priority``)
        # is not an export: the page did not print that spelling as a linker
        # name.  Only the kinds a linker exports become EXPORTS lines.
        kinds = entity["kinds"] or []
        exportable = bool(kinds and kinds[0] in EXPORTABLE and
                          "::" not in entity["name"] and
                          "." not in entity["name"] and
                          " " not in entity["name"])
        for module, stated in modules.items():
            worklist = by_module[module]
            worklist["stated"] |= stated
            if not exportable:
                continue
            worklist["entries"].append((entity, declaration, library_from))
            exports += 1

        manifest.append((
            entity["id"], entity["name"], ";".join(kinds),
            entity.get("surface") or "", ";".join(headers),
            ";".join(sorted(modules)),
            ";".join(k for k in stated_libs if module_of(k)[1] == "dll"),
            ";".join(stated_libs),
            declaration["id"] if declaration else "",
            declaration["source"]["path"] if declaration else "",
            borrowed_from,
            ";".join(sorted(entity["ce_sets"])),
            header_from,
            library_from,
        ))

    out = os.path.abspath(args.out)
    if out == ROOT or out.startswith(ROOT + os.sep) and \
            os.path.relpath(out, ROOT).split(os.sep)[0] not in ("build",):
        print(f"note: writing into the repository ({args.out}); generated "
              "material belongs outside corpus/ and knowledge/", file=sys.stderr)
    os.makedirs(out, exist_ok=True)
    generated = {"set": args.target, "pages": len(pages)}
    include_dir = write_includes(out, by_header, generated)
    link_dir = write_defs(out, by_module, generated, load_ordinals(),
                          reference_exports=load_reference_exports())
    ordinal_files, ordinal_names = write_ordinal_defs(out, args.target)
    UNSUPPORTED.update(load_unsupported())
    constant_report = write_constants(out, constants, args.target,
                                      not args.no_borrow)

    with open(os.path.join(out, "manifest.tsv"), "w", encoding="utf-8") as fh:
        fh.write("entity\tname\tkinds\tsurface\theader_files\tmodules\t"
                 "dlls\tlibraries\tdeclaration\tsource_page\tborrowed_from"
                 "\tce_sets\theader_from\tlibrary_from\n")
        for row in manifest:
            fh.write("\t".join(row) + "\n")

    surfaces = collections.Counter(e.get("surface") for e in entities)
    report = [
        f"# Generation report -- {args.target}",
        "",
        "## Boundary: this is Windows CE, not Win32",
        "",
        "Windows CE is the CE-specific surface **plus** the part of Win32 that",
        "Windows CE documents share -- not the whole Win32 API.  Every entity",
        "below is documented by a Windows CE set (`ce_sets` contains the",
        "target); the Win32 reference is only ever *evidence* or a marked",
        "fallback:",
        "",
        f"* entities emitted by surface: " + ", ".join(
            f"`{k}` {v:,}" for k, v in sorted(surfaces.items(), key=lambda kv: str(kv[0]))),
        f"* declarations that come from a Win32 page: "
        f"**{borrowed.get('win32-reference', 0):,}** (marked in the fragment "
        "comments, the manifest and the `.def` worklists)",
        f"* a Win32-only name (a page the CE documents never claim) is never "
        "emitted, even with `--include-win32`: that flag only adds entries "
        "whose CE evidence exists",
        "",
        "## What was generated",
        "",
        f"* entities in scope: **{len(entities):,}**",
        f"* declarations written: "
        f"**{sum(len(v) for v in by_header.values()):,}** in "
        f"{len(by_header):,} header fragment(s) ({include_dir})",
        f"* ANSI spellings left out because a CE page states the device "
        f"supports only the Unicode version: **{denied_ansi:,}** "
        f"(`knowledge/kb/unicode-only.tsv` has the sentence; the Win32 "
        f"reference documents those `A` names for the desktop)",
        f"* export tables printed by this set's own pages: "
        f"**{ordinal_files:,}** DLL(s), **{ordinal_names:,}** name(s) with the "
        f"ordinal the page prints (`link/*.ordinals.def`).  Every other "
        f"`.def` line here has no ordinal, because no document gives it one",
        f"* declarations borrowed from another CE set: "
        f"**{borrowed.get('ce-set', 0):,}**"
        f"{' (borrowing switched off)' if args.no_borrow else ''}"
        f" -- **{borrowed.get('spacing', 0):,}** of them because this version's "
        "page lost the spaces between tokens and another CE page kept them, "
        "and the two texts are the same once whitespace is removed "
        "(quoted as that page printed them, not repaired)",
        f"* declarations taken from the Win32 reference instead (the CE pages "
        f"print none): **{borrowed.get('win32-reference', 0):,}** -- marked in "
        "the fragments, the manifest and here: the Win32 pages document the "
        "shared surface as desktop Windows, so each one must be checked "
        "against the CE SDK",
        f"* headers taken from another CE set, because this version's pages "
        f"state none: **{borrowed.get('header ce-set', 0):,}** (marked "
        "`header_from` in the manifest and in the fragment comment)",
        f"* headers taken from the Win32 reference, because no CE page states "
        f"one: **{borrowed.get('header win32-reference', 0):,}** -- a desktop "
        "header (`processthreadsapi.h`, `windows.h`) is never passed off as a "
        "Windows CE header",
        f"* libraries borrowed the same way: CE set "
        f"**{borrowed.get('library ce-set', 0):,}**, Win32 reference "
        f"**{borrowed.get('library win32-reference', 0):,}**",
        f"* EXPORTS worklists: {len(by_module):,} module file(s) in {link_dir}, "
        f"**{exports:,} export line(s)** "
        "(functions and callbacks only; structures, typedefs and C++ methods "
        "stay in the include material)",
        f"* numbered constants: **{constant_report['defines']:,}** derived "
        f"`#define` lines in {constant_report['headers']:,} "
        f"`*.h.constants` file(s), from **{constant_report['rows']:,}** "
        "table rows the pages print.  The `#define` keyword is not on the "
        "page; the row is quoted above each line.  "
        f"**{constant_report['conflicts']:,}** name(s) whose pages disagree "
        "on the number were not turned into a `#define`.  "
        f"**{constant_report['unsupported']:,}** `#define` line(s) are "
        f"commented out because a CE page lists the name as not supported "
        f"(the sentence is quoted above the line); "
        f"**{constant_report['no_header']:,}** rows name no header, so they "
        "stay in `constants.tsv` only.  A number stated only by the Win32 "
        "reference is not borrowed",
        f"* pages behind the output: {len(pages):,}",
        "",
        "## Rights behind the output",
        "",
        "Every declaration in this build comes from a page whose statement is",
        "recorded in `data/license-scopes.tsv`; the counts below are the",
        "scopes of those pages.  **Check before publishing an export**: a",
        "scope whose `redistribution` is not `yes` may not be republished",
        "(`tools/check-licenses.py`, `docs/LICENSING.md`).",
        "",
        "| scope | declarations written | may be published |",
        "|-------|---------------------:|------------------|",
    ]
    scopes = collections.Counter()
    for entries in by_header.values():
        for entry in entries:
            declaration = entry[1]
            for record in [declaration]:
                scopes[record.get("license") or "?"] += 1
    try:
        sys.path.insert(0, os.path.join(ROOT, "tools"))
        import license_scopes
        registry = license_scopes.Registry.load()
        permission_of = {}
        for row in registry.rows:
            permission_of.setdefault(row.scope, row.redistribution)
    except Exception:
        permission_of = {}
    for scope, count in scopes.most_common():
        report.append(f"| {scope} | {count:,} | "
                      f"{permission_of.get(scope, '?')} |")
    report += [
        "",
        "## The wall this generator keeps",
        "",
        "* the corpus pages read by this generator: "
        f"**{len(CORPUS_READS)}** (the generator reads `knowledge/` only; a "
        "corpus path is refused, see `docs/clean-room.md`)",
        "",
        "## What was skipped",
        "",
        "| reason | entities |",
        "|--------|----------|",
    ]
    for reason, count in skipped.most_common():
        report.append(f"| {reason} | {count:,} |")
    report += [
        "",
        "The skipped entities are the collection worklist: their pages exist,",
        "they simply do not state the declaration, the header or the library.",
        "`knowledge/reports/gaps.tsv` has the same list with one row per",
        "entity and the set each one should be collected from, and",
        "`knowledge/reports/filtered-values.tsv` lists the library/DLL values",
        "that name no file (they are statements about the API, not libraries).",
    ]
    with open(os.path.join(out, "report.md"), "w", encoding="utf-8") as fh:
        fh.write("\n".join(report) + "\n")

    print(f"entities {len(entities):,}  header fragments {len(by_header):,}  "
          f"module files {len(by_module):,}  export lines {exports:,}  "
          f"ordinal files {ordinal_files:,} ({ordinal_names:,} names)  "
          f"borrowed ce-set {borrowed.get('ce-set', 0):,} / win32 "
          f"{borrowed.get('win32-reference', 0):,}")
    print(f"written to {out} (see report.md)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
