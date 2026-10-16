/* d3dmx.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 62 declarations, 10 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _D3DMX_
#define _D3DMX_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* D3DMXMATRIX  [struct; ce-only] */

/* D3DMXMATRIXFXD  [struct; ce-only] */

/* D3DMXToDegree  [macro; ce-only] */

/* D3DMXToFixed  [macro; ce-only] */

/* D3DMXToFloat  [macro; ce-only] */

/* D3DMXToRadian  [macro; ce-only] */

/* D3DMXVECTOR3  [struct; ce-only] */

/* D3DMXVECTOR3FXD  [struct; ce-only] */

/* D3DMXVECTOR4  [struct; ce-only] */

/* D3DMXVECTOR4FXD  [struct; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* FIXED  [typedef, struct; shared] */
typedef int FIXED; // signed 15.16 fixed-point format

#endif /* _D3DMX_ */
