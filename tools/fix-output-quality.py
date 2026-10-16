#!/usr/bin/env python3
"""tools/fix-output-quality.py -- Fix output quality issues.

This script fixes:
1. Removes extra blank lines between #define statements
2. Improves DEF file formatting (removes excessive comments)
3. Better overall layout and readability
"""

import os
import re
from pathlib import Path

def fix_fragment_file(filepath):
    """Fix formatting issues in a fragment file."""
    with open(filepath, 'r', encoding='utf-8', errors='replace') as f:
        lines = f.readlines()
    
    # Remove consecutive blank lines (keep only one)
    fixed_lines = []
    prev_blank = False
    for line in lines:
        is_blank = line.strip() == ''
        if is_blank and prev_blank:
            continue  # Skip consecutive blank lines
        fixed_lines.append(line)
        prev_blank = is_blank
    
    # Write back
    with open(filepath, 'w', encoding='utf-8') as f:
        f.writelines(fixed_lines)


def fix_def_file(filepath):
    """Fix formatting issues in a DEF file."""
    with open(filepath, 'r', encoding='utf-8', errors='replace') as f:
        content = f.read()
    
    # Remove excessive comment blocks
    # Keep only essential header comments (first 10 lines)
    lines = content.split('\n')
    
    # Find where EXPORTS starts
    exports_idx = None
    for i, line in enumerate(lines):
        if line.strip() == 'EXPORTS':
            exports_idx = i
            break
    
    if exports_idx is None:
        return  # No EXPORTS, skip
    
    # Keep header (first few lines) and EXPORTS section
    # Remove reference-export leads comments
    fixed_lines = []
    in_reference_leads = False
    
    for i, line in enumerate(lines):
        # Keep header comments (before EXPORTS)
        if i < exports_idx:
            # Skip reference-export leads section
            if 'reference-export leads' in line:
                in_reference_leads = True
                continue
            if in_reference_leads:
                if line.strip().startswith(';') and 'stated as:' not in line:
                    continue  # Skip reference lead comments
                elif line.strip() == '':
                    in_reference_leads = False
                else:
                    in_reference_leads = False
            
            if not in_reference_leads:
                fixed_lines.append(line)
        else:
            # Keep EXPORTS and actual exports
            # Remove trailing comments about leads
            if '; lead' in line:
                continue  # Skip lead comments
            fixed_lines.append(line)
    
    # Remove consecutive blank lines
    final_lines = []
    prev_blank = False
    for line in fixed_lines:
        is_blank = line.strip() == ''
        if is_blank and prev_blank:
            continue
        final_lines.append(line)
        prev_blank = is_blank
    
    # Write back
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write('\n'.join(final_lines))


def main():
    """Fix all output files."""
    winsur_dir = Path('winsur')
    
    if not winsur_dir.exists():
        print("winsur directory not found!")
        return
    
    # Fix fragment files
    print("Fixing fragment files...")
    fragment_dir = winsur_dir / 'include'
    if fragment_dir.exists():
        count = 0
        for filepath in fragment_dir.glob('*.fragment'):
            fix_fragment_file(filepath)
            count += 1
        print(f"Fixed {count} fragment files")
    
    # Fix DEF files
    print("\nFixing DEF files...")
    link_dir = winsur_dir / 'link'
    if link_dir.exists():
        count = 0
        for filepath in link_dir.glob('*.def'):
            fix_def_file(filepath)
            count += 1
        print(f"Fixed {count} DEF files")
    
    print("\nDone!")


if __name__ == '__main__':
    main()
