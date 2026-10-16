/* wsdapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 8 constants, 20 declarations, 50 outlines, 0 base types, 0 extra macros, 63 extra decls
 */
#ifndef _WSDAPI_
#define _WSDAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ONE_WAY 0
#define TWO_WAY 1
#define WSDAPI_OPTION_MAX_INBOUND_MESSAGE_SIZE 0x0001
#define WSDET_INCOMING_FAULT 2
#define WSDET_INCOMING_MESSAGE 1
#define WSDET_NONE 0
#define WSDET_RESPONSE_TIMEOUTWSDET_RESPONSE_TIMEOUT 4
#define WSDET_TRANSMISSION_FAILURE 3

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* WSDEventType  [enum; shared; wsdapi.lib] */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* IWSDAttachment  [interface; shared; CE 6.0..699; wsdapi.lib] */
#endif /* _WIN32_WCE */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* WSD_APP_SEQUENCE  [struct; shared; wsdapi.lib] */
typedef struct _WSD_APP_SEQUENCE {
 ULONGLONG InstanceId;
 const WCHAR* SequenceId;
 ULONGLONG MessageNumber;
} WSD_APP_SEQUENCE;
typedef WSD_APP_SEQUENCE *PWSD_APP_SEQUENCE, *LPWSD_APP_SEQUENCE;

/* WSD_DATETIME  [struct; shared; wsdapi.lib] */
typedef struct _WSD_DATETIME {
 BOOL isPositive;
 ULONG year;
 UCHAR month;
 UCHAR day;
 UCHAR hour;
 UCHAR minute;
 UCHAR second;
 UINT millisecond;
 BOOL TZIsLocal;
 BOOL TZIsPositive;
 UCHAR TZHour;
 UCHAR TZMinute;
} WSD_DATETIME;
typedef WSD_DATETIME *PWSD_DATETIME, *LPWSD_DATETIME;

/* WSD_DURATION  [struct; shared; wsdapi.lib] */
typedef struct _WSD_DURATION {
 BOOL isPositive;
 ULONG year;
 ULONG month;
 ULONG day;
 ULONG hour;
 ULONG minute;
 ULONG second;
 ULONG millisecond;
} WSD_DURATION;
typedef WSD_DURATION *PWSD_DURATION, *LPWSD_DURATION;

/* WSD_EVENTING_DELIVERY_MODE  [struct; shared; wsdapi.lib] */
typedef struct _WSD_EVENTING_DELIVERY_MODE {
 const WCHAR* Mode;
 void* Data;
} WSD_EVENTING_DELIVERY_MODE;
typedef WSD_EVENTING_DELIVERY_MODE *PWSD_EVENTING_DELIVERY_MODE, *LPWSD_EVENTING_DELIVERY_MODE;

/* WSD_EVENTING_EXPIRES  [struct; shared; wsdapi.lib] */
typedef struct _WSD_EVENTING_EXPIRES {
 WSD_DURATION* Duration;
 WSD_DATETIME* DateTime;
} WSD_EVENTING_EXPIRES;
typedef WSD_EVENTING_EXPIRES *PWSD_EVENTING_EXPIRES, *LPWSD_EVENTING_EXPIRES;

/* WSD_EVENTING_FILTER  [struct; shared; wsdapi.lib] */
typedef struct _WSD_EVENTING_FILTER {
 const WCHAR* Dialect;
 void* Data;
} WSD_EVENTING_FILTER;
typedef WSD_EVENTING_FILTER *PWSD_EVENTING_FILTER, *LPWSD_EVENTING_FILTER;

/* WSD_PROTOCOL_TYPE  [enum; shared; wsdapi.lib] */
typedef enum _WSD_PROTOCOL_TYPE
{
 WSD_PT_NONE = 0x00,
 WSD_PT_UDP = 0x01,
 WSD_PT_HTTP = 0x02,
 WSD_PT_HTTPS = 0x04,
 WSD_PT_ALL = 0xff
}WSD_PROTOCOL_TYPE;
typedef WSD_PROTOCOL_TYPE *PWSD_PROTOCOL_TYPE, *LPWSD_PROTOCOL_TYPE;

