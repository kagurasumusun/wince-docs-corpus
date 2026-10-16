/* Oomui.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 12 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _OOMUI_
#define _OOMUI_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* OomUI_CreateNotRespondingWindow  [function; ce-only; CE 3.0..699] */
HWND OomUI_CreateNotRespondingWindow(void);

/* OomUI_CreateOomWindow  [function; ce-only; CE 3.0..699] */
HWND OomUI_CreateOomWindow(void);

/* OomUI_FShowOomWindow  [function; ce-only; CE 3.0..699] */
BOOL OomUI_FShowOomWindow(void);

/* OomUI_Initialize  [function; ce-only; CE 3.0..699] */
VOID OomUI_Initialize( 
 HINSTANCE hinst 
);

/* OomUI_NotRespondingWndProc  [function; ce-only; CE 3.0..699] */
LRESULT CALLBACK OomUI_NotRespondingWndProc( 
 HWND hwnd, 
 UINT message, 
 WPARAM wParam, 
 LPARAM lParam 
);

/* OomUI_OnShow  [function; ce-only; CE 3.0..699] */
VOID OomUI_OnShow(void);

/* OomUI_OomWndProc  [function; ce-only; CE 3.0..699] */
LRESULT CALLBACK OomUI_OomWndProc( 
 HWND hwnd, 
 UINT message, 
 WPARAM wParam, 
 LPARAM lParam 
);

/* OomUICallback_IsCritical  [function; ce-only; CE 3.0..699] */
BOOL OomUICallback_IsCritical(void);

/* OomUICallback_NonClientPaint  [function; ce-only; CE 3.0..699] */
VOID OomUICallback_NonClientPaint( 
 HWND hwnd 
);
#endif /* _WIN32_WCE */

#endif /* _OOMUI_ */
