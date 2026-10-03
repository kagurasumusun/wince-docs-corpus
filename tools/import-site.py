#!/usr/bin/env python3
"""tools/import-site.py -- import the HTML page trees kept under sources/.

Some official media in ``sources/`` are *not* a CHM set: the CE 2.0 Technical
Information CD carries the Microsoft "Windows CE Developer" site as plain
HTML, and the 4.2 / 5.0 / 6.0 discs carry their release notes next to the
CHMs.  Those documents were never imported into ``corpus/`` -- the CHM
extractor and the media importer both look at other things -- so this tool
does it, from the local ``sources/`` tree, with no network access.

    python3 tools/import-site.py --config queues/site-sets.tsv
    python3 tools/import-site.py --list
    python3 tools/import-site.py --once windows-ce-6.0       # one entry
    python3 tools/import-site.py --config queues/site-sets.tsv --dry-run

Config (tab separated, ``#`` comments)::

    name <TAB> source tree <TAB> output dir <TAB> [exclude regex]

The importer

* copies every ``.htm``/``.html`` file, re-encoded to UTF-8, keeping the
  site's relative layout (``developer/prodinfo/v1revguide.htm`` ->
  ``corpus/site/windows-ce-2.0/developer/prodinfo/v1revguide.html``);
* skips everything else (images, CSS, the CHMs/HLPs that other tools already
  extracted, installers) -- the corpus holds documentation pages;
* refuses a page whose content is a "Topic Not Found" placeholder;
* skips a page that ``data/index/aliases.tsv`` already collapsed elsewhere
  (the same release notes can be on two discs);
* writes the receipt ``data/reports/site-imported.tsv`` so a re-run does not
  import the same tree twice (``--force`` overrides).

The page id is the file stem; a generic site stem (``default``, ``index``,
``home``) is prefixed with its directory so the id stays meaningful
(``prodinfo_default``).
"""

import argparse
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import alias_index  # noqa: E402

ROOT = alias_index.ROOT
RECEIPT = os.path.join(ROOT, "data", "reports", "site-imported.tsv")
PAGE_EXT = (".htm", ".html")
GENERIC_STEMS = {"default", "index", "home", "main"}
CHARSET_RE = re.compile(rb"charset\s*=\s*[\"']?([A-Za-z0-9_.:-]+)", re.I)
CP1252 = {"windows-1252", "cp1252", "iso-8859-1", "latin-1", "iso8859-1"}
UTF8 = {"utf-8", "utf8", "ascii", "us-ascii"}
PLACEHOLDER = re.compile(rb"<title>\s*(Topic Not Found|Page Not Found)\s*</title>",
                         re.I)


def log(*parts):
    print("[site]", *parts, flush=True)


def to_utf8(body):
    match = CHARSET_RE.search(body[:2048])
    charset = match.group(1).decode("ascii", "replace").lower() if match else ""
    if charset in UTF8:
        return body
    if not charset:
        try:
            body.decode("utf-8")
            return body
        except UnicodeDecodeError:
            charset = "cp1252"
    codec = "cp1252" if charset in CP1252 else charset
    try:
        text = body.decode(codec)
    except (UnicodeDecodeError, LookupError):
        text = body.decode("cp1252", "replace")
    return text.encode("utf-8")


def page_id(rel):
    stem, _ext = os.path.splitext(rel)
    stem = stem.replace("/", "_").replace(" ", "_")
    parts = rel.split(os.sep)
    base = os.path.splitext(parts[-1])[0].lower()
    if base in GENERIC_STEMS and len(parts) > 1:
        parent = re.sub(r"[^A-Za-z0-9]+", "_", parts[-2])
        return f"{parent}_{base}"
    return stem


def load_config(path):
    entries = []
    with open(path, encoding="utf-8") as fh:
        for line in fh:
            line = line.rstrip("\n")
            if not line.strip() or line.startswith("#"):
                continue
            parts = [p.strip() for p in line.split("\t")]
            if len(parts) < 3:
                log(f"config: ignoring malformed line: {line!r}")
                continue
            entries.append({
                "name": parts[0], "source": parts[1], "out": parts[2],
                "exclude": parts[3] if len(parts) > 3 else "",
            })
    return entries


