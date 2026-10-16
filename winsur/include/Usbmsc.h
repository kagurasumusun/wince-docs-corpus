/* Usbmsc.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 2 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _USBMSC_
#define _USBMSC_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* TRANSPORT_COMMAND  [struct; ce-only] */
typedef struct _TRANSPORT_COMMAND {
 DWORD Flags;
 DWORD Timeout;
 DWORD Length;
 DWORD dwLun;
 PVOID CommandBlock;
} TRANSPORT_COMMAND, *PTRANSPORT_COMMAND;

/* TRANSPORT_DATA  [struct; ce-only] */
typedef struct _TRANSPORT_DATA_BUFFER {
 DWORD RequestLength;
 DWORD TransferLength;
 PVOID DataBlock;
} TRANSPORT_DATA, *PTRANSPORT_DATA;

#endif /* _USBMSC_ */
