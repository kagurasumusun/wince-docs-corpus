/* lmsname.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 51 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _LMSNAME_
#define _LMSNAME_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define SERVER_DISPLAY_NAME TEXT("Server")
#define SERVICE_AFP TEXT("AFP")
#define SERVICE_ALERTER TEXT("ALERTER")
#define SERVICE_BROWSER TEXT("BROWSER")
#define SERVICE_DHCP TEXT("DHCP")
#define SERVICE_LM20_AFP SERVICE_AFP
#define SERVICE_LM20_ALERTER SERVICE_ALERTER
#define SERVICE_LM20_BROWSER SERVICE_BROWSER
#define SERVICE_LM20_DHCP SERVICE_DHCP
#define SERVICE_LM20_LMHOSTS SERVICE_LMHOSTS
#define SERVICE_LM20_MESSENGER SERVICE_MESSENGER
#define SERVICE_LM20_NBT SERVICE_NBT
#define SERVICE_LM20_NETLOGON SERVICE_NETLOGON
#define SERVICE_LM20_NETPOPUP SERVICE_NETPOPUP
#define SERVICE_LM20_NETRUN SERVICE_NETRUN
#define SERVICE_LM20_NWSAP SERVICE_NWSAP
#define SERVICE_LM20_REPL SERVICE_REPL
#define SERVICE_LM20_RIPL SERVICE_RIPL
#define SERVICE_LM20_SCHEDULE SERVICE_SCHEDULE
#define SERVICE_LM20_SERVER TEXT("SERVER")
#define SERVICE_LM20_SPOOLER SERVICE_SPOOLER
#define SERVICE_LM20_SQLSERVER SERVICE_SQLSERVER
#define SERVICE_LM20_TCPIP SERVICE_TCPIP
#define SERVICE_LM20_TELNET SERVICE_TELNET
#define SERVICE_LM20_TIMESOURCE SERVICE_TIMESOURCE
#define SERVICE_LM20_UPS SERVICE_UPS
#define SERVICE_LM20_WORKSTATION TEXT("WORKSTATION")
#define SERVICE_LM20_XACTSRV SERVICE_XACTSRV
#define SERVICE_LMHOSTS TEXT("LMHOSTS")
#define SERVICE_MESSENGER TEXT("MESSENGER")
#define SERVICE_NBT TEXT("NBT")
#define SERVICE_NETLOGON TEXT("NETLOGON")
#define SERVICE_NETPOPUP TEXT("NETPOPUP")
#define SERVICE_NETRUN TEXT("NETRUN")
#define SERVICE_NTLMSSP TEXT("NtLmSsp")
#define SERVICE_NWCS TEXT("NWCWorkstation")
#define SERVICE_NWSAP TEXT("NwSapAgent")
#define SERVICE_REPL TEXT("REPLICATOR")
#define SERVICE_RIPL TEXT("REMOTEBOOT")
#define SERVICE_SCHEDULE TEXT("Schedule")
#define SERVICE_SERVER TEXT("LanmanServer")
#define SERVICE_SPOOLER TEXT("SPOOLER")
#define SERVICE_SQLSERVER TEXT("SQLSERVER")
#define SERVICE_TCPIP TEXT("TCPIP")
#define SERVICE_TELNET TEXT("Telnet")
#define SERVICE_TIMESOURCE TEXT("TIMESOURCE")
#define SERVICE_UPS TEXT("UPS")
#define SERVICE_WORKSTATION TEXT("LanmanWorkstation")
#define SERVICE_XACTSRV TEXT("XACTSRV")
#define WORKSTATION_DISPLAY_NAME TEXT("Workstation")

#endif /* _LMSNAME_ */
