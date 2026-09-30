# Windows CE .NET 4.2 documents — provenance

## Source (official Microsoft media, preserved by the Internet Archive)

* Item: `winceemul42` — "Windows CE .NET 4.2 Platform Builder Emulation
  Edition (x86 Emulator only Version)"
* URL: https://archive.org/details/winceemul42
* Media: `winceemul42.exe` (542,061,464 bytes; self-extracting
  CAB-installer; Microsoft Corporation; 2003)
* Collected: 2026-09-14 (JST).

## Contents (documents only)

* `EMULATOR.CHM`  — CE .NET 4.2 Platform Builder emulator help (58 KB)
* `REMTOOLS.CHM`  — Platform Builder remote-tools help (486 KB)
* `release notes.htm`, `whatsnew.html` — disc-level release notes

## What this disc does NOT contain (important)

The Platform Builder **Emulation Edition** is the emulator + remote tools
edition: the installer payload (`disk1.cab`/`disk2.cab`/`Data.Cab`) is the
emulator image, Platform Manager, and remote tools. It has **no Windows CE
.NET 4.x API reference**. The eVC 4.0 disc (`EMbeddedVisualC4.0`,
`MSDN_..._eMbedded_Visual_C_4.0..._Disc_1393.2`) is likewise toolchain-only.

The official CE .NET 4.x API reference documentation is therefore taken from
(a) the Learn `previous-versions/windows/embedded` CE 4.x pages already in
`pages4/`, and (b) the MSDN Library for Visual Studio .NET 2003 (which also
carries the .NET Compact Framework 1.0 reference) — see the .NET track.
No third-party/vendor/sample content is preserved (documents only; policy:
wince-api docs/iso-collection.md).
