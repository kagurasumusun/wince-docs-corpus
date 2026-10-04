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
import hashlib
import io
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import ce_api_names  # noqa: E402
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

TREE_LAYER = (
    ("corpus/win32/", "win32"),
    ("corpus/dotnet/", "dotnet"),
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

def parse_page(job):
    """One page -> its facts.  Runs in a worker process."""
    page_id, book, path, title = job
    layer = layer_of(book)
    fact = {"page_id": page_id, "book": book, "path": path, "title": title,
            "layer": layer, "entity": None, "entity_evidence": None,
            "display": None, "kind": None,
            "requirements": [], "declarations": [], "constraints": [],
            "documented_fields": [], "documented_fields_page": None,
            "abi_offsets": [], "constants": []}
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
        fact["constraints"] = [dict(note, kind="abi-note")
                               for note in page_parse.abi_notes(text)]
        # sdk-api documents every member of a structure under -struct-fields,
        # sometimes without printing a syntax block; that member list is a
        # documented fact (member names and order, no offsets), so it is kept.
        fact["documented_fields"] = [f["name"] for f in struct_fields]
        fact["documented_fields_page"] = path if struct_fields else None
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
    fact["declarations"] = page_parse.declarations(fragment)
    fact["constraints"] = [dict(item, kind="ce-restriction")
                           for item in page_parse.constraints(fragment)]
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


def requirement_records(facts, entity_of):
    records = []
    for fact in facts:
        for req in fact["requirements"]:
            key = hashlib.sha1(
                (fact["path"] + "\x00" + req["field"] + "\x00" +
                 req["value"]).encode("utf-8")).hexdigest()[:12]
            records.append({
                "id": "r" + key,
                "entity": entity_of(fact),
                "page_id": fact["page_id"],
                "layer": fact["layer"],
                "field": req["field"],
                "label": req["label"],
                "value": req["value"],
                "key": normalize_value(req["value"], req["field"]),
                "evidence": req["evidence"],
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
            records.append({
                "id": "k" + key,
                "name": item["name"],
                "value": item["value"],
                "decimal": item["decimal"],
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


def entity_records(facts, declarations, requirements):
    by_entity = collections.defaultdict(list)
    for fact in facts:
        if fact["entity"]:
            by_entity[fact["entity"]].append(fact)

    decl_by_entity = collections.defaultdict(list)
    for record in declarations:
        if record["entity"]:
            decl_by_entity[record["entity"]].append(record)
    req_by_entity = collections.defaultdict(list)
    for record in requirements:
        if record["entity"]:
            req_by_entity[record["entity"]].append(record)

    out = []
    for entity in sorted(by_entity):
        pages = by_entity[entity]
        licenses = sorted({license_of(f["path"]) for f in pages})
        ce_pages = sorted({f["path"] for f in pages if f["layer"] == "ce"})
        win32_pages = sorted({f["path"] for f in pages if f["layer"] == "win32"})
        dotnet_pages = sorted({f["path"] for f in pages if f["layer"] == "dotnet"})
        sets = sorted({f["book"] for f in pages if f["layer"] == "ce"})
        displays = collections.Counter(f["display"] for f in pages if f["display"])
        kinds = collections.Counter()
        for f in pages:
            if f["kind"]:
                kinds[f["kind"]] += 1
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
            "libraries": values("library"),
            "dlls": values("dll"),
            "unicode_ansi": values("unicode_ansi"),
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
    * ``interface-method`` -- the name is printed as ``Interface::Method``, so
      the method belongs to that interface's vtable;
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

    for entity in entities:
        name = entity["name"]
        if "::" in name:
            interface = name.split("::", 1)[0]
            entity["relations"].append({
                "type": "interface-method",
                "name": interface,
                "id": ce_api_names.normalize(interface),
                "present": ce_api_names.normalize(interface) in by_id,
                "evidence": name,
                "page": entity["ce_pages"][0] if entity["ce_pages"] else "",
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
        if record["field"] != field or not record["value"] or not record["key"]:
            continue
        entry = table[record["key"]]
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
            ";".join(entity["licenses"])))
    abi_rows.sort(key=lambda r: r[1].lower())
    write_tsv(os.path.join(REPORTS, "abi.tsv"),
              ["entity", "name", "kinds", "surface", "calling_conventions",
               "declarations_without_convention", "syntax_declarations",
               "declared_members", "typed_members", "bitfield_members",
               "abi_flags", "abi_notes", "documented_offsets",
               "stated_size_bytes", "headers", "modules", "ce_sets",
               "licenses"], abi_rows)

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
            record["license"]))
    write_tsv(os.path.join(KB, "constants.tsv"),
              ["name", "value", "decimal", "headers", "page_entity", "page",
               "page_id", "title", "table", "row", "license"], constant_rows)

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

    # ---- catalog-only names: what Windows CE actually prints for them
    write_tsv(os.path.join(REPORTS, "catalog-leads.tsv"),
              ["name", "entity", "ce_page_id", "ce_page", "ce_page_title",
               "ce_printed_names", "ce_syntax_blocks", "win32_page",
               "win32_documented_fields"],
              lead_rows)

    # ---- requirement values that name no file (kept, but not in the maps)
    filtered = collections.defaultdict(collections.Counter)
    for record in requirements:
        if record["field"] in ("library", "dll", "header") \
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
        missing = []
        if not entity["syntax_declarations"]:
            missing.append("no-declaration")
        if not entity["headers"]:
            missing.append("no-header")
        if not entity["libraries"]:
            missing.append("no-library")
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
                  abi_offsets, constants, per_tree, gap_rows)
    return (facts, entities, declarations, requirements, constraints,
            abi_offsets, constants)


def jst_today():
    """The report date in the timezone the collection is run from (JST)."""
    now = datetime.datetime.now(datetime.timezone.utc) + datetime.timedelta(hours=9)
    return now.date().isoformat()


def write_summary(facts, entities, declarations, requirements, constraints,
                  abi_offsets, constants, per_tree, gap_rows):
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
        f"Decimal`, a cell printed `NAME = 0x0001` or `NAME (0x0001)`, and "
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
        f"* numbered constants: **{len(constants):,}** "
        f"(`kb/constants.jsonl`, {len(constant_pages):,} page(s))",
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
        "for the spelling a CE page prints)",
        f"* catalog-only names (the CE TOC names it, no CE page for it is in "
        f"the corpus): **{surface.get('catalog-only', 0):,}** "
        "(`reports/catalog-leads.tsv` shows the CE page the name list points"
        " at, what that page actually prints, and what the Win32 page"
        " documents -- a lead, not a CE definition)",
        "* requirement values that name no file (a library statement like "
        "`Developer Implemented`) stay in `kb/requirements.jsonl` with an "
        "empty derived key and are listed in `reports/filtered-values.tsv`",
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
        "(`kb/constants.jsonl`).  Symbol decoration (`_Name@N`) and export "
        "ordinals are not in these documents, so none is recorded.",
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
    return 0


CATALOGS = {}

if __name__ == "__main__":
    sys.exit(main())
