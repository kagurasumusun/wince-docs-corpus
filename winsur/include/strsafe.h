/* strsafe.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 5 constants, 30 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _STRSAFE_
#define _STRSAFE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define STRSAFE_FILL_BEHIND_NULL 0x00000200
#define STRSAFE_FILL_ON_FAILURE 0x00000400
#define STRSAFE_IGNORE_NULLS 0x00000100
#define STRSAFE_NO_TRUNCATION 0x00001000
#define STRSAFE_NULL_ON_FAILURE 0x00000800

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* StringCbCat  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCbCatA,StringCbCatW (CE is W-side)] */
HRESULT StringCbCat(
 LPTSTR pszDest,
 size_t cbDestest,
 LPCTSTR pszSrc
);

/* StringCbCatEx  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCbCatExA,StringCbCatExW (CE is W-side)] */
HRESULT StringCbCatEx(
 LPTSTR pszDest,
 size_t cbDest,
 LPCTSTR pszSrc,
 LPTSTR *ppszDestEnd,
 size_t *pcbRemaining,
 DWORD dwFlags
);

/* StringCbCatN  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCbCatNA,StringCbCatNW (CE is W-side)] */
HRESULT StringCbCatN( 
 LPTSTR pszDest,
 size_t cbDest,
 LPCTSTR pszSrc,
 size_t cbMaxAppend
);

/* StringCbCatNEx  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCbCatNExA,StringCbCatNExW (CE is W-side)] */
HRESULT StringCbCatNEx( 
 LPTSTR pszDest,
 size_t cbDest,
 LPCTSTR pszSrc,
 size_t cbMaxAppend,
 LPTSTR *ppszDestEnd,
 size_t *pcbRemaining,
 DWORD dwFlags
);

/* StringCbCopy  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCbCopyA,StringCbCopyW (CE is W-side)] */
HRESULT StringCbCopy( 
 LPTSTR pszDest,
 size_t cbDest,
 LPCTSTR pszSrc
);

/* StringCbCopyEx  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCbCopyExA,StringCbCopyExW (CE is W-side)] */
HRESULT StringCbCopyEx( 
 LPTSTR pszDest,
 size_t cbDest,
 LPCTSTR pszSrc,
 LPTSTR *ppszDestEnd,
 size_t *pcbRemaining,
 DWORD dwFlags
);

/* StringCbCopyN  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCbCopyNA,StringCbCopyNW (CE is W-side)] */
HRESULT StringCbCopyN( 
 LPTSTR pszDest,
 size_t cbDest,
 LPCTSTR pszSrc,
 size_t cbSrc
);

/* StringCbCopyNEx  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCbCopyNExA,StringCbCopyNExW (CE is W-side)] */
HRESULT StringCbCopyNEx( 
 LPTSTR pszDest,
 size_t cbDest,
 LPCTSTR pszSrc,
 size_t cbSrc,
 LPTSTR *ppszDestEnd,
 size_t *pcbRemaining,
 DWORD dwFlags
);

/* StringCbGets  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCbGetsA,StringCbGetsW (CE is W-side)] */
HRESULT StringCbGets( 
 LPTSTR pszDest,
 size_t cbDest
);

/* StringCbGetsEx  [function; shared; CE 5.0..699; A/W StringCbGetsExA,StringCbGetsExW (CE is W-side)] */
HRESULT StringCbGetsEx( 
 LPTSTR pszDest,
 size_t cbDest,
 LPTSTR *ppszDestEnd,
 size_t *pcbRemaining,
 DWORD dwFlags
);

/* StringCbLength  [function; shared; CE 5.0..699; coredll.dll, strsafe.lib; A/W StringCbLengthA,StringCbLengthW (CE is W-side)] */
HRESULT StringCbLength( 
 LPCTSTR psz,
 size_t cbMax,
 size_t *pcb
);

/* StringCbPrintf  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCbPrintfA,StringCbPrintfW (CE is W-side)] */
HRESULT StringCbPrintf( 
 LPTSTR pszDest,
 size_t cbDest,
 LPCTSTR pszFormat,
 ...
);

/* StringCbPrintfEx  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCbPrintfExA,StringCbPrintfExW (CE is W-side)] */
HRESULT StringCbPrintfEx( 
 LPTSTR pszDest,
 size_t cbDest,
 LPTSTR *ppszDestEnd,
 size_t *pcbRemaining,
 DWORD dwFlags,
 LPCTSTR pszFormat,
 ...
);

/* StringCbVPrintf  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCbVPrintfA,StringCbVPrintfW (CE is W-side)] */
HRESULT StringCbVPrintf( 
 LPTSTR pszDest,
 size_t cbDest,
 LPCTSTR pszFormat,
 va_list argList
);

