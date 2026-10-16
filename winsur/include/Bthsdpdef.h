/* Bthsdpdef.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 3 constants, 9 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _BTHSDPDEF_
#define _BTHSDPDEF_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define SDP_ATTRIB_PROTOCOL_DESCRIPTOR_LIST 0x4
#define SDP_CHANNEL_OFFSET 32
#define SDP_RECORD_SIZE 0x00000043

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* BTHNS_SETBLOB  [struct; ce-only] */
typedef struct _BTHNS_SETBLOB {
 ULONG* pRecordHandle;
 ULONG fSecurity;
 ULONG fOptions;
 ULONG ulRecordLength;
 UCHAR pRecord[1];
} BTHNS_SETBLOB, *PBTHNS_SETBLOB;

/* NODECONTAINERTYPE  [enum; ce-only] */
typedef enum {
 NODECONTAINERTYPESEQUENCE = 0,
 NODECONTAINERTYPEALTERNATIVE = NodeContainerTypeSequence + 1
} NODECONTAINERTYPE;
typedef NODECONTAINERTYPE *PNODECONTAINERTYPE, *LPNODECONTAINERTYPE;

/* SDP_SPECIFICTYPE  [enum; ce-only] */
typedef enum {
 SDP_ST_NONE = 0x0000,
 SDP_ST_UINT8 = 0x0010,
 SDP_ST_UINT16 = 0x0110,
 SDP_ST_UINT32 = 0x0210,
 SDP_ST_UINT64 = 0x0310,
 SDP_ST_UINT128 = 0x0410,
 SDP_ST_INT8 = 0x0020,
 SDP_ST_INT16 = 0x0120,
 SDP_ST_INT32 = 0x0220,
 SDP_ST_INT64 = 0x0320,
 SDP_ST_INT128 = 0x0420,
 SDP_ST_UUID16 = 0x0130,
 SDP_ST_UUID32 = 0x0220,
 SDP_ST_UUID128 = 0x0430
} SDP_SPECIFICTYPE;
typedef SDP_SPECIFICTYPE *PSDP_SPECIFICTYPE, *LPSDP_SPECIFICTYPE;

/* SDP_TYPE  [enum; ce-only] */
typedef enum {
 SDP_TYPE_NIL = 0x00,
 SDP_TYPE_UINT = 0x01,
 SDP_TYPE_INT = 0x02,
 SDP_TYPE_UUID = 0x03,
 SDP_TYPE_STRING = 0x04,
 SDP_TYPE_BOOLEAN = 0x05,
 SDP_TYPE_SEQUENCE = 0x06,
 SDP_TYPE_ALTERNATIVE = 0x07,
 SDP_TYPE_URL = 0x08,
 SDP_TYPE_CONTAINER = 0x20
} SDP_TYPE;
typedef SDP_TYPE *PSDP_TYPE, *LPSDP_TYPE;

/* SdpAttributeRange  [struct; shared] */
struct _SdpAttributeRange {
 USHORT minAttribute;
 USHORT maxAttribute;
} SdpAttributeRange;

/* SdpQueryUuid  [struct; shared] */
typedef struct _SdpQueryUuid {
 SdpQueryUuidUnion u;
 USHORT uuidType;
} SdpQueryUuid;
typedef SdpQueryUuid *PSdpQueryUuid, *LPSdpQueryUuid;

#endif /* _BTHSDPDEF_ */
