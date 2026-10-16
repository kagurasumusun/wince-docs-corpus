/* Sphelper.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 7 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SPHELPER_
#define _SPHELPER_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* SpGetDefaultTokenIdFromCategoryId  [function; ce-only; CE 4.0..699; Sapilib.lib, sapilib.lib] */
inline HRESULT SpGetDefaultTokenIdFromCategoryId(
 const WCHAR* pszCategoryId,
 WCHAR** ppszTokenId
);

/* SpSetDefaultTokenIdForCategoryId  [function; ce-only; CE 4.0..699; Sapilib.lib, sapilib.lib] */
inline HRESULT SpSetDefaultTokenIdForCategoryId(
 const WCHAR* pszCategoryId,
 const WCHAR* pszTokenId
);
#endif /* _WIN32_WCE */

#endif /* _SPHELPER_ */
