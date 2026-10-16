/* Cecap.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 8 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CECAP_
#define _CECAP_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x700)) /* CE 4.2..699 */

/* CommentMarkAtProfile  [function; ce-only; CE 4.2..699; Cecap.lib, cecap.lib] */
int CommentMarkAtProfile(
 _int64 dnTimestamp,
 long lMarkID,
 char* pszText
);

/* CommentMarkProfile  [function; ce-only; CE 4.2..699; Cecap.lib, cecap.lib] */
int CommentMarkProfile(
 long lMarkID,
 char* pszText
);

/* MarkProfile  [function; ce-only; CE 4.2..699; Cecap.lib, cecap.lib] */
int MarkProfile(
 long lMarkID
);

/* NameProfile  [function; ce-only; CE 4.2..699; Cecap.lib, cecap.lib] */
int NameProfile(
 LPCSTR pszName,
 int nLevel,
 DWORD dwID
);

/* ResumeProfile  [function; ce-only; CE 4.2..699; Cecap.lib, cecap.lib] */
int ResumeProfile(
 int nLevel,
 DWORD dwID
);

/* StartProfile  [function; ce-only; CE 4.2..699; Cecap.lib, cecap.lib] */
int StartProfile(
 int nLevel,
 DWORD dwID
);

/* StopProfile  [function; ce-only; CE 4.2..699; Cecap.lib, cecap.lib] */
int StopProfile(
 int nLevel,
 DWORD dwID
);

/* SuspendProfile  [function; ce-only; CE 4.2..699; Cecap.lib, cecap.lib] */
int SuspendProfile(
 int nLevel,
 DWORD dwID
);
#endif /* _WIN32_WCE */

#endif /* _CECAP_ */
