/* Aygshell.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 59 constants, 59 declarations, 2 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _AYGSHELL_
#define _AYGSHELL_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define GN_CONTEXTMENU 1000
#define IDM_NEWMENUMAX 3000
#define IDM_SHAREDNEW 10
#define IDM_SHAREDNEWDEFAULT 11
#define IDS_SHEDIT 2
#define IDS_SHFAVORITES 7
#define IDS_SHFILE 5
#define IDS_SHGO 6
#define IDS_SHNEW 1
#define IDS_SHOPEN 8
#define IDS_SHTOOLS 3
#define IDS_SHVIEW 4
#define NMN_GETAPPREGKEY 1101
#define NMN_INVOKECOMMAND 1103
#define NMN_NEWMENUDESTROY 1102
#define NOMENU 0xFFFF
#define SHCIDS_COLUMNMASK 0x0000FFFF
#define SHCMBF_COLORBK 0x08
#define SHCMBF_EMPTYBAR 0x01
#define SHCMBF_HIDDEN 0x02
#define SHCMBF_HIDESIPBUTTON 0x04
#define SHCMBF_HMENU 0x10
#define SHCMBM_GETMENU 0x0592
#define SHCMBM_GETSUBMENU 0x0591
#define SHCMBM_OVERRIDEKEY (WM_USER
#define SHCMBM_SETSUBMENU 0x0590
#define SHDB_HIDE 2
#define SHDB_SHOW 1
#define SHFS_HIDESIPBUTTON 8
#define SHFS_HIDESTARTICON 32
#define SHFS_HIDETASKBAR 2
#define SHFS_SHOWSIPBUTTON 4
#define SHFS_SHOWSTARTICON 16
#define SHFS_SHOWTASKBAR 1
#define SHIC_FEATURE_AUTOCORRECT 0x00000001
#define SHIC_FEATURE_AUTOSUGGEST 0x00000002
#define SHIC_FEATURE_CLASS 0x00000004
#define SHIC_FEATURE_HAVETRAILER 0x00000003
#define SHIC_FEATURE_RESTOREDEFAULT 0
#define SHIDIF_DONEBUTTON 0x0001
#define SHIDIF_EMPTYMENU 0x0020
#define SHIDIF_FULLSCREENNOMENUBAR 0x0010
#define SHIDIF_SIPDOWN 0x0008
#define SHIDIF_SIZEDLG 0x0002
#define SHIDIF_SIZEDLGFULLSCREEN 0x0004
#define SHIDIM_FLAGS 0x0001
#define SHMBOF_NODEFAULT 0x00000001
#define SHMBOF_NOTIFY 0x00000002
#define SHNF_CRITICAL 2
#define SHNF_DISPLAYON 16
#define SHNF_FORCEMESSAGE 8
#define SHNF_SILENT 32
#define SHNF_STRAIGHTTOTRAY 1
#define SHRG_RETURNCMD 0x0001
#define SHRT_MAX 32767
#define SHRT_MIN -32768
#define VK_TBACK VK_ESCAPE
#define WC_SIPPREF L"SIPPREF"
#define WS_NONAVDONEBUTTON WS_MINIMIZEBOX

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* SHACTIVATEINFO  [struct; ce-only; aygshell.lib] */

/* SHINITDLGINFO  [struct, macro; ce-only; aygshell.lib] */
typedef struct tagSHINITDIALOG {
 DWORD dwMask;
 HWND hDlg;
 DWORD dwFlags;
} SHINITDLGINFO, *PSHINITDLGINFO;

/* SHORTS  [typedef; ce-only; heuristic-prefix] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* SHCHANGENOTIFYENTRY  [struct; shared; ceshell.lib] */
typedef struct tagSHCHANGENOTIFYENTRY {
 DWORD dwEventMask;
 LPTSTR pszWatchDir;
 BOOL fRecursive;
} SHCHANGENOTIFYENTRY;
typedef SHCHANGENOTIFYENTRY *PSHCHANGENOTIFYENTRY, *LPSHCHANGENOTIFYENTRY;

/* SHMENUBARINFO  [struct; ce-only; aygshell.lib] */
typedef struct tagSHMENUBARINFO {
 DWORD cbSize;
 HWND hwndParent;
 DWORD dwFlags;
 UINT nToolBarId;
 HINSTANCE hInstRes;
 int nBmpId;
 int cBmpImages;
 HWND hwndMB;
 COLORREF clrBk;
} SHMENUBARINFO, *PSHMENUBARINFO;

/* SHNP  [enum; ce-only] */
typedef enum _SHNP {
 SHNP_INFORM,
 SHNP_ICONIC
} SHNP;
typedef SHNP *PSHNP, *LPSHNP;

/* SHRGINFO  [struct; ce-only; aygshell.lib] */
typedef struct tagSHRGI {
 DWORD cbSize;
 HWND hwndClient;
 POINT ptDown;
 DWORD dwFlags;
} SHRGINFO, *PSHRGINFO;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* SHCreateMenuBar  [function; ce-only; unified-kb; unified-kb] */
BOOL SHCreateMenuBar( 
 SHMENUBARINFO* pmb 
);

