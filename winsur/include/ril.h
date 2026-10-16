/* ril.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 3 constants, 242 declarations, 1 outlines, 0 base types, 0 extra macros, 5 extra decls
 */
#ifndef _RIL_
#define _RIL_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define RIL_PARAM_NITZ_DAYLIGHTSAVINGOFFSET 0x00000004
#define RIL_PARAM_NITZ_SYSTEMTIME 0x00000001
#define RIL_PARAM_NITZ_TIMEZONEOFFSET 0x00000002

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* RILNDISIPCONFIG  [struct; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* RILAUDIODEVICEINFO  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwTxDevice;
 DWORD dwRxDevice;
} RILAUDIODEVICEINFO;
typedef RILAUDIODEVICEINFO *PRILAUDIODEVICEINFO, *LPRILAUDIODEVICEINFO;

/* RILBEARERSVCINFO  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwSpeed;
 DWORD dwServiceName;
 DWORD dwConnectionElement;
} RILBEARERSVCINFO;
typedef RILBEARERSVCINFO *PRILBEARERSVCINFO, *LPRILBEARERSVCINFO;

/* RILBYTECOUNTER  [struct; ce-only; Ril.lib] */
typedef struct rilbytecounter_tag {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwRxByte;
 DWORD dwTxByte;
 DWORD dwTotalByte;
} RILBYTECOUNTER, *LPRILBYTECOUNTER;

