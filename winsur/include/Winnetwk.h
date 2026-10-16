/* Winnetwk.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 150 constants, 16 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WINNETWK_
#define _WINNETWK_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CONNDLG_CONN_POINT 2
#define CONNDLG_HIDE_BOX 8
#define CONNDLG_NOT_PERSIST 32
#define CONNDLG_PERSIST 16
#define CONNDLG_RO_PATH 1
#define CONNDLG_USE_MRU 4
#define CONNECT_CURRENT_MEDIA 512
#define CONNECT_INTERACTIVE 8
#define CONNECT_LOCALDRIVE 256
#define CONNECT_NEED_DRIVE 32
#define CONNECT_PROMPT 16
#define CONNECT_REDIRECT 128
#define CONNECT_REFCOUNT 64
#define CONNECT_TEMPORARY 4
#define CONNECT_UPDATE_PROFILE 1
#define CONNECT_UPDATE_RECENT 2
#define DISC_NO_FORCE 64
#define DISC_UPDATE_PROFILE 1
#define NETINFO_DISKRED 4
#define NETINFO_DLL16 1
#define NETINFO_PRINTERRED 8
#define NETPROPERTY_PERSISTENT 1
#define PFNGETPROFILEPATH PFNGETPROFILEPATHW
#define PFNPROCESSPOLICIES PFNPROCESSPOLICIESW
#define PFNRECONCILEPROFILE PFNRECONCILEPROFILEW
#define PP_DISPLAYERRORS 1
#define REMOTE_NAME_INFO_LEVEL 2
#define RESOURCE_CONNECTED 1
#define RESOURCE_CONTEXT 5
#define RESOURCE_GLOBALNET 2
#define RESOURCE_RECENT 4
#define RESOURCE_REMEMBERED 3
#define RESOURCEDISPLAYTYPE_DIRECTORY 9
#define RESOURCEDISPLAYTYPE_DOMAIN 1
#define RESOURCEDISPLAYTYPE_FILE 4
#define RESOURCEDISPLAYTYPE_GENERIC 0
#define RESOURCEDISPLAYTYPE_GROUP 5
#define RESOURCEDISPLAYTYPE_NETWORK 6
#define RESOURCEDISPLAYTYPE_ROOT 7
#define RESOURCEDISPLAYTYPE_SERVER 2
#define RESOURCEDISPLAYTYPE_SHARE 3
#define RESOURCEDISPLAYTYPE_SHAREADMIN 8
#define RESOURCEDISPLAYTYPE_TREE 10
#define RESOURCETYPE_ANY 0
#define RESOURCETYPE_DISK 1
#define RESOURCETYPE_PRINT 2
#define RESOURCETYPE_RESERVED 8
#define RESOURCETYPE_UNKNOWN 0xFFFFFFFF
#define RESOURCEUSAGE_ALL (RESOURCEUSAGE_CONNECTABLE
#define RESOURCEUSAGE_ATTACHED 0x00000010
#define RESOURCEUSAGE_CONNECTABLE 0x00000001
#define RESOURCEUSAGE_CONTAINER 0x00000002
#define RESOURCEUSAGE_NOLOCALDEVICE 0x00000004
#define RESOURCEUSAGE_RESERVED 0x80000000
#define RESOURCEUSAGE_SIBLING 0x00000008
#define RP_INIFILE 2
#define RP_LOGON 1
#define UNIVERSAL_NAME_INFO_LEVEL 1
#define WN_ACCESS_DENIED ERROR_ACCESS_DENIED
#define WN_ALREADY_CONNECTED ERROR_ALREADY_ASSIGNED
#define WN_BAD_DEV_TYPE ERROR_BAD_DEV_TYPE
#define WN_BAD_HANDLE ERROR_INVALID_HANDLE
#define WN_BAD_LEVEL ERROR_INVALID_LEVEL
#define WN_BAD_LOCALNAME ERROR_BAD_DEVICE
#define WN_BAD_NETNAME ERROR_BAD_NET_NAME
#define WN_BAD_PASSWORD ERROR_INVALID_PASSWORD
#define WN_BAD_POINTER ERROR_INVALID_ADDRESS
#define WN_BAD_PROFILE ERROR_BAD_PROFILE
#define WN_BAD_PROVIDER ERROR_BAD_PROVIDER
#define WN_BAD_USER ERROR_BAD_USERNAME
#define WN_BAD_VALUE ERROR_INVALID_PARAMETER
#define WN_CANCEL ERROR_CANCELLED
#define WN_CANNOT_OPEN_PROFILE ERROR_CANNOT_OPEN_PROFILE
#define WN_CONNECTION_CLOSED ERROR_CONNECTION_UNAVAIL
#define WN_DEVICE_ALREADY_REMEMBERED ERROR_DEVICE_ALREADY_REMEMBERED
#define WN_DEVICE_ERROR ERROR_GEN_FAILURE
#define WN_DEVICE_IN_USE ERROR_DEVICE_IN_USE
#define WN_EXTENDED_ERROR ERROR_EXTENDED_ERROR
#define WN_FUNCTION_BUSY ERROR_BUSY
#define WN_MORE_DATA ERROR_MORE_DATA
#define WN_NET_ERROR ERROR_UNEXP_NET_ERR
#define WN_NO_ERROR NO_ERROR
#define WN_NO_MORE_DEVICES ERROR_NO_MORE_DEVICES
#define WN_NO_MORE_ENTRIES ERROR_NO_MORE_ITEMS
#define WN_NO_NET_OR_BAD_PATH ERROR_NO_NET_OR_BAD_PATH
#define WN_NO_NETWORK ERROR_NO_NETWORK
#define WN_NOT_AUTHENTICATED ERROR_NOT_AUTHENTICATED
#define WN_NOT_CONNECTED ERROR_NOT_CONNECTED
#define WN_NOT_CONTAINER ERROR_NOT_CONTAINER
#define WN_NOT_INITIALIZING ERROR_ALREADY_INITIALIZED
#define WN_NOT_LOGGED_ON ERROR_NOT_LOGGED_ON
#define WN_NOT_SUPPORTED ERROR_NOT_SUPPORTED
#define WN_NOT_VALIDATED ERROR_NO_LOGON_SERVERS
#define WN_OPEN_FILES ERROR_OPEN_FILES
#define WN_OUT_OF_MEMORY ERROR_NOT_ENOUGH_MEMORY
#define WN_RETRY ERROR_RETRY
#define WN_SUCCESS NO_ERROR
#define WN_WINDOWS_ERROR ERROR_UNEXP_NET_ERR
#define WNCON_DYNAMIC 8
#define WNCON_FORNETCARD 1
#define WNCON_NOTROUTED 2
#define WNCON_SLOWLINK 4
#define WNFMT_ABBREVIATED 2
#define WNFMT_CONNECTION 32
#define WNFMT_INENUM 16
#define WNFMT_MULTILINE 1
#define WNNC_CRED_MANAGER 0xFFFF0000
#define WNNC_NET_10NET 0x00050000
#define WNNC_NET_3IN1 0x00270000
#define WNNC_NET_9TILES 0x00090000
#define WNNC_NET_APPLETALK 0x00130000
#define WNNC_NET_AS400 0x000B0000
#define WNNC_NET_AVID 0x001A0000
#define WNNC_NET_BMC 0x00180000
#define WNNC_NET_BWNFS 0x00100000
#define WNNC_NET_CLEARCASE 0x00160000
#define WNNC_NET_COGENT 0x00110000
#define WNNC_NET_CSC 0x00260000
#define WNNC_NET_DCE 0x00190000
#define WNNC_NET_DECORB 0x00200000
#define WNNC_NET_DISTINCT 0x00230000
#define WNNC_NET_DOCUSPACE 0x001B0000
#define WNNC_NET_EXTENDNET 0x00290000
#define WNNC_NET_FARALLON 0x00120000
#define WNNC_NET_FJ_REDIR 0x00220000
#define WNNC_NET_FRONTIER 0x00170000
#define WNNC_NET_FTP_NFS 0x000C0000
#define WNNC_NET_HOB_NFS 0x00320000
#define WNNC_NET_IBMAL 0x00340000
#define WNNC_NET_INTERGRAPH 0x00140000
#define WNNC_NET_LANMAN 0x00020000
#define WNNC_NET_LANSTEP 0x00080000
#define WNNC_NET_LANTASTIC 0x000A0000
#define WNNC_NET_LIFENET 0x000E0000
#define WNNC_NET_LOCUS 0x00060000
#define WNNC_NET_MANGOSOFT 0x001C0000
#define WNNC_NET_MASFAX 0x00310000
#define WNNC_NET_MSNET 0x00010000
#define WNNC_NET_NETWARE 0x00030000
#define WNNC_NET_OBJECT_DIRE 0x00300000
#define WNNC_NET_PATHWORKS 0x000D0000
#define WNNC_NET_POWERLAN 0x000F0000
#define WNNC_NET_PROTSTOR 0x00210000
#define WNNC_NET_RDR2SAMPLE 0x00250000
#define WNNC_NET_SERNET 0x001D0000
#define WNNC_NET_SHIVA 0x00330000
#define WNNC_NET_SUN_PC_NFS 0x00070000
#define WNNC_NET_SYMFONET 0x00150000
#define WNNC_NET_TWINS 0x00240000
#define WNNC_NET_VINES 0x00040000

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CONNECTDLGSTRUCT  [struct, typedef; shared; A/W CONNECTDLGSTRUCTA,CONNECTDLGSTRUCTW (CE is W-side)] */
typedef struct {
 DWORD cbStructure;
 HWND hwndOwner;
 LPNETRESOURCE lpConnRes;
 DWORD dwFlags;
 DWORD dwDevNum;
} CONNECTDLGSTRUCT;
typedef CONNECTDLGSTRUCT *PCONNECTDLGSTRUCT, *LPCONNECTDLGSTRUCT;

