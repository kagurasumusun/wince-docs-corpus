#!/usr/bin/env python3
"""tools/devsurface/collect_abi_facts.py -- collect ABI statements from the corpus.

The Development Surface database records ABI fields as `unknown` unless a page
states something. This tool collects the pages that *do* state something
(structure packing, alignment, name decoration, exports, module definition
files, byte order, parameter passing, entry points) and stores, for each
curated fact, the statement **verbatim from the page** together with the page
locator.

The list of facts below is curated (a human chose which statements matter), but
the text is always extracted from the page by the tool: if an anchor cannot be
found, the tool fails instead of writing a fact it could not verify.

Usage:
  python3 tools/devsurface/collect_abi_facts.py [--check]

Output: devsurface/data/abi/abi-facts.jsonl
"""

from __future__ import annotations

import argparse
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import extract as E  # noqa: E402
import vocab  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
OUT = os.path.join(ROOT, "devsurface", "data", "abi", "abi-facts.jsonl")

# topic: packs facts that answer the same question.
# extract: {"mode": "sentence", "anchor": str, "sentences": n} or
#          {"mode": "table", "index": n}
FACTS = [
    # -- structure packing and alignment ---------------------------------
    {
        "id": "abi-structure-packing-rule-ce5", "topic": "structure_packing_alignment",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/ms924244.html",
        "extract": {"mode": "sentence", "anchor": "If the packsize is set equal to or greater than the default alignment", "sentences": 3},
        "note": "Compiler behaviour documented for the Windows CE 5.0 compiler.",
    },
    {
        "id": "abi-structure-packing-rule-ce6", "topic": "structure_packing_alignment",
        "source_id": "mslearn-windows-embedded-ce-6.0",
        "page": "docs/mslearn/windows-embedded-ce-6.0/ee479299.html",
        "extract": {"mode": "sentence", "anchor": "If the packsize is set equal to or greater than the default alignment", "sentences": 3},
        "note": "Same statement documented for Windows Embedded CE 6.0.",
    },
    {
        "id": "abi-pragma-pack-1-alignment", "topic": "structure_packing_alignment",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/ms924244.html",
        "extract": {"mode": "sentence", "anchor": "in a structure declared under #pragma pack(1)", "sentences": 1},
        "note": "Effect of the pack pragma on member alignment.",
    },
    {
        "id": "abi-zp-default-alignment", "topic": "structure_packing_alignment",
        "source_id": "mslearn-windows-ce-net-4x",
        "page": "docs/mslearn/windows-ce-net-4x/ms864512.html",
        "extract": {"mode": "sentence", "anchor": "Ordinarily, when storage is allocated for structures", "sentences": 1},
        "note": "Default structure member alignment.",
    },
    {
        "id": "abi-zp-option-boundaries", "topic": "structure_packing_alignment",
        "source_id": "mslearn-windows-ce-net-4x",
        "page": "docs/mslearn/windows-ce-net-4x/ms864512.html",
        "extract": {"mode": "sentence", "anchor": "each structure member after the first is stored on", "sentences": 1},
        "note": "Allowed pack sizes.",
    },
    {
        "id": "abi-unaligned-keyword-ce5", "topic": "alignment_rules",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/ms937758.html",
        "extract": {"mode": "sentence", "anchor": "The __unaligned keyword is a type modifier", "sentences": 3},
        "note": "Documented alignment requirement and the __unaligned escape hatch.",
    },
    {
        "id": "abi-unaligned-keyword-ce6", "topic": "alignment_rules",
        "source_id": "mslearn-windows-embedded-ce-6.0",
        "page": "docs/mslearn/windows-embedded-ce-6.0/ee480166.html",
        "extract": {"mode": "sentence", "anchor": "The __unaligned keyword is a type modifier", "sentences": 3},
        "note": "Same statement documented for Windows Embedded CE 6.0.",
    },
    # -- name decoration and linker names --------------------------------
    {
        "id": "abi-linker-name-composition", "topic": "name_decoration",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/aa449609.html",
        "extract": {"mode": "sentence", "anchor": "By default, C++ uses the function name, parameters, and return type", "sentences": 1},
        "note": "What enters a linker name.",
    },
    {
        "id": "abi-linker-names-by-calling-convention", "topic": "name_decoration",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/aa449609.html",
        "extract": {"mode": "table", "index": 0},
        "note": "Documented linker name for each calling convention and language form.",
    },
    {
        "id": "abi-decorated-name-content", "topic": "name_decoration",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/ms924281.html",
        "extract": {"mode": "sentence", "anchor": "The following information is contained in a decorated name", "sentences": 3},
        "note": "What a C++ decorated name encodes.",
    },
    {
        "id": "abi-decorated-name-examples", "topic": "name_decoration",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/ms924281.html",
        "extract": {"mode": "table", "index": 0},
        "note": "Documented example pairs of undecorated and decorated C++ names.",
    },
    # -- exports, .def, libraries ----------------------------------------
    {
        "id": "abi-module-definition-file-ce5", "topic": "module_definition_file",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/ms923590.html",
        "extract": {"mode": "sentence", "anchor": "A module-definition (.def) file is a text file", "sentences": 2},
        "note": "What a .def file is used for.",
    },
    {
        "id": "abi-module-definition-file-ce6", "topic": "module_definition_file",
        "source_id": "mslearn-windows-embedded-ce-6.0",
        "page": "docs/mslearn/windows-embedded-ce-6.0/ee478878.html",
        "extract": {"mode": "sentence", "anchor": "A module-definition (.def) file is a text file", "sentences": 2},
        "note": "Same topic for Windows Embedded CE 6.0.",
    },
    {
        "id": "abi-def-linker-option", "topic": "module_definition_file",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/aa449722.html",
        "extract": {"mode": "sentence", "anchor": "This option passes a module-definition file", "sentences": 2},
        "note": "Linker option that consumes a .def file.",
    },
    {
        "id": "abi-export-by-name", "topic": "export_mechanism",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/aa449735.html",
        "extract": {"mode": "sentence", "anchor": "This option allows you to export a function from your program", "sentences": 2},
        "note": "Entry name versus internal name.",
    },
    {
        "id": "abi-export-ordinal-noname", "topic": "export_mechanism",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/aa449735.html",
        "extract": {"mode": "sentence", "anchor": "The ordinal specifies an index into the exports table", "sentences": 2},
        "note": "Export ordinals and the NONAME keyword.",
    },
    {
        "id": "abi-defaultlib-search-order", "topic": "link_library_resolution",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/aa449721.html",
        "extract": {"mode": "sentence", "anchor": "A library specified with /DEFAULTLIB is searched after", "sentences": 1},
        "note": "How a linker finds the library that provides a symbol.",
    },
    # -- byte order --------------------------------------------------------
    {
        "id": "abi-byte-order-winsock-spi-ce5", "topic": "byte_order",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/ms880976.html",
        "extract": {"mode": "sentence", "anchor": "A service provider should treat all sockaddr calls", "sentences": 1},
        "note": "Byte-order rule stated for the Winsock service provider interface.",
    },
    {
        "id": "abi-little-endian-registry-value", "topic": "byte_order",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/ms904871.html",
        "extract": {"mode": "sentence", "anchor": "stored in memory from the lowest byte", "sentences": 1},
        "note": "Little-endian layout stated for a 32-bit registry value.",
    },
    # -- architecture-specific call and return rules ----------------------
    {
        "id": "abi-arm-parameter-passing", "topic": "parameter_passing",
        "source_id": "mslearn-windows-ce-net-4x",
        "page": "docs/mslearn/windows-ce-net-4x/ms881422.html",
        "extract": {"mode": "sentence", "anchor": "a calling function passes them as 32-bit words", "sentences": 2},
        "note": "Documented argument sizes for the ARM target.",
    },
    {
        "id": "abi-arm-prolog-stack-frame", "topic": "stack_frame",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/aa448590.html",
        "extract": {"mode": "sentence", "anchor": "4-byte aligned offset from R13", "sentences": 1},
        "note": "Documented stack frame allocation for the ARM target.",
    },
    {
        "id": "abi-sh4-prolog-stack-frame", "topic": "stack_frame",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/ms925517.html",
        "extract": {"mode": "sentence", "anchor": "4-byte aligned offset from R15", "sentences": 1},
        "note": "Documented stack frame allocation for the SH-4 target.",
    },
    {
        "id": "abi-arm-thumb-interworking-directives", "topic": "instruction_sets",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/aa448594.html",
        "extract": {"mode": "table", "index": 0},
        "note": "Assembler directives that select the ARM instruction set.",
    },
    # -- entry points ------------------------------------------------------
    {
        "id": "abi-crt-entry-points-ce6", "topic": "entry_points",
        "source_id": "mslearn-windows-embedded-ce-6.0",
        "page": "docs/mslearn/windows-embedded-ce-6.0/ee479912.html",
        "extract": {"mode": "sentence", "anchor": "For a DLL, the default entry point is", "sentences": 2},
        "note": "Default image entry points for DLLs and EXEs.",
    },
    {
        "id": "abi-device-driver-entry-point-naming", "topic": "entry_points",
        "source_id": "mslearn-windows-ce-5.0",
        "page": "docs/mslearn/windows-ce-5.0/ms923699.html",
        "extract": {"mode": "sentence", "anchor": "Device Manager uses the XXX prefix", "sentences": 2},
        "note": "Documented stream-interface entry point naming, including the undecorated alternative.",
    },
]


