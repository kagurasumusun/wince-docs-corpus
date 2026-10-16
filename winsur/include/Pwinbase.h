/* Pwinbase.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _PWINBASE_
#define _PWINBASE_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* FileSystemPowerFunction  [function; ce-only; CE 4.0..699; Coredll.lib, coredll.lib] */
void FileSystemPowerFunction(
 DWORD dwflags
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* GetPasswordStatus  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
DWORD GetPasswordStatus(void);

/* SetPasswordStatus  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL SetPasswordStatus(
 DWORD dwStatus,
 LPWSTR lpszPassword
);
#endif /* _WIN32_WCE */

#endif /* _PWINBASE_ */
