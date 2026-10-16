/* Fwapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 18 declarations, 1 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _FWAPI_
#define _FWAPI_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* FW_LOG_ENTRY  [struct; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* FW_ACTIONS  [enum; ce-only] */
typedef enum _FW_ACTIONS {
 FWA_BLOCK = 0x01,
 FWA_ALLOW = 0x02,
 FWA_ALLOW_RESPONSE = 0x03,
} FW_ACTIONS;
typedef FW_ACTIONS *PFW_ACTIONS, *LPFW_ACTIONS;

/* FW_DAYS  [enum; ce-only] */
typedef enum _FW_DAYS {
 FWD_SUNDAY = 0x01,
 FWD_MONDAY = 0x02,
 FWD_TUESDAY = 0x04,
 FWD_WEDNESDAY = 0x08,
 FWD_THURSDAY = 0x10,
 FWD_FRIDAY = 0x20,
 FWD_SATURDAY = 0x40,
 FWD_WEEKDAY = 0x3E,
 FWD_WEEKEND = 0x41,
} FW_DAYS;
typedef FW_DAYS *PFW_DAYS, *LPFW_DAYS;

/* FW_DIRECTIONS  [enum; ce-only] */
typedef enum _FW_DIRECTIONS {
 FWD_INBOUND = 0x08,
 FWD_OUTBOUND = 0x10,
} FW_DIRECTIONS;
typedef FW_DIRECTIONS *PFW_DIRECTIONS, *LPFW_DIRECTIONS;

/* FW_RULE_FLAGS  [enum; ce-only] */
typedef enum _FW_RULE_FLAGS {
 FWF_BLOCK = FWA_BLOCK,
 FWF_ALLOW = FWA_ALLOW,
 FWF_LOG = 0x04,
 FWF_INBOUND = FWD_INBOUND,
 FWF_OUTBOUND = FWD_OUTBOUND,
 FWF_DISABLED = 0x20
} FW_RULE_FLAGS;
typedef FW_RULE_FLAGS *PFW_RULE_FLAGS, *LPFW_RULE_FLAGS;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* FirewallEnable  [function; ce-only; CE 4.0..699; Fwapi.lib, fwapi.lib] */
DWORD FirewallEnable(
 USHORT Family,
 BOOL bEnable, 
 BOOL bPersist
);

/* FirewallLogInit  [function; ce-only; CE 4.0..699] */
void FirewallLogInit();

/* FirewallLogUninit  [function; ce-only; CE 4.0..699] */
void FirewallLogUninit();

/* FirewallRefresh  [function; ce-only; CE 4.0..699] */
VOID FirewallRefresh();

/* FirewallSetInterface  [function; ce-only; CE 4.0..699] */
DWORD FirewallSetInterface(
 LPCWSTR pszInterfaceName, 
 BOOL bFirewalled, 
 BOOL bPersist
);

/* IsFirewallEnabled  [function; ce-only; CE 4.0..699] */
BOOL IsFirewallEnabled(
 USHORT Family
);

/* IsInterfaceFirewalled  [function; ce-only; CE 4.0..699] */
BOOL IsInterfaceFirewalled(
 LPCWSTR pszInterfaceName
);
#endif /* _WIN32_WCE */

#endif /* _FWAPI_ */
