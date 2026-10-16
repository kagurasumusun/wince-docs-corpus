/* Recog.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 16 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _RECOG_
#define _RECOG_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* HWXGUIDE  [struct; ce-only] */
typedef struct tagHWXGUIDE {
 UINT cHorzBox;
 UINT cVertBox;
 INT xOrigin;
 INT yOrigin;
 UINT cxBox;
 UINT cyBox;
 UINT cxOffset;
 UINT cyOffset;
 UINT cxWriting;
 UINT cyWriting;
 UINT cyMid;
 UINT cyBase;
 UINT nDir; 
} HWXGUIDE, *PHWXGUIDE;

/* HWXRESULTS  [struct; ce-only] */
typedef struct tagHWXRESULTS {
 USHORT indxBox;
 WCHAR rgChar[1] 
} HWXRESULTS, *PHWXRESULTS;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..699 */

/* HwxConfig  [function; ce-only; CE 2.11..2.12, 3.0..699; Hwxcht.lib, hwxcht.lib, Hwxjpn.lib, hwxjpn.lib, Hwxkor.lib, Hwxusa.lib, hwxusa.lib] */
BOOL HwxConfig(void);
#endif /* _WIN32_WCE */

#endif /* _RECOG_ */
