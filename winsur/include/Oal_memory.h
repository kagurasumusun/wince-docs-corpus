/* Oal_memory.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 7 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _OAL_MEMORY_
#define _OAL_MEMORY_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* OALCAtoUA  [function; ce-only; CE 5.0..699] */
VOID* OALCAtoUA(
 VOID *ca
);

/* OALUAtoCA  [function; ce-only; CE 5.0..699] */
VOID* OALUAtoCA(
 VOID *ua
);
#endif /* _WIN32_WCE */

#endif /* _OAL_MEMORY_ */
