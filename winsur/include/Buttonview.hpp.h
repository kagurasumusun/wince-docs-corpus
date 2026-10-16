/* Buttonview.hpp -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 1 outlines, 0 base types, 0 extra macros, 9 extra decls
 */
#ifndef _BUTTONVIEW_HPP_
#define _BUTTONVIEW_HPP_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* ButtonView_t::DrawText  [enum; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* ButtonControlRectangleStyle_t  [enum; ce-only] */
enum ButtonControlRectangleStyle_t {
 CBR_CLIENTRECT,
 CBR_CHECKBOX,
 CBR_CHECKTEXT,
 CBR_GROUPTEXT,
 CBR_GROUPFRAME,
 CBR_PUSHBUTTON
};

/* alignment  [extra enum] */
static void DrawText(  HWND hwnd,  HDC hdc,  BOOL dbt,  BOOL fDepress,  UINT pbfPush,  enum ButtonControlRectangleStyle_t bcrs,  WORD alignment  );

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void DrawCheckBoxandRadioStyle( HWND hwnd, HDC hdc, HBRUSH hbr, WORD alignment );
void DrawGroupBoxText( HWND hwnd, HBRUSH hbr, HDC hdc, WORD alignment );
void DrawPushStyle( HWND hwnd, HDC hdc, HBRUSH hbr, UINT pbfPush, UINT state );
void DrawPushable( HDC hdc, HBRUSH hbr, RECT* lprc, UINT state, UINT flags );
static bool HitDetect(  HWND hwnd,  POINT pt  );
static HBRUSH InitDC(  HWND hwnd,  HDC hdc  );
void PaintGroupBox( HWND hwnd, HDC hdc, HBRUSH hbr, WORD alignment );
void PaintNonPushStyle( HWND hwnd, HDC hdc, HBRUSH hbr );

#endif /* _BUTTONVIEW_HPP_ */
