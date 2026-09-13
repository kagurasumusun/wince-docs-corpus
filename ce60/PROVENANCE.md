# Windows CE 6.0 documents — provenance

## Source (official Microsoft media, preserved by the Internet Archive)

* Item: `en_windows_embedded_ce_6.0_dvd` — "Windows Embedded CE 6.0 English"
* URL: https://archive.org/details/en_windows_embedded_ce_6.0_dvd
* ISO: `en_windows_embedded_ce_6.0_dvd.iso` (4,080,269,312 bytes; UDF;
  Microsoft; 2006-09-12)
* Collected: 2026-09-14 (JST).

## Contents (documents only)

* `release notes.htm` — the CE 6.0 disc release notes (the only CE 6.0
  document on the DVD).

## What the CE 6.0 DVD does NOT contain (important finding)

The DVD carries 363 `CE_*`/`tools_*`/`wcetk_*` CABs (the OS catalog,
host tools, and the Windows CE Test Kit), `ActiveSync_4.2`, and setup
files. A full listing of every CAB found **no documentation CHM/HTM set** —
only three host-tool `.hlp` files (mc.hlp, rc.hlp, samplestressdll.hlp,
which are desktop host-tool help, not CE API reference).

So the CE 6.0 API reference is **not on the product DVD**. It ships through
the Platform Builder 6.0 documentation installed into the Visual Studio
2005 help collection, and it is already collected in `pages6/` from the
official Learn `previous-versions/windows/embedded` CE 6.0 pages. The
.NET Compact Framework 3.5 reference (CE 6.0 R3) is tracked in the .NET
catalog (`catalog-netfx-35.tsv` / `cf-surface.tsv`).

Documents-only policy (wince-api docs/iso-collection.md): the CAB payloads
are OS binaries/tools and were not preserved.
