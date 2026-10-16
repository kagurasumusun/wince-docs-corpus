/* Ipsec_api.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 7 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _IPSEC_API_
#define _IPSEC_API_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* IPSEC_API_MODE_INFO  [struct, typedef; ce-only] */
typedef struct {
 DWORD inAction;
 DWORD outAction;
 DWORD auth;
 PBYTE authInfo;
 DWORD authInfoSize;
 DWORD mmHashMask;
 DWORD mmEncMask;
 DWORD qmHashMask;
 DWORD qmEncMask;
 DWORD dhMask;
 DWORD protocol;
 DWORD scrIP;
} IPSEC_API_MODE_INFO, *PIPSEC_API_MODE_INFO;

/* IPSEC_API_PARAM  [struct, typedef; ce-only] */
typedef struct {
 DWORD id;
 PVOID val;
 DWORD valSize;
} IPSEC_API_PARAM, *PIPSEC_API_PARAM;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* IsIPSecRunning  [function; ce-only; CE 5.0..699; Ipsec_api.lib] */
HRESULT IsIPSecRunning(void);

/* SetIPSecConfig  [function; ce-only; CE 5.0..699; Ipsec_api.lib] */
HRESULT SetIPSecConfig(
 IPSEC_API_PARAM param,
 DWORD flags
);

/* SetIPSecMode  [function; ce-only; CE 5.0..699; Ipsec_api.lib] */
HRESULT SetIPSecMode(
 IPSEC_API_MODE_INFO modeInfo,
 DWORD flags
);

/* StartIPSec  [function; ce-only; CE 5.0..699; Ipsec_api.lib] */
HRESULT StartIPSec(void);

/* StopIPSec  [function; ce-only; CE 5.0..699; Ipsec_api.lib] */
HRESULT StopIPSec(void);
#endif /* _WIN32_WCE */

#endif /* _IPSEC_API_ */
