# `knowledge/` — the machine-readable knowledge base

This repository is not only a page archive.  The point of collecting Windows CE
documentation is to end up with **statements a tool can use**: which API exists,
in which Windows CE version, in which header, in which library, with which
signature, with which ABI facts, and with which restrictions — each one tied to
the page it was read from.

`knowledge/` is that layer.  It is *derived* from `corpus/` by
`tools/build-kb.py`, and it is deliberately **not** a set of include or def
files: it is the material those files will be generated from.

```
sources/     the media and upstream snapshots (the origin)
corpus/      the documentation pages themselves (the material)
knowledge/   statements extracted from the pages, each with its source  <- here
data/        indexes, catalogs, receipts and reports about corpus/
tools/       the pipeline that produces all of the above
```

## What is here

| Path | Contents |
|------|----------|
| `kb/entities.jsonl.gz` | One record per API name (**30,076** names): kinds, layers, `surface` (where the name sits in the Windows CE / Win32 split), `ce_sets` (the version scope), the CE and Win32 pages, the header/library/DLL/module names the pages state, the ids of its evidence records, its `relations` to other definitions, its `variants` (Unicode/ANSI spellings), and `generation_use`. |
| `kb/declarations.jsonl.gz` | Every C/C++ declaration, prototype and struct/enum body found in a CE or Win32 page (**78,976**; of 110,302 records in both declaration files, **96,756** are `role: "syntax"` interface declarations and **13,546** are `role: "example"` blocks; **46,854** member lines are recovered, **38,909** of them with the type the line prints -- a page that lost its line breaks and spaces still yields its members, quoted as printed), **quoted from its page**. A `#define` / `#pragma` / `#undef` block with no parentheses is kept too, unless the heading above it is an example. A `<pre>` with no Syntax heading is `role: "syntax"` when it is a documented prototype immediately before Parameters, Parameter, Members, Elements, Constants, Return Values, Enumerators or Enumerator Values, and the heading above it is not an example or a parameter list. `<p class="clsRef">` (the CE 5.0 MSHTML/shdocvw CHM) and `<p class="blue">` (the 2000-04 ATL template) are section labels, not prose. A prototype under that Syntax label is the declaration. A paragraph in a blue Syntax section is kept only when it is a C prototype or a `typedef` alias; `SINK_ENTRY(id, dispid, fn)` and `Len(<string>)` are not turned into one. A call after Parameters, resource-compiler grammar, Visual Basic, and a JScript `function` stay examples. A `*` or `&` glued to the name (`void *malloc`) and a `Class::Method` name are still that prototype. A prototype of a different name than the page title stays an example, as does a prototype on a page that also prints `#define` of that name. A title that prints `Interface::Member Method`, `MSMQMessage.Priority`, `IXRCollection<In_T, Out_T>::Insert`, `CComPtr::operator !` or `strcpy, wcscpy` names those APIs; each name is an entity only when a syntax block declares it. `operator !` and `operator *` stay separate records. A parameter list longer than eight lines is still the declaration; a parameter named `dialog` is not a resource script. A property page that prints `get_Priority` declares the title's `Priority`. The dotted spelling is not rewritten to `::`. Whitespace is normalised and `spacing: "collapsed"` says the archived page itself had already lost the spaces between tokens. `implementation: true` (**4,581** records; the checker counts 4,570 of them as quarantined example blocks, the rest are `#define` blocks) marks a block that is sample code: kept as evidence, never emitted. Each record carries `member_types` (the type each member line prints), `abi_flags` (bitfield / pack / align) and the `license` scope of its page. |
| `kb/declarations-dotnet.jsonl.gz` | The signature blocks of the separated .NET layer (**31,326**, `language: "managed"`), kept as evidence of that layer and out of the C declaration file. |
| `kb/requirements.jsonl.gz` | Every Header / Library / DLL / module / OS-version / sysgen / architecture statement (**173,831**), with the page's own label next to the mapped field — the raw material of the include map and of the import-library/`.def` map. `Versions`, `Pocket PC`, `Smartphone` and `Smartphones` are OS-version statements. `Module: Nk` is the module the page printed, not `nk.dll`. `Component: fsdbase` is the catalog component, not a DLL. `sysgen` and `Architecture` are the catalog variable and the CPU list. A `::` in a C++ name is not a requirement label. A two-cell `Header file | mshtmcid.h` row is a header even when the section title is `C++ Information` rather than Requirements. `At a Glance` marked `class="blue"` is the same requirements table. `Platforms` is not an OS version. The blank-template sentence `Windows CE versions that include this API element.` is not a version. An empty cell is not given the next row's label. The CE 3.0 SDK's column table (`Runs on | Versions | Defined in | Include | Link to`) is read column by column; `Defined in` and `Include` stay distinct labels, both mapped to `header`. The same table printed as `Declared in | Link to`, with no `Include` column, is that table too: `Declared in` is a header. Every `Requirements` heading on the page is read, including a later `Windows Mobile Requirements` block and a second `Requirements` heading whose first block is only a note. A library/DLL cell that names several files keeps the printed list as one statement; the derived key is the first file. A parenthetical (`Rts.lib (for development workstation), PSPubSubCE.lib (for target device)`) says which machine and is not a second file. `Uuid.lib. Not supported in Windows CE.` is not a CE library. A sentence that names this page's own event, function, structure, message, macro, control code, interface, callback or method (`The DISPID for this event is defined in mshtmdid.h`, `This function is declared in the Serhw.h`, `This function is exported by Ppcload.dll`, `This function is implemented in the Edbg.dll`, `This is an API exported by the Store.dll`) is that page's header or DLL. A sentence about a different type (`BT_ADDR is defined in Ws2bth.h`) is not. A component page that says the following functions are defined in a header and imported from a library, or implemented in a DLL, then lists those names, assigns the files to each listed name that is already an entity. The component title is not given the library. A misspelled cell is not rewritten, and a sentence that lists no names assigns nothing. A table that states the files outside a Requirements section is read too: MSHTML's `Interface Information` block (`Header and IDL files`, `Header`, `Stock Implementation`, `Import library`) and a DirectShow filter's `Executable` row. `Stock Implementation | None` names no file and is not a DLL; `Import library | mshtml.dll` is a DLL, because that is the file the cell names. `Minimum operating systems` is an OS-version statement only when the cell names Windows CE, Windows Mobile or Pocket PC, and the desktop names in the same cell stay as printed. A registry sentence that mentions a DLL (`Default set to "\\windows\\mboxcht.dll"`) is not such a cell. `To use this API, include the shellcb.h header file and link with shellcb.lib` states this page's header and library. The listed-name readers also read `the functions that are exported by Setup.dll` and `The Install_Exit function prototype is part of Setup.dll`; the ISV-created clause stays in the evidence. |
| `kb/constraints.jsonl.gz` | Sentences in which a page states a Windows CE restriction or extension (`kind: "ce-restriction"`), the CE 1.0 Books Online's own labelled `Windows CE Notes` paragraph (`kind: "ce-note"`, 206 pages — most of it states no restriction *word* and was invisible to the sentence reader: *The only supported raster operations are SRCCOPY and SRCINVERT*, *Cannot be used with the uObjectType flag OBJ_PAL*) or an ABI fact about itself (**969**, `kind: "abi-note"`: alignment, byte order, pointer width, structure size — each a quoted sentence with the `pattern` that matched). Offsets are not in this file; a page that prints them does so in a layout table, recorded in `kb/abi-offsets.jsonl.gz`. |
| `kb/headers.tsv` | Header -> entities (the include mapping). The key is the value the page printed with trailing punctuation and whitespace removed (`Winbase.h.` -> `Winbase.h`); the `as_printed` column shows the verbatim forms. A value that names several files (`Bthapi.h, Bthapi.idl`) is kept as the page printed it — split it if you generate includes from it. |
| `kb/libraries.tsv` | Library -> entities (the link mapping). A cell that names several files (`Ole32.lib, Uuid.lib`, `OEMMain.lib or OEMMain_StaticKITL.lib`) maps the entity to each file the page named. A sentence that names one file (`Iphlpapi.dll on Windows Server 2008`, `Shell32.dll (version 4.0 or later)`) maps that file only — the `or` in the version sentence is not a second library. The requirement record stays one statement; its derived key is the first file. |
| `kb/dlls.tsv` | DLL -> entities. A cell that names several DLL files maps the entity to each of them, the same way `libraries.tsv` does. |
| `kb/modules-ce.tsv` | **What a Windows CE *module* page states about the binary** (**350** statements over **101** pages, 44 modules: `coredll`, `gwe`, `nk`, `filesys`, `quartz`, `winsock`, …): `module <TAB> component <TAB> field <TAB> value <TAB> notes <TAB> page <TAB> page_id <TAB> set <TAB> title <TAB> quote <TAB> license`. A `Component \| Description \| Notes \| Library` table gives one row per component with the `.lib` it is imported from (`coredll` has 32 of them, `Coremain.lib`, `Lmem.lib`, …); the module's own sentence (`The msmqrt module includes functions … defined in the Mq.h header file`, `To import these functions, you must link to the Msmqapix.lib file`) gives the module's header and library. The `notes` cell is the page's own words (`Required`, `Optional and exposes no public functions.`) and is not turned into a flag. A component whose row names no `.lib` (`HAL … None`) keeps the component and no file. **A module name is not a DLL name**: `coredll` is the module the pages name, and `Coredll.dll` is recorded only where a page prints it. `tools/gen-include-def.py` does not read this file yet. |
| `kb/unicode-only.tsv` | **Where a CE page states that only the Unicode form exists** (**165** statements over **32** names): `entity <TAB> name <TAB> kinds <TAB> subject <TAB> scope <TAB> statement <TAB> ansi_variant_documented_by_win32 <TAB> page <TAB> page_id <TAB> set <TAB> license`. `scope: "this-api"` is a sentence about the API the page documents (*Windows CE supports only the Unicode version of this function.*); `scope: "system"` is a sentence about the system (*Windows CE supports only Unicode strings.*) and does not by itself deny the `A` spelling of that name. Where the Win32 reference documents an `A` spelling of the same name, the two documents describe two different systems: the CE page governs the device. The entity keeps both, the conflict is visible, and `tools/gen-include-def.py` leaves the ANSI spelling out with the sentence quoted in the fragment. |
| `kb/export-ordinals.tsv` | **The export ordinals the documents actually print** (**94** rows, **1** page): `name <TAB> ordinal <TAB> dll <TAB> entity <TAB> page <TAB> page_id <TAB> set <TAB> title <TAB> table <TAB> row <TAB> dll_evidence <TAB> license`. The one page family that prints them is *Exports from the Floating Point C Run-Time Library*, two `Export \| Ordinal` tables for `Fpcrt.dll` (`_cabs` 1000 … `tanh` 1053 for the platform-independent half, `__addd` 960 … `__utos` 999 for the platform-dependent half). The ordinal is stored as the page prints it, the DLL comes from the page's own sentence (`dll_evidence`), and the table row is kept as the quote. Every other page in the corpus states no ordinal, and **none is derived, counted or inferred** for them — a `.def` generated from this base lists `@n` only for these 94 names. |
| `kb/def-rules.tsv` | **What the documents state about building the module-definition file itself** (**533** sentences over **309** pages): `topics <TAB> statement <TAB> page <TAB> page_id <TAB> set <TAB> title <TAB> license`. Topics: `module-definition-file`, `calling-convention`, `export-ordinal`, `name-decoration`, `dllexport`, `exports-section`, `extern-c`. The sentence is quoted verbatim; no rule is generalised beyond its page. Examples of what this holds: a 32-bit `.def` lists `__cdecl`, `__stdcall` and `__fastcall` functions in `EXPORTS` **undecorated**; `GetProcAddress` matches the spelling and case of the `EXPORTS` entry and accepts an ordinal in the low-order word; a CEF DLL that exports by ordinal must use identical ordinals on every CPU; `wsprintf` uses the C calling convention (`_cdecl`) unlike other Win32 functions. These are the constraints a generator has to obey, and they are now evidence rather than assumption. |
| `kb/modules.tsv` | Module -> entities. A Win32 sdk-api page contributes the module in its UID. A CE page that prints `Module: Nk` contributes `Nk`, as printed, not rewritten to a DLL name. `Component` is a separate field on the entity (`components`), not a row here. |
| `reports/oss-surface.tsv` | Names observed in the Qt 4.8 and SDL 1.2 Windows CE implementations, read 2026-10-05. The source was not stored. A row is not a declaration, not a constant and not an EXPORT. `called` names that are already in the knowledge base stay documented by their pages. `entry-point` and `dll-loaded` names absent from the corpus are collection leads, not generated symbols. `shim` names are replacements the implementation supplies; the prototypes were not copied. `refused` rows are values the implementation prints that are not Windows CE facts (stand-in numbers, an SDL port limitation). `tools/gen-include-def.py` does not read this file. |
| `kb/abi-offsets.jsonl.gz` | One record per row of a **layout table** a page prints (`Offset | Field | Size | …`): **399** rows over **58** pages. The row is quoted as printed, `offset` is read from the offset cell (the cell itself is kept as `offset_printed`), the size cell likewise, and `matches_declared_member` says whether the name is one the same page declares in a syntax block (**18** are). The rest are wire/packet layouts, the page's own array spellings (`dwIndex[0]` where the declaration says `dwOffset`) and string literals inside the table: each is kept exactly as the page printed it, and no offset is inferred for a member the page gives none for. |
| `kb/abi-offsets.tsv` | The same as a flat table (`entity <TAB> member <TAB> offset <TAB> offset_printed <TAB> size <TAB> size_unit <TAB> matches_declared_member <TAB> page <TAB> page_id <TAB> title <TAB> table <TAB> row <TAB> license`). |
| `kb/constants.jsonl.gz` | One row of a **name/value table** a page prints, or one cell the page prints as `NAME = 0x0001` / `NAME (0x0001)`: **18,746** rows over **791** pages. Headings include `Flag \| Value`, `Symbolic constant \| Value (Hex)`, `Control code \| Value`, `Message identifier \| Value`, `Element \| Hex code` and `Value \| Weight` (the font-weight constants). A separate-column row is kept only when the name cell is one identifier and the value cell is one number. A one-cell row is kept only when the whole cell is that spelling and the name is an all-caps identifier (`S_OK`, `TRUE`; a one-letter `A=0` is left out). `decimal` is set only when a decimal column prints a decimal beside the value — a hexadecimal is never converted, and a column headed hexadecimal whose cell has no `0x` is stored as those digits. `headers` are the header files that same page states (**5,044** rows have one); a constant is not assigned a header the page does not name. A correspondence (a virtual key beside a scan code, a character set beside a code page, a locale beside an LCID) is not a constant. A constant the page does not number (`WM_CREATE` is documented, its value is not) has no row. |
| `kb/constants.tsv` | The same as a flat table (`name <TAB> value <TAB> decimal <TAB> headers <TAB> page_entity <TAB> page <TAB> page_id <TAB> title <TAB> table <TAB> row <TAB> license`). |
| `kb/struct-fields.tsv` | `entity <TAB> field <TAB> order <TAB> page` — the members a page documents in its `-struct-fields` section (**5,204** rows over **801** structures). 882 sdk-api pages use `### -field` and 842 of them are a struct member list (40 use the heading for enum values, with no `-struct-fields` section); **840 of those 842 print no declaration at all** (only `WIN32_FIND_DATAA`/`W` do), so the member list, in documented order, is the only ABI fact held; **no offsets on those pages**, and none is invented; where the corpus *does* document offsets (layout tables on 58 other pages, `kb/abi-offsets.tsv`) they are recorded as the page's own rows. |
| `kb/sets.tsv` | CE set -> entities, and how many of them have a declaration/header/library/DLL. |
| `reports/coverage-by-tree.tsv` | What each corpus tree contributed (pages, requirements, declarations). |
| `reports/coverage.tsv` | One row per entity: what is known about it. |
| `reports/gaps.tsv` | **The collection worklist**: every reference entity for which a declaration, a header or a library is still missing. |
| `reports/filtered-values.tsv` | The Header/Library/DLL values that name no file at all (`Library: Developer Implemented`, `Header: Windows 7`). The requirement record keeps the printed value and stays in `requirements.jsonl`, but its derived `key` is empty, so no header file or library is invented for it. |
| `reports/catalog-leads.tsv` | The collection leads for the 3 `catalog-only` names: the CE page id the catalog list points at, the page in `corpus/`, the title, the spelling that page prints, how many syntax blocks it has, and the Win32 page with its documented member list. The finding it records: `AVIMAINHEADER`'s CE pages do print the type (as `MainAVIHeader`), while `MESSAGE`/`SECTION`'s CE pages are tool-option topics that print nothing. |
| `reports/abi.tsv` | **The ABI view, one row per name**: `entity <TAB> name <TAB> kinds <TAB> surface <TAB> calling_conventions <TAB> declarations_without_convention <TAB> syntax_declarations <TAB> declared_members <TAB> typed_members <TAB> bitfield_members <TAB> abi_flags <TAB> abi_notes <TAB> documented_offsets <TAB> stated_size_bytes <TAB> headers <TAB> modules <TAB> ce_sets <TAB> licenses <TAB> architectures` (30,076 rows). It records only what the pages print: 93,135 of 96,756 syntax declarations print **no** calling convention and none is guessed; 19 names have documented offsets or a stated size. `architectures` is the CPU list a page prints under `Architecture`, empty when the page prints none. |
| `reports/cleanroom.tsv` | The clean-room invariants `tools/check-cleanroom.py` verifies, with what was checked and the violations (0 on 2026-10-06, with `--all`: 276,032 quotes compared, including layout-table rows, constant-table rows, the module-table rows and the open-source document quotations). |
| `reports/license-audit.tsv` | What the repository publishes, by rights scope and permission (`tools/check-licenses.py --tracked`). |
| `reports/surface.tsv` | **The Windows CE / Win32 boundary, one row per name**: `surface <TAB> entity <TAB> name <TAB> kinds <TAB> ce_sets <TAB> headers <TAB> libraries` (30,076 rows). Windows CE is the CE-specific surface *plus* the part of Win32 the CE documents share — not the whole Win32 API — and this file is that statement in machine-readable form. |
| `reports/summary.md` | The same in prose, with the totals. |
| `schema/*.json` | JSON Schema for the four record types. |

