#!/usr/bin/env python3
"""tools/build-kb.py -- build the knowledge base from the corpus.

The corpus (``corpus/``) holds the *documents*.  This tool turns them into the
*statements* a Windows CE include/def database can be built from, without
asking a model to guess anything: every fact is quoted from a page and carries
that page's path, id, set and title.

    python3 tools/build-kb.py                 # build knowledge/
    python3 tools/build-kb.py --report        # summarize, write nothing
    python3 tools/build-kb.py --tree learn/windows-ce-5.0   # one tree
    python3 tools/build-kb.py --workers 8

What it writes (all under ``knowledge/``, see knowledge/README.md and
knowledge/schema/):

    kb/entities.jsonl       one record per API name the corpus documents
                            (kinds, CE sets, pages, headers, libraries, DLLs,
                            counts, the ids of its evidence records)
    kb/declarations.jsonl   every C/C++ declaration/prototype/member block,
                            verbatim, with its source page and markup
    kb/requirements.jsonl   every Header/Library/DLL/OS-version statement
    kb/constraints.jsonl    sentences that state a Windows CE restriction
    kb/constants.jsonl      rows of a name/value table a page numbers
    kb/headers.tsv          header -> entities (the include mapping)
    kb/libraries.tsv        library -> entities (the link mapping)
    kb/dlls.tsv             DLL -> entities
    kb/sets.tsv             CE set -> entities, with coverage counts
    reports/coverage-by-tree.tsv   what each corpus tree contributed
    reports/coverage.tsv           per entity: what is known, what is missing
    reports/gaps.tsv               the actionable gaps (a list to collect for)
    reports/summary.md              the same in prose (English)

Rules

* No fabrication: a value only enters the knowledge base when a page in the
  corpus states it.  ``source`` is mandatory for every declaration,
  requirement and constraint record.
* No normalisation of C text: declarations are stored exactly as the page
  prints them (``spacing`` tells whether the page itself lost the spaces).
* Derived values (``kind``, ``spacing``, the ``field`` of a requirement) are
  documented in the schema as derived and carry their evidence.
"""

import argparse
import collections
import concurrent.futures
import datetime
import glob
import gzip
import hashlib
import io
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import ce_api_names  # noqa: E402
import header_map  # noqa: E402
import license_scopes  # noqa: E402
import page_parse  # noqa: E402

# The rights registry (data/license-scopes.tsv): every record is stamped with
# the scope of the page it came from, so a fact can never be read without its
# terms attached.  A page whose scope nobody has looked at is a build error
# (tools/check-licenses.py reports the same thing for the whole tree).
LICENSES = license_scopes.Registry.load()

ROOT = ce_api_names.ROOT
CORPUS = os.path.join(ROOT, "corpus")
INDEX = os.path.join(ROOT, "data", "index", "INDEX.tsv")
CATALOG_DIR = os.path.join(ROOT, "data", "catalogs")
WIN32_MAP = os.path.join(ROOT, "data", "reports", "win32-imported.tsv")
SHARED_MAP = os.path.join(ROOT, "data", "reports", "win32-shared.tsv")
CE_API_NAMES = os.path.join(ROOT, "data", "reports", "ce-api-names.tsv")
KNOWLEDGE = os.path.join(ROOT, "knowledge")
KB = os.path.join(KNOWLEDGE, "kb")
REPORTS = os.path.join(KNOWLEDGE, "reports")
# The isolated weak-auxiliary reference (pinvoke.net), deliberately NOT
# under kb/: it is not part of the specification the include/def surface
# is generated from, only weak evidence for judging linkages.
AUX = os.path.join(KNOWLEDGE, "aux")

TREE_LAYER = (
    ("corpus/win32/", "win32"),
    ("corpus/dotnet/", "dotnet"),
    # Official documentation of named open-source projects.  Not Microsoft's
    # statement, and not include/def material: parse_page records a quoted
    # note and does not mint an entity, a declaration or a constant from it.
    ("corpus/oss/", "oss"),
    # pinvoke.net P/Invoke signatures and constants for Win32 APIs
    ("corpus/pinvoke/", "pinvoke"),
)
PAPERWORK = {"README.md", "PROVENANCE.md"}


# ------------------------------------------------------------------- inputs

def read_index(only_tree=None):
    rows = []
    with open(INDEX, encoding="utf-8") as fh:
        for line in fh:
            if line.startswith("#") or not line.strip():
                continue
            parts = line.rstrip("\n").split("\t")
            if len(parts) < 4:
                continue
            page_id, book, path, title = parts[0], parts[1], parts[2], parts[3]
            if os.path.basename(path) in PAPERWORK:
                continue
            if only_tree and not path.startswith("corpus/" + only_tree):
                continue
            rows.append((page_id, book, path, title))
    return rows


def read_catalogs():
    """page id -> official name, from data/catalogs/*.tsv."""
    names = {}
    if not os.path.isdir(CATALOG_DIR):
        return names
    for fn in sorted(os.listdir(CATALOG_DIR)):
        if not fn.endswith(".tsv"):
            continue
        with open(os.path.join(CATALOG_DIR, fn), encoding="utf-8",
                  errors="replace") as fh:
            for line in fh:
                if line.startswith("#") or not line.strip():
                    continue
                parts = line.rstrip("\n").split("\t")
                if len(parts) >= 2 and parts[0] not in names:
                    names[parts[0]] = parts[1]
    return names


def read_win32_map():
    """corpus path -> (module, kind, name, ce_sets, ce_page_ids)."""
    out = {}
    if not os.path.isfile(WIN32_MAP):
        return out
    with open(WIN32_MAP, encoding="utf-8") as fh:
        next(fh, None)
        for line in fh:
            parts = line.rstrip("\n").split("\t")
            if len(parts) == 6:
                out[parts[0]] = (parts[1], parts[2], parts[3],
                                 parts[4].split(";"), parts[5].split(";"))
    return out


NAME_SHAPE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")


def read_ce_api_names():
    """normalized name -> (catalog/corpus label, the CE page ids for it).

    ``data/reports/ce-api-names.tsv`` is the list the Win32 import is derived
    from (``tools/build-ce-api-names.py``): a name comes from the official TOC
    export of a harvested CE set (``catalog``) or was mined from the pages of a
    CE set that has no catalog (``corpus``).
    """
    out = {}
    if not os.path.isfile(CE_API_NAMES):
        return out
    with open(CE_API_NAMES, encoding="utf-8") as fh:
        next(fh, None)
        for line in fh:
            parts = line.rstrip("\n").split("\t")
            if len(parts) >= 4:
                pages = [p for p in parts[2].split(";") if p]
                out[ce_api_names.normalize(parts[0])] = (parts[3], pages)
    return out


def read_shared_map():
    """win32 corpus path -> the shared names it was imported under.

    ``data/reports/win32-shared.tsv`` is the audit trail of the Win32 import
    rule: each row is a name Windows CE documents, with the sdk-api pages that
    were imported for it -- including the ``A``/``W`` spelling of the CE name
    (``CreateFileW`` for the CE name ``CreateFile``).  Reading it back is how a
    Win32 spelling page is linked to its CE base when the page itself prints no
    "Unicode and ANSI" statement.
    """
    out = collections.defaultdict(set)
    if not os.path.isfile(SHARED_MAP):
        return out
    with open(SHARED_MAP, encoding="utf-8") as fh:
        next(fh, None)
        for line in fh:
            parts = line.rstrip("\n").split("\t")
            if len(parts) == 4:
                for page in parts[3].split(";"):
                    if page:
                        out[page].add(parts[0])
    return out


def layer_of(book):
    page = "corpus/" + book
    for prefix, layer in TREE_LAYER:
        if page.startswith(prefix):
            return layer
    return "ce"


# ------------------------------------------------------------------- worker


def attach_name_rows(fact, rows):
    """A name|description table documents each name in its own row.

    The row becomes: an entity evidence item (quote = the row), the kind
    the row documents, the declaration the row quotes (a typedef body or
    a #define) and the header the row states -- each aimed at that one
    name (``for_name``), never at every name of the page.
    """
    if not rows:
        fact["name_rows"] = []
        return
    fact["name_rows"] = [{
        "name": row["name"], "description": row["description"],
        "table": row["table"], "row": row["row"],
    } for row in rows]
    also = fact.setdefault("also_documented", [])
    have = {item["id"] for item in also}
    for row in rows:
        entity = ce_api_names.entity_id(row["name"])
        kind = next((d["kind"] for d in row["declarations"] if d.get("kind")),
                    "typedef")
        if entity not in have:
            also.append({"id": entity, "name": row["name"], "row": row["row"],
                         "kind": kind})
            have.add(entity)
        fact["declarations"].extend(row["declarations"])
        for req in row["requirements"]:
            fact["requirements"].append(dict(req, for_name=row["name"]))


def parse_page(job):
    """One page -> its facts.  Runs in a worker process."""
    page_id, book, path, title = job
    layer = layer_of(book)
    fact = {"page_id": page_id, "book": book, "path": path, "title": title,
            "layer": layer, "entity": None, "entity_evidence": None,
            "display": None, "kind": None,
            "requirements": [], "declarations": [], "constraints": [],
            "documented_fields": [], "documented_fields_page": None,
            "abi_offsets": [], "constants": [], "module_facts": [],
            "export_ordinals": [], "def_rules": [], "unicode_only": [],
            "unsupported_constants": []}
    # An open-source documentation page is evidence of what that project
    # printed about Windows CE.  It is not a CE API page: no entity is minted
    # from the title, and a code sample on the page is not a declaration.
    # The quoted note is the page as this corpus reads it.
    if layer == "oss":
        full = os.path.join(ROOT, path)
        try:
            raw = open(full, "rb").read()
        except OSError:
            return fact
        fragment = page_parse.article_html(raw)
        fact["constraints"] = page_parse.oss_statements(fragment)
        return fact
    # pinvoke.net is a user-contributed P/Invoke wiki, NOT Microsoft
    # documentation.  By design (docs/COLLECTION-POLICY.md) it is an
    # *isolated* layer: its facts are kept as ``pinvoke`` evidence on the
    # fact record and are written to knowledge/aux/, never into the
    # entities/declarations/requirements/constants tables the include/def
    # surface is built from.  A pinvoke page mints no entity, no
    # declaration and no requirement; it only yields:
    #   * apis:      the name the page documents, the DLL its DllImport
    #                line names, and the header *inferred* from the module
    #                the page filed the name under (a weak, derived hint);
    #   * constants: the C# ``const``/``#define`` spellings the page prints.
    # Both are consumed as *weak auxiliary* evidence only -- for the
    # constant/header linkage where the official documentation states
    # nothing -- and are always labelled as such in output.
    if layer == "pinvoke":
        full = os.path.join(ROOT, path)
        try:
            raw = open(full, "rb").read()
        except OSError:
            return fact
        fragment = page_parse.article_html(raw)
        pinvoke = {"apis": [],
                   "constants": page_parse.pinvoke_constants(fragment)}
        module = page_id.split("/", 1)[0] if "/" in page_id else page_id
        dlls = [req["value"] for req in
                page_parse.pinvoke_requirements(fragment)]
        if "/" in page_id:
            func = page_id.split("/", 1)[1]
            if func and func != "index":
                pinvoke["apis"].append({
                    "name": func,
                    "module": module,
                    "dll": dlls[0] if dlls else "",
                    "header": page_parse.pinvoke_header_from_module(module),
                    "evidence": "pinvoke.net page " + page_id,
                })
        fact["pinvoke"] = pinvoke
        return fact
    full = os.path.join(ROOT, path)
    try:
        raw = open(full, "rb").read()
    except OSError:
        return fact
    name = os.path.basename(path)

    if name.endswith(".md"):
        text = page_parse.decode(raw)
        fields, reqs, decls, struct_fields = page_parse.markdown(text)
        # The title carries the public name in its own casing; the file name
        # is lower-case and the UID uses the C tag name for structures.
        title_name = page_parse.name_from_markdown_title(fields.get("title", ""))
        api = title_name or page_parse.name_from_filename(name)
        fact["display"] = api
        fact["entity"] = ce_api_names.normalize(api) if api else None
        fact["entity_evidence"] = ("sdk-api-title" if title_name else
                                   "sdk-api-filename" if api else None)
        fact["kind"] = page_parse.kind_from_filename(name)
        fact["requirements"] = reqs
        fact["declarations"] = decls
        # The same values as the HTML side: enum members and #define lines
        # quoted by the *syntax* blocks, and ``NAME (0x...)`` in prose.
        fact["constants"] = page_parse.syntax_constant_rows(decls) + \
            page_parse.prose_constants_text(text) + \
            page_parse.constant_tables_text(text) + \
            page_parse.define_line_constants(text)
        fact["constraints"] = [dict(note, kind="abi-note")
                               for note in page_parse.abi_notes(text)]
        # sdk-api documents every member of a structure under -struct-fields,
        # sometimes without printing a syntax block; that member list is a
        # documented fact (member names and order, no offsets), so it is kept.
        fact["documented_fields"] = [f["name"] for f in struct_fields]
        fact["documented_fields_page"] = path if struct_fields else None
        # A page like "Windows Data Types" documents its names in one
        # name|description table, each row carrying the typedef body and
        # the header statement ("This type is declared in WinNT.h ...").
        attach_name_rows(fact, page_parse.listed_type_rows_text(text))
        # Constants the page documents but does not number (flag and
        # style name lists): one tuple per row, value left absent.
        fact["constant_names"] = page_parse.constant_name_rows_text(text)
        fact["front_matter"] = {k: v for k, v in fields.items()
                                if k in ("title", "UID", "ms.date",
                                         "req.header", "req.lib", "req.dll")}
        return fact

    fragment = page_parse.article_html(raw)
    display = None
    evidence = None
    catalog_hit = CATALOGS.get(page_id)
    title_name = page_parse.name_from_title(title)
    if catalog_hit and page_parse.name_from_title(catalog_hit):
        display = page_parse.name_from_title(catalog_hit)
        evidence = "catalog"
    elif title_name:
        display = title_name
        evidence = "page-title"
    fact["display"] = display
    fact["entity"] = ce_api_names.normalize(display) if display else None
    fact["entity_evidence"] = evidence
    fact["requirements"] = page_parse.requirements(fragment)
    # A component page that lists functions and states their header and link
    # library.  Attached to those function entities after they exist, not to
    # the component title.  A misspelled cell is not rewritten.
    fact["listed_requirements"] = page_parse.listed_function_requirements(
        fragment)
    fact["declarations"] = page_parse.declarations(fragment, page_title=title)
    # ``abort Method (DOMDocument)`` is not a single identifier, so the title
    # parser leaves it without an entity.  When the page also prints a
    # C/C++ Syntax declaration, the title's own parent and member are the
    # name.  A title that does not print the parent stays unattached: the
    # declaration is quoted, and no interface is invented for it.
    if not fact["entity"]:
        # ``abort Method (DOMDocument)`` is attached only when a C/C++ Syntax
        # heading holds the declaration: a script-only page is not an entity.
        qualified = page_parse.interface_member_title(title)
        if qualified and any(
                d["role"] == "syntax" for d in fact["declarations"]):
            headings = [page_parse.text_of(m.group(0), keep_newlines=False)
                        .strip().lower()
                        for m in page_parse.HEADING.finditer(fragment)]
            if any(h in ("c/c++ syntax", "c/c++syntax") for h in headings):
                fact["display"] = qualified
                fact["entity"] = ce_api_names.normalize(qualified)
                fact["entity_evidence"] = "page-title"
    if not fact["entity"]:
        # ``ITimerService::CreateTimer Method`` prints the parent and the
        # member.  ``strcpy, wcscpy`` prints both names.
        # ``MSMQMessage.Priority`` prints both, with a dot.
        # ``IXRCollection<In_T, Out_T>::Insert`` prints both, including the
        # template arguments.  ``CComPtr::operator !`` prints the class and
        # the operator; the id keeps the operator, so ``!`` and ``*`` do not
        # collapse.  Attach a name only when a syntax block on the page
        # declares it.  A title that does not name the parent
        # (``absoluteChildNumber Method``) is not in this list, and no
        # interface is invented for it.
        named = [name for name in page_parse.documented_title_names(title)
                 if any(d["role"] == "syntax" and
                        page_parse.syntax_declares_name(name, d["text"])
                        for d in fact["declarations"])]
        if named:
            fact["display"] = named[0]
            fact["entity"] = ce_api_names.entity_id(named[0])
            fact["entity_evidence"] = "page-title"
            fact["also_documented"] = [
                {"id": ce_api_names.entity_id(name), "name": name}
                for name in named]
    if not fact["entity"] and fact.get("layer") == "ce":
        # ``IHTMLTableRowMetrics Interface`` is that interface.  The kind
        # word is the title template.  ``User Interface`` and ``Message
        # Function`` are not given an entity.  A .NET page is not a C name.
        kind_name = page_parse.kind_title_name(title)
        if kind_name:
            fact["display"] = kind_name
            fact["entity"] = ce_api_names.normalize(kind_name)
            fact["entity_evidence"] = "page-title"
    fact["constraints"] = [dict(item, kind="ce-restriction")
                           for item in page_parse.constraints(fragment)]
    # The CE 1.0 Books Online put the platform difference in one labelled
    # paragraph; most of it states no restriction *word*, so the
    # restriction-word reader never saw it.
    fact["constraints"] += [dict(note, kind="ce-note")
                            for note in page_parse.ce_notes(fragment)]
    fact["constraints"] += [dict(note, kind="abi-note")
                            for note in page_parse.abi_notes(
                                page_parse.text_of(fragment,
                                                   keep_newlines=False))]
    # A layout table (Offset | Field | Size | ...) is a documented ABI fact of
    # the page, quoted row by row (page_parse.offset_tables).  The sdk-api
    # markdown pages carry no such table (checked 2026-10-05), so this is the
    # HTML path only.
    fact["abi_offsets"] = page_parse.offset_tables(fragment)
    # A name/value table (Flag | Value | Description, Return code | Hexadecimal
    # | Decimal, ...) or a cell the page prints as ``NAME = 0x0001`` /
    # ``NAME (0x0001)`` is a numbered constant the page states.  Read only,
    # and only when the name is one identifier and the value one number.
    fact["constants"] = page_parse.constant_tables(fragment)
    # The same rule for the other two shapes a page numbers a constant in:
    # running prose (``WM_USER (0x0400)``) and the page's own *syntax*
    # declarations (``#define OEM_BLOCK_RESERVED 0x01``, an enum member
    # ``FWM_PRIVATE_HOST = 0x01,``).  Example code yields none of these
    # (page_parse.syntax_constant_rows).
    fact["constants"] += page_parse.prose_constants(fragment)
    # A name|description table ("Windows Data Types", structure lists):
    # the row name is a documented type, and the row may quote the typedef
    # body and state the header it lives in.  Read before the syntax
    # constants so a row-quoted #define counts too.
    attach_name_rows(fact, page_parse.listed_type_rows(fragment))
    # Constants the page documents but does not number (the Control
    # Styles mother table, `Value | Description` flag lists): one tuple
    # per row, value left absent -- never merged, never invented.
    fact["constant_names"] = page_parse.constant_name_rows(fragment)
    fact["constants"] += page_parse.syntax_constant_rows(fact["declarations"])
    fact["constants"] += page_parse.define_line_constants(fragment,
                                                        quote_stripped=True)
    # The one page family that prints export ordinals: ``Export | Ordinal``
    # for the floating point C run-time library.  A `.def` needs exactly
    # this (`name @ordinal`), and it exists nowhere else in the corpus, so
    # it is read where it does exist rather than assumed to be absent.
    fact["export_ordinals"] = page_parse.export_ordinal_tables(fragment)
    # What the documents state about .def files, EXPORTS, decoration and
    # ordinals -- the rules the generator has to obey, quoted.
    fact["def_rules"] = page_parse.def_rules(fragment)
    # "Windows CE supports only the Unicode version of this function."
    fact["unicode_only"] = (page_parse.unicode_support(fragment)
                            if fact["layer"] == "ce" else [])
    # "Windows CE does not support the following nIndex values: SM_ARRANGE..."
    fact["unsupported_constants"] = (page_parse.unsupported_constants(fragment)
                                     if fact["layer"] == "ce" else [])
    # A Windows CE *module* page states how the binary is composed: the
    # components of ``coredll``, the ``.lib`` each component is imported
    # from, and the header/library of the module's own functions.  This is
    # the only place the documents describe the module rather than the API,
    # so it is kept as its own table (kb/modules-ce.tsv), not folded into a
    # name's requirements.  Nothing is turned into a DLL name.
    if fact["layer"] == "ce":
        fact["module_facts"] = page_parse.module_facts(fragment,
                                                       page_title=title)
    kinds = collections.Counter(d["kind"] for d in fact["declarations"]
                                if d["role"] == "syntax" and d["kind"])
    if kinds:
        fact["kind"] = kinds.most_common(1)[0][0]
    return fact


