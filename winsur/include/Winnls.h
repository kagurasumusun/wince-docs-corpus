/* Winnls.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 424 constants, 70 declarations, 10 outlines, 2 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WINNLS_
#define _WINNLS_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define C1_ALPHA 0x0100
#define C1_BLANK 0x0040
#define C1_CNTRL 0x0020
#define C1_DEFINED 0x0200
#define C1_DIGIT 0x0004
#define C1_LOWER 0x0002
#define C1_PUNCT 0x0010
#define C1_SPACE 0x0008
#define C1_UPPER 0x0001
#define C1_XDIGIT 0x0080
#define C2_ARABICNUMBER 0x0006
#define C2_BLOCKSEPARATOR 0x0008
#define C2_COMMONSEPARATOR 0x0007
#define C2_EUROPENUMBER 0x0003
#define C2_EUROPESEPARATOR 0x0004
#define C2_EUROPETERMINATOR 0x0005
#define C2_LEFTTORIGHT 0x0001
#define C2_NOTAPPLICABLE 0x0000
#define C2_OTHERNEUTRAL 0x000B
#define C2_RIGHTTOLEFT 0x0002
#define C2_SEGMENTSEPARATOR 0x0009
#define C2_WHITESPACE 0x000A
#define C3_ALPHA 0x8000
#define C3_DIACRITIC 0x0002
#define C3_FULLWIDTH 0x0080
#define C3_HALFWIDTH 0x0040
#define C3_HIGHSURROGATE 0x0800
#define C3_HIRAGANA 0x0020
#define C3_IDEOGRAPH 0x0100
#define C3_KASHIDA 0x0200
#define C3_KATAKANA 0x0010
#define C3_LEXICAL 0x0400
#define C3_LOWSURROGATE 0x1000
#define C3_NONSPACING 0x0001
#define C3_NOTAPPLICABLE 0x0000
#define C3_SYMBOL 0x0008
#define C3_VOWELMARK 0x0004
#define CAL_GREGORIAN 1
#define CAL_GREGORIAN_ARABIC 10
#define CAL_GREGORIAN_ME_FRENCH 9
#define CAL_GREGORIAN_US 2
#define CAL_GREGORIAN_XLIT_ENGLISH 11
#define CAL_GREGORIAN_XLIT_FRENCH 12
#define CAL_HEBREW 8
#define CAL_HIJRI 6
#define CAL_ICALINTVALUE 1
#define CAL_ITWODIGITYEARMAX 48
#define CAL_IYEAROFFSETRANGE 3
#define CAL_JAPAN 3
#define CAL_KOREA 5
#define CAL_NOUSEROVERRIDE LOCALE_NOUSEROVERRIDE
#define CAL_RETURN_NUMBER LOCALE_RETURN_NUMBER
#define CAL_SABBREVDAYNAME1 14
#define CAL_SABBREVDAYNAME2 15
#define CAL_SABBREVDAYNAME3 16
#define CAL_SABBREVDAYNAME4 17
#define CAL_SABBREVDAYNAME5 18
#define CAL_SABBREVDAYNAME6 19
#define CAL_SABBREVDAYNAME7 20
#define CAL_SABBREVMONTHNAME1 34
#define CAL_SABBREVMONTHNAME10 43
#define CAL_SABBREVMONTHNAME11 44
#define CAL_SABBREVMONTHNAME12 45
#define CAL_SABBREVMONTHNAME13 46
#define CAL_SABBREVMONTHNAME2 35
#define CAL_SABBREVMONTHNAME3 36
#define CAL_SABBREVMONTHNAME4 37
#define CAL_SABBREVMONTHNAME5 38
#define CAL_SABBREVMONTHNAME6 39
#define CAL_SABBREVMONTHNAME7 40
#define CAL_SABBREVMONTHNAME8 41
#define CAL_SABBREVMONTHNAME9 42
#define CAL_SCALNAME 2
#define CAL_SDAYNAME1 7
#define CAL_SDAYNAME2 8
#define CAL_SDAYNAME3 9
#define CAL_SDAYNAME4 10
#define CAL_SDAYNAME5 11
#define CAL_SDAYNAME6 12
#define CAL_SDAYNAME7 13
#define CAL_SERASTRING 4
#define CAL_SLONGDATE 6
#define CAL_SMONTHNAME1 21
#define CAL_SMONTHNAME10 30
#define CAL_SMONTHNAME11 31
#define CAL_SMONTHNAME12 32
#define CAL_SMONTHNAME13 33
#define CAL_SMONTHNAME2 22
#define CAL_SMONTHNAME3 23
#define CAL_SMONTHNAME4 24
#define CAL_SMONTHNAME5 25
#define CAL_SMONTHNAME6 26
#define CAL_SMONTHNAME7 27
#define CAL_SMONTHNAME8 28
#define CAL_SMONTHNAME9 29
#define CAL_SSHORTDATE 5
#define CAL_SYEARMONTH 47
#define CAL_TAIWAN 4
#define CAL_THAI 7
#define CAL_UMALQURA 23
#define CAL_USE_CP_ACP LOCALE_USE_CP_ACP
#define CALINFO_ENUMPROC CALINFO_ENUMPROCW
#define CALINFO_ENUMPROCEX CALINFO_ENUMPROCEXW
#define CODEPAGE_ENUMPROC CODEPAGE_ENUMPROCW
#define CP_ACP 0
#define CP_INSTALLED 1
#define CP_MACCP 2
#define CP_OEMCP 1
#define CP_SUPPORTED 2
#define CP_SYMBOL 42
#define CP_THREAD_ACP 3
#define CP_UTF7 65000
#define CP_UTF8 65001
#define CSTR_EQUAL 2
#define CSTR_GREATER_THAN 3
#define CSTR_LESS_THAN 1
#define CT_CTYPE1 1
#define CT_CTYPE2 2
#define CT_CTYPE3 4
#define CTRY_ALBANIA 355
#define CTRY_ALGERIA 213
#define CTRY_ARGENTINA 54
#define CTRY_ARMENIA 374
#define CTRY_AUSTRALIA 61
#define CTRY_AUSTRIA 43
#define CTRY_AZERBAIJAN 994
#define CTRY_BAHRAIN 973
#define CTRY_BELARUS 375
#define CTRY_BELGIUM 32
#define CTRY_BELIZE 501
#define CTRY_BOLIVIA 591
#define CTRY_BRAZIL 55
#define CTRY_BRUNEI_DARUSSALAM 673
#define CTRY_BULGARIA 359
#define CTRY_CANADA 2
#define CTRY_CARIBBEAN 1
#define CTRY_CHILE 56
#define CTRY_COLOMBIA 57
#define CTRY_COSTA_RICA 506
#define CTRY_CROATIA 385
#define CTRY_CZECH 420
#define CTRY_DEFAULT 0
#define CTRY_DENMARK 45
#define CTRY_DOMINICAN_REPUBLIC 1
#define CTRY_ECUADOR 593
#define CTRY_EGYPT 20
#define CTRY_EL_SALVADOR 503
#define CTRY_ESTONIA 372
#define CTRY_FAEROE_ISLANDS 298
#define CTRY_FINLAND 358
#define CTRY_FRANCE 33
#define CTRY_GEORGIA 995
#define CTRY_GERMANY 49
#define CTRY_GREECE 30
#define CTRY_GUATEMALA 502
#define CTRY_HONDURAS 504
#define CTRY_HONG_KONG 852
#define CTRY_HUNGARY 36
#define CTRY_ICELAND 354
#define CTRY_INDIA 91
#define CTRY_INDONESIA 62
#define CTRY_IRAN 981
#define CTRY_IRAQ 964
#define CTRY_IRELAND 353
#define CTRY_ISRAEL 972
#define CTRY_ITALY 39
#define CTRY_JAMAICA 1
#define CTRY_JAPAN 81
#define CTRY_JORDAN 962
#define CTRY_KAZAKSTAN 7
#define CTRY_KENYA 254
#define CTRY_KUWAIT 965
#define CTRY_KYRGYZSTAN 996
#define CTRY_LATVIA 371
#define CTRY_LEBANON 961
#define CTRY_LIBYA 218
#define CTRY_LIECHTENSTEIN 41
#define CTRY_LITHUANIA 370
#define CTRY_LUXEMBOURG 352
#define CTRY_MACAU 853
#define CTRY_MACEDONIA 389
#define CTRY_MALAYSIA 60
#define CTRY_MALDIVES 960
#define CTRY_MEXICO 52
#define CTRY_MONACO 33
#define CTRY_MONGOLIA 976
#define CTRY_MOROCCO 212
#define CTRY_NETHERLANDS 31
#define CTRY_NEW_ZEALAND 64
#define CTRY_NICARAGUA 505
#define CTRY_NORWAY 47
#define CTRY_OMAN 968
#define CTRY_PAKISTAN 92
#define CTRY_PANAMA 507
#define CTRY_PARAGUAY 595
#define CTRY_PERU 51
#define CTRY_PHILIPPINES 63
#define CTRY_POLAND 48
#define CTRY_PORTUGAL 351
#define CTRY_PRCHINA 86
#define CTRY_PUERTO_RICO 1
#define CTRY_QATAR 974
#define CTRY_ROMANIA 40
#define CTRY_RUSSIA 7
#define CTRY_SAUDI_ARABIA 966
#define CTRY_SERBIA 381
#define CTRY_SINGAPORE 65
#define CTRY_SLOVAK 421
#define CTRY_SLOVENIA 386
#define CTRY_SOUTH_AFRICA 27
#define CTRY_SOUTH_KOREA 82
#define CTRY_SPAIN 34
#define CTRY_SWEDEN 46
#define CTRY_SWITZERLAND 41
#define CTRY_SYRIA 963
#define CTRY_TAIWAN 886
#define CTRY_TATARSTAN 7
#define CTRY_THAILAND 66
#define CTRY_TRINIDAD_Y_TOBAGO 1
#define CTRY_TUNISIA 216
#define CTRY_TURKEY 90
#define CTRY_UAE 971
#define CTRY_UKRAINE 380
#define CTRY_UNITED_KINGDOM 44
#define CTRY_UNITED_STATES 1
#define CTRY_URUGUAY 598
#define CTRY_UZBEKISTAN 7
#define CTRY_VENEZUELA 58
#define CTRY_VIET_NAM 84
#define CTRY_YEMEN 967
#define CTRY_ZIMBABWE 263
#define DATE 9
#define DATE_LONGDATE 2
#define DATE_LTRREADING 16
#define DATE_RTLREADING 32
#define DATE_SHORTDATE 1
#define DATE_USE_ALT_CALENDAR 4
#define DATE_YEARMONTH 8
#define DATEFMT_ENUMPROC DATEFMT_ENUMPROCW
#define DATEFMT_ENUMPROCEX DATEFMT_ENUMPROCEXW
#define ENUM_ALL_CALENDARS (-1)
#define LANGGROUPLOCALE_ENUMPROC LANGGROUPLOCALE_ENUMPROCW
#define LANGUAGEGROUP_ENUMPROC LANGUAGEGROUP_ENUMPROCW
#define LCID_ALTERNATE_SORTS 4
#define LCID_INSTALLED 1
#define LCID_SUPPORTED 2
#define LCMAP_BYTEREV 0x00000800
#define LCMAP_FULLWIDTH 0x00800000
#define LCMAP_HALFWIDTH 0x00400000
#define LCMAP_HIRAGANA 0x00100000
#define LCMAP_KATAKANA 0x00200000
#define LCMAP_LINGUISTIC_CASING 0x01000000
#define LCMAP_LOWERCASE 0x00000100
#define LCMAP_SIMPLIFIED_CHINESE 0x02000000
#define LCMAP_SORTKEY 0x00000400
#define LCMAP_TRADITIONAL_CHINESE 0x04000000
#define LCMAP_UPPERCASE 0x00000200
#define LGRPID_ARABIC 13
#define LGRPID_ARMENIAN 17
#define LGRPID_BALTIC 3
#define LGRPID_CENTRAL_EUROPE 2
#define LGRPID_CYRILLIC 5
#define LGRPID_GEORGIAN 16
#define LGRPID_GREEK 4
#define LGRPID_HEBREW 12
#define LGRPID_INDIC 15
#define LGRPID_INSTALLED 1
#define LGRPID_JAPANESE 7
#define LGRPID_KOREAN 8
#define LGRPID_SIMPLIFIED_CHINESE 10
#define LGRPID_SUPPORTED 2
#define LGRPID_THAI 11
#define LGRPID_TRADITIONAL_CHINESE 9
#define LGRPID_TURKISH 6
#define LGRPID_VIETNAMESE 14
#define LGRPID_WESTERN_EUROPE 1
#define LOCALE_ENUMPROC LOCALE_ENUMPROCW
#define LOCALE_FONTSIGNATURE 88
#define LOCALE_ICALENDARTYPE 0x1009
#define LOCALE_ICENTURY 36
#define LOCALE_ICOUNTRY 5
#define LOCALE_ICURRDIGITS 25
#define LOCALE_ICURRENCY 27
#define LOCALE_IDATE 33
#define LOCALE_IDAYLZERO 38
#define LOCALE_IDEFAULTANSICODEPAGE 0x1004
#define LOCALE_IDEFAULTCODEPAGE 11
#define LOCALE_IDEFAULTCOUNTRY 10
#define LOCALE_IDEFAULTEBCDICCODEPAGE 0x1012
#define LOCALE_IDEFAULTLANGUAGE 9
#define LOCALE_IDIGITS 17
#define LOCALE_IDIGITSUBSTITUTION 0x1014
#define LOCALE_IFIRSTDAYOFWEEK 0x100C
#define LOCALE_IFIRSTWEEKOFYEAR 0x100D
#define LOCALE_IINTLCURRDIGITS 26
#define LOCALE_ILANGUAGE 1
#define LOCALE_ILDATE 34
#define LOCALE_ILZERO 18
#define LOCALE_IMEASURE 13
#define LOCALE_IMONLZERO 39
#define LOCALE_INEGCURR 28
#define LOCALE_INEGNUMBER 0x1010
#define LOCALE_INEGSEPBYSPACE 87
#define LOCALE_INEGSIGNPOSN 83
#define LOCALE_INEGSYMPRECEDES 86
#define LOCALE_IOPTIONALCALENDAR 0x100B
#define LOCALE_IPAPERSIZE 0x100A
#define LOCALE_IPOSSEPBYSPACE 85
#define LOCALE_IPOSSIGNPOSN 82
#define LOCALE_IPOSSYMPRECEDES 84
#define LOCALE_ITIME 35
#define LOCALE_ITIMEMARKPOSN 0x1005
#define LOCALE_ITLZERO 37
#define LOCALE_NOUSEROVERRIDE 0x80000000
#define LOCALE_RETURN_NUMBER 0x20000000
#define LOCALE_S1159 40
#define LOCALE_S2359 41
#define LOCALE_SABBREVCTRYNAME 7
#define LOCALE_SABBREVDAYNAME1 49
#define LOCALE_SABBREVDAYNAME2 50
#define LOCALE_SABBREVDAYNAME3 51
#define LOCALE_SABBREVDAYNAME4 52
#define LOCALE_SABBREVDAYNAME5 53
#define LOCALE_SABBREVDAYNAME6 54
#define LOCALE_SABBREVDAYNAME7 55
#define LOCALE_SABBREVLANGNAME 3
#define LOCALE_SABBREVMONTHNAME1 68
#define LOCALE_SABBREVMONTHNAME10 77
#define LOCALE_SABBREVMONTHNAME11 78
#define LOCALE_SABBREVMONTHNAME12 79
#define LOCALE_SABBREVMONTHNAME13 0x100F
#define LOCALE_SABBREVMONTHNAME2 69
#define LOCALE_SABBREVMONTHNAME3 70
#define LOCALE_SABBREVMONTHNAME4 71
#define LOCALE_SABBREVMONTHNAME5 72
#define LOCALE_SABBREVMONTHNAME6 73
#define LOCALE_SABBREVMONTHNAME7 74
#define LOCALE_SABBREVMONTHNAME8 75
#define LOCALE_SABBREVMONTHNAME9 76
#define LOCALE_SCOUNTRY 6
#define LOCALE_SCURRENCY 20
#define LOCALE_SDATE 29
#define LOCALE_SDAYNAME1 0
#define LOCALE_SDAYNAME2 1
#define LOCALE_SDAYNAME3 2
#define LOCALE_SDAYNAME4 3
#define LOCALE_SDAYNAME5 4
#define LOCALE_SDAYNAME6 5
#define LOCALE_SDAYNAME7 6
#define LOCALE_SDECIMAL 14
#define LOCALE_SENGCOUNTRY 0x1002
#define LOCALE_SENGCURRNAME 0x1007
#define LOCALE_SENGLANGUAGE 0x1001
#define LOCALE_SGROUPING 16
#define LOCALE_SINTLSYMBOL 21
#define LOCALE_SISO3166CTRYNAME 90
#define LOCALE_SISO639LANGNAME 89
#define LOCALE_SLANGUAGE 2
#define LOCALE_SLIST 12
#define LOCALE_SLONGDATE 32
#define LOCALE_SMONDECIMALSEP 22
#define LOCALE_SMONGROUPING 24
#define LOCALE_SMONTHNAME1 56
#define LOCALE_SMONTHNAME10 65
#define LOCALE_SMONTHNAME11 66
#define LOCALE_SMONTHNAME12 67
#define LOCALE_SMONTHNAME13 0x100E
#define LOCALE_SMONTHNAME2 57
#define LOCALE_SMONTHNAME3 58
#define LOCALE_SMONTHNAME4 59
#define LOCALE_SMONTHNAME5 60
#define LOCALE_SMONTHNAME6 61
#define LOCALE_SMONTHNAME7 62
#define LOCALE_SMONTHNAME8 63
#define LOCALE_SMONTHNAME9 64
#define LOCALE_SMONTHOUSANDSEP 23
#define LOCALE_SNATIVECTRYNAME 8
#define LOCALE_SNATIVECURRNAME 0x1008
#define LOCALE_SNATIVEDIGITS 19
#define LOCALE_SNATIVELANGNAME 4
#define LOCALE_SNEGATIVESIGN 81
#define LOCALE_SPOSITIVESIGN 80
#define LOCALE_SSHORTDATE 31
#define LOCALE_SSORTNAME 0x1013
#define LOCALE_STHOUSAND 15
#define LOCALE_STIME 30
#define LOCALE_STIMEFORMAT 0x1003
#define LOCALE_SYEARMONTH 0x1006
#define LOCALE_SYSTEM_DEFAULT 0x800
#define LOCALE_TRANSIENT_KEYBOARD1 0x2000
#define LOCALE_TRANSIENT_KEYBOARD2 0x2400
#define LOCALE_USE_CP_ACP 0x40000000
#define LOCALE_USER_DEFAULT 0x400
#define MAP_COMPOSITE 64
#define MAP_EXPAND_LIGATURES 0x2000
#define MAP_FOLDCZONE 16
#define MAP_FOLDDIGITS 128
#define MAP_PRECOMPOSED 32
#define MAX_DEFAULTCHAR 2
#define MAX_LEADBYTES 12
#define MB_COMPOSITE 2
#define MB_ERR_INVALID_CHARS 8
#define MB_PRECOMPOSED 1
#define MB_USEGLYPHCHARS 4
#define NORM_IGNORECASE 1
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The ANSI version of this function is not supported The following values are NOT supported for the dwCmpFlags parameter: [corpus/mvb/windows-ce-1.0/PEGSDK/AB140C.html] */
#define NORM_IGNOREKANATYPE 65536
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The ANSI version of this function is not supported The following values are NOT supported for the dwCmpFlags parameter: [corpus/mvb/windows-ce-1.0/PEGSDK/AB140C.html] */
#define NORM_IGNORENONSPACE 2
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The ANSI version of this function is not supported The following values are NOT supported for the dwCmpFlags parameter: [corpus/mvb/windows-ce-1.0/PEGSDK/AB140C.html] */
#define NORM_IGNORESYMBOLS 4
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The ANSI version of this function is not supported The following values are NOT supported for the dwCmpFlags parameter: [corpus/mvb/windows-ce-1.0/PEGSDK/AB140C.html] */
#define NORM_IGNOREWIDTH 131072
#define SORT_STRINGSORT 4096
#define TIME_FORCE24HOURFORMAT 8
#define TIME_NOMINUTESORSECONDS 1
#define TIME_NOSECONDS 2
#define TIME_NOTIMEMARKER 4
#define TIME_ZONE_ID_DAYLIGHT 2
#define TIME_ZONE_ID_STANDARD 1
#define TIME_ZONE_ID_UNKNOWN 0
#define TIMEFMT_ENUMPROC TIMEFMT_ENUMPROCW
#define UILANGUAGE_ENUMPROC UILANGUAGE_ENUMPROCW
#define WC_COMPOSITECHECK 512
#define WC_DEFAULTCHAR 64
#define WC_DISCARDNS 16
#define WC_NO_BEST_FIT_CHARS 1024
#define WC_SEPCHARS 32

