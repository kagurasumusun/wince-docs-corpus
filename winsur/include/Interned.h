/* Interned.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 3 declarations, 25 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _INTERNED_
#define _INTERNED_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* alert  [typedef; ce-only; heuristic-prefix] */

/* blur  [typedef; ce-only; heuristic-prefix] */

/* clearTimeout  [typedef; ce-only; heuristic-prefix] */

/* Close  [function, typedef; ce-only; heuristic-prefix] */

/* confirm  [typedef; ce-only; heuristic-prefix] */

/* document  [typedef; ce-only; heuristic-prefix] */

/* external  [typedef; ce-only; heuristic-prefix] */

/* focus  [typedef; ce-only; heuristic-prefix] */

/* history  [typedef; ce-only; heuristic-prefix] */

/* length  [typedef; ce-only; heuristic-prefix] */

/* location  [typedef; ce-only; heuristic-prefix] */

/* Method  [typedef; ce-only; heuristic-prefix] */

/* Name  [function, typedef; ce-only; heuristic-prefix] */

/* navigate  [typedef; ce-only; heuristic-prefix] */

/* navigator  [typedef; ce-only; heuristic-prefix] */

/* onload  [typedef; ce-only; heuristic-prefix] */

/* onunload  [typedef; ce-only; heuristic-prefix] */

/* Parent  [typedef; ce-only; heuristic-prefix] */

/* PROMPT  [typedef; ce-only; heuristic-prefix] */

/* screen  [typedef; ce-only; heuristic-prefix] */

/* scrollTo  [typedef; ce-only; heuristic-prefix] */

/* self  [typedef; ce-only; heuristic-prefix] */

/* setTimeout  [typedef; ce-only; heuristic-prefix] */

/* Top  [typedef; ce-only; heuristic-prefix] */

/* window  [typedef; ce-only; heuristic-prefix] */

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* EVENT  [function, typedef; ce-only] */
HRESULT Event(
 int index, 
 DWORD *pdispidEvt
);

/* Scroll  [function, typedef; ce-only; heuristic-prefix] */
Private Sub grid_Scroll( );

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* Count  [function; ce-only; CE 5.0..699] */
HRESULT Count(long *pCount);
#endif /* _WIN32_WCE */

#endif /* _INTERNED_ */
