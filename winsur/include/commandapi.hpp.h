/* commandapi.hpp -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 1 constants, 4 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _COMMANDAPI_HPP_
#define _COMMANDAPI_HPP_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define phaPhoneApp 0

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* PH_APPLICATION  [enum; ce-only; PhCommon.dll] */
typedef enum _PH_APPLICATION
{
 phaPhoneApp = 0,
 phaHomeScreenApp,
 phaSettingsApp,
 phaContactsApp,
 phaLast, 
} PH_APPLICATION;
typedef PH_APPLICATION *PPH_APPLICATION, *LPPH_APPLICATION;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* PHGetAppWindow  [function; ce-only; CE 6.0..699; PhCommon.dll] */
HWND PHGetAppWindow(
 PH_APPLICATION Id,
 BOOL SleepRetry
);

/* PHSendCommandLine  [function; ce-only; CE 6.0..699; PhCommon.dll] */
HRESULT PHSendCommandLine(
 PH_APPLICATION Id,
 WCHAR* pArguments
);
#endif /* _WIN32_WCE */

#endif /* _COMMANDAPI_HPP_ */
