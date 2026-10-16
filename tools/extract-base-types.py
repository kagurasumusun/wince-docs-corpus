#!/usr/bin/env python3
"""tools/extract-base-types.py -- Extract Windows base type definitions.

This script extracts typedef declarations from windows-data-types.md and
generates a comprehensive base types reference for Windows CE development.

Base types are critical for CE development because:
1. Some types have CE-specific definitions (different from desktop Win32)
2. They're used everywhere in API signatures
3. Missing typedefs break compilation

Output: knowledge/kb/base-types.tsv with all typedef definitions
"""

import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CORPUS = os.path.join(ROOT, "corpus")
KB = os.path.join(ROOT, "knowledge", "kb")

# Windows data types page
DATA_TYPES_PAGE = os.path.join(CORPUS, "win32", "common", "windows-data-types.md")

# CE-specific type definitions (where CE differs from desktop Win32)
# Based on Windows CE SDK headers and documentation
CE_SPECIFIC_TYPES = {
    # CE uses different sizes for some types on different architectures
    "DWORD": {
        "ce_definition": "typedef unsigned long DWORD;",
        "ce_header": "Windef.h",
        "ce_note": "32-bit unsigned integer (same as desktop)",
        "ce_value_note": "Always 32-bit on CE regardless of architecture"
    },
    "HANDLE": {
        "ce_definition": "typedef void *HANDLE;",
        "ce_header": "Winnt.h",
        "ce_note": "Generic handle type",
        "ce_value_note": "Pointer-sized on CE (32-bit on ARM, SHx; varies by platform)"
    },
    "HWND": {
        "ce_definition": "typedef HANDLE HWND;",
        "ce_header": "Windef.h",
        "ce_note": "Window handle",
        "ce_value_note": "Same as HANDLE"
    },
    "BOOL": {
        "ce_definition": "typedef int BOOL;",
        "ce_header": "Windef.h",
        "ce_note": "Boolean (TRUE/FALSE)",
        "ce_value_note": "32-bit int on CE"
    },
    "BYTE": {
        "ce_definition": "typedef unsigned char BYTE;",
        "ce_header": "Windef.h",
        "ce_note": "8-bit unsigned integer",
        "ce_value_note": "Always 8-bit"
    },
    "WORD": {
        "ce_definition": "typedef unsigned short WORD;",
        "ce_header": "Windef.h",
        "ce_note": "16-bit unsigned integer",
        "ce_value_note": "Always 16-bit"
    },
    "LONG": {
        "ce_definition": "typedef long LONG;",
        "ce_header": "Winnt.h",
        "ce_note": "32-bit signed integer",
        "ce_value_note": "Always 32-bit on CE"
    },
    "ULONG": {
        "ce_definition": "typedef unsigned long ULONG;",
        "ce_header": "Winnt.h",
        "ce_note": "32-bit unsigned integer",
        "ce_value_note": "Always 32-bit on CE"
    },
    "INT": {
        "ce_definition": "typedef int INT;",
        "ce_header": "Windef.h",
        "ce_note": "Signed integer",
        "ce_value_note": "Platform-dependent (32-bit on most CE platforms)"
    },
    "UINT": {
        "ce_definition": "typedef unsigned int UINT;",
        "ce_header": "Windef.h",
        "ce_note": "Unsigned integer",
        "ce_value_note": "Platform-dependent (32-bit on most CE platforms)"
    },
    "TCHAR": {
        "ce_definition": "#ifdef UNICODE\ntypedef WCHAR TCHAR;\n#else\ntypedef char TCHAR;\n#endif",
        "ce_header": "Winnt.h",
        "ce_note": "Unicode/ANSI character type",
        "ce_value_note": "CE is fundamentally Unicode (WCHAR); TCHAR is usually WCHAR on CE"
    },
    "WCHAR": {
        "ce_definition": "typedef wchar_t WCHAR;",
        "ce_header": "Winnt.h",
        "ce_note": "16-bit Unicode character",
        "ce_value_note": "Always 16-bit on CE (UTF-16LE)"
    },
    "CHAR": {
        "ce_definition": "typedef char CHAR;",
        "ce_header": "Winnt.h",
        "ce_note": "8-bit ANSI character",
        "ce_value_note": "Always 8-bit; limited use on CE (prefer WCHAR)"
    },
    "LPCTSTR": {
        "ce_definition": "#ifdef UNICODE\ntypedef LPCWSTR LPCTSTR;\n#else\ntypedef LPCSTR LPCTSTR;\n#endif",
        "ce_header": "Winnt.h",
        "ce_note": "Pointer to const TCHAR string",
        "ce_value_note": "Usually LPCWSTR on CE"
    },
    "LPTSTR": {
        "ce_definition": "#ifdef UNICODE\ntypedef LPWSTR LPTSTR;\n#else\ntypedef LPSTR LPTSTR;\n#endif",
        "ce_header": "Winnt.h",
        "ce_note": "Pointer to TCHAR string",
        "ce_value_note": "Usually LPWSTR on CE"
    },
    "LPCWSTR": {
        "ce_definition": "typedef const WCHAR *LPCWSTR;",
        "ce_header": "Winnt.h",
        "ce_note": "Pointer to const wide string",
        "ce_value_note": "Primary string type on CE"
    },
    "LPWSTR": {
        "ce_definition": "typedef WCHAR *LPWSTR;",
        "ce_header": "Winnt.h",
        "ce_note": "Pointer to wide string",
        "ce_value_note": "Primary mutable string type on CE"
    },
    "SIZE_T": {
        "ce_definition": "typedef ULONG_PTR SIZE_T;",
        "ce_header": "BaseTsd.h",
        "ce_note": "Size type for memory operations",
        "ce_value_note": "Pointer-sized (32-bit on 32-bit CE platforms)"
    },
    "HRESULT": {
        "ce_definition": "typedef LONG HRESULT;",
        "ce_header": "Winnt.h",
        "ce_note": "COM result code",
        "ce_value_note": "32-bit signed integer"
    },
    "LPARAM": {
        "ce_definition": "typedef LONG_PTR LPARAM;",
        "ce_header": "Windef.h",
        "ce_note": "Message parameter (signed)",
        "ce_value_note": "Pointer-sized on CE"
    },
    "WPARAM": {
        "ce_definition": "typedef UINT_PTR WPARAM;",
        "ce_header": "Windef.h",
        "ce_note": "Message parameter (unsigned)",
        "ce_value_note": "Pointer-sized on CE"
    },
    "LRESULT": {
        "ce_definition": "typedef LONG_PTR LRESULT;",
        "ce_header": "Windef.h",
        "ce_note": "Message result",
        "ce_value_note": "Pointer-sized on CE"
    },
}


