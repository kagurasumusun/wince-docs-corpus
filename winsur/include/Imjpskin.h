/* Imjpskin.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 24 extra decls
 */
#ifndef _IMJPSKIN_
#define _IMJPSKIN_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* MARGINS  [struct; shared] */
typedef struct _MARGINS {
 int cxLeftWidth;
 int cxRightWidth;
 int cyTopHeight;
 int cyBottomHeight;
} MARGINS,* PMARGINS;

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void AdjustRect( LPRECT lprcContent, DWORD dwState );
HANDLE CreateRenderingMetrics( HDC hDC, INT iMaxCand, WCHAR* pszCandidates, WCHAR* pszInlineComments, HFONT hFontCandidates, HFONT hFontInlineComments, HICON hIconMemo, DWORD dwFlags );
HANDLE FreeRenderingMetrics( HANDLE hMetrics );
DWORD GetHorizontalOffset(void);
void GetMargins( PMARGINS pMargins );
static INT GetMaxHeight(void);
static INT GetMaxItems(void);
UINT GetSeparator(void);
DWORD GetWndStyle(void);
DWORD GetWndStyleEx(void);
BOOL IsAvailable(void);
BOOL IsHoverActionSupported(void);
BOOL IsVisibleAlways(void);
void PaintBackground( HDC hDC, LPRECT lprc, DWORD dwState, DWORD dwFlags );
void PaintBitmap( HDC hDC, LPRECT lprc, HBITMAP hBitmap, DWORD dwState, DWORD dwFlags );
void PaintCandidateString( HDC hDC, const LPRECT lprc, HANDLE hMetrics, INT iIdMenu, INT iIdMenuMax, BOOL bSel, BOOL fScrollBarIsVisible, LPCTSTR pszCandString, DWORD dwFlags );
BOOL PaintGripper( HDC hDC, LPRECT lprc, DWORD dwType );
void PaintIcon( HDC hDC, LPRECT lprc, HICON hIcon, DWORD dwState, DWORD dwFlags );
void PaintInlineComment( HDC hDC, const LPRECT lprc, HANDLE hMetrics, INT iIdMenu, INT iIdMenuMax, BOOL bSel, BOOL fScrollBarIsVisible, LPCTSTR pszInlineComment, DWORD dwFlags );
void PaintText( HDC hDC, LPRECT lprc, const WCHAR* pchText, INT cchText, DWORD dwTextFlag, DWORD dwState );
BOOL UseCandMenuButton(void);
BOOL UseCandNumText(void);
BOOL UseNumButtons(void);
BOOL UseSortButton(void);

#endif /* _IMJPSKIN_ */
