#!/usr/bin/env python3
"""tools/devsurface/extract.py -- mechanical Development Surface extraction.

Reads the Windows CE documentation already held in this corpus and writes, for
every page,

  * one **page coverage row** (devsurface/data/pages/<book>.tsv), and
  * zero or more **symbol records** (devsurface/data/_work/symbols-<book>.ndjson),

using only what the page text states. Nothing is guessed: a field that the page
does not document is emitted as `null` with `evidence_status: "unknown"` and the
field name is collected in `uncertainty.unknown_fields`.

Design rules (see devsurface/METHODOLOGY.md):
  R1  A value is only ever copied from the document, or produced by a mapping
      table in tools/devsurface/vocab.py.
  R2  The declaration text is stored verbatim (whitespace normalised) and is
      the authoritative artifact; parsed fields are explicitly marked `derived`.
  R3  A symbol record is only created when the page documents a declaration
      (or a labelled symbol table). Pages that look like symbol pages but carry
      no declaration are recorded as coverage gaps instead of being filled in.
  R4  Documentation presence is recorded as documentation, never as runtime
      availability. Version statements are stored as quoted statements plus a
      normalisation result, with `unmapped` kept when the vocabulary does not
      cover the literal.
  R5  ABI fields (calling convention, decoration, ordinal, layout, data model)
      stay `unknown` unless a page states them. Documented macro tokens such as
      WINAPI are recorded as *tokens present in the declaration*, not as an ABI
      conclusion.

Usage:
  python3 tools/devsurface/extract.py --all
  python3 tools/devsurface/extract.py --book mslearn-windows-ce-5.0
  python3 tools/devsurface/extract.py --book chm-windows-ce-3.0 --limit 200

Dependencies: beautifulsoup4 (lxml parser used when available).
"""

from __future__ import annotations

import argparse
import datetime as dt
import hashlib
import json
import os
import re
import sys
import time
from concurrent.futures import ProcessPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import vocab  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
WORK = os.path.join(ROOT, "devsurface", "data", "_work")
PAGES = os.path.join(ROOT, "devsurface", "data", "pages")

try:
    from bs4 import BeautifulSoup
except ImportError:  # pragma: no cover
    print("ERROR: beautifulsoup4 is required (pip install beautifulsoup4 lxml)", file=sys.stderr)
    raise SystemExit(2)

# --------------------------------------------------------------------------
# text / html helpers
# --------------------------------------------------------------------------

WS = re.compile(r"\s+")
SENTENCE = re.compile(r"[^.!?\n]{0,240}?(?:\.[\s$]|$)")


def ws(text: str) -> str:
    return WS.sub(" ", (text or "").replace("\xa0", " ")).strip()


def clip(text: str, limit: int):
    """Return (value, truncated). Bounds record size; the corpus keeps full text."""
    text = text or ""
    if len(text) <= limit:
        return text, False
    return text[:limit].rstrip(), True


def node_text(node) -> str:
    return ws(node.get_text(" ")) if node is not None else ""


DEPRECATION_PATTERNS = [
    r"deprecat\w*",
    r"no longer supported",
    r"has been removed",
    r"is removed\b",
    r"replaced by",
    r"not supported in",
    r"discontinued",
    r"obsolete",
]


def deprecation_sentences(text: str, limit: int = 2):
    """Return sentences that state removal/deprecation, verbatim from the page."""
    found = []
    for match in re.finditer("|".join(DEPRECATION_PATTERNS), text, re.I):
        start = max(0, match.start() - 200)
        segment = text[start:match.end() + 240]
        pieces = SENTENCE.findall(segment) or [segment]
        sentence = None
        for piece in pieces:
            if re.search("|".join(DEPRECATION_PATTERNS), piece, re.I):
                sentence = ws(piece)
                break
        if not sentence:
            sentence = ws(segment)
        sentence, _ = clip(sentence, 320)
        if sentence and sentence not in found:
            found.append(sentence)
        if len(found) >= limit:
            break
    return found


# --------------------------------------------------------------------------
# page loading
# --------------------------------------------------------------------------

REMOVE_SELECTORS = [
    "script", "style", "nav", "header", "footer",
    "[id^=ms--]", "[class*=feedback]", "[class*=additional-resources]",
    "[class*=breadcrumb]", "[class*=affixed-]", "noscript",
]


def load_soup(html: str):
    try:
        return BeautifulSoup(html, "lxml")
    except Exception:
        return BeautifulSoup(html, "html.parser")


def page_shell(html: str, soup, path: str, source_id: str):
    title = ""
    if soup.title and soup.title.string:
        title = ws(soup.title.string)
    title = re.sub(r"\s*\|\s*Microsoft Learn\s*$", "", title)
    url = None
    link = soup.find("link", rel="canonical")
    if link and link.get("href"):
        url = link["href"].strip()
    if not url:
        meta = soup.find("meta", attrs={"property": "og:url"})
        if meta and meta.get("content"):
            url = meta["content"].strip()
    if not url:
        src = vocab.SOURCES.get(source_id, {})
        template = src.get("locator_template", "")
        page_id = os.path.basename(path)[:-5]
        url = template.replace("{page_id}", page_id) if template else None
    updated = ""
    match = re.search(r"Last updated on\s*:?\s*([0-9]{4}-[0-9]{2}-[0-9]{2}|[A-Z][a-z]+day,? [A-Z][a-z]+ \d{1,2}, \d{4})", html)
    if match:
        updated = ws(match.group(1))
    return title, url, updated


def content_root(soup):
    """Pick the article container.

    Learn pages carry more than one `div.content` (layout placeholders are
    empty), so the container with the most text wins instead of the first hit.
    """
    best, best_length = None, -1
    for selector in ("div.content", "main#main", "main", "div#mainBody"):
        for node in soup.select(selector):
            length = len(node.get_text(" ", strip=True))
            if length > best_length:
                best, best_length = node, length
    return best if best is not None else soup


def prune(node):
    for selector in REMOVE_SELECTORS:
        try:
            for junk in node.select(selector):
                junk.decompose()
        except Exception:
            pass
    return node


# --------------------------------------------------------------------------
# declaration extraction
#
# Precision rules (see devsurface/METHODOLOGY.md):
#   * a block is only a *candidate* when it looks like a declaration,
#   * a candidate only becomes the page's declaration when the identifier it
#     declares is the identifier the page title names,
#   * everything else is reported as a coverage gap, never as a record.
# --------------------------------------------------------------------------

SOURCE_KIND_PATTERNS = [
    (r"\bThis\s+macro\b", "macro"),
    (r"\bThis\s+function\b", "function"),
    (r"\bThis\s+callback\s+function\b", "callback"),
    (r"\bThis\s+structure\b", "struct"),
    (r"\bThis\s+union\b", "union"),
    (r"\bThis\s+enumeration\b", "enum"),
    (r"\bThis\s+typedef\b", "type"),
    (r"\bThis\s+constant\b", "constant"),
    (r"\bThis\s+variable\b", "variable"),
    (r"\bThis\s+class\b", "class"),
    (r"\bThis\s+message\b", "constant"),
    (r"\bThis\s+IOCTL\b", "ioctl"),
    (r"\bThis\s+input/output\s+control\b", "ioctl"),
    (r"\bThis\s+I/O\s+control\b", "ioctl"),
    (r"\bThis\s+interface\b", "interface_method"),
    (r"\bis\s+a\s+synthesized\s+structure\b", "struct"),
]

