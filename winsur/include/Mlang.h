/* Mlang.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 10 constants, 18 declarations, 0 outlines, 0 base types, 0 extra macros, 32 extra decls
 */
#ifndef _MLANG_
#define _MLANG_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ABCD 1
#define BCD 1
#define CD 1
#define MAX_LOCALE_NAME 32
#define MAX_MIMECP_NAME 64
#define MAX_MIMECSET_NAME 50
#define MAX_MIMEFACE_NAME 32
#define MAX_RFC1766_NAME 6
#define MAX_SCRIPT_NAME 48
#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */
#define D 1
#endif /* _WIN32_WCE */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DetectEncodingInfo  [struct; ce-only] */
typedef struct tagDetectEncodingInfo {
 UINT nLangID;
 UINT nCodePage;
 INT nDocPercent;
 INT nConfidence;
} DetectEncodingInfo, *pDetectEncodingInfo;

/* MIMECONTF  [enum; ce-only] */
typedef enum tagMIMECONTF {
 MIMECONTF_MAILNEWS = 0x00000001,
 MIMECONTF_BROWSER = 0x00000002,
 MIMECONTF_MINIMAL = 0x00000004,
 MIMECONTF_IMPORT = 0x00000008,
 MIMECONTF_SAVABLE_MAILNEWS = 0x00000100,
 MIMECONTF_SAVABLE_BROWSER = 0x00000200,
 MIMECONTF_EXPORT = 0x00000400,
 MIMECONTF_PRIVCONVERTER = 0x00010000,
 MIMECONTF_VALID = 0x00020000,
 MIMECONTF_VALID_NLS = 0x00040000,
 MIMECONTF_MIME_IE4 = 0x10000000,
 MIMECONTF_MIME_LATEST = 0x20000000,
 MIMECONTF_MIME_REGISTRY = 0x40000000
} MIMECONTF;
typedef MIMECONTF *PMIMECONTF, *LPMIMECONTF;

/* MIMECPINFO  [struct; ce-only] */
typedef struct tagMIMECPINFO {
 DWORD dwFlags;
 UINT uiCodePage;
 UINT uiFamilyCodePage;
 WCHAR wszDescription[MAX_MIMECP_NAME];
 WCHAR wszWebCharset[MAX_MIMECSET_NAME];
 WCHAR wszHeaderCharset[MAX_MIMECSET_NAME];
 WCHAR wszBodyCharset[MAX_MIMECSET_NAME];
 WCHAR wszFixedWidthFont[MAX_MIMEFACE_NAME];
 WCHAR wszProportionalFont[MAX_MIMEFACE_NAME];
 BYTE bGDICharset;
} MIMECPINFO, *PMIMECPINFO;

/* MIMECSETINFO  [struct; ce-only] */
typedef struct tagMIMECSETINFO {
 UINT uiCodePage;
 UINT uiInternetEncoding;
 WCHAR wszCharset[MAX_MIMECSET_NAME];
} MIMECSETINFO, *PMIMECSETINFO;

/* MLCONVCHAR  [enum; ce-only] */
typedef enum tagMLCONVCHARF {
 MLCONVCHARF_NONE = 0,
 MLCONVCHARF_AUTODETECT = 1,
 MLCONVCHARF_NCR_ENTITIZE = 2,
 MLCONVCHARF_NAME_ENTITIZE = 4,
 MLCONVCHARF_USEDEFCHAR = 8,
 MLCONVCHARF_NOBESTFITCHARS = 16
} MLCONVCHAR;
typedef MLCONVCHAR *PMLCONVCHAR, *LPMLCONVCHAR;

/* MLCP  [enum; ce-only] */
typedef enum tagMLCPF {
 MLDETECTF_MAILNEWS = 0x0001,
 MLDETECTF_BROWSER = 0x0002,
 MLDETECTF_VALID = 0x0004,
 MLDETECTF_VALID_NLS = 0x0008,
 MLDETECTF_PRESERVE_ORDER = 0x0010,
 MLDETECTF_PREFERRED_ONLY = 0x0020,
 MLDETECTF_FILTER_SPECIALCHAR = 0x0040
} MLCP;
typedef MLCP *PMLCP, *LPMLCP;

