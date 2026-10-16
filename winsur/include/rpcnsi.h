/* rpcnsi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 8 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _RPCNSI_
#define _RPCNSI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define RPC_C_NS_DEFAULT_EXP_AGE -1
#define RPC_C_NS_SYNTAX_DCE 3
#define RPC_C_NS_SYNTAX_DEFAULT 0
#define RPC_C_PROFILE_ALL_ELT 1
#define RPC_C_PROFILE_DEFAULT_ELT 0
#define RPC_C_PROFILE_MATCH_BY_BOTH 4
#define RPC_C_PROFILE_MATCH_BY_IF 2
#define RPC_C_PROFILE_MATCH_BY_MBR 3

#endif /* _RPCNSI_ */
