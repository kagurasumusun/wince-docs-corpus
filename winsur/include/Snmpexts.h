/* Snmpexts.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SNMPEXTS_
#define _SNMPEXTS_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* SnmpTfxClose  [function; ce-only; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
VOID WINAPI SnmpTfxClose(
 SnmpTfxHandle tfxHandle 
);

/* SnmpTfxOpen  [function; ce-only; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
SnmpTfxHandle WINAPI SnmpTfxOpen(
 DWORD numViews, 
 SnmpMibView* supportedViews 
);

/* SnmpTfxQuery  [function; ce-only; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
BOOL WINAPI SnmpTfxQuery(
 SnmpTfxHandle tfxHandle, 
 BYTE RequestType, 
 RFC1157VarBindList* pVarBindList, 
 AsnInteger* pErrorStatus, 
 AsnInteger* pErrorIndex 
);
#endif /* _WIN32_WCE */

#endif /* _SNMPEXTS_ */
