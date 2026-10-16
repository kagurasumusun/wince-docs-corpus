/* adsprop.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 8 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _ADSPROP_
#define _ADSPROP_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define WM_ADSPROP_NOTIFY_APPLY (WM_USER+1104)
#define WM_ADSPROP_NOTIFY_CHANGE (WM_USER+1103)
#define WM_ADSPROP_NOTIFY_ERROR (WM_USER+1110)
#define WM_ADSPROP_NOTIFY_EXIT (WM_USER+1107)
#define WM_ADSPROP_NOTIFY_FOREGROUND (WM_USER+1106)
#define WM_ADSPROP_NOTIFY_PAGEHWND (WM_USER+1102)
#define WM_ADSPROP_NOTIFY_PAGEINIT (WM_USER+1101)
#define WM_ADSPROP_NOTIFY_SETFOCUS (WM_USER+1105)

#endif /* _ADSPROP_ */
