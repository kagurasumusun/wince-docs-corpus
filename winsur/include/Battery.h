/* Battery.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 5 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _BATTERY_
#define _BATTERY_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* BATTERY_STATUS  [struct; ce-only] */
typedef struct { 
BYTE ACLineStatus; 
BYTE BatteryFlag; 
BYTE BatteryLifePercent; 
BYTE Reserved1; 
DWORD BatteryLifeTime; 
DWORD BatteryFullLifeTime; 
BYTE Reserved2; 
BYTE BackupBatteryFlag; 
BYTE BackupBatteryLifePercent; 
BYTE fBatteriesChangedSinceLastCall; 
DWORD BackupBatteryLifeTime; 
DWORD BackupBatteryFullLifeTime; 
} BATTERY_STATUS;
typedef BATTERY_STATUS *PBATTERY_STATUS, *LPBATTERY_STATUS;

/* BATTERYLIFETIMEINFO  [struct; ce-only] */
typedef struct _BatteryLifetimeInfo_tag {
 SYSTEMTIME stLastChange;
 DWORD cmsCpuUsage;
 DWORD cmsPreviousCpuUsage;
} BATTERYLIFETIMEINFO, *PBATTERYLIFETIMEINFO;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x700)) /* CE 2.11..699 */

/* BatteryDrvrGetLevels  [function; ce-only; CE 2.11..699; Coredll.lib, coredll.lib] */
LONG BatteryDrvrGetLevels(void);

/* BatteryDrvrSupportsChangeNotification  [function; ce-only; CE 2.11..699; Acmdwrap.lib, Coredll.lib, coredll.lib] */
BOOL BatteryDrvrSupportsChangeNotification(void);
#endif /* _WIN32_WCE */

#endif /* _BATTERY_ */
