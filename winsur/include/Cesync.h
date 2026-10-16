/* Cesync.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 14 constants, 14 declarations, 1 outlines, 0 base types, 0 extra macros, 35 extra decls
 */
#ifndef _CESYNC_
#define _CESYNC_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define RSF_AUTO_COMBINE 0x00000200
#define RSF_COMBINE 0x00000008
#define RSF_CONFLICT_OBJECT 0x00000001
#define RSF_DISCARDED_OBJ 0x00000080
#define RSF_DUPLICATED_OBJECT 0x00000004
#define RSF_NEW_OBJECT 0x00000002
#define RSF_NEW_VOLUME 0x00000100
#define RSF_RESERVED1 0x00100000
#define RSF_RESERVED2 0x00200000
#define RSF_RESERVED3 0x00400000
#define RSF_RESERVED4 0x00800000
#define RSF_SYNC_DESKTOP_ONLY 0x00000020
#define RSF_SYNC_DEVICE_ONLY 0x00000010
#define RSF_UPDATED_HANDLE 0x00000040

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* REPLSETUP  [struct; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DEVINFO  [struct; shared] */
typedef struct tagDevInfo {
 DWORD pid;
 char szName[MAX_PATH];
 char szType[80];
 char szPath[MAX_PATH];
} DEVINFO, *PDEVINFO;

/* HREPLFLD  [struct; ce-only] */
typedef struct _REPLFLD FAR* HREPLFLD;
typedef HREPLFLD *PHREPLFLD, *LPHREPLFLD;

/* HREPLITEM  [struct; ce-only] */
typedef struct _REPLITEM FAR* HREPLITEM;
typedef HREPLITEM *PHREPLITEM, *LPHREPLITEM;

/* HREPLOBJ  [struct; ce-only] */
typedef struct _REPLOBJ FAR* HREPLOBJ;
typedef HREPLOBJ *PHREPLOBJ, *LPHREPLOBJ;

/* OBJUIDATA  [struct; ce-only] */
typedef struct tagObjUIData {
 UINT cbStruct;
 HICON hIconLarge;
 HICON hIconSmall;
 char szName[MAX_PATH];
 char szSyncText[MAX_PATH];
 char szTypeText[80];
 char szPlTypeText[80];
} OBJUIDATA, *POBJUIDATA;

/* ReplDialogs  [enum; ce-only] */
enum ReplDialogs {
 OPTIONS_DIALOG
};

/* STOREINFO  [struct; ce-only] */
typedef struct tagStoreInfo {
 UINT cbStruct;
 UINT uFlags;
 TCHAR szProgId[ 256 ];
 TCHAR szStoreDesc[ 200 ];
 UINT uTimerRes;
 UINT cbMaxStoreId;
 UINT cbStoreId;
 LPBYTE lpbStoreId;
} STOREINFO, *PSTOREINFO;

/* OPTIONS_DIALOG  [extra enum] */
enum ReplDialogs {OPTIONS_DIALOG };

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* OnSSPDisable  [function; ce-only; CE 6.0..699] */
HRESULT
 WINAPI
 OnSSPDisable
 (
 HWND
 hwndParent
 );

/* OnSSPEnable  [function; ce-only; CE 6.0..699] */
HRESULT
 WINAPI
 OnSSPEnable
 (
 HWND
 hwndParent
 );
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HREPLOBJ BytesToObject(  LPBYTE lpb,  UINT cb);
HRESULT Clone( IEnumReplItem FAR *FAR *ppEnum);
int CompareItem( HREPLITEM hItem1, HREPLITEM hItem2);
HRESULT CompareStoreIDs( LPBYTE lpbID1, UINT cbID1, LPBYTE lpbID2, UINT cbID2);
BOOL CopyObject( HREPLOBJ hObjSrc, HREPLOBJ hObjDst);
HRESULT DeleteObj( PREPLSETUP pSetup);
HRESULT FindFirstItem( HREPLFLD hFolder, HREPLITEM *phItem, BOOL *pfExist);
HRESULT FindItemClose( HREPLFLD hFolder);
HRESULT FindNextItem( HREPLFLD hFolder, HREPLITEM *phItem, BOOL *pfExist);
void FreeObject( HREPLOBJ hObject);
HRESULT GetConflictInfo( PCONFINFO pConfInfo);
hHREPLFLD GetFolderHandle ( );
BOOL GetObjTypeInfo (POBJTYPEINFO pObjTypeInfo);
HRESULT GetObjTypeUIData( HREPLFLD hFolder, POBJUIDATA pData);
HRESULT GetPacket( LPBYTE *lppbData, DWORD *pcbData, DWORD cbRecommend);
HRESULT IsFolderChanged( HREPLFLD hFolder, BOOL *pfChanged);
BOOL IsItemChanged( HREPLFLD hFolder, HREPLITEM hItem, HREPLITEM hItemComp);
HRESULT IsValidObject( HREPLFLD hFolder, HREPLITEM hItem, UINT uFlags);
HRESULT Next( unsigned long celt, HREPLITEM *phItem, unsigned long FAR *pCeltFetched);
BOOL ObjectNotify( POBJNOTIFY pNotify);
UINT ObjectToBytes( HREPLOBJ hObject, LPBYTE lpb);
HRESULT OnItemNotify( UINT uCode, LPSTR lpszProgId, LPSTR lpszObjType, HREPLITEM hItem, ULONG ulFlags);
HRESULT OnObjectCompleted( PREPLSETUP pSetup);
void QueryDevice( UINT uCode, LPVOID *ppvData);
HRESULT RemoveDuplicates( LPSTR lpszObjType, UINT uFlags);
HRESULT ReportStatus( HREPLFLD hFolder, HREPLITEM hItem, UINT uStatus, UINT uParam);
HRESULT Reset();
HRESULT SetPacket( LPBYTE lpbData, DWORD cbData);
HRESULT SetStatusText ( LPSTR lpszText);
HRESULT Setup( PREPLSETUP pSetup);
HRESULT Skip( unsigned long celt);
void UpdateItem( HREPLFLD hFolder, HREPLITEM hItemDst, HREPLITEM hItemSrc);

#endif /* _CESYNC_ */
