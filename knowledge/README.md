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
| `kb/entities.jsonl.gz` | One record per API name (**24,442** names): kinds, layers, `ce_sets` (the version scope), the CE and Win32 pages, the header/library/DLL/module names the pages state, the ids of its evidence records, its `relations` to other definitions, and `generation_use`. |
| `kb/declarations.jsonl.gz` | Every C/C++ declaration, prototype and struct/enum body found in a CE or Win32 page (**78,518**), **verbatim** — the raw material of the generated `.h` files. |
| `kb/declarations-dotnet.jsonl.gz` | The signature blocks of the separated .NET layer (**31,827**, `language: "managed"`), kept as evidence of that layer and out of the C declaration file. |
| `kb/requirements.jsonl.gz` | Every Header / Library / DLL / module / OS-version statement (**156,548**), with the page's own label next to the mapped field — the raw material of the include map and of the import-library/`.def` map. |
| `kb/constraints.jsonl.gz` | Sentences in which a page states a Windows CE restriction or extension (**3,289**), quoted. |
| `kb/headers.tsv` | Header -> entities (the include mapping). The key is the value the page printed with trailing punctuation and whitespace removed (`Winbase.h.` -> `Winbase.h`); the `as_printed` column shows the verbatim forms. A value that names several files (`Bthapi.h, Bthapi.idl`) is kept as the page printed it — split it if you generate includes from it. |
| `kb/libraries.tsv` | Library -> entities (the link mapping). |
| `kb/dlls.tsv` | DLL -> entities. |
| `kb/modules.tsv` | sdk-api module -> entities (the Win32-side grouping; from each page's UID). |
| `kb/sets.tsv` | CE set -> entities, and how many of them have a declaration/header/library/DLL. |
| `reports/coverage-by-tree.tsv` | What each corpus tree contributed (pages, requirements, declarations). |
| `reports/coverage.tsv` | One row per entity: what is known about it. |
| `reports/gaps.tsv` | **The collection worklist**: every reference entity for which a declaration, a header or a library is still missing. |
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
  the requirement `field`/`key` and the declaration `language` are computed
  deterministically and documented as derived in the schema; the original label
  and text are always kept beside them.
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
| **How does it relate to other definitions?** | `relations`: `unicode-ansi` (the page's own "X (Unicode) and Y (ANSI)" statement), `unicode-ansi-base` (the base name the pair belongs to, derived from that statement), `interface-method` (`Interface::Method`, the vtable owner) and `layer` (documented by CE *and* the Win32 reference). Each entry names its target, whether that target is present in this file, the page and the printed text |
| **How can it be used to generate include/def?** | `generation_use` says which generator steps the record can feed — `include-declaration` (a syntax declaration plus a stated header), `type-definition` (struct/enum/union/typedef), `link-library` (a function/callback with a stated library or DLL), `def-export` (a function/callback with a stated DLL), `abi-layout` (a struct whose declaration lists members), `unicode-mapping`, `version-scope`, `ce-restriction` — and `kb/headers.tsv`/`libraries.tsv`/`dlls.tsv`/`modules.tsv` are the inverted maps. `generation_use` is rule-based (DERIVED); it says what the record *can* feed, never that the record is complete |

Nothing is invented: `present: false` in a relation means the other side was
never collected (a collection lead), and an entity with no `syntax_declarations`
appears in `reports/gaps.tsv` instead of getting a declaration from anywhere
else.

## How this becomes include / def material

The intended pipeline (nothing here generates those files yet — this layer is
the input to it):

1. **Include map.**  For a version target, take the entities whose `ce_sets`
   include that version, group them by `headers`, and use each entity's
   `syntax_declarations` as the declaration text.  `report/reports/gaps.tsv`
   tells you which entities would come out empty.
2. **Link map.**  `libraries` and `dlls` per entity give the library/DLL names a
   linker needs (`libraries.tsv` is the inverted view).
3. **Def/symbol worklist.**  The exports a `.def` file needs are the entities
   whose `generation_use` contains `def-export`/`link-library`, grouped by
   `libraries`/`dlls`; the `constraints` records and the `relations` of type
   `unicode-ansi`/`unicode-ansi-base` then say which of them exist in a given
   CE version and how the `A`/`W` spellings pair up.
4. **ABI facts.**  The declaration text carries the calling convention and the
   parameter/field types; struct bodies come with their `members` lines.  For a
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
```

`tools/build-kb.py` reads `data/index/INDEX.tsv` for the page list and
`data/reports/win32-imported.tsv` for the Win32 side; run `tools/build-index.py`
first when the corpus changed.  The extraction rules live in
`tools/page_parse.py` (one file, with the templates it knows documented at the
top).
