/* MiniSH.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 10 extra decls
 */
#ifndef _MINISH_
#define _MINISH_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT GetNearestLineFromAddress( ADDRESS_TYPEAddress, LPWSTR*ppszModule, LPWSTR*ppszSource, DWORD*dwLine);
HRESULT GetNearestSymbolFromAddress( ADDRESS_TYPEAddress,DWORD*pdwPid,LPWSTR*ppszModule,LPWSTR*ppszSource,LPWSTR* ppszRoutine,LPWSTR*ppszSymbol,DWORD*pdwDistance);
HRESULT GetSymbolPath( LPWSTR* ppszPath);
HRESULT SetSymbolPath( LPCWSTR pszPath);

#endif /* _MINISH_ */
