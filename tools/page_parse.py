#!/usr/bin/env python3
"""tools/page_parse.py -- read one documentation page into structured facts.

This module is the bottom half of the knowledge base
(``tools/build-kb.py``).  It knows the page templates the corpus contains and
returns *only what the page says*, always with the raw evidence, so a record
can be checked against its source:

    page = page_parse.parse(path, book, page_id, title)
    page.system          # 'learn' | 'chm' | 'mvb' | 'msdn-library' | 'kb' | 'site'
                          # | 'win32-sdk-api'
    page.entity          # canonical API name (None for an article page)
    page.requirements    # [{'field': 'header', 'label': 'Header',
                          #   'value': 'Winbase.h.', 'evidence': 'Header: ...'}]
    page.declarations    # [{'text': 'HANDLE CreateFile(...)', 'markup': 'pre',
                          #   'spacing': 'preserved', 'role': 'syntax',
                          #   'members': [...]}]
    page.constraints     # [{'text': sentence, 'pattern': 'not supported'}]

Nothing here normalises a declaration: the text is quoted from the page
(whitespace and all), because an include/def generator has to see the original.
Two things *are* derived, and are labelled as such:

* ``spacing`` -- ``collapsed`` when the code block lost the spaces between
  tokens (the archived Learn pages sometimes render ``HANDLE CreateFile(`` as
  ``HANDLECreateFile(``); a consumer can prefer the same API's declaration from
  another source.  It is a property of the text, not a repair.
* ``field`` -- the requirement label mapped to a stable name (``Header file:``
  -> ``header``).  The original label is kept next to it.
"""

import html as _html
import re

# ---------------------------------------------------------------- documents

# The archived Learn pages wrap the article in site chrome whose markup carries
# words like "Header" (``uhfHeaderId``); the article starts at the first <h1>.
END_MARKERS = (
    '<div id="ms--inline-notifications"',
    '<div id="assertive-live-region"',
    '<div id="affixed-right-container"',
    'Send Feedback on this topic',
    '<div class="feedback-verbatim',
)
SCRIPT = re.compile(r"(?is)<(script|style|noscript)\b.*?</\1>")
HEAD_TAG = re.compile(r"(?is)^.*?<h1\b[^>]*>")
BLOCK_END = re.compile(r"(?i)</(p|div|li|tr|td|th|h[1-6]|pre|table|ul|ol|dl|dt|dd)>")
BR = re.compile(r"(?i)<br\s*/?>")
TAG = re.compile(r"(?s)<[^>]+>")
TITLE_RE = re.compile(r"(?is)<title>(.*?)</title>")
HEADING = re.compile(
    r"(?is)<h([1-6])[^>]*>(?:\s*<[^>]+>)*\s*([^<]{2,60}?)\s*(?:<[^>]+>)*</h\1>")

# Requirement labels of the templates in the corpus, mapped to a stable field.
LABEL_MAP = {
    "header": "header", "headers": "header", "header file": "header",
    "header files": "header", "include file": "header",
    "link library": "library", "library": "library", "link libraries": "library",
    "library file": "library", "import library": "library", "libraries": "library",
    "dll": "dll", "dlls": "dll", "dll file": "dll", "dynamic link library": "dll",
    "os versions": "os_versions", "os version": "os_versions",
    "windows ce versions": "os_versions", "windows ce version": "os_versions",
    "operating system": "os_versions", "platform": "os_versions",
    "windows embedded ce": "os_versions", "windows mobile": "os_versions",
    "namespace": "namespace", "assembly": "assembly", "class": "class",
    "requires": "requires", "requirement": "requires", "type": "type",
    "send feedback": None, "see also": None, "note": None, "notes": None,
    "reference": None, "applies to": "os_versions", "imports": "requires",
    "complete documentation": None, "online documentation": None,
    "sample application": None, "example": None, "unicode": "unicode_ansi",
    "unicode/ansi": "unicode_ansi", "ansi": "unicode_ansi",
}

CONSTRAINT_WORDS = (
    "not supported", "does not support", "do not support", "not implemented",
    "not available", "unsupported", "does not implement", "is not provided",
    "not provided", "no support for", "limitation", "restriction",
    "cannot be used", "must not be used", "is ignored",
)
CE_WORDS = ("windows ce", "windows embedded ce", "ce .net", "wince",
            "pocket pc", "handheld pc")


def decode(raw):
    """bytes -> str, deciding the encoding the way the rest of the tools do."""
    for codec in ("utf-8", "cp1252"):
        try:
            return raw.decode(codec)
        except UnicodeDecodeError:
            continue
    return raw.decode("utf-8", "replace")


