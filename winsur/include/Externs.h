/* Externs.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 20 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _EXTERNS_
#define _EXTERNS_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* MiniportShutdown  [function; ce-only; CE 5.0..699] */
VOID MiniportShutdown(
 PVOID ShutdownContext
);

/* MiniportSynchronizeISR  [function; ce-only; CE 5.0..699] */
BOOLEAN MiniportSynchronizeISR(
 PVOID SynchronizeContext 
);

/* MiniportTimer  [function; ce-only; CE 5.0..699] */
VOID MiniportTimer(
 PVOID SystemSpecific1,
 PVOID FunctionContext,
 PVOID SystemSpecific2,
 PVOID SystemSpecific3
);
#endif /* _WIN32_WCE */

#endif /* _EXTERNS_ */