# Control-flow and other statement keywords: never part of a declaration.
STATEMENT_KEYWORDS = re.compile(
    r"\b(return|goto|break|continue|else|case|default|new|delete|switch|while|for|if)\b",
    re.I)

# Calls that only appear in example code.
EXAMPLE_CALLS = re.compile(
    r"\b(printf|sprintf|wsprintf|TRACE|RETAILMSG|DEBUGMSG|OEMWriteDebugString|"
    r"assert|fprintf|MessageBox|MessageBoxW|OutputDebugString)\s*\(",
    re.I)

STATEMENT_SEQUENCE = re.compile(r";\s*[^\s;)\]}]")

# A single bare call line: example code unless the page states what the symbol is.
BARE_CALL_LINE = re.compile(r"^\s*[A-Za-z_]\w*\s*\([^()]*\)\s*;\s*$")
# Pointer-to-member / member access: never part of a declaration.
MEMBER_ACCESS = re.compile(r"->|\b[A-Za-z_]\w*\s*\.\s*[A-Za-z_]\w*\s*\(")
ASSIGNMENT = re.compile(r"(?<![=!<>+\-*/%&|^~])=(?!=)")

DECLARATION_HEAD = re.compile(
    r"^\s*(?:#\s*define\b|typedef\b|extern\b|__declspec|struct\b|union\b|enum\b|class\b|"
    r"virtual\b|const\b|static\b|inline\b|template\b|"
    r"[A-Za-z_]\w*[\s\*&]+[A-Za-z_]|[A-Z_]\w*\s*\()",
    re.I,
)

AGGREGATE = re.compile(r"\b(struct|union|class|enum)\b[^;{}]*\{", re.I)
FUNC_PTR_TYPEDEF = re.compile(r"typedef[\s\S]*?\(\s*\*\s*[A-Za-z_]\w*\s*\)\s*\(")
PROTOTYPE_END = re.compile(r"\)\s*(?:[A-Za-z_]\w*\s*)*;\s*$")

MANAGED_TITLE = re.compile(
    r"\b(Method|Property|Class|Enumeration|Structure|Delegate|Interface|Constructor|Field|Event)"
    r"\s*\(\s*(?:Microsoft|System|Ws|Compact\s*7|[A-Za-z0-9_.]+\.[A-Za-z0-9_.]+)"
    r"|\((?:Microsoft|System|Ws)(?:\.[A-Za-z0-9_]+)*\)\s*$"
    r"|\b(?:Microsoft|System|Ws)\.[A-Za-z0-9_.]+\s*$",
    re.I)


def managed_title(title: str) -> bool:
    """True for .NET / managed-SDK reference pages (outside include/def/lib)."""
    return bool(MANAGED_TITLE.search(title or ""))


def source_kind_label(text: str):
    """Kind stated by the page prose (e.g. "This macro ..."), else None."""
    if not text:
        return None
    for pattern, kind in SOURCE_KIND_PATTERNS:
        if re.search(pattern, text, re.I):
            return kind
    return None


DIAGNOSTIC_TITLE = re.compile(
    r"\b(?:Compiler|Linker|BSCMAKE|NMAKE|MIDL|CV)\s+Error\b"
    r"|\berror\s+[A-Z]{1,3}\d{3,4}\b"
    r"|^\s*(?:C|BC|LNK|BK|MC|RC|CV|MIDL)\d{3,4}\b",
    re.I)

# Markers the documentation prints inside example code to point at the faulty
# (or accepted) line, e.g. `class A { }; class B : public A, public A { }; // error`.
# A block carrying one is example code from a diagnostic topic, not a declaration,
# so it is never turned into a symbol record. The page stays in the coverage TSV.
EXAMPLE_MARKERS = re.compile(r"//\s*(?:error|OK)\b|/\*\s*(?:error|OK)\b", re.I)


def classify_block(text: str, kind_label=None, title_ident=None):
    """Classify a code block. Returns (form, reason); form None means rejected."""
    if not text or not text.strip():
        return None, "empty"
    lines = [line for line in text.splitlines() if line.strip()]
    if len(text) > 2000 or len(lines) > 25:
        return None, "size_out_of_range"
    if EXAMPLE_MARKERS.search(text):
        return None, "example_code_markers"
    if STATEMENT_KEYWORDS.search(text):
        return None, "statement_keyword"
    if AGGREGATE.search(text) and "}" in text:
        # A structure/union/enum definition: member declarations separated by
        # ';' on one line are normal in these topics.
        return "aggregate", "accepted"
    if STATEMENT_SEQUENCE.search(text):
        return None, "statement_sequence"
    if re.match(r"#\s*define\b", text.strip()):
        # A preprocessor definition is never example code, even when its body
        # names a debug-print macro.
        return "preprocessor", "accepted"
    call = EXAMPLE_CALLS.search(text)
    if call:
        called = re.match(r"[A-Za-z_]\w*", call.group(0))
        if not (title_ident and called and called.group(0).lower() == title_ident.lower()):
            return None, "example_call"
    if MEMBER_ACCESS.search(text):
        return None, "member_access_or_arrow"
    if BARE_CALL_LINE.match(text.strip()) and not kind_label:
        return None, "bare_call_line_without_kind_label"
    if not DECLARATION_HEAD.match(lines[0]):
        return None, "first_line_not_a_declaration"
    stripped = text.strip()
    if stripped.startswith("#define") or re.match(r"#\s*define\b", stripped):
        return "preprocessor", "accepted"
    if AGGREGATE.search(text):
        return "aggregate", "accepted"
    if FUNC_PTR_TYPEDEF.search(text):
        return "callback", "accepted"
    if ASSIGNMENT.search(text):
        return None, "assignment_in_block"
    if PROTOTYPE_END.search(text):
        return "prototype", "accepted"
    if kind_label:
        return "labelled_form", "accepted"
    if stripped.endswith(";") and "(" not in text:
        return "variable", "accepted"
    return None, "unrecognised_declaration_form"


COMPARISON_OPERATORS = ("<", ">", "=", "&&", "||", "+", "-", "%")


def parameters_look_documented(params, documented_names, kind_label=None):
    """Reject parameter lists that cannot be parameter lists.

    A parameter is accepted when it is empty/void, variadic, carries a pointer or
    array declarator, has at least two identifiers (type and name), is a single
    upper-case token (a type name), is a name the page documents, or is a
    documented name glued to a leading type token by the source markup.
    """
    for entry in params:
        raw = (entry.get("type_raw") or "").strip()
        if raw in ("", "void", "..."):
            continue
        if any(operator in raw for operator in COMPARISON_OPERATORS):
            return False
        name = (entry.get("name") or "").lower()
        if name and name in documented_names:
            continue
        if "*" in raw or "[" in raw or "(" in raw:
            continue
        identifiers = [m.group(0) for m in IDENT.finditer(raw)]
        if len(identifiers) >= 2:
            continue
        token = identifiers[0].lower() if identifiers else ""
        if token and any(token.endswith(documented) for documented in documented_names):
            continue
        if token and token.isupper():
            continue
        if token and kind_label:
            # The page states what the symbol is; macro topics print their
            # arguments as bare names ("ASSERT (Expression)").
            continue
        return False
    return True