def article_html(raw):
    """The article part of a harvested page (no site chrome)."""
    text = SCRIPT.sub(" ", decode(raw))
    match = HEAD_TAG.match(text)
    if match:
        text = text[match.end():]
    for marker in END_MARKERS:
        index = text.find(marker)
        if index > 0 and not text[:index].rstrip().endswith("</html>"):
            text = text[:index]
            break
    return text


def text_of(fragment, keep_newlines=True):
    """Tag -> text.  Block tags become newlines; inline tags vanish."""
    fragment = BR.sub("\n", fragment)
    fragment = BLOCK_END.sub("\n", fragment)
    fragment = TAG.sub("", fragment)
    text = _html.unescape(fragment)
    if keep_newlines:
        text = re.sub(r"[ \t\r\f\v\u00a0]+", " ", text)
        return re.sub(r"\n\s*\n+", "\n", text).strip()
    return re.sub(r"\s+", " ", text).strip()


def region(fragment, *headings, window=6000):
    """The part of an article that follows one of ``headings``."""
    for match in HEADING.finditer(fragment):
        title = text_of(match.group(0), keep_newlines=False).strip(": ")
        if title.lower() in headings:
            rest = fragment[match.end():]
            next_heading = HEADING.search(rest)
            if next_heading and next_heading.start() < window:
                rest = rest[:next_heading.start()]
            return rest[:window]
    return ""


# ------------------------------------------------------------- requirements

ROW = re.compile(r"(?is)<tr\b[^>]*>(.*?)</tr>")
CELL = re.compile(r"(?is)<t[dh]\b[^>]*>(.*?)</t[dh]>")
LINE_LABEL = re.compile(r"([A-Za-z][A-Za-z /+.]{2,28}?)\s*:\s*([^\n]{1,200})")


FILEISH = re.compile(r"[A-Za-z0-9_.+\-]+\.(h|hpp|hh|hxx|lib|dll|hlp|inc)\b", re.I)
PROSE_WORDS = re.compile(r"\b(this|your|the|to|of|for|and|see|use|must|not)\b", re.I)


def _plausible(field, value):
    """Reject prose that a template put into a requirement table cell.

    ``Add this macro to your class's header file`` is a *description* of an
    MFC header requirement, not a header name; a header/library/DLL value has
    to look like a file name (or be a short bare name).
    """
    if field in ("header", "library", "dll"):
        if len(value) > 120 or PROSE_WORDS.search(value):
            return len(value.split()) <= 2 and bool(FILEISH.search(value))
        if not FILEISH.search(value) and len(value.split()) > 2:
            return False
    return True


def _field(label):
    key = re.sub(r"\s+", " ", label.strip().rstrip(":")).lower()
    if key in LABEL_MAP:
        return LABEL_MAP[key]
    return "other"


def requirements(fragment):
    """Requirement label/value pairs, from a table or from ``Label: value``."""
    out = []
    seen = set()
    for heading in ("requirements", "at a glance", "requirements", "system requirements"):
        block = region(fragment, heading)
        if not block:
            continue
        for row in ROW.finditer(block):
            cells = [text_of(c, keep_newlines=False) for c in CELL.findall(row.group(1))]
            if len(cells) < 2 or not cells[0]:
                continue
            label = cells[0].rstrip(":").strip()
            value = " ".join(c for c in cells[1:] if c).strip()
            field = _field(label)
            if not field or not value or (field, value) in seen \
                    or not _plausible(field, value):
                continue
            seen.add((field, value))
            out.append({"field": field, "label": label, "value": value,
                        "evidence": f"{label}: {value}"})
        plain = text_of(block)
        for match in LINE_LABEL.finditer(plain):
            label, value = match.group(1).strip(), match.group(2).strip()
            field = _field(label)
            if not field or not value or (field, value) in seen \
                    or not _plausible(field, value):
                continue
            seen.add((field, value))
            out.append({"field": field, "label": label, "value": value,
                        "evidence": match.group(0).strip()})
        if out:
            break
    return out


# ------------------------------------------------------------- declarations

PRE = re.compile(r"(?is)(<pre\b[^>]*>)(.*?)</pre>")
PARA = re.compile(r"(?is)<p\b[^>]*>(.*?)</p>")


