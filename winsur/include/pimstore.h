/* pimstore.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 116 constants, 11 declarations, 24 outlines, 0 base types, 0 extra macros, 15 extra decls
 */
#ifndef _PIMSTORE_
#define _PIMSTORE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CEVT_PIM_AUTO_I4 (102)
#define CEVT_PIM_STREAM (100)
#define olAppointmentItem 1
#define olBusy 2
#define olCityItem 102
#define olConfidential 3
#define olContactItem 2
#define olDialog 4
#define olFolderCalendar 9
#define olFolderCities 101
#define olFolderContacts 10
#define olFolderInfrared 102
#define olFolderTasks 13
#define olFree 0
#define olFriday 32
#define olHomeCity 0
#define olImportanceHigh 2
#define olImportanceLow 0
#define olImportanceNormal 1
#define olLED 1
#define olMeeting 1
#define olMeetingAccepted 3
#define olMeetingCanceled 7
#define olMonday 2
#define olNonMeeting 0
#define olNormal 0
#define olOutOfOffice 3
#define olPersonal 1
#define olPrivate 2
#define olRecursDaily 0
#define olRecursMonthly 2
#define olRecursMonthNth 3
#define olRecursOnce -1
#define olRecursWeekly 1
#define olRecursYearly 5
#define olRecursYearNth 6
#define olRepeat 16
#define olSaturday 64
#define olSound 8
#define olSunday 1
#define olTaskItem 3
#define olTentative 1
#define olThursday 16
#define olTuesday 4
#define olVibrate 2
#define olVisitingCity 1
#define olWednesday 8
#define PIMPR_ACCOUNT_NAME PROP_TAG(
#define PIMPR_ANNIVERSARY PROP_TAG(
#define PIMPR_ASSISTANT_NAME PROP_TAG(
#define PIMPR_ASSISTANT_TELEPHONE_NUMBER PROP_TAG(
#define PIMPR_BIRTHDAY PROP_TAG(
#define PIMPR_BUSINESS2_TELEPHONE_NUMBER PROP_TAG(
#define PIMPR_BUSINESS_ADDRESS PROP_TAG(
#define PIMPR_BUSINESS_ADDRESS_CITY PROP_TAG(
#define PIMPR_BUSINESS_ADDRESS_COUNTRY PROP_TAG(
#define PIMPR_BUSINESS_ADDRESS_POSTAL_CODE PROP_TAG(
#define PIMPR_BUSINESS_ADDRESS_STATE PROP_TAG(
#define PIMPR_BUSINESS_ADDRESS_STREET PROP_TAG(
#define PIMPR_BUSINESS_FAX_NUMBER PROP_TAG(
#define PIMPR_BUSINESS_TELEPHONE_NUMBER PROP_TAG(
#define PIMPR_CAR_TELEPHONE_NUMBER PROP_TAG(
#define PIMPR_CHILDREN PROP_TAG(
#define PIMPR_COMPANY_NAME PROP_TAG(
#define PIMPR_COMPANY_TELEPHONE_NUMBER PROP_TAG(
#define PIMPR_CONTACT_TYPE PROP_TAG(
#define PIMPR_CUSTOMERID PROP_TAG(
#define PIMPR_DEPARTMENT PROP_TAG(
#define PIMPR_DISPLAY_NAME PROP_TAG(
#define PIMPR_EMAIL1_ADDRESS PROP_TAG(
#define PIMPR_EMAIL2_ADDRESS PROP_TAG(
#define PIMPR_EMAIL3_ADDRESS PROP_TAG(
#define PIMPR_FILEAS PROP_TAG(
#define PIMPR_FIRST_NAME PROP_TAG(
#define PIMPR_GOVERNMENTID PROP_TAG(
#define PIMPR_HOME2_TELEPHONE_NUMBER PROP_TAG(
#define PIMPR_HOME_ADDRESS PROP_TAG(
#define PIMPR_HOME_ADDRESS_CITY PROP_TAG(
#define PIMPR_HOME_ADDRESS_COUNTRY PROP_TAG(
#define PIMPR_HOME_ADDRESS_POSTAL_CODE PROP_TAG(
#define PIMPR_HOME_ADDRESS_STATE PROP_TAG(
#define PIMPR_HOME_ADDRESS_STREET PROP_TAG(
#define PIMPR_HOME_FAX_NUMBER PROP_TAG(
#define PIMPR_HOME_TELEPHONE_NUMBER PROP_TAG(
#define PIMPR_IM1_ADDRESS PROP_TAG(
#define PIMPR_IM2_ADDRESS PROP_TAG(
#define PIMPR_IM3_ADDRESS PROP_TAG(
#define PIMPR_JOB_TITLE PROP_TAG(
#define PIMPR_LAST_NAME PROP_TAG(
#define PIMPR_MANAGER PROP_TAG(
#define PIMPR_MIDDLE_NAME PROP_TAG(
#define PIMPR_MMS PROP_TAG(
#define PIMPR_MOBILE_TELEPHONE_NUMBER PROP_TAG(
#define PIMPR_NICKNAME PROP_TAG(
#define PIMPR_OFFICE_LOCATION PROP_TAG(
#define PIMPR_OTHER_ADDRESS PROP_TAG(
#define PIMPR_OTHER_ADDRESS_CITY PROP_TAG(
#define PIMPR_OTHER_ADDRESS_COUNTRY PROP_TAG(
#define PIMPR_OTHER_ADDRESS_POSTAL_CODE PROP_TAG(
#define PIMPR_OTHER_ADDRESS_STATE PROP_TAG(
#define PIMPR_OTHER_ADDRESS_STREET PROP_TAG(
#define PIMPR_PAGER_NUMBER PROP_TAG(
#define PIMPR_PICTURE PROP_TAG(
#define PIMPR_RADIO_TELEPHONE_NUMBER PROP_TAG(
#define PIMPR_RINGTONE PROP_TAG(
#define PIMPR_SIM_PHONE PROP_TAG(
#define PIMPR_SMARTPROP PROP_TAG(
#define PIMPR_SMS PROP_TAG(
#define PIMPR_SPOUSE PROP_TAG(
#define PIMPR_SUFFIX PROP_TAG(
#define PIMPR_TITLE PROP_TAG(
#define PIMPR_WEB_PAGE PROP_TAG(
#define PIMPR_YOMI_COMPANY PROP_TAG(
#define PIMPR_YOMI_FILEAS PROP_TAG(
#define PIMPR_YOMI_FIRSTNAME PROP_TAG(
#define PIMPR_YOMI_LASTNAME PROP_TAG(

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* IAppointment::get_AllDayEvent  [function, macro; ce-only; Pimstore.lib] */

