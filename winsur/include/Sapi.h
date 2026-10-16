/* Sapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 67 declarations, 3 outlines, 0 base types, 0 extra macros, 111 extra decls
 */
#ifndef _SAPI_
#define _SAPI_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* SPPHRASEALT  [struct; ce-only] */

/* SPPHRASEALTREQUEST  [struct; ce-only] */

/* SPRECORESULTINFO  [struct; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* SPAUDIOBUFFERINFO  [struct; ce-only] */
typedef struct SPAUDIOBUFFERINFO{
 ULONG ulMsMinNotification;
 ULONG ulMsBufferSize;
 ULONG ulMsEventBias;
} SPAUDIOBUFFERINFO;
typedef SPAUDIOBUFFERINFO *PSPAUDIOBUFFERINFO, *LPSPAUDIOBUFFERINFO;

/* SPAUDIOOPTIONS  [enum; ce-only] */
typedef enum SPAUDIOOPTIONS{
 SPAO_NONE = 0,
 SPAO_RETAIN_AUDIO = (1 << 0)
} SPAUDIOOPTIONS;
typedef SPAUDIOOPTIONS *PSPAUDIOOPTIONS, *LPSPAUDIOOPTIONS;

/* SPAUDIOSTATE  [enum; ce-only] */
typedef enum _SPAUDIOSTATE{
 SPAS_CLOSED,
 SPAS_STOP,
 SPAS_PAUSE,
 SPAS_RUN
} SPAUDIOSTATE;
typedef SPAUDIOSTATE *PSPAUDIOSTATE, *LPSPAUDIOSTATE;

/* SPAUDIOSTATUS  [struct; ce-only] */
typedef [restricted] struct SPAUDIOSTATUS{
 long cbFreeBuffSpace;
 ULONG cbNonBlockingIO;
 SPAUDIOSTATE State;
 ULONGLONG CurSeekPos;
 ULONGLONG CurDevicePos;
 DWORD dwReserved1;
 DWORD dwReserved2;
} SPAUDIOSTATUS;

/* SPBINARYGRAMMAR  [struct; ce-only] */
typedef struct SPBINARYGRAMMAR{
 ULONG ulTotalSerializedSize;
} SPBINARYGRAMMAR;
typedef SPBINARYGRAMMAR *PSPBINARYGRAMMAR, *LPSPBINARYGRAMMAR;

/* SPBOOKMARKOPTIONS  [enum; ce-only] */
typedef enum SPBOOKMARKOPTIONS{
 SPBO_NONE = 0,
 SPBO_PAUSE = 1
} SPBOOKMARKOPTIONS;
typedef SPBOOKMARKOPTIONS *PSPBOOKMARKOPTIONS, *LPSPBOOKMARKOPTIONS;

/* SPCONTEXTSTATE  [enum; ce-only] */
typedef enum SPCONTEXTSTATE{
 SPCS_DISABLED = 0,
 SPCS_ENABLED = 1
} SPCONTEXTSTATE;
typedef SPCONTEXTSTATE *PSPCONTEXTSTATE, *LPSPCONTEXTSTATE;

/* SPDATAKEYLOCATION  [enum; ce-only] */
typedef enum SPDATAKEYLOCATION{
 SPDKL_DefaultLocation = 0,
 SPDKL_CurrentUser = 1,
 SPDKL_LocalMachine = 2,
 SPDKL_CurrentConfig = 5
} SPDATAKEYLOCATION;
typedef SPDATAKEYLOCATION *PSPDATAKEYLOCATION, *LPSPDATAKEYLOCATION;

/* SPDISPLAYATTRIBUTES  [enum; ce-only] */
typedef enum tagSPDISPLYATTRIBUTES{
 SPAF_ONE_TRAILING_SPACE = 0x02,
 SPAF_TWO_TRAILING_SPACES = 0x04,
 SPAF_CONSUME_LEADING_SPACES = 0x08,
 SPAF_ALL = 0x0F 
} SPDISPLAYATTRIBUTES;
typedef SPDISPLAYATTRIBUTES *PSPDISPLAYATTRIBUTES, *LPSPDISPLAYATTRIBUTES;

