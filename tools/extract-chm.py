#!/usr/bin/env python3
"""Extract the HTML documentation out of the CHM help files of a media set.

The releases under ``sources/`` ship their documentation as Compiled HTML
Help (``*.chm``); the pages inside them are the official reference/guide
text.  This tool unpacks a CHM with 7-Zip (p7zip reads CHM, for example on a
GitHub runner where the sandbox has no 7z), keeps every HTML page, re-encodes
it as UTF-8 and writes it into the corpus:

    corpus/chm/<release>/<component>/<original relative path>

``<component>`` is the CHM's own file name without the ``P<nnn>_`` inventory
prefix, so several CHMs of one release stay apart.

Because a release's CHM pages can already be in the corpus from another tree
(the CE 5.0 Learn harvest, for instance), the tool can work in two steps:

    # 1. extract into a staging directory and measure the overlap
    python3 tools/extract-chm.py --config queues/chm-sets.tsv \\
        --only windows-ce-5.0 --staging /tmp/chm --report

    # 2. import what is new (or everything, with --keep-duplicates)
    python3 tools/extract-chm.py --config queues/chm-sets.tsv \\
        --only windows-ce-5.0

Config file (`queues/chm-sets.tsv`, tab-separated, `#` comments):

    name <TAB> output dir <TAB> chm glob[,more globs]
"""

import argparse
import collections
import datetime as _dt
import glob
import hashlib
import html
import os
import re
import shutil
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PAGE_EXT = (".htm", ".html")
SKIP_EXT = (".hhc", ".hhk", ".css", ".js", ".gif", ".png", ".jpg", ".jpeg",
            ".bmp", ".ico", ".xml", ".dtd", ".xsl", ".h", ".cpp", ".c",
            ".rc", ".def", ".lib", ".dll", ".exe", ".cab", ".chm", ".zip")
CHARSET_RE = re.compile(rb"charset\s*=\s*[\"']?([A-Za-z0-9_.:-]+)", re.I)
TITLE_RE = re.compile(r"<title>(.*?)</title>", re.S | re.I)
COMPONENT_RE = re.compile(r"^P\d+_")
SEVEN_ZIP_CANDIDATES = ("7z", "7za", "7zr")


def find_seven_zip(explicit=None):
    for name in ([explicit] if explicit else []) + list(SEVEN_ZIP_CANDIDATES):
        if not name:
            continue
        path = shutil.which(name)
        if path:
            return path
    return None


def load_config(path):
    entries = []
    with open(path, encoding="utf-8") as fh:
        for line_no, line in enumerate(fh, 1):
            line = line.rstrip("\n")
            if not line.strip() or line.lstrip().startswith("#"):
                continue
            parts = [p.strip() for p in line.split("\t")]
            if len(parts) != 3:
                print(f"[chm] {path}: line {line_no} has {len(parts)} fields,"
                      f" expected 3 -- ignored", file=sys.stderr)
                continue
            name, out, patterns = parts
            chms = []
            for pattern in patterns.split(","):
                chms.extend(sorted(glob.glob(os.path.join(ROOT, pattern))))
            entries.append({"name": name, "out": out, "chms": chms})
    return entries


def to_utf8(body):
    match = CHARSET_RE.search(body[:2048])
    charset = match.group(1).decode("ascii", "replace").lower() if match else ""
    if charset in ("utf-8", "utf8", "us-ascii", "ascii"):
        return body
    if not charset:
        try:
            body.decode("utf-8")
            return body
        except UnicodeDecodeError:
            charset = "cp1252"
    codec = "cp1252" if charset in ("windows-1252", "cp1252", "iso-8859-1",
                                    "latin-1", "iso8859-1") else charset
    try:
        text = body.decode(codec)
    except (UnicodeDecodeError, LookupError):
        text = body.decode("cp1252", "replace")
    return text.encode("utf-8")


def component_name(chm_path):
    stem = os.path.splitext(os.path.basename(chm_path))[0]
    return COMPONENT_RE.sub("", stem).lower()


def page_title(path):
    try:
        with open(path, encoding="utf-8", errors="replace") as fh:
            head = fh.read(8000)
    except OSError:
        return ""
    match = TITLE_RE.search(head)
    return html.unescape(re.sub(r"\s+", " ", match.group(1)).strip()) \
        if match else ""


def extract_chm(seven_zip, chm_path, dest_dir, dry_run=False):
    """Unpack one CHM into dest_dir; returns (pages, bytes)."""
    if dry_run:
        return 0, 0
    os.makedirs(dest_dir, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="chm-") as tmp:
        result = subprocess.run(
            [seven_zip, "x", "-y", "-bso0", "-bsp0", chm_path, f"-o{tmp}"],
            capture_output=True, text=True)
        if result.returncode != 0:
            tail = (result.stderr or result.stdout or "").strip().splitlines()
            print(f"[chm] 7z failed on {os.path.basename(chm_path)}: "
                  f"{tail[-1] if tail else 'no output'}", file=sys.stderr)
            return 0, 0
        pages = written_bytes = 0
        used_stems = set()
        for dirpath, dirnames, filenames in os.walk(tmp):
            dirnames.sort()
            for name in sorted(filenames):
                source = os.path.join(dirpath, name)
                rel = os.path.relpath(source, tmp).replace(os.sep, "/")
                lower = name.lower()
                if lower.endswith(SKIP_EXT) or lower.startswith("."):
                    continue
                if not lower.endswith(PAGE_EXT):
                    continue
                try:
                    with open(source, "rb") as fh:
                        body = fh.read()
                except OSError:
                    continue
                if not body.strip():
                    continue
                body = to_utf8(body)
                stem, ext = os.path.splitext(rel)
                target_stem = stem
                counter = 2
                while target_stem.lower() in used_stems:
                    target_stem = f"{stem}-{counter}"
                    counter += 1
                used_stems.add(target_stem.lower())
                target = os.path.join(dest_dir, target_stem + ".html")
                os.makedirs(os.path.dirname(target), exist_ok=True)
                with open(target, "wb") as fh:
                    fh.write(body)
                pages += 1
                written_bytes += len(body)
        return pages, written_bytes


