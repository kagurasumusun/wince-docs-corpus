/* todaycmn.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 13 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _TODAYCMN_
#define _TODAYCMN_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define IDD_TODAY_CUSTOM 500
#define TODAYCOLOR_HIGHLIGHT 0x10000022
#define TODAYCOLOR_HIGHLIGHTEDTEXT 0x10000023
#define TODAYCOLOR_TEXT 0x10000004
#define TODAYM_DRAWWATERMARK (WM_USER+101)
#define TODAYM_GETCOLOR (WM_USER+100)
#define TODAYM_TOOKSELECTION (WM_USER+102)
#define WM_TODAYCUSTOM_ACTION (WM_USER+247)
#define WM_TODAYCUSTOM_CLEARCACHE (WM_USER+242)
#define WM_TODAYCUSTOM_LOSTSELECTION (WM_USER+245)
#define WM_TODAYCUSTOM_QUERYREFRESHCACHE (WM_USER+243)
#define WM_TODAYCUSTOM_RECEIVEDSELECTION (WM_USER+244)
#define WM_TODAYCUSTOM_USERNAVIGATION (WM_USER+246)

#endif /* _TODAYCMN_ */
