#!/usr/bin/env python3
"""Merge the scattered knowledge/kb files into one identifier-centric view.

The quote store (``kb/*.jsonl.gz``) stays as evidence.  This module picks,
for each name, the Windows CE fact a generator can emit: one value, one
header, one declaration.  It never invents a number the pages did not print.
A Win32-only number is kept only when no CE page numbers the name, and is
marked ``win32-reference``.
"""

from __future__ import annotations

import re
import sys
import os
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import header_map  # noqa: E402
import quality_filters  # noqa: E402

HEADER_FILE = re.compile(r"[\w.+-]+\.(?:h|hpp|hh|hxx|idl|inc)\b", re.I)

# ANSI / OEM code pages that CE tables print *beside* a charset or locale
# name.  They are not the GDI charset id (ANSI_CHARSET is 0, not 1252).
CODE_PAGE_NUMBERS = {
    437, 708, 709, 710, 720, 737, 775, 850, 852, 855, 857, 858, 860, 861,
    862, 863, 864, 865, 866, 869, 874, 932, 936, 949, 950, 1200, 1201,
    1250, 1251, 1252, 1253, 1254, 1255, 1256, 1257, 1258, 1361, 10000,
    65000, 65001,
}

_INT = re.compile(r"^(-?\d+|0[xX][0-9A-Fa-f]+)[uUlL]*$")
_KEEP_VALUE = re.compile(
    r"^(?:"
    r"-?\d+[uUlL]*|0[xX][0-9A-Fa-f]+[uUlL]*"
    r"|[A-Z][A-Z0-9_]*\s*[+-]\s*(?:0[xX][0-9A-Fa-f]+|\d+)[uUlL]*"
    r"|\(\s*[A-Z][A-Z0-9_]*\s*[+-]\s*(?:0[xX][0-9A-Fa-f]+|\d+)[uUlL]*\s*\)"
    r"|[A-Z][A-Z0-9_]*\(\s*(?:0[xX][0-9A-Fa-f]+|-?\d+)\s*\)"
    r"|[A-Z][A-Z0-9_]+"
    r")$"
)


# Well-known C names whose printed table hit is often a different column.
_NULL_OK = re.compile(r"^(0|0[lL]|0x0+|NULL|\(\s*\(\s*void\s*\*\s*\)\s*0\s*\))$")


def is_keepable_constant_value(value):
    """A printed number, alias, or constructor expression -- not sample C."""
    text = quality_filters.strip_markup(value or "")
    text = re.sub(r"\s+", " ", text).strip().rstrip(";")
    if not text or "<" in text or ">" in text or "</" in text:
        return False
    if any(tok in text for tok in (
            "sizeof", "memset", "declspec", "IMPLICIT_CALL", "(*",
            "hArray", "pguid")):
        return False
    compact = re.sub(r"\s+", "", text)
    return bool(_KEEP_VALUE.match(text) or _KEEP_VALUE.match(compact))

ORIGIN_RANK = {
    "define": 0,
    "enum": 1,
    "cell": 2,
    "table": 3,
    "prose": 4,
    "extra-define": 5,
    "extra-enum": 6,
}


def int_of(value):
    text = str(value or "").strip().replace(" ", "")
    match = _INT.match(text)
    if not match:
        return None
    token = match.group(1)
    try:
        return int(token, 16) if token.lower().startswith("0x") else int(token)
    except ValueError:
        return None


def split_header_files(value):
    """Pull individual header file names out of a printed cell."""
    out = []
    seen = set()
    for match in HEADER_FILE.finditer(value or ""):
        name = header_map.canonical_header(match.group(0).rstrip(".,;"))
        key = name.lower()
        if key in seen:
            continue
        seen.add(key)
        out.append(name)
    return out


def prefer_h(headers):
    """Prefer a .h spelling over .hpp / .idl of the same stem."""
    if not headers:
        return []
    scored = []
    for h in headers:
        ext = h.rsplit(".", 1)[-1].lower()
        scored.append((0 if ext == "h" else 1 if ext == "hpp" else 2, h.lower(), h))
    scored.sort()
    return [scored[0][2]]


