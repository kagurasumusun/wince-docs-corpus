/* search.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SEARCH_
#define _SEARCH_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 5.0..599 */

/* qsort  [function; ce-only; CE 5.0..599; coredll.dll] */
void qsort( void*base,size_tnum,size_twidth,int( __cdecl*compare)( constvoid*elem1,constvoid*elem2) );
#endif /* _WIN32_WCE */

#endif /* _SEARCH_ */
