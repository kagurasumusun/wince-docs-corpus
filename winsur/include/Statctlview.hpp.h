/* Statctlview.hpp -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 3 outlines, 0 base types, 0 extra macros, 5 extra decls
 */
#ifndef _STATCTLVIEW_HPP_
#define _STATCTLVIEW_HPP_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* StaticControlView_t::DrawStaticImage  [enum; ce-only] */

/* StaticControlView_t::DrawStaticText  [enum; ce-only] */

/* StaticControlView_t::ResizeRectToImage  [enum; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* StaticControlType  [enum; ce-only] */
enum StaticControlType {
 sctLeft = SS_LEFT,
 sctCenter = SS_CENTER,
 sctRight = SS_RIGHT,
 sctIcon = SS_ICON,
 sctLeftNoWordWrap = SS_LEFTNOWORDWRAP,
 sctBitmap = SS_BITMAP,
 sctIconCenter = SS_ICON,
 sctBitmapCenter = SS_BITMAP 
};

/* hImage  [extra enum] */
static void DrawStaticImage(  HWND hwnd,  enum StaticControlType sct,  HDC hdc,  HBRUSH hbrBk,  HANDLE hImage  );

/* hbrBk  [extra enum] */
static void DrawStaticText(  HWND hwnd,  unsigned int Style,  enum StaticControlType sct,  HDC hdc,  HBRUSH hbrBk  );

/* prc  [extra enum] */
static bool ResizeRectToImage(  HWND hwnd,  unsigned int Style,  enum StaticControlType sct,  HANDLE hImage,  RECT* prc  );

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void DrawStaticImage( HWND hwnd, enum StaticControlType sct, HDC hdc, HBRUSH hbrBk, HANDLE hImage );
void DrawStaticText( HWND hwnd, unsigned int Style, enum StaticControlType sct, HDC hdc, HBRUSH hbrBk );

#endif /* _STATCTLVIEW_HPP_ */