# ------------------------------------------------------------------ records

VALUE_TAIL = re.compile(r"[\s.,;:]+$")


FILE_TOKEN = re.compile(r"[\w.+-]+\.(?:lib|dll|drv|sys|ocx|tlb)\b", re.I)
# A Header value is a file name too, and a page may state several
# ("Wilhelm.h, Otto.h"); a cell that names no header file at all (the OS
# version, a source file name, "Developer Implemented") keeps its requirement
# row but gets an empty key, so it never enters the header map.
HEADER_TOKEN = re.compile(r"[\w.+-]*\.(?:h|hpp|hh|hxx|idl|inc)\b", re.I)


def normalize_value(value, field=None):
    """DERIVED key for grouping a requirement value.

    The pages print the same header as ``Winbase.h``, ``Winbase.h.`` and
    ``winbase.h``; grouping needs one key, so trailing punctuation and
    whitespace are removed -- the verbatim ``value`` stays in the record, so
    nothing is invented and nothing is lost.

    For a library/DLL the key is the file name the value contains
    (``Iphlpapi.dll on Windows Server 2008`` -> ``Iphlpapi.dll``); a value that
    names no file at all (``Library: Developer Implemented``) gets an empty key
    -- it is a statement about the API, not a library, and it is listed in
    ``reports/filtered-values.tsv`` instead of entering the link map.
    """
    value = VALUE_TAIL.sub("", re.sub(r"\s+", " ", value)).strip()
    if field in ("library", "dll"):
        match = FILE_TOKEN.search(value)
        return match.group(0) if match else ""
    if field == "header" and not HEADER_TOKEN.search(value):
        return ""
    # ``Component: fsdbase`` is one identifier.  A template sentence in the
    # same cell is a statement, not a component name, and gets an empty key.
    if field == "component":
        return value if re.fullmatch(r"[A-Za-z][A-Za-z0-9_]*", value) else ""
    return value


def declaration_records(facts, entity_of):
    records = []
    for fact in facts:
        for decl in fact["declarations"]:
            key = hashlib.sha1(
                (fact["path"] + "\x00" + decl["text"]).encode("utf-8")
            ).hexdigest()[:12]
            records.append({
                "id": "d" + key,
                "entity": entity_of(fact),
                "page_id": fact["page_id"],
                "layer": fact["layer"],
                "kind": decl["kind"],
                "role": decl["role"],
                # The .NET tree documents managed classes: its signature blocks
                # are C#/VB/C++/JScript, so they say "managed" and are written
                # to their own file (they are not include/def material).
                "language": "managed" if fact["layer"] == "dotnet" else "c",
                "markup": decl["markup"],
                "spacing": decl["spacing"],
                "calling_convention": decl.get("calling_convention"),
                "text": decl["text"],
                "members": decl["members"],
                "member_types": decl.get("member_types", []),
                "abi_flags": decl.get("abi_flags", []),
                # a code block a page prints as a *sample*: kept as evidence,
                # never emitted as interface material (docs/clean-room.md)
                "implementation": bool(decl.get("implementation")),
                "license": license_of(fact["path"]),
                "source": source_of(fact),
            })
    records.sort(key=lambda r: (r["entity"] or "", r["source"]["path"], r["id"]))
    return records


def source_of(fact):
    return {"path": fact["path"], "page_id": fact["page_id"],
            "set": fact["book"], "title": fact["title"],
            "layer": fact["layer"],
            "license": license_of(fact["path"])}


def license_of(path):
    """The scope governing a path; a page outside every rule is an error."""
    scope = LICENSES.scope_for(path)
    if scope is None:
        raise SystemExit(f"{path}: no rule in data/license-scopes.tsv governs "
                         "this page -- add one before building")
    return scope


def attach_listed_functions(facts, entities, requirements):
    """Attach a component page's stated header and library to the listed names.

    The component title is not the function.  The assignment is stored only
    when that printed name is already an entity (its own page).  A cell the
    page misspelled is not corrected into a different entity, and it does not
    become a new one.  The source stays the component page.
    """
    by_id = {entity["id"]: entity for entity in entities}
    seen_ids = {record["id"] for record in requirements}
    attached = 0
    for fact in facts:
        for item in fact.get("listed_requirements") or []:
            entity_id = ce_api_names.entity_id(item["name"])
            entity = by_id.get(entity_id)
            if not entity:
                continue
            key = hashlib.sha1(
                (fact["path"] + "\x00" + item["name"] + "\x00" +
                 item["field"] + "\x00" + item["value"]).encode("utf-8")
            ).hexdigest()[:12]
            record = {
                "id": "r" + key,
                "entity": entity_id,
                "page_id": fact["page_id"],
                "layer": fact["layer"],
                "field": item["field"],
                "label": item["label"],
                "value": item["value"],
                "key": normalize_value(item["value"], item["field"]),
                "evidence": item["evidence"],
                "license": license_of(fact["path"]),
                "source": source_of(fact),
            }
            if not record["key"] or record["id"] in seen_ids:
                continue
            seen_ids.add(record["id"])
            requirements.append(record)
            if record["id"] not in entity["requirements"]:
                entity["requirements"].append(record["id"])
            slot = {"header": "headers", "library": "libraries",
                    "dll": "dlls"}.get(item["field"])
            if slot and record["key"] not in entity[slot]:
                entity[slot].append(record["key"])
                entity[slot].sort()
            # The component page is the requirement's source.  It is not added
            # to ce_pages: that list is the pages whose title is this name,
            # and inserting a component overview would reshuffle it.
            attached += 1
    if requirements:
        requirements.sort(key=lambda r: (r["entity"] or "", r["field"],
                                         r["source"]["path"], r["value"]))
    for entity in entities:
        entity["requirements"] = sorted(set(entity["requirements"]))
    return attached


def requirement_records(facts, entity_of):
    records = []
    for fact in facts:
        for req in fact["requirements"]:
            # a name-list row states its own header: the target name is part
            # of the identity, or every "declared in WinNT.h" row of one
            # page collapses into a single record
            key = hashlib.sha1(
                (fact["path"] + "\x00" + req["field"] + "\x00" +
                 req["value"] + "\x00" +
                 (req.get("for_name") or "")).encode("utf-8")).hexdigest()[:12]
            records.append({
                "id": "r" + key,
                "entity": (ce_api_names.entity_id(req["for_name"])
                           if req.get("for_name") else entity_of(fact)),
                "page_id": fact["page_id"],
                "layer": fact["layer"],
                "field": req["field"],
                "label": req["label"],
                "value": req["value"],
                "key": normalize_value(req["value"], req["field"]),
                "evidence": req["evidence"],
                "for_name": req.get("for_name"),
                "license": license_of(fact["path"]),
                "source": source_of(fact),
            })
    records.sort(key=lambda r: (r["entity"] or "", r["field"],
                                r["source"]["path"], r["value"]))
    return records


def constraint_records(facts, entity_of):
    records = []
    for fact in facts:
        for item in fact["constraints"]:
            kind = item.get("kind") or "ce-restriction"
            key = hashlib.sha1(
                (kind + "\x00" + fact["path"] + "\x00" +
                 item["text"]).encode("utf-8")).hexdigest()[:12]
            records.append({
                "id": "c" + key,
                "entity": entity_of(fact),
                "page_id": fact["page_id"],
                "layer": fact["layer"],
                "kind": kind,
                "pattern": item["pattern"],
                "text": item["text"],
                "license": license_of(fact["path"]),
                "source": source_of(fact),
            })
    records.sort(key=lambda r: (r["entity"] or "", r["source"]["path"], r["id"]))
    return records


def abi_offset_records(facts, entity_of):
    """One record per row of a documented layout table (offset + field).

    The row is quoted as printed; ``offset`` is derived from the offset cell and
    ``matches_declared_member`` says whether the name is one the same page
    declares in a syntax block.  Nothing is inferred: a member the page gives no
    offset for has no record, and a row whose offset cell is not a number is
    dropped (it is still on the page for a reader).
    """
    records = []
    for fact in facts:
        declared = set()
        for decl in fact["declarations"]:
            if decl["role"] != "syntax":
                continue
            for member in decl.get("members") or []:
                _type, name = page_parse.member_parts(member)
                if name:
                    declared.add(name.lower())
        for item in fact.get("abi_offsets") or []:
            key = hashlib.sha1(
                (fact["path"] + "\x00" + item["row"]).encode("utf-8")
            ).hexdigest()[:12]
            records.append({
                "id": "o" + key,
                "entity": entity_of(fact),
                "page_id": fact["page_id"],
                "layer": fact["layer"],
                "member": item["member"],
                "offset": item["offset"],
                "offset_printed": item["offset_printed"],
                "size": item["size"],
                "size_unit": item["size_unit"],
                "size_printed": item["size_printed"],
                "matches_declared_member": re.sub(
                    r"\[[^\]]*\]$", "", item["member"]).strip().lower()
                in declared,
                "table": item["table"],
                "row": item["row"],
                "license": license_of(fact["path"]),
                "source": source_of(fact),
            })
    records.sort(key=lambda r: (r["entity"] or "", r["source"]["path"],
                                r["offset"], r["member"].lower()))
    return records


def constant_records(facts, entity_of):
    """One record per row of a name/value table a page prints.

    The row is quoted as printed.  ``value`` is the number cell (hexadecimal
    when the page prints one); ``decimal`` is set only when a decimal column
    prints a decimal beside it.  ``headers`` are the header files the *same
    page* states -- a constant is not assigned a header the page does not name.
    ``entity`` is the page's entity only when the constant's own name is that
    entity; a flag table on a function's page does not make the flag that
    function.
    """
    records = []
    for fact in facts:
        headers = []
        for req in fact.get("requirements") or []:
            if req.get("field") != "header":
                continue
            for match in HEADER_TOKEN.findall(req.get("value") or ""):
                if match not in headers:
                    headers.append(match)
        page_entity = entity_of(fact)
        for index, item in enumerate(fact.get("constants") or []):
            key = hashlib.sha1(
                (fact["path"] + "\x00" + item["table"] + "\x00" +
                 str(index) + "\x00" + item["row"]).encode("utf-8")
            ).hexdigest()[:12]
            own = ce_api_names.normalize(item["name"])
            value = re.sub(r"^0X", "0x", item["value"])
            records.append({
                "id": "k" + key,
                "name": item["name"],
                "value": value,
                "decimal": item.get("decimal"),
                # How the page numbers the constant: a name/value table row
                # ("table"), a one-cell ``NAME = 0x0001`` ("cell"), a
                # ``#define`` line of a syntax declaration ("define"), an
                # enum member of a syntax declaration ("enum"), or running
                # prose, ``NAME (0x0400)`` ("prose").
                "origin": item.get("origin") or "table",
                "headers": headers,
                "entity": own if own and own == page_entity else None,
                "page_entity": page_entity,
                "page_id": fact["page_id"],
                "layer": fact["layer"],
                "table": item["table"],
                "row": item["row"],
                "license": license_of(fact["path"]),
                "source": source_of(fact),
            })
    records.sort(key=lambda r: (r["source"]["path"], r["name"].lower(),
                                r["value"]))
    return records


def constant_conflict_rows(constants, review):
    """Every CE constant whose pages print more than one number, examined.

    A name the generations document at *different* numbers is a version
    branch, not a conflict (the generator writes an ``#if`` chain).  The
    rows here are the disagreements that a branch cannot explain: two
    numbers printed by one page (``same-page``), by one set
    (``same-set``), or by overlapping version intervals
    (``version-overlap``).  Each row carries the printed values, the
    pages behind each, and -- where ``data/constant-value-review.tsv``
    reviewed the case -- the category, the resolved value and the
    verdict.  Resolution never invents a number: the resolved value must
    be one the pages themselves print.
    """
    by_name = collections.defaultdict(list)
    for record in constants:
        if record.get("layer") != "ce":
            continue
        by_name[record["name"]].append(record)
    rows = []
    for name in sorted(by_name, key=str.lower):
        values = collections.defaultdict(lambda: {
            "pages": set(), "sets": set(), "printed": set()})
        for record in by_name[name]:
            number = value_number(record.get("value"))
            if number is None:
                continue
            slot = values[number]
            slot["printed"].add(record.get("value"))
            slot["pages"].add(record["source"]["path"])
            slot["sets"].add(record["source"]["set"])
        if len(values) < 2:
            continue
        same_page = any(
            len({value_number(r.get("value")) for r in by_name[name]
                 if r["source"]["path"] == page}) > 1
            for page in {r["source"]["path"] for r in by_name[name]})
        same_set = any(
            len({value_number(r.get("value")) for r in by_name[name]
                 if r["source"]["set"] == book}) > 1
            for book in {r["source"]["set"] for r in by_name[name]})
        # disjoint set families per number -> a version branch, skipped
        if not same_page and not same_set:
            set_families = [slot["sets"] for slot in values.values()]
            overlap = any(a & b for i, a in enumerate(set_families)
                          for b in set_families[i + 1:])
            if not overlap:
                continue
            category = "version-overlap"
        else:
            category = ("same-page" if same_page else "same-set")
        verdict_row = review.get(name) or {}
        resolved = (verdict_row.get("resolved_value") or "").strip()
        printed_all = {p for slot in values.values() for p in slot["printed"]}
        if resolved and resolved not in printed_all:
            resolved = ""      # a resolution must quote a printed form
        rows.append((
            name,
            ",".join(str(number) for number in sorted(values)),
            "|".join(sorted(printed_all)),
            category,
            verdict_row.get("category") or "",
            ";".join(sorted({p for slot in values.values()
                             for p in slot["pages"]})),
            ";".join(sorted({s for slot in values.values()
                             for s in slot["sets"]})),
            resolved,
            verdict_row.get("verdict") or ""))
    return rows


