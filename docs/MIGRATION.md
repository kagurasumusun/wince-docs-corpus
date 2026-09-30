# Migration 2026-10-01

Old tree = tag `pre-restructure-20261001`. All moves are pure renames (history of content preserved).
Consumers (`wince-api`) must switch prefixes per `meta/path-map.tsv`; file-level exceptions are in `meta/path-renames.tsv`.
Quick form: `docs/mslearn/` → `corpus/learn/`, `docs/wayback-msdn/2010-05/` → `corpus/wayback/msdn-2010-05/`,
`data/*` → `meta/*`, `archives/` → `corpus/archives/`, `urls/` → `queues/sources/`.
`corpus.sqlite3` moved to Release `index-latest`.
