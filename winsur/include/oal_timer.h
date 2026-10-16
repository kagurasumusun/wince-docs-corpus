/* oal_timer.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 16 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _OAL_TIMER_
#define _OAL_TIMER_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* OALCPUIdle  [function; ce-only; CE 5.0..699] */
VOID OALCPUIdle();
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* OALTimerQueryPerformanceCounter  [function; ce-only; CE 6.0..699] */
BOOL OALTimerQueryPerformanceCounter(
 LARGE_INTEGER *pCounter
);

/* OALTimerQueryPerformanceFrequency  [function; ce-only; CE 6.0..699] */
BOOL OALTimerQueryPerformanceFrequency(
 LARGE_INTEGER *pFrequency
);

/* OALTimerUpdateRescheduleTime  [function; ce-only; CE 6.0..699] */
VOID OALTimerUpdateRescheduleTime(DWORD time);
#endif /* _WIN32_WCE */

#endif /* _OAL_TIMER_ */