def flatten(page_path):
    with open(page_path, encoding="utf-8", errors="replace") as handle:
        html = handle.read()
    soup = E.load_soup(html)
    content = E.prune(E.content_root(soup))
    return E.node_text(content), content


LEADING_JUNK = re.compile(
    r"^(?:Send\s+Feedback|Feedback|In this article|Table of contents|Read in English|"
    r"Add to Plans|Copy Markdown|Print|Ask Learn|Exit editor mode|Note|"
    r"\d{1,2}/\d{1,2}/\d{2,4}|\d+\)|Access to this page[^.]*\.|"
    r"You can try signing in[^.]*\.|[^.]{0,140}?\((?:Windows|Compact|Microsoft)[^)]*\)|"
    r"/[A-Z]+(?::[A-Za-z<>{|}\[\]]+)?\s*(?:Remarks\s*)?|Supports?\s+|\s)+",
    re.I)


def clean_lead(text):
    text = E.ws(text)
    for _ in range(6):
        cleaned = LEADING_JUNK.sub("", text)
        if cleaned == text:
            break
        text = cleaned
    return text


def sentence_window(text, anchor, count):
    index = text.find(anchor)
    if index < 0:
        return None
    window_start = max(0, index - 400)
    terminators = list(re.compile(r"[.!?](?=\s|$)").finditer(text, window_start, index))
    start = terminators[-1].end() if terminators else window_start
    cursor = 0
    position = index
    while cursor < count:
        match = re.compile(r"[.!?](?=\s|$)").search(text, max(position, index))
        if not match:
            position = len(text)
            break
        position = match.end()
        cursor += 1
    return clean_lead(text[start:position])


