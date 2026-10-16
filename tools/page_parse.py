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
    "required header": "header", "required headers": "header",
    "link library": "library", "library": "library", "link libraries": "library",
    "library file": "library", "import library": "library", "libraries": "library",
    "required library": "library", "required link library": "library",
    "dll": "dll", "dlls": "dll", "dll file": "dll", "dynamic link library": "dll",
    "os versions": "os_versions", "os version": "os_versions",
    "windows ce versions": "os_versions", "windows ce version": "os_versions",
    "operating system": "os_versions", "platform": "os_versions",
    "windows embedded ce": "os_versions", "windows mobile": "os_versions",
    "namespace": "namespace", "assembly": "assembly", "class": "class",
    "requires": "requires", "requirement": "requires", "type": "type",
    # ``Versions: 2.0 and later`` is the MFC template's OS-version line.
    # ``Pocket PC`` / ``Smartphone`` print the platform version.  ``Module:
    # Nk`` is the module the page names; it is not rewritten to ``nk.dll``.
    # ``sysgen`` and ``Architecture`` are the catalog variable and the CPU
    # list the page prints.  ``C++ Namespace: av_upnp.`` keeps the printed
    # value; the trailing period is sentence punctuation, stripped only
    # from the derived key, the same way ``Winbase.h.`` is.
    "versions": "os_versions", "pocket pc": "os_versions",
    # ``Smartphones: Windows Mobile 5.0 and later`` is the same fact as
    # ``Smartphone``, plural.  ``Platforms`` is not mapped: its values are
    # not a version.
    "smartphone": "os_versions", "smartphones": "os_versions",
    "pocket": "os_versions",
    "module": "module", "c++ namespace": "namespace",
    # ``Component: fsdbase`` is the catalog component the page names.  It is
    # not a DLL, and the template sentence ``Windows CE component that
    # includes this API element.`` is not a component name (empty key).
    "sysgen": "sysgen", "architecture": "architecture",
    "component": "component",
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


def regions(fragment, *headings, window=6000):
    """Every block that follows one of ``headings``, not only the first.

    A Learn page prints ``Requirements`` twice: the first heading is a note,
    and the header is under the second.  ``region`` keeps the first block,
    which is what a Syntax heading wants.  A requirements reader has to see
    both, and ``Windows Mobile Requirements`` is a second requirements block
    on the same page, not a different API.
    """
    wanted = {heading.lower() for heading in headings}
    for match in HEADING.finditer(fragment):
        title = text_of(match.group(0), keep_newlines=False).strip(": ")
        if title.lower() not in wanted:
            continue
        rest = fragment[match.end():]
        next_heading = HEADING.search(rest)
        if next_heading and next_heading.start() < window:
            rest = rest[:next_heading.start()]
        yield rest[:window]


# ``<p class="clsRef">Syntax</p>`` is the section label in the CE 5.0 MSHTML
# and shdocvw CHM.  ``<p class=blue><b>At a Glance</b></p>`` is the 2000-04
# ATL template; the class is often unquoted.  Neither is an ``<h1>``–``<h6>``,
# so ``region`` does not see it.  A blue paragraph that is a procedure step
# (``To import a desktop computer database``) is not a heading — only the
# titles listed here are.  ``<p class="label">`` stays on its own path: the
# CE 3.0 requirements table is read from its column headers, and cutting
# every label paragraph would shorten regions that reader already handles.
_P_CLASS_SECTION = re.compile(
    r"(?is)<p\b[^>]*\bclass\s*=\s*[\"']?(clsRef|blue|label)(?=[\"'\s>])"
    r"[^>]*>\s*(?:<[^>]+>\s*)*([^<]{2,40})")
_P_CLASS_TITLES = {
    "syntax", "c/c++ syntax", "c/c++syntax", "declaration", "prototype",
    "parameters", "parameter", "c/c++ parameters",
    "return value", "return values", "remarks", "general remarks",
    "requirements", "at a glance", "system requirements",
    "c/c++ requirements", "c/c++requirements",
    "members", "elements", "constants",
    "example", "examples", "code example", "sample", "samples",
    "see also", "enumerator values", "enumerators",
    # the CE-difference section of the CHM/MSDN reference pages; a label
    # like any other, and a boundary for the readers that scan forward
    "windows ce remarks", "windows ce notes",
}


def _p_class_sections(fragment, start, end):
    """``(pos, end, title)`` of clsRef/blue section labels in ``[start, end)``."""
    out = []
    for match in _P_CLASS_SECTION.finditer(fragment, start, end):
        title = text_of(match.group(2), keep_newlines=False).strip(": ").lower()
        if title not in _P_CLASS_TITLES:
            continue
        out.append((match.start(), match.end(), title))
    return out


def labeled_region(fragment, *headings, window=6000):
    """The block after a clsRef/blue label, until the next heading.

    An ``<h1>``–``<h6>`` is a boundary only.  It is not a start: ``region``
    already returns those, and a page that has one is not this template.
    """
    wanted = {heading.lower() for heading in headings}
    marks = [(match.start(), match.end(), None)
             for match in HEADING.finditer(fragment)]
    marks.extend(_p_class_sections(fragment, 0, len(fragment)))
    marks.sort()
    for index, (_start, end, title) in enumerate(marks):
        if title not in wanted:
            continue
        stop = end + window
        if index + 1 < len(marks) and marks[index + 1][0] < stop:
            stop = marks[index + 1][0]
        return fragment[end:stop]
    return ""


# ------------------------------------------------------------- requirements

ROW = re.compile(r"(?is)<tr\b[^>]*>(.*?)</tr>")
CELL = re.compile(r"(?is)<t[dh]\b[^>]*>(.*?)</t[dh]>")
# The value has to be on the label's own line.  ``\s*`` used to cross the
# newline, so an empty ``Platforms:`` cell became the value ``Versions:``
# and an empty ``Header File:`` cell became ``Module:``.  The page printed
# neither.  A value that really is on the next row is read from the table.
# The colon that separates a label from its value is not the second colon
# of ``::``.  ``IReplStore::FindNextItem`` is a C++ name, not a requirement
# whose value is ``:FindNextItem``.  ``C++ Namespace: av_upnp::DIDL_Lite``
# still matches: only the label's own colon is the separator, and that
# colon is not followed by another colon.
LINE_LABEL = re.compile(
    r"(?<![:A-Za-z])([A-Za-z][A-Za-z /+.]{2,28}?)[ \t]*:(?!:)"
    r"[ \t]*([^\n]{1,200})")


FILEISH = re.compile(r"[A-Za-z0-9_.+\-]+\.(h|hpp|hh|hxx|lib|dll|hlp|inc)\b", re.I)
PROSE_WORDS = re.compile(r"\b(this|your|the|to|of|for|and|see|use|must|not)\b", re.I)
# The same extensions ``build-kb.FILE_TOKEN`` treats as a library/DLL file.
ASSIGNED_FILE = re.compile(
    r"[\w.+-]+\.(?:lib|dll|drv|sys|ocx|tlb)\b", re.I)


def _file_cell(value):
    """True when ``value`` is only file names, commas, and parentheticals.

    ``mshtml.h, mshtml.idl`` and ``Quartz.dll`` are file cells.
    ``Default set to "\\\\windows\\\\mboxcht.dll"`` is a registry sentence,
    even though a file name occurs in it.  ``None`` is not a file.
    """
    if not value:
        return False
    residue = re.sub(
        r"(?i)[A-Za-z_][\w.+-]*\.(?:h|hpp|hh|hxx|idl|inc|lib|dll|drv|sys)\b",
        " ", value)
    residue = re.sub(r"\([^)]*\)", " ", residue)
    residue = re.sub(r"[,;/]|\bor\b|\band\b|[.]", " ", residue, flags=re.I)
    return not residue.strip() and bool(re.search(
        r"(?i)\.(?:h|hpp|hh|hxx|idl|inc|lib|dll|drv|sys)\b", value))


def _file_list(value):
    """True when the value is only file names, commas, and ``or`` / ``and``.

    A display-driver page prints eight ``.lib`` names joined by commas and
    ``or``.  That is a list of files, not prose, even though it is longer
    than 120 characters and contains ``or``.  ``Shell32.dll (version 4.0 or
    later)`` is not a list: the ``or`` sits inside a version sentence, and
    the parenthetical remains after the file name is removed.
    """
    # ``findall`` would return the extension group only (``lib``), and
    # replacing that would eat the ``lib`` inside ``Ddi_ati_lib.lib``.
    files = [match.group(0) for match in FILEISH.finditer(value or "")]
    if not files:
        return False
    residue = value or ""
    for name in files:
        residue = residue.replace(name, " ", 1)
    # ``Rts.lib (for development workstation), PSPubSubCE.lib (for target
    # device)`` is a file list.  The parenthetical says which machine, and
    # it is not a second file.  It stays in the printed value.
    residue = re.sub(r"\([^)]*\)", " ", residue)
    residue = re.sub(r"[,;/]|\bor\b|\band\b|[.]", " ", residue, flags=re.I)
    return not residue.strip()


def assigned_files(value):
    """Every library/DLL file a requirement value assigns, in printed order.

    ``Ole32.lib, Uuid.lib`` and ``OEMMain.lib or OEMMain_StaticKITL.lib``
    assign each name.  ``Iphlpapi.dll on Windows Server 2008`` assigns the
    one file the sentence names.  ``Shell32.dll (version 4.0 or later)``
    assigns ``Shell32.dll`` only.  A value that names no file
    (``Developer Implemented``) assigns nothing.  Nothing is invented: a
    second file is kept only when removing the file names, commas and
    ``or`` / ``and`` leaves nothing else.
    """
    files = ASSIGNED_FILE.findall(value or "")
    if len(files) <= 1:
        return files
    residue = value or ""
    for name in files:
        residue = residue.replace(name, " ", 1)
    residue = re.sub(r"[,;/]|\bor\b|\band\b|[.]", " ", residue, flags=re.I)
    if residue.strip():
        return files[:1]
    out = []
    seen = set()
    for name in files:
        if name.lower() in seen:
            continue
        seen.add(name.lower())
        out.append(name)
    return out


# ``Not applicable``, ``None``, ``N/A`` and ``Developer Implemented`` are
# the whole cell: the page says this API has no header / no link library /
# no DLL of its own.  A cell that also names a file is not one of these.
_STATED_NONE = re.compile(
    r"(?i)^\s*(?:not\s+applicable|none(?:\s+required)?|n/?a|"
    r"developer\s+implemented|not\s+required)\s*[.]?\s*$")


def stated_none(value):
    """True when the cell says there is no such file, rather than naming one."""
    return bool(_STATED_NONE.match(value or ""))


def _plausible(field, value):
    """Reject prose that a template put into a requirement table cell.

    ``Add this macro to your class's header file`` is a *description* of an
    MFC header requirement, not a header name; a header/library/DLL value has
    to look like a file name (or be a short bare name).  A cell that is only
    a list of file names is kept whole, however long.
    ``Windows CE versions that include this API element.`` is the blank
    template's own instruction, not a version the page assigns.
    """
    # The blank ATL template prints ``that include this API element``
    # (no ``s``).  A real version line does not.
    if field == "os_versions" and re.search(
            r"(?i)that includes? this API element", value or ""):
        return False
    if field in ("header", "library", "dll"):
        if _file_list(value):
            return True
        # ``Link Library: Not applicable.`` and ``DLL: None`` are the page
        # saying there is no such file.  That is a statement, not a missing
        # cell, and it is the difference between "the documents do not say"
        # and "the documents say there is none".  It is kept as printed; it
        # names no file, so it never enters the include/link map.
        if stated_none(value):
            return True
        # ``Uuid.lib. Not supported in Windows CE.`` and
        # ``CEPubSub.h (for development workstation), CePubSub.idl.`` start
        # with the file the label assigns.  The rest of the cell is kept as
        # printed.  ``Add this macro to your class's header file`` does not
        # start with a file, and stays prose.
        # ``Uuid.lib. Not supported in Windows CE.`` names a file and then
        # says the file is not a CE library.  The non-support sentence is
        # the fact.  The file is not recorded as a header or a library.
        if re.search(r"(?i)\bnot\s+supported\b", value or ""):
            return False
        if re.match(r"(?i)\s*[A-Za-z_][\w.+-]*\.(?:h|hpp|hh|hxx|lib|dll|idl|inc)\b",
                    value or ""):
            return True
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


TABLE = re.compile(r"(?is)<table\b[^>]*>(.*?)</table>")


def _column_labels(cells):
    """The column-header row of an old-SDK requirements table, or None.

    The Windows CE 3.0 SDK CHM prints requirements as one wide table whose
    first row names the columns instead of one label per row::

        Runs on | Versions | Defined in | Include | Link to
        Windows CE OS | 3.0 and later | Windbase.h | Winbase.h | coredll.lib

    Reading that table row by row (label = first cell) flattens three facts
    into one string, so the column names map each cell to its own field.
    """
    labels = [re.sub(r"\s+", " ", c).strip().rstrip(":").lower()
              for c in cells]
    # The usual row is ``Defined in | Include | Link to``.  DirectDraw and a
    # few other components print ``Declared in`` instead of ``Defined in`` /
    # ``Include``, and some of those tables have no ``Link to`` column.  Both
    # are the same table.  Requiring ``Include`` dropped the header and the
    # library together.
    file_columns = {"include", "defined in", "declared in", "link to"}
    if len(labels) >= 3 and labels[0].startswith("runs on") \
            and file_columns.intersection(labels):
        return labels
    return None


def _requirements_from_columns(block, seen):
    """Requirements from column-header tables in the block.

    Returns ``(records, had_column_table)``; the caller skips the generic
    row-by-row read when a column table is present, because that read is what
    flattened the columns into one string.
    """
    out = []
    found = False
    for table in TABLE.finditer(block):
        rows = ROW.findall(table.group(1))
        if not rows:
            continue
        header = [text_of(c, keep_newlines=False) for c in
                  CELL.findall(rows[0])]
        labels = _column_labels(header)
        if not labels:
            continue
        found = True
        index = {}
        for i, label in enumerate(labels):
            index.setdefault(label, i)

        def cell(values, name):
            i = index.get(name)
            if i is None or i >= len(values):
                return ""
            return re.sub(r"\s+", " ", values[i]).strip()

        for body in rows[1:]:
            values = [text_of(c, keep_newlines=False) for c in
                      CELL.findall(body)]
            if not any(values):
                continue
            runs = cell(values, "runs on")
            versions = cell(values, "versions")
            if runs or versions:
                value = " ".join(v for v in (runs, versions) if v)
                if ("os_versions", value) not in seen:
                    seen.add(("os_versions", value))
                    out.append({
                        "field": "os_versions", "label": "Runs on / Versions",
                        "value": value,
                        "evidence": f"Runs on: {runs}, Versions: {versions}"})
            for name, field in (("defined in", "header"),
                                ("declared in", "header"),
                                ("include", "header"),
                                ("link to", "library")):
                value = cell(values, name)
                if value and _plausible(field, value) \
                        and (field, value) not in seen:
                    seen.add((field, value))
                    label = {"defined in": "Defined in",
                             "declared in": "Declared in",
                             "include": "Include",
                             "link to": "Link to"}[name]
                    out.append({"field": field, "label": label,
                                "value": value,
                                "evidence": f"{label}: {value}"})
    return out, found


