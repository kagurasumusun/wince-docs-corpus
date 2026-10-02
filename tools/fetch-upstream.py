#!/usr/bin/env python3
"""tools/fetch-upstream.py -- import shared Win32 documentation from Microsoft.

Microsoft publishes the sources of the Win32 documentation on GitHub, and
Windows CE implements a subset of that same Win32 API, so those pages are the
authoritative reference for the "Win32-common" half of this corpus:

  MicrosoftDocs/sdk-api   Win32 API reference (function/structure/enum pages)
  MicrosoftDocs/win32     Win32 programming guides (desktop-src/*)

Both repositories are CC-BY-4.0 (LICENSE) with MIT-licensed tooling
(LICENSE-CODE); the license files are copied next to the extracted material.

What this script can do
-----------------------

1. ``subset`` (default) -- extract the pages that Windows CE shares with Win32
   into ``corpus/win32/``:

   * ``corpus/win32/api/<module>/<page>.md``
     every sdk-api page whose API name also appears in one of the CE catalogs
     (``data/catalogs/*.tsv``), including the ANSI/Unicode ``A``/``W``
     variants of a shared base name (``CreateFileW`` -> ``CreateFile``).
     ``--scope modules`` additionally takes *every* page of the modules that
     contain at least one shared API name, so that the interfaces, enums and
     structs used together with a shared function are present too
     (183 modules, ~17k pages).
   * ``corpus/win32/guide/<folder>/<page>.md``
     the programming guides for CE-relevant subsystems (see ``GUIDE_FOLDERS``).

2. ``pack`` -- store a complete upstream snapshot as a single compressed
   tarball under ``sources/microsoftdocs/`` (markdown only, no images), so the
   full set can be unpacked offline later::

       python3 tools/fetch-upstream.py pack --source sdk-api

3. ``list`` -- show what a subset run would extract, without writing anything.

Network access
--------------

Downloads use ``codeload.github.com`` (tarball of a pinned commit).  If the
machine has no outbound network, pass ``--tarball`` with a snapshot that was
downloaded elsewhere; every mode works from a local tarball.

Usage
-----

    python3 tools/fetch-upstream.py list
    python3 tools/fetch-upstream.py subset --source sdk-api
    python3 tools/fetch-upstream.py subset --source win32
    python3 tools/fetch-upstream.py pack --source sdk-api
    python3 tools/fetch-upstream.py subset --source sdk-api --tarball sdk-api.tar.gz
"""
import argparse
import collections
import glob
import io
import os
import re
import shutil
import subprocess
import sys
import tarfile
import urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CORPUS = os.path.join(ROOT, "corpus")
SOURCES = os.path.join(ROOT, "sources", "microsoftdocs")

# Upstream snapshots are pinned to a commit so that the material is
# reproducible even after the repositories move on.
UPSTREAM = {
    "sdk-api": {
        "repo": "MicrosoftDocs/sdk-api",
        "ref": "c12073e417d5780fe796278ada21b90cef1b0568",
        "sha": "c12073e417d5780fe796278ada21b90cef1b0568",
        "date": "2026-09-30",
        "subdir": "sdk-api-src/content",
        "license": ["LICENSE", "LICENSE-CODE"],
    },
    "win32": {
        "repo": "MicrosoftDocs/win32",
        "ref": "e103fa4e8810bd8d42c4777e17081e24dbe62dbd",
        "sha": "e103fa4e8810bd8d42c4777e17081e24dbe62dbd",
        "date": "2026-09-15",
        "subdir": "desktop-src",
        "license": ["LICENSE", "LICENSE-CODE"],
    },
}

# sdk-api page kinds: nf=function ns=struct ne=enum nc=callback ni=interface
# nn=namespace nl=library na=attribute
SDK_PAGE = re.compile(r"^(nf|ns|ne|nc|ni|nn|nl|na)-([^-]+)-(.+)\.md$")

# Programming-guide folders from MicrosoftDocs/win32 (desktop-src/) that
# document subsystems Windows CE also implements.  Keep this list in sync
# with corpus/win32/README.md.
GUIDE_FOLDERS = (
    # core OS
    "FileIO", "Memory", "Sync", "ProcThread", "ipc", "Dlls", "Debug",
    "DevIO", "SysInfo", "Power", "Services",
    # windowing / GWES
    "gdi", "menurc", "dlgbox", "inputdev",
    # networking
    "WinSock", "NetMgmt", "Bluetooth",
)

