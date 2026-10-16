/* wsnetbs.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 5 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WSNETBS_
#define _WSNETBS_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define NETBIOS_GROUP_NAME 1
#define NETBIOS_NAME_LENGTH 16
#define NETBIOS_TYPE_QUICK_GROUP 3
#define NETBIOS_TYPE_QUICK_UNIQUE 2
#define NETBIOS_UNIQUE_NAME 0

#endif /* _WSNETBS_ */
