/* Exdisp.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 20 constants, 4 declarations, 0 outlines, 0 base types, 0 extra macros, 20 extra decls
 */
#ifndef _EXDISP_
#define _EXDISP_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CSC_UPDATECOMMANDS 0xFFFFFFFF
#define navAllowAutosearch 0x10
#define navBrowserBar 0x20
#define navHyperlink 0x40
#define navNoHistory 0x2
#define navNoReadFromCache 0x4
#define navNoWriteToCache 0x8
#define navOpenInNewWindow 0x1
#define secureLockIcon128Bit 0x6
#define secureLockIcon40Bit 0x3
#define secureLockIcon56Bit 0x4
#define secureLockIconFortezza 0x5
#define secureLockIconMixed 0x1
#define secureLockIconSecure128Bit 0x6
#define secureLockIconSecure40Bit 0x3
#define secureLockIconSecure56Bit 0x4
#define secureLockIconSecureFortezza 0x5
#define secureLockIconSecureUnknownBits 0x2
#define secureLockIconUnknownBits 0x2
#define secureLockIconUnsecure 0

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* BrowserNavConstants  [enum; ce-only] */
typedef enum BrowserNavConstants { 
 navOpenInNewWindow = 0x1, 
 navNoHistory = 0x2, 
 navNoReadFromCache = 0x4, 
 navNoWriteToCache = 0x8, 
 navAllowAutosearch = 0x10, 
 navBrowserBar = 0x20, 
 navHyperlink = 0x40 
} BrowserNavConstants;
typedef BrowserNavConstants *PBrowserNavConstants, *LPBrowserNavConstants;

/* CommandStateChangeConstants  [enum; ce-only; shdocvw.lib] */
enum CommandStateChangeConstants{
 CSC_NAVIGATEFORWARD = 0x1,
 CSC_NAVIGATEBACK = 0x2
} CommandStateChangeConstants;

/* RefreshConstants  [enum; ce-only] */
typedef enum RefreshConstants { 
 REFRESH_NORMAL = 0, 
 REFRESH_IFEXPIRED = 1, 
 REFRESH_CONTINUE = 2, 
 REFRESH_COMPLETELY = 3 
} RefreshConstants;
typedef RefreshConstants *PRefreshConstants, *LPRefreshConstants;

/* SecureLockIconConstants  [enum; ce-only; shdocvw.lib] */
enum SecureLockIconConstants{
 secureLockIconUnsecure = 0,
 secureLockIconMixed = 0x1,
 secureLockIconSecureUnknownBits = 0x2,
 secureLockIconSecure40Bit = 0x3,
 secureLockIconSecure56Bit = 0x4,
 secureLockIconSecureFortezza = 0x5,
 secureLockIconSecure128Bit = 0x6
} SecureLockIconConstants;

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void ClientToHostWindow( long* plCX, long* plCY );
HRESULT ClientToWindow( int* pcx, int* pcy );
HRESULT GoBack(VOID);
HRESULT GoForward(VOID);
HRESULT GoHome(VOID);
HRESULT GoSearch(VOID);
void ProgressChange( long lProgress, long lProgressMax );
HRESULT Quit(VOID);
void SetSecureLockIcon( long lSecureLockIcon );
void WindowSetHeight( long lHeight );
void WindowSetLeft( long lLeft );
void WindowSetTop( long lTop );
void WindowSetWidth( long lWidth );

#endif /* _EXDISP_ */
