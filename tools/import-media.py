#!/usr/bin/env python3
"""Bring a piece of official media into the corpus.

The releases under ``sources/`` were collected by hand: download the medium
(the CD/DVD image or installer archive), keep it verbatim, extract the
documentation pages from it.  This tool does the same thing on a runner, for
media that the working environment cannot reach (archive.org is not on its
network allow list) but a GitHub runner can:

    # what is in an Internet Archive item?  (download + inventory only)
    python3 tools/import-media.py --item MPLATSDK.20 --name windows-ce-2.0-sdk

    # extract the documentation of an already downloaded medium
    python3 tools/import-media.py --scan sources/windows-ce-2.0-sdk \\
        --extract --out corpus/msdn-library/windows-ce-2.0-sdk --name windows-ce-2.0-sdk

What "documentation" means here, per file type inside the medium:

* ``.htm``/``.html``            copied as pages (re-encoded to UTF-8)
* ``.chm``                      unpacked with 7z (see tools/extract-chm.py)
* ``.hlp``/``.mvb``             decoded with helpdeco (if it is on PATH; see
                                tools/extract-mvb.py for the MVB recipe)
* ``.iso``                      read with tools/iso9660.py (no 7z needed)
* ``.cab``                      InstallShield cabinets are unpacked with
                                ``unshield`` when it is on PATH
* ``.zip``/``.exe``/``.7z``     unpacked with 7z and then scanned again

Everything else (binaries, sources, samples, images) is skipped and counted,
so the inventory says what the medium holds without importing it.

By default the medium is kept verbatim under ``sources/<name>/`` and gets a
``PROVENANCE.md`` recording the Internet Archive item, the file name, size
and md5 of every file that was downloaded.  Action ``import-scratch`` is for a
medium that is *not* kept: it is fetched to ``.cache/media/<name>/``, the
documentation pages go to the corpus, and a ``PROVENANCE.md`` next to those
pages records where they came from.  Either way, only documentation is
imported - this is a documentation corpus, not a source-code mirror.
"""

import argparse
import collections
import hashlib
import html
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
import time
import urllib.parse
import urllib.request
import zipfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BASE_URL = "https://archive.org"          # overridable with --base-url
USER_AGENT = ("wince-docs-corpus/2.0 "
              "(+https://github.com/kagurasumusun/wince-docs-corpus)")
ARCHIVE = ("archive", "archive.zip", "archive.rar", "archive.7z")
# Media that is fetched and thrown away again (scratch mode) still needs its
# provenance recorded - next to the pages it produced, not next to the image.
_SCRATCH = {}
ARCHIVE_EXT = (".iso", ".zip", ".7z", ".rar", ".cab", ".exe", ".msi", ".img",
               ".bin", ".tar", ".gz", ".tgz")
PAGE_EXT = (".htm", ".html")
HELP_EXT = (".hlp", ".mvb", ".mvw", ".gid")
# Assets, binaries, toolchains and source code: counted, never imported.  A
# medium is a carrier for its documentation; the code it ships stays where it
# is (see "What is collected" in the top-level README).
SKIP_EXT = (".gif", ".png", ".jpg", ".jpeg", ".bmp", ".ico", ".css", ".js",
            ".xml", ".dtd", ".xsl", ".hhc", ".hhk", ".cnt", ".dll", ".exe",
            ".lib", ".obj", ".pdb", ".sys", ".cab", ".msi", ".c", ".h",
            ".cpp", ".cxx", ".hpp", ".cs", ".vb", ".java", ".rc", ".def",
            ".asm", ".s", ".inc", ".mak", ".dsp", ".dsw", ".vbp", ".vcp",
            ".vcxproj", ".sln", ".py", ".sh", ".bat", ".ocx", ".tlb", ".res",
            ".map", ".pch", ".ncb", ".opt", ".plg", ".bsc", ".exp")
CHARSET_RE = re.compile(rb"charset\s*=\s*[\"']?([A-Za-z0-9_.:-]+)", re.I)
TITLE_RE = re.compile(r"<title>(.*?)</title>", re.S | re.I)


def log(message):
    print(message, flush=True)


# ---------------------------------------------------------------------------
# downloading
# ---------------------------------------------------------------------------
def open_url(url, timeout):
    request = urllib.request.Request(url, headers={"User-Agent": USER_AGENT})
    return urllib.request.urlopen(request, timeout=timeout)


