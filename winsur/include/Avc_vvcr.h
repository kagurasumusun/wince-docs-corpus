/* Avc_vvcr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 9 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _AVC_VVCR_
#define _AVC_VVCR_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* VVCR_Complete_Request  [struct; ce-only] */
typedef struct {PVOID vvcr_RequestIdentifier;BOOL vvcr_Status;} VVCR_Complete_Request;
typedef VVCR_Complete_Request *PVVCR_Complete_Request, *LPVVCR_Complete_Request;

/* VVCR_Event_Request  [struct; ce-only] */
typedef struct {ULONG vve_Flags;} VVCR_Event_Request;
typedef VVCR_Event_Request *PVVCR_Event_Request, *LPVVCR_Event_Request;

/* VVCR_Event_Response  [struct; ce-only] */
typedef struct {VVCR_EVENT_Type vve_Event;union { struct { ULONG psc_PlugNumber; ULONG psc_Direction; BOOL psc_PlugState; STREAM_MediaType psc_MediaType; HANDLE psc_Plug; } PlugStateChange; struct { PVOID pr_RequestIdentifier; ULONG pr_PlayMode; } PlayRequest; struct { PVOID rr_RequestIdentifier; ULONG rr_RecordMode; } RecordRequest; struct { PVOID wr_RequestIdentifier; ULONG wr_WindMode; } WindRequest; struct { PVOID rtc_RequestIdentifier; BYTE rtc_Hour; BYTE rtc_Minute; BYTE rtc_Second; BYTE rtc_Frame; BOOL rtc_Negative; } RelativeTimeCounter; struct { PVOID tc_RequestIdentifier; BYTE tc_Hour; BYTE tc_Minute; BYTE tc_Second; BYTE tc_Frame; } TimeCode; struct { PVOID atn_RequestIdentifier; ULONG atn_TrackNumber; } AbsoluteTrackNumber; } vve_Union;} VVCR_Event_Response;
typedef VVCR_Event_Response *PVVCR_Event_Response, *LPVVCR_Event_Response;

/* VVCR_EVENT_Type  [enum; ce-only] */
typedef enum { VVCR_EVENT_PlugStateChange, VVCR_EVENT_ConnectToRemotePlug, VVCR_EVENT_PlayRequest, VVCR_EVENT_RecordRequest, VVCR_EVENT_WindRequest, VVCR_EVENT_RelativeTimeCounter, VVCR_EVENT_TimeCode, VVCR_EVENT_AbsoluteTrackNumber} VVCR_EVENT_Type;
typedef VVCR_EVENT_Type *PVVCR_EVENT_Type, *LPVVCR_EVENT_Type;

/* VVCR_MECHANISM_STATE  [enum; ce-only] */
typedef enum { VVCR_MECHANISM_STATE_Stopped, VVCR_MECHANISM_STATE_Playing, VVCR_MECHANISM_STATE_Recording, VVCR_MECHANISM_STATE_Rewinding, VVCR_MECHANISM_STATE_FastForwarding, VVCR_MECHANISM_STATE_HighSpeedRewinding} VVCR_MECHANISM_STATE;
typedef VVCR_MECHANISM_STATE *PVVCR_MECHANISM_STATE, *LPVVCR_MECHANISM_STATE;

/* VVCR_SetMechanismPosition_Request  [struct; ce-only] */
typedef struct {BYTE vvsmp_Hour;BYTE vvsmp_Minute;BYTE vvsmp_Second;BYTE vvsmp_Frame;BOOL vvsmp_Negative;} VVCR_SetMechanismPosition_Request;
typedef VVCR_SetMechanismPosition_Request *PVVCR_SetMechanismPosition_Request, *LPVVCR_SetMechanismPosition_Request;

/* VVCR_SetMechanismState_Request  [struct; ce-only] */
typedef struct {VVCR_MECHANISM_STATE vsms_State;} VVCR_SetMechanismState_Request;
typedef VVCR_SetMechanismState_Request *PVVCR_SetMechanismState_Request, *LPVVCR_SetMechanismState_Request;

/* VVCR_SetMechanismTrackNumber_Request  [struct; ce-only] */
typedef struct {ULONG vvsmtn_TrackNumber;} VVCR_SetMechanismTrackNumber_Request;
typedef VVCR_SetMechanismTrackNumber_Request *PVVCR_SetMechanismTrackNumber_Request, *LPVVCR_SetMechanismTrackNumber_Request;

#endif /* _AVC_VVCR_ */
