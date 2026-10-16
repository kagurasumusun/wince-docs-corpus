/* shellapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 162 constants, 37 declarations, 0 outlines, 1 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SHELLAPI_
#define _SHELLAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define _WIN32_IE 0x0500
#define ABE_BOTTOM 3
#define ABE_LEFT 0
#define ABE_RIGHT 2
#define ABE_TOP 1
#define ABM_ACTIVATE 6
#define ABM_GETAUTOHIDEBAR 7
#define ABM_GETSTATE 4
#define ABM_GETTASKBARPOS 5
#define ABM_NEW 0
#define ABM_QUERYPOS 2
#define ABM_REMOVE 1
#define ABM_SETAUTOHIDEBAR 8
#define ABM_SETPOS 3
#define ABM_WINDOWPOSCHANGED 9
#define ABN_EXIT_USING_VOICE 0x0004
#define ABN_FULLSCREENAPP 2
#define ABN_POSCHANGED 1
#define ABN_RECORDS_ADDED 0x0001
#define ABN_RECORDS_DELETED 0x0002
#define ABN_RESORT_DB 0x0008
#define ABN_STATECHANGE 0
#define ABN_WINDOWARRANGE 3
#define ABS_ALWAYSONTOP 2
#define ABS_AUTOHIDE 1
#define DE_ACCESSDENIEDSRC 0x78
#define DE_DEST_IS_CDRECORD 0x84
#define DE_DEST_IS_CDROM 0x82
#define DE_DEST_IS_DVD 0x83
#define DE_DESTSAMETREE 0x7D
#define DE_DESTSUBTREE 0x76
#define DE_DIFFDIR 0x73
#define DE_ERROR_MAX 0xB7
#define DE_FILE_TOO_LARGE 0x85
#define DE_FILEDESTISFLD 0x80
#define DE_FILENAMETOOLONG 0x81
#define DE_FLDDESTISFILE 0x7E
#define DE_INVALIDFILES 0x7C
#define DE_MANYDEST 0x7A
#define DE_MANYSRC1DEST 0x72
#define DE_OPCANCELLED 0x75
#define DE_PATHTOODEEP 0x79
#define DE_ROOTDIR 0x74
#define DE_SAMEFILE 0x71
#define DE_SRC_IS_CDRECORD 0x88
#define DE_SRC_IS_CDROM 0x86
#define DE_SRC_IS_DVD 0x87
#define ERRORONDEST 0x10000
#define FO_COPY 2
#define FO_DELETE 3
#define FO_DONE_ONE_VOL 0x00000002
#define FO_MORE_VOLUME 0x00000001
#define FO_MOVE 1
#define FO_RENAME 4
#define FOF_ALLOWUNDO 64
#define FOF_CONFIRMMOUSE 2
#define FOF_FILESONLY 128
#define FOF_MULTIDESTFILES 1
#define FOF_NOCONFIRMATION 16
#define FOF_NOCONFIRMMKDIR 512
#define FOF_NOCOPYSECURITYATTRIBS 2048
#define FOF_NOERRORUI 1024
#define FOF_RENAMEONCOLLISION 8
#define FOF_SILENT 4
#define FOF_SIMPLEPROGRESS 256
#define FOF_WANTMAPPINGHANDLE 32
#define NIF_GUID 0x00000020
#define NIF_ICON 0x00000002
#define NIF_INFO 0x00000010
#define NIF_MESSAGE 0x00000001
#define NIF_REALTIME 0x00000040
#define NIF_SHOWTIP 0x00000080
#define NIF_STATE 0x00000008
#define NIF_TIP 0x00000004
#define NIIF_ERROR 0x00000003
#define NIIF_ICON_MASK 0x0000000F
#define NIIF_INFO 0x00000001
#define NIIF_LARGE_ICON 0x00000020
#define NIIF_NONE 0x00000000
#define NIIF_NOSOUND 0x00000010
#define NIIF_RESPECT_QUIET_TIME 0x00000080
#define NIIF_USER 0x00000004
#define NIIF_WARNING 0x00000002
#define NIM_ADD 0x00000000
#define NIM_DELETE 0x00000002
#define NIM_MODIFY 0x00000001
#define NIM_SETFOCUS 0x00000003
#define NIM_SETVERSION 0x00000004
#define NIN_POPUPCLOSE WM_USER+7
#define NIN_POPUPOPEN WM_USER+6
#define NIS_HIDDEN 0x00000001
#define NIS_SHAREDICON 0x00000002
#define NOTIFYICON_VERSION 3
#define NOTIFYICON_VERSION_4 4
#define NOTIFYICONDATA_V1_SIZE 152
#define NOTIFYICONDATA_V2_SIZE 936
#define PO_DELETE 19
#define PO_PORTCHANGE 32
#define PO_REN_PORT 52
#define PO_RENAME 20
#define SE_ERR_ACCESSDENIED 5
#define SE_ERR_ASSOCINCOMPLETE 27
#define SE_ERR_DDEBUSY 30
#define SE_ERR_DDEFAIL 29
#define SE_ERR_DDETIMEOUT 28
#define SE_ERR_DLLNOTFOUND 32
#define SE_ERR_FNF 2
#define SE_ERR_NOASSOC 31
#define SE_ERR_OOM 8
#define SE_ERR_PNF 3
#define SE_ERR_SHARE 26
#define SE_UNKNOWN_OBJECT_TYPE 0
#define SEE_MASK_ASYNCOK 0x00100000
#define SEE_MASK_CLASSKEY 0x00000003
#define SEE_MASK_CLASSNAME 0x00000001
#define SEE_MASK_CONNECTNETDRV 0x00000080
#define SEE_MASK_DEFAULT 0x00000000
#define SEE_MASK_DOENVSUBST 0x00000200
#define SEE_MASK_FLAG_DDEWAIT 0x00000100
#define SEE_MASK_FLAG_HINST_IS_SITE 0x08000000
#define SEE_MASK_FLAG_LOG_USAGE 0x04000000
#define SEE_MASK_FLAG_NO_UI 0x00000400
#define SEE_MASK_HMONITOR 0x00200000
#define SEE_MASK_HOTKEY 0x00000020
#define SEE_MASK_ICON 0x00000010
#define SEE_MASK_IDLIST 0x00000004
#define SEE_MASK_INVOKEIDLIST 0x0000000C
#define SEE_MASK_NO_CONSOLE 0x00008000
#define SEE_MASK_NOASYNC 0x00000100
#define SEE_MASK_NOCLOSEPROCESS 0x00000040
#define SEE_MASK_NOQUERYCLASSSTORE 0x01000000
#define SEE_MASK_NOZONECHECKS 0x00800000
#define SEE_MASK_UNICODE 0x00004000
#define SEE_MASK_WAITFORINPUTIDLE 0x02000000
#define SHERB_NOCONFIRMATION 1
#define SHERB_NOPROGRESSUI 2
#define SHERB_NOSOUND 4
#define SHGFI_ADDOVERLAYS 0x000000020
#define SHGFI_ATTR_SPECIFIED 0x000020000
/* NOT SUPPORTED per msdn-library/wcedevcon-99/wcesdkr: Remarks For Windows CE versions 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/msdn-library/wcedevcon-99/wcesdkr/kf_s_41.html] */
#define SHGFI_ATTRIBUTES 0x000000800
#define SHGFI_DISPLAYNAME 0x000000200
/* NOT SUPPORTED per chm/windows-ce-3.0: Remarks For Windows CE versions 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/chm/windows-ce-3.0/_wcesdk_Win32_SHGetFileInfo.html] */
/* NOT SUPPORTED per chm/windows-ce-5.0/wceui5/html: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/chm/windows-ce-5.0/wceui5/html/wce50lrfSHGetFileInfo.html] */
/* NOT SUPPORTED per learn/windows-ce-5.0: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/learn/windows-ce-5.0/aa453700(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-embedded-ce-6.0: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/learn/windows-embedded-ce-6.0/ee499381(v=winembedded.60).html] */
/* NOT SUPPORTED per msdn-library/wcedevcon-99/wcesdkr: Remarks For Windows CE versions 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/msdn-library/wcedevcon-99/wcesdkr/kf_s_41.html] */
#define SHGFI_EXETYPE 0x000002000
#define SHGFI_ICON 0x000000100
/* NOT SUPPORTED per chm/windows-ce-3.0: Remarks For Windows CE versions 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/chm/windows-ce-3.0/_wcesdk_Win32_SHGetFileInfo.html] */
/* NOT SUPPORTED per chm/windows-ce-5.0/wceui5/html: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/chm/windows-ce-5.0/wceui5/html/wce50lrfSHGetFileInfo.html] */
/* NOT SUPPORTED per learn/windows-ce-5.0: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/learn/windows-ce-5.0/aa453700(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-embedded-ce-6.0: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/learn/windows-embedded-ce-6.0/ee499381(v=winembedded.60).html] */
/* NOT SUPPORTED per msdn-library/wcedevcon-99/wcesdkr: Remarks For Windows CE versions 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/msdn-library/wcedevcon-99/wcesdkr/kf_s_41.html] */
#define SHGFI_ICONLOCATION 0x000001000
#define SHGFI_LARGEICON 0x000000000
/* NOT SUPPORTED per chm/windows-ce-3.0: Remarks For Windows CE versions 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/chm/windows-ce-3.0/_wcesdk_Win32_SHGetFileInfo.html] */
/* NOT SUPPORTED per chm/windows-ce-5.0/wceui5/html: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/chm/windows-ce-5.0/wceui5/html/wce50lrfSHGetFileInfo.html] */
/* NOT SUPPORTED per learn/windows-ce-5.0: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/learn/windows-ce-5.0/aa453700(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-embedded-ce-6.0: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/learn/windows-embedded-ce-6.0/ee499381(v=winembedded.60).html] */
/* NOT SUPPORTED per msdn-library/wcedevcon-99/wcesdkr: Remarks For Windows CE versions 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/msdn-library/wcedevcon-99/wcesdkr/kf_s_41.html] */
#define SHGFI_LINKOVERLAY 0x000008000
/* NOT SUPPORTED per chm/windows-ce-3.0: Remarks For Windows CE versions 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/chm/windows-ce-3.0/_wcesdk_Win32_SHGetFileInfo.html] */
/* NOT SUPPORTED per chm/windows-ce-5.0/wceui5/html: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/chm/windows-ce-5.0/wceui5/html/wce50lrfSHGetFileInfo.html] */
/* NOT SUPPORTED per learn/windows-ce-5.0: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/learn/windows-ce-5.0/aa453700(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-embedded-ce-6.0: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/learn/windows-embedded-ce-6.0/ee499381(v=winembedded.60).html] */
/* NOT SUPPORTED per msdn-library/wcedevcon-99/wcesdkr: Remarks For Windows CE versions 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/msdn-library/wcedevcon-99/wcesdkr/kf_s_41.html] */
#define SHGFI_OPENICON 0x000000002
#define SHGFI_OVERLAYINDEX 0x000000040
#define SHGFI_PIDL 0x000000008
/* NOT SUPPORTED per chm/windows-ce-3.0: Remarks For Windows CE versions 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/chm/windows-ce-3.0/_wcesdk_Win32_SHGetFileInfo.html] */
/* NOT SUPPORTED per chm/windows-ce-5.0/wceui5/html: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/chm/windows-ce-5.0/wceui5/html/wce50lrfSHGetFileInfo.html] */
/* NOT SUPPORTED per learn/windows-ce-5.0: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/learn/windows-ce-5.0/aa453700(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-embedded-ce-6.0: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/learn/windows-embedded-ce-6.0/ee499381(v=winembedded.60).html] */
/* NOT SUPPORTED per msdn-library/wcedevcon-99/wcesdkr: Remarks For Windows CE versions 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/msdn-library/wcedevcon-99/wcesdkr/kf_s_41.html] */
#define SHGFI_SELECTED 0x000010000
/* NOT SUPPORTED per chm/windows-ce-3.0: Remarks For Windows CE versions 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/chm/windows-ce-3.0/_wcesdk_Win32_SHGetFileInfo.html] */
/* NOT SUPPORTED per chm/windows-ce-5.0/wceui5/html: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/chm/windows-ce-5.0/wceui5/html/wce50lrfSHGetFileInfo.html] */
/* NOT SUPPORTED per learn/windows-ce-5.0: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/learn/windows-ce-5.0/aa453700(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-embedded-ce-6.0: For Windows CE 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/learn/windows-embedded-ce-6.0/ee499381(v=winembedded.60).html] */
/* NOT SUPPORTED per msdn-library/wcedevcon-99/wcesdkr: Remarks For Windows CE versions 2.10 and later, SHGetFileInfo does not support the following values for uFlags: [corpus/msdn-library/wcedevcon-99/wcesdkr/kf_s_41.html] */
#define SHGFI_SHELLICONSIZE 0x000000004
#define SHGFI_SMALLICON 0x000000001
#define SHGFI_SYSICONINDEX 0x000004000
#define SHGFI_TYPENAME 0x000000400
#define SHGFI_USEFILEATTRIBUTES 0x000000010
#define SHIL_EXTRALARGE 0x2
#define SHIL_JUMBO 0x4
#define SHIL_LARGE 0x0
#define SHIL_LAST SHIL_JUMBO
#define SHIL_SMALL 0x1
#define SHIL_SYSSMALL 0x3
#define WINSHELLAPI DECLSPEC_IMPORT