/* SPEAKFLAGS  [enum; ce-only] */
typedef enum SPEAKFLAGS{
 // SpVoice flags
 SPF_DEFAULT = 0,
 SPF_ASYNC = (1L << 0),
 SPF_PURGEBEFORESPEAK = (1L << 1),
 SPF_IS_FILENAME = (1L << 2),
 SPF_IS_XML = (1L << 3),
 SPF_IS_NOT_XML = (1L << 4),
 SPF_PERSIST_XML = (1L << 5),
 // Normalizer flags
 SPF_NLP_SPEAK_PUNC = (1L << 6),
 // Masks
 SPF_NLP_MASK = (SPF_NLP_SPEAK_PUNC),
 SPF_VOICE_MASK = (SPF_ASYNC|SPF_PURGEBEFORESPEAK|SPF_IS_FILENAME|
 SPF_IS_XML|SPF_IS_NOT_XML|SPF_NLP_MASK|SPF_PERSIST_XML),
 SPF_UNUSED_FLAGS = ~(SPF_VOICE_MASK)
} SPEAKFLAGS;
typedef SPEAKFLAGS *PSPEAKFLAGS, *LPSPEAKFLAGS;

/* SPENDSRSTREAMFLAGS  [enum; ce-only] */
typedef enum SPENDSRSTREAMFLAGS{
 SPESF_NONE = 0,
 SPESF_STREAM_RELEASED = (1 << 0)
} SPENDSRSTREAMFLAGS;
typedef SPENDSRSTREAMFLAGS *PSPENDSRSTREAMFLAGS, *LPSPENDSRSTREAMFLAGS;

/* SPEVENT  [struct; ce-only] */
typedef [restricted] struct SPEVENT{
 WORD eEventId;
 WORD elParamType;
 ULONG ulStreamNum;
 ULONGLONG ullAudioStreamOffset;
 WPARAM wParam;
 LPARAM lParam;
} SPEVENT;

/* SPEVENTLPARAMTYPE  [enum; ce-only] */
typedef enum SPEVENTLPARAMTYPE{
 SPET_LPARAM_IS_UNDEFINED = 0,
 SPET_LPARAM_IS_TOKEN,
 SPET_LPARAM_IS_OBJECT,
 SPET_LPARAM_IS_POINTER,
 SPET_LPARAM_IS_STRING
} SPEVENTLPARAMTYPE;
typedef SPEVENTLPARAMTYPE *PSPEVENTLPARAMTYPE, *LPSPEVENTLPARAMTYPE;

/* SPEVENTSOURCEINFO  [struct; ce-only] */
typedef struct SPEVENTSOURCEINFO{
 ULONGLONG ullEventInterest;
 ULONGLONG ullQueuedInterest;
 ULONG ulCount;
} SPEVENTSOURCEINFO;
typedef SPEVENTSOURCEINFO *PSPEVENTSOURCEINFO, *LPSPEVENTSOURCEINFO;

/* SPFILEMODE  [enum; ce-only] */
typedef enum SPFILEMODE{
 SPFM_OPEN_READONLY,
 SPFM_OPEN_READWRITE,
 SPFM_CREATE,
 SPFM_CREATE_ALWAYS,
 SPFM_NUM_MODES
} SPFILEMODE;
typedef SPFILEMODE *PSPFILEMODE, *LPSPFILEMODE;

/* SPGRAMMARSTATE  [enum; ce-only] */
typedef enum SPGRAMMARSTATE{
 SPGS_ENABLED = 0,
 SPGS_DISABLED = 1,
 SPGS_EXCLUSIVE = 3
} SPGRAMMARSTATE;
typedef SPGRAMMARSTATE *PSPGRAMMARSTATE, *LPSPGRAMMARSTATE;

/* SPGRAMMARWORDTYPE  [enum; ce-only] */
typedef enum SPGRAMMARWORDTYPE{
 SPWT_DISPLAY,
 SPWT_LEXICAL,
 SPWT_PRONUNCIATION
} SPGRAMMARWORDTYPE;
typedef SPGRAMMARWORDTYPE *PSPGRAMMARWORDTYPE, *LPSPGRAMMARWORDTYPE;