/* ==================================================================
 * base types -- fundamental Windows type definitions
 * CE-specific types are marked; verify sizes for your platform
 * ================================================================ */

/* LCID
 * source: win32/common/windows-data-types.md */
typedef DWORD LCID;

/* LCTYPE
 * source: win32/common/windows-data-types.md */
typedef DWORD LCTYPE;

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* HIMAGELIST  [typedef; ce-only; heuristic-prefix] */

/* HIMC  [typedef; ce-only; heuristic-prefix] */

/* LPCRITICAL_SECTION  [typedef; ce-only; heuristic-prefix] */

/* LUID  [typedef; ce-only; heuristic-prefix] */

/* PCRITICAL_SECTION  [typedef; ce-only; heuristic-prefix] */

/* PCWCH  [typedef; ce-only; heuristic-prefix] */

/* PLUID  [typedef; ce-only; heuristic-prefix] */

/* REGSAM  [typedef; ce-only; heuristic-prefix] */

/* UNSIGNED  [typedef; ce-only; heuristic-prefix] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CPINFO  [struct; shared] */
typedef struct _cpinfo { 
 UINT MaxCharSize; 
 BYTE DefaultChar[MAX_DEFAULTCHAR]; 
 BYTE LeadByte[MAX_LEADBYTES]; 
} CPINFO;
typedef CPINFO *PCPINFO, *LPCPINFO;

