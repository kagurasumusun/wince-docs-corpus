/* basetyps.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 19 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _BASETYPS_
#define _BASETYPS_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define EXTERN_C extern
#define GUID_EXT EXTERN_C
#define GUID_SECT __attribute__
#define GUID_SECTION ".text"
#define PURE =0
#define REFCLSID const
#define REFFMTID const
#define REFGUID const
#define REFIID const
#define STDAPI EXTERN_C
#define STDAPICALLTYPE __stdcall
#define STDAPIV EXTERN_C
#define STDAPIVCALLTYPE __cdecl
#define STDMETHODCALLTYPE __stdcall
#define STDMETHODIMP HRESULT
#define STDMETHODIMPV HRESULT
#define STDMETHODVCALLTYPE __cdecl
#define THIS void
#define THIS_ INTERFACE

#endif /* _BASETYPS_ */
