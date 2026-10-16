/* Commdlg.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 230 constants, 26 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _COMMDLG_
#define _COMMDLG_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define BOLD_FONTTYPE 0x0100
#define CC_ANYCOLOR 0x00000100
#define CC_ENABLEHOOK 0x00000010
#define CC_ENABLETEMPLATE 0x00000020
#define CC_ENABLETEMPLATEHANDLE 0x00000040
#define CC_FULLOPEN 0x00000002
#define CC_PREVENTFULLOPEN 0x00000004
#define CC_RGBINIT 0x00000001
#define CC_SHOWHELP 0x00000008
#define CC_SOLIDCOLOR 0x00000080
#define CD_LBSELADD 2
#define CD_LBSELCHANGE 0
#define CD_LBSELNOITEMS (-1)
#define CD_LBSELSUB 1
#define CDERR_DIALOGFAILURE 0xFFFF
#define CDERR_FINDRESFAILURE 0x0006
#define CDERR_INITIALIZATION 0x0002
#define CDERR_LOADRESFAILURE 0x0007
#define CDERR_LOADSTRFAILURE 0x0005
#define CDERR_LOCKRESFAILURE 0x0008
#define CDERR_MEMALLOCFAILURE 0x0009
#define CDERR_MEMLOCKFAILURE 0x000A
#define CDERR_NOHINSTANCE 0x0004
#define CDERR_NOHOOK 0x000B
#define CDERR_NOTEMPLATE 0x0003
#define CDERR_REGISTERMSGFAIL 0x000C
#define CDERR_STRUCTSIZE 0x0001
#define CDM_FIRST (WM_USER+100)
#define CDM_GETFILEPATH (CDM_FIRST+1)
#define CDM_GETFOLDERIDLIST (CDM_FIRST+3)
#define CDM_GETFOLDERPATH (CDM_FIRST+2)
#define CDM_GETSPEC CDM_FIRST
#define CDM_HIDECONTROL (CDM_FIRST+5)
#define CDM_LAST (WM_USER+200)
#define CDM_SETCONTROLTEXT (CDM_FIRST+4)
#define CDM_SETDEFEXT (CDM_FIRST+6)
#define CDN_FILEOK (CDN_FIRST-5U)
#define CDN_FOLDERCHANGE (CDN_FIRST-2U)
#define CDN_HELP (CDN_FIRST-4U)
#define CDN_INITDONE CDN_FIRST
#define CDN_SELCHANGE (CDN_FIRST-1U)
#define CDN_SHAREVIOLATION (CDN_FIRST-3U)
#define CDN_TYPECHANGE (CDN_FIRST-6U)
#define CF_ANSIONLY 0x00000400L
#define CF_APPLY 0x00000200L
#define CF_BOTH 0x00000003
#define CF_EFFECTS 0x00000100L
#define CF_ENABLEHOOK 0x00000008L
#define CF_ENABLETEMPLATE 0x00000010L
#define CF_ENABLETEMPLATEHANDLE 0x00000020L
#define CF_FIXEDPITCHONLY 0x00004000L
#define CF_FORCEFONTEXIST 0x00010000L
#define CF_INACTIVEFONTS 0x02000000L
#define CF_INITTOLOGFONTSTRUCT 0x00000040L
#define CF_LIMITSIZE 0x00002000L
#define CF_NOFACESEL 0x00080000L
#define CF_NOOEMFONTS 0x00000800L
#define CF_NOSCRIPTSEL 0x00800000L
#define CF_NOSIMULATIONS 0x00001000L
#define CF_NOSIZESEL 0x00200000L
#define CF_NOSTYLESEL 0x00100000L
#define CF_NOVECTORFONTS 0x00000800L
#define CF_NOVERTFONTS 0x01000000L
#define CF_PRINTERFONTS 0x00000002
#define CF_SCALABLEONLY 0x00020000L
#define CF_SCREENFONTS 0x00000001
#define CF_SCRIPTSONLY 0x00000400L
#define CF_SELECTSCRIPT 0x00400000L
#define CF_SHOWHELP 0x00000004L
#define CF_TTONLY 0x00040000L
#define CF_USESTYLE 0x00000080L
#define CF_WYSIWYG 0x00008000L
#define CFERR_MAXLESSTHANMIN 0x2002
#define CFERR_NOFONTS 0x2001
#define COLOROKSTRING COLOROKSTRINGW
#define COLOROKSTRINGA "commdlg_ColorOK"
#define COLOROKSTRINGW L"commdlg_ColorOK"
#define DN_DEFAULTPRN 1
#define FILEOKSTRING FILEOKSTRINGW
#define FILEOKSTRINGA "commdlg_FileNameOK"
#define FILEOKSTRINGW L"commdlg_FileNameOK"
#define FINDMSGSTRING FINDMSGSTRINGW
#define FINDMSGSTRINGA "commdlg_FindReplace"
#define FINDMSGSTRINGW L"commdlg_FindReplace"
#define FNERR_BUFFERTOOSMALL 0x3003
#define FNERR_INVALIDFILENAME 0x3002
#define FNERR_SUBCLASSFAILURE 0x3001
#define FR_DIALOGTERM 0x00000040
#define FR_DOWN 0x00000001
#define FR_ENABLEHOOK 0x00000100
#define FR_ENABLETEMPLATE 0x00000200
#define FR_ENABLETEMPLATEHANDLE 0x00002000
#define FR_FINDNEXT 0x00000008
#define FR_HIDEMATCHCASE 0x00008000
#define FR_HIDEUPDOWN 0x00004000
#define FR_HIDEWHOLEWORD 0x00010000
#define FR_MATCHALEFHAMZA 0x80000000
#define FR_MATCHCASE 0x00000004
#define FR_MATCHDIAC 0x20000000
#define FR_MATCHKASHIDA 0x40000000
#define FR_NOMATCHCASE 0x00000800
#define FR_NOUPDOWN 0x00000400
#define FR_NOWHOLEWORD 0x00001000
#define FR_REPLACE 0x00000010
#define FR_REPLACEALL 0x00000020
#define FR_SHOWHELP 0x00000080
#define FR_WHOLEWORD 0x00000002
#define FRERR_BUFFERLENGTHZERO 0x4001
#define HELPMSGSTRING HELPMSGSTRINGW
#define HELPMSGSTRINGA "commdlg_help"
#define HELPMSGSTRINGW L"commdlg_help"
#define ITALIC_FONTTYPE 0x0200
#define LBSELCHSTRING LBSELCHSTRINGW
#define LBSELCHSTRINGA "commdlg_LBSelChangedNotify"
#define LBSELCHSTRINGW L"commdlg_LBSelChangedNotify"
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The following members are not supported: · lCustData · lpfnHook · lpTemplateName The following flags are not supported: [corpus/mvb/windows-ce-1.0/PEGSDK/AC133B.html] */
#define OFN_ALLOWMULTISELECT 0x00000200
#define OFN_CREATEPROMPT 0x00002000
#define OFN_DONTADDTORECENT 0x02000000
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The following members are not supported: · lCustData · lpfnHook · lpTemplateName The following flags are not supported: [corpus/mvb/windows-ce-1.0/PEGSDK/AC133B.html] */
#define OFN_ENABLEHOOK 0x00000020
#define OFN_ENABLEINCLUDENOTIFY 0x00400000
#define OFN_ENABLESIZING 0x00800000
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The following members are not supported: · lCustData · lpfnHook · lpTemplateName The following flags are not supported: [corpus/mvb/windows-ce-1.0/PEGSDK/AC133B.html] */
#define OFN_ENABLETEMPLATE 0x00000040
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The following members are not supported: · lCustData · lpfnHook · lpTemplateName The following flags are not supported: [corpus/mvb/windows-ce-1.0/PEGSDK/AC133B.html] */
#define OFN_ENABLETEMPLATEHANDLE 0x00000080
#define OFN_EX_NOPLACESBAR 0x00000001
#define OFN_EXPLORER 0x00080000
#define OFN_EXTENSIONDIFFERENT 0x00000400
#define OFN_FILEMUSTEXIST 0x00001000
#define OFN_FORCESHOWHIDDEN 0x10000000
#define OFN_HIDEREADONLY 0x00000004
#define OFN_LONGNAMES 0x00200000
#define OFN_NOCHANGEDIR 0x00000008
#define OFN_NODEREFERENCELINKS 0x00100000
#define OFN_NOLONGNAMES 0x00040000
#define OFN_NONETWORKBUTTON 0x00020000
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The following members are not supported: · lCustData · lpfnHook · lpTemplateName The following flags are not supported: [corpus/mvb/windows-ce-1.0/PEGSDK/AC133B.html] */
#define OFN_NOREADONLYRETURN 0x00008000
#define OFN_NOTESTFILECREATE 0x00010000
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The following members are not supported: · lCustData · lpfnHook · lpTemplateName The following flags are not supported: [corpus/mvb/windows-ce-1.0/PEGSDK/AC133B.html] */
#define OFN_NOVALIDATE 0x00000100
#define OFN_OVERWRITEPROMPT 0x00000002
#define OFN_PATHMUSTEXIST 0x00000800
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The following members are not supported: · lCustData · lpfnHook · lpTemplateName The following flags are not supported: [corpus/mvb/windows-ce-1.0/PEGSDK/AC133B.html] */
#define OFN_READONLY 0x00000001
/* NOT SUPPORTED per mvb/windows-ce-1.0/PEGSDK: Windows CE Notes The following members are not supported: · lCustData · lpfnHook · lpTemplateName The following flags are not supported: [corpus/mvb/windows-ce-1.0/PEGSDK/AC133B.html] */
#define OFN_SHAREAWARE 0x00004000
#define OFN_SHAREFALLTHROUGH 2
#define OFN_SHARENOWARN 1
#define OFN_SHAREWARN 0
#define OFN_SHOWHELP 0x00000010
#define OPENFILENAME_SIZE_VERSION_400 76
#define PD_ALLPAGES 0x00000000
#define PD_COLLATE 0x00000010
#define PD_CURRENTPAGE 0x00400000
#define PD_DISABLEPRINTTOFILE 0x00080000
#define PD_ENABLEPRINTHOOK 0x00001000
#define PD_ENABLEPRINTTEMPLATE 0x00004000
#define PD_ENABLEPRINTTEMPLATEHANDLE 0x00010000
#define PD_ENABLESETUPHOOK 0x00002000
#define PD_ENABLESETUPTEMPLATE 0x00008000
#define PD_ENABLESETUPTEMPLATEHANDLE 0x00020000
#define PD_EXCLUSIONFLAGS 0x01000000
#define PD_FORCE_SWITCH 0x00010000
#define PD_HIDEPRINTTOFILE 0x00100000
#define PD_NOCURRENTPAGE 0x00800000
#define PD_NONETWORKBUTTON 0x00200000
#define PD_NOPAGENUMS 0x00000008
#define PD_NOSELECTION 0x00000004
#define PD_NOWARNING 0x00000080
#define PD_PAGENUMS 0x00000002
#define PD_PRINTSETUP 0x00000040
#define PD_PRINTTOFILE 0x00000020
#define PD_RESULT_APPLY 2
#define PD_RESULT_CANCEL 0
#define PD_RESULT_PRINT 1
#define PD_RETURNDC 0x00000100
#define PD_RETURNDEFAULT 0x00000400
#define PD_RETURNIC 0x00000200
#define PD_SELECTION 0x00000001
#define PD_SHOWHELP 0x00000800
#define PD_USEDEVMODECOPIES 0x00040000
#define PD_USEDEVMODECOPIESANDCOLLATE 0x00040000
#define PD_USELARGETEMPLATE 0x10000000
#define PDERR_CREATEICFAILURE 0x100A
#define PDERR_DEFAULTDIFFERENT 0x100C
#define PDERR_DNDMMISMATCH 0x1009
#define PDERR_GETDEVMODEFAIL 0x1005
#define PDERR_INITFAILURE 0x1006
#define PDERR_LOADDRVFAILURE 0x1004
#define PDERR_NODEFAULTPRN 0x1008
#define PDERR_NODEVICES 0x1007
#define PDERR_PARSEFAILURE 0x1002
#define PDERR_PRINTERNOTFOUND 0x100B
#define PDERR_RETDEFFAILURE 0x1003
#define PDERR_SETUPFAILURE 0x1001
#define PRINTER_FONTTYPE 0x4000
#define PSD_DEFAULTMINMARGINS 0x00000000
#define PSD_DISABLEMARGINS 0x00000010
#define PSD_DISABLEORIENTATION 0x00000100
#define PSD_DISABLEPAGEPAINTING 0x00080000
#define PSD_DISABLEPAPER 0x00000200
#define PSD_DISABLEPRINTER 0x00000020
#define PSD_ENABLEPAGEPAINTHOOK 0x00040000
#define PSD_ENABLEPAGESETUPHOOK 0x00002000
#define PSD_ENABLEPAGESETUPTEMPLATE 0x00008000
#define PSD_ENABLEPAGESETUPTEMPLATEHANDLE 0x00020000
#define PSD_INHUNDREDTHSOFMILLIMETERS 0x00000008
#define PSD_INTHOUSANDTHSOFINCHES 0x00000004
#define PSD_INWININIINTLMEASURE 0x00000000
#define PSD_MARGINS 0x00000002
#define PSD_MINMARGINS 0x00000001
#define PSD_NONETWORKBUTTON 0x00200000
#define PSD_NOWARNING 0x00000080
#define PSD_RETURNDEFAULT 0x00000400
#define PSD_SHOWHELP 0x00000800
#define REGULAR_FONTTYPE 0x0400
#define SCREEN_FONTTYPE 0x2000
#define SETRGBSTRING SETRGBSTRINGW
#define SETRGBSTRINGA "commdlg_SetRGBColor"
#define SETRGBSTRINGW L"commdlg_SetRGBColor"
#define SHAREVISTRING SHAREVISTRINGW
#define SHAREVISTRINGA "commdlg_ShareViolation"
#define SHAREVISTRINGW L"commdlg_ShareViolation"
#define SIMULATED_FONTTYPE 0x8000
#define START_PAGE_GENERAL 0XFFFFFFFF
#define WM_CHOOSEFONT_GETLOGFONT (WM_USER+1)
#define WM_CHOOSEFONT_SETFLAGS (WM_USER+102)
#define WM_CHOOSEFONT_SETLOGFONT (WM_USER+101)
#define WM_PSD_ENVSTAMPRECT (WM_USER+5)
#define WM_PSD_FULLPAGERECT (WM_USER+1)
#define WM_PSD_GREEKTEXTRECT (WM_USER+4)
#define WM_PSD_MARGINRECT (WM_USER+3)
#define WM_PSD_MINMARGINRECT (WM_USER+2)
#define WM_PSD_PAGESETUPDLG WM_USER
#define WM_PSD_YAFULLPAGERECT (WM_USER+6)

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DEVNAMES  [struct; shared] */
typedef struct tagDEVNAMES {
 WORD wDriverOffset; 
 WORD wDeviceOffset; 
 WORD wOutputOffset; 
 WORD wDefault; 
} DEVNAMES;
typedef DEVNAMES *PDEVNAMES, *LPDEVNAMES;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* ChooseColor  [function; ce-only; unified-kb; unified-kb] */
BOOL ChooseColor( LPCHOOSECOLOR lpcc);

