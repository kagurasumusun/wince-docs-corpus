/* Voipstore.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 2 declarations, 0 outlines, 0 base types, 0 extra macros, 9 extra decls
 */
#ifndef _VOIPSTORE_
#define _VOIPSTORE_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* VoIPCallType  [enum; ce-only] */
typedef enum VoIPCallType {
..e_vctInvalid = 0,
..e_vctIncoming,
..e_vctOutgoing,
..e_vctMissed
} VoIPCallType;
typedef VoIPCallType *PVoIPCallType, *LPVoIPCallType;

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* VOIP_INVALID_SPEED_DIAL_ENTRY  [?; ce-only; CE 6.0..699] */
enum {
..VOIP_INVALID_SPEED_DIAL_ENTRY = -1
};
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT DeleteFromDB();
HRESULT get_CallType( VoIPCallType* pvctType );
HRESULT get_Capacity( int* cRecords );
HRESULT get_SpeedDialEntry( int* pidxSpeedDial );
HRESULT put_CallType( VoIPCallType vctType );
HRESULT put_Capacity( int cRecords );
HRESULT put_SpeedDialEntry( int idxSpeedDial );

#endif /* _VOIPSTORE_ */
