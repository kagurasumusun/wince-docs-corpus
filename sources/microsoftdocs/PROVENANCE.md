# MicrosoftDocs snapshots — provenance

The Win32 half of this corpus comes from Microsoft's public documentation
repositories on GitHub. Both are CC-BY-4.0 (see the `LICENSE` file copied into
each subdirectory) with MIT-licensed tooling (`LICENSE-CODE`).

## `sdk-api/` — Win32 API reference

* Repository: <https://github.com/MicrosoftDocs/sdk-api>
* Commit: `c12073e417d5780fe796278ada21b90cef1b0568` (2026-09-30, branch `docs`)
* Snapshot: `sources/microsoftdocs/sdk-api-c12073e417d5-md.tar.gz`
  (65,910 markdown pages, 29.3 MB, `.md` only — no images)
* Full upstream tree: 65,911 `.md` pages under `sdk-api-src/content/`
  (1,336 `index.md`/`TOC.md` navigation files excluded from the snapshot).

Tarball layout: `sdk-api-src/content/<module>/<kind>-<module>-<name>.md`
with `nf` = function, `ns` = structure, `ne` = enumeration, `nc` = callback,
`ni` = interface, `nn` = namespace, `nl` = library, `na` = attribute.

### What was extracted into the corpus

`corpus/win32/api/<module>/<page>.md` — **17,095 pages** in two rings:

* **5,219 pages** for the **5,009 API names** that also appear in the Windows
  CE catalogs (`data/catalogs/windows-ce-*.tsv`), including the `A`/`W`
  variants of a shared base name (`CreateFileW` is included because Windows CE
  documents `CreateFile`). This is the "Win32-common" API surface of CE.
* **11,876 pages** that are the remaining content of the 183 modules those
  shared names live in (`--scope modules`, the default), so the enums,
  structs, callbacks and interfaces that accompany a shared function are
  present. `data/reports/win32-imported.tsv` marks each page `ce_shared`.

Page-by-page extraction stops at those 183 modules on purpose: importing all
65,911 sdk-api pages would more than double this repository with desktop-only
material (DirectX, WMI, AD schema, …). The snapshot tarball next to this file
*is* complete — unpack it with:

```bash
python3 tools/fetch-upstream.py pack --source sdk-api   # rebuild the snapshot
tar -xzf sources/microsoftdocs/sdk-api-*-md.tar.gz      # or just unpack
```

Re-running `tools/fetch-upstream.py subset --source sdk-api` regenerates
`corpus/win32/api/` from the pinned commit.

## `win32/` — Win32 programming guides

* Repository: <https://github.com/MicrosoftDocs/win32>
* Commit: `e103fa4e8810bd8d42c4777e17081e24dbe62dbd` (2026-09-15, branch `docs`)
* Upstream tree: 48,212 `.md` pages under `desktop-src/` (plus images).

Only the guide folders for subsystems Windows CE also implements are
extracted, into `corpus/win32/guide/<folder>/` — **2,070 pages** from
`FileIO`, `Memory`, `Sync`, `ProcThread`, `ipc`, `Dlls`, `Debug`, `DevIO`,
`SysInfo`, `Power`, `Services`, `gdi`, `menurc`, `dlgbox`, `WinMsg`,
`inputdev`, `WinSock`, `NetMgmt`, `Bluetooth` (see `GUIDE_FOLDERS` in
`tools/fetch-upstream.py`).

Desktop-only areas (DirectX, WMI/CIM, Active Directory schema, Hyper-V,
MSI, Ribbon, ADSI, TAPI, printing, …) are deliberately not extracted:
Windows CE has no counterpart, and their ~46,000 pages would dwarf the CE
material. They remain one tarball away in the upstream repository.

## License and attribution

* Documentation: CC-BY-4.0, © Microsoft Corporation — attribution is provided
  by keeping the upstream `LICENSE` files in `sdk-api/` and `win32/`.
* Tooling in the upstream repositories: MIT.

## Why not just link to learn.microsoft.com?

`learn.microsoft.com/en-us/windows/win32/` serves exactly these pages, but the
same URL space and page ids change over time, and this corpus is meant to be
usable offline. The GitHub repositories are the source of truth behind Learn
and are versioned, so a pinned commit gives a reproducible snapshot.
