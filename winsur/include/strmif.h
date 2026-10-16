/* strmif.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 40 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _STRMIF_
#define _STRMIF_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CK_INDEX 0x00000001
#define CK_NOCOLORKEY 0x00000000
#define CK_RGB 0x00000002
#define DVD_AUDIO_CAPS_AC3 0x00000001
#define DVD_AUDIO_CAPS_DTS 0x00000008
#define DVD_AUDIO_CAPS_LPCM 0x00000004
#define DVD_AUDIO_CAPS_MPEG2 0x00000002
#define DVD_AUDIO_CAPS_SDDS 0x00000010
#define ED_FORMAT_SMPTE_24 0x00001199
#define ED_FORMAT_SMPTE_25 0x00001198
#define ED_FORMAT_SMPTE_30 0x00001196
#define ED_FORMAT_SMPTE_30DROP 0x00001197
#define KSAUDIO_SPEAKER_CENTER 0x00000004
#define KSAUDIO_SPEAKER_LEFT 0x00000001
#define KSAUDIO_SPEAKER_LEFT_OF_CENTER 0x00000040
#define KSAUDIO_SPEAKER_RIGHT 0x00000002
#define KSAUDIO_SPEAKER_RIGHT_OF_CENTER 0x00000080
#define KSAUDIO_SPEAKER_SIDE_LEFT 0x00000200
#define KSAUDIO_SPEAKER_SIDE_RIGHT 0x00000400
#define KSAUDIO_SPEAKER_SUBWOOFER 0x00000020
#define KSAUDIO_SPEAKER_SURROUND_LEFT 0x00000008
#define KSAUDIO_SPEAKER_SURROUND_MONO 0x00000100
#define KSAUDIO_SPEAKER_SURROUND_RIGHT 0x00000010
#define KSAUDIO_SPEAKER_TOP 0x00000800
#define MAX_FILTER_NAME 128
#define MAX_PIN_NAME 128
#define MPEG2_PROGRAM_DIRECTORY_PES_PACKET 0x00000002
#define MPEG2_PROGRAM_ELEMENTARY_STREAM 0x00000001
#define MPEG2_PROGRAM_PACK_HEADER 0x00000003
#define MPEG2_PROGRAM_PES_STREAM 0x00000004
#define MPEG2_PROGRAM_STREAM_MAP 0x00000000
#define MPEG2_PROGRAM_SYSTEM_HEADER 0x00000005
#define SUBSTREAM_FILTER_VAL_NONE 0x10000000
#define TVAUDIO_MODE_MASK 0x000000FF
#define TVAUDIO_PRESET_MASK 0x0000FF00
#define VMRBITMAP_DISABLE 0x00000001
#define VMRBITMAP_ENTIREDDS 0x00000004
#define VMRBITMAP_HDC 0x00000002
#define VMRBITMAP_SRCCOLORKEY 0x00000008
#define VMRBITMAP_SRCRECT 0x00000010

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* MPEG2Level  [enum, typedef; ce-only; heuristic-prefix] */
enum MPEG2Level {
 MPEG2Level_Low = 1,
 MPEG2Level_Main,
 MPEG2Level_High1440,
 MPEG2Level_High
};

/* MPEG2Profile  [enum, typedef; ce-only; heuristic-prefix] */
enum MPEG2Profile {
 MPEG2Profile_Simple = 1,
 MPEG2Profile_Main,
 MPEG2Profile_SNRScalable,
 MPEG2Profile_SpatiallyScalable,
 MPEG2Profile_High
};

/* StreamControlState  [enum, typedef; ce-only; heuristic-prefix] */
enum StreamControlState {
 STREAM_FLOWING,
 STREAM_DISCARDING
};

#endif /* _STRMIF_ */
