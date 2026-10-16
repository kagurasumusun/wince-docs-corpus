/* Oal_cache.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 15 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _OAL_CACHE_
#define _OAL_CACHE_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* OALCacheGlobalsInit  [function; ce-only; CE 5.0..699] */
VOID OALCacheGlobalsInit();

/* OALCleanDCache  [function; ce-only; CE 5.0..699] */
VOID OALCleanDCache();

/* OALClearDTLB  [function; ce-only; CE 5.0..699] */
VOID OALClearDTLB();

/* OALClearDTLBEntry  [function; ce-only; CE 5.0..699] */
VOID OALClearDTLBEntry(
 VOID *pAddress
);

/* OALClearITLB  [function; ce-only; CE 5.0..699] */
VOID OALClearITLB();

/* OALClearITLBEntry  [function; ce-only; CE 5.0..699] */
VOID OALClearITLBEntry(
 VOID *pAddress
);

/* OALClearTLB  [function; ce-only; CE 5.0..699] */
VOID OALClearTLB();

/* OALClearTLBEntry  [function; ce-only; CE 5.0..699] */
VOID OALClearTLBEntry(
 VOID *pAddress
);

/* OALFlushDCache  [function; ce-only; CE 5.0..699] */
VOID OALFlushDCache();

/* OALFlushICache  [function; ce-only; CE 5.0..699] */
VOID OALFlushICache();
#endif /* _WIN32_WCE */

#endif /* _OAL_CACHE_ */
