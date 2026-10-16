/* winable.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 22 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WINABLE_
#define _WINABLE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CHILDID_SELF 0
#define GUI_CARETBLINKING 0x00000001
#define GUI_INMENUMODE 0x00000004
#define GUI_INMOVESIZE 0x00000002
#define GUI_POPUPMENUMODE 0x00000010
#define GUI_SYSTEMMENUMODE 0x00000008
#define OBJID_ALERT 0xFFFFFFF6
#define OBJID_CARET 0xFFFFFFF8
#define OBJID_CLIENT 0xFFFFFFFC
#define OBJID_CURSOR 0xFFFFFFF7
#define OBJID_HSCROLL 0xFFFFFFFA
#define OBJID_MENU 0xFFFFFFFD
#define OBJID_SIZEGRIP 0xFFFFFFF9
#define OBJID_SOUND 0xFFFFFFF5
#define OBJID_SYSMENU 0xFFFFFFFF
#define OBJID_TITLEBAR 0xFFFFFFFE
#define OBJID_VSCROLL 0xFFFFFFFB
#define OBJID_WINDOW 0x00000000
#define WINEVENT_INCONTEXT 0x0004
#define WINEVENT_OUTOFCONTEXT 0x0000
#define WINEVENT_SKIPOWNPROCESS 0x0002
#define WINEVENT_SKIPOWNTHREAD 0x0001

#endif /* _WINABLE_ */