PINVOKE_AUX_README = """# `aux/` -- the isolated weak-auxiliary pinvoke material

The files here are **not** part of the specification in `kb/`: they are the
machine-readable residue of the **one third-party exception** in
`docs/COLLECTION-POLICY.md`, the pinvoke P/Invoke reference, and they are
kept strictly separate from the official-documentation knowledge base.
They are consumed as **weak auxiliary evidence only**: where Microsoft's own
pages state nothing about a constant's header, a pinvoke statement may
*hint* at the linkage (`strength: "pinvoke-weak"` in
`kb/constant-headers.tsv`) so the gap is visible and decisions can be
reviewed; it never overrides a documented statement, it is always labelled,
and the rules are in `data/license-scopes.tsv`.  A pinvoke value is never
treated as a Windows CE value and never written into a generated header:
the review report `reports/constant-pinvoke-review.tsv` compares each
community value with the documented CE one.

Two accept paths feed this directory, both isolated:

* `sources/dotnet-pinvoke/` -- the pinned, archived github.com/dotnet
  /pinvoke snapshot (MIT), parsed by `tools/pinvoke_extract.py` into
  constants (`public const`/`enum` member) and API (`[DllImport]`) rows.
  Each record quotes the verbatim `.cs` line with its archive member and
  line number; `header` is DERIVED from the module directory (the Windows
  library project the name is filed under -- a weak hint by design).
* `corpus/pinvoke/` -- the pinvoke.net user wiki, queue-gated by
  `queues/pinvoke-net.txt` (currently empty: not harvested).

| File | Contents |
|------|----------|
| `pinvoke-apis.jsonl.gz` | one row per API: `name`, `module`, `dll` (the DllImport text, when it names one), `header` (derived), `evidence`, `source` (archive member + line) |
| `pinvoke-constants.jsonl.gz` | one row per constant: `name`, `value` as printed, `value_eval` (best-effort fold, marked), `module`, `header` (derived), `table`, `row` (the quote), `source` |
| `pinvoke-apis.tsv` / `pinvoke-constants.tsv` | flat review views of the same rows |
"""


def pinvoke_records(facts):
    """The isolated pinvoke.net layer -> knowledge/aux records.

    pinvoke.net is a user-contributed P/Invoke wiki, collected as a
    *weak auxiliary* reference for judging constant/value/header
    linkages -- never as documentation of Windows CE.  Its records are
    written to knowledge/aux/ and are deliberately NOT part of
    entities/requirements/constants: a pinvoke page mints no entity.
    The ``header`` of an API record is *derived* from the module the
    site files the name under (page_parse.pinvoke_header_from_module)
    and is labelled as derived wherever it is used.
    """
    apis, constants = [], []
    for fact in facts:
        pinvoke = fact.get("pinvoke")
        if not pinvoke:
            continue
        for item in pinvoke.get("apis") or []:
            key = hashlib.sha1(
                (fact["path"] + "\x00" + item["name"]).encode("utf-8")
            ).hexdigest()[:12]
            apis.append({
                "id": "p" + key,
                "name": item["name"],
                "module": item["module"],
                "dll": item["dll"],
                "header": item["header"],
                "evidence": item["evidence"],
                "page_id": fact["page_id"],
                "layer": "pinvoke",
                "license": license_of(fact["path"]),
                "source": source_of(fact),
            })
        module = fact["book"].split("/", 1)[1] if "/" in fact["book"] else ""
        for index, item in enumerate(pinvoke.get("constants") or []):
            key = hashlib.sha1(
                (fact["path"] + "\x00" + item["name"] + "\x00" +
                 item["value"] + "\x00" + str(index)).encode("utf-8")
            ).hexdigest()[:12]
            constants.append({
                "id": "p" + key,
                "name": item["name"],
                "value": re.sub(r"^0X", "0x", item["value"]),
                "decimal": item.get("decimal"),
                "module": module,
                "header": page_parse.pinvoke_header_from_module(module)
                if module else "",
                "table": item.get("table") or "pinvoke",
                "row": item["row"],
                "page_id": fact["page_id"],
                "layer": "pinvoke",
                "license": license_of(fact["path"]),
                "source": source_of(fact),
            })
    # Second accept path for the weak-auxiliary layer: the pinned
    # dotnet/pinvoke snapshot (sources/dotnet-pinvoke/, MIT).  Its records
    # quote the .cs lines, carry the module placement, and the derived
    # header; like the wiki rows, they are aux evidence only.
    try:
        import pinvoke_extract  # noqa: E402
        archive = pinvoke_extract.recent_archive()
    except ImportError:  # pragma: no cover - defensive
        archive = None
    if archive is not None:
        dotnet_apis, dotnet_constants = pinvoke_extract.parse_archive(
            archive)
        apis.extend(dotnet_apis)
        constants.extend(dotnet_constants)

    apis.sort(key=lambda r: (r["name"].lower(), r["source"]["path"]))
    constants.sort(key=lambda r: (r["name"].lower(), r["source"]["path"]))
    return apis, constants


# The constant -> header linkage ranks, best first.  A rank's label says
# *who* states the header for a constant the pages number.  The official
# Windows CE documentation always outranks the Win32 desktop reference,
# which in turn outranks the pinned reference headers that *define* the
# name (a definition is stronger membership evidence than a listing),
# which outrank the co-mention evidence of other CE pages, which in turn
# outranks the pinvoke.net weak auxiliary hint; within one name only the
# best available rank is written out.
# Wine/ReactOS/MinGW-w64 are prohibited (not Windows CE); the
# ``reference-header-secondary`` rung existed for MinGW-w64 and is
# retired with it.
LINK_RANKS = ("own-page", "entity-page", "constant-entity",
              "win32-reference",
              "reference-header",
              "co-mention", "heuristic-prefix", "pinvoke-weak")
LINK_RANK_INDEX = {rank: index for index, rank in enumerate(LINK_RANKS)}


def value_number(text):
    """The integer one printed value states, or None (never re-emitted).

    A C suffix (``0x0001L``) is a printing mark, not part of the number.
    """
    try:
        text = str(text).strip()
        # a suffix is L/U/f -- never a hex digit (0xFFFFFFFF keeps its F's)
        text = re.sub(r"[uUlL]+$", "", text)
        if text.lower().startswith(("0x", "-0x")):
            return int(text, 16)
        return int(text, 10)
    except (ValueError, TypeError):
        return None


# The hand-reviewed value disagreements (data/constant-value-review.tsv):
# one row per name whose pages print more than one number, the value the
# review resolved it to (empty when the corpus alone cannot say), the
# category of the disagreement and the verdict text.  The file is an
# INPUT of the build -- the analysis lives beside the other curated
# inputs (data/win32-exclude.tsv and friends) so rebuilding knowledge/
# stays reproducible.
CONSTANT_VALUE_REVIEW = os.path.join(ROOT, "data", "constant-value-review.tsv")


def read_constant_value_review():
    review = {}
    if not os.path.exists(CONSTANT_VALUE_REVIEW):
        return review
    with open(CONSTANT_VALUE_REVIEW, encoding="utf-8") as fh:
        header = None
        for line in fh:
            if line.startswith("#"):
                continue
            cells = line.rstrip("\n").split("\t")
            if header is None:
                header = cells
                continue
            if len(cells) < 4:
                continue
            row = dict(zip(header, cells))
            review[row["name"]] = row
    return review


# The pinned, licence-vetted public references under sources/: their
# header files *define* names, so a documented constant they define is
# evidence of the header membership (which file the name sits in) --
# never of its value: values come only from the CE/Win32 documentation
# pages.  The ONLY reference is the CeGCC w32api, the classic 32-bit
# Win32 headers adapted for Windows CE (public domain,
# sources/w32api-cegcc/PROVENANCE.md), filed at the marked rank
# ``reference-header``.
#
# STANDING PROHIBITION (2026-10, user order): Wine, ReactOS and
# MinGW-w64 are NOT Windows CE and must never be used as reference
# material for this corpus -- not for header membership, not for values,
# not for cross-checking, not as a secondary fallback.  Their snapshots
# and every row derived from them are deleted; do not re-add them.
REFERENCE_RANKS = (
    {"tag": "w32api-cegcc", "rank": "reference-header",
     "glob": os.path.join(ROOT, "sources", "w32api-cegcc",
                          "w32api-*-src.tar.gz"),
     "parseable": None, "label": "w32api-cegcc"},
)

REF_DEFINE_RE = re.compile(r"^\s*#\s*define\s+([A-Za-z_]\w*)\s*(.*)$")
REF_COMMENT_RE = re.compile(r"/\*.*?\*/|//.*$")
REF_ENUM_RE = re.compile(r"\benum\b[^{};]*\{([^{}]*)\}", re.S)
REF_MEMBER_RE = re.compile(r"^\s*([A-Za-z_]\w*)\s*(?::\s*\d+\s*)?(?:=|,|$)")
REF_GUARDISH = re.compile(r"_INC_[A-Z0-9_]+$|__?\S+_H(?:INCLUDED)?_+$")


DEF_EXPORT_RE = re.compile(r"^([A-Za-z_@$?][\w@$?]*)")
DEF_KEYWORDS = {"LIBRARY", "NAME", "EXPORTS", "SECTIONS", "VERSION",
                "HEAPSIZE", "STACKSIZE", "DESCRIPTION"}


def reference_export_names():
    """module -> [(name, def_member, rank, evidence)] from the pinned
    reference's ``.def`` export lists (its lib/ and libce/ -- the CeGCC
    import libraries' export lists).

    MEMBERSHIP ONLY -- which export list claims which name.  Ordinals and
    decoration are parsed away and never returned (values: never).  The
    rank is ``reference-export``: a lead for the generated .def
    worklists, never documentation.  The A/W spelling is kept exactly as
    the list prints it: an A-sounding name is a review lead, and the
    A/W-per-page confirmation rule still applies.
    """
    import tarfile  # local: only the reference pass needs archives

    out = collections.defaultdict(list)
    for spec in REFERENCE_RANKS:
        tarballs = sorted(glob.glob(spec["glob"]))
        if not tarballs:
            continue
        tarball = tarballs[-1]
        with tarfile.open(tarball) as tar:
            for member in tar.getmembers():
                parts = member.name.split("/")
                if len(parts) < 2 or parts[-2] not in ("lib", "libce"):
                    continue
                if not parts[-1].lower().endswith(".def"):
                    continue
                handle = tar.extractfile(member)
                if handle is None:
                    continue
                text = handle.read().decode("utf-8", "replace")
                module = parts[-1][:-4].lower()
                evidence = (f"{os.path.relpath(tarball, ROOT)}!{member.name}")
                in_exports = False
                for line in text.splitlines():
                    s = line.strip()
                    if not s or s.startswith(";"):
                        continue
                    head = s.split()[0].upper()
                    if head == "EXPORTS":
                        in_exports = True
                        continue
                    if head in DEF_KEYWORDS:
                        in_exports = False
                        continue
                    if not in_exports:
                        continue
                    match = DEF_EXPORT_RE.match(s)
                    if match is None:
                        continue
                    name = match.group(1)
                    out[module].append((name, member.name, spec["rank"],
                                        evidence))
    return out


def reference_define_headers():
    """name -> [(header, rank, evidence)] from the pinned reference headers.

    Both ``#define`` lines and ``enum`` members of the top-level files of
    the reference's ``include/`` directory are read.  The value beside
    the name is parsed away and never returned: this function can only
    say *which header defines the name*.
    """
    import tarfile  # local: only the reference pass needs archives

    out = collections.defaultdict(list)
    for spec in REFERENCE_RANKS:
        tarballs = sorted(glob.glob(spec["glob"]))
        if not tarballs:
            print(f"[kb] reference {spec['tag']}: no pinned tarball under "
                  "sources/ -- header-membership evidence skipped",
                  flush=True)
            continue
        tarball = tarballs[-1]
        try:
            from xcheck_references import w32api_cegcc_class  # noqa
        except ImportError:  # pragma: no cover - defensive
            continue
        classifier = w32api_cegcc_class
        rows = 0
        with tarfile.open(tarball) as tar:
            for member in tar.getmembers():
                if not member.isfile():
                    continue
                parts = member.name.split("/")
                dirs = spec.get("dirs") or ("include",)
                if len(parts) < 2 or parts[-2] not in dirs:
                    continue        # top-level include/ (and crt/) files only
                if not parts[-1].lower().endswith((".h", ".hpp")):
                    continue
                handle = tar.extractfile(member)
                if handle is None:
                    continue
                text = handle.read().decode("utf-8", "replace")
                klas = classifier(text)
                if spec["parseable"] is not None and \
                        klas not in spec["parseable"]:
                    continue
                header = parts[-1]
                evidence = f"{os.path.relpath(tarball, ROOT)}!{member.name}"
                seen = set()
                for line in text.splitlines():
                    match = REF_DEFINE_RE.match(line)
                    if match is None:
                        continue
                    name = match.group(1)
                    value = REF_COMMENT_RE.sub("", match.group(2)).strip()
                    if value.startswith("(") and f"{name}(" in line:
                        continue            # function-like macro
                    if name.startswith("__") or REF_GUARDISH.match(name):
                        continue
                    if name not in seen:
                        seen.add(name)
                        out[name].append((header, spec["rank"], evidence))
                        rows += 1
                for enum in REF_ENUM_RE.findall(text):
                    for piece in enum.split(","):
                        match = REF_MEMBER_RE.match(
                            piece.split("/*")[0].split("//")[0])
                        if match is None:
                            continue
                        name = match.group(1)
                        if name.startswith("__") or name in seen:
                            continue
                        seen.add(name)
                        out[name].append((header, spec["rank"], evidence))
                        rows += 1
        print(f"[kb] reference {spec['tag']}: {rows:,} name -> header "
              f"statement(s) from {os.path.basename(tarball)}", flush=True)
    return out


def co_mention_links(names, requirements):
    """name -> [(header, page, headers_of_page)]: the CE pages that state a
    header while *listing* the name among their subject's values.

    This is the one corpus-side bridge for a constant whose own pages
    state no header: the value tables number the name, another page of
    the same API family presents it as a named value of an entity whose
    Requirements block names a header (``GetSysColor`` lists
    ``COLOR_*`` and states ``Winuser.h``).  Accepted only under a strict
    unanimity rule -- every such page must name the *same single* header,
    and the name must be a spelled identifier (an underscore inside an
    uppercase-initial name), never a word like ``True`` or ``READ`` that
    pages use in passing.  Everything weaker stays in the worklist.
    """
    wanted = {n for n in names
              if "_" in n and re.match(r"^[A-Z][A-Za-z0-9_]*$", n)
              and len(n) >= 6}
    if not wanted:
        return {}
    page_headers = collections.defaultdict(set)
    page_set = {}
    for record in requirements:
        if record.get("field") != "header" or record.get("layer") != "ce":
            continue
        page_set[record["source"]["path"]] = record["source"]["set"]
        for match in HEADER_TOKEN.findall(record.get("value") or ""):
            page_headers[record["source"]["path"]].add(
                match.split("/")[-1].split("\\")[-1])
    hits = collections.defaultdict(list)   # name -> [(page, headers)]
    scanned = 0
    token_re = re.compile(r"\b[A-Z][A-Za-z0-9_]{4,}\b")
    for path, headers in sorted(page_headers.items()):
        if not headers:
            continue
        try:
            text = open(os.path.join(ROOT, path), encoding="utf-8",
                        errors="replace").read()
        except OSError:
            continue
        scanned += 1
        found = {match.group(0) for match in token_re.finditer(text)}
        for name in found & wanted:
            hits[name].append((path, headers))
    out = {}
    for name, rows in hits.items():
        common = set(rows[0][1])
        for _path, headers in rows[1:]:
            common &= headers
        if len(common) != 1:
            continue        # zero common header, or several: never guessed
        header = sorted(common)[0]
        out[name] = [(header, path, page_set.get(path, ""))
                     for path, headers in rows]
    print(f"[kb] co-mention scan: {scanned:,} header-stating CE page(s), "
          f"{len(out):,} name(s) with one unanimous header", flush=True)
    return out


