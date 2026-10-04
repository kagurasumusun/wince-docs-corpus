#!/usr/bin/env python3
"""tools/gen-include-def.py -- prototype: knowledge/ -> include/def material.

This is the first consumer of the knowledge base, and it exists to prove the
pipeline end to end: take the machine-readable statements in ``knowledge/``,
filter them to one Windows CE version, and write the material an include/def
generator would be built from.

    python3 tools/gen-include-def.py --set learn/windows-ce-5.0 \
        --out build/generated/wince50
    python3 tools/gen-include-def.py --set chm/windows-ce-3.0 --out ... \
        --no-borrow            # only declarations from that set's own pages
    python3 tools/gen-include-def.py --list      # sets that can be generated

What it writes (nothing is added to the repository -- ``--out`` is yours):

    include/<Header>.h.fragment   the declarations of that header, verbatim,
                                  each with the page it was read from
    link/<Module>.def             EXPORTS material per library/DLL, with the
                                  source of every name (a *worklist*, see the
                                  warning the file itself carries)
    manifest.tsv                  entity <-> header files/libraries <-> declaration
                                  id <-> source page, for traceability
    report.md                     what was generated, what was skipped and why

Honesty rules (the same ones the knowledge base keeps):

* the declaration text is quoted verbatim; nothing is reformatted, completed
  or repaired.  A ``collapsed`` declaration is still written (with the flag in
  the manifest) and a better copy from another set is preferred when
  ``--borrow`` is on, but no text is invented either way;
* a declaration is borrowed from another corpus set only when the same entity
  is documented there, and the borrowing is recorded per declaration in
  ``manifest.tsv`` and in the fragment's comment;
* a page states a header as ``Wilhelm.h, Otto.h`` -- the declaration is
  written into each of those files, because that is what the page says; a
  value that names no file at all (``Library: Developer Implemented``) is
  *not* turned into a file name, it is counted in ``report.md`` and stays
  visible in ``knowledge/reports/filtered-values.tsv``;
* a library and a DLL are kept apart (``coredll.lib`` in the library field,
  ``coredll.dll`` in the DLL field) and the worklist file is named after the
  module both spellings refer to, with the spellings it was stated as printed
  at the top.  Only functions and callbacks become export lines -- a struct,
  a typedef or a C++ method (``Interface::Method``) is not an export;
* everything the documents do not state is left out and listed in
  ``report.md``: no header, no declaration, no library -> a gap to collect,
  never a guess;
* symbol decoration (the ``_Name@N`` spelling of an exported stdcall function),
  ordinals and export tables are *not* in the documentation, so the ``.def``
  output says so at the top instead of pretending to be complete.
"""

import argparse
import collections
import gzip
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
KB = os.path.join(ROOT, "knowledge", "kb")

DECLARATIONS = os.path.join(KB, "declarations.jsonl.gz")
ENTITIES = os.path.join(KB, "entities.jsonl.gz")

# The documentation prints header and library names as they are; these pull
# the file names out of a value and leave the prose alone.
HEADER_FILE = re.compile(r"[\w.+-]*\.(?:h|hpp|hh|hxx|idl|inc)\b", re.I)
MODULE_FILE = re.compile(r"(?P<base>[\w.+-]+?)\.(?P<ext>lib|dll|drv|sys|ocx|tlb)\b",
                         re.I)
EXPORTABLE = ("function", "callback")


def load(path):
    if not os.path.exists(path) and path.endswith(".gz"):
        path = path[:-3]
    if not os.path.exists(path):
        sys.exit(f"{os.path.relpath(path, ROOT)} not found -- run "
                 "python3 tools/build-kb.py first")
    opener = gzip.open if path.endswith(".gz") else open
    with opener(path, "rt", encoding="utf-8") as fh:
        for line in fh:
            line = line.strip()
            if line:
                yield json.loads(line)


def safe_name(value, extension=""):
    """A header/library value -> a file name.

    ``Winbase.h.`` -> ``Winbase.h``, and when the name already carries the
    extension the output adds (``Coredll.lib`` -> ``coredll.def``), it is
    dropped first so the file name is not doubled.
    """
    name = re.sub(r"[^A-Za-z0-9_.+-]", "_", value.strip().rstrip(". ")) \
        or "unnamed"
    if extension and name.lower().endswith(extension.lower()):
        name = name[:-len(extension)]
    return name or "unnamed"


def header_files(headers):
    """The file names inside the stated ``Header`` values, in stated order."""
    files = []
    for value in headers:
        for match in HEADER_FILE.findall(value):
            name = match.split("/")[-1].split("\\")[-1]
            if name and name.lower() not in [f.lower() for f in files]:
                files.append(name)
    return files


def module_of(value):
    """(module, extension) of a stated library/DLL value, or None."""
    match = MODULE_FILE.search(value or "")
    if not match:
        return None
    return match.group("base"), match.group("ext").lower()


