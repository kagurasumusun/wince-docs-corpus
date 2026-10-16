/* Oleauto.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 63 constants, 189 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _OLEAUTO_
#define _OLEAUTO_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ACTIVEOBJECT_STRONG 0
#define ACTIVEOBJECT_WEAK 1
#define DISPATCH_METHOD 1
#define DISPATCH_PROPERTYGET 2
#define DISPATCH_PROPERTYPUT 4
#define DISPATCH_PROPERTYPUTREF 8
#define ID_DEFAULTINST (-2)
#define LOCALE_USE_NLS 0x10000000
#define MEMBERID_NIL DISPID_UNKNOWN
#define NUMPRS_CURRENCY 0x00400
#define NUMPRS_DECIMAL 0x00100
#define NUMPRS_EXPONENT 0x00800
#define NUMPRS_HEX_OCT 0x00040
#define NUMPRS_INEXACT 0x20000
#define NUMPRS_LEADING_MINUS 0x00010
#define NUMPRS_LEADING_PLUS 0x00004
#define NUMPRS_LEADING_WHITE 0x00001
#define NUMPRS_NEG 0x10000
#define NUMPRS_PARENS 0x00080
#define NUMPRS_STD 0x01FFF
#define NUMPRS_THOUSANDS 0x00200
#define NUMPRS_TRAILING_MINUS 0x00020
#define NUMPRS_TRAILING_PLUS 0x00008
#define NUMPRS_TRAILING_WHITE 0x00002
#define NUMPRS_USE_ALL 0x01000
#define STDOLE_LCID 0
#define STDOLE_MAJORVERNUM 1
#define STDOLE_MINORVERNUM 0
#define VAR_CALENDAR_GREGORIAN 0x0100
#define VAR_CALENDAR_HIJRI 0x0008
#define VAR_CALENDAR_THAI 0x0080
#define VAR_DATEVALUEONLY 0x0002
#define VAR_FORMAT_NOSUBSTITUTE 0x0020
#define VAR_FOURDIGITYEARS 0x0040
#define VAR_LOCALBOOL 0x0010
#define VAR_TIMEVALUEONLY 0x0001
#define VAR_VALIDDATE 0x0004
#define VARCMP_EQ 1
#define VARCMP_GT 2
#define VARCMP_LT 0
#define VARCMP_NULL 3
#define VARIANT_ALPHABOOL 0x02
#define VARIANT_CALENDAR_GREGORIAN 0x40
#define VARIANT_CALENDAR_HIJRI 0x08
#define VARIANT_CALENDAR_THAI 0x20
#define VARIANT_LOCALBOOL 0x08
#define VARIANT_NOUSEOVERRIDE 0x04
#define VARIANT_NOUSEROVERRIDE 0x04
#define VARIANT_NOVALUEPROP 0x01
#define VARIANT_USE_NLS 0x80
#define VTBIT_CY (1<<VT_CY)
#define VTBIT_DECIMAL (1<<VT_DECIMAL)
#define VTBIT_I1 (1<<VT_I1)
#define VTBIT_I2 (1<<VT_I2)
#define VTBIT_I4 (1<<VT_I4)
#define VTBIT_I8 (1<<VT_I8)
#define VTBIT_R4 (1<<VT_R4)
#define VTBIT_R8 (1<<VT_R8)
#define VTBIT_UI1 (1<<VT_UI1)
#define VTBIT_UI2 (1<<VT_UI2)
#define VTBIT_UI4 (1<<VT_UI4)
#define VTBIT_UI8 (1<<VT_UI8)
#define WINOLEAUTAPI STDAPI

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* Var  [struct; ce-only; heuristic-prefix] */
typedef struct Var {
 WORD wLength;
 WORD wValueLength;
 WORD wType;
 WCHAR szKey[];
 WORD Padding[];
 DWORD Value[];
} Var;
typedef Var *PVar, *LPVar;

/* VarFileInfo  [struct; ce-only; heuristic-prefix] */
typedef struct VarFileInfo {
 WORD wLength;
 WORD wValueLength;
 WORD wType;
 WCHAR szKey[];
 WORD Padding[];
 Var Children[];
} VarFileInfo;
typedef VarFileInfo *PVarFileInfo, *LPVarFileInfo;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 1.0..199, 2.11..2.12, 3.0..699 */