def constant_header_links(constants, requirements, pinvoke_records_pair,
                          reference_links=None, mention_links=None):
    """constant name -> header file, ranked by the strength of the statement.

    Every row keeps its evidence: how many statements say it, one example
    page, and the sets those pages belong to.  ``own-page``: the page
    that numbers the constant also states a Header.  ``entity-page``:
    the requirements of the page's own entity (the enumeration's or
    macro's page) name a header.  ``win32-reference``: only the desktop
    Win32 reference names a header (marked -- the generator has to
    verify those against the CE SDK).  ``reference-header``:
    the pinned, licence-vetted reference
    headers under sources/ *define* the name in one header file (marked
    -- header membership only; their values are never taken).
    ``co-mention``: another CE page lists the name among its subject's
    values and names one unanimous header (a listing ranks under a
    definition, so an error code listed on an API page stays where its
    defining header puts it).  ``pinvoke-weak``: nothing else says
    anything, and the only hint is the pinvoke.net module the name is
    filed under.  No header is invented: every emitted row traces to a
    printed statement or, at the weakest ranks, to the reference or
    pinvoke material itself.
    """
    def headers_of_value(value):
        files = []
        for match in HEADER_TOKEN.findall(value or ""):
            name = match.split("/")[-1].split("\\")[-1]
            if name and name.lower() not in [f.lower() for f in files]:
                files.append(name)
        return files

    # entity -> header files, split by who states them (CE docs / win32 ref)
    entity_headers = {"ce": collections.defaultdict(set),
                      "win32": collections.defaultdict(set)}
    for record in requirements:
        if record.get("field") != "header" or not record.get("entity"):
            continue
        layer = record.get("layer")
        if layer not in entity_headers:
            continue
        for name in headers_of_value(record.get("value")):
            entity_headers[layer][record["entity"]].add(name)

    best = collections.defaultdict(
        lambda: {"rank": None, "headers": collections.defaultdict(
            lambda: {"count": 0, "page": "", "sets": set()})})

    def offer(name, rank, headers, page, book):
        slot = best[name]
        if slot["rank"] is None or LINK_RANK_INDEX[rank] < \
                LINK_RANK_INDEX[slot["rank"]]:
            slot["rank"] = rank
            slot["headers"] = collections.defaultdict(
                lambda: {"count": 0, "page": "", "sets": set()})
        if rank != slot["rank"]:
            return
        for header in headers:
            entry = slot["headers"][header.lower()]
            entry["count"] += 1
            if not entry["page"]:
                entry["page"] = page
            entry["sets"].add(book)
            if len(header) > len(entry.get("as_printed", "")):
                entry["as_printed"] = header

    # rank 1+4: the numbering page itself states the header
    by_name = collections.defaultdict(list)
    for record in constants:
        by_name[record["name"]].append(record)
    for name, rows in by_name.items():
        for record in rows:
            if record.get("layer") not in ("ce", "win32"):
                continue
            own = headers_of_value(";".join(record.get("headers") or ()))
            rank = "own-page" if record.get("layer") == "ce" \
                else "win32-reference"
            if own:
                offer(name, rank, own, record["source"]["path"],
                      record["source"]["set"])
            # rank 2: the entity whose page carries the constant
            entity = record.get("page_entity")
            if entity and entity_headers["ce"].get(entity):
                offer(name, "entity-page",
                      sorted(entity_headers["ce"][entity]),
                      record["source"]["path"], record["source"]["set"])
            if entity and entity_headers["win32"].get(entity):
                offer(name, "win32-reference",
                      sorted(entity_headers["win32"][entity]),
                      record["source"]["path"], record["source"]["set"])
        # Aggregation is by constant *name*: a constant one page numbers
        # without naming a header and another page numbers while naming
        # the header lands at "own-page" through the second page's row, so
        # a weaker "another page also documents it" tier is not needed.
        # But a constant that is ITSELF an entity (a macro with a page of
        # its own) takes its header from that entity's CE requirements
        # even when the numbering page is a different one.
        entity_headers_ce = sorted(entity_headers["ce"].get(
            ce_api_names.normalize(name) or "") or ())
        if entity_headers_ce:
            first = rows[0]
            offer(name, "constant-entity", entity_headers_ce,
                  first["source"]["path"], first["source"]["set"])

    # ranks: the pinned, licence-vetted reference headers under sources/.
    # They *define* the name in one header file -- evidence of the header
    # membership only.  No value is ever read from them (the value beside
    # the name is parsed away in reference_define_headers()), and the
    # rows are marked so the generator has to verify against the CE SDK.
    # Wine/ReactOS/MinGW-w64 are prohibited (not Windows CE): no row of
    # theirs may ever appear here.
    ref_links = reference_links or {}
    for name in sorted(ref_links, key=str.lower):
        if name not in by_name:
            continue
        for header, rank, evidence in ref_links[name]:
            book = evidence.split("/")[1] if "/" in evidence else rank
            offer(name, rank, [header], evidence, book)

    # rank: co-mention -- another CE page of the same API family lists the
    # name among its subject's values while its Requirements block names
    # one unanimous header.  The official documentation one step removed
    # from the numbering page -- but only a listing, never a definition,
    # so it ranks under the references above (an error code listed on an
    # API page belongs to winerror.h, not to that API's header); the
    # strict rule is in co_mention_links().
    for name, rows in (mention_links or {}).items():
        if name not in by_name:
            continue
        for header, page, book in rows:
            offer(name, "co-mention", [header], page, book)

    # rank: heuristic-prefix -- well-known constant name prefixes that
    # reliably map to specific headers.  This is a fallback for constants
    # with no other linkage, based on Windows API naming conventions.
    # Only used when no stronger rank applies.
    for name in by_name:
        if name in best and best[name]["rank"] is not None:
            continue  # already has stronger linkage
        header = header_map.header_for_constant(name)
        if header:
            first = by_name[name][0]
            offer(name, "heuristic-prefix", [header],
                  first["source"]["path"], first["source"]["set"])

    # last rank: the pinvoke.net weak auxiliary hint.  It may only file a
    # name the CE (or CE-shared Win32) documentation actually numbers:
    # a community name with no documented value anywhere in the corpus
    # mints no linkage row at all.
    apis, pinvoke_constants = pinvoke_records_pair or ([], [])
    for item in apis + pinvoke_constants:
        header = item.get("header")
        name = item.get("name")
        if name and header and name in by_name:
            offer(name, "pinvoke-weak", [header],
                  item["source"]["path"], item["source"]["set"])

    out = []
    for name in sorted(best, key=str.lower):
        slot = best[name]
        if slot["rank"] is None:
            continue
        for lower, entry in sorted(slot["headers"].items()):
            out.append((
                name,
                entry.get("as_printed") or lower,
                slot["rank"],
                entry["count"],
                entry["page"],
                ";".join(sorted(entry["sets"]))))
    return out


def entity_records(facts, declarations, requirements):
    by_entity = collections.defaultdict(list)
    # A title that prints several names (``strcpy, wcscpy``) documents each
    # of them.  The declaration record is stored once, under the first name;
    # the others share that quotation when the text prints their name, and
    # they share the page's requirements.  No name is added that the title
    # and a syntax block do not both print.
    extras_of = {}
    for fact in facts:
        extras = fact.get("also_documented") or []
        if extras:
            extras_of[fact["path"]] = extras
        ids = [item["id"] for item in extras]
        if fact["entity"] and fact["entity"] not in ids:
            ids.append(fact["entity"])
        for entity in ids:
            by_entity[entity].append(fact)

    decl_by_entity = collections.defaultdict(list)
    for record in declarations:
        if record["entity"]:
            decl_by_entity[record["entity"]].append(record)
        extras = extras_of.get((record.get("source") or {}).get("path"))
        if not extras or record.get("role") != "syntax":
            continue
        for item in extras:
            if item["id"] == record.get("entity"):
                continue
            if page_parse.syntax_declares_name(item["name"], record.get("text")):
                decl_by_entity[item["id"]].append(record)
    req_by_entity = collections.defaultdict(list)
    for record in requirements:
        if record["entity"]:
            req_by_entity[record["entity"]].append(record)
        if record.get("for_name"):
            # a name-list row states its own header; it is not the page's
            # requirement for every name the page lists
            continue
        extras = extras_of.get((record.get("source") or {}).get("path"))
        if not extras:
            continue
        for item in extras:
            if item["id"] != record.get("entity"):
                req_by_entity[item["id"]].append(record)

    out = []
    for entity in sorted(by_entity):
        pages = by_entity[entity]
        licenses = sorted({license_of(f["path"]) for f in pages})
        ce_pages = sorted({f["path"] for f in pages if f["layer"] == "ce"})
        win32_pages = sorted({f["path"] for f in pages if f["layer"] == "win32"})
        dotnet_pages = sorted({f["path"] for f in pages if f["layer"] == "dotnet"})
        sets = sorted({f["book"] for f in pages if f["layer"] == "ce"})
        displays = collections.Counter()
        for fact_page in pages:
            shown = None
            for item in fact_page.get("also_documented") or []:
                if item["id"] == entity:
                    shown = item["name"]
                    break
            if not shown:
                shown = fact_page.get("display")
            if shown:
                displays[shown] += 1
        kinds = collections.Counter()
        for f in pages:
            if f["kind"]:
                kinds[f["kind"]] += 1
            for item in f.get("also_documented") or []:
                if item["id"] == entity and item.get("kind"):
                    kinds[item["kind"]] += 1
        for record in decl_by_entity[entity]:
            if record["role"] == "syntax" and record["kind"]:
                kinds[record["kind"]] += 1
        reqs = req_by_entity[entity]
        field_pages = [f for f in pages if f["documented_fields"]]
        # The same name can be documented by more than one page (the A and W
        # spellings of a structure): the field list is their union, and each
        # field keeps the page it was actually read from (used for
        # kb/struct-fields.tsv); the page list is kept beside it.
        documented = []
        field_page_of = {}
        for fact_page in field_pages:
            for name in fact_page["documented_fields"]:
                if name not in field_page_of:
                    field_page_of[name] = fact_page["documented_fields_page"]
                if name not in documented:
                    documented.append(name)
        documented_pages = sorted({f["documented_fields_page"]
                                   for f in field_pages})

        def values(field):
            # A library cell that names several files assigns each of them.
            # The requirement's derived key stays the first file; the link
            # map has to list the rest as well, or ``Uuid.lib`` never
            # appears for a page that printed ``Ole32.lib, Uuid.lib``.
            if field in ("library", "dll"):
                found = []
                for record in reqs:
                    if record["field"] != field:
                        continue
                    names = page_parse.assigned_files(record.get("value") or "")
                    if not names and record["key"]:
                        names = [record["key"]]
                    for name in names:
                        if name not in found:
                            found.append(name)
                return sorted(found)
            if field == "header":
                # Header values may contain multiple files (e.g., "Winuser.h Rapi.h")
                found = []
                for record in reqs:
                    if record["field"] != field:
                        continue
                    names = HEADER_TOKEN.findall(record.get("value") or "")
                    if not names and record["key"]:
                        names = HEADER_TOKEN.findall(record["key"])
                    for name in names:
                        if name not in found:
                            found.append(name)
                return sorted(found)
            return sorted({r["key"] for r in reqs
                           if r["field"] == field and r["key"]})

        syntax_records = [d for d in decl_by_entity[entity]
                          if d["role"] == "syntax"]
        syntax_decls = sorted({d["id"] for d in syntax_records})
        # The ABI view of a name: what its declarations print about
        # themselves.  Nothing here is inferred -- a convention that no page
        # prints is absent, and the count of such declarations is kept.
        conventions = sorted({d["calling_convention"] for d in syntax_records
                              if d.get("calling_convention")})
        without_convention = sum(1 for d in syntax_records
                                 if not d.get("calling_convention"))
        declared_members = sum(len(d.get("members") or [])
                               for d in syntax_records)
        typed_members = sum(1 for d in syntax_records
                            for line, type_text in zip(
                                d.get("members") or [],
                                d.get("member_types") or [])
                            if type_text)
        bitfield_members = sum(1 for d in syntax_records
                               for line in (d.get("members") or [])
                               if re.search(r"\w+\s*:\s*\d+", line))
        abi_flag_names = sorted({flag for d in syntax_records
                                 for flag in (d.get("abi_flags") or [])})
        reference_fields = {"header", "library", "dll", "os_versions"}
        looks_like_reference = bool(values("header") or values("library") or
                                    values("dll")) or any(
            r["field"] in reference_fields for r in reqs)
        # doc_role is derived, and says what the *corpus* has for this name:
        #   api-definition -- a page prints a syntax block for it
        #   api-page       -- a page looks like reference (requirements) but
        #                     prints no syntax block  -> a collection gap
        #   topic          -- the name only appears as the title of a prose page
        if syntax_decls:
            doc_role = "api-definition"
        elif looks_like_reference:
            doc_role = "api-page"
        else:
            doc_role = "topic"

        out.append({
            "id": entity,
            "name": displays.most_common(1)[0][0] if displays else entity,
            # A name that is not an API at all.  Only one pattern is certain
            # enough to flag: an all-caps double-underscore identifier
            # (__COMMONPUBROOT, __PROJROOT) is a build-system variable that a
            # page's code block mentioned, not something to generate a
            # declaration for.  Flagged, never deleted -- the record and its
            # page stay readable.
            "noise": "build-variable"
            if re.match(r"^__[A-Z0-9_]+$", displays.most_common(1)[0][0]
                        if displays else entity) else None,
            "layers": sorted({f["layer"] for f in pages}),
            "kinds": [k for k, _n in kinds.most_common()],
            "kind_evidence": "sdk-api-filename" if any(
                f["entity_evidence"] == "sdk-api-filename" for f in pages) else (
                "syntax" if any(d["kind"] for d in decl_by_entity[entity]
                                if d["role"] == "syntax") else None),
            "ce_sets": sets,
            "ce_pages": ce_pages,
            "win32_pages": win32_pages,
            "dotnet_pages": dotnet_pages,
            "name_evidence": sorted({f["entity_evidence"] for f in pages
                                     if f["entity_evidence"]}),
            # The members a page documents (sdk-api -struct-fields) when the
            # page prints no declaration body: names and order as documented,
            # no offsets -- the ABI gap stays visible instead of being filled.
            "documented_fields": documented,
            "documented_fields_page": (field_page_of[documented[0]]
                                       if documented else None),
            "documented_fields_pages": documented_pages,
            "documented_field_pages": field_page_of,
            "abi": {
                "calling_conventions": conventions,
                "declarations_without_convention": without_convention,
                "syntax_declarations": len(syntax_decls),
                "declared_members": declared_members,
                "typed_members": typed_members,
                "bitfield_members": bitfield_members,
                "flags": abi_flag_names,
                # CPU list the page prints (``Architecture: ARM, MIPS, SH-4``).
                # Not inferred from the name, and not a calling convention.
                "architectures": values("architecture"),
                # the ABI statements the pages make in prose (kind abi-note),
                # attached below once the constraint ids are known
                "notes": 0,
            },
            # Set by fold_variants(): a Windows CE page documents the base
            # name (CreateFile) while the Win32 reference is written per
            # spelling (CreateFileW).  ``win32_documented`` says the shared
            # surface documents the name, whether directly or as a variant.
            "variants_of": None,
            "variants": [],
            "win32_pages_from_variants": [],
            "win32_documented": bool(win32_pages),
            # Set by classify_surface(): ce-only / shared / win32-spelling /
            # win32-only -- Windows CE is a part of Win32, not all of it.
            "surface": None,
            "headers": values("header"),
            "modules": values("module"),
            # Catalog component the page prints (``Component: fsdbase``).
            # Not a DLL name, and not rewritten to one.
            "components": values("component"),
            # Catalog variables the page prints (``sysgen: SYSGEN_XAML_RUNTIME``).
            # Not a header and not a library.
            "sysgens": values("sysgen"),
            "libraries": values("library"),
            "dlls": values("dll"),
            # Fields for which a page states there is no such file
            # (``Link Library: Not applicable.``, ``DLL: None``).  An empty
            # list here and an empty ``libraries`` are different facts: the
            # first is a page that said nothing, the second a page that said
            # there is none.  The generator must not go looking for a file
            # the documents deny.
            "stated_none": sorted({r["field"] for r in reqs
                                   if r["field"] in ("header", "library",
                                                     "dll")
                                   and page_parse.stated_none(r["value"])}),
            "unicode_ansi": values("unicode_ansi"),
            # Pages of this entity that state only the Unicode form exists
            # on the device.  The Win32 reference page for the same name
            # documents an ANSI spelling; that is the desktop.  Nothing is
            # deleted here -- the contradiction is recorded with both
            # quotations so a generator can obey the CE page.
            "unicode_only": [
                {"text": item["text"], "subject": item["subject"],
                 "scope": item.get("scope", "system"),
                 "page": fact["path"], "page_id": fact["page_id"],
                 "set": fact["book"], "license": license_of(fact["path"])}
                for fact in by_entity[entity]
                for item in (fact.get("unicode_only") or [])],
            "doc_role": doc_role,
            "declarations": sorted({d["id"] for d in decl_by_entity[entity]}),
            "syntax_declarations": syntax_decls,
            "licenses": licenses,
            "requirements": sorted({r["id"] for r in reqs}),
            "constraints": [],
            "relations": [],
            "generation_use": [],
        })
    return out


# --------------------------------------------------------------- relations

UNICODE_PAIR = re.compile(
    r"([A-Za-z_][A-Za-z0-9_]*)\s*\((Unicode|ANSI)\)", re.I)


