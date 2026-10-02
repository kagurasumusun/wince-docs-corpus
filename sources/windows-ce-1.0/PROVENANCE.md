# Windows CE 1.0 documentation — provenance

## Source (official Microsoft CD, preserved by the Internet Archive)

* Item: `ms-wince-desktopemulation-sdk-beta21`
  "Microsoft Windows CE 1.0 Desktop Emulation SDK - Beta 2.1"
* URL: https://archive.org/details/ms-wince-desktopemulation-sdk-beta21
* ISO: `WCESDK.iso` (115,355,648 bytes; CDIMAGE; Microsoft Corporation)
* Collected: 2026-09-14 (JST).

The **Visual C++ for Windows CE 1.0** CD (`msvcceu.100`, `MSVCCEU.100.iso`,
182 MB) was checked first: it carries the compiler/SDK toolchain and samples
but no API reference (the docs live on the SDK help, below); it is not
preserved here.

## Contents (documents only; no shared source, no code)

This directory (`ce10/` in the wince-api tree) holds the Windows CE 1.0
"Books Online" help files extracted from
`VCWCE/HELP/`:

* `PEGSDK.MVB` (+ `.AUX/.CAC/.IDX/.KWD`) — **Pegasus SDK Books Online**,
  the CE 1.0 SDK / Win32 API reference (5.3 MB Multimedia Viewer book).
* `PEGDDK.MVB` (+ `.AUX/.CAC/.IDX/.KWD`) — **Pegasus DDK Books Online**,
  the CE 1.0 driver/kernel reference.
* `RELNOTES.HLP` — "Release Notes for Pegasus DDK Books Online".
* `MSDNLIB.HLP` — MSDN Library pointer help.

`.MVB` is the Microsoft Multimedia Viewer book format (the WinHelp-era
reader for Books Online).  The files are preserved verbatim as the
official CE 1.0 documentation.  No source code, sample code, compiler
binaries or OS images are included (documents only, per the collection
policy in wince-api `docs/iso-collection.md`).

## Extraction (2026-10)

The books were decoded and filed into the corpus:

* `PEGSDK.MVB` → `corpus/mvb/windows-ce-1.0/PEGSDK/` — **1,919 pages**
  (SDK / Win32 API reference).
* `PEGDDK.MVB` → `corpus/mvb/windows-ce-1.0/PEGDDK/` — **181 pages**
  (driver and kernel reference).
* `RELNOTES.HLP` → `corpus/mvb/windows-ce-1.0/RELNOTES/` — **4 pages**
  (release notes).
* `MSDNLIB.HLP` — deliberately not extracted: it is the Development Library
  viewer help (how to search the library), not CE documentation.

Method: [helpdeco](https://github.com/pmachapman/helpdeco) 2.1.4, commit
`7852737` (GPL), built from source with one local fix (its `my_malloc`
aborts on a zero-byte allocation) and run with `-y`; the RTF it writes is
converted to one HTML page per topic by `tools/extract-mvb.py`.  Images
(BMP/WMF written next to the RTF) are not part of the corpus.  See
`corpus/mvb/windows-ce-1.0/README.md` for the exact commands and the page
naming convention.