def metadata(item):
    url = f"{BASE_URL}/metadata/{urllib.parse.quote(item)}"
    with open_url(url, 60) as fh:
        return json.load(fh)


def download(url, dest, attempts=3):
    log(f"[media] {url}")
    os.makedirs(os.path.dirname(dest), exist_ok=True)
    last_error = None
    for attempt in range(1, attempts + 1):
        digest = hashlib.md5()
        try:
            with open_url(url, 600) as response, \
                    open(dest + ".part", "wb") as out:
                while True:
                    chunk = response.read(1 << 20)
                    if not chunk:
                        break
                    out.write(chunk)
                    digest.update(chunk)
            os.replace(dest + ".part", dest)
            return digest.hexdigest(), os.path.getsize(dest)
        except Exception as exc:                          # noqa: BLE001
            last_error = exc
            log(f"[media] attempt {attempt}/{attempts} failed: "
                f"{type(exc).__name__}: {exc}")
            if os.path.exists(dest + ".part"):
                os.remove(dest + ".part")
            time.sleep(5 * attempt)
    raise RuntimeError(f"could not download {url}: {last_error}")


def provenance_text(item, data, rows, medium_note):
    meta = data.get("metadata", {})
    lines = [f"# {medium_note} — provenance", "",
             f"* Internet Archive item: <https://archive.org/details/{item}>",
             f"* Title: {meta.get('title', '')}",
             f"* Creator / date: {meta.get('creator', '')} / "
             f"{meta.get('date', '')}",
             f"* Collected: {_today()} by tools/import-media.py "
             "(via .github/workflows/import-media.yml)", "",
             "| File | Bytes | md5 (Internet Archive) | URL |",
             "|------|------:|------------------------|-----|"]
    for name, size, md5, url in rows:
        lines.append(f"| `{name}` | {size:,} | `{md5}` | {url} |")
    return "\n".join(lines) + "\n"


def write_scratch_provenance(out, item, data, rows):
    """The medium was not kept: record where the pages came from instead."""
    os.makedirs(out, exist_ok=True)
    rel = os.path.relpath(out, ROOT) if out.startswith(ROOT) else out
    text = provenance_text(item, data, rows, rel)
    text += (
        "\nThe medium itself is **not** kept in this repository: "
        ".github/workflows/import-media.yml\ndownloads it to a scratch "
        "directory, imports the documentation pages of the\ntree above and "
        "discards the image. Binaries, headers, samples and toolchains\nare "
        "not part of this corpus - see \"What is collected\" in the "
        "top-level\nREADME.\n")
    with open(os.path.join(out, "PROVENANCE.md"), "w", encoding="utf-8") as fh:
        fh.write(text)


def fetch_item(item, name, pattern, keep=True):
    data = metadata(item)
    files = [f for f in data.get("files", [])
             if f.get("source") == "original"
             and not f["name"].lower().endswith((".torrent", ".xml", ".sqlite",
                                                 ".jpg", ".jpeg", ".png"))
             and re.search(pattern, f["name"], re.I)]
    if not files:
        log(f"[media] {item}: nothing matches {pattern!r}")
        return 1
    out = (os.path.join(ROOT, "sources", name) if keep
           else os.path.join(ROOT, ".cache", "media", name))
    os.makedirs(out, exist_ok=True)
    rows = []
    for entry in files:
        url = (f"{BASE_URL}/download/{urllib.parse.quote(item)}/"
               f"{urllib.parse.quote(entry['name'])}")
        dest = os.path.join(out, entry["name"])
        if os.path.exists(dest):
            log(f"[media] {entry['name']}: already here")
        else:
            md5, size = download(url, dest)
            log(f"[media] {entry['name']}: {size:,} bytes, md5 {md5}")
        rows.append((entry["name"], os.path.getsize(dest),
                     entry.get("md5", ""), url))
    if keep:
        write_provenance(out, item, data, rows)
    else:
        # No medium in the repository: the provenance goes next to the pages.
        _SCRATCH[name] = {"rows": rows, "data": data, "item": item}
    inventory(out, name)
    return 0


def write_provenance(out, item, data, rows):
    """Provenance of a medium that stays in the repository (sources/<name>)."""
    path = os.path.join(out, "PROVENANCE.md")
    if os.path.exists(path):
        return
    text = provenance_text(item, data, rows,
                           f"sources/{os.path.basename(out)}")
    text += ("\nThe files here are the untouched medium. The documentation "
             "pages\nextracted from them are under `corpus/` (see the tree's "
             "own README\nfor what was taken).\n")
    with open(path, "w", encoding="utf-8") as fh:
        fh.write(text)


