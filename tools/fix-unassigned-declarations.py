#!/usr/bin/env python3
"""tools/fix-unassigned-declarations.py -- Include unassigned declarations in output.

This script fixes the issue where declarations without header assignments
are not included in the output. It reads _unassigned.declarations.json
and creates an ExtraDeclarations.h.fragment file with all unassigned
declarations.
"""

import json
import os
from pathlib import Path

def load_unassigned_declarations():
    """Load unassigned declarations from KB."""
    kb_dir = Path('knowledge/kb')
    unassigned_path = kb_dir / 'declarations-by-header' / '_unassigned.declarations.json'
    
    if not unassigned_path.exists():
        print(f"Warning: {unassigned_path} not found")
        return []
    
    with open(unassigned_path, 'r', encoding='utf-8') as f:
        return json.load(f)


def generate_extra_declarations_fragment(declarations):
    """Generate ExtraDeclarations.h.fragment with unassigned declarations."""
    if not declarations:
        print("No unassigned declarations found")
        return
    
    # Group by type
    by_type = {}
    for decl in declarations:
        dtype = decl.get('type', 'function')
        if dtype not in by_type:
            by_type[dtype] = []
        by_type[dtype].append(decl)
    
    # Generate fragment
    lines = []
    lines.append("/* ExtraDeclarations.h -- declarations without header assignment")
    lines.append(" *")
    lines.append(" * These declarations were found in the corpus but could not be")
    lines.append(" * assigned to a specific header file. They may belong to")
    lines.append(" * internal or undocumented headers.")
    lines.append(" *")
    lines.append(f" * {len(declarations)} unassigned declarations")
    lines.append(" */")
    lines.append("#ifndef _EXTRADECLARATIONS_H_")
    lines.append("#define _EXTRADECLARATIONS_H_")
    lines.append("")
    
    # Output by type
    for dtype in sorted(by_type.keys()):
        decls = by_type[dtype]
        lines.append(f"/* {len(decls)} {dtype}(s) */")
        lines.append("")
        
        for decl in decls:
            decl_text = decl.get('declaration', '').strip()
            if decl_text:
                lines.append(decl_text)
                lines.append("")
    
    lines.append("#endif /* _EXTRADECLARATIONS_H_ */")
    
    return '\n'.join(lines)


def main():
    """Generate ExtraDeclarations.h.fragment."""
    print("Loading unassigned declarations...")
    declarations = load_unassigned_declarations()
    print(f"Found {len(declarations)} unassigned declarations")
    
    if not declarations:
        return
    
    print("\nGenerating ExtraDeclarations.h.fragment...")
    fragment = generate_extra_declarations_fragment(declarations)
    
    # Write to winsur/include/
    out_dir = Path('winsur/include')
    out_dir.mkdir(parents=True, exist_ok=True)
    
    out_path = out_dir / 'ExtraDeclarations.h.fragment'
    with open(out_path, 'w', encoding='utf-8') as f:
        f.write(fragment)
    
    print(f"Written to {out_path}")
    print(f"Total: {len(declarations)} declarations")


if __name__ == '__main__':
    main()
