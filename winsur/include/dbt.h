/* dbt.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 53 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _DBT_
#define _DBT_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define BSF_ALLOWSFW 0x00000080
#define BSF_FLUSHDISK 0x00000004
#define BSF_FORCEIFHUNG 0x00000020
#define BSF_IGNORECURRENTTASK 0x00000002
#define BSF_LUID 0x00000400
#define BSF_MSGSRV32ISOK 0x80000000
#define BSF_MSGSRV32ISOK_BIT 31
#define BSF_NOHANG 0x00000008
#define BSF_NOTIMEOUTIFNOTHUNG 0x00000040
#define BSF_POSTMESSAGE 0x00000010
#define BSF_QUERY 0x00000001
#define BSF_RETURNHDESK 0x00000200
#define BSF_SENDNOTIFYMESSAGE 0x00000100
#define BSM_ALLCOMPONENTS 0
#define BSM_ALLDESKTOPS 16
#define BSM_APPLICATIONS 8
#define BSM_INSTALLABLEDRIVERS 4
#define BSM_NETDRIVER 2
#define BSM_VXDS 1
#define DBT_APPYBEGIN 0
#define DBT_APPYEND 1
#define DBT_CONFIGCHANGECANCELED 0x19
#define DBT_CONFIGCHANGED 0x18
#define DBT_CONFIGMGAPI32 34
#define DBT_CONFIGMGPRIVATE 0x7FFF
#define DBT_DEVICEARRIVAL 0x8000
#define DBT_DEVICEQUERYREMOVE 0x8001
#define DBT_DEVICEQUERYREMOVEFAILED 0x8002
#define DBT_DEVICEREMOVECOMPLETE 0x8004
#define DBT_DEVICEREMOVEPENDING 0x8003
#define DBT_DEVICETYPESPECIFIC 0x8005
#define DBT_DEVNODES_CHANGED 7
#define DBT_DEVTYP_DEVICEINTERFACE 5
#define DBT_DEVTYP_DEVNODE 1
#define DBT_DEVTYP_HANDLE 6
#define DBT_DEVTYP_NET 4
#define DBT_DEVTYP_OEM 0
#define DBT_DEVTYP_PORT 3
#define DBT_DEVTYP_VOLUME 2
#define DBT_MONITORCHANGE 0x1B
#define DBT_NO_DISK_SPACE 0x47
#define DBT_QUERYCHANGECONFIG 0x17
#define DBT_SHELLLOGGEDON 32
#define DBT_USERDEFINED 0xFFFF
#define DBT_VOLLOCKLOCKFAILED 0x8043
#define DBT_VOLLOCKLOCKRELEASED 0x8045
#define DBT_VOLLOCKLOCKTAKEN 0x8042
#define DBT_VOLLOCKQUERYLOCK 0x8041
#define DBT_VOLLOCKQUERYUNLOCK 0x8044
#define DBT_VOLLOCKUNLOCKFAILED 0x8046
#define DBT_VXDINITCOMPLETE 35
#define DBTF_MEDIA 1
#define DBTF_NET 2

#endif /* _DBT_ */
