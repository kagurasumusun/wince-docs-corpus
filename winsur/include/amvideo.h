/* amvideo.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 17 constants, 0 declarations, 1 outlines, 0 base types, 0 extra macros, 12 extra decls
 */
#ifndef _AMVIDEO_
#define _AMVIDEO_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define AMDDS_ ALL
#define AMDDS_DCIPS 0x01
#define AMDDS_DEFAULT 0xFF
#define AMDDS_NONE 0x00
#define AMDDS_PRIMARY 0x03
#define AMDDS_PS 0x02
#define AMDDS_RGB 0x58
#define AMDDS_RGBFLP 0x40
#define AMDDS_RGBOFF 0x10
#define AMDDS_RGBOVR 0x04
#define AMDDS_YUV 0xA8
#define AMDDS_YUVFLP 0x80
#define AMDDS_YUVOFF 0x20
#define AMDDS_YUVOVR 0x08
#define SIZE_EGA_PALETTE (16*sizeof(RGBQUAD))
#define SIZE_MASKS (3*sizeof(DWORD))
#define SIZE_PALETTE (256*sizeof(RGBQUAD))

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* HEADER  [function, struct, typedef; shared; entity-headers] */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT CanUseOverlayStretch( long *UseOverlayStretch);
HRESULT CanUseScanLine( long *UseScanLine);
HRESULT GetSurfaceType( DWORD *pSurfaceType);
HRESULT GetSwitches( DWORD *pSwitches);
HRESULT SetDefault( );
HRESULT SetSwitches( DWORD pSwitches);
HRESULT UseOverlayStretch( long UseOverlayStretch);
HRESULT UseScanLine( long UseScanLine);
HRESULT UseWhenFullScreen( long UseWhenFullScreen);
HRESULT WillUseFullScreen( long *UseWhenFullScreen);

#endif /* _AMVIDEO_ */
