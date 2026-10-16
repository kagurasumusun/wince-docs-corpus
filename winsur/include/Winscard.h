/* Winscard.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 9 constants, 31 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WINSCARD_
#define _WINSCARD_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define SCARD_F_COMM_ERROR 0x80100013L
#define SCARD_F_INTERNAL_ERROR 0x80100001L
#define SCARD_F_UNKNOWN_ERROR 0x80100014L
#define SCARD_F_WAITED_TOO_LONG 0x80100007L
#define SCARD_P_SHUTDOWN 0x80100018L
#define SCARD_PROVIDER_CARD_MODULE 0x80000001
#define SCARD_PROVIDER_CSP 2
#define SCARD_PROVIDER_KSP 3
#define SCARD_PROVIDER_PRIMARY 1

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* SCARD_ATRMASK  [struct; shared] */
typedef struct _SCARD_ATRMASK {
 DWORD cbAtr; 
 BYTE rgbAtr[36]; 
 BYTE rgbMask[36]; 
} SCARD_ATRMASK, *PSCARD_ATRMASK, *LPSCARD_ATRMASK;

/* SCARD_IO_REQUEST  [struct; ce-only] */
typedef struct {
 DWORD dwProtocol;
 DWORD cbPciLength;
} SCARD_IO_REQUEST;
typedef SCARD_IO_REQUEST *PSCARD_IO_REQUEST, *LPSCARD_IO_REQUEST;

/* SCARD_READERSTATE  [struct; shared; A/W SCARD_READERSTATEA,SCARD_READERSTATEW (CE is W-side)] */
typedef struct {
 LPCTSTR szReader;
 LPVOID pvUserData;
 DWORD dwCurrentState;
 DWORD dwEventState;
 DWORD cbAtr;
 BYTE rgbAtr[36];
} SCARD_READERSTATE, *PSCARD_READERSTATE, *LPSCARD_READERSTATE;

#endif /* _WINSCARD_ */