def find_declaration(soup, content, kind_label=None, title_ident=None, documented_names=()):
    """Locate the page's declaration.

    Returns (declaration, origin, parsed_name, status) with status one of
    matched / candidate_mismatch / no_candidate.
    """
    candidates = []
    heading = None
    for h in content.find_all(["h1", "h2", "h3", "h4", "h5", "p", "b", "strong"]):
        if h.get("id") == "syntax" or ws(h.get_text(" ")).lower().rstrip(":") == "syntax":
            heading = h
            break
    if heading is not None:
        pre = heading.find_next("pre")
        if pre is not None:
            candidates.append((node_text(pre), "syntax_section"))
    pre = content.find("pre", class_="syntax")
    if pre is not None:
        candidates.append((node_text(pre), "chm_syntax_pre"))
    for index, pre in enumerate(content.find_all("pre")):
        origin = "first_code_block" if index == 0 else "code_block_%d" % index
        candidates.append((node_text(pre), origin))

    first_rejected = None
    first_mismatch = None
    for text, origin in candidates:
        form, reason = classify_block(text, kind_label, title_ident)
        if form is None:
            if first_rejected is None:
                first_rejected = reason
            continue
        parsed = parse_declaration(text, "")
        name = parsed.get("symbol")
        if parsed.get("parameters") and not parameters_look_documented(
                parsed["parameters"], documented_names, kind_label):
            if first_rejected is None:
                first_rejected = "parameter_list_not_a_parameter_list"
            continue
        if title_ident and name and name.lower() == title_ident.lower():
            return text, origin, name, "matched"
        if title_ident and name and len(title_ident) > len(name) \
                and title_ident.lower().endswith(name.lower()):
            prefix = title_ident[:len(title_ident) - len(name)]
            return_type = ws(parsed.get("return_type") or "")
            if prefix and return_type.lower().endswith(prefix.lower()):
                # e.g. "HANDLE MyFSD _CreateFileW(...)" on the MyFSD_CreateFileW
                # topic: the source splits the documented name across the type
                # and the declarator. The split point is not recoverable, so the
                # return type is left unknown.
                parsed["parse_notes"].append(
                    "declaration splits the documented name across tokens;"
                    " symbol taken from the page title, return type unknown")
                return text, origin + "+split_identifier", title_ident, "matched_glued"
        if title_ident and name and name.lower().endswith(title_ident.lower()) \
                and len(name) > len(title_ident):
            # The source markup glued the declaration's leading tokens together
            # (e.g. "DWORDGetTickCount(void);"). The page title still names the
            # symbol; the split point inside the glued run is NOT recoverable
            # and is therefore left unknown.
            return text, origin + "+glued_identifier", title_ident, "matched_glued"
        if title_ident and name and name.lower() != title_ident.lower():
            if first_mismatch is None:
                first_mismatch = (name, origin)
            continue
        if title_ident is None:
            return text, origin, name, "matched"
    if first_mismatch is not None:
        return None, "none", first_mismatch[0], "candidate_mismatch:%s" % first_mismatch[0]
    return None, "none", None, first_rejected or "no_candidate"


# --------------------------------------------------------------------------
# C declaration parsing (mechanical only)
# --------------------------------------------------------------------------

CC_TOKENS = ["WINAPI", "CALLBACK", "APIENTRY", "PASCAL", "FAR PASCAL",
             "__stdcall", "__cdecl", "__fastcall", "STDMETHODCALLTYPE",
             "STDAPICALLTYPE", "WINGDIAPI", "NTAPI"]

EXPORT_TOKENS = ["__declspec(dllexport)", "dllexport", "DLLEXPORT"]

C_KEYWORDS = {
    "void", "char", "short", "int", "long", "float", "double", "signed",
    "unsigned", "const", "volatile", "static", "extern", "register", "auto",
    "struct", "union", "enum", "typedef", "return", "sizeof", "inline",
    "virtual", "class", "public", "private", "protected", "operator",
    "bool", "wchar_t", "int8_t", "int16_t", "int32_t", "int64_t",
}
IDENT = re.compile(r"[A-Za-z_]\w*")
NUMERIC_LITERAL = re.compile(r"^[-(+]?(?:0[xX][0-9A-Fa-f]+|\d+)[uUlLfF]*$")
STRING_LITERAL = re.compile(r'^[LuU]?"')


def split_top_level(text: str, separators=","):
    parts, depth, current, quote = [], 0, [], None
    index = 0
    while index < len(text):
        char = text[index]
        if quote:
            current.append(char)
            if char == quote and text[index - 1] != "\\":
                quote = None
            index += 1
            continue
        if char in "\"'":
            quote = char
            current.append(char)
        elif char in "([{":
            depth += 1
            current.append(char)
        elif char in ")]}":
            depth -= 1
            current.append(char)
        elif char in separators and depth == 0:
            parts.append("".join(current))
            current = []
        else:
            current.append(char)
        index += 1
    parts.append("".join(current))
    return [part.strip() for part in parts if part.strip() != ""]


def find_param_list_end(text: str, start: int):
    depth = 0
    for index in range(start, len(text)):
        if text[index] == "(":
            depth += 1
        elif text[index] == ")":
            depth -= 1
            if depth == 0:
                return index
    return -1


def top_level_declarators(text: str):
    """[(identifier, open_paren_index, close_paren_index, name_start)] at depth 0."""
    out, depth = [], 0
    for index, char in enumerate(text):
        if char == "(":
            if depth == 0:
                head = text[:index]
                match = re.search(r"([A-Za-z_]\w*)\s*$", head)
                if match:
                    close = find_param_list_end(text, index)
                    if close > 0:
                        out.append((match.group(1), index, close, match.start()))
            depth += 1
        elif char in "[{":
            depth += 1
        elif char in ")]}":
            depth -= 1
    return out


def parse_parameters(param_text: str):
    params, notes, tags = [], [], []
    text = ws(param_text)
    if text in ("", "void"):
        if text == "void":
            tags.append("void_parameter_list")
        else:
            notes.append("empty_parameter_list")
        return params, notes, tags
    for position, raw in enumerate(split_top_level(text), start=1):
        raw_ws = ws(raw)
        entry = {
            "position": position,
            "name": None,
            "type": raw_ws,
            "type_raw": raw_ws,
            "direction": None,
            "description": None,
            "documented_values": [],
            "evidence_status": "derived",
        }
        if raw_ws.startswith("..."):
            entry["type"] = "..."
            tags.append("variadic")
            params.append(entry)
            continue
        pointer = re.search(r"\(\s*\*+\s*([A-Za-z_]\w*)\s*\)", raw_ws) or \
            re.search(r"\(\s*\^+\s*([A-Za-z_]\w*)\s*\)", raw_ws)
        if pointer:
            entry["name"] = pointer.group(1)
            entry["type"] = ws(raw_ws[:pointer.start(1)] + "*" + re.sub(r"^[^\s]*", "", ws(raw_ws[pointer.end(1):])))
            entry["type_raw"] = raw_ws
        else:
            identifiers = [m for m in IDENT.finditer(raw_ws) if m.group(0) not in C_KEYWORDS]
            if len(identifiers) >= 2:
                name = identifiers[-1]
                entry["name"] = name.group(0)
                entry["type"] = ws(raw_ws[:name.start()] + raw_ws[name.end():])
            elif len(identifiers) == 1:
                notes.append("unnamed_parameter:%d" % position)
                tags.append("unnamed_parameters")
        params.append(entry)
    return params, notes, tags