def _spacing(text):
    """'collapsed' when a code block lost the spaces between tokens.

    All four rules are properties of the text itself, e.g. the archived CE 5.0
    page that renders ``HANDLE CreateFile(LPCTSTR lpFileName,`` as
    ``HANDLECreateFile(LPCTSTRlpFileName,``.
    """
    if text.count(",") >= 2 and not re.search(r",\s", text):
        return "collapsed"
    if len(text) > 40 and " " not in text:
        return "collapsed"
    if re.search(r"\)[A-Za-z_]", text) and not re.search(r"\)\s", text):
        return "collapsed"
    if re.search(r"\btypedef\s*struct\b", text, re.I) and \
            re.search(r";[A-Za-z_]", text):
        return "collapsed"
    # a type and its declarator glued together: LPCTSTRlpFileName, HANDLECreateFile
    if re.search(r"\b[A-Z_]{2,}[a-z_][A-Za-z0-9_]*\s*[,);]", text):
        return "collapsed"
    if re.search(r"\b[A-Z_]{3,}[A-Z][a-z][A-Za-z0-9_]*\s*\(", text):
        return "collapsed"
    return "preserved"


CALLING_CONVENTION = (
    ("winapi", r"\bWINAPI\b|\bAPIENTRY\b|\bSTDAPICALLTYPE\b|\bWINAPIV\b"),
    ("cdecl", r"\b_cdecl\b|\b__cdecl\b|\bCDECL\b"),
    ("stdcall", r"\b_stdcall\b|\b__stdcall\b|\bSTDAPI\b|\bCALLBACK\b|"
                r"\bPASCAL\b|\b_export\b"),
    ("fastcall", r"\b_fastcall\b|\b__fastcall\b"),
    ("this", r"\bthis\b\s*\("),
    ("extern-c", r'extern\s+"C"'),
)


def _calling_convention(text):
    """Which calling convention the declaration *prints*, if any.

    The declaration text is quoted verbatim; this only reports which of the
    documented spellings occur (``WINAPI``, ``CALLBACK``, ``_stdcall``, ...).
    When the text says nothing, the answer is None -- not a guess.
    """
    found = [name for name, pattern in CALLING_CONVENTION
             if re.search(pattern, text)]
    return found[0] if found else None


def _members(text):
    """Struct/enum member lines, quoted as they appear (no interpretation)."""
    if not re.search(r"(?i)\b(typedef\s+)?(struct|enum|union)\b",
            text) and not re.search(r"(?i)\btypedef\b", text):
        return []
    members = []
    depth = 0
    for line in text.splitlines():
        stripped = line.strip()
        if not stripped:
            continue
        depth += stripped.count("{") - stripped.count("}")
        if depth <= 0 or stripped in ("{", "}"):
            continue
        if "{" in stripped and "}" in stripped:
            continue            # a whole nested declaration on one line
        if stripped.lower().startswith("typedef"):
            continue            # the declaration line, not a member
        if re.match(r"^[A-Za-z_#].*;\s*$", stripped) or \
                re.match(r"^[A-Za-z_][A-Za-z0-9_]*\s*(=[^;]*)?,?\s*$", stripped):
            members.append(stripped.rstrip(","))
    if members:
        return members
    # A page can print the body without line breaks too: the archived CE pages
    # lose the spaces *and* the newlines (``typedef struct X {DWORD a;INT b;} X;``),
    # and some blocks use literal ``\n`` escapes.  The member declarations are
    # then the pieces between the semicolons inside the outermost braces, and an
    # enum's between the commas.  Nothing is completed or reordered; a piece
    # that carries a brace (a nested declaration) is left out rather than
    # guessed at.
    start, end = text.find("{"), text.rfind("}")
    if start == -1 or end <= start:
        return members
    body = text[start + 1:end]
    if "\n" not in body:   # the page lost the newlines too
        body = body.replace(chr(92) + "n", " ")
    for piece in body.split(";"):
        piece = re.sub(r"\s+", " ", piece).strip()
        if not piece or "{" in piece or "}" in piece:
            continue
        if re.search(r"\benum\b", text) and "," in piece:
            members.extend(part.strip() for part in piece.split(",")
                           if part.strip())
        else:
            members.append(piece)
    return members


# ------------------------------------------------------------- ABI readers
#
# What an ABI consumer needs is: the calling convention, the member list with
# its types, and any alignment/packing/size statement the page makes.  The
# first two are read out of the declaration text itself (exact); the third is
# only kept as a quoted sentence and only when it names a concrete fact (a
# number of bytes, a byte order, a pointer width) -- loose prose ("alignment"
# in the UI sense and similar) is deliberately not collected.

