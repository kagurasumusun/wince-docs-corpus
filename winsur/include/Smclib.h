/* Smclib.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 20 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _SMCLIB_
#define _SMCLIB_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* SCARD_READER_CAPABILITIES  [struct; ce-only] */
typedef struct _SCARD_READER_CAPABILITIES {
 struct {
 ULONG Async;
 ULONG Sync;
 } SupportedProtocols;
 ULONG ReaderType;
 ULONG MechProperties;
 ULONG CurrentState;
 ULONG Channel;
 struct {
 ULONG Default;
 ULONG Max;
 } CLKFrequency;
 struct {
 ULONG Default;
 ULONG Max;
 } DataRate;
 ULONG MaxIFSD;
 ULONG PowerMgmtSupport;
 ULONG Reserved[25];
} SCARD_READER_CAPABILITIES, *PSCARD_READER_CAPABILITIES;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* SmartcardCreateLink  [function; ce-only; CE 3.0..399, 5.0..699] */
NTSTATUS SmartcardCreateLink(
 LPCWSTR pszFriendlyName,
 LPCWSTR pszDeviceName
);

/* SmartcardDeleteLink  [function; ce-only; CE 3.0..399, 5.0..699] */
NTSTATUS SmartcardDeleteLink(
 LPCWSTR pszFriendlyName
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* MapNtStatusToWinError  [function; ce-only; CE 3.0..699] */
ULONG MapNtStatusToWinError(
 NTSTATUS Status
);
#endif /* _WIN32_WCE */

#endif /* _SMCLIB_ */