def parse_aggregate_members(body: str):
    """Members of a struct/union/enum body, mechanically split on ';'."""
    members = []
    for chunk in split_top_level(body, ";"):
        chunk = ws(chunk)
        if not chunk:
            continue
        if chunk.startswith("#") or chunk in ("{", "}"):
            continue
        bitfield = None
        bit = re.search(r":\s*([^:]+)$", chunk)
        if bit and "::" not in bit.group(1):
            bitfield = ws(bit.group(1))
            chunk = chunk[:bit.start()].strip()
        members.append({"text_raw": chunk, "bitfield_width_raw": bitfield})
    return members


def parse_declaration(declaration: str, title_symbol: str):
    """Mechanically parse a documented C/C++ declaration. Never guesses names."""
    text = (declaration or "").strip()
    out = {
        "symbol": None,
        "kind": "unknown",
        "return_type": None,
        "parameters": [],
        "members": [],
        "enumerators": [],
        "derived_tags": [],
        "parse_notes": [],
        "parse_status": "unsupported",
        "calling_convention_tokens": [],
        "export_tokens": [],
        "packing_pragma": None,
    }
    for token in CC_TOKENS:
        if re.search(r"\b%s\b" % re.escape(token), text, re.I):
            out["calling_convention_tokens"].append(token)
    for token in EXPORT_TOKENS:
        if token in text:
            out["export_tokens"].append(token)
    pack = re.search(r"#\s*pragma\s+pack\s*\(([^)]*)\)", text)
    if pack:
        out["packing_pragma"] = ws(pack.group(0))

    macro = re.match(r"#\s*define\s+([A-Za-z_]\w*)\s*(.*)$", text, re.S)
    if macro:
        name, rest = macro.group(1), macro.group(2)
        rest_ws = ws(rest)
        out["symbol"] = name
        out["kind"] = "macro"
        out["parse_status"] = "parsed"
        if rest.startswith("("):
            out["derived_tags"].append("function_like_macro")
        else:
            if NUMERIC_LITERAL.match(rest_ws):
                out["derived_tags"].append("numeric_literal_value")
            elif STRING_LITERAL.match(rest_ws):
                out["derived_tags"].append("string_literal_value")
        out["macro_value_raw"] = clip(rest_ws, 400)[0]
        out["macro_form"] = "function_like" if rest.startswith("(") else "object_like"
        return out

    aggregate = re.search(r"\b(struct|union|class)\s+([A-Za-z_]\w*)?\s*\{", text)
    enum = re.search(r"\benum\s+([A-Za-z_]\w*)?\s*\{", text)
    if enum:
        out["kind"] = "enum"
        out["parse_status"] = "parsed"
        body_start = text.index("{", enum.end() - 1)
        body_end = text.rfind("}")
        body = text[body_start + 1:body_end] if body_end > body_start else ""
        for entry in split_top_level(body, ","):
            entry_ws = ws(entry)
            if not entry_ws:
                continue
            match = re.match(r"([A-Za-z_]\w*)\s*(?:=\s*(.*))?$", entry_ws)
            out["enumerators"].append({
                "name": match.group(1) if match else entry_ws,
                "value_raw": ws(match.group(2)) if match and match.group(2) else None,
            })
        alias = re.search(r"\}\s*([A-Za-z_]\w*)\s*;", text)
        out["symbol"] = (alias.group(1) if alias else (enum.group(1) or None))
        out["tag_name"] = enum.group(1)
        return out
    if aggregate:
        out["kind"] = aggregate.group(1)
        out["tag_name"] = aggregate.group(2)
        out["parse_status"] = "parsed"
        body_start = text.index("{", aggregate.end() - 1)
        body_end = text.rfind("}")
        body = text[body_start + 1:body_end] if body_end > body_start else ""
        out["members"] = parse_aggregate_members(body)
        alias = re.search(r"\}\s*([A-Za-z_]\w*)\s*;", text)
        out["symbol"] = alias.group(1) if alias else aggregate.group(2)
        return out

    typedef_ptr = re.search(r"typedef\b([\s\S]*?)\(\s*\*\s*([A-Za-z_]\w*)\s*\)\s*\(([\s\S]*?)\)\s*;", text)
    if typedef_ptr:
        out["kind"] = "callback"
        out["symbol"] = typedef_ptr.group(2)
        out["return_type"] = ws(typedef_ptr.group(1))
        params, notes, tags = parse_parameters(typedef_ptr.group(3))
        out["parameters"] = params
        out["parse_notes"] += notes
        out["derived_tags"] += tags
        out["parse_status"] = "parsed"
        return out

    declarators = top_level_declarators(text)
    if declarators:
        # The parameter list of the outermost declarator that ends the statement.
        best = None
        for entry in declarators:
            tail = text[entry[2] + 1:].strip().rstrip(";").strip()
            tail = re.sub(r"\b(const|noexcept|override|=0)\b", "", tail).strip()
            if not tail:
                best = entry
        if best is None:
            best = declarators[-1]
        name, open_index, close_index, name_start = best
        out["symbol"] = name
        out["kind"] = "function"
        ret = ws(text[:name_start])
        if ret.lower().startswith("typedef "):
            out["parse_notes"].append("typedef_function_declarator")
            ret = ret[8:].strip()
        out["return_type"] = ret or None
        params, notes, tags = parse_parameters(text[open_index + 1:close_index])
        out["parameters"] = params
        out["parse_notes"] += notes
        out["derived_tags"] += tags
        out["parse_status"] = "parsed"
        return out

    if re.fullmatch(r"typedef[\s\S]*;", text):
        out["kind"] = "type"
        match = re.search(r"([A-Za-z_]\w*)\s*;$", text)
        out["symbol"] = match.group(1) if match else None
        out["parse_status"] = "parsed" if out["symbol"] else "partial"
        return out

    if text.strip().endswith(";") and "(" not in text:
        out["kind"] = "variable"
        identifiers = [m for m in IDENT.finditer(text) if m.group(0) not in C_KEYWORDS]
        if identifiers:
            out["symbol"] = identifiers[-1].group(0)
            out["return_type"] = ws(text[:identifiers[-1].start()])
            out["parse_status"] = "parsed"
        else:
            out["parse_status"] = "partial"
        return out

    out["parse_notes"].append("declaration_form_not_recognised")
    return out


# --------------------------------------------------------------------------
# requirements section
# --------------------------------------------------------------------------

REQ_LABEL_RE = re.compile(r"^\s*([A-Za-z][A-Za-z /()]{1,28}?)\s*:\s*(.*)$")
VERSION_ROW_LABEL = re.compile(
    r"^(?:windows|microsoft|pocket|smartphone|handheld|palm|platform)", re.I)


def statement_entry(field, label_raw, value_raw):
    value = ws(value_raw)
    entry = {
        "field": field,
        "label_raw": ws(label_raw),
        "value_raw": value,
        "normalized": vocab.normalize_version_statement(value),
    }
    if field in ("header", "include", "library", "module", "namespace", "assembly"):
        cleaned = [ws(part).rstrip(".") for part in re.split(r"[,;]", value) if ws(part)]
        if cleaned and cleaned[0].lower() in ABSENT_VALUES:
            # The topic states that there is none; that is a documented value.
            entry["stated_absent"] = True
            cleaned = []
        entry["values"] = cleaned
        if cleaned:
            entry["value_normalized"] = cleaned[0]
    return entry


