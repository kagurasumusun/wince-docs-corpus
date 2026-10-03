#!/usr/bin/env python3
"""tools/fetch-upstream.py -- import the Win32-common documentation.

Windows CE implements a subset of the Win32 API, and Microsoft publishes the
sources of the Win32 documentation on GitHub.  Those pages are the
authoritative reference for the "Win32-common" half of this corpus:

  MicrosoftDocs/sdk-api   Win32 API reference (function/structure/enum pages)
  MicrosoftDocs/win32     Win32 programming guides (desktop-src/*)

Both repositories are CC-BY-4.0 (LICENSE) with MIT-licensed tooling
(LICENSE-CODE); the license files are copied next to the extracted material.

What this script can do
-----------------------

1. ``subset`` (default) -- extract the CE-shared API reference pages into
   ``corpus/win32/api/``::

       python3 tools/fetch-upstream.py subset --source sdk-api

   *Every* page of ``MicrosoftDocs/sdk-api`` whose API name Windows CE also
   documents (``tools/ce_api_names.py``) is imported, including the ANSI and
   Unicode variants of a shared base name (Windows CE documents ``CreateFile``,
   so ``CreateFileA`` and ``CreateFileW`` both come along).  Nothing else is:
   the desktop-only context of those modules (WMI, DirectX, the Shell, Windows
   Media, WinRT, ...) is *not* CE documentation and stays out.  The importer
   also refuses the modules named in ``data/win32-exclude.tsv``.

   That is the whole rule, and it is checkable: every markdown file under
   ``corpus/win32/`` carries a name that occurs in
   ``data/reports/ce-api-names.tsv`` (``tools/check-policy.py`` enforces it).

2. ``guides`` -- the programming guides of ``MicrosoftDocs/win32`` are desktop
   documentation (they describe transactional NTFS, change journals, the
   desktop service control manager, ...), so they are **not** part of the
   corpus.  They can still be extracted as an offline extra, outside the
   repository::

       python3 tools/fetch-upstream.py guides --out .cache/win32-guides

   ``--out`` defaults to ``.cache/win32-guides`` (git-ignored).  Do not point
   it at ``corpus/`` -- ``tools/check-policy.py`` reports desktop material
   there.

3. ``pack`` -- store a complete upstream snapshot as a single compressed
   tarball under ``sources/microsoftdocs/`` (markdown only, no images), so the
   full set can be unpacked offline later::

       python3 tools/fetch-upstream.py pack --source sdk-api

4. ``list`` -- show what a ``subset`` run would extract, without writing
   anything.

Network access
--------------

Downloads use ``codeload.github.com`` (tarball of a pinned commit).  If the
machine has no outbound network, pass ``--tarball`` with a snapshot that was
downloaded elsewhere; every mode works from a local tarball.

Usage
-----

    python3 tools/fetch-upstream.py list
    python3 tools/fetch-upstream.py subset --source sdk-api
    python3 tools/fetch-upstream.py guides --out .cache/win32-guides
    python3 tools/fetch-upstream.py pack --source sdk-api
    python3 tools/fetch-upstream.py subset --source sdk-api --tarball sdk-api.tar.gz
"""

import argparse
import collections
import io
import os
import re
import shutil
import sys
import tarfile
import urllib.request

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import ce_api_names  # noqa: E402

ROOT = ce_api_names.ROOT
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

# sdk-api page kinds; the pattern lives in tools/ce_api_names.py so that the
# importer and tools/check-policy.py cannot drift apart.
SDK_PAGE = ce_api_names.SDK_PAGE

# Programming-guide folders of MicrosoftDocs/win32 (desktop-src/) that document
# subsystems Windows CE also implements.  Used by the `guides` mode only - see
# the docstring: these pages are desktop documentation and not part of the
# corpus.
GUIDE_FOLDERS = (
    # core OS
    "FileIO", "Memory", "Sync", "ProcThread", "ipc", "Dlls", "Debug",
    "DevIO", "SysInfo", "Power", "Services",
    # windowing / GWES
    "gdi", "menurc", "dlgbox", "inputdev",
    # networking
    "WinSock", "NetMgmt", "Bluetooth",
    # security and COM: both are part of the CE platform (CryptoAPI, COM)
    "SecCrypto", "com",
)

