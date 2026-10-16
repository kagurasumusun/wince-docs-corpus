/* Ocidl.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 13 constants, 11 declarations, 11 outlines, 0 base types, 0 extra macros, 15 extra decls
 */
#ifndef _OCIDL_
#define _OCIDL_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define mpReadyStateComplete 4
#define MpReadyStateComplete 4
#define mpReadyStateInteractive 3
#define MpReadyStateInteractive 3
#define mpReadyStateLoading 1
#define MpReadyStateLoading 1
#define mpReadyStateUninitialized 0
#define MpReadyStateUninitialized 0
#define XFORMCOORDS_CONTAINERTOHIMETRIC 0x8
#define XFORMCOORDS_EVENTCOMPAT 0x10
#define XFORMCOORDS_HIMETRICTOCONTAINER 0x4
#define XFORMCOORDS_POSITION 0x1
#define XFORMCOORDS_SIZE 0x2

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 3.0..399, 5.0..599 */

/* IClassFactory  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IClassFactory2  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IConnectionPoint  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IConnectionPointContainer  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IEnumConnectionPoints  [function, interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IEnumConnections  [function, interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */

/* IPersistStreamInit  [interface; shared; CE 3.0..399, 5.0..599; Ole32.lib, Uuid.lib] */
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 5.0..599 */

/* IProvideClassInfo  [interface; shared; CE 5.0..599; Ole32.lib, Uuid.lib] */

/* IProvideClassInfo2  [interface; shared; CE 5.0..599; Ole32.lib, Uuid.lib] */

/* IViewObjectEx  [interface; shared; CE 5.0..599; Ole32.lib, Uuid.lib] */
#endif /* _WIN32_WCE */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CONTROLINFO  [struct; shared] */
typedef struct tagCONTROLINFO {
 ULONG cb;
 HACCEL hAccel;
 USHORT cAccel;
 DWORD dwFlags;
} CONTROLINFO;
typedef CONTROLINFO *PCONTROLINFO, *LPCONTROLINFO;

/* DVASPECT2  [enum; shared] */
typedef enum tagDVASPECT2 { 
 DVASPECT_OPAQUE = 16, 
 DVASPECT_TRANSPARENT = 32 
} DVASPECT2;
typedef DVASPECT2 *PDVASPECT2, *LPDVASPECT2;

/* DVASPECTINFOFLAG  [enum; shared] */
typedef enum tagDVASPECTINFOFLAG { 
 DVASPECTINFOFLAG_CANOPTIMIZE = 1 
} DVASPECTINFOFLAG;
typedef DVASPECTINFOFLAG *PDVASPECTINFOFLAG, *LPDVASPECTINFOFLAG;

/* DVEXTENTMODE  [enum; shared] */
typedef enum tagDVEXTENTMODE { 
 DVEXTENT_CONTENT = 0, 
 DVEXTENT_INTEGRAL = DVEXTENT_CONTENT + 1
} DVEXTENTMODE;
typedef DVEXTENTMODE *PDVEXTENTMODE, *LPDVEXTENTMODE;

/* HITRESULT  [enum; shared] */
typedef enum tagHITRESULT { 
 HITRESULT_OUTSIDE = 0, 
 HITRESULT_TRANSPARENT = 1, 
 HITRESULT_CLOSE = 2, 
 HITRESULT_HIT = 3 
} HITRESULT;
typedef HITRESULT *PHITRESULT, *LPHITRESULT;

/* LICINFO  [struct; shared] */
typedef struct tagLICINFO {
 ULONG cbLicInfo; 
 BOOL fRuntimeKeyAvail; 
 BOOL fLicVerified; 
} LICINFO;
typedef LICINFO *PLICINFO, *LPLICINFO;

/* ReadyState  [enum; shared] */
enum tagREADYSTATE{
 READYSTATE_UNINITIALIZED = 0,
 READYSTATE_LOADING = 1,
 READYSTATE_LOADED = 2,
 READYSTATE_INTERACTIVE = 3,
 READYSTATE_COMPLETE = 4
} READYSTATE;

/* VIEWSTATUS  [enum; shared] */
typedef enum tagVIEWSTATUS { 
 VIEWSTATUS_OPAQUE = 1, 
 VIEWSTATUS_SOLIDBKGND = 2, 
 VIEWSTATUS_DVASPECTOPAQUE = 4, 
 VIEWSTATUS_DVASPECTTRANSPARENT = 8 
} VIEWSTATUS;
typedef VIEWSTATUS *PVIEWSTATUS, *LPVIEWSTATUS;

/* CONNECTDATA  [struct; shared] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   pUnk */
/*   dwCookie */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT GetLicInfo( LICINFO *pLicInfo );
HRESULT GetPages( CAUUID *pPages //Pointer to structure );
HRESULT GetSizeMax( ULARGE_INTEGER *pcbSize );
HRESULT GetViewStatus( DWORD* pdwStatus );
HRESULT LockInPlaceActive( BOOL fLock);
HRESULT OnControlInfoChanged(void);
HRESULT OnFocus( BOOL fGotFocus);
HRESULT QueryHitRect( DWORD dwAspect, LPRECT pRectBounds, LPRECT pRectLoc, LONG lCloseHint, DWORD* pHitResult );
HRESULT ShowPropertyFrame(void);
HRESULT Unadvise( DWORD dwCookie );

#endif /* _OCIDL_ */