The `.jsonl.gz` files are gzipped because they are ~150 MB of text and ~15 MB
compressed, and they are generated: read them with anything that reads gzip
(`zcat kb/entities.jsonl.gz | jq .`, `polars.read_ndjson`, `gzip.open(...)` in
Python).  `python3 tools/build-kb.py --plain` writes them uncompressed.

## The rules this layer keeps

* **Every fact has a source.** No record exists without a `source` naming the
  corpus page, its id, its set and its title.  There are no model-written
  values and no values inferred from outside the corpus.
* **Declarations are never normalised.** `text` is quoted as the page prints it.
  `spacing: "collapsed"` flags a page that itself lost the spaces between tokens
  (the archived CE 5.0 Learn pages print `HANDLECreateFile(LPCTSTRlpFileName,`);
  a consumer can then prefer another page's copy of the same declaration —
  the same text, whitespace aside, not a copy that also prints a calling
  convention or a different type.  The text is not repaired here.
* **An ABI fact is only recorded when a page states it.**  The calling
  convention comes from the declaration text; member types from the member line;
  offsets from a layout table row (quoted); a structure size from a sentence that
  defines it (five sentences exist in the whole corpus: `IPCANDIDATE` 68 bytes,
  `SOCKADDR_STORAGE` 128 bytes).  Where a page says nothing, the field stays
  empty and `reports/abi.tsv` shows the gap as a count -- never as a guess.