/* CURRENCYFMT  [struct; shared; A/W CURRENCYFMTA,CURRENCYFMTW (CE is W-side)] */
typedef struct _currencyfmt { 
 UINT NumDigits; 
 UINT LeadingZero; 
 UINT Grouping; 
 LPTSTR lpDecimalSep; 
 LPTSTR lpThousandSep; 
 UINT NegativeOrder; 
 UINT PositiveOrder; 
 LPTSTR lpCurrencySymbol;
} CURRENCYFMT;
typedef CURRENCYFMT *PCURRENCYFMT, *LPCURRENCYFMT;

/* NUMBERFMT  [struct; shared; A/W NUMBERFMTA,NUMBERFMTW (CE is W-side)] */
typedef struct _numberfmt { 
 UINT NumDigits; 
 UINT LeadingZero; 
 UINT Grouping; 
 LPTSTR lpDecimalSep; 
 LPTSTR lpThousandSep; 
 UINT NegativeOrder; 
} NUMBERFMT;
typedef NUMBERFMT *PNUMBERFMT, *LPNUMBERFMT;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* GetACP  [function; shared; unified-kb; unified-kb] */
UINT GetACP(VOID);

/* GetCPInfo  [function; shared; unified-kb; unified-kb] */
BOOL GetCPInfo( 
 UINT CodePage, 
 LPCPINFO lpCPInfo 
);

