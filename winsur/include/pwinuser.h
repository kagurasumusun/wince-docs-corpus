/* pwinuser.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 18 constants, 39 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _PWINUSER_
#define _PWINUSER_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ARG_SCROLL_DOWN 1
#define ARG_SCROLL_LEFT 2
#define ARG_SCROLL_NONE 0
#define ARG_SCROLL_RIGHT 4
#define ARG_SCROLL_UP 3
#define GF_BEGIN 0x00000001
#define GF_END 0x00000004
#define GF_INERTIA 0x00000002
#define GID_BEGIN 1
#define GID_END 2
#define GID_MAX 63
#define GID_PAN 4
#define GID_PRESSANDTAP 7
#define GID_ROTATE 5
#define GID_TWOFINGERTAP 6
#define GID_ZOOM 3
#define TGF_SCOPE_PROCESS 1
#define TGF_SCOPE_WINDOW 0

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* ANIMATEMESSAGEINFO  [struct; ce-only] */
typedef struct tagANIMATEMESSAGEINFO {
 size_t cbSize;
 DWORD dwAnimationID;
 int nVPixelPosition;
 int nHPixelPosition;
} ANIMATEMESSAGEINFO

/* GESTUREMETRICS  [struct; ce-only] */
typedef struct tagGESTUREMETRICS {
 UINT cbSize;
 DWORD dwID;
 DWORD dwTimeout;
 DWORD dwDistanceTolerance; 
 DWORD dwAngularTolerance;
 DWORD dwExtraInfo;
} GESTUREMETRICS, *LPGESTUREMETRICS;

/* GET_FOREGROUND_INFO  [struct; ce-only] */
typedef struct tagGetForegroundInfo {
 HWND hwndActive;
 HWND hwndFocus;
 HWND hwndMenu;
 HWND hwndKeyboardDest;
 DWORD fdwConversion;
 DWORD fdwSentence;
 BOOL fOpen;
 DWORD dwCompStrLen;
 HKL KeyboardLayoutHandle;
} GET_FOREGROUND_INFO;
typedef GET_FOREGROUND_INFO *PGET_FOREGROUND_INFO, *LPGET_FOREGROUND_INFO;

/* PHYSICSENGINEINIT  [struct; ce-only] */
typedef struct tagPHYSICSENGINEINIT {
 DWORD cbSize;
 DWORD dwEngineType;
 DWORD dwFlags;
 LONG lInitialVelocity; 
 DWORD dwInitialAngle;
 BYTE bXAxisMovementMode;
 BYTE bXAxisBoundaryMode;
 BYTE bYAxisMovementMode;
 BYTE bYAxisBoundaryMode;
 RECT rcBoundary;
 SIZE sizeView;
 POINT ptInitialPosition;
 SIZE sizeItem;
} PHYSICSENGINEINIT;
typedef PHYSICSENGINEINIT *PPHYSICSENGINEINIT, *LPPHYSICSENGINEINIT;

/* PHYSICSENGINESTATE  [struct; ce-only] */
typedef struct tagPHYSICSENGINESTATE {
 DWORD cbSize; 
 DWORD dwTime;
 POINT ptPosition;
 LONG lVelocityX;
 LONG lVelocityY;
 BOOL fComplete;
} PHYSICSENGINESTATE;
typedef PHYSICSENGINESTATE *PPHYSICSENGINESTATE, *LPPHYSICSENGINESTATE;

/* WAGINFO  [struct; ce-only] */
typedef struct tagWAGI {
 size_t cbSize;
 DWORD dwFlags;
 UINT nOwnerAnimateMessage;
 UINT nAnimateStatusMessage;
 HBRUSH hExtentBrush;
 UINT nItemHeight;
 UINT nItemWidth;
 BYTE bHorizontalExtent;
 BYTE bVerticalExtent;
} WAGINFO

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 1.0..199, 4.0..699 */

