# Archived-source inventory

`data/sources/archive-sources.json` is the machine-readable inventory for the
six already-retained Windows CE archive groups. Run
`python3 tools/validate-source-records.py` after changing it.

## What this inventory establishes

* Each retained archive group has an explicit source locator, publisher,
  retrieval date, version scope, confidence, rights state, and provenance-file
  link.
* Archive records are **documentation evidence**. They do not establish an API
  declaration, import library, calling convention, structure layout, ordinal,
  or compatibility behavior.
* `unknown` architecture/toolchain values are intentional absence states, not
  desktop-Windows defaults. An API-specific research batch must resolve or
  retain those values independently.

## Coverage gaps and next research order

1. Normalize the CE 1.0 Multimedia Viewer and CE 5.0 CHM topic text while
   preserving source-to-topic provenance.
2. Produce per-topic source records for the extracted CE 3.0 HTML tree, using
   each topic's requirements rows rather than archive-level scope.
3. Add independent records for historical Microsoft Learn and Wayback MSDN
   pages; do not merge mirror records with the original media record.
4. For each proposed `akari-dev` declaration, build a neutral model from
   topic-level documentation plus independent header, export, or controlled
   observation evidence.

## Explicit non-coverage

This inventory does not catalog product binaries, OS images, BSP/OAL sources,
or SDK redistribution rights. Those are separate evidence and rights questions
and must not be inferred from documentation availability.
