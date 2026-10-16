/* exdispid.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 6 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 2 extra decls
 */
#ifndef _EXDISPID_
#define _EXDISPID_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DISPID_BEFORENAVIGATE2 250
#define DISPID_DOCUMENTCOMPLETE 259
#define DISPID_NEWWINDOW2 251
#define DISPID_PROGRESSCHANGE 108
#define DISPID_STATUSTEXTCHANGE 102
#define DISPID_TITLECHANGE 113

#endif /* _EXDISPID_ */
