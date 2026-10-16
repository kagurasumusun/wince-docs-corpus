/* Rndismini.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 8 constants, 11 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _RNDISMINI_
#define _RNDISMINI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define REQ_ID_DEVICE_MACADDR 0x80000004
#define REQ_ID_DEVICE_MAX_RX 0x80000003
#define REQ_ID_DISABLE_INT 0x00000004
#define REQ_ID_ENABLE_INT 0x00000003
#define REQ_ID_HARD_RESET 0x00000001
#define REQ_ID_SOFT_RESET 0x00000002
#define REQ_ID_VENDOR_DESCRIPTION 0x80000002
#define REQ_ID_VENDOR_ID 0x80000001

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* PDDDeinit  [function; ce-only; CE 4.0..699] */
void pdddEINIT(void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* MDDAllocMem  [function; ce-only; CE 5.0..699] */
PBYTE MDDAllocMem(void);

/* MddDisconnect  [function; ce-only; CE 5.0..699] */
void MddDisconnect();

/* MDDFreeMem  [function; ce-only; CE 5.0..699] */
void MDDFreeMem(
 PBYTE pBuffer
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void MddSendRndisMessageComplete(PDATA_WRAPPER pDataWrapper);

#endif /* _RNDISMINI_ */