/* SPINTERFERENCE  [enum; ce-only] */
typedef enum SPINTERFERENCE{
 SPINTERFERENCE_NONE = 0,
 SPINTERFERENCE_NOISE,
 SPINTERFERENCE_NOSIGNAL,
 SPINTERFERENCE_TOOLOUD,
 SPINTERFERENCE_TOOQUIET,
 SPINTERFERENCE_TOOFAST,
 SPINTERFERENCE_TOOSLOW
} SPINTERFERENCE;
typedef SPINTERFERENCE *PSPINTERFERENCE, *LPSPINTERFERENCE;

/* SPLEXICONTYPE  [enum; ce-only] */
typedef enum SPLEXICONTYPE{
 eLEXTYPE_USER = (1L << 0),
 eLEXTYPE_APP = (1L << 1),
 eLEXTYPE_RESERVED1 = (1L << 2),
 eLEXTYPE_RESERVED2 = (1L << 3),
 eLEXTYPE_RESERVED3 = (1L << 4),
 eLEXTYPE_RESERVED4 = (1L << 5),
 eLEXTYPE_RESERVED5 = (1L << 6),
 eLEXTYPE_RESERVED6 = (1L << 7),
 eLEXTYPE_RESERVED7 = (1L << 8),
 eLEXTYPE_RESERVED8 = (1L << 9),
 eLEXTYPE_RESERVED9 = (1L << 10),
 eLEXTYPE_RESERVED10 = (1L << 11),
 eLEXTYPE_PRIVATE1 = (1L << 12),
 eLEXTYPE_PRIVATE2 = (1L << 13),
 eLEXTYPE_PRIVATE3 = (1L << 14),
 eLEXTYPE_PRIVATE4 = (1L << 15),
 eLEXTYPE_PRIVATE5 = (1L << 16),
 eLEXTYPE_PRIVATE6 = (1L << 17),
 eLEXTYPE_PRIVATE7 = (1L << 18),
 eLEXTYPE_PRIVATE8 = (1L << 19),
 eLEXTYPE_PRIVATE9 = (1L << 20),
 eLEXTYPE_PRIVATE10 = (1L << 21),
 eLEXTYPE_PRIVATE11 = (1L << 22),
 eLEXTYPE_PRIVATE12 = (1L << 23),
 eLEXTYPE_PRIVATE13 = (1L << 24),
 eLEXTYPE_PRIVATE14 = (1L << 25),
 eLEXTYPE_PRIVATE15 = (1L << 26),
 eLEXTYPE_PRIVATE16 = (1L << 27),
 eLEXTYPE_PRIVATE17 = (1L << 28),
 eLEXTYPE_PRIVATE18 = (1L << 29),
 eLEXTYPE_PRIVATE19 = (1L << 30),
 eLEXTYPE_PRIVATE20 = (1L << 31)
} SPLEXICONTYPE;
typedef SPLEXICONTYPE *PSPLEXICONTYPE, *LPSPLEXICONTYPE;

/* SPLOADOPTIONS  [enum; ce-only] */
typedef enum SPLOADOPTIONS{
 SPLO_STATIC = 0,
 SPLO_DYNAMIC = 1
} SPLOADOPTIONS;
typedef SPLOADOPTIONS *PSPLOADOPTIONS, *LPSPLOADOPTIONS;

/* SPPARTOFSPEECH  [enum; ce-only] */
typedef enum SPPARTOFSPEECH{
 //--- SAPI5 public POS category values (bits 28-31)
 SPPS_NotOverriden = -1,
 SPPS_Unknown = 0,
 SPPS_Noun = 0x1000,
 SPPS_Verb = 0x2000,
 SPPS_Modifier = 0x3000,
 SPPS_Function = 0x4000,
 SPPS_Interjection = 0x5000
} SPPARTOFSPEECH;
typedef SPPARTOFSPEECH *PSPPARTOFSPEECH, *LPSPPARTOFSPEECH;

/* SPPHRASEREPLACEMENT  [struct; ce-only] */
typedef struct tagSPPHRASEREPLACEMENT{
 BYTE bDisplayAttributes;
 const WCHAR* pszReplacementText;
 ULONG ulFirstElement;
 ULONG ulCountOfElements;
} SPPHRASEREPLACEMENT;
typedef SPPHRASEREPLACEMENT *PSPPHRASEREPLACEMENT, *LPSPPHRASEREPLACEMENT;

