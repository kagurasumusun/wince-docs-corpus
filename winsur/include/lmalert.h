/* lmalert.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 20 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _LMALERT_
#define _LMALERT_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ALERT_ADMIN_EVENT TEXT("ADMIN")
#define ALERT_ERRORLOG_EVENT TEXT("ERRORLOG")
#define ALERT_MESSAGE_EVENT TEXT("MESSAGE")
#define ALERT_PRINT_EVENT TEXT("PRINTING")
#define ALERT_USER_EVENT TEXT("USER")
#define ALERTER_MAILSLOT TEXT("\\\\.\\MAILSLOT\\Alerter")
#define PRJOB_ 16
#define PRJOB_COMPLETE 4
#define PRJOB_DELETED 32768
#define PRJOB_DESTNOPAPER 256
#define PRJOB_DESTOFFLINE 32
#define PRJOB_DESTPAUSED 64
#define PRJOB_DEVSTATUS 508
#define PRJOB_INTERV 8
#define PRJOB_NOTIFY 128
#define PRJOB_QS_PAUSED 1
#define PRJOB_QS_PRINTING 3
#define PRJOB_QS_QUEUED 0
#define PRJOB_QS_SPOOLING 2
#define PRJOB_QSTATUS 3

#endif /* _LMALERT_ */
