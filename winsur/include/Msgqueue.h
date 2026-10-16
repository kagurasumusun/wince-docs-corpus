/* Msgqueue.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 2 constants, 9 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _MSGQUEUE_
#define _MSGQUEUE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define MSGQUEUE_ALLOW_BROKEN 2
#define MSGQUEUE_NOPRECOMMIT 1

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* MSGQUEUEINFO  [typedef; ce-only] */
typedef MSGQUEUEINFO{
 DWORD dwSize;
 DWORD dwFlags;
 DWORD dwMaxMessages;
 DWORD cbMaxMessage;
 DWORD dwCurrentMessages;
 DWORD dwMaxQueueMessages;
 WORD wNumReaders;
 WORD wNumWriters;
} MSGQUEUEINFO, *PMSGQUEUEINFO, FAR* LPMSGQUEUEINFO;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* CloseMsgQueue  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CloseMsgQueue(
 HANDLE hMsgQ
);

/* GetMsgQueueInfo  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL GetMsgQueueInfo(
 HANDLE hMsgQ,
 LPMSGQUEUEINFO lpInfo
);

/* ReadMsgQueue  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL ReadMsgQueue(
 HANDLE hMsgQ,
 LPVOID lpBuffer,
 DWORD cbBufferSize,
 LPDWORD lpNumberOfBytesRead,
 DWORD dwTimeout,
 DWORD* pdwFlags
);

/* WriteMsgQueue  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL WriteMsgQueue(
 HANDLE hMsgQ,
 LPVOID lpBuffer,
 DWORD cbDataSize,
 DWORD dwTimeout,
 DWORD dwFlags
);
#endif /* _WIN32_WCE */

#endif /* _MSGQUEUE_ */
