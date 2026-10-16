/* controldefinitions.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 3 constants, 18 declarations, 1 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CONTROLDEFINITIONS_
#define _CONTROLDEFINITIONS_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define phcDefaultTransparentColor 0
#define phfStandardText 0
#define shpError 0

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* STATUS_HEADER_PARAMETERS  [struct; ce-only; PhCommon.dll] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DIALOG_HOOK_PROC  [typedef; ce-only; PhCommon.dll] */
typedef BOOL (CALLBACK* DIALOG_HOOK_PROC)(
 HWND hDialogWnd,
 UINT Message,
 WPARAM wParam, 
 LPARAM lParam,
 void* pUserData
);

/* PH_COLOR  [enum; ce-only; PhCommon.dll] */
typedef enum _PH_COLOR
{
 phcDefaultTransparentColor = 0,
 phcDefaultBackgroundColor,
 phcDefaultTextColor,
 phcDisplayItemBackgroundColor,
 phcDisplayItemSelectedBackgroundColor,
 phcDisplayItemTextColor,
 phcDisplayItemSelectedTextColor,
 phcDisplayItemBorderColor,
 phcDisplayItemSelectedBorderColor,
 phcLast,
} PH_COLOR;
typedef PH_COLOR *PPH_COLOR, *LPPH_COLOR;

/* PH_DIALOG_SCREEN_PARAMETERS  [struct; ce-only; PhCommon.dll] */
typedef struct _PH_DIALOG_SCREEN_PARAMETERS
{
 DWORD StructSize; 
 DWORD Flags; 
 HWND Owner; 
 UINT Id; 
 HINSTANCE Instance; 
 const WCHAR* pStatusHeader; 
 const WCHAR* pTitle; 
 UINT MenuId;
 DIALOG_HOOK_PROC pDialogHook; 
 void* pUserData; 
 union {
 UINT SelectedId; 
 HWND Dialog; 
 } result;
} PH_DIALOG_SCREEN_PARAMETERS;
typedef PH_DIALOG_SCREEN_PARAMETERS *PPH_DIALOG_SCREEN_PARAMETERS, *LPPH_DIALOG_SCREEN_PARAMETERS;

/* PH_FONT  [enum; ce-only; PhCommon.dll] */
typedef enum _PH_FONT
{
 phfStandardText = 0,
 phfStandardTextBold,
 phfInformationText,
 phfLargeText,
 phfBigNumbersText,
 phfLast,
} PH_FONT;
typedef PH_FONT *PPH_FONT, *LPPH_FONT;

/* PH_MESSAGE_BOX_PARAMETERS  [struct; ce-only; PhCommon.dll] */
typedef struct _PH_MESSAGE_BOX_PARAMETERS
{
 DWORD StructSize; 
 DWORD Flags; 
 HWND Owner; 
 HINSTANCE Instance; 
 const WCHAR* pTitle; 
 const WCHAR* pText; 
 UINT IconId; 
 UINT MenuId; 
 union{ 
 UINT SelectedId; 
 HWND Dialog; 
 } result;
} PH_MESSAGE_BOX_PARAMETERS;
typedef PH_MESSAGE_BOX_PARAMETERS *PPH_MESSAGE_BOX_PARAMETERS, *LPPH_MESSAGE_BOX_PARAMETERS;

/* PHMS_ITEM  [struct; ce-only; PhCommon.dll] */
typedef struct _PHMS_ITEM
{
 int Identifier;
 int StringId;
} PHMS_ITEM;
typedef PHMS_ITEM *PPHMS_ITEM, *LPPHMS_ITEM;

/* STATUS_HEADER_PRIORITY  [enum; ce-only; PhCommon.dll] */
typedef enum _STATUS_HEADER_PRIORITY
{
 shpError = 0, 
 shpTempChanges, 
 shpNodeHelp, 
 shpSystem, 
 shpHelp, 
 shpForwarding, 
 shpIncomingCall, 
 shpMissedCalls, 
 shpDefault, 
 StatusHeaderPriorities, 
} STATUS_HEADER_PRIORITY;
typedef STATUS_HEADER_PRIORITY *PSTATUS_HEADER_PRIORITY, *LPSTATUS_HEADER_PRIORITY;

/* PH_MENU_SCREEN_PARAMETERS  [struct; ce-only; PhCommon.dll] */
typedef struct _PH_MENU_SCREEN_PARAMETERS
{
 DWORD StructSize; 
 DWORD Flags; 
 HWND Owner; 
 UINT Id; 
 HINSTANCE Instance; 
 const WCHAR* pTitle; 
 PHMS_ITEM* pMenuScreenItems;
 int ItemCount;
 UINT NotificationMsg; 
 union{
 UINT SelectedId; 
 HWND Dialog; 
 } result;
} PH_MENU_SCREEN_PARAMETERS;
typedef PH_MENU_SCREEN_PARAMETERS *PPH_MENU_SCREEN_PARAMETERS, *LPPH_MENU_SCREEN_PARAMETERS;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* PHDialogScreen  [function; ce-only; CE 6.0..699; PhCommon.dll] */
BOOL PHDialogScreen(
PH_DIALOG_SCREEN_PARAMETERS* pParameters
);

/* PHDrawBackground  [function; ce-only; CE 6.0..699; PhCommon.dll] */
BOOL PHDrawBackground(
HDC hdc,
RECT* pDrawRectangle
);

/* PHGetColor  [function; ce-only; CE 6.0..699; PhCommon.dll] */
COLORREF PHGetColor(
PH_COLOR Id
);

/* PHGetFont  [function; ce-only; CE 6.0..699; PhCommon.dll] */
HFONT PHGetFont(
PH_FONT Id
);

/* PHInitCommonControls  [function; ce-only; CE 6.0..699; PhCommon.dll] */
BOOL PHInitCommonControls();

/* PHMenuScreen  [function; ce-only; CE 6.0..699; PhCommon.dll] */
BOOL PHMenuScreen(
 PH_MENU_SCREEN_PARAMETERS* pParameters
);

/* PHMessageBox  [function; ce-only; CE 6.0..699; PhCommon.dll] */
BOOL PHMessageBox(
 PH_MESSAGE_BOX_PARAMETERS* pParameters
);

/* PHRegisterSingletonApplication  [function; ce-only; CE 6.0..699; PhCommon.dll] */
BOOL PHRegisterSingletonApplication(
const WCHAR* pNameToRegister, 
HANDLE* phApplication
);

/* PHUnInitCommonControls  [function; ce-only; CE 6.0..699; PhCommon.dll] */
BOOL PHUnInitCommonControls();
#endif /* _WIN32_WCE */

#endif /* _CONTROLDEFINITIONS_ */