def load_receipt():
    done = {}
    if not os.path.isfile(RECEIPT):
        return done
    with open(RECEIPT, encoding="utf-8") as fh:
        for line in fh:
            if line.startswith("#") or not line.strip():
                continue
            parts = line.rstrip("\n").split("\t")
            if len(parts) >= 3:
                done[parts[0]] = {"pages": parts[1], "date": parts[2],
                                  "out": parts[3] if len(parts) > 3 else ""}
    return done


def mark_imported(entry, pages):
    header = not os.path.isfile(RECEIPT)
    os.makedirs(os.path.dirname(RECEIPT), exist_ok=True)
    with open(RECEIPT, "a", encoding="utf-8") as fh:
        if header:
            fh.write("# name\tpages\tdate\tout\n")
        fh.write(f"{entry['name']}\t{pages}\t{today()}\t{entry['out']}\n")


def today():
    import datetime
    return datetime.date.today().isoformat()


def import_entry(entry, dry_run=False, force=False):
    source = os.path.join(ROOT, entry["source"])
    out = os.path.join(ROOT, entry["out"])
    if not os.path.isdir(source):
        log(f"{entry['name']}: source tree missing: {entry['source']}")
        return 0
    refused = re.compile(entry["exclude"], re.I) if entry["exclude"] else None
    imported = skipped = excluded = aliased = 0
    written = []
    for dirpath, dirnames, filenames in os.walk(source):
        dirnames.sort()
        for name in sorted(filenames):
            path = os.path.join(dirpath, name)
            rel = os.path.relpath(path, source)
            if os.path.splitext(name)[1].lower() not in PAGE_EXT:
                continue
            if refused and refused.search(rel.replace(os.sep, "/")):
                excluded += 1
                continue
            with open(path, "rb") as fh:
                body = fh.read()
            if not body.strip() or PLACEHOLDER.search(body[:4096]):
                skipped += 1
                continue
            target = os.path.join(out, os.path.splitext(rel)[0] + ".html")
            if alias_index.is_aliased(target):
                aliased += 1
                continue
            imported += 1
            written.append((rel, target))
            if dry_run:
                continue
            os.makedirs(os.path.dirname(target), exist_ok=True)
            with open(target, "wb") as fh:
                fh.write(to_utf8(body))
    log(f"{entry['name']}: {imported} page(s) -> {entry['out']}"
        + (f", {aliased} already collapsed" if aliased else "")
        + (f", {excluded} excluded by {entry['exclude']!r}" if excluded else "")
        + (f", {skipped} placeholder/empty" if skipped else ""))
    if not dry_run:
        mark_imported(entry, imported)
    return imported


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0],
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--config", default=os.path.join("queues", "site-sets.tsv"))
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--once", help="import a single entry by name")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--force", action="store_true",
                    help="import again even when the receipt says done")
    args = ap.parse_args()

    entries = load_config(os.path.join(ROOT, args.config))
    if args.once:
        entries = [e for e in entries if e["name"] == args.once]
        if not entries:
            log(f"no config entry named {args.once!r}")
            return 1
    done = load_receipt()

    if args.list:
        for entry in entries:
            state = "imported " + done[entry["name"]]["date"] \
                if entry["name"] in done else "pending"
            print(f"{entry['name']:20s} {entry['source']:28s} "
                  f"{entry['out']:34s} {state}")
        return 0

    total = 0
    for entry in entries:
        if entry["name"] in done and not args.force and not args.dry_run:
            log(f"{entry['name']}: already imported "
                f"({done[entry['name']]['pages']} pages, "
                f"{done[entry['name']]['date']}); --force to repeat")
            continue
        total += import_entry(entry, args.dry_run, args.force)
    log(f"total {total} page(s) "
        f"{'would be ' if args.dry_run else ''}imported")
    return 0


if __name__ == "__main__":
    sys.exit(main())
