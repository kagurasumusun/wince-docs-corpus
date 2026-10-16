/* StressUtils.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 12 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _STRESSUTILS_
#define _STRESSUTILS_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* ITERATION_INFO  [struct; ce-only] */
typedef struct {
 UINT cbSize;
 int index;
 int iteration;
} ITERATION_INFO;
typedef ITERATION_INFO *PITERATION_INFO, *LPITERATION_INFO;

/* MODULE_PARAMS  [struct; ce-only] */
typedef struct {
 DWORD dwDuration;
 DWORD dwLoggingZones;
 UINT uVerbosity;
 UINT uHarnessLogLevel;
 UINT uBreakLevel;
 UINT iSlot;
 LPTSTR tszServer;
 LPTSTR tszReserved;
 LPTSTR tszUser;
} MODULE_PARAMS;
typedef MODULE_PARAMS *PMODULE_PARAMS, *LPMODULE_PARAMS;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x200 && _WIN32_WCE < 0x210) || (_WIN32_WCE >= 0x212 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.0..209, 2.12..399, 5.0..699 */

/* Log  [function; ce-only; CE 2.0..209, 2.12..399, 5.0..699; coredll.dll, StressUtils.lib, stressutils.lib] */
void Log(
 DWORD dwVerbosity,
 const TCHAR* tszFormat,
 vargs ...
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* GetRunningModuleCount  [function; ce-only; CE 5.0..699; StressUtils.lib, stressutils.lib] */
LONG GetRunningModuleCount(
 HANDLE hInstance
);

/* InitializeStressUtils  [function; ce-only; CE 5.0..699; StressUtils.lib, stressutils.lib] */
BOOL InitializeStressUtils(
 LPCTSTR tszModuleName,
 DWORD dwDefaultLoggingZones,
 MODULE_PARAMS* pmp
);

/* LogAll  [function; ce-only; CE 5.0..699; StressUtils.lib, stressutils.lib] */
void LogAll(
 const TCHAR* tszFormat,
 vargs ...
);

/* LogComment  [function; ce-only; CE 5.0..699; StressUtils.lib, stressutils.lib] */
void LogComment(
 const TCHAR* tszFormat,
 vargs ...
);

/* LogEx  [function; ce-only; CE 5.0..699; StressUtils.lib, stressutils.lib] */
void LogEx(
 DWORD dwVerbosity,
 DWORD dwZone,
 const TCHAR* tszFormat,
 vargs ...
);

/* LogFail  [function; ce-only; CE 5.0..699; StressUtils.lib, stressutils.lib] */
void LogFail(
 const TCHAR* tszFormat,
 vargs ...
);

/* LogVerbose  [function; ce-only; CE 5.0..699; StressUtils.lib, stressutils.lib] */
void LogVerbose(
 const TCHAR* tszFormat,
 vargs ...
);

/* LogWarn1  [function; ce-only; CE 5.0..699; StressUtils.lib, stressutils.lib] */
void LogWarn1(
 const TCHAR* tszFormat,
 vargs ...
);

/* LogWarn2  [function; ce-only; CE 5.0..699; StressUtils.lib, stressutils.lib] */
void LogWarn2(
 const TCHAR* tszFormat,
 vargs ...
);
#endif /* _WIN32_WCE */

#endif /* _STRESSUTILS_ */