/* SPPHRASERNG  [enum; ce-only] */
typedef enum SPPHRASERNG{
 SPPR_ALL_ELEMENTS = -1
} SPPHRASERNG;
typedef SPPHRASERNG *PSPPHRASERNG, *LPSPPHRASERNG;

/* SPPHRASERULE  [struct; ce-only] */
struct tagSPPHRASERULE{
 const WCHAR* pszName;
 ULONG ulId;
 ULONG ulFirstElement;
 ULONG ulCountOfElements;
 const SPPHRASERULE* pNextSibling;
 const SPPHRASERULE* pFirstChild;
 float SREngineConfidence;
 signed char Confidence;
};

/* SPRECOCONTEXTSTATUS  [struct; ce-only] */
typedef [restricted] struct SPRECOCONTEXTSTATUS{
 SPINTERFERENCE eInterference;
 WCHAR szRequestTypeOfUI[255];
 DWORD dwReserved1;
 DWORD dwReserved2;
} SPRECOCONTEXTSTATUS;

/* SPRECOEVENTFLAGS  [enum; ce-only] */
typedef enum SPRECOEVENTFLAGS{
 SPREF_AutoPause = (1 << 0)
 SPREF_Emulated = (1 << 1)
} SPRECOECOEVENTFLAGS;

/* SPRECORESULTTIMES  [struct; ce-only] */
typedef struct SPRECORESULTTIMES{
 FILETIME ftStreamTime;
 ULONGLONG ullLength;
 DWORD dwTickCount;
 ULONGLONG ullStart;
} SPRECORESULTTIMES;
typedef SPRECORESULTTIMES *PSPRECORESULTTIMES, *LPSPRECORESULTTIMES;

/* SPRECOSTATE  [enum; ce-only] */
typedef enum SPRECOSTATE{
 SPRST_INACTIVE,
 SPRST_ACTIVE,
 SPRST_ACTIVE_ALWAYS,
 SPRST_INACTIVE_WITH_PURGE,
 SPRST_NUM_STATES
} SPRECOSTATE;
typedef SPRECOSTATE *PSPRECOSTATE, *LPSPRECOSTATE;

/* SPRULESTATE  [enum; ce-only] */
typedef enum SPRULESTATE{
 SPRS_INACTIVE = 0,
 SPRS_ACTIVE = 1,
 SPRS_ACTIVE_WITH_AUTO_PAUSE = 3
} SPRULESTATE;
typedef SPRULESTATE *PSPRULESTATE, *LPSPRULESTATE;

/* SPRUNSTATE  [enum; ce-only] */
typedef enum SPRUNSTATE{
 SPRS_DONE = (1L << 0),
 SPRS_IS_SPEAKING = (1L << 1) 
} SPRUNSTATE;
typedef SPRUNSTATE *PSPRUNSTATE, *LPSPRUNSTATE;

/* SPSERIALIZEDEVENT  [struct; ce-only] */
typedef [restricted] struct SPSERIALIZEDEVENT{
 WORD eEventId;
 WORD elParamType;
 ULONG ulStreamNum;
 ULONGLONG ullAudioStreamOffset;
 ULONG SerializedwParam;
 LONG SerializedlParam;
} SPSERIALIZEDEVENT;

/* SPSERIALIZEDEVENT64  [struct; ce-only] */
typedef [restricted] struct SPSERIALIZEDEVENT64{
 WORD eEventId;
 WORD elParamType;
 ULONG ulStreamNum;
 ULONGLONG ullAudioStreamOffset;
 ULONGLONG SerializedwParam;
 LONGLONG SerializedlParam;
} SPSERIALIZEDEVENT64;

/* SPSERIALIZEDPHRASE  [struct; ce-only] */
typedef struct tagSPSERIALIZEDPHRASE{
 ULONG ulSerializedSize;
} SPSERIALIZEDPHRASE;
typedef SPSERIALIZEDPHRASE *PSPSERIALIZEDPHRASE, *LPSPSERIALIZEDPHRASE;

/* SPSERIALIZEDRESULT  [struct; ce-only] */
typedef struct SPSERIALIZEDRESULT{
 ULONG ulSerializedSize;
} SPSERIALIZEDRESULT;
typedef SPSERIALIZEDRESULT *PSPSERIALIZEDRESULT, *LPSPSERIALIZEDRESULT;