TYPE_WORDS = frozenset("""
    void char short int long float double signed unsigned bool
    BOOL BOOLEAN BYTE WORD DWORD QWORD WCHAR TCHAR LPSTR LPCSTR LPWSTR
    LPCWSTR LPVOID LPCVOID HANDLE HWND HMODULE HINSTANCE FARPROC WPARAM
    LPARAM LRESULT INT8 INT16 INT32 INT64 UINT8 UINT16 UINT32 UINT64 SIZE_T
    ULONG LONG USHORT SHORT UINT PSTR PCSTR PWSTR PCWSTR PVOID
""".split())


def member_parts(line):
    """(type, name) a member line declares, or (None, None) when there is none.

    ``"DWORD dwFlags;"`` -> ``("DWORD", "dwFlags")``;
    ``"unsigned int LAP : 24;"`` -> ``("unsigned int", "LAP")``;
    ``"unsigned int : 3;"`` -> ``("unsigned int", None)`` (anonymous bitfield);
    ``"};"`` -> ``(None, None)``.  The type is quoted as printed; a member
    whose type the declaration does not spell out is None.
    """
    text = line.strip().rstrip(",").rstrip(";").strip()
    if not text or set(text) <= set("{}"):
        return None, None
    text = re.sub(r":\s*\d+$", "", text).strip()          # bitfield width
    text = re.sub(r"\[[^\]]*\]$", "", text).strip()       # array extent
    tokens = text.split()
    if not tokens:
        return None, None
    if len(tokens) == 1:
        token = tokens[0].rstrip("*&")
        return (tokens[0], None) if token in TYPE_WORDS else (None, tokens[0])
    name = tokens[-1].rstrip("*&")
    pointer = re.match(r"^([*&]+)", tokens[-1])
    type_text = " ".join(tokens[:-1])
    if pointer:                       # ``struct _foo *pNext``: the ``*`` is
        name = tokens[-1][len(pointer.group(1)):]     # part of the type
        type_text = (type_text + " " + pointer.group(1)).strip()
    if name in TYPE_WORDS and len(tokens) == 2 and tokens[0] in TYPE_WORDS:
        # ``unsigned int`` -- a two-word type with no declarator name
        return text, None
    if not type_text:
        return (text, None) if name in TYPE_WORDS else (None, name)
    return type_text, name


def member_type(line):
    """The type part of a member line, or None when it names no type."""
    return member_parts(line)[0]


# A page can also *state* an ABI fact in prose.  Only a sentence that names a
# concrete fact is kept -- a number of bytes, a byte order, a pointer width --
# because loose prose is not an ABI fact.  The sentence is quoted, never
# summarised, and no fact is inferred from it.
ABI_PROSE = (
    ("alignment", re.compile(
        r"\balign(?:ed|ment)\b[^.]{0,60}\b\d+\s*-?\s*byte|"
        r"\b\d+\s*-?\s*byte[- ]aligned\b|"
        r"__declspec\s*\(\s*align|#pragma\s+pack", re.I)),
    ("byte-order", re.compile(r"\b(?:little|big)[- ]endian\b|\bbyte order\b",
                              re.I)),
    ("pointer-size", re.compile(
        r"\b(?:32|64)[- ]bit\s+(?:pointers?|addresses)\b", re.I)),
    # Only a sentence that *defines* the size of a structure counts: "the size
    # of this structure is 68 bytes", "the structure is 128 bytes in length".
    # Loose size talk ("a packet size is recommended to be less than 8,000
    # bytes", "not including the initial 8 bytes") is deliberately not
    # collected -- it states no size of a structure.
    ("structure-size", re.compile(
        r"\bsize\s+of\s+(?:this|the)\s+structure\s+is\s+\d+\s*-?\s*bytes\b"
        r"|\b(?:this|the)\s+structure\s+is\s+(?:a\s+total\s+of\s+)?"
        r"\d+\s*-?\s*bytes\b", re.I)),
)

ABI_FLAGS = (
    ("bitfield", re.compile(r"\w+\s*:\s*\d+\s*[;,]?(?=\s*\}?\s*$)", re.M)),
    ("pack", re.compile(r"#pragma\s+pack\b", re.I)),
    ("align", re.compile(r"__declspec\s*\(\s*align\b", re.I)),
    ("pragma-once", re.compile(r"#pragma\s+once\b", re.I)),
)


def abi_flags(text):
    """Which ABI-relevant constructs the declaration text itself prints."""
    return [name for name, pattern in ABI_FLAGS if pattern.search(text)]


