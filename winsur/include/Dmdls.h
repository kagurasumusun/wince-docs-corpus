/* Dmdls.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 8 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _DMDLS_
#define _DMDLS_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DMUS_NOTERANGE  [struct; ce-only] */
typedef struct _DMUS_NOTERANGE {
DWORD dwLowNote;
DWORD dwHighNote;
} DMUS_NOTERANGE, *LPDMUS_NOTERANGE;

/* DMUS_WAVE  [struct; ce-only] */
typedef struct {
 ULONG ulFirstExtCkIdx;
 ULONG ulCopyrightIdx;
 ULONG ulWaveDataIdx;
 WAVEFORMATEX WaveformatEx;
} DMUS_WAVE;
typedef DMUS_WAVE *PDMUS_WAVE, *LPDMUS_WAVE;

/* DMUS_WAVEDATA  [struct; ce-only] */
typedef struct {
 ULONG cbSize;
 BYTE byData[ ];
} DMUS_WAVEDATA;
typedef DMUS_WAVEDATA *PDMUS_WAVEDATA, *LPDMUS_WAVEDATA;

#endif /* _DMDLS_ */
