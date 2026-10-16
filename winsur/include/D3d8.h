/* D3d8.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 9 outlines, 0 base types, 0 extra macros, 17 extra decls
 */
#ifndef _D3D8_
#define _D3D8_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* IDirect3D8  [struct; ce-only; D3d8.lib] */

/* IDirect3DBaseTexture8  [struct; ce-only; D3d8.lib] */

/* IDirect3DDevice8  [struct; ce-only; D3d8.lib] */

/* IDirect3DIndexBuffer8  [struct; ce-only; D3d8.lib] */

/* IDirect3DResource8  [struct; ce-only; D3d8.lib] */

/* IDirect3DSurface8  [struct; ce-only; D3d8.lib] */

/* IDirect3DSwapChain8  [struct; ce-only; D3d8.lib] */

/* IDirect3DTexture8  [struct; ce-only; D3d8.lib] */

/* IDirect3DVertexBuffer8  [struct; ce-only; D3d8.lib] */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT ApplyStateBlock( DWORD Token );
HRESULT BeginStateBlock();
HRESULT CaptureStateBlock( DWORD Token );
HRESULT DeleteStateBlock( DWORD Token );
HRESULT EndStateBlock( DWORD* pToken );
HMONITOR GetAdapterMonitor( UINT Adapter );
UINT GetAvailableTextureMem();
HRESULT GetClipPlane( DWORD Index, float* pPlane );
HRESULT GetVertexShader( DWORD* pHandle );
HRESULT SetClipPlane( DWORD Index, CONST float* pPlane );

#endif /* _D3D8_ */
