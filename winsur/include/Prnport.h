/* Prnport.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 5 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _PRNPORT_
#define _PRNPORT_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..699 */

/* GetPrinterInfo  [function; ce-only; CE 2.11..2.12, 3.0..699] */
DWORD WINAPI GetPrinterInfo(
 HANDLE hPrint,
 DWORD dwOption,
 PVOID pBuff,
 PDWORD pBuffLen 
);

/* PrinterClose  [function; ce-only; CE 2.11..2.12, 3.0..699] */
VOID WINAPI PrinterClose(
 HANDLE hPrint 
);

/* PrinterSend  [function; ce-only; CE 2.11..2.12, 3.0..699] */
BOOL WINAPI PrinterSend(
 HANDLE hPrint,
 LPCVOID lpBuffer,
 DWORD dwBytes 
);

/* ReportPrinterStatus  [function; ce-only; CE 2.11..2.12, 3.0..699] */
BOOL WINAPI ReportPrinterStatus(
 DWORD dwStatus,
 LPCTSTR lpPortName,
 LPCTSTR lpPrinterName,
 LPARAM lparam 
);
#endif /* _WIN32_WCE */

#endif /* _PRNPORT_ */