def requirements(fragment):
    """Requirement label/value pairs, from a table or from ``Label: value``."""
    out = []
    seen = set()
    got_columns = False
    # ``C/C++ Requirements`` is the requirements heading on the dual
    # Script/C++ template.  A few pages print it without the space
    # (``C/C++Requirements``).  ``Script Syntax`` is not a C declaration
    # and is not a requirements heading.
    # ``Windows Mobile Requirements`` is the same page's second requirements
    # block (Pocket PC / Smartphone header and library).  It is not a
    # hardware "system requirements" topic.  Every occurrence is read: the
    # first ``Requirements`` heading is sometimes empty or a note, and the
    # files are under the next one.
    requirement_headings = (
        "requirements", "windows mobile requirements", "at a glance",
        "system requirements", "c/c++ requirements", "c/c++requirements")
    blocks = list(regions(fragment, *requirement_headings))
    if not blocks:
        for heading in requirement_headings:
            labeled = labeled_region(fragment, heading)
            if labeled:
                blocks.append(labeled)
                break
    for block in blocks:
        column_records, had_column_table = _requirements_from_columns(block,
                                                                      seen)
        out += column_records
        if had_column_table:
            got_columns = True
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
            continue
        for row in ROW.finditer(block):
            cells = [text_of(c, keep_newlines=False) for c in CELL.findall(row.group(1))]
            if len(cells) < 2 or not cells[0]:
                continue
            label = cells[0].rstrip(":").strip()
            value = " ".join(c for c in cells[1:] if c).strip()
            # ``IUnknown::QueryInterface | Returns pointers...`` is a method
            # row, not a requirement label.  A real label does not contain
            # ``::``.
            if "::" in label:
                continue
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
    # The CE 3.0 SDK marks the section with <p class="label">Requirements</p>,
    # not a heading, and a few pages split the word across tags
    # (<b>Requir</b>e<b>ments</b>) or omit it.  The column header itself
    # (Runs on | Versions | Defined in | Include | Link to) is the fact, so
    # when the heading search did not already read that table, read it from
    # the article.  The header check is the whole guard: no other table in
    # the corpus starts with those columns.
    # A ``Declared in`` table has no ``Include`` column, and a few of them
    # have no ``Link to`` either.  The heading search does not see a
    # ``<b>Requirements</b>`` label, so the table is read from the article.
    # ``seen`` drops a table the heading search already read.
    if ("Runs on" in fragment or "Runs On" in fragment) and (
            "Link to" in fragment or "Declared in" in fragment
            or "Defined in" in fragment):
        extra, had = _requirements_from_columns(fragment, seen)
        if had:
            got_columns = True
        out.extend(extra)
    # ``Header file | mshtmcid.h`` sits under ``C++ Information``, which is
    # not a requirements heading.  The row is the requirement.  The same
    # table's ``Applies to`` cell is not a version and is not read.  A cell
    # that does not name a header file (a column title, a sentence) is not
    # a requirement either.
    for row in ROW.finditer(fragment):
        cells = [text_of(cell, keep_newlines=False).strip()
                 for cell in CELL.findall(row.group(1))]
        if len(cells) < 2 or not cells[0]:
            continue
        label = cells[0].rstrip(":").strip()
        if label.lower() not in ("header file", "header files"):
            continue
        value = re.sub(r"\s+", " ", " ".join(cell for cell in cells[1:] if cell)).strip()
        if not value or ("header", value) in seen:
            continue
        if not FILEISH.search(value) or not _plausible("header", value):
            continue
        seen.add(("header", value))
        out.append({"field": "header", "label": label, "value": value,
                    "evidence": f"{label}: {value}"})
    # A sentence that assigns the header or the exporting DLL, not a mention
    # of some other type.  ``The DISPID for this event is defined in
    # mshtmdid.h`` is the event page's header.  ``This function is declared
    # in the Serhw.h`` is that function's header.  ``This function is
    # exported by Ppcload.dll`` is the DLL.  ``BT_ADDR is defined in
    # Ws2bth.h`` and ``CGID_MSHTML (defined in mshtmhst.h)`` name a different
    # thing, so they are not this page's requirement.  A sample ``#include``
    # is not one either.
    plain = text_of(fragment, keep_newlines=False)
    stated = (
        ("header", "defined in",
         re.compile(r"(?i)the\s+DISPID\s+for\s+this\s+event\s+is\s+defined\s+"
                    r"in\s+([A-Za-z0-9_]+\.h)\b")),
        ("header", "declared in",
         re.compile(r"(?i)\bthis\s+(?:function|macro|structure|struct|"
                    r"message|control code|interface|callback|method)\s+"
                    r"is\s+(?:declared|defined)\s+in\s+(?:the\s+)?"
                    r"(?:header\s+(?:file\s+)?)?([A-Za-z0-9_]+\.h)\b")),
        ("dll", "exported by",
         re.compile(r"(?i)\bthis\s+(?:function|macro)\s+is\s+exported\s+"
                    r"(?:by|from)\s+([A-Za-z0-9_]+\.dll)\b")),
        ("dll", "implemented in",
         re.compile(r"(?i)\bthis\s+function\s+is\s+implemented\s+in\s+"
                    r"(?:the\s+)?([A-Za-z0-9_]+\.dll)\b")),
        ("dll", "exported by",
         re.compile(r"(?i)\bthis\s+is\s+an\s+(?:application\s+programming\s+"
                    r"interface\s+\(API\)|API)\s+exported\s+by\s+(?:the\s+)?"
                    r"([A-Za-z0-9_]+\.dll)\b")),
        # ``It is declared in Stdlib.h as follows:`` -- the subject is the
        # variable or function the page documents.  ``the`` before the file
        # name is optional; ``as follows`` or a colon ends the clause.
        ("header", "declared in",
         re.compile(r"(?i)\bit\s+is\s+(?:declared|defined)\s+in\s+(?:the\s+)?"
                    r"([A-Za-z0-9_]+\.h)\b")),
        # ``The library (X.lib)`` or ``library X.lib`` assigns a library.
        # ``The ACM Driver Wrapper library (Acmdwrap.lib)`` is the library
        # for the API the page documents.
        ("library", "library",
         re.compile(r"(?i)\b(?:the\s+)?[A-Z][\w\s]*library\s*"
                    r"\(\s*([A-Za-z0-9_]+\.lib)\s*\)")),
        # ``link to X.lib`` / ``link with X.lib`` in prose.  Not a
        # requirements table: ``you must link to the Coredll.lib file``.
        ("library", "link to",
         re.compile(r"(?i)\b(?:must|need\s+to|should)?\s*link\s+(?:to|with)"
                    r"\s+(?:the\s+)?([A-Za-z0-9_]+\.lib)\b")),
        # ``defined in X.h`` without ``header file`` -- the CE 3.0 OAL pages
        # print ``defined in dstruct.h`` for structures and variables.  The
        # match has to be about *this* page's subject, not a random mention.
        ("header", "defined in",
         re.compile(r"(?i)\b(?:this\s+)?(?:structure|variable|type|enum|"\
                    r"union|constant|macro)\s+(?:is\s+)?defined\s+in\s+"
                    r"(?:the\s+)?([A-Za-z0-9_]+\.h)\b")),
        # ``X.h include file`` -- error code tables and similar pages
        # mention the header file that defines the constants.
        ("header", "include file",
         re.compile(r"(?i)\b([A-Za-z0-9_]+\.h)\s+include\s+file\b")),
    )
    for field, label, pattern in stated:
        for match in pattern.finditer(plain):
            value = match.group(1)
            if (field, value) in seen or not _plausible(field, value):
                continue
            seen.add((field, value))
            out.append({"field": field, "label": label, "value": value,
                        "evidence": re.sub(r"\s+", " ", match.group(0)).strip()})
    # MSHTML prints the header and the implementing DLL under
    # ``Interface Information``, not under Requirements:
    # ``Header and IDL files | mshtml.h, mshtml.idl``,
    # ``Stock Implementation | Mshtml.dll``,
    # ``Import library | mshtml.dll``.  A DirectShow filter page prints
    # ``Executable | Quartz.dll``.  ``None`` is not a DLL.  A registry
    # sentence that mentions a DLL is not this table.  ``Minimum operating
    # systems`` is kept only when the cell names Windows CE; the desktop
    # names in the same cell stay as printed.
    out.extend(_information_rows(fragment, seen))
    # ``To use this API, include the shellcb.h header file and link with
    # shellcb.lib.``  The subject is this API.  A sentence about some other
    # API is not matched.
    use = re.compile(
        r"(?i)(?:to\s+use\s+this\s+API|implementing\s+this\s+function)"
        r".{0,80}?include\s+(?:the\s+)?([A-Za-z0-9_]+\.h)\s+header\s+file"
        r"\s+and\s+link\s+with\s+(?:the\s+)?([A-Za-z0-9_]+\.lib)\b")
    for match in use.finditer(plain):
        evidence = re.sub(r"\s+", " ", match.group(0)).strip()
        for field, label, value in (("header", "include", match.group(1)),
                                    ("library", "link with", match.group(2))):
            if (field, value) in seen or not _plausible(field, value):
                continue
            seen.add((field, value))
            out.append({"field": field, "label": label, "value": value,
                        "evidence": evidence})
    return out


def _information_rows(fragment, seen):
    """File rows of an Interface Information or filter table.

    These labels are not Requirements headings, so the heading search never
    sees them.  The row itself is the statement.  The field follows the file
    the cell names: ``Import library | mshtml.dll`` is a DLL, not a ``.lib``.
    """
    out = []
    header_labels = {"header", "header and idl files", "idl file", "idl files"}
    dll_labels = {"stock implementation", "executable"}
    for row in ROW.finditer(fragment):
        cells = [text_of(cell, keep_newlines=False).strip()
                 for cell in CELL.findall(row.group(1))]
        if len(cells) < 2 or not cells[0]:
            continue
        label = cells[0].rstrip(":").strip()
        key = re.sub(r"\s+", " ", label).lower()
        value = re.sub(r"\s+", " ",
                       " ".join(cell for cell in cells[1:] if cell)).strip()
        if not value or len(value) > 200:
            continue
        field = None
        if key == "minimum operating systems":
            if PROSE_WORDS.search(value):
                continue
            if not re.search(r"(?i)windows\s+(?:embedded\s+)?ce\b|"
                             r"pocket\s+pc|windows\s+mobile", value):
                continue
            field = "os_versions"
        elif key == "import library":
            if not _file_cell(value):
                continue
            if re.search(r"(?i)\.dll\b", value) and not re.search(
                    r"(?i)\.lib\b", value):
                field = "dll"
            elif re.search(r"(?i)\.lib\b", value):
                field = "library"
        elif key in header_labels:
            if _file_cell(value) and re.search(
                    r"(?i)\.(?:h|hpp|hh|hxx|idl|inc)\b", value):
                field = "header"
        elif key in dll_labels:
            if _file_cell(value) and re.search(
                    r"(?i)\.(?:dll|drv|sys)\b", value):
                field = "dll"
        if not field or (field, value) in seen:
            continue
        seen.add((field, value))
        out.append({"field": field, "label": label, "value": value,
                    "evidence": f"{label}: {value}"})
    
    # Learn pages sometimes embed "Requirements" inside a <pre> block and
    # place the actual requirement data in the next paragraph as
    # <strong>Label:</strong> value pairs (e.g., <strong>Header:</strong> Dmusici.h.).
    # Extract these <strong>Label:</strong> patterns from the fragment.
    # Handle both <strong>Label:</strong> and <strong>Label</strong>: forms.
    strong_label_pattern = re.compile(
        r"<strong>([^<]+?)</strong>\s*:?\s*([^<]+?)(?:<br|</p)", re.I)
    for match in strong_label_pattern.finditer(fragment):
        label = text_of(match.group(1), keep_newlines=False).strip().rstrip(":")
        value = text_of(match.group(2), keep_newlines=False).strip()
        if not label or not value:
            continue
        field = _field(label)
        if not field or field == "other":
            continue
        if not value or (field, value) in seen:
            continue
        # For header/library/dll fields, the value should look like a file name
        # or be a stated-none value. Reject prose text.
        if field in ("header", "library", "dll"):
            if not stated_none(value) and not FILEISH.search(value):
                continue
        if not _plausible(field, value):
            continue
        seen.add((field, value))
        out.append({"field": field, "label": label, "value": value,
                    "evidence": match.group(0).strip()})
    
    return out


# ``To import these functions, you need to link to the fsdmgr.lib file.``
# The header, when the same paragraph names one, is ``defined in the
# Fsdmgr.h header file``.  The names are the identifier cells of the table
# that follows.  A page that states the library and lists no names assigns
# nothing: the component is not one of the functions.
_IMPORT_LIB = re.compile(
    r"(?i)to\s+import\s+(?:this|these)\s+functions?\s*,\s*you\s+"
    r"(?:must|need\s+to)\s+link\s+to\s+the\s+([A-Za-z0-9_]+\.lib)\b")
_DEFINED_HEADER_FILE = re.compile(
    r"(?i)defined\s+in\s+(?:the\s+)?([A-Za-z0-9_]+\.h)\s+header\s+file")
_LISTED_NAME = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")


def listed_function_requirements(fragment):
    """Header and link library a component page assigns to the functions it lists.

    The page says which file the following functions are defined in, and which
    library imports them, then prints their names.  Each name is kept as
    printed, including a misspelling.  Nothing is attached to the component
    itself, and a sentence that lists no names is not guessed into one.
    """
    out = []
    seen = set()
    low = fragment.lower()
    start = 0
    while True:
        idx = low.find("to import", start)
        if idx < 0:
            break
        start = idx + len("to import")
        sentence = text_of(fragment[idx:idx + 420], keep_newlines=False)
        lib = _IMPORT_LIB.search(sentence)
        if not lib:
            continue
        before = text_of(fragment[max(0, idx - 700):idx], keep_newlines=False)
        headers = list(_DEFINED_HEADER_FILE.finditer(before))
        header = headers[-1] if headers else None
        rest = fragment[idx:idx + 8000]
        see = rest.lower().find("see also")
        chunk = rest[:see] if see >= 0 else rest
        table = re.search(r"(?is)<table\b[^>]*>(.*?)</table>", chunk)
        if not table:
            continue
        names = []
        for row in ROW.finditer(table.group(1)):
            for cell in CELL.findall(row.group(1)):
                name = text_of(cell, keep_newlines=False).strip()
                if _LISTED_NAME.match(name) and name.lower() not in (
                        "function", "functions"):
                    names.append(name)
        if not names:
            continue
        lib_value = lib.group(1)
        lib_evidence = re.sub(r"\s+", " ", lib.group(0)).strip()
        header_value = header.group(1) if header else None
        header_evidence = (re.sub(r"\s+", " ", header.group(0)).strip()
                           if header else None)
        for name in names:
            key = (name, "library", lib_value)
            if key not in seen and _plausible("library", lib_value):
                seen.add(key)
                out.append({"name": name, "field": "library",
                            "label": "link to", "value": lib_value,
                            "evidence": lib_evidence})
            if header_value and _plausible("header", header_value):
                key = (name, "header", header_value)
                if key not in seen:
                    seen.add(key)
                    out.append({"name": name, "field": "header",
                                "label": "defined in", "value": header_value,
                                "evidence": header_evidence})
    # ``The following functions are implemented in Ws2.dll`` then a table of
    # those names.  The DLL is assigned to each listed name, not to the page
    # title.  A sentence that lists no names assigns nothing.
    impl = re.compile(
        r"(?i)the\s+following\s+functions\s+are\s+implemented\s+in\s+"
        r"(?:the\s+)?([A-Za-z0-9_]+\.dll)\b")
    start = 0
    while True:
        match = impl.search(low[start:])
        if not match:
            break
        idx = start + match.start()
        start = idx + len("the following")
        sentence = text_of(fragment[idx:idx + 220], keep_newlines=False)
        found = impl.search(sentence)
        if not found:
            continue
        rest = fragment[idx:idx + 12000]
        see = rest.lower().find("see also")
        chunk = rest[:see] if see >= 0 else rest
        table = re.search(r"(?is)<table\b[^>]*>(.*?)</table>", chunk)
        if not table:
            continue
        names = []
        for row in ROW.finditer(table.group(1)):
            for cell in CELL.findall(row.group(1)):
                name = text_of(cell, keep_newlines=False).strip()
                if _LISTED_NAME.match(name) and name.lower() not in (
                        "function", "functions", "description"):
                    names.append(name)
        dll_value = found.group(1)
        evidence = re.sub(r"\s+", " ", found.group(0)).strip()
        for name in names:
            key = (name, "dll", dll_value)
            if key in seen or not _plausible("dll", dll_value):
                continue
            seen.add(key)
            out.append({"name": name, "field": "dll", "label": "implemented in",
                        "value": dll_value, "evidence": evidence})
    # ``The following table shows the functions that are exported by
    # Setup.dll`` then a Function column.  The DLL is assigned to each
    # listed name.  ``exported by the client driver`` names no DLL, so it
    # assigns nothing.  The page title is not given the DLL.
    exported = re.compile(
        r"(?i)following\s+(?:table\s+shows\s+the\s+)?functions\s+"
        r"(?:that\s+are\s+)?exported\s+by\s+(?:the\s+)?"
        r"([A-Za-z0-9_]+\.dll)\b")
    start = 0
    while True:
        match = exported.search(low[start:])
        if not match:
            break
        idx = start + match.start()
        start = idx + len("following")
        sentence = text_of(fragment[idx:idx + 240], keep_newlines=False)
        found = exported.search(sentence)
        if not found:
            continue
        names = _names_in_next_table(fragment, idx)
        dll_value = found.group(1)
        evidence = re.sub(r"\s+", " ", found.group(0)).strip()
        for name in names:
            key = (name, "dll", dll_value)
            if key in seen or not _plausible("dll", dll_value):
                continue
            seen.add(key)
            out.append({"name": name, "field": "dll",
                        "label": "exported by", "value": dll_value,
                        "evidence": evidence})
    # ``The Install_Exit function prototype is part of Setup.dll, an
    # ISV-created file``.  The named function gets the DLL.  The page says
    # the DLL is ISV-created when it says so; that clause stays in the
    # evidence.  It is not rewritten into a system DLL.
    part_of = re.compile(
        r"(?i)the\s+([A-Za-z_][A-Za-z0-9_]*)\s+function\s+prototype\s+is\s+"
        r"part\s+of\s+([A-Za-z0-9_]+\.dll)\b"
        r"(?:\s*,\s*an\s+ISV-created\s+file)?")
    for match in part_of.finditer(text_of(fragment, keep_newlines=False)):
        name, dll_value = match.group(1), match.group(2)
        key = (name, "dll", dll_value)
        if key in seen or not _plausible("dll", dll_value):
            continue
        seen.add(key)
        out.append({"name": name, "field": "dll", "label": "part of",
                    "value": dll_value,
                    "evidence": re.sub(r"\s+", " ", match.group(0)).strip()})
    return out


