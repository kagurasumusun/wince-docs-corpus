/* Ole2.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 18 constants, 6 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _OLE2_
#define _OLE2_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DATA_E_FORMATETC DV_E_FORMATETC
#define E_DRAW VIEW_E_DRAW
#define EMBDHLP_CREATENOW 0x00000000L
#define EMBDHLP_DELAYCREATE 0x00010000L
#define EMBDHLP_INPROC_HANDLER 0x0000L
#define EMBDHLP_INPROC_SERVER 0x0001L
#define OLEGETMONIKER_FORCEASSIGN 2
#define OLEGETMONIKER_ONLYIFTHERE 1
#define OLEGETMONIKER_TEMPFORUSER 4
#define OLEGETMONIKER_UNASSIGN 3
#define OLEIVERB_DISCARDUNDOSTATE -6
#define OLEIVERB_HIDE -3
#define OLEIVERB_INPLACEACTIVATE -5
#define OLEIVERB_OPEN -2
#define OLEIVERB_PRIMARY (0L)
#define OLEIVERB_SHOW -1
#define OLEIVERB_UIACTIVATE -4
#define OLELINKBIND_EVENIFCLASSDIFF 1

#endif /* _OLE2_ */
