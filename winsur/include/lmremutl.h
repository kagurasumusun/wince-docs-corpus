/* lmremutl.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 9 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _LMREMUTL_
#define _LMREMUTL_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ALLOCATE_RESPONSE 2
#define NO_PERMISSION_REQUIRED 1
#define SUPPORTS_ANY 0xFFFFFFFF
#define SUPPORTS_LOCAL 32
#define SUPPORTS_REMOTE_ADMIN_PROTOCOL 2
#define SUPPORTS_RPC 4
#define SUPPORTS_SAM_PROTOCOL 8
#define SUPPORTS_UNICODE 16
#define USE_SPECIFIC_TRANSPORT 0x80000000

#endif /* _LMREMUTL_ */
