/* Cdioctl.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 7 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CDIOCTL_
#define _CDIOCTL_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CD_SENSE_DATA  [struct; ce-only] */
typedef struct _CD_SENSE_DATA {
 BYTE sd_ErrCode; 
 BYTE sd_SegNum; 
 BYTE sd_ILI_Key; 
 BYTE sd_Info[4]; 
 BYTE sd_Length; 
 BYTE sd_CmdInfo[4]; 
 BYTE sd_SenseCode; 
 BYTE sd_Qualifier; 
 BYTE sd_UnitCode; 
 BYTE sd_Key1; 
 BYTE sd_Key2; 
 BYTE sd_Key3; 
} CD_SENSE_DATA, *PCD_SENSE_DATA;

/* CDROM_PLAY_AUDIO_MSF  [struct, typedef; ce-only] */
typedef struct _CDROM_PLAY_AUDIO_MSF {
 UCHAR StartingM; 
 UCHAR StartingS; 
 UCHAR StartingF; 
 UCHAR EndingM; 
 UCHAR EndingS; 
 UCHAR EndingF; 
} CDROM_PLAY_AUDIO_MSF, *PCDROM_PLAY_AUDIO_MSF;

/* CDROM_TESTUNITREADY  [struct; ce-only] */
typedef struct CDROM_TESTUNITREADY {
 ULONG Reserved; 
 BOOL bUnitReady; 
} CDROM_TESTUNITREADY, *PCDROM_TESTUNITREADY;

/* SGX_BUF  [struct; ce-only] */
typedef struct _SGX_BUF {
 PUCHAR sb_buf; 
 DWORD sb_len; 
} SGX_BUF, *PSGX_BUF;

#endif /* _CDIOCTL_ */