def abi_notes(text):
    """Sentences of a page that state an alignment/byte-order/pointer fact."""
    notes = []
    flat = re.sub(r"\s+", " ", text)
    for sentence in re.split(r"(?<=[.!?])\s+", flat):
        sentence = sentence.strip()
        if not sentence or len(sentence) > 400:
            continue
        for pattern_name, pattern in ABI_PROSE:
            if pattern.search(sentence):
                notes.append({"pattern": "abi: " + pattern_name,
                              "text": sentence})
                break
    return notes


# A second kind of ABI fact a page can carry: a layout *table*.  Many CE pages
# document a structure or a wire format as ``Offset | Field | Size | …``
# instead of (or beside) a C declaration.  What the page states is kept as
# printed -- the offset cell, the field name, the size cell and the whole row --
# and nothing is computed: no offset is inferred for a row the page gives none
# for, and no member is invented.

HTML_TABLE = re.compile(r"(?is)<table\b[^>]*>(.*?)</table>")
OFFSET_COLUMN = re.compile(r"\boffsets?\b", re.I)
NAME_COLUMN = re.compile(r"\b(?:member|field|name)s?\b", re.I)
SIZE_COLUMN = re.compile(r"\b(?:size|length)\b", re.I)
OFFSET_VALUE = re.compile(r"^\s*(0x[0-9A-Fa-f]+|\d+)\s*$")
SIZE_VALUE = re.compile(r"^\s*(0x[0-9A-Fa-f]+|\d+)\s*(bits?|bytes?)?\s*$", re.I)


def _cell_int(text):
    match = OFFSET_VALUE.match(text or "")
    if not match:
        return None
    value = match.group(1)
    return int(value, 16) if value.lower().startswith("0x") else int(value)


def offset_tables(fragment):
    """Layout tables: ``Offset | Field | Size | …`` rows, quoted as printed.

    Returns one dict per data row of a table that has both an *Offset* column
    and a *member/field/name* column: ``member``, ``offset`` (int, derived from
    the printed cell), ``offset_printed``, ``size``/``size_unit`` when the table
    prints one, ``table`` (the header cells, as printed) and ``row`` (all cells
    of the row, as printed -- the evidence a checker re-reads).
    """
    out = []
    for table in HTML_TABLE.finditer(fragment):
        rows = ROW.findall(table.group(1))
        if len(rows) < 2:
            continue
        headers = [text_of(cell, keep_newlines=False).strip()
                   for cell in CELL.findall(rows[0])]
        labels = [header.lower() for header in headers]
        offset_i = next((i for i, label in enumerate(labels)
                         if OFFSET_COLUMN.search(label)), None)
        name_i = next((i for i, label in enumerate(labels)
                       if NAME_COLUMN.search(label)), None)
        size_i = next((i for i, label in enumerate(labels)
                       if SIZE_COLUMN.search(label)), None)
        if offset_i is None or name_i is None or offset_i == name_i:
            continue
        header = " ".join(headers)
        for row in rows[1:]:
            cells = [text_of(cell, keep_newlines=False).strip()
                     for cell in CELL.findall(row)]
            if len(cells) <= max(offset_i, name_i):
                continue
            offset = _cell_int(cells[offset_i])
            member = cells[name_i]
            if offset is None or not member:
                continue
            size = size_unit = None
            size_printed = (cells[size_i]
                            if size_i is not None and len(cells) > size_i
                            else "")
            if size_printed:
                match = SIZE_VALUE.match(size_printed)
                if match:
                    value = match.group(1)
                    size = (int(value, 16) if value.lower().startswith("0x")
                            else int(value))
                    size_unit = (match.group(2) or "bytes").lower()
                    if size_unit.startswith("bit"):
                        size_unit = "bits"
            out.append({
                "member": member,
                "offset": offset,
                "offset_printed": cells[offset_i],
                "size": size,
                "size_unit": size_unit,
                "size_printed": size_printed or None,
                "table": header,
                "row": " ".join(cells),
            })
    return out


# ------------------------------------------------- what is implementation code
#
# A page prints two kinds of code block: the *declaration* of an interface
# (what include/def material is built from) and *sample code* (what it is not).
# The test below is deliberately blunt and conservative: it only fires when the
# block is unmistakably an implementation -- a preprocessor include, or a
# statement form (`return`, `if`, `for`, `while`, `switch`, `goto`, `break;`,
# `continue;`).  A ``#define``/``#pragma`` block is a declaration; an
# ``#ifdef``-fenced block is treated as code because the corpus uses those
# fences around sample sources.

IMPLEMENTATION_STATEMENT = re.compile(
    r"\b(?:return|if|for|while|switch|goto)\b\s*[\s(\w*&=;]|"
    r"\b(?:break|continue)\s*;")


