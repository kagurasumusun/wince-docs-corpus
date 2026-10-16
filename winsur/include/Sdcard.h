/* Sdcard.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 5 constants, 5 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SDCARD_
#define _SDCARD_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define SDCARD_ZONE_ERROR 15
#define SDCARD_ZONE_FUNC 11
#define SDCARD_ZONE_INFO 12
#define SDCARD_ZONE_INIT 13
#define SDCARD_ZONE_WARN 14

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* BUILD_IO_RW_EXTENDED_ARG  [function; ce-only; CE 5.0..699] */
DWORD BUILD_IO_RW_EXTENDED_ARG(
 Read_Write,
 BlockMode,
 Function,
 Address,
 IncrementAddress,
 Count
);
#endif /* _WIN32_WCE */

#endif /* _SDCARD_ */
