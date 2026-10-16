/* Oaidl.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 61 constants, 30 declarations, 19 outlines, 0 base types, 0 extra macros, 100 extra decls
 */
#ifndef _OAIDL_
#define _OAIDL_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DISPID_COLLECT (-8)
#define DISPID_CONSTRUCTOR (-6)
#define DISPID_DESTRUCTOR (-7)
#define DISPID_EVALUATE (-5)
#define DISPID_NEWENUM (-4)
#define DISPID_PROPERTYPUT (-3)
#define DISPID_UNKNOWN (-1)
#define DISPID_VALUE (0)
#define FADF_AUTO 0x0001
#define FADF_BSTR 0x0100
#define FADF_CREATEVECTOR (0x2000)
#define FADF_DATADELETED (0x1000)
#define FADF_DISPATCH 0x0400
#define FADF_EMBEDDED 0x0004
#define FADF_FIXEDSIZE 0x0010
#define FADF_HAVEIID 0x0040
#define FADF_HAVEVARTYPE 0x0080
#define FADF_RECORD 0x0020
#define FADF_RESERVED 0xF0E8
#define FADF_STATIC 0x0002
#define FADF_UNKNOWN 0x0200
#define FADF_VARIANT 0x0800
#define IDLFLAG_FIN PARAMFLAG_FIN
#define IDLFLAG_FLCID PARAMFLAG_FLCID
#define IDLFLAG_FOUT PARAMFLAG_FOUT
#define IDLFLAG_FRETVAL PARAMFLAG_FRETVAL
#define IDLFLAG_NONE PARAMFLAG_NONE
#define IMPLTYPEFLAG_FDEFAULT 0x1
#define IMPLTYPEFLAG_FDEFAULTVTABLE 0x8
#define IMPLTYPEFLAG_FRESTRICTED 0x4
#define IMPLTYPEFLAG_FSOURCE 0x2
#define PARAMFLAG_FHASDEFAULT (32)
#define PARAMFLAG_FIN (1)
#define PARAMFLAG_FLCID (4)
#define PARAMFLAG_FOPT (16)
#define PARAMFLAG_FOUT (2)
#define PARAMFLAG_FRETVAL (8)
#define PARAMFLAG_NONE (0)
#define VT_BLOB 65
#define VT_BLOBOBJECT 70
#define VT_BSTR_BLOB 0xfff
#define VT_CF 71
#define VT_CLSID 72
#define VT_DECIMAL 14
#define VT_FILETIME 64
#define VT_I1 16
#define VT_I8 20
#define VT_INT 22
#define VT_LPSTR 30
#define VT_LPWSTR 31
#define VT_STORAGE 67
#define VT_STORED_OBJECT 69
#define VT_STREAM 66
#define VT_STREAMED_OBJECT 68
#define VT_TYPEMASK 0xFFF
#define VT_UI2 18
#define VT_UI4 19
#define VT_UI8 21
#define VT_UINT 23
#define VT_VECTOR 0x1000
#define VT_VERSIONED_STREAM 73

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* IDLDESC  [struct; ce-only] */

/* module  [typedef; ce-only; entity-headers] */

/* SAFEARRAY  [struct, macro; shared] */
typedef struct FARSTRUCT tagSAFEARRAY {
 unsigned short cDims;
 unsigned short fFeatures;
 unsigned short cbElements;
 unsigned short cLocks;
 unsigned long handle;
 void HUGEP* pvData;
 SAFEARRAYBOUND rgsabound[1];
} SAFEARRAY;

/* union  [typedef; ce-only; entity-headers] */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)) /* CE 3.0..399, 4.2..599 */

/* IEnumVARIANT  [interface; shared; CE 3.0..399, 4.2..599; Oleaut32.lib, Uuid.lib] */
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 3.0..399, 5.0..599 */

/* ICreateErrorInfo  [interface; shared; CE 3.0..399, 5.0..599; Oleaut32.lib, Uuid.lib] */

/* ICreateTypeInfo  [interface; shared; CE 3.0..399, 5.0..599; Oleaut32.lib, Uuid.lib] */

/* ICreateTypeLib  [interface; shared; CE 3.0..399, 5.0..599; Oleaut32.lib, Uuid.lib] */

/* IDispatch  [interface; shared; CE 3.0..399, 5.0..599; Oleaut32.lib, Uuid.lib] */

/* IErrorInfo  [interface; shared; CE 3.0..399, 5.0..599; Oleaut32.lib, Uuid.lib] */

/* ISupportErrorInfo  [interface; shared; CE 3.0..399, 5.0..599; Oleaut32.lib, Uuid.lib] */

