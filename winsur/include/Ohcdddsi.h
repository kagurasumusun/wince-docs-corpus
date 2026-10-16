/* Ohcdddsi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 36 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _OHCDDDSI_
#define _OHCDDDSI_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400)) /* CE 2.11..2.12, 3.0..399 */

/* OhcdMdd_CreateMemoryObject  [function; ce-only; CE 2.11..2.12, 3.0..399] */
LPVOID OhcdMdd_CreateMemoryObject( 
DWORD cbSize, 
DWORD cbHighPrioritySize, 
PUCHAR pVirtAddr, 
PUCHAR pPhysAddr );

/* OhcdMdd_CreateOhcdObject  [function; ce-only; CE 2.11..2.12, 3.0..399] */
LPVOID OhcdMdd_CreateOhcdObject( 
LPVOID lpvOhcdPddObject, 
LPVOID lpvMemoryObject, 
LPCWSTR szRegKey, 
PUCHAR ioPortBase, 
DWORD dwSysIntr );

/* OhcdMdd_DestroyMemoryObject  [function; ce-only; CE 2.11..2.12, 3.0..399] */
BOOL OhcdMdd_DestroyMemoryObject( 
LPVOID lpvMemoryObject );

/* OhcdMdd_DestroyOhcdObject  [function; ce-only; CE 2.11..2.12, 3.0..399] */
BOOL OhcdMdd_DestroyOhcdObject( 
LPVOID lpvOhcdObject );

/* OhcdMdd_PowerDown  [function; ce-only; CE 2.11..2.12, 3.0..399] */
BOOL OhcdMdd_PowerDown( 
LPVOID lpvOhcdObject );

/* OhcdMdd_PowerUp  [function; ce-only; CE 2.11..2.12, 3.0..399] */
BOOL OhcdMdd_PowerUp( 
LPVOID lpvOhcdObject );

/* OhcdPdd_CheckConfigPower  [function; ce-only; CE 2.11..2.12, 3.0..399] */
BOOL OhcdPdd_CheckConfigPower( 
UCHAR bPort, 
DWORD dwConfigPower, 
DWORD dwTotalPower );

/* OhcdPdd_Close  [function; ce-only; CE 2.11..2.12, 3.0..399] */
BOOL OhcdPdd_Close( 
DWORD dwOpenContext );

/* OhcdPdd_Deinit  [function; ce-only; CE 2.11..2.12, 3.0..399] */
BOOL OhcdPdd_Deinit( 
DWORD dwDeviceContext );

/* OhcdPdd_DllMain  [function; ce-only; CE 2.11..2.12, 3.0..399] */
BOOL OhcdPdd_DllMain( 
HANDLE hinstDLL, 
DWORD dwReason, 
LPVOID lpvReserved );

/* OhcdPdd_Init  [function; ce-only; CE 2.11..2.12, 3.0..399] */
DWORD OhcdPdd_Init( 
DWORD dwContext );

/* OhcdPdd_IOControl  [function; ce-only; CE 2.11..2.12, 3.0..399] */
BOOL OhcdPdd_IOControl( 
DWORD dwOpenContext );

/* OhcdPdd_Open  [function; ce-only; CE 2.11..2.12, 3.0..399] */
DWORD OhcdPdd_Open( 
DWORD dwDeviceContext, 
DWORD dwAccessCode, 
DWORD dwShareMode );

/* OhcdPdd_PowerDown  [function; ce-only; CE 2.11..2.12, 3.0..399] */
void OhcdPdd_PowerDown( 
DWORD dwDeviceContext );

/* OhcdPdd_PowerUp  [function; ce-only; CE 2.11..2.12, 3.0..399] */
void OhcdPdd_PowerUp( 
DWORD dwDeviceContext );

/* OhcdPdd_Read  [function; ce-only; CE 2.11..2.12, 3.0..399] */
DWORD OhcdPdd_Read( 
DWORD dwOpenContext );

