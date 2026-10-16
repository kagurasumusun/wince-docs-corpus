/* Oal_log.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 3 declarations, 7 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _OAL_LOG_
#define _OAL_LOG_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* OALLED  [macro; ce-only] */

/* OALLog  [macro; ce-only] */

/* OALLogV  [macro; ce-only] */

/* OALMASK  [macro; ce-only] */

/* OALMSG  [macro; ce-only] */

/* OALMSGS  [macro; ce-only] */

/* OALZONE  [macro; ce-only] */

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* OALLogSerial  [function; ce-only; CE 5.0..699] */
void OALLogSerial(
 LPCWSTR format,
 ...
);
#endif /* _WIN32_WCE */

#endif /* _OAL_LOG_ */