def add_relations(entities, requirements, declarations):
    """Fill ``relations`` and ``generation_use``.

    Both are DERIVED, and every relation carries the page and the printed text
    it was read from:

    * ``unicode-ansi``  -- the page's own ``Unicode and ANSI`` requirement names
      the pair (``CreateFileW (Unicode) and CreateFileA (ANSI)``), so the two
      spellings are linked, not guessed;
    * ``interface-method`` -- the name is printed as ``Interface::Method``
      or ``MSMQMessage.Priority``, so the member belongs to the parent the
      title printed;
    * ``layer`` -- the same name is documented both by Windows CE and by the
      Win32 reference (the pages are already listed in the record; this states
      the relation for a consumer that only reads ``relations``).
    """
    by_id = {e["id"]: e for e in entities}
    per_entity = collections.defaultdict(list)

    for record in requirements:
        if record["field"] != "unicode_ansi" or not record["entity"]:
            continue
        names = list(dict.fromkeys(UNICODE_PAIR.findall(record["value"])))
        if len(names) < 2:
            continue
        # keep the order the page printed: "X (Unicode) and Y (ANSI)"
        plain = [name for name, _tag in names]
        # The base name the pair belongs to: when the two spellings differ
        # only in a trailing A/W and the base is documented, link the base as
        # well (``CreateFile`` -> ``CreateFileW``/``CreateFileA``).  The pair
        # is printed by the page; the base link is derived from it.
        base = None
        if len(plain) == 2 and plain[0][:-1].lower() == plain[1][:-1].lower() \
                and {plain[0][-1:].upper(), plain[1][-1:].upper()} == {"A", "W"}:
            base = plain[0][:-1]
            if ce_api_names.normalize(base) not in by_id:
                base = None
        if base:
            base_id = ce_api_names.normalize(base)
            for variant in plain:
                per_entity[base_id].append({
                    "type": "unicode-ansi-base",
                    "name": variant,
                    "id": ce_api_names.normalize(variant),
                    "present": ce_api_names.normalize(variant) in by_id,
                    "evidence": (f"{base} -> " + " and ".join(plain) + "; " +
                                 record["evidence"]),
                    "page": record["source"]["path"],
                })
            for n in plain:
                per_entity[ce_api_names.normalize(n)].append({
                    "type": "unicode-ansi-base",
                    "name": base,
                    "id": base_id,
                    "present": base_id in by_id,
                    "evidence": record["evidence"],
                    "page": record["source"]["path"],
                })
        for name in plain:
            other = [n for n in plain if n != name]
            per_entity[record["entity"]].append({
                "type": "unicode-ansi",
                "name": name,
                "id": ce_api_names.normalize(name),
                "present": ce_api_names.normalize(name) in by_id,
                "evidence": record["evidence"],
                "page": record["source"]["path"],
            })
            for n in other:
                per_entity[ce_api_names.normalize(name)].append({
                    "type": "unicode-ansi",
                    "name": n,
                    "id": ce_api_names.normalize(n),
                    "present": ce_api_names.normalize(n) in by_id,
                    "evidence": record["evidence"],
                    "page": record["source"]["path"],
                })

    members = collections.defaultdict(set)
    for record in declarations:
        if record["entity"] and record["members"]:
            members[record["entity"]].add(record["id"])

    # ``Related macro: MonthCal_GetSelRange`` and ``Related message:
    # LVM_HITTEST`` name the other definition the page prints.  A
    # space-separated list is kept token by token when every token is an
    # identifier.  Prose is not split into names.
    related_of = collections.defaultdict(list)
    related_kind = {
        "related macro": "related-macro",
        "related macros": "related-macro",
        "related message": "related-message",
    }
    related_ident = re.compile(r"^[A-Za-z_][\w]*$")
    for record in requirements:
        kind = related_kind.get((record.get("label") or "").strip().lower())
        if not kind or not record.get("entity"):
            continue
        value = (record.get("value") or "").strip()
        tokens = value.split()
        if not tokens or not all(related_ident.match(token) for token in tokens):
            one = value.rstrip(".,;")
            tokens = [one] if related_ident.match(one) else []
        if not tokens:
            continue
        page = (record.get("source") or {}).get("path") or ""
        evidence = record.get("evidence") or f"{record.get('label')}: {value}"
        for token in tokens:
            related_of[record["entity"]].append((kind, token, evidence, page))

    for entity in entities:
        name = entity["name"]
        # The title printed the parent.  A dot is the spelling
        # ``MSMQMessage.Priority`` uses; it is not rewritten to ``::``.
        interface = page_parse.printed_parent(name)
        if interface:
            entity["relations"].append({
                "type": "interface-method",
                "name": interface,
                "id": ce_api_names.normalize(interface),
                "present": ce_api_names.normalize(interface) in by_id,
                "evidence": name,
                "page": entity["ce_pages"][0] if entity["ce_pages"] else "",
            })
        for kind, token, evidence, page in related_of.get(entity["id"], ()):
            target = ce_api_names.normalize(token)
            entity["relations"].append({
                "type": kind,
                "name": token,
                "id": target,
                "present": target in by_id,
                "evidence": evidence,
                "page": page,
            })
        layers = set(entity["layers"])
        if {"ce", "win32"} <= layers:
            entity["relations"].append({
                "type": "layer",
                "name": "Windows CE and Win32",
                "id": "",
                "present": True,
                "evidence": "documented by both corpora",
                "page": "",
            })
        entity["relations"] += per_entity.get(entity["id"], [])
        unique = {}
        for relation in entity["relations"]:
            unique[(relation["type"], relation["id"], relation["page"],
                    relation["evidence"])] = relation
        entity["relations"] = [unique[key] for key in sorted(unique)]

        use = []
        kinds = set(entity["kinds"])
        if entity["syntax_declarations"] and entity["headers"]:
            use.append("include-declaration")
        if kinds & {"struct", "enum", "union", "typedef", "attribute"}:
            use.append("type-definition")
        if kinds & {"function", "callback", "interface", "other"} and \
                (entity["libraries"] or entity["dlls"]):
            use.append("link-library")
        if kinds & {"function", "callback"} and entity["dlls"]:
            use.append("def-export")
        if any(item.get("scope") == "this-api"
               for item in entity.get("unicode_only") or ()):
            # the device has the W form of *this* API only: no A export,
            # no A macro.  A sentence about the system in general
            # ("Windows CE supports only Unicode strings") is kept as
            # evidence but does not make this claim about the name.
            use.append("unicode-only")
        if kinds & {"struct", "union"} and entity["id"] in members:
            use.append("abi-layout")
        if entity["documented_fields"] and "abi-layout" not in use:
            use.append("abi-members")
        abi = entity.get("abi") or {}
        if abi.get("calling_conventions") or abi.get("flags") or \
                abi.get("bitfield_members"):
            use.append("abi-note")
        if abi.get("documented_offsets"):
            use.append("abi-offset")
        if any(r["type"].startswith("unicode-ansi")
               for r in entity["relations"]):
            use.append("unicode-mapping")
        if entity["ce_sets"]:
            use.append("version-scope")
        if entity["constraints"]:
            use.append("ce-restriction")
        entity["generation_use"] = use
        entity["relations"].sort(key=lambda r: (r["type"], r["id"]))


def fold_variants(entities, shared_map):
    """Link a variant spelling (``CreateSemaphoreW``) to its base name.

    Win32 reference pages are written per spelling while the Windows CE pages
    document the base name, so one API lived in two entities.  A link is made
    only on evidence, and ``variants_of.basis`` says which evidence it was:

    * ``page-statement`` -- the variant's own page prints the pair
      (``CreateSemaphoreW (Unicode) and CreateSemaphoreA (ANSI)``), which
      ``add_relations`` recorded as a ``unicode-ansi-base`` relation;
    * ``import-rule`` -- the page was imported for the CE name because it is
      that name's ``A``/``W`` spelling (``data/reports/win32-shared.tsv`` says
      so), and the CE name is in the corpus.  Used only when the page itself
      states no pair, and recorded with the report as its evidence.

    Nothing else is paired: a variant that neither states a base nor was
    imported under one stays on its own.

    * the variant gets ``variants_of`` (base name, kind, basis, evidence, page);
    * the base gets the variant in ``variants``, the variant's Win32 pages in
      ``win32_pages_from_variants`` and ``win32_documented`` set, so the shared
      surface is visible under the name the CE reader knows.
    """
    by_id = {e["id"]: e for e in entities}

    def fold(entity, base, kind, basis, evidence, page):
        entity["variants_of"] = {
            "name": base["name"], "id": base["id"], "kind": kind,
            "basis": basis, "evidence": evidence, "page": page,
        }
        pages = sorted(set(entity["win32_pages"]))
        base["variants"].append({
            "name": entity["name"], "id": entity["id"], "kind": kind,
            "basis": basis, "win32_pages": pages,
            "evidence": evidence, "page": page,
        })
        base["win32_pages_from_variants"] += pages
        if pages:
            base["win32_documented"] = True
            base["relations"].append({
                "type": "unicode-ansi-variant",
                "name": entity["name"], "id": entity["id"], "present": True,
                "evidence": evidence, "page": pages[0],
            })

    folded = 0
    for entity in entities:
        name = entity["name"]
        if entity["variants_of"] or len(name) < 2 or name[-1] not in "AW" \
                or not NAME_SHAPE.match(name[:-1]):
            continue
        kind = "unicode" if name[-1] == "W" else "ansi"
        # (a) the page's own statement, recorded by add_relations()
        for relation in entity["relations"]:
            if relation["type"] != "unicode-ansi-base" \
                    or not relation["present"]:
                continue
            base = by_id.get(relation["id"])
            if not base or base is entity \
                    or base["name"].lower() != name[:-1].lower():
                continue
            fold(entity, base, kind, "page-statement", relation["evidence"],
                 relation["page"])
            folded += 1
            break
        if entity["variants_of"]:
            continue
        # (b) the import rule: this Win32 page was taken for a CE name because
        #     it is that name's A/W spelling, and the CE name is documented.
        for page in entity["win32_pages"]:
            for shared in sorted(shared_map.get(page, ())):
                if shared.lower() != name[:-1].lower():
                    continue
                base = by_id.get(shared.lower())
                if not base or base is entity or not base["ce_pages"]:
                    continue
                fold(entity, base, kind, "import-rule",
                     f"data/reports/win32-shared.tsv imports {page} under the "
                     f"Windows CE name {base['name']}", page)
                folded += 1
                break
            if entity["variants_of"]:
                break
    for entity in entities:
        entity["win32_pages_from_variants"] = sorted(
            set(entity["win32_pages_from_variants"]))
        entity["variants"].sort(key=lambda v: v["name"])
    return folded


def add_ce_name_leads(entities, facts, ce_names):
    """Catalog-only names: what the Windows CE page actually prints.

    ``data/reports/ce-api-names.tsv`` attributes the CE page ids to the name
    (that is how the Win32 import knows what to take), but a CE page whose
    title is prose prints the type under the name *the CE documentation used*
    -- ``AVIMAINHEADER`` is documented by the CE pages as ``MainAVIHeader``.
    This pass reads the identifiers out of the page's own syntax block and
    records them as a ``ce-name-lead`` relation (a lead with its evidence, not
    a renamed entity: the printed spelling may or may not be an entity here).

    Returns the rows for ``reports/catalog-leads.tsv``.
    """
    by_id = {e["id"]: e for e in entities}
    fact_by_id = collections.defaultdict(list)
    for fact in facts:
        fact_by_id[fact["page_id"]].append(fact)

    def printed(fact):
        names = []
        for decl in fact["declarations"]:
            if decl["role"] != "syntax":
                continue
            for name in page_parse.declared_names(decl["text"]):
                if name not in names:
                    names.append(name)
        return names

    rows = []
    for entity in entities:
        if entity["surface"] != "catalog-only":
            continue
        _label, page_ids = ce_names.get(entity["id"], ("", []))
        for page_id in page_ids:
            for fact in fact_by_id.get(page_id, []):
                names = printed(fact)
                for name in names:
                    target = ce_api_names.normalize(name)
                    entity["relations"].append({
                        "type": "ce-name-lead",
                        "name": name,
                        "id": target,
                        "present": target in by_id,
                        "evidence": f"data/reports/ce-api-names.tsv attributes "
                                    f"{page_id} to {entity['name']}; the page "
                                    f"prints {name}",
                        "page": fact["path"],
                    })
                rows.append((
                    entity["name"], entity["id"], page_id, fact["path"],
                    fact["title"], ";".join(names),
                    sum(1 for d in fact["declarations"]
                        if d["role"] == "syntax"),
                    ";".join(entity["win32_pages"]),
                    ";".join(entity["documented_fields"]),
                ))
    for entity in entities:
        unique = {}
        for relation in entity["relations"]:
            unique[(relation["type"], relation["id"], relation["page"],
                    relation["evidence"])] = relation
        entity["relations"] = [unique[key] for key in sorted(unique)]
    rows.sort(key=lambda r: (r[1], r[2]))
    return rows


def classify_surface(entities, shared_map, ce_names):
    """``surface``: where a name belongs in the Windows CE / Win32 split.

    Windows CE is **not** the whole Win32 API: it is the CE-specific surface
    plus the part of Win32 the CE documents share.  This field makes that
    explicit per name, so a generator never has to guess which side a record
    came from:

    * ``ce-only``      -- only Windows CE documents the name;
    * ``shared``       -- Windows CE documents it and the Win32 reference does
      too (directly or through an A/W spelling);
    * ``win32-spelling`` -- the entity is a Win32 page for an A/W spelling of a
      documented CE name (it carries ``variants_of``);
    * ``catalog-only`` -- the official Windows CE catalog lists the name, but
      no CE page for it is in the corpus yet: the Win32 page is the only
      documentation held, so this is a collection lead, not a CE definition;
    * ``win32-only``   -- a Win32 page the corpus holds that is not tied to a
      Windows CE name at all; it is *not* part of the Windows CE surface.
    """
    counts = collections.Counter()
    for entity in entities:
        if entity["ce_pages"]:
            surface = "shared" if entity["win32_documented"] else "ce-only"
        elif entity["variants_of"]:
            surface = "win32-spelling"
        elif any("catalog" in (ce_names.get(shared.lower(), ("", ()))[0])
                 for page in entity["win32_pages"]
                 for shared in shared_map.get(page, ())):
            surface = "catalog-only"
        else:
            surface = "win32-only"
        entity["surface"] = surface
        counts[surface] += 1
    return counts


# ------------------------------------------------------------------- outputs

def dedupe_records(records):
    """One record per id: the same page can print the same block twice."""
    unique = {}
    for record in records:
        unique.setdefault(record["id"], record)
    return [unique[key] for key in sorted(unique)]


def write_jsonl(path, records, compress=True):
    """Write JSONL, gzipped by default.

    The three big files are ~150 MB of text but ~15 MB gzipped, and they are
    generated: ``knowledge/README.md`` explains how to read them.  ``--plain``
    keeps them uncompressed for local work.
    """
    os.makedirs(os.path.dirname(path), exist_ok=True)
    if compress:
        import gzip
        target = path + ".gz"
        # mtime=0: the build is deterministic, so rebuilding unchanged records
        # must not produce a different file (the gzip header stores the time).
        with open(target, "wb") as raw:
            with gzip.GzipFile(filename="", mode="wb", fileobj=raw,
                               compresslevel=9, mtime=0) as gz:
                with io.TextIOWrapper(gz, encoding="utf-8", newline="\n") as fh:
                    for record in records:
                        fh.write(json.dumps(record, ensure_ascii=False,
                                            sort_keys=True) + "\n")
        if os.path.exists(path):
            os.remove(path)
        return target
    with open(path, "w", encoding="utf-8") as fh:
        for record in records:
            fh.write(json.dumps(record, ensure_ascii=False, sort_keys=True) + "\n")
    if os.path.exists(path + ".gz"):
        os.remove(path + ".gz")
    return path


def write_tsv(path, header, rows):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="utf-8") as fh:
        fh.write("\t".join(header) + "\n")
        for row in rows:
            fh.write("\t".join(str(c) for c in row) + "\n")


def aggregate(records, field):
    """key -> entities/sets, plus the verbatim forms seen (for evidence).

    Records whose derived key is empty (a library/DLL/header statement that
    names no file) are left out here and reported separately; the record
    itself stays in ``requirements.jsonl``.
    """
    table = collections.defaultdict(
        lambda: {"entities": set(), "sets": set(),
                 "printed": collections.Counter()})
    for record in records:
        if record["field"] != field or not record["value"]:
            continue
        if field in ("library", "dll"):
            keys = page_parse.assigned_files(record.get("value") or "")
            if not keys and record["key"]:
                keys = [record["key"]]
        else:
            keys = [record["key"]] if record["key"] else []
        for key in keys:
            entry = table[key]
            if record["entity"]:
                entry["entities"].add(record["entity"])
            entry["sets"].add(record["source"]["set"])
            entry["printed"][record["value"]] += 1
    return table


