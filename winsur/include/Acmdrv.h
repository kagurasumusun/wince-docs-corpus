/* Acmdrv.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 9 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _ACMDRV_
#define _ACMDRV_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x200 && _WIN32_WCE < 0x210) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699 */

/* ACM_Close  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Acmdwrap.lib] */
BOOL ACM_Close(
 DWORD dwOpenData
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x200 && _WIN32_WCE < 0x210) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 2.0..209, 2.11..2.12, 3.0..699 */

/* ACM_Deinit  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Acmdwrap.lib] */
PVOID ACM_Deinit(
 DWORD dwData
);

/* ACM_Init  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Acmdwrap.lib] */
PVOID ACM_Init(
 DWORD dwInfo
);

/* ACM_IOControl  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Acmdwrap.lib] */
BOOL ACM_IOControl(
 DWORD dwOpenData,
 DWORD dwCode,
 PBYTE pBufIn,
 DWORD dwLenIn,
 PBYTE pBufOut,
 DWORD dwLenOut,
 PDWORD pdwActualOut
);

/* ACM_PowerDown  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Acmdwrap.lib] */
void ACM_PowerDown(void);

/* ACM_PowerUp  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Acmdwrap.lib] */
void ACM_PowerUp(void);

/* ACM_Read  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Acmdwrap.lib] */
DWORD ACM_Read(
 DWORD dwOpenData,
 LPVOID pBuf,
 DWORD len
);

/* ACM_Seek  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Acmdwrap.lib] */
DWORD ACM_Seek(
 DWORD dwOpenData,
 long pos,
 DWORD type
);

/* ACM_Write  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Acmdwrap.lib] */
DWORD ACM_Write(
 DWORD dwOpenData,
 LPCVOID pBuf,
 DWORD len
);
#endif /* _WIN32_WCE */

#endif /* _ACMDRV_ */
