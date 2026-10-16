/* Docobj.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 5 constants, 0 declarations, 1 outlines, 0 base types, 0 extra macros, 2 extra decls
 */
#ifndef _DOCOBJ_
#define _DOCOBJ_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define OLECMDERR_E_CANCELED (-2147221245)
#define OLECMDERR_E_DISABLED (-2147221247)
#define OLECMDERR_E_NOHELP (-2147221246)
#define OLECMDERR_E_NOTSUPPORTED (-2147221248)
#define OLECMDERR_E_UNKNOWNGROUP (-2147221244)

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 5.0..599 */

/* IContinueCallback  [interface; shared; CE 5.0..599] */
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT FContinue(void);

#endif /* _DOCOBJ_ */