/* DISCDLGSTRUCT  [struct, typedef; shared; A/W DISCDLGSTRUCTA,DISCDLGSTRUCTW (CE is W-side)] */
typedef struct _wcesdk_win32_DISCDLGSTRUCT_str{
 DWORD cbStructure;
 HWND hwndOwner;
 LPTSTR lpLocalName;
 LPTSTR lpRemoteName;
 DWORD dwFlags;
} DISCDLGSTRUCT;
typedef DISCDLGSTRUCT *PDISCDLGSTRUCT, *LPDISCDLGSTRUCT;

/* NETRESOURCE  [struct, typedef; shared; A/W NETRESOURCEA,NETRESOURCEW (CE is W-side)] */
typedef struct _NETRESOURCE {
 DWORD dwScope; 
 DWORD dwType; 
 DWORD dwDisplayType; 
 DWORD dwUsage; 
 LPTSTR lpLocalName; 
 LPTSTR lpRemoteName; 
 LPTSTR lpComment; 
 LPTSTR lpProvider; 
} NETRESOURCE;
typedef NETRESOURCE *PNETRESOURCE, *LPNETRESOURCE;

/* REMOTE_NAME_INFO  [struct, typedef; shared; A/W REMOTE_NAME_INFOA,REMOTE_NAME_INFOW (CE is W-side)] */
typedef struct _REMOTE_NAME_INFO {
 LPTSTR lpUniversalName; 
 LPTSTR lpConnectionName; 
 LPTSTR lpRemainingPath;
} REMOTE_NAME_INFO;
typedef REMOTE_NAME_INFO *PREMOTE_NAME_INFO, *LPREMOTE_NAME_INFO;