/* VarBoolFromI2  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarBoolFromI2(
 short sIn, 
 BOOL* pboolOut 
);

/* VarBoolFromI4  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarBoolFromI4(
 long lIn, 
 BOOL* pboolOut 
);

/* VarBoolFromR4  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarBoolFromR4(
 float fltIn, 
 BOOL* pboolOut 
);

/* VarBoolFromR8  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarBoolFromR8(
 double dblIn, 
 BOOL* pboolOut 
);

/* VarBoolFromUI1  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarBoolFromUI1(
 BYTE bIn, 
 BOOL* pboolOut 
);

/* VarI2FromBool  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarI2FromBool(
 BOOL boolIn, 
 short* psOut 
);

/* VarI2FromI4  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarI2FromI4(
 LONG lIn, 
 short* psOut 
);

/* VarI2FromR4  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarI2FromR4(
 float fltIn, 
 short* psOut 
);

/* VarI2FromR8  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarI2FromR8(
 double dblIn, 
 short* psOut 
);

/* VarI2FromUI1  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarI2FromUI1(
 BYTE bIn, 
 short* psOut 
);

/* VarI4FromBool  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarI4FromBool(
 BOOL boolIn, 
 long* plOut 
);

/* VarI4FromI2  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarI4FromUI1(
 short sIn, 
 long* plOut 
);

/* VarI4FromR4  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarI4FromR4(
 float fltIn, 
 long* plOut 
);

/* VarI4FromR8  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarI4FromR8(
 double dblIn, 
 long* plOut 
);

/* VarI4FromUI1  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarI4FromUI1(
 BYTE bIn, 
 long* plOut 
);

/* VarR4FromBool  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarR4FromBool(
 BOOL boolIn, 
 float* pfltOut 
);

/* VarR4FromI2  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarR4FromI2(
 short sIn, 
 float* pfltOut 
);

/* VarR4FromI4  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarR4FromI4(
 long lIn, 
 float* pfltOut 
);

/* VarR4FromR8  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarR4FromR8(
 DOUBLE dblIn, 
 float* pfltOut 
);

/* VarR4FromUI1  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarR4FromUI1(
 BYTE bIn, 
 float* pfltOut 
);

/* VarR8FromBool  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarR8FromBool(
 BOOL boolIn, 
 double* pdblOut 
);

/* VarR8FromI2  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarR8FromI2(
 short sIn, 
 double* pdblOut 
);

/* VarR8FromI4  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarR8FromI4(
 long lIn, 
 double* pdblOut 
);

/* VarR8FromR4  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarR8FromR4(
 float fltIn, 
 double* pdblOut 
);

/* VarR8FromUI1  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarR8FromUI1(
 BYTE bIn, 
 double* pdblOut 
);

/* VarUI1FromBool  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarUI1FromBool(
 BOOL boolIn, 
 BYTE* pbOut 
);

/* VarUI1FromI2  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarUI1FromI2(
 short sIn, 
 BYTE* pbOut 
);

/* VarUI1FromI4  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarUI1FromI4(
 long lIn, 
 BYTE* pbOut 
);

/* VarUI1FromR4  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarUI1FromR4(
 float fltIn, 
 BYTE* pbOut 
);

/* VarUI1FromR8  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT VarUI1FromR8(
 double dblIn, 
 BYTE* pbOut 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..699 */

/* GetErrorInfo  [function; shared; CE 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
HRESULT GetErrorInfo( 
 DWORD dwReserved, 
 IerrorInfo** pperrinfo 
);

/* SystemTimeToVariantTime  [function; shared; CE 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
int SystemTimeToVariantTime(
 SYSTEMTIME lpSystemTime, 
 double* pvtime 
);

/* VariantTimeToSystemTime  [function; shared; CE 2.11..2.12, 3.0..699; Oleaut32.lib, oleaut32.lib] */
int VariantTimeToSystemTime(
 double vtime, 
 LPSYSTEMTIME lpSystemTime 
);
#endif /* _WIN32_WCE */

#endif /* _OLEAUTO_ */