/* ITypeComp  [interface; shared; CE 3.0..399, 5.0..599; Oleaut32.lib, Uuid.lib] */

/* ITypeInfo  [interface; shared; CE 3.0..399, 5.0..599; Oleaut32.lib, Uuid.lib] */

/* ITypeInfo2  [interface; shared; CE 3.0..399, 5.0..599; Oleaut32.lib, Uuid.lib] */

/* ITypeLib  [interface; shared; CE 3.0..399, 5.0..599; Oleaut32.lib, Uuid.lib] */
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 5.0..599 */

/* ICreateTypeInfo2  [interface; shared; CE 5.0..599; Oleaut32.lib, Uuid.lib] */

/* ICreateTypeLib2  [interface; shared; CE 5.0..599; Oleaut32.lib, Uuid.lib] */

/* ITypeLib2  [interface; shared; CE 5.0..599; Oleaut32.lib, Uuid.lib] */
#endif /* _WIN32_WCE */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CALLCONV  [enum; shared] */
typedef enum tagCALLCONV {
 CC_CDECL = 1,
 CC_MSCPASCAL = 2,
 CC_PASCAL = CC_MSCPASCAL,
 CC_MACPASCAL = 3,
 CC_STDCALL = 4,
 CC_RESERVED = 5,
 CC_SYSCALL = 6,
 CC_MPWCDECL = 7,
 CC_MPWPASCAL = 8,
 CC_MAX = 9
} CALLCONV;
typedef CALLCONV *PCALLCONV, *LPCALLCONV;

/* CURRENCY  [typedef; ce-only] */
typedef CY CURRENCY;

/* DESCKIND  [enum; shared] */
typedef enum tagDESCKIND {
 DESCKIND_NONE,
 DESCKIND_FUNCDESC,
 DESCKIND_VARDESC,
 DESCKIND_TYPECOMP,
 DESCKIND_IMPLICITAPPOBJ
} DESCKIND;
typedef DESCKIND *PDESCKIND, *LPDESCKIND;

/* FUNCFLAGS  [enum; shared] */
typedef enum tagFUNCFLAGS {
 FUNCFLAG_FRESTRICTED = 0x1,
 FUNCFLAG_FSOURCE = 0x2,
 FUNCFLAG_FBINDABLE = 0x4,
 FUNCFLAG_FREQUESTEDIT = 0x8,
 FUNCFLAG_FDISPLAYBIND = 0x10,
 FUNCFLAG_FDEFAULTBIND = 0x20,
 FUNCFLAG_FHIDDEN = 0x40,
 FUNCFLAG_FUSESGETLASTERROR = 0x80,
 FUNCFLAG_FDEFAULTCOLLELEM = 0x100,
 FUNCFLAG_FUIDEFAULT = 0x200,
 FUNCFLAG_FNONBROWSABLE = 0x400,
 FUNCFLAG_FREPLACEABLE = 0x800,
 FUNCFLAG_FIMMEDIATEBIND = 0x1000
} FUNCFLAGS;
typedef FUNCFLAGS *PFUNCFLAGS, *LPFUNCFLAGS;

/* FUNCKIND  [enum; shared] */
typedef enum tagFUNCKIND {
 FUNC_VIRTUAL,
 FUNC_PUREVIRTUAL,
 FUNC_NONVIRTUAL,
 FUNC_STATIC,
 FUNC_DISPATCH,
} FUNCKIND;
typedef FUNCKIND *PFUNCKIND, *LPFUNCKIND;

/* HREFTYPE  [typedef; ce-only] */
typedef unsigned long HREFTYPE;

/* INVOKEKIND  [enum; shared] */
typedef enum tagINVOKEKIND {
 INVOKE_FUNC = DISPATCH_METHOD,
 INVOKE_PROPERTYGET = DISPATCH_PROPERTYGET,
 INVOKE_PROPERTYPUT = DISPATCH_PROPERTYPUT,
 INVOKE_PROPERTYPUTREF = DISPATCH_PROPERTYPUTREF
} INVOKEKIND;
typedef INVOKEKIND *PINVOKEKIND, *LPINVOKEKIND;

/* SAFEARRAYBOUND  [struct; shared] */
typedef struct tagSAFEARRAYBOUND {
 unsigned long cElements;
 long lLbound;
} SAFEARRAYBOUND;
typedef SAFEARRAYBOUND *PSAFEARRAYBOUND, *LPSAFEARRAYBOUND;

/* SYSKIND  [enum; shared] */
typedef enum tagSYSKIND {
 SYS_WIN16 = 0, 
 SYS_WIN32 = SYS_WIN16 +1, 
 SYS_MAC = SYS_WIN32 +1
} SYSKIND;
typedef SYSKIND *PSYSKIND, *LPSYSKIND;