_MODULE_TITLE = re.compile(
    r"(?i)^([A-Za-z_][A-Za-z0-9_]*)\s+(?:Module|Components)$")
# ``The coredll module contains the following components.`` and
# ``The msmqrt module includes functions for application developers, which
# are defined in the Mq.h header file.``
_MODULE_COMPONENTS = re.compile(
    r"(?i)the\s+([A-Za-z_][A-Za-z0-9_]*)\s+module\s+contains\s+the\s+"
    r"following\s+components")
_MODULE_FUNCTIONS = re.compile(
    r"(?i)the\s+([A-Za-z_][A-Za-z0-9_]*)\s+module\s+(?:contains|includes)\s+"
    r"(?:the\s+following\s+)?functions[^.]{0,120}?defined\s+in\s+(?:the\s+)?"
    r"([A-Za-z0-9_]+\.h)\b")
_MODULE_IMPORT_LIB = re.compile(
    r"(?i)to\s+import\s+(?:this|these)\s+functions?\s*,\s*you\s+"
    r"(?:must|need\s+to)\s+link\s+to\s+the\s+([A-Za-z0-9_]+\.lib)\b")


def module_facts(fragment, page_title=None):
    """What a Windows CE *module* page states about the module's build.

    A CE module page is the one place the documents describe the binary
    rather than the API: ``The coredll module contains the following
    components`` with a ``Component | Description | Notes | Library`` table,
    and ``defined in the Mq.h header file`` / ``link to the Msmqapix.lib
    file`` for the module itself.  Each row is kept as printed; the ``Notes``
    cell (``Exposes no public functions.``, ``Required``) is the page's own
    words and is not interpreted into a flag.  A module is never turned into
    a DLL name: the pages name ``coredll`` the module, and
    ``Coredll.dll`` only where they print it.
    """
    out = []
    plain = text_of(fragment, keep_newlines=False)
    title_module = None
    if page_title:
        match = _MODULE_TITLE.match(_title_core(page_title))
        if match:
            title_module = match.group(1)

    def add(record):
        if record not in out:
            out.append(record)

    for match in _MODULE_FUNCTIONS.finditer(plain):
        add({"module": match.group(1), "component": "", "field": "header",
             "value": match.group(2),
             "evidence": re.sub(r"\s+", " ", match.group(0)).strip()})
        tail = plain[match.end():match.end() + 400]
        lib = _MODULE_IMPORT_LIB.search(tail)
        if lib:
            add({"module": match.group(1), "component": "", "field": "library",
                 "value": lib.group(1),
                 "evidence": re.sub(r"\s+", " ", lib.group(0)).strip()})

    for match in _MODULE_COMPONENTS.finditer(plain):
        module = match.group(1)
        index = fragment.lower().find("following components")
        if index < 0:
            continue
        rows = _component_rows(fragment, index)
        for component, library, notes, quote in rows:
            add({"module": module, "component": component,
                 "field": "library" if library else "component",
                 "value": library or component, "notes": notes,
                 "evidence": quote})
    # A page titled ``winsock Module`` whose sentence names no module still
    # states the module: the title does.  Only the file facts are kept, and
    # only when the sentence that states them names no other module.
    if title_module and not any(r["module"] for r in out):
        for pattern, field in ((_MODULE_IMPORT_LIB, "library"),):
            found = pattern.search(plain)
            if found:
                add({"module": title_module, "component": "", "field": field,
                     "value": found.group(1),
                     "evidence": re.sub(r"\s+", " ", found.group(0)).strip()})
    for record in out:
        record.setdefault("notes", "")
    return out


def _component_rows(fragment, index):
    """``Component | Description | Notes | Library`` rows of the next table."""
    rest = fragment[index:index + 30000]
    table = re.search(r"(?is)<table\b[^>]*>(.*?)</table>", rest)
    if not table:
        return []
    rows = ROW.findall(table.group(1))
    if not rows:
        return []
    header = [re.sub(r"\s+", " ", text_of(cell, keep_newlines=False))
              .strip().lower() for cell in CELL.findall(rows[0])]
    if "component" not in header:
        return []
    file_column = None
    for name in ("library", "import file", "import library", "library file"):
        if name in header:
            file_column = header.index(name)
            break
    notes_column = header.index("notes") if "notes" in header else None
    component_column = header.index("component")
    out = []
    for body in rows[1:]:
        cells = [re.sub(r"\s+", " ", text_of(cell, keep_newlines=False)).strip()
                 for cell in CELL.findall(body)]
        if len(cells) <= component_column:
            continue
        # The quote is the row as the page prints it, so it stays a
        # verbatim substring of the page (a joined-with-bars string would
        # not be).
        quote = re.sub(r"\s+", " ", text_of(body, keep_newlines=False)).strip()
        component = cells[component_column]
        # The CE 3.0 table prints the link text twice in one cell
        # (``Accel_c Accel_c``).  One repeated identifier is that
        # identifier; two different words are not a component name.
        words = component.split()
        if len(words) == 2 and words[0] == words[1]:
            component = words[0]
        if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", component):
            continue
        library = ""
        if file_column is not None and file_column < len(cells):
            value = cells[file_column]
            if re.fullmatch(r"(?i)[A-Za-z_][\w.+-]*\.lib", value):
                library = value
        notes = ""
        if notes_column is not None and notes_column < len(cells):
            notes = cells[notes_column]
        out.append((component, library, notes, quote))
    return out


def _names_in_next_table(fragment, start, limit=12000):
    """Identifier cells of the first table after ``start``, before See Also."""
    rest = fragment[start:start + limit]
    see = rest.lower().find("see also")
    chunk = rest[:see] if see >= 0 else rest
    table = re.search(r"(?is)<table\b[^>]*>(.*?)</table>", chunk)
    if not table:
        return []
    names = []
    for row in ROW.finditer(table.group(1)):
        for cell in CELL.findall(row.group(1)):
            name = text_of(cell, keep_newlines=False).strip()
            if _LISTED_NAME.match(name) and name.lower() not in (
                    "function", "functions", "description"):
                names.append(name)
    return names


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


# A constant a page *numbers*.  Only a table that names the constant in one
# column and prints its value in another is read, and only a row whose name
# cell is one identifier and whose value cell is one number -- a cell that
# mixes prose with a number is left on the page, not parsed apart.  A layout
# table (it has an Offset column) is not a constant table; offset_tables owns
# those rows.  Nothing is computed: a decimal is recorded only when the page
# prints one, never by converting the hexadecimal.
CONSTANT_NAME_COLUMNS = {
    "flag", "name", "constant", "symbolic constant", "resource identifier",
    # the MicrosoftDocs/win32 style tables head them "Constant name" /
    # "Constant value"; the classic tables head them "Constant" / "Value"
    "constant name",
    "notification flag", "error code", "return code", "identifier",
    "message", "macro", "symbol", "symbolic name",
    # The same shape under a more specific heading.  Each label was checked
    # against the tables that use it: the name cell is the symbol and the
    # other cell is the number the page assigns to it.  A correspondence
    # (a character set beside a code page, a virtual key beside a scan code,
    # a locale beside an LCID, a buffer index beside a type name) is not in
    # this set -- those numbers are not the symbol's value.
    "symbolic constant name", "screen identifier", "control code",
    "message identifier", "virtual key code", "status identifier",
    "hresult name", "version identifier", "escape code", "dwmessage",
    "power notification type", "device generating notification",
    "propvariant type", "message text", "visual basic constant",
    "constant (button)", "constant (shift)", "system color",
    "ioctl call", "event", "element", "error",
}
CONSTANT_HEX_COLUMNS = {
    "hexadecimal", "hexadecimal value", "hex value", "hex",
    "value (hex)", "value (hexadecimal)", "hex code",
}
CONSTANT_DECIMAL_COLUMNS = {"decimal"}
CONSTANT_VALUE_COLUMNS = {
    "value", "numeric value", "code", "win32 value", "registry order",
    # the MicrosoftDocs/win32 style tables head it "Constant value"
    "constant value",
}
# Columns that number a *different* thing sitting next to the symbol
# (charset -> ANSI code page, VK -> OEM scan code, locale -> LCID).
# Those numbers are not the constant's value and must not become #define.
CORRESPONDENCE_VALUE_COLUMNS = {
    "code page", "code pages", "codepage", "ansi code page", "oem code page",
    "scan code", "scan codes", "scancode", "oem scan",
    "lcid", "locale id", "locale identifier",
}
_CORRESPONDENCE_LABEL = re.compile(
    r"code\s*pages?|scan\s*codes?|\blcid\b|locale\s+id", re.I)


def _is_correspondence_label(label):
    lab = re.sub(r"\s+", " ", (label or "").strip().rstrip(":").lower())
    if lab in CORRESPONDENCE_VALUE_COLUMNS:
        return True
    return bool(_CORRESPONDENCE_LABEL.search(lab))


def _correspondence_indices(labels):
    return {i for i, lab in enumerate(labels) if _is_correspondence_label(lab)}
CONSTANT_IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
# A printed number is more than ``0x..`` or ``digits``: the Data Type
# Constants page prints ``-32768`` (typed with a dash that is not
# hyphen-minus), ``2.2204460492503131e-016`` and ``255 (0xff)``.  The cell
# is read as printed; every dash-like sign mark is accepted, and a C number
# suffix may trail.
_NUM_CORE = (r"(?:0[xX][0-9A-Fa-f]+|\d+\.\d*(?:[eE][+-]?\d+)?"
             r"|\d+[eE][+-]?\d+|\.\d+(?:[eE][+-]?\d+)?|\d+)")
_DASHS = "[-\u2010-\u2015\u2212]"
_NUM = "(" + _DASHS + "?" + _NUM_CORE + "[uUlLfF]*)"
_NUM_TOKEN = re.compile("^" + _NUM + "$")
_NUM_PAIR = re.compile(
    "^\(?\s*" + _NUM + "\s*\(\s*" + _NUM + "\s*\)\s*\)?$")


def number_cell(cell):
    """Read one printed number cell -> (value, paired) or (None, None).

    ``value`` is the number as printed (sign marks normalised to ``-`` so
    the text stays valid in a generated ``#define``); ``row`` evidence
    keeps the original cell.  A compound ``255 (0xff)`` prints one number
    two ways: the hexadecimal becomes ``value`` (hexadecimal preferred,
    like the columns rule) and the decimal becomes ``paired`` -- both are
    printed beside each other, so both are read.
    """
    text = re.sub(r"\s+", " ", (cell or "").replace("\xa0", " ")).strip()
    for dash in "\u2010\u2011\u2012\u2013\u2014\u2015\u2212":
        text = text.replace(dash, "-")
    if not text:
        return None, None
    pair = _NUM_PAIR.match(text)
    if pair:
        first, second = pair.group(1), pair.group(2)
        if first.lower().startswith(("0x", "-0x")):
            return first, second
        if second.lower().startswith(("0x", "-0x")):
            return second, first
        return first, second
    token = _NUM_TOKEN.match(text)
    if token:
        return token.group(1), None
    return None, None


def _column(labels, names):
    for index, label in enumerate(labels):
        if label in names:
            return index
    return None


def constant_tables(fragment, raw_row=False):
    """Rows of a name/value table a page prints, quoted as printed.

    One dict per row that states both: ``name`` (the identifier cell),
    ``value`` (the number cell, hexadecimal preferred when the page prints
    one), ``decimal`` (only when a decimal column prints a decimal), ``table``
    and ``row`` (the evidence a checker re-reads).
    """
    out = []
    for table in HTML_TABLE.finditer(fragment):
        rows = ROW.findall(table.group(1))
        if len(rows) < 2:
            continue
        headers = [text_of(cell, keep_newlines=False).strip()
                   for cell in CELL.findall(rows[0])]
        labels = [re.sub(r"\s+", " ", header).strip().rstrip(":").lower()
                  for header in headers]
        if any(OFFSET_COLUMN.search(label) for label in labels):
            continue
        name_i = _column(labels, CONSTANT_NAME_COLUMNS)
        hex_i = _column(labels, CONSTANT_HEX_COLUMNS)
        dec_i = _column(labels, CONSTANT_DECIMAL_COLUMNS)
        val_i = _column(labels, CONSTANT_VALUE_COLUMNS)
        corr_is = _correspondence_indices(labels)
        # LOGFONT weight tables print the constant in the column headed
        # ``Value`` and the number in the column headed ``Weight``
        # (``FW_THIN | 100``).  ``Value`` is not a name column anywhere else;
        # this pair is the only table in the corpus that uses ``Weight``.
        if name_i is None and "value" in labels and "weight" in labels:
            name_i = labels.index("value")
            val_i = labels.index("weight")
            hex_i = dec_i = None
        if hex_i in corr_is:
            hex_i = None
        if val_i in corr_is:
            val_i = None
        if dec_i in corr_is:
            dec_i = None
        value_is = [i for i in (hex_i, val_i, dec_i) if i is not None]
        header = " ".join(headers)
        body = list(ROW.finditer(table.group(1)))[1:]
        body_cells = [[text_of(cell, keep_newlines=False).strip()
                       for cell in CELL.findall(row.group(1))]
                      for row in body]
        if name_i is None or not value_is or name_i in value_is:
            # The headers do not name the columns ("Level description",
            # "Raster operation", a value column ahead of the name).  Fall
            # back to the CELLS: a name column is one whose cells are
            # constant identifiers; a value column is one whose cells are
            # all printed values (number or expression).  A table read
            # this way is still only ever read as printed.
            def ident_column(i):
                seen = 0
                for cells in body_cells:
                    if i >= len(cells):
                        return False
                    text = cells[i]
                    if not text:
                        continue
                    if not CONSTANT_IDENT.match(text) or \
                            (text.upper() != text and "_" not in text):
                        return False
                    seen += 1
                return seen >= 2

            def value_column(i):
                if i in corr_is or (i < len(labels)
                                    and _is_correspondence_label(labels[i])):
                    return False
                seen = 0
                for cells in body_cells:
                    if i >= len(cells):
                        return False
                    text = cells[i]
                    if not text:
                        continue
                    if not (number_cell(text)[0] or expression_cell(text)):
                        return False
                    seen += 1
                return seen >= 2

            width = max((len(c) for c in body_cells), default=0)
            if name_i is None or name_i in value_is or \
                    (name_i is not None and not ident_column(name_i)):
                # also when a HEADER match points at a non-name column
                # ("Error code" holding 0xC00CE508L beside "Error string"
                # holding MSG_E_BADCHARDATA)
                name_i = next((i for i in range(width)
                               if i not in value_is and ident_column(i)),
                              None)
            if not value_is or name_i in value_is:
                value_is = [i for i in range(width)
                            if i != name_i and value_column(i)]
                hex_i = value_is[0] if value_is else None
                val_i = (value_is[1] if len(value_is) > 1
                         else (value_is[0] if value_is else None))
                dec_i = (value_is[2] if len(value_is) > 2 else None)
        if name_i is None or not value_is or name_i in value_is:
            continue
        for row_match, cells in zip(body, body_cells):
            row = row_match.group(1)
            row_quote = _raw_row_text(row_match.group(0))
            if len(cells) <= name_i or not CONSTANT_IDENT.match(cells[name_i]):
                continue

            def number_at(index):
                if index is None or index >= len(cells):
                    return None, None
                return number_cell(cells[index])

            value = None
            value_from = None
            paired = None
            for index in (hex_i, val_i, dec_i):
                got, pair = number_at(index)
                if got:
                    value = got
                    paired = pair
                    value_from = index
                    break
            if not value:
                # printed expression values (``RASBASE+1``): quoted as
                # printed, never computed (values: never derived)
                for index in (val_i, hex_i, dec_i):
                    if index is None or index >= len(cells):
                        continue
                    got = expression_cell(cells[index])
                    if got:
                        value = got
                        value_from = index
                        break
            if not value:
                continue
            # A decimal is kept only when the page prints one *beside* the
            # value (a separate decimal column, or the second half of a
            # compound ``255 (0xff)`` cell), never by converting a
            # hexadecimal and never by repeating the only number printed.
            decimal = number_at(dec_i)[0]
            if not decimal or decimal.lower().startswith("0x") \
                    or value_from == dec_i:
                decimal = paired
            elif paired:
                decimal = paired
            out.append({
                "name": cells[name_i],
                "value": value,
                "decimal": decimal,
                "table": header,
                "origin": "table",
                "row": (row_quote if raw_row else " ".join(cells)),
            })
    out.extend(_constants_in_cells(fragment, out, raw_row=raw_row))
    return out


# The reference pages of the message surface print the DEFINITION as the
# syntax block itself: ``#define WM_CREATE 0x0001`` (winmsg) or
# ``#define EM_... (WM_USER + 255)``.  The page PRINTS the #define -- the
# line is not derived; it is quoted.  The value is taken exactly as
# printed (an expression stays an expression: values are never computed).
# not line-anchored: a table cell can quote the definition inline
# (``<code>#define TBSTYLE_EX_VERTICAL 0x00000004</code>`` in a note)
DEFINE_LINE_RE = re.compile(
    r"#\s*define\s+([A-Z][A-Z0-9_]{1,60})\s+(.+)")