ABSENT_VALUES = {"none", "n/a", "na", "-", "not applicable", "no"}


def node_segments(node):
    """Split one node into <br>-separated segments (Learn prints each
    requirement label on its own line inside a single <p>)."""
    parts = re.split(r"(?i)<br\s*/?>", str(node))
    out = []
    for part in parts:
        text = ws(re.sub(r"<[^>]+>", " ", part))
        if text:
            out.append(text)
    return out


def parse_requirements_table(table):
    rows = table.find_all("tr")
    if not rows:
        return []
    header_cells = [ws(cell.get_text(" ")) for cell in rows[0].find_all(["th", "td"])]
    out = []
    for row in rows[1:]:
        cells = [ws(cell.get_text(" ")) for cell in row.find_all(["th", "td"])]
        if not cells:
            continue
        if header_cells and len(cells) == len(header_cells) and any(
                re.search(r"run|version|defined|declared|include|link", label, re.I) for label in header_cells):
            for label, value in zip(header_cells, cells):
                field = vocab.REQUIREMENT_LABELS.get(ws(label).lower())
                if field and ws(value):
                    out.append(statement_entry(field, label, value))
        elif len(cells) >= 2:
            label, value = cells[0], cells[1]
            if VERSION_ROW_LABEL.match(label) and re.search(r"\d\.\d|CE|Mobile|PC", value, re.I):
                out.append(statement_entry("os_versions", label, value))
            else:
                field = vocab.REQUIREMENT_LABELS.get(label.lower().rstrip(":"))
                if field:
                    out.append(statement_entry(field, label, value))
    return out


def parse_requirements_lines(block_text):
    out = []
    for line in re.split(r"(?<=[.;])\s{1,3}(?=[A-Z][A-Za-z /()]{1,28}:)|\\n", block_text):
        for piece in line.split("\n"):
            match = REQ_LABEL_RE.match(piece)
            if not match:
                continue
            label, value = match.group(1), match.group(2)
            field = vocab.REQUIREMENT_LABELS.get(ws(label).lower())
            if field and ws(value):
                out.append(statement_entry(field, label, value))
    return out


def extract_requirements(soup, content, source_id):
    found, statements, raw_parts = False, [], []
    node = content.find(id="requirements")
    if node is None:
        for candidate in content.find_all(["h2", "h3", "h4", "p", "b", "strong"]):
            if ws(candidate.get_text(" ")).lower().rstrip(":") == "requirements":
                node = candidate
                break
    if node is not None:
        level = int(node.name[1]) if node.name and node.name[:1] == "h" and node.name[1:].isdigit() else 4
        for sibling in node.next_siblings:
            name = getattr(sibling, "name", None)
            if name in ("h1", "h2", "h3", "h4"):
                sibling_level = int(name[1])
                if sibling_level <= level:
                    break
            if name is None:
                text = ws(str(sibling))
                if text:
                    raw_parts.append(text)
                    statements.extend(parse_requirements_lines(text))
                continue
            if name == "table":
                raw_parts.append(node_text(sibling))
                statements.extend(parse_requirements_table(sibling))
            elif name in ("p", "ul", "ol", "div", "dl", "blockquote"):
                text = node_text(sibling)
                raw_parts.append(text)
                for segment in node_segments(sibling):
                    statements.extend(parse_requirements_lines(segment))
                for table in sibling.find_all("table"):
                    statements.extend(parse_requirements_table(table))
        found = bool(statements)

    if not found:
        # CHM Windows CE 3.0 style: a dtTABLE whose header row labels the fields.
        for table in content.find_all("table"):
            header_cells = [ws(c.get_text(" ")) for c in table.find_all("th")]
            if header_cells and sum(
                    1 for label in header_cells
                    if label.lower() in ("runs on", "runs on (os)", "versions", "defined in",
                                         "declared in", "include", "link to")) >= 2:
                statements.extend(parse_requirements_table(table))
                raw_parts.append(node_text(table))
                found = True
                break

    result = {
        "found": found,
        "statements": statements,
        "raw_block": clip(ws(" ".join(raw_parts)), 600)[0],
        "header": None,
        "include": None,
        "libraries": [],
        "modules": [],
        "namespaces": [],
        "assemblies": [],
    }

    def dedupe(entries):
        seen, out = set(), []
        for entry in entries:
            key = (entry["field"], entry["value_raw"])
            if key not in seen:
                seen.add(key)
                out.append(entry)
        return out

    statements = dedupe(statements)
    result["statements"] = statements
    for entry in statements:
        if entry["field"] == "header" and result["header"] is None:
            result["header"] = entry
        elif entry["field"] == "include" and result["include"] is None:
            result["include"] = entry
        elif entry["field"] == "library":
            result["libraries"].append(entry)
        elif entry["field"] == "module":
            result["modules"].append(entry)
        elif entry["field"] == "namespace":
            result["namespaces"].append(entry)
        elif entry["field"] == "assembly":
            result["assemblies"].append(entry)
    return result


# --------------------------------------------------------------------------
# parameters section
# --------------------------------------------------------------------------

PARAM_DIRECTION = re.compile(r"^\[\s*(in|out|in\s*,\s*out|out\s*,\s*in|optional|retval|in,\s*optional)\s*\]", re.I)


def extract_documented_parameters(content):
    """name -> {direction, description, values} as written in the page."""
    documented = {}

    def record(name, description, values):
        name = ws(name).strip("*&^ ")
        if not name or not re.match(r"^[A-Za-z_]\w*$", name):
            return
        direction = None
        match = PARAM_DIRECTION.match(description or "")
        if match:
            direction = ws(match.group(1)).lower().replace(",", ", ")
            description = ws(PARAM_DIRECTION.sub("", description))
        entry = documented.setdefault(name.lower(), {
            "name": name, "direction": None, "description": None, "documented_values": [],
        })
        if entry["direction"] is None and direction:
            entry["direction"] = direction
        if entry["description"] is None and description:
            entry["description"] = clip(ws(description), 700)[0]
        for token, value_description in values:
            item = {"token": token, "description": clip(ws(value_description), 300)[0]}
            if item not in entry["documented_values"]:
                entry["documented_values"].append(item)

    # CHM definition lists: only those under a "Parameters" label
    parameter_dls = []
    for node in content.find_all(["p", "b", "strong", "div"]):
        if ws(node.get_text(" ")).lower().rstrip(":") in ("parameters", "parameter"):
            for sibling in node.next_siblings:
                name = getattr(sibling, "name", None)
                if name == "dl":
                    parameter_dls.append(sibling)
                    break
                if name in ("p", "div") and ws(sibling.get_text(" ")).lower().startswith(("parameter", "return", "remarks", "see also")):
                    break
    if not parameter_dls:
        for node in content.find_all(["p", "b", "strong"]):
            if "parameters" in ws(node.get_text(" ")).lower():
                for sibling in node.next_siblings:
                    if getattr(sibling, "name", None) == "dl":
                        parameter_dls.append(sibling)
                        break
    for dl in parameter_dls:
        terms = dl.find_all(["dt", "dd"])
        current = None
        for term in terms:
            if term.name == "dt":
                current = node_text(term)
            elif current is not None:
                values = []
                for table in term.find_all("table"):
                    rows = table.find_all("tr")[1:]
                    for row in rows:
                        cells = [ws(c.get_text(" ")) for c in row.find_all(["td", "th"])]
                        if len(cells) >= 2 and cells[0]:
                            values.append((cells[0], cells[1]))
                record(current, node_text(term), values)
                current = None
    # Learn list items
    heading = content.find(id="parameters")
    if heading is None:
        for candidate in content.find_all(["h2", "h3", "h4", "p"]):
            if ws(candidate.get_text(" ")).lower().rstrip(":") == "parameters":
                heading = candidate
                break
    if heading is not None:
        for sibling in heading.next_siblings:
            name = getattr(sibling, "name", None)
            if name in ("h1", "h2", "h3", "h4"):
                break
            if name not in ("ul", "ol", "div", "dl"):
                continue
            for item in sibling.find_all("li"):
                text = node_text(item)
                if not text:
                    continue
                match = re.match(r"^([A-Za-z_]\w*(?:\s*\|\s*[A-Za-z_]\w*)*)\s*(.*)$", text)
                if not match:
                    continue
                values = []
                for table in item.find_all("table"):
                    for row in table.find_all("tr")[1:]:
                        cells = [ws(c.get_text(" ")) for c in row.find_all(["td", "th"])]
                        if len(cells) >= 2 and cells[0]:
                            values.append((cells[0], cells[1]))
                record(match.group(1).split("|")[0], match.group(2), values)
            if name in ("ul", "ol", "dl"):
                break
    return documented