def _today():
    import datetime as _dt
    return _dt.datetime.now(_dt.timezone.utc).strftime("%Y-%m-%d")


# ---------------------------------------------------------------------------
# inventory / extraction
# ---------------------------------------------------------------------------
def seven_zip():
    for name in ("7z", "7za", "7zr"):
        path = shutil.which(name)
        if path:
            return path
    return None


def unpack(seven, source, dest):
    """Unpack an archive into dest; returns True when it worked."""
    os.makedirs(dest, exist_ok=True)
    result = subprocess.run([seven, "x", "-y", "-bso0", "-bsp0", source,
                             f"-o{dest}"], capture_output=True, text=True)
    if result.returncode != 0:
        tail = (result.stderr or result.stdout or "").strip().splitlines()
        log(f"[media] 7z could not unpack {os.path.basename(source)}: "
            f"{tail[-1] if tail else 'no output'}")
        return False
    return True


def unpack_iso(source, dest):
    """Read an ISO 9660 image with tools/iso9660.py; no external tool needed."""
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import iso9660  # noqa: E402  (local tool, same directory)
    try:
        image = iso9660.ISO9660(source)
    except Exception as exc:                                  # noqa: BLE001
        log(f"[media] {os.path.basename(source)}: not ISO 9660 ({exc})")
        return False
    entries = [e for e in image.entries if not e.is_dir]
    for entry in entries:
        target = os.path.join(dest, *entry.path.split("/"))
        os.makedirs(os.path.dirname(target), exist_ok=True)
        with open(target, "wb") as fh:
            fh.write(image.read(entry))
    log(f"[media] {os.path.basename(source)}: ISO 9660, "
        f"{len(entries)} file(s) read with tools/iso9660.py")
    return True


def unpack_cab(source, dest):
    """Unpack an InstallShield cabinet with unshield (7z cannot read them)."""
    tool = shutil.which("unshield")
    if not tool:
        return False
    os.makedirs(dest, exist_ok=True)
    result = subprocess.run([tool, "x", "-d", dest, source],
                            capture_output=True, text=True)
    if result.returncode != 0:
        tail = (result.stderr or result.stdout or "").strip().splitlines()
        log(f"[media] unshield could not unpack {os.path.basename(source)}: "
            f"{tail[-1] if tail else 'no output'}")
        return False
    return True


def walk_medium(root, seven, depth=0, unpacked=None, prefix=""):
    """Yield (path, kind, rel) for every interesting file below root.

    Archives are unpacked as they are met (depth-limited) and the files inside
    them keep the archive's name as a path prefix, so a medium that holds two
    archives does not mix their documentation trees.
    """
    unpacked = unpacked if unpacked is not None else {}
    for dirpath, dirnames, filenames in os.walk(root):
        dirnames.sort()
        for name in sorted(filenames):
            path = os.path.join(dirpath, name)
            lower = name.lower()
            rel = prefix + os.path.relpath(path, root).replace(os.sep, "/")
            if lower.endswith(ARCHIVE_EXT) and depth < 4:
                key = rel
                if key in unpacked:
                    continue
                stem = re.sub(r"\.(iso|zip|7z|rar|cab|exe|msi|img|bin|tar|gz|tgz)$",
                              "", name, flags=re.I)
                inner_prefix = f"{prefix}{stem}/"
                if seven or lower.endswith(".iso") or lower.endswith(".cab"):
                    target = os.path.join(
                        tempfile.gettempdir(), "media-unpack", f"d{depth}",
                        hashlib.md5(key.encode()).hexdigest()[:12])
                    done = os.path.isdir(target)
                    if not done and lower.endswith(".iso"):
                        done = unpack_iso(path, target)
                    if not done and lower.endswith(".cab"):
                        done = unpack_cab(path, target)
                    if not done and seven:
                        done = unpack(seven, path, target)
                    if done:
                        unpacked[key] = target
                        yield from walk_medium(target, seven, depth + 1,
                                               unpacked, inner_prefix)
                        continue
                    # Could not look inside: count it as the asset it is.
                    yield path, "asset", rel
                    continue
                if lower.endswith(".zip"):
                    # A machine without 7z can still look inside a zip.
                    target = os.path.join(
                        tempfile.gettempdir(), "media-unpack", f"d{depth}",
                        hashlib.md5(key.encode()).hexdigest()[:12])
                    if not os.path.isdir(target):
                        os.makedirs(target, exist_ok=True)
                        try:
                            with zipfile.ZipFile(path) as archive:
                                archive.extractall(target)
                        except (zipfile.BadZipFile, OSError) as exc:
                            log(f"[media] zip {name}: {exc}")
                            continue
                    unpacked[key] = target
                    yield from walk_medium(target, seven, depth + 1, unpacked,
                                           inner_prefix)
                    continue
            if lower.endswith(PAGE_EXT + HELP_EXT + (".chm",)):
                yield path, "documentation", rel
            elif lower.endswith(SKIP_EXT):
                yield path, "asset", rel
            else:
                yield path, "other", rel