/* RILCALLERIDSETTINGS  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwStatus;
 DWORD dwProvisioning;
} RILCALLERIDSETTINGS;
typedef RILCALLERIDSETTINGS *PRILCALLERIDSETTINGS, *LPRILCALLERIDSETTINGS;

/* RILCALLHSCSDINFO  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwRxTimeslots;
 DWORD dwTxTimeslots;
 DWORD dwAirInterfaceUserRat;
 DWORD dwChannelCoding;
} RILCALLHSCSDINFO;
typedef RILCALLHSCSDINFO *PRILCALLHSCSDINFO, *LPRILCALLHSCSDINFO;

/* RILCAPSBARRINGPWDLENGTH  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwType;
 DWORD dwPasswordLength;
} RILCAPSBARRINGPWDLENGTH;
typedef RILCAPSBARRINGPWDLENGTH *PRILCAPSBARRINGPWDLENGTH, *LPRILCAPSBARRINGPWDLENGTH;

/* RILCAPSBEARERSVC  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwSpeeds1;
 DWORD dwSpeeds2;
 DWORD dwServiceNames;
 DWORD dwConnectionElements;
} RILCAPSBEARERSVC;
typedef RILCAPSBEARERSVC *PRILCAPSBEARERSVC, *LPRILCAPSBEARERSVC;

/* RILCAPSDIAL  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwCallTypes;
 DWORD dwOptions;
} RILCAPSDIAL;
typedef RILCAPSDIAL *PRILCAPSDIAL, *LPRILCAPSDIAL;

/* RILCAPSERRORCORRECTION  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwOriginalRequest;
 DWORD dwOriginalFallback;
 DWORD dwAnswererFallback;
} RILCAPSERRORCORRECTION, *LPRILCAPSERRORCORRECTION;

/* RILCAPSLOCKINGPWDLENGTH  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwFacility;
 DWORD dwPasswordLength;
} RILCAPSLOCKINGPWDLENGTH;
typedef RILCAPSLOCKINGPWDLENGTH *PRILCAPSLOCKINGPWDLENGTH, *LPRILCAPSLOCKINGPWDLENGTH;

/* RILCAPSMSGMEMORYLOCATIONS  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwReadLocations;
 DWORD dwWriteLocations;
 DWORD dwStoreLocations;
} RILCAPSMSGMEMORYLOCATIONS;
typedef RILCAPSMSGMEMORYLOCATIONS *PRILCAPSMSGMEMORYLOCATIONS, *LPRILCAPSMSGMEMORYLOCATIONS;

/* RILCAPSPBENTRYLENGTH  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwMaxAddressLength;
 DWORD dwMaxTextLength;
} RILCAPSPBENTRYLENGTH, *LPRILCAPSPBENTRYLENGTH;

/* RILCLOSEDGROUPSETTINGS  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwStatus;
 DWORD dwIndex;
 DWORD dwInfo;
} RILCLOSEDGROUPSETTINGS;
typedef RILCLOSEDGROUPSETTINGS *PRILCLOSEDGROUPSETTINGS, *LPRILCLOSEDGROUPSETTINGS;

/* RILCONNECTINFO  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwCallType;
 DWORD dwBaudRate;
} RILCONNECTINFO;
typedef RILCONNECTINFO *PRILCONNECTINFO, *LPRILCONNECTINFO;

/* RILDATACOMPINFO  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwDirection;
 DWORD dwNegotiation;
 DWORD dwMaxDictEntries;
 DWORD dwMaxStringLength;
} RILDATACOMPINFO;
typedef RILDATACOMPINFO *PRILDATACOMPINFO, *LPRILDATACOMPINFO;

/* RILDIALEDIDSETTINGS  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwStatus;
 DWORD dwProvisioning;
} RILDIALEDIDSETTINGS;
typedef RILDIALEDIDSETTINGS *PRILDIALEDIDSETTINGS, *LPRILDIALEDIDSETTINGS;

/* RILDIALINFO  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 HRESULT hrCmdId;
 DWORD dwCallId;
} RILDIALINFO;
typedef RILDIALINFO *PRILDIALINFO, *LPRILDIALINFO;

/* RILEMLPPPRIORITY  [struct; ce-only; Ril.lib] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwPriority;
 DWORD dwMaxPriority;
}RILEMLPPPRIORITY;
typedef RILEMLPPPRIORITY *PRILEMLPPPRIORITY, *LPRILEMLPPPRIORITY;

/* RILENTERGPRSDATAMODE  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwL2Protocol;
 DWORD dwNumContexts;
 DWORD dwContextID[];
} RILENTERGPRSDATAMODE;
typedef RILENTERGPRSDATAMODE *PRILENTERGPRSDATAMODE, *LPRILENTERGPRSDATAMODE;

/* RILEQUIPMENTSTATE  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwRadioSupport;
 DWORD dwEqState;
 DWORD dwReadyState;
} RILEQUIPMENTSTATE;
typedef RILEQUIPMENTSTATE *PRILEQUIPMENTSTATE, *LPRILEQUIPMENTSTATE;

/* RILERRORCORRECTIONINFO  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwOriginalRequest;
 DWORD dwOriginalFallback;
 DWORD dwAnswererFallback;
} RILERRORCORRECTIONINFO;
typedef RILERRORCORRECTIONINFO *PRILERRORCORRECTIONINFO, *LPRILERRORCORRECTIONINFO;

/* RILGAININFO  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwTxGain;
 DWORD dwRxGain;
} RILGAININFO;
typedef RILGAININFO *PRILGAININFO, *LPRILGAININFO;

/* RILGPRSANSWER  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
} RILGPRSANSWER;
typedef RILGPRSANSWER *PRILGPRSANSWER, *LPRILGPRSANSWER;

/* RILGPRSCONTEXTACTIVATED  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwContextID;
 BOOL fActivated;
} RILGPRSCONTEXTACTIVATED;
typedef RILGPRSCONTEXTACTIVATED *PRILGPRSCONTEXTACTIVATED, *LPRILGPRSCONTEXTACTIVATED;

/* RILGPRSQOSPROFILE  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwContextID;
 DWORD dwPrecedenceClass;
 DWORD dwDelayClass;
 DWORD dwReliabilityClass;
 DWORD dwPeakThruClass;
 DWORD dwMeanThruClass;
} RILGPRSQOSPROFILE;
typedef RILGPRSQOSPROFILE *PRILGPRSQOSPROFILE, *LPRILGPRSQOSPROFILE;

/* RILGPRSQOSPROFILECAPS  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwProtocolType;
 DWORD dwPrecedenceClass;
 DWORD dwDelayClass;
 DWORD dwReliabilityClass;
 DWORD dwPeakThruClass;
 char dwMeanThruClass;
} RILGPRSQOSPROFILECAPS, *LPRILGPRSQOSPROFILECAPS;

/* RILHIDECONNECTEDIDSETTINGS  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwStatus;
 DWORD dwProvisioning;
} RILHIDECONNECTEDIDSETTINGS;
typedef RILHIDECONNECTEDIDSETTINGS *PRILHIDECONNECTEDIDSETTINGS, *LPRILHIDECONNECTEDIDSETTINGS;

/* RILHIDEIDSETTINGS  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwStatus;
 DWORD dwProvisioning;
} RILHIDEIDSETTINGS;
typedef RILHIDEIDSETTINGS *PRILHIDEIDSETTINGS, *LPRILHIDEIDSETTINGS;

/* RILHSCSDINFO  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwTranspRxTimeslots;
 DWORD dwTranspChannelCodings;
 DWORD dwNonTranspRxTimeslots;
 DWORD dwNonTranspChannelCodings;
 DWORD dwAirInterfaceUserRate;
 DWORD dwRxTimeslotsLimit;
 BOOL fAutoSvcLevelUpgrading;
} RILHSCSDINFO;
typedef RILHSCSDINFO *PRILHSCSDINFO, *LPRILHSCSDINFO;

/* RILLOCATIONINFO  [struct; ce-only] */
typedef struct rillocationinfo_tag {
 DWORD cbSize;
 DWORD dwLocationAreaCode;
 DWORD dwCellID;
} RILLOCATIONINFO, *LPRILLOCATIONINFO;