_ANY_TAG = re.compile(r"<[^>]+>")
_VALUE_TOKEN = re.compile(
    r"^(?:0x[0-9A-Fa-f]{1,16}[uUlL]{0,3}|-?\d+[uUlL]{0,3}"
    r"|[A-Z][A-Z0-9_]{1,60}(?:\s*[+\-]\s*\d+)?"
    r"|\([A-Z][A-Z0-9_]{1,60}(?:\s*[+\-]\s*\d+)?\))")


_PRE_BLOCK = re.compile(r"(?is)<pre[^>]*>.*?</pre>")
_FENCE_BLOCK = re.compile(r"(?ms)^```.*?^```")


_DEFINE_NUMERIC = re.compile(
    r"^(0[xX][0-9A-Fa-f]+|0[bB][01]+|-?\d+(?:\.\d*)?(?:[eE][+-]?\d+)?"
    r"|-?\d+[eE][+-]?\d+)[uUlLfF]*$")
_DEFINE_ALIAS = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
# Example code never yields constants: a define line announced by "the
# following code fragment / sample code ..." is an example, not a spec.
_EXAMPLE_LOOKBEHIND = re.compile(
    r"(?i)(code fragment|code sample|sample code|following sample"
    r"|example code|example application)\W{0,40}[^#]{0,220}$")


def define_line_constants(text, quote_stripped=False):
    """``#define NAME value`` lines a page prints OUTSIDE code blocks ->
    constant rows.

    ``quote_stripped``: the row quote is the tag-free line -- the .html
    reader's ground (check-cleanroom compares against
    ``text_of(article_html())``).  The markdown reader quotes the raw
    line (its page text is the raw markdown).

    ``<pre>`` and fenced code are the syntax/example readers' ground
    (syntax_constant_rows keeps the cleanroom example rule); this reader
    covers the definitions a page prints inline -- a table note quoting
    ``#define TBSTYLE_EX_VERTICAL 0x00000004`` for a style the header
    does not define.  The trailing C comment is not part of the value;
    the value is otherwise quoted as printed.  A line whose right side is
    not a number, a printed expression or a single identifier (an alias
    another page defines) is skipped -- prose macro bodies are not
    constants."""
    out = []
    if not text:
        return out
    text = _PRE_BLOCK.sub(" ", text or "")
    text = _FENCE_BLOCK.sub(" ", text)
    for line in text.splitlines():
        raw = line.strip()
        clean = _ANY_TAG.sub(" ", line)
        for match in DEFINE_LINE_RE.finditer(clean):
            name, rest = match.group(1), match.group(2)
            value = re.split(r"//|/\*", rest, 1)[0].strip()
            value = re.sub(r"\s+", " ", value).strip()
            # the docstring contract: the value head is a number, a
            # printed expression or a single identifier (an alias
            # another page defines) -- nothing else.  Kept as printed,
            # never truncated at a token boundary: TEXT("X") is a prose
            # macro body, not a constant; RASBASE+127 is kept whole.
            # Table-row residue after the value ("0x4 | ") is not part
            # of the head.
            ctor = re.match(
                r"^([A-Z][A-Z0-9_]{2,60})\s*\(\s*(0[xX][0-9A-Fa-f]+|-?\d+)\s*\)\s*;?$",
                value)
            if ctor:
                head = re.sub(r"\s+", "", value).rstrip(";")
            else:
                if re.match(r"^[A-Za-z_][A-Za-z0-9_]*\s*\(", value):
                    continue
                head = re.split(r"[\s;|]", value, 1)[0].strip()
                if not (_DEFINE_NUMERIC.match(head) or _EXPR_VALUE.match(head)
                        or _DEFINE_ALIAS.match(head)):
                    continue
            if _EXAMPLE_LOOKBEHIND.search(clean[:match.start()]):
                continue
            out.append({
                "name": name,
                "value": head,
                "decimal": None,
                "table": "printed #define",
                "origin": "define",
                "row": (clean.strip()[:240] if quote_stripped
                        else raw[:240])
            })
    return out


# A page also prints a constant as one cell, ``NAME = 0x0001`` or
# ``NAME (0x0001)``, instead of a name column and a value column.  The cell
# has to be that and nothing else: a sentence that mentions a number is not
# split apart.  The name is the all-caps identifier the page prints.  A
# one-letter cell (``A=0``, a setting, not a constant) is left out; a name
# with an underscore or at least four characters is kept (``S_OK``, ``TRUE``).
# A printed value can be an EXPRESSION the page prints instead of a
# number: the RAS error table prints ``RASBASE+1`` under "Code".  The
# expression is quoted exactly as printed -- never computed (values:
# never derived).  A C header defines the name exactly this way.
_EXPR_VALUE = re.compile(r"^[A-Z][A-Z0-9_]{1,40}\s*[+-]\s*\d{1,6}$")


def expression_cell(text):
    """The cell is one printed expression value (``RASBASE+1``) -> the
    text as printed.  Anything else -> None."""
    text = (text or "").strip()
    if _EXPR_VALUE.match(text):
        return re.sub(r"\s+", "", text)
    return None


_CELL_EQ = re.compile(
    r"^([A-Z][A-Z0-9_]*)\s*=\s*(0x[0-9A-Fa-f]+|-?\d+"
    r"|[A-Z][A-Z0-9_]{1,40}\s*[+-]\s*\d{1,6})$")
_CELL_PAR = re.compile(
    r"^([A-Z][A-Z0-9_]*)\s*\(\s*(0x[0-9A-Fa-f]+|-?\d+"
    r"|[A-Z][A-Z0-9_]{1,40}\s*[+-]\s*\d{1,6})\s*\)$")
# The sdk-api style prints the pair in ONE cell of the "Value" column:
# ``KLF_ACTIVATE 0x00000001``.  Same honesty: the whole cell is the
# name and one number and nothing else.
_CELL_NAME_VALUE = re.compile(
    r"^([A-Z][A-Z0-9_]*)\s+((?:0x[0-9A-Fa-f]+|-?\d+)\s*[uUlL]*"
    r"|[A-Z][A-Z0-9_]{1,40}\s*[+-]\s*\d{1,6})$")


def _constant_name(name):
    return "_" in name or len(name) >= 4


def _raw_row_text(raw):
    """One whitespace-normalised line of the row as the page printed it
    (markup included): the quote a markdown page can carry verbatim."""
    return re.sub(r"\s+", " ", raw).strip()


def _constants_in_cells(fragment, already, raw_row=False):
    seen = {(item["name"], item["value"]) for item in already}
    out = []
    for table in HTML_TABLE.finditer(fragment):
        rows = list(ROW.finditer(table.group(1)))
        if not rows:
            continue
        headers = [text_of(cell, keep_newlines=False).strip()
                   for cell in CELL.findall(rows[0].group(1))]
        labels = [header.lower() for header in headers]
        if any(OFFSET_COLUMN.search(label) for label in labels):
            continue
        header = " ".join(headers)
        for row_match in rows:
            row = row_match.group(1)
            cells = [text_of(cell, keep_newlines=False).strip()
                     for cell in CELL.findall(row)]
            for cell in cells:
                match = (_CELL_EQ.match(cell) or _CELL_PAR.match(cell)
                         or _CELL_NAME_VALUE.match(cell))
                if not match or not _constant_name(match.group(1)):
                    continue
                name, value = match.group(1), match.group(2)
                if (name, value) in seen:
                    continue
                seen.add((name, value))
                out.append({
                    "name": name,
                    "value": value,
                    "decimal": None,
                    "table": header,
                    "origin": "cell",
                    # the evidence is the row as the page printed it; on
                    # a markdown page that includes its markup, which is
                    # exactly what the page carries (docs/clean-room.md)
                    "row": (_raw_row_text(row_match.group(0)) if raw_row
                            else cell),
                })
    return out


# ------------------------------------------------------------------ #
# Constant name lists: rows that state a constant name and its        #
# meaning but print no number.                                        #
# ------------------------------------------------------------------ #

# A page also documents constants it does NOT number: the Control Styles
# mother table (twenty `X styles | Description` tables of BS_/ES_/SS_/...
# names), the `Value | Description` flag tables whose "Value" column
# holds symbolic names (MF_BYCOMMAND, KLF_ACTIVATE), and their kin.  The
# row states the name and what it means but prints no number, so the
# numbered reader rightly passes it by -- yet the name is a documented
# constant and must not be lost ("情報の欠落").  Each row is filed as its
# own tuple (name, no value, the row's own text), never merged into a
# page blob.
#
# Shape gates (a type table must not be stolen by this reader): the
# header must NOT use a type-name label (listed_type_rows owns those),
# and the name cell must look like a constant -- an all-caps identifier
# with an underscore (BS_3STATE, MF_BYCOMMAND, WH_CALLWNDPROC).
CONSTANT_NAME_CELL = re.compile(r"^[A-Z][A-Z0-9_]*_[A-Z0-9_]+$")
# Tables headed "Value | Description", "Error code | Description" and kin
# carry the identifier itself in the first cell: PATCOPY, BLACKNESS,
# S_OK, WSANOTINITIALISED... the underscore form above rejects the
# unhyphenated spellings; this tier takes all-caps identifiers, and the
# event tier takes positioned event/message/command names (onclick...).
UPPER_NAME_CELL = re.compile(r"^[A-Z][A-Z0-9_]+$")
EVENT_NAME_CELL = re.compile(r"^[A-Za-z_][A-Za-z0-9_]+$")
EVENT_LABELS = {"event", "events", "message", "messages", "command", "commands",
                "notification", "notifications", "element", "elements"}


def _const_name_cell_ok(name, name_label):
    if TYPEISH_NAME.match(name):
        return False
    return bool(CONSTANT_NAME_CELL.match(name) or UPPER_NAME_CELL.match(name)
                or (name_label in EVENT_LABELS and EVENT_NAME_CELL.match(name)))
# A base type is not a constant: LONG_PTR, DWORD_PTR, SIZE_T and kin are
# documented in type tables this reader must never claim.  (The type
# tables this reader is walled off from via TYPE_NAME_COLUMNS carry the
# obvious spellings; this blocklist catches the stragglers.)
TYPEISH_NAME = re.compile(
    r"^(LONG|ULONG|DWORD|WORD|SHORT|USHORT|INT|UINT|U?INT8|U?INT16|"
    r"U?INT32|U?INT64|CHAR|UCHAR|WCHAR|TCHAR|BYTE|BOOL|BOOLEAN|FLOAT|"
       r"DOUBLE|SIZE|SSIZE|HANDLE|SOCKET|HRESULT|LRESULT|WPARAM|LPARAM|"
    r"FILETIME|SYSTEMTIME|LARGE_INTEGER|ULARGE_INTEGER|POINTER)_"
    r"|_(PTR|T|TA|TW)$")
_DESC_LABELS = {"description", "meaning", "definition", "remarks",
                "comments", "comment", "notes"}
_CONST_LIST_LABELS = {
    "value", "flag", "flags", "constant", "constants", "style", "styles",
    "identifier", "code", "command", "message", "event", "notification",
    "symbol", "name", "option", "options", "attribute", "attributes",
    "id", "constant name", "flag name", "style name",
    # "Element | Description" heads both structure member lists (the
    # CONSTANT_NAME_CELL gate below keeps those out) and flag/constant
    # name lists; the name is a documented identifier either way.
    "element", "elements",
    "error code", "error codes", "return code", "return codes",
    "status code", "status codes", "code name",
}


def constant_name_rows(fragment, raw_row=False):
    """One dict per documented-but-unnumbered constant row of the page.

    ``name`` (the identifier cell), ``value`` None (the page prints no
    number -- nothing is ever computed), ``table`` (the header row) and
    ``row`` (the evidence).
    """
    out = []
    header = None
    header_name_i = 0
    header_name_label = ""
    for match in ROW.finditer(fragment):
        cells = [text_of(cell, keep_newlines=False).strip()
                 for cell in CELL.findall(match.group(1))]
        if not cells:
            continue
        labels = [re.sub(r"\s+", " ", c).strip().rstrip(":").lower()
                  for c in cells]
        if any(OFFSET_COLUMN.search(label) for label in labels):
            header = None
            continue
        # a header row: one column names constants (or styles/flags), one
        # is a description -- and no type-name label (those are type rows)
        desc_i = [i for i, label in enumerate(labels)
                  if label in _DESC_LABELS]
        name_i = [i for i, label in enumerate(labels)
                  if (label in _CONST_LIST_LABELS or
                      label.endswith(("style", "styles", "flags",
                                      "constants")))
                  and i not in desc_i]
        if name_i and len(labels) >= 2 and \
                not any(label in TYPE_NAME_COLUMNS for label in labels):
            header = " ".join(cells)
            header_name_i = name_i[0]
            header_name_label = labels[name_i[0]]
            continue
        if header is None:
            continue
        if header_name_i >= len(cells):
            continue
        name = cells[header_name_i]
        if not _const_name_cell_ok(name, header_name_label):
            continue
        out.append({
            "name": name,
            "value": None,
            "decimal": None,
            "table": header,
            "origin": "table-name-list",
            "row": (_raw_row_text(match.group(0)) if raw_row
                    else " ".join(cells)),
        })
    return out


# Markdown pipe tables (the MicrosoftDocs/win32 guide style): the readers
# below walk them as rows of cells the way the HTML readers do.  A cell may
# carry inline HTML (`<span id="CBS_AUTOHSCROLL"></span><dl> <dt>**CBS\_
# AUTOHSCROLL**</dt> </dl>`) -- the name is read from the cleaned text
# (`CBS_AUTOHSCROLL`), and the row is quoted as the raw line the page
# printed.  Bold markers and backslash escapes are presentation only and
# are removed before a name or number is matched, never in the quote.
_MD_PIPE_ROW = re.compile(r"^[ \t]*\|.*\|[ \t]*$")
_MD_PIPE_RULE = re.compile(r"^[ \t]*\|[ \t:|-]+\|[ \t]*$")
_MD_BOLD = re.compile(r"\*\*([^*]+)\*\*")
_MD_CODE = re.compile(r"`([^`]*)`")


def _md_cell_clean(cell):
    """One pipe-table cell as text: tags and emphasis off, escapes open."""
    text = text_of(cell, keep_newlines=False)
    text = _MD_BOLD.sub(r"\1", text)
    text = _MD_CODE.sub(r"\1", text)
    return text.replace("\\_", "_").replace("\\*", "*").strip()


def _md_pipe_cells(line):
    inner = line.strip()
    if inner.startswith("|"):
        inner = inner[1:]
    if inner.endswith("|"):
        inner = inner[:-1]
    return [_md_cell_clean(c) for c in inner.split("|")]


def _md_pipe_tables(text):
    """Yield (header_line, header_cells, [(raw_line, cells), ...])."""
    lines = text.splitlines()
    i = 0
    while i < len(lines) - 1:
        if not _MD_PIPE_ROW.match(lines[i]) or \
                not _MD_PIPE_RULE.match(lines[i + 1]):
            i += 1
            continue
        header_line = lines[i]
        header_cells = _md_pipe_cells(header_line)
        i += 2
        rows = []
        while i < len(lines) and _MD_PIPE_ROW.match(lines[i]):
            rows.append((lines[i], _md_pipe_cells(lines[i])))
            i += 1
        yield header_line, header_cells, rows


def constant_tables_text(text):
    """The numbered-constant readers for a markdown page: the embedded
    HTML tables (the sdk-api style, fence stripped) AND the markdown pipe
    tables (the guide style).  Pipe rows are quoted as the raw line the
    page printed."""
    body = _MD_FENCE.sub("", text)
    out = constant_tables(body, raw_row=True)
    seen = {(item["name"], item["value"]) for item in out}
    for _header_line, header_cells, rows in _md_pipe_tables(text):
        labels = [re.sub(r"\s+", " ", c).strip().rstrip(":").lower()
                  for c in header_cells]
        if any(OFFSET_COLUMN.search(label) for label in labels):
            continue
        name_i = _column(labels, CONSTANT_NAME_COLUMNS)
        hex_i = _column(labels, CONSTANT_HEX_COLUMNS)
        dec_i = _column(labels, CONSTANT_DECIMAL_COLUMNS)
        val_i = _column(labels, CONSTANT_VALUE_COLUMNS)
        corr_is = _correspondence_indices(labels)
        if name_i is None and "value" in labels and "weight" in labels:
            name_i = labels.index("value")
            val_i = labels.index("weight")
            hex_i = dec_i = None
        if hex_i in corr_is:
            hex_i = None
        if val_i in corr_is:
            val_i = None
        if dec_i in corr_is:
            dec_i = None
        header = " ".join(header_cells)
        for raw, cells in rows:
            row_quote = re.sub(r"\s+", " ", raw).strip()
            # the pair in one cell: `**WS\_BORDER** 0x00800000L`
            for cell in cells:
                match = (_CELL_EQ.match(cell) or _CELL_PAR.match(cell)
                         or _CELL_NAME_VALUE.match(cell))
                if not match or not _constant_name(match.group(1)):
                    continue
                key = (match.group(1), match.group(2))
                if key in seen:
                    continue
                seen.add(key)
                out.append({
                    "name": match.group(1),
                    "value": match.group(2),
                    "decimal": None,
                    "table": header,
                    "origin": "cell",
                    "row": row_quote,
                })
            value_is = [i for i in (hex_i, val_i, dec_i) if i is not None]
            if name_i is None or not value_is or name_i in value_is:
                continue
            if len(cells) <= name_i or not CONSTANT_IDENT.match(cells[name_i]):
                continue

            def number_at(index):
                if index is None or index >= len(cells):
                    return None, None
                return number_cell(cells[index])

            value = paired = value_from = None
            for index in (hex_i, val_i, dec_i):
                got, pair = number_at(index)
                if got:
                    value = got
                    paired = pair
                    value_from = index
                    break
            if not value:
                continue
            decimal = number_at(dec_i)[0]
            if not decimal or decimal.lower().startswith("0x") \
                    or value_from == dec_i:
                decimal = paired
            elif paired:
                decimal = paired
            key = (cells[name_i], value)
            if key in seen:
                continue
            seen.add(key)
            out.append({
                "name": cells[name_i],
                "value": value,
                "decimal": decimal,
                "table": header,
                "origin": "table",
                "row": row_quote,
            })
    return out


