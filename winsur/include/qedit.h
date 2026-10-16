/* qedit.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 20 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _QEDIT_
#define _QEDIT_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CONNECTF_DYNAMIC_EFFECTS 0x02
#define CONNECTF_DYNAMIC_NONE 0x00
#define CONNECTF_DYNAMIC_SOURCES 0x01
#define E_MUST_INIT_RENDERER 0x80040402
#define E_NO_TIMELINE 0x80040404
#define E_NOTDETERMINED 0x80040403
#define E_NOTINTREE 0x80040400
#define E_RENDER_ENGINE_IS_BROKEN 0x80040401
#define RESIZEF_CROP 1
#define RESIZEF_PRESERVEASPECTRATIO 2
#define RESIZEF_PRESERVEASPECTRATIO_NOLETTERBOX 3
#define RESIZEF_STRETCH 0
#define S_WARN_OUTPUTRESET 0x00009DD4
#define SFN_VALIDATEF_CHECK 0x01
#define SFN_VALIDATEF_IGNOREMUTED 0x40
#define SFN_VALIDATEF_NOFIND 0x20
#define SFN_VALIDATEF_POPUP 0x02
#define SFN_VALIDATEF_REPLACE 0x08
#define SFN_VALIDATEF_TELLME 0x04
#define SFN_VALIDATEF_USELOCAL 0x10

#endif /* _QEDIT_ */
