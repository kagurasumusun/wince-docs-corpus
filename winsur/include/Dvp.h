/* Dvp.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 8 declarations, 0 outlines, 0 base types, 0 extra macros, 13 extra decls
 */
#ifndef _DVP_
#define _DVP_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DDVIDEOPORTBANDWIDTH  [struct; shared] */
typedef struct _DDVIDEOPORTBANDWIDTH { 
 DWORD dwSize; 
 DWORD dwCaps; 
 DWORD dwOverlay; 
 DWORD dwColorkey; 
 DWORD dwYInterpolate; 
 DWORD dwYInterpAndColorkey; 
 DWORD dwReserved1; 
 DWORD dwReserved2; 
} DDVIDEOPORTBANDWIDTH, *LPDDVIDEOPORTBANDWIDTH;

/* DDVIDEOPORTCAPS  [struct; shared] */
typedef struct _DDVIDEOPORTCAPS { 
 DWORD dwSize; 
 DWORD dwFlags; 
 DWORD dwMaxWidth; 
 DWORD dwMaxVBIWidth; 
 DWORD dwMaxHeight; 
 DWORD dwVideoPortID; 
 DWORD dwCaps; 
 DWORD dwFX; 
 DWORD dwNumAutoFlipSurfaces; 
 DWORD dwAlignVideoPortBoundary; 
 DWORD dwAlignVideoPortPrescaleWidth; 
 DWORD dwAlignVideoPortCropBoundary; 
 DWORD dwAlignVideoPortCropWidth; 
 DWORD dwPreshrinkXStep; 
 DWORD dwPreshrinkYStep; 
 DWORD dwNumVBIAutoFlipSurfaces; 
 DWORD dwNumPreferredAutoflip; 
 WORD wNumFilterTapsX; 
 WORD wNumFilterTapsY; 
} DDVIDEOPORTCAPS, *LPDDVIDEOPORTCAPS;

/* LPDDVIDEOPORTCONTAINER  [extra struct] */
typedef struct IDDVideoPortContainer FAR *LPDDVIDEOPORTCONTAINER;

/* LPDIRECTDRAWVIDEOPORT  [extra struct] */
typedef struct IDirectDrawVideoPort FAR *LPDIRECTDRAWVIDEOPORT;

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT GetFieldPolarity( LPBOOL lpbFieldPolarity);
HRESULT GetVideoLine( LPDWORD lpdwLine);
HRESULT QueryVideoPortStatus( DWORD dwPortId, LPDDVIDEOPORTSTATUS lpVPStatus);
HRESULT StartVideo( LPDDVIDEOPORTINFO lpVideoInfo);
HRESULT StopVideo();
HRESULT UpdateVideo( LPDDVIDEOPORTINFO lpVideoInfo);

#endif /* _DVP_ */
