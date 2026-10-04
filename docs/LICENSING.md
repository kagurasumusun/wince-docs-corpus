# Licensing — per item, from the statement that actually attaches to it

The collection keeps one published documentation page per file in `corpus/`
(121,039 pages), and the pages were not all published under the same terms.
The rule of this project is therefore: **handle each item according to the
licence text that actually attaches to it, and never substitute a general
assumption or a summary for that text.**

The rule is implemented, not promised:

| Artefact | What it is |
|----------|------------|
| `data/license-scopes.tsv` | The rights registry. One row per rule (a directory prefix, or `file:` for a single file), each carrying **the wording itself quoted**, the file it was read from, what is permitted, the conditions, and the finding (`yes`/`no`/`unclear`). The longest matching rule governs, so a file rule overrides its tree. |
| `sources/terms/` | Statements that are not in the repository as a file of their own (the Microsoft Learn Terms of Use excerpt), quoted verbatim with the URL and the date read. |
| `license` on every record | Every declaration, requirement and constraint record carries the scope id of the page it came from; every entity carries `licenses` (all the pages that document it — one name can have a CE page and a Win32 page under different statements). |
| `tools/check-licenses.py` | Checks the registry: every corpus page and every tracked file resolves to exactly one rule; every quoted statement is found, verbatim, in the file it names; and counts what is published. |
| `knowledge/reports/license-audit.tsv` | The result: pages and published files per scope, with the permission and the terms. |
| `docs/LICENSING.md` (this file) | The finding, and the decision that is still open. |

Every record names its page, and that page's terms govern the record (the
registry's own sheet for `docs/` quotes this sentence as the basis). The
knowledge base is not a new work under a new licence: it is a set of facts and
quotes, each traceable to one page.

## The finding (`python3 tools/check-licenses.py --tracked`, 2026-10-05)

```
published (git-tracked) files by redistribution: yes 5,285, no 115,934, unclear 133
```

| Scope | Covers | The statement it rests on (as read from the item) | May be published |
|-------|--------|---------------------------------------------------|------------------|
| `sdk-api-cc-by-4.0` | 5,279 Win32 reference pages + `sources/microsoftdocs/` | `sources/microsoftdocs/sdk-api/LICENSE`: "Attribution 4.0 International" (CC-BY-4.0; the code licence of the same snapshot is MIT, `LICENSE-CODE`) | **yes**, with attribution, a link to the licence and an indication of changes |
| `learn-tou` | `corpus/learn/` 58,046 + `corpus/dotnet/` 10,657 | Microsoft Learn Terms of Use: "use of such Documents from the Services is for informational and non-commercial or personal use only and **will not be copied or posted on any network computer**"; "You may not modify, copy, distribute, transmit, publicly display, perform, reproduce, publish … without prior written consent from Microsoft." (`sources/terms/learn-com-termsofuse-excerpt.txt`) | no |
| `ce30-internal-reference` | 8,962 pages of the CE 3.0 archive + the archive | The retired-content notice on every page: "You may copy and use this document for your internal, reference purposes." — and, in the same sentence, "does not provide you with any legal rights to any intellectual property in any Microsoft product" | no (internal reference use) |
| `ms-media-copyright` | CE 1.0 / 2.0 / 4.2 / 5.0 / 6.0 media (CHM, MVB, release notes), 23,302 files | **No licence statement located.** What is there is a notice, and CE 6.0's release notes state a restriction: "Without limiting the rights under copyright, no part of this document may be reproduced, stored in or introduced into a retrieval system, or transmitted in any form or by any means … without the express written permission of Microsoft Corporation." | no (treated as all rights reserved) |
| `mvb-third-party-notice` | 1 page of the CE 1.0 Pegasus SDK | The page's own Hitachi/HMSI notice: "No one is permitted to reproduce or duplicate, in any form, the whole or part of this document without Hitachi's permission." | no |
| `kb-article-copyright` | 257 Knowledge Base articles | "Copyright Microsoft Corporation" on every article | no |
| `msdn-library-copyright` | 14,678 MSDN Library captures | "© 2011 Microsoft. All rights reserved." where a notice is present (143 of 14,678 pages) | no |
| `site-copyright` | 25 pages of the CE 2.0 CD site mirror | "© 1997 Microsoft Corporation. All rights reserved." | no |
| `derived-from-sources` | `knowledge/`, `data/` | No separate statement: each record names its page, and that page's terms govern the record | per record |
| `project-own` | `tools/`, `docs/`, `queues/`, `.github/`, the READMEs | **The repository publishes no LICENSE file** — its own licence is undecided | undecided |

Every quote above is checked against the file it was read from
(`tools/check-licenses.py`; HTML pages are read the way the corpus reads them,
whitespace aside). A summary is never used in place of the wording.

## What this means

* As a **public** repository, 115,934 of the 121,352 files it carries are not
  licensed for redistribution. The Learn terms forbid copying the pages onto a
  network computer; the CE 3.0 notice grants internal reference use only; for
  the CHM/MVB media no permission statement was located at all.
* That is a property of the **publication**, not of the collection. Keeping the
  pages and the knowledge built from them for one's own use is what the CE 3.0
  notice describes, and the Learn terms allow personal, non-commercial use.
* The one part that is unambiguously publishable today is the CC-BY-4.0 Win32
  reference (5,285 files) — and it too carries the attribution obligation.
* Knowing a declaration's text is not the same as being allowed to publish it:
  the quotes in `knowledge/kb/declarations.jsonl` are as restricted as the
  pages they come from.
* Learning the Win32 terms' priority clause — "Certain documentation may be
  subject to explicit license terms separate from the terms contained here. To
  the extent the terms conflict, the explicit license terms control." — is why
  the registry decides by longest match: `corpus/win32/` is CC-BY-4.0, not
  Learn terms.

## What the project does about it

1. **Measure, per item.** `tools/check-licenses.py --tracked` is the audit;
   `knowledge/reports/license-audit.tsv` is the committed result.
2. **Make the gate available.** `--fail-on-restricted` exits non-zero while
   anything that may not be published is tracked. It is *not* enabled in CI:
   the decision is the owner's, and the report is what CI keeps.
3. **Do not publish what is generated.** `tools/gen-include-def.py` writes into
   a git-ignored `build/`, and its report lists the rights scopes behind the
   output, so an export can be filtered before it leaves the machine.
4. **Do not launder the terms into the facts.** `unclear` and `no` are recorded
   as they are; a media whose statement was not located is treated as all rights
   reserved rather than rounded up to something convenient.

## The decision that is still open

* Make the repository **private** while it carries the restricted trees, or
* keep it public and **move the restricted trees (and the quotes taken from
  them) out of it**, publishing only the CC-BY-4.0 part, or
* obtain **written permission** from Microsoft for the CE material.

Until one of those is chosen, nothing in this repository asserts a right it does
not have. `docs/review-2026-10.ja.md` §14 records the finding for the owner.

## Limits

This page records what the statements say and what the tools check. It is not
legal advice, and it does not cover patents, trademarks or trade secrets —
those are separate from copyright and are not addressed by the statements
above. Where the registry says "no licence statement located", the safe reading
(all rights reserved) is used.
