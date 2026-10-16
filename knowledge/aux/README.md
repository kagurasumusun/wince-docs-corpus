# `aux/` -- the isolated weak-auxiliary pinvoke material

The files here are **not** part of the specification in `kb/`: they are the
machine-readable residue of the **one third-party exception** in
`docs/COLLECTION-POLICY.md`, the pinvoke P/Invoke reference, and they are
kept strictly separate from the official-documentation knowledge base.
They are consumed as **weak auxiliary evidence only**: where Microsoft's own
pages state nothing about a constant's header, a pinvoke statement may
*hint* at the linkage (`strength: "pinvoke-weak"` in
`kb/constant-headers.tsv`) so the gap is visible and decisions can be
reviewed; it never overrides a documented statement, it is always labelled,
and the rules are in `data/license-scopes.tsv`.  A pinvoke value is not
treated as a Windows CE fact.  `tools/pinvoke_gaps.py` may emit one
integer `#define` at last rank when a CE page names the constant and
no CE, Win32 CC-BY, or w32api public-domain number exists (MIT).  The
review report `reports/constant-pinvoke-review.tsv` still compares
community values with documented CE ones.

Two accept paths feed this directory, both isolated:

* `sources/dotnet-pinvoke/` -- the pinned, archived github.com/dotnet
  /pinvoke snapshot (MIT), parsed by `tools/pinvoke_extract.py` into
  constants (`public const`/`enum` member) and API (`[DllImport]`) rows.
  Each record quotes the verbatim `.cs` line with its archive member and
  line number; `header` is DERIVED from the module directory (the Windows
  library project the name is filed under -- a weak hint by design).
* `corpus/pinvoke/` -- the pinvoke.net user wiki, queue-gated by
  `queues/pinvoke-net.txt` (currently empty: not harvested).

| File | Contents |
|------|----------|
| `pinvoke-apis.jsonl.gz` | one row per API: `name`, `module`, `dll` (the DllImport text, when it names one), `header` (derived), `evidence`, `source` (archive member + line) |
| `pinvoke-constants.jsonl.gz` | one row per constant: `name`, `value` as printed, `value_eval` (best-effort fold, marked), `module`, `header` (derived), `table`, `row` (the quote), `source` |
| `pinvoke-apis.tsv` / `pinvoke-constants.tsv` | flat review views of the same rows |
