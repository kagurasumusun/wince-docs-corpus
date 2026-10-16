/* Wtypes.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 7 constants, 6 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WTYPES_
#define _WTYPES_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CLSID_NULL GUID_NULL
#define DECIMAL_NEG ((BYTE)0x80)
#define IID_NULL GUID_NULL
#define ROTFLAGS_ALLOWANYCLIENT 0x02
#define ROTFLAGS_REGISTRATIONKEEPSALIVE 0x01
#define VARIANT_FALSE ((VARIANT_BOOL)0)
#define VARIANT_TRUE ((VARIANT_BOOL)0xffff)

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CLSCTX  [enum; shared] */
typedef enum tagCLSCTX {
 CLSCTX_INPROC_SERVER = 0x1,
 CLSCTX_INPROC_HANDLER = 0x2,
 CLSCTX_LOCAL_SERVER = 0x4,
 CLSCTX_REMOTE_SERVER = 0x10
} CLSCTX;
typedef CLSCTX *PCLSCTX, *LPCLSCTX;

/* COAUTHIDENTITY  [struct; shared] */
typedef struct _COAUTHIDENTITY {
 USHORT* User; 
 ULONG UserLength; 
 USHORT* Domain; 
 ULONG DomainLength; 
 USHORT* Password; 
 ULONG PasswordLength; 
 ULONG Flags; 
} COAUTHIDENTITY;
typedef COAUTHIDENTITY *PCOAUTHIDENTITY, *LPCOAUTHIDENTITY;

/* COAUTHINFO  [struct; shared] */
typedef struct _COAUTHINFO { 
 DWORD dwAuthnSvc; 
 DWORD dwAuthzSvc; 
 LPWSTR pwszServerPrincName; 
 DWORD dwAuthnLevel; 
 DWORD dwImpersonationLevel; 
 COAUTHIDENTITY __RPC_FAR* pAuthIdentityData; 
 DWORD dwCapabilities; 
} COAUTHINFO;
typedef COAUTHINFO *PCOAUTHINFO, *LPCOAUTHINFO;

/* COSERVERINFO  [struct; shared] */
typedef struct _COSERVERINFO {
 DWORD dwReserved1;
 LPWSTR pwszName;
 COAUTHINFO* pAuthInfo;
 DWORD dwReserved2;
} COSERVERINFO;
typedef COSERVERINFO *PCOSERVERINFO, *LPCOSERVERINFO;

/* DVASPECT  [enum; shared] */
typedef enum tagDVASPECT { 
 DVASPECT_CONTENT = 1,
 DVASPECT_THUMBNAIL = 2,
 DVASPECT_ICON = 4,
 DVASPECT_DOCPRINT = 8
} DVASPECT;
typedef DVASPECT *PDVASPECT, *LPDVASPECT;

/* STGC  [enum; shared] */
typedef enum tagSTGC { 
 STGC_DEFAULT = 0, 
 STGC_OVERWRITE = 1, 
 STGC_ONLYIFCURRENT = 2, 
 STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE = 4, 
} STGC;
typedef STGC *PSTGC, *LPSTGC;

#endif /* _WTYPES_ */
