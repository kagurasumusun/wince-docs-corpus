/* cfgmgrapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 2 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CFGMGRAPI_
#define _CFGMGRAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CFGFLAG_METADATA 0x0002
#define CFGFLAG_PROCESS 0x0001

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* DMProcessConfigXML  [function; ce-only; CE 6.0..699; aygshell.lib] */
HRESULT DMProcessConfigXML(
 LPCWSTR pszWXMLin,
 DWORD dwFlags,
 LPWSTR* ppszwXMLout
);
#endif /* _WIN32_WCE */

#endif /* _CFGMGRAPI_ */