/* UNIVERSAL_NAME_INFO  [struct, typedef; shared; A/W UNIVERSAL_NAME_INFOA,UNIVERSAL_NAME_INFOW (CE is W-side)] */
typedef struct _UNIVERSAL_NAME_INFO {
 LPTSTR lpUniversalName;
} UNIVERSAL_NAME_INFO;
typedef UNIVERSAL_NAME_INFO *PUNIVERSAL_NAME_INFO, *LPUNIVERSAL_NAME_INFO;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..699 */

/* WNetAddConnection3  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Redir.lib, redir.lib; A/W WNetAddConnection3A,WNetAddConnection3W (CE is W-side)] */
DWORD WNetAddConnection3(
 HWND hwndOwner, 
 LPNETRESOURCE lpNetResource, 
 LPTSTR lpPassword, 
 LPTSTR lpUserName, 
 DWORD dwFlags 
);

/* WNetCancelConnection2  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Redir.lib, redir.lib; A/W WNetCancelConnection2A,WNetCancelConnection2W (CE is W-side)] */
DWORD WNetCancelConnection2(
 LPTSTR lpName, 
 DWORD dwFlags, 
 BOOL fForce 
);

/* WNetCloseEnum  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Redir.lib, redir.lib] */
DWORD WNetCloseEnum(
 HANDLE hEnum 
);

