# corpus/msdn-library/wcedevcon-99 — provenance

* Internet Archive item: <https://archive.org/details/windowscedevcon99conferencecd>
* Title: Windows CE Developers Conference DevCon 99 Conference CD
* Creator / date: Microsoft Corporation / 1999-05-24
* Collected: 2026-10-03 by tools/import-media.py (via .github/workflows/import-media.yml);
  re-imported 2026-10-04 with the exclusions below (queues/media.tsv).

| File | Bytes | md5 (Internet Archive) | URL |
|------|------:|------------------------|-----|
| `Windows CE Developers Conference DevCon 99 Conference CD (Microsoft Corporation)(1999).iso` | 338,046,976 | `37dc2148539cdd7a7acdcf3c29c244ed` | https://archive.org/download/windowscedevcon99conferencecd/Windows%20CE%20Developers%20Conference%20DevCon%2099%20Conference%20CD%20%28Microsoft%20Corporation%29%281999%29.iso |

The medium itself is **not** kept in this repository: .github/workflows/import-media.yml
downloads it to a scratch directory, imports the documentation pages of the
tree above and discards the image. Binaries, headers, samples and toolchains
are not part of this corpus - see "What is collected" in the top-level
README.

## What was imported — and what was refused

The disc carries the Windows CE 2.11/2.12 SDK, DDK and Platform Builder
documentation (6,382 pages) next to the conference's own material. Only the
documentation of the product is imported; the exclude regex in
`queues/media.tsv` refuses:

| Refused | What it is |
|---------|------------|
| `Windows_CE_Developers_Conference_DevCon_99_Conference_CD/` (839 pages) | the conference's sponsors' pages (Kingston, Casio, Compaq, Hitachi, … press releases and product sheets), the Win32/ATL sample trees with their readme/help pages, and the FrontPage site (`qworks/`) |
| `MPLAYER2/` (174 pages) | the Books Online of the desktop Windows Media Player 2 (`mplayer2.hlp`) |
| `MPSUPP/` (3 pages) | Microsoft Product Support Services - generic support pages, not CE documentation |
| `ACCESSIB/` (6 pages) | Microsoft's general accessibility material |
| `Handhelds/` (29 pages) | a vendor's Compal/Compaq Palm-size PC specification sheets |
| `_vti_cnf/`, `_vti_pvt/`, `_derived/` (423 pages) | FrontPage metadata directories, refused by tools/import-media.py for every medium |

The first import (2026-10-03) did not have those exclusions and imported
7,437 pages, including all of the above; they were removed in the 2026-10
review (`docs/COLLECTION-POLICY.md`).

## What is in the tree

| Directory | Pages | Contents |
|-----------|------:|----------|
| `wcesdkr/` | 3,315 | Windows CE 2.11/2.12 SDK reference (API reference, release notes) |
| `wceapc/` | 995 | application-programming chapters (user interface, files, …) |
| `wceddk/` | 741 | device-driver kit documentation |
| `wcesdkg/` | 456 | SDK guides (debugging, tools, shell) |
| `wcecomm/` | 244 | communications (serial, sockets, TAPI, SSPI, …) |
| `wceui/` | 188 | user-interface documentation |
| `wcehpc/` | 143 | Handheld PC material |
| `wcecore/` | 91 | core OS topics |
| `wcesvcs/` | 86 | services |
| `wceppc/` | 70 | Palm-size PC material |
| `wcegloss/`, `wceglob/`, `wceintro/`, `wcelib/` | 53 | glossary, global topics, introduction, library notes |