# Not extracted page-by-page (they would add ~1,300 more files):  ``SecCrypto``
# and ``com`` are available in the upstream snapshot (see ``pack`` mode) and on
# GitHub; the Windows CE side of CryptoAPI/COM is already documented in
# corpus/learn/.


# ------------------------------------------------------------------ helpers
def ep(text):
    return text


def load_catalogs():
    """CE API names -> set of books, from data/catalogs/*.tsv."""
    names = collections.defaultdict(set)
    for path in sorted(glob.glob(os.path.join(ROOT, "data", "catalogs", "*.tsv"))):
        book = os.path.basename(path)[:-4]
        with open(path, encoding="utf-8", errors="replace") as fh:
            for line in fh:
                parts = line.rstrip("\n").split("\t")
                if len(parts) < 2:
                    continue
                name = normalize(parts[1])
                if name:
                    names[name].add(book)
    return names


def normalize(text):
    """'CreateFile (Windows CE 5.0)' -> 'createfile'"""
    text = text.lower()
    text = re.sub(r"\(.*?\)", "", text)
    text = re.sub(r"\s+", "", text)
    return re.sub(r"[^a-z0-9_]", "", text)


def download(source, dest):
    meta = UPSTREAM[source]
    url = (f"https://codeload.github.com/{meta['repo']}/tar.gz/"
           f"{meta['ref']}")
    print(f"[fetch] {url}")
    os.makedirs(os.path.dirname(dest), exist_ok=True)
    with urllib.request.urlopen(url, timeout=600) as resp, \
            open(dest, "wb") as out:
        shutil.copyfileobj(resp, out, 1 << 20)
    print(f"[fetch] {dest} ({os.path.getsize(dest):,} bytes)")
    return dest


def open_tarball(path):
    return tarfile.open(path, "r:*")


def tarball_root(tar):
    """The single top-level directory of a GitHub codeload tarball."""
    tops = {name.split("/")[0] for name in tar.getnames() if name}
    assert len(tops) == 1, tops
    return tops.pop()


def iter_blobs(tar, root, prefix):
    for member in tar:
        if not member.isfile():
            continue
        if not member.name.startswith(f"{root}/{prefix}/"):
            continue
        if not member.name.lower().endswith(".md"):
            continue
        yield member


# ------------------------------------------------------------------ subset
def shared_api_names(tar, root, subdir, catalogs):
    """Return {member_name: (kind, module, name)} for CE-shared API pages."""
    pages = {}
    names = collections.defaultdict(list)
    for member in iter_blobs(tar, root, subdir):
        fn = os.path.basename(member.name)
        m = SDK_PAGE.match(fn)
        if not m:
            continue
        kind, module, name = m.groups()
        names[normalize(name)].append((kind, module, member.name))

    shared = set()
    for name in names:
        if name in catalogs:
            shared.add(name)
        elif name.endswith(("a", "w")) and name[:-1] in catalogs:
            # CreateFileW / CreateFileA also document the CE CreateFile page
            shared.add(name)

    for name in shared:
        for kind, module, member_name in names[name]:
            pages[member_name] = (kind, module, os.path.basename(member_name))
    return pages, names, shared


def extract_subset(source, tar_path, apply, pack=False, scope="shared"):
    meta = UPSTREAM[source]
    catalogs = load_catalogs() if source == "sdk-api" else {}
    written = []
    with open_tarball(tar_path) as tar:
        root = tarball_root(tar)
        if source == "sdk-api":
            pages, names, shared = shared_api_names(
                tar, root, meta["subdir"], catalogs)
            if scope == "modules":
                modules = {module for kind, module, _n in pages.values()}
                extra = 0
                for name, entries in names.items():
                    for kind, module, member_name in entries:
                        if module in modules and member_name not in pages:
                            pages[member_name] = (kind, module,
                                                  os.path.basename(
                                                      member_name))
                            extra += 1
                print(f"[subset] sdk-api scope=modules: +{extra:,} pages from "
                      f"{len(modules)} modules")
            print(f"[subset] sdk-api pages: {len(pages):,} "
                  f"(shared API names: {len(shared):,})")
            for member_name, (kind, module, fn) in sorted(pages.items()):
                dest = os.path.join(CORPUS, "win32", "api", module, fn)
                if apply:
                    extract_member(tar, member_name, dest)
                written.append(dest)
        else:
            for member in iter_blobs(tar, root, meta["subdir"]):
                rel = os.path.relpath(member.name,
                                      f"{root}/{meta['subdir']}")
                folder = rel.split(os.sep)[0]
                if folder not in GUIDE_FOLDERS:
                    continue
                dest = os.path.join(CORPUS, "win32", "guide", rel)
                if apply:
                    extract_member(tar, member.name, dest)
                written.append(dest)

        if apply:
            copy_licenses(tar, root, source)

    total = sum(os.path.getsize(p) for p in written if os.path.exists(p))
    print(f"[subset] {source}: {len(written):,} pages, "
          f"{total / 1048576:.1f} MB -> corpus/win32/")
    return written


