/* cderr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 6 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CDERR_
#define _CDERR_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CCERR_CHOOSECOLORCODES 0x5000
#define CDERR_GENERALCODES 0x0000
#define CFERR_CHOOSEFONTCODES 0x2000
#define FNERR_FILENAMECODES 0x3000
#define FRERR_FINDREPLACECODES 0x4000
#define PDERR_PRINTERCODES 0x1000

#endif /* _CDERR_ */
