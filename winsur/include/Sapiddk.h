/* Sapiddk.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 7 declarations, 0 outlines, 0 base types, 0 extra macros, 55 extra decls
 */
#ifndef _SAPIDDK_
#define _SAPIDDK_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* SPPROPSRC  [enum; ce-only] */
typedef enum SPPROPSRC{
 SPPROPSRC_RECO_INST,
 SPPROPSRC_RECO_CTX,
 SPPROPSRC_RECO_GRAMMAR
} SPPROPSRC;
typedef SPPROPSRC *PSPPROPSRC, *LPSPPROPSRC;

/* SPRESULTTYPE  [enum; ce-only] */
typedef enum SPRESULTTYPE {
 SPRT_CFG = 0,
 SPRT_SLM = 1,
 SPRT_PROPRIETARY = 2,
 SPRT_FALSE_RECOGNITION = (1 << 1)
} SPRESULTTYPE;
typedef SPRESULTTYPE *PSPRESULTTYPE, *LPSPRESULTTYPE;

/* SPRULEINFOOPT  [enum; ce-only] */
typedef enum SPRULEINFOOPT{
 SPRIO_NONE = 0
} SPRULEINFOOPT;
typedef SPRULEINFOOPT *PSPRULEINFOOPT, *LPSPRULEINFOOPT;

/* SPTRANSITIONTYPE  [enum; ce-only] */
typedef enum SPTRANSITIONTYPE{
 SPTRANSEPSILON,
 SPTRANSWORD,
 SPTRANSRULE,
 SPTRANSTEXTBUF,
 SPTRANSWILDCARD,
 SPTRANSDICTATION
} SPTRANSITIONTYPE;
typedef SPTRANSITIONTYPE *PSPTRANSITIONTYPE, *LPSPTRANSITIONTYPE;

/* SPVESACTIONS  [enum; ce-only] */
typedef enum SPVESACTIONS{
 SPVES_CONTINUE = 0,
 SPVES_ABORT = ( 1L << 0 ),
 SPVES_SKIP = ( 1L << 1 ),
 SPVES_RATE = ( 1L << 2 ),
 SPVES_VOLUME = ( 1L << 3 )
} SPVESACTIONS;
typedef SPVESACTIONS *PSPVESACTIONS, *LPSPVESACTIONS;

/* SPVSKIPTYPE  [enum; ce-only] */
typedef enum SPVSKIPTYPE{
 SPVST_SENTENCE = (1L << 0)
} SPVSKIPTYPE;
typedef SPVSKIPTYPE *PSPVSKIPTYPE, *LPSPVSKIPTYPE;

/* SPWORDINFOOPT  [enum; ce-only] */
typedef enum SPWORDINFOOPT{
 SPWIO_NONE = 0,
 SPWIO_WANT_TEXT = 1
} SPWORDINFOOPT;
typedef SPWORDINFOOPT *PSPWORDINFOOPT, *LPSPWORDINFOOPT;

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT CallEngine( VOID* pCallFrame, ULONG ulCallFrameSize );
HRESULT CallEngineEx( const void* pInFrame, ULONG ulInFrameSize, void** ppCoMemOutFrame, ULONG* pulOutFrameSize );
HRESULT CompleteSkip( long ulNumSkipped );
HRESULT DataAvailable( ULONG* pcb );
DWORD GetActions(void);
HRESULT GetPropertyNum( SPPROPSRC eSrc, void* pvSrcObj, const WCHAR* pName, LONG* lValue );
HRESULT GetPropertyString( SPPROPSRC eSrc, void* pvSrcObj, const WCHAR* pName, WCHAR** ppCoMemValue );
HRESULT GetResourceValue( const WCHAR* pszResourceName, WCHAR** ppCoMemResource );
HRESULT GetSkipInfo( SPVSKIPTYPE* peType, long* plNumItems );
HRESULT InitGrammar( const WCHAR* pszGrammarName, const void** pvGrammarData );
HRESULT LoadITNGrammar( WCHAR* pszCLSID );
HRESULT LoadSLM( void* pvEngineGrammar, const WCHAR* pszTopicName );
HRESULT OnDeleteGrammar( void* pvEngineGrammar );
HRESULT OnDeleteRecoContext( void* pvEngineContext );
HRESULT PrivateCall( void* pvEngineContext, PVOID* pCallFrame, ULONG ulCallFrameSize );
HRESULT PrivateCallEx( void* pvEngineContext, const void* pInCallFrame, ULONG ulInCallFrameSize, void** ppvCoMemResponse, ULONG* pulResponseSize );
HRESULT SetAttribs( const WCHAR* pszReqAttribs, const WCHAR* pszOptAttribs );
HRESULT SetPropertyNum( SPPROPSRC eSrc, void* pvSrcObj, const WCHAR* pName, LONG lValue );
HRESULT SetPropertyString( SPPROPSRC eSrc, void* pvSrcObj, const WCHAR* pName, const WCHAR* pValue );
HRESULT StartThread( DWORD dwFlags, HWND* phwnd );
HRESULT Synchronize( ULONGLONG ullStreamPos );
HRESULT TerminateTask( DWORD dwTaskId, ULONG ulWaitPeriod );
HRESULT TerminateTaskGroup( DWORD dwGroupId, ULONG ulWaitPeriod );
HANDLE ThreadCompleteEvent(void);
HANDLE ThreadHandle(void);
DWORD ThreadId(void);
HRESULT UnloadProprietaryGrammar( void* pvEngineGrammar );
HRESULT UnloadSLM( void* pvEngineGrammar );
HRESULT UpdateRecoPos( ULONGLONG ullStreamPos );
HWND WindowHandle(void);

#endif /* _SAPIDDK_ */