def constant_name_rows_text(text):
    """The name-list reader for a markdown page: the embedded HTML tables
    AND the markdown pipe tables.  Rows are quoted as printed (markup
    included) -- the page carries them verbatim."""
    body = _MD_FENCE.sub("", text)
    out = constant_name_rows(body, raw_row=True)
    seen = {item["name"] for item in out}
    for _header_line, header_cells, rows in _md_pipe_tables(text):
        labels = [re.sub(r"\s+", " ", c).strip().rstrip(":").lower()
                  for c in header_cells]
        if any(OFFSET_COLUMN.search(label) for label in labels):
            continue
        desc_i = [i for i, label in enumerate(labels)
                  if label in _DESC_LABELS]
        name_i = [i for i, label in enumerate(labels)
                  if (label in _CONST_LIST_LABELS or
                      label.endswith(("style", "styles", "flags",
                                      "constants")))
                  and i not in desc_i]
        if not name_i or len(labels) < 2 or \
                any(label in TYPE_NAME_COLUMNS for label in labels):
            continue
        header = " ".join(header_cells)
        header_name_i = name_i[0]
        header_name_label = labels[name_i[0]]
        for raw, cells in rows:
            if header_name_i >= len(cells):
                continue
            name = cells[header_name_i]
            if not _const_name_cell_ok(name, header_name_label):
                continue
            if name in seen:
                continue
            seen.add(name)
            out.append({
                "name": name,
                "value": None,
                "decimal": None,
                "table": header,
                "origin": "table-name-list",
                "row": re.sub(r"\s+", " ", raw).strip(),
            })
    return out


# ------------------------------------------------------------------ #
# Name-list tables: the pages that document many types at once.       #
#                                                                      #
# "Windows Data Types" is one table (Data type | Description) whose    #
# rows carry the type name, what it means, often the typedef behind    #
# it ("This type is declared in WinNT.h as follows: <code>typedef     #
# PVOID HANDLE;</code>") and sometimes the header it lives in.  The    #
# name/value readers read none of this: there is no value column.     #
# Each row is read as printed -- the name, the description, any        #
# declaration the description quotes, any header it states.            #
# ------------------------------------------------------------------ #

# The name column of a name|description *data-type* list.  Bare ``type``
# is deliberately absent: a member table (Field | Type | Description) and
# an option table (Type | Description) carry a Type column whose cells are
# not the documented names -- reading them mints noise (``std``, ``tzi``).
TYPE_NAME_COLUMNS = {
    "data type", "data types", "datatype", "data type name",
    "generic-text data type name", "structure",
}
_FIELD_COLUMNS = {"field", "member", "offset", "option", "parameter",
                  "bit", "flag name", "value"}
_TYPE_DESC_COLUMNS = {
    "description", "definition", "comments", "comment",
    "unicode defined", "ansi defined", "_unicode defined", "_ansi defined",
}
# A row quotes one declaration: a typedef, or a #define whose value is the
# one token that follows the name (``#define CALLBACK __stdcall``).  A
# ``#ifdef``-guarded block is read whole (see _pre_blocks below).
_ROW_DECL = re.compile(
    r"typedef\s+[^;{}]+;|#define\s+[A-Za-z_][A-Za-z0-9_]*\s+[A-Za-z_][A-Za-z0-9_]*")
_ROW_HEADER = re.compile(
    r"(?i)(?:declared|defined|prototype\s+d)?\s*in\s+([A-Za-z][A-Za-z0-9_]*\.h)"
    r"|(?:header|headers)\s*:\s*([A-Za-z][A-Za-z0-9_,\.\s]*\.h)")
_PRE_BLOCK = re.compile(r"(?is)<pre\b[^>]*>(.*?)</pre>")


def _row_code_spans(cell):
    """The <code>...</code> / `...` spans of one cell, tags stripped."""
    out = []
    for match in re.finditer(r"(?is)<code\b[^>]*>(.*?)</code>", cell):
        out.append(text_of(match.group(1), keep_newlines=False).strip())
    for match in re.finditer(r"`([^`\n]+)`", cell):
        out.append(match.group(1).strip())
    return out


def _pre_blocks(cell):
    """The <pre> blocks of one cell, newlines preserved (a ``#ifdef``
    branch block is only readable line by line)."""
    out = []
    for match in _PRE_BLOCK.finditer(cell):
        inner = re.sub(r"(?is)</?code\b[^>]*>", "", match.group(1))
        text = text_of(inner, keep_newlines=True).strip("\n")
        if text.strip():
            out.append(text)
    return out


def _block_names(text):
    """Every name a declaration block defines (branch by branch)."""
    names = []
    # only the conditional directives are stripped -- a #define line is
    # the declaration, not scaffolding
    body = re.sub(r"(?m)^\s*#\s*(?:if|ifdef|ifndef|elif|else|endif)\b.*$",
                  "", text)
    # statement by statement: a typedef with a braced body declares its tag
    # *and* its tail aliases (``} UNICODE_STRING;``)
    for statement in re.findall(r"typedef\s+(?:[^;{}]|\{[^}]*\})*;|"
                               r"#define\s+[A-Za-z_][A-Za-z0-9_]*\b[^;\n]*",
                                body):
        for name in declared_names(statement):
            if name not in names:
                names.append(name)
    for name in declared_names(text):
        if name not in names:
            names.append(name)
    return names


def _decl_of(text):
    kind = _kind_of(text)
    if re.match(r"\s*#\s*(?:if|ifdef|ifndef)\b", text):
        # a conditional block: its kind is what the branches define,
        # not the ``defined(...)`` parentheses _kind_of would read
        stripped = re.sub(
            r"(?m)^\s*#\s*(?:if|ifdef|ifndef|elif|else|endif)\b.*$", "",
            text)
        if re.search(r"typedef\b", stripped):
            kind = "typedef"
        elif re.search(r"#\s*define\b", stripped):
            kind = "macro"
        else:
            kind = None
    elif kind is None and _block_names(text):
        kind = "typedef"
    return {
        "text": text,
        "markup": "table-row",
        "spacing": _spacing(text),
        "role": "syntax",
        "calling_convention": _calling_convention(text),
        "kind": kind,
        "members": _members(text),
        "member_types": [],
        "abi_flags": abi_flags(text),
        # a name-list row quotes the declaration the *reference table*
        # states for the type -- never sample code
        "implementation": False,
    }


def listed_type_rows(fragment):
    """Rows of a name|description table: one dict per documented name.

    Each row states ``name`` (the identifier cell), ``description`` (the
    remaining cells, as printed), ``declarations`` (the C declarations the
    row's own text quotes -- a typedef body, a #define, or a whole
    ``#ifdef`` branch block), ``requirements`` (the headers the row's text
    states) and ``row`` (the evidence).  The reader walks the *rows* of
    the page, not the <table> elements: the archived pages nest a code
    table inside a row, and the outer table's HTML never closes again.

    A continuation row that prints only a declaration block (the
    ``#ifdef _WIN64`` shape) is read as documentation of the names the
    block defines.
    """
    out = []
    header = None
    for match in ROW.finditer(fragment):
        cells = [text_of(cell, keep_newlines=False).strip()
                 for cell in CELL.findall(match.group(1))]
        if not cells:
            continue
        labels = [re.sub(r"\s+", " ", c).strip().rstrip(":").lower()
                  for c in cells]
        if any(OFFSET_COLUMN.search(label) for label in labels) \
                or any(label in _FIELD_COLUMNS for label in labels):
            header = None
            continue
        name_i = None
        for index, label in enumerate(labels):
            if label in TYPE_NAME_COLUMNS:
                name_i = index
                break
        if name_i is not None and (len(cells) > 1 or
                                   any(l in _TYPE_DESC_COLUMNS
                                       for l in labels)):
            header = " ".join(cells)
            header_name_i = name_i
            continue
        if header is None:
            continue
        name = cells[0].strip().strip("`") if cells else ""
        # the description side of the row (the raw cell markup, so that
        # <pre> blocks keep their lines and <code> spans keep their text)
        desc_markup = match.group(1)
        raw_cells = CELL.findall(match.group(1))
        desc_raw = " ".join(raw_cells[1:] if len(raw_cells) > 1 else raw_cells)
        declarations = []
        blocks = _pre_blocks(desc_raw)
        if blocks:
            declarations = [_decl_of(block) for block in blocks]
        else:
            for span in _row_code_spans(desc_raw):
                for piece in _ROW_DECL.findall(span) or [span.strip()]:
                    piece = piece.strip()
                    if piece and _block_names(piece):
                        declarations.append(_decl_of(piece))
        plain = text_of(desc_raw, keep_newlines=False)
        if not blocks:
            for piece in _ROW_DECL.findall(plain):
                piece = piece.strip()
                if piece and _block_names(piece) \
                        and not any(d["text"].find(piece) >= 0
                                    for d in declarations):
                    declarations.append(_decl_of(piece))
        requirements = []
        for row_header in _ROW_HEADER.finditer(plain):
            for group in row_header.groups():
                if not group:
                    continue
                for item in re.split(r",", group):
                    item = item.strip().strip(".")
                    if item and item.lower().endswith(".h"):
                        requirements.append({
                            "field": "header",
                            "label": "declared in",
                            "value": item,
                            "evidence": row_header.group(0).strip(),
                        })
        if CONSTANT_IDENT.match(name):
            out.append({
                "name": name,
                "description": plain,
                "declarations": declarations,
                "requirements": requirements,
                "table": header,
                "row": " ".join(cells),
            })
        elif declarations:
            # a continuation row: the block documents the names it defines
            for block_name in _block_names(declarations[0]["text"]):
                out.append({
                    "name": block_name,
                    "description": plain,
                    "declarations": declarations,
                    "requirements": requirements,
                    "table": header,
                    "row": " ".join(cells),
                })
        else:
            header = None
    # A row whose HTML nests the code block splits into two reads (the name
    # row and the block's own row): same name, union of what was read.
    merged = {}
    order = []
    for row in out:
        key = row["name"]
        if key not in merged:
            merged[key] = row
            order.append(key)
            continue
        keep = merged[key]
        if len(row["description"]) > len(keep["description"]):
            keep["description"] = row["description"]
        if len(row["row"]) > len(keep["row"]):
            keep["row"] = row["row"]
        for decl in row["declarations"]:
            if not any(d["text"] == decl["text"]
                       for d in keep["declarations"]):
                keep["declarations"].append(decl)
        for req in row["requirements"]:
            if not any(q["value"] == req["value"]
                       and q["evidence"] == req["evidence"]
                       for q in keep["requirements"]):
                keep["requirements"].append(req)

    return [merged[key] for key in order]


def listed_type_rows_text(text):
    """The same reader for a markdown page: strip fences so code spans and
    tables are the only carriers, then read the HTML tables embedded in
    the markdown (the sdk-api style)."""
    body = _MD_FENCE.sub("", text)
    return listed_type_rows(body)


# ------------------------------------------------------------------ #
# More numbered constants: the definitions a *syntax declaration*      #
# quotes, and the values a page prints in running prose.               #
#                                                                      #
# A page prints a number for a constant in more shapes than a          #
# name/value table: the `#define NAME <number>` line of a macro        #
# declaration, the `NAME = <number>` member of an enum body it         #
# quotes, and the inline spelling `NAME (0x0400)` / `NAME = 0x0400` of #
# a paragraph.  The same honesty rule as the table reader applies:     #
# the quote is the text the page printed, only a numeric right-hand    #
# side is a value, and example code is never read (these readers are   #
# given syntax declarations and prose only, by build-kb.py).           #
# ------------------------------------------------------------------ #

# ``#define NAME (0x0400)`` / ``#define NAME MAKE_D3DMHRESULT(2158)`` /
# ``#define NAME (WM_USER + 255)``.  The value is quoted as printed --
# never computed.  A function-like macro (``#define SIZEOF(x)``) is not
# a numbered constant.  Collapsed pages glue several #define tokens on
# one line, so the reader is not line-anchored.
_DEFINE_VALUE = (
    r"(?:"
    r"\(?\s*(?:0[xX][0-9A-Fa-f]+|-?\d+)\s*[uUlL]*\s*\)?"
    r"|[A-Z][A-Z0-9_]{1,60}\s*[+-]\s*(?:0[xX][0-9A-Fa-f]+|\d+)[uUlL]*"
    r"|\(\s*[A-Z][A-Z0-9_]{1,60}\s*[+-]\s*(?:0[xX][0-9A-Fa-f]+|\d+)[uUlL]*\s*\)"
    r"|[A-Z][A-Z0-9_]{2,60}\s*\(\s*(?:0[xX][0-9A-Fa-f]+|-?\d+)\s*\)"
    r")"
)
_DEFINE_ROW = re.compile(
    r"^\s*#\s*define\s+([A-Za-z_][A-Za-z0-9_]*)\s+"
    + _DEFINE_VALUE +
    r"\s*(?:(?:/\*[^*]*\*/|//[^\n]*)\s*)?$")
_DEFINE_ANY = re.compile(
    r"#\s*define\s+([A-Za-z_][A-Za-z0-9_]*)(?!\s*\()\s+" + _DEFINE_VALUE)
_ENUM_MEMBER_ANY = re.compile(
    r"\b([A-Z][A-Z0-9_]{2,})\s*=\s*"
    r"\(?\s*(0[xX][0-9A-Fa-f]+|-?\d+)\s*[uUlL]*\s*\)?")

# ``NAME = 0x01,`` -- an enum member that carries its value.  Applied
# only inside a declaration that has an ``enum`` and a ``{`` (the
# caller's check), so an initialiser in a struct body or a default
# argument of a prototype is never taken for one.
_ENUM_MEMBER_ROW = re.compile(
    r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*"
    r"\(?\s*(0[xX][0-9A-Fa-f]+|-?\d+)\s*[uUlL]*\)?\s*,\s*"
    r"(?:(?:/\*[^*]*\*/|//[^\n]*)\s*)?$|"
    r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*"
    r"\(?\s*(0[xX][0-9A-Fa-f]+|-?\d+)\s*[uUlL]*\)?\s*"
    r"(?:/\*[^*]*\*/\s*)?$")


def define_value_rows(text):
    """``#define NAME <number-or-printed-expression>`` in a syntax block.

    Collapsed pages (several ``#define`` tokens on one line) are split with
    finditer.  ``MAKE_D3DMHRESULT(2158)`` and ``WM_USER+255`` stay as
    printed -- never computed.  ``#define FOO(x)`` is skipped.
    """
    out = []
    seen = set()
    blob = text or ""
    for match in _DEFINE_ANY.finditer(blob):
        name = match.group(1)
        value = match.group(0)
        # value is the RHS of this match
        rhs = blob[match.start():match.end()]
        parts = re.split(r"#\s*define\s+" + re.escape(name) + r"\s+", rhs, 1)
        rhs_text = parts[-1] if parts else match.group(2)
        rhs_text = re.split(r"//|/\*", rhs_text, 1)[0].strip()
        rhs_text = re.sub(r"\s+", " ", rhs_text).strip()
        # prefer a compact form for ctor / sum expressions
        if re.match(r"^[A-Z]", rhs_text) or rhs_text.startswith("("):
            compact = re.sub(r"\s+", "", rhs_text)
        else:
            compact = rhs_text
        key = (name, compact)
        if key in seen:
            continue
        seen.add(key)
        out.append({"name": name, "value": compact,
                    "table": "#define", "origin": "define",
                    "row": match.group(0).strip()[:240]})
    return out


def enum_value_rows(text):
    """``NAME = <number>`` members of an enum body a syntax block quotes.

    Collapsed ``typedef enum { A = 1, B = 2 }`` on one line is split with
    finditer.  The number is quoted as printed.
    """
    if not text or "{" not in text or "enum" not in text.lower():
        return []
    out = []
    seen = set()
    for match in _ENUM_MEMBER_ANY.finditer(text):
        name, value = match.group(1), match.group(2)
        key = (name, value)
        if key in seen:
            continue
        seen.add(key)
        out.append({"name": name, "value": value, "table": "enum member",
                    "origin": "enum", "row": match.group(0).strip()[:240]})
    return out


