#!/usr/bin/env python3
"""Import the Windows CE documentation sets of the techshelps MSDN mirror.

The mirror (https://techshelps.github.io/ , repository
https://github.com/techshelps/techshelps.github.io) is a decompiled copy of
MSDN Library content from the late 1990s — the editions that documented
**Windows CE 1.0 and 2.0**, which Microsoft never put on the Web and which the
rest of this corpus does not cover.

Seven CE sets are imported (5,170 pages):

    MSDN/CEGUIDE   Windows CE Guide (SDK guide)          974 pages
    MSDN/WCEMFC    Windows CE MFC                       2,247 pages
    MSDN/WCEATL    Windows CE ATL                         745 pages
    MSDN/VBCE      Visual Basic for Windows CE            672 pages
    MSDN/WCEDDK    Windows CE DDK                         340 pages
    MSDN/VCCE      Visual C++ for Windows CE              106 pages
    MSDN/DNEMBED   Embedded/Windows CE development         86 pages

Pages are copied verbatim except for the mirror's injected Google Analytics
snippet, which is removed (documented in the tree's PROVENANCE.md).

    # work with an existing clone
    python3 tools/import-techshelps.py --src /tmp/techshelps

    # or let the tool make a partial clone (only the CE sets are fetched)
    python3 tools/import-techshelps.py --clone --cache-dir .cache/techshelps

    python3 tools/import-techshelps.py --src ... --list   # show the sets
"""

import argparse
import os
import re
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REPO_URL = "https://github.com/techshelps/techshelps.github.io.git"
REPO_SHA = "dbd21c49bbe919fd089084f2a5dd90a602685ba1"  # master as of 2021-03-11 (see PROVENANCE.md)
OUT = os.path.join("corpus", "msdn-library", "techshelps")

SETS = {
    "CEGUIDE": "Windows CE Guide (SDK guide, CE 1.0/2.0)",
    "WCEMFC": "Windows CE MFC",
    "WCEATL": "Windows CE ATL",
    "VBCE": "Visual Basic for Windows CE",
    "WCEDDK": "Windows CE DDK",
    "VCCE": "Visual C++ for Windows CE",
    "DNEMBED": "Windows CE embedded development",
}

# The mirror injects a Google Analytics snippet into every page.
GA_RE = re.compile(
    r"<script[^>]*googletagmanager[^>]*>\s*</script>"
    r"|<script>\s*window\.dataLayer.*?</script>",
    re.S | re.I)


def run(cmd, **kw):
    return subprocess.run(cmd, check=True, text=True, **kw)


def clone_to(cache_dir):
    os.makedirs(cache_dir, exist_ok=True)
    target = os.path.join(cache_dir, "techshelps.github.io")
    if os.path.isdir(os.path.join(target, ".git")):
        print(f"[techshelps] reusing {target}")
        return target
    print(f"[techshelps] partial clone into {target} ...", flush=True)
    run(["git", "clone", "--filter=blob:none", "--no-checkout", "--depth", "1",
         REPO_URL, target])
    run(["git", "-C", target, "sparse-checkout", "init", "--no-cone"])
    patterns = [f"MSDN/{name}/**" for name in SETS]
    run(["git", "-C", target, "sparse-checkout", "set"] + patterns)
    run(["git", "-C", target, "checkout"])
    return target


def page_title(text):
    m = re.search(r"<title>(.*?)</title>", text, re.S | re.I)
    if not m:
        return ""
    return re.sub(r"\s+", " ", m.group(1)).strip()


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    src = ap.add_mutually_exclusive_group(required=True)
    src.add_argument("--src", help="existing clone of techshelps.github.io")
    src.add_argument("--clone", action="store_true",
                     help="partial-clone the repository into --cache-dir")
    ap.add_argument("--cache-dir", default=os.path.join(ROOT, ".cache"))
    ap.add_argument("--out", default=OUT)
    ap.add_argument("--list", action="store_true",
                    help="list the CE sets and their page counts, then stop")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    if args.clone:
        root = clone_to(args.cache_dir)
    else:
        root = args.src
    if not os.path.isdir(os.path.join(root, "MSDN")):
        print(f"not a techshelps clone: {root}", file=sys.stderr)
        return 1

    total = 0
    for name, description in SETS.items():
        source = os.path.join(root, "MSDN", name)
        if not os.path.isdir(source):
            print(f"[techshelps] {name}: missing (sparse checkout?)")
            continue
        pages = [p for p in walk_html(source)]
        if args.list:
            print(f"  {name:9s} {len(pages):5d} pages  {description}")
            continue
        target = os.path.join(ROOT, args.out, name)
        if args.dry_run:
            print(f"[techshelps] {name}: would write {len(pages)} pages to "
                  f"{os.path.relpath(target, ROOT)}")
            continue
        os.makedirs(target, exist_ok=True)
        written = 0
        for path in pages:
            rel = os.path.relpath(path, source)
            dest = os.path.join(target, rel)
            os.makedirs(os.path.dirname(dest), exist_ok=True)
            with open(path, "rb") as fh:
                raw = fh.read()
            text = raw.decode("cp1252", "replace")
            new = GA_RE.sub("", text)
            if new == text:
                new = text.replace("\r\n", "\n")
            with open(dest, "w", encoding="utf-8", newline="\n") as fh:
                fh.write(new)
            written += 1
        total += written
        print(f"[techshelps] {name}: {written} pages -> {os.path.relpath(target, ROOT)}")

    if args.list or args.dry_run:
        return 0
    print(f"[techshelps] {total} pages imported")
    return 0


def walk_html(directory):
    for dirpath, dirnames, filenames in os.walk(directory):
        dirnames.sort()
        for name in sorted(filenames):
            if name.lower().endswith((".htm", ".html")) \
                    and not name.lower().startswith("notopic"):
                yield os.path.join(dirpath, name)


if __name__ == "__main__":
    sys.exit(main())
