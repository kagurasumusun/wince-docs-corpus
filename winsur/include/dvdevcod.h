/* dvdevcod.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 27 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _DVDEVCOD_
#define _DVDEVCOD_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define EC_DVD_ANGLE_CHANGE 0x0106
#define EC_DVD_ANGLES_AVAILABLE 0x0113
#define EC_DVD_AUDIO_STREAM_CHANGE 0x0104
#define EC_DVD_BUTTON_AUTO_ACTIVATED 0x0115
#define EC_DVD_BUTTON_CHANGE 0x0107
#define EC_DVD_CHAPTER_AUTOSTOP 0x010E
#define EC_DVD_CHAPTER_START 0x0103
#define EC_DVD_CMD_END 0x0117
#define EC_DVD_CMD_START 0x0116
#define EC_DVD_CURRENT_HMSF_TIME 0x011A
#define EC_DVD_CURRENT_TIME 0x010B
#define EC_DVD_DISC_EJECTED 0x0118
#define EC_DVD_DISC_INSERTED 0x0119
#define EC_DVD_DOMAIN_CHANGE 0x0101
#define EC_DVD_ERROR 0x010C
#define EC_DVD_KARAOKE_MODE 0x011B
#define EC_DVD_NO_FP_PGC 0x010F
#define EC_DVD_PARENTAL_LEVEL_CHANGE 0x0111
#define EC_DVD_PLAYBACK_RATE_CHANGE 0x0110
#define EC_DVD_PLAYBACK_STOPPED 0x0112
#define EC_DVD_PLAYPERIOD_AUTOSTOP 0x0114
#define EC_DVD_STILL_OFF 0x010A
#define EC_DVD_STILL_ON 0x0109
#define EC_DVD_SUBPICTURE_STREAM_CHANGE 0x0105
#define EC_DVD_TITLE_CHANGE 0x0102
#define EC_DVD_VALID_UOPS_CHANGE 0x0108
#define EC_DVD_WARNING 0x010D

#endif /* _DVDEVCOD_ */
