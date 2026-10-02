#!/usr/bin/env python3
"""Extract a Windows Help / Multimedia Viewer book (.mvb / .hlp) into pages.

The proprietary container is decoded by ``helpdeco`` (GPL, Manfred Winterhoff
/ Paul Wise), which writes an RTF rendition with one topic per ``\\page`` and
the help footnotes (``$`` title, ``#`` context id) preserved.  This tool turns
that RTF into the corpus convention — one HTML page per topic, named after the
topic's context id, with the title in ``<title>``/``<h1>``:

    python3 tools/extract-mvb.py --rtf /tmp/PEGSDK.rtf --book PEGSDK \\
        --out corpus/mvb/windows-ce-1.0
    python3 tools/extract-mvb.py --mvb sources/windows-ce-1.0/PEGSDK.MVB \\
        --book PEGSDK --out corpus/mvb/windows-ce-1.0 --helpdeco /path/helpdeco

Pass ``--rtf`` to reuse an RTF that helpdeco already produced; pass ``--mvb``
to run helpdeco (in a scratch directory) first.  Only text is converted —
bitmaps, metafiles and byte-exact RTF layout are deliberately dropped.
"""

import argparse
import os
import re
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MEDIUM = ""  # set by --medium, recorded in each page's provenance comment

# RTF control words that are pure formatting and carry no text.
IGNORED_WORDS = {
    "ansi", "ansicpg", "deff", "deflang", "deflangfe", "froman", "fswiss",
    "fnil", "fmodern", "fscript", "ftech", "fbidi", "fcharset", "fprq",
    "plain", "pard", "par", "page", "keep", "keepn", "sa", "sb", "sl", "li",
    "ri", "fi", "tx", "trqc", "trleft", "trgaph", "brdrs", "brdrb", "brsp",
    "intbl", "cs", "cf", "b", "i", "ul", "uldb", "ulnone", "v", "super",
    "sub", "nosupersub", "chdate", "chtime", "chpgn", "sect", "sectd",
    "cols", "colno", "sbknone", "wrapdefault", "widowctrl", "formshade",
    "ftnbj", "aenddoc", "aendnotes", "fet", "cn", "stshfdbch", "stshfloch",
    "stshfhich", "stshfbi", "rsid", "margl", "margr", "margt", "margb",
    "pgnstart", "ftnstart", "pnseclvl", "pndec", "pntxta", "pntxtb",
    "afs", "afs", "f", "fs", "up", "dn", "charscalex", "expnd", "expndtw",
    "mac", "pc", "pca", "cocoartf", "cocoatextscaling", "cocoaplatform",
}

SKIP_DESTINATIONS = {
    "fonttbl", "colortbl", "stylesheet", "info", "pict", "object",
    "header", "footer", "footerl", "footerr", "headerl", "headerr",
    "listtable", "listoverridetable", "revtbl", "generator", "themedata",
    "colorschememapping", "latentstyles", "datastore", "xmlnstbl",
    "filetbl", "pnseclvl", "bkmkstart", "bkmkend", "nonshppict",
}

TITLE_RE = re.compile(r"<\s*title\s*>(.*?)<\s*/\s*title\s*>", re.S | re.I)


# ---------------------------------------------------------------------------
# RTF tokenizer
# ---------------------------------------------------------------------------
CTRL_RE = re.compile(r"\\([a-zA-Z]+)(-?\d+)?[ ]?")


def tokenize(text):
    """Yield ('group', '{'|'}'), ('ctrl', word, param, delimiter) or ('text', str)."""
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == "{":
            yield ("group", "{")
            i += 1
        elif c == "}":
            yield ("group", "}")
            i += 1
        elif c == "\\":
            if i + 1 < n and text[i + 1] in "{}\\":
                yield ("text", text[i + 1])
                i += 2
                continue
            if i + 1 < n and text[i + 1] == "'":
                yield ("text", bytes([int(text[i + 2:i + 4], 16)]).decode("cp1252",
                                                                       "replace"))
                i += 4
                continue
            m = CTRL_RE.match(text, i)
            if not m:
                i += 1
                continue
            word = m.group(1)
            param = int(m.group(2)) if m.group(2) else None
            yield ("ctrl", word, param, m.group(0)[-1] == " ")
            i = m.end()
        else:
            j = i
            while j < n and text[j] not in "\\{}":
                j += 1
            yield ("text", text[i:j])
            i = j


class Page:
    def __init__(self):
        self.title = ""
        self.ids = []
        self.html = []


# Authoring directives left in the text by the help compiler, e.g.
#   {ewc msdncd, EWGraphic, ab5a 0 /a "PEGFUNC\art\BLURULE.BMP"}
# (a reference to an embedded bitmap/metafile).  They are not prose.
EWC_RE = re.compile(r"\{(?:ew[a-z]|bm[a-z])\b[^}]*\}")