/* SHFullScreen  [function; ce-only; unified-kb; unified-kb] */
BOOL SHFullScreen( 
 HWND hwndRequester, 
 DWORD dwState 
);

/* SHGetSpecialFolderPath  [function; shared; unified-kb; unified-kb] */
BOOL SHGetSpecialFolderPath( 
 HWND hwndOwner, 
 LPTSTR lpszPath, 
 int nFolder, 
 BOOL fCreate 
);

/* SHSipInfo  [function; ce-only; unified-kb; unified-kb] */
BOOL WINAPI SHSipInfo( 
 UINT uiAction, 
 UINT uiParam, 
 PVOID pvParam, 
 UINT fWinIni 
);

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 5.0..699 */

/* SHCloseApps  [function; ce-only; CE 2.11..2.12, 5.0..699; Aygshell.lib, aygshell.lib] */
BOOL SHCloseApps(
 DWORD dwMemSought
);

/* SHGetAppKeyAssoc  [function; ce-only; CE 2.11..2.12, 5.0..699; Aygshell.lib, aygshell.lib] */
BYTE SHGetAppKeyAssoc(
 LPCTSTR ptszApp
);

/* SHInitExtraControls  [function; ce-only; CE 2.11..2.12, 5.0..699; Aygshell.lib, aygshell.lib] */
BOOL SHInitExtraControls(void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* SHChangeNotifyDeregister  [function; shared; CE 5.0..699; Aygshell.lib, aygshell.lib, ceshell.lib] */
BOOL WINAPI SHChangeNotifyDeregister(
 HWND hwnd
);

/* SHChangeNotifyRegister  [function; shared; CE 5.0..699; Aygshell.lib, aygshell.lib, ceshell.lib] */
BOOL WINAPI SHChangeNotifyRegister(
 HWND hwnd,
 SHCHANGENOTIFYENTRY * pshcne
);

/* SHDoneButton  [function; ce-only; CE 5.0..699; Aygshell.lib, aygshell.lib] */
BOOL SHDoneButton(
 HWND hwndRequester,
 DWORD dwState
);

/* SHFindMenuBar  [function; ce-only; CE 5.0..699; Aygshell.lib, aygshell.lib] */
HWND WINAPI SHFindMenuBar(
 HWND hwnd
);

/* SHFreeContextMenuExtensions  [function; ce-only; CE 5.0..699; Aygshell.lib, aygshell.lib] */
BOOL SHFreeContextMenuExtensions(
 HANDLE hCMExtensions
);

/* SHGetAutoRunPath  [function; ce-only; CE 5.0..699; Aygshell.lib, aygshell.lib] */
BOOL SHGetAutoRunPath(
 LPTSTR pAutoRunPath
);

/* SHGetEmergencyCallList  [function; ce-only; CE 5.0..699; Aygshell.lib, aygshell.lib] */
HRESULT SHGetEmergencyCallList(
 TCHAR* pwszBuffer,
 UINT uLenBuf
);

/* SHGetInputContext  [function; ce-only; CE 5.0..699; Aygshell.lib, aygshell.lib] */
HRESULT SHGetInputContext (
 HWND hwnd,
 DWORD dwFeature,
 LPVOID lpValue,
 LPDWORD lpdwSize
);

/* SHInputDialog  [function; ce-only; CE 5.0..699; Aygshell.lib, aygshell.lib] */
void SHInputDialog(
 HWND hwnd,
 UINT uMsg,
 WPARAM wParam
);

/* SHInvokeContextMenuCommand  [function; ce-only; CE 5.0..699; Aygshell.lib, aygshell.lib] */
BOOL SHInvokeContextMenuCommand(
 HWND hwndOwner,
 UINT idCmd,
 HANDLE hCMExtensions
);

/* SHNavigateBack  [function; ce-only; CE 5.0..699; Aygshell.lib, aygshell.lib] */
void SHNavigateBack(void);

/* SHSetAppKeyWndAssoc  [function; ce-only; CE 5.0..699; Aygshell.lib, aygshell.lib] */
BOOL SHSetAppKeyWndAssoc(
 BYTE bVk,
 HWND hwnd
);

/* SHSetBack  [function; ce-only; CE 5.0..699; Aygshell.lib, aygshell.lib] */
void SHSetBack(
 int eOp,
 HWND hwnd
);

/* SHSetInputContext  [function; ce-only; CE 5.0..699; Aygshell.lib, aygshell.lib] */
HRESULT SHSetInputContext (
 HWND hwnd,
 DWORD dwFeature,
 const LPVOID lpValue
);

/* SHSetNavBarText  [function; ce-only; CE 5.0..699; Aygshell.lib, aygshell.lib] */
BOOL SHSetNavBarText(
 HWND hwndRequester,
 LPCTSTR pszText
);
#endif /* _WIN32_WCE */

#endif /* _AYGSHELL_ */