def is_implementation(text):
    """True when a code block is implementation code, not a declaration."""
    if re.search(r"#\s*include\b", text):
        return True
    if re.match(r"\s*#\s*(define|pragma)\b", text):
        return False            # a #define/#pragma block is a declaration
    if re.match(r"\s*#", text):
        return True             # an #ifdef/#if-fenced block is code
    if not re.search(r"[;{}]", text):
        return False            # prose, a field list, a documentation header
    return bool(IMPLEMENTATION_STATEMENT.search(text))


def _kind_of(text):
    lowered = text.lower()
    if re.search(r"\btypedef\s+struct\b|\bstruct\s+[A-Za-z_]", lowered):
        return "struct"
    if "typedef enum" in lowered or re.search(r"\benum\s+[A-Za-z_]", lowered):
        return "enum"
    if re.match(r"\s*#\s*define\b", text):
        return "macro"
    if re.search(r"\(\s*\*\s*[A-Za-z_]", text) and "typedef" in lowered:
        return "callback"
    if re.search(r"\bDECLARE_INTERFACE|\binterface\s+[A-Za-z_]", text):
        return "interface"
    if "(" in text and ")" in text:
        return "function"
    return None


def _looks_like_declaration(text):
    if len(text) < 8 or len(text) > 4000:
        return False
    return ("(" in text and ")" in text) or ";" in text or "{" in text


def declarations(fragment):
    """Syntax blocks of one page, with their markup and the raw text."""
    out = []
    syntax_region = region(fragment, "syntax", "declaration", "prototype")
    for match in PRE.finditer(fragment):
        attrs, inner = match.group(1), match.group(2)
        text = text_of(inner)
        if not _looks_like_declaration(text):
            continue
        implementation = is_implementation(text)
        role = "example" if implementation else (
            "syntax" if (syntax_region and
                         syntax_region.find(inner[:200]) != -1) else "example")
        if role == "example" and not implementation and not syntax_region:
            # Templates without a Syntax heading put the prototype between the
            # description and the Parameters/Remarks heading; a page with a
            # single code block there is documenting a declaration, not
            # quoting an example.
            before = fragment[:match.start()]
            tail = text_of(before[-200:], keep_newlines=False)
            following = fragment[match.end():match.end() + 400]
            head = re.search(r"(?is)<h[2-6][^>]*>\s*([^<]{2,30})", following)
            nxt = head.group(1).strip().lower() if head else ""
            if len(PRE.findall(fragment)) == 1 and \
                    tail and nxt in ("parameters", "return values", "remarks",
                                     "members", "see also", "requirements", ""):
                role = "syntax"
        out.append({
            "text": text,
            "markup": (re.search(r'class\s*=\s*"([^"]+)"', attrs, re.I) or
                       [None, "pre"])[1] if 'class=' in attrs.lower() else "pre",
            "spacing": _spacing(text),
            "calling_convention": _calling_convention(text),
            "role": role,
            "kind": _kind_of(text),
            "members": _members(text),
            "member_types": [member_type(line) for line in _members(text)],
            "abi_flags": abi_flags(text),
            "implementation": implementation,
        })
    if not any(d["role"] == "syntax" for d in out):
        block = syntax_region or ""
        for para in PARA.finditer(block):
            text = text_of(para.group(1))
            if _looks_like_declaration(text) and re.search(r"[;{()]", text):
                implementation = is_implementation(text)
                out.insert(0, {
                    "text": text, "markup": "paragraph",
                    "spacing": _spacing(text),
                    "calling_convention": _calling_convention(text),
                    "role": "example" if implementation else "syntax",
                    "kind": _kind_of(text), "members": _members(text),
                    "member_types": [member_type(line)
                                     for line in _members(text)],
                    "abi_flags": abi_flags(text),
                    "implementation": implementation,
                })
                break
    return out


# ---------------------------------------------------------------- markdown

FRONT_FIELD = re.compile(r"^(?P<key>[A-Za-z][A-Za-z0-9_.-]*):[ \t]*(?P<value>.*)$")
FENCE = re.compile(r"(?s)```([A-Za-z0-9+#-]*)[ \t]*\n(.*?)```")


MD_FIELD = re.compile(r"^###\s*-field\s+([A-Za-z_]\w*)\s*$", re.M)
MD_FIELD_BODY = re.compile(
    r"^###\s*-field\s+([A-Za-z_]\w*)\s*$\s*\n+(.*?)(?=\n###\s|\n##\s|\Z)",
    re.M | re.S)

