/* Htmlctrl.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 8 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _HTMLCTRL_
#define _HTMLCTRL_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* INLINEIMAGEINFO  [struct, typedef; ce-only] */
typedef struct tagINLINEIMAGEINFO { 
DWORD dwCookie; 
int iOrigHeight; 
int iOrigWidth; 
HBITMAP hbm; 
BOOL bOwnBitmap; 
} INLINEIMAGEINFO, *LPINLINEIMAGEINFO;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* InitHTMLControl  [function; ce-only; unified-kb; unified-kb] */
BOOL InitHTMLControl( 
HINSTANCE hinst );

#endif /* _HTMLCTRL_ */