/* WNetConnectionDialog1  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Redir.lib, redir.lib; A/W WNetConnectionDialog1A,WNetConnectionDialog1W (CE is W-side)] */
DWORD WNetConnectionDialog1(
 LPCONNECTDLGSTRUCT lpConnectDlgStruct 
);

/* WNetDisconnectDialog  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Redir.lib, redir.lib] */
DWORD WNetDisconnectDialog(
 HWND hwnd,
 DWORD dwType
);

/* WNetDisconnectDialog1  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Redir.lib, redir.lib; A/W WNetDisconnectDialog1A,WNetDisconnectDialog1W (CE is W-side)] */
DWORD WNetDisconnectDialog1(
 LPDISCDLGSTRUCT lpDiscDlgStruct 
);

/* WNetEnumResource  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Redir.lib, redir.lib; A/W WNetEnumResourceA,WNetEnumResourceW (CE is W-side)] */
DWORD WNetEnumResource( 
 HANDLE hEnum, 
 LPDWORD lpcCount, 
 LPVOID lpBuffer, 
 LPDWORD lpBufferSize 
);

/* WNetGetConnection  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Redir.lib, redir.lib; A/W WNetGetConnectionA,WNetGetConnectionW (CE is W-side)] */
DWORD WNetGetConnection( 
 LPCTSTR lpLocalName, 
 LPTSTR lpRemoteName, 
 LPDWORD lpnLength 
);

/* WNetGetUniversalName  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Redir.lib, redir.lib; A/W WNetGetUniversalNameA,WNetGetUniversalNameW (CE is W-side)] */
DWORD WNetGetUniversalName(
 LPCTSTR lpLocalPath, 
 DWORD dwInfoLevel, 
 LPVOID lpBuffer, 
 LPDWORD lpBufferSize 
);

/* WNetGetUser  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Redir.lib, redir.lib; A/W WNetGetUserA,WNetGetUserW (CE is W-side)] */
DWORD WNetGetUser( 
 LPCTSTR lpName, 
 LPTSTR lpUserName, 
 LPDWORD lpnLength 
);

/* WNetOpenEnum  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Redir.lib, redir.lib; A/W WNetOpenEnumA,WNetOpenEnumW (CE is W-side)] */
DWORD WNetOpenEnum(
 DWORD dwScope, 
 DWORD dwType, 
 DWORD dwUsage, 
 LPNETRESOURCE lpNetResource, 
 LPHANDLE lphEnum 
);
#endif /* _WIN32_WCE */

#endif /* _WINNETWK_ */
