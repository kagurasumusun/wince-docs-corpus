/* dhcpcsdk.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 3 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _DHCPCSDK_
#define _DHCPCSDK_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DHCPCAPI_REGISTER_HANDLE_EVENT 0x00000001
#define DHCPCAPI_REQUEST_PERSISTENT 0x00000001
#define DHCPCAPI_REQUEST_SYNCHRONOUS 0x00000002

#endif /* _DHCPCSDK_ */
