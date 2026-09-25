#!/usr/bin/env python3
"""tools/devsurface/vocab.py -- controlled vocabularies for the Development
Surface database (`devsurface/`).

This module deliberately contains **no knowledge about Windows CE APIs**.
It only holds:

  * the controlled vocabularies used by the record schemas, and
  * mechanical mapping tables that translate strings *as written in the
    corpus documents* into database values.

Anything that is not present in a mapping table is reported as unmapped.
Nothing in this module may be used to guess a value that the source
document does not state (see devsurface/METHODOLOGY.md).

Dependencies: standard library only.
"""

from __future__ import annotations

import re

SCHEMA_VERSION = 1
TOOL_VERSION = "1.0.0"

# --------------------------------------------------------------------------
# Source registry: one id per documentation collection held in this corpus.
# `rights` is recorded per collection; see devsurface/RIGHTS.md.
# --------------------------------------------------------------------------

SOURCES = {
    "mslearn-windows-ce-5.0": {
        "kind": "official_documentation_online",
        "publisher": "Microsoft Corporation",
        "book_path": "docs/mslearn/windows-ce-5.0",
        "collection": "Microsoft Learn previous-versions, Windows CE 5.0 product documentation",
        "version_scope": ["Windows CE 5.0"],
        "locator_template": "https://learn.microsoft.com/en-us/previous-versions/windows/embedded/{page_id}",
        "rights": "cc-by-4.0",
    },
    "mslearn-windows-ce-net-4x": {
        "kind": "official_documentation_online",
        "publisher": "Microsoft Corporation",
        "book_path": "docs/mslearn/windows-ce-net-4x",
        "collection": "Microsoft Learn previous-versions, Windows CE .NET 4.x documentation",
        "version_scope": ["Windows CE .NET 4.0", "Windows CE .NET 4.1", "Windows CE .NET 4.2"],
        "locator_template": "https://learn.microsoft.com/en-us/previous-versions/windows/embedded/{page_id}",
        "rights": "cc-by-4.0",
    },
    "mslearn-windows-embedded-ce-6.0": {
        "kind": "official_documentation_online",
        "publisher": "Microsoft Corporation",
        "book_path": "docs/mslearn/windows-embedded-ce-6.0",
        "collection": "Microsoft Learn previous-versions, Windows Embedded CE 6.0 documentation",
        "version_scope": ["Windows Embedded CE 6.0"],
        "locator_template": "https://learn.microsoft.com/en-us/previous-versions/windows/embedded/{page_id}",
        "rights": "cc-by-4.0",
    },
    "mslearn-windows-embedded-compact-7": {
        "kind": "official_documentation_online",
        "publisher": "Microsoft Corporation",
        "book_path": "docs/mslearn/windows-embedded-compact-7",
        "collection": "Microsoft Learn previous-versions, Windows Embedded Compact 7 documentation",
        "version_scope": ["Windows Embedded Compact 7"],
        "locator_template": "https://learn.microsoft.com/en-us/previous-versions/windows/embedded/{page_id}",
        "rights": "cc-by-4.0",
    },
    "mslearn-uncategorized": {
        "kind": "official_documentation_online",
        "publisher": "Microsoft Corporation",
        "book_path": "docs/mslearn/uncategorized",
        "collection": "Microsoft Learn previous-versions pages without a version marker in the title",
        "version_scope": ["unknown"],
        "locator_template": "https://learn.microsoft.com/en-us/previous-versions/windows/embedded/{page_id}",
        "rights": "cc-by-4.0",
    },
    "wayback-msdn-2010-05": {
        "kind": "official_documentation_archived",
        "publisher": "Microsoft Corporation",
        "book_path": "docs/wayback-msdn/2010-05",
        "collection": "MSDN Library snapshots preserved by the Internet Archive (Wayback Machine)",
        "version_scope": ["unknown"],
        "locator_template": "https://web.archive.org/web/2011/{page_id}",
        "rights": "archived-copy-rights-unknown",
    },
    "chm-windows-ce-3.0": {
        "kind": "official_download_archive",
        "publisher": "Microsoft Corporation",
        "book_path": "docs/chm/windows-ce-3.0",
        "collection": "Windows CE 3.0 documentation archive (Microsoft Download Center id=41197)",
        "version_scope": ["Windows CE 1.0", "Windows CE 2.0", "Windows CE 2.1", "Windows CE 3.0"],
        "locator_template": "archives/windows-ce-3.0/WindowsCE3.0_DocumentationArchive.zip::{page_id}",
        "rights": "archived-copy-rights-unknown",
    },
    "supplementary-windows-mobile-6.5": {
        "kind": "official_documentation_online",
        "publisher": "Microsoft Corporation",
        "book_path": "supplementary/windows-mobile-6.5",
        "collection": "Windows Mobile 6.5 supplementary reference topics",
        "version_scope": ["Windows Mobile 6.5"],
        "locator_template": "https://learn.microsoft.com/en-us/previous-versions/windows/embedded/{page_id}",
        "rights": "cc-by-4.0",
    },
    # Held in the corpus but explicitly outside the include/def/lib surface.
    # Pages under this collection are catalogued as out_of_scope, never read
    # for symbol records.
    "mslearn-dotnet-compact-framework": {
        "kind": "official_documentation_online",
        "publisher": "Microsoft Corporation",
        "book_path": "docs/mslearn/dotnet-compact-framework",
        "collection": "Microsoft Learn .NET Compact Framework class library reference",
        "version_scope": ["Windows CE .NET 4.x", "Windows CE 5.0", "Windows Embedded CE 6.0"],
        "locator_template": "https://learn.microsoft.com/en-us/previous-versions/windows/embedded/{page_id}",
        "rights": "cc-by-4.0",
        "out_of_scope": "Managed (.NET) class library surface: not part of the native include/def/lib development surface.",
    },
}

