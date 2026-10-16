/* Ce_setup.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 4 constants, 8 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CE_SETUP_
#define _CE_SETUP_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define codeINSTALL_EXIT_DONE 0
#define codeINSTALL_INIT_CONTINUE 0
#define codeUNINSTALL_EXIT_DONE 0
#define codeUNINSTALL_INIT_CONTINUE 0

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* codeINSTALL_EXIT  [enum; ce-only] */
typedef enum {
 codeINSTALL_EXIT_DONE = 0, 
 codeINSTALL_EXIT_UNINSTALL 
} codeINSTALL_EXIT;
typedef codeINSTALL_EXIT *PcodeINSTALL_EXIT, *LPcodeINSTALL_EXIT;

/* codeINSTALL_INIT  [enum; ce-only] */
typedef enum {
 codeINSTALL_INIT_CONTINUE = 0,
 codeINSTALL_INIT_CANCEL
} codeINSTALL_INIT;
typedef codeINSTALL_INIT *PcodeINSTALL_INIT, *LPcodeINSTALL_INIT;

/* codeUNINSTALL_EXIT  [enum; ce-only] */
typedef enum {
 codeUNINSTALL_EXIT_DONE = 0 
} codeUNINSTALL_EXIT;
typedef codeUNINSTALL_EXIT *PcodeUNINSTALL_EXIT, *LPcodeUNINSTALL_EXIT;

/* codeUNINSTALL_INIT  [enum; ce-only] */
typedef enum {
 codeUNINSTALL_INIT_CONTINUE = 0,
 codeUNINSTALL_INIT_CANCEL
} codeUNINSTALL_INIT;
typedef codeUNINSTALL_INIT *PcodeUNINSTALL_INIT, *LPcodeUNINSTALL_INIT;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699 */

/* Uninstall_Exit  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Setup.dll] */
codeUNINSTALL_EXIT Uninstall_Exit(
 HWND hwndParent 
);

/* Uninstall_Init  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Setup.dll] */
codeUNINSTALL_INIT Uninstall_Init(
 HWND hwndParent,
 LPCTSTR pszInstallDir
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 1.0..199, 2.11..2.12, 3.0..699 */

/* Install_Exit  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..699; Coredll.lib, Setup.dll] */
codeINSTALL_EXIT Install_Exit(
 HWND hwndParent,
 LPCTSTR pszInstallDir,
 WORD cFailedDirs,
 WORD cFailedFiles,
 WORD cFailedRegKeys,
 WORD cFailedRegVals,
 WORD cFailedShortcuts
);

/* Install_Init  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..699; Setup.dll] */
codeINSTALL_INIT Install_Init(
 HWND hwndParent,
 BOOL fFirstCall, 
 BOOL fPreviouslyInstalled,
 LPCTSTR pszInstallDir
);
#endif /* _WIN32_WCE */

#endif /* _CE_SETUP_ */
