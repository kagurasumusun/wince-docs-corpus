/* XamlRuntime.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 1 constants, 57 declarations, 7 outlines, 0 base types, 0 extra macros, 21 extra decls
 */
#ifndef _XAMLRUNTIME_
#define _XAMLRUNTIME_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define XRS_STRING 0

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* PFN_CREATE_CONTROL  [typedef; ce-only] */

/* PFN_PROPERTY_CHANGE  [typedef; ce-only] */

/* PFN_TYPE_CONVERTER  [typedef; ce-only] */

/* XRDependencyPropertyMetaData  [struct; ce-only] */

/* XRMouseEventArgs  [struct; ce-only] */

/* XRRoutedEventArgs  [struct; ce-only] */

/* XRXamlSource  [struct; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* VALUE_TYPE  [enum; ce-only] */
enum VALUE_TYPE
{
 VTYPE_NONE = 0,
 VTYPE_FLOAT = 1,
 VTYPE_INT = 2,
 VTYPE_BOOL = 3,
 VTYPE_UINT = 4,
 VTYPE_COLOR = 5,
 VTYPE_READONLY_STRING = 6,
 VTYPE_BSTR = 7
 VTYPE_POINT = 8,
 VTYPE_RECT = 9,
 VTYPE_THICKNESS = 10,
 VTYPE_SIZE = 11,
 VTYPE_GRIDLENGTH = 12,
 VTYPE_CORNER_RADIUS = 13,
 VTYPE_OBJECT = 14
};

/* XRAlignmentX  [enum; ce-only] */
enum XRAlignmentX{
 XRAlignmentX_Left=0,
 XRAlignmentX_Center=1,
 XRAlignmentX_Right=2
};

/* XRAlignmentY  [enum; ce-only] */
enum XRAlignmentY{
 XRAlignmentY_Top=0,
 XRAlignmentY_Center=1,
 XRAlignmentY_Bottom=2
};

/* XRBrushMappingMode  [enum; ce-only] */
enum XRBrushMappingMode
{
 XRBrushMappingMode_Absolute=0,
 XRBrushMappingMode_RelativeToBoundingBox=1
};

/* XRClickMode  [enum; ce-only] */
enum XRClickMode{
 XRClickMode_Release = 0, 
 XRClickMode_Press, 
 XRClickMode_Hover,
};

/* XRClockState  [enum; ce-only] */
enum XRClockState
{
 XRClockState_Active=0,
 XRClockState_Filling=1,
 XRClockState_Stopped=2
};

/* XRColorInterpolationMode  [enum; ce-only] */
enum XRColorInterpolationMode{
 XRColorInterpolationMode_ScRgbLinearInterpolation=0,
 XRColorInterpolationMode_SRgbLinearInterpolation=1
};

/* XRCornerRadius  [struct; ce-only] */
struct XRCornerRadius{
 float TopLeft;
 float TopRight;
 float BottomRight;
 float BottomLeft;
};

/* XRCursor  [enum; ce-only] */
enum XRCursor
{
 XRCursor_Default = 0,
 XRCursor_Arrow = 1,
 XRCursor_Hand = 2,
 XRCursor_Wait = 3,
 XRCursor_IBeam = 4,
 XRCursor_Stylus = 5,
 XRCursor_Eraser = 6,
 XRCursor_SizeNS = 7,
 XRCursor_SizeWE = 8,
 XRCursor_None = 9
};

/* XRDragCompletedEventArgs  [struct; ce-only] */
struct XRDragCompletedEventArgs : XRRoutedEventArgs{
 double HorizontalChange;
 double VerticalChange;
 bool Cancelled;
};

/* XRDragDeltaEventArgs  [struct; ce-only] */
struct XRDragDeltaEventArgs : XRRoutedEventArgs{
 double HorizontalDelta;
 double VeriticalDelta;
};

/* XRDragStartedEventArgs  [struct; ce-only] */
struct XRDragStartedEventArgs : XRRoutedEventArgs{
 double VerticalOffset;
 double HorizontalOffset;
};

/* XRDuration  [struct; ce-only] */
struct XRDuration{
 enum _DurationType{
 DurationType_Automatic,
 DurationType_TimeSpan,
 DurationType_Forever
 };
 XRTimeSpan TimeSpan;
 _DurationType DurationType;
};

/* XREventArgs  [struct; ce-only] */
struct XREventArgs{
 UINT Size;
};

/* XRFillBehavior  [enum; ce-only] */
enum XRFillBehavior{
 XRFillBehavior_HoldEnd=0,
 XRFillBehavior_Stop=1
};

/* XRFillRule  [enum; ce-only] */
enum XRFillRule
{
 XRFillRule_EvenOdd=0,
 XRFillRule_Nonzero=1
};

