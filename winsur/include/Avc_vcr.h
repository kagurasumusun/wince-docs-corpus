/* Avc_vcr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _AVC_VCR_
#define _AVC_VCR_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x600)) /* CE 4.0..599 */

/* IOCTL_VCR_AVCCMD  [function; ce-only; CE 4.0..599] */
BOOL DeviceIoControl(
 HANDLE hDevice,
 DWORD dwIoControlCode,
 LPVOID lpInBuffer,
 DWORD nInBufferSize,
 LPVOID lpOutBuffer,
 DWORD nOutBufferSize,
 LPDWORD lpBytesReturned,
 LPOVERLAPPED lpOverlapped
);
#endif /* _WIN32_WCE */

#endif /* _AVC_VCR_ */