/* RILMESSAGE_IN_SIM  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwLocation;
 DWORD dwIndex;
} RILMESSAGE_IN_SIM;
typedef RILMESSAGE_IN_SIM *PRILMESSAGE_IN_SIM, *LPRILMESSAGE_IN_SIM;

/* RILMSGDCS  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwType;
 DWORD dwFlags;
 DWORD dwMsgClass;
 DWORD dwAlphabet;
 DWORD dwIndication;
 DWORD dwLanguage;
} RILMSGDCS;
typedef RILMSGDCS *PRILMSGDCS, *LPRILMSGDCS;

/* RILMSGSERVICEINFO  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwService;
 DWORD dwMsgClasses;
 DWORD dwReadLocation;
 DWORD dwReadUsed;
 DWORD dwReadTotal;
 DWORD dwWriteLocation;
 DWORD dwWriteUsed;
 DWORD dwWriteTotal;
 DWORD dwStoreLocation;
 DWORD dwStoreUsed;
 DWORD dwStoreTotal;
} RILMSGSERVICEINFO;
typedef RILMSGSERVICEINFO *PRILMSGSERVICEINFO, *LPRILMSGSERVICEINFO;

/* RILMSGSTORAGEINFO  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwReadLocation;
 DWORD dwWriteLocation;
 DWORD dwStoreLocation;
} RILMSGSTORAGEINFO;
typedef RILMSGSTORAGEINFO *PRILMSGSTORAGEINFO, *LPRILMSGSTORAGEINFO;

/* RILMULTIPLECALLSETTINGS  [struct; ce-only; Ril.lib] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 BOOL fEnable;
 DWORD dwServiceStatus;
}RILMULTIPLECALLSETTINGS;
typedef RILMULTIPLECALLSETTINGS *PRILMULTIPLECALLSETTINGS, *LPRILMULTIPLECALLSETTINGS;

/* RILNCHINDICATION  [struct; ce-only; Ril.lib] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 BOOL fEnable;
 DWORD dwNCHStatus;
} RILNCHINDICATION;
typedef RILNCHINDICATION *PRILNCHINDICATION, *LPRILNCHINDICATION;

/* RILNDISBUFFER  [struct; ce-only] */
typedef struct rilndisbuffer_tag {
 const BYTE *pbyBytes;
 DWORD cByteCount;
} RILNDISBUFFER, *LPRILNDISBUFFER;

/* RILNDISPACKET  [struct; ce-only] */
typedef struct rilndispacket_tag {
 DWORD dwSize;
 DWORD dwContextID;
 DWORD cBufferCount;
 const RILNDISBUFFER NDISBuffer[1];
} RILNDISPACKET, *LPRILNDISPACKET;

/* RILNDISRECEIVECALLBACK  [typedef; ce-only] */
typedef void (CALLBACK *RILNDISRECEIVECALLBACK)(
 PVOID pCallbackContext,
 LPRILNDISPACKET pRilPacket
);

/* RILNDISTRANSMITCALLBACK  [typedef; ce-only] */
typedef void (CALLBACK *RILNDISTRANSMITCALLBACK)(
 PVOID pCallbackContext,
 LPRILNDISPACKET pRilPacket
);

