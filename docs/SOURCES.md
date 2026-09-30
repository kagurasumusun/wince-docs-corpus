# Sources (scope)

Authoritative list: `sources/sources.json`. Summary:

- **Microsoft Learn previous-versions** – TOC crawl (several candidate TOCs, unavailable ones are reported not fatal) + link closure from harvested pages.
- **Wayback MSDN** – CDX lookups over CE/Compact/Windows Mobile id ranges, restricted to ids known from the catalogs.
- **archive.org** – search for official CE/Platform Builder/eVC/Windows Mobile documentation media; candidates are listed in `meta/harvest/archive-org-candidates.tsv`, reviewed, then promoted to `known_items`.
- Products in scope: Windows CE 1.0–3.0, CE .NET 4.x, CE 5.0, Embedded CE 6.0, Compact 7/2013, Windows Mobile 2003–6.5, Pocket PC, Smartphone, H/PC, P/PC, Auto PC, .NET CF, .NET Micro Framework, SQL Server Compact, eVC/eVB, Platform Builder.

Not verified from the authoring sandbox (no access to learn.microsoft.com / web.archive.org): which candidate TOCs exist and what the CDX ranges return. Run *Discover* and read `meta/harvest/discovery-report.json`.
