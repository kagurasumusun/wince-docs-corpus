/* errors.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 33 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _ERRORS_
#define _ERRORS_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define MAX_ERROR_TEXT_LEN 160
#define VFW_E_CERTIFICATION_FAILURE 0x80040295
#define VFW_E_COPYPROT_FAILED 0x8004027D
#define VFW_E_DDRAW_VERSION_NOT_SUITABLE 0x8004027C
#define VFW_E_DVD_CMD_CANCELLED 0x80040283
#define VFW_E_DVD_INCOMPATIBLE_REGION 0x80040287
#define VFW_E_DVD_INVALID_DISC 0x80040291
#define VFW_E_DVD_LOW_PARENTAL_LEVEL 0x8004028A
#define VFW_E_DVD_MENU_DOES_NOT_EXIST 0x80040282
#define VFW_E_DVD_NO_ATTRIBUTES 0x80040288
#define VFW_E_DVD_NO_GOUP_PGC 0x80040289
#define VFW_E_DVD_NO_RESUME_INFORMATION 0x80040292
#define VFW_E_DVD_NOT_IN_KARAOKE_MODE 0x8004028B
#define VFW_E_DVD_STATE_CORRUPT 0x80040285
#define VFW_E_DVD_STATE_WRONG_DISC 0x80040286
#define VFW_E_DVD_STATE_WRONG_VERSION 0x80040284
#define VFW_E_DVD_STREAM_DISABLED 0x8004028F
#define VFW_E_DVD_TITLE_UNKNOWN 0x80040290
#define VFW_E_DVD_VMR9_INCOMPATIBLEDEC 0x8004029A
#define VFW_E_DVD_WRONG_SPEED 0x80040281
#define VFW_E_FRAME_STEP_UNSUPPORTED 0x8004028E
#define VFW_E_NO_COPP_HW 0x8004029B
#define VFW_E_PIN_ALREADY_BLOCKED 0x80040294
#define VFW_E_PIN_ALREADY_BLOCKED_ON_THIS_THREAD 0x80040293
#define VFW_E_TIME_EXPIRED 0x8004027F
#define VFW_E_VMR_NO_AP_SUPPLIED 0x80040297
#define VFW_E_VMR_NO_DEINTERLACE_HW 0x80040298
#define VFW_E_VMR_NO_PROCAMP_HW 0x80040299
#define VFW_E_VMR_NOT_IN_MIXER_MODE 0x80040296
#define VFW_S_DVD_CHANNEL_CONTENTS_NOT_AVAILABLE 0x0004028C
#define VFW_S_DVD_NON_ONE_SEQUENTIAL 0x00040280
#define VFW_S_DVD_NOT_ACCURATE 0x0004028D
#define VFW_S_NOPREVIEWPIN 0x0004027E

#endif /* _ERRORS_ */
