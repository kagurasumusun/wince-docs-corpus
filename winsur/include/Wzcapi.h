/* Wzcapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 14 constants, 2 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WZCAPI_
#define _WZCAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define INTFCAP_MAX_CIPHER_MASK 0x000000ff
#define INTFCAP_SSN 0x00000100
#define INTFCTL_8021XSUPP 0x1000
#define INTFCTL_CM_MASK 0x0007
#define INTFCTL_ENABLED 0x8000
#define INTFCTL_FALLBACK 0x4000
#define INTFCTL_OIDSSUPP 0x2000
#define INTFCTL_POLICY 0x0800
#define INTFCTL_VOLATILE 0x1000
#define WZCCTL_ONEX_ENABLED 0x0010
#define WZCCTL_POLICY 0x0008
#define WZCCTL_VOLATILE 0x0004
#define WZCCTL_WEPK_PRESENT 0x0001
#define WZCCTL_WEPK_XFORMAT 0x0002

#endif /* _WZCAPI_ */
