#!/usr/bin/env python3
"""tools/build-ce-api-names.py -- write data/reports/ce-api-names.tsv.

The reviewable evidence behind the Win32-common surface: one row per API name
that Windows CE documents, with the CE pages that document it and the source
(catalog or mined set) each name came from.  ``tools/ce_api_names.py`` explains
how the names are assembled; this tool only prints them.

    python3 tools/build-ce-api-names.py            # write the report
    python3 tools/build-ce-api-names.py --check    # fail if it is stale

    # a name in the report
    grep -P '^createfile\t' data/reports/ce-api-names.tsv

Columns: name <TAB> ce_sets <TAB> ce_page_ids <TAB> sources
  name          normalised API name (``createfile``)
  ce_sets       CE sets that document it (``windows-ce-5.0;...``)
  ce_page_ids   page ids of the CE pages documenting it (``;`` separated,
                truncated at 8 with a trailing ``…``)
  sources       how the name was found: ``catalog`` (the official catalog of a
                harvested set) and/or ``corpus`` (extracted from the pages of
                an uncatalogued CE set)
"""

import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import ce_api_names  # noqa: E402

ROOT = ce_api_names.ROOT
REPORT = os.path.join(ROOT, "data", "reports", "ce-api-names.tsv")
MAX_IDS = 8


def set_name(section):
    """``msdn-library/techshelps/WCEMFC`` -> ``techshelps/WCEMFC``."""
    parts = section.split("/")
    if parts[0] == "learn":
        return parts[1] if len(parts) > 1 else parts[0]
    if parts[0] == "dotnet":
        return "dotnet/" + (parts[1] if len(parts) > 1 else parts[0])
    if parts[0] == "msdn-library":
        return "/".join(parts[1:3]) if len(parts) > 2 else parts[-1]
    if parts[0] == "chm":
        return "/".join(parts[1:]) if len(parts) > 1 else parts[0]
    if parts[0] == "mvb":
        return "/".join(parts[1:]) if len(parts) > 1 else parts[0]
    return section


def rows():
    names = ce_api_names.load_names()
    for name in sorted(names):
        entry = names[name]
        sets, ids, sources = set(), [], set()
        for page_id, _title, book in sorted(entry.get("catalog", ())):
            sets.add(book)
            ids.append(page_id)
            sources.add("catalog")
        for page_id, _title, section in sorted(entry.get("corpus", ())):
            sets.add(set_name(section))
            ids.append(page_id)
            sources.add("corpus")
        unique = list(dict.fromkeys(ids))
        shown = ";".join(unique[:MAX_IDS])
        if len(unique) > MAX_IDS:
            shown += ";… (%d more)" % (len(unique) - MAX_IDS)
        yield name, ";".join(sorted(sets)), shown, "+".join(sorted(sources))


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--check", action="store_true",
                    help="do not write; exit 1 when the report is stale")
    args = ap.parse_args()

    lines = ["# name\tce_sets\tce_page_ids\tsources"]
    lines += ["\t".join(row) for row in rows()]
    text = "\n".join(lines) + "\n"

    if args.check:
        current = ""
        if os.path.isfile(REPORT):
            with open(REPORT, encoding="utf-8") as fh:
                current = fh.read()
        if current != text:
            print("data/reports/ce-api-names.tsv is stale "
                  "(run tools/build-ce-api-names.py)", file=sys.stderr)
            return 1
        print("data/reports/ce-api-names.tsv is up to date (%d names)"
              % (len(lines) - 1))
        return 0

    os.makedirs(os.path.dirname(REPORT), exist_ok=True)
    with open(REPORT, "w", encoding="utf-8") as fh:
        fh.write(text)
    print("data/reports/ce-api-names.tsv: %d names" % (len(lines) - 1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
