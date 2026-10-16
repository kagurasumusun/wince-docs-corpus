/* Netui.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 23 declarations, 0 outlines, 0 base types, 0 extra macros, 2 extra decls
 */
#ifndef _NETUI_
#define _NETUI_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* LINECONFIGDATA  [struct; ce-only] */
typedef struct _LINECONFIGDATA {
 DWORD dwVersion;
 DWORD dwBaudRate;
 DWORD dwSettableBaud;
 BYTE bByteSize;
 BYTE bParity;
 BYTE bStopBits;
 BYTE bReserved;
 WORD wSettableData;
 WORD wWaitBong;
 DWORD dwCallSetupFailTimer;
 DWORD dwModemOptions;
 DWORD dwTermOptions;
 DWORD dwDdevCapFlags;
 DWORD dwModMaxLen;
 TCHAR szDialModifier[NETUI_LCD_DIAL_MOD_LEN + 1];
 WORD wSettableStopParity;
} LINECONFIGDATA, *PLINECONFIGDATA;

/* NETUI_NEWPWD  [struct; ce-only] */
typedef struct _NETUI_NEWPWD{
 TCHAR szNewPassword[PWLEN+1];
} NETUI_NEWPWD, *PNETUI_NEWPWD;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* AdapterIPProperties  [function; ce-only; CE 3.0..699; Netui.lib, netui.lib] */
BOOL AdapterIPProperties(
 HWND hWndOwner, 
 LPTSTR szAdapterName
);

/* DisconnectDialog  [function; ce-only; CE 3.0..699; Netui.lib, netui.lib] */
BOOL DisconnectDialog( 
 HWND hParent, 
 DWORD dwType
);

/* GetIPAddress  [function; ce-only; CE 3.0..699; Netui.lib, netui.lib] */
DWORD GetIPAddress(
 HWND hParent
);

/* GetNetString  [function; ce-only; CE 3.0..699; Netui.lib, netui.lib] */
int GetNetString(
 UINT uID, 
 LPTSTR lpBuffer, 
 int cchBufferMax
);

/* LineConfigEdit  [function; ce-only; CE 3.0..699; Netui.lib, netui.lib] */
BOOL LineConfigEdit(
 HWND hParent, 
 PLINECONFIGDATA pLineConfigData
);

/* NetMsgBox  [function; ce-only; CE 3.0..699; Netui.lib, netui.lib] */
BOOL NetMsgBox(
 HWND hParent, 
 DWORD dwFlags, 
 TCHAR* szStr
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* CreateScanDevice  [function; ce-only; CE 4.0..699; Netui.lib] */
int CreateScanDevice(
 HINSTANCE hInstance, 
 HWND hWnd
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* CloseUsernamePasswordDialog  [function; ce-only; CE 5.0..699; Netui.lib] */
BOOL CloseUsernamePasswordDialog(
 HWND hDlg
);

/* GetNewPassword  [function; ce-only; CE 5.0..699; Netui.lib] */
BOOL WINAPI GetNewPassword (
 HWND hParent, 
 OUT PNETUI_NEWPWD pNewPwd
);

/* GetNewPasswordEx  [function; ce-only; CE 5.0..699; Netui.lib] */
BOOL WINAPI GetNewPasswordEx (
 HWND hParent, 
 OUT PNETUI_NEWPWD pNewPwd, 
 OUT OPTIONAL HWND* phDlg
);

/* RegisterIPClass  [function; ce-only; CE 5.0..699; Netui.lib] */
void RegisterIPClass(
 HINSTANCE hInst
);

/* UnregisterIPClass  [function; ce-only; CE 5.0..699; Netui.lib] */
void UnregisterIPClass(
 HINSTANCE hInst
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
DWORD LineTranslateDialog ( HWND hParent, HWND *pDialogWnd);

#endif /* _NETUI_ */
