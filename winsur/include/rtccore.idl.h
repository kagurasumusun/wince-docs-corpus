/* rtccore.idl -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 8 extra decls
 */
#ifndef _RTCCORE_IDL_
#define _RTCCORE_IDL_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* RTC_SUBSCRIPTION_STATE  [enum; ce-only] */
typedef enum RTC_SUBSCRIPTION_STATE
{
 RTCSUBC_NOT_SUBSCRIBED, 
 RTCSUBC_SUBSCRIBING,
 RTCSUBC_SUBSCRIBED, 
 RTCSUBC_LOGGED_OFF,
 RTCSUBC_ERROR,
 RTCSUBC_UNSUBSCRIBING, 
} RTC_SUBSCRIPTION_STATE;
typedef RTC_SUBSCRIPTION_STATE *PRTC_SUBSCRIPTION_STATE, *LPRTC_SUBSCRIPTION_STATE;

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT StatusCode( LONG* pStatusCode );
HRESULT SubscriptionState( RTC_SUBSCRIPTION_STATE* pSubscriptionState );
HRESULT get_SIPPrivacyType( LONG* pPrivacyFlags );
HRESULT get_SubscriptionState ( RTC_SUBSCRIPTION_STATE *pSubscriptionState );
HRESULT put_SIPPrivacyType( LONG PrivacyType );

#endif /* _RTCCORE_IDL_ */
