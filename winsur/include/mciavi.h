/* mciavi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 18 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _MCIAVI_
#define _MCIAVI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define MCI_AVI_SETVIDEO_DRAW_PROCEDURE 0x8000
#define MCI_AVI_SETVIDEO_PALETTE_COLOR 0x8100
#define MCI_AVI_SETVIDEO_PALETTE_HALFTONE 0x0000FFFF
#define MCI_AVI_STATUS_AUDIO_BREAKS 0x8003
#define MCI_AVI_STATUS_FRAMES_SKIPPED 0x8001
#define MCI_AVI_STATUS_LAST_PLAY_SPEED 0x8002
#define MCI_MCIAVI_PLAY_FULLBY2 0x4000000
#define MCI_MCIAVI_PLAY_FULLSCREEN 0x2000000
#define MCI_MCIAVI_PLAY_WINDOW 0x1000000
#define MCIERR_AVI_AUDIOERROR (MCIERR_CUSTOM_DRIVER_BASE+107)
#define MCIERR_AVI_BADPALETTE (MCIERR_CUSTOM_DRIVER_BASE+108)
#define MCIERR_AVI_CANTPLAYFULLSCREEN (MCIERR_CUSTOM_DRIVER_BASE+103)
#define MCIERR_AVI_DISPLAYERROR (MCIERR_CUSTOM_DRIVER_BASE+106)
#define MCIERR_AVI_NOCOMPRESSOR (MCIERR_CUSTOM_DRIVER_BASE+105)
#define MCIERR_AVI_NODISPDIB (MCIERR_CUSTOM_DRIVER_BASE+102)
#define MCIERR_AVI_NOTINTERLEAVED (MCIERR_CUSTOM_DRIVER_BASE+101)
#define MCIERR_AVI_OLDAVIFORMAT (MCIERR_CUSTOM_DRIVER_BASE+100)
#define MCIERR_AVI_TOOBIGFORVGA (MCIERR_CUSTOM_DRIVER_BASE+104)

#endif /* _MCIAVI_ */
