/* displayitem.hpp -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 5 extra decls
 */
#ifndef _DISPLAYITEM_HPP_
#define _DISPLAYITEM_HPP_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
BOOL GetHeight( UINT* pHeight );
HRESULT GetSubItemText( int Index, WCHAR* pBuffer, UINT cchBuffer );
BOOL IsSelectable( void );
BOOL NeedsToolTip( RECT* pRectangle );
HRESULT SetText( WCHAR* pText );

#endif /* _DISPLAYITEM_HPP_ */
