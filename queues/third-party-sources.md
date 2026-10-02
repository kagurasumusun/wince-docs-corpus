# Third-party sources: what is collected and what is not

The collection policy is *official Microsoft documentation first*, but for the
CE 1.0/2.0 era that material no longer has an official home: the product
documentation shipped on CDs, the MSDN Library editions, and the Knowledge
Base. The owner of this corpus therefore added the mirrors below as accepted
sources (2026-10) - they are filed under `corpus/msdn-library/` and
`corpus/kb/` so they stay distinguishable from Microsoft's own material.

## Accepted (see each tree's README for what was taken)

| Source | What is taken | Where it lands |
|--------|---------------|----------------|
| https://techshelps.github.io/ (github.com/techshelps/techshelps.github.io) | The seven MSDN Library sets that document Windows CE 1.0/2.0 (CEGUIDE, WCEMFC, WCEATL, VBCE, WCEDDK, VCCE, DNEMBED) | `corpus/msdn-library/techshelps/` (tools/import-techshelps.py) |
| https://github.com/jeffpar/kbarchive | The KnowledgeBase articles of the Windows CE product family | `corpus/kb/` (tools/import-kbarchive.py) |
| https://library.thedatadungeon.com/ | The Windows CE documentation of the MSDN Library April 2000 (its 1998/1992 editions can be added later) | `corpus/msdn-library/datadungeon-2000-04/` (tools/crawl-mirror.py, config queues/mirrors.tsv) |

Robots/usage notes: library.thedatadungeon.com/robots.txt disallows
AI-training crawlers (GPTBot, ClaudeBot, anthropic-ai, CCBot, Amazonbot,
Google-Extended) but not documentation crawlers; this corpus uses an honest
user agent, one request at a time, 2.5 s apart, and honours that file.
GitHub-hosted sources are cloned, not crawled.

## Not collected

Candidate sources that were looked at and deliberately left out - vendor
knowledge bases, blog posts and SDK downloads. They are CE-related but are
either commercial vendor material or not documentation:

* https://blog.ch3cooh.jp/entry/20130417/1366182420 (blog post)
* https://datalogic.github.io/wince-sdk/ (vendor SDK page)
* https://developer.toradex.com/windows-ce/knowledge-base/vf50-vf61-wec-software/ (vendor knowledge base)
