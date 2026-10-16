/* dwdmptxt.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 4 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _DWDMPTXT_
#define _DWDMPTXT_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* GetDmpLines  [function; ce-only; CE 6.0..699; dwdmptxt.lib] */
HRESULT GetDmpLines(
 HANDLE hDmpFile,
 LPWSTR pwzBuf,
 DWORD dwBufSize,
 DWORD dwBegLine,
 DWORD dwEndLine
);

/* InitDmpTxt  [function; ce-only; CE 6.0..699; dwdmptxt.lib] */
HRESULT InitDmpTxt(
 LPCWSTR pwzFilePath,
 DWORD dwMaxCharsPerLine,
 DWORD* pdwTotalLines,
 HANDLE* phDmpFile
);
#endif /* _WIN32_WCE */

#endif /* _DWDMPTXT_ */
