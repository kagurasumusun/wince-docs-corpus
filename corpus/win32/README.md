# corpus/win32/

The **Win32-common** half of the documentation: pages from Microsoft's public
Win32 documentation repositories on GitHub that Windows CE shares, kept next
to the CE-specific material so that the two halves of any API question are in
one place.

```
corpus/win32/
├── api/<module>/<page>.md     Win32 API reference (17,095 pages)
└── guide/<folder>/<page>.md   Win32 programming guides (3,357 pages)
```

20,452 pages in total — `api/` covers **every page of the 183 sdk-api modules
that document at least one CE-shared API**, so the structs, enums, callbacks
and interfaces used together with a shared function are present as well.
`data/reports/win32-imported.tsv` marks each page `ce_shared = yes/no`
(5,219 pages are CE-shared, 11,876 are module context).

Format is the upstream markdown (YAML front matter with `title`, `description`,
`helpviewer_keywords`, `ms.assetid`, …) — not HTML like the rest of the corpus.
The upstream commit, licenses and the complete snapshots are documented in
`sources/microsoftdocs/PROVENANCE.md`; extraction is reproducible with
`python3 tools/fetch-upstream.py subset --source sdk-api|win32`.

## api/ — 17,095 pages, 183 modules

Two rings of pages, both from `MicrosoftDocs/sdk-api`:

* **CE-shared (5,219 pages, 5,009 API names).** Every page whose name also
  occurs in a Windows CE catalog (`data/catalogs/*.tsv`), including `A`/`W`
  variants of a shared base name — Windows CE documents `CreateFile`, so
  `CreateFileA` and `CreateFileW` are both included. These are the APIs the
  two platforms have in common; `data/reports/win32-shared.tsv` maps each name
  to its CE page ids and its Win32 page.
* **Module context (11,876 pages).** Every remaining page of the modules those
  shared APIs live in (`winbase`, `wingdi`, `winuser`, `winsock2`, `wincrypt`,
  `strmif`, `commctrl`, `shobjidl_core`, …). They provide the surrounding API
  surface — e.g. `CRYPT_*` alongside the shared `CryptAcquireContext`, the
  DirectShow interfaces alongside the CE DirectShow pages.

| kind | pages | example |
|------|------:|---------|
| `nf` function | 4,232 | `api/fileapi/nf-fileapi-createfilew.md` |
| `ns` structure/union | 813 | `api/minwinbase/ns-minwinbase-overlapped.md` |
| `ne` enumeration | 69 | `api/wingdi/ne-wingdi-bi_compression.md` |
| `nn` namespace/topic | 64 | Winsock/COM namespaces |
| `nc` callback | 26 | `api/libloaderapi/nc-libloaderapi-enumresnametypew.md` |
| `nl` library | 10 | `api/` static library notes |
| `ni` interface | 5 | `api/combaseapi/nf-combaseapi-cocreateinstance.md` |

The join key is the normalised title in the catalogs
(`CreateFile (Windows CE 5.0)` → `createfile`), so a page here pairs with the
CE page in `corpus/learn/<set>/`. Note that CE documents many of these APIs
only as part of `corpus/chm/windows-ce-3.0/` (CE 3.0) and
`corpus/learn/windows-ce-5.0/`.

## guide/ — 3,357 pages, 20 folders

Programming guides for the subsystems CE implements. CE's own documentation is
reference-heavy and thin on concepts, so these generic Win32 guides are the
closest thing to the "how it works" chapters of the CE platform docs:

| folder | pages | topic |
|--------|------:|-------|
| `SecCrypto` | 835 | CryptoAPI: providers, hashes, certificates, CNG |
| `com` | 452 | COM: apartments, marshalling, registration, monikers |
| `WinSock` | 363 | Winsock 2 programming model, overlapped I/O |
| `gdi` | 337 | GDI objects, mapping modes, painting |
| `menurc` | 220 | menus and resources (GWES) |
| `FileIO` | 195 | files, volumes, reparse points, transactional NTFS (not on CE) |
| `Debug` | 121 | debugging API |
| `SysInfo` | 99 | system information |
| `NetMgmt` | 84 | network management |
| `inputdev` | 80 | keyboard/mouse/tablet input (GWES) |
| `dlgbox` | 73 | dialog boxes (GWES) |
| `Memory` | 72 | virtual memory, heaps |
| `ProcThread` | 68 | processes and threads |
| `DevIO` | 66 | device I/O, IOCTLs |
| `Services` | 64 | services (CE services model differs) |
| `Power` | 61 | power management (CE power manager differs — use CE pages) |
| `ipc` | 57 | pipes/mailslots/RPC basics |
| `Sync` | 46 | events, mutexes, semaphores, wait functions |
| `Bluetooth` | 39 | Bluetooth stack |
| `Dlls` | 23 | DLL loading |

(CryptoAPI and COM are part of the CE platform, so their guides are included;
two sdk-api pages that upstream keeps inside guide folders —
`Dlls/unknown/nf-unknown-dllgetdocumentation.md`,
`inputdev/winuser/nf-winuser-setmaxtouchpadsensitivity.md` — come along.)

## Caveats

* These are **desktop Win32** pages. They describe the full Windows API, which
  is a superset of what Windows CE implements — a page here is a *reference*,
  not proof that a given CE version has the API. The CE page (in
  `corpus/learn/<set>/`) or the CE 3.0 CHM topic is the authority on that;
  where the two disagree, the CE page wins. Typical divergences: transactional
  NTFS and reparse points (not on CE), the services/power models, and anything
  introduced after CE 6.0.
* File names keep the upstream `nf-`/`ns-`/`ne-` prefixes, so a page can be
  traced back to the upstream snapshot without a mapping file.
* The pages carry upstream front matter (`ms.assetid`, `helpviewer_keywords`,
  `old-location`) — useful for matching a topic to old MSDN/CHM ids.
  `data/index/INDEX.tsv` and the SQL index include these pages with ids such as
  `nf-fileapi-createfilew` and book `win32/api/fileapi`.
* Not everything here is on CE: `--scope modules` brings in desktop-only pages
  of a shared module (transactional NTFS, `SERVICE_*`, DirectShow filters that
  CE never had). `data/reports/win32-imported.tsv` says which is which.