def table_rows(content, index):
    tables = content.find_all("table")
    if index >= len(tables):
        return None
    rows = []
    for row in tables[index].find_all("tr"):
        cells = [E.ws(cell.get_text(" ")) for cell in row.find_all(["th", "td"])]
        cells = [E.ws(cell.replace("\xa0", " ")) for cell in cells]
        if cells:
            rows.append(" | ".join(cells))
    return " || ".join(rows) or None


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true", help="verify anchors, do not write")
    args = parser.parse_args()

    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    records, problems = [], []
    for fact in FACTS:
        page_path = os.path.join(ROOT, fact["page"])
        if not os.path.exists(page_path):
            problems.append("%s: page not found: %s" % (fact["id"], fact["page"]))
            continue
        text, content = flatten(page_path)
        spec = fact["extract"]
        if spec["mode"] == "sentence":
            statement = sentence_window(text, spec["anchor"], spec.get("sentences", 1))
        else:
            statement = table_rows(content, spec.get("index", 0))
        if not statement:
            problems.append("%s: statement not found (anchor %r)" % (fact["id"], spec.get("anchor")))
            continue
        statements = [E.ws(piece) for piece in statement.split(" || ")] if spec["mode"] == "table" else [statement]
        page_id = E.os.path.basename(fact["page"])[:-5]
        source = vocab.SOURCES[fact["source_id"]]
        records.append({
            "schema_version": 1,
            "id": fact["id"],
            "topic": fact["topic"],
            "statement": statements,
            "statement_kind": "documented_table" if spec["mode"] == "table" else "documented_sentence",
            "evidence_status": "documented",
            "note": fact.get("note"),
            "source_id": fact["source_id"],
            "page_path": fact["page"],
            "page_id": page_id,
            "source_url": "%s(v=)" % source["locator_template"].replace("{page_id}", page_id)
                          if "(v=" not in fact["page"] else source["locator_template"].replace("{page_id}", page_id),
            "collection": source["collection"],
            "rights_status": source["rights"],
        })
    if problems:
        for problem in problems:
            print("ERROR: %s" % problem, file=sys.stderr)
        return 1
    if args.check:
        print("OK: %d abi facts verified" % len(records))
        return 0
    with open(OUT, "w", encoding="utf-8") as handle:
        for record in records:
            handle.write(json.dumps(record, ensure_ascii=False, sort_keys=True) + "\n")
    print("wrote %s (%d documented ABI statements)" % (os.path.relpath(OUT, ROOT), len(records)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
