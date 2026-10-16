/* Mmddk.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 13 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _MMDDK_
#define _MMDDK_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* MXDM_CLOSE  [struct; ce-only] */
typedef struct {
 DWORD uDeviceId;
 UINT uMsg;
 DWORD dwUser;
 DWORD lParam1;
 DWORD lParam2;
} MXDM_CLOSE;
typedef MXDM_CLOSE *PMXDM_CLOSE, *LPMXDM_CLOSE;

/* MXDM_GETCONTROLDETAILS  [struct; ce-only] */
typedef struct {
 DWORD uDeviceId;
 UINT uMsg;
 DWORD dwUser;
 DWORD lParam1;
 DWORD lParam2;
} MXDM_GETCONTROLDETAILS;
typedef MXDM_GETCONTROLDETAILS *PMXDM_GETCONTROLDETAILS, *LPMXDM_GETCONTROLDETAILS;

/* MXDM_GETDEVCAPS  [struct; ce-only] */
typedef struct {
 DWORD uDeviceId;
 UINT uMsg;
 DWORD dwUser;
 DWORD lParam1;
 DWORD lParam2;
} MXDM_GETDEVCAPS;
typedef MXDM_GETDEVCAPS *PMXDM_GETDEVCAPS, *LPMXDM_GETDEVCAPS;

/* MXDM_GETLINECONTROLS  [struct; ce-only] */
typedef struct {
 DWORD uDeviceId;
 UINT uMsg;
 DWORD dwUser;
 DWORD lParam1;
 DWORD lParam2;
} MXDM_GETLINECONTROLS;
typedef MXDM_GETLINECONTROLS *PMXDM_GETLINECONTROLS, *LPMXDM_GETLINECONTROLS;

/* MXDM_GETLINEINFO  [struct; ce-only] */
typedef struct {
 DWORD uDeviceId;
 UINT uMsg;
 DWORD dwUser;
 DWORD lParam1;
 DWORD lParam2;
} MXDM_GETLINEINFO;
typedef MXDM_GETLINEINFO *PMXDM_GETLINEINFO, *LPMXDM_GETLINEINFO;

/* MXDM_GETNUMDEVS  [struct; ce-only] */
typedef struct {
 DWORD uDeviceId;
 UINT uMsg;
 DWORD dwUser;
 DWORD lParam1;
 DWORD lParam2;
} MXDM_GETNUMDEVS;
typedef MXDM_GETNUMDEVS *PMXDM_GETNUMDEVS, *LPMXDM_GETNUMDEVS;

/* MXDM_INIT  [struct; ce-only] */
typedef struct {
 DWORD uDeviceId;
 UINT uMsg;
 DWORD dwUser;
 DWORD lParam1;
 DWORD lParam2;
} MXDM_INIT;
typedef MXDM_INIT *PMXDM_INIT, *LPMXDM_INIT;

/* MXDM_OPEN  [struct; ce-only] */
typedef struct {
 DWORD uDeviceId;
 UINT uMsg;
 DWORD dwUser;
 DWORD lParam1;
 DWORD lParam2;
} MXDM_OPEN;
typedef MXDM_OPEN *PMXDM_OPEN, *LPMXDM_OPEN;

/* MXDM_SETCONTROLDETAILS  [struct; ce-only] */
typedef struct {
 DWORD uDeviceId;
 UINT uMsg;
 DWORD dwUser;
 DWORD lParam1;
 DWORD lParam2;
} MXDM_SETCONTROLDETAILS;
typedef MXDM_SETCONTROLDETAILS *PMXDM_SETCONTROLDETAILS, *LPMXDM_SETCONTROLDETAILS;

/* WAVEOUTEXTCAPS  [struct; ce-only] */
typedef struct tag_WAVEOUTEXTCAPS {
 DWORD dwMaxHwStreams;
 DWORD dwFreeHwStreams;
 DWORD dwSwMixerSampleRate;
 DWORD dwSwMixerBufferSize;
 DWORD dwSwMixerBufferCount;
 DWORD dwMinSampleRate;
 DWORD dwMaxSampleRate;
} WAVEOUTEXTCAPS;
typedef WAVEOUTEXTCAPS *PWAVEOUTEXTCAPS, *LPWAVEOUTEXTCAPS;

#endif /* _MMDDK_ */
