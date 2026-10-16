/* WinDef.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 30 constants, 67 declarations, 9 outlines, 122 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WINDEF_
#define _WINDEF_

#include <stddef.h>
/* CE's Win32 API surface is Unicode (LPWSTR). */
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

/* compiler surface: empty 16-bit keywords + SAL, GCC __int64.
 * These expand to nothing / long long.  Not copied from an SDK.
 * stdarg.h is ISO C (va_list on FormatMessage). */
#include <stdarg.h>
#ifndef CONST
#define CONST const
#endif
#ifndef FAR
#define FAR
#endif
#ifndef NEAR
#define NEAR
#endif
#ifndef far
#define far
#endif
#ifndef near
#define near
#endif
#ifndef PASCAL
#define PASCAL
#endif
#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef OPTIONAL
#define OPTIONAL
#endif
#ifndef UNALIGNED
#define UNALIGNED
#endif
#ifndef __nullterminated
#define __nullterminated
#endif
#ifndef __nullnullterminated
#define __nullnullterminated
#endif
#ifndef _MSC_VER
#ifndef __int64
#define __int64 long long
#endif
#ifndef __stdcall
#define __stdcall
#endif
#ifndef __cdecl
#define __cdecl
#endif
#ifndef _cdecl
#define _cdecl
#endif
#ifndef __fastcall
#define __fastcall
#endif
#ifndef __declspec
#define __declspec(x)
#endif
#endif /* _MSC_VER */
#ifndef WINAPI
#define WINAPI __stdcall
#endif
#ifndef CALLBACK
#define CALLBACK __stdcall
#endif
#ifndef APIENTRY
#define APIENTRY WINAPI
#endif
#ifndef TEXT
#define TEXT(s) L ## s
#endif
#ifndef __TEXT
#define __TEXT(s) L ## s
#endif
#ifndef _T
#define _T(s) TEXT(s)
#endif


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define APIENTRY WINAPI
#define APIPRIVATE __stdcall
#define CALLBACK __stdcall
#define CDECL _cdecl
#define DECLSPEC_EXPORT __declspec(dllexport)
#define DECLSPEC_IMPORT __declspec(dllimport)
#define DECLSPEC_NORETURN __declspec(noreturn)
#define DUMMYSTRUCTNAME s
#define DUMMYSTRUCTNAME2 s2
#define DUMMYSTRUCTNAME3 s3
#define DUMMYUNIONNAME2 u2
#define DUMMYUNIONNAME3 u3
#define DUMMYUNIONNAME4 u4
#define DUMMYUNIONNAME5 u5
#define DUMMYUNIONNAME6 u6
#define DUMMYUNIONNAME7 u7
#define DUMMYUNIONNAME8 u8
#define FALSE 0
#define FASTCALL __fastcall
#define HMONITOR_DECLARED 1
#define MAX_PATH 128
#ifndef NULL
#define NULL 0
#endif
#define PACKED __attribute__((packed))
#define STDCALL __stdcall
#define STRICT 1
#define TRUE 1
#define VOID void
#define WINAPI __stdcall
#define WINAPIV __cdecl
#define WINVER 0x0400

/* ==================================================================
 * base types -- fundamental Windows type definitions
 * CE-specific types are marked; verify sizes for your platform
 * ================================================================ */

/* BOOL [CE-SPECIFIC]
 * Boolean (TRUE/FALSE)
 * 32-bit int on CE
 * source: win32/common/windows-data-types.md */
typedef int BOOL;

/* BYTE [CE-SPECIFIC]
 * 8-bit unsigned integer
 * Always 8-bit
 * source: win32/common/windows-data-types.md */
typedef unsigned char BYTE;

/* DWORD [CE-SPECIFIC]
 * 32-bit unsigned integer (same as desktop)
 * Always 32-bit on CE regardless of architecture
 * source: win32/common/windows-data-types.md */
typedef unsigned long DWORD;

/* DWORD64
 * source: win32/common/windows-data-types.md */
typedef unsigned __int64 DWORD64;

/* FLOAT
 * source: win32/common/windows-data-types.md */
typedef float FLOAT;

/* HFILE
 * source: win32/common/windows-data-types.md */
typedef int HFILE;

/* INT [CE-SPECIFIC]
 * Signed integer
 * Platform-dependent (32-bit on most CE platforms)
 * source: win32/common/windows-data-types.md */
typedef int INT;

/* LONG64
 * source: win32/common/windows-data-types.md */
