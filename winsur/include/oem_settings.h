/* oem_settings.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 8 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _OEM_SETTINGS_
#define _OEM_SETTINGS_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* RDP_TAB_INFO  [struct; ce-only] */
typedef struct {
 TCHAR szTabName[MAX_PATH];
 DLGPROC pDlgProc;
 UINT uTemplateId;
} RDP_TAB_INFO, *PRDP_TAB_INFO;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* OemHelpProc  [function; ce-only; CE 6.0..699] */
HRESULT WINAPI OemHelpProc(
 HWND hOwnerWnd
);

/* OemProcXXX  [function; ce-only; CE 6.0..699] */
BOOL CALLBACK OemProcXXX(
 HWND hwnd, 
 UINT msg, 
 WPARAM wParam, 
 LPARAM lParam
);

/* SetTabDispArea  [function; ce-only; CE 6.0..699] */
void WINAPI SetTabDispArea(
 RECT *prect
);

/* TscSettingsRead  [function; ce-only; CE 6.0..699] */
HRESULT TscSettingsRead ( 
 UINT uID,
 LPVOID val
);

/* TscSettingsWrite  [function; ce-only; CE 6.0..699] */
HRESULT TscSettingsWrite ( 
 UINT uID,
 LPVOID val
);
#endif /* _WIN32_WCE */

#endif /* _OEM_SETTINGS_ */
