/* Btagpub.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 9 constants, 23 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _BTAGPUB_
#define _BTAGPUB_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define NETWORK_FLAGS_DROP_ACTIVE 0x01
#define NETWORK_FLAGS_DROP_ALL 0x0f
#define NETWORK_FLAGS_DROP_HOLD 0x02
#define NETWORK_FLAGS_DROP_OFFERING 0x04
#define NETWORK_FLAGS_DROP_OUTGOING 0x08
#define NETWORK_FLAGS_STATE_ACTIVE 0x01
#define NETWORK_FLAGS_STATE_HOLD 0x02
#define NETWORK_FLAGS_STATE_OFFERING 0x04
#define NETWORK_FLAGS_STATE_OUTGOING 0x08

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 5.0..599 */

/* BthAGDeinitPhoneExt  [function; ce-only; CE 5.0..599; Btagsvc_phoneext.lib] */
void BthAGPhoneExtDeinit(void);

/* BthAGInitPhoneExt  [function; ce-only; CE 5.0..599; Btagsvc_phoneext.lib] */
DWORD BthAGInitPhoneExt(void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* BthAGATHandler  [function; ce-only; CE 5.0..699] */
BOOL BthAGATHandler (
 LPSTR szCommand, 
 DWORD cbCommand
);

/* BthAGGetLastDialed  [function; ce-only; CE 5.0..699; Btagsvc_phoneext.lib] */
BOOL BthAGGetLastDialed(
 LPWSTR pwszNumber
);

/* BthAGGetNameByPhoneNumber  [function; ce-only; CE 5.0..699; Btagsvc_phoneext.lib] */
BOOL BthAGGetNameByPhoneNumber (
 LPCWSTR pwszNumber,
 LPWSTR pwszName
);

/* BthAGGetSpeedDial  [function; ce-only; CE 5.0..699; Btagsvc_phoneext.lib] */
BOOL BthAGGetSpeedDial(
 unsigned short usIndex,
 LPwSTR pwszNumber
);

/* BthAGNetworkAnswerCall  [function; ce-only; CE 5.0..699; Btagsvc_network.lib] */
DWORD BthAGNetworkAnswerCall(void);

/* BthAGNetworkDeinit  [function; ce-only; CE 5.0..699; Btagsvc_network.lib] */
void BthAGNetworkDeinit(void);

/* BthAGNetworkDialNumber  [function; ce-only; CE 5.0..699; Btagsvc_network.lib] */
DWORD BthAGNetworkDialNumber(LPSTR pszNumber);

/* BthAGNetworkDropCall  [function; ce-only; CE 5.0..699; Btagsvc_network.lib] */
DWORD BthAGNetworkHangupCall(DWORD dwFlags);

/* BthAGNetworkGetCallState  [function; ce-only; CE 5.0..699; Btagsvc_network.lib] */
DWORD BthAGNetworkGetCallState ( PDWORD pdwFlags);

/* BthAGNetworkHoldCall  [function; ce-only; CE 5.0..699; Btagsvc_network.lib] */
DWORD BthAgNetworkHoldCall(void);

/* BthAGNetworkInit  [function; ce-only; CE 5.0..699; Btagsvc_network.lib] */
DWORD BthAGNetworkInit(
 HINSTANCE hInstance
);

/* BthAGNetworkRejectCall  [function; ce-only; CE 5.0..699; Btagsvc_network.lib] */
DWORD BthAGNetworkRejectCall(void);

/* BthAGNetworkSwapCall  [function; ce-only; CE 5.0..699; Btagsvc_network.lib] */
DWORD BthAGNetworkSwapCall(void);

/* BthAGNetworkTransmitDTMF  [function; ce-only; CE 5.0..699; Btagsvc_network.lib] */
DWORD BthAGNetworkTransmitDTMF(LPSTR pszDTMF);

/* BthAGNetworkUnholdCall  [function; ce-only; CE 5.0..699; Btagsvc_network.lib] */
DWORD BthAGNetworkUnholdCall(void);

/* BthAGOverrideCallIn  [function; ce-only; CE 5.0..699; Btagsvc_phoneext.lib] */
BOOL BthAGOverrideCallIn(BOOL fHandsfree);

/* BthAGOverrideCallOut  [function; ce-only; CE 5.0..699; Btagsvc_phoneext.lib] */
BOOL BthAGOverrideCallOut(BOOL fHandsfree);

/* BthAGPhoneExtDeinit  [function; ce-only; CE 5.0..699; Btagsvc_phoneext.lib] */
void BthAGPhoneExtDeinit(void);

/* BthAGPhoneExtEvent  [function; ce-only; CE 5.0..699; Btagsvc_phoneext.lib] */
void BthAGPhoneExtEvent(
 DWORD dwEvent,
 DWORD dwParam,
 VOID* pvParam2
);

/* BthAGPhoneExtInit  [function; ce-only; CE 5.0..699; Btagsvc_phoneext.lib] */
DWORD BthAGInitPhoneExt(void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* BthAGNetworkDropSwapCall  [function; ce-only; CE 6.0..699; Btagsvc_network.lib] */
DWORD BthAGNetworkDropSwapCall(void);
#endif /* _WIN32_WCE */

#endif /* _BTAGPUB_ */
