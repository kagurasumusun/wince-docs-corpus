/* lmaudit.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 96 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _LMAUDIT_
#define _LMAUDIT_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define AA_A_ACL 32768
#define AA_A_ALL (AA_F_OPEN|AA_F_WRITE|AA_F_DELETE|AA_F_ACL)
#define AA_A_CREATE 8192
#define AA_A_DELETE 16384
#define AA_A_OPEN 2048
#define AA_A_OWNER 4
#define AA_A_WRITE 4096
#define AA_AUDIT_ALL 1
#define AA_CLOSE 8
#define AA_F_ACL 2048
#define AA_F_ALL (AA_F_OPEN|AA_F_WRITE|AA_F_DELETE|AA_F_ACL)
#define AA_F_CREATE 512
#define AA_F_DELETE 1024
#define AA_F_OPEN 256
#define AA_F_WRITE 512
#define AA_S_ACL 128
#define AA_S_ALL 253
#define AA_S_CREATE 32
#define AA_S_DELETE 64
#define AA_S_OPEN 16
#define AA_S_WRITE 32
#define ACTION_ADMINUNLOCK 1
#define ACTION_LOCKOUT 0
#define AE_ACCLIMITEXCD 17
#define AE_ACCRESTRICT 4
#define AE_ACLMOD 12
#define AE_ACLMODFAIL 19
#define AE_ADD 2
#define AE_ADMIN 2
#define AE_ADMIN_CLOSE 2
#define AE_ADMINDIS 3
#define AE_ADMINPRIVREQD 2
#define AE_AUTODIS 2
#define AE_BADPW 1
#define AE_CLOSEFILE 9
#define AE_CONNREJ 6
#define AE_CONNSTART 4
#define AE_CONNSTOP 5
#define AE_DELETE 1
#define AE_ERROR 1
#define AE_GENERAL 0
#define AE_GENERIC_TYPE 21
#define AE_GUEST 0
#define AE_LIM_DELETED 5
#define AE_LIM_DISABLED 4
#define AE_LIM_EXPIRED 2
#define AE_LIM_INVAL_WKSTA 3
#define AE_LIM_LOGONHOURS 1
#define AE_LIM_UNKNOWN 0
#define AE_LOCKOUT 20
#define AE_MOD 0
#define AE_NETLOGDENIED 16
#define AE_NETLOGOFF 15
#define AE_NETLOGON 14
#define AE_NOACCESSPERM 3
#define AE_NORMAL 0
#define AE_NORMAL_CLOSE 0
#define AE_RESACCESS 7
#define AE_RESACCESS2 18
#define AE_RESACCESSREJ 8
#define AE_SERVICESTAT 11
#define AE_SES_CLOSE 1
#define AE_SESSDIS 1
#define AE_SESSLOGOFF 2
#define AE_SESSLOGON 1
#define AE_SESSPWERR 3
#define AE_SRVCONT 2
#define AE_SRVPAUSED 1
#define AE_SRVSTART 0
#define AE_SRVSTATUS 0
#define AE_SRVSTOP 3
#define AE_UAS_GROUP 1
#define AE_UAS_MODALS 2
#define AE_UAS_USER 0
#define AE_UASMOD 13
#define AE_UNSHARE 2
#define AE_USER 1
#define AE_USERLIMIT 0
#define LOGFLAGS_BACKWARD 1
#define LOGFLAGS_FORWARD 0
#define LOGFLAGS_SEEK 2
#define SVAUD_BADNETLOGON 384
#define SVAUD_BADSESSLOGON 24
#define SVAUD_BADUSE 0x1800
#define SVAUD_GOODNETLOGON 96
#define SVAUD_GOODSESSLOGON 6
#define SVAUD_GOODUSE 0x600
#define SVAUD_LOGON (SVAUD_NETLOGON|SVAUD_SESSLOGON)
#define SVAUD_LOGONLIM 65536
#define SVAUD_NETLOGON (SVAUD_GOODNETLOGON|SVAUD_BADNETLOGON)
#define SVAUD_PERMISSIONS 16384
#define SVAUD_RESOURCE 32768
#define SVAUD_SERVICE 1
#define SVAUD_SESSLOGON (SVAUD_GOODSESSLOGON|SVAUD_BADSESSLOGON)
#define SVAUD_USE (SVAUD_GOODUSE|SVAUD_BADUSE)
#define SVAUD_USERLIST 8192

#endif /* _LMAUDIT_ */