/* BatteryNotifyOfTimeChange  [function; ce-only; CE 1.0..199, 4.0..699; Coredll.lib, coredll.lib] */
void WINAPI BatteryNotifyOfTimeChange(
 BOOL fForward,
 FILETIME *pftDelta
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* NotifyWinUserSystem  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
void NotifyWinUserSystem(
 UINT uEvent
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* BatteryGetLifeTimeInfo  [function; ce-only; CE 3.0..699; Coredll.lib, coredll.lib] */
void BatteryGetLifeTimeInfo( 
 LPSYSTEMTIME pstLastChange, 
 DWORD* pcmsCpuUsage, 
 DWORD* pcmsPreviousCpuUsage 
);

/* RegisterTaskBar  [function; ce-only; CE 3.0..699; coredll.lib] */
BOOL RegisterTaskBar( 
 HWND hwndTaskbar 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* GwesPowerOffSystem  [function; ce-only; CE 4.0..699; Coredll.lib, coredll.lib] */
void GwesPowerOffSystem(void);

/* NLedGetDeviceInfo  [function; ce-only; CE 4.0..699; Coredll.dll, coredll.dll] */
BOOL WINAPI NLedGetDeviceInfo(
 UINT nInfoId,
 void* pOutput
);

/* NLedSetDevice  [function; ce-only; CE 4.0..699; Coredll.dll, coredll.dll] */
BOOL WINAPI NLedSetDevice(
 UINT nDeviceId,
 void* pInput
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* GetForegroundInfo  [function; ce-only; CE 5.0..699] */
BOOL WINAPI GetForegroundInfo(
 GET_FOREGROUND_INFO* pgfi
);

/* GetForegroundKeyboardLayoutHandle  [function; ce-only; CE 5.0..699] */
HKL GetForegroundKeyboardLayoutHandle( void );

/* GetForegroundKeyboardTarget  [function; ce-only; CE 5.0..699] */
HWND GetForegroundKeyboardTarget(void);

/* ImmGetConversionStatusForeground  [function; ce-only; CE 5.0..699] */
BOOL WINAPI ImmGetConversionStatusForeground(
 DWORD* pfdwConversion,
 DWORD* pfdwSentence
);

/* KeybdGetDeviceInfo  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL KeybdGetDeviceInfo(
 INT iIndex,
 LPVOID lpOutput 
);

/* RegisterDesktop  [function; ce-only; CE 5.0..699] */
BOOL RegisterDesktop( 
 HWND hwndDesktop
);

/* RegisterTaskBarEx  [function; ce-only; CE 5.0..699] */
BOOL RegisterTaskBarEx( 
 HWND hwndTaskbar,
 BOOL bTaskBarOnTop
);

/* TouchCalibrate  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL WINAPI TouchCalibrate(void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* DisableGestures  [function; ce-only; CE 6.0..699; TouchGesture.lib] */
BOOL DisableGestures(
 HWND hwnd,
 ULONGLONG ullFlags,
 UINT uScope
);

/* EnableGestures  [function; ce-only; CE 6.0..699; TouchGesture.lib] */
BOOL EnableGestures(
 HWND hwnd,
 ULONGLONG ullFlags,
 UINT uScope
);

/* GetAnimateMessageInfo  [function; ce-only; CE 6.0..699] */
BOOL GetAnimateMessageInfo(
 HWND hWnd, 
 WPARAM wParam, 
 LPARAM lParam, 
 LPANIMATEMESSAGEINFO pAnimateMessageInfo
);

/* GetWindowAutoGesture  [function; ce-only; CE 6.0..699] */
BOOL GetWindowAutoGesture(
 HWND hWnd, 
 LPWAGINFO lpAutoGestureInfo
);

/* SetWindowAutoGesture  [function; ce-only; CE 6.0..699] */
BOOL SetWindowAutoGesture(
 HWND hWnd, 
 LPWAGINFO lpAutoGestureInfo
);
#endif /* _WIN32_WCE */

#endif /* _PWINUSER_ */
