/* WDbgExts_CE.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 18 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WDBGEXTS_CE_
#define _WDBGEXTS_CE_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* EXTSTACKTRACE  [struct; ce-only] */
typedef struct _EXTSTACKTRACE {
 ULONG FramePointer;
 ULONG ProgramCounter;
 ULONG ReturnAddress;
 ULONG Args[4];
} EXTSTACKTRACE, *PEXTSTACKTRACE;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* CheckControlC  [function; ce-only; CE 5.0..699] */
ULONG CheckControlC(VOID);

/* GetSymbol  [function; ce-only; CE 5.0..699] */
VOID GetSymbol(
 PVOID offset,
 PUCHAR pchBuffer,
 PULONG pDisplacement
);

/* Ioctl  [function; ce-only; CE 5.0..699] */
ULONG Ioctl(
 USHORT IoctlType,
 PVOID lpvData,
 ULONG cbSizeOfContext
);

/* ReadControlSpace  [function; ce-only; CE 5.0..699] */
VOID ReadControlSpace(
 USHORT processor,
 ULONG address,
 PVOID buf,
 ULONG size
);

/* ReadIoSpace  [function; ce-only; CE 5.0..699] */
VOID ReadIoSpace(
 ULONG address,
 PULONG data,
 PULONG size
);

/* ReadMemory  [function; ce-only; CE 5.0..699] */
ULONG ReadMemory(
 ULONG offset,
 PVOID lpBuffer,
 ULONG cb,
 PULONG lpcbBytesRead
);

/* ReadPhysical  [function; ce-only; CE 5.0..699] */
VOID ReadPhysical(
 LARGE_INTEGER address,
 PVOID buf,
 ULONG size,
 PULONG sizer
);

/* SetThreadForOperation  [function; ce-only; CE 5.0..699] */
VOID SetTreadForOperation(
 PULONG Thread
);

/* StackTrace  [function; ce-only; CE 5.0..699] */
ULONG StackTrace(
 ULONG FramePointer,
 ULONG StackPointer,
 ULONG ProgramCounter,
 PEXTSTACKTRACE StackFrames,
 ULONG Frames
);

/* WriteIoSpace  [function; ce-only; CE 5.0..699] */
VOID WriteIoSpace(
 ULONG address,
 ULONG data,
 PULONG size
);

/* WriteMemory  [function; ce-only; CE 5.0..699] */
ULONG WriteMemory(
 ULONG offset,
 LPCVOID lpbuffer,
 ULONG cb,
 PULONG lpcbBytesWritten
);

/* WritePhysical  [function; ce-only; CE 5.0..699] */
VOID WritePhysical(
 LARGE_INTEGER address,
 PVOID buf,
 ULONG size,
 PULONG sizew
);
#endif /* _WIN32_WCE */

#endif /* _WDBGEXTS_CE_ */
