/* Dbgapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 14 declarations, 2 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _DBGAPI_
#define _DBGAPI_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* ASSERT  [function, macro; shared] */

/* DEBUGZONE  [macro, function; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DBGPARAM  [struct; ce-only] */
typedef struct _DBGPARAM {
 WCHAR lpszName[32];
 WCHAR rglpszZones[16][32];
 ULONG ulZoneMask;
} DBGPARAM, *LPDBGPARAM;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* NKDbgPrintfW  [function; ce-only; unified-kb; unified-kb] */
void WINAPIV NKDbgPrintfW(
 LPCWSTR lpszFmt,...
);

/* WriteDebugLED  [function; ce-only; unified-kb; unified-kb] */
void WriteDebugLED( 
 WORD wIndex, 
 DWORD dwPattern 
);

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* RegisterDbgZones  [function; ce-only; CE 5.0..699] */
BOOL RegisterDbgZones(
 HMODULE hMod,
 LPDBGPARAM lpdbgparam
);
#endif /* _WIN32_WCE */

#endif /* _DBGAPI_ */
