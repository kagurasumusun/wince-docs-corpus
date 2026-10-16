/* Toolbarview.hpp -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 1 outlines, 0 base types, 0 extra macros, 6 extra decls
 */
#ifndef _TOOLBARVIEW_HPP_
#define _TOOLBARVIEW_HPP_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* ToolBarView_t::LoadSystemBitmap  [enum; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* BitmapType  [enum; ce-only] */
enum BitmapType {
 btStdSmallColor,
 btStdSmallMono,
 btViewSmallColor,
 btViewSmallMono,
 btClose,
 btOk
};

/* btOk  [extra enum] */
enum BitmapType {
  btStdSmallColor,
  btStdSmallMono,
  btViewSmallColor,
  btViewSmallMono,
  btClose,
  btOk
};

/* bt  [extra enum] */
static HBITMAP LoadSystemBitmap(  enum BitmapType bt  );

/* BitmapTypebt  [extra enum] */
static HBITMAP LoadSystemBitmap(enum BitmapTypebt);

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void DrawDropdownArrow( HDC hdc, int x, int y, int dx, int dy, int cxEdge, int cyEdge, int cyBorder, COLORREF clrBtnFace, int cxDropdownArrow, int yOffset );
void FaceRect( RECT* prcButton, int cxEdge, int cyEdge );
void InitializeButtonSlopValue( int* pxSlop, int* pySlop );

#endif /* _TOOLBARVIEW_HPP_ */
