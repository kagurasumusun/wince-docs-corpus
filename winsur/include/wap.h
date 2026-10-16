/* wap.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 19 declarations, 0 outlines, 0 base types, 0 extra macros, 6 extra decls
 */
#ifndef _WAP_
#define _WAP_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* WAP_ADDRESS_TYPE  [enum; ce-only] */
enum WAP_ADDRESS_TYPE{
 WAP_ADDRESS_TYPE_UDP = 1,
 WAP_ADDRESS_TYPE_GSM_SMS
};

/* WAP_LAYER  [enum; ce-only] */
enum WAP_LAYER{
 WAP_LAYER_WDP = 1,
 WAP_LAYER_WTLS,
 WAP_LAYER_WTP,
 WAP_LAYER_WSP,
 WAP_LAYER_WAE
};

/* WAP_PRIMITIVE_ID  [enum; ce-only] */
enum WAP_PRIMITIVE_ID{
 WAP_PRIMITIVE_ID_T_DUNITDATA = 1,
 WAP_PRIMITIVE_ID_TR_INVOKE,
 WAP_PRIMITIVE_ID_TR_RESULT,
 WAP_PRIMITIVE_ID_TR_ABORT
};

/* WAP_PRIMITIVE_TYPE  [enum; ce-only] */
enum WAP_PRIMITIVE_TYPE{
 WAP_PRIMITIVE_TYPE_REQUEST = 1,
 WAP_PRIMITIVE_TYPE_INDICATION,
 WAP_PRIMITIVE_TYPE_RESPONSE,
 WAP_PRIMITIVE_TYPE_CONFIRM
};

/* WTP_TRANSACTION_CLASS_TYPE  [enum; ce-only] */
enum WTP_TRANSACTION_CLASS_TYPE{
 WTP_TRANSACTION_CLASS_TYPE_0 = 1,
 WTP_TRANSACTION_CLASS_TYPE_1,
 WTP_TRANSACTION_CLASS_TYPE_2
};

/* WTP_TRANSACTION_HANDLE  [typedef; ce-only] */
typedef LONG WTP_TRANSACTION_HANDLE;

/* WTP_TRANSACTION_SECURITY_LEVEL  [enum; ce-only] */
enum WTP_TRANSACTION_SECURITY_LEVEL
{
 WTP_TRANSACTION_SECURITY_LEVEL_NOTSECURE = 1,
 WTP_TRANSACTION_SECURITY_LEVEL_SECURENOAUTH, 
 WTP_TRANSACTION_SECURITY_LEVEL_GATEWAYAUTH,
};

/* WAP_PRIMITIVE_BASE  [struct; ce-only] */
typedef struct wap_primitive_base_tag{
 WAP_PRIMITIVE_ID wpiPrimitiveID;
 WAP_PRIMITIVE_TYPE wptPrimitiveType;
 DWORD dwValidFields;
} WAP_PRIMITIVE_BASE;
typedef WAP_PRIMITIVE_BASE *PWAP_PRIMITIVE_BASE, *LPWAP_PRIMITIVE_BASE;

/* WTP_ABORT  [struct; ce-only] */
typedef struct wtp_abort_tag{
 WAP_PRIMITIVE_ID wpiPrimitiveID;
 WAP_PRIMITIVE_TYPE wptPrimitiveType;
 DWORD dwValidFields;
 BYTE bAbortCode;
 WTP_TRANSACTION_HANDLE wthTransactionHandle;
} WTP_ABORT;
typedef WTP_ABORT *PWTP_ABORT, *LPWTP_ABORT;

/* WTP_RESULT  [struct; ce-only] */
typedef struct wtp_result_tag{
 WAP_PRIMITIVE_ID wpiPrimitiveID;
 WAP_PRIMITIVE_TYPE wptPrimitiveType;
 DWORD dwValidFields;
 const BYTE* pbUserData;
 DWORD dwUserDataSize;
 const BYTE* pbExitInfo;
 DWORD dwExitInfoSize;
 WTP_TRANSACTION_HANDLE wthTransactionHandle 
 WTP_TRANSACTION_SECURITY_LEVEL wtslTransactionSecurityLevel;
} WTP_RESULT;
typedef WTP_RESULT *PWTP_RESULT, *LPWTP_RESULT;

/* WAP_PRIMITIVE_TYPE_CONFIRM  [extra enum] */
enum WAP_PRIMITIVE_TYPE{
  WAP_PRIMITIVE_TYPE_REQUEST = 1,
  WAP_PRIMITIVE_TYPE_INDICATION,
  WAP_PRIMITIVE_TYPE_RESPONSE,
  WAP_PRIMITIVE_TYPE_CONFIRM
};

/* WAP_LAYER_WAE  [extra enum] */
enum WAP_LAYER{
  WAP_LAYER_WDP = 1,
  WAP_LAYER_WTLS,
  WAP_LAYER_WTP,
  WAP_LAYER_WSP,
  WAP_LAYER_WAE
};

/* WAP_ADDRESS_TYPE_GSM_SMS  [extra enum] */
enum WAP_ADDRESS_TYPE{ WAP_ADDRESS_TYPE_UDP = 1, WAP_ADDRESS_TYPE_GSM_SMS };

/* WTP_TRANSACTION_SECURITY_LEVEL_GATEWAYAUTH  [extra enum] */
enum WTP_TRANSACTION_SECURITY_LEVEL
{
  WTP_TRANSACTION_SECURITY_LEVEL_NOTSECURE = 1,
  WTP_TRANSACTION_SECURITY_LEVEL_SECURENOAUTH,
  WTP_TRANSACTION_SECURITY_LEVEL_GATEWAYAUTH,
};

/* WTP_TRANSACTION_CLASS_TYPE_2  [extra enum] */
enum WTP_TRANSACTION_CLASS_TYPE{
  WTP_TRANSACTION_CLASS_TYPE_0 = 1,
  WTP_TRANSACTION_CLASS_TYPE_1,
  WTP_TRANSACTION_CLASS_TYPE_2
};

/* WAP_PRIMITIVE_ID_TR_ABORT  [extra enum] */
enum WAP_PRIMITIVE_ID{
  WAP_PRIMITIVE_ID_T_DUNITDATA = 1,
  WAP_PRIMITIVE_ID_TR_INVOKE,
  WAP_PRIMITIVE_ID_TR_RESULT,
  WAP_PRIMITIVE_ID_TR_ABORT
};

#endif /* _WAP_ */
