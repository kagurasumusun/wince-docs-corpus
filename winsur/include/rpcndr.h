/* rpcndr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 13 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _RPCNDR_
#define _RPCNDR_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CONST_VTBL const
#define NDR_ASCII_CHAR (unsigned
#define NDR_BIG_ENDIAN (unsigned
#define NDR_CHAR_REP_MASK (unsigned
#define NDR_EBCDIC_CHAR (unsigned
#define NDR_FLOAT_REP_MASK (unsigned
#define NDR_IEEE_FLOAT (unsigned
#define NDR_INT_REP_MASK (unsigned
#define NDR_LITTLE_ENDIAN (unsigned
#define NDR_LOCAL_DATA_REPRESENTATION (unsigned
#define NDR_LOCAL_ENDIAN NDR_LITTLE_ENDIAN
#define NDR_VAX_FLOAT (unsigned
#define RPC_VAR_ENTRY __cdecl

#endif /* _RPCNDR_ */