# Books that are extracted for symbol records, in processing order.
EXTRACT_BOOKS = [
    "chm-windows-ce-3.0",
    "wayback-msdn-2010-05",
    "mslearn-windows-ce-net-4x",
    "mslearn-windows-ce-5.0",
    "mslearn-windows-embedded-ce-6.0",
    "mslearn-windows-embedded-compact-7",
    "mslearn-uncategorized",
    "supplementary-windows-mobile-6.5",
]

# Books that are catalogued for coverage but never read for symbols.
CATALOG_ONLY_BOOKS = ["mslearn-dotnet-compact-framework"]

# --------------------------------------------------------------------------
# Records held in the CE media archives (archives/*). These are documentation
# media; they are recorded for provenance but are not parsed by extract.py.
# --------------------------------------------------------------------------

ARCHIVE_MEDIA = [
    ("archives/windows-ce-1.0", ["Windows CE 1.0"], "https://archive.org/details/ms-wince-desktopemulation-sdk-beta21"),
    ("archives/windows-ce-2.0", ["Windows CE 2.0"], "https://archive.org/details/Windows_CE_2.0_Technical_Information_Microsoft_1997"),
    ("archives/windows-ce-3.0", ["Windows CE 1.0", "Windows CE 2.0", "Windows CE 2.1", "Windows CE 3.0"],
     "https://www.microsoft.com/en-us/download/details.aspx?id=41197"),
    ("archives/windows-ce-4.2", ["Windows CE .NET 4.2"], "https://www.microsoft.com/en-us/download/details.aspx?id=44017"),
    ("archives/windows-ce-5.0", ["Windows CE 5.0"], "https://www.microsoft.com/en-us/download/details.aspx?id=17363"),
    ("archives/windows-ce-6.0", ["Windows Embedded CE 6.0"], "https://www.microsoft.com/en-us/download/details.aspx?id=22453"),
]

# --------------------------------------------------------------------------
# Field label vocabulary.
#
# Documents label the same requirement with different field names. The keys
# below are the label spellings observed in this corpus; the values are the
# canonical database field. A mapping is a *documented label to schema field*
# translation and is always recorded together with the original label, so a
# consumer can re-derive it. See devsurface/METHODOLOGY.md.
# --------------------------------------------------------------------------

