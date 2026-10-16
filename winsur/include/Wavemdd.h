/* Wavemdd.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 10 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WAVEMDD_
#define _WAVEMDD_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..399, 5.0..699 */

/* WAV_Close  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
BOOL WAV_Close(
 DWORD dwOpenData 
);

/* WAV_Deinit  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
PVOID WAV_Deinit(
 DWORD dwData 
);

/* WAV_Init  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
PVOID WAV_Init(
 DWORD dwInfo 
);

/* WAV_IOControl  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
BOOL WAV_IOControl(
 DWORD dwOpenData,
 DWORD dwCode,
 PBYTE pBufIn,
 DWORD dwLenIn,
 PBYTE pBufOut,
 DWORD dwLenOut,
 PDWORD pdwActualOut 
);

/* WAV_Open  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
PVOID WAV_Open(
 DWORD dwData,
 DWORD dwAccess,
 DWORD dwShareMode 
);

/* WAV_PowerDown  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
void WAV_PowerDown(void);

/* WAV_PowerUp  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
void WAV_PowerUp(void);

/* WAV_Read  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
DWORD WAV_Read(
 DWORD dwOpenData,
 LPVOID pBuf,
 DWORD len 
);

/* WAV_Seek  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
DWORD WAV_Seek(
 DWORD dwOpenData,
 long pos,
 DWORD type 
);

/* WAV_Write  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
DWORD WAV_Write(
 DWORD dwOpenData,
 LPCVOID pBuf,
 DWORD len 
);
#endif /* _WIN32_WCE */

#endif /* _WAVEMDD_ */
