# .actions/

Staging area for GitHub Actions workflow files that could not be installed
under `.github/workflows/` yet.

| File | Status |
|------|--------|
| `harvest.yml` | Updated `Windows CE Documentation Harvester` workflow for the reorganized tree (queues/, corpus/, tools/build-index.py, data/index/ + corpus/ + data/logs/). **Not executed by GitHub from here.** |

## Why the copy is here and not in .github/workflows/

GitHub only runs workflows from `.github/workflows/`, and any push that
creates, updates or deletes a file under that path is rejected unless the
pushing credential has the `workflows` permission. The credential available in
this working environment does not have it, so
`.github/workflows/harvest.yml` was deliberately left untouched and still
refers to the pre-reorganization paths (`urls/`, `docs/`,
`tools/make-index.py`, `data/harvest/`).

## Installing it

With a credential that has the `workflows` permission:

```bash
git mv .actions/harvest.yml .github/workflows/harvest.yml
git commit -m "harvest: install the updated workflow"
git push
```

Or paste the contents of `.actions/harvest.yml` into
`.github/workflows/harvest.yml` in the GitHub web UI. Review the `.github`
copy's pre-reorganization state before deleting it if you would rather keep a
history of the change.

Until then, run the harvester locally with the commands in the repository
`README.md`.