REQUIREMENT_LABELS = {
    "os versions": "os_versions",
    "os version": "os_versions",
    "versions": "os_versions",
    "runs on": "platform",
    "runs on (os)": "platform",
    "header": "header",
    "headers": "header",
    "defined in": "header",
    "declared in": "header",
    "header file": "header",
    "include": "include",
    "includes": "include",
    "link library": "library",
    "link libraries": "library",
    "library": "library",
    "libraries": "library",
    "link to": "library",
    "dll": "module",
    "module": "module",
    "import library": "library",
    "namespace": "namespace",
    "assembly": "assembly",
    "platform": "platform",
    "compatibility": "compatibility",
    "applies to": "compatibility",
}

# --------------------------------------------------------------------------
# Symbol kind vocabulary.
# --------------------------------------------------------------------------

KINDS = [
    "function",          # function declarator documented on the page
    "interface",         # source documents an interface (COM/C++ class surface)
    "interface_method",  # title is Interface::Member and the declaration is a method
    "callback",          # typedef of a function pointer
    "macro",             # #define
    "struct",
    "union",
    "enum",
    "type",              # typedef that is not a function pointer
    "variable",
    "class",
    "constant",          # source itself labels the symbol as a constant
    "ioctl",             # source documents an input/output control code
    "unknown",
]

KIND_BASIS = [
    "declaration",        # kind read off the documented declaration form
    "source_label",       # kind stated by the source document
    "title_form",         # kind implied by the documented page title form only
    "unknown",
]

# Mechanical classification tags. A tag is a statement about the *documented
# text*, not about the API's semantics. Tags are recorded under
# `derived_tags` and never promoted to documented fields.
DERIVED_TAGS = {
    "numeric_literal_value": "replacement list of an object-like #define is a numeric literal",
    "string_literal_value": "replacement list of an object-like #define is a string literal",
    "function_like_macro": "object-like versus function-like #define form",
    "void_parameter_list": "parameter list is a single void",
    "unnamed_parameters": "parameter list has entries without an identifier",
    "variadic": "parameter list ends in ...",
}

# --------------------------------------------------------------------------
# Page classification vocabulary (devsurface/data/pages/<book>.tsv and each
# record's `page_class`). Every page of every collection gets exactly one value;
# the meanings are documented in devsurface/METHODOLOGY.md section 6.
# --------------------------------------------------------------------------

PAGE_CLASSES = [
    "symbol_page",
    "prose_page_code_fragment",
    "concept_or_overview",
    "duplicate_page",
    "identifier_title_no_requirements",
    "identifier_title_no_declaration",
    "declaration_candidate_mismatch",
    "example_code_page",
    "out_of_scope_managed_surface",
    "deprecation_notice",
]

# How the page presents the block the declaration was read from.
DOCUMENTATION_ROLES = [
    "declaration_section",
    "unlabelled_block_symbol_topic",
    "example_code_fragment",
    "declaration_not_documented",
]

# --------------------------------------------------------------------------
# Evidence status vocabulary (how a field came to exist).
# --------------------------------------------------------------------------

EVIDENCE_STATUS = [
    "documented",  # stated in the text of an official Microsoft document
    "observed",    # read from an artifact (binary/header) by direct inspection
    "reproduced",  # reproduced by running the toolchain/runtime
    "derived",     # computed by a mechanical rule from documented/observed data
    "inferred",    # reasoned guess; never usable as confirmed
    "unknown",     # not established by any available evidence
]

# Fields that must never carry a value without evidence. extract.py fills
# them with a null value plus evidence_status "unknown".
UNKNOWN_FIELDS = [
    "module",
    "export.name",
    "export.ordinal",
    "export.decorated_name",
    "calling_convention",
    "abi.architecture",
    "abi.data_model",
    "abi.structure_layout",
    "abi.packing",
    "abi.name_decoration",
]

