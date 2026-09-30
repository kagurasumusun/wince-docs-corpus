# Windows CE 5.0 documentation — provenance

## Source (official Microsoft media, preserved by the Internet Archive)

* Item: `en_win_ce_net_cd1` — "Windows Embedded CE 5.0 CD1 English"
* URL: https://archive.org/details/en_win_ce_net_cd1
* ISO: `en_win_ce_net_cd1.iso` (533,657,600 bytes; Microsoft; 2004-07-02)
* Collected: 2026-09-14 (JST).

## Contents (documents only)

`ce50/` holds the **official Windows CE 5.0 component documentation CHM
set** (98 CHMs, ~33 MB) extracted from `PB_1.cab` on CD1, plus the disc
`release notes.htm` / `whatsnew.html`. Each `wce*5.chm` is the CE 5.0
documentation for one OS component — e.g.:

* `P312_wcecore5.chm`   — core OS services (registry, CELog, event logging…)
* `P404_wcewinsock5.chm` — Winsock
* `P314_wcecrypto5.chm` — CryptoAPI
* `P324_wceedb5.chm` / `P326_wcefiledb5.chm` — EDB / CEDB database APIs
* `P316_wcedcom5.chm`, `P320_wcedshow5.chm`, `P391_wceui5.chm`, …
* `P302`…`P407` cover access/ACM/ActiveSync/ASP/auth/Bluetooth/certs/…/XMLDOM.

Each CHM interleaves concepts (`wce50con*`) and API reference
(`wce50grf*`, `wce50lrf*`) pages — the same content Learn serves as the
CE 5.0 pages already in `pages5/`, but as the official offline source.

## Not collected (per documents-only policy)

* `CE_1.cab`/`CE_2.cab`/`Data1.cab` — OS binaries, host tools, emulator
  image, remote tools (binaries; also `EMULATOR.CHM`/`REMTOOLS.CHM` are the
  same emulator/tool help already collected under `ce42/`).
* `dotnetfx.exe` — .NET Framework 2.0 host redistributable (binary).
* The host SDK `.hlp` files in `CE_2.cab` (errlook/mc/oletools/rc/shed/
  tstcon32) — desktop host-tool help, not CE documentation.
* CDs 2–6 were not downloaded: CD1's installer payload is the only doc
  carrier; the remaining discs are the OS catalog / shared-source volume.
