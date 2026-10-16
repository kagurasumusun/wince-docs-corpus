/* Rndis.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 21 constants, 9 declarations, 1 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _RNDIS_
#define _RNDIS_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define REMOTE_NDIS_HALT_MSG 0x00000003
#define REMOTE_NDIS_INDICATE_STATUS_MSG 0x00000007
#define REMOTE_NDIS_INITIALIZE_CMPLT 0x80000002
#define REMOTE_NDIS_INITIALIZE_MSG 0x00000002
#define REMOTE_NDIS_KEEPALIVE_CMPLT 0x80000008
#define REMOTE_NDIS_KEEPALIVE_MSG 0x00000008
#define REMOTE_NDIS_QUERY_CMPLT 0x80000004
#define REMOTE_NDIS_QUERY_MSG 0x00000004
#define REMOTE_NDIS_RESET_CMPLT 0x80000006
#define REMOTE_NDIS_RESET_MSG 0x00000006
#define REMOTE_NDIS_SET_CMPLT 0x80000005
#define REMOTE_NDIS_SET_MSG 0x00000005
#define RNDIS_MEDIUM_802_3 0x00000000
#define RNDIS_STATUS_BUFFER_OVERFLOW 0x80000005L
#define RNDIS_STATUS_FAILURE 0xC0000001L
#define RNDIS_STATUS_INVALID_DATA 0xC0010015
#define RNDIS_STATUS_MEDIA_CONNECT 0x4001000B
#define RNDIS_STATUS_MEDIA_DISCONNECT 0x4001000C
#define RNDIS_STATUS_NOT_SUPPORTED 0xC00000BB
#define RNDIS_STATUS_RESOURCES 0xC000009AL
#define RNDIS_STATUS_SUCCESS 0x00000000

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* RNDIS_PDD_CHARACTERISTICS  [struct; ce-only] */

#endif /* _RNDIS_ */
