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

`ce10/` holds the Windows CE 1.0 "Books Online" help files extracted from
`VCWCE/HELP/`:

* `PEGSDK.MVB` (+ `.AUX/.CAC/.IDX/.KWD`) — **Pegasus SDK Books Online**,
  the CE 1.0 SDK / Win32 API reference (5.3 MB Multimedia Viewer book).
* `PEGDDK.MVB` (+ `.AUX/.CAC/.IDX/.KWD`) — **Pegasus DDK Books Online**,
  the CE 1.0 driver/kernel reference.
* `RELNOTES.HLP` — "Release Notes for Pegasus DDK Books Online".
* `MSDNLIB.HLP` — MSDN Library pointer help.

`.MVB` is the Microsoft Multimedia Viewer book format (the WinHelp-era
reader for Books Online).  The files are preserved verbatim as the
official CE 1.0 documentation; topic-text extraction is a separate step.
No source code, sample code, compiler binaries or OS images are included
(documents only, per the collection policy in wince-api
`docs/iso-collection.md`).
