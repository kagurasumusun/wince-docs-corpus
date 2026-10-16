/* Sip.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 2 declarations, 0 outlines, 0 base types, 0 extra macros, 13 extra decls
 */
#ifndef _SIP_
#define _SIP_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* LMDATA  [struct; ce-only] */
typedef struct _tagLMDATA{
 DWORD dwVersion;
 DWORD flags;
 DWORD cnt;
 DWORD dwOffsetSymbols;
 DWORD dwOffsetSkip;
 DWORD dwOffsetScore;
}LMDATA;
typedef LMDATA *PLMDATA, *LPLMDATA;

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT Deselect( void );
HRESULT GetImData( DWORD dwSize, void *pvImData);
HRESULT Hiding( void );
HRESULT Select( HWND hwndSip);
HRESULT SendAlternatives (LMDATA* plmd);
HRESULT SendAlternatives2( LMDATA *plmd);
HRESULT SendCharEvents( UINT uVK, UINT uKeyFlags, UINT uChars, UINT *puShift, UINT *puChars);
HRESULT SendString( LPTSTR ptszStr, DWORD dwSize);
HRESULT SendVirtualKey( BYTE bVk, DWORD dwFlags);
HRESULT SetIMMActiveContext ( HWND hwnd, BOOL bOpen, DWORD dwConversion, DWORD dwSentence, DWORD hkl);
HRESULT SetImData( DWORD dwSize, void *pvImData);
HRESULT Showing( void );

#endif /* _SIP_ */