/* GetOEMCP  [function; shared; unified-kb; unified-kb] */
UINT GetOEMCP(void);

/* IsDBCSLeadByte  [function; shared; unified-kb; unified-kb] */
BOOL IsDBCSLeadByte( 
 BYTE TestChar 
);

/* IsDBCSLeadByteEx  [function; shared; unified-kb; unified-kb] */
BOOL IsDBCSLeadByteEx( 
 UINT CodePage, 
 BYTE TestChar 
);

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..399, 5.0..699 */

/* MultiByteToWideChar  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, coreloc.lib, locusa.lib] */
int MultiByteToWideChar(
 UINT CodePage,
 DWORD dwFlags,
 LPCSTR lpMultiByteStr,
 int cbMultiByte,
 LPWSTR lpWideCharStr,
 int cchWideChar
);

/* WideCharToMultiByte  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, coreloc.lib, locusa.lib] */
int WideCharToMultiByte(
 UINT CodePage,
 DWORD dwFlags,
 LPCWSTR lpWideCharStr,
 int cchWideChar,
 LPSTR lpMultiByteStr,
 int cbMultiByte,
 LPCSTR lpDefaultChar,
 LPBOOL lpUsedDefaultChar
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x600)) /* CE 2.11..2.12, 3.0..599 */