def choose_declarations(entity, declarations_of, target, borrow):
    """Declarations for one entity, target set first.

    Returns (chosen, alternatives) where each chosen item is a declaration
    record.  A declaration of the target set always wins; when the entity is
    not declared there, one declaration from another set is borrowed (if
    allowed) and every alternative is reported so a reader can compare.
    """
    records = [declarations_of[did] for did in entity["syntax_declarations"]
               if did in declarations_of]
    own = [r for r in records if r["source"]["set"].startswith(target)]
    other = [r for r in records if r not in own]
    if own:
        return own, other
    if borrow and other:
        return other[:1], other[1:]
    return [], other


def write_includes(out, by_header, generated):
    include_dir = os.path.join(out, "include")
    os.makedirs(include_dir, exist_ok=True)
    for header, entries in sorted(by_header.items(), key=lambda kv: kv[0].lower()):
        path = os.path.join(include_dir, safe_name(header, ".h") +
                            ".h.fragment")
        lines = [
            f"/* {header} -- declarations documented for {generated['set']}",
            " *",
            " * Generated by tools/gen-include-def.py from wince-docs-corpus.",
            " * Every block below is quoted verbatim from the page named above",
            " * it; nothing here is written, completed or reformatted by the",
            " * generator.  This file is a *fragment*: include guards, include",
            " * order and the parts of the header the documentation does not",
            " * describe are the job of the generator built on top.",
            f" * {len(entries)} declaration(s).",
            " */",
        ]
        for entity, declaration in entries:
            libs = ", ".join(entity["libraries"] or entity["dlls"] or []) or "-"
            lines += [
                "",
                "/*" + "-" * 68,
                f" * {entity['name']}  [{', '.join(entity['kinds']) or '?'}]",
                f" * library: {libs}",
                f" * source: {declaration['source']['path']}",
            ]
            if not declaration["source"]["set"].startswith(generated["set"]):
                lines.append(f" * borrowed from: {declaration['source']['set']}"
                             " (this set does not declare it)")
            if declaration["spacing"] != "preserved":
                lines.append(" * NOTE: the page lost the spaces in this "
                             "declaration (spacing: collapsed) -- prefer "
                             "another page's copy")
            lines.append(" */")
            lines.append(declaration["text"])
        with open(path, "w", encoding="utf-8") as fh:
            fh.write("\n".join(lines) + "\n")
    return include_dir


def write_defs(out, by_module, generated):
    link_dir = os.path.join(out, "link")
    os.makedirs(link_dir, exist_ok=True)
    for module, worklist in sorted(by_module.items()):
        entries = worklist["entries"]
        path = os.path.join(link_dir, safe_name(module) + ".def")
        lines = [
            f"; {module} -- EXPORTS worklist for {generated['set']}",
            ";",
            "; Generated by tools/gen-include-def.py from wince-docs-corpus:",
            "; one line per function or callback whose page states this",
            "; module, with the page behind every name.  The name is the",
            "; documented name -- NOT the decorated symbol: the documentation",
            "; does not state the _Name@N spelling, the ordinal or the export",
            "; table of the real library, so verify each line against the SDK",
            "; before linking.",
            ";",
            f"; stated as: {', '.join(worklist['stated'])}",
            f"; {len(entries)} name(s)",
            "EXPORTS",
        ]
        for entity, declaration in entries:
            page = declaration["source"]["path"] if declaration else "-"
            kind = (entity["kinds"] or ["?"])[0]
            lines.append(f"    {entity['name']:32s}; {kind}  {page}")
        with open(path, "w", encoding="utf-8") as fh:
            fh.write("\n".join(lines) + "\n")
    return link_dir


