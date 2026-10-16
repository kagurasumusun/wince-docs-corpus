/* Objidl.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 45 constants, 12 declarations, 37 outlines, 0 base types, 0 extra macros, 71 extra decls
 */
#ifndef _OBJIDL_
#define _OBJIDL_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define COLE_DEFAULT_AUTHINFO (
#define COLE_DEFAULT_PRINCIPAL (
#define DVASPECT_CONTENT 1
#define DVASPECT_DOCPRINT 8
#define DVASPECT_ICON 4
#define DVASPECT_OPAQUE 16
#define DVASPECT_THUMBNAIL 2
#define DVASPECT_TRANSPARENT 32
#define EXTCONN_STRONG 0x0001
#define PIDDSI_BYTECOUNT 0x00000004
#define PIDDSI_CATEGORY 0x00000002
#define PIDDSI_COMPANY 0x0000000F
#define PIDDSI_DOCPARTS 0x0000000D
#define PIDDSI_HEADINGPAIR 0x0000000C
#define PIDDSI_HIDDENCOUNT 0x00000009
#define PIDDSI_LINECOUNT 0x00000005
#define PIDDSI_LINKSDIRTY 0x00000010
#define PIDDSI_MANAGER 0x0000000E
#define PIDDSI_MMCLIPCOUNT 0x0000000A
#define PIDDSI_NOTECOUNT 0x00000008
#define PIDDSI_PARCOUNT 0x00000006
#define PIDDSI_PRESFORMAT 0x00000003
#define PIDDSI_SCALE 0x0000000B
#define PIDDSI_SLIDECOUNT 0x00000007
#define PIDSI_APPNAME 0x00000012
#define PIDSI_AUTHOR 0x00000004
#define PIDSI_CHARCOUNT 0x00000010
#define PIDSI_COMMENTS 0x00000006
#define PIDSI_CREATE_DTM 0x0000000C
#define PIDSI_DOC_SECURITY 0x00000013
#define PIDSI_EDITTIME 0x0000000A
#define PIDSI_KEYWORDS 0x00000005
#define PIDSI_LASTAUTHOR 0x00000008
#define PIDSI_LASTPRINTED 0x0000000B
#define PIDSI_LASTSAVE_DTM 0x0000000D
#define PIDSI_PAGECOUNT 0x0000000E
#define PIDSI_REVNUMBER 0x00000009
#define PIDSI_SUBJECT 0x00000003
#define PIDSI_TEMPLATE 0x00000007
#define PIDSI_THUMBNAIL 0x00000011
#define PIDSI_TITLE 0x00000002
#define PIDSI_WORDCOUNT 0x0000000F
#define PRSPEC_INVALID 0xFFFFFFFF
#define PRSPEC_LPWSTR 0x00000000
#define PRSPEC_PROPID 0x00000001

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* STGMEDIUM  [struct; ce-only] */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 3.0..399, 5.0..599 */

/* IAdviseSink  [interface; shared; CE 3.0..399, 5.0..599; Oleaut32.lib, Uuid.lib] */

/* IClassActivator  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IClientSecurity  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IEnumMoniker  [function, interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IEnumSTATDATA  [function, interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IEnumSTATSTG  [function, interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IEnumString  [function, interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IExternalConnection  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IFillLockBytes  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* ILockBytes  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IMarshal  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IMessageFilter  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IMoniker  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IMultiQI  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IPersist  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IPersistFile  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IPersistStorage  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IRootStorage  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IROTData  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IRunnableObject  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IRunningObjectTable  [function, interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* ISequentialStream  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IServerSecurity  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IStdMarshalInfo  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IStorage  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IStream  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* IEnumUnknown  [function, interface; shared; CE 4.0..699; Ole32.lib, ole32.lib, Uuid.lib, uuid.lib] */
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 5.0..599 */

/* IBindCtx  [interface; shared; CE 5.0..599; Ole32.lib, Uuid.lib] */