# --------------------------------------------------------------------------
# record construction
# --------------------------------------------------------------------------

TITLE_IDENT = re.compile(r"^([A-Za-z_]\w*(?:::[A-Za-z_]\w*)?)\s*(?:\(.*\))?$")

EMPTY_PARSE = {
    "symbol": None,
    "kind": "unknown",
    "return_type": None,
    "parameters": [],
    "members": [],
    "enumerators": [],
    "derived_tags": [],
    "parse_notes": [],
    "parse_status": "no_declaration_documented",
    "calling_convention_tokens": [],
    "export_tokens": [],
    "packing_pragma": None,
}
DEPRECATED_TITLE = re.compile(r"\bdeprecat|not supported", re.I)


def title_symbol(title: str):
    base = re.sub(r"\s*\(([^()]*(?:Windows|CE|Compact|Mobile|\.NET|System|Microsoft)[^()]*)\)\s*$", "", title or "")
    base = base.strip()
    match = re.match(r"^([A-Za-z_]\w*)::([A-Za-z_]\w*)$", base)
    if match:
        # Interface::Member topic: the symbol is the member, the scope is the
        # interface the page names.
        return match.group(2), match.group(1)
    match = TITLE_IDENT.match(base)
    if match:
        return base, None
    return None, None


def normalize_kind(kind, scope, symbol):
    """Scope-less 'interface_method' is an interface, not a member topic."""
    if kind == "interface_method" and not scope and "::" not in (symbol or ""):
        return "interface"
    return kind


DECLARATION_SECTION_ORIGINS = ("syntax_section", "chm_syntax_pre")


def documentation_role(origin, title_ident, declaration):
    """How the page presents the block the declaration was read from.

    Only the page's own structure decides this: a dedicated Syntax/declaration
    section is a declaration section, an unlabelled code block on a topic whose
    title *is* the symbol is that symbol's documentation, and an unlabelled code
    block on any other topic is example code.
    """
    if not declaration:
        return "declaration_not_documented"
    base = (origin or "").split("+")[0]
    if base in DECLARATION_SECTION_ORIGINS:
        return "declaration_section"
    if title_ident:
        return "unlabelled_block_symbol_topic"
    return "example_code_fragment"


def symbol_id(source_id, page_id, symbol, declaration):
    key = "%s|%s|%s|%s" % (source_id, page_id, symbol, (declaration or "")[:400])
    return "sym-" + hashlib.sha1(key.encode("utf-8")).hexdigest()[:16]


def build_symbol_record(*, source_id, page_id, path, title, source_url, updated,
                        declaration, declaration_origin, parsed, requirements,
                        documented_params, deprecations, scope, page_kind_label,
                        documentation_role_value, extracted_on, corpus_revision):
    symbol = parsed["symbol"]
    kind = parsed["kind"]
    unknown_fields = []
    if scope:
        kind = "interface_method"

    params = []
    for entry in parsed["parameters"]:
        item = dict(entry)
        item["evidence_status"] = "derived"
        doc = documented_params.get((item.get("name") or "").lower())
        if doc:
            item["direction"] = doc["direction"]
            item["description"] = doc["description"]
            item["documented_values"] = doc["documented_values"]
            item["evidence_status"] = "derived+documented" if not doc["documented_values"] else "documented"
        params.append(item)
    for key, doc in documented_params.items():
        if not any((p.get("name") or "").lower() == key for p in params):
            params.append({
                "position": None,
                "name": doc["name"],
                "type": None,
                "type_raw": None,
                "direction": doc["direction"],
                "description": doc["description"],
                "documented_values": doc["documented_values"],
                "evidence_status": "documented",
                "declaration_match": False,
            })

    header_entry = requirements["header"]
    include_entry = requirements["include"]
    libraries = requirements["libraries"]
    modules = requirements["modules"]

    if not header_entry:
        unknown_fields.append("header")
    if not libraries and not any(entry.get("stated_absent") for entry in requirements["statements"]
                                 if entry["field"] == "library"):
        unknown_fields.append("library")
    if not modules:
        unknown_fields.append("module")
    if not parsed["calling_convention_tokens"]:
        unknown_fields.append("calling_convention")
    unknown_fields += ["export.name", "export.ordinal", "export.decorated_name",
                       "abi.architecture", "abi.data_model"]

    statements = []
    for entry in requirements["statements"]:
        statements.append({
            "field": entry["field"],
            "label_raw": entry["label_raw"],
            "value_raw": entry["value_raw"],
            "normalized": entry["normalized"],
            "derived": True,
        })

    if declaration is None:
        unknown_fields.append("declaration")
    record = {
        "schema_version": vocab.SCHEMA_VERSION,
        "id": symbol_id(source_id, page_id, symbol, declaration),
        "symbol": symbol,
        "kind": kind,
        "kind_evidence": {
            "basis": parsed.get("kind_basis", "declaration" if parsed["parse_status"] == "parsed" else "unknown"),
            "detail": "declared_form:%s" % parsed.get("declared_form_kind", parsed["kind"]),
            "source_label": page_kind_label,
        },
        "scope": scope,
        "declaration": declaration,
        "declaration_origin": declaration_origin,
        "documentation_role": documentation_role_value,
        "declaration_glued_identifier_raw": parsed.get("glued_identifier_raw"),
        "declaration_language": "c",
        "return_type": parsed["return_type"],
        "macro_form": parsed.get("macro_form"),
        "macro_value_raw": parsed.get("macro_value_raw"),
        "tag_name": parsed.get("tag_name"),
        "parameters": params,
        "members": parsed["members"],
        "enumerators": parsed["enumerators"],
        "parse": {
            "model": "c_declarator_v1",
            "status": parsed["parse_status"],
            "notes": parsed["parse_notes"],
            "derived_fields": ["kind", "return_type", "parameters", "members", "enumerators", "derived_tags"],
        },
        "declaration_calling_convention_tokens": parsed["calling_convention_tokens"],
        "documented_export_tokens": parsed["export_tokens"],
        "packing_pragma_raw": parsed["packing_pragma"],
        "derived_tags": parsed["derived_tags"],
        "header": None if not header_entry else {
            "value": header_entry["values"][0] if header_entry.get("values") else header_entry["value_raw"],
            "label_raw": header_entry["label_raw"],
            "value_raw": header_entry["value_raw"],
            "evidence_status": "documented",
        },
        "include": None if not include_entry else {
            "value": include_entry["value_raw"],
            "label_raw": include_entry["label_raw"],
            "evidence_status": "documented",
        },
        "libraries": [{
            "value": entry["values"][0] if entry.get("values") else None,
            "values": entry.get("values", []),
            "label_raw": entry["label_raw"],
            "value_raw": entry["value_raw"],
            "stated_absent": bool(entry.get("stated_absent")),
            "evidence_status": "documented",
        } for entry in libraries],
        "module": None,
        "export": {"name": None, "ordinal": None, "decorated_name": None,
                   "evidence_status": "unknown"},
        "calling_convention": {"value": None, "evidence_status": "unknown"},
        "abi": {
            "architecture": [],
            "data_model": None,
            "structure_layout": None,
            "packing": None,
            "name_decoration": None,
            "evidence_status": "unknown",
        },
        "version_availability": {
            "statements": statements,
            "status": "documented_statement" if statements else "unknown",
        },
        "deprecation_statements": deprecations,
        "documented_in_books": [source_id],
        "source": {
            "source_id": source_id,
            "book_path": vocab.SOURCES[source_id]["book_path"],
            "page_path": os.path.relpath(path, ROOT),
            "page_id": page_id,
            "page_title": title,
            "source_url": source_url,
            "document_last_updated": updated or None,
        },
        "evidence": [{
            "source_id": source_id,
            "page_path": os.path.relpath(path, ROOT),
            "locator": "requirements+declaration",
            "detail": "declaration, requirements block, parameter list read mechanically from the page",
        }],
        "uncertainty": {
            "unknown_fields": sorted(set(unknown_fields)),
            "notes": parsed["parse_notes"],
            "declaration_parse_is_mechanical": True,
        },
        "extraction": {
            "tool": "tools/devsurface/extract.py",
            "tool_version": vocab.TOOL_VERSION,
            "method": "mechanical_document_extraction",
            "extracted_on": extracted_on,
            "corpus_revision": corpus_revision,
            "verbatim_declaration": True,
        },
    }
    return record


