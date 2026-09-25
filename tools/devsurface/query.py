#!/usr/bin/env python3
"""tools/devsurface/query.py -- query the Development Surface database.

Reads devsurface/index/devsurface.sqlite3 (build it with
tools/devsurface/build_index.py). Every answer prints the page the facts came
from, so a result can be checked against the corpus immediately.

Examples:
  python3 tools/devsurface/query.py symbol GetTickCount
  python3 tools/devsurface/query.py header winbase --kind function --limit 20
  python3 tools/devsurface/query.py library coredll
  python3 tools/devsurface/query.py version windows-ce-1.0
  python3 tools/devsurface/query.py unknown calling_convention
  python3 tools/devsurface/query.py abi
  python3 tools/devsurface/query.py gaps declaration_candidate_mismatch --limit 30
  python3 tools/devsurface/query.py summary
  python3 tools/devsurface/query.py sql "SELECT symbol, header, library FROM symbols WHERE kind='macro' LIMIT 10"
"""

from __future__ import annotations

import argparse
import os
import sqlite3
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
DB = os.path.join(ROOT, "devsurface", "index", "devsurface.sqlite3")


def connect():
    if not os.path.exists(DB):
        sys.exit("database not found: %s\nbuild it with: python3 tools/devsurface/build_index.py"
                 % os.path.relpath(DB, ROOT))
    connection = sqlite3.connect(DB)
    connection.row_factory = sqlite3.Row
    return connection


