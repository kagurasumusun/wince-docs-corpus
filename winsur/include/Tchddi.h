/* Tchddi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 10 declarations, 0 outlines, 0 base types, 0 extra macros, 5 extra decls
 */
#ifndef _TCHDDI_
#define _TCHDDI_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* enumTouchPanelSampleFlags  [enum; ce-only] */
enum enumTouchPanelSampleFlags {
 TouchSampleValidFlag = 0x01,
 TouchSampleDownFlag = 0x02,
 TouchSampleIsCalibratedFlag = 0x04,
 TouchSamplePreviousDownFlag = 0x08,
 TouchSampleIgnore = 0x10,
 TouchSampleMouse = 0x40000000
};

/* TPDC_CALIBRATION_POINT  [struct; ce-only] */
struct TPDC_CALIBRATION_POINT {
 INT PointNumber;
 INT cDisplayWidth;
 INT cDisplayHeight;
 INT CalibrationX;
 INT CalibrationY;
};

/* TPDC_SAMPLE_RATE  [struct; ce-only] */
struct TPDC_SAMPLE_RATE {
 INT SamplesPerSecondLow;
 INT SamplesPerSecondHigh;
 INT CurrentSampleRateSetting; 
};

/* x40000000  [extra enum] */
enum enumTouchPanelSampleFlags {TouchSampleValidFlag = 0x01,TouchSampleDownFlag = 0x02,TouchSampleIsCalibratedFlag = 0x04,TouchSamplePreviousDownFlag = 0x08,TouchSampleIgnore = 0x10,TouchSampleMouse = 0x40000000};

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..399, 5.0..699 */

/* TouchPanelDisable  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699; Tchmain.lib] */
VOID TouchPanelDisable(void);

/* TouchPanelGetDeviceCaps  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699; Tchmain.lib] */
BOOL TouchPanelGetDeviceCaps(
 INT iIndex,
 LPVOID lpOutput 
);

/* TouchPanelPowerHandler  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699; Tchmain.lib] */
VOID TouchPanelPowerHandler(
 BOOL bOff
);

/* TouchPanelReadCalibrationAbort  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699; Tchmain.lib] */
VOID TouchPanelReadCalibrationAbort(void);

/* TouchPanelSetMode  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699; Tchmain.lib] */
BOOL TouchPanelSetMode(
 INT iIndex,
 LPVOID lpInput 
);
#endif /* _WIN32_WCE */

#endif /* _TCHDDI_ */
