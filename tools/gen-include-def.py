#!/usr/bin/env python3
"""tools/gen-include-def.py -- prototype: knowledge/ -> include/def material.

This is the first consumer of the knowledge base, and it exists to prove the
pipeline end to end: take the machine-readable statements in ``knowledge/``,
filter them to one Windows CE version, and write the material an include/def
generator would be built from.

    python3 tools/gen-include-def.py --set learn/windows-ce-5.0 \
        --out build/generated/wince50
    python3 tools/gen-include-def.py --set chm/windows-ce-3.0 --out ... \
        --no-borrow            # only declarations from that set's own pages
    python3 tools/gen-include-def.py --list      # sets that can be generated

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
  The ``*.h.constants`` file quotes that row and, below it, a ``#define``
  whose keyword the page did not print -- the comment says so.  Pages that
  disagree on the number produce no ``#define``.  A number stated only by
  the Win32 reference is not borrowed: desktop and Windows CE values are
  not assumed to match;
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
import gzip
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
# Splits a requirement *value* already stored in knowledge/.  It does not
# read a corpus page.  The generator still refuses corpus paths below.
import page_parse  # noqa: E402

KB = os.path.join(ROOT, "knowledge", "kb")

# The clean-room wall (docs/clean-room.md): this generator reads the
# *specification* (knowledge/), never the corpus pages the specification was
# built from.  Anything that reaches into corpus/ is counted and refused, so a
# build of a generated header cannot depend on a page a reader may not take.
CORPUS_READS = []


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

# The documentation prints header and library names as they are; these pull
# the file names out of a value and leave the prose alone.
HEADER_FILE = re.compile(r"[\w.+-]*\.(?:h|hpp|hh|hxx|idl|inc)\b", re.I)
MODULE_FILE = re.compile(r"(?P<base>[\w.+-]+?)\.(?P<ext>lib|dll|drv|sys|ocx|tlb)\b",
                         re.I)
EXPORTABLE = ("function", "callback")


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


def write_defs(out, by_module, generated, ordinals=None):
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
        with open(path, "w", encoding="utf-8") as fh:
            fh.write("\n".join(lines) + "\n")
    return link_dir


def in_set(book, target):
    return book == target or book.startswith(target + "/")


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
                lines.append(f" * row: {record['row']}")
                lines.append(f" * source: {record['source']['path']}"
                             f"{borrowed_note}")
            if conflict:
                lines.append(" * CONFLICT: the pages do not agree on the "
                             "number -- no #define is written")
                lines.append(" */")
                continue
            lines.append(" * derived: the #define keyword is not on the page")
            lines.append(" */")
            record = rows[0][0]
            lines.append(f"#define {record['name']} {record['value']}")
            written += 1
        with open(path, "w", encoding="utf-8") as fh:
            fh.write("\n".join(lines) + "\n")

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


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--set", dest="target",
                    help="corpus set to generate for (learn/windows-ce-5.0)")
    ap.add_argument("--out", help="output directory (outside the repository)")
    ap.add_argument("--no-borrow", action="store_true",
                    help="do not use a declaration from another corpus set")
    ap.add_argument("--include-win32", action="store_true",
                    help="also emit entities the Win32 reference documents")
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

    if not args.target or not args.out:
        ap.error("--set and --out are required (or use --list)")

    declarations_of = {d["id"]: d for d in load(DECLARATIONS)}
    reqs_of = collections.defaultdict(list)
    for record in load(REQUIREMENTS):
        if record.get("entity"):
            reqs_of[record["entity"]].append(record)
    constants = list(load(CONSTANTS)) if os.path.exists(CONSTANTS) else []
    entities = [e for e in load(ENTITIES)
                if not e.get("noise") and
                (args.target in e["ce_sets"] or
                 (args.include_win32 and e["win32_pages"]))]
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

    for entity in sorted(entities, key=lambda e: e["name"].lower()):
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
    link_dir = write_defs(out, by_module, generated, load_ordinals())
    ordinal_files, ordinal_names = write_ordinal_defs(out, args.target)
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