# --------------------------------------------------------------------------
# per-page driver
# --------------------------------------------------------------------------

def classify_page(title, requirements, declaration, symbol):
    if declaration and symbol:
        return "symbol_page"
    if managed_title(title):
        return "out_of_scope_managed_surface"
    if DIAGNOSTIC_TITLE.search(title or ""):
        return "example_code_page"
    if DEPRECATED_TITLE.search(title or ""):
        return "deprecation_notice"
    ident, _ = title_symbol(title)
    if ident and not requirements["found"]:
        return "identifier_title_no_requirements"
    if ident:
        return "identifier_title_no_declaration"
    return "concept_or_overview"


def process_page(args):
    (path, source_id, extracted_on, corpus_revision) = args
    page_id = os.path.basename(path)[:-5]
    try:
        with open(path, encoding="utf-8", errors="replace") as handle:
            html = handle.read()
    except OSError as error:
        return {"page": None, "records": [], "error": "%s: %s" % (path, error)}

    soup = load_soup(html)
    title, source_url, updated = page_shell(html, soup, path, source_id)
    content = prune(content_root(soup))
    text = node_text(content)[:60000]

    requirements = extract_requirements(soup, content, source_id)
    deprecations = deprecation_sentences(text)
    ident, scope = title_symbol(title)
    managed = managed_title(title) or bool(
        requirements["namespaces"] or requirements["assemblies"])
    kind_label = source_kind_label(text)

    documented_params = extract_documented_parameters(content)
    documented_names = {name for name in documented_params}

    declaration, origin, decl_name, decl_status = None, "none", None, "not_attempted"
    if not managed:
        declaration, origin, decl_name, decl_status = find_declaration(
            soup, content, kind_label, ident, documented_names)
    parsed = None
    if declaration:
        parsed = parse_declaration(declaration, "")
        if decl_status == "matched_glued":
            parsed["glued_identifier_raw"] = parsed["symbol"]
            parsed["symbol"] = ident
            parsed["return_type"] = None
            parsed["parse_status"] = "partial"
            if "+split_identifier" in (origin or ""):
                parsed["parse_notes"].append(
                    "declaration_splits_the_documented_name_across_tokens;"
                    " symbol taken from the page title, split point unknown")
            else:
                parsed["parse_notes"].append(
                    "declaration_identifier_is_glued_to_preceding_tokens_in_source_markup;"
                    " symbol taken from the page title, split point unknown")
            if not any("taken from the page title" in note for note in parsed["parse_notes"]):
                parsed["parse_notes"].append("symbol taken from the page title")
        if kind_label and parsed["kind"] != kind_label and parsed["kind"] in (
                "unknown", "function", "variable", "type"):
            parsed["parse_notes"].append("source_states_kind:%s" % kind_label)
            parsed["declared_form_kind"] = parsed["kind"]
            parsed["kind"] = kind_label
            parsed["kind_basis"] = "source_label"
        if parsed.get("kind") == "interface_method" and not scope and "::" not in (parsed.get("symbol") or ""):
            # The prose says "This interface ..." and the page is not a member
            # topic: record an interface, not a method.
            parsed["kind"] = "interface"
            parsed["declared_form_kind"] = "interface_method"
            parsed["kind_basis"] = "source_label"
            parsed["parse_notes"].append("source_states_kind:interface")

    records = []
    if managed:
        page_class = "out_of_scope_managed_surface"
    elif DIAGNOSTIC_TITLE.search(title or ""):
        # Diagnostic topics ("Compiler Error C2500", "BSCMAKE Error BK1500")
        # print example code that triggers the message, not a declaration of a
        # development-surface symbol. Nothing is extracted from them; the page
        # stays catalogued so the decision is visible.
        page_class = "example_code_page"
    else:
        if parsed is not None and not parsed["symbol"]:
            parsed = None
        if parsed is None and ident and (requirements["found"] or documented_params):
            # The topic documents a symbol but prints no declaration (for
            # example the CE 3.0 IOCTL topics). Only what the page states is
            # recorded; the missing declaration stays a declared gap.
            parsed = dict(EMPTY_PARSE)
            parsed["symbol"] = ident
            parsed["kind"] = normalize_kind(kind_label or "unknown", scope, ident)
            parsed["parse_notes"] = ["declaration_not_documented_on_page"]
            declaration = None
            origin = "none"
        if parsed is not None and parsed["symbol"]:
            role = documentation_role(origin, ident, declaration)
            record = build_symbol_record(
                source_id=source_id, page_id=page_id, path=path, title=title,
                source_url=source_url, updated=updated, declaration=declaration,
                declaration_origin=origin or "none", parsed=parsed,
                requirements=requirements, documented_params=documented_params,
                deprecations=deprecations, scope=scope,
                page_kind_label=kind_label, documentation_role_value=role,
                extracted_on=extracted_on,
                corpus_revision=corpus_revision)
            record["kind"] = normalize_kind(record["kind"], record.get("scope"), record["symbol"])
            record["page_class"] = ("symbol_page" if role != "example_code_fragment"
                                    else "prose_page_code_fragment")
            record["declaration_status"] = decl_status
            mismatch = bool(ident) and ident.lower() != (record["symbol"] or "").lower()
            record["title_symbol"] = ident
            record["title_symbol_matches_declaration"] = (
                bool(ident) and not mismatch)
            if mismatch:
                record["uncertainty"]["notes"].append(
                    "page title identifier differs from the declaration identifier: %s vs %s"
                    % (ident, record["symbol"]))
            records.append(record)
        if records:
            page_class = records[0]["page_class"]
        elif decl_status.startswith("candidate_mismatch"):
            page_class = "declaration_candidate_mismatch"
        else:
            page_class = classify_page(title, requirements, declaration, None)

    source_url_out = clip(source_url or "", 200)[0]
    header = requirements["header"]["value_raw"] if requirements["header"] else ""
    library = requirements["libraries"][0]["value_raw"] if requirements["libraries"] else ""
    version_text = ""
    for entry in requirements["statements"]:
        if entry["field"] == "os_versions":
            version_text = entry["value_raw"]
            break

    page_row = [
        page_id,
        source_id,
        os.path.relpath(path, ROOT),
        clip(title, 160)[0],
        page_class,
        str(len(records)),
        (records[0]["kind"] if records else ""),
        (records[0]["symbol"] if records else (ident or "")),
        (origin or "none"),
        clip(header, 80)[0],
        clip(library, 80)[0],
        clip(version_text, 120)[0],
        (decl_status or "")[:60],
        "",
        source_url_out,
    ]
    return {"page": page_row, "records": records, "error": None}


