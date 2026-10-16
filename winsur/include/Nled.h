/* Nled.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 4 declarations, 0 outlines, 0 base types, 0 extra macros, 4 extra decls
 */
#ifndef _NLED_
#define _NLED_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* NLED_COUNT_INFO  [struct; ce-only] */
struct NLED_COUNT_INFO {
 UINT cLeds; 
};

/* NLED_SETTINGS_INFO  [struct; ce-only] */
struct NLED_SETTINGS_INFO {
 UINT LedNum;
 INT OffOnBlink;
 LONG TotalCycleTime;
 LONG OnTime;
 LONG OffTime;
 INT MetaCycleOn;
 INT MetaCycleOff; 
};

/* NLED_SUPPORTS_INFO  [struct; ce-only] */
struct NLED_SUPPORTS_INFO {
 UINT LedNum;
 LONG lCycleAdjust;
 BOOL fAdjustTotalCycleTime;
 BOOL fAdjustOnTime;
 BOOL fAdjustOffTime;
 BOOL fMetaCycleOn;
 BOOL fMetaCycleOff; 
};

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400)) /* CE 2.11..2.12, 3.0..399 */

/* NLedDriverDllEntry  [function; ce-only; CE 2.11..2.12, 3.0..399; heuristic-prefix] */
BOOL NLedDriverDllEntry( 
HANDLE hinstDll, 
DWORD fdwReason, 
LPVOID lpvReserved );
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
VOID WINAPI NLedDriverDeInitialize(VOID);

#endif /* _NLED_ */
