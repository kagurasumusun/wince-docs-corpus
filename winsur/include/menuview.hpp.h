/* menuview.hpp -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 17 extra decls
 */
#ifndef _MENUVIEW_HPP_
#define _MENUVIEW_HPP_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
int CascadeArrowWidth(void);
void ColumnComputeWidth( long& xColumn, long cxMaxString, long cxMaxAccel, long* pcxTotal, long* pxAccel );
void DrawCascadeArrow( HDC hdc, long x, long y, long cx, long cy, UINT menustate, BOOL bRightToLeft );
void DrawCheckMark( HDC hdc, long x, long y, UINT menustate, );
void DrawColumnBreak( HDC hdc, long x, long y, long cx, long cy, long cxMenu, long cyMenu, UINT menustate );
void DrawScrollArrows( HDC hdc, long cxMenu, long cyMenu, BOOL bUpArrowEnabled, BOOL bDownArrowEnabled );
void DrawSeparator( HDC hdc, long x, long y, long cx, long cy, long cxMenu );
void DrawString( HDC hdc, WCHAR* pszItemString, int cchItemString, BOOL bPopup, UINT menustate, UINT uDrawAction, BOOL bBigFillRect, long x, long y, long cx, long cy, long cxMenu, long ichAccel, long xAccel, WCHAR chMnemo, long cxArrow );
void EraseBackground( HDC hdc, RECT* prc );
static HFONT MenuBarFont(void);
void NotPopupStringItemComputeSize( HDC hdc, WCHAR* pszItemString, int cchItemString, long cxMenu, long cyMenu, long* pcx, long* pcy );
static HFONT PopupMenuFont(void);
void PopupStringItemComputeSize( HDC hdc, WCHAR* pszItemString, int cchItemString, int ichAccel, WCHAR chMnemo, long cxMenu, long cyMenu, long* pcx, long* pcy );
int ScrollArrowHeight(void);
void SeparatorItemComputeSize( BOOL bPopup, long cxMenu, long cyMenu, long* pcx, long* pcy );
void SetupColors( HDC hdc, UINT menustate );
void SingleColumnComputeWidth( long cxMaxString, long cxMaxAccel, long* pcxTotal, long* pxAccel );

#endif /* _MENUVIEW_HPP_ */
