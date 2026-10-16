/* richole.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 29 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _RICHOLE_
#define _RICHOLE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define RECO_COPY 2
#define RECO_CUT 3
#define RECO_DRAG 4
#define RECO_DROP 1
#define RECO_PASTE 0
#define REO_BELOWBASELINE 2
#define REO_BLANK 16
#define REO_CP_SELECTION ((ULONG)-1)
#define REO_DONTNEEDPALETTE 32
#define REO_DYNAMICSIZE 8
#define REO_GETMETAFILE 0x400000
#define REO_GETOBJ_ALL_INTERFACES 7
#define REO_GETOBJ_NO_INTERFACES 0
#define REO_GETOBJ_POLEOBJ 1
#define REO_GETOBJ_POLESITE 4
#define REO_GETOBJ_PSTG 2
#define REO_HILITED 0x1000000
#define REO_INPLACEACTIVE 0x2000000
#define REO_INVERTEDSELECT 4
#define REO_IOB_SELECTION ((ULONG)-1)
#define REO_IOB_USE_CP ((ULONG)-2)
#define REO_LINK 0x80000000
#define REO_LINKAVAILABLE 0x800000
#define REO_NULL 0
#define REO_OPEN 0x4000000
#define REO_READWRITEMASK 0x3FL
#define REO_RESIZABLE 1
#define REO_SELECTED 0x08000000
#define REO_STATIC 0x40000000

#endif /* _RICHOLE_ */
