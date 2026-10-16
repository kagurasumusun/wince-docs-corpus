/* Notifext.hxx -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 19 declarations, 0 outlines, 0 base types, 0 extra macros, 4 extra decls
 */
#ifndef _NOTIFEXT_HXX_
#define _NOTIFEXT_HXX_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* NotifyPacket  [struct; ce-only] */
struct NotifyPacket {
 NotifyPacket* pNext;
 NotifyPacket* pPrev;
 unsigned int uiPacketType;
 CEOID oidRecord;
 HICON hIcon;
 HICON hBigIcon;
 int fHasIcon;
 HWND hDlg;
 void* pExtraUIData;
 PersistentPacket* sPacket; 
};

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* PersistentPacket  [?; ce-only; CE 3.0..699] */
union PersistentPacket {
 struct {
 DWORD dwActionFlags;
 DWORD dwPacketFlags;
 FILETIME ftStart;
 FILETIME ftStop;
 union {
 unsigned int uiAppNameOffset;
 WCHAR* lpszAppName;
 };
 union {
 unsigned int uiCmdLineOffset;
 WCHAR* lpszCmdLine;
 };
 union {
 unsigned int uiDialogTitleOffset;
 WCHAR* lpszDialogTitle;
 };
 union {
 unsigned int uiDialogTextOffset;
 WCHAR* lpszDialogText;
 };
 union {
 unsigned int uiSoundOffset;
 WCHAR* lpszSound;
 };
 union {
 unsigned int uiExpansionOffset;
 void* pvExpansionData;
 };
 unsigned char header_end[1];
 };
 unsigned char packet_start[1]; 
};
#endif /* _WIN32_WCE */

/* sPacket  [extra struct] */
struct NotifyPacket {
  NotifyPacket *pNext;
  NotifyPacket *pPrev;
  unsigned int uiPacketType;
  CEOID oidRecord;
  HICON hIcon;
  HICON hBigIcon;
  int fHasIcon;
  HWND hDlg;
  void *pExtraUIData;
  PersistentPacket *sPacket; };

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* CeNotifyPrivate_ClearUserAlarm  [function; ce-only; CE 3.0..699] */
void CeNotifyPrivate_ClearUserAlarm (void);

/* CeNotifyPrivate_DeleteNotification  [function; ce-only; CE 3.0..699] */
void CeNotifyPrivate_DeleteNotification(
 CEOID oid
);

/* CeNotifyPrivate_Lock  [function; ce-only; CE 3.0..699] */
void CeNotifyPrivate_Lock (void);

/* CeNotifyPrivate_Reschedule  [function; ce-only; CE 3.0..699] */
int CeNotifyPrivate_Reschedule(
 CEOID oid,
 Int iDelaySeconds
);

/* CeNotifyPrivate_SetUserAlarm  [function; ce-only; CE 3.0..699] */
void CeNotifyPrivate_SetUserAlarm(
 FILETIME* ftWhen
);

/* CeNotifyPrivate_Unlock  [function; ce-only; CE 3.0..699] */
void CeNotifyPrivate_Unlock (void);

/* CeNotifyPublic_DisposeOfPacket  [function; ce-only; CE 3.0..699] */
void CeNotifyPublic_DisposeOfPacket(
 NotifyPacket* pPacket
);

/* CeNotifyPublic_FilterEvent  [function; ce-only; CE 3.0..699] */
int CeNotifyPublic_FilterEvent(
 DWORD dwEvent
);

/* CeNotifyPublic_Initialize  [function; ce-only; CE 3.0..699] */
int CeNotifyPublic_Initialize(void);

/* CeNotifyPublic_NewPacket  [function; ce-only; CE 3.0..699] */
void CeNotifyPublic_NewPacket(
 CEOID oidRecord
);

/* CeNotifyPublic_UIWndProc  [function; ce-only; CE 3.0..699] */
LRESULT CALLBACK CeNotifyPublic_UIWndProc(
 HWND hWnd,
 UINT message,
 WPARAM wParam,
 LPARAM lParam
);

/* CeNotifyPublic_UserAlarmSignalled  [function; ce-only; CE 3.0..699] */
void CeNotifyPublic_UserAlarmSignalled (void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* CeNotifyPublic_InitializeUI  [function; ce-only; CE 5.0..699] */
int CeNotifyPublic_InitializeUI(
 HINSTANCE hInst,
 HWND hwndUI
);

/* CeNotifyPublic_Uninitialize  [function; ce-only; CE 5.0..699] */
void CeNotifyPublic_Uninitialize(void);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void CeNotifyPrivate_FilterType ( unsigned int uiFlag );
NotifyPacket *CeNotifyPrivate_TranslateOID (  CEOID oid );
union PersistentPacket {
  struct {
    DWORD dwActionFlags;
    DWORD dwPacketFlags;
    FILETIME ftStart;
    FILETIME ftStop;
    union {
      unsigned int uiAppNameOffset;
      WCHAR *lpszAppName;
    };
    union {
      unsigned int uiCmdLineOffset;
      WCHAR *lpszCmdLine;
    };
    union {
      unsigned int uiDialogTitleOffset;
      WCHAR *lpszDialogTitle;
    };
    union {
      unsigned int uiDialogTextOffset;
      WCHAR *lpszDialogText;
    };
    union {
      unsigned int uiSoundOffset;
      WCHAR *lpszSound;
    };
    union {
      unsigned int uiExpansionOffset;
      void *pvExpansionData;
    };
    unsigned char header_end[1];
  };
  unsigned char packet_start[1]; };

#endif /* _NOTIFEXT_HXX_ */