/* ==================================================================
 * base types -- fundamental Windows type definitions
 * CE-specific types are marked; verify sizes for your platform
 * ================================================================ */

/* HDESK
 * source: win32/common/windows-data-types.md */
typedef HANDLE HDESK;

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* HDROP  [typedef; shared; entity-headers; win32-reference] */
typedef HANDLE HDROP;

/* NOTIFYICONDATA  [struct; shared; A/W NOTIFYICONDATAA,NOTIFYICONDATAW (CE is W-side)] */
typedef struct _NOTIFYICONDATA { 
 DWORD cbSize;
 HWND hWnd; 
 UINT uID; 
 UINT uFlags; 
 UINT uCallbackMessage; 
 HICON hIcon; 
 WCHAR szTip[64]; 
} NOTIFYICONDATA, *PNOTIFYICONDATA;

/* SHELLEXECUTEINFO  [struct; ce-only; harvest-kb; harvest-kb] */
typedef struct _SHELLEXECUTEINFO { 
DWORD cbSize; 
ULONG fMask; 
HWND hwnd; 
LPCSTR lpVerb; 
LPCSTR lpFile; 
LPCSTR lpParameters; 
LPCSTR lpDirectory; 
int nShow; 
HINSTANCE hInstApp; 
// Optional members 
LPVOID lpIDList; 
LPCSTR lpClass; 
HKEY hkeyClass; 
DWORD dwHotKey; 
HANDLE hIcon; 
HANDLE hProcess; 
} SHELLEXECUTEINFO, FAR *LPSHELLEXECUTEINFO;

