/* af_irda.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 2 constants, 4 declarations, 0 outlines, 0 base types, 0 extra macros, 5 extra decls
 */
#ifndef _AF_IRDA_
#define _AF_IRDA_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define IRLMP_ENUMDEVICES 0x00000010
#define SOL_IRLMP 0x00FF

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* IAS_QUERY  [struct, typedef; ce-only] */
typedef struct IAS_QUERY {
 u_char irdaDeviceID[4];
 char irdaClassName[61];
 char irdaAttribName[61];
 u_short irdaAttribType;
 union {
 int irdaAttribInt;
 struct {
 int Len;
 u_char OctetSeq[1];
 u_char Reserved[3];
 } irdaAttribOctetSeq;
 struct {
 int Len;
 u_char CharSet;
 u_char UsrStr[1];
 u_char Reserved[2];
 } irda AttribUsrStr;
 } irdaAttribute; 
} _IAS_QUERY, *PIAS_QUERY;

/* IAS_SET  [struct, typedef; ce-only] */
typedef struct _IAS_SET {
 char irdaClassName[61];
 char irdaAttribName[61];
 u_short irdaAttribType;
 union {
 int irdaAttribInt;
 struct {
 int Len;
 u_char OctetSeq[1];
 u_char Reserved[3];
 } irdaAttribOctetSeq;
 struct {
 int Len;
 u_char CharSet;
 u_char UsrStr[1];
 u_char Reserved[2];
 } irda AttribUsrStr;
 } irdaAttribute;
} _IAS_SET, *PIAS_SET;

/* IRDA_DEVICE_INFO  [struct, typedef; ce-only] */
typedef struct IRDA_DEVICE_INFO {
 u_char irdaDeviceID[4];
 char irdaDeviceName[22];
 u_char Reserved[2];
} _IRDA_DEVICE_INFO;

/* irdaServiceName  [extra struct] */
struct sockaddr_irda {  u_short irdaAddressFamily;  u_char irdaDeviceID[4];  char irdaServiceName[25];};

#endif /* _AF_IRDA_ */
