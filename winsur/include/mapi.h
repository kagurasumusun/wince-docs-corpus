/* mapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 53 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _MAPI_
#define _MAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define MAPI_AB_NOMODIFY 0x0400
#define MAPI_BCC 3
#define MAPI_BODY_AS_FILE 0x0200
#define MAPI_CC 2
#define MAPI_DIALOG 0x0008
#define MAPI_E_ACCESS_DENIED 6
#define MAPI_E_AMBIGUOUS_RECIP 21
#define MAPI_E_AMBIGUOUS_RECIPIENT 21
#define MAPI_E_ATTACHMENT_NOT_FOUND 11
#define MAPI_E_ATTACHMENT_OPEN_FAILURE 12
#define MAPI_E_ATTACHMENT_WRITE_FAILURE 13
#define MAPI_E_BAD_RECIPTYPE 15
#define MAPI_E_BLK_TOO_SMALL 6
#define MAPI_E_DISK_FULL 4
#define MAPI_E_FAILURE 2
#define MAPI_E_INSUFFICIENT_MEMORY 5
#define MAPI_E_INVALID_EDITFIELDS 24
#define MAPI_E_INVALID_MESSAGE 17
#define MAPI_E_INVALID_RECIPS 25
#define MAPI_E_INVALID_SESSION 19
#define MAPI_E_LOGIN_FAILURE 3
#define MAPI_E_LOGON_FAILURE 3
#define MAPI_E_MESSAGE_IN_USE 22
#define MAPI_E_NETWORK_FAILURE 23
#define MAPI_E_NO_MESSAGES 16
#define MAPI_E_NOT_SUPPORTED 26
#define MAPI_E_TEXT_TOO_LARGE 18
#define MAPI_E_TOO_MANY_FILES 9
#define MAPI_E_TOO_MANY_RECIPIENTS 10
#define MAPI_E_TOO_MANY_SESSIONS 8
#define MAPI_E_TYPE_NOT_SUPPORTED 20
#define MAPI_E_UNKNOWN_RECIPIENT 14
#define MAPI_E_USER_ABORT 1
#define MAPI_ENVELOPE_ONLY 0x0040
#define MAPI_FORCE_DOWNLOAD 0x1000
#define MAPI_GUARANTEE_FIFO 0x0100
#define MAPI_LOGOFF_SHARED 0x0001
#define MAPI_LOGOFF_UI 0x0002
#define MAPI_LOGON_UI 0x0001
#define MAPI_LONG_MSGID 0x4000
#define MAPI_NEW_SESSION 0x0002
#define MAPI_OLE 0x0001
#define MAPI_OLE_STATIC 0x0002
#define MAPI_ORIG 0
#define MAPI_PEEK 0x0080
#define MAPI_RECEIPT_REQUESTED 0x0002
#define MAPI_SENT 0x0004
#define MAPI_SUPPRESS_ATTACH 0x0800
#define MAPI_TO 1
#define MAPI_UNREAD 0x0001
#define MAPI_UNREAD_ONLY 0x0020
#define MAPI_USER_ABORT 1
#define SUCCESS_SUCCESS 0

#endif /* _MAPI_ */
