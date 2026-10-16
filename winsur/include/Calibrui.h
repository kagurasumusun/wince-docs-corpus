/* Calibrui.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 6 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CALIBRUI_
#define _CALIBRUI_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* TouchCalibrateUI_DrawConfirmationScreen  [function; ce-only; CE 3.0..699] */
void TouchCalibrateUI_DrawConfirmationScreen( 
 HDC hdc 
);

/* TouchCalibrateUI_DrawMainScreen  [function; ce-only; CE 3.0..699] */
void TouchCalibrateUI_DrawMainScreen( 
 HDC hdc 
);

/* TouchCalibrateUI_HandleUserInputMessage  [function; ce-only; CE 3.0..699] */
void TouchCalibrateUI_HandleUserInputMessage( 
 UINT Message, 
 UINT wParam, 
 UINT lParam 
);

/* TouchCalibrateUI_WaitForConfirmation  [function; ce-only; CE 3.0..699] */
void TouchCalibrateUI_WaitForConfirmation( 
 HANDLE hevt, 
 HDC hdc 
);
#endif /* _WIN32_WCE */

#endif /* _CALIBRUI_ */