def rtf_to_pages(rtf):
    """Split an RTF document into pages, one per top-level \\page."""
    pages = []
    page = Page()
    out = page.html

    skip_stack = []          # destination groups that carry no text
    depth = 0
    hidden_depth = None      # \v ... : hidden link anchors
    footnote_depth = None
    footnote_text = []
    marker_depth = None      # {\up $} / {\up #} superscript markers
    in_table = row_open = cell_open = False
    cell_parts = []
    pending_pard = False
    buf = []
    para_fs = None
    para_font = None
    title_lower = lambda: page.title.strip().lower()

    def text_now():
        return EWC_RE.sub("", "".join(buf))

    def flush_paragraph():
        nonlocal para_fs, para_font, pending_pard
        text = text_now().strip()
        buf.clear()
        fs, font = para_fs, para_font
        para_fs = para_font = None
        if in_table:
            if text:
                cell_parts.append(text)
            return
        if pending_pard:
            close_table()
        if not text or text.lower() == title_lower():
            return
        if font in ("f3", "f4"):
            out.append('<pre class="code">' + escape(text) + "</pre>\n")
        elif fs is not None and fs >= 28:
            out.append("<h2>" + escape(text) + "</h2>\n")
        else:
            out.append("<p>" + escape(text) + "</p>\n")

    def close_table():
        nonlocal in_table, row_open, cell_open, pending_pard, cell_parts
        if cell_parts:
            emit_cell()
        if row_open:
            out.append("</tr>\n")
        if in_table:
            out.append("</table>\n")
        in_table = row_open = cell_open = pending_pard = False
        cell_parts = []

    def emit_cell():
        nonlocal cell_open, cell_parts, row_open
        if not row_open:
            out.append("<tr>")
            row_open = True
        content = "<br>".join(escape(p) for p in cell_parts)
        out.append("<td>" + content + "</td>")
        cell_parts = []
        cell_open = False

    for token in tokenize(rtf):
        kind = token[0]
        if kind == "group":
            if token[1] == "{":
                depth += 1
                continue
            depth -= 1
            if footnote_depth is not None and depth < footnote_depth:
                value = "".join(footnote_text).strip()
                footnote_text = []
                footnote_depth = None
                if value[:1] == "$":
                    page.title = value[1:].strip()
                    title_lower()
                elif value[:1] == "#":
                    page.ids.append(value[1:].strip())
            if skip_stack and depth < skip_stack[-1]:
                skip_stack.pop()
            if hidden_depth is not None and depth < hidden_depth:
                hidden_depth = None
            if marker_depth is not None and depth < marker_depth:
                marker_depth = None
            if marker_depth is not None or hidden_depth is not None:
                continue
            if not skip_stack and in_table and depth == 0:
                pass
            continue

        if kind == "text":
            if footnote_depth is not None:
                footnote_text.append(token[1])
                continue
            if skip_stack or marker_depth is not None or hidden_depth is not None:
                continue
            buf.append(token[1])
            continue

        word, param = token[1], token[2]

        if word == "v":
            hidden_depth = depth
            continue
        if word == "footnote":
            if not skip_stack:
                footnote_depth = depth
                footnote_text = []
            continue
        if word == "up":
            marker_depth = depth
            continue
        if word in SKIP_DESTINATIONS:
            skip_stack.append(depth)
            continue
        if skip_stack:
            continue

        if word == "page":
            flush_paragraph()
            close_table()
            if page.title or page.html:
                pages.append(page)
            page = Page()
            out = page.html
            continue
        if word in ("par", "line"):
            if in_table:
                text = text_now().strip()
                buf.clear()
                if text:
                    cell_parts.append(text)
            else:
                flush_paragraph()
            continue
        if word == "trowd":
            if not in_table:
                out.append('<table class="dtTABLE">\n')
                in_table = True
            if row_open:
                if cell_parts:
                    emit_cell()
                out.append("</tr>\n")
            out.append("<tr>")
            row_open = True
            pending_pard = False
            continue
        if word in ("trqc", "trleft", "trgaph", "cellx"):
            continue
        if word == "cell":
            text = text_now().strip()
            buf.clear()
            if text:
                cell_parts.append(text)
            emit_cell()
            continue
        if word == "row":
            text = text_now().strip()
            buf.clear()
            if text:
                cell_parts.append(text)
            if cell_parts:
                emit_cell()
            out.append("</tr>\n")
            row_open = False
            continue
        if word == "intbl":
            pending_pard = False
            continue
        if word == "pard":
            if in_table:
                pending_pard = True
            continue
        if word == "tab":
            buf.append("\t" if not in_table else "    ")
            continue
        if word in ("bullet", "emdash", "endash", "lquote", "rquote",
                    "ldblquote", "rdblquote"):
            buf.append({"bullet": "\u2022", "emdash": "\u2014",
                        "endash": "\u2013", "lquote": "\u2018",
                        "rquote": "\u2019", "ldblquote": "\u201c",
                        "rdblquote": "\u201d"}[word])
            continue
        if word == "fs":
            para_fs = param
            continue
        if word == "f":
            para_font = "f" + str(param)
            continue

    flush_paragraph()
    close_table()
    if page.title or page.html:
        pages.append(page)
    return pages


