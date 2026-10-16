/* Nclientview.hpp -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 1 constants, 2 declarations, 1 outlines, 0 base types, 0 extra macros, 14 extra decls
 */
#ifndef _NCLIENTVIEW_HPP_
#define _NCLIENTVIEW_HPP_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define widInvalid -1

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* NonClientView_t::WidgetRect  [enum; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* NcHitTestCode  [typedef; ce-only] */
typedef int NcHitTestCode;

/* WidgetId  [enum; ce-only] */
enum WidgetId{
 widInvalid = -1,
 widClose,
 widMaxRestore,
 widMin,
 widOk,
 widHelp
};

/* bTopLevelWindow  [extra enum] */
static RECT WidgetRect(  HWND hwnd,  enum WidgetId wid,  bool bTopLevelWindow  );

/* widHelp  [extra enum] */
enum WidgetId{
  widInvalid = -1,
  widClose,
  widMaxRestore,
  widMin,
  widOk,
  widHelp
};

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void BoundPoint( RECT* prcBound, POINT* ppt );
static RECT BoundingRect(  HWND hwnd  );
BOOL CalcCaptionRect( HWND hwnd, RECT* lprc );
void CalcClientRectWithHorzScrollBars( RECT* lprc );
void CalcClientRectWithNoScrollBars( HWND hwnd, RECT* lprc, DWORD dwStyle, DWORD dwExStyle );
void CalcClientRectWithVertScrollBars( RECT* lprc, DWORD dwExStyle );
static bool DoesHorzScrollBarFit(  RECT* lprc  );
static bool DoesVertScrollBarFit(  RECT* lprc  );
BOOL DrawBorder( HWND hwnd, HDC hdc, LPCRECT lprc );
BOOL ExposedDrawFrameControl( HDC hdc, RECT* prc, UINT wType, UINT wState );

#endif /* _NCLIENTVIEW_HPP_ */