* **Every record says who may use it.**  Each declaration, requirement and
  constraint carries `license` — the scope id its page belongs to in
  `data/license-scopes.tsv` — and each entity carries `licenses` (all its
  pages).  The scope is not a guess: the registry quotes the statement it rests
  on, and `tools/check-licenses.py` verifies the quote against the file it was
  read from.  See `docs/LICENSING.md` for the finding (most of the collection
  is not licensed for redistribution).
* **Sample code is quarantined, not deleted.**  A block a page prints as an
  example is `role: "example"` with `implementation: true`; it stays readable
  as evidence but is never part of the include/def material, and
  `tools/check-cleanroom.py` verifies that no entity's `syntax_declarations`
  points at one.  See `docs/clean-room.md`.
* **Derived fields are marked as derived.**  `kind`, `doc_role`, `spacing`,
  the requirement `field`/`key`, the declaration `language` and
  `calling_convention` are computed deterministically and documented as derived
  in the schema; the original label and text are always kept beside them.
  `calling_convention` is read from the declaration text (`WINAPI`, `CALLBACK`,
  `_stdcall`, `_cdecl`, `_fastcall`, `extern "C"`) and stays `null` when the page
  does not say -- a missing convention is not guessed.
* **The Windows CE / Win32 boundary is explicit.**  Windows CE is **not** the
  whole Win32 API: it is the CE-specific surface plus the part of Win32 that
  the CE documentation shares, and every entity carries `surface` so a consumer
  never has to guess which side a record came from:

  | `surface` | names | meaning |
  |-----------|------:|---------|
  | `ce-only` | 18,931 | only Windows CE documents the name |
  | `shared` | 4,353 | Windows CE documents it *and* the Win32 reference does (directly or through an A/W spelling) |
  | `win32-spelling` | 1,155 | the entity is a Win32 page for an A/W spelling of a documented CE name (`variants_of`) |
  | `catalog-only` | 3 | only the official CE catalog names it; the Win32 page is the only documentation held, so it is a collection lead, not a CE definition (`AVIMAINHEADER`, `MESSAGE`, `SECTION`). `reports/catalog-leads.tsv` records the CE page the name list points at, the spelling that page actually prints (`AVIMAINHEADER` is printed `MainAVIHeader`), and the Win32 page with the member list — a lead, never a CE declaration. Two of the three (`MESSAGE`, `SECTION`) turn out to be name-list noise: their CE pages are the `#message` / `/SECTION` tool-option topics and print no declaration at all (`ce_syntax_blocks` = 0) |
  | `win32-only` | 0 | a Win32 page not tied to a CE name — there is none: every imported Win32 page was taken because a CE document claims its name |

