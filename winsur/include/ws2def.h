/* ws2def.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 12 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WS2DEF_
#define _WS2DEF_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define AI_ADDRCONFIG 0x0400
#define AI_ALL 0x0100
#define AI_CANONNAME 0x02
#define AI_DISABLE_IDN_ENCODING 0x00080000
#define AI_FILESERVER 0x00040000
#define AI_FQDN 0x00020000
#define AI_NON_AUTHORITATIVE 0x04000
#define AI_NUMERICHOST 0x04
#define AI_PASSIVE 0x01
#define AI_RETURN_PREFERRED_NAMES 0x010000
#define AI_SECURE 0x08000
#define AI_V4MAPPED 0x0800

#endif /* _WS2DEF_ */
