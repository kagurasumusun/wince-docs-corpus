/* D3dx8math.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 8 declarations, 4 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _D3DX8MATH_
#define _D3DX8MATH_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* D3DXMATRIX  [struct; ce-only] */

/* D3DXToDegree  [macro; ce-only] */

/* D3DXToRadian  [macro; ce-only] */

/* D3DXVECTOR3  [struct; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* D3DXVECTOR4  [struct; ce-only] */
typedef struct D3DXVECTOR4 {
 FLOAT x, y, z, w;
} D3DXVECTOR4;
typedef D3DXVECTOR4 *PD3DXVECTOR4, *LPD3DXVECTOR4;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x500)) /* CE 4.0..499 */

/* D3DXVec4Dot  [function; ce-only; CE 4.0..499; D3dx8.lib] */
FLOAT D3DXVec4Dot(
 CONST D3DXVECTOR4* pV1,
 CONST D3DXVECTOR4* pV2
);

/* D3DXVec4Length  [function; ce-only; CE 4.0..499; D3dx8.lib] */
FLOAT D3DXVec4Length(
 CONST D3DXVECTOR4* pV
);

/* D3DXVec4LengthSq  [function; ce-only; CE 4.0..499; D3dx8.lib] */
FLOAT D3DXVec4LengthSq(
 CONST D3DXVECTOR4* pV
);
#endif /* _WIN32_WCE */

#endif /* _D3DX8MATH_ */
