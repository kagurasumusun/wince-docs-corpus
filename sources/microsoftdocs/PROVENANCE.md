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

`corpus/win32/api/<module>/<page>.md` — **5,279 pages**, the sdk-api pages
whose API name (or, for an `A`/`W` variant, whose base name) is an API name
Windows CE documents: 5,068 shared names. `CreateFileW` is included because
Windows CE documents `CreateFile`; `IDirectDrawVideo::CanUseOverlayStretch`
because CE 5.0 documents that interface method. Every page carries its CE
evidence in `data/reports/win32-imported.tsv` (`ce_sets`, `ce_page_ids`).

Nothing else is extracted. The 183-module "context ring" that an earlier
revision imported (11,819 desktop-only pages: the Shell, Windows Media,
DirectShow interfaces CE never had, WMI, …) is gone: those pages document
desktop Windows, not the part of Win32 that Windows CE shares.
`data/win32-exclude.tsv` lists the reviewed exceptions — the two name
coincidences (CE's `Run (Windows Media Player)` vs. the printer-driver `RUN`
structure; the CE 3.0 DDK's device-driver `Address` vs. the dbghelp `ADDRESS`
structure) and the seven modules whose APIs CE never had (Windows Runtime,
Direct2D, the shim `TAG` macro, Windows Contacts, the desktop Task Scheduler,
Core Audio, display cloning). `tools/check-policy.py` fails if a page that CE does
not document appears under `corpus/win32/`.

The name list is built by `tools/ce_api_names.py` from `data/catalogs/*.tsv`
plus the names mined from the CE sets without a catalog, and is printed for
review in `data/reports/ce-api-names.tsv`.

The snapshot tarball next to this file is **complete** (all 65,910 pages), so
the corpus can be re-derived — or a wider extraction attempted — offline:

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
* **Not part of the corpus.** The guides describe desktop Windows (transactional
  NTFS, change journals, the desktop service control manager, …), so they are
  not Windows CE documentation. Only the `LICENSE` files are kept here, for
  attribution.
* For an offline copy of the guide folders of the subsystems CE implements
  (`FileIO`, `Memory`, `Sync`, `ProcThread`, `ipc`, `Dlls`, `Debug`, `DevIO`,
  `SysInfo`, `Power`, `Services`, `gdi`, `menurc`, `dlgbox`, `inputdev`,
  `WinSock`, `NetMgmt`, `Bluetooth`, `SecCrypto`, `com` — see `GUIDE_FOLDERS`
  in `tools/fetch-upstream.py`), extract them outside the repository:

  ```bash
  python3 tools/fetch-upstream.py guides --out .cache/win32-guides
  ```

## License and attribution

* Documentation: CC-BY-4.0, © Microsoft Corporation — attribution is provided
  by keeping the upstream `LICENSE` files in `sdk-api/` and `win32/`.
* Tooling in the upstream repositories: MIT.

## Why not just link to learn.microsoft.com?

`learn.microsoft.com/en-us/windows/win32/` serves exactly these pages, but the
same URL space and page ids change over time, and this corpus is meant to be
usable offline. The GitHub repositories are the source of truth behind Learn
and are versioned, so a pinned commit gives a reproducible snapshot.