/* TYPEFLAGS  [enum; shared] */
typedef enum tagTYPEFLAGS {
 TYPEFLAG_FAPPOBJECT = 0x01, 
 TYPEFLAG_FCANCREATE = 0x02, 
 TYPEFLAG_FLICENSED = 0x04, 
 TYPEFLAG_FPREDECLID = 0x08,
 TYPEFLAG_FHIDDEN = 0x10, 
 TYPEFLAG_FCONTROL = 0x20, 
 TYPEFLAG_FDUAL = 0x40, 
 TYPEFLAG_FNONEXTENSIBLE = 0x80, 
 TYPEFLAG_FOLEAUTOMATION = 0x100, 
 TYPEFLAG_FRESTRICTED = 0x200, 
 TYPEFLAG_FAGGREGATABLE = 0x400, 
 TYPEFLAG_FREPLACEABLE = 0x800, 
 TYPEFLAG_FDISPATCHABLE = 0x1000, 
 TYPEFLAG_FREVERSEBIND = 0x2000, 
} TYPEFLAGS;
typedef TYPEFLAGS *PTYPEFLAGS, *LPTYPEFLAGS;

/* TYPEKIND  [enum; shared] */
typedef enum tagTYPEKIND {
 TKIND_ENUM = 0,
 TKIND_RECORD,
 TKIND_MODULE,
 TKIND_INTERFACE,
 TKIND_DISPATCH,
 TKIND_COCLASS,
 TKIND_ALIAS,
 TKIND_UNION,
 TKIND_MAX
} TYPEKIND;
typedef TYPEKIND *PTYPEKIND, *LPTYPEKIND;

/* VARKIND  [enum; shared] */
typedef enum tagVARKIND { 
 VAR_PERINSTANCE = 0, 
 VAR_STATIC = VAR_PERINSTANCE +1, 
 VAR_CONST = VAR_STATIC +1, 
 VAR_DISPATCH = VAR_CONST +1 
} VARKIND;
typedef VARKIND *PVARKIND, *LPVARKIND;

/* VARTYPE  [enum, function; ce-only] */
typedef unsigned short VARTYPE;
enum VARENUM {
 VT_EMPTY = 0, 
 VT_NULL = 1, 
 VT_I2 = 2, 
 VT_I4 = 3, 
 VT_R4 = 4, 
 VT_R8 = 5, 
 VT_CY = 6, 
 VT_DATE = 7, 
 VT_BSTR = 8, 
 VT_DISPATCH = 9, 
 VT_ERROR = 10, 
 VT_BOOL = 11, 
 VT_VARIANT = 12, 
 VT_UNKNOWN = 13, 
 VT_UI1 = 17, 
};
VT_RESERVED = 0x8000
VT_BYREF = 0x4000
VT_ARRAY = 0x2000

/* EXCEPINFO  [struct; shared] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   wCode */
/*   wReserved */
/*   bstrSource */
/*   bstrDescription */
/*   bstrHelpFile */
/*   dwHelpContext */
/*   pvReserved */
/*   pfnDeferredFillIn */
/*   scode */

/* PROPVARIANT  [struct; shared] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   tag_inner_PROPVARIANT */
/*   decVal */

