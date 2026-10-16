/* Dmusicf.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _DMUSICF_
#define _DMUSICF_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DMUS_MUTE_PARAM  [struct; ce-only] */
typedef struct _DMUS_MUTE_PARAM {
 DWORD dwPChannel;
 DWORD dwPChannelMap;
 BOOL fMute;
 } DMUS_MUTE_PARAM;
typedef DMUS_MUTE_PARAM *PDMUS_MUTE_PARAM, *LPDMUS_MUTE_PARAM;

#endif /* _DMUSICF_ */