def is_code_page_for_charset(name, number):
    if number is None or name is None:
        return False
    if not str(name).endswith("_CHARSET") and not str(name).endswith("CHARSET"):
        return False
    return int(number) in CODE_PAGE_NUMBERS


def choose_constant_value(records, resolved=None):
    """Pick one printed number for *name* from *records*.

    *records*: dicts with ``value``, ``layer``, ``origin``, optional ``headers``.
    *resolved*: a number the review table already chose (still a printed one).

    Returns (print_value, layer, origin, discarded) where discarded is a
    list of ``{value, reason}``.
    """
    discarded = []
    if not records:
        return None, None, None, discarded
    records = [r for r in records if is_keepable_constant_value(r.get("value"))]
    name0 = (records[0].get("name") if records else "") or ""
    if name0 == "NULL":
        records = [r for r in records
                   if _NULL_OK.match(re.sub(r"\s+", "", str(r.get("value") or "")))]
    if not records:
        return None, None, None, discarded

    if resolved not in (None, ""):
        want = int_of(resolved)
        for rec in records:
            if int_of(rec.get("value")) == want or str(rec.get("value")) == str(resolved):
                return rec.get("value"), rec.get("layer") or "ce", rec.get("origin"), discarded

    ce = [r for r in records if (r.get("layer") or "ce") != "win32"]
    win32 = [r for r in records if r.get("layer") == "win32"]
    pool = ce or win32
    layer = "ce" if ce else "win32"

    by_num = defaultdict(list)
    for rec in pool:
        value = rec.get("value")
        number = int_of(value)
        if number is None and not str(value or "").strip():
            continue
        key = number if number is not None else str(value).strip()
        by_num[key].append(rec)

    if not by_num:
        return None, None, None, discarded

    name = (records[0].get("name") if records else "") or ""
    keys = list(by_num)
    if len(keys) > 1:
        charset_keep = [k for k in keys
                        if not (isinstance(k, int) and is_code_page_for_charset(name, k))]
        if charset_keep and len(charset_keep) < len(keys):
            for k in keys:
                if k not in charset_keep:
                    discarded.append({"value": str(by_num[k][0].get("value")),
                                      "reason": "code-page-column"})
            keys = charset_keep
            by_num = {k: by_num[k] for k in keys}

    if len(keys) == 1:
        recs = by_num[keys[0]]
        recs = sorted(recs, key=lambda r: ORIGIN_RANK.get(r.get("origin"), 9))
        return recs[0].get("value"), layer, recs[0].get("origin"), discarded

    # Still several numbers: prefer define/enum origin, then the most
    # frequently printed form.  Do not invent a compromise.
    scored = []
    for key, recs in by_num.items():
        origin = min(ORIGIN_RANK.get(r.get("origin"), 9) for r in recs)
        scored.append((origin, -len(recs), str(key), recs))
    scored.sort()
    best = scored[0][3]
    for origin, _n, _k, recs in scored[1:]:
        discarded.append({"value": str(recs[0].get("value")),
                          "reason": "conflict-kept-best-origin"})
    return best[0].get("value"), layer, best[0].get("origin"), discarded


def choose_header(name, headers, kinds=None):
    """One header file for *name*.

    Page-stated files win when they agree with ``header_map``; otherwise
    the map; otherwise the first .h the pages named.
    """
    files = []
    for raw in headers or []:
        files.extend(split_header_files(raw) if isinstance(raw, str) else [])
        if isinstance(raw, str) and raw and not split_header_files(raw):
            # already a single file name
            if "." in raw:
                files.append(header_map.canonical_header(raw))
    # unique, preserve order
    seen = set()
    uniq = []
    for h in files:
        key = h.lower()
        if key in seen:
            continue
        seen.add(key)
        uniq.append(h)
    mapped = header_map.header_for_constant(name) \
        or header_map.header_for_entity(name, kinds or [])
    if mapped:
        mapped_key = mapped.lower()
        for h in uniq:
            if h.lower() == mapped_key:
                return h
        # map wins over a weak win32-only / correspondence header
        return mapped
    picked = prefer_h(uniq)
    return picked[0] if picked else None


def source_layer(record):
    src = record.get("source")
    if isinstance(src, dict):
        return src.get("layer") or record.get("layer") or ""
    return record.get("layer") or ""
