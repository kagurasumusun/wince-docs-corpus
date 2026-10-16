/* wsahelp.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 11 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WSAHELP_
#define _WSAHELP_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define SO_CONTEXT 1
#define SOL_INTERNAL 0xFFFE
#define WSH_NOTIFY_ACCEPT 0x00000008
#define WSH_NOTIFY_BIND 0x00000001
#define WSH_NOTIFY_CLOSE 0x00000080
#define WSH_NOTIFY_CONNECT 0x00000004
#define WSH_NOTIFY_CONNECT_ERROR 0x00000100
#define WSH_NOTIFY_LISTEN 0x00000002
#define WSH_NOTIFY_SHUTDOWN_ALL 0x00000040
#define WSH_NOTIFY_SHUTDOWN_RECEIVE 0x00000010
#define WSH_NOTIFY_SHUTDOWN_SEND 0x00000020

#endif /* _WSAHELP_ */