def copy_licenses(tar, root, source):
    meta = UPSTREAM[source]
    dest_dir = os.path.join(SOURCES, meta["repo"].split("/")[1])
    os.makedirs(dest_dir, exist_ok=True)
    for name in meta["license"]:
        member_name = f"{root}/{name}"
        try:
            member = tar.getmember(member_name)
        except KeyError:
            continue
        data = tar.extractfile(member).read()
        with open(os.path.join(dest_dir, name), "wb") as fh:
            fh.write(data)


def extract_member(tar, member_name, dest):
    member = tar.getmember(member_name)
    os.makedirs(os.path.dirname(dest), exist_ok=True)
    with tar.extractfile(member) as src, open(dest, "wb") as out:
        shutil.copyfileobj(src, out)


# ------------------------------------------------------------------ pack
def build_pack(source, tar_path):
    meta = UPSTREAM[source]
    dest = os.path.join(SOURCES, f"{meta['repo'].split('/')[1]}-"
                                 f"{meta['sha'][:12]}-md.tar.gz")
    count = 0
    with open_tarball(tar_path) as tar, tarfile.open(dest, "w:gz") as out:
        root = tarball_root(tar)
        for member in iter_blobs(tar, root, meta["subdir"]):
            data = tar.extractfile(member).read()
            info = tarfile.TarInfo(
                member.name[len(root) + 1:])          # drop the repo prefix
            info.size = len(data)
            info.mtime = 0
            out.addfile(info, io.BytesIO(data))
            count += 1
    print(f"[pack] {dest}: {count:,} pages, "
          f"{os.path.getsize(dest) / 1048576:.1f} MB")
    return dest


# ------------------------------------------------------------------ main
def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("mode", nargs="?", default="subset",
                    choices=["subset", "pack", "list"])
    ap.add_argument("--source", default="all",
                    choices=["all", *UPSTREAM])
    ap.add_argument("--tarball", help="use a local snapshot instead of "
                                      "downloading (per --source)")
    ap.add_argument("--cache-dir", default=os.path.join(ROOT, ".cache",
                                                        "upstream"))
    ap.add_argument("--scope", default="modules",
                    choices=["shared", "modules"],
                    help="sdk-api: shared API names only, or whole modules "
                         "that contain them (default: modules)")
    args = ap.parse_args()

    sources = list(UPSTREAM) if args.source == "all" else [args.source]
    for source in sources:
        tar_path = args.tarball or os.path.join(
            args.cache_dir, f"{source}-{UPSTREAM[source]['sha'][:12]}.tar.gz")
        if not args.tarball and not os.path.exists(tar_path):
            download(source, tar_path)
        if args.mode == "list":
            with open_tarball(tar_path) as tar:
                root = tarball_root(tar)
                if source == "sdk-api":
                    pages, names, shared = shared_api_names(
                        tar, root, UPSTREAM[source]["subdir"], load_catalogs())
                    if args.scope == "modules":
                        modules = {mod for _k, mod, _n in pages.values()}
                        for entries in names.values():
                            for _k, mod, member in entries:
                                if mod in modules:
                                    pages.setdefault(member, None)
                    print(f"{source}: would extract {len(pages):,} pages "
                          f"({len(shared):,} shared API names, "
                          f"scope={args.scope})")
                else:
                    n = 0
                    for member in iter_blobs(tar, root,
                                             UPSTREAM[source]["subdir"]):
                        rel = os.path.relpath(
                            member.name,
                            f"{root}/{UPSTREAM[source]['subdir']}")
                        if rel.split(os.sep)[0] in GUIDE_FOLDERS:
                            n += 1
                    print(f"{source}: would extract {n:,} guide pages "
                          f"from {len(GUIDE_FOLDERS)} folders")
            continue
        if args.mode == "pack":
            build_pack(source, tar_path)
        else:
            extract_subset(source, tar_path, apply=True, scope=args.scope)
    return 0


if __name__ == "__main__":
    sys.exit(main())
