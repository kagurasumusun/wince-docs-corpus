#!/usr/bin/env python3
"""A small ISO 9660 reader (with Joliet and the common extensions).

The media under ``sources/`` are often CD images (``.iso``), and the working
environment this corpus is maintained from has no 7z, so this module reads an
ISO 9660 image in pure Python.  It is used by ``tools/import-media.py`` to
list and to extract the documentation files of such a medium - nothing else is
imported, and the medium itself stays untouched.

    python3 tools/iso9660.py sources/windows-ce-2.0-sdk/MPLATSDK.20.ISO
    python3 tools/iso9660.py <iso> --grep "\.hlp$"
    python3 tools/iso9660.py <iso> --extract docs/ --out /tmp/iso-out

Only the directory tree is parsed (Primary and Joliet Supplementary Volume
Descriptors, and Rock Ridge's ``NM`` names when present); multi-extent files
and UDF are not supported, which is fine for these 1990s CD images.
"""

import argparse
import os
import re
import struct
import sys

SECTOR = 2048
VD_OFFSET = 16 * SECTOR
VD_PRIMARY = 1
VD_SUPPLEMENTARY = 2
VD_TERMINATOR = 255


class Entry:
    """One file (or directory) of the image."""

    __slots__ = ("path", "is_dir", "lba", "size", "name")

    def __init__(self, path, is_dir, lba, size, name):
        self.path = path
        self.is_dir = is_dir
        self.lba = lba
        self.size = size
        self.name = name

    def __repr__(self):
        kind = "dir " if self.is_dir else "file"
        return f"<{kind} {self.path} ({self.size} bytes)>"


class ISO9660:
    def __init__(self, path):
        self.path = path
        self.entries = []
        self.volume_name = ""
        with open(path, "rb") as fh:
            self._read_volumes(fh)

    # -- volume descriptors --------------------------------------------------
    def _read_volumes(self, fh):
        primary = joliet = None
        for index in range(32):
            fh.seek(VD_OFFSET + index * SECTOR)
            sector = fh.read(SECTOR)
            if len(sector) < 7:
                break
            kind = sector[0]
            if kind == VD_TERMINATOR:
                break
            if kind not in (VD_PRIMARY, VD_SUPPLEMENTARY):
                continue
            escape = sector[88:91]
            # UDF bridged discs (Windows install media) describe their files in
            # UDF, not ISO 9660; when the escape sequences say "no Joliet" the
            # plain record is still the best this reader can do.
            if kind == VD_PRIMARY:
                primary = sector
            elif kind == VD_SUPPLEMENTARY and escape.startswith(b"%/"):
                joliet = sector
        record = joliet or primary
        if record is None:
            raise ValueError("no ISO 9660 volume descriptor found")
        self.joliet = joliet is not None
        self.volume_name = record[40:72].decode("utf-8", "replace").strip()
        root = self._parse_record(record[156:190], "", 0, root=True)
        if root is None:
            raise ValueError("the image has no root directory record")
        self._read_tree(root, fh)

    # -- records -------------------------------------------------------------
    def _decode(self, raw):
        if self.joliet:
            return raw.decode("utf-16-be", "replace")
        return raw.decode("cp437", "replace")

    def _parse_record(self, record, parent, index, root=False):
        length = record[0]
        if length < 34:
            return None
        lba = struct.unpack_from("<I", record, 2)[0]
        size = struct.unpack_from("<I", record, 10)[0]
        flags = record[25]
        name_len = record[32]
        raw_name = record[33:33 + name_len]
        if name_len == 1 and raw_name in (b"\x00", b"\x01") and not root:
            return None                      # "." and ".." entries
        if root:
            return Entry("", True, lba, size, "")
        name = self._decode(raw_name).split(";")[0]
        return Entry(os.path.join(parent, name) if parent else name,
                     bool(flags & 0x02), lba, size, name)

    def _read_tree(self, root, fh):
        stack = [root]
        seen = set()
        while stack:
            directory = stack.pop()
            if directory.path in seen:
                continue
            seen.add(directory.path)
            for entry in self._read_directory(fh, directory):
                self.entries.append(entry)
                if entry.is_dir:
                    stack.append(entry)

    def _read_directory(self, fh, directory):
        fh.seek(directory.lba * SECTOR)
        data = fh.read(directory.size)
        entries = []
        offset = 0
        while offset < len(data):
            length = data[offset]
            if length == 0:
                # records do not cross a sector boundary
                offset = (offset // SECTOR + 1) * SECTOR
                continue
            record = data[offset:offset + length]
            entry = self._parse_record(record, directory.path, offset)
            if entry is not None:
                entries.append(entry)
            offset += length
        return entries

    # -- public helpers ------------------------------------------------------
    def find(self, pattern, directories_only=False):
        regex = re.compile(pattern, re.I)
        for entry in self.entries:
            if directories_only and not entry.is_dir:
                continue
            if regex.search(entry.path):
                yield entry

    def read(self, entry):
        with open(self.path, "rb") as fh:
            fh.seek(entry.lba * SECTOR)
            return fh.read(entry.size)

    def extract(self, entry, out_dir):
        target = os.path.join(out_dir, entry.path)
        os.makedirs(os.path.dirname(target) or out_dir, exist_ok=True)
        with open(target, "wb") as fh:
            fh.write(self.read(entry))
        return target

    def inventory(self):
        """ext -> (count, bytes), and the total."""
        counts = {}
        for entry in self.entries:
            if entry.is_dir:
                continue
            ext = os.path.splitext(entry.name)[1].lower() or "(none)"
            number, size = counts.get(ext, (0, 0))
            counts[ext] = (number + 1, size + entry.size)
        return counts


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("iso")
    ap.add_argument("--grep", help="only entries whose path matches this regex")
    ap.add_argument("--extract", help="directory prefix to extract")
    ap.add_argument("--out", help="where to extract (with --extract)")
    args = ap.parse_args()

    image = ISO9660(args.iso)
    print(f"{args.iso}: volume {image.volume_name!r}, "
          f"{'Joliet' if image.joliet else 'ISO 9660'} names, "
          f"{len(image.entries):,} entries")
    counts = image.inventory()
    print(f"{'ext':10s} {'files':>7s} {'MiB':>8s}")
    for ext, (number, size) in sorted(counts.items(),
                                      key=lambda kv: -kv[1][1])[:20]:
        print(f"{ext:10s} {number:7,d} {size / 1024 / 1024:8.2f}")

    if args.grep:
        found = list(image.find(args.grep))
        print(f"\n{len(found):,} entries match {args.grep!r}:")
        for entry in found[:80]:
            kind = "dir " if entry.is_dir else "file"
            print(f"  {kind} {entry.path}  {entry.size:,}")
    if args.extract:
        if not args.out:
            ap.error("--extract needs --out")
        chosen = [e for e in image.entries if not e.is_dir
                  and e.path.lower().startswith(args.extract.lower())]
        for entry in chosen:
            image.extract(entry, args.out)
        print(f"\nextracted {len(chosen):,} files to {args.out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
