/* Led_drvr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 4 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _LED_DRVR_
#define _LED_DRVR_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..699 */

/* NLedDriverGetDeviceInfo  [function; ce-only; CE 2.11..2.12, 3.0..699; Nleddrv.lib] */
BOOL NLedDriverGetDeviceInfo(
 INT nId,
 PVOID pOutput 
);

/* NLedDriverInitialize  [function; ce-only; CE 2.11..2.12, 3.0..699; Nleddrv.lib] */
BOOL NLedDriverInitialize (void);

/* NLedDriverPowerDown  [function; ce-only; CE 2.11..2.12, 3.0..699; Nleddrv.lib] */
VOID NLedDriverPowerDown(
 BOOL power_down 
);

/* NLedDriverSetDevice  [function; ce-only; CE 2.11..2.12, 3.0..699; Nleddrv.lib] */
BOOL NLedDriverSetDevice(
 INT nInfoId,
 PVOID pInput 
);
#endif /* _WIN32_WCE */

#endif /* _LED_DRVR_ */
