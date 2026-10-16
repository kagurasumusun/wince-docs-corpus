/* Mqoai.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 62 extra decls
 */
#ifndef _MQOAI_
#define _MQOAI_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void ArrivedError( Idispatch* Queue, long ErrorCode, long Cursor );
HRESULT get_ MaxTimeToReachQueue(  long* plMaxTimeToReachQueue  );  HRESULT put_MaxTimeToReachQueue(  long lMaxTimeToReachQueue  );
HRESULT Refresh(void);
HRESULT get_Access( long* plAccess );
HRESULT get_Ack( long* plAck );
HRESULT get_AdminQueueInfo( MSMQQueueInfo** ppinfoAdmin );
HRESULT get_AppSpecific( long* plAppSpecific );
HRESULT get_AuthLevel( long* plAuthLevel );
HRESULT get_Authenticate( long* plAuthenticate );
HRESULT get_BasePriority( long* plBasePriority );
HRESULT get_Class( long* plClass );
HRESULT get_Delivery( long* plDelivery );
HRESULT get_DestinationQueueInfo( MSMQQueueInfo** ppqinfoDest );
HRESULT get_EncryptAlgorithm( long* plEncryptAlg );
HRESULT get_Handle( long* plHandle );
HRESULT get_HashAlgorithm( long* plHashAlg );
HRESULT get_IsAuthenticated( Boolean* pIsAuthenticated );
HRESULT get_IsOpen( Boolean* pisOpen );
HRESULT get_IsTransactional( Boolean* pisTransactional );
HRESULT get_IsWorldReadable( Boolean* pisWorldReadable );
HRESULT get_Journal( long* plJournal );
HRESULT get_JournalQuota( long* plJournalQuota );
HRESULT get_MaxTimeToReceive( long* plMaxTimeToReceive );
HRESULT get_Priority( long* plPriority );
HRESULT get_PrivLevel( long* plPrivLevel );
HRESULT get_QueueInfo( MSMQQueue** ppinfo );
HRESULT get_Quota( long* plQuota );
HRESULT get_SenderIdType( long* plSenderIdType );
HRESULT get_ShareMode( long* plShareMode );
HRESULT get_Trace( long* plTrace );
HRESULT put_Ack( long* lAck );
HRESULT put_AppSpecific( long plAppSpecific );
HRESULT put_AuthLevel( long lAuthLevel );
HRESULT put_Authenticate( long lAuthenticate );
HRESULT put_BasePriority( long lBasePriority );
HRESULT put_Delivery( long lDelivery );
HRESULT put_EncryptAlgorithm( long lEncryptAlg );
HRESULT put_HashAlgorithm( long lHashAlg );
HRESULT put_Journal( long lJournal );
HRESULT put_JournalQuota( long lJournalQuota );
HRESULT put_MaxTimeToReachQueue( long lMaxTimeToReachQueue );
HRESULT put_MaxTimeToReceive( long lMaxTimeToReceive );
HRESULT put_Priority( long lPriority );
HRESULT put_PrivLevel( long lPrivLevel );
HRESULT put_Quota( long lQuota );
HRESULT put_SenderIdType( long lSenderIdType );
HRESULT put_Trace( long lTrace );
HRESULT putref_AdminQueueInfo( MSMQQueueInfo* pinfoAdmin );

#endif /* _MQOAI_ */
