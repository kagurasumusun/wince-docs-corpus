/* dvdmedia.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 2 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _DVDMEDIA_
#define _DVDMEDIA_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define AMCONTROL_COLORINFO_PRESENT 0x00000008
#define AMCONTROL_USED 0x00000001

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* KS_AM_KSPROPSETID_TSRateChange  [enum; ce-only] */
typedef enum {
 KS_AM_RATE_SimpleRateChange=1,
 KS_AM_RATE_ExactRateChange=2,
 KS_AM_RATE_MaxFullDataRate=3,
 KS_AM_RATE_Step=4
} KS_AM_PROPERTY_TS_RATE_CHANGE;

#endif /* _DVDMEDIA_ */