def extract_typedefs_from_markdown(text):
    """Extract typedef definitions from windows-data-types.md."""
    typedefs = {}
    
    # Pattern: typedef <definition>; in <header>
    # Example: "typedef unsigned long DWORD;" in IntSafe.h
    pattern = r'typedef\s+([^;]+);.*?in\s+(\w+\.h)'
    
    for match in re.finditer(pattern, text, re.IGNORECASE | re.DOTALL):
        definition = match.group(1).strip()
        header = match.group(2).strip()
        
        # Extract the type name (last identifier before semicolon)
        # Handle: "typedef unsigned long DWORD;" -> "DWORD"
        # Handle: "typedef void *HANDLE;" -> "HANDLE"
        # Handle: "typedef HANDLE HWND;" -> "HWND"
        parts = definition.split()
        if parts:
            type_name = parts[-1].rstrip('*').strip()
            if type_name and type_name.isidentifier():
                typedefs[type_name] = {
                    "definition": f"typedef {definition};",
                    "header": header,
                    "raw_definition": definition
                }
    
    return typedefs


def main():
    """Extract base types and write to knowledge base."""
    if not os.path.exists(DATA_TYPES_PAGE):
        print(f"ERROR: {DATA_TYPES_PAGE} not found")
        return 1
    
    with open(DATA_TYPES_PAGE, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Extract typedefs from the page
    typedefs = extract_typedefs_from_markdown(content)
    
    print(f"Extracted {len(typedefs)} typedef definitions from {DATA_TYPES_PAGE}")
    
    # Merge with CE-specific definitions
    output_rows = []
    for type_name in sorted(typedefs.keys()):
        info = typedefs[type_name]
        ce_info = CE_SPECIFIC_TYPES.get(type_name, {})
        
        # Use CE-specific definition if available, otherwise use extracted
        definition = ce_info.get("ce_definition", info["definition"])
        header = ce_info.get("ce_header", info["header"])
        
        output_rows.append({
            "type": type_name,
            "definition": definition,
            "header": header,
            "ce_specific": "yes" if type_name in CE_SPECIFIC_TYPES else "no",
            "ce_note": ce_info.get("ce_note", ""),
            "ce_value_note": ce_info.get("ce_value_note", ""),
            "source": "win32/common/windows-data-types.md"
        })
    
    # Add CE-specific types that weren't in the page
    for type_name, ce_info in CE_SPECIFIC_TYPES.items():
        if type_name not in typedefs:
            output_rows.append({
                "type": type_name,
                "definition": ce_info["ce_definition"],
                "header": ce_info["ce_header"],
                "ce_specific": "yes",
                "ce_note": ce_info["ce_note"],
                "ce_value_note": ce_info["ce_value_note"],
                "source": "CE SDK reference"
            })
    
    # Sort by type name
    output_rows.sort(key=lambda x: x["type"])
    
    # Write to TSV
    output_path = os.path.join(KB, "base-types.tsv")
    with open(output_path, 'w', encoding='utf-8') as f:
        f.write("type\tdefinition\theader\tce_specific\tce_note\tce_value_note\tsource\n")
        for row in output_rows:
            f.write(f"{row['type']}\t{row['definition']}\t{row['header']}\t"
                   f"{row['ce_specific']}\t{row['ce_note']}\t{row['ce_value_note']}\t"
                   f"{row['source']}\n")
    
    print(f"Wrote {len(output_rows)} base type definitions to {output_path}")
    print(f"  CE-specific types: {sum(1 for r in output_rows if r['ce_specific'] == 'yes')}")
    print(f"  Standard types: {sum(1 for r in output_rows if r['ce_specific'] == 'no')}")
    
    return 0


if __name__ == "__main__":
    sys.exit(main())
