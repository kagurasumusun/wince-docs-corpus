# .actions/

Staging area for GitHub Actions workflows that are not (yet) installed under
`.github/workflows/`.

| File | Status |
|------|--------|
| `harvest.yml` | `Windows CE Documentation Harvester`, current tooling: `queues/`, `tools/build-index.py`, `--dry-run` input, refresh of the Win32 map report, `corpus/` + `data/index/` + `data/logs/` staged. |
| `import-win32.yml` | `Refresh Win32-shared documentation`: re-extract `corpus/win32/` from the pinned MicrosoftDocs commits, optionally rebuild the snapshot tarball, refresh reports and indexes, commit/push. |

Both are **not executed by GitHub from here** — GitHub only runs workflows
under `.github/workflows/`.

## Why the copies live here

Any push that creates, updates or deletes a file under `.github/workflows/`
is rejected unless the pushing credential has the `workflows` permission.
The credential available in this working environment does not have it, so the
workflows are staged here instead of being pushed to that path. (The harvest
workflow in `.github/workflows/harvest.yml` was updated to the reorganized
paths by the repository owner, so the `.actions/harvest.yml` copy differs only
in the extra steps listed above.)

## Installing

With a credential that has the `workflows` permission:

```bash
git mv .actions/harvest.yml .github/workflows/harvest.yml
git mv .actions/import-win32.yml .github/workflows/import-win32.yml
git commit -m "ci: install the updated workflows"
git push
```

or paste the file contents into the corresponding file in the GitHub web UI.

Until then, run the same commands locally (see the repository `README.md`):
`python3 tools/harvest.py …`, `python3 tools/fetch-upstream.py …`,
`python3 tools/build-index.py`, `python3 tools/build-index-sql.py`,
`python3 tools/build-win32-map.py`.
