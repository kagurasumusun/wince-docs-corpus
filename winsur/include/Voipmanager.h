/* Voipmanager.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 16 constants, 4 declarations, 2 outlines, 0 base types, 0 extra macros, 12 extra decls
 */
#ifndef _VOIPMANAGER_
#define _VOIPMANAGER_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DCRP_VALID_DOMAIN 0x00000008
#define DCRP_VALID_PASSWORD 0x00000002
#define DCRP_VALID_USERNAME 0x00000001
#define DCRP_VALID_XML 0x00000004
#define e_vceInvalid 0
#define e_vcsInvalid 0
#define e_vctInvalid 0
#define e_vseInvalid 0
#define VMS_AUTOFORWARDING 0x00000020
#define VMS_CALL_LOG_DB_READY 0x00000008
#define VMS_CALLER_INFO_DB_READY 0x00000010
#define VMS_INITIALIZED 0x00000001
#define VMS_NOT_READY 0x00000000
#define VMS_REGISTERED 0x00000002
#define VMS_REREGISTERING 0x00000040
#define VMS_SHUTTING_DOWN 0x00000004

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* DirectoryClientRegParams  [struct; ce-only] */

/* VoIPMgrParameters  [struct; ce-only; Voipguid.lib] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* SIPServerRegistrationParameters  [struct; ce-only; Voipguid.lib] */
typedef struct SIPServerRegistrationParameters { 
 const WCHAR *wszURI; 
 const WCHAR *wszServer; 
 const WCHAR *wszAccountName; 
 const WCHAR *wszAccountPassword; 
 const WCHAR *wszTransport; 
 const WCHAR *wszAuthType; 
} SIPServerRegistrationParameters;
typedef SIPServerRegistrationParameters *PSIPServerRegistrationParameters, *LPSIPServerRegistrationParameters;

/* VoIPCallEvent  [enum; ce-only] */
typedef enum VoIPCallEvent { 
 e_vceInvalid = 0, 
 e_vceStatusChanged, 
 e_vceMissed, 
 e_vceAutoBlocked, 
 e_vceAutoForwarded, 
 e_vceDropped, 
 e_vceRedirectSucceeded, 
 e_vceRedirectFailed 
} VoIPCallEvent;
typedef VoIPCallEvent *PVoIPCallEvent, *LPVoIPCallEvent;

/* VoIPCallStatus  [enum; ce-only] */
typedef enum VoIPCallStatus { 
 e_vcsInvalid = 0, 
 e_vcsIdle = RTCSS_IDLE, 
 e_vcsIncoming = RTCSS_INCOMING, 
 e_vcsAnswering = RTCSS_ANSWERING, 
 e_vcsInProgress = RTCSS_INPROGRESS, 
 e_vcsConnected = RTCSS_CONNECTED, 
 e_vcsDisconnected = RTCSS_DISCONNECTED, 
 e_vcsHolding = RTCSS_HOLD, 
 e_vcsReferring = RTCSS_REFER, 
 e_vcsInConference = RTCSS_REFER+1, 
} VoIPCallStatus;
typedef VoIPCallStatus *PVoIPCallStatus, *LPVoIPCallStatus;

/* VoIPSystemEvent  [enum; ce-only] */
typedef enum VoIPSystemEvent{ 
 e_vseInvalid = 0, 
 e_vseTerminated, 
 e_vseRegistering, 
 e_vseRegistrationSucceeded, 
 e_vseRegistrationFailed 
} VoIPSystemEvent;
typedef VoIPSystemEvent *PVoIPSystemEvent, *LPVoIPSystemEvent;

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT Hangup();
HRESULT Ignore();
HRESULT OnSystemEvent( VoIPSystemEvent vseEvent, INT_PTR iptrParam );
HRESULT RegisterWithSIPServer( SIPServerRegistrationParameters *pParams );
HRESULT Reregister( VoIPMgrParameters* pvmpMgrParams );
HRESULT Unhold();
HRESULT get_MissedCallTimeout( UINT* pnTimeoutMilliseconds );
HRESULT get_NetworkStatus( LONG* plStatus );
HRESULT get_Parameters( VoIPMgrParameters* pvmpUsed );
HRESULT put_MissedCallTimeout( UINT nTimeoutMilliseconds );

#endif /* _VOIPMANAGER_ */
