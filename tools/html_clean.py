#!/usr/bin/env python3
"""tools/html_clean.py -- HTML to plain text conversion for readable comments.

This module provides utilities to clean HTML markup from quoted rows in the
knowledge base, converting them to readable plain text suitable for inclusion
in C/C++ header comments.
"""

import re

# HTML entity mappings for common entities
HTML_ENTITIES = {
    'nbsp': ' ', 'amp': '&', 'lt': '<', 'gt': '>', 'quot': '"',
    'apos': "'", 'copy': '(c)', 'reg': '(R)', 'trade': '(TM)',
    'mdash': '--', 'ndash': '-', 'hellip': '...', 'lsquo': "'",
    'rsquo': "'", 'ldquo': '"', 'rdquo': '"', 'bull': '*',
    'middot': '*', 'deg': 'deg', 'plusmn': '+/-', 'times': 'x',
    'divide': '/', 'frac12': '1/2', 'frac14': '1/4', 'frac34': '3/4',
}


def clean_html(html_text):
    """Convert HTML markup to clean plain text suitable for C comments.
    
    Handles:
    - HTML tags removal with appropriate spacing
    - HTML entity decoding
    - Whitespace normalization
    - Line break handling
    """
    if not html_text:
        return ""
    
    text = html_text
    
    # Decode HTML entities
    def replace_entity(match):
        entity = match.group(1).lower()
        if entity.startswith('#x'):
            try:
                return chr(int(entity[2:], 16))
            except:
                return ' '
        elif entity.startswith('#'):
            try:
                return chr(int(entity[1:]))
            except:
                return ' '
        return HTML_ENTITIES.get(entity, ' ')
    
    text = re.sub(r'&([a-zA-Z0-9#]+);', replace_entity, text)
    
    # Replace block-level tags with newlines or spaces
    text = re.sub(r'<(?:br|p|div|tr|li|h[1-6])[^>]*>', '\n', text, flags=re.I)
    text = re.sub(r'</(?:p|div|tr|li|h[1-6]|table)>', '\n', text, flags=re.I)
    
    # Replace inline tags with appropriate spacing
    text = re.sub(r'</?(?:td|th|dd|dt)[^>]*>', ' ', text, flags=re.I)
    text = re.sub(r'</?(?:span|b|i|u|em|strong|code|pre|a|font)[^>]*>', '', text, flags=re.I)
    
    # Remove all remaining HTML tags
    text = re.sub(r'<[^>]+>', '', text)
    
    # Normalize whitespace
    text = re.sub(r'[ \t]+', ' ', text)
    text = re.sub(r'\n\s*\n+', '\n', text)
    text = re.sub(r'^\s+|\s+$', '', text, flags=re.M)
    
    # Collapse multiple newlines
    text = re.sub(r'\n{3,}', '\n\n', text)
    
    return text.strip()


def format_evidence_row(row_text, max_length=120):
    """Format a quoted row for inclusion in a C comment.
    
    Cleans HTML if present and formats the text to be concise and readable.
    Truncates long text with ellipsis.
    """
    if not row_text:
        return ""
    
    # Clean HTML if present
    cleaned = clean_html(row_text) if '<' in row_text else row_text
    
    # Normalize whitespace
    cleaned = re.sub(r'\s+', ' ', cleaned).strip()
    
    # Truncate if too long
    if len(cleaned) > max_length:
        cleaned = cleaned[:max_length-3] + "..."
    
    return cleaned


def extract_constant_description(row_text):
    """Extract a concise description from a constant table row.
    
    For HTML table rows like:
    <tr><td>CONSTANT_NAME</td><td>0x1234</td><td>Description text</td></tr>
    
    Returns just the description part.
    """
    if not row_text:
        return ""
    
    cleaned = clean_html(row_text) if '<' in row_text else row_text
    
    # Try to extract just the description (usually the last meaningful part)
    parts = [p.strip() for p in re.split(r'[|:;\n]+', cleaned) if p.strip()]
    
    if len(parts) > 2:
        # Likely: name, value, description - take the description
        return parts[-1]
    
    return cleaned


def clean_declaration(decl_text):
    """Clean and format declaration text.
    
    Removes HTML artifacts, fixes incomplete declarations, and formats nicely.
    """
    if not decl_text:
        return decl_text
    
    # Use clean_html to remove HTML tags and decode entities
    text = clean_html(decl_text) if '<' in decl_text else decl_text
    
    # Remove inline comments (// ...) only if they're explanatory
    # Keep comments that are part of the code (like // optional parameter)
    lines = text.split('\n')
    cleaned_lines = []
    for line in lines:
        # Remove comments that start with // at the beginning or after whitespace
        line = re.sub(r'^\s*//.*$', '', line)
        # Remove trailing comments that are clearly explanatory
        line = re.sub(r'\s+//\s+[A-Z].*$', '', line)
        cleaned_lines.append(line)
    text = '\n'.join(cleaned_lines)
    
    # Remove block comments (/* ... */)
    text = re.sub(r'/\*.*?\*/', '', text, flags=re.DOTALL)
    
    # Decide whether to keep multi-line or collapse to single line
    # For structs/enums with multiple members, keep multi-line with proper indentation
    # For simple typedefs and functions, collapse to single line
    
    is_complex = ('{' in text and text.count('\n') > 3)
    
    if is_complex:
        # Keep multi-line but format nicely
        lines = text.split('\n')
        formatted_lines = []
        indent_level = 0
        
        for line in lines:
            stripped = line.strip()
            if not stripped:
                continue
            
            # Decrease indent for closing braces
            if stripped.startswith('}'):
                indent_level = max(0, indent_level - 1)
            
            # Add line with proper indentation
            formatted_lines.append('  ' * indent_level + stripped)
            
            # Increase indent after opening braces
            if stripped.endswith('{'):
                indent_level += 1
        
        text = '\n'.join(formatted_lines)
    else:
        # Collapse to single line
        text = re.sub(r'[ \t]+', ' ', text)
        text = re.sub(r'\n\s*', ' ', text)
        text = text.strip()
    
    # Fix incomplete struct/enum declarations (missing closing brace)
    if ('typedef struct' in text or 'typedef enum' in text or 
        'struct ' in text or 'enum ' in text):
        if '{' in text and '}' not in text:
            # Add missing closing brace
            text = text.rstrip() + ' }'
    
    # Fix function declarations missing return type
    if re.match(r'^(WINAPI|STDAPI|APIENTRY)\s+\w+\s*\(', text):
        # Add void return type
        text = 'VOID ' + text
    
    # Ensure declaration ends with semicolon (for typedef/struct/enum)
    if ('typedef' in text or 'struct' in text or 'enum' in text):
        if not text.rstrip().endswith(';'):
            # Check if it's a struct/enum definition (has closing brace)
            if '}' in text and not text.rstrip().endswith('};'):
                text = text.rstrip() + ';'
            elif '}' not in text and not text.rstrip().endswith(';'):
                text = text.rstrip() + ';'
    
    return text