/* XRFontStretch  [enum; ce-only] */
enum XRFontStretch{
 XRFontStretch_UltraCondensed=1,
 XRFontStretch_ExtraCondensed=2,
 XRFontStretch_Condensed=3,
 XRFontStretch_SemiCondensed=4,
 XRFontStretch_Normal=5,
 XRFontStretch_Medium=5,
 XRFontStretch_SemiExpanded=6,
 XRFontStretch_Expanded=7,
 XRFontStretch_ExtraExpanded=8,
 XRFontStretch_UltraExpanded=9
};

/* XRFontStyle  [enum; ce-only] */
enum XRFontStyle{
 XRFontStyle_Normal=0,
 XRFontStyle_Oblique=1,
 XRFontStyle_Italic=2
};

/* XRFontWeight  [enum; ce-only] */
enum XRFontWeight{
 XRFontWeight_Thin=100,
 XRFontWeight_ExtraLight=200,
 XRFontWeight_Light=300,
 XRFontWeight_Normal=400,
 XRFontWeight_Medium=500,
 XRFontWeight_SemiBold=600,
 XRFontWeight_Bold=700,
 XRFontWeight_ExtraBold=800,
 XRFontWeight_Black=900,
 XRFontWeight_ExtraBlack=950
};

/* XRGradientSpreadMethod  [enum; ce-only] */
enum XRGradientSpreadMethod{
 XRGradientSpreadMethod_Pad=0,
 XRGradientSpreadMethod_Reflect=1,
 XRGradientSpreadMethod_Repeat=2
};

/* XRGridLength  [struct; ce-only] */
struct XRGridLength{
 float UnitValue;
 XRGridUnitType UnitType;
};

/* XRGridUnitType  [enum; ce-only] */
enum XRGridUnitType{
 XRGridUnitType_Auto=0,
 XRGridUnitType_Pixel=1,
 XRGridUnitType_Star=2
};

/* XRHorizontalAlignment  [enum; ce-only] */
enum XRHorizontalAlignment{
 XRHorizontalAlignment_Left=0,
 XRHorizontalAlignment_Center=1,
 XRHorizontalAlignment_Right=2,
 XRHorizontalAlignment_Stretch=3
};

/* XRKeyboardNavigationMode  [enum; ce-only] */
enum XRKeyboardNavigationMode{
 XRKeyboardNavigationMode_Local=0,
 XRKeyboardNavigationMode_Cycle=1,
 XRKeyboardNavigationMode_Once=2
};

/* XRKeyEventArgs  [struct; ce-only] */
struct XRKeyEventArgs : XRRoutedEventArgs{
 BOOL Handled;
 UINT PlatformKeyCode;
};

/* XRKeyTime  [struct; ce-only] */
struct XRKeyTime : public XRTimeSpan
{
};

/* XRLineStackingStrategy  [enum; ce-only] */
enum XRLineStackingStrategy{
 XRLineStackingStrategy_MaxHeight=0,
 XRLineStackingStrategy_BlockLineHeight=1
};

/* XRMouseButtonEventArgs  [struct; ce-only] */
struct XRMouseButtonEventArgs : XRMouseEventArgs{
 BOOL Handled;
};

/* XROrientation  [enum; ce-only] */
enum XROrientation{
 XROrientation_Vertical=0,
 XROrientation_Horizontal=1
};

/* XRPenLineCap  [enum; ce-only] */
enum XRPenLineCap{
 XRPenLineCap_Flat=0,
 XRPenLineCap_Square=1,
 XRPenLineCap_Round=2,
 XRPenLineCap_Triangle=3
};

/* XRPenLineJoin  [enum; ce-only] */
enum XRPenLineJoin{
 XRPenLineJoin_Miter=0,
 XRPenLineJoin_Bevel=1,
 XRPenLineJoin_Round=2
};

/* XRPoint  [struct; ce-only] */
struct XRPoint{
 float x;
 float y;
};

/* XRRect  [struct; ce-only] */
struct XRRect{
 float left;
 float top;
 float right;
 float bottom;
};

/* XRRepeatBehavior  [struct; ce-only] */
struct XRRepeatBehavior{
 enum RepeatBehaviorType{
 RepeatBehaviorType_IterationCount,
 RepeatBehaviorType_RepeatDuration,
 RepeatBehaviorType_Forever
 };
 float IterationCount;
 XRTimeSpan RepeatDuration;
 RepeatBehaviorType BehaviorType;
};

/* XRScrollBarVisibility  [enum; ce-only] */
enum XRScrollBarVisibility
{
 XRScrollBarVisibility_Disabled = 0,
 XRScrollBarVisibility_Auto,
 XRScrollBarVisibility_Hidden,
 XRScrollBarVisibility_Visible
};

/* XRScrollChangedEventArgs  [struct; ce-only] */
struct XRScrollChangedEventArgs : XRRoutedEventArgs
{
 float XOffset;
 float YOffset;
};