/* IAppointment::get_IsRecurring  [function, macro; ce-only; Pimstore.lib] */

/* IAppointment::get_ReminderSet  [function, macro; ce-only; Pimstore.lib] */

/* IAppointment::put_AllDayEvent  [function, macro; ce-only; Pimstore.lib] */

/* IAppointment::put_ReminderSet  [function, macro; ce-only; Pimstore.lib] */

/* ICity::get_InROM  [function, macro; ce-only; Pimstore.lib] */

/* IException::get_Deleted  [function, macro; ce-only; Pimstore.lib] */

/* IPOlRecipient::Resolve  [function, macro; ce-only; Pimstore.lib] */

/* IPOutlookApp::get_OutlookCompatible  [function, macro; ce-only; Pimstore.lib] */

/* IPOutlookItemCollection::get_IncludeRecurrences  [function, macro; ce-only; Pimstore.lib] */

/* IPOutlookItemCollection::put_IncludeRecurrences  [function, macro; ce-only; Pimstore.lib] */

/* IPOutlookItemCollection::Sort  [function, macro; ce-only; Pimstore.lib] */

/* IRecurrencePattern::get_NoEndDate  [function, macro; ce-only; Pimstore.lib] */

/* IRecurrencePattern::put_NoEndDate  [function, macro; ce-only; Pimstore.lib] */

/* ITask::get_Complete  [function, macro; ce-only; Pimstore.lib] */

/* ITask::get_IsRecurring  [function, macro; ce-only; Pimstore.lib] */

