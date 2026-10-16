#!/usr/bin/env python3
"""tools/extract-missing-defines.py -- Extract #define macros missed by the main parser.

This script scans CE corpus pages for #define lines that the main parser
(page_parse.py) may have missed, particularly:
- Function-like macros (#define NAME(args) ...)
- Multi-line macros with backslash continuations
- Macros in non-standard locations

Output: knowledge/kb/extra-defines.tsv
"""

import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import quality_filters  # noqa: E402

CORPUS = os.path.join(ROOT, "corpus")
KB = os.path.join(ROOT, "knowledge", "kb")

# Directories to scan for CE-specific pages
CE_DIRS = [
    os.path.join(CORPUS, "chm"),
    os.path.join(CORPUS, "learn"),
    os.path.join(CORPUS, "msdn-library"),
]

# Pattern for #define lines
DEFINE_PATTERN = re.compile(
    r'#define\s+([A-Za-z_]\w*)\s*(?:\(([^)]*)\))?\s*(.*?)$',
    re.MULTILINE
)

# Continuation pattern
CONTINUATION_PATTERN = re.compile(r'\\\s*$')


def scan_file(filepath):
    """Scan a file for #define macros."""
    defines = []
    try:
        with open(filepath, 'r', encoding='utf-8', errors='replace') as f:
            content = f.read()
    except OSError:
        return defines
    
    # Skip non-CE pages
    rel_path = os.path.relpath(filepath, ROOT)
    if 'win32/' in rel_path or 'dotnet/' in rel_path:
        return defines
    if quality_filters.is_sample_source(rel_path):
        return defines

    # Tags become spaces so ``#define</b> NAME`` does not glue tokens.
    content = re.sub(r'<[^>]+>', ' ', content)
    content = content.replace('&lt;', '<').replace('&gt;', '>')
    content = content.replace('&amp;', '&').replace('&nbsp;', ' ')
    
    # Find #define lines
    for match in DEFINE_PATTERN.finditer(content):
        name = match.group(1)
        args = match.group(2)  # None for object-like macros
        value = match.group(3).strip()
        
        # Skip if it's inside a comment or code block
        line_start = content.rfind('\n', 0, match.start()) + 1
        prefix = content[line_start:match.start()].strip()
        if prefix.startswith(('//', '/*', '*', '<!--')):
            continue
        
        # Determine macro type
        if args is not None:
            macro_type = "function-like"
            full_def = f"#define {name}({args}) {value}"
        else:
            macro_type = "object-like"
            full_def = f"#define {name} {value}" if value else f"#define {name}"
        
        defines.append({
            "name": name,
            "type": macro_type,
            "args": args or "",
            "value": value[:200],  # Truncate long values
            "definition": full_def[:300],
            "source": rel_path,
        })
    
    return defines


def main():
    """Scan CE corpus for #define macros."""
    all_defines = []
    files_scanned = 0
    
    for ce_dir in CE_DIRS:
        if not os.path.exists(ce_dir):
            continue
        for root, dirs, files in os.walk(ce_dir):
            for fname in files:
                if not (fname.endswith('.html') or fname.endswith('.md')):
                    continue
                filepath = os.path.join(root, fname)
                defines = scan_file(filepath)
                all_defines.extend(defines)
                files_scanned += 1
    
    print(f"Scanned {files_scanned} files")
    print(f"Found {len(all_defines)} #define macros")
    
    # Deduplicate by name, keeping the cleanest definition; drop sample /
    # HTML / incomplete macros (tools/quality_filters.py).
    by_name = {}
    for d in all_defines:
        by_name.setdefault(d["name"], []).append(d)
    unique_defines = []
    for name, rows in by_name.items():
        best = quality_filters.pick_best_define(rows)
        if best:
            unique_defines.append(best)
    
    print(f"Unique defines: {len(unique_defines)}")
    
    # Count by type
    func_like = sum(1 for d in unique_defines if d["type"] == "function-like")
    obj_like = sum(1 for d in unique_defines if d["type"] == "object-like")
    print(f"  Function-like: {func_like}")
    print(f"  Object-like: {obj_like}")
    
    # Write to TSV
    output_path = os.path.join(KB, "extra-defines.tsv")
    with open(output_path, 'w', encoding='utf-8') as f:
        f.write("name\ttype\targs\tvalue\tdefinition\tsource\n")
        for d in sorted(unique_defines, key=lambda x: x["name"]):
            f.write(f"{d['name']}\t{d['type']}\t{d['args']}\t"
                   f"{d['value']}\t{d['definition']}\t{d['source']}\n")
    
    print(f"Wrote to {output_path}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
