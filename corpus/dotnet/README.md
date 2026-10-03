# corpus/dotnet/ — the .NET families, kept apart

10,657 pages documenting the managed-code layers that Microsoft shipped
*around* Windows CE. They arrived through the same harvest as the CE pages
(`learn.microsoft.com/…/previous-versions/windows/embedded`) and were filed
under `corpus/learn/` until 2026-10; they now live here.

| Set | Pages | Contents |
|-----|------:|----------|
| `pos-for-net/` | 5,793 | POS for .NET (`Microsoft.PointOfService`) reference and guides. |
| `dotnet-micro-framework/` | 4,012 | .NET Micro Framework (`Microsoft.SPOT.*`, `Ws.*`, `Dpws.*`, `System.Ext.*`, the WSD/DPWS stack). |
| `dotnet-compact-framework/` | 852 | .NET Compact Framework class-library pages (`System.*` namespaces). |

## Why they are separate

The project exists to build the knowledge base an include/def generator for
Windows CE is derived from — the C/C++ API surface of the operating system:
headers, libraries, exports, calling conventions, struct layouts, CE-specific
restrictions. The .NET families document something else:

* their "API surface" is classes, properties and namespaces in managed
  assemblies (`System.Windows.Forms`, `Microsoft.PointOfService`,
  `Microsoft.SPOT.Hardware`), not header declarations and exports;
* their names collide with unrelated Win32 names in the most confusing way
  (`Font`, `Image`, `Timer`, `CheckColors`, `Graphics`), which is why they were
  never allowed into the Win32-common mining (`tools/ce_api_names.py`);
* a CE include/def generator has nothing to take from them.

Keeping them in the same tree as the CE pages made every count, every grep and
every coverage number ambiguous. They are not deleted — they are the
documentation of a real, CE-adjacent product family, and some of it is the only
description of parts of the CE platform (the Compact Framework is how the
platform is programmed from managed code; POS for .NET and the Micro Framework
are CE derivatives). They are simply a different layer.

## What this means in practice

* `corpus/learn/` holds CE pages only: CE 5.0, Embedded CE 6.0, CE .NET 4.x,
  Embedded Compact 7 and the unclassified CE-era topics.
* `tools/harvest.py` classifies the .NET title rules into `DOTNET_DIR`
  (`DOTNET_SETS`); the same rules that used to send them to `learn/`.
* `tools/check-policy.py` treats `dotnet/` as one of the corpus trees and
  counts it separately from the CE trees.
* In the knowledge base the pages are parsed like every other page and carry
  `layer: "dotnet"`; their `Namespace:`/`Assembly:` requirements are recorded
  as such. Being non-C, their declarations land with `role: example` and no
  entity, which is the honest result: nothing in them states a header
  declaration.
* The Win32-common rule and its evidence report
  (`data/reports/ce-api-names.tsv`) are unchanged by the move: `dotnet/` names
  were excluded from that mining before and are excluded now.

## Provenance

Same harvest and same queues as the CE trees (`queues/mslearn-embedded.txt`,
`queues/to-fetch-mslearn.txt`); the pages come from the archived Microsoft
Learn copies of the MSDN Library. Set membership is decided by the title rules
in `corpus/README.md`. 60 of the 161 Internet Archive captures in
`corpus/msdn-library/2010-05/` are .NET Compact Framework topics and remain
filed there under the set they duplicate.
