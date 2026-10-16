/* mpconfig.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 11 extra decls
 */
#ifndef _MPCONFIG_
#define _MPCONFIG_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT GetBlendingParameter( DWORD *pdwBlendingParameter );
HRESULT GetRelativePosition( DWORD *pdwLeft, DWORD *pdwTop, DWORD *pdwRight, DWORD *pdwBottom );
HRESULT GetStreamTransparent( BOOL *pbStreamTransparent );
HRESULT GetZOrder( DWORD *pdwZOrder );
HRESULT SetBlendingParameter( DWORD dwBlendingParameter );
HRESULT SetRelativePosition( DWORD dwLeft, DWORD dwTop, DWORD dwRight, DWORD dwBottom );
HRESULT SetStreamTransparent( BOOL bStreamTransparent );
HRESULT SetZOrder( DWORD dwZOrder );

#endif /* _MPCONFIG_ */