def split_libraries(entity):
    """(libraries, dlls, modules, unstated) for one entity.

    ``modules`` maps the lower-case module name to the spellings the pages
    state (``coredll.lib`` and ``coredll.dll`` are one module).  ``unstated``
    counts values that name no file -- they are not a library, so they never
    become a worklist file.
    """
    modules = {}
    unstated = 0
    for value in entity["libraries"]:
        parsed = module_of(value)
        if parsed:
            modules.setdefault(parsed[0].lower(), set()).add(value)
        else:
            unstated += 1
    for value in entity["dlls"]:
        parsed = module_of(value)
        if parsed:
            modules.setdefault(parsed[0].lower(), set()).add(value)
        else:
            unstated += 1
    return modules, unstated


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--set", dest="target",
                    help="corpus set to generate for (learn/windows-ce-5.0)")
    ap.add_argument("--out", help="output directory (outside the repository)")
    ap.add_argument("--no-borrow", action="store_true",
                    help="do not use a declaration from another corpus set")
    ap.add_argument("--include-win32", action="store_true",
                    help="also emit entities the Win32 reference documents")
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--list", action="store_true",
                    help="list the corpus sets and their entity counts")
    args = ap.parse_args()

    if args.list:
        counts = collections.Counter()
        for entity in load(ENTITIES):
            for book in entity["ce_sets"]:
                counts[book] += 1
        for book, count in sorted(counts.items()):
            print(f"{book:44s} {count:7,} entities")
        return 0

    if not args.target or not args.out:
        ap.error("--set and --out are required (or use --list)")

    declarations_of = {d["id"]: d for d in load(DECLARATIONS)}
    entities = [e for e in load(ENTITIES)
                if not e.get("noise") and
                (args.target in e["ce_sets"] or
                 (args.include_win32 and e["win32_pages"]))]
    if args.limit:
        entities = entities[:args.limit]

    by_header = collections.defaultdict(list)
    by_module = collections.defaultdict(
        lambda: {"entries": [], "stated": set()})
    manifest = []
    skipped = collections.Counter()
    borrowed = 0
    pages = set()
    exports = 0

    for entity in sorted(entities, key=lambda e: e["name"].lower()):
        chosen, alternatives = choose_declarations(entity, declarations_of,
                                                   args.target,
                                                   not args.no_borrow)
        declaration = chosen[0] if chosen else None
        if declaration and not declaration["source"]["set"].startswith(
                args.target):
            borrowed += 1
        for record in chosen + alternatives:
            pages.add(record["source"]["path"])

        headers = header_files(entity["headers"])
        modules, unstated = split_libraries(entity)
        if not declaration:
            skipped["no declaration in the corpus"] += 1
        elif not entity["headers"]:
            skipped["no header stated"] += 1
        elif not headers:
            skipped["header value names no header file"] += 1
        else:
            for header in headers:
                by_header[header].append((entity, declaration))
        if unstated:
            skipped["library stated but naming no file"] += unstated

        # A C++ method (``Interface::Method``) is not an export, and only the
        # kinds a linker exports become EXPORTS lines.
        kinds = entity["kinds"] or []
        exportable = bool(kinds and kinds[0] in EXPORTABLE and
                          "::" not in entity["name"] and
                          " " not in entity["name"])
        for module, stated in modules.items():
            worklist = by_module[module]
            worklist["stated"] |= stated
            if not exportable:
                continue
            worklist["entries"].append((entity, declaration))
            exports += 1

        manifest.append((
            entity["id"], entity["name"], ";".join(kinds),
            ";".join(headers), ";".join(sorted(modules)),
            ";".join(entity["dlls"]), ";".join(entity["libraries"]),
            declaration["id"] if declaration else "",
            declaration["source"]["path"] if declaration else "",
            "borrowed" if declaration and not
            declaration["source"]["set"].startswith(args.target) else "",
            ";".join(sorted(entity["ce_sets"])),
        ))

    out = os.path.abspath(args.out)
    if out == ROOT or out.startswith(ROOT + os.sep) and \
            os.path.relpath(out, ROOT).split(os.sep)[0] not in ("build",):
        print(f"note: writing into the repository ({args.out}); generated "
              "material belongs outside corpus/ and knowledge/", file=sys.stderr)
    os.makedirs(out, exist_ok=True)
    generated = {"set": args.target, "pages": len(pages)}
    include_dir = write_includes(out, by_header, generated)
    link_dir = write_defs(out, by_module, generated)

    with open(os.path.join(out, "manifest.tsv"), "w", encoding="utf-8") as fh:
        fh.write("entity\tname\tkinds\theader_files\tmodules\tdlls\t"
                 "libraries\tdeclaration\tsource_page\tborrowed\tce_sets\n")
        for row in manifest:
            fh.write("\t".join(row) + "\n")

    report = [
        f"# Generation report -- {args.target}",
        "",
        f"* entities in scope: **{len(entities):,}**",
        f"* declarations written: "
        f"**{sum(len(v) for v in by_header.values()):,}** in "
        f"{len(by_header):,} header fragment(s) ({include_dir})",
        f"* of those borrowed from another set: **{borrowed:,}** "
        f"({'allowed' if not args.no_borrow else 'not allowed'})",
        f"* EXPORTS worklists: {len(by_module):,} module file(s) in {link_dir}, "
        f"**{exports:,} export line(s)** "
        "(functions and callbacks only; structures, typedefs and C++ methods "
        "stay in the include material)",
        f"* pages behind the output: {len(pages):,}",
        "",
        "## What was skipped",
        "",
        "| reason | entities |",
        "|--------|----------|",
    ]
    for reason, count in skipped.most_common():
        report.append(f"| {reason} | {count:,} |")
    report += [
        "",
        "The skipped entities are the collection worklist: their pages exist,",
        "they simply do not state the declaration, the header or the library.",
        "`knowledge/reports/gaps.tsv` has the same list with one row per",
        "entity and the set each one should be collected from, and",
        "`knowledge/reports/filtered-values.tsv` lists the library/DLL values",
        "that name no file (they are statements about the API, not libraries).",
    ]
    with open(os.path.join(out, "report.md"), "w", encoding="utf-8") as fh:
        fh.write("\n".join(report) + "\n")

    print(f"entities {len(entities):,}  header fragments {len(by_header):,}  "
          f"module files {len(by_module):,}  export lines {exports:,}  "
          f"borrowed {borrowed:,}")
    print(f"written to {out} (see report.md)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