/* IDataObject  [interface; shared; CE 5.0..599; Ole32.lib, Uuid.lib] */

/* IEnumFORMATETC  [interface; shared; CE 5.0..599; Ole32.lib, Uuid.lib] */

/* IGlobalInterfaceTable  [function, interface; shared; CE 5.0..599; Ole32.lib, Uuid.lib] */

/* IMalloc  [interface; shared; CE 5.0..599; Ole32.lib] */

/* IMallocSpy  [interface; shared; CE 5.0..599; Ole32.lib] */

/* IPersistStream  [interface; shared; CE 5.0..599; Ole32.lib, Uuid.lib] */

/* IProgressNotify  [interface; shared; CE 5.0..599; Ole32.lib, Uuid.lib] */
#endif /* _WIN32_WCE */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* ADVF  [enum; shared] */
typedef enum tagADVF { 
 ADVF_NODATA = 1, 
 ADVF_PRIMEFIRST = 2, 
 ADVF_ONLYONCE = 4, 
 ADVFCACHE_NOHANDLER = 8, 
 ADVFCACHE_FORCEBUILTIN = 16, 
 ADVFCACHE_ONSAVE = 32, 
 ADVF_DATAONSTOP = 64 
} ADVF;
typedef ADVF *PADVF, *LPADVF;

/* BIND_OPTS  [struct; shared] */
typedef struct tagBIND_OPTS {
 DWORD cbStruct; 
 DWORD grfFlags; 
 DWORD grfMode; 
 DWORD dwTickCountDeadline; 
} BIND_OPTS, *LPBIND_OPTS;

/* DATADIR  [enum; shared] */
typedef enum tagDATADIR { 
 DATADIR_GET = 1, 
 DATADIR_SET = 2 
} DATADIR;
typedef DATADIR *PDATADIR, *LPDATADIR;

/* DVTARGETDEVICE  [struct; shared] */
typedef struct tagDVTARGETDEVICE{
 DWORD tdSize;
 WORD tdDriverNameOffset;
 WORD tdDeviceNameOffset;
 WORD tdPortNameOffset;
 WORD tdExtDevmodeOffset;
 BYTE tdData;
} DVTARGETDEVICE;
typedef DVTARGETDEVICE *PDVTARGETDEVICE, *LPDVTARGETDEVICE;

/* MKRREDUCE  [enum; shared] */
typedef enum tagMKRREDUCE { 
 MKRREDUCE_ONE = 3<<16, 
 MKRREDUCE_TOUSER = 2<<16, 
 MKRREDUCE_THROUGHUSER = 1<<16, 
 MKRREDUCE_ALL = 0 
} MKRREDUCE;
typedef MKRREDUCE *PMKRREDUCE, *LPMKRREDUCE;

/* MKSYS  [enum; shared] */
typedef enum tagMKSYS { 
 MKSYS_NONE = 0,
 MKSYS_GENERICCOMPOSITE = 1,
 MKSYS_FILEMONIKER = 2,
 MKSYS_ANTIMONIKER = 3,
 MKSYS_ITEMMONIKER = 4,
 MKSYS_POINTERMONIKER = 5,
 MKSYS_CLASSMONIKER = 7,
 MKSYS_OBJREFMONIKER = 8,
 MKSYS_SESSIONMONIKER = 9
} MKSYS;
typedef MKSYS *PMKSYS, *LPMKSYS;

/* TYMED  [enum; shared] */
typedef enum tagTYMED {
 TYMED_HGLOBAL = 1,
 TYMED_FILE = 2,
 TYMED_ISTREAM = 4,
 TYMED_ISTORAGE = 8,
 TYMED_NULL = 0,
} TYMED;
typedef TYMED *PTYMED, *LPTYMED;