# Running prose also numbers a constant, ``WM_USER (0x0400)`` /
# ``WM_USER = 0x0400``.  Precision over recall: hexadecimal only (a
# decimal in parentheses is too often "(2)" a version), the name is an
# all-caps identifier of at least four characters, and without an
# underscore it has to be at least six (``HTERROR`` borders on fine,
# ``BYTE`` at length four does not).  PRE/TABLE/CODE regions are read by
# the other readers and are stripped before this one runs, so a value is
# not recorded twice.
_PROSE_REGION = re.compile(r"(?is)<(pre|table|code)\b[^>]*>.*?</\1>")
_PROSE_EQ = re.compile(
    r"(?<![\w(\[])([A-Z][A-Z0-9_]{3,})\s*=\s*(0[xX][0-9A-Fa-f]+)\b")
_PROSE_PAREN = re.compile(
    r"(?<![\w(\[])([A-Z][A-Z0-9_]{3,})\s*\(\s*(0[xX][0-9A-Fa-f]+)\s*\)")
_PROSE_NAME_OK = re.compile(r"^(?:[A-Z][A-Z0-9]*_[A-Z0-9_]*|[A-Z0-9_]{6,})$")


def prose_constants(fragment):
    """``NAME (0x...)`` / ``NAME = 0x...`` spelled in running prose.

    The evidence ``row`` is the matched span itself.  A matched name is
    still only a *documented* constant: a name the page does not number
    has no row here, and a win32-only number is never treated as a
    Windows CE value by the generator.
    """
    out = []
    seen = set()
    fragment = _PROSE_REGION.sub(" ", fragment)
    text = text_of(fragment, keep_newlines=False)
    for pattern in (_PROSE_EQ, _PROSE_PAREN):
        for match in pattern.finditer(text):
            name, value = match.group(1), match.group(2)
            if not _PROSE_NAME_OK.match(name) or (name, value) in seen:
                continue
            seen.add((name, value))
            out.append({"name": name, "value": value,
                        "table": "prose value", "origin": "prose",
                        "row": match.group(0)})
    return out


def syntax_constant_rows(declarations):
    """The constant definitions a page's *syntax* declarations quote.

    build-kb.py hands this reader the declarations a page already
    classified, so the clean-room rule is kept by construction: a
    ``role: "example"`` or ``implementation`` block is sample code and
    yields nothing here -- sample ``#define cEvents 3`` is not a
    documented constant of the SDK.
    """
    out = []
    for decl in declarations or []:
        if decl.get("role") != "syntax" or decl.get("implementation"):
            continue
        out.extend(define_value_rows(decl.get("text") or ""))
        out.extend(enum_value_rows(decl.get("text") or ""))
    return out


_MD_FENCE = re.compile(r"(?ms)^```.*?^```")
_MD_CODE = re.compile(r"`([^`\n]+)`")


def prose_constants_text(text):
    """The markdown twin of :func:`prose_constants` (no HTML to strip).

    Fenced code (````` ``` `````) and inline code spans are read by the
    declaration reader (or are example code), so the prose reader sees
    the text with them removed -- the same no-double-record rule as the
    PRE/TABLE/CODE stripping on the HTML side.
    """
    out = []
    seen = set()
    text = _MD_FENCE.sub(" ", text or "")
    text = _MD_CODE.sub(r" \1 ", text)
    for pattern in (_PROSE_EQ, _PROSE_PAREN):
        for match in pattern.finditer(text):
            name, value = match.group(1), match.group(2)
            if not _PROSE_NAME_OK.match(name) or (name, value) in seen:
                continue
            seen.add((name, value))
            out.append({"name": name, "value": value,
                        "table": "prose value", "origin": "prose",
                        "row": match.group(0)})
    return out


_ORDINAL_COLUMN = re.compile(r"(?i)^ordinals?$")
_EXPORT_COLUMN = re.compile(r"(?i)^(?:export|export name|function|symbol|"
                            r"entry point)s?$")
# ``the floating point C run-time library, Fpcrt.dll`` -- the DLL the
# exports on this page belong to.  Only a sentence on the same page counts.
_EXPORTS_OF_DLL = re.compile(
    r"(?i)exports?\s+(?:that\s+are\s+)?(?:required\s+)?for\s+[^.]{0,80}?"
    r"\b([A-Za-z0-9_]+\.dll)\b")


def export_ordinal_tables(fragment):
    """``Export | Ordinal`` rows: the one place the documents print ordinals.

    ``Exports from the Floating Point C Run-Time Library`` lists the exports
    of ``Fpcrt.dll`` with the ordinal each one must use.  Every other page
    of this corpus states no ordinal, and none is invented: only a table
    with an ordinal column and an export column is read, the number is kept
    as printed, and the DLL comes from a sentence on the same page (empty
    when the page names none).
    """
    out = []
    plain = text_of(fragment, keep_newlines=False)
    dll_match = _EXPORTS_OF_DLL.search(plain)
    dll = dll_match.group(1) if dll_match else ""
    dll_evidence = (re.sub(r"\s+", " ", dll_match.group(0)).strip()
                    if dll_match else "")
    for table in TABLE.finditer(fragment):
        rows = ROW.findall(table.group(1))
        if len(rows) < 2:
            continue
        headers = [re.sub(r"\s+", " ", text_of(cell, keep_newlines=False))
                   .strip() for cell in CELL.findall(rows[0])]
        labels = [header.lower() for header in headers]
        ordinal_i = next((i for i, label in enumerate(labels)
                          if _ORDINAL_COLUMN.match(label)), None)
        name_i = next((i for i, label in enumerate(labels)
                       if _EXPORT_COLUMN.match(label)), None)
        if ordinal_i is None or name_i is None or ordinal_i == name_i:
            continue
        header = " ".join(headers)
        for row in rows[1:]:
            cells = [re.sub(r"\s+", " ", text_of(cell, keep_newlines=False))
                     .strip() for cell in CELL.findall(row)]
            if len(cells) <= max(ordinal_i, name_i):
                continue
            name, printed = cells[name_i], cells[ordinal_i]
            if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_@?$]*", name):
                continue
            if not re.fullmatch(r"\d+", printed):
                continue
            out.append({
                "name": name,
                "ordinal": int(printed),
                "ordinal_printed": printed,
                "dll": dll,
                "dll_evidence": dll_evidence,
                "table": header,
                "row": " ".join(cell for cell in cells if cell),
            })
    return out


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
        # An #ifdef/#if-fenced block is code unless every branch only
        # declares: the conditional typedefs a reference header prints
        # (``#ifdef _WIN64 typedef int HALF_PTR; #else ...``) are interface
        # material, and the branch keywords are scaffolding, not statements.
        body = re.sub(
            r"(?m)^\s*#\s*(?:if|ifdef|ifndef|elif|else|endif)\b.*$", "",
            text)
        body = body.replace("#if", "\n#if")  # inline forms, one per line
        body = re.sub(
            r"(?m)^\s*#\s*(?:if|ifdef|ifndef|elif|else|endif)\b.*$", "",
            body)
        if re.search(r"#\s*include\b", body):
            return True
        if not body.strip():
            return True
        return bool(IMPLEMENTATION_STATEMENT.search(body))
    if not re.search(r"[;{}]", text):
        return False            # prose, a field list, a documentation header
    return bool(IMPLEMENTATION_STATEMENT.search(text))


def _is_build_script(text):
    """True when a block is makefile/Sources-file variable assignments.

    The Sources, Makefile and .bat pages print blocks like
    ``TARGETLIBS=$(_COMMONOAKROOT)\\lib\\$(_CPUDEPPATH)\\blcommon.lib``.  They
    contain ``(`` and ``)`` only because of ``$(...)`` expansion, so the
    generic "has parentheses -> function" rule used to call them C functions
    and gave the build variable an entity of kind ``function``.  A build
    variable is not an exported symbol and must not reach a header or a .def,
    so it is named for what it is.

    A line of C (a ``;``, a brace, a type before the name) disqualifies the
    block; the reader never rewrites it, it only labels it.
    """
    if "$(" not in text or "=" not in text:
        return False
    saw = False
    for line in text.splitlines():
        stripped = line.strip().rstrip("\\").strip()
        if not stripped or stripped.startswith(("#", "!", "//", "rem ", "REM ")):
            continue
        if any(ch in stripped for ch in ";{}"):
            return False
        if re.match(r"^[A-Za-z_][A-Za-z0-9_]*\s*=", stripped):
            saw = True
            continue
        # a continuation line of a previous assignment: a bare path/token
        if re.match(r"^[-$()A-Za-z0-9_.\\/:*]+$", stripped):
            continue
        return False
    return saw


def _kind_of(text):
    lowered = text.lower()
    if _is_build_script(text):
        return "build-variable"
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
    if re.match(r"\s*typedef\b", text):
        return "typedef"
    if "(" in text and ")" in text:
        return "function"
    return None


def _is_macro_block(text):
    """True when a block is only ``#define`` / ``#pragma`` / ``#undef`` lines.

    A comment and a backslash continuation belong to the macro.  A ``typedef``,
    a statement or an ``#include`` does not -- those stay whatever role the
    rest of the reader gives them.  The page printed a declaration; this does
    not repair or complete it.
    """
    if not text or not re.search(r"#\s*define\b", text):
        return False
    continued = False
    saw = False
    for line in text.splitlines():
        stripped = line.strip()
        if not stripped:
            continue
        if continued:
            continued = stripped.endswith("\\")
            continue
        if stripped.startswith(("//", "/*", "*", "*/")):
            continue
        if re.match(r"#\s*(define|pragma|undef)\b", stripped):
            saw = True
            continued = stripped.endswith("\\")
            continue
        return False
    return saw


def _section_title_after(fragment, pos, window=800):
    """The first heading or section label after ``pos``, lower-cased."""
    titles = []
    for match in HEADING.finditer(fragment, pos, pos + window):
        titles.append((match.start(),
                       text_of(match.group(0), keep_newlines=False)
                       .strip(": ").lower()))
    for match in re.finditer(
            r"(?is)<p\b[^>]*\bclass\s*=\s*[\"']label[\"'][^>]*>\s*"
            r"(?:<[^>]+>\s*)*([^<]{2,40})",
            fragment[pos:pos + window]):
        titles.append((pos + match.start(),
                       re.sub(r"\s+", " ", match.group(1)).strip(": ").lower()))
    for start, _end, title in _p_class_sections(fragment, pos, pos + window):
        titles.append((start, title))
    if not titles:
        return ""
    titles.sort()
    return titles[0][1]


_PROTO_AFTER = ("parameters", "parameter", "members", "elements", "constants",
                "c/c++ parameters", "return values", "return value",
                "enumerators", "enumerator values")
_NOT_PROTO_BEFORE = ("parameters", "return values", "return value", "remarks",
                     "general remarks", "script syntax", "script parameters",
                     "script return value", "example", "examples",
                     "code example", "sample", "samples", "example code")
# A resource script states the keyword in uppercase (``IDD_ABOUT DIALOG``,
# a line that starts with ``MENU``).  A C parameter named ``dialog`` is not
# that statement; a case-insensitive match used to reject
# ``showModalDialog``.
_RESOURCE_GRAMMAR = re.compile(
    r"(?m)^[ \t]*(?:[A-Za-z_][\w]*\s+)?"
    r"(?:ACCELERATORS|DIALOGEX|DIALOG|STRINGTABLE|RCDATA|VERSIONINFO|MENU)\b"
    r"|^\s*POPUP\b|\[\[")
_VB_BLOCK = re.compile(
    r"(?i)^\s*(?:dim |sub |function |private |public |end |select )")
# Compact Framework pages print JScript as ``protected abstract function
# Dispose( disposing : boolean )``.  That is not a C prototype.  A comment
# that merely says "callback function" is not this form.
_JSCRIPT_FUNCTION = re.compile(
    r"(?im)^(?!\s*(?://|/\*|\*))\s*"
    r"(?:(?:public|private|protected|internal|override|virtual|abstract|"
    r"sealed|static)\s+)*function\s+[A-Za-z_]")
_SIGNATURE = re.compile(
    r"(?is)^(?:typedef\s+)?(?:enum\s+|struct\s+|union\s+)?"
    r"[A-Za-z_][\w\s\*]*\s+[*&]*\s*"
    r"[A-Za-z_][\w]*(?:::[A-Za-z_][\w]*)?\s*\(")
# Function pointer typedef: ``DWORD (APIENTRY *PDD_CREATESURFACEEX)(...)``
# or ``typedef DWORD (*LPFN)(...)``
_FUNC_PTR_TYPEDEF = re.compile(
    r"(?is)^(?:typedef\s+)?[A-Za-z_][\w\s\*]*\(\s*(?:\w+\s+)?\*\s*"
    r"[A-Za-z_][\w]*\s*\)\s*\(")
# Constructor-style declaration: ``ClassName();`` (single line, no type prefix)
_CONSTRUCTOR_DECL = re.compile(
    r"(?i)^[A-Za-z_][\w]*(?:::[A-Za-z_][\w]*)?\s*\(\s*\)\s*;?\s*$")
# ``typedef CComAutoCriticalSection AutoCriticalSection`` is the declaration.
# The page omitted the semicolon.  A sentence that starts with typedef is not
# this form: the whole paragraph has to be the two identifiers.
_TYPEDEF_ALIAS = re.compile(
    r"(?i)^typedef\s+[A-Za-z_][\w:<>]*\s+[A-Za-z_][\w:]*\s*;?\s*$")


def _prototype_name(text):
    """The identifier immediately before the first call parenthesis."""
    cleaned = re.sub(r"/\*.*?\*/", " ", text or "", flags=re.S)
    cleaned = re.sub(r"//.*?$", " ", cleaned, flags=re.M)
    match = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", cleaned)
    return match.group(1) if match else ""


def _slot_belongs_to_title(text, page_title):
    """A prototype slot is this page's declaration only when the title names it.

    A title that is not one API name (``IContact Properties``) has no entity,
    so the quote stays unattached.  A title that names an API does not adopt
    a different function printed in the same slot (``CryptDuplicateHash`` on
    the ``CryptDuplicateKey`` page, ``WindowProc`` on ``WM_NCPAINT``).
    A title that lists several names (``strcpy, wcscpy``) or prints
    ``Interface::Member Method`` names those APIs; the slot has to print
    one of them.
    """
    names = documented_title_names(page_title)
    if not names:
        return True
    cleaned = re.sub(r"/\*.*?\*/", " ", text or "", flags=re.S)
    cleaned = re.sub(r"//.*?$", " ", cleaned, flags=re.M)
    return any(name_in_syntax(name, cleaned) for name in names)


def _fragment_defines(fragment, name):
    """True when this page prints ``#define <name>``."""
    if not name:
        return False
    return re.search(r"#\s*define\s+" + re.escape(name) + r"\b",
                     fragment or "") is not None


def _is_documented_prototype(text):
    """A block the page put in the declaration slot, not a call or a script.

    Resource-compiler grammar (``DIALOG``, ``[[optional]]``) and Visual Basic
    are not C prototypes.  A default argument (``tStart = 0``) still is.
    """
    body = (text or "").strip()
    if not body or _VB_BLOCK.match(body) or _RESOURCE_GRAMMAR.search(body):
        return False
    if _JSCRIPT_FUNCTION.search(body):
        return False
    if re.match(r"(?i)(?:if|for|while|switch|return|sizeof|do|else|case)\b",
                body):
        return False
    lowered = body.lower()
    if lowered.startswith(("typedef enum", "typedef struct", "typedef union",
                           "enum ", "struct ", "union ")):
        return True
    lines = [line.strip() for line in body.splitlines()
             if line.strip() and not line.strip().startswith(("/*", "*", "//"))]
    # A long parameter list is still the declaration.  A long block with a
    # brace is a body, not the prototype the page put in the slot.
    if len(lines) > 8 and ("{" in body or not (
            _SIGNATURE.match(body) and ";" in body)):
        return False
    # Check standard signature, function pointer typedef, or constructor
    return bool(_SIGNATURE.match(body) or _FUNC_PTR_TYPEDEF.match(body) or
                _CONSTRUCTOR_DECL.match(body)) and (";" in body or len(lines) <= 3)


def _section_title_before(fragment, pos):
    """The last heading or section label before ``pos``, lower-cased."""
    titles = []
    for match in HEADING.finditer(fragment, 0, pos):
        titles.append((match.start(),
                       text_of(match.group(0), keep_newlines=False)
                       .strip(": ").lower()))
    for match in re.finditer(
            r"(?is)<p\b[^>]*\bclass\s*=\s*[\"']label[\"'][^>]*>\s*"
            r"(?:<[^>]+>\s*)*([^<]{2,40})", fragment[:pos]):
        titles.append((match.start(),
                       re.sub(r"\s+", " ", match.group(1)).strip(": ").lower()))
    for start, _end, title in _p_class_sections(fragment, 0, pos):
        titles.append((start, title))
    if not titles:
        return ""
    titles.sort()
    return titles[-1][1]