def inventory(root, label):
    """Print (and return) what a medium holds, without importing anything."""
    seven = seven_zip()
    counts = collections.Counter()
    examples = collections.defaultdict(list)
    pages = help_files = chms = 0
    for path, kind, rel in walk_medium(root, seven):
        ext = os.path.splitext(path)[1].lower()
        if kind == "documentation":
            if ext in PAGE_EXT:
                pages += 1
            elif ext in HELP_EXT:
                help_files += 1
            elif ext == ".chm":
                chms += 1
        counts[ext or "(none)"] += 1
        if len(examples[ext]) < 3:
            examples[ext].append(rel)
    log(f"[media] {label}: {sum(counts.values()):,} files "
        f"({pages:,} HTML pages, {help_files:,} WinHelp/MVB, {chms:,} CHM)")
    for ext, number in counts.most_common(20):
        log(f"    {ext:10s} {number:6,d}   e.g. {examples[ext][0][:70]}")
    return counts


def page_title(path):
    try:
        with open(path, encoding="utf-8", errors="replace") as fh:
            head = fh.read(8000)
    except OSError:
        return ""
    match = TITLE_RE.search(head)
    return html.unescape(re.sub(r"\s+", " ", match.group(1)).strip()) \
        if match else ""


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


PLACEHOLDER = re.compile(rb"<title>\s*(Topic Not Found|Page Not Found)\s*"
                         rb"</title>", re.I)


def extract_pages(root, out, label, dry_run=False):
    """Copy the documentation pages of a medium into the corpus."""
    seven = seven_zip()
    imported = skipped = 0
    for path, kind, rel in walk_medium(root, seven):
        if kind != "documentation":
            continue
        ext = os.path.splitext(path)[1].lower()
        if ext in PAGE_EXT:
            with open(path, "rb") as fh:
                body = fh.read()
            if not body.strip() or PLACEHOLDER.search(body[:2048]):
                skipped += 1
                continue
            if dry_run:
                imported += 1
                continue
            body = to_utf8(body)
            target = os.path.join(out, os.path.splitext(rel)[0] + ".html")
            os.makedirs(os.path.dirname(target), exist_ok=True)
            with open(target, "wb") as fh:
                fh.write(body)
            imported += 1
        elif ext == ".chm":
            components = os.path.join(out, os.path.splitext(
                os.path.basename(path))[0])
            if os.path.isdir(components) and not dry_run:
                continue
            if dry_run:
                imported += 1
                continue
            sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
            import extract_chm  # noqa: E402  (local tool, same directory)
            pages, _size = extract_chm.extract_chm(seven, path, components)
            imported += pages
        elif ext in HELP_EXT:
            imported += extract_helpfile(path, out, rel, dry_run)
        log(f"    {os.path.basename(path)}: {kind} ({ext})")
    log(f"[media] {label}: imported {imported:,} pages "
        f"({skipped} placeholders/empties skipped)")
    return imported


def extract_helpfile(path, out, rel, dry_run=False):
    """WinHelp/MVB: hand the file to tools/extract-mvb.py (helpdeco + RTF).

    helpdeco itself is a third-party decompiler that is not part of this
    repository; the workflow builds it from its pinned commit.  Without it the
    file is reported and left for a run that has it.
    """
    if dry_run:
        return 1
    tool = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                        "extract-mvb.py")
    book = re.sub(r"[^A-Za-z0-9_]+", "_",
                  os.path.splitext(os.path.basename(path))[0]).upper()
    result = subprocess.run(
        [sys.executable, tool, "--mvb", os.path.abspath(path),
         "--book", book, "--out", os.path.abspath(out)],
        capture_output=True, text=True)
    pages = 0
    for line in (result.stdout or "").splitlines():
        if line.startswith("[mvb]") and "pages" in line:
            match = re.search(r"(\d+) pages", line)
            if match:
                pages = int(match.group(1))
    if result.returncode != 0:
        tail = (result.stderr or result.stdout or "").strip().splitlines()
        log(f"[media] extract-mvb failed on {rel}: "
            f"{tail[-1] if tail else 'no output'}")
    else:
        log(f"[media] {os.path.basename(rel)} -> {pages} pages (book {book})")
    return pages