_C_ID = re.compile(r"[A-Za-z_]\w*")
_C_KEYWORD = {"if", "for", "while", "switch", "return", "sizeof", "defined",
              "typedef", "struct", "union", "enum", "const", "void", "int",
              "char", "short", "long", "float", "double", "unsigned", "signed",
              "bool", "static", "extern", "inline", "register", "volatile",
              "this", "class", "public", "private", "protected", "virtual"}
_TAG = re.compile(r"\b(?:struct|union|enum)\s+([A-Za-z_]\w*)")
# the aliases of a typedef: everything between the closing brace (or the
# declaration start) and the final semicolon
_TAIL = re.compile(r"([A-Za-z_\w\s,*]+)\s*;$", re.S)


def declared_names(text):
    """The identifier(s) a C declaration defines, as printed.

    Used to answer "which name does this page's declaration define?" for pages
    whose title is prose (``AVI Main Header``) -- the answer is the tag and the
    typedef alias (``MainAVIHeader``), and both are read from the text, never
    guessed.  A declaration that defines nothing recognisable returns [].
    """
    if not text or not text.strip():
        return []
    text = text.strip()
    names = []

    def add(name):
        name = (name or "").strip()
        if name and name not in _C_KEYWORD and name not in names:
            names.append(name)

    if text.startswith("#"):
        match = re.match(r"#\s*define\s+([A-Za-z_]\w*)", text)
        if match:
            add(match.group(1))
        return names
    for match in _TAG.finditer(text):
        add(match.group(1))
    if re.match(r"^\s*(?:extern\s+|static\s+|inline\s+)*[A-Za-z_]",
                text) and "(" in text and "}" not in text.split("(", 1)[0]:
        head = text.split("(", 1)[0]
        ids = _C_ID.findall(head)
        if ids:
            add(ids[-1])
    for match in re.finditer(
            r"\(\s*[A-Za-z_]*\s*\*+\s*([A-Za-z_]\w*)\s*\)", text):
        add(match.group(1))
    tail = _TAIL.search(text)
    if tail and "}" in text[:tail.start()]:
        for part in tail.group(1).split(","):
            part = part.strip().strip("*").strip()
            match = re.search(r"([A-Za-z_]\w*)\s*\)?$", part)
            if match:
                add(match.group(1))
    return [name for name in names if not name.startswith("__")]


def markdown_struct_fields(text):
    """sdk-api ``## -struct-fields`` -> [{name, description}], in page order.

    Some sdk-api structure pages document every member but print no syntax
    block (``AVIMAINHEADER`` is one).  The member names and their order are a
    documented fact, so they are extracted; the description is kept to the
    first sentence as the page's own wording.
    """
    fields = []
    for match in MD_FIELD_BODY.finditer(text):
        name = match.group(1)
        body = re.sub(r"\s+", " ", match.group(2)).strip()
        sentence = body.split(". ")[0].strip()
        fields.append({"name": name, "description": sentence[:300]})
    return fields


def markdown(text):
    """sdk-api page -> (fields, requirements, declarations, struct fields).

    The front matter is the YAML block the Win32 reference ships
    (``req.header``, ``req.lib``, ``req.dll``, ``api_location``, ...); the
    declaration is the fenced code block, usually under ``## -syntax``, and a
    structure page may instead (or also) document its members under
    ``## -struct-fields``.
    """
    fields = {}
    if text.startswith("---"):
        end = text.find("\n---", 3)
        head = text[3:end if end > 0 else len(text)]
        for line in head.splitlines():
            match = FRONT_FIELD.match(line.strip())
            if match:
                key = match.group("key").strip()
                value = match.group("value").strip()
                if value and not value.startswith("|"):
                    fields.setdefault(key, value)
        text = text[end + 4:] if end > 0 else ""

    reqs = []
    for key, field in (("req.header", "header"),
                       ("req.include-header", "header"),
                       ("req.lib", "library"),
                       ("req.dll", "dll"),
                       ("api_location", "dll"),
                       ("req.unicode-ansi", "unicode_ansi"),
                       ("req.typenames", "type"),
                       ("req.namespace", "namespace"),
                       ("req.assembly", "assembly")):
        value = fields.get(key)
        if not value:
            continue
        for item in re.split(r",|;", value):
            item = item.strip().strip("-").strip()
            if item:
                reqs.append({"field": field, "label": key, "value": item,
                             "evidence": f"{key}: {item}"})

    # The UID names the API exactly and its module:
    #   UID: NF:fileapi.CreateFileW  ->  module "fileapi", name "CreateFileW"
    uid = fields.get("UID")
    if uid and ":" in uid:
        module = uid.split(":", 1)[1].split(".")[0].strip()
        if module:
            reqs.append({"field": "module", "label": "UID", "value": module,
                         "evidence": f"UID: {uid}"})

    decls = []
    for match in FENCE.finditer(text):
        language, body = match.group(1), match.group(2)
        body = body.strip()
        if not body or not _looks_like_declaration(body):
            continue
        before = text[:match.start()]
        implementation = is_implementation(body)
        role = "example" if implementation else (
            "syntax" if re.search(r"(?im)^##\s+-?syntax\s*$", before)
            else "example")
        decls.append({"text": body, "markup": f"fence:{language or 'text'}",
                      "spacing": _spacing(body), "role": role,
                      "calling_convention": _calling_convention(body),
                      "kind": _kind_of(body), "members": _members(body),
                      "member_types": [member_type(line)
                                       for line in _members(body)],
                      "abi_flags": abi_flags(body),
                      "implementation": implementation})
    return fields, reqs, decls, markdown_struct_fields(text)


