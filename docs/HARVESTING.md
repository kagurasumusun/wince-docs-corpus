# Harvesting

1. **Define scope** – edit `sources/sources.json`.
2. **Discover** – Actions → *Discover*. Modes: `learn-toc`, `wayback-cdx`, `archive-org`, `learn-links` (needs full checkout), `pending`, `all`. Writes `queues/sources/*`, `meta/catalogs/learn-toc-*.tsv`, `meta/harvest/discovery-report.json` (which sources answered, how many URLs). No documents are downloaded.
3. **Harvest** – Actions → *Harvest* (`queue = learn | wayback`). It builds `queues/pending/<queue>.txt` = all source queues − already harvested − remembered 404s, then fetches.

Why it is fast now
- Sparse + blobless checkout (~25 MB instead of 3.4 GB); "already have" comes from `git ls-tree` (0.1 s for 95k files).
- Parallel shards (`shards`), bounded workers/host, token-bucket rate limit, keep-alive, gzip.
- 404s remembered in `meta/harvest/notfound-*.txt`.
- Batched commits that `git add` only the new files; push runs in the background and retries with rebase, so shards can push concurrently.
- Stops at 330 min and re-dispatches itself (`chain` input) until the pending queue is empty.

Local run: `python3 tools/harvest.py --queue queues/pending/learn.txt --limit 100`.
Indexes: `python3 tools/build_index.py [--sqlite out.sqlite3]` (the *Index* workflow does this weekly).