/* OhcdPdd_Seek  [function; ce-only; CE 2.11..2.12, 3.0..399] */
DWORD OhcdPdd_Seek( 
DWORD dwOpenContext );

/* OhcdPdd_Write  [function; ce-only; CE 2.11..2.12, 3.0..399] */
DWORD OhcdPdd_Write( 
DWORD dwOpenContext );
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* HcdMdd_CreateHcdObject  [function; ce-only; CE 4.0..699] */
LPVOID HcdMdd_CreateHcdObject(
 LPVOID lpvOhcdPddObject,
 LPVOID lpvMemoryObject,
 LPCWSTR szRegKey,
 PUCHAR ioPortBase,
 DWORD dwSysIntr 
);

/* HcdMdd_CreateMemoryObject  [function; ce-only; CE 4.0..699] */
LPVOID HcdMdd_CreateMemoryObject(
 DWORD cbSize,
 DWORD cbHighPrioritySize,
 PUCHAR pVirtAddr,
 PUCHAR pPhysAddr 
);

/* HcdMdd_DestroyHcdObject  [function; ce-only; CE 4.0..699] */
BOOL HcdMdd_DestroyOhcdObject(
 LPVOID lpvOhcdObject 
);

/* HcdMdd_DestroyMemoryObject  [function; ce-only; CE 4.0..699] */
BOOL HcdMdd_DestroyMemoryObject(
 LPVOID lpvMemoryObject 
);

/* HcdMdd_PowerDown  [function; ce-only; CE 4.0..699] */
BOOL HcdMdd_PowerDown(
 LPVOID lpvOhcdObject 
);

/* HcdMdd_PowerUp  [function; ce-only; CE 4.0..699] */
BOOL HcdMdd_PowerUp(
 LPVOID lpvOhcdObject 
);

/* HcdPdd_CheckConfigPower  [function; ce-only; CE 4.0..699] */
BOOL HcdPdd_CheckConfigPower(
 UCHAR bPort,
 DWORD dwConfigPower,
 DWORD dwTotalPower 
);

/* HcdPdd_Close  [function; ce-only; CE 4.0..699] */
BOOL HcdPdd_Close(
 DWORD dwOpenContext 
);

/* HcdPdd_Deinit  [function; ce-only; CE 4.0..699] */
BOOL HcdPdd_Deinit(
 DWORD dwDeviceContext 
);

/* HcdPdd_DllMain  [function; ce-only; CE 4.0..699] */
BOOL HcdPdd_DllMain(
 HANDLE hinstDLL,
 DWORD dwReason,
 LPVOID lpvReserved 
);

/* HcdPdd_Init  [function; ce-only; CE 4.0..699] */
DWORD HcdPdd_Init(
 DWORD dwContext 
);

/* HcdPdd_IOControl  [function; ce-only; CE 4.0..699] */
BOOL HcdPdd_IOControl(
 DWORD dwOpenContext 
);

/* HcdPdd_Open  [function; ce-only; CE 4.0..699] */
DWORD HcdPdd_Open(
 DWORD dwDeviceContext,
 DWORD dwAccessCode,
 DWORD dwShareMode 
);

/* HcdPdd_PowerDown  [function; ce-only; CE 4.0..699] */
void HcdPdd_PowerDown(
 DWORD dwDeviceContext 
);

/* HcdPdd_PowerUp  [function; ce-only; CE 4.0..699] */
void HcdPdd_PowerUp(
 DWORD dwDeviceContext 
);

/* HcdPdd_Read  [function; ce-only; CE 4.0..699] */
DWORD HcdPdd_Read(
 DWORD dwOpenContext 
);

/* HcdPdd_Seek  [function; ce-only; CE 4.0..699] */
DWORD HcdPdd_Seek(
 DWORD dwOpenContext 
);

/* HcdPdd_Write  [function; ce-only; CE 4.0..699] */
DWORD HcdPdd_Write(
 DWORD dwOpenContext 
);
#endif /* _WIN32_WCE */

#endif /* _OHCDDDSI_ */
