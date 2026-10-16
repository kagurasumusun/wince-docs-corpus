/* Trackbarview.hpp -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 3 extra decls
 */
#ifndef _TRACKBARVIEW_HPP_
#define _TRACKBARVIEW_HPP_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void DrawChannel( HDC hdc, DWORD style, BOOL bSelection, LONG lSelStart, LONG lSelEnd, LONG lLogMin, LONG lLogMax, LONG iSizePhys, int left, LPRECT lprc );
void DrawThumb( HWND hwnd, HDC hdc, DWORD style, int iThumbHeight, int iThumbWidth, LPRECT lprc, BOOL fSelected );
void DrawTics( HDC hdc, DWORD style, RECT* prc, PDWORD pTics, int nTics, int ticFreq, LONG lSelStart, LONG lSelEnd, LONG lLogMin, LONG lLogMax, LONG iSizePhys, bool bDrawSelectionTriangles );

#endif /* _TRACKBARVIEW_HPP_ */