typedef __int64 LONG64;

/* UHALF_PTR
 * CE is 32-bit: pointer-sized integer
 * source: win32/common/windows-data-types.md */
typedef unsigned short UHALF_PTR;

/* UINT [CE-SPECIFIC]
 * Unsigned integer
 * Platform-dependent (32-bit on most CE platforms)
 * source: win32/common/windows-data-types.md */
typedef unsigned int UINT;

/* UINT64
 * source: win32/common/windows-data-types.md */
typedef unsigned __int64 UINT64;

/* WORD [CE-SPECIFIC]
 * 16-bit unsigned integer
 * Always 16-bit
 * source: win32/common/windows-data-types.md */
typedef unsigned short WORD;

/* LONG [CE-SPECIFIC]
 * 32-bit signed integer
 * Always 32-bit on CE
 * source: win32/common/windows-data-types.md */
typedef long LONG;

/* ULONG [CE-SPECIFIC]
 * 32-bit unsigned integer
 * Always 32-bit on CE
 * source: win32/common/windows-data-types.md */
typedef unsigned long ULONG;

/* SHORT
 * source: win32/common/windows-data-types.md */
typedef short SHORT;

/* CHAR [CE-SPECIFIC]
 * 8-bit ANSI character
 * Always 8-bit; limited use on CE (prefer WCHAR)
 * source: win32/common/windows-data-types.md */
typedef char CHAR;

/* WCHAR [CE-SPECIFIC]
 * 16-bit Unicode character
 * Always 16-bit on CE (UTF-16LE)
 * source: win32/common/windows-data-types.md */
typedef wchar_t WCHAR;

/* HANDLE [CE-SPECIFIC]
 * Generic handle type
 * Pointer-sized on CE (32-bit on ARM, SHx; varies by platform)
 * source: win32/common/windows-data-types.md */
typedef void *HANDLE;

/* HDC
 * source: win32/common/windows-data-types.md */
typedef HANDLE HDC;

/* HPEN
 * source: win32/common/windows-data-types.md */
typedef HANDLE HPEN;

/* LPWSTR [CE-SPECIFIC]
 * Pointer to wide string
 * Primary mutable string type on CE
 * source: CE SDK reference */
typedef WCHAR *LPWSTR;

/* LPCWSTR [CE-SPECIFIC]
 * Pointer to const wide string
 * Primary string type on CE
 * source: CE SDK reference */
typedef const WCHAR *LPCWSTR;

/* LONG_PTR
 * CE is 32-bit: pointer-sized integer
 * source: win32/common/windows-data-types.md */
typedef long LONG_PTR;

/* UINT_PTR
 * CE is 32-bit: pointer-sized integer
 * source: win32/common/windows-data-types.md */
typedef unsigned long UINT_PTR;

/* ULONG_PTR
 * CE is 32-bit: pointer-sized integer
 * source: win32/common/windows-data-types.md */
typedef unsigned long ULONG_PTR;

/* DWORD_PTR
 * CE is 32-bit: pointer-sized integer
 * source: win32/common/windows-data-types.md */
typedef unsigned long DWORD_PTR;

/* INT_PTR [CE-SPECIFIC]
 * 32-bit CE pointer-sized integer
 * CE is 32-bit: pointer-sized integer
 * source: win32/common/windows-data-types.md (32-bit row) */
typedef long INT_PTR;

/* HALF_PTR [CE-SPECIFIC]
 * 32-bit CE pointer-sized integer
 * CE is 32-bit: pointer-sized integer
 * source: win32/common/windows-data-types.md (32-bit row) */
typedef short HALF_PTR;

