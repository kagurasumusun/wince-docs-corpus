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
| `kb/entities.jsonl.gz` | One record per API name (**24,442** names): kinds, layers, `surface` (where the name sits in the Windows CE / Win32 split), `ce_sets` (the version scope), the CE and Win32 pages, the header/library/DLL/module names the pages state, the ids of its evidence records, its `relations` to other definitions, its `variants` (Unicode/ANSI spellings), and `generation_use`. |
| `kb/declarations.jsonl.gz` | Every C/C++ declaration, prototype and struct/enum body found in a CE or Win32 page (**78,442**), **verbatim** — the raw material of the generated `.h` files. |
| `kb/declarations-dotnet.jsonl.gz` | The signature blocks of the separated .NET layer (**31,326**, `language: "managed"`), kept as evidence of that layer and out of the C declaration file. |
| `kb/requirements.jsonl.gz` | Every Header / Library / DLL / module / OS-version statement (**156,514**), with the page's own label next to the mapped field — the raw material of the include map and of the import-library/`.def` map. |
| `kb/constraints.jsonl.gz` | Sentences in which a page states a Windows CE restriction or extension (**3,239**), quoted. |
| `kb/headers.tsv` | Header -> entities (the include mapping). The key is the value the page printed with trailing punctuation and whitespace removed (`Winbase.h.` -> `Winbase.h`); the `as_printed` column shows the verbatim forms. A value that names several files (`Bthapi.h, Bthapi.idl`) is kept as the page printed it — split it if you generate includes from it. |
| `kb/libraries.tsv` | Library -> entities (the link mapping). |
| `kb/dlls.tsv` | DLL -> entities. |
| `kb/modules.tsv` | sdk-api module -> entities (the Win32-side grouping; from each page's UID). |
| `kb/struct-fields.tsv` | `entity <TAB> field <TAB> order <TAB> page` — the members a page documents in its `-struct-fields` section (**5,204** rows over **801** structures). 882 sdk-api pages use `### -field` and 842 of them are a struct member list (40 use the heading for enum values, with no `-struct-fields` section); **840 of those 842 print no declaration at all** (only `WIN32_FIND_DATAA`/`W` do), so the member list, in documented order, is the only ABI fact held; **no offsets anywhere**, and none are invented (`generation_use: abi-members`). |
| `kb/sets.tsv` | CE set -> entities, and how many of them have a declaration/header/library/DLL. |
| `reports/coverage-by-tree.tsv` | What each corpus tree contributed (pages, requirements, declarations). |
| `reports/coverage.tsv` | One row per entity: what is known about it. |
| `reports/gaps.tsv` | **The collection worklist**: every reference entity for which a declaration, a header or a library is still missing. |
| `reports/filtered-values.tsv` | The Header/Library/DLL values that name no file at all (`Library: Developer Implemented`, `Header: Windows 7`). The requirement record keeps the printed value and stays in `requirements.jsonl`, but its derived `key` is empty, so no header file or library is invented for it. |
| `reports/catalog-leads.tsv` | The collection leads for the 3 `catalog-only` names: the CE page id the catalog list points at, the page in `corpus/`, the title, the spelling that page prints, how many syntax blocks it has, and the Win32 page with its documented member list. The finding it records: `AVIMAINHEADER`'s CE pages do print the type (as `MainAVIHeader`), while `MESSAGE`/`SECTION`'s CE pages are tool-option topics that print nothing. |
| `reports/surface.tsv` | **The Windows CE / Win32 boundary, one row per name**: `surface <TAB> entity <TAB> name <TAB> kinds <TAB> ce_sets <TAB> headers <TAB> libraries` (24,442 rows). Windows CE is the CE-specific surface *plus* the part of Win32 the CE documents share — not the whole Win32 API — and this file is that statement in machine-readable form. |
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
  a consumer can then prefer another page's copy of the same declaration.  The
  text is not repaired here.
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
* **A name that is not an API is flagged, not deleted.**  One pattern is
  certain enough to mark: an all-caps double-underscore identifier
  (`__COMMONPUBROOT`, `__PROJROOT`) is a build-system variable mentioned in a
  page's code block.  Those two records carry `noise: "build-variable"`, stay
  readable with their page, and are left out of `reports/gaps.tsv`; a generator
  filters on `noise`.
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
