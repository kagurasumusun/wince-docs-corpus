/* Dsdriver.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 19 declarations, 0 outlines, 0 base types, 0 extra macros, 16 extra decls
 */
#ifndef _DSDRIVER_
#define _DSDRIVER_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DSDM_UNLOCK  [struct; ce-only] */
typedef struct {
 DWORD dwMsg;
 DWORD dwInstance;
 LPVOID pBuffer1;
 DWORD dwCount1;
 LPVOID pBuffer2;
 DWORD dwCount2;
} DSDM_UNLOCK;
typedef DSDM_UNLOCK *PDSDM_UNLOCK, *LPDSDM_UNLOCK;

/* DSDMP_MSG  [struct; ce-only] */
typedef struct _DSDMP_MSG {
 DWORD dwMsg;
 DWORD dwInstance;
} DSDMP_MSG;
typedef DSDMP_MSG *PDSDMP_MSG, *LPDSDMP_MSG;

/* DSDMP_DELETEBUFFER  [extra struct] */
typedef struct { DWORD dwMsg;  PDWORD dwInstance; } DSDMP_DELETEBUFFER;

/* DSDMP_DUPLICATEBUFFER  [extra struct] */
typedef struct {
  DWORD dwMsg;
  DWORD dwInstance;
  PDWORD pdwInstance;
} DSDMP_DUPLICATEBUFFER;

/* DSDMP_GETPOSITION  [extra struct] */
typedef struct {
  DWORD dwMsg;
  DWORD dwInstance;
  PDWORD pdwPlay;
  PDWORD pdwWrite;
} DSDMP_GETPOSITION;

/* DSDMP_GETSTATUS  [extra struct] */
typedef struct {
  DWORD dwMsg;
  DWORD dwInstance;
  PDWORD pdwStatus;
} DSDMP_GETSTATUS;

/* DSDMP_LOCK  [extra struct] */
typedef struct {
  DWORD dwMsg;
  DWORD dwInstance;
  DWORD dwOffset;
  DWORD dwCount;
  LPVOID* ppBuffer1;
  LPDWORD pdwCount1;
  LPVOID* ppBuffer2;
  LPDWORD pdwCount2;
  DWORD dwFlags;
} DSDMP_LOCK;

/* DSDMP_PLAY  [extra struct] */
typedef struct {
  DWORD dwMsg;
  DWORD dwInstance;
  DWORD dwFlags;
} DSDMP_PLAY;

/* DSDMP_SETFORMAT  [extra struct] */
typedef struct {
  DWORD dwMsg;
  DWORD dwInstance;
  LPWAVEFORMATEX pWFX;
} DSDMP_SETFORMAT;

/* DSDMP_SETFREQUENCY  [extra struct] */
typedef struct {
  DWORD dwMsg;
  DWORD dwInstance;
  DWORD dwFreq;
} DSDMP_SETFREQUENCY;

/* DSDMP_SETPOSITION  [extra struct] */
typedef struct {
  DWORD dwMsg;
  DWORD dwInstance;
  DWORD dwPosition;
} DSDMP_SETPOSITION;

/* DSDMP_SETVOLUMEPAN  [extra struct] */
typedef struct {
  DWORD dwMsg;
  DWORD dwInstance;
  LONG lVolume;
  LONG lPan;
} DSDMP_SETVOLUMEPAN;

/* DSDMP_STOP  [extra struct] */
typedef struct { DWORD dwMsg; DWORD dwInstance; } DSDMP_STOP;

#endif /* _DSDRIVER_ */