# Deliberately not extracted by `guides` either: ``lwef`` ("Legacy Windows
# Environment Features", deprecated Windows Desktop Search 2.x), ``WES``
# (Windows Embedded Standard, a different product line), the
# DirectX/WMI/ADSchema/HyperV/... trees (no CE counterpart) and
# ``windows-driver-docs`` (WDM/KMDF drivers, a different driver model from CE).

GUIDE_OUT = os.path.join(ROOT, ".cache", "win32-guides")


# ------------------------------------------------------------------ helpers
def load_catalogs():
    """Kept for callers that predate tools/ce_api_names.py."""
    return ce_api_names.load_catalogs()


def normalize(text):
    return ce_api_names.normalize(text)


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


def tarball_root(tar, subdir):
    """The prefix that holds ``subdir`` in a codeload tarball or a snapshot.

    A codeload tarball has one top-level directory (``sdk-api-<sha>/``), while
    a snapshot written by ``pack`` has the repository prefix stripped
    (``sdk-api-src/content/...``).  Both are accepted; the returned value is
    ``""`` for a packed snapshot.
    """
    names = [name for name in tar.getnames() if name]
    tops = {name.split("/")[0] for name in names}
    if len(tops) == 1:
        root = tops.pop()
        if any(name.startswith(f"{root}/{subdir}/") for name in names):
            return root
    if any(name.startswith(f"{subdir}/") for name in names):
        return ""
    raise SystemExit(f"{subdir} not found in {getattr(tar, 'name', 'tarball')}")


def join(root, *parts):
    return "/".join(p for p in (root,) + parts if p)


def iter_blobs(tar, root, prefix):
    base = join(root, prefix) + "/"
    for member in tar:
        if not member.isfile():
            continue
        if not member.name.startswith(base):
            continue
        if not member.name.lower().endswith(".md"):
            continue
        yield member


# ------------------------------------------------------------------ subset
def shared_api_pages(tar, root, subdir, names, excluded):
    """Return {member_name: page file name} for the CE-shared API pages.

    A page belongs in the corpus when Windows CE documents its API name - or,
    for an ``A``/``W`` variant, the base name (``CreateFileW`` -> the
    CE-documented ``CreateFile``).  Pages of an excluded module
    (``data/win32-exclude.tsv``) never do.
    """
    pages = {}
    skipped_module = collections.Counter()
    for member in iter_blobs(tar, root, subdir):
        fn = os.path.basename(member.name)
        match = SDK_PAGE.match(fn)
        if not match:
            continue
        _kind, module, name = match.groups()
        if ce_api_names.module_excluded(module, excluded):
            skipped_module[module] += 1
            continue
        if ce_api_names.documented(ce_api_names.normalize(name), names):
            pages[member.name] = fn
    for module, count in skipped_module.most_common():
        print(f"[subset] excluded module {module}: {count} page(s) "
              f"(data/win32-exclude.tsv)")
    return pages


def extract_subset(source, tar_path, apply, names):
    meta = UPSTREAM[source]
    excluded = ce_api_names.load_excluded()
    written = []
    with open_tarball(tar_path) as tar:
        root = tarball_root(tar, meta["subdir"])
        if source != "sdk-api":
            raise SystemExit(
                "only --source sdk-api is imported; the win32 guides are "
                "desktop material - use `guides --out <dir>` to extract them "
                "outside the corpus")
        pages = shared_api_pages(tar, root, meta["subdir"], names, excluded)
        print(f"[subset] sdk-api: {len(pages):,} CE-shared pages of "
              f"{len(names):,} CE-documented API names")
        for member_name, fn in sorted(pages.items()):
            module = SDK_PAGE.match(fn).group(2)
            dest = os.path.join(CORPUS, "win32", "api", module, fn)
            if apply:
                extract_member(tar, member_name, dest)
            written.append(dest)
        if apply:
            copy_licenses(tar, root, source)

    total = sum(os.path.getsize(p) for p in written if os.path.exists(p))
    print(f"[subset] {source}: {len(written):,} pages, "
          f"{total / 1048576:.1f} MB -> corpus/win32/api/")
    return written