/* UCHAR [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef unsigned char UCHAR;

/* USHORT [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef unsigned short USHORT;

/* PVOID [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef void *PVOID;

/* LPVOID [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef void *LPVOID;

/* LPCVOID [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef CONST void *LPCVOID;

/* LPSTR [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef CHAR *LPSTR;

/* LPCSTR [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef CONST CHAR *LPCSTR;

/* TCHAR [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef WCHAR TCHAR;

/* LPTSTR [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef LPWSTR LPTSTR;

/* LPCTSTR [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef LPCWSTR LPCTSTR;

/* PCTSTR [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef LPCWSTR PCTSTR;

/* LONGLONG [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef __int64 LONGLONG;

/* ULONGLONG [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef unsigned __int64 ULONGLONG;

/* HRESULT [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef LONG HRESULT;

/* NTSTATUS [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef LONG NTSTATUS;

/* SIZE_T [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef ULONG_PTR SIZE_T;

/* SSIZE_T [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef LONG_PTR SSIZE_T;

/* FARPROC [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef INT_PTR (WINAPI *FARPROC)(void);

/* NEARPROC [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef INT_PTR (WINAPI *NEARPROC)(void);

/* PROC [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef INT_PTR (WINAPI *PROC)(void);

/* SECURITY_ATTRIBUTES [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct _SECURITY_ATTRIBUTES SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

/* FILETIME [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct _FILETIME { DWORD dwLowDateTime; DWORD dwHighDateTime; } FILETIME, *PFILETIME, *LPFILETIME;

/* SYSTEMTIME [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct _SYSTEMTIME { WORD wYear; WORD wMonth; WORD wDayOfWeek; WORD wDay; WORD wHour; WORD wMinute; WORD wSecond; WORD wMilliseconds; } SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

/* CEOID [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef DWORD CEOID;

/* PCEOID [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef CEOID *PCEOID;

/* CEPROPID [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef DWORD CEPROPID;

/* PPVOID [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef PVOID *PPVOID;

/* LPTHREAD_START_ROUTINE [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID);

/* LARGE_INTEGER [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef union _LARGE_INTEGER { struct { DWORD LowPart; LONG HighPart; } u; LONGLONG QuadPart; } LARGE_INTEGER, *PLARGE_INTEGER;

/* PHYSICAL_ADDRESS [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;

/* CRITICAL_SECTION [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct _CRITICAL_SECTION CRITICAL_SECTION, *PCRITICAL_SECTION, *LPCRITICAL_SECTION;

/* STARTUPINFOW [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct _STARTUPINFOW STARTUPINFOW, *LPSTARTUPINFOW;

/* STARTUPINFO [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef STARTUPINFOW STARTUPINFO, *LPSTARTUPINFO;

/* PROCESS_INFORMATION [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct _PROCESS_INFORMATION PROCESS_INFORMATION, *LPPROCESS_INFORMATION, *PPROCESS_INFORMATION;

/* BITMAPINFOHEADER [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct tagBITMAPINFOHEADER BITMAPINFOHEADER, *PBITMAPINFOHEADER, *LPBITMAPINFOHEADER;

/* BITMAPINFO [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct tagBITMAPINFO BITMAPINFO, *PBITMAPINFO, *LPBITMAPINFO;

/* CHOOSECOLOR [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct tagCHOOSECOLOR CHOOSECOLOR, *LPCHOOSECOLOR;

/* CHOOSEFONT [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct tagCHOOSEFONT CHOOSEFONT, *LPCHOOSEFONT;

/* OPENFILENAME [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct tagOPENFILENAME OPENFILENAME, *LPOPENFILENAME;

/* DLGTEMPLATE [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct tagDLGTEMPLATE DLGTEMPLATE, *LPDLGTEMPLATE, *LPCDLGTEMPLATE;

/* LCID [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef DWORD LCID;

/* PDWORD [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef DWORD *PDWORD;

/* PUINT [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef UINT *PUINT;

/* LPINT [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef int *LPINT;

/* PINT [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef int *PINT;

/* PUSHORT [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef USHORT *PUSHORT;

/* PLONG [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef LONG *PLONG;

/* PULONG [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef ULONG *PULONG;

/* SYSTEM_INFO [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct _SYSTEM_INFO SYSTEM_INFO, *LPSYSTEM_INFO;

/* LPLOGFONT [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct tagLOGFONT *PLOGFONT, *LPLOGFONT;

/* TEXTMETRIC [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct tagTEXTMETRIC TEXTMETRIC, *PTEXTMETRIC, *LPTEXTMETRIC;

/* ENUMLOGFONT [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct tagENUMLOGFONT ENUMLOGFONT, *PENUMLOGFONT, *LPENUMLOGFONT;

/* WAVEFORMATEX [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct tWAVEFORMATEX WAVEFORMATEX, *PWAVEFORMATEX, *LPWAVEFORMATEX;

/* ULARGE_INTEGER [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct ULARGE_INTEGER { ULONGLONG QuadPart; } ULARGE_INTEGER, *PULARGE_INTEGER;

/* LPABC [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef struct _ABC *LPABC;

/* ATOM
 * source: win32/common/windows-data-types.md */
