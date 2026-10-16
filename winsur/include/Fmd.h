/* Fmd.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 2 constants, 16 declarations, 3 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _FMD_
#define _FMD_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define OEM_BLOCK_READONLY 0x02
#define OEM_BLOCK_RESERVED 0x01

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* FlashInfoEx  [struct; ce-only] */

/* FMDInterface  [struct; ce-only] */

/* SectorInfo  [struct, macro; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* RawWriteBlocksReq  [struct; ce-only] */
typedef struct _RawWriteBlocksReq {
 DWORD dwStartBlock;
 DWORD dwNumBlocks;
 LPBYTE pBuffer;
 DWORD cbBuffer;
} RawWriteBlocksReq, *PRawWriteBlocksReq;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* FMD_Deinit  [function; ce-only; CE 4.0..699] */
BOOL FMD_Deinit(
PVOID hFMD
);

/* FMD_GetInfo  [function; ce-only; CE 4.0..699] */
BOOL FMD_GetInfo(
 PFlashInfo pFlashInfo
);

/* FMD_PowerDown  [function; ce-only; CE 4.0..699] */
VOID FMD_PowerDown(VOID);

/* FMD_PowerUp  [function; ce-only; CE 4.0..699] */
VOID FMD_PowerUp(VOID);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* FMD_GetInfoEx  [function; ce-only; CE 6.0..699] */
BOOL FMD_GetInfoEx(
 PFlashInfoEx pFlashInfo,
 PDWORD pdwNumRegions
);
#endif /* _WIN32_WCE */

#endif /* _FMD_ */
