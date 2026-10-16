/* Kitl.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 23 declarations, 1 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _KITL_
#define _KITL_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* KITLTRANSPORT  [struct; ce-only] */

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x600)) /* CE 1.0..199, 2.11..2.12, 4.0..599 */

/* TransportRecv  [function; ce-only; CE 1.0..199, 2.11..2.12, 4.0..599; Kitl.lib] */
BOOL TransportRecv(
 LPBYTE pbBuffer,
 PUSHORT pcbBuffer
);

/* TransportSend  [function; ce-only; CE 1.0..199, 2.11..2.12, 4.0..599; Kitl.lib] */
BOOL TransportSend(LPBYTE pbFrame,USHORT cbFrame);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x600)) /* CE 4.0..599 */

/* KitlInit  [function; ce-only; CE 4.0..599; Kitl.lib] */
BOOL KitlInit(
 BOOL fStartKitl
);

/* KITLOutputDebugString  [function; ce-only; CE 4.0..599; Kitl.lib] */
void KITLOutputDebugString(const char* fmt,
 ...
);

/* KitlSendRawData  [function; ce-only; CE 4.0..599; Kitl.lib] */
BOOL KitlSendRawData(
 LPBYTE pbData,
 WORD wLength
);

/* TransportDecode  [function; ce-only; CE 4.0..599; Kitl.lib] */
LPBYTE TransportDecode(
 LPBYTE pbFrame,
 PUSHORT pcbData
);

/* TransportEnableInt  [function; ce-only; CE 4.0..599; Kitl.lib] */
void TransportEnableInt(BOOL fEnable);

/* TransportEncode  [function; ce-only; CE 4.0..599; Kitl.lib] */
BOOL TransportEncode(
 LPBYTE pbFrame,
 USHORT cbData
);

/* TransportGetDevCfg  [function; ce-only; CE 4.0..599; Kitl.lib] */
BOOL TransportGetDevCfg(
 LPBYTE pbBuffer,
 PUSHORT pcbBuffer
);

/* TransportSetHostCfg  [function; ce-only; CE 4.0..599; Kitl.lib] */
BOOL TransportSetHostCfg(
 LPBYTE pbBuffer,
 PUSHORT pcbBuffer
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* OEMKitlGetSecs  [function; ce-only; CE 4.0..699; Kitl.lib] */
DWORD OEMKitlGetSecs(void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* PFN_DECODE  [function; ce-only; CE 6.0..699; Kitl.lib] */
LPBYTE TransportDecode(
 LPBYTE pbFrame,
 PUSHORT pcbData
);

/* PFN_ENABLEINT  [function; ce-only; CE 6.0..699; Kitl.lib] */
void TransportEnableInt(
 BOOL Enable
);

/* PFN_ENCODE  [function; ce-only; CE 6.0..699; Kitl.lib] */
BOOL TransportEncode(
 LPBYTE pbFrame,
 USHORT cbData
);

/* PFN_GETDEVCFG  [function; ce-only; CE 6.0..699; Kitl.lib] */
BOOL TransportGetDevCfg(
 LPBYTE pbBuffer,
 PUSHORT pcbBuffer
);

/* PFN_RECVFRAME  [function; ce-only; CE 6.0..699; Kitl.lib] */
BOOL TransportRecv(
 LPBYTE pbBuffer,
 PUSHORT pcbBuffer
);

/* PFN_SENDFRAME  [function; ce-only; CE 6.0..699; Kitl.lib] */
BOOL TransportSend(
 LPBYTE pbFrame,
 USHORT cbFrame
);

/* PFN_SETHOSTCFG  [function; ce-only; CE 6.0..699; Kitl.lib] */
BOOL TransportSetHostCfg(
 LPBYTE pbBuffer,
 PUSHORT pcbBuffer
);
#endif /* _WIN32_WCE */

#endif /* _KITL_ */
