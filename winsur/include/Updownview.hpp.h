/* Updownview.hpp -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 3 extra decls
 */
#ifndef _UPDOWNVIEW_HPP_
#define _UPDOWNVIEW_HPP_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void HorzDrawSettings( DWORD dwStyle, int iVersion, LPRECT prcBtn, BOOL bEnabled, BOOL fHasBorder, unsigned fUp, unsigned fDown, int nPos, int nUpper, int nLower, UINT uHot, UINT* puLeftFlags, LPRECT prcLeft, UINT* puRightFlags, LPRECT prcRight );
void SetSunkenBorder( DWORD dwStyle, UINT* puBorderType );
void VertDrawSettings( DWORD dwStyle, int iVersion, LPRECT prcBtn, BOOL bEnabled, BOOL fHasBorder, unsigned fUp, unsigned fDown, int nPos, int nUpper, int nLower, UINT uHot, UINT* puUpFlags, LPRECT prcUp, UINT* puDownFlags, LPRECT prcDown );

#endif /* _UPDOWNVIEW_HPP_ */