/* SPSTREAMFORMAT  [enum; ce-only] */
typedef enum SPSTREAMFORMAT{
 SPSF_Default = -1,
 SPSF_NoAssignedFormat = 0,
 SPSF_Text,
 SPSF_NonStandardFormat,
 SPSF_ExtendedAudioFormat,
 // Standard PCM wave formats
 SPSF_8kHz8BitMono,
 SPSF_8kHz8BitStereo,
 SPSF_8kHz16BitMono,
 SPSF_8kHz16BitStereo,
 SPSF_11kHz8BitMono,
 SPSF_11kHz8BitStereo,
 SPSF_11kHz16BitMono,
 SPSF_11kHz16BitStereo,
 SPSF_12kHz8BitMono,
 SPSF_12kHz8BitStereo,
 SPSF_12kHz16BitMono,
 SPSF_12kHz16BitStereo,
 SPSF_16kHz8BitMono,
 SPSF_16kHz8BitStereo,
 SPSF_16kHz16BitMono,
 SPSF_16kHz16BitStereo,
 SPSF_22kHz8BitMono,
 SPSF_22kHz8BitStereo,
 SPSF_22kHz16BitMono,
 SPSF_22kHz16BitStereo,
 SPSF_24kHz8BitMono,
 SPSF_24kHz8BitStereo,
 SPSF_24kHz16BitMono,
 SPSF_24kHz16BitStereo,
 SPSF_32kHz8BitMono,
 SPSF_32kHz8BitStereo,
 SPSF_32kHz16BitMono,
 SPSF_32kHz16BitStereo,
 SPSF_44kHz8BitMono,
 SPSF_44kHz8BitStereo,
 SPSF_44kHz16BitMono,
 SPSF_44kHz16BitStereo,
 SPSF_48kHz8BitMono,
 SPSF_48kHz8BitStereo,
 SPSF_48kHz16BitMono,
 SPSF_48kHz16BitStereo,
 // TrueSpeech format
 SPSF_TrueSpeech_8kHz1BitMono,
 // A-Law formats
 SPSF_CCITT_ALaw_8kHzMono,
 SPSF_CCITT_ALaw_8kHzStereo,
 SPSF_CCITT_ALaw_11kHzMono,
 SPSF_CCITT_ALaw_11kHzStereo,
 SPSF_CCITT_ALaw_22kHzMono,
 SPSF_CCITT_ALaw_22kHzStereo,
 SPSF_CCITT_ALaw_44kHzMono,
 SPSF_CCITT_ALaw_44kHzStereo,
 // u-Law formats
 SPSF_CCITT_uLaw_8kHzMono,
 SPSF_CCITT_uLaw_8kHzStereo,
 SPSF_CCITT_uLaw_11kHzMono,
 SPSF_CCITT_uLaw_11kHzStereo,
 SPSF_CCITT_uLaw_22kHzMono,
 SPSF_CCITT_uLaw_22kHzStereo,
 SPSF_CCITT_uLaw_44kHzMono,
 SPSF_CCITT_uLaw_44kHzStereo,
 // ADPCM formats
 SPSF_ADPCM_8kHzMono,
 SPSF_ADPCM_8kHzStereo,
 SPSF_ADPCM_11kHzMono,
 SPSF_ADPCM_11kHzStereo,
 SPSF_ADPCM_22kHzMono,
 SPSF_ADPCM_22kHzStereo,
 SPSF_ADPCM_44kHzMono,
 SPSF_ADPCM_44kHzStereo,
 // GSM 6.10 formats
 SPSF_GSM610_8kHzMono,
 SPSF_GSM610_11kHzMono,
 SPSF_GSM610_22kHzMono,
 SPSF_GSM610_44kHzMono,
 SPSF_NUM_FORMATS
} SPSTREAMFORMAT;
typedef SPSTREAMFORMAT *PSPSTREAMFORMAT, *LPSPSTREAMFORMAT;

