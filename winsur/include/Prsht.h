/* Prsht.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 113 constants, 26 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _PRSHT_
#define _PRSHT_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ID_PSREBOOTSYSTEM 3
#define ID_PSRESTARTWINDOWS 2
#define LPCPROPSHEETHEADER LPCPROPSHEETHEADERW
#define LPCPROPSHEETPAGE LPCPROPSHEETPAGEW
#define LPFNPSPCALLBACK LPFNPSPCALLBACKW
#define LPPROPSHEETHEADER LPPROPSHEETHEADERW
#define LPPROPSHEETPAGE LPPROPSHEETPAGEW
#define MAXPROPPAGES 100
#define POSTMSG ::PostMessage
#define PROP_LG_CXDLG 252
#define PROP_LG_CYDLG 218
#define PROP_MED_CXDLG 227
#define PROP_MED_CYDLG 215
#define PROP_SM_CXDLG 212
#define PROP_SM_CYDLG 188
#define PROPSHEETHEADER PROPSHEETHEADERW
#define PROPSHEETPAGE PROPSHEETPAGEW
#define PSBTN_APPLYNOW 4
#define PSBTN_BACK 0
#define PSBTN_CANCEL 5
#define PSBTN_FINISH 2
#define PSBTN_HELP 6
#define PSBTN_MAX 6
#define PSBTN_NEXT 1
#define PSBTN_OK 3
#define PSCB_GETVERSION 3
#define PSCB_INITIALIZED 1
#define PSCB_PRECREATE 2
#define PSH_DEFAULT 0
#define PSH_HASHELP 512
#define PSH_HEADER 524288
#define PSH_MAXIMIZE 8192
#define PSH_MODELESS 1024
#define PSH_NOAPPLYNOW 128
#define PSH_NOCONTEXTHELP 0x2000000
#define PSH_PROPSHEETPAGE 8
#define PSH_PROPTITLE 1
#define PSH_RTLREADING 2048
#define PSH_STRETCHWATERMARK 262144
#define PSH_USECALLBACK 256
#define PSH_USEHBMHEADER 1048576
#define PSH_USEHBMWATERMARK 65536
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The following dwFlags values are not supported: [corpus/mvb/windows-ce-1.0/PEGSDK/AC51C.html] */
#define PSH_USEHICON 2
#define PSH_USEHPLWATERMARK 131072
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The following dwFlags values are not supported: [corpus/mvb/windows-ce-1.0/PEGSDK/AC51C.html] */
#define PSH_USEICONID 4
#define PSH_USEPAGELANG 2097152
#define PSH_USEPSTARTPAGE 64
#define PSH_WATERMARK 32768
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The following dwFlags values are not supported: [corpus/mvb/windows-ce-1.0/PEGSDK/AC51C.html] */
#define PSH_WIZARD 32
#define PSH_WIZARD97 0x00002000
#define PSH_WIZARD_LITE 0x400000
#define PSH_WIZARDCONTEXTHELP 4096
#define PSH_WIZARDHASFINISH 16
#define PSM_ADDPAGE (WM_USER+103)
#define PSM_APPLY (WM_USER+110)
#define PSM_CANCELTOCLOSE (WM_USER+107)
#define PSM_CHANGED (WM_USER+104)
#define PSM_GETCURRENTPAGEHWND 1142
#define PSM_GETTABCONTROL 1140
#define PSM_ISDIALOGMESSAGE 1141
#define PSM_PRESSBUTTON 1137
#define PSM_QUERYSIBLINGS (WM_USER+108)
#define PSM_REBOOTSYSTEM (WM_USER+106)
#define PSM_REMOVEPAGE (WM_USER+102)
#define PSM_RESTARTWINDOWS (WM_USER+105)
#define PSM_SETCURSEL (WM_USER+101)
#define PSM_SETCURSELID 1138
#define PSM_SETFINISHTEXT PSM_SETFINISHTEXTW
#define PSM_SETFINISHTEXTA 1139
#define PSM_SETFINISHTEXTW 1145
#define PSM_SETTITLE PSM_SETTITLEW
#define PSM_SETTITLEA (WM_USER+111)
#define PSM_SETTITLEW (WM_USER+120)
#define PSM_SETWIZBUTTONS (WM_USER+112)
#define PSM_UNCHANGED (WM_USER+109)
#define PSN_APPLY (-202)
#define PSN_FIRST (-200)
#define PSN_HELP (-205)
#define PSN_KILLACTIVE (-201)
#define PSN_LAST (-299)
#define PSN_QUERYCANCEL (-209)
#define PSN_RESET (-203)
#define PSN_SETACTIVE (-200)
#define PSN_WIZBACK (-206)
#define PSN_WIZFINISH (-208)
#define PSN_WIZNEXT (-207)
#define PSNRET_INVALID 1
#define PSNRET_INVALID_NOCHANGEPAGE 2
#define PSNRET_NOERROR 0
#define PSP_DEFAULT 0
#define PSP_DLGINDIRECT 1
#define PSP_HASHELP 32
#define PSP_HIDEHEADER 2048
#define PSP_PREMATURE 1024
#define PSP_RTLREADING 16
#define PSP_USECALLBACK 128
#define PSP_USEHEADERSUBTITLE 8192
#define PSP_USEHEADERTITLE 4096
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The following dwFlags values are not supported: [corpus/mvb/windows-ce-1.0/PEGSDK/AC54C.html] */
#define PSP_USEHICON 2
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The following dwFlags values are not supported: [corpus/mvb/windows-ce-1.0/PEGSDK/AC54C.html] */
#define PSP_USEICONID 4
#define PSP_USEREFPARENT 64
#define PSP_USETITLE 8
#define PSPCB_CREATE 2
#define PSPCB_RELEASE 1
#define PSWIZB_BACK 1
#define PSWIZB_DISABLEDFINISH 8
#define PSWIZB_FINISH 4
#define PSWIZB_NEXT 2
#define WIZ_BODYCX 184
#define WIZ_BODYX 92
#define WIZ_CXBMP 80
#define WIZ_CXDLG 276
#define WIZ_CYDLG 140

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..399, 5.0..699 */

