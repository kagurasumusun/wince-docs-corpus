/* Mspyime.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _MSPYIME_
#define _MSPYIME_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* ClearEudpContent  [function; ce-only; CE 5.0..699; Chsime03.lib] */
void ClearEudpContent(void);

/* GetPinyinType  [function; ce-only; CE 5.0..699; Chsime03.lib] */
BOOL GetPinyinType(
 DWORD* pdwType
);

/* SetPinyinType  [function; ce-only; CE 5.0..699; Chsime03.lib] */
BOOL SetPinyinType(
 DWORD dwType
);
#endif /* _WIN32_WCE */

#endif /* _MSPYIME_ */