/* ITask::get_ReminderSet  [function, macro; ce-only; Pimstore.lib] */

/* ITask::get_TeamTask  [function, macro; ce-only; Pimstore.lib] */

/* ITask::put_Complete  [function, macro; ce-only; Pimstore.lib] */

/* ITask::put_ReminderSet  [function, macro; ce-only; Pimstore.lib] */

/* ITask::put_TeamTask  [function, macro; ce-only; Pimstore.lib] */

/* ITimeZone::get_IsDaylightAbsoluteDate  [function, macro; ce-only; Pimstore.lib] */

/* ITimeZone::get_IsStandardAbsoluteDate  [function, macro; ce-only; Pimstore.lib] */

/* ITimeZone::get_SupportsDST  [function, macro; ce-only; Pimstore.lib] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* OlBusyStatus  [enum; ce-only; Pimstore.lib] */
enum OlBusyStatus {
 olFree = 0,
 olTentative = 1,
 olBusy = 2,
 olOutOfOffice = 3
};

/* OlCurrentCity  [enum; ce-only; Pimstore.lib] */
enum OlCurrentCity {
 olHomeCity = 0,
 olVisitingCity = 1
};

/* OlDaysOfWeek  [enum; ce-only; Pimstore.lib] */
enum OlDaysOfWeek {
 olSunday = 1,
 olMonday = 2,
 olTuesday = 4,
 olWednesday = 8,
 olThursday = 16,
 olFriday = 32,
 olSaturday = 64
};

/* OlDefaultFolders  [enum; ce-only; Pimstore.lib] */
enum OlDefaultFolders {
 olFolderCalendar = 9,
 olFolderContacts = 10,
 olFolderTasks = 13,
 olFolderCities = 101,
 olFolderInfrared = 102
};

/* OlImportance  [enum; ce-only; Pimstore.lib] */
enum OlImportance {
 olImportanceLow = 0,
 olImportanceNormal = 1,
 olImportanceHigh = 2
};

/* OlItemType  [enum; ce-only; Pimstore.lib] */
enum OlItemType {
 olAppointmentItem = 1,
 olContactItem = 2,
 olTaskItem = 3,
 olCityItem = 102
};

/* OlMeetingStatus  [enum; ce-only; Pimstore.lib] */
enum OlMeetingStatus {
 olNonMeeting = 0,
 olMeeting = 1,
 olMeetingAccepted = 3,
 olMeetingCanceled = 7
};

/* OlRecurrenceType  [enum; ce-only; Pimstore.lib] */
enum OlRecurrenceType {
 olRecursOnce = -1,
 olRecursDaily = 0,
 olRecursWeekly = 1,
 olRecursMonthly = 2,
 olRecursMonthNth = 3,
 olRecursYearly = 5,
 olRecursYearNth = 6
};

/* OlReminderOptions  [enum; ce-only; Pimstore.lib] */
enum OlReminderOptions {
 olLED = 1,
 olVibrate = 2,
 olDialog = 4,
 olSound = 8,
 olRepeat = 16
};

/* OlSensitivity  [enum; ce-only; Pimstore.lib] */
enum OlSensitivity {
 olNormal = 0,
 olPersonal = 1,
 olPrivate = 2,
 olConfidential = 3
};

/* PIMTYPE  [extra enum] */
typedef enum tagPIMTYPE { PT_CALENDAR = 0, PT_TASKS, PT_CONTACT } PIMTYPE;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* CePimCommand  [function; ce-only; CE 3.0..399, 5.0..699; Pimstore.lib] */
void CePimCommand(
 HWND hWnd,
 PIMTYPE ptData,
 UINT uDataCount,
 HANDLE * rghData,
 void pReserved
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT Cancel();
HRESULT ClearReccurencePattern();
HRESULT ClearRecurrencePattern();
HRESULT Delete();
HRESULT Display();
HRESULT Logoff();
HRESULT Logon( long hWnd );
HRESULT Remove( int iItem );
HRESULT Save();
HRESULT Send();
HRESULT SendToInfrared();
HRESULT SkipRecurrence();

#endif /* _PIMSTORE_ */
