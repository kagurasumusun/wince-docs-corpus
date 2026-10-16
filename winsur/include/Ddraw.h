/* Ddraw.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 31 declarations, 0 outlines, 0 base types, 0 extra macros, 56 extra decls
 */
#ifndef _DDRAW_
#define _DDRAW_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DDARGB  [struct; ce-only] */
typedef struct _DDARGB{
 BYTE blue;
 BYTE green;
 BYTE red;
 BYTE alpha;
} DDARGB, *LPDDARGB;

/* DDCOLORCONTROL  [struct; shared] */
typedef struct _DDCOLORCONTROL {
 DWORD dwSize;
 DWORD dwFlags;
 LONG lBrightness;
 LONG lContrast;
 LONG lHue;
 LONG lSaturation;
 LONG lSharpness;
 LONG lGamma;
 LONG lColorEnable;
} DDCOLORCONTROL, FAR* LPDDCOLORCONTROL;

/* DDCOLORKEY  [struct; shared] */
typedef struct _DDCOLORKEY{ 
 DWORD dwColorSpaceLowValue; 
 DWORD dwColorSpaceHighValue; 
} DDCOLORKEY,FAR *LPDDCOLORKEY;

/* DDGAMMARAMP  [struct; shared] */
typedef struct _DDGAMMARAMP
{
 WORD red[256];
 WORD green[256];
 WORD blue[256];
}DDGAMMARAMP, *LPDDGAMMARAMP;

/* DDOVERLAYFX  [struct; shared] */
typedef struct _DDOVERLAYFX{ 
 DWORD dwSize; 
 DWORD dwAlphaConstBitDepth; 
 DWORD dwAlphaConst; 
 DDCOLORKEY dckDestColorkey; 
 DDCOLORKEY dckSrcColorkey; 
} DDOVERLAYFX,FAR *LPDDOVERLAYFX;

/* DDPIXELFORMAT  [struct; shared] */
typedef struct _DDPIXELFORMAT {
 DWORD dwSize;
 DWORD dwFlags;
 DWORD dwFourCC;
 union
 {
 DWORD dwRGBBitCount;
 DWORD dwYUVBitCount;
 DWORD dwAlphaBitDepth;
 };
 union
 {
 DWORD dwRBitMask;
 DWORD dwYBitMask;
 };
 union
 {
 DWORD dwGBitMask;
 DWORD dwUBitMask;
 };
 union
 {
 DWORD dwBBitMask;
 DWORD dwVBitMask;
 };
 union
 {
 DWORD dwRGBAlphaBitMask;
 };
} DDPIXELFORMAT, FAR* LPDDPIXELFORMAT;

/* DDSCAPS  [struct; shared] */
typedef struct _DDSCAPS{ 
 DWORD dwCaps; 
} DDSCAPS, FAR* LPDDSCAPS;

/* DDSCAPS2  [struct; shared] */
typedef struct _DDSCAPS2 { 
 DWORD dwCaps; 
 DWORD dwCaps2; 
 DWORD dwCaps3; 
 DWORD dwCaps4; 
} DDSCAPS2, FAR* LPDDSCAPS2;

/* DDSCAPSEX  [struct; ce-only] */
typedef struct _DDSCAPSEX { 
 DWORD dwCaps2; 
 DWORD dwCaps3; 
 DWORD dwCaps4; 
} DDSCAPSEX, FAR* LPDDSCAPSEX;

/* DDSURFACEDESC  [struct; shared] */
typedef struct _DDSURFACEDESC {
 DWORD dwSize;
 DWORD dwFlags;
 DWORD dwHeight;
 DWORD dwWidth;
 LONG lPitch;
 LONG lXPitch;
 DWORD dwBackBufferCount;
 DWORD dwRefreshRate;
 LPVOID lpSurface;
 DDCOLORKEY ddckCKDestOverlay;
 DDCOLORKEY ddckCKDestBlt;
 DDCOLORKEY ddckCKSrcOverlay;
 DDCOLORKEY ddckCKSrcBlt;
 DDPIXELFORMAT ddpfPixelFormat;
 DDSCAPS ddsCaps;
 DWORD dwSurfaceSize;
} DDSURFACEDESC, FAR* LPDDSURFACEDESC;

/* DDSURFACEDESC2  [struct; shared] */
typedef struct _DDSURFACEDESC2 { 
 DWORD dwSize; 
 DWORD dwFlags; 
 DWORD dwHeight; 
 DWORD dwWidth; 
 union 
 { 
 LONG lPitch; 
 DWORD dwLinearSize; 
 } DUMMYUNIONNAMEN(1); 
 DWORD dwBackBufferCount; 
 union 
 { 
 DWORD dwMipMapCount; 
 DWORD dwRefreshRate; 
 } DUMMYUNIONNAMEN(2); 
 DWORD dwAlphaBitDepth; 
 DWORD dwReserved; 
 LPVOID lpSurface; 
 DDCOLORKEY ddckCKDestOverlay; 
 DDCOLORKEY ddckCKDestBlt; 
 DDCOLORKEY ddckCKSrcOverlay; 
 DDCOLORKEY ddckCKSrcBlt; 
 DDPIXELFORMAT ddpfPixelFormat; 
 DDSCAPS2 ddsCaps; 
 DWORD dwTextureStage; 
} DDSURFACEDESC2, FAR* LPDDSURFACEDESC2;