/* WSD_URI_LIST  [struct; shared; wsdapi.lib] */
typedef struct _WSD_URI_LIST {
 WSD_URI_LIST* Next;
 const WCHAR* Element;
} WSD_URI_LIST;
typedef WSD_URI_LIST *PWSD_URI_LIST, *LPWSD_URI_LIST;

/* WSD_EVENTING_FILTER_ACTION  [struct; shared; wsdapi.lib] */
typedef struct _WSD_EVENTING_FILTER_ACTION {
 WSD_URI_LIST* Actions;
} WSD_EVENTING_FILTER_ACTION;
typedef WSD_EVENTING_FILTER_ACTION *PWSD_EVENTING_FILTER_ACTION, *LPWSD_EVENTING_FILTER_ACTION;

/* WSD_SCOPES  [struct; shared; wsdapi.lib] */
typedef struct _WSD_SCOPES {
 const WCHAR* MatchBy;
 WSD_URI_LIST* Scopes;
} WSD_SCOPES;
typedef WSD_SCOPES *PWSD_SCOPES, *LPWSD_SCOPES;

/* REQUESTBODY_GetStatus  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Any */

/* REQUESTBODY_Renew  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Expires */
/*   Any */

/* REQUESTBODY_Subscribe  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   EndTo */
/*   Delivery */
/*   Expires */
/*   Filter */
/*   Any */

/* REQUESTBODY_Unsubscribe  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   any */

/* RESPONSEBODY_GetStatus  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   expires */
/*   any */

/* RESPONSEBODY_Renew  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   expires */
/*   any */

/* RESPONSEBODY_Subscribe  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   SubscriptionManager */
/*   expires */
/*   any */

/* RESPONSEBODY_SubscriptionEnd  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   SubscriptionManager */
/*   Status */
/*   Reason */
/*   Any */

/* WSD_BYE  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   EndpointReference */
/*   Any */

/* WSD_ENDPOINT_REFERENCE  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Address */
/*   ReferenceProperties */
/*   ReferenceParameters */
/*   PortType */
/*   ServiceName */
/*   Any */

/* WSD_EVENT  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Hr */
/*   EventType */
/*   DispatchTag */
/*   HandlerContext */
/*   Soap */
/*   Operation */
/*   MessageParameters */

/* WSD_HANDLER_CONTEXT  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Handler */
/*   PVoid */
/*   Unknown */

/* WSD_HEADER_RELATESTO  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   RelationshipType */
/*   MessageID */

/* WSD_HELLO  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   EndpointReference */
/*   Types */
/*   Scopes */
/*   XAddrs */
/*   MetadataVersion */
/*   Any */

/* WSD_LOCALIZED_STRING  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   lang */
/*   String */

/* WSD_METADATA_SECTION  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Dialect */
/*   Identifier */
/*   Data */
/*   MetadataReference */
/*   Location */
/*   Any */

/* WSD_NAME_LIST  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Next */
/*   Element */

/* WSD_OPERATION  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   RequestType */
/*   ResponseType */
/*   RequestStubFunction */

/* WSD_PROBE  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Types */
/*   Scopes */
/*   Any */

/* WSD_PROBE_MATCH  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   EndpointReference */
/*   Types */
/*   Scopes */
/*   XAddrs */
/*   MetadataVersion */
/*   Any */

/* WSD_PROBE_MATCHES  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   ProbeMatch */
/*   Any */

/* WSD_REFERENCE_PARAMETERS  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Any */

/* WSD_REFERENCE_PROPERTIES  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Any */

/* WSD_RELATIONSHIP_METADATA  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Type */
/*   Data */
/*   Any */

/* WSD_RESOLVE  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   EndpointReference */
/*   Any */

