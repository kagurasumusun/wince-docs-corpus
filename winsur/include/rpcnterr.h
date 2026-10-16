/* rpcnterr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 15 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _RPCNTERR_
#define _RPCNTERR_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define RPC_S_ACCESS_DENIED ERROR_ACCESS_DENIED
#define RPC_S_BUFFER_TOO_SMALL ERROR_INSUFFICIENT_BUFFER
#define RPC_S_INVALID_ARG ERROR_INVALID_PARAMETER
#define RPC_S_INVALID_LEVEL ERROR_INVALID_PARAMETER
#define RPC_S_INVALID_SECURITY_DESC ERROR_INVALID_SECURITY_DESCR
#define RPC_S_OK ERROR_SUCCESS
#define RPC_S_OUT_OF_MEMORY ERROR_OUTOFMEMORY
#define RPC_S_OUT_OF_THREADS ERROR_MAX_THRDS_REACHED
#define RPC_S_SERVER_OUT_OF_MEMORY ERROR_NOT_ENOUGH_SERVER_MEMORY
#define RPC_X_ENUM_VALUE_TOO_LARGE RPC_X_ENUM_VALUE_OUT_OF_RANGE
#define RPC_X_INVALID_BOUND RPC_S_INVALID_BOUND
#define RPC_X_INVALID_BUFFER ERROR_INVALID_USER_BUFFER
#define RPC_X_INVALID_TAG RPC_S_INVALID_TAG
#define RPC_X_NO_MEMORY RPC_S_OUT_OF_MEMORY
#define RPC_X_SS_CONTEXT_MISMATCH ERROR_INVALID_HANDLE

#endif /* _RPCNTERR_ */