def build(rows, workers, report_only, plain=False):
    facts = []
    with concurrent.futures.ProcessPoolExecutor(max_workers=workers) as pool:
        for index, fact in enumerate(pool.map(parse_page, rows, chunksize=200), 1):
            facts.append(fact)
            if index % 20000 == 0:
                print(f"  parsed {index:,}/{len(rows):,}", flush=True)

    entity_of = lambda f: f["entity"]  # noqa: E731
    declarations = declaration_records(facts, entity_of)
    requirements = requirement_records(facts, entity_of)
    constraints = constraint_records(facts, entity_of)
    abi_offsets = abi_offset_records(facts, entity_of)
    constants = constant_records(facts, entity_of)
    pinvoke_pair = pinvoke_records(facts)
    # Header-membership evidence beyond the pages themselves: the pinned,
    # licence-vetted reference headers under sources/ (marked ranks, no
    # values), and the co-mention scan over the header-stating CE pages.
    reference_links = reference_define_headers()
    # The full CE-adapted header surface of the pinned reference
    # (membership ONLY -- the value beside each name was parsed away):
    # which file of the CE toolchain's headers defines which name.  The
    # generator uses this to know a name is part of the Win32-shared CE
    # surface even when no CE page lists it (WH_*, HCBT_*, ...).
    ref_name_rows = []
    for name in sorted(reference_links, key=str.lower):
        for header, rank, evidence in reference_links[name]:
            ref_name_rows.append((name, header, rank, evidence))
    write_tsv(os.path.join(KB, "reference-names.tsv"),
              ["name", "header", "rank", "evidence"], ref_name_rows)
    print(f"[kb] {len(ref_name_rows):,} reference header-membership "
          f"row(s) (values never taken) -> kb/reference-names.tsv",
          flush=True)
    # Export-list membership from the same pinned reference's .def files
    # (lib/ and libce/): which export list claims which name.  Names
    # only -- ordinals and decoration parsed away (values: never).  The
    # generator appends these as marked leads under the .def worklists.
    reference_exports = reference_export_names()
    ref_export_rows = []
    for module in sorted(reference_exports):
        for name, def_member, rank, evidence in reference_exports[module]:
            ref_export_rows.append((module, name, def_member, rank,
                                    evidence))
    write_tsv(os.path.join(KB, "reference-exports.tsv"),
              ["module", "name", "def_member", "rank", "evidence"],
              ref_export_rows)
    print(f"[kb] {len(ref_export_rows):,} reference export-membership "
          f"row(s) (names only, ordinals never taken) -> "
          f"kb/reference-exports.tsv",
          flush=True)
    ce_constant_names = {r["name"] for r in constants
                         if r.get("layer") == "ce"}
    mention_links = co_mention_links(ce_constant_names, requirements)
    link_rows = constant_header_links(constants, requirements, pinvoke_pair,
                                      reference_links, mention_links)
    value_review = read_constant_value_review()
    conflict_rows = constant_conflict_rows(constants, value_review)
    entities = entity_records(facts, declarations, requirements)

    # attach constraint ids to entities
    constraint_ids = collections.defaultdict(list)
    for record in constraints:
        if record["entity"]:
            constraint_ids[record["entity"]].append(record["id"])
    notes_by_entity = collections.Counter()
    sizes_by_entity = collections.defaultdict(set)
    for record in constraints:
        if not record["entity"] or record.get("kind") != "abi-note":
            continue
        notes_by_entity[record["entity"]] += 1
        if record.get("pattern") == "abi: structure-size":
            # the sentence is the fact; the number is a deterministic read of it
            match = re.search(r"\b(\d+)\s*-?\s*bytes\b", record["text"])
            if match:
                sizes_by_entity[record["entity"]].add(int(match.group(1)))
    offsets_by_entity = collections.Counter(
        record["entity"] for record in abi_offsets if record["entity"])
    offset_pages = collections.defaultdict(set)
    for record in abi_offsets:
        if record["entity"]:
            offset_pages[record["entity"]].add(record["source"]["path"])
    for entity in entities:
        entity["constraints"] = sorted(constraint_ids.get(entity["id"], []))
        if entity.get("abi"):
            abi = entity["abi"]
            abi["notes"] = notes_by_entity.get(entity["id"], 0)
            abi["documented_offsets"] = offsets_by_entity.get(entity["id"], 0)
            abi["offset_pages"] = sorted(offset_pages.get(entity["id"], ()))
            abi["stated_size_bytes"] = sorted(sizes_by_entity.get(entity["id"], ()))
    listed = attach_listed_functions(facts, entities, requirements)
    print(f"[kb] {listed:,} function header/library assignment(s) from "
          "component pages", flush=True)
    add_relations(entities, requirements, declarations)
    folded = fold_variants(entities, read_shared_map())
    print(f"[kb] {folded:,} Unicode/ANSI variant spelling(s) folded into their "
          "base name", flush=True)
    ce_names = read_ce_api_names()
    surfaces = classify_surface(entities, read_shared_map(), ce_names)
    print("[kb] surface: " + ", ".join(f"{k} {v:,}"
                                       for k, v in surfaces.most_common()),
          flush=True)
    # Runs after classify_surface() and before the entity records are written,
    # so the lead lands in the entity as a relation (the report is its view).
    lead_rows = add_ce_name_leads(entities, facts, ce_names)
    print(f"[kb] {len(lead_rows):,} catalog-only lead(s) with a CE page",
          flush=True)

    if report_only:
        return (facts, entities, declarations, requirements, constraints,
                abi_offsets, constants)

    compress = not plain
    entities = dedupe_records(entities)
    declarations = dedupe_records(declarations)
    requirements = dedupe_records(requirements)
    constraints = dedupe_records(constraints)
    write_jsonl(os.path.join(KB, "entities.jsonl"), entities, compress)
    # The .NET layer is separated here as in corpus/: kb/declarations.jsonl is
    # the include/def material (C/C++), declarations-dotnet.jsonl.gz the
    # managed-code signature blocks, kept as evidence of that layer.
    write_jsonl(os.path.join(KB, "declarations.jsonl"),
                [r for r in declarations if r["layer"] != "dotnet"], compress)
    write_jsonl(os.path.join(KB, "declarations-dotnet.jsonl"),
                [r for r in declarations if r["layer"] == "dotnet"], compress)
    write_jsonl(os.path.join(KB, "requirements.jsonl"), requirements, compress)
    write_jsonl(os.path.join(KB, "constraints.jsonl"), constraints, compress)
    write_jsonl(os.path.join(KB, "abi-offsets.jsonl"), abi_offsets, compress)
    write_jsonl(os.path.join(KB, "constants.jsonl"), constants, compress)

    # The constant -> header linkage the include/def generator consumes:
    # one row per (name, header) at the best available evidence rank.
    write_tsv(os.path.join(KB, "constant-headers.tsv"),
              ["name", "header", "strength", "statements", "example_page",
               "sets"], link_rows)

    # The examined value disagreements: names whose pages print more than
    # one number and cannot be explained as a version branch, with the
    # reviewed category/verdict beside them (data/constant-value-review.tsv).
    write_tsv(os.path.join(KB, "constant-conflicts.tsv"),
              ["name", "numbers", "printed_values", "category",
               "reviewed_category", "pages", "sets", "resolved_value",
               "verdict"], conflict_rows)

    # The collection worklist: CE constants no evidence files in any
    # header.  The corpus pages that number them state none, the names
    # are not entities, the CE-shared Win32 subset documents none of
    # them, no other CE page co-mentions them with one unanimous header,
    # and neither pinned reference header defines them -- so they land
    # here, one row per name with the sets, a page to start from, and
    # the classification of why no header can be filed yet.  The CE SDK
    # verification is the intended way to shrink this list.
    linked_names = {row[0] for row in link_rows}
    gap = {}
    ce_value = collections.defaultdict(set)   # name -> values the CE docs print
    for record in constants:
        if record.get("layer") != "ce":
            continue
        ce_value[record["name"]].add(record.get("value") or "")
        if record["name"] in linked_names:
            continue
        entry = gap.setdefault(record["name"], {
            "rows": 0, "origins": collections.Counter(),
            "sets": set(), "example_page": ""})
        entry["rows"] += 1
        entry["origins"][record.get("origin") or "?"] += 1
        entry["sets"].add(record["source"]["set"])
        if not entry["example_page"]:
            entry["example_page"] = record["source"]["path"]

    # The weak-auxiliary review view over the gap names: which of them the
    # isolated pinvoke layer knows, in which module, and whether the
    # community value AGREES with the documented CE value.  It is review
    # material only -- it never changes a number or a header by itself.
    _, pinvoke_constants = pinvoke_pair
    aux_by_name = collections.defaultdict(list)
    for item in pinvoke_constants:
        aux_by_name[item["name"]].append(item)

    def aux_hit_text(name):
        hits = aux_by_name.get(name) or []
        return ";".join(sorted({h["module"] for h in hits}))

    VB_SETS = ("msdn-library/datadungeon-2000-04/vbce",
               "msdn-library/techshelps/VBCE")
    AUTOMATION_SETS = ("msdn-library/datadungeon-2000-04/adoce",)

    def classify_gap(sets):
        """Why the corpus cannot file this name in a header (yet).

        ``vb-language-constant``: documented only by the eVB/VBCE
        language references -- language-runtime constants with no C
        header at all.  ``ole-automation-constant``: documented only by
        the ADO CE automation reference -- type-library enumerations.
        ``needs-sdk-verification``: a platform constant whose header no
        public material examined so far states.
        """
        if all(any(s.startswith(p) for p in VB_SETS) for s in sets):
            return "vb-language-constant"
        if all(any(s.startswith(p) for p in AUTOMATION_SETS) for s in sets):
            return "ole-automation-constant"
        return "needs-sdk-verification"

    for entry in gap.values():
        entry["class"] = classify_gap(entry["sets"])
    write_tsv(
        os.path.join(REPORTS, "constant-header-gaps.tsv"),
        ["name", "rows", "origins", "sets", "example_page", "pinvoke_hit",
         "classification"],
        sorted((name, entry["rows"],
                ",".join(f"{k}:{v}" for k, v in
                         entry["origins"].most_common()),
                ";".join(sorted(entry["sets"])),
                entry["example_page"], aux_hit_text(name),
                entry["class"])
               for name, entry in gap.items()))

    def numeric_candidates(text):
        """The numeric readings of one printed value, for comparison only.

        A bare-digits cell of a hex-headed table keeps its digits, so the
        comparison tries both decimal and hex (a hexadecimal is never
        re-written in the knowledge base itself -- this set exists only
        to judge the community value against the documented one).
        """
        out = set()
        try:
            out.add(int(text, 0))
        except (TypeError, ValueError):
            pass
        if re.fullmatch(r"[0-9a-fA-F]+", text or ""):
            out.add(int(text, 16))
        return out

    # The review target is the set of names the corpus itself numbers
    # *and* for which only the weak auxiliary states a header -- for
    # those names the community value can be compared against the
    # documented CE value, and disagreements are SDK-review red flags.
    weak_names = {row[0] for row in link_rows if row[2] == "pinvoke-weak"}
    review = []
    for name, hits in sorted(aux_by_name.items(), key=lambda kv: kv[0].lower()):
        if name not in weak_names:
            continue
        ce_numbers = set()
        for v in ce_value.get(name, ()):
            ce_numbers |= numeric_candidates(v)
        agrees, disagrees, unclear = 0, 0, 0
        for hit in hits:
            fold = hit.get("value_eval")
            if fold is None:
                unclear += 1
            elif fold in ce_numbers:
                agrees += 1
            else:
                disagrees += 1
        agreement = ("match" if agrees and not disagrees else
                     "mismatch" if disagrees else
                     "no-hit" if unclear == len(hits) else "partial")
        review.append((
            name,
            ",".join(sorted(v for v in ce_value.get(name, ()) if v)),
            ";".join(sorted({h["module"] for h in hits})),
            ",".join(sorted({str(h.get("value_eval")) for h in hits
                             if h.get("value_eval") is not None})),
            agreement,
            hits[0]["source"]["archive_member"]))
    write_tsv(os.path.join(REPORTS, "constant-pinvoke-review.tsv"),
              ["name", "ce_values", "pinvoke_modules", "pinvoke_values",
               "agreement", "example_member"], review)

    # The isolated pinvoke.net weak-auxiliary reference -> knowledge/aux/
    # (written only when the isolated corpus tree has been harvested).
    pinvoke_apis, pinvoke_constants_rows = pinvoke_pair
    os.makedirs(AUX, exist_ok=True)
    with open(os.path.join(AUX, "README.md"), "w",
              encoding="utf-8") as fh:
        fh.write(PINVOKE_AUX_README)
    if pinvoke_apis or pinvoke_constants_rows:
        if pinvoke_apis:
            write_jsonl(os.path.join(AUX, "pinvoke-apis.jsonl"),
                        pinvoke_apis, compress)
            write_tsv(os.path.join(AUX, "pinvoke-apis.tsv"),
                      ["id", "name", "module", "dll", "header", "evidence",
                       "page_id", "site", "archive_member", "line"],
                      [(r["id"], r["name"], r["module"], r.get("dll") or "",
                        r["header"], r.get("evidence") or "", r["page_id"],
                        r["source"].get("site") or "",
                        r["source"].get("archive_member") or "",
                        r["source"].get("line") or "")
                       for r in pinvoke_apis])
        if pinvoke_constants_rows:
            write_jsonl(os.path.join(AUX, "pinvoke-constants.jsonl"),
                        pinvoke_constants_rows, compress)
            write_tsv(os.path.join(AUX, "pinvoke-constants.tsv"),
                      ["id", "name", "value", "value_eval", "module",
                       "header", "enum", "table", "page_id", "site",
                       "archive_member", "line"],
                      [(r["id"], r["name"], r["value"],
                        "" if r.get("value_eval") is None
                        else r.get("value_eval"),
                        r["module"], r["header"], r.get("enum") or "",
                        r["table"], r["page_id"],
                        r["source"].get("site") or "",
                        r["source"].get("archive_member") or "",
                        r["source"].get("line") or "")
                       for r in pinvoke_constants_rows])

    for field, filename, title in (("header", "headers.tsv", "header"),
                                   ("library", "libraries.tsv", "library"),
                                   ("dll", "dlls.tsv", "dll"),
                                   ("module", "modules.tsv", "module")):
        table = aggregate(requirements, field)
        write_tsv(os.path.join(KB, filename),
                  [title, "entities", "sets", "as_printed", "entity_names"],
                  sorted((value, len(entry["entities"]),
                          ",".join(sorted(entry["sets"])),
                          ",".join(v for v, _n in entry["printed"].most_common(3)),
                          ",".join(sorted(entry["entities"]))) for value, entry in
                         table.items()))

    entity_of_set = collections.defaultdict(set)
    for entity in entities:
        for book in entity["ce_sets"]:
            entity_of_set[book].add(entity["id"])
    write_tsv(os.path.join(KB, "sets.tsv"),
              ["set", "entities", "with_declaration", "with_header",
               "with_library", "with_dll"],
              sorted((book, len(ids),
                      sum(1 for e in entities if e["id"] in ids and
                          e["syntax_declarations"]),
                      sum(1 for e in entities if e["id"] in ids and e["headers"]),
                      sum(1 for e in entities if e["id"] in ids and e["libraries"]),
                      sum(1 for e in entities if e["id"] in ids and e["dlls"]))
                     for book, ids in entity_of_set.items()))

    # ---- the Windows CE / Win32 split, one row per name
    surface_rows = [(e["surface"], e["id"], e["name"], ";".join(e["kinds"]),
                     ";".join(e["ce_sets"]), ";".join(e["headers"]),
                     ";".join(e["libraries"] or e["dlls"]))
                    for e in entities]
    surface_rows.sort(key=lambda r: (r[0], r[2].lower()))
    write_tsv(os.path.join(REPORTS, "surface.tsv"),
              ["surface", "entity", "name", "kinds", "ce_sets", "headers",
               "libraries"], surface_rows)

    # ---- the ABI view, one row per name: what its declarations print about
    # themselves (nothing inferred; an absent convention stays absent)
    entity_of_id = {e["id"]: e for e in entities}
    abi_rows = []
    for entity in entities:
        abi = entity.get("abi") or {}
        abi_rows.append((
            entity["id"], entity["name"], ";".join(entity["kinds"]),
            entity["surface"] or "",
            ";".join(abi.get("calling_conventions") or []),
            abi.get("declarations_without_convention", 0),
            abi.get("syntax_declarations", 0),
            abi.get("declared_members", 0),
            abi.get("typed_members", 0),
            abi.get("bitfield_members", 0),
            ";".join(abi.get("flags") or []),
            abi.get("notes", 0),
            abi.get("documented_offsets", 0),
            ";".join(str(size) for size in abi.get("stated_size_bytes", [])),
            ";".join(entity["headers"]),
            ";".join(entity["modules"]),
            ";".join(entity["ce_sets"]),
            ";".join(entity["licenses"]),
            ";".join(abi.get("architectures") or [])))
    abi_rows.sort(key=lambda r: r[1].lower())
    write_tsv(os.path.join(REPORTS, "abi.tsv"),
              ["entity", "name", "kinds", "surface", "calling_conventions",
               "declarations_without_convention", "syntax_declarations",
               "declared_members", "typed_members", "bitfield_members",
               "abi_flags", "abi_notes", "documented_offsets",
               "stated_size_bytes", "headers", "modules", "ce_sets",
               "licenses", "architectures"], abi_rows)

    # ---- the documented offsets, one row per layout-table row
    offset_rows = []
    for record in abi_offsets:
        offset_rows.append((
            record["entity"] or "", record["member"], record["offset"],
            record["offset_printed"], record["size"] if record["size"] is not None else "",
            record["size_unit"] or "", "yes" if record["matches_declared_member"]
            else "no", record["source"]["path"], record["page_id"],
            record["source"]["title"], record["table"], record["row"],
            record["license"]))
    write_tsv(os.path.join(KB, "abi-offsets.tsv"),
              ["entity", "member", "offset", "offset_printed", "size",
               "size_unit", "matches_declared_member", "page", "page_id",
               "title", "table", "row", "license"], offset_rows)

    # ---- numbered constants a page prints in a name/value table
    constant_rows = []
    for record in constants:
        constant_rows.append((
            record["name"], record["value"], record["decimal"] or "",
            ";".join(record["headers"]), record["page_entity"] or "",
            record["source"]["path"], record["page_id"],
            record["source"]["title"], record["table"], record["row"],
            record.get("origin") or "table", record["license"]))
    write_tsv(os.path.join(KB, "constants.tsv"),
              ["name", "value", "decimal", "headers", "page_entity", "page",
               "page_id", "title", "table", "row", "origin", "license"],
              constant_rows)

    # ---- constants a page documents WITHOUT a number (name lists)
    named_rows = []
    for fact in facts:
        for item in fact.get("constant_names") or []:
            named_rows.append((
                item["name"], fact["path"], fact["page_id"], fact["book"],
                fact["title"], item["table"], item["row"],
                license_of(fact["path"])))
    named_rows.sort(key=lambda r: (r[0].lower(), r[1]))
    print(f"[kb] {len(named_rows):,} unnumbered constant name(s) from "
          f"{len({row[1] for row in named_rows}):,} page(s)", flush=True)
    write_tsv(os.path.join(KB, "constant-names.tsv"),
              ["name", "page", "page_id", "set", "title", "table", "row",
               "license"],
              named_rows)

    # ---- the members a page documents without printing a declaration
    field_pages = [f for f in facts if f["documented_fields"]]
    field_pages_no_decl = [f for f in field_pages
                           if not any(d["role"] == "syntax"
                                      for d in f["declarations"])]
    field_rows = []
    for entity in entities:
        for order, name in enumerate(entity["documented_fields"], 1):
            field_rows.append((entity["id"], name, order,
                               entity["documented_fields_page"] or ""))
    field_rows.sort(key=lambda r: (r[0], r[2]))
    write_tsv(os.path.join(KB, "struct-fields.tsv"),
              ["entity", "field", "order", "page"], field_rows)

    # ---- export ordinals: the only `name @ordinal` the documents print
    ordinal_rows = []
    for fact in facts:
        for item in fact.get("export_ordinals") or []:
            ordinal_rows.append((
                item["name"], item["ordinal_printed"], item["dll"],
                ce_api_names.entity_id(item["name"]),
                fact["path"], fact["page_id"], fact["book"], fact["title"],
                item["table"], item["row"], item["dll_evidence"],
                license_of(fact["path"])))
    ordinal_rows.sort(key=lambda r: (r[2].lower(), int(r[1])))
    print(f"[kb] {len(ordinal_rows):,} export ordinal(s) from "
          f"{len({row[4] for row in ordinal_rows}):,} page(s)", flush=True)
    write_tsv(os.path.join(KB, "export-ordinals.tsv"),
              ["name", "ordinal", "dll", "entity", "page", "page_id", "set",
               "title", "table", "row", "dll_evidence", "license"],
              ordinal_rows)

    # ---- constants a CE page lists as not supported (or as the only ones)
    unsupported_rows = []
    for fact in facts:
        for item in fact.get("unsupported_constants") or []:
            status = "not-supported" if item["negated"] else "only-supported"
            for name in item["names"]:
                unsupported_rows.append((
                    name, status, fact["entity"] or "", item["intro"],
                    fact["path"], fact["page_id"], fact["book"],
                    fact["title"], license_of(fact["path"])))
    unsupported_rows.sort(key=lambda r: (r[0], r[4]))
    print(f"[kb] {len(unsupported_rows):,} stated-unsupported constant(s) "
          f"over {len({row[4] for row in unsupported_rows}):,} page(s)",
          flush=True)
    write_tsv(os.path.join(KB, "unsupported-constants.tsv"),
              ["name", "status", "page_entity", "statement", "page",
               "page_id", "set", "title", "license"],
              unsupported_rows)

    # ---- "Windows CE supports only the Unicode version of this function"
    unicode_rows = []
    for entity in entities:
        for item in entity.get("unicode_only") or []:
            unicode_rows.append((
                entity["id"], entity["name"],
                ";".join(entity["kinds"]), item["subject"],
                item.get("scope", "system"), item["text"],
                ";".join(variant["name"] for variant in entity["variants"]
                         if variant["kind"] == "ansi"),
                item["page"], item["page_id"], item["set"], item["license"]))
    unicode_rows.sort(key=lambda r: (r[1].lower(), r[6]))
    print(f"[kb] {len(unicode_rows):,} Unicode-only statement(s) over "
          f"{len({row[0] for row in unicode_rows}):,} name(s)", flush=True)
    write_tsv(os.path.join(KB, "unicode-only.tsv"),
              ["entity", "name", "kinds", "subject", "scope", "statement",
               "ansi_variant_documented_by_win32", "page", "page_id", "set",
               "license"],
              unicode_rows)

    # ---- the stated rules for building a module-definition file
    rule_rows = []
    for fact in facts:
        for item in fact.get("def_rules") or []:
            rule_rows.append((
                ";".join(item["topics"]), item["text"],
                fact["path"], fact["page_id"], fact["book"], fact["title"],
                license_of(fact["path"])))
    rule_rows.sort(key=lambda r: (r[0], r[2], r[1]))
    print(f"[kb] {len(rule_rows):,} stated .def/export rule(s) from "
          f"{len({row[2] for row in rule_rows}):,} page(s)", flush=True)
    write_tsv(os.path.join(KB, "def-rules.tsv"),
              ["topics", "statement", "page", "page_id", "set", "title",
               "license"],
              rule_rows)

    # ---- Windows CE modules: what the module pages state about the binary
    module_rows = []
    for fact in facts:
        for item in fact.get("module_facts") or []:
            module_rows.append((
                item["module"], item.get("component") or "", item["field"],
                item["value"], item.get("notes") or "",
                fact["path"], fact["page_id"], fact["book"], fact["title"],
                item["evidence"], license_of(fact["path"])))
    module_rows.sort(key=lambda r: (r[0].lower(), r[1].lower(), r[2], r[3]))
    print(f"[kb] {len(module_rows):,} module statement(s) from "
          f"{len({row[5] for row in module_rows}):,} Windows CE module page(s)",
          flush=True)
    write_tsv(os.path.join(KB, "modules-ce.tsv"),
              ["module", "component", "field", "value", "notes", "page",
               "page_id", "set", "title", "quote", "license"], module_rows)

    # ---- catalog-only names: what Windows CE actually prints for them
    write_tsv(os.path.join(REPORTS, "catalog-leads.tsv"),
              ["name", "entity", "ce_page_id", "ce_page", "ce_page_title",
               "ce_printed_names", "ce_syntax_blocks", "win32_page",
               "win32_documented_fields"],
              lead_rows)

    # ---- requirement values that name no file (kept, but not in the maps)
    filtered = collections.defaultdict(collections.Counter)
    for record in requirements:
        if record["field"] in ("library", "dll", "header", "component") \
                and not record["key"]:
            filtered[record["field"]][record["value"]] += 1
    write_tsv(os.path.join(REPORTS, "filtered-values.tsv"),
              ["field", "value", "pages"],
              [(field, value, count)
               for field, values in sorted(filtered.items())
               for value, count in values.most_common()])

    # ---- coverage per tree
    per_tree = collections.defaultdict(collections.Counter)
    for fact in facts:
        tree = fact["book"]
        counts = per_tree[tree]
        counts["pages"] += 1
        counts["pages_with_entity"] += bool(fact["entity"])
        counts["pages_with_requirements"] += bool(fact["requirements"])
        counts["pages_with_declaration"] += bool(fact["declarations"])
        counts["requirements"] += len(fact["requirements"])
        counts["declarations"] += len(fact["declarations"])
        counts["constraints"] += len(fact["constraints"])
    write_tsv(os.path.join(REPORTS, "coverage-by-tree.tsv"),
              ["tree", "pages", "pages_with_entity", "pages_with_requirements",
               "pages_with_declaration", "requirements", "declarations",
               "constraints"],
              [(tree, c["pages"], c["pages_with_entity"],
                c["pages_with_requirements"], c["pages_with_declaration"],
                c["requirements"], c["declarations"], c["constraints"])
               for tree, c in sorted(per_tree.items())])

    # ---- coverage per entity and the gap list
    declaration_sets = {}
    for record in declarations:
        if record["entity"] and record["role"] == "syntax":
            declaration_sets.setdefault(record["entity"], set()).add(
                record["source"]["set"])
    coverage_rows, gap_rows = [], []
    for entity in sorted(entities, key=lambda e: (not bool(e["ce_pages"]), e["id"])):
        row = (entity["id"], entity["name"], ",".join(entity["kinds"]),
               ",".join(entity["layers"]), ",".join(entity["ce_sets"]),
               len(entity["ce_pages"]), len(entity["win32_pages"]),
               len(entity["syntax_declarations"]), len(entity["declarations"]),
               len(entity["requirements"]), len(entity["headers"]),
               len(entity["libraries"]), len(entity["dlls"]),
               len(entity["constraints"]))
        coverage_rows.append(row)
        # ``no-*`` means the documents are silent.  A page that prints
        # ``Link Library: Not applicable.`` has answered the question, so
        # that entity is not a collection gap for the library; it is
        # listed as ``library-stated-none`` instead.
        stated = set(entity.get("stated_none") or ())
        missing = []
        if not entity["syntax_declarations"]:
            missing.append("no-declaration")
        if not entity["headers"]:
            missing.append("header-stated-none" if "header" in stated
                           else "no-header")
        if not entity["libraries"] and not entity["dlls"]:
            missing.append("library-stated-none"
                           if stated & {"library", "dll"} else "no-library")
        if entity.get("noise"):
            continue
        if missing and entity["doc_role"] in ("api-definition", "api-page"):
            elsewhere = ",".join(sorted(declaration_sets.get(entity["id"], set()) -
                                        set(entity["ce_sets"])))
            gap_rows.append((entity["id"], entity["name"], entity["doc_role"],
                             ",".join(entity["ce_sets"]), ",".join(missing),
                             len(entity["ce_pages"]), elsewhere,
                             "yes" if entity["win32_pages"] else "",
                             entity["ce_pages"][0] if entity["ce_pages"] else ""))
    write_tsv(os.path.join(REPORTS, "coverage.tsv"),
              ["entity", "name", "kinds", "layers", "ce_sets", "ce_pages",
               "win32_pages", "syntax_declarations", "declarations",
               "requirements", "headers", "libraries", "dlls", "constraints"],
              [row for row in coverage_rows])
    write_tsv(os.path.join(REPORTS, "gaps.tsv"),
              ["entity", "name", "doc_role", "ce_sets", "missing", "ce_pages",
               "declaration_in_other_sets", "has_win32_page", "example_page"],
              gap_rows)
    write_summary(facts, entities, declarations, requirements, constraints,
                  abi_offsets, constants, per_tree, gap_rows, ordinal_rows,
                  rule_rows, unicode_rows, unsupported_rows,
                  link_rows, conflict_rows, gap)
    return (facts, entities, declarations, requirements, constraints,
            abi_offsets, constants)