/* DDALPHABLTFX  [typedef; ce-only] */
typedef union _DDALPHABLTFX {
 DWORD dwSize;
 DDARGB ddargbScaleFactors;
 DWORD dwFillValue;
} DDALPHABLTFX, FAR * LPDDALPHABLTFX;

/* DDBLTFX  [struct; shared] */
typedef struct _DDBLTFX{ 
 DWORD dwSize; 
 DWORD dwROP; 
 DWORD dwFillColor; 
 DDCOLORKEY ddckDestColorkey; 
 DDCOLORKEY ddckSrcColorkey; 
} DDBLTFX,FAR* LPDDBLTFX;

/* LPDIRECTDRAWCLIPPER  [extra struct] */
typedef struct IDirectDrawClipper FAR *LPDIRECTDRAWCLIPPER;

/* LPDIRECTDRAWCOLORCONTROL  [extra struct] */
typedef struct IDirectDrawColorControl FAR *LPDIRECTDRAWCOLORCONTROL;

/* LPDIRECTDRAWPALETTE  [extra struct] */
typedef struct IDirectDrawPalette FAR *LPDIRECTDRAWPALETTE;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x600)) /* CE 3.0..599 */

/* EnumModesCallback2  [function; ce-only; CE 3.0..599] */
HRESULT WINAPI EnumModesCallback( 
 LPDDSURFACEDESC2 lpDDSurfaceDesc, 
 LPVOID lpContext 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* EnumModesCallback  [function; ce-only; CE 3.0..699] */
HRESULT WINAPI EnumModesCallback(
 LPDDSURFACEDESC lpDDSurfaceDesc, 
 LPVOID lpContext
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT AddOverlayDirtyRect( LPRECT lpRect);
HRESULT ChangeUniquenessValue();
HRESULT Compact();
HRESULT FlipToGDISurface();
HRESULT GetAvailableVidMem( LPDDSCAPS2 lpDDSCaps2, LPDWORD lpdwTotal, LPDWORD lpdwFree);
HRESULT GetClipper( LPDIRECTDRAWCLIPPER FAR *lplpDDClipper);
HRESULT GetColorControls( LPDDCOLORCONTROL lpColorControl);
HRESULT GetColorKey( DWORD dwFlags, LPDDCOLORKEY lpDDColorKey);
HRESULT GetDDInterface( LPVOID FAR *lplpDD);
HRESULT GetDeviceIdentifier( LPDDDEVICEIDENTIFIER lpdddi, DWORD dwFlags);
HRESULT GetDisplayMode( LPDDSURFACEDESC2 lpDDSurfaceDesc2);
HRESULT GetEntries( DWORD dwFlags, DWORD dwBase, DWORD dwNumEntries, LPPALETTEENTRY lpEntries);
HRESULT GetFourCCCodes( LPDWORD lpNumCodes, LPDWORD lpCodes);
HRESULT GetHWnd( HWND FAR *lphWnd);
HRESULT GetMonitorFrequency( LPDWORD lpdwFrequency);
HRESULT GetOverlayPosition( LPLONG lplX, LPLONG lplY);
HRESULT GetPalette( LPDIRECTDRAWPALETTE FAR *lplpDDPalette);
HRESULT GetScanLine( LPDWORD lpdwScanLine);
HRESULT GetSurfaceDesc( LPDDSURFACEDESC2 lpDDSurfaceDesc);
HRESULT GetUniquenessValue( LPDWORD lpValue,);
HRESULT GetVerticalBlankStatus( LPBOOL lpbIsInVB);
HRESULT IsClipListChanged( BOOL FAR *lpbChanged);
HRESULT IsLost();
HRESULT PageLock( DWORD dwFlags);
HRESULT PageUnlock( DWORD dwFlags);
HRESULT Restore();
HRESULT RestoreAllSurfaces();
HRESULT RestoreDisplayMode();
HRESULT SetClipper( LPDIRECTDRAWCLIPPER lpDDClipper);
HRESULT SetColorControls( LPDDCOLORCONTROL lpColorControl);
HRESULT SetCooperativeLevel( HWND hWnd, DWORD dwFlags);
HRESULT SetDisplayMode( DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, DWORD dwRefreshRate, DWORD dwFlags);
HRESULT SetHWnd( DWORD dwFlags, HWND hWnd);
HRESULT SetSurfaceDesc( LPDDSURFACEDESC2 lpddsd2, DWORD dwFlags);
HRESULT TestCooperativeLevel(void);

#endif /* _DDRAW_ */
