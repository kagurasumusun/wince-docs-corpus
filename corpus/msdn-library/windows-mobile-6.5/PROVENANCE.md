# Windows Mobile 6.5 topics (MSDN Library format) — provenance

## What is here

34 topics covering the Windows Mobile 6.5 shell/input surface —
`SHFullScreen`, `SHSipInfo`, `SHRecognizeGesture`, `LMDATA`, `SIPSTATE`,
`IIMCallback*`, "How to …" guides, and the `SH*`/`Sip*` reference pages.
Files are named `wm65-<topic>.html`; the names are collector-assigned labels,
not the original topic ids.

## Evidence in the files

The pages are MSHelp-format topics from an MSDN Library / Visual Studio help
collection (`xmlns:MSHelp="http://msdn.microsoft.com/mshelp"`,
`MSHelp:TOCTitle`, `MSHelp:Keyword`, `MSHelp:Attr`). The metadata is uniform
across all 34 files:

```
MSHelp:Attr Name="Product"      Value="kbwince"
MSHelp:Attr Name="DocSet"       Value="kbwcedoc"
MSHelp:Attr Name="ProductVers"  Value="kbceplat60"      (all 34)
MSHelp:Attr Name="TargetOS"     Value="WinCE"
MSHelp:Attr Name="Audience"     Value="WindowsMobile"   (all 34)
MSHelp:Attr Name="Audience"     Value="WindowsEmbeddedCE"  (22 of 34)
MSHelp:Attr Name="Windows Embedded CE" Value="Windows CE 2.12 and later"
MSHelp:Attr Name="Windows Mobile"      Value="Windows Mobile Version 5.0 and later"
```

Each file ends with a `© 2010 Microsoft` notice. The topic metadata identifies
the source collection as the Windows CE / Windows Mobile documentation set
(`kbwince` / `kbwcedoc`, platform version `kbceplat60`) that Microsoft shipped
in the MSDN Library channel; per-topic `Header` attributes (e.g. `sip.h`) sit
next to the syntax blocks.

## What is *not* recorded

The extraction method, tool and date are not recorded in this repository's
history — these files were committed under the former
`supplementary/windows-mobile-6.5/` directory in the initial squashed commit,
with no accompanying note. There is no `saved from url` comment and no
canonical link, so the individual source URLs cannot be reconstructed from the
files. 22 of the 34 pages are also marked `Audience=WindowsEmbeddedCE`, i.e.
the same topics appear in the CE 6.0 platform documentation.

If you re-derive these topics from an official medium, replace the files,
keep the `wm65-` prefix convention (the rest of the corpus uses canonical page
ids; these files predate that convention), and update this document.
