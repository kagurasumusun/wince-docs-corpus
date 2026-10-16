/* Devload.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 17 constants, 6 declarations, 0 outlines, 0 base types, 4 extra macros, 1 extra decls
 */
#ifndef _DEVLOAD_
#define _DEVLOAD_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DEVFLAGS_BOOTPHASE_1 0x00001000
#define DEVFLAGS_IRQ_EXCLUSIVE 0x00000100
#define DEVFLAGS_LOAD_ASYNC 0x01000000
#define DEVFLAGS_LOADLIBRARY 0x00000002
#define DEVFLAGS_NAKEDENTRIES 0x00000008
#define DEVFLAGS_NOLOAD 0x00000004
#define DEVFLAGS_NONE 0x00000000
#define DEVFLAGS_TRUSTEDCALLERONLY 0x00010000
#define DEVFLAGS_UNLOAD 0x00000001
#define DEVLOAD_BUSINITCODE_VALTYPE REG_DWORD
#define DEVLOAD_CLIENTINFO_VALNAME L"ClientInfo"
#define DEVLOAD_DEVKEY_VALNAME L"Key"
#define DEVLOAD_DEVNAME_VALNAME L"Name"
#define DEVLOAD_HANDLE_VALNAME L"Hnd"
#define DEVLOAD_INITCODE_VALTYPE REG_DWORD
#define DEVLOAD_LOAD_ASYNC_EVENT_TIMEOUT_VALTYPE REG_DWORD
#define DEVLOAD_LOAD_ASYNC_EVENT_VALTYPE REG_SZ

/* ==================================================================
 * macros -- supplementary #define from CE pages
 * ================================================================ */
#define DEVLOAD_BUSINITCODE_VALNAME TEXT("BusIoctl") //Bus IO control code to indicate context
#define DEVLOAD_INITCODE_VALNAME TEXT("Ioctl") //Device IO control code to indicate context
#define DEVLOAD_LOAD_ASYNC_EVENT_TIMEOUT_VALNAME TEXT("LoadAsyncDelay")
#define DEVLOAD_LOAD_ASYNC_EVENT_VALNAME TEXT("LoadAsyncEvent")

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* POST_INIT_BUF  [struct; ce-only] */
struct _POST_INIT_BUF {
 HANDLE p_hDevice;
 HKEY p_hDeviceKey;
} POST_INIT_BUF, *PPOST_INIT_BUF;

/* REGINI  [struct; ce-only] */
typedef struct _REGINI {
 LPCWSTR lpszVal;
 LPBYTE pData;
 DWORD dwLen;
 DWORD dwType;
} REGINI;
typedef REGINI *PREGINI, *LPREGINI;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* EnumDevices  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
DWORD EnumDevices(
 LPTSTR lpszDevList,
 LPDWORD lpBuflen
);

/* EnumPnpIds  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
DWORD EnumPnpIds(
 LPTSTR lpszPnpList,
 LPDWORD lpBuflen
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* OpenDeviceKey  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
HKEY OpenDeviceKey(
 LPCTSTR ActiveKey
);
#endif /* _WIN32_WCE */

#endif /* _DEVLOAD_ */