def load_config(path):
    entries = []
    with open(path, encoding="utf-8") as fh:
        for line_no, line in enumerate(fh, 1):
            line = line.rstrip("\n")
            if not line.strip() or line.lstrip().startswith("#"):
                continue
            parts = [p.strip() for p in line.split("\t")]
            if len(parts) < 4:
                print(f"[media] {path}: line {line_no} has {len(parts)} "
                      f"fields, expected name/item/pattern/out [+action]",
                      file=sys.stderr)
                continue
            name, item, pattern, out = parts[:4]
            action = parts[4] if len(parts) > 4 else "inventory"
            entries.append({"name": name, "item": item, "pattern": pattern,
                            "out": out, "action": action})
    return entries


def run_config(config, only, dry_run=False):
    entries = load_config(config)
    if only:
        entries = [e for e in entries if e["name"] == only]
        if not entries:
            log(f"[media] no config entry named {only}")
            return 1
    for entry in entries:
        scratch = entry["action"] == "import-scratch"
        wanted = entry["action"] in ("import", "import-scratch")
        source_dir = (os.path.join(ROOT, ".cache", "media", entry["name"])
                      if scratch else
                      os.path.join(ROOT, "sources", entry["name"]))
        if not os.path.isdir(source_dir) or not os.listdir(source_dir):
            log(f"[media] {entry['name']}: fetching {entry['item']}"
                f"{' (scratch: the medium is not kept)' if scratch else ''}")
            if dry_run:
                continue
            if fetch_item(entry["item"], entry["name"], entry["pattern"],
                          keep=not scratch):
                return 1
        else:
            log(f"[media] {entry['name']}: already fetched, inventory:")
            inventory(source_dir, entry["name"])
        if wanted and entry["out"]:
            out = entry["out"] if os.path.isabs(entry["out"]) else os.path.join(
                ROOT, entry["out"])
            log(f"[media] {entry['name']}: importing pages into {entry['out']}")
            extract_pages(source_dir, out, entry["name"], dry_run)
            if scratch and not dry_run and entry["name"] in _SCRATCH:
                scratch_info = _SCRATCH[entry["name"]]
                write_scratch_provenance(out, scratch_info["item"],
                                         scratch_info["data"],
                                         scratch_info["rows"])
                log(f"[media] {entry['name']}: provenance written to "
                    f"{os.path.relpath(os.path.join(out, 'PROVENANCE.md'), ROOT)}")
    return 0


def main():
    ap = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--base-url", default=BASE_URL,
                    help="archive host (for tests; default archive.org)")
    ap.add_argument("--config", help="queues/media.tsv (declare media to fetch)")
    ap.add_argument("--only", help="one entry of --config")
    ap.add_argument("--item", help="Internet Archive item to download")
    ap.add_argument("--file", default=r"\.(iso|zip|7z|rar|cab|exe|msi|img|bin)$",
                    help="which files of the item to download (regex)")
    ap.add_argument("--name", help="directory under sources/ (and label)")
    ap.add_argument("--scan", help="a directory (already downloaded medium)")
    ap.add_argument("--extract", action="store_true",
                    help="import the documentation pages into --out")
    ap.add_argument("--out", help="corpus directory to import into")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()
    globals()["BASE_URL"] = args.base_url.rstrip("/")

    if args.config:
        return run_config(os.path.join(ROOT, args.config), args.only,
                          args.dry_run)

    if args.item:
        if not args.name:
            ap.error("--item needs --name")
        return fetch_item(args.item, args.name, args.file)

    if args.scan:
        label = args.name or os.path.basename(args.scan.rstrip("/"))
        if args.extract:
            if not args.out:
                ap.error("--extract needs --out")
            out = args.out if os.path.isabs(args.out) else os.path.join(
                ROOT, args.out)
            return 0 if extract_pages(args.scan, out, label,
                                      args.dry_run) >= 0 else 1
        inventory(args.scan, label)
        return 0

    ap.error("give --config, --item or --scan")


if __name__ == "__main__":
    sys.exit(main())