_EXAMPLE_SECTION = ("example", "examples", "code example", "sample",
                    "samples", "example code")


def _looks_like_declaration(text):
    if _is_macro_block(text):
        return 8 <= len(text) <= 4000
    if len(text) < 8 or len(text) > 4000:
        return False
    return ("(" in text and ")" in text) or ";" in text or "{" in text


def _syntax_paragraph(inner, strict):
    """The declaration text of a Syntax paragraph, or None.

    An unclosed ``<p>`` runs into the member ``<dl>``.  The declaration is
    the text before that list, when that text is itself a prototype.  A
    clsRef/blue Syntax paragraph (``strict``) is kept only when it is a C
    prototype or a typedef alias.  ``SINK_ENTRY(id, dispid, fn)`` and
    ``Len(<string>)`` are calling forms the page did not print as C, and
    they are not turned into one.
    """
    cut_html = re.split(
        r"(?i)<(?:dl|table|h[1-6]|ul|ol|pre)\b", inner, maxsplit=1)[0]
    cut = text_of(cut_html).strip()
    full = text_of(inner).strip()
    if _TYPEDEF_ALIAS.match(cut):
        return cut, False
    if _is_documented_prototype(cut) and not is_implementation(cut) \
            and (strict or cut != full):
        return cut, False
    if strict:
        return None
    if _looks_like_declaration(full) and re.search(r"[;{()]", full):
        return full, is_implementation(full)
    return None


def declarations(fragment, page_title=None):
    """Syntax blocks of one page, with their markup and the raw text."""
    out = []
    # ``C/C++ Syntax`` is the declaration on the dual Script/C++ template.
    # ``Script Syntax`` is Visual Basic and is not read as a C declaration.
    # ``Syntax 1`` / command-line ``syntax`` headings are grammar or a tool
    # invocation, not this heading, so they are not listed.
    syntax_region = region(fragment, "syntax", "declaration", "prototype",
                           "c/c++ syntax", "c/c++syntax")
    for match in PRE.finditer(fragment):
        attrs, inner = match.group(1), match.group(2)
        text = text_of(inner)
        if not _looks_like_declaration(text):
            continue
        implementation = is_implementation(text)
        macro_block = _is_macro_block(text)
        role = "example" if implementation else (
            "syntax" if (syntax_region and
                         syntax_region.find(inner[:200]) != -1) else "example")
        # A block that is only #define/#pragma lines is the declaration of
        # those macros, unless the page put it under an Example heading.
        # Templates without a Syntax heading were leaving these as examples,
        # so a header generator never saw them.
        if role == "example" and macro_block and not implementation:
            title = _section_title_before(fragment, match.start())
            if title not in _EXAMPLE_SECTION and not title.startswith("example"):
                role = "syntax"
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
            # A page with an Example pre as well still prints the prototype
            # immediately before Parameters / Members / Elements.  That slot
            # is the declaration.  A block already under Example, or one that
            # follows Parameters, is a call, not this slot.  Resource-compiler
            # grammar and Visual Basic stay out.
            if role == "example" and _is_documented_prototype(text):
                prev = _section_title_before(fragment, match.start())
                nxt_any = _section_title_after(fragment, match.end())
                if nxt_any in _PROTO_AFTER and prev not in _NOT_PROTO_BEFORE \
                        and not prev.startswith("example") \
                        and not prev.startswith("sample"):
                    role = "syntax"
                    # A page that also prints ``#define Name`` is documenting a
                    # macro.  The prototype-shaped line is the calling form,
                    # not a second declaration that should replace the macro.
                    # A prototype of a different name than the title is not
                    # this page's declaration.
                    body = text.lstrip().lower()
                    if body.startswith(("typedef enum", "typedef struct",
                                        "typedef union", "enum ", "struct ",
                                        "union ")):
                        pass
                    elif not _slot_belongs_to_title(text, page_title) \
                            or _fragment_defines(fragment, _prototype_name(text)):
                        role = "example"
        out.append({
            "text": text,
            "markup": (re.search(r'class\s*=\s*"([^"]+)"', attrs, re.I) or
                       [None, "pre"])[1] if 'class=' in attrs.lower() else "pre",
            "spacing": _spacing(text),
            "calling_convention": _calling_convention(text),
            "role": role,
            "kind": "macro" if macro_block else _kind_of(text),
            "members": _members(text),
            "member_types": [member_type(line) for line in _members(text)],
            "abi_flags": abi_flags(text),
            "implementation": implementation,
        })
    if not any(d["role"] == "syntax" for d in out):
        # An ``<h*>`` Syntax region keeps the looser paragraph rule.  A
        # clsRef/blue Syntax region is used only when there is no heading,
        # and only a C prototype or a typedef alias is the declaration.
        blocks = []
        if syntax_region:
            blocks.append((syntax_region, False))
        labeled = labeled_region(
            fragment, "syntax", "declaration", "prototype",
            "c/c++ syntax", "c/c++syntax")
        if labeled:
            blocks.append((labeled, True))
        for block, strict in blocks:
            taken = None
            for para in PARA.finditer(block):
                taken = _syntax_paragraph(para.group(1), strict)
                if taken:
                    break
            if not taken:
                continue
            text, implementation = taken
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
    if re.match(r"\s*typedef\b", text) and "{" not in text:
        # ``typedef unsigned long DWORD, *PDWORD;`` -- every alias of a
        # brace-less typedef is declared by it.  A function-pointer
        # typedef (``typedef int (*FARPROC)();``) is read by the
        # pointer-name rule below instead.
        body = text.split(";", 1)[0]
        body = re.sub(r"^\s*typedef\s+", "", body)
        for part in body.split(","):
            if "(" in part:
                continue
            ids = _C_ID.findall(part)
            if ids:
                add(ids[-1])
        if names:
            return [name for name in names if not name.startswith("__")]
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
        # A block that is only #define definition lines is the declaration
        # of those macros (the message reference prints ``#define WM_CREATE
        # 0x0001`` with no Syntax heading at all), unless the page put it
        # under an Example heading -- same rule as the HTML reader.
        if role == "example" and _is_macro_block(body) and not implementation:
            title = ""
            for line in before.splitlines()[::-1]:
                m = re.match(r"(?im)^#{1,6}\s+(.+?)\s*$", line)
                if m:
                    title = m.group(1).strip().lower()
                    break
            if title not in _EXAMPLE_SECTION and \
                    not title.startswith("example"):
                role = "syntax"
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


_LEARN_SUFFIX = re.compile(r"\s*\|\s*Microsoft Learn\s*$", re.I)
_WIN_SUFFIX = re.compile(r"\s*\(Windows[^)]*\)\s*$", re.I)
# ``abort Method (DOMDocument)`` -- the title prints the member and the parent.
# A title that is only ``abort Method`` does not name the parent, so it is not
# this form.  The parent is taken as printed, not completed to a C++ interface.
_MEMBER_TITLE = re.compile(
    r"^([A-Za-z_][\w]*)\s+(?:Method|Property|Event)\s*"
    r"\(([A-Za-z_][\w./]*)\)\s*$")


def interface_member_title(title):
    """``abort Method (DOMDocument) (Windows CE 5.0)`` -> ``DOMDocument::abort``.

    None when the title does not print both.  Used only for a page whose
    ``C/C++ Syntax`` heading holds the declaration, so a script-only page is
    not turned into an entity.
    """
    if not title:
        return None
    text = _LEARN_SUFFIX.sub("", title).strip()
    for _ in range(2):
        text = _WIN_SUFFIX.sub("", text).strip()
    match = _MEMBER_TITLE.match(text)
    if not match:
        return None
    return f"{match.group(2)}::{match.group(1)}"


_QUALIFIED_KIND = re.compile(
    r"^([A-Za-z_][\w]*::[A-Za-z_][\w]*)\s+(?:Method|Property|Event)\s*$",
    re.I)
_IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")


def _title_core(title):
    """Drop the Learn suffix and a trailing ``(Windows …)`` parenthetical."""
    if not title:
        return ""
    text = _LEARN_SUFFIX.sub("", title).strip()
    for _ in range(2):
        text = _WIN_SUFFIX.sub("", text).strip()
    return text


# ``MSMQMessage.Priority`` prints the parent and the member with a dot, the
# same fact as ``Interface::Member``.  ``winbase.h`` is a file name, not a
# member, so a trailing extension is not this form.
_DOTTED_MEMBER = re.compile(r"^([A-Za-z_][\w]*)\.([A-Za-z_][\w]*)$")
_DOTTED_EXTENSION = {
    "h", "hpp", "hh", "hxx", "lib", "dll", "htm", "html", "txt", "idl",
    "inc", "def",
}
# ``IXRCollection<In_T, Out_T>::Insert`` prints the parent, including the
# template arguments, and the member.  The stored title may still have the
# HTML escapes (``&lt;``); the page printed the brackets.
_TEMPLATED_MEMBER = re.compile(
    r"^([A-Za-z_][\w]*<[^<>]+>::[A-Za-z_][\w]*)$")
# ``CComPtr::operator !`` and ``wstring::operator+=`` print the class and
# the operator.  ``COleDateTime::operator ==, !=`` prints several; each
# token is one operator, and only a syntax block that declares that token
# is attached.  A conversion operator may contain spaces
# (``operator const wchar_t*``).
_OPERATOR_TITLE = re.compile(
    r"^([A-Za-z_][\w]*)::\s*(operators?)\s*(.+)$", re.I)
_DESTRUCTOR_TITLE = re.compile(
    r"^([A-Za-z_][\w]*)::(~[A-Za-z_][\w]*)$")
# ``COleControl:: OnMnemonic`` prints the parent and the member with a
# space the template inserted.  The identifiers are those two words.
_SPACED_QUALIFIED = re.compile(
    r"^([A-Za-z_][\w]*)::[ \t]+([A-Za-z_][\w]*)$")


def _declared_member(name):
    """The member a qualified title names, or the name itself."""
    text = name or ""
    if "::" in text:
        return text.rsplit("::", 1)[-1]
    if _DOTTED_MEMBER.match(text):
        return text.split(".", 1)[1]
    return text


def operator_token(name):
    """The operator a title prints after ``operator``, or empty.

    Spaces are kept here.  ``entity_id`` strips them so ``operator +=`` and
    ``operator+=`` are one key.  A title that is not an operator is empty.
    """
    text = _html.unescape(name or "")
    match = re.search(r"(?i)\boperators?\s*(.+)$", text)
    if not match or "::" not in text:
        return ""
    return match.group(1).strip()


def operator_title_names(title):
    """``CComPtr::operator !`` and ``CTime::operators <<, >>``.

    A comma list becomes one name per token the title prints.  Nothing is
    added that the title does not print.  The caller still requires a
    syntax block that declares that token.
    """
    text = _html.unescape(_title_core(title))
    match = _OPERATOR_TITLE.match(text)
    if not match:
        return []
    parent, rest = match.group(1), match.group(3).strip()
    if not rest or len(rest) > 60:
        return []
    if "," not in rest:
        return [text]
    names = []
    for part in rest.split(","):
        part = part.strip()
        if not part or len(part) > 12 or re.search(r"\s", part):
            return []
        names.append(f"{parent}::operator {part}")
    return names


def printed_parent(name):
    """The parent a qualified name prints, or empty.

    ``ITimerService::CreateTimer`` and ``MSMQMessage.Priority`` both print
    one.  The spelling is kept (``::`` is not rewritten to a dot, or the
    reverse).  A file name such as ``winbase.h`` is not a parent.
    """
    text = name or ""
    if "::" in text:
        return text.split("::", 1)[0]
    if _DOTTED_MEMBER.match(text) and text.split(".", 1)[1].lower() not in _DOTTED_EXTENSION:
        return text.split(".", 1)[0]
    return ""


def documented_title_names(title):
    """Names a title prints, when the title is itself the list of APIs.

    ``CreateFile`` and ``GPE::AllocSurface`` are one name.
    ``ITimerService::CreateTimer Method`` prints the parent and the member.
    ``abort Method (DOMDocument)`` does too.  ``strcpy, wcscpy`` prints both.
    ``MSMQMessage.Priority`` prints the parent and the member with a dot.
    ``IXRCollection<In_T, Out_T>::Insert`` prints both, template arguments
    included.  ``CComPtr::operator !`` prints the class and the operator.
    ``absoluteChildNumber Method`` does not name a parent, and
    ``IContact Properties`` is not a list of identifiers, so both are empty.
    Nothing is completed or invented.
    """
    single = name_from_title(title)
    if single:
        return [single]
    text = _title_core(title)
    match = _QUALIFIED_KIND.match(text)
    if match:
        return [match.group(1)]
    qualified = interface_member_title(title)
    if qualified:
        return [qualified]
    printed = _html.unescape(text)
    printed_base = re.sub(r"\s*\([^()]*\)\s*$", "", printed)
    templated = _TEMPLATED_MEMBER.match(printed_base)
    if templated:
        return [templated.group(1)]
    operators = operator_title_names(title)
    if operators:
        return operators
    destructor = _DESTRUCTOR_TITLE.match(printed)
    if destructor:
        return [printed]
    spaced = _SPACED_QUALIFIED.match(printed)
    if spaced:
        return [f"{spaced.group(1)}::{spaced.group(2)}"]
    dotted = _DOTTED_MEMBER.match(text)
    if dotted and dotted.group(2).lower() not in _DOTTED_EXTENSION:
        return [text]
    parts = [part.strip() for part in text.split(",")]
    if 2 <= len(parts) <= 4 and all(_IDENT.match(part) for part in parts):
        return parts
    return []


def _syntax_declares_operator(name, text):
    """True when ``text`` declares the operator the title prints.

    ``BOOL operator !( );`` declares ``operator !``.  ``operator !=`` does
    not.  A mention with no semicolon is not a declaration.
    """
    token = operator_token(name)
    body = text or ""
    # Some pages omit the semicolon (``T** operator &( VOID )``).  A list of
    # overloads has no brace.  A block with a brace is a body, not this
    # declaration.
    lines = [line for line in body.splitlines() if line.strip()]
    if not token or "{" in body or len(lines) > 24:
        return False
    if ";" not in body and (len(lines) > 4 or "(" not in body):
        return False
    compact = re.sub(r"\s+", "", token)
    for match in re.finditer(r"(?i)\boperator\s*([^\n;]+)", body):
        found = match.group(1).strip()
        found = re.split(r"\s*\(", found, maxsplit=1)[0].strip()
        if re.sub(r"\s+", "", found) == compact:
            return True
    return False


def syntax_declares_name(name, text):
    """True when ``text`` is a declaration of ``name``, not a mention of it.

    ``recordset.{MoveFirst | MoveNext}`` mentions the name and is not a
    declaration.  ``FILE *stdin;`` and ``HRESULT CreateTimer(...)`` are.
    ``BOOL operator !( );`` declares ``CComPtr::operator !``.
    ``~CBasePropertyPage(void);`` declares that destructor.
    """
    if operator_token(name):
        return _syntax_declares_operator(name, text)
    if "::" in (name or "") and name.rsplit("::", 1)[-1].startswith("~"):
        member = name.rsplit("::", 1)[-1]
        return (";" in (text or "") and re.search(
            r"(?<![A-Za-z0-9_])" + re.escape(member) + r"\s*\(",
            text or "") is not None)
    if not name_in_syntax(name, text):
        return False
    body = (text or "").strip()
    if _is_documented_prototype(body):
        return True
    if re.match(r"(?is)(?:typedef\s+)?(?:struct|enum|union)\b", body):
        return True
    if re.match(r"(?m)\s*#\s*define\b", body):
        return True
    member = _declared_member(name)
    return re.search(
        r"(?i)(?<![A-Za-z0-9_])" + re.escape(member) + r"\s*;",
        body) is not None


def name_in_syntax(name, text):
    """True when ``text`` prints ``name`` (or, for a property, its get/put).

    ``IHTMLElement3::onactivate`` is documented as ``get_onactivate``.
    ``MSMQMessage.Priority`` is documented as ``get_Priority``.  A
    comma-list name has to be that identifier, not a substring of another.
    """
    member = _declared_member(name)
    if not member:
        return False
    qualified = member != (name or "")
    if qualified:
        pattern = (r"(?i)(?<![A-Za-z0-9_])(?:get_|put_)?"
                   + re.escape(member) + r"(?![A-Za-z0-9_])")
    else:
        pattern = (r"(?i)(?<![A-Za-z0-9_])" + re.escape(member)
                   + r"(?![A-Za-z0-9_])")
    return re.search(pattern, text or "") is not None


_KIND_TITLE = re.compile(
    r"(?i)^([A-Za-z_][A-Za-z0-9_]*)\s+"
    r"(interface|dispinterface|structure|function|prototype|"
    r"enumerated\s+type)$")


