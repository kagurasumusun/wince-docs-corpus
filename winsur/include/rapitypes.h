/* rapitypes.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 6 declarations, 1 outlines, 0 base types, 0 extra macros, 2 extra decls
 */
#ifndef _RAPITYPES_
#define _RAPITYPES_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* RAPI_DEVICE_PLATFORM  [struct; ce-only; rapi.lib] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CE_FIND_DATA  [struct; ce-only] */
typedef struct _CE_FIND_DATA {
 DWORD dwFileAttributes;
 FILETIME ftCreationTime;
 FILETIME ftLastAccessTime;
 FILETIME ftLastWriteTime;
 DWORD nFileSizeHigh;
 DWORD nFileSizeLow;
 DWORD dwOID;
 WCHAR cFileName[MAX_PATH];
} CE_FIND_DATA, *LPCE_FIND_DATA;

/* CEGUID  [struct; ce-only] */
typedef struct _CEGUID {
 DWORD Data1;
 DWORD Data2;
 DWORD Data3;
 DWORD Data4;
} CEGUID;
typedef CEGUID *PCEGUID, *LPCEGUID;

/* CEOSVERSIONINFO  [struct; ce-only] */
typedef struct _CEOSVERSIONINFO {
 DWORD dwOSVersionInfoSize; 
 DWORD dwMajorVersion; 
 DWORD dwMinorVersion; 
 DWORD dwBuildNumber; 
 DWORD dwPlatformId; 
 WCHAR szCSDVersion[ 128 ]; 
} CEOSVERSIONINFO, * LPCEOSVERSIONINFO;

/* RAPIINIT  [struct; ce-only] */
typedef struct _RAPIINIT {
 DWORD cbSize;
 HANDLE heRapiInit;
 HRESULT hrRapiInit;
} RAPIINIT;
typedef RAPIINIT *PRAPIINIT, *LPRAPIINIT;

/* RAPISTREAMFLAG  [enum; ce-only; rapi.lib] */
typedef enum tagRAPISTREAMFLAG {
 STREAM_TIMEOUT_READ
} RAPISTREAMFLAG;
typedef RAPISTREAMFLAG *PRAPISTREAMFLAG, *LPRAPISTREAMFLAG;

/* CENOTIREQUEST  [extra struct] */
typedef struct _CENOTIFYREQUEST { DWORD dwSize; HWND hwnd; DWORD dwFlags; HANDLE hHeap; DWORD dwParam; } CENOTIREQUEST;

#endif /* _RAPITYPES_ */
