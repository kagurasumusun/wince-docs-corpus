/* csmedia.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 27 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CSMEDIA_
#define _CSMEDIA_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CS_BITMAPINFOHEADER  [struct; ce-only] */
typedef struct tagCS_BITMAPINFOHEADER{
 DWORD biSize;
 LONG biWidth;
 LONG biHeight;
 WORD biPlanes;
 WORD biBitCount;
 DWORD biCompression;
 DWORD biSizeImage;
 LONG biXPelsPerMeter;
 LONG biYPelsPerMeter;
 DWORD biClrUsed;
 DWORD biClrImportant;
} CS_BITMAPINFOHEADER, *PCS_BITMAPINFOHEADER;

/* CS_CompressionCaps  [enum; ce-only] */
typedef enum {
 CS_CompressionCaps_CanQuality = 1,
 CS_CompressionCaps_CanCrunch = 2,
 CS_CompressionCaps_CanKeyFrame = 4,
 CS_CompressionCaps_CanBFrame = 8,
 CS_CompressionCaps_CanWindow = 0x10,
} CS_CompressionCaps;
typedef CS_CompressionCaps *PCS_CompressionCaps, *LPCS_CompressionCaps;

/* CS_FRAME_INFO  [struct; ce-only] */
typedef struct tagCS_FRAME_INFO {
 ULONG ExtendedHeaderSize;
 DWORD dwFrameFlags;
 LONGLONG PictureNumber;
 LONGLONG DropCount;
 HANDLE hDirectDraw;
 HANDLE hSurfaceHandle;
 RECT DirectDrawRect;
 DWORD Reserved1;
 DWORD Reserved2;
 DWORD Reserved3;
 DWORD Reserved4;
} CS_FRAME_INFO, *PCS_FRAME_INFO;

/* CS_RGBQUAD  [struct; ce-only] */
typedef struct tagCS_RGBQUAD {
 BYTE rgbBlue;
 BYTE rgbGreen;
 BYTE rgbRed;
 BYTE rgbReserved;
} CS_RGBQUAD, *PCS_RGBQUAD;

/* CS_TRUECOLORINFO  [struct; ce-only] */
typedef struct tag_CS_TRUECOLORINFO {
 DWORD dwBitMasks[CS_iMASK_COLORS];
 CS_RGBQUAD bmiColors[CS_iPALETTE_COLORS];
} CS_TRUECOLORINFO, *PCS_TRUECOLORINFO;

/* CS_VideoControlFlags  [enum; ce-only] */
typedef enum {
 CS_VideoControlFlag_FlipHorizontal = 0x0001,
 CS_VideoControlFlag_FlipVertical = 0x0002,
 CS_Obsolete_VideoControlFlag_ExternalTriggerEnable = 0x0010,
 CS_Obsolete_VideoControlFlag_Trigger = 0x0020,
 CS_VideoControlFlag_ExternalTriggerEnable = 0x0004,
 CS_VideoControlFlag_Trigger = 0x0008,
} CS_VideoControlFlags;
typedef CS_VideoControlFlags *PCS_VideoControlFlags, *LPCS_VideoControlFlags;

/* CSPROPERTY_VIDCAP_CAMERACONTROL  [enum; ce-only] */
typedef enum {
 CSPROPERTY_CAMERACONTROL_PAN,
 CSPROPERTY_CAMERACONTROL_TILT,
 CSPROPERTY_CAMERACONTROL_ROLL,
 CSPROPERTY_CAMERACONTROL_ZOOM,
 CSPROPERTY_CAMERACONTROL_EXPOSURE,
 CSPROPERTY_CAMERACONTROL_IRIS,
 CSPROPERTY_CAMERACONTROL_FOCUS,
 CSPROPERTY_CAMERACONTROL_FLASH
} CSPROPERTY_VIDCAP_CAMERACONTROL;
typedef CSPROPERTY_VIDCAP_CAMERACONTROL *PCSPROPERTY_VIDCAP_CAMERACONTROL, *LPCSPROPERTY_VIDCAP_CAMERACONTROL;

