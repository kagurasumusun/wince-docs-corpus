/* aviriff.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 10 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _AVIRIFF_
#define _AVIRIFF_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define AVIF_COPYRIGHTED 0x00020000
#define AVIF_HASINDEX 0x00000010
#define AVIF_ISINTERLEAVED 0x00000100
#define AVIF_MUSTUSEINDEX 0x00000020
#define AVIF_WASCAPTUREFILE 0x00010000
#define AVIIF_KEYFRAME 0x00000010
#define AVIIF_LIST 0x00000001
#define AVIIF_NO_TIME 0x00000100
#define AVISF_DISABLED 0x00000001
#define AVISF_VIDEO_PALCHANGES 0x00010000

#endif /* _AVIRIFF_ */
