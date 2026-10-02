#!/usr/bin/env python3
"""Import the Windows CE articles of the Microsoft KnowledgeBase Archive.

Source: https://github.com/jeffpar/kbarchive — a static archive of the
Knowledge Base, populated from Microsoft's FTP archive (circa 2002) and from
the Microsoft Programmer's Library CD-ROMs.  The CE subset of that archive
documents problems and answers for the CE 1.0/2.0/2.1x, Handheld PC,
Palm-size PC, Pocket PC and Windows CE Toolkit products, which the rest of
this corpus (a documentation archive) does not cover at all.

The tool works on the original ``txt/<prefix>/Q<id>.TXT`` files: an article is
kept when its header block (the ``DOCUMENT``/``TITLE``/``PRODUCT`` lines and
the "applies to" list) mentions a Windows CE family product.  Each article
becomes one HTML page, ``corpus/kb/<prefix>/<id>.html``, with the original
text preserved verbatim inside a ``<pre>`` block.

    python3 tools/import-kbarchive.py --src /tmp/kbarch
    python3 tools/import-kbarchive.py --src /tmp/kbarch --list
    python3 tools/import-kbarchive.py --clone --cache-dir .cache
"""

import argparse
import html
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REPO_URL = "https://github.com/jeffpar/kbarchive.git"
OUT = os.path.join("corpus", "kb")

# Products / platforms that make an article part of the CE set.
CE_PATTERNS = (
    r"Windows CE",
    r"Windows\s*CE\s*Services",
    r"Handheld PC",
    r"H/PC",
    r"Palm-?size PC",
    r"Pocket PC",
    r"Windows Embedded",
    r"Microsoft Auto PC",
    r"CE Toolkit",
)
CE_RE = re.compile("|".join(CE_PATTERNS), re.I)

TITLE_RE = re.compile(r"^TITLE\s*:\s*(.*)$", re.M)
DOC_RE = re.compile(r"^DOCUMENT:(\S+)", re.M)

TEMPLATE = """<!DOCTYPE HTML>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>{title}</title>
</head>
<body>
<!-- {kb_id} — Microsoft KnowledgeBase article, from the KB archive at
     github.com/jeffpar/kbarchive (original text). Product line: Windows CE. -->
<h1>{title}</h1>
<pre class="kb">
{body}</pre>
</body>
</html>
"""


def run(cmd, **kw):
    return subprocess.run(cmd, check=True, text=True, **kw)


def clone_to(cache_dir):
    os.makedirs(cache_dir, exist_ok=True)
    target = os.path.join(cache_dir, "kbarchive")
    if os.path.isdir(os.path.join(target, ".git")):
        print(f"[kb] reusing {target}")
        return target
    print(f"[kb] partial clone into {target} ...", flush=True)
    run(["git", "clone", "--filter=blob:none", "--no-checkout", "--depth", "1",
         REPO_URL, target])
    run(["git", "-C", target, "sparse-checkout", "init", "--no-cone"])
    run(["git", "-C", target, "sparse-checkout", "set", "txt/**"])
    run(["git", "-C", target, "checkout"])
    return target


def read_article(path):
    with open(path, "rb") as fh:
        raw = fh.read()
    text = raw.decode("cp1252", "replace").replace("\r\n", "\n")
    return text


def article_title(text, path):
    m = TITLE_RE.search(text)
    if m:
        return m.group(1).strip()
    return os.path.splitext(os.path.basename(path))[0]


def is_ce_article(text):
    head = "\n".join(text.split("\n")[:60])
    return bool(CE_RE.search(head))


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    src = ap.add_mutually_exclusive_group(required=True)
    src.add_argument("--src", help="existing clone of jeffpar/kbarchive")
    src.add_argument("--clone", action="store_true")
    ap.add_argument("--cache-dir", default=os.path.join(ROOT, ".cache"))
    ap.add_argument("--out", default=OUT)
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    root = clone_to(args.cache_dir) if args.clone else args.src
    txt = os.path.join(root, "txt")
    if not os.path.isdir(txt):
        print(f"no txt/ directory in {root}", file=sys.stderr)
        return 1

    found, written = [], 0
    for dirpath, dirnames, filenames in os.walk(txt):
        dirnames.sort()
        for name in sorted(filenames):
            if not name.upper().endswith(".TXT"):
                continue
            path = os.path.join(dirpath, name)
            text = read_article(path)
            if not is_ce_article(text):
                continue
            prefix = os.path.basename(dirpath)
            found.append((prefix, name, article_title(text, path)))
    print(f"[kb] {len(found)} Windows CE articles "
          f"({len({f[0] for f in found})} number ranges)")
    if args.list:
        for prefix, name, title in found[:40]:
            print(f"  {prefix}/{name:14s} {title[:70]}")
        return 0
    if args.dry_run:
        return 0

    for prefix, name, title in found:
        source = os.path.join(txt, prefix, name)
        text = read_article(source)
        dest_dir = os.path.join(ROOT, args.out, prefix)
        os.makedirs(dest_dir, exist_ok=True)
        dest = os.path.join(dest_dir,
                            os.path.splitext(name)[0].lower() + ".html")
        with open(dest, "w", encoding="utf-8", newline="\n") as fh:
            fh.write(TEMPLATE.format(title=html.escape(title),
                                     body=html.escape(text), kb_id=name))
        written += 1
    print(f"[kb] wrote {written} pages to "
          f"{os.path.relpath(os.path.join(ROOT, args.out), ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