/* RILNITZINFO  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwNotificationCode;
 int TimeZoneOffsetMinutes;
 int DaylightSavingOffsetMinutes;
 SYSTEMTIME SysTime;
} RILNITZINFO;
typedef RILNITZINFO *PRILNITZINFO, *LPRILNITZINFO;

/* RILNOTIFYCALLBACK  [typedef; ce-only] */
typedef void (CALLBACK *RILNOTIFYCALLBACK)(
 DWORD dwCode,
 const void* lpData,
 DWORD cbData,
 DWORD dwParam
);

/* RILPDPPACKETSUPPORTCAPS  [struct; ce-only; Ril.lib] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 BOOL fPacket;
 DWORD dwActiveContexts;
} RILPDPPACKETSUPPORTCAPS;
typedef RILPDPPACKETSUPPORTCAPS *PRILPDPPACKETSUPPORTCAPS, *LPRILPDPPACKETSUPPORTCAPS;

/* RILPHONEBOOKINFO  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwStoreLocation;
 DWORD dwUsed;
 DWORD dwTotal;
} RILPHONEBOOKINFO;
typedef RILPHONEBOOKINFO *PRILPHONEBOOKINFO, *LPRILPHONEBOOKINFO;

/* RILRESULTCALLBACK  [typedef; ce-only; Ril.lib] */
typedef void (CALLBACK *RILRESULTCALLBACK)(
 DWORD dwCode,
 HRESULT hrCmdID,
 const void* lpData,
 DWORD cbData,
 DWORD dwParam
);

/* RILRLPINFO  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwIWS;
 DWORD dwMWS;
 DWORD dwAckTimer;
 DWORD dwRetransmissionAttempts;
 DWORD dwVersion;
 DWORD dwResequencingPeriod;
} RILRLPINFO;
typedef RILRLPINFO *PRILRLPINFO, *LPRILRLPINFO;

/* RILSECONDARYPDPCONTEXT  [struct; ce-only; Ril.lib] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwContextID;
 DWORD dwPriContextID;
 DWORD dwDataCompression;
 DWORD dwHeaderCompression;
} RILSECONDARYPDPCONTEXT;
typedef RILSECONDARYPDPCONTEXT *PRILSECONDARYPDPCONTEXT, *LPRILSECONDARYPDPCONTEXT;

/* RILSERIALPORTSTATS  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwReadBitsPerSecond;
 DWORD dwWrittenBitsPerSecond;
} RILSERIALPORTSTATS;
typedef RILSERIALPORTSTATS *PRILSERIALPORTSTATS, *LPRILSERIALPORTSTATS;

/* RILSERVICEINFO  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 BOOL fSynchronous;
 BOOL fTransparent;
} RILSERVICEINFO;
typedef RILSERVICEINFO *PRILSERVICEINFO, *LPRILSERVICEINFO;

/* RILSIGNALQUALITY  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 int nSignalStrength;
 int nMinSignalStrength;
 int nMaxSignalStrength;
 DWORD dwBitErrorRate;
 int nLowSignalStrength;
 int nHighSignalStrength;
} RILSIGNALQUALITY;
typedef RILSIGNALQUALITY *PRILSIGNALQUALITY, *LPRILSIGNALQUALITY;

/* RILSIMCMDPARAMETERS  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwFileID;
 DWORD dwParameter1;
 DWORD dwParameter2;
 DWORD dwParameter3;
} RILSIMCMDPARAMETERS;
typedef RILSIMCMDPARAMETERS *PRILSIMCMDPARAMETERS, *LPRILSIMCMDPARAMETERS;

/* RILSIMRECORDSTATUS  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwRecordType;
 DWORD dwItemCount;
 DWORD dwSize;
} RILSIMRECORDSTATUS;
typedef RILSIMRECORDSTATUS *PRILSIMRECORDSTATUS, *LPRILSIMRECORDSTATUS;

/* RILSIMRESPONSE  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwStatusWord1;
 DWORD dwStatusWord2;
 BYTE pbResponse[];
} RILSIMRESPONSE;
typedef RILSIMRESPONSE *PRILSIMRESPONSE, *LPRILSIMRESPONSE;

/* RILSIMTOOLKITCMD  [struct; ce-only] */
typedef struct rilsimtoolkitcmd_tag {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwId;
 DWORD dwTag;
 DWORD dwType;
 DWORD dwQualifier;
 DWORD dwError;
 DWORD dwDetailsOffset;
 DWORD dwDetailsSize;
} RILSIMTOOLKITCMD;
typedef RILSIMTOOLKITCMD *PRILSIMTOOLKITCMD, *LPRILSIMTOOLKITCMD;

