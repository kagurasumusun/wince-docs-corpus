/* Projects.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 6 constants, 6 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _PROJECTS_
#define _PROJECTS_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define PA_MAX_PATHNAME 96
#define PRJ_ENUM_ALL_DEVICES 0x4
#define PRJ_ENUM_ALL_PROJ 0x10
#define PRJ_ENUM_FLASH 0x2
#define PRJ_ENUM_HOME_PROJ 0x100
#define PRJ_ENUM_MEMORY 0x1

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213)) /* CE 2.11..2.12 */

/* FindFirstFlashCard  [function; ce-only; CE 2.11..2.12] */
HANDLE FindFirstFlashCard(LPWIN32_FIND_DATA lpFindFlashData);

/* FindFirstProjectFile  [function; ce-only; CE 2.11..2.12] */
HANDLE FindFirstProjectFile(LPCTSTR lpFileName, 
LPWIN32_FIND_DATA lpFindFileData, DWORD dwOidFlash, 
LPTSTR lpszProj);

/* FindNextFlashCard  [function; ce-only; CE 2.11..2.12] */
BOOL FindNextFlashCard(HANDLE hFlashCard, 
LPWIN32_FIND_DATA lpFindFlashData);

/* FindNextProjectFile  [function; ce-only; CE 2.11..2.12] */
BOOL FindNextProjectFile(HANDLE hHandle, 
LPWIN32_FIND_DATA lpFindProjData);
#endif /* _WIN32_WCE */

#endif /* _PROJECTS_ */