/* StringCbVPrintfEx  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCbVPrintfExA,StringCbVPrintfExW (CE is W-side)] */
HRESULT StringCbVPrintfEx( 
 LPTSTR pszDest,
 size_t cbDest,
 LPTSTR *ppszDestEnd,
 size_t *pcbRemaining,
 DWORD dwFlags,
 LPCTSTR pszFormat,
 va_list argList
);

/* StringCchCat  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCchCatA,StringCchCatW (CE is W-side)] */
HRESULT StringCchCat( 
 LPTSTR pszDest,
 size_t cchDest,
 LPCTSTR pszSrc
);

/* StringCchCatEx  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCchCatExA,StringCchCatExW (CE is W-side)] */
HRESULT StringCchCatEx( 
 LPTSTR pszDest,
 size_t cchDest,
 LPCTSTR pszSrc,
 LPTSTR *ppszDestEnd,
 size_t *pcchRemaining,
 DWORD dwFlags
);

/* StringCchCatN  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCchCatNA,StringCchCatNW (CE is W-side)] */
HRESULT StringCchCatN( 
 LPTSTR pszDest,
 size_t cchDest,
 LPCTSTR pszSrc,
 size_t cchMaxAppend
);

/* StringCchCatNEx  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCchCatNExA,StringCchCatNExW (CE is W-side)] */
HRESULT StringCchCatNEx( 
 LPTSTR pszDest,
 size_t cchDest,
 LPCTSTR pszSrc,
 size_t cchMaxAppend,
 LPTSTR *ppszDestEnd,
 size_t *pcchRemaining,
 DWORD dwFlags
);

/* StringCchCopy  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCchCopyA,StringCchCopyW (CE is W-side)] */
HRESULT StringCchCopy( 
 LPTSTR pszDest,
 size_t cchDest,
 LPCTSTR pszSrc
);

/* StringCchCopyEx  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCchCopyExA,StringCchCopyExW (CE is W-side)] */
HRESULT StringCchCopyEx( 
 LPTSTR pszDest,
 size_t cchDest,
 LPCTSTR pszSrc,
 LPTSTR *ppszDestEnd,
 size_t *pcchRemaining,
 DWORD dwFlags
);

/* StringCchCopyN  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCchCopyNA,StringCchCopyNW (CE is W-side)] */
HRESULT StringCchCopyN( 
 LPTSTR pszDest,
 size_t cchDest,
 LPCTSTR pszSrc,
 size_t cchSrc
);

/* StringCchCopyNEx  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCchCopyNExA,StringCchCopyNExW (CE is W-side)] */
HRESULT StringCchCopyNEx( 
 LPTSTR pszDest,
 size_t cchDest,
 LPCTSTR pszSrc,
 size_t cchSrc,
 LPTSTR *ppszDestEnd,
 size_t *pcchRemaining,
 DWORD dwFlags
);

/* StringCchGets  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCchGetsA,StringCchGetsW (CE is W-side)] */
HRESULT StringCchGets( 
 LPTSTR pszDest,
 size_t cchDest
);

/* StringCchGetsEx  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCchGetsExA,StringCchGetsExW (CE is W-side)] */
HRESULT StringCchGetsEx( 
 LPTSTR pszDest,
 size_t cchDest,
 LPTSTR *ppszDestEnd,
 size_t *pcchRemaining,
 DWORD dwFlags
);

/* StringCchLength  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCchLengthA,StringCchLengthW (CE is W-side)] */
HRESULT StringCchLength( 
 LPCTSTR psz,
 size_t cchMax,
 size_t *pcch
);

/* StringCchPrintf  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCchPrintfA,StringCchPrintfW (CE is W-side)] */
HRESULT StringCchPrintf( 
 LPTSTR pszDest,
 size_t cchDest,
 LPCTSTR pszFormat,
 ...
);

/* StringCchPrintfEx  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCchPrintfExA,StringCchPrintfExW (CE is W-side)] */
HRESULT StringCchPrintfEx( 
 LPTSTR pszDest,
 size_t cchDest,
 LPTSTR *ppszDestEnd,
 size_t *pcchRemaining,
 DWORD dwFlags,
 LPCTSTR pszFormat,
 ...
);

/* StringCchVPrintf  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCchVPrintfA,StringCchVPrintfW (CE is W-side)] */
HRESULT StringCchVPrintf( 
 LPTSTR pszDest,
 size_t cchDest,
 LPCTSTR pszFormat,
 va_list argList
);

/* StringCchVPrintfEx  [function; shared; CE 5.0..699; strsafe.lib; A/W StringCchVPrintfExA,StringCchVPrintfExW (CE is W-side)] */
HRESULT StringCchVPrintfEx( 
 LPTSTR pszDest,
 size_t cchDest,
 LPTSTR *ppszDestEnd,
 size_t *pcchRemaining,
 DWORD dwFlags,
 LPCTSTR pszFormat,
 va_list argList
);
#endif /* _WIN32_WCE */

#endif /* _STRSAFE_ */
