/* Mshtmhst.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 8 declarations, 3 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _MSHTMHST_
#define _MSHTMHST_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* SHOWHTMLDIALOGEXFN  [typedef; ce-only; mshtml.dll] */

/* SHOWHTMLDIALOGFN  [typedef; ce-only; mshtml.dll] */

/* SHOWMODELESSHTMLDIALOGFN  [typedef; ce-only; mshtml.dll] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DOCHOSTUIDBLCLK  [enum; ce-only] */
typedef enum tagDOCHOSTUIDBLCLK { 
 DOCHOSTUIDBLCLK_DEFAULT = 0, 
 DOCHOSTUIDBLCLK_SHOWPROPERTIES = 1, 
 DOCHOSTUIDBLCLK_SHOWCODE = 2 
} DOCHOSTUIDBLCLK;
typedef DOCHOSTUIDBLCLK *PDOCHOSTUIDBLCLK, *LPDOCHOSTUIDBLCLK;

/* DOCHOSTUIFLAG  [enum; ce-only] */
typedef enum tagDOCHOSTUIFLAG { 
 DOCHOSTUIFLAG_DIALOG = 0x00000001, 
 DOCHOSTUIFLAG_DISABLE_HELP_MENU = 0x00000002, 
 DOCHOSTUIFLAG_NO3DBORDER = 0x00000004, 
 DOCHOSTUIFLAG_SCROLL_NO = 0x00000008, 
 DOCHOSTUIFLAG_DISABLE_SCRIPT_INACTIVE = 0x00000010, 
 DOCHOSTUIFLAG_OPENNEWWIN = 0x00000020, 
 DOCHOSTUIFLAG_DISABLE_OFFSCREEN = 0x00000040, 
 DOCHOSTUIFLAG_FLAT_SCROLLBAR = 0x00000080, 
 DOCHOSTUIFLAG_DIV_BLOCKDEFAULT = 0x00000100, 
 DOCHOSTUIFLAG_ACTIVATE_CLIENTHIT_ONLY = 0x00000200, 
 DOCHOSTUIFLAG_OVERRIDEBEHAVIORFACTORY = 0x00000400, 
 DOCHOSTUIFLAG_CODEPAGELINKEDFONTS = 0x00000800, 
 DOCHOSTUIFLAG_URL_ENCODING_DISABLE_UTF8 = 0x00001000, 
 DOCHOSTUIFLAG_URL_ENCODING_ENABLE_UTF8 = 0x00002000, 
 DOCHOSTUIFLAG_ENABLE_FORMS_AUTOCOMPLETE = 0x00004000, 
 DOCHOSTUIFLAG_ENABLE_INPLACE_NAVIGATION = 0x00010000, 
 DOCHOSTUIFLAG_IME_ENABLE_RECONVERSION = 0x00020000, 
 DOCHOSTUIFLAG_THEME = 0x00040000, 
 DOCHOSTUIFLAG_NOTHEME = 0x00080000, 
 DOCHOSTUIFLAG_NOPICS = 0x00100000, 
 DOCHOSTUIFLAG_NO3DOUTERBORDER = 0x00200000 
} DOCHOSTUIFLAG;
typedef DOCHOSTUIFLAG *PDOCHOSTUIFLAG, *LPDOCHOSTUIFLAG;

/* DOCHOSTUITYPE  [enum; ce-only] */
typedef enum tagDOCHOSTUITYPE { 
 DOCHOSTUITYPE_BROWSE = 0, 
 DOCHOSTUITYPE_AUTHOR = 1 
} DOCHOSTUITYPE;
typedef DOCHOSTUITYPE *PDOCHOSTUITYPE, *LPDOCHOSTUITYPE;

/* NVFOCUS_DIRECTION  [enum; ce-only] */
typedef enum _NvFocusDirection {
 FOCUS_NONE = 0,
 FOCUS_UP = 1,
 FOCUS_DOWN = 2,
 FOCUS_LEFT = 3,
 FOCUS_RIGHT = 4,
} NVFOCUS_DIRECTION;
typedef NVFOCUS_DIRECTION *PNVFOCUS_DIRECTION, *LPNVFOCUS_DIRECTION;

#endif /* _MSHTMHST_ */
