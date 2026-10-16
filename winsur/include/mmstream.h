/* mmstream.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 3 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 5 extra decls
 */
#ifndef _MMSTREAM_
#define _MMSTREAM_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define COMPSTAT_ABORT 0x04
#define COMPSTAT_NOUPDATEOK 0x01
#define COMPSTAT_WAIT 0x02

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT CompletionStatus( DWORD dwFlags, DWORD dwMilliseconds);
HRESULT GetEndOfStreamEventHandle( HANDLE *phEOS);

#endif /* _MMSTREAM_ */