/* SHFILEINFO  [struct; shared; A/W SHFILEINFOA,SHFILEINFOW (CE is W-side)] */
typedef struct _SHFILEINFO { 
 HICON hIcon; 
 int iIcon; 
 DWORD dwAttributes; 
 TCHAR szDisplayName[MAX_PATH]; 
 TCHAR szTypeName[80]; 
} SHFILEINFO;
typedef SHFILEINFO *PSHFILEINFO, *LPSHFILEINFO;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699 */

/* SHCreateShortcut  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Shortcut.lib, shortcut.lib] */
DWORD WINAPI SHCreateShortcut(
 LPTSTR szShortcut, 
 LPTSTR szTarget 
);

/* SHGetShortcutTarget  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Shortcut.lib, shortcut.lib] */
BOOL SHGetShortcutTarget(
 LPTSTR szShortcut, 
 LPTSTR szTarget, 
 int cbMax 
);

/* SHLoadDIBitmap  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Shmisc.lib, shmisc.lib] */
HBITMAP SHLoadDIBitmap(
 LPCTSTR szFileName 
);

/* SHShowOutOfMemory  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Shmisc.lib, shmisc.lib] */
int SHShowOutOfMemory(
 HWND hwndOwner, 
 UINT grfFlags 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..699 */

/* ExtractIconEx  [function; shared; CE 2.11..2.12, 3.0..699; A/W ExtractIconExA,ExtractIconExW (CE is W-side)] */
HICON ExtractIconEx(
 LPCTSTR lpszFile, 
 int nIconIndex,
 HICON FAR* phiconLarge,
 HICON FAR* phiconSmall,
 UINT nIcons
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* SHCreateShortcutEx  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
DWORD WINAPI SHCreateShortcutEx(
 LPTSTR lpszDir,
 LPTSTR lpszTarget,
 LPTSTR szShortcut,
 LPDWORD lpcbShortcut
);
#endif /* _WIN32_WCE */

#endif /* _SHELLAPI_ */
