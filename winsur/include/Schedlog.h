/* Schedlog.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SCHEDLOG_
#define _SCHEDLOG_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x500)) /* CE 3.0..499 */

/* SchedLogGetProcessName  [function; ce-only; CE 3.0..499; Schedlog.lib] */
LPCSTR SchedLogGetProcessName(
 DWORD dwProcID 
);

/* SchedLogGetThreadProgramCounter  [function; ce-only; CE 3.0..499; Schedlog.lib] */
DWORD SchedLogGetThreadProgramCounter(
 DWORD dwThreadID, 
 LPCSTR* ppszThreadModuleName, 
 LPCSTR* ppszThreadFunctionName 
);

/* SchedLogTranslate  [function; ce-only; CE 3.0..499; Schedlog.lib] */
void SchedLogTranslate( 
 DWORD dwThreadID, 
 HANDLE* pThreadHandle, 
 DWORD dwProcID, 
 HANDLE* pProcessHandle 
);
#endif /* _WIN32_WCE */

#endif /* _SCHEDLOG_ */