def _api_shaped(name):
    """True when a kind-suffixed title is an API name, not an English word.

    ``IElementBehaviorSubmit Interface`` and ``HTML_PAINTER_INFO Structure``
    name an API.  ``Message Function``, ``User Interface`` and ``COM
    Interface`` do not: one English word, or all-caps shorter than a type.
    """
    if re.match(r"I[A-Z][A-Za-z0-9_]+$", name):
        return True
    if "_" in name and re.match(r"[A-Z][A-Za-z0-9_]+$", name):
        return True
    if re.fullmatch(r"[A-Z][A-Z0-9]{7,}", name):
        return True
    # ``HTMLInputTextElementEvents`` and ``DWebBrowserEvents2`` have an
    # acronym and then a capital.  ``COM``, ``User`` and ``Message`` do not.
    if (re.match(r"[A-Z]", name) and re.search(r"[a-z]", name)
            and len(re.findall(r"[A-Z]", name)) >= 2 and len(name) >= 6):
        return True
    return False


def kind_title_name(title):
    """``IHTMLTableRowMetrics Interface`` -> ``IHTMLTableRowMetrics``.

    The kind word is part of the title template, not part of the name.
    A title that is not one API-shaped identifier is left alone.
    """
    text = _title_core(title)
    text = re.sub(r"\s*\([^)]*\)\s*$", "", text).strip()
    match = _KIND_TITLE.match(text)
    if not match:
        return None
    name = match.group(1)
    if not _api_shaped(name):
        return None
    return name


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


def oss_statements(fragment):
    """The open-source document, quoted as this reader sees it.

    One note per page.  The text is the article (everything from the first
    heading), not a summary and not a declaration extracted from a sample.
    ``pattern`` is ``page``: the whole article is the statement.
    """
    text = text_of(fragment, keep_newlines=False)
    if not text:
        return []
    return [{"text": text, "pattern": "page", "kind": "oss-statement"}]


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


# Topics that decide what a generated `.def` may contain.  Each key is the
# topic recorded with the sentence; the values are the words that have to be
# in the sentence for that topic to apply.  A sentence is kept verbatim --
# the rule is the document's wording, never a paraphrase of it.
DEF_RULE_TOPICS = (
    ("module-definition-file", ("module-definition", "module definition file",
                                ".def file", "def file syntax")),
    ("exports-section", ("exports section", "exports statement",
                         "exports keyword")),
    ("name-decoration", ("decorated name", "name decoration",
                         "undecorated", "decorating", "decorates")),
    ("dllexport", ("__declspec(dllexport)", "declspec(dllexport)",
                   "dllexport", "dllimport")),
    ("export-ordinal", ("export ordinal", "ordinal value", "by ordinal",
                        "ordinal number")),
    ("extern-c", ('extern "c"',)),
    # the ABI half of the same question: how the call is made, which the
    # user asked for explicitly
    ("calling-convention", ("calling convention", "__stdcall", "__cdecl",
                            "__fastcall", "winapiv")),
)
# A period that ends a sentence is followed by a space; ``.def`` is not.
_DEF_SENTENCE = re.compile(r"(?<=[.:;!?])\s+(?=[A-Z0-9\"(\u00b7])")
# Without a verb the match is a run of headings or a table of contents.
_DEF_RULE_VERB = re.compile(
    r"\b(is|are|was|were|be|been|must|can|cannot|may|might|should|will|"
    r"would|do|does|did|has|have|had|use|uses|used|requires?|required|"
    r"specif(?:y|ies|ied)|causes?|contains?|exports?|prevents?|allows?|"
    r"list(?:s|ed)?|appends?|adds?|returns?|creates?|calls?|needs?|"
    r"support(?:s|ed)?|produces?|takes?|treats?)\b")
# Cheap gate: a page without one of these strings cannot produce a rule, and
# the corpus is 121,000 pages.
_DEF_RULE_TRIGGERS = tuple(sorted(
    {word for _topic, words in () for word in words} |
    {".def", "module-definition", "module definition file", "exports section",
     "exports statement", "exports keyword", "decorated", "decoration",
     "dllexport", "dllimport", "by ordinal", "ordinal value",
     "ordinal number", "export ordinal", 'extern "c"',
     "calling convention", "__stdcall", "__cdecl", "__fastcall",
     "winapiv"}))
# Page furniture that happens to contain a topic word.
_DEF_RULE_NOISE = ("see also", "send feedback", "in this article",
                   "table of contents", "last updated on", "feedback faqs",
                   "copy markdown", "ask learn")


def def_rules(fragment):
    """Sentences stating how an export, a .def file or a decorated name works.

    These pages are the specification for the artefact this corpus exists to
    produce: what a module-definition file may list, whether the name in it
    is decorated, what ``__declspec(dllexport)`` does, when an export is
    reached by ordinal.  The sentence is quoted as printed, with the topic it
    matched; nothing is generalised into a rule the page does not state.

    Sentences are cut on ``. `` (a period *and* a space), not on every
    period, because the subject of these pages is spelled ``.def`` and a
    naive split turns one rule into two halves of nonsense.  Block structure
    is kept, so a heading does not run into the paragraph under it.
    """
    lowered_fragment = fragment.lower()
    if not any(word in lowered_fragment for word in _DEF_RULE_TRIGGERS):
        return []
    out = []
    seen = set()
    for line in text_of(fragment, keep_newlines=True).splitlines():
        line = re.sub(r"[ \t]+", " ", line).strip()
        if not line:
            continue
        for sentence in _DEF_SENTENCE.split(line):
            sentence = sentence.strip()
            lowered = sentence.lower()
            if not (20 <= len(sentence) <= 400):
                continue
            if any(noise in lowered for noise in _DEF_RULE_NOISE):
                continue
            if len(sentence.split()) < 8:
                continue
            if not _DEF_RULE_VERB.search(lowered):
                continue
            topics = [topic for topic, words in DEF_RULE_TOPICS
                      if any(word in lowered for word in words)]
            if not topics:
                continue
            if lowered in seen:
                continue
            seen.add(lowered)
            out.append({"text": sentence, "topics": topics})
    return out


# "Windows CE supports only the Unicode version of this function."  The A
# spelling of that function is not on the device, so a generated header or
# .def must not carry one.  The Win32 reference page for the same name does
# document the ANSI spelling -- that is the desktop, and this sentence is the
# document saying so.
_UNICODE_ONLY = re.compile(
    r"(?i)supports only (?:the )?unicode(?: version| strings)?")
_UNICODE_ONLY_SUBJECT = re.compile(
    r"(?i)\b(windows ce|windows embedded ce|windows mobile|pocket pc|"
    r"handheld pc|ce \.net|\.net)\b")


def unicode_support(fragment):
    """Sentences stating that only the Unicode form of this API exists.

    Returned verbatim, with the subject the sentence names.  The caller is
    expected to use this only on a Windows CE page: a sentence whose subject
    is a desktop Windows version says nothing about the device.
    """
    if "upports only" not in fragment:
        return []
    out = []
    seen = set()
    for line in text_of(fragment, keep_newlines=True).splitlines():
        line = re.sub(r"[ \t]+", " ", line).strip()
        if not line:
            continue
        for sentence in re.split(r"(?<=[.:;!?])\s+(?=[A-Z0-9\"(])", line):
            sentence = sentence.strip()
            if not (20 <= len(sentence) <= 400):
                continue
            if not _UNICODE_ONLY.search(sentence):
                continue
            subject = _UNICODE_ONLY_SUBJECT.search(sentence)
            if sentence.lower() in seen:
                continue
            seen.add(sentence.lower())
            # "...only the Unicode version of this function" is about the
            # API the page documents; "Windows CE supports only Unicode
            # strings" is about the system.  Only the first one says that
            # this name has no ANSI form, so the two are not merged.
            scope = ("this-api"
                     if re.search(r"(?i)version of (?:this|the )"
                                  r"(?: \w+)? ?"
                                  r"(function|structure|macro|message|"
                                  r"method|interface|api)", sentence)
                     or re.search(r"(?i)supports only the unicode version "
                                  r"of [A-Z_][A-Za-z0-9_]*", sentence)
                     else "system")
            out.append({"text": sentence,
                        "subject": subject.group(1) if subject else "",
                        "scope": scope,
                        "pattern": "supports only Unicode"})
    return out


# The CE 1.0 Books Online print the platform difference as one paragraph
# that starts with the label: "<p>Windows CE Notes   Cannot be used with the
# uObjectType flag OBJ_PAL.</p>".  The whole paragraph is the statement, and
# most of it is not caught by the restriction-word reader ("The only
# supported raster operations are SRCCOPY and SRCINVERT", "The file excpt.h
# has to be explicitly included in order to use this function").
_CE_NOTES = re.compile(
    r"(?is)<p>\s*Windows\s+CE\s+Notes\b[:\s]*(.*?)</p>")
# The CHM 3.0 / MSDN reference pages print it as a section label instead:
# ``<P class="label"><B>Windows CE Remarks</B></P>`` followed by the
# paragraphs that state the difference.
_CE_SECTION_LABEL = re.compile(
    r"(?is)<(p|div|h[1-6])\b[^>]*>\s*(?:<[^>]+>\s*)*"
    r"(Windows\s+CE\s+(?:Remarks|Notes))\s*(?:</[^>]+>\s*)*</\1>")
_CE_SECTION_END = re.compile(
    r"(?is)<p\b[^>]*class\s*=\s*[\"\']?(?:label|clsRef|blue)|<h[1-6]\b|"
    r"<p>\s*(?:<[^>]+>\s*)*(?:See Also|Requirements|Return Values?|"
    r"Parameters|Remarks|Syntax)\s*(?:</[^>]+>)*\s*</p>")


def ce_notes(fragment):
    """The page's own ``Windows CE Notes``/``Windows CE Remarks`` block.

    Two shapes: the CE 1.0 Books Online print the label and the text in one
    paragraph; the CHM 3.0 and MSDN reference pages print the label as a
    section and the text in the paragraphs under it.  Both are quoted as
    printed and neither is summarised.
    """
    out = []
    for match in _CE_SECTION_LABEL.finditer(fragment):
        rest = fragment[match.end():match.end() + 4000]
        stop = _CE_SECTION_END.search(rest)
        block = rest[:stop.start()] if stop else rest
        text = re.sub(r"\s+", " ",
                      text_of(block, keep_newlines=False)).strip()
        if len(text) < 3:
            continue
        out.append({"text": text[:1200], "pattern": match.group(2)})
    for match in _CE_NOTES.finditer(fragment):
        text = re.sub(r"\s+", " ",
                      text_of(match.group(1), keep_newlines=False)).strip()
        if len(text) < 3:
            continue
        out.append({"text": text, "pattern": "Windows CE Notes"})
    return out


# "Windows CE does not support the following nIndex values: SM_ARRANGE
# SM_CXMINIMIZED ...".  The names after the colon are a printed list of
# constants that the device does not accept.  A generator that emits a
# header from the Win32 reference would define them all; the CE page says
# which ones are not there.
_UNSUPPORTED_INTRO = re.compile(
    r"(?is)(Windows (?:Embedded )?CE[^.<>]{0,60}?)?\b"
    r"(does not support|do not support|are not supported(?: by)?|"
    r"supports only)\b([^.:<>]{0,60}?)\s*:")
# A constant is an all-caps identifier with an underscore or a digit in it.
# A bare all-caps word (NULL, TRUE, GDI) is not taken: too many of them are
# prose.  Nothing here is renamed, completed or expanded.
_CONSTANT_TOKEN = re.compile(r"^[A-Z][A-Z0-9]*(?:_[A-Z0-9]+)+$")
_TOKEN = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")


def unsupported_constants(fragment):
    """Constant names a page lists after "does not support the following ...".

    Returns one record per list, with the sentence that introduces it and
    the names as printed.  The list ends at the first word that is not a
    constant: these pages print the names as a run of list items, so the
    first ordinary word is the end of the list.
    """
    plain = re.sub(r"\s+", " ", text_of(fragment, keep_newlines=False))
    out = []
    for match in _UNSUPPORTED_INTRO.finditer(plain):
        # the sentence the list hangs off, so that "For Windows CE versions
        # 2.10 and later, SHGetFileInfo does not support ..." counts as a
        # Windows CE statement even though the subject is the function
        begin = plain.rfind(". ", max(0, match.start() - 300), match.start())
        begin = begin + 2 if begin != -1 else max(0, match.start() - 300)
        intro = re.sub(r"\s+", " ", plain[begin:match.end()]).strip()
        if not re.search(r"(?i)windows (?:embedded )?ce", intro):
            continue
        names = []
        for token in _TOKEN.finditer(plain, match.end(),
                                     min(len(plain), match.end() + 1500)):
            if _CONSTANT_TOKEN.match(token.group(0)):
                if token.group(0) not in names:
                    names.append(token.group(0))
                continue
            break
        if len(names) < 2:
            continue
        out.append({"intro": intro[:300], "names": names,
                    "negated": match.group(2).lower() != "supports only"})
    return out

# ---------------------------------------------------------------------------
# pinvoke.net support
# ---------------------------------------------------------------------------
# pinvoke.net is a wiki-style site that documents P/Invoke signatures for
# calling Win32 API from .NET. Pages contain C# code blocks with DllImport
# attributes and constant definitions.
#
# URL pattern: http://www.pinvoke.net/default.aspx/{module}/{function}
# Stored at: corpus/pinvoke/{module}/{function}.html

_PINVOKE_DLL = re.compile(r'DllImport\s*\(\s*"([^"]+)"')
_PINVOKE_CONST = re.compile(
    r'(?:public\s+)?(?:const|static\s+readonly)\s+'
    r'(?:uint|int|ushort|short|byte|long)\s+'
    r'(\w+)\s*=\s*(0x[0-9a-fA-F]+|\d+)'
)
_PINVOKE_DEFINE = re.compile(
    r'#define\s+(\w+)\s+(0x[0-9a-fA-F]+|\d+)'
)


def pinvoke_requirements(fragment):
    """Extract requirements from a pinvoke.net page.
    
    Returns a list of requirement records with field/value pairs:
    - dll: the DLL name from DllImport attribute
    """
    out = []
    text = text_of(fragment, keep_newlines=False)
    
    # Extract DLL name from DllImport
    dll_match = _PINVOKE_DLL.search(text)
    if dll_match:
        dll_name = dll_match.group(1)
        out.append({
            "field": "dll",
            "label": "DLL",
            "value": dll_name,
            "evidence": f'DllImport("{dll_name}")'
        })
    
    return out


def pinvoke_constants(fragment):
    """Extract constants from a pinvoke.net page.
    
    Returns a list of constant records with name/value pairs.
    """
    out = []
    text = text_of(fragment, keep_newlines=False)
    
    # Extract const definitions
    for match in _PINVOKE_CONST.finditer(text):
        name = match.group(1)
        value = match.group(2)
        out.append({
            "name": name,
            "value": value,
            "decimal": "",
            "table": "pinvoke constant",
            "row": f"{name} = {value}",
        })
    
    # Extract #define definitions
    for match in _PINVOKE_DEFINE.finditer(text):
        name = match.group(1)
        value = match.group(2)
        out.append({
            "name": name,
            "value": value,
            "decimal": "",
            "table": "pinvoke define",
            "row": f"#define {name} {value}",
        })
    
    return out


# Map pinvoke.net module names to Windows header files
_PINVOKE_MODULE_TO_HEADER = {
    "kernel32": "Windows.h",
    "user32": "Windows.h",
    "gdi32": "Windows.h",
    "advapi32": "Windows.h",
    "shell32": "Shellapi.h",
    "comctl32": "Commctrl.h",
    "comdlg32": "Commdlg.h",
    "winmm": "Mmsystem.h",
    "wininet": "Wininet.h",
    "ws2_32": "Winsock2.h",
    "ole32": "Objbase.h",
    "oleaut32": "Oleauto.h",
    "crypt32": "Wincrypt.h",
    "secur32": "Security.h",
    "rasapi32": "Ras.h",
    "mpr": "Mpr.h",
    "netapi32": "Lm.h",
    "shlwapi": "Shlwapi.h",
    "urlmon": "Urlmon.h",
    "version": "Winver.h",
    "winspool": "Winspool.h",
    "coredll": "Windows.h",
    "rapi": "Rapi.h",
    # dotnet/pinvoke library projects beyond the classic wiki modules
    "bcrypt": "Bcrypt.h",
    "cabinet": "Fci.h",
    "cfgmgr32": "Cfgmgr32.h",
    "dbghelp": "Dbghelp.h",
    "dwmapi": "Dwmapi.h",
    "fusion": "Fusion.h",
    "hid": "Hidsdi.h",
    "iphlpapi": "Iphlpapi.h",
    "imagehlp": "Imagehlp.h",
    "mscoree": "Mscoree.h",
    "magnification": "Magnification.h",
    "msi": "Msi.h",
    "ncrypt": "Ncrypt.h",
    "ntdll": "Winternl.h",
    "newdev": "Newdev.h",
    "psapi": "Psapi.h",
    "shcore": "Shellscalingapi.h",
    "setupapi": "Setupapi.h",
}


def pinvoke_header_from_module(module_name):
    """Infer header file from pinvoke.net module name."""
    module_lower = module_name.lower()
    return _PINVOKE_MODULE_TO_HEADER.get(module_lower, "Windows.h")
