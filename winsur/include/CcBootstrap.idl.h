/* CcBootstrap.idl -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 6 constants, 0 declarations, 1 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _CCBOOTSTRAP_IDL_
#define _CCBOOTSTRAP_IDL_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define KTS_DEFAULT 0
#define KTS_ETHER 1
#define KTS_NONE 63
#define KTS_PASSIVE_MODE 0x40
#define KTS_SERIAL 2
#define KTS_USB 3

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* ICcBootstrap::DeviceInfo  [enum; ce-only] */

#endif /* _CCBOOTSTRAP_IDL_ */
