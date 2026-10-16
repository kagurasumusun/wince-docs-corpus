/* pnrpdef.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _PNRPDEF_
#define _PNRPDEF_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* PNRP_CLOUD_FLAGS  [enum; shared; p2p.lib] */
typedef enum 
{ 
 PNRP_CLOUD_NO_FLAGS, 
 PNRP_CLOUD_NAME_LOCAL 
} PNRP_CLOUD_FLAGS;
typedef PNRP_CLOUD_FLAGS *PPNRP_CLOUD_FLAGS, *LPPNRP_CLOUD_FLAGS;

/* PNRP_CLOUD_STATE  [enum; shared; p2p.lib] */
typedef enum 
{ 
 PNRP_CLOUD_STATE_VIRTUAL, 
 PNRP_CLOUD_STATE_SYNCHRONISING, 
 PNRP_CLOUD_STATE_ACTIVE, 
 PNRP_CLOUD_STATE_DEAD, 
 PNRP_CLOUD_STATE_DISABLED, 
 PNRP_CLOUD_STATE_NO_NET, 
 PNRP_CLOUD_STATE_ALONE 
} PNRP_CLOUD_STATE;
typedef PNRP_CLOUD_STATE *PPNRP_CLOUD_STATE, *LPPNRP_CLOUD_STATE;

/* PNRP_RESOLVE_CRITERIA  [enum; shared; p2p.lib] */
typedef enum 
{ 
 PNRP_RESOLVE_CRITERIA_DEFAULT, 
 PNRP_RESOLVE_CRITERIA_ANY_PEER_NAME, 
 PNRP_RESOLVE_CRITERIA_NEAREST_NON_CURRENT_PROCESS_PEER_NAME, 
 PNRP_RESOLVE_CRITERIA_NEAREST_PEER_NAME, 
 PNRP_RESOLVE_CRITERIA_NEAREST_REMOTE_PEER_NAME, 
 PNRP_RESOLVE_CRITERIA_NON_CURRENT_PROCESS_PEER_NAME, 
 PNRP_RESOLVE_CRITERIA_REMOTE_PEER_NAME 
} PNRP_RESOLVE_CRITERIA;
typedef PNRP_RESOLVE_CRITERIA *PPNRP_RESOLVE_CRITERIA, *LPPNRP_RESOLVE_CRITERIA;

#endif /* _PNRPDEF_ */
