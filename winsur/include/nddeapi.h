/* nddeapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 49 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _NDDEAPI_
#define _NDDEAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define BAR_CHAR "|"
#define BAR_WCHAR L"|"
#define MAX_APPNAME 255
#define MAX_DOMAINNAME 15
#define MAX_ITEMNAME 255
#define MAX_NDDESHARENAME 256
#define MAX_TOPICNAME 255
#define MAX_USERNAME 15
#define NDDE_ACCESS_DENIED 1
#define NDDE_BUF_TOO_SMALL 2
#define NDDE_CANT_ACCESS_SERVER 24
#define NDDE_CMD_SHOW_MASK 0x0000FFFFL
#define NDDE_ERROR_MORE_DATA 3
#define NDDE_INTERNAL_ERROR 11
#define NDDE_INVALID_APPNAME 13
#define NDDE_INVALID_FILENAME 17
#define NDDE_INVALID_ITEM_LIST 21
#define NDDE_INVALID_ITEMNAME 9
#define NDDE_INVALID_LEVEL 7
#define NDDE_INVALID_PARAMETER 6
#define NDDE_INVALID_PASSWORD 8
#define NDDE_INVALID_SECURITY_DESC 26
#define NDDE_INVALID_SERVER 4
#define NDDE_INVALID_SESSION 20
#define NDDE_INVALID_SHARE 5
#define NDDE_INVALID_SPECIAL_COMMAND 25
#define NDDE_INVALID_TOPIC 10
#define NDDE_INVALID_WINDOW 19
#define NDDE_NO_ERROR 0
#define NDDE_NOT_IMPLEMENTED 14
#define NDDE_NOT_RUNNING 18
#define NDDE_OUT_OF_MEMORY 12
#define NDDE_REGISTRY_ERROR 23
#define NDDE_SHARE_ALREADY_EXIST 15
#define NDDE_SHARE_DATA_CORRUPTED 22
#define NDDE_SHARE_NOT_EXIST 16
#define NDDE_TRUST_CMD_SHOW 0x10000000L
#define NDDE_TRUST_SHARE_DEL 0x20000000L
#define NDDE_TRUST_SHARE_FAIL 27
#define NDDE_TRUST_SHARE_INIT 0x40000000L
#define NDDE_TRUST_SHARE_START 0x80000000L
#define NDDEF_NOCACHELOOKUP 0x0002
#define NDDEF_NOPASSWORDPROMPT 0x0001
#define NDDEF_STRIP_NDDE 0x0004
#define SEP_CHAR ','
#define SEP_WCHAR L','
#define SHARE_TYPE_NEW 0x02
#define SHARE_TYPE_OLD 0x01
#define SHARE_TYPE_STATIC 0x04

#endif /* _NDDEAPI_ */