/* WSD_RESOLVE_MATCH  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   EndpointReference */
/*   Types */
/*   Scopes */
/*   XAddrs */
/*   MetadataVersion */
/*   Any */

/* WSD_RESOLVE_MATCHES  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   ResolveMatch */
/*   Any */

/* WSD_SERVICE_METADATA  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   EndpointReference */
/*   Types */
/*   ServiceId */
/*   Any */

/* WSD_SOAP_FAULT  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Code */
/*   Reason */
/*   Node */
/*   Role */
/*   Detail */

/* WSD_SOAP_FAULT_CODE  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Value */
/*   Subcode */

/* WSD_SOAP_FAULT_SUBCODE  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Value */
/*   Subcode */

/* WSD_SOAP_HEADER  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   To */
/*   Action */
/*   MessageID */
/*   RelatesTo */
/*   ReplyTo */
/*   From */
/*   FaultTo */
/*   AppSequence */
/*   AnyHeaders */

/* WSD_SOAP_MESSAGE  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Header */
/*   Body */
/*   BodyType */

/* WSD_SYNCHRONOUS_RESPONSE_CONTEXT  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   hr */
/*   eventHandle */
/*   messageParameters */
/*   results */

/* WSD_THIS_DEVICE_METADATA  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   FriendlyName */
/*   FirmwareVersion */
/*   SerialNumber */
/*   Any */

/* WSD_THIS_MODEL_METADATA  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Manufacturer */
/*   ManufacturerUrl */
/*   ModelName */
/*   ModelNumber */
/*   ModelUrl */
/*   PresentationUrl */
/*   Any */

/* WSD_UNKNOWN_LOOKUP  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Any */

/* WSDUdpMessageType  [enum; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   TWO_WAY */

/* WSDUdpRetransmitParams  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   ulSendDelay */
/*   ulRepeat */
/*   ulRepeatMinDelay */
/*   ulRepeatMaxDelay */
/*   ulRepeatUpperDelay */

/* WSDXML_ATTRIBUTE  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Element */
/*   Next */
/*   Name */
/*   Value */

/* WSDXML_ELEMENT  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Node */
/*   Name */
/*   FirstAttribute */
/*   FirstChild */
/*   PrefixMappings */

/* WSDXML_ELEMENT_LIST  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Next */
/*   Element */

/* WSDXML_NAME  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Space */
/*   LocalName */

/* WSDXML_NAMESPACE  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Uri */
/*   PreferredPrefix */
/*   Names */
/*   NamesCount */
/*   Encoding */

/* WSDXML_NODE  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Parent */
/*   Next */

/* WSDXML_PREFIX_MAPPING  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Refs */
/*   Next */
/*   Space */
/*   Prefix */

/* WSDXML_TEXT  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Node */
/*   Text */

