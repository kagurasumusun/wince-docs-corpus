/* Splapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 14 constants, 15 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _SPLAPI_
#define _SPLAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define SPL_LIMIT_ADD 35
#define SPL_LIMIT_ADD_DOUBLE_CONSONANT 14
#define SPL_LIMIT_ADD_DOUBLE_VOWEL 16
#define SPL_LIMIT_CAPITAL 1
#define SPL_LIMIT_DROP 31
#define SPL_LIMIT_DROP_DOUBLE_CONSONANT 14
#define SPL_LIMIT_DROP_DOUBLE_VOWEL 16
#define SPL_LIMIT_NONE 0
#define SPL_LIMIT_SUBSTITUTE 43
#define SPL_LIMIT_SUBSTITUTE_CONSONANT 41
#define SPL_LIMIT_SUBSTITUTE_VOWEL 21
#define SPL_LIMIT_TRANSPOSE 19
#define SPL_LIMIT_TRANSPOSE_CONSONANT 18
#define SPL_LIMIT_TRANSPOSE_VOWEL 15

#endif /* _SPLAPI_ */
