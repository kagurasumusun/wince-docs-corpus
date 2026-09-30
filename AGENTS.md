# Policy (humans and agents)

1. Collect **official Microsoft public documentation only** (Learn, archived MSDN via Wayback, official media). Third-party links live in `sources/reference-links.txt` and are never harvested.
2. Documents only: no ISOs, binaries, SDK installers (`corpus/archives/*/PROVENANCE.md` states each source).
3. Be polite: rates are set in `tools/harvest.py` (`HOST_DEFAULTS`), adaptive back-off on 429/503 must stay. Do not raise them without a reason.
4. Layout rules are in `docs/LAYOUT.md` and enforced by `tools/verify_layout.py` (CI). New top-level dirs need a rule change first.
5. Scope is data, not code: change `sources/sources.json`, run the *Discover* workflow.
6. Never commit generated binaries (`*.sqlite3`) or secrets. Never commit under `corpus/` by hand except via `tools/harvest.py` or a documented import.