/* WSDXML_TYPE  [struct; shared; wsdapi.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   Uri */
/*   Table */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT Deserialize( LPCWSTR pszBuffer );
HRESULT Detach();
HRESULT GetAllMetadata( WSD_METADATA_SECTION_LIST** ppMetadata );
HRESULT* GetEndpointReference( WSD_ENDPOINT_REFERENCE** ppEndPointReference );
HRESULT GetExclusive();
HRESULT GetFaultInfo( WSD_SOAP_FAULT** ppFault );
HRESULT GetHostMetadata( WSD_HOST_METADATA** ppHostMetadata );
HRESULT GetID( LPCWSTR* ppszId );
HRESULT GetInboundHttpHeaders( LPCWSTR* ppszHeaders );
HRESULT* GetInstanceId( ULONGLONG* pullInstanceId );
HRESULT GetLocalTransportAddress( LPCWSTR* ppszLocalTransportAddress );
HRESULT GetMetadata( WSD_METADATA_SECTION_LIST** MetadataOut );
HRESULT GetMetadataVersion( ULONGLONG* pullMetadataVersion );
HRESULT GetOutboundHttpHeaders( LPCWSTR* ppszHeaders );
HRESULT GetPort( WORD* pwPort );
HRESULT GetProbeResolveTag( LPCWSTR* ppszTag );
HRESULT GetRemoteTransportAddress( LPCWSTR* ppszRemoteTransportAddress );
HRESULT GetScopeRule( LPCWSTR* ppszScopeMatchingRule );
HRESULT GetScopes( WSD_URI_LIST** ppScopesList );
HRESULT GetSecure();
HRESULT GetServiceMetadata( WSD_SERVICE_METADATA** ppServiceMetadata );
HRESULT GetTTL( DWORD* pdwTTL );
HRESULT GetThisDeviceMetadata( WSD_THIS_DEVICE_METADATA** ppThisDeviceMetadata );
HRESULT GetThisModelMetadata( WSD_THIS_MODEL_METADATA** ppManufacturerMetadata );
HRESULT GetTransportAddress( LPCWSTR* ppszAddress );
HRESULT GetTransportAddressEx( BOOL fSafe, LPCWSTR* ppszAddress );
HRESULT GetTypes( WSD_NAME_LIST** ppTypesList );
HRESULT GetXAddrs( WSD_URI_LIST** ppXAddrsList );
HRESULT HasCompleted();
HRESULT MatchScopes( LPCWSTR pszScope1, LPCWSTR pszScope2, BOOL* pfMatch );
HRESULT ProcessFault( const WSD_SOAP_FAULT* pFault );
HRESULT RegisterPortType( const WSD_PORT_TYPE* pPortType );
HRESULT RemoveDynamicService( LPCWSTR pszServiceId );
HRESULT RetireService( LPCWSTR pszServiceId );
HRESULT SearchByAddress( LPCWSTR pszAddress, LPCWSTR pszTag );
HRESULT SearchById( LPCWSTR pszId, LPCWSTR pszTag );
HRESULT SearchByType( WSD_NAME_LIST* pTypesList, WSD_URI_LIST* pScopesList, LPCWSTR pszMatchBy, LPCWSTR pszTag );
HRESULT SearchFailed( HRESULT hr, LPCWSTR pszTag );
HRESULT SendOneWayRequest( const void* pBody, const WSD_OPERATION* pOperation );
HRESULT SendTwoWayRequest( const void* pBody, const WSD_OPERATION* pOperation, WSD_SYNCHRONOUS_RESPONSE_CONTEXT* pResponseContext );
HRESULT SetAddressFamily( DWORD dwAddressFamily );
HRESULT SetExclusive( BOOL fExclusive );
HRESULT SetID( LPCWSTR pszId );
HRESULT SetInboundHttpHeaders( LPCWSTR pszHeaders );
HRESULT SetMetadata( const WSD_THIS_MODEL_METADATA* pThisModelMetadata, const WSD_THIS_DEVICE_METADATA* pThisDeviceMetadata, const WSD_HOST_METADATA* pHostMetadata, const WSD_METADATA_SECTION_LIST* pCustomMetadata );
HRESULT SetOutboundHttpHeaders( LPCWSTR pszHeaders );
HRESULT SetPort( WORD wPort );
HRESULT SetSecure( BOOL fSecure );
HRESULT SetServiceDiscoverable( const WCHAR* pszServiceId, BOOL fDiscoverable );
HRESULT SetTTL( DWORD dwTTL );
HRESULT SetTransportAddress( LPCWSTR pszAddress );
HRESULT SetWaitHandle( HANDLE hWaitHandle );
HRESULT SignalEvent( LPCWSTR pszServiceId, const void* pBody, const WSD_OPERATION* pOperation );
void SubscriptionEnded( LPCWSTR pszSubscriptionAction );
void SubscriptionRenewalFailed( LPCWSTR pszSubscriptionAction, HRESULT hr );
void SubscriptionRenewed( LPCWSTR pszSubscriptionAction );
HRESULT UnsubscribeToOperation( const WSD_OPERATION* pOperation );

#endif /* _WSDAPI_ */