/* PropSheet_AddPage  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
BOOL PropSheet_AddPage( 
 hPropSheetDlg, 
 hpage 
);

/* PropSheet_Apply  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
BOOL PropSheet_Apply( 
 hPropSheetDlg 
);

/* PropSheet_CancelToClose  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
VOID PropSheet_CancelToClose( 
 hPropSheetDlg 
);

/* PropSheet_Changed  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
BOOL PropSheet_Changed( 
 hPropSheetDlg, 
 hwndPage
);

/* PropSheet_GetCurrentPageHwnd  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
HWND PropSheet_GetCurrentPageHwnd( 
 hDlg 
);

/* PropSheet_GetTabControl  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
HWND PropSheet_GetTabControl( 
 hPropSheetDlg 
);

/* PropSheet_IsDialogMessage  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
BOOL PropSheet_IsDialogMessage( 
 hDlg, 
 pMsg 
);

/* PropSheet_PressButton  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
BOOL PropSheet_PressButton( 
 hPropSheetDlg, 
 iButton 
);

/* PropSheet_QuerySiblings  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
int PropSheet_QuerySiblings( 
 hPropSheetDlg, 
 param1, 
 param2 
);

/* PropSheet_RebootSystem  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
void PropSheet_RebootSystem( 
 hPropSheetDlg 
);

/* PropSheet_RemovePage  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
void PropSheet_RemovePage( 
 hPropSheetDlg, 
 index, 
 hpage 
);

/* PropSheet_RestartWindows  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
void PropSheet_RestartWindows( 
 hPropSheetDlg 
);

/* PropSheet_SetCurSel  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
BOOL PropSheet_SetCurSel( 
 hPropSheetDlg, 
 hpage, 
 index 
);

/* PropSheet_SetCurSelByID  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
BOOL PropSheet_SetCurSelByID( 
 hPropSheetDlg, 
 id 
);

/* PropSheet_SetFinishText  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
VOID PropSheet_SetFinishText( 
 hPropSheetDlg, 
 lpszText 
);

/* PropSheet_SetTitle  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
void PropSheet_SetTitle( 
 hPropSheetDlg, 
 dwStyle, 
 lpszText 
);

/* PropSheet_SetWizButtons  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
VOID PropSheet_SetWizButtons( 
 HWND hPropSheetDlg, 
 DWORD dwFlags 
);

/* PropSheet_UnChanged  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
void PropSheet_UnChanged( 
 hPropSheetDlg, 
 hwndPage 
);

/* PropSheetProc  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
int CALLBACK PropSheetProc(
 HWND hwndDlg, 
 UINT uMsg, 
 LPARAM lParam 
);
#endif /* _WIN32_WCE */

#endif /* _PRSHT_ */