/* ChooseFont  [function; ce-only; unified-kb; unified-kb] */
BOOL APIENTRY ChooseFont(  LPCHOOSEFONT lpcf  );

/* CommDlgExtendedError  [function; shared; unified-kb; unified-kb] */
DWORD CommDlgExtendedError();

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..399, 5.0..699 */

/* CCHookProc  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
UINT APIENTRY CCHookProc(
 HWND hdlg, 
 UINT uiMsg, 
 WPARAM wParam, 
 LPARAM lParam
);

/* GetOpenFileName  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Fileopen.lib, fileopen.lib; A/W GetOpenFileNameA,GetOpenFileNameW (CE is W-side)] */
BOOL GetOpenFileName( 
 LPOPENFILENAME lpofn
);

/* GetSaveFileName  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Fileopen.lib, fileopen.lib; A/W GetSaveFileNameA,GetSaveFileNameW (CE is W-side)] */
BOOL GetSaveFileName( 
 LPOPENFILENAME lpofn
);

/* PagePaintHook  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
UINT CALLBACK PagePaintHook(
 HWND hdlg, 
 UINT uiMsg, 
 WPARAM wParam, 
 LPARAM lParam
);

/* PageSetupHook  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
UINT CALLBACK PageSetupHook(
 HWND hdlg, 
 UINT uiMsg, 
 WPARAM wParam, 
 LPARAM lParam
);

/* PrintHookProc  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
UINT APIENTRY PrintHookProc(
 HWND hdlg, 
 UINT uiMsg, 
 WPARAM wParam, 
 LPARAM lParam 
);
#endif /* _WIN32_WCE */

#endif /* _COMMDLG_ */
