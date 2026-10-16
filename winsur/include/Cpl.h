/* Cpl.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 15 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CPL_
#define _CPL_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CPL_DBLCLK 5
#define CPL_DYNAMIC_RES 0
#define CPL_EXIT 7
#define CPL_GETCOUNT 2
#define CPL_INIT 1
#define CPL_INQUIRE 3
#define CPL_NEWINQUIRE 8
#define CPL_SELECT 4
#define CPL_SETUP 200
#define CPL_STARTWPARMS CPL_STARTWPARMSW
#define CPL_STARTWPARMSA 9
#define CPL_STARTWPARMSW 10
#define CPL_STOP 6
#define WM_CPL_LAUNCH (WM_USER+1000)
#define WM_CPL_LAUNCHED (WM_USER+1001)

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CPLINFO  [struct; shared] */
typedef struct tagCPLINFO { 
 int idIcon; 
 int idName; 
 int idInfo; 
 LONG lData; 
} CPLINFO;
typedef CPLINFO *PCPLINFO, *LPCPLINFO;

/* NEWCPLINFO  [struct; shared; A/W NEWCPLINFOA,NEWCPLINFOW (CE is W-side)] */
typedef struct tagNEWCPLINFO { 
 DWORD dwSize; 
 DWORD dwFlags; 
 DWORD dwHelpContext; 
 LONG lData; 
 HICON hIcon; 
 TCHAR szName[32]; 
 TCHAR szInfo[64]; 
 TCHAR szHelpFile[128]; 
} NEWCPLINFO;
typedef NEWCPLINFO *PNEWCPLINFO, *LPNEWCPLINFO;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* CPlApplet  [function; ce-only; CE 5.0..699] */
LONG CPlApplet(
 HWND hwndCPl,
 UINT msg,
 LPARAM lParam1,
 LPARAM lParam2
);
#endif /* _WIN32_WCE */

#endif /* _CPL_ */