def escape(text):
    return (text.replace("&", "&amp;").replace("<", "&lt;")
                .replace(">", "&gt;"))


def slug(title):
    s = re.sub(r"[^A-Za-z0-9]+", "-", title).strip("-").lower()
    return s or "page"


HTML = """<!DOCTYPE HTML>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>{title}</title>
</head>
<body>
<!-- {book} Books Online ({medium}); text extracted with helpdeco, images dropped. -->
<h1>{title}</h1>
{body}</body>
</html>
"""

BAD_ID = re.compile(r"[^A-Za-z0-9_.-]")


def page_id(page, used):
    for candidate in page.ids:
        clean = BAD_ID.sub("_", candidate)[:80]
        if clean and clean not in used:
            used.add(clean)
            return clean
    base = slug(page.title)
    candidate, n = base, 2
    while candidate in used:
        candidate = f"{base}-{n}"
        n += 1
    used.add(candidate)
    return candidate


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    src = ap.add_mutually_exclusive_group(required=True)
    src.add_argument("--rtf", help="RTF produced by helpdeco")
    src.add_argument("--mvb", help=".mvb/.hlp file to decode with helpdeco")
    ap.add_argument("--book", required=True,
                    help="book directory below --out (e.g. PEGSDK)")
    ap.add_argument("--out", required=True,
                    help="corpus directory for the book (e.g. corpus/mvb/windows-ce-1.0)")
    ap.add_argument("--helpdeco", default=shutil.which("helpdeco") or "",
                    help="path to the helpdeco binary (default: $PATH)")
    ap.add_argument("--keep-rtf", metavar="FILE",
                    help="also copy the RTF here")
    ap.add_argument("--medium", default="",
                    help="source file name recorded in each page's comment")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()
    global MEDIUM
    MEDIUM = args.medium or os.path.basename(args.mvb or args.rtf)

    rtf_path = args.rtf
    scratch = None
    if rtf_path is None:
        if not args.helpdeco or not os.path.exists(args.helpdeco):
            print("helpdeco not found: pass --helpdeco or use --rtf",
                  file=sys.stderr)
            return 1
        scratch = os.path.join(ROOT, ".cache", "mvb")
        os.makedirs(scratch, exist_ok=True)
        for name in os.listdir(scratch):
            os.remove(os.path.join(scratch, name))
        print(f"[mvb] helpdeco {os.path.basename(args.mvb)} ...", flush=True)
        result = subprocess.run(
            [args.helpdeco, "-y", os.path.abspath(args.mvb)],
            cwd=scratch, capture_output=True, text=True)
        rtf_path = os.path.join(
            scratch, os.path.splitext(os.path.basename(args.mvb))[0] + ".rtf")
        if not os.path.exists(rtf_path):
            print(result.stdout[-2000:], result.stderr[-2000:], file=sys.stderr)
            print(f"[mvb] no RTF produced for {args.mvb}", file=sys.stderr)
            return 1

    with open(rtf_path, encoding="latin-1") as fh:
        rtf = fh.read()
    pages = rtf_to_pages(rtf)
    print(f"[mvb] {os.path.basename(rtf_path)}: {len(pages)} pages")

    if args.keep_rtf:
        os.makedirs(os.path.dirname(os.path.abspath(args.keep_rtf)), exist_ok=True)
        shutil.copyfile(rtf_path, args.keep_rtf)

    outdir = os.path.join(ROOT, args.out, args.book) if not os.path.isabs(args.out) \
        else os.path.join(args.out, args.book)
    if args.dry_run:
        for page in pages[:10]:
            print(f"  {page.ids[:1]}  {page.title}")
        return 0

    os.makedirs(outdir, exist_ok=True)
    used = set()
    written = 0
    for page in pages:
        if not page.title and not page.html:
            continue
        pid = page_id(page, used)
        body = "".join(page.html)
        if not body.strip():
            body = "<p></p>\n"
        html = HTML.format(title=escape(page.title or pid), body=body,
                           book=args.book, medium=MEDIUM)
        with open(os.path.join(outdir, pid + ".html"), "w",
                  encoding="utf-8", newline="\n") as fh:
            fh.write(html)
        written += 1
    print(f"[mvb] wrote {written} pages to {os.path.relpath(outdir, ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