* **A Unicode/ANSI spelling is folded into its base name, on evidence.**
  `CreateSemaphoreW` is a page of its own in the Win32 reference while the CE
  page documents `CreateSemaphore`.  The page's own "Unicode and ANSI"
  statement is the evidence: the variant gets `variants_of`, the base gets the
  variant in `variants`, the variant's Win32 pages in
  `win32_pages_from_variants`, `win32_documented` set and a
  `unicode-ansi-variant` relation.  `variants_of.basis` says which evidence the
  link rests on: `page-statement` (the page prints the pair) or `import-rule`
  (the page was imported for that CE name because it is its A/W spelling, as
  `data/reports/win32-shared.tsv` records — used only when the page itself
  states no pair). A spelling with neither is left as its own entity: nothing
  is paired by name alone.
* **The .NET layer stays separated here too.**  `corpus/dotnet/` pages are
  parsed like every other page and their records say `layer: "dotnet"`, but
  their signature blocks (C#/VB/C++/JScript) go to
  `kb/declarations-dotnet.jsonl.gz` rather than the C declaration file. Nothing
  in the .NET tree states a header declaration, so it produces no entities —
  which is the honest result, not a parser failure.
* **A name that is not an API is flagged, not deleted.**  Two signals mark one:
  an all-caps double-underscore identifier (`__COMMONPUBROOT`, `__PROJROOT`) is
  a build-system variable mentioned in a page's code block, and carries
  `noise: "build-variable"`; and a code block that is makefile/Sources-file
  assignment (`TARGETLIBS=$(_COMMONOAKROOT)\lib\$(_CPUDEPPATH)\blcommon.lib`)
  is read as `kind: "build-variable"` rather than as a C function — it contains
  `(` and `)` only because of `$(...)` expansion, and the generic
  "has parentheses -> function" rule used to call nine of these build variables
  (`LDEFINES`, `SOURCELIBS`, `TARGETFILES_MC`, `TARGETFILES_MIDL`,
  `TARGETFILES_OAK`, `TARGETFILES_SDK`, `TARGETFILES_GUID`, `__COMMONPUBROOT`,
  `__PROJROOT`) functions. They stay readable with their page, are left out of
  `reports/gaps.tsv`, and a generator filters on `noise`/`kinds`.
* **Removed duplicates stay traceable.**  `data/index/aliases.tsv` records every
  page `tools/dedupe-corpus.py` collapsed, so a page id can always be followed to
  the copy that is still in the corpus.

## Following a record back to the documentation

The four questions a consumer has to be able to ask, and the fields that answer
them:

| Question | Fields |
|----------|--------|
| **Which document is this from?** | every record has `source` (`path`, `page_id`, `set`, `title`, `layer`); `entities.jsonl` lists the pages in `ce_pages`/`win32_pages`/`dotnet_pages`, the evidence records in `declarations`/`requirements`/`constraints`, and the relation entries carry their own `page` and the printed `evidence` text |
| **Which version / generation?** | `ce_sets` (the corpus sets that document the name, e.g. `learn/windows-embedded-ce-6.0`), the requirement `field: "os_versions"` values ("Windows CE versions: 5.0 and later"), and the per-set counts in `kb/sets.tsv` |
| **How does it relate to other definitions?** | `relations`: `unicode-ansi` (the page's own "X (Unicode) and Y (ANSI)" statement), `unicode-ansi-base` (the base name the pair belongs to, derived from that statement), `interface-method` (`Interface::Method`, the vtable owner), `layer` (documented by CE *and* the Win32 reference) and `ce-name-lead` (the CE page prints the name under a different spelling, e.g. `MainAVIHeader` for `AVIMAINHEADER` — as a lead with its page; no renaming). Each entry names its target, whether that target is present in this file, the page and the printed text |
| **How can it be used to generate include/def?** | `generation_use` says which generator steps the record can feed — `include-declaration` (a syntax declaration plus a stated header), `type-definition` (struct/enum/union/typedef), `link-library` (a function/callback with a stated library or DLL), `def-export` (a function/callback with a stated DLL), `abi-layout` (a struct whose declaration lists members), `abi-members` (only the documented member list exists — names and order, no offsets), `unicode-mapping`, `version-scope`, `ce-restriction` — and `kb/headers.tsv`/`libraries.tsv`/`dlls.tsv`/`modules.tsv` are the inverted maps. `generation_use` is rule-based (DERIVED); it says what the record *can* feed, never that the record is complete |

Nothing is invented: `present: false` in a relation means the other side was
never collected (a collection lead), and an entity with no `syntax_declarations`
appears in `reports/gaps.tsv` instead of getting a declaration from anywhere
else.

## How this becomes include / def material

The intended pipeline.  The prototype consumer
(`tools/gen-include-def.py --set <set> --out <dir>`, §8 of
`docs/review-2026-10.ja.md`) already walks it end to end and writes fragments
into a git-ignored `build/` directory; it is a worklist generator, not a
finished include/def set.  Because Windows CE is not the whole of Win32, it
emits only names a CE set documents, prefers the CE set's own declaration, and
uses a Win32 reference page only as a **marked** fallback when no CE page
prints one (`borrowed_from: win32-reference` in `manifest.tsv`, a comment in
the fragment, a note on the `.def` line):

1. **Include map.**  For a version target, take the entities whose `ce_sets`
   include that version, group them by `headers`, and use each entity's
   `syntax_declarations` as the declaration text.  Filter on `surface` to keep
   the CE-specific and shared names apart (`catalog-only`/`win32-spelling`
   records are never a CE definition).  `reports/gaps.tsv` tells you which
   entities would come out empty.
2. **Link map.**  `libraries` and `dlls` per entity give the library/DLL names a
   linker needs (`libraries.tsv` is the inverted view).
3. **Def/symbol worklist.**  The exports a `.def` file needs are the entities
   whose `generation_use` contains `def-export`/`link-library`, grouped by
   `libraries`/`dlls`; the `constraints` records and the `relations` of type
   `unicode-ansi`/`unicode-ansi-base` then say which of them exist in a given
   CE version and how the `A`/`W` spellings pair up.
4. **ABI facts.**  The declaration text carries the calling convention and the
   parameter/field types; struct bodies come with their `members` lines.
   Where a struct has no printed declaration, `documented_fields` and
   `kb/struct-fields.tsv` give the member names in documented order (the
   sdk-api `-struct-fields` sections) — usable for `#pragma pack`-free
   re-declaration checks and for detecting a missing member, **not** for field
   offsets, which no page states.  For a
   struct whose declaration is `collapsed`, look for the same name in another
   set (`declaration_in_other_sets` in `reports/gaps.tsv`, or the same entity in
   `kb/entities.jsonl.gz`).
5. **Versioning.**  Because every record names its set, a CE 5.0 target and a
   CE 6.0 target are two filters over the same knowledge base, not two
   collections.

Whatever generator is built on top should write its output **outside**
`corpus/` and `knowledge/` (for example under a git-ignored `build/`), so that
the repository keeps its current shape: media -> documents -> statements.

## Regenerating

```bash
python3 tools/build-kb.py                # rebuild everything under knowledge/
python3 tools/build-kb.py --report       # totals only, write nothing
python3 tools/build-kb.py --tree learn/windows-ce-5.0   # one tree while iterating
python3 tools/check-kb.py                # validate what was written (expects "knowledge OK")
python3 tools/check-kb.py --strict --sample 2
```

`tools/build-kb.py` reads `data/index/INDEX.tsv` for the page list and
`data/reports/win32-imported.tsv` for the Win32 side; run `tools/build-index.py`
first when the corpus changed.  The extraction rules live in
`tools/page_parse.py` (one file, with the templates it knows documented at the
top).