typedef WORD ATOM;

/* BOOLEAN
 * source: win32/common/windows-data-types.md */
typedef BYTE BOOLEAN;

/* COLORREF
 * source: win32/common/windows-data-types.md */
typedef DWORD COLORREF;

/* HBITMAP
 * source: win32/common/windows-data-types.md */
typedef HANDLE HBITMAP;

/* HBRUSH
 * source: win32/common/windows-data-types.md */
typedef HANDLE HBRUSH;

/* HCONVLIST
 * source: win32/common/windows-data-types.md */
typedef HANDLE HCONVLIST;

/* HDDEDATA
 * source: win32/common/windows-data-types.md */
typedef HANDLE HDDEDATA;

/* HDWP
 * source: win32/common/windows-data-types.md */
typedef HANDLE HDWP;

/* HENHMETAFILE
 * source: win32/common/windows-data-types.md */
typedef HANDLE HENHMETAFILE;

/* HFONT
 * source: win32/common/windows-data-types.md */
typedef HANDLE HFONT;

/* HGDIOBJ
 * source: win32/common/windows-data-types.md */
typedef HANDLE HGDIOBJ;

/* HGLOBAL
 * source: win32/common/windows-data-types.md */
typedef HANDLE HGLOBAL;

/* HHOOK
 * source: win32/common/windows-data-types.md */
typedef HANDLE HHOOK;

/* HICON
 * source: win32/common/windows-data-types.md */
typedef HANDLE HICON;

/* HINSTANCE
 * source: win32/common/windows-data-types.md */
typedef HANDLE HINSTANCE;

/* HKEY
 * source: win32/common/windows-data-types.md */
typedef HANDLE HKEY;

/* HKL
 * source: win32/common/windows-data-types.md */
typedef HANDLE HKL;

/* HLOCAL
 * source: win32/common/windows-data-types.md */
typedef HANDLE HLOCAL;

/* HMENU
 * source: win32/common/windows-data-types.md */
typedef HANDLE HMENU;

/* HMETAFILE
 * source: win32/common/windows-data-types.md */
typedef HANDLE HMETAFILE;

/* HMODULE
 * source: win32/common/windows-data-types.md */
typedef HINSTANCE HMODULE;

/* HMONITOR
 * source: win32/common/windows-data-types.md */
typedef HANDLE HMONITOR;

/* HPALETTE
 * source: win32/common/windows-data-types.md */
typedef HANDLE HPALETTE;

/* HRGN
 * source: win32/common/windows-data-types.md */
typedef HANDLE HRGN;

/* HSZ
 * source: win32/common/windows-data-types.md */
typedef HANDLE HSZ;

/* HWND [CE-SPECIFIC]
 * Window handle
 * Same as HANDLE
 * source: win32/common/windows-data-types.md */
typedef HANDLE HWND;

/* LPARAM [CE-SPECIFIC]
 * Message parameter (signed)
 * Pointer-sized on CE
 * source: win32/common/windows-data-types.md */
typedef LONG_PTR LPARAM;

/* LRESULT [CE-SPECIFIC]
 * Message result
 * Pointer-sized on CE
 * source: win32/common/windows-data-types.md */
typedef LONG_PTR LRESULT;

/* PTSTR
 * source: win32/common/windows-data-types.md */
typedef LPWSTR PTSTR;

/* WINSTA
 * source: win32/common/windows-data-types.md */
typedef HANDLE WINSTA;

/* WPARAM [CE-SPECIFIC]
 * Message parameter (unsigned)
 * Pointer-sized on CE
 * source: CE SDK reference */
typedef UINT_PTR WPARAM;

/* WNDPROC [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef LRESULT (CALLBACK *WNDPROC)(HWND, UINT, WPARAM, LPARAM);

/* TIMERPROC [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef void (CALLBACK *TIMERPROC)(HWND, UINT, UINT, DWORD);

/* DLGPROC [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef INT_PTR (CALLBACK *DLGPROC)(HWND, UINT, WPARAM, LPARAM);

/* WNDENUMPROC [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef BOOL (CALLBACK *WNDENUMPROC)(HWND, LPARAM);

/* WNDENUMPROCW [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef BOOL (CALLBACK *WNDENUMPROCW)(HWND, LPARAM);

/* FONTENUMPROC [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef int (CALLBACK *FONTENUMPROC)(ENUMLOGFONT FAR *, TEXTMETRIC FAR *, int, LPARAM);

/* FONTENUMPROCW [CE-SPECIFIC]
 * CE Unicode / 32-bit data-types row
 * source: win32/common/windows-data-types.md */
