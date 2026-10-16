/* simmgr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 50 constants, 37 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SIMMGR_
#define _SIMMGR_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define SIM_E_BADPARAM 0
#define SIM_E_BUFFERTOOSMALL 0
#define SIM_E_CORPPINREQUIRED 0
#define SIM_E_CORPPUKREQUIRED 0
#define SIM_E_EMPTYINDEX 0
#define SIM_E_INCORRECTPASSWORD 0
#define SIM_E_INVALIDINDEX 0
#define SIM_E_MEMORYFAILURE 0
#define SIM_E_MEMORYFULL 0
#define SIM_E_MOBILEERROR 0
#define SIM_E_NETWKPINREQUIRED 0
#define SIM_E_NETWKPUKREQUIRED 0
#define SIM_E_NETWORKERROR 0
#define SIM_E_NOSIM 0
#define SIM_E_NOSIMMSGSTORAGE 0
#define SIM_E_NOTFOUND 0
#define SIM_E_NOTREADY 0
#define SIM_E_NOTTEXTMESSAGE 0
#define SIM_E_PHFSIMPINREQUIRED 0
#define SIM_E_PHFSIMPUKREQUIRED 0
#define SIM_E_PHSIMPINREQUIRED 0
#define SIM_E_RADIONOTPRESENT 0
#define SIM_E_RADIOOFF 0
#define SIM_E_SECURITYFAILURE 0
#define SIM_E_SIMBUSY 0
#define SIM_E_SIMDOWNLOADERROR 0
#define SIM_E_SIMFAILURE 0
#define SIM_E_SIMMSGSTORAGEFULL 0
#define SIM_E_SIMNOTINSERTED 0
#define SIM_E_SIMPIN2REQUIRED 0
#define SIM_E_SIMPINREQUIRED 0
#define SIM_E_SIMPUK2REQUIRED 0
#define SIM_E_SIMPUKREQUIRED 0
#define SIM_E_SIMTOOLKITBUSY 0
#define SIM_E_SIMWRONG 0
#define SIM_E_SUBSETPINREQUIRED 0
#define SIM_E_SUBSETPUKREQUIRED 0
#define SIM_E_SVCPINREQUIRED 0
#define SIM_E_SVCPUKREQUIRED 0
#define SIM_E_UNDETERMINED 0
#define SIM_E_UNSUPPORTED 0
#define SIM_INIT_SIMCARD_NOTIFICATIONS 0x00000001
#define SIM_RECORDTYPE_CYCLIC 0x00000002
#define SIM_RECORDTYPE_DEDICATED 0x00000005
#define SIM_RECORDTYPE_LINEAR 0x00000003
#define SIM_RECORDTYPE_MASTER 0x00000004
#define SIM_RECORDTYPE_TRANSPARENT 0x00000001
#define SIM_RECORDTYPE_UNKNOWN 0x00000000
#define SIM_SMSSTORAGE_BROADCAST 0
#define SIM_SMSSTORAGE_SIM 0

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* SIMLOCKINGPWDLENGTH  [struct; ce-only] */
typedef struct simlockingpwdlength {
 DWORD dwFacility;
 DWORD dwPasswordLength;
} SIMLOCKINGPWDLENGTH, FAR *LPSIMLOCKINGPWDLENGTH;

/* SIMMESSAGECHANGE  [struct; ce-only] */
typedef struct simmessagechange_tag {
 DWORD dwEntry;
 DWORD dwStorage;
} SIMMESSAGECHANGE, FAR *LPSIMMESSAGECHANGE;

/* SIMPBECHANGE  [struct; ce-only] */
typedef struct simpbechange_tag {
 DWORD dwEntry;
 DWORD dwStorage;
} SIMPBECHANGE, FAR *LPSIMPBECHANGE;

/* SIMRECORDINFO  [struct; ce-only] */
typedef struct simrecordinfo_tag {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwRecordType;
 DWORD dwItemCount;
 DWORD dwSize;
} SIMRECORDINFO, FAR *LPSIMRECORDINFO;

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* SIMCALLBACK  [callback; ce-only; CE 6.0..699; cellcore.lib] */
typedef void (*SIMCALLBACK) (
 DWORD dwNotifyCode,
 const void* pData,
 DWORD dwDataSize,
 DWORD dwParam
);
#endif /* _WIN32_WCE */

#endif /* _SIMMGR_ */
