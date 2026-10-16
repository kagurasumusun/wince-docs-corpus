/* Startui.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 6 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _STARTUI_
#define _STARTUI_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* Startup_DestroyDialogCallback  [function; ce-only; CE 3.0..699] */
void Startup_DestroyDialogCallback(void);

/* Startup_DlgProc  [function; ce-only; CE 3.0..699] */
BOOL Startup_DlgProc( 
 HWND hDlg, 
 UINT message, 
 WPARAM wParam, 
 LPARAM lParam 
);

/* Startup_Initialize  [function; ce-only; CE 3.0..699] */
void Startup_Initialize( 
 HINSTANCE hinst 
);

/* Startup_PowerOffWhileStartupActiveNotification  [function; ce-only; CE 3.0..699] */
void Startup_PowerOnNotification( 
 HWND hwndDlg 
);

/* Startup_PowerOnNotification  [function; ce-only; CE 3.0..699] */
void Startup_PowerOnNotification( 
 HWND hwndDlg 
);

/* Startup_WantStartupScreen  [function; ce-only; CE 3.0..699] */
BOOL Startup_WantStartupScreen(void);
#endif /* _WIN32_WCE */

#endif /* _STARTUI_ */