# ------------------------------------------------------------------ entities

_PAREN_SUFFIX = re.compile(r"\s*\([^()]*\)\s*$")
_API_NAME = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*(::[A-Za-z_][A-Za-z0-9_]*)*$")


def name_from_title(title):
    """``CreateFile (Windows CE 5.0)`` -> ``CreateFile``; None for an article.

    Only a title that is a single identifier (with the optional ``Class::Member``
    form) names an API: everything else is a documentation article about
    something, not a definition of a name.
    """
    if not title:
        return None
    text = re.sub(r"\s*\|\s*Microsoft Learn\s*$", "", title).strip()
    for _ in range(2):
        text = _PAREN_SUFFIX.sub("", text).strip()
    if not text or not _API_NAME.match(text):
        return None
    return text


MD_KIND_WORD = re.compile(
    r"(?i)\s+(function|structure|enumeration|callback|interface|class|"
    r"library|attribute|macro|union|typedef|constant|method|property|"
    r"event|operator|constructor|destructor|field)$")


def name_from_markdown_title(title):
    """``DEVMODEW (wingdi.h)`` / ``CreateFileW function (fileapi.h)`` ->
    ``DEVMODEW`` / ``CreateFileW``.

    The sdk-api title carries the public name in its own casing (the file name
    is lower-case, and the UID uses the C tag name for structures:
    ``NS:wingdi._devicemodeW``), so this is the name a declaration must use.
    Returns None when the title is not a name (e.g. a README).
    """
    text = (title or "").strip().strip('"').strip()
    for _ in range(2):
        text = _PAREN_SUFFIX.sub("", text).strip()
    while True:
        stripped = MD_KIND_WORD.sub("", text)
        if stripped == text:
            break
        text = stripped
    return text if text and _API_NAME.match(text) else None


def name_from_filename(name):
    """``nf-fileapi-createfilew.md`` -> ``CreateFileW`` (sdk-api page name)."""
    match = re.match(r"^(nf|ns|ne|nc|ni|nn|nl|na)-([^-]+)-(.+)\.md$", name)
    return match.group(3) if match else None


KIND_FROM_PREFIX = {"nf": "function", "ns": "struct", "ne": "enum",
                    "nc": "callback", "ni": "other", "nn": "interface",
                    "nl": "library", "na": "attribute"}


def kind_from_filename(name):
    """``nf-fileapi-createfilew.md`` -> ``function``."""
    match = re.match(r"^(nf|ns|ne|nc|ni|nn|nl|na)-", name)
    return KIND_FROM_PREFIX.get(match.group(1)) if match else None


# ---------------------------------------------------------------- constraints

SENTENCE = re.compile(r"[^.\n]{20,400}\.")


def constraints(fragment):
    """Sentences of the page that state a Windows CE restriction.

    Only a sentence that mentions Windows CE *and* a constraint word is kept,
    and the sentence itself is quoted -- this is not a summary of the page.
    """
    plain = re.sub(r"\s+", " ", text_of(fragment, keep_newlines=False))
    out = []
    for match in SENTENCE.finditer(plain):
        sentence = match.group(0).strip()
        lowered = sentence.lower()
        if not any(word in lowered for word in CE_WORDS):
            continue
        hit = next((word for word in CONSTRAINT_WORDS if word in lowered), None)
        if not hit:
            continue
        out.append({"text": sentence, "pattern": hit})
    return out
