/* D3dcaps.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _D3DCAPS_
#define _D3DCAPS_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* D3DLIGHTINGCAPS  [struct, typedef; ce-only] */
typedef struct _D3DLIGHTINGCAPS {
 DWORD dwSize;
 DWORD dwCaps;
 DWORD dwLightingModel; 
 DWORD dwNumLights;
} D3DLIGHTINGCAPS, *LPD3DLIGHTINGCAPS;

/* D3DPRIMCAPS  [struct, typedef; ce-only] */
typedef struct _D3DPrimCaps {
 DWORD dwSize;
 DWORD dwMiscCaps; 
 DWORD dwRasterCaps;
 DWORD dwZCmpCaps;
 DWORD dwSrcBlendCaps;
 DWORD dwDestBlendCaps;
 DWORD dwAlphaCmpCaps;
 DWORD dwShadeCaps;
 DWORD dwTextureCaps;
 DWORD dwTextureFilterCaps;
 DWORD dwTextureBlendCaps;
 DWORD dwTextureAddressCaps;
 DWORD dwStippleWidth; 
 DWORD dwStippleHeight; 
} D3DPRIMCAPS, *LPD3DPRIMCAPS;

/* D3DTRANSFORMCAPS  [struct, typedef; ce-only] */
typedef struct _D3DTRANSFORMCAPS {
 DWORD dwSize;
 DWORD dwCaps;
} D3DTRANSFORMCAPS, *LPD3DTRANSFORMCAPS;

#endif /* _D3DCAPS_ */
