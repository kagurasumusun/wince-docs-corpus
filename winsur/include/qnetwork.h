/* qnetwork.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 6 extra decls
 */
#ifndef _QNETWORK_
#define _QNETWORK_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* AMExtendedSeekingCapabilities  [enum; shared; entity-headers] */
typedef enum AMExtendedSeekingCapabilities{
 AM_EXSEEK_CANSEEK = 1,
 AM_EXSEEK_CANSCAN = 2,
 AM_EXSEEK_MARKERSEEK = 4,
 AM_EXSEEK_SCANWITHOUTCLOCK = 8,
 AM_EXSEEK_NOSTANDARDREPAINT = 16,
 AM_EXSEEK_BUFFERING = 32,
 AM_EXSEEK_SENDS_VIDEOFRAMEREADY = 64
};

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT GetMarkerTime( long MarkerNum, double* pMarkerTime );
HRESULT get_CurrentMarker( long* pCurrentMarker );
HRESULT get_ExSeekCapabilities( long* pExCapabilities );
HRESULT get_MarkerCount( long* pMarkerCount );
HRESULT get_PlaybackSpeed( double* pSpeed );
HRESULT put_PlaybackSpeed( double Speed );

#endif /* _QNETWORK_ */
