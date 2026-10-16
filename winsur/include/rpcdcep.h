/* rpcdcep.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 11 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _RPCDCEP_
#define _RPCDCEP_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define RPC_FLAGS_VALID_BIT 0x8000
#define RPC_NCA_FLAGS_BROADCAST 2
#define RPC_NCA_FLAGS_DEFAULT 0
#define RPC_NCA_FLAGS_IDEMPOTENT 1
#define RPC_NCA_FLAGS_MAYBE 4
#define RPCFLG_ASYNCHRONOUS 0x40000000
#define RPCFLG_INPUT_SYNCHRONOUS 0x20000000
#define TRANSPORT_TYPE_CN 1
#define TRANSPORT_TYPE_DG 2
#define TRANSPORT_TYPE_LPC 4
#define TRANSPORT_TYPE_WMSG 8

#endif /* _RPCDCEP_ */
