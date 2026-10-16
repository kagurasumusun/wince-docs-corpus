/* ipxconst.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 4 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _IPXCONST_
#define _IPXCONST_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ADMIN_STATE_DISABLED 0x00000001
#define ADMIN_STATE_ENABLED 0x00000002
#define ADMIN_STATE_ENABLED_ONLY_FOR_NETBIOS_STATIC_ROUTING 0x00000003
#define ADMIN_STATE_ENABLED_ONLY_FOR_OPER_STATE_UP 0x00000004

#endif /* _IPXCONST_ */