# --------------------------------------------------------------------------
# Windows CE version vocabulary.
#
# Mapping keys are version numbers exactly as the documents write them.
# A value not present here is *unmapped*, not guessed.
# --------------------------------------------------------------------------

VERSION_VOCAB = {
    "1.0": {"version_id": "windows-ce-1.0", "generation": "ce-1.x"},
    "1.0a": {"version_id": "windows-ce-1.0a", "generation": "ce-1.x"},
    "1.0b": {"version_id": "windows-ce-1.0b", "generation": "ce-1.x"},
    "2.0": {"version_id": "windows-ce-2.0", "generation": "ce-2.x"},
    "2.01": {"version_id": "windows-ce-2.01", "generation": "ce-2.x"},
    "2.1": {"version_id": "windows-ce-2.1", "generation": "ce-2.x"},
    "2.10": {"version_id": "windows-ce-2.1", "generation": "ce-2.x"},
    "2.11": {"version_id": "windows-ce-2.11", "generation": "ce-2.x"},
    "2.12": {"version_id": "windows-ce-2.12", "generation": "ce-2.x"},
    "3.0": {"version_id": "windows-ce-3.0", "generation": "ce-3.x"},
    "4.0": {"version_id": "windows-ce-4.0", "generation": "ce-net-4.x"},
    "4.1": {"version_id": "windows-ce-4.1", "generation": "ce-net-4.x"},
    "4.2": {"version_id": "windows-ce-4.2", "generation": "ce-net-4.x"},
    "5.0": {"version_id": "windows-ce-5.0", "generation": "ce-5.x"},
    "6.0": {"version_id": "windows-embedded-ce-6.0", "generation": "ce-6.x"},
    "7.0": {"version_id": "windows-embedded-compact-7.0", "generation": "cec-7.x"},
}

# Product family spellings, longest match first.
FAMILY_VOCAB = [
    (r"windows\s+embedded\s+compact", "windows-embedded-compact", "Windows Embedded Compact"),
    (r"windows\s+embedded\s+ce", "windows-embedded-ce", "Windows Embedded CE"),
    (r"microsoft\s+windows\s+ce", "windows-ce", "Microsoft Windows CE"),
    (r"windows\s+ce\s*\.net", "windows-ce-net", "Windows CE .NET"),
    (r"windows\s+ce\s+os", "windows-ce-os", "Windows CE OS"),
    (r"windows\s+ce", "windows-ce", "Windows CE"),
    (r"pocket\s+pc", "pocket-pc", "Pocket PC"),
    (r"palm[- ]size\s+pc", "palm-size-pc", "Palm-size PC"),
    (r"handheld\s+pc", "handheld-pc", "Handheld PC"),
    (r"smartphone", "smartphone", "Smartphone"),
    (r"windows\s+mobile", "windows-mobile", "Windows Mobile"),
]

# Release suffixes that the documents spell out after the version number.
RELEASE_SUFFIX = re.compile(r"\b(R\d)\b", re.I)

# Qualifier phrases attached to a version number.
QUALIFIERS = [
    (r"^and\s+later$", "and later"),
    (r"^or\s+later$", "or later"),
    (r"^and\s+earlier$", "and earlier"),
    (r"^and\s+newer$", "and newer"),
    (r"^only$", "only"),
]

VERSION_RE = re.compile(r"(?<![\w.])(\d+)\.(\d+)([a-z])?(?![\w.])")
BARE_YEAR_RE = re.compile(r"(?<![\w.])(19\d{2}|20\d{2})(?![\w.])")


def normalize_ws(text: str) -> str:
    """Collapse all whitespace runs (including NBSP) to single spaces."""
    return re.sub(r"\s+", " ", (text or "").replace("\xa0", " ")).strip()