def print_records(rows, limit):
    for index, row in enumerate(rows):
        if index >= limit:
            print("... (use --limit to see more)")
            break
        print("=" * 78)
        print("%s   [%s, %s]" % (row["symbol"], row["kind"], row["source_id"]))
        if row["scope"]:
            print("  scope        %s" % row["scope"])
        if row["declaration"]:
            print("  declaration  %s" % row["declaration"].replace("\n", " "))
        elif row["parse_status"] == "no_declaration_documented":
            print("  declaration  (not printed by the topic - recorded as a gap)")
        print("  header       %s" % (row["header"] or "(not documented)"))
        print("  library      %s" % (row["library"] or "(not documented)"))
        if row["version_raw"]:
            print("  version      %s -> %s%s" % (
                row["version_raw"], row["version_min_id"] or "unmapped",
                " (%s)" % row["version_qualifier"] if row["version_qualifier"] else ""))
        print("  page         %s" % row["page_path"])
        if row["source_url"]:
            print("  source       %s" % row["source_url"])
        if row["unknown_fields"]:
            print("  unknown      %s" % row["unknown_fields"])


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("command", choices=["symbol", "header", "library", "version",
                                            "kind", "unknown", "abi", "gaps", "summary",
                                            "sql", "params", "members"])
    parser.add_argument("argument", nargs="?")
    parser.add_argument("--limit", type=int, default=25)
    parser.add_argument("--kind", help="extra kind filter")
    parser.add_argument("--source", help="extra source_id filter")
    arguments = parser.parse_args()
    connection = connect()

    def rows(sql, parameters=()):
        return connection.execute(sql, parameters).fetchall()

    if arguments.command == "symbol":
        if not arguments.argument:
            sys.exit("symbol needs a name, e.g. query.py symbol GetTickCount")
        data = rows("SELECT * FROM symbols WHERE lower(symbol)=lower(?) ORDER BY source_id",
                    (arguments.argument,))
        if not data:
            data = rows("SELECT * FROM symbols WHERE lower(symbol) LIKE lower(?) "
                        "ORDER BY symbol, source_id", ("%" + arguments.argument + "%",))
        print_records(data, arguments.limit)
    elif arguments.command == "header":
        data = rows("SELECT * FROM symbols WHERE lower(header)=lower(?) "
                    "AND (? IS NULL OR kind=?) AND (? IS NULL OR source_id=?) "
                    "ORDER BY symbol, source_id",
                    (arguments.argument, arguments.kind, arguments.kind,
                     arguments.source, arguments.source))
        print_records(data, arguments.limit)
    elif arguments.command == "library":
        data = rows("SELECT * FROM symbols WHERE lower(library_all) LIKE lower(?) "
                    "AND (? IS NULL OR kind=?) ORDER BY symbol, source_id",
                    ("%" + (arguments.argument or "") + "%", arguments.kind, arguments.kind))
        print_records(data, arguments.limit)
    elif arguments.command == "version":
        data = rows("SELECT * FROM symbols WHERE version_min_id=? "
                    "AND (? IS NULL OR kind=?) ORDER BY symbol, source_id",
                    (arguments.argument, arguments.kind, arguments.kind))
        print_records(data, arguments.limit)
    elif arguments.command == "kind":
        data = rows("SELECT * FROM symbols WHERE kind=? ORDER BY symbol, source_id",
                    (arguments.argument,))
        print_records(data, arguments.limit)
    elif arguments.command == "unknown":
        field = arguments.argument or "calling_convention"
        data = rows("SELECT * FROM symbols WHERE unknown_fields LIKE ? "
                    "ORDER BY symbol, source_id", ("%" + field + "%",))
        print("%d records have no documented value for %s" % (len(data), field))
        print_records(data, arguments.limit)
    elif arguments.command == "abi":
        if arguments.argument:
            data = rows("SELECT * FROM abi_facts WHERE topic LIKE ? ORDER BY id",
                        ("%" + arguments.argument + "%",))
        else:
            data = rows("SELECT * FROM abi_facts ORDER BY topic, id")
        for row in data:
            print("=" * 78)
            print("%s  [%s]" % (row["id"], row["topic"]))
            print("  %s" % row["statement"])
            print("  page: %s" % row["page_path"])
            if row["note"]:
                print("  note: %s" % row["note"])
    elif arguments.command == "gaps":
        page_class = arguments.argument or "declaration_candidate_mismatch"
        data = rows("SELECT page_id, source_id, title, duplicate_of, path, declaration_status "
                    "FROM pages WHERE page_class=? ORDER BY source_id, page_id LIMIT ?",
                    (page_class, arguments.limit))
        print("%s: showing %d of %d" % (
            page_class, len(data),
            rows("SELECT COUNT(*) AS n FROM pages WHERE page_class=?", (page_class,))[0]["n"]))
        for row in data:
            print("  %-14s %-26s %-46s %s" % (row["page_id"], row["source_id"],
                                              (row["title"] or "")[:46], row["path"]))
    elif arguments.command == "summary":
        for label, sql in [
            ("symbol records", "SELECT COUNT(*) AS n FROM symbols"),
            ("documented symbols", "SELECT COUNT(DISTINCT lower(symbol)) AS n FROM symbols"),
            ("pages catalogued", "SELECT COUNT(*) AS n FROM pages"),
            ("page rows that produced records", "SELECT COUNT(*) AS n FROM pages WHERE page_class='symbol_page'"),
            ("abi facts", "SELECT COUNT(*) AS n FROM abi_facts"),
            ("records without a documented calling convention",
             "SELECT COUNT(*) AS n FROM symbols WHERE unknown_fields LIKE '%calling_convention%'"),
            ("records without a documented module",
             "SELECT COUNT(*) AS n FROM symbols WHERE unknown_fields LIKE '%module%'"),
            ("records with no declaration printed",
             "SELECT COUNT(*) AS n FROM symbols WHERE declaration IS NULL"),
            ("records with a deprecation statement",
             "SELECT COUNT(*) AS n FROM symbols WHERE deprecation_count > 0"),
        ]:
            print("%-46s %d" % (label, rows(sql)[0]["n"]))
        print()
        print("per source:")
        for row in rows("SELECT source_id, COUNT(*) AS n FROM symbols GROUP BY source_id ORDER BY n DESC"):
            print("  %-34s %d" % (row["source_id"], row["n"]))
    elif arguments.command == "params":
        if not arguments.argument:
            sys.exit("params needs a symbol name")
        data = rows("SELECT s.symbol, s.source_id, p.* FROM symbols s JOIN parameters p "
                    "ON p.symbol_id=s.id WHERE lower(s.symbol)=lower(?) "
                    "ORDER BY s.source_id, p.position", (arguments.argument,))
        for row in data:
            print("%-28s %-24s pos=%-4s %-18s %-8s %s" % (
                row["symbol"], row["source_id"], row["position"], row["name"] or "-",
                row["direction"] or "-", (row["description"] or "")[:70]))
    elif arguments.command == "members":
        if not arguments.argument:
            sys.exit("members needs a struct name")
        data = rows("SELECT s.symbol, s.source_id, m.idx, m.text_raw FROM symbols s "
                    "JOIN members m ON m.symbol_id=s.id WHERE lower(s.symbol)=lower(?) "
                    "ORDER BY s.source_id, m.idx", (arguments.argument,))
        for row in data:
            print("%-20s %-26s %2d  %s" % (row["symbol"], row["source_id"], row["idx"],
                                           row["text_raw"]))
    elif arguments.command == "sql":
        if not arguments.argument:
            sys.exit("sql needs a statement")
        data = rows(arguments.argument)
        if data:
            print(" | ".join(data[0].keys()))
        for row in data[:max(arguments.limit, 1)]:
            print(" | ".join("" if value is None else str(value)[:60] for value in row))
    return 0


if __name__ == "__main__":
    sys.exit(main())