/* XRScrollEventArgs  [struct; ce-only] */
struct XRScrollEventArgs : XRRoutedEventArgs
{
 float NewValue;
 XRScrollEventType ScrollEventType;
};

/* XRScrollEventType  [enum; ce-only] */
enum XRScrollEventType{
 XRScrollEventType_EndScroll = 8,
 XRScrollEventType_First = 6,
 XRScrollEventType_LargeDecrement = 2,
 XRScrollEventType_LargeIncrement = 3,
 XRScrollEventType_Last = 7,
 XRScrollEventType_SmallDecrement = 0,
 XRScrollEventType_SmallIncrement = 1,
 XRScrollEventType_ThumbPosition = 4,
 XRScrollEventType_ThumbTrack = 5
};

/* XRSize  [struct; ce-only] */
struct XRSize{
 float cx;
 float cy;
};

/* XRSizeChangedEventArgs  [struct; ce-only] */
struct XRSizeChangedEventArgs : XRRoutedEventArgs
{
 XRSize PreviousSize;
 XRSize NewSize;
};

/* XRStretch  [enum; ce-only] */
enum XRStretch{
 XRStretch_None=0,
 XRStretch_Fill=1,
 XRStretch_Uniform=2,
 XRStretch_UniformToFill=3
};

/* XRStyleSimulations  [enum; ce-only] */
enum XRStyleSimulations{
 XRStyleSimulations_None=0,
 XRStyleSimulations_BoldSimulation=1,
 XRStyleSimulations_ItalicSimulation=2,
 XRStyleSimulations_BoldItalicSimulation=3
};

/* XRSweepDirection  [enum; ce-only] */
enum XRSweepDirection
{
 XRSweepDirection_Counterclockwise=0,
 XRSweepDirection_Clockwise=1
};

/* XRTextAlignment  [enum; ce-only] */
enum XRTextAlignment{
 XRTextAlignment_Center=0,
 XRTextAlignment_Left=1,
 XRTextAlignment_Right=2
};

/* XRTextChangedEventArgs  [struct; ce-only] */
struct XRTextChangedEventArgs : XRRoutedEventArgs{
};

/* XRTextDecorationType  [enum; ce-only] */
enum XRTextDecorationType{
 XRTextDecorationType_None=0,
 XRTextDecorationType_Underline=1
};

/* XRTextWrapping  [enum; ce-only] */
enum XRTextWrapping{
 XRTextWrapping_NoWrap = 1,
 XRTextWrapping_Wrap = 2
};

/* XRThickness  [struct; ce-only] */
struct XRThickness{
 float Left;
 float Top;
 float Right;
 float Bottom;
};

/* XRThreeState  [enum; ce-only] */
enum XRThreeState
{
 XRThreeState_Unchecked = 0,
 XRThreeState_Checked,
 XRThreeState_Indeterminate
};

/* XRTimeSpan  [struct; ce-only] */
struct XRTimeSpan
{
 XRTimeSpan(){};
 XRTimeSpan(__int64 TotalTicks)
 XRTimeSpan(int Days, int Hours, int Minutes, int Seconds, 
 int Milliseconds)
 static const int MinutesPerDay = 3600;
 static const int HoursPerDay = 24;
 static const int MinutesPerHour = 60;
 static const int MillisecondPerSecond = 1000;
 __int64 TotalSeconds()
 __int64 TotalMinutes()
 __int64 TotalHours()
 __int64 TotalMilliseconds()
 static __int64 FromSeconds(double Value)
 static __int64 Interval(double Value, int scale)
 __int64 Ticks;
 static const __int64 TicksPerDay = 864000000000;
 static const __int64 TicksPerHour = 36000000000;
 static const __int64 TicksPerMinute = 600000000;
 static const __int64 TicksPerSecond = 10000000;
 static const __int64 TicksPerMillisecond = 10000;
};

/* XRVerticalAlignment  [enum; ce-only] */
enum XRVerticalAlignment{
 XRVerticalAlignment_Top=0,
 XRVerticalAlignment_Center=1,
 XRVerticalAlignment_Bottom=2,
 XRVerticalAlignment_Stretch=3
};

/* XRVisibility  [enum; ce-only] */
enum XRVisibility{
 XRVisibility_Visible = 0,
 XRVisibility_Collapsed = 1
};

/* DurationType  [extra struct] */
struct XRDuration{
  enum _DurationType{
    DurationType_Automatic,
    DurationType_TimeSpan,
    DurationType_Forever
  };
  XRTimeSpan TimeSpan;
  _DurationType DurationType;
};

/* XRThreeState_Indeterminate  [extra enum] */
enum XRThreeState
{
  XRThreeState_Unchecked = 0,
  XRThreeState_Checked,
  XRThreeState_Indeterminate
};