/* CSPROPERTY_VIDCAP_DROPPEDFRAMES  [enum; ce-only] */
typedef enum {
 CSPROPERTY_DROPPEDFRAMES_CURRENT
} CSPROPERTY_VIDCAP_DROPPEDFRAMES;
typedef CSPROPERTY_VIDCAP_DROPPEDFRAMES *PCSPROPERTY_VIDCAP_DROPPEDFRAMES, *LPCSPROPERTY_VIDCAP_DROPPEDFRAMES;

/* CSPROPERTY_VIDCAP_VIDEOCOMPRESSION  [enum; ce-only] */
typedef enum {
 CSPROPERTY_VIDEOCOMPRESSION_GETINFO,
 CSPROPERTY_VIDEOCOMPRESSION_KEYFRAME_RATE,
 CSPROPERTY_VIDEOCOMPRESSION_PFRAMES_PER_KEYFRAME,
 CSPROPERTY_VIDEOCOMPRESSION_QUALITY,
 CSPROPERTY_VIDEOCOMPRESSION_OVERRIDE_KEYFRAME,
 CSPROPERTY_VIDEOCOMPRESSION_OVERRIDE_FRAME_SIZE,
 CSPROPERTY_VIDEOCOMPRESSION_WINDOWSIZE,
} CSPROPERTY_VIDCAP_VIDEOCOMPRESSION;
typedef CSPROPERTY_VIDCAP_VIDEOCOMPRESSION *PCSPROPERTY_VIDCAP_VIDEOCOMPRESSION, *LPCSPROPERTY_VIDCAP_VIDEOCOMPRESSION;

/* CSPROPERTY_VIDCAP_VIDEOCONTROL  [enum; ce-only] */
typedef enum {
 CSPROPERTY_VIDEOCONTROL_CAPS,
 CSPROPERTY_VIDEOCONTROL_ACTUAL_FRAME_RATE,
 CSPROPERTY_VIDEOCONTROL_FRAME_RATES,
 CSPROPERTY_VIDEOCONTROL_MODE
} CSPROPERTY_VIDCAP_VIDEOCONTROL;
typedef CSPROPERTY_VIDCAP_VIDEOCONTROL *PCSPROPERTY_VIDCAP_VIDEOCONTROL, *LPCSPROPERTY_VIDCAP_VIDEOCONTROL;

/* CSPROPERTY_VIDCAP_VIDEOPROCAMP  [enum; ce-only] */
typedef enum {
 CSPROPERTY_VIDEOPROCAMP_BRIGHTNESS,
 CSPROPERTY_VIDEOPROCAMP_CONTRAST,
 CSPROPERTY_VIDEOPROCAMP_HUE,
 CSPROPERTY_VIDEOPROCAMP_SATURATION,
 CSPROPERTY_VIDEOPROCAMP_SHARPNESS,
 CSPROPERTY_VIDEOPROCAMP_GAMMA,
 CSPROPERTY_VIDEOPROCAMP_COLORENABLE,
 CSPROPERTY_VIDEOPROCAMP_WHITEBALANCE,
 CSPROPERTY_VIDEOPROCAMP_BACKLIGHT_COMPENSATION,
 CSPROPERTY_VIDEOPROCAMP_GAIN,
} CSPROPERTY_VIDCAP_VIDEOPROCAMP;
typedef CSPROPERTY_VIDCAP_VIDEOPROCAMP *PCSPROPERTY_VIDCAP_VIDEOPROCAMP, *LPCSPROPERTY_VIDCAP_VIDEOPROCAMP;

/* CSSTREAM_ALLOCATOR  [struct; ce-only] */
typedef struct {
 ULONG DesiredCount;
 ULONG ActualCount;
 LPVOID pBuffers;
} CSSTREAM_ALLOCATOR, * PCSSTREAM_ALLOCATOR;

#endif /* _CSMEDIA_ */
