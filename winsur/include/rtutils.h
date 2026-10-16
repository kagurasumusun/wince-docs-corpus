/* rtutils.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 7 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _RTUTILS_
#define _RTUTILS_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define INVALID_TRACEID 0xFFFFFFFF
#define TRACE_NO_STDINFO 0x00000001
#define TRACE_NO_SYNCH 0x00000004
#define TRACE_USE_CONSOLE 0x00000002
#define TRACE_USE_FILE 0x00000001
#define TRACE_USE_MASK 0x00000002
#define TRACE_USE_MSEC 0x00000004

#endif /* _RTUTILS_ */
