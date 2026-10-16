/* Avc_unit.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 12 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _AVC_UNIT_
#define _AVC_UNIT_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* UNIT_AllocateLocalPlug_Request  [struct; ce-only] */
typedef struct {PVOID ualp_RegistrationToken;STREAM_MediaType ualp_MediaType;ULONG ualp_Direction;ULONG ualp_Flags;ULONG ualp_SubunitPlugID;union { ULONG ualp_MaximumThroughput; struct {ULONG ualp_ClusterDimension;ULONG ualp_SampleFrequency; }; };} UNIT_AllocateLocalPlug_Request;
typedef UNIT_AllocateLocalPlug_Request *PUNIT_AllocateLocalPlug_Request, *LPUNIT_AllocateLocalPlug_Request;

/* UNIT_AllocateLocalPlug_Response  [struct; ce-only] */
typedef struct {HANDLE ualp_Plug;ULONG ualp_PlugNumber;} UNIT_AllocateLocalPlug_Response;
typedef UNIT_AllocateLocalPlug_Response *PUNIT_AllocateLocalPlug_Response, *LPUNIT_AllocateLocalPlug_Response;

/* UNIT_ConnectionRequestProcessed_Request  [struct; ce-only] */
typedef struct {PVOID ucrp_RegistrationToken;PVOID ucrp_Request;NTSTATUS ucrp_Status;} UNIT_ConnectionRequestProcessed_Request;
typedef UNIT_ConnectionRequestProcessed_Request *PUNIT_ConnectionRequestProcessed_Request, *LPUNIT_ConnectionRequestProcessed_Request;

/* UNIT_DereferenceConnectionPlug_Request  [struct; ce-only] */
typedef struct {PVOID udcp_RegistrationToken;HANDLE udcp_Plug;} UNIT_DereferenceConnectionPlug_Request;
typedef UNIT_DereferenceConnectionPlug_Request *PUNIT_DereferenceConnectionPlug_Request, *LPUNIT_DereferenceConnectionPlug_Request;

/* UNIT_FreeLocalPlug_Request  [struct; ce-only] */
typedef struct {PVOID uflp_RegistrationToken;HANDLE uflp_Plug;} UNIT_FreeLocalPlug_Request;
typedef UNIT_FreeLocalPlug_Request *PUNIT_FreeLocalPlug_Request, *LPUNIT_FreeLocalPlug_Request;

/* UNIT_ProcessRegistryPlugs_Request  [struct; ce-only] */
typedef struct {PVOID uprp_RegistrationToken;HANDLE uprp_RootKey;} UNIT_ProcessRegistryPlugs_Request;
typedef UNIT_ProcessRegistryPlugs_Request *PUNIT_ProcessRegistryPlugs_Request, *LPUNIT_ProcessRegistryPlugs_Request;

/* UNIT_QueryLocalPlugs_Request  [struct; ce-only] */
typedef struct {PVOID uqlp_RegistrationToken;ULONG uqlp_Flags;} UNIT_QueryLocalPlugs_Request;
typedef UNIT_QueryLocalPlugs_Request *PUNIT_QueryLocalPlugs_Request, *LPUNIT_QueryLocalPlugs_Request;

/* UNIT_QueryLocalPlugs_Response  [struct; ce-only] */
typedef struct {BOOL uqlp_PlugState;ULONG uqlp_PlugNumber;ULONG uqlp_Direction;ULONG uqlp_MediaType;HANDLE uqlp_Plug;} UNIT_QueryLocalPlugs_Response;
typedef UNIT_QueryLocalPlugs_Response *PUNIT_QueryLocalPlugs_Response, *LPUNIT_QueryLocalPlugs_Response;

/* UNIT_RegisterSubunit_Response  [struct; ce-only] */
typedef struct {PVOID urs_RegistrationToken;} UNIT_RegisterSubunit_Response;
typedef UNIT_RegisterSubunit_Response *PUNIT_RegisterSubunit_Response, *LPUNIT_RegisterSubunit_Response;

#endif /* _AVC_UNIT_ */