/* MULTI_QI  [struct; shared] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   pIID */
/*   pItf */
/*   hr */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT AddConnection( DWORD exconn, DWORD dwreserved );
HRESULT Commit( DWORD grfCommitFlags );
HRESULT DUnadvise( DWORD dwConnection );
HRESULT DestroyElement( WCHAR *pwcsName );
int DidAlloc( void* pv );
HRESULT DisconnectObject( DWORD dwReserved );
HRESULT FillAppend( void const *pv, ULONG cb, ULONG *pcbWritten );
HRESULT FillAt( ULARGE_INTEGER uIOffset, void const *pv, ULONG cb, ULONG *pcbWritten );
HRESULT FreeSurrogate();
HRESULT GetBindOptions( BIND_OPTS* pbindopts );
HRESULT GetCanonicalFormatEtc( FORMATETC* pFormatetcIn, FORMATETC* pFormatetcOut );
HRESULT GetComparisonData( byte *pbData, ULONG cbMax, ULONG *pcbData );
HRESULT GetData( FORMATETC* pFormatetc, STGMEDIUM* pmedium );
HRESULT GetDataHere( FORMATETC* pFormatetc, STGMEDIUM* pmedium );
HRESULT HandsOfStorage(void);
void HeapMinimize();
HRESULT ImpersonateClient( )
HRESULT IsDirty(void);
BOOL IsImpersonating( )
HRESULT LockRunning( BOOL fLock, BOOL fLastUnlockCloses );
HRESULT NoteChangeTime( DWORD dwRegister, FILETIME *pfiletime );
HRESULT OnProgress( DWORD dwProgressCurrent, DWORD dwProgressMaximum, BOOL fAccurate, BOOL fOwner );
void* PostAlloc(  void* pActual  );
int PostDidAlloc( void* pRequest, BOOL fSpyed, int fActual );
void PostFree( BOOL fSpyed );
LONG PostGetSize( ULONG cbActual, BOOL fSpyed );
void PostHeapMinimize(void);
void* PostRealloc(  void* pActual,  BOOL fSpyed  );
LONG PreAlloc( ULONG cbRequest );
void* PreDidAlloc(  void* pRequest,  BOOL fSpyed  );
void* PreFree(  void* pRequest,  BOOL fSpyed  );
void* PreGetSize(  void* pRequest,  BOOL fSpyed  );
void PreHeapMinimize(void);
LONG PreRealloc( void* pRequest, ULONG cbRequest, void** ppNewRequest, BOOL fSpyed );
HRESULT QueryGetData( FORMATETC* pFormatetc );
HRESULT QueryMultipleInterfaces( ULONG cMQIs, MULTI_QI *pMQIs );
HRESULT Read( void *pv, ULONG cb, ULONG *pcbRead );
void* Realloc(  void* pv,  ULONG cb  );
HRESULT ReleaseBoundObjects(void);
HRESULT RenameElement( const WCHAR *pwcsOldName, const WCHAR *pwcsNewName );
HRESULT Revert( void );
HRESULT RevertToSelf( )
HRESULT Revoke( DWORD dwRegister );
HRESULT RevokeInterfaceFromGlobal( DWORD dwCookie );
HRESULT Seek( ULARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER plibNewPosition );
HRESULT SetBindOptions( BIND_OPTS* pbindopts );
HRESULT SetContainedObject( BOOL fContained );
HRESULT SetData( FORMATETC* pFormatetc, STGMEDIUM* pmedium, BOOL fRelease );
HRESULT SetElementTimes( const WCHAR *pwcsName, FILETIME const *pctime, FILETIME const *patime, FILETIME const *pmtime );
HRESULT SetFillSize( ULARGE_INTEGER uISize );
HRESULT SetStateBits( DWORD grfStateBits, DWORD grfMask );
HRESULT Terminate( BOOL bCanceled );
HRESULT Write( void const *pv, ULONG cb, ULONG *pcbWritten );

#endif /* _OBJIDL_ */
