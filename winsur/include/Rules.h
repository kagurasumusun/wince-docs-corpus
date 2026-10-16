/* Rules.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _RULES_
#define _RULES_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* FW_RULE_MASKS  [enum; ce-only] */
typedef enum _FW_RULE_MASKS {
 FWM_PRIVATE_HOST = 0x01,
 FWM_PUBLIC_HOST = 0x02,
 FWM_PORT = 0x04,
 FWM_TYPE = 0x08,
 FWM_CODE = 0x10,
 FWM_PROTOCOL = 0x20
 FWM_ACTION = 0x40,
 FWM_TIME_OF_DAY = 0x80,
 FWM_DAY_OF_WEEK = 0x100,
 FWM_DAY = 0x200,
 FWM_MONTH = 0x400,
 FWM_PUBLIC_HOST_MASK= 0x800,
 FWM_PUBLIC_HOST_PREFIX = 0x1000
} FW_RULE_MASKS;
typedef FW_RULE_MASKS *PFW_RULE_MASKS, *LPFW_RULE_MASKS;

#endif /* _RULES_ */