/* MLDETECTCP  [enum; ce-only] */
typedef enum tagMLDETECTCP {
 MLDETECTCP_NONE = 0,
 MLDETECTCP_7BIT = 1,
 MLDETECTCP_8BIT = 2,
 MLDETECTCP_DBCS = 4,
 MLDETECTCP_HTML = 8
} MLDETECTCP;
typedef MLDETECTCP *PMLDETECTCP, *LPMLDETECTCP;

/* RFC1766INFO  [struct; ce-only] */
typedef struct tagRFC1766INFO {
 LCID lcid;
 WCHAR wszRfc1766[MAX_RFC1766_NAME];
 WCHAR wszLocaleName[MAX_LOCALE_NAME];
} RFC1766INFO, *PRFC1766INFO;

/* SCRIPTCONTF  [enum; ce-only] */
typedef enum tagSCRIPTCONTF {
 sidDefault,
 sidMerge,
 sidAsciiSym,
 sidAsciiLatin,
 sidLatin,
 sidGreek,
 sidCyrillic,
 sidArmenian,
 sidHebrew,
 sidArabic,
 sidDevanagari,
 sidBengali,
 sidGurmukhi,
 sidGujarati,
 sidOriya,
 sidTamil,
 sidTelugu,
 sidKannada,
 sidMalayalam,
 sidThai,
 sidLao,
 sidTibetan,
 sidGeorgian,
 sidHangul,
 sidKana,
 sidBopomofo,
 sidHan,
 sidEthiopic,
 sidCanSyllabic,
 sidCherokee,
 sidYi,
 sidBraille,
 sidRunic,
 sidOgham,
 sidSinhala,
 sidSyriac,
 sidBurmese,
 sidKhmer,
 sidThaana,
 sidMongolian,
 sidLim,
 sidFEFirst = sidHangul,
 sidFELast = sidHan
} SCRIPTCONTF;
typedef SCRIPTCONTF *PSCRIPTCONTF, *LPSCRIPTCONTF;

/* SCRIPTFONTCONTF  [enum; ce-only] */
typedef enum tagSCRIPTFONTCONTF {
 SCRIPTCONTF_FIXED_FONT = 0x00000001,
 SCRIPTCONTF_PROPORTIONAL_FONT = 0x00000002,
 SCRIPTCONTF_SCRIPT_USER = 0x00010000,
 SCRIPTCONTF_SCRIPT_HIDE = 0x00020000,
 SCRIPTCONTF_SCRIPT_SYSTEM = 0x00040000
} SCRIPTFONTCONTF;
typedef SCRIPTFONTCONTF *PSCRIPTFONTCONTF, *LPSCRIPTFONTCONTF;

/* UNICODERANGE  [struct; ce-only] */
typedef struct tagUNICODERANGE {
 WCHAR wcFrom;
 WCHAR wcTo;
} UNICODERANGE;
typedef UNICODERANGE *PUNICODERANGE, *LPUNICODERANGE;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* ConvertINetMultiByteToUnicode  [function; ce-only; CE 4.0..699; Mlang.dll, mlang.dll] */
HRESULT ConvertINetMultiByteToUnicode(
 LPDWORD lpdwMode,
 DWORD dwSrcEncoding,
 LPCSTR lpSrcStr,
 LPINT lpnMultiCharCount,
 LPWSTR lpDstStr,
 LPINT lpnWideCharCount
);

/* ConvertINetString  [function; ce-only; CE 4.0..699; Mlang.dll, mlang.dll] */
HRESULT ConvertINetString(
 LPDWORD lpdwMode,
 DWORD dwSrcEncoding,
 DWORD dwDstEncoding,
 LPCSTR lpSrcStr,
 LPINT lpnSrcSize,
 LPBYTE lpDstStr,
 LPINT lpnDstSize
);

/* ConvertINetUnicodeToMultiByte  [function; ce-only; CE 4.0..699; Mlang.dll, mlang.dll] */
HRESULT ConvertINetUnicodeToMultiByte(
 LPDWORD lpdwMode,
 DWORD dwEncoding,
 LPCWSTR lpSrcStr,
 LPINT lpnWideCharCount,
 LPSTR lpDstStr,
 LPINT lpnMultiCharCount
);

/* IsConvertINetStringAvailable  [function; ce-only; CE 4.0..699; Mlang.dll, mlang.dll] */
HRESULT IsConvertINetStringAvailable(
 DWORD dwSrcEncoding,
 DWORD dwDstEncoding
);

/* LcidToRfc1766  [function; ce-only; CE 4.0..699; Mlang.dll, mlang.dll] */
HRESULT LcidToRfc1766(
 LCID Locale,
 LPTSTR pszRfc1766,
 int nChar
);

