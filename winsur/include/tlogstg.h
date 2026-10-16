/* tlogstg.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 5 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _TLOGSTG_
#define _TLOGSTG_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define TLEF_ABSOLUTE 0x00000031
#define TLEF_INCLUDE_UNINVOKEABLE 0x00000040
#define TLEF_RELATIVE_BACK 0x00000010
#define TLEF_RELATIVE_FORE 0x00000020
#define TLEF_RELATIVE_INCLUDE_CURRENT 0x00000001

#endif /* _TLOGSTG_ */