/* SPTEXTSELECTIONINFO  [struct; ce-only] */
typedef struct tagSPTEXTSELECTIONINFO{
 ULONG ulStartActiveOffset;
 ULONG cchActiveChars;
 ULONG ulStartSelection;
 ULONG cchSelection;
} SPTEXTSELECTIONINFO;
typedef SPTEXTSELECTIONINFO *PSPTEXTSELECTIONINFO, *LPSPTEXTSELECTIONINFO;

/* SPTMTHREADINFO  [struct; ce-only] */
typedef struct SPTMTHREADINFO{
 long lPoolSize;
 long lPriority;
 ULONG ulConcurrencyLimit;
 ULONG ulMaxQuickAllocThreads;
} SPTMTHREADINFO;
typedef SPTMTHREADINFO *PSPTMTHREADINFO, *LPSPTMTHREADINFO;

/* SPVACTIONS  [enum; ce-only] */
typedef enum SPVACTIONS{
 SPVA_Speak = 0,
 SPVA_Silence,
 SPVA_Pronounce,
 SPVA_Bookmark,
 SPVA_SpellOut,
 SPVA_Section,
 SPVA_ParseUnknownTag
} SPVACTIONS;
typedef SPVACTIONS *PSPVACTIONS, *LPSPVACTIONS;

/* SPVALUETYPE  [enum; ce-only] */
typedef enum SPVALUETYPE{
 SPDF_PROPERTY = 0x00000001,
 SPDF_REPLACEMENT = 0x00000002,
 SPDF_RULE = 0x00000004,
 SPDF_DISPLAYTEXT = 0x00000008,
 SPDF_LEXICALFORM = 0x00000010,
 SPDF_PRONUNCIATION = 0x00000020,
 SPDF_AUDIO = 0x00000040,
 SPDF_ALTERNATES = 0x00000080,
 SPDF_ALL = 0x000000FF
} SPVALUETYPE;
typedef SPVALUETYPE *PSPVALUETYPE, *LPSPVALUETYPE;

/* SPVCONTEXT  [struct; ce-only] */
typedef [restricted] struct SPVCONTEXT{
 LPCWSTR pCategory;
 LPCWSTR pBefore;
 LPCWSTR pAfter;
} SPVCONTEXT;

/* SPVFEATURE  [enum; ce-only] */
typedef enum SPVFEATURE{
 SPVFEATURE_STRESSED = (1L << 0),
 SPVFEATURE_EMPHASIS = (1L << 1)
} SPVFEATURE;
typedef SPVFEATURE *PSPVFEATURE, *LPSPVFEATURE;

/* SPVISEMES  [enum; ce-only] */
typedef enum SPVISEMES{
 // English examples
 //------------------
 SP_VISEME_0 = 0,
 SP_VISEME_1,
 SP_VISEME_2,
 SP_VISEME_3,
 SP_VISEME_4,
 SP_VISEME_5,
 SP_VISEME_6,
 SP_VISEME_7,
 SP_VISEME_8,
 SP_VISEME_9,
 SP_VISEME_10,
 SP_VISEME_11,
 SP_VISEME_12,
 SP_VISEME_13,
 SP_VISEME_14,
 SP_VISEME_15,
 SP_VISEME_16,
 SP_VISEME_17,
 SP_VISEME_18,
 SP_VISEME_19,
 SP_VISEME_20,
 SP_VISEME_21
} SPVISEMES;
typedef SPVISEMES *PSPVISEMES, *LPSPVISEMES;

/* SPVLIMITS  [enum; ce-only] */
typedef enum SPVLIMITS{
 SPMIN_VOLUME = 0,
 SPMAX_VOLUME = 100,
 SPMIN_RATE = -10,
 SPMAX_RATE = 10
} SPVLIMITS;
typedef SPVLIMITS *PSPVLIMITS, *LPSPVLIMITS;

/* SPVPITCH  [struct; ce-only] */
typedef struct SPVPITCH{
 long MiddleAdj;
 long RangeAdj;
} SPVPITCH;
typedef SPVPITCH *PSPVPITCH, *LPSPVPITCH;

/* SPVPRIORITY  [enum; ce-only] */
typedef enum SPVPRIORITY{
 SPVPRI_NORMAL = 0,
 SPVPRI_ALERT = (1L << 0),
 SPVPRI_OVER = (1L << 1)
} SPVPRIORITY;
typedef SPVPRIORITY *PSPVPRIORITY, *LPSPVPRIORITY;