PAGE_COLUMNS = ["page_id", "source_id", "path", "title", "page_class", "symbol_count",
                "kind", "symbol", "declaration_origin", "header", "library",
                "os_versions_raw", "declaration_status", "duplicate_of", "source_url"]


def run_book(book, jobs, limit, force, extracted_on, corpus_revision, log):
    source = vocab.SOURCES[book]
    book_dir = os.path.join(ROOT, source["book_path"])
    if not os.path.isdir(book_dir):
        log("SKIP %s: no directory %s" % (book, book_dir))
        return 0, 0
    symbols_out = os.path.join(WORK, "symbols-%s.ndjson" % book)
    pages_out = os.path.join(PAGES, "%s.tsv" % book)
    if not force and os.path.exists(symbols_out) and os.path.exists(pages_out):
        log("SKIP %s: outputs already present (use --force)" % book)
        return -1, -1

    # The corpus holds some pages twice: once as "<id>.html" and once as
    # "<id>(v=tag).html" (two harvest passes of the same Microsoft page, same
    # canonical URL). Only the canonical file is read for symbols; the extra
    # copy is listed in the coverage table as a duplicate so that the page
    # inventory stays complete.
    names = [name for name in sorted(os.listdir(book_dir)) if name.endswith((".html", ".htm"))]
    groups = {}
    for name in names:
        base = re.sub(r"\(v=[^)]+\)(?=\.html?$)", "", name)
        groups.setdefault(base, []).append(name)
    pages, duplicates = [], []
    for base in sorted(groups):
        group = groups[base]
        canonical = base if base in group else group[0]
        pages.append(os.path.join(book_dir, canonical))
        for name in group:
            if name != canonical:
                duplicates.append((base, name))
    if limit:
        pages = pages[:limit]
    log("BOOK %s: %d canonical pages (%d duplicate files skipped)"
        % (book, len(pages), len(duplicates)))

    arguments = [(path, book, extracted_on, corpus_revision) for path in pages]
    symbols_written, page_rows = 0, 0
    started = time.time()
    with open(symbols_out, "w", encoding="utf-8") as symbol_file, \
            open(pages_out, "w", encoding="utf-8") as page_file:
        page_file.write("#" + "\t".join(PAGE_COLUMNS) + "\n")
        if jobs > 1:
            with ProcessPoolExecutor(max_workers=jobs) as pool:
                results = pool.map(process_page, arguments, chunksize=8)
                results = _consume(results, symbol_file, page_file, log, started, len(pages))
                symbols_written, page_rows = results
        else:
            results = (process_page(argument) for argument in arguments)
            symbols_written, page_rows = _consume(results, symbol_file, page_file, log, started, len(pages))
        for base, name in duplicates:
            row = [base, book, os.path.relpath(os.path.join(book_dir, name), ROOT),
                   "", "duplicate_page", "0", "", "", "none", "", "", "",
                   "duplicate of %s" % base, os.path.relpath(os.path.join(book_dir, base), ROOT)
                   if os.path.exists(os.path.join(book_dir, base)) else "", ""]
            page_file.write("\t".join(field.replace("\t", " ") for field in row) + "\n")
            page_rows += 1
    log("BOOK %s: %d symbol records, %d page rows (%d duplicates listed)"
        % (book, symbols_written, page_rows, len(duplicates)))
    return symbols_written, page_rows


def _consume(results, symbol_file, page_file, log, started, total):
    symbols_written, page_rows, errors = 0, 0, 0
    for index, result in enumerate(results, start=1):
        if result["error"]:
            errors += 1
            if errors < 5:
                log("ERROR %s" % result["error"])
        if result["page"]:
            row = [str(field).replace("\t", " ").replace("\n", " ") for field in result["page"]]
            page_file.write("\t".join(row) + "\n")
            page_rows += 1
        for record in result["records"]:
            symbol_file.write(json.dumps(record, ensure_ascii=False, sort_keys=True) + "\n")
            symbols_written += 1
        if index % 5000 == 0:
            log("  ... %d/%d pages (%.0fs)" % (index, total, time.time() - started))
    return symbols_written, page_rows


def git_revision():
    try:
        import subprocess
        return subprocess.check_output(["git", "-C", ROOT, "rev-parse", "--short", "HEAD"],
                                       text=True).strip()
    except Exception:
        return "unknown"


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--all", action="store_true", help="extract every in-scope book")
    parser.add_argument("--book", action="append", default=[], help="source id to extract")
    parser.add_argument("--limit", type=int, default=0, help="limit pages per book (debug)")
    parser.add_argument("--jobs", type=int, default=max(1, min(4, (os.cpu_count() or 1))))
    parser.add_argument("--force", action="store_true", help="rewrite existing outputs")
    args = parser.parse_args()

    books = args.book or (vocab.EXTRACT_BOOKS if args.all else [])
    if not books:
        parser.error("one of --all or --book is required")
    unknown = [book for book in books if book not in vocab.SOURCES]
    if unknown:
        parser.error("unknown source id(s): %s" % ", ".join(unknown))

    os.makedirs(WORK, exist_ok=True)
    os.makedirs(PAGES, exist_ok=True)
    extracted_on = dt.date.today().isoformat()
    revision = git_revision()

    def log(message):
        print(message, flush=True)

    log("corpus revision %s, extracted_on %s, jobs %d" % (revision, extracted_on, args.jobs))
    for book in books:
        run_book(book, args.jobs, args.limit, args.force, extracted_on, revision, log)


if __name__ == "__main__":
    main()