def jst_today():
    """The report date in the timezone the collection is run from (JST)."""
    now = datetime.datetime.now(datetime.timezone.utc) + datetime.timedelta(hours=9)
    return now.date().isoformat()


def write_summary(facts, entities, declarations, requirements, constraints,
                  abi_offsets, constants, per_tree, gap_rows,
                  ordinal_rows=(), rule_rows=(), unicode_rows=(),
                  unsupported_rows=(), link_rows=(), conflict_rows=(),
                  gap=None):
    def top(book):
        """learn/windows-ce-5.0/... -> learn/windows-ce-5.0 (the report unit)."""
        parts = book.split("/")
        if parts[0] in ("learn", "dotnet") and len(parts) > 1:
            return "/".join(parts[:2])
        if parts[0] == "msdn-library" and len(parts) > 1:
            return "/".join(parts[:2])
        if parts[0] == "chm" and len(parts) > 1:
            return "/".join(parts[:2])
        return book

    rolled = collections.defaultdict(collections.Counter)
    for book, counts in per_tree.items():
        rolled[top(book)].update(counts)
    per_tree = rolled
    decs_c = sum(1 for r in declarations if r["layer"] != "dotnet")
    # The ABI view, measured from the records themselves (never inferred):
    # a convention no page prints stays absent, and the number of declarations
    # that print none is reported so the gap is visible.
    syntax_records = [r for r in declarations if r["role"] == "syntax"]
    conventions = collections.Counter(r["calling_convention"] for r in syntax_records)
    typed_members = sum(1 for r in syntax_records
                        for type_text in (r.get("member_types") or [])
                        if type_text)
    member_lines = sum(len(r.get("members") or []) for r in syntax_records)
    abi_flags = collections.Counter(flag for r in syntax_records
                                    for flag in (r.get("abi_flags") or []))
    abi_notes = [c for c in constraints if c.get("kind") == "abi-note"]
    size_notes = [c for c in abi_notes
                  if c.get("pattern") == "abi: structure-size"]
    offset_pages = {r["source"]["path"] for r in abi_offsets}
    offset_matched = sum(1 for r in abi_offsets if r["matches_declared_member"])
    surface = collections.Counter(e["surface"] for e in entities)
    field_pages = [f for f in facts if f["documented_fields"]]
    field_pages_no_decl = [f for f in field_pages
                           if not any(d["role"] == "syntax"
                                      for d in f["declarations"])]
    with_variant_win32 = sum(
        1 for e in entities if e["win32_pages_from_variants"])
    constant_pages = {r["source"]["path"] for r in constants}
    # What each version's own pages state, which is all a generator for that
    # version may treat as its own.  A fact stated only by another version is
    # a borrow, and a number no page prints is not counted.
    ready_units = (
        "learn/windows-ce-5.0", "learn/windows-embedded-ce-6.0",
        "learn/windows-ce-net-4x", "chm/windows-ce-5.0",
        "chm/windows-ce-3.0", "chm/windows-ce-4.2",
        "mvb/windows-ce-1.0/PEGSDK", "msdn-library/wcedevcon-99",
        "msdn-library/techshelps",
    )
    in_unit = {unit: set() for unit in ready_units}
    for entity in entities:
        if entity.get("noise"):
            continue
        for book in entity.get("ce_sets") or []:
            for unit in ready_units:
                if book == unit or book.startswith(unit + "/"):
                    in_unit[unit].add(entity["id"])
    syntax_unit = {unit: set() for unit in ready_units}
    for record in declarations:
        if record.get("role") != "syntax" or not record.get("entity"):
            continue
        book = record["source"]["set"]
        for unit in ready_units:
            if book == unit or book.startswith(unit + "/"):
                syntax_unit[unit].add(record["entity"])
    header_unit = {unit: set() for unit in ready_units}
    library_unit = {unit: set() for unit in ready_units}
    for record in requirements:
        if not record.get("entity") or not record.get("key"):
            continue
        if record["field"] not in ("header", "library", "dll"):
            continue
        book = record["source"]["set"]
        for unit in ready_units:
            if book == unit or book.startswith(unit + "/"):
                (header_unit if record["field"] == "header"
                 else library_unit)[unit].add(record["entity"])
    const_rows = collections.Counter()
    const_names = {unit: set() for unit in ready_units}
    for record in constants:
        book = record["source"]["set"]
        for unit in ready_units:
            if book == unit or book.startswith(unit + "/"):
                const_rows[unit] += 1
                const_names[unit].add(record["name"])
    function_ids = {entity["id"] for entity in entities
                    if "function" in (entity.get("kinds") or [])
                    and not entity.get("noise")}

    def pct(part, whole):
        return f"{part:,} ({100 * part // whole if whole else 0}%)"

    lines = [
        "# Knowledge base coverage",
        "",
        f"Generated {jst_today()} by "
        "`python3 tools/build-kb.py`.",
        "",
        "The knowledge base is built from the pages in `corpus/` only: every "
        "declaration, requirement and constraint record quotes the page it came "
        "from. This report says how much of the corpus is *structured* so far, "
        "and what is missing -- it is the collection worklist, not a quality "
        "judgement of a document.",
        "",
        "## ABI",
        "",
        f"* syntax declarations: **{len(syntax_records):,}**; of those "
        f"**{conventions.get(None, 0):,}** print no calling convention (none is "
        f"guessed) and **{len(syntax_records) - conventions.get(None, 0):,}** "
        "print one ("
        + ", ".join(f"{name} {count:,}" for name, count
                    in conventions.most_common() if name) + ")",
        f"* member lines that print a type: **{typed_members:,}** out of "
        f"**{member_lines:,}**; bitfields **{abi_flags.get('bitfield', 0):,}**, "
        f"`#pragma pack` **{abi_flags.get('pack', 0):,}**, "
        f"`__declspec(align` **{abi_flags.get('align', 0):,}**",
        f"* statements a page makes about alignment, byte order, pointer width "
        f"or a structure size: **{len(abi_notes):,}** quoted sentences "
        "(`kind: \"abi-note\"` in `kb/constraints.jsonl`; the structure-size "
        "sentences are counted again on their own line below)",
        f"* layout tables (`Offset | Field | Size | …`): **{len(abi_offsets):,}** "
        f"documented offset rows over **{len(offset_pages):,}** page(s), quoted "
        f"row by row in `kb/abi-offsets.jsonl` (the flat view is "
        f"`kb/abi-offsets.tsv`, with the page and its title). "
        f"**{offset_matched:,}** of the rows name a member the same page "
        "declares in a syntax block; the others are rows whose field the page "
        "does not declare (wire/packet layouts, array spellings such as "
        "`dwIndex[0]` where the declaration says `dwOffset`, and string "
        "literals inside the table) -- each is kept as the page printed it, "
        "and the column is marked `matches_declared_member`",
        f"* structure sizes stated in prose: **{len(size_notes):,}** sentences "
        "(the number is a read of the quoted sentence, never a guess)",
        f"* numbered constants (`Name | Value`, `Return code | Hexadecimal | "
        f"Decimal`, `Symbolic constant | Value (Hex)`, `Control code | Value`, "
        f"`Message identifier | Value`, `Element | Hex code`, "
        f"`Value | Weight` for the font-weight constants, a cell printed "
        f"`NAME = 0x0001` or `NAME (0x0001)`, and "
        f"the same shapes): **{len(constants):,}** rows over "
        f"**{len(constant_pages):,}** page(s), quoted in `kb/constants.jsonl` "
        "(the flat view is `kb/constants.tsv`).  A row is kept only when the "
        "name is one identifier and the value is one number; a one-letter "
        "`A=0` cell is left out, and a hexadecimal is never converted.  A "
        "decimal is kept only when the page prints one.  A constant the page "
        "does not number has no row",
        "* where a page states **no** offset, none is recorded: for the "
        "structures whose members a page documents without printing a body, "
        "`kb/struct-fields.tsv` keeps the names and documented order only, and "
        "`reports/abi.tsv` says how many offsets a name has (0 for most)",
        "",
        "## Totals",
        "",
        f"* pages parsed: **{len(facts):,}**",
        f"* API entities: **{len(entities):,}** -- CE-specific "
        f"**{surface.get('ce-only', 0):,}**, documented by Windows CE and the "
        f"Win32 reference alike **{surface.get('shared', 0):,}**, Win32 pages "
        f"for a CE name's A/W spelling **{surface.get('win32-spelling', 0):,}**, "
        f"named by the CE catalog only **{surface.get('catalog-only', 0):,}**, "
        f"unclaimed Win32 pages **{surface.get('win32-only', 0):,}** "
        f"(`reports/surface.tsv`; {with_variant_win32:,} names have a Win32 "
        "page through a variant spelling)",
        f"* declarations extracted: **{len(declarations):,}** "
        f"(C/C++ {decs_c:,} in `kb/declarations.jsonl`, managed-code "
        f"signatures {len(declarations) - decs_c:,} in "
        f"`kb/declarations-dotnet.jsonl` -- the separated .NET layer)",
        f"* requirement statements: **{len(requirements):,}**",
        f"* of those, a page's own `Module` (not an sdk-api UID): "
        f"**{sum(1 for r in requirements if r.get('label') == 'Module'):,}**; "
        f"a `sysgen` variable: "
        f"**{sum(1 for r in requirements if r.get('field') == 'sysgen'):,}**; "
        f"a CPU list (`Architecture`): "
        f"**{sum(1 for r in requirements if r.get('field') == 'architecture'):,}**; "
        f"a catalog `Component`: "
        f"**{sum(1 for r in requirements if r.get('field') == 'component' and r.get('key')):,}**",
        f"* numbered constants: **{len(constants):,}** "
        f"(`kb/constants.jsonl`, {len(constant_pages):,} page(s))",
        f"* constant -> header linkage: **{len(link_rows):,}** rows over "
        f"**{len({row[0] for row in link_rows}):,}** names "
        f"(`kb/constant-headers.tsv`; ranks: "
        + (", ".join(
            f"`{rank}` {sum(1 for row in link_rows if row[2] == rank):,}"
            for rank in LINK_RANKS
            if any(row[2] == rank for row in link_rows)) or "none")
        + (f"); **{len(gap or {}):,}** name(s) wait in "
           "`reports/constant-header-gaps.tsv` ("
           + ", ".join(
               f"{kind} {sum(1 for entry in (gap or {}).values() if entry.get('class') == kind):,}"
               for kind in ("needs-sdk-verification", "vb-language-constant",
                            "ole-automation-constant"))
           + ")" if gap else ")"),
        f"* value disagreements examined: **{len(conflict_rows):,}** "
        "name(s) whose pages print more than one number and cannot be a "
        "version branch (`kb/constant-conflicts.tsv`; categories: "
        + (", ".join(
            f"{kind} {sum(1 for row in conflict_rows if row[3] == kind):,}"
            for kind in ("same-page", "same-set", "version-overlap")
            if any(row[3] == kind for row in conflict_rows)) or "none")
        + ")",
        f"* Windows CE constraint sentences: "
        f"**{sum(1 for c in constraints if c.get('kind') != 'abi-note'):,}** "
        f"and ABI statements quoted from the pages "
        f"(**{sum(1 for c in constraints if c.get('kind') == 'abi-note'):,}**, "
        "`kind: \"abi-note\"`)",
        f"* entities with a gap record: **{len(gap_rows):,}** "
        "(`reports/gaps.tsv`)",
        f"* structures whose members a page documents without printing a "
        f"declaration body: **{sum(1 for e in entities if e['documented_fields']):,}**"
        f" ({len(field_pages):,} page(s) carry a member list, "
        f"{len(field_pages_no_decl):,} of them print no declaration at all; "
        "`kb/struct-fields.tsv` has the member names and order, one row per "
        "field -- the pages state no offsets, so none are recorded)",
        f"* relations between definitions: "
        f"**{sum(len(e['relations']) for e in entities):,}** "
        "(`unicode-ansi`/`unicode-ansi-base`/`unicode-ansi-variant` from the "
        "page's own statement, `interface-method`, `layer`, `ce-name-lead` "
        "for the spelling a CE page prints, `related-macro` / "
        "`related-message` for the identifier a page prints beside that label)",
        f"* catalog-only names (the CE TOC names it, no CE page for it is in "
        f"the corpus): **{surface.get('catalog-only', 0):,}** "
        "(`reports/catalog-leads.tsv` shows the CE page the name list points"
        " at, what that page actually prints, and what the Win32 page"
        " documents -- a lead, not a CE definition)",
        "* requirement values that name no file (a library statement like "
        "`Developer Implemented`) stay in `kb/requirements.jsonl` with an "
        "empty derived key and are listed in `reports/filtered-values.tsv`",
        "* a library/DLL cell that is only a list of file names "
        "(`Ole32.lib, Uuid.lib`, `A.lib or B.lib`) assigns each file.  "
        "The requirement record stays one statement and its derived key is "
        "the first file; `kb/libraries.tsv`, `kb/dlls.tsv` and "
        "`entity.libraries` / `entity.dlls` list every file the cell names.  "
        "A sentence that names one file (`Shell32.dll (version 4.0 or "
        "later)`) assigns that file only",
        "",
        "## What each tree contributed",
        "",
        "| tree | pages | with entity | with requirements | with declaration |"
        " requirements | declarations |",
        "|------|-------|-------------|-------------------|------------------|"
        "--------------|--------------|",
    ]
    for tree, c in sorted(per_tree.items(), key=lambda kv: -kv[1]["pages"]):
        lines.append(f"| `{tree}` | {c['pages']:,} | {c['pages_with_entity']:,} | "
                     f"{c['pages_with_requirements']:,} | "
                     f"{c['pages_with_declaration']:,} | {c['requirements']:,} | "
                     f"{c['declarations']:,} |")
    lines += ["",
              "The full per-book breakdown (one row per component CHM, mirror "
              "folder, ...) is `reports/coverage-by-tree.tsv`."]
    lines += [
        "",
        "## Reading the numbers",
        "",
        "* *with requirements / with declaration* counts pages, not entities: a "
        "page of prose has neither, and that is expected.",
        "* `corpus/site/` and `corpus/kb/` are mostly prose and release notes, so "
        "their reference coverage is low by nature.",
        "* The `.NET` tree (`corpus/dotnet/`) is documentation of a layer on top "
        "of Windows CE; its `Namespace:`/`Assembly:` values are recorded in the "
        "same requirement records, with `layer: dotnet`, and are not part of the "
        "CE include/def surface.",
        "* The open-source documents (`corpus/oss/`) are `layer: oss`.  Each page "
        "is quoted as an `oss-statement`.  No entity, declaration or constant "
        "is minted from them, and the include/def generator does not emit them.",
        "",
        "## What a version's own pages state",
        "",
        "A header or a `.def` for one Windows CE version can only be built from "
        "what *that version's pages* state.  The columns count entities "
        "documented by the set, and — of those — how many have a syntax "
        "declaration, a header file and a library stated by a page of that "
        "same set.  A fact stated only by another version is not counted here "
        "(a generator may borrow it, and must say so).  A calling convention, "
        "an export ordinal or a constant with no value cell is absent because "
        "the documents do not state it.",
        "",
        "| set | entities | syntax | header | library | functions with all three | numbered constants |",
        "|-----|----------|--------|--------|---------|--------------------------|--------------------|",
    ]
    for unit in ready_units:
        ents = in_unit[unit]
        if not ents and not const_rows[unit]:
            continue
        funcs = function_ids & ents
        all_three = (funcs & syntax_unit[unit] & header_unit[unit]
                     & library_unit[unit])
        lines.append(
            f"| `{unit}` | {len(ents):,} | {len(syntax_unit[unit] & ents):,} | "
            f"{len(header_unit[unit] & ents):,} | "
            f"{len(library_unit[unit] & ents):,} | "
            f"{len(all_three):,} / {len(funcs):,} | "
            f"{const_rows[unit]:,} ({len(const_names[unit]):,} names) |")
    lines += [
        "",
        "Numbered constants are rows of a name/value table the page prints, "
        "or a cell it prints as `NAME = 0x0001` / `NAME (0x0001)` "
        "(`kb/constants.jsonl`).  A heading such as `Value (Hex)`, "
        "`Control code`, `Message identifier`, `Hex code` or `Weight` is "
        "read when the cells are one identifier and one number.  Digits in "
        "a column the page heads as hexadecimal are stored as printed; "
        "`0x` is not added.  A scan code beside a virtual key, a code page "
        "beside a character set, and a locale beside an LCID are not "
        "constant values, so those tables are not read.  No page prints the "
        "decorated form (`_Name@N`) of a Windows CE export, so no decorated "
        "symbol is recorded; the compiler's decoration *rules* are "
        "documented, and those sentences are quoted in `kb/def-rules.tsv` "
        "under the `name-decoration` topic.",
        "",
        f"**Export ordinals.**  One page family does print them: "
        f"`Exports from the Floating Point C Run-Time Library` lists "
        f"`Export | Ordinal` for `Fpcrt.dll`.  "
        f"{len(ordinal_rows):,} ordinals over "
        f"{len({row[4] for row in ordinal_rows}):,} page(s) are in "
        f"`kb/export-ordinals.tsv`, the number as printed, with the "
        f"sentence that names the DLL.  Every other page states none, and "
        f"none is invented for them.",
        "",
        f"**Constants the pages take away.**  {len(unsupported_rows):,} "
        f"name(s) are listed by a CE page after \"does not support the "
        f"following ...\" (or, for a few, as the only values it does "
        f"support): `kb/unsupported-constants.tsv`, with the sentence that "
        f"introduces the list.  `GetSystemMetrics` alone loses 47 `SM_` "
        f"values.  A header generated from the Win32 reference would define "
        f"all of them; this file is the document saying which are not on "
        f"the device.",
        "",
        f"**Unicode only.**  {len(unicode_rows):,} statement(s) say that "
        f"Windows CE supports only Unicode "
        f"({sum(1 for row in unicode_rows if row[4] == 'this-api'):,} of "
        f"them about the API the page documents, the rest about the system) "
        f"-- `kb/unicode-only.tsv`.  Where the Win32 reference "
        f"documents an `A` spelling of the same name, the two documents "
        f"disagree about two different systems: the CE page governs the "
        f"device, and a generated header or `.def` must not carry the ANSI "
        f"spelling for it.  Both quotations are kept.",
        "",
        f"**The rules for the file itself.**  {len(rule_rows):,} sentence(s) "
        f"on {len({row[2] for row in rule_rows}):,} page(s) state how a "
        f"module-definition file, an `EXPORTS` section, `dllexport`, an "
        f"ordinal or a decorated name behaves; they are quoted with their "
        f"topic in `kb/def-rules.tsv`.  Among them the documents state that "
        f"a 32-bit `.def` lists `__cdecl`, `__stdcall` and `__fastcall` "
        f"functions undecorated -- a generator that writes `_Name@N` into "
        f"`EXPORTS` would contradict the source.",
        "",
        "## The gaps",
        "",
        "`reports/gaps.tsv` lists, for every CE-only entity, which of the three "
        "things an include/def generator needs is missing from the documents "
        "collected so far:",
        "",
        "`doc_role` in `kb/entities.jsonl` says what the corpus has for a name: "
        "`api-definition` (a page prints its syntax), `api-page` (a reference "
        "page without a syntax block -- the gap this list is about) or `topic` "
        "(the name is only the title of a prose page, so it is not listed here).",
        "",
        "| missing | entities | what to collect |",
        "|---------|----------|-----------------|",
        f"| `no-declaration` | "
        f"{sum(1 for g in gap_rows if 'no-declaration' in g[4]):,} | the page "
        "prints no syntax block -- look for the same topic in another collected "
        "set (another medium often has it), or add the SDK/DOC medium that does |",
        f"| `no-header` | {sum(1 for g in gap_rows if 'no-header' in g[4]):,} | "
        "the page has no `Header` requirement -- same approach |",
        f"| `no-library` | {sum(1 for g in gap_rows if 'no-library' in g[4]):,} | "
        "the page has no `Link Library`/`Library` requirement -- expected for "
        "compiler intrinsics and macros, worth collecting for functions |",
        f"| `header-stated-none` | "
        f"{sum(1 for g in gap_rows if 'header-stated-none' in g[4]):,} | "
        "nothing: the page prints `Header: Not applicable` / `None` / "
        "`Developer Implemented`, so the documents have answered |",
        f"| `library-stated-none` | "
        f"{sum(1 for g in gap_rows if 'library-stated-none' in g[4]):,} | "
        "nothing: the page prints `Link Library: Not applicable` / `None`, "
        "so there is no library to collect |",
        "",
        "The `*-stated-none` rows are **not** a collection worklist: they are "
        "the pages that answered the question.  They are listed so that the "
        "silence of a page and the statement of a page are never counted as "
        "the same thing.",
        "",
        "## Using it",
        "",
        "* `kb/entities.jsonl` -- one record per API name; `headers`, `libraries` "
        "and `dlls` are the include/link mapping, `syntax_declarations` the "
        "evidence for the declaration, `ce_sets` the version scope.",
        "* `kb/entities.jsonl` `relations` -- the links between definitions "
        "(the page's own Unicode/ANSI pair, `Interface::Method`, the CE<->Win32 "
        "layer match, `ce-name-lead` for a name the CE page prints under a "
        "different spelling), each with its page and the printed text; "
        "`present` says whether the target exists in this file.",
        "* `kb/entities.jsonl` `generation_use` -- the derived, rule-based list "
        "of generator steps the record can feed (`include-declaration`, "
        "`type-definition`, `link-library`, `def-export`, `abi-layout`, "
        "`abi-members` when only the documented member list exists, "
        "`abi-note` when the declarations or pages state ABI facts, "
        "`unicode-mapping`, `version-scope`, `ce-restriction`). It says what "
        "the record *can* be used for, with the fields that justify it.",
        "* `kb/modules.tsv` -- sdk-api module -> entities (the Win32-side "
        "grouping; the module comes from each page's UID).",
        "* `kb/modules-ce.tsv` -- what a Windows CE *module* page states "
        "about the binary: the components of `coredll`, `gwe`, `nk`, ..., "
        "the `.lib` each component is imported from, and the header and "
        "link library of the module's own functions. The `notes` cell "
        "(`Required`, `Exposes no public functions.`) is the page's own "
        "words. A module name is not a DLL name: only a page that prints "
        "`Coredll.dll` states one.",
        "* `kb/declarations.jsonl` -- the raw C/C++ declarations. Nothing is "
        "normalised: an include generator reads the text and the `spacing` flag.",
        "* `kb/declarations-dotnet.jsonl` -- the signature blocks of the "
        "separated .NET layer (`language: managed`), kept out of the C "
        "declaration file on purpose.",
        "* `kb/requirements.jsonl` -- Header/Library/DLL/OS-version statements "
        "with both the mapped `field` and the page's own `label`.",
        "* `kb/constraints.jsonl` -- the Windows CE restriction sentences "
        "(`kind: \"ce-restriction\"`) and the ABI sentences a page states "
        "(`kind: \"abi-note\"`, with the `pattern` that matched: alignment, "
        "byte order, pointer width, structure size). Each is quoted, not "
        "summarised.",
        "* `kb/constants.jsonl` -- one row of a name/value table a page prints, "
        "or one cell printed `NAME = 0x0001` / `NAME (0x0001)` "
        "(the identifier and the number, both as printed; `decimal` only when "
        "the page prints a decimal beside the value; `headers` only the header "
        "files that same page names). A constant the page does not number is "
        "not here.",
        "* `kb/sets.tsv`, `kb/headers.tsv`, `kb/libraries.tsv`, `kb/dlls.tsv`, "
        "`kb/modules.tsv` -- the same data aggregated.",
        "",
    ]
    os.makedirs(REPORTS, exist_ok=True)
    with open(os.path.join(REPORTS, "summary.md"), "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines) + "\n")


# ---------------------------------------------------------------------- main

def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--tree", help="only this corpus tree (e.g. learn/windows-ce-5.0)")
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--workers", type=int, default=min(8, os.cpu_count() or 4))
    ap.add_argument("--report", action="store_true", help="print totals, write nothing")
    ap.add_argument("--plain", action="store_true",
                    help="write the JSONL files uncompressed (they are gzipped by default)")
    args = ap.parse_args()

    global CATALOGS
    CATALOGS = read_catalogs()
    rows = read_index(args.tree)
    if args.limit:
        rows = rows[:args.limit]
    print(f"[kb] parsing {len(rows):,} page(s) with {args.workers} worker(s)",
          flush=True)
    (facts, entities, declarations, requirements, constraints,
     abi_offsets, constants) = build(rows, args.workers, args.report, args.plain)
    print(f"[kb] entities={len(entities):,} declarations={len(declarations):,} "
          f"requirements={len(requirements):,} constraints={len(constraints):,} "
          f"abi-offsets={len(abi_offsets):,} constants={len(constants):,}",
          flush=True)
    if not args.report:
        print(f"[kb] written to knowledge/ (see knowledge/reports/summary.md)")
        # Consumer view: one name, one CE-preferred fact.
        import importlib.util
        unify_path = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                  "build-unified-kb.py")
        spec = importlib.util.spec_from_file_location("build_unified_kb",
                                                      unify_path)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        mod.build()
        print("[kb] unified view written to knowledge/unified/", flush=True)
        print("[kb] after extractor changes also run "
              "python3 tools/harvest-corpus-kb.py && "
              "python3 tools/build-unified-kb.py", flush=True)
    return 0


CATALOGS = {}

if __name__ == "__main__":
    sys.exit(main())
