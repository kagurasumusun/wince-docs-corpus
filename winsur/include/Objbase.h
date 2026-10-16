/* Objbase.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 42 constants, 66 declarations, 0 outlines, 0 base types, 0 extra macros, 10 extra decls
 */
#ifndef _OBJBASE_
#define _OBJBASE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ASYNC_MODE_COMPATIBILITY 1
#define ASYNC_MODE_DEFAULT 0
#define CLSCTX_ALL (CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER|CLSCTX_LOCAL_SERVER)
#define CLSCTX_INPROC (CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER)
#define CLSCTX_INPROC_HANDLER 0x2
#define CLSCTX_INPROC_SERVER 0x1
#define CLSCTX_LOCAL_SERVER 0x4
#define CLSCTX_REMOTE_SERVER 0x10
#define CLSCTX_SERVER (CLSCTX_INPROC_SERVER|CLSCTX_LOCAL_SERVER|CLSCTX_REMOTE_SERVER)
#define COM_RIGHTS_EXECUTE 1
#define COM_RIGHTS_SAFE_FOR_SCRIPTING 2
#define CWCSTORAGENAME 32
#define EOAC_NONE 0x0
#define MARSHALINTERFACE_MIN 500
#define STG_LAYOUT_INTERLEAVED 1
#define STG_LAYOUT_SEQUENTIAL 0
#define STG_TOEND 0xFFFFFFFF
#define STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE 4
#define STGC_DEFAULT 0
#define STGC_ONLYIFCURRENT 2
#define STGC_OVERWRITE 1
#define STGM_CONVERT 0x00020000L
#define STGM_CREATE 0x00001000L
#define STGM_DELETEONRELEASE 0x04000000L
#define STGM_DIRECT 0x00000000L
#define STGM_DIRECT_SWMR 0x00400000L
#define STGM_FAILIFTHERE 0x00000000L
#define STGM_NOSCRATCH 0x00100000L
#define STGM_NOSNAPSHOT 0x00200000L
#define STGM_PRIORITY 0x00040000L
#define STGM_READ 0x00000000L
#define STGM_READWRITE 0x00000002L
#define STGM_SHARE_DENY_NONE 0x00000040L
#define STGM_SHARE_DENY_READ 0x00000030L
#define STGM_SHARE_DENY_WRITE 0x00000020L
#define STGM_SHARE_EXCLUSIVE 0x00000010L
#define STGM_SIMPLE 0x08000000L
#define STGM_TRANSACTED 0x00010000L
#define STGM_WRITE 0x00000001L
#define STGOPTIONS_VERSION 2
#define STGTY_REPEAT 256
#define WINOLEAPI STDAPI

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* CoInitialize  [macro, function; shared; Ole232.lib, Ole32.lib] */
HRESULT CoInitialize(
 LPVOID pvReserved 
);

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* AUTH_IDENTITY  [struct; ce-only] */
typedef struct _AUTH_IDENTITY {
 [size_is(UserLength+1)] USHORT *User;
 ULONG UserLength;
 [size_is(DomainLength+1)] USHORT * Domain;
 ULONG DomainLength;
 [size_is(DomainLength+1)] USHORT *Password;
 ULONG Flags;
} AUTH_IDENTITY;
typedef AUTH_IDENTITY *PAUTH_IDENTITY, *LPAUTH_IDENTITY;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x200 && _WIN32_WCE < 0x210) || (_WIN32_WCE >= 0x212 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.0..209, 2.12..399, 5.0..699 */

/* Exp  [function; ce-only; CE 2.0..209, 2.12..399, 5.0..699; coredll.dll, ole232.lib] */
double exp( doublex);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..699 */

/* CoFreeLibrary  [function; shared; CE 2.11..2.12, 3.0..699; Ole32.lib, ole32.lib] */
void CoFreeLibrary(
 HINSTANCE hInst
);

/* CoFreeUnusedLibraries  [function; shared; CE 2.11..2.12, 3.0..699; Ole32.lib, ole32.lib] */
void CoFreeUnusedLibraries();

/* CoInitializeEx  [function; shared; CE 2.11..2.12, 3.0..699; Ole32.lib, ole32.lib] */
HRESULT CoInitializeEx(
 LPVOID pvReserved, 
 DWORD dwCoInit
);

/* CoTaskMemAlloc  [function; shared; CE 2.11..2.12, 3.0..699; Ole32.lib, ole32.lib] */
LPVOID CoTaskMemAlloc(
 ULONG cb
);

/* CoTaskMemFree  [function; shared; CE 2.11..2.12, 3.0..699; Ole32.lib, ole32.lib] */
void CoTaskMemFree(
 LPVOID pv
);

/* CoTaskMemRealloc  [function; shared; CE 2.11..2.12, 3.0..699; Ole32.lib, ole32.lib] */
LPVOID CoTaskMemRealloc(
 LPVOID pv, 
 ULONG cb
);

/* CoUninitialize  [function; shared; CE 2.11..2.12, 3.0..699; Ole32.lib, ole32.lib] */
void CoUninitialize();
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* CoAddRefServerProcess  [function; shared; CE 3.0..699; Ole232.lib, Ole32.lib, ole32.lib] */
ULONG CoAddRefServerProcess(void);

/* CoFileTimeNow  [function; shared; CE 3.0..699; Ole232.lib, Ole32.lib, ole32.lib] */
HRESULT CoFileTimeNow(
 FILETIME* lpFileTime
);

/* CoFreeAllLibraries  [function; shared; CE 3.0..699; Ole232.lib, Ole32.lib, ole32.lib] */
void CoFreeAllLibraries( );

/* CoGetCurrentProcess  [function; shared; CE 3.0..699; Ole232.lib, Ole32.lib, ole32.lib] */
DWORD CoGetCurrentProcess(void);

/* CoImpersonateClient  [function; shared; CE 3.0..699; Ole232.lib, Ole32.lib, ole32.lib] */
HRESULT CoImpersonateClient( );

/* CoReleaseServerProcess  [function; shared; CE 3.0..699; Ole232.lib, Ole32.lib, ole32.lib] */
ULONG CoReleaseServerProcess(void);

/* CoResumeClassObjects  [function; shared; CE 3.0..699; Ole232.lib, Ole32.lib, ole32.lib] */
WINOLEAPI CoResumeClassObjects(void);

/* CoRevertToSelf  [function; shared; CE 3.0..699; Ole232.lib, Ole32.lib, ole32.lib] */
HRESULT CoRevertToSelf( );

/* CoRevokeClassObject  [function; shared; CE 3.0..699; Ole232.lib, Ole32.lib, ole32.lib] */
HRESULT CoRevokeClassObject(
 DWORD dwRegister
);

/* CoRevokeMallocSpy  [function; shared; CE 3.0..699; Ole232.lib, Ole32.lib, ole32.lib] */
HRESULT CoRevokeMallocSpy( );

/* CoSuspendClassObjects  [function; shared; CE 3.0..699; Ole232.lib, Ole32.lib, ole32.lib] */
WINOLEAPI CoSuspendClassObjects(void);

/* DllCanUnloadNow  [function; shared; CE 3.0..699; Oleaut32.lib, oleaut32.lib] */
STDAPI DllCanUnloadNow(void);

/* UpdateDCOMSettings  [function; ce-only; CE 3.0..699; Ole232.lib, Ole32.lib, ole32.lib] */
void UpdateDCOMSettings(void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* CoFreeUnusedLibrariesEx  [function; shared; CE 5.0..699; Ole32.lib, ole32.lib] */
void CoFreeUnusedLibrariesEx(
 DWORD dwUnloadDelay,
 DWORD dwReserved
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT Flush( void );
HRESULT LockRegion( ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType );
HRESULT ReadAt( ULARGE_INTEGER ulOffset, void *pv, ULONG cb, ULONG *pcbRead );
HRESULT SetSize( ULARGE_INTEGER cb );
HRESULT UnlockRegion( ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType );
HRESULT WriteAt( ULARGE_INTEGER ulOffset, void const *pv, ULONG cb, ULONG * pcbWritten );

#endif /* _OBJBASE_ */
