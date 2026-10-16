/* Tchaud.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _TCHAUD_
#define _TCHAUD_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* TOUCHPANEL_POINT_SAMPLE  [struct; ce-only] */
typedef struct { 
USHORT XSample; 
USHORT XzaSample; 
USHORT XzbSample; 
USHORT YSample; 
USHORT YzaSample; 
USHORT YzbSample; 
} TOUCHPANEL_POINT_SAMPLE;
typedef TOUCHPANEL_POINT_SAMPLE *PTOUCHPANEL_POINT_SAMPLE, *LPTOUCHPANEL_POINT_SAMPLE;

#endif /* _TCHAUD_ */
