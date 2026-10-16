/* Ws2bth.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 2 constants, 6 declarations, 3 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WS2BTH_
#define _WS2BTH_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define AF_BTH 32
#define BTHPROTO_RFCOMM 3

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* BTH_HOLD_MODE  [struct; ce-only] */

/* BTH_PARK_MODE  [struct; ce-only] */

/* BTH_SNIFF_MODE  [struct; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* BTH_LOCAL_VERSION  [struct; ce-only] */
typedef struct _BTH_LOCAL_VERSION {
 unsigned char hci_version;
 unsigned short hci_revision; 
 unsigned char lmp_version;
 unsigned short lmp_subversion; 
 unsigned short manufacturer; 
 unsigned char lmp_features[8];
} BTH_LOCAL_VERSION, *PBTH_LOCAL_VERSION;

/* BTH_REMOTE_VERSION  [struct; ce-only] */
typedef struct _BTH_REMOTE_VERSION {
 unsigned char lmp_version;
 unsigned short lmp_subversion; 
 unsigned short manufacturer; 
 unsigned char lmp_features[8];
} BTH_REMOTE_VERSION, *PBTH_REMOTE_VERSION;

/* BTH_SOCKOPT_SECURITY  [struct; ce-only] */
typedef struct _BTH_SOCKOPT_SECURITY {
 int iLength; 
 bt_addr btAddr; 
 unsigned char caData[16];
} BTH_SOCKOPT_SECURITY, *PBTH_SOCKOPT_SECURITY;

#endif /* _WS2BTH_ */
