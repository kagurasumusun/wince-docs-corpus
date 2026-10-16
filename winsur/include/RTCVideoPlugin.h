/* RTCVideoPlugin.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _RTCVIDEOPLUGIN_
#define _RTCVIDEOPLUGIN_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* RTCRTPHeader  [struct; ce-only] */
struct _RTCRTPHeader {
 double dReceptionTime;
 DWORD dwSequenceNumber;
 DWORD64 qwTimestamp;
 DWORD dwPayloadType;
 DWORD dwSSRC;
 BOOL fMarkerBitSet;
 BOOL fIsRedundancy;
} RTCRTPHeader;

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT CheckAcceptableFmtp( const CHAR *szFmtp );

#endif /* _RTCVIDEOPLUGIN_ */
