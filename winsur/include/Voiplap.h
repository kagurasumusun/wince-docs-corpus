/* Voiplap.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 10 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _VOIPLAP_
#define _VOIPLAP_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define VOIPLAP_E_BUSY 6008
#define VOIPLAP_E_CANTAUTHENTICATESERVER 6004
#define VOIPLAP_E_CANTCONNECT 6003
#define VOIPLAP_E_INVALIDDATA 6007
#define VOIPLAP_E_NOCREDENTIALS 6002
#define VOIPLAP_E_NOSERVER 6001
#define VOIPLAP_E_TIMEOUT 6006
#define VOIPLAP_E_TRANSMISSIONFAILED 6005
#define VOIPLAP_S_PCLOCKED 1
#define VOIPLAP_S_PCUNLOCKED 0

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 5.0..599 */

/* AttemptConnection  [function; ce-only; CE 5.0..599] */
DWORD AttemptConnection();

/* GetPCSyncName  [function; ce-only; CE 5.0..599] */
HRESULT GetPCSyncName( 
 WCHAR* wszNameBuffer, 
 INT cchNameBuffer 
);

/* SetPCSyncName  [function; ce-only; CE 5.0..599] */
HRESULT SetPCSyncName( 
 const WCHAR* c_wszPCName 
);
#endif /* _WIN32_WCE */

#endif /* _VOIPLAP_ */