/* Rfc1766ToLcid  [function; ce-only; CE 4.0..699; Mlang.dll, mlang.dll] */
HRESULT Rfc1766ToLcid(
 LCID* pLocale,
 LPTSTR pszRfc1766
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT BreakLineA( LCID locale, UINT uCodePage, const CHAR* pszSrc, long cchSrc, long cMaxColumns, long* pcchLine, long* pcchSkip );
HRESULT BreakLineW( LCID locale, const WCHAR* pszSrc, long cchSrc, long cMaxColumns, long* pcchLine, long* pcchSkip );
HRESULT CodePageToCodePages( UINT uCodePage, DWORD* pdwCodePages );
HRESULT CodePagesToCodePage( DWORD dwCodePages, UINT uDefaultCodePage, UINT* puCodePage );
HRESULT ConvertString( DWORD* pdwMode, DWORD dwSrcEncoding, DWORD dwDstEncoding, BYTE* pSrcStr, UINT* pcSrcSize, BYTE* pDstStr, UINT* pcDstSize );
HRESULT ConvertStringFromUnicode( DWORD* pdwMode, DWORD dwEncoding, WCHAR* pSrcStr, UINT* pcSrcSize, CHAR* pDstStr, UINT* pcDstSize );
HRESULT ConvertStringFromUnicodeEx( DWORD* pdwMode, DWORD dwEncoding, WCHAR* pSrcStr, UINT* pcSrcSize, CHAR* pDstStr, UINT* pcDstSize, DWORD dwFlag, WCHAR* lpFallBack );
HRESULT ConvertStringToUnicode( DWORD* pdwMode, DWORD dwEncoding, CHAR* pSrcStr, UINT* pcSrcSize, WCHAR* pDstStr, UINT* pcDstSize );
HRESULT ConvertStringToUnicodeEx( DWORD* pdwMode, DWORD dwEncoding, CHAR* pSrcStr, UINT* pcSrcSize, WCHAR* pDstStr, UINT* pcDstSize, DWORD dwFlag, WCHAR* lpFallBack );
HRESULT DetectOutboundCodePage( DWORD dwFlags, LPCWSTR lpWideCharStr, UINT cchWideChar, UINT* puiPreferredCodePages, UINT nPreferredCodePages, UINT* puiDetectedCodePages, UINT* pnDetectedCodePages, WCHAR* lpSpecialChar );
HRESULT DoConversion( BYTE* pSrcStr, UINT* pcSrcSize, BYTE* pDstStr, UINT* pcDstSize );
HRESULT DoConversionFromUnicode( WCHAR* pSrcStr, UINT* pcSrcSize, CHAR* pDstStr, UINT* pcDstSize );
HRESULT DoConversionToUnicode( CHAR* pSrcStr, UINT* pcSrcSize, WCHAR* pDstStr, UINT* pcDstSize );
HRESULT GetCharCodePages( WCHAR chSrc, DWORD* pdwCodePages );
HRESULT GetCodePageDescription( UINT uiCodePage, LCID lcid, LPWSTR lpWideCharStr, int cchWideChar );
HRESULT GetDestinationCodePage( UINT* puiDstCodePage );
HRESULT GetFamilyCodePage( UINT uiCodePage, UINT* puiFamilyCodePage );
HRESULT GetFontCodePages( HDC hDC, HFONT hFont, DWORD* pdwCodePages );
HRESULT GetFontUnicodeRanges( HDC hDC, UINT* puiRanges, UNICODERANGE* pUranges );
HRESULT GetNumberOfCodePageInfo( UINT* pcCodePage );
HRESULT GetNumberOfScripts( UINT* pnScripts );
HRESULT GetSourceCodePage( UINT* puiSrcCodePage );
HRESULT GetStrCodePages( const WCHAR* pszSrc, long cchSrc, DWORD dwPriorityCodePages, DWORD* pdwCodePages, long* pcchCodePages );
HRESULT IsConvertible( DWORD dwSrcEncoding, DWORD dwDstEncoding );
HRESULT MapFont( HDC hDC, DWORD dwCodePages, WCHAR chSrc, HFONT* pFont );
HRESULT ReleaseFont( HFONT hFont );
HRESULT ResetFontMapping(void);
HRESULT SetMimeDBSource( MIMECONTF dwSource );

#endif /* _MLANG_ */