/* SPWAVEFORMATTYPE  [enum; ce-only] */
typedef enum SPWAVEFORMATTYPE{
 SPWF_INPUT,
 SPWF_SRENGINE
} SPSTREAMFORMATTYPE;

/* SPWORDPRONOUNCEABLE  [enum; ce-only] */
typedef enum SPWORDPRONOUNCEABLE{
 SPWP_UNKNOWN_WORD_UNPRONOUNCEABLE = 0,
 SPWP_UNKNOWN_WORD_PRONOUNCEABLE = 1,
 SPWP_KNOWN_WORD_PRONOUNCEABLE = 2
} SPWORDPRONOUNCEABLE;
typedef SPWORDPRONOUNCEABLE *PSPWORDPRONOUNCEABLE, *LPSPWORDPRONOUNCEABLE;

/* SPWORDTYPE  [enum; ce-only] */
typedef enum SPWORDTYPE{
 eWORDTYPE_ADDED = (1L << 0),
 eWORDTYPE_DELETED = (1L << 1)
} SPWORDTYPE;
typedef SPWORDTYPE *PSPWORDTYPE, *LPSPWORDTYPE;

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT AddElements( ULONG cElements, const SPPHRASEELEMENT* pElement );
HRESULT AddEvents( const SPEVENT* pEventArray, ULONG ulCount );
HRESULT AddReplacements( ULONG cReplacements, const SPPHRASEREPLACEMENT* pReplacements );
HRESULT AppendTranscript( const WCHAR* pszTranscript );
HRESULT Bookmark( SPBOOKMARKOPTIONS Options, ULONGLONG ullStreamPosition, LPARAM lParamEvent );
HRESULT DeleteKey( const WCHAR* pszSubKeyName );
HRESULT DeleteValue( const WCHAR* pszValueName );
HRESULT Discard( DWORD dwValueTypes );
HRESULT EnumKeys( ULONG Index, WCHAR** ppszSubKeyName );
HRESULT EnumValues( ULONG Index, WCHAR** ppszValueName );
HANDLE EventHandle(void);
HRESULT GetBufferInfo( SPAUDIOBUFFERINFO* pBuffInfo );
HRESULT GetBufferNotifySize( ULONG* pcbSize );
HRESULT GetContextState( SPCONTEXTSTATE* peContextState );
HRESULT GetDWORD( const WCHAR* pszKeyName, DWORD* pdwValue );
HRESULT GetDefaultTokenId( const WCHAR** ppszCoMemTokenId );
HRESULT GetDeviceId( UINT* puDeviceId );
HRESULT GetEventInterest( ULONGLONG* pullEventInterest );
HRESULT GetEvents( ULONG ulCount, SPEVENT* pEventArray, ULONG* pulFetched );
HRESULT GetGeneration( DWORD* pdwGeneration );
HRESULT GetGenerationChange( DWORD dwFlags, DWORD* pdwGeneration, SPWORDLIST* pWordList );
HRESULT GetGrammarId( ULONGLONG* pullGrammarId );
HRESULT GetGrammarState( SPGRAMMARSTATE* peGrammarState );
HRESULT GetId( WCHAR** ppszCoMemCategoryId );
HRESULT GetLineId( UINT* puLineId );
HRESULT GetMMHandle( void** pHandle );
HRESULT GetMaxAlternates( ULONG* pcMaxAlternates );
HANDLE GetNotifyEventHandle(void);
HRESULT GetPhrase( SPPHRASE** ppCoMemPhrase );
HRESULT GetRecoState( SPRECOSTATE* pState );
HRESULT GetResultTimes( SPRECORESULTTIMES* pTimes );
HRESULT GetSerializedPhrase( SPSERIALIZEDPHRASE** ppCoMemPhrase );
HRESULT GetStringValue( const WCHAR* pszValueName, WCHAR** ppszValue );
HRESULT GetSyncSpeakTimeout( ULONG* pmsTimeout );
HRESULT GetText( ULONG ulStart, ULONG ulCount, BOOL fUseTextReplacements, WCHAR** ppszCoMemText, BYTE* pbDisplayAttributes );
HRESULT GetTranscript( WCHAR** ppszTranscript );
HRESULT GetVoicePurgeEvent( ULONGLONG* pullEventInterest );
HRESULT GetWords( DWORD dwFlags, DWORD* pdwGeneration, DWORD* pdwCookie, SPWORDLIST* pWordList );
HRESULT InitFromPhrase( const SPPHRASE* pSrcPhrase );
HRESULT InitFromSerializedPhrase( const SPSERIALIZEDPHRASE* pPhrase );
HRESULT InitWin32Event( HANDLE hEvent, BOOL fCloseHandleOnRelease );
HRESULT InitWindowMessage( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
HRESULT IsPronounceable( const WCHAR* pszWord, SPWORDPRONOUNCEABLE* pfPronounceable );
HRESULT IsSharedInstance(void);
HRESULT LoadCmdFromFile( const WCHAR* pszFileName, SPLOADOPTIONS Options );
HRESULT LoadCmdFromMemory( const SPBINARYGRAMMAR* pBinaryData, SPLOADOPTIONS Options );
HRESULT LoadCmdFromResource( HMODULE hModule, const WCHAR* pszResourceName, const WCHAR* pszResourceType, WORD wLanguage, SPLOADOPTIONS Options );
HRESULT LoadDictation( const WCHAR* pszTopicName, SPLOADOPTIONS Options );
HRESULT MatchesAttributes( const WCHAR* pszAttributes, BOOL* pfMatches );
HRESULT NotifyCallback( WPARAM wParam, LPARAM lParam );
HRESULT ResetSeekPosition(void);
HRESULT ScaleBaseToConvertedOffset( ULONGLONG ullOffsetBaseStream, ULONGLONG* pullOffsetConvertedStream );
HRESULT ScaleConvertedToBaseOffset( ULONGLONG ullOffsetConvertedStream, ULONGLONG* pullOffsetBaseStream );
HRESULT Serialize( SPSERIALIZEDRESULT** ppCoMemSerializedResult );
HRESULT SetAdaptationData( const WCHAR* pAdaptationData, const ULONG cch );
HRESULT SetBufferInfo( const SPAUDIOBUFFERINFO* pBuffInfo );
HRESULT SetBufferNotifySize( ULONG cbSize );
HRESULT SetContextState( SPCONTEXTSTATE eContextState );
HRESULT SetDWORD( const WCHAR* pszKeyName DWORD dwValue );
HRESULT SetDefaultTokenId( const WCHAR* pszTokenId );
HRESULT SetDeviceId( UINT uDeviceId );
HRESULT SetDictationState( SPRULESTATE NewState );
HRESULT SetGrammarState( SPGRAMMARSTATE eGrammarState );
HRESULT SetId( const WCHAR* pszCategoryId, BOOL fCreateIfNotExist );
HRESULT SetInterest( ULONGLONG ullEventInterest, ULONGLONG ullQueuedInterest );
HRESULT SetKey( HKEY hkey, BOOL fReadOnly );
HRESULT SetLineId( UINT uLineId );
HRESULT SetMaxAlternates( ULONG cAlternates );
HRESULT SetNotifyWin32Event(void);
HRESULT SetNotifyWindowMessage( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
HRESULT SetRecoState( SPRECOSTATE NewState );
HRESULT SetRuleIdState( ULONG ulRuleId, SPRULESTATE NewState );
HRESULT SetRuleState( const WCHAR* pszName, void* pReserved, SPRULESTATE NewState );
HRESULT SetStringValue( const WCHAR* pszValueName, const WCHAR* pszValue );
HRESULT SetSyncSpeakTimeout( ULONG msTimeout );
HRESULT SetTextSelection( const SPTEXTSELECTIONINFO* pInfo );
HRESULT SetVoicePurgeEvent( ULONGLONG ullEventInterest );
HRESULT SetWordSequenceData( const WCHAR* pText, ULONG cchText, const SPTEXTSELECTIONINFO* pInfo );
HRESULT SpeakAudio( ULONG ulStartElement, ULONG cElements, DWORD dwFlags, ULONG* pulStreamNumber );
HANDLE SpeakCompleteEvent(void);
HRESULT UnloadDictation(void);
HRESULT WaitUntilDone( ULONG msTimeout );

#endif /* _SAPI_ */
