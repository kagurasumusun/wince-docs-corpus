/* Snapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 3 constants, 0 declarations, 0 outlines, 0 base types, 4 extra macros, 0 extra decls
 */
#ifndef _SNAPI_
#define _SNAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define SN_ACTIVEAPPLICATION_ROOT HKEY_CURRENT_USER
#define SN_PHONENOSIM_BITMASK 2
#define SN_PHONENOSIM_ROOT HKEY_LOCAL_MACHINE

/* ==================================================================
 * macros -- supplementary #define from CE pages
 * ================================================================ */
#define SN_ACTIVEAPPLICATION_PATH TEXT("System\\State\\Shell")
#define SN_ACTIVEAPPLICATION_VALUE TEXT("Active Application")
#define SN_PHONENOSIM_PATH TEXT("System\\State\\Phone")
#define SN_PHONENOSIM_VALUE TEXT("Status")

#endif /* _SNAPI_ */