/* GetStringType  [function; shared; CE 2.11..2.12, 3.0..599; Coredll.lib, Coreloc.lib, Locusa.lib; A/W GetStringTypeA (CE is W-side)] */
BOOL GetStringType( 
 DWORD dwInfoType, 
 LPCWSTR lpSrcStr, 
 int cchSrc, 
 LPWORD lpCharType 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..699 */

/* CompareString  [function; shared; CE 2.11..2.12, 3.0..699; Coreloc.lib, coreloc.lib, locusa.lib; A/W CompareStringA,CompareStringW (CE is W-side)] */
int CompareString(
 LCID Locale, 
 DWORD dwCmpFlags, 
 LPCTSTR lpString1, 
 int cchCount1, 
 LPCTSTR lpString2, 
 int cchCount2 
);

/* ConvertDefaultLocale  [function; shared; CE 2.11..2.12, 3.0..699; Coreloc.lib, coreloc.lib, locusa.lib] */
LCID ConvertDefaultLocale(
 LCID Locale
);

/* EnumCalendarInfoProc  [function; ce-only; CE 2.11..2.12, 3.0..699; Coreloc.lib] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows Embedded CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
BOOL CALLBACK EnumCalendarInfoProc(
 LPWSTR lpCalendarInfoString
);

/* EnumCodePagesProc  [function; ce-only; CE 2.11..2.12, 3.0..699; Coreloc.lib] */
BOOL CALLBACK EnumCodePagesProc( 
 LPTSTR lpCodePageString
);

/* EnumDateFormatsProc  [function; ce-only; CE 2.11..2.12, 3.0..699; Coreloc.lib] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows Embedded CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
BOOL CALLBACK EnumDateFormatsProc(
 LPWSTR lpDateFormatString
);

/* EnumLocalesProc  [function; ce-only; CE 2.11..2.12, 3.0..699; Coreloc.lib] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows Embedded CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
BOOL CALLBACK EnumLocalesProc(
 LPWSTR lpLocaleString
);

/* EnumTimeFormatsProc  [function; ce-only; CE 2.11..2.12, 3.0..699; Coreloc.lib] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows Embedded CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
BOOL CALLBACK EnumTimeFormatsProc(
 LPWSTR lpTimeFormatString 
);

/* FoldString  [function; shared; CE 2.11..2.12, 3.0..699; Coreloc.lib, coreloc.lib, locusa.lib; A/W FoldStringA,FoldStringW (CE is W-side)] */
int FoldString(
 DWORD dwMapFlags, 
 LPCTSTR lpSrcStr, 
 int cchSrc, 
 LPTSTR lpDestStr, 
 int cchDest 
);

/* GetCurrencyFormat  [function; shared; CE 2.11..2.12, 3.0..699; Coreloc.lib, coreloc.lib, locusa.lib; A/W GetCurrencyFormatA,GetCurrencyFormatW (CE is W-side)] */
int GetCurrencyFormat(
 LCID Locale, 
 DWORD dwFlags, 
 LPCTSTR lpValue, 
 const CURRENCYFMT* lpFormat, 
 LPTSTR lpCurrencyStr, 
 int cchCurrency 
);

/* GetDateFormat  [function; shared; CE 2.11..2.12, 3.0..699; Coreloc.lib, coreloc.lib, locusa.lib; A/W GetDateFormatA,GetDateFormatW (CE is W-side)] */
int GetDateFormat(
 LCID Locale, 
 DWORD dwFlags, 
 CONST SYSTEMTIME* lpDate, 
 LPCTSTR lpFormat, 
 LPTSTR lpDateStr, 
 int cchDate 
);

/* GetLocaleInfo  [function; shared; CE 2.11..2.12, 3.0..699; Coreloc.lib, coreloc.lib, locusa.lib; A/W GetLocaleInfoA,GetLocaleInfoW (CE is W-side)] */
int GetLocaleInfo(
 LCID Locale, 
 LCTYPE LCType, 
 LPTSTR lpLCData, 
 int cchData 
);

/* GetNumberFormat  [function; shared; CE 2.11..2.12, 3.0..699; Coreloc.lib, coreloc.lib, locusa.lib; A/W GetNumberFormatA,GetNumberFormatW (CE is W-side)] */
int GetNumberFormat(
 LCID Locale, 
 DWORD dwFlags, 
 LPCTSTR lpValue, 
 const NUMBERFMT* lpFormat, 
 LPTSTR lpNumberStr, 
 int cchNumber 
);

/* GetStringTypeEx  [function; shared; CE 2.11..2.12, 3.0..699; Coreloc.lib, coreloc.lib, locusa.lib; A/W GetStringTypeExW (CE is W-side)] */
/* Windows CE supports only the Unicode version of GetStringTypeEx, which ignores the Locale parameter. */
/* Windows CE supports only the Unicode version of GetStringTypeEx, which ignores the Locale parameter. */
/* Windows CE supports only the Unicode version of GetStringTypeEx, which ignores the Locale parameter. */
/* Windows CE supports only the Unicode version of GetStringTypeEx, which ignores the Locale parameter. */
/* Windows Embedded CE supports only the Unicode version of GetStringTypeEx, which ignores the Locale parameter. */
/* Windows CE supports only the Unicode version of GetStringTypeEx, which ignores the Locale parameter. */
BOOL GetStringTypeEx(
 LCID Locale, 
 DWORD dwInfoType, 
 LPCTSTR lpSrcStr, 
 int cchSrc, 
 LPWORD lpCharType 
);

/* GetSystemDefaultLCID  [function; shared; CE 2.11..2.12, 3.0..699; Coreloc.lib, coreloc.lib, locusa.lib] */
LCID GetSystemDefaultLCID(void);

/* GetTimeFormat  [function; shared; CE 2.11..2.12, 3.0..699; Coreloc.lib, coreloc.lib, locusa.lib; A/W GetTimeFormatA,GetTimeFormatW (CE is W-side)] */
int GetTimeFormat(
 LCID Locale, 
 DWORD dwFlags, 
 const SYSTEMTIME* lpTime, 
 LPCTSTR lpFormat, 
 LPTSTR lpTimeStr, 
 int cchTime 
);

/* GetUserDefaultLCID  [function; shared; CE 2.11..2.12, 3.0..699; Coreloc.lib, coreloc.lib, locusa.lib] */
LCID GetUserDefaultLCID(void);

/* IsValidCodePage  [function; shared; CE 2.11..2.12, 3.0..699; Coreloc.lib, coreloc.lib, locusa.lib] */
BOOL IsValidCodePage(
 UINT CodePage 
);

/* IsValidLocale  [function; shared; CE 2.11..2.12, 3.0..699; Coreloc.lib, coreloc.lib, locusa.lib] */
BOOL IsValidLocale(
 LCID Locale, 
 DWORD dwFlags 
);

/* LCMapString  [function; shared; CE 2.11..2.12, 3.0..699; Coreloc.lib, coreloc.lib, locusa.lib; A/W LCMapStringA,LCMapStringW (CE is W-side)] */
/* Even though Windows CE supports only the Unicode version of this function, the output string is only in WCHAR or CHAR format if the string mapping mode of LCMapString is used. */
/* Even though Windows CE supports only the Unicode version of this function, the output string is only in WCHAR or CHAR format if the string-mapping mode of LCMapString is used. */
/* Even though Windows CE supports only the Unicode version of this function, the output string is only in WCHAR or CHAR format if the string-mapping mode of LCMapString is used. */
/* Even though Windows CE supports only the Unicode version of this function, the output string is only in WCHAR or CHAR format if the string-mapping mode of LCMapString is used. */
/* Even though Windows Embedded CE supports only the Unicode version of this function, the output string is only in WCHAR or CHAR format if the string-mapping mode of LCMapString is used. */
/* Even though Windows CE supports only the Unicode version of this function, the output string is only in WCHAR or CHAR format if the string mapping mode of LCMapString is used. */
int LCMapString(
 LCID Locale, 
 DWORD dwMapFlags, 
 LPCTSTR lpSrcStr, 
 int cchSrc, 
 LPTSTR lpDestStr, 
 int cchDest 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* GetStringTypeW  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL GetStringTypeW(
 DWORD dwInfoType, 
 LPCWSTR lpSrcStr, 
 int cchSrc, 
 LPWORD lpCharType 
);
#endif /* _WIN32_WCE */

#endif /* _WINNLS_ */