def extract_guides(tar_path, out_dir):
    meta = UPSTREAM["win32"]
    written = []
    with open_tarball(tar_path) as tar:
        root = tarball_root(tar, meta["subdir"])
        for member in iter_blobs(tar, root, meta["subdir"]):
            rel = os.path.relpath(member.name, join(root, meta["subdir"]))
            if rel.split(os.sep)[0] not in GUIDE_FOLDERS:
                continue
            dest = os.path.join(out_dir, rel)
            extract_member(tar, member.name, dest)
            written.append(dest)
        copy_licenses(tar, root, "win32")
    print(f"[guides] {len(written):,} desktop guide pages -> {out_dir}")
    print("[guides] these describe desktop Windows, not Windows CE - keep them "
          "out of corpus/")
    return written


def copy_licenses(tar, root, source):
    meta = UPSTREAM[source]
    dest_dir = os.path.join(SOURCES, meta["repo"].split("/")[1])
    os.makedirs(dest_dir, exist_ok=True)
    for name in meta["license"]:
        member_name = join(root, name)
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
        root = tarball_root(tar, meta["subdir"])
        for member in iter_blobs(tar, root, meta["subdir"]):
            data = tar.extractfile(member).read()
            info = tarfile.TarInfo(
                member.name[len(root) + 1:] if root else member.name)
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
                    choices=["subset", "guides", "pack", "list"])
    ap.add_argument("--source", default="sdk-api",
                    choices=["sdk-api", "win32"],
                    help="sdk-api for the API reference (default); win32 is "
                         "only used by pack/guides")
    ap.add_argument("--tarball", help="use a local snapshot instead of "
                                      "downloading (per --source)")
    ap.add_argument("--out", default=GUIDE_OUT,
                    help=f"guides: output directory (default {GUIDE_OUT})")
    ap.add_argument("--cache-dir", default=os.path.join(ROOT, ".cache",
                                                        "upstream"))
    args = ap.parse_args()

    if args.mode == "guides":
        source = "win32"
    else:
        source = args.source

    tar_path = args.tarball or os.path.join(
        args.cache_dir, f"{source}-{UPSTREAM[source]['sha'][:12]}.tar.gz")
    if not args.tarball and not os.path.exists(tar_path):
        download(source, tar_path)

    if args.mode == "list":
        names = ce_api_names.load_names()
        with open_tarball(tar_path) as tar:
            root = tarball_root(tar, UPSTREAM[source]["subdir"])
            if source == "sdk-api":
                pages = shared_api_pages(tar, root, UPSTREAM[source]["subdir"],
                                         names, ce_api_names.load_excluded())
                print(f"{source}: would extract {len(pages):,} CE-shared pages "
                      f"of {len(names):,} CE-documented API names")
            else:
                n = 0
                root = tarball_root(tar, UPSTREAM[source]["subdir"])
                for member in iter_blobs(tar, root, UPSTREAM[source]["subdir"]):
                    rel = os.path.relpath(
                        member.name, join(root, UPSTREAM[source]["subdir"]))
                    if rel.split(os.sep)[0] in GUIDE_FOLDERS:
                        n += 1
                print(f"{source}: `guides` would extract {n:,} desktop pages "
                      f"to {args.out} (not into the corpus)")
        return 0

    if args.mode == "pack":
        build_pack(source, tar_path)
    elif args.mode == "guides":
        extract_guides(tar_path, args.out)
    else:
        extract_subset(source, tar_path, apply=True,
                       names=ce_api_names.load_names())
    return 0


if __name__ == "__main__":
    sys.exit(main())