/* CLIPDATA  [extra struct] */
typedef struct tagCLIPDATA { // cbSize is the size of the buffer pointed to // by pClipData, plus sizeof(ulClipFmt) ULONG cbSize; long ulClipFmt; BYTE* pClipData; } CLIPDATA;

/* CY  [extra struct] */
typedef struct tagCY { unsigned long Lo; long Hi; } CY;

/* DECIMAL  [extra struct] */
typedef struct tagDEC { USHORT wReserved; BYTE scale; BYTE sign; ULONG Hi32; ULONGLONG Lo64; } DECIMAL;

/* tagIDLDESC  [extra struct] */
typedef struct tagIDLDESC { ULONG dwReserved; USHORT wIDLFlags; };

/* VARIANT_BOOL  [extra typedef] */
typedef short VARIANT_BOOL;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* DISPID  [?; ce-only; CE 4.0..699] */
Typedef LONG DISPID;
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* FreePropVariantArray  [function; shared; CE 5.0..699; Oleaut32.lib, oleaut32.lib] */
WINOLEAPI FreePropVariantArray(
 ULONG cVariants,
 PROPVARIANT* rgvars
);

/* PropVariantClear  [function; shared; CE 5.0..699; Oleaut32.lib, oleaut32.lib] */
WINOLEAPI PropVariantClear(
 PROPVARIANT* pvar
);

/* PropVariantCopy  [function; shared; CE 5.0..699; Oleaut32.lib, oleaut32.lib] */
WINOLEAPI PropVariantCopy(
 PROPVARIANT* pvarDest,
 const PROPVARIANT* pvarSrc
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT AddFuncDesc( unsigned int index, FUNCDESC FAR *pFuncDesc);
HRESULT AddImplType( unsigned int index, HREFTYPE hRefType);
HRESULT AddRefTypeInfo( ITypeInfo FAR *pTInfo, HREFTYPE FAR *phRefType);
HRESULT AddVarDesc( unsigned int index, VARDESC FAR *pVarDesc);
HRESULT DeleteFuncDesc( unsigned int index);
HRESULT DeleteImplType( unsigned int index);
HRESULT DeleteVarDesc( unsigned int index);
HRESULT GetAllCustData( CUSTDATA *pCustData );
HRESULT GetAllFuncCustData( unsigned int index, CUSTDATA *pCustData );
HRESULT GetAllImplTypeCustData( unsigned int index, CUSTDATA *pCustData );
HRESULT GetAllParamCustData( unsigned int indexFunc, unsigned int indexParam, CUSTDATA *pCustData);
HRESULT GetAllVarCustData( unsigned int index, CUSTDATA *pCustData);
HRESULT GetContainingTypeLib( ITypeLib FAR *FAR *ppTLib, unsigned int FAR *pIndex );
HRESULT GetFuncDesc( unsigned int index, FUNCDESC FAR *FAR *ppFuncDesc );
HRESULT GetHelpContext( DWORD *pdwHelpContext );
HRESULT GetImplTypeFlags( unsigned int index, int *pImplTypeFlags );
HRESULT GetLibAttr( TLIBATTR FAR *FAR *ppTLibAttrr );
HRESULT GetLibStatistics( unsigned long *pcUniqueNames, unsigned long *pcchUniqueNames );
HRESULT GetRefTypeInfo( HREFTYPE hRefType, ITypeInfo FAR *FAR *ppTInfo );
HRESULT GetRefTypeOfImplType( unsigned int index, HREFTYPE FAR *pRefType );
HRESULT GetTypeAttr( TYPEATTR FAR *FAR *ppTypeAttr );
HRESULT GetTypeComp( ITypeComp FAR *FAR *ppTComp );
HRESULT GetTypeFlags( unsigned long *pTypeFlags);
HRESULT GetTypeInfo( unsigned int iTInfo, LCID lcid, ITypeInfo FAR *FAR *ppTInfo);
HRESULT GetTypeInfoCount( unsigned int FAR *pctinfo);
HRESULT GetTypeInfoType( unsigned int index, TYPEKIND FAR *pTKind );
HRESULT GetTypeKind( TYPEKIND *pTypeKind);
HRESULT GetVarDesc( unsigned int index, VARDESC FAR *FAR *ppVarDesc );
HRESULT Hash( DWORD *pdwHash);
HRESULT IsSystemMoniker( DWORD *pdwMksys);
HRESULT LayOut();
void OnClose();
void OnSave();
void OnViewChange( DWORD dwAspect, LONG lindex);
HRESULT ReleaseFuncDesc( FUNCDESC FAR *pFuncDesc );
HRESULT ReleaseTLibAttr( TLIBATTR FAR *pTLibAttr );
HRESULT ReleaseTypeAttr( TYPEATTR FAR *pTypeAttr );
HRESULT ReleaseVarDesc( VARDESC FAR *pVarDesc );
HRESULT SetAlignment( unsigned short cbAlignment);
HRESULT SetFuncHelpContext( unsigned int index, unsigned long dwHelpContext);
HRESULT SetFuncHelpStringContext( unsigned int index, DWORD dwHelpStringContext);
HRESULT SetHelpContext( DWORD dwHelpContext);
HRESULT SetHelpStringContext( DWORD *dwHelpStringContext);
HRESULT SetImplTypeFlags( unsigned int index, int implTypeFlags);
HRESULT SetLcid( LCID lcid);
HRESULT SetLibFlags( unsigned int uLibFlags);
HRESULT SetTypeDescAlias( TYPEDESC FAR *pTDescAlias);
HRESULT SetTypeFlags( unsigned int uTypeFlags);
HRESULT SetVarHelpContext( unsigned int index, unsigned long dwHelpContext);
HRESULT SetVarHelpStringContext( unsigned int index, DWORD dwHelpStringContext);
HRESULT SetVersion( unsigned short wMajorVerNum, unsigned short wMinorVerNum);

#endif /* _OAIDL_ */
