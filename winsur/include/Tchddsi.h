/* Tchddsi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 8 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _TCHDDSI_
#define _TCHDDSI_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..699 */

/* DdsiTouchPanelDisable  [function; ce-only; CE 2.11..2.12, 3.0..699; Tchmdd.lib] */
VOID DdsiTouchPanelDisable(void);

/* DdsiTouchPanelEnable  [function; ce-only; CE 2.11..2.12, 3.0..699; Tchmdd.lib] */
BOOL DdsiTouchPanelEnable(void);

/* DdsiTouchPanelGetDeviceCaps  [function; ce-only; CE 2.11..2.12, 3.0..699; Tchmdd.lib] */
BOOL DdsiTouchPanelGetDeviceCaps(
 ULONG iIndex,
 LPVOID lpOutput 
);

/* DdsiTouchPanelPowerHandler  [function; ce-only; CE 2.11..2.12, 3.0..699; Tchmdd.lib] */
VOID DdsiTouchPanelPowerHandler(
 BOOL bOff
);

/* DdsiTouchPanelSetMode  [function; ce-only; CE 2.11..2.12, 3.0..699; Tchmdd.lib] */
BOOL DdsiTouchPanelSetMode(
 ULONG iIndex,
 LPVOID lpInput 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* DdsiTouchPanelAttach  [function; ce-only; CE 4.0..699; Tchmdd.lib] */
LONG DdsiTouchPanelAttach(void);

/* DdsiTouchPanelDetach  [function; ce-only; CE 4.0..699; Tchmdd.lib] */
LONG DdsiTouchPanelDetach(void);
#endif /* _WIN32_WCE */

#endif /* _TCHDDSI_ */
