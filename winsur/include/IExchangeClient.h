/* IExchangeClient.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 8 constants, 5 declarations, 6 outlines, 0 base types, 0 extra macros, 24 extra decls
 */
#ifndef _IEXCHANGECLIENT_
#define _IEXCHANGECLIENT_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define e_ecrsPending 0
#define e_ecrtInvalid 0
#define OWAEC_E_ALREADYINITIALIZED 0x80bb0006
#define OWAEC_E_INVALIDSEARCH 0x80bb0004
#define OWAEC_E_NODATA 0x80bb0005
#define OWAEC_E_NOSERVER 0x80bb0002
#define OWAEC_E_NOTINITIALIZED 0x80bb0001
#define OWAEC_E_NOUSER 0x80bb0003

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* IExchangeClient::RequestContacts  [struct; ce-only; OWAExchangeClient.lib] */

/* IExchangeClient::RequestFreeBusyData  [struct; ce-only; OWAExchangeClient.lib] */

/* IExchangeClient::RequestGALSearch  [struct; ce-only; OWAExchangeClient.lib] */

/* IExchangeClientRequest::GetStatus  [enum; ce-only; OWAExchangeClient.lib] */

/* IExchangeClientRequest::GetType  [enum; ce-only; OWAExchangeClient.lib] */

/* IExchangeClientRequestCallback::OnRequestProgress  [enum; ce-only; OWAExchangeClient.lib] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* ContactsSearchCriteria  [struct; ce-only] */
struct ContactsSearchCriteria {
 WCHAR* wszFirstName;
 WCHAR* wszLastName;
};

/* ExchangeClientRequestStatus  [enum; ce-only] */
enum ExchangeClientRequestStatus
{
 e_ecrsPending = 0,
 e_ecrsInProgress,
 e_ecrsSending,
 e_ecrsBypassingOWAPage,
 e_ecrsSucceeded,
 e_ecrsOutOfMemory,
 e_ecrsParseFailed,
 e_ecrsHttpFailure,
 e_ecrsFailedToSend,
 e_ecrsFailedToBypassAuthPage,
 e_ecrsCancelled,
 e_ecrsNoCredentials
};

/* ExchangeClientRequestType  [enum; ce-only] */
enum ExchangeClientRequestType
{
 e_ecrtInvalid = 0,
 e_ecrtContacts,
 e_ecrtGALSearch,
 e_ecrtFreeBusy
};

/* FreeBusyCriteria  [struct; ce-only] */
struct FreeBusyCriteria {
 WCHAR* wszAlias;
 SYSTEMTIME* pstStart;
};

/* GALSearchCriteria  [struct; ce-only] */
struct GALSearchCriteria {
 WCHAR* wszAlias;
 WCHAR* wszFirstName;
 WCHAR* wszLastName;
};

/* wszLastName  [extra struct] */
struct ContactsSearchCriteria {  WCHAR* wszFirstName;  WCHAR* wszLastName;  };

/* e_ecrsNoCredentials  [extra enum] */
enum ExchangeClientRequestStatus
{
  e_ecrsPending = 0,
  e_ecrsInProgress,
  e_ecrsSending,
  e_ecrsBypassingOWAPage,
  e_ecrsSucceeded,
  e_ecrsOutOfMemory,
  e_ecrsParseFailed,
  e_ecrsHttpFailure,
  e_ecrsFailedToSend,
  e_ecrsFailedToBypassAuthPage,
  e_ecrsCancelled,
  e_ecrsNoCredentials,
};

/* e_ecrtFreeBusy  [extra enum] */
enum ExchangeClientRequestType
{
  e_ecrtInvalid = 0,
  e_ecrtContacts,
  e_ecrtGALSearch,
  e_ecrtFreeBusy,
};

/* pstStart  [extra struct] */
struct FreeBusyCriteria {  WCHAR* wszAlias;  SYSTEMTIME* pstStart;  };

/* pStatus  [extra enum] */
HRESULT GetStatus(  enum ExchangeClientRequestStatus* pStatus  );

/* pecrt  [extra enum] */
HRESULT GetType(  enum ExchangeClientRequestType* pecrt  );

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT CancelPendingRequests();
HRESULT GetAlias( WCHAR* wszBuffer, UINT cchBuffer );
HRESULT GetEmailAddress( WCHAR* wszBuffer, UINT cchBuffer );
HRESULT GetFreeBusyData( WCHAR* wszDataBuffer, UINT cchDataBuffer );
HRESULT GetHomeAddress( WCHAR* wszBuffer, UINT cchBuffer );
HRESULT GetHomePhoneNumber( WCHAR* wszNumberBuffer, UINT cchNumberBuffer );
HRESULT GetHttpStatus( LONG* plHttpStatus );
HRESULT GetMobilePhoneNumber( WCHAR* wszBuffer, UINT cchBuffer );
HRESULT GetOffice( WCHAR* wszBuffer, UINT cchBuffer );
HRESULT GetPhoneNumber( WCHAR* wszNumberBuffer, UINT cchNumberBuffer );
HRESULT GetSMTPAddress( WCHAR* wszBuffer, UINT cchBuffer );
HRESULT GetServer( WCHAR* wszBuffer, UINT cchBuffer );
HRESULT GetWorkAddress( WCHAR* wszBuffer, UINT cchBuffer );
HRESULT GetWorkPhoneNumber( WCHAR* wszBuffer, UINT cchBuffer );
HRESULT OnShutdown();
HRESULT SetCredentials( const WCHAR* c_wszUsername, const WCHAR* c_wszPassword );
HRESULT SetServer( const WCHAR* c_wszServername );
HRESULT Uninitialize();

#endif /* _IEXCHANGECLIENT_ */
