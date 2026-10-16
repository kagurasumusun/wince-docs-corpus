# Unified include/def surface -- report

ONE tree for every Windows CE generation.  Per-generation trees are
not written anywhere in this build: where generations differ, the
tree carries a derived `_WIN32_WCE` branch (the version macro the
documentation itself prints; the set -> interval wiring is
documented in tools/gen-include-def.py and is derived structure,
not a quotation).  The Win32-shared half of the surface lives in
the SAME tree, marked 'Win32 reference' -- never a second tree.

## What was generated

* entities in scope: **29,161** (by surface: `ce-only` 24,666, `shared` 4,495)
* header fragments: **650** under `include/`, each
  with its documented constants first, then the macros, the types
  and the functions; quoted text is verbatim, the `#define`
  keyword and the header/constant filing are derived and say so
* derived `#define` lines written: **28,747**
* derived member outlines (structures whose body no page prints):
  **564** -- marked DERIVED in the fragment
* constants whose pages disagree / overlap: **33** name(s) examined in `kb/constant-conflicts.tsv`
  (2 of them reach a header fragment in this build;
  **0** resolved by the review in
  `data/constant-value-review.tsv` to a print the pages themselves
  state, the rest get no `#define` -- every one keeps its
  CONFLICT block with the verdict)
* constants with no header linkage at all: **1,986**
  (worklist only -- they stay in `constants.tsv`)
* module `.def` worklists: **266** under `link/`
  (per-line version range is a comment; `.def` has no
  conditionals)
* printed export ordinals: 1 file(s),
  94 name(s)
* declarations taken from the Win32 reference because no CE page
  prints one: **111** -- every
  one marked in the fragment and the manifest; CE and desktop
  values are never assumed equal
* constants numbered only by the Win32 shared reference (and only
  for names a CE page documents): **2,046** -- same
  tree, every one marked 'verify against the CE SDK'; a number a
  CE page prints always wins
* spacing-only repairs across CE generations: **0**
* pages behind this output: 8,325

## Constant/header linkage (kb/constant-headers.tsv)

Ranks consumed by this build (best rank per name: the CE
documentation always outranks the Win32 desktop reference, which
outranks the co-mention evidence and the pinned reference
headers, and everything outranks the pinvoke weak auxiliary
hint):

| rank | link rows |
|------|----------:|
| own-page | 4,466 |
| entity-page | 1,366 |
| constant-entity | 63 |
| win32-reference | 1,636 |
| co-mention | 20 |
| reference-header | 1,632 |
| heuristic-prefix | 123 |
| pinvoke-weak | 18 |

The reference-header ranks come from the pinned, licence-vetted
public references under `sources/`: their header files *define*
the name (the row quotes tarball!member), so they say which
header the name sits in.  No value is ever taken from them --
every `#define` number above is a CE documentation quotation.

## The isolated weak-auxiliary pinvoke reference

* aux API rows: **588**, aux constant rows:
  **4,498** (`knowledge/aux/`, isolated from
  the specification; accept paths: the pinned dotnet/pinvoke
  snapshot under `sources/dotnet-pinvoke/` and, not yet harvested,
  the user wiki under `corpus/pinvoke/`)
* what they are used for: ONLY the weakest constant/header
  linkage rank above, consumed so that the gap between official
  documentation and community reference is reviewable;
  **18** linkage rows rest on
  them directly, each loudly marked in its header comment, and
  `reports/constant-pinvoke-review.tsv` compares every such
  community value with the documented CE value
* what they are never used for: no value ever comes from the
  pinvoke material (values are CE-page quotations only), no
  entity, no declaration, no requirement is minted from it, and
  no pinvoke statement overrides a documented one
* Win32-only numbers seen but not used: **2,241**
  constants (CE and desktop values are not assumed to match)

## The wall this generator keeps

* the corpus pages read by this generator: **0**
  (the generator reads `knowledge/` only; see docs/clean-room.md)

## What was skipped

| reason | entities |
|--------|----------|
| no declaration in the corpus | 20,583 |
| declaration is not a C declaration | 17,071 |
| no header stated | 5,510 |
| no CE version evidence | 1,504 |

The skipped entities are the collection worklist, same as in the
per-version build: `knowledge/reports/gaps.tsv` has the per-entity
rows, and `constants.tsv` here lists every numbered constant whose
header linkage is still missing.
