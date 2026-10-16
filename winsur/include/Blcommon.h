/* Blcommon.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 3 constants, 16 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _BLCOMMON_
#define _BLCOMMON_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define BL_DOWNLOAD 0
#define BL_ERROR -1
#define BL_JUMP 1

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* BootloaderMain  [function; ce-only; CE 4.0..699; Blcommon.lib, blcommon.lib] */
void BootloaderMain (void);

/* OEMCheckSignature  [function; ce-only; CE 4.0..699; Blcommon.lib, blcommon.lib] */
BOOL OEMCheckSignature(
 DWORD dwImageStart,
 DWORD dwROMOffset,
 DWORD dwLaunchAddr,
 BOOL bDownloaded
);

/* OEMContinueEraseFlash  [function; ce-only; CE 4.0..699; Blcommon.lib, blcommon.lib] */
void OEMContinueEraseFlash (void);

/* OEMDebugInit  [function; ce-only; CE 4.0..699; Blcommon.lib, blcommon.lib] */
BOOL OEMDebugInit (void);

/* OEMFinishEraseFlash  [function; ce-only; CE 4.0..699; Blcommon.lib, blcommon.lib] */
BOOL OEMFinishEraseFlash (void);

/* OEMIsFlashAddr  [function; ce-only; CE 4.0..699; Blcommon.lib, blcommon.lib] */
BOOL OEMIsFlashAddr(
 DWORD dwAddr
);

/* OEMMapMemAddr  [function; ce-only; CE 4.0..699; Blcommon.lib, blcommon.lib] */
LPBYTE OEMMapMemAddr(
 DWORD dwImageStart,
 DWORD dwAddr
);

/* OEMMultiBINNotify  [function; ce-only; CE 4.0..699; Blcommon.lib, blcommon.lib] */
void OEMMultiBINNotify(
 const PMultiBINInfo pInfo
);

/* OEMPlatformInit  [function; ce-only; CE 4.0..699; Blcommon.lib, blcommon.lib] */
BOOL OEMPlatformInit (void);

/* OEMPreDownload  [function; ce-only; CE 4.0..699; Blcommon.lib, blcommon.lib] */
DWORD OEMPreDownload (void);

/* OEMReadData  [function; ce-only; CE 4.0..699; Blcommon.lib, blcommon.lib] */
BOOL OEMReadData(
 DWORD cbData,
 LPBYTE pbData
);

/* OEMShowProgress  [function; ce-only; CE 4.0..699; Blcommon.lib, blcommon.lib] */
void OEMShowProgress(
 DWORD dwPacketNum
);

/* OEMStartEraseFlash  [function; ce-only; CE 4.0..699; Blcommon.lib, blcommon.lib] */
BOOL OEMStartEraseFlash(
 DWORD dwStartAddr,
 DWORD dwLength
);

/* OEMVerifyMemory  [function; ce-only; CE 4.0..699; Blcommon.lib, blcommon.lib] */
BOOL OEMVerifyMemory(
 DWORD dwStartAddr,
 DWORD dwLength
);

/* OEMWriteFlash  [function; ce-only; CE 4.0..699; Blcommon.lib, blcommon.lib] */
BOOL OEMWriteFlash(
 DWORD dwStartAddr,
 DWORD dwLength
);
#endif /* _WIN32_WCE */

#endif /* _BLCOMMON_ */