def corpus_titles():
    """Normalised page titles already in the corpus, by tree."""
    titles = {}
    index = os.path.join(ROOT, "data", "index", "INDEX.tsv")
    if not os.path.exists(index):
        return titles
    with open(index, encoding="utf-8", errors="replace") as fh:
        for line in fh:
            if line.startswith("#"):
                continue
            parts = line.rstrip("\n").split("\t")
            if len(parts) >= 4 and parts[3]:
                key = re.sub(r"[^a-z0-9]+", " ", parts[3].lower()).strip()
                titles.setdefault(key, set()).add(parts[1].split("/")[0])
    return titles


def normalise(title):
    return re.sub(r"[^a-z0-9]+", " ", title.lower()).strip()


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--config", help="queues/chm-sets.tsv")
    ap.add_argument("--only", help="entry to process (default: all unfinished)")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--chm", help="a single CHM to extract (with --out)")
    ap.add_argument("--out", help="output directory for --chm")
    ap.add_argument("--staging", help="extract here instead of the corpus")
    ap.add_argument("--report", action="store_true",
                    help="write data/reports/chm-overlap-<name>.tsv")
    ap.add_argument("--keep-duplicates", action="store_true",
                    help="import pages whose title is already in the corpus")
    ap.add_argument("--seven-zip", help="path to the 7z binary")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    seven_zip = find_seven_zip(args.seven_zip)

    specs = []
    if args.chm:
        if not args.out:
            ap.error("--chm needs --out")
        specs = [{"name": os.path.basename(args.out.rstrip("/")),
                  "out": args.out, "chms": [args.chm]}]
    else:
        specs = load_config(os.path.join(ROOT, args.config))
        if args.list:
            for spec in specs:
                print(f"  {spec['name']:20s} out={spec['out']:36s} "
                      f"chms={len(spec['chms'])}")
            return 0
        if args.only:
            specs = [s for s in specs if s["name"] == args.only]
            if not specs:
                print(f"no config entry named {args.only}", file=sys.stderr)
                return 1

    if not args.dry_run and not seven_zip:
        print("[chm] no 7z on this machine (a runner has it); "
              "install p7zip-full to extract here", file=sys.stderr)
        return 1

    known = corpus_titles()
    total_new = total_dupe = 0
    for spec in specs:
        out = args.staging or spec["out"]
        out = out if os.path.isabs(out) else os.path.join(ROOT, out)
        print(f"[chm] {spec['name']}: {len(spec['chms'])} CHM(s) -> {out}")
        report_rows = []
        pages_total = 0
        for chm in spec["chms"]:
            component = component_name(chm)
            dest = os.path.join(out, component)
            if os.path.isdir(dest) and not args.staging:
                print(f"    {component}: already extracted, skipped")
                continue
            pages, size = extract_chm(seven_zip, chm, dest, args.dry_run)
            pages_total += pages
            print(f"    {component:18s} {pages:5d} pages "
                  f"{size / 1024 / 1024:5.1f} MiB")
            if args.report and pages:
                for dirpath, _dirnames, filenames in os.walk(dest):
                    for name in sorted(filenames):
                        if not name.lower().endswith(PAGE_EXT):
                            continue
                        path = os.path.join(dirpath, name)
                        title = page_title(path)
                        if not title:
                            continue
                        where = known.get(normalise(title))
                        report_rows.append(
                            (os.path.relpath(path, out), title,
                             ";".join(sorted(where)) if where else ""))
        if args.report and report_rows:
            seen = collections.Counter(1 if r[2] else 0 for r in report_rows)
            dupes = seen.get(1, 0)
            total_new += seen.get(0, 0)
            total_dupe += dupes
            path = os.path.join(ROOT, "data", "reports",
                                f"chm-overlap-{spec['name']}.tsv")
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with open(path, "w", encoding="utf-8") as fh:
                fh.write("page\ttitle\talready_in\n")
                for row in report_rows:
                    fh.write("\t".join(row) + "\n")
            print(f"[chm] {spec['name']}: {len(report_rows):,} pages with a "
                  f"title, {dupes:,} of them already in the corpus "
                  f"({100 * dupes / max(1, len(report_rows)):.0f}%) "
                  f"-> {os.path.relpath(path, ROOT)}")
        print(f"[chm] {spec['name']}: {pages_total:,} pages extracted")
    if args.report:
        print(f"[chm] new titles: {total_new:,} | already in corpus: "
              f"{total_dupe:,}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
