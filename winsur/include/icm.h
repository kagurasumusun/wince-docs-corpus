/* icm.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 48 constants, 0 declarations, 1 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _ICM_
#define _ICM_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ATTRIB_MATTE 2
#define ATTRIB_TRANSPARENCY 1
#define CLASS_ABSTRACT 0x61627374
#define CLASS_COLORSPAC 0x73706163
#define CLASS_LINK 0x6C696E6B
#define CLASS_MONITOR 0x6D6E7472
#define CLASS_NAMED 0x6E6D636C
#define CLASS_PRINTER 0x70727472
#define CLASS_SCANNER 0x73636E72
#define CMS_DISABLEICM 0x1
#define CMS_ENABLEPROOFING 0x2
#define CMS_MONITOROVERFLOW 0x80000000
#define CMS_PRINTERROVERFLOW 0x40000000
#define CMS_SETMONITORPROFILE 0x10
#define CMS_SETPRINTERPROFILE 0x20
#define CMS_SETPROOFINTENT 0x8
#define CMS_SETRENDERINTENT 0x4
#define CMS_SETTARGETPROFILE 0x40
#define CMS_TARGETOVERFLOW 0x20000000
#define CMS_USEAPPLYCALLBACK 0x100
#define CMS_USEDESCRIPTION 0x200
#define CMS_USEHOOK 0x80
#define COLOR_MATCH_VERSION 0x200
#define FLAG_DEPENDENTONDATA 2
#define FLAG_EMBEDDEDPROFILE 1
#define INTENT_ABSOLUTE_COLORIMETRIC 3
#define INTENT_PERCEPTUAL 0
#define INTENT_RELATIVE_COLORIMETRIC 1
#define INTENT_SATURATION 2
#define MAX_COLOR_CHANNELS 8
#define PROFILE_FILENAME 1
#define PROFILE_MEMBUFFER 2
#define PROFILE_READ 1
#define PROFILE_READWRITE 2
#define SPACE_2_CHANNEL 0x32434C52
#define SPACE_3_CHANNEL 0x33434C52
#define SPACE_4_CHANNEL 0x34434C52
#define SPACE_5_CHANNEL 0x35434C52
#define SPACE_6_CHANNEL 0x36434C52
#define SPACE_7_CHANNEL 0x37434C52
#define SPACE_8_CHANNEL 0x38434C52
#define SPACE_CMY 0x434D5920
#define SPACE_CMYK 0x434D594B
#define SPACE_GRAY 0x47524159
#define SPACE_HLS 0x484C5320
#define SPACE_HSV 0x48535620
#define SPACE_RGB 0x52474220
#define SPACE_XYZ 0x58595A20

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* PROFILE  [struct; shared; entity-headers] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   dwType */
/*   pProfileData */
/*   cbDataSize */

#endif /* _ICM_ */