/* NewSize  [extra struct] */
struct XRSizeChangedEventArgs : XRRoutedEventArgs
{
  XRSize PreviousSize;
  XRSize NewSize;
};

/* BehaviorType  [extra struct] */
struct XRRepeatBehavior{
  enum RepeatBehaviorType{
    RepeatBehaviorType_IterationCount,
    RepeatBehaviorType_RepeatDuration,
    RepeatBehaviorType_Forever
  };
  float IterationCount;
  XRTimeSpan RepeatDuration;
  RepeatBehaviorType BehaviorType;
};

/* Handled  [extra struct] */
struct XRMouseButtonEventArgs : XRMouseEventArgs{ BOOL Handled; };

/* HorizontalOffset  [extra struct] */
struct XRDragStartedEventArgs : XRRoutedEventArgs{ double VerticalOffset; double HorizontalOffset; };

/* PlatformKeyCode  [extra struct] */
struct XRKeyEventArgs : XRRoutedEventArgs{ BOOL Handled; UINT PlatformKeyCode; };

/* ScrollEventType  [extra struct] */
struct XRScrollEventArgs : XRRoutedEventArgs
{
  float NewValue;
  XRScrollEventType ScrollEventType;
};

/* BottomLeft  [extra struct] */
struct XRCornerRadius{
  float TopLeft;
  float TopRight;
  float BottomRight;
  float BottomLeft;
};

/* Bottom  [extra struct] */
struct XRThickness{
  float Left;
  float Top;
  float Right;
  float Bottom;
};

/* YOffset  [extra struct] */
struct XRScrollChangedEventArgs : XRRoutedEventArgs
{
  float XOffset;
  float YOffset;
};

/* XRClickMode_Hover  [extra enum] */
enum XRClickMode{
  XRClickMode_Release = 0,
  XRClickMode_Press,
  XRClickMode_Hover,
};

/* cy  [extra struct] */
struct XRSize{ float cx; float cy; };

/* Cancelled  [extra struct] */
struct XRDragCompletedEventArgs : XRRoutedEventArgs{
  double HorizontalChange;
  double VerticalChange;
  bool Cancelled;
};

/* TicksPerMillisecond  [extra struct] */
struct XRTimeSpan
{
  XRTimeSpan(){};
  XRTimeSpan(__int64 TotalTicks)
  XRTimeSpan(int Days, int Hours, int Minutes, int Seconds,
  int Milliseconds)
  static const int MinutesPerDay = 3600;
  static const int HoursPerDay = 24;
  static const int MinutesPerHour = 60;
  static const int MillisecondPerSecond = 1000;
  __int64 TotalSeconds()
  __int64 TotalMinutes()
  __int64 TotalHours()
  __int64 TotalMilliseconds()
  static __int64 FromSeconds(double Value)
  static __int64 Interval(double Value, int scale)
  __int64 Ticks;
  static const __int64 TicksPerDay = 864000000000;
  static const __int64 TicksPerHour = 36000000000;
  static const __int64 TicksPerMinute = 600000000;
  static const __int64 TicksPerSecond = 10000000;
  static const __int64 TicksPerMillisecond = 10000;
};

/* XRScrollBarVisibility_Visible  [extra enum] */
enum XRScrollBarVisibility
{
  XRScrollBarVisibility_Disabled = 0,
  XRScrollBarVisibility_Auto,
  XRScrollBarVisibility_Hidden,
  XRScrollBarVisibility_Visible
};

/* VeriticalDelta  [extra struct] */
struct XRDragDeltaEventArgs : XRRoutedEventArgs{ double HorizontalDelta; double VeriticalDelta; };

/* bottom  [extra struct] */
struct XRRect{
  float left;
  float top;
  float right;
  float bottom;
};

/* UnitType  [extra struct] */
struct XRGridLength{ float UnitValue; XRGridUnitType UnitType; };

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* FreeXRValue  [function; ce-only; CE 6.0..699] */
void WINAPI FreeXRValue(
 XRValue* pValue
);

/* XamlRuntimeInitialize  [function; ce-only; CE 6.0..699] */
BOOL WINAPI XamlRuntimeInitialize();

/* XamlRuntimeUninitialize  [function; ce-only; CE 6.0..699] */
BOOL WINAPI XamlRuntimeUninitialize();

/* XR_HOOKPROC  [function; ce-only; CE 6.0..699] */
BOOL CALLBACK HostHookProc(
 VOID* pv,
 HWND hwnd,
 UINT Msg,
 WPARAM wParam,
 LPARAM lParam,
 LRESULT* pRetVal
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
BOOL CALLBACK HostHookProc( VOID* pv, HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam, LRESULT* pRetVal );

#endif /* _XAMLRUNTIME_ */
