/* Tux.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 11 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _TUX_
#define _TUX_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* SPS_LOAD_DLL  [struct; ce-only] */
typedef struct _SPS_LOAD_DLL {
 BOOL fUnicode;
} SPS_LOAD_DLL, *LPSPS_LOAD_DLL;

/* SPS_SHELL_INFO  [struct; ce-only] */
typedef struct _SPS_SHELL_INFO {
 HINSTANCE hInstance;
 HWND hWnd;
 HINSTANCE hLib;
 HANDLE hevmTerminate;
 BOOL fUsingServer;
 LPCTSTR szDllCmdLine;
} SPS_SHELL_INFO, *LPSPS_SHELL_INFO;

/* TPS_EXECUTE  [struct; ce-only] */
typedef struct _TPS_EXECUTE {
 DWORD dwRandomSeed;
 DWORD dwThreadCount;
 DWORD dwThreadNumber;
} TPS_EXECUTE, *LPTPS_EXECUTE;

/* TPS_QUERY_THREAD_COUNT  [struct; ce-only] */
typedef struct _TPS_QUERY_THREAD_COUNT {
 DWORD dwThreadCount;
} TPS_QUERY_THREAD_COUNT, *LPTPS_QUERY_THREAD_COUNT;

#endif /* _TUX_ */