typedef int (CALLBACK *FONTENUMPROCW)(ENUMLOGFONT FAR *, TEXTMETRIC FAR *, int, LPARAM);

/* HCURSOR
 * source: win32/common/windows-data-types.md */
typedef HICON HCURSOR;

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* CALLBACK  [typedef, macro; shared; entity-headers] */

/* CONST  [struct, typedef, macro; shared; entity-headers] */

/* HIBYTE  [macro; shared] */

/* HIWORD  [macro; shared] */

/* HWINSTA  [typedef; shared; entity-headers] */

/* LOBYTE  [macro; shared] */

/* LOWORD  [macro; shared] */

/* MAKELONG  [macro; shared] */
#define MAKELONG(a, b) \ 
 ((LONG) (((WORD) (a)) | ((DWORD) ((WORD) (b))) << 16));

/* MAKEWORD  [macro; shared] */
#define MAKEWORD(a, b) \ 
 ((WORD) (((BYTE) (a)) | ((WORD) ((BYTE) (b))) << 8));

/* WINAPI  [typedef, macro; shared; entity-headers] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* HACCEL  [typedef; shared; entity-headers; win32-reference] */
typedef HANDLE HACCEL;

/* HDESK  [typedef; shared; entity-headers; win32-reference] */
typedef HANDLE HDESK;

/* HRSRC  [typedef; shared; entity-headers; win32-reference] */
typedef HANDLE HRSRC;

/* LPBOOL  [typedef; shared; entity-headers; win32-reference] */
typedef BOOL far *LPBOOL;

/* LPBYTE  [typedef; shared; entity-headers; win32-reference] */
typedef BYTE far *LPBYTE;

/* LPCOLORREF  [typedef; shared; entity-headers; win32-reference] */
typedef DWORD *LPCOLORREF;

/* LPDWORD  [typedef; shared; entity-headers; win32-reference] */
typedef DWORD *LPDWORD;

/* LPHANDLE  [typedef; shared; entity-headers; win32-reference] */
typedef HANDLE *LPHANDLE;

/* LPLONG  [typedef; shared; entity-headers; win32-reference] */
typedef long *LPLONG;

/* PBOOL  [typedef; shared; entity-headers; win32-reference] */
typedef BOOL *PBOOL;

/* PBYTE  [typedef; shared; entity-headers; win32-reference] */
typedef BYTE *PBYTE;

/* PFLOAT  [typedef; shared; entity-headers; win32-reference] */
typedef FLOAT *PFLOAT;

/* PHKEY  [typedef; shared; entity-headers; win32-reference] */
typedef HKEY *PHKEY;

/* POINT  [struct, function, library; shared] */
typedef struct tagPOINT {
 LONG x;
 LONG y;
} POINT;
typedef POINT *PPOINT, *LPPOINT;

/* POINTS  [struct; shared] */
typedef struct tagPOINTS { 
 SHORT x;
 SHORT y; 
} POINTS;
typedef POINTS *PPOINTS, *LPPOINTS;

/* RECT  [struct, library; shared] */
typedef struct _RECT { 
 LONG left; 
 LONG top; 
 LONG right; 
 LONG bottom; 
} RECT;
typedef RECT *PRECT, *LPRECT;

/* RECTL  [struct; shared] */
typedef struct _RECTL { 
 LONG left; 
 LONG top; 
 LONG right; 
 LONG bottom; 
} RECTL, *PRECTL;

/* SIZE  [struct, function, library; shared] */
typedef struct tagSIZE { 
 LONG cx; 
 LONG cy; 
} SIZE;
typedef SIZE *PSIZE, *LPSIZE;

/* LPWORD  [typedef; shared; entity-headers; win32-reference] */
typedef WORD *LPWORD;

/* PUCHAR  [typedef; shared; entity-headers; win32-reference] */
typedef UCHAR *PUCHAR;

/* PWORD  [typedef; shared; entity-headers; win32-reference] */
typedef WORD *PWORD;
typedef RECT *PRECT, *LPRECT;
typedef CONST RECT *LPCRECT;
typedef POINT *PPOINT, *LPPOINT;
typedef SIZE *PSIZE, *LPSIZE;

#endif /* _WINDEF_ */
