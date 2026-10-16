/* lmshare.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 28 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _LMSHARE_
#define _LMSHARE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define PERM_FILE_CREATE 4
#define PERM_FILE_READ 1
#define PERM_FILE_WRITE 2
#define SESI1_NUM_ELEMENTS 8
#define SESI2_NUM_ELEMENTS 9
#define SESS_GUEST 1
#define SESS_NOENCRYPTION 2
#define SHARE_CURRENT_USES_PARMNUM 7
#define SHARE_FILE_SD_INFOLEVEL (PARMNUM_BASE_INFOLEVEL+SHARE_FILE_SD_PARMNUM)
#define SHARE_FILE_SD_PARMNUM 501
#define SHARE_MAX_USES_INFOLEVEL (PARMNUM_BASE_INFOLEVEL+SHARE_MAX_USES_PARMNUM)
#define SHARE_MAX_USES_PARMNUM 6
#define SHARE_NETNAME_PARMNUM 1
#define SHARE_PASSWD_PARMNUM 9
#define SHARE_PATH_PARMNUM 8
#define SHARE_PERMISSIONS_PARMNUM 5
#define SHARE_REMARK_INFOLEVEL (PARMNUM_BASE_INFOLEVEL+SHARE_REMARK_PARMNUM)
#define SHARE_REMARK_PARMNUM 4
#define SHARE_TYPE_PARMNUM 3
#define SHI1_NUM_ELEMENTS 4
#define SHI2_NUM_ELEMENTS 10
#define SHI_USES_UNLIMITED (DWORD)(-1)
#define STYPE_DEVICE 2
#define STYPE_DFS 100
#define STYPE_DISKTREE 0
#define STYPE_IPC 3
#define STYPE_PRINTQ 1
#define STYPE_SPECIAL 0x80000000

#endif /* _LMSHARE_ */