/* RILSIMTOOLKITEVENTCAPS  [struct; ce-only] */
typedef struct rilsimtoolkiteventcaps_tag {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwMTCall;
 DWORD dwCallConnected;
 DWORD dwCallDisconnected;
 DWORD dwLocationStatus;
 DWORD dwUserActivity;
 DWORD dwIdleScreen;
 DWORD dwLanguageSelection;
 DWORD dwBrowserTermination;
 DWORD dwDataAvailable;
 DWORD dwChannelStatus;
 DWORD dwDisplayChange;
} RILSIMTOOLKITEVENTCAPS, *LPRILSIMTOOLKITEVENTCAPS;

/* RILSIMTOOLKITNOTIFYCAPS  [struct; ce-only] */
typedef struct rilsimtoolkitnotifycaps_tag {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwRefresh;
 DWORD dwMoreTime;
 DWORD dwPollInterval;
 DWORD dwPollingOff;
 DWORD dwSetUpCall;
 DWORD dwSendSS;
 DWORD dwSendUSSD;
 DWORD dwSendSMS;
 DWORD dwPlayTone;
 DWORD dwDisplayText;
 DWORD dwGetInkey;
 DWORD dwGetInput;
 DWORD dwSelectItem;
 DWORD dwSetupMenu;
 DWORD dwSetupIdleModeText;
 DWORD dwLocalInfo;
 DWORD dwNotifyFlags;
 DWORD dwSetupEventList;
 DWORD dwSendDTMF;
 DWORD dwLaunchBrowser;
 DWORD dwOpenChannel;
 DWORD dwCloseChannel;
 DWORD dwReceiveData;
 DWORD dwSendData;
 DWORD dwTimerManagement;
 DWORD dwRunAtCmd;
 RILSIMTOOLKITEVENTCAPS rstecEvents;
} RILSIMTOOLKITNOTIFYCAPS, *LPRILSIMTOOLKITNOTIFYCAPS;

/* RILSIMTOOLKITRSP  [struct; ce-only] */
typedef struct rilsimtoolkitrsp_tag {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwId;
 DWORD dwTag;
 DWORD dwType;
 DWORD dwQualifier;
 DWORD dwResponse; 
 DWORD dwAdditionalInfo;
} RILSIMTOOLKITRSP;
typedef RILSIMTOOLKITRSP *PRILSIMTOOLKITRSP, *LPRILSIMTOOLKITRSP;

/* RILSUPSERVICEDATA  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwStatus;
 BYTE pbData[];
} RILSUPSERVICEDATA;
typedef RILSUPSERVICEDATA *PRILSUPSERVICEDATA, *LPRILSUPSERVICEDATA;

/* RILVGCSTALKERACCESSINFO  [struct; ce-only; Ril.lib] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwMode;
 DWORD dwTime;
} RILVGCSTALKERACCESSINFO;
typedef RILVGCSTALKERACCESSINFO *PRILVGCSTALKERACCESSINFO, *LPRILVGCSTALKERACCESSINFO;

/* RILVGCSUPLINKINFO  [struct; ce-only; Ril.lib] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 BOOL fEnable;
 DWORD dwStatus;
} RILVGCSUPLINKINFO;
typedef RILVGCSUPLINKINFO *PRILVGCSUPLINKINFO, *LPRILVGCSUPLINKINFO;

/* RILVGCSVBSSTATEATTR  [struct; ce-only; Ril.lib] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 BOOL fEnable;
 BOOL fDownlink;
 BOOL fUplink;
 BOOL fBothDirComm;
 BOOL fOriginator;
} RILVGCSVBSSTATEATTR;
typedef RILVGCSVBSSTATEATTR *PRILVGCSVBSSTATEATTR, *LPRILVGCSVBSSTATEATTR;

/* RILRINGINFO  [struct; ce-only] */
typedef struct {
 DWORD cbSize;
 DWORD dwParams;
 DWORD dwCallType;
 DWORD dwAddressId;
 RILSERVICEINFO rsiServiceInfo;
} RILRINGINFO;
typedef RILRINGINFO *PRILRINGINFO, *LPRILRINGINFO;

#endif /* _RIL_ */