def map_kind_label(label: str):
    """Map a document-stated kind word to the kind vocabulary, else None."""
    key = normalize_ws(label).lower().rstrip(":")
    table = {
        "function": "function",
        "function pointer": "callback",
        "callback function": "callback",
        "macro": "macro",
        "constant": "constant",
        "structure": "struct",
        "struct": "struct",
        "union": "union",
        "enumeration": "enum",
        "enum": "enum",
        "typedef": "type",
        "type": "type",
        "variable": "variable",
        "class": "class",
        "interface": "interface_method",
        "method": "interface_method",
        "ioctl": "constant",
        "message": "constant",
    }
    return table.get(key)


def detect_family(text: str):
    """Return (family_id, family_label) for the first documented family spelling."""
    if not text:
        return None, None
    low = normalize_ws(text).lower()
    for pattern, family_id, label in FAMILY_VOCAB:
        if re.search(pattern, low):
            return family_id, label
    return None, None


def normalize_version_statement(raw: str):
    """Translate one documented version string into database values.

    Returns a dict with `status` in {mapped, partial, unmapped}. Only literals
    that appear in the string are produced; nothing is completed by guessing.
    """
    text = normalize_ws(raw)
    result = {
        "raw": (raw or "").strip(),
        "normalized_text": text,
        "family_id": None,
        "family_label": None,
        "version_number": None,
        "version_id": None,
        "generation": None,
        "release_suffix": None,
        "qualifier": None,
        "status": "unmapped",
    }
    if not text:
        return result

    family_id, family_label = detect_family(text)
    result["family_id"] = family_id
    result["family_label"] = family_label

    # Version numbers: the first literal in the string.
    #
    # A version number is only translated into a Windows CE version id when the
    # statement is about Windows CE itself. A statement such as
    # "Pocket PC 2002 and later" or "Smartphone 2003" keeps its literal number
    # and stays untranslated: mapping it to a CE version id would invent a
    # relation the document does not state.
    numbers = VERSION_RE.findall(text)
    if numbers:
        major, minor, letter = numbers[0]
        number = f"{major}.{minor}" + (letter or "")
        result["version_number"] = number
        ce_family = family_id in (None, "windows-ce", "windows-ce-os",
                                  "windows-ce-net", "windows-embedded-ce",
                                  "windows-embedded-compact")
        if ce_family:
            entry = VERSION_VOCAB.get(number)
            if entry is None and letter:
                entry = VERSION_VOCAB.get(f"{major}.{minor}")
            if entry is not None:
                result["version_id"] = entry["version_id"]
                result["generation"] = entry["generation"]

    suffix = RELEASE_SUFFIX.search(text)
    if suffix:
        result["release_suffix"] = suffix.group(1).upper()

    tail = text
    if numbers:
        tail = text[text.index(numbers[0][0] + "." + numbers[0][1]):]
        tail = re.sub(r"^\d+\.\d+[a-z]?", "", tail)
        tail = re.sub(r"^\s*R\d\s*", "", tail)
    tail = normalize_ws(tail).strip(" .,;")
    for pattern, qualifier in QUALIFIERS:
        if re.fullmatch(pattern, tail, re.I):
            result["qualifier"] = qualifier
            break

    if result["version_id"]:
        result["status"] = "mapped"
    elif numbers or family_id:
        result["status"] = "partial"
    else:
        result["status"] = "unmapped"
    return result


def record_shard(record) -> str:
    """Shard file name for a record: its header, else its include, else unknown."""
    header = (record.get("header") or {}).get("value")
    if header:
        return shard_name(header)
    include = (record.get("include") or {}).get("value")
    if include:
        return shard_name(include)
    return "unknown-header"


def canonical_kind_order():
    """Stable ordering used by generated Markdown indexes."""
    return list(KINDS)


def shard_name(header: str) -> str:
    """Shard file name for a header spelling (e.g. 'Winbase.h' -> 'winbase')."""
    if not header:
        return "unknown-header"
    name = header.strip().strip("<>").lower()
    name = re.sub(r"\.(h|hpp|hxx|idl|inc)$", "", name)
    name = re.sub(r"[^a-z0-9_.+-]+", "-", name).strip("-")
    return name or "unknown-header"
