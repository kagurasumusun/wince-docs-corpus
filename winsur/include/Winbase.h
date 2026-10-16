/* Winbase.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 566 constants, 350 declarations, 8 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WINBASE_
#define _WINBASE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ABOVE_NORMAL_PRIORITY_CLASS 0x00008000
#define AC_LINE_BACKUP_POWER 2
#define AC_LINE_OFFLINE 0
#define AC_LINE_ONLINE 1
#define AC_LINE_UNKNOWN 255
#define ACTCTX_FLAG_APPLICATION_NAME_VALID 0x00000020
#define ACTCTX_FLAG_ASSEMBLY_DIRECTORY_VALID 0x00000004
#define ACTCTX_FLAG_HMODULE_VALID 0x00000080
#define ACTCTX_FLAG_LANGID_VALID 0x00000002
#define ACTCTX_FLAG_PROCESSOR_ARCHITECTURE_VALID 0x00000001
#define ACTCTX_FLAG_RESOURCE_NAME_VALID 0x00000008
#define ACTCTX_FLAG_SET_PROCESS_DEFAULT 0x00000010
#define BACKUP_ALTERNATE_DATA 4
#define BACKUP_DATA 1
#define BACKUP_EA_DATA 2
#define BACKUP_INVALID 0
#define BACKUP_LINK 5
#define BACKUP_OBJECT_ID 7
#define BACKUP_PROPERTY_DATA 6
#define BACKUP_REPARSE_DATA 8
#define BACKUP_SECURITY_DATA 3
#define BACKUP_SPARSE_BLOCK 9
#define BATTERY_FLAG_CHARGING 8
#define BATTERY_FLAG_CRITICAL 4
#define BATTERY_FLAG_HIGH 1
#define BATTERY_FLAG_LOW 2
#define BATTERY_FLAG_NO_BATTERY 128
#define BATTERY_FLAG_UNKNOWN 255
#define BATTERY_LIFE_UNKNOWN 0xFFFFFFFF
#define BATTERY_PERCENTAGE_UNKNOWN 255
#define BAUD_075 0x00000001
#define BAUD_110 0x00000002
#define BAUD_115200 0x00020000
#define BAUD_1200 0x00000040
#define BAUD_128K 0x00010000
#define BAUD_134_5 0x00000004
#define BAUD_14400 0x00001000
#define BAUD_150 0x00000008
#define BAUD_1800 0x00000080
#define BAUD_19200 0x00002000
#define BAUD_2400 0x00000100
#define BAUD_300 0x00000010
#define BAUD_38400 0x00004000
#define BAUD_4800 0x00000200
#define BAUD_56K 0x00008000
#define BAUD_57600 0x00040000
#define BAUD_600 0x00000020
#define BAUD_7200 0x00000400
#define BAUD_9600 0x00000800
#define BAUD_USER 0x10000000
#define BELOW_NORMAL_PRIORITY_CLASS 0x00004000
#define CALLBACK_CHUNK_FINISHED 0
#define CALLBACK_STREAM_SWITCH 1
#define CBR_110 110
#define CBR_115200 115200
#define CBR_1200 1200
#define CBR_128000 128000
#define CBR_14400 14400
#define CBR_19200 19200
#define CBR_2400 2400
#define CBR_256000 256000
#define CBR_300 300
#define CBR_38400 38400
#define CBR_4800 4800
#define CBR_56000 56000
#define CBR_57600 57600
#define CBR_600 600
#define CBR_9600 9600
#define CE_BREAK 0x0010
#define CE_DNS 2048
#define CE_FRAME 0x0008
#define CE_IOE 1024
#define CE_MODE 32768
#define CE_OOP 4096
#define CE_OVERRUN 0x0002
#define CE_PTO 512
#define CE_RXOVER 0x0001
#define CE_RXPARITY 0x0004
#define CE_TXFULL 256
#define CLRBREAK 9
#define CLRDTR 6
#define CLRRTS 4
#define CONSOLE_TEXTMODE_BUFFER 1
#define CONTROL_C_EXIT STATUS_CONTROL_C_EXIT
#define COPY_FILE_ALLOW_DECRYPTED_DESTINATION 0x00000008
#define COPY_FILE_COPY_SYMLINK 0x00000800
#define COPY_FILE_FAIL_IF_EXISTS 0x00000001
#define COPY_FILE_NO_BUFFERING 0x00001000
#define COPY_FILE_OPEN_SOURCE_FOR_WRITE 0x00000004
#define COPY_FILE_REQUEST_COMPRESSED_TRAFFIC 0x10000000
#define COPY_FILE_RESTARTABLE 0x00000002
#define CREATE_ALWAYS 2
#define CREATE_BREAKAWAY_FROM_JOB 0x01000000
#define CREATE_DEFAULT_ERROR_MODE 0x04000000
#define CREATE_FORCEDOS 0x00002000
#define CREATE_NEW 1
#define CREATE_NEW_CONSOLE 0x00000010
#define CREATE_NEW_PROCESS_GROUP 0x00000200
#define CREATE_NO_WINDOW 0x08000000
#define CREATE_SEPARATE_WOW_VDM 0x00000800
#define CREATE_SHARED_WOW_VDM 0x00001000
#define CREATE_SUSPENDED 0x00000004
#define CREATE_UNICODE_ENVIRONMENT 0x00000400
#define CREATE_WITH_USERPROFILE 0x02000000
#define DATABITS_16 0x0010
#define DATABITS_16X 0x0020
#define DATABITS_5 0x0001
#define DATABITS_6 0x0002
#define DATABITS_7 0x0004
#define DATABITS_8 0x0008
#define DDD_EXACT_MATCH_ON_REMOVE 4
#define DDD_RAW_TARGET_PATH 1
#define DDD_REMOVE_DEFINITION 2
#define DEACTIVATE_ACTCTX_FLAG_FORCE_EARLY_DEACTIVATION 0x00000001
#define DEBUG_ONLY_THIS_PROCESS 0x00000002
#define DEBUG_PROCESS 0x00000001
#define DETACHED_PROCESS 0x00000008
#define DEVICE_COUNTER_1 2
#define DEVICE_COUNTER_2 4
#define DEVICE_ID_LENGTH 20
#define DEVICE_LIST_LEN 10
#define DEVICE_STATE_CONNECTED 1
#define DEVICE_STATE_DISCONNECTED 0
#define DISABLE_MAX_PRIVILEGE 1
#define DOCKINFO_DOCKED 2
#define DOCKINFO_UNDOCKED 1
#define DOCKINFO_USER_DOCKED (DOCKINFO_USER_SUPPLIED|DOCKINFO_DOCKED)
#define DOCKINFO_USER_SUPPLIED 4
#define DOCKINFO_USER_UNDOCKED (DOCKINFO_USER_SUPPLIED|DOCKINFO_UNDOCKED)
#define DONT_RESOLVE_DLL_REFERENCES 0x00000001
#define DRIVE_CDROM 5
#define DRIVE_FIXED 3
#define DRIVE_NO_ROOT_DIR 1
#define DRIVE_RAMDISK 6
#define DRIVE_REMOTE 4
#define DRIVE_REMOVABLE 2
#define DRIVE_UNKNOWN 0
#define DTR_CONTROL_DISABLE 0x00
#define DTR_CONTROL_ENABLE 0x01
#define DTR_CONTROL_HANDSHAKE 0x02
#define DUPLICATE_CLOSE_SOURCE 0x00000001
#define DUPLICATE_SAME_ACCESS 0x00000002
#define ENUMRESLANGPROC ENUMRESLANGPROCW
#define ENUMRESNAMEPROC ENUMRESNAMEPROCW
#define ENUMRESTYPEPROC ENUMRESTYPEPROCW
#define EV_BREAK 0x0040
#define EV_CTS 0x0008
#define EV_DSR 0x0010
#define EV_ERR 0x0080
#define EV_EVENT1 0x0800
#define EV_EVENT2 0x1000
#define EV_PERR 0x0200
#define EV_RING 0x0100
#define EV_RLSD 0x0020
#define EV_RX80FULL 0x0400
#define EV_RXCHAR 0x0001
#define EV_RXFLAG 0x0002
#define EV_TXEMPTY 0x0004
#define EVENPARITY 2
#define EVENT_ALL_ACCESS 0x1f0003
#define EVENT_MODIFY_STATE 2
#define EVENTLOG_AUDIT_FAILURE 16
#define EVENTLOG_AUDIT_SUCCESS 8
#define EVENTLOG_BACKWARDS_READ 8
#define EVENTLOG_ERROR_TYPE 1
#define EVENTLOG_FORWARDS_READ 4
#define EVENTLOG_INFORMATION_TYPE 4
#define EVENTLOG_SEEK_READ 2
#define EVENTLOG_SEQUENTIAL_READ 1
#define EVENTLOG_SUCCESS 0
#define EVENTLOG_WARNING_TYPE 2
#define EXCEPTION_ACCESS_VIOLATION STATUS_ACCESS_VIOLATION
#define EXCEPTION_ARRAY_BOUNDS_EXCEEDED STATUS_ARRAY_BOUNDS_EXCEEDED
#define EXCEPTION_BREAKPOINT STATUS_BREAKPOINT
#define EXCEPTION_DATATYPE_MISALIGNMENT STATUS_DATATYPE_MISALIGNMENT
#define EXCEPTION_FLT_DENORMAL_OPERAND STATUS_FLOAT_DENORMAL_OPERAND
#define EXCEPTION_FLT_DIVIDE_BY_ZERO STATUS_FLOAT_DIVIDE_BY_ZERO
#define EXCEPTION_FLT_INEXACT_RESULT STATUS_FLOAT_INEXACT_RESULT
#define EXCEPTION_FLT_INVALID_OPERATION STATUS_FLOAT_INVALID_OPERATION
#define EXCEPTION_FLT_OVERFLOW STATUS_FLOAT_OVERFLOW
#define EXCEPTION_FLT_STACK_CHECK STATUS_FLOAT_STACK_CHECK
#define EXCEPTION_FLT_UNDERFLOW STATUS_FLOAT_UNDERFLOW
#define EXCEPTION_GUARD_PAGE STATUS_GUARD_PAGE_VIOLATION
#define EXCEPTION_ILLEGAL_INSTRUCTION STATUS_ILLEGAL_INSTRUCTION
#define EXCEPTION_IN_PAGE_ERROR STATUS_IN_PAGE_ERROR
#define EXCEPTION_INT_DIVIDE_BY_ZERO STATUS_INTEGER_DIVIDE_BY_ZERO
#define EXCEPTION_INT_OVERFLOW STATUS_INTEGER_OVERFLOW
#define EXCEPTION_INVALID_DISPOSITION STATUS_INVALID_DISPOSITION
#define EXCEPTION_INVALID_HANDLE STATUS_INVALID_HANDLE
#define EXCEPTION_NONCONTINUABLE_EXCEPTION STATUS_NONCONTINUABLE_EXCEPTION
#define EXCEPTION_PRIV_INSTRUCTION STATUS_PRIVILEGED_INSTRUCTION
#define EXCEPTION_SINGLE_STEP STATUS_SINGLE_STEP
#define EXCEPTION_STACK_OVERFLOW STATUS_STACK_OVERFLOW
#define FILE_ATTRIBUTE_COMPRESSED 0x800
#define FILE_ATTRIBUTE_DEVICE 0x40
#define FILE_ATTRIBUTE_DIRECTORY 0x10
#define FILE_ATTRIBUTE_ENCRYPTED 0x4000
#define FILE_ATTRIBUTE_REPARSE_POINT 0x400
#define FILE_ATTRIBUTE_SPARSE_FILE 0x200
#define FILE_BEGIN 0
#define FILE_CURRENT 1
#define FILE_END 2
#define FILE_FLAG_BACKUP_SEMANTICS 0x02000000
#define FILE_FLAG_DELETE_ON_CLOSE 0x04000000
#define FILE_FLAG_FIRST_PIPE_INSTANCE 524288
#define FILE_FLAG_NO_BUFFERING 0x20000000
#define FILE_FLAG_OPEN_NO_RECALL 0x00100000
#define FILE_FLAG_OPEN_REPARSE_POINT 0x00200000
#define FILE_FLAG_OVERLAPPED 0x40000000
#define FILE_FLAG_POSIX_SEMANTICS 0x01000000
#define FILE_FLAG_RANDOM_ACCESS 0x10000000
#define FILE_FLAG_SEQUENTIAL_SCAN 0x08000000
#define FILE_FLAG_SESSION_AWARE 0x00800000
#define FILE_FLAG_WRITE_THROUGH 0x80000000
#define FILE_MAP_ALL_ACCESS 0xf001f
#define FILE_MAP_COPY 1
#define FILE_MAP_READ 4
#define FILE_MAP_WRITE 2
#define FILE_NAME_NORMALIZED 0x0
#define FILE_NAME_OPENED 0x8
#define FILE_SHARE_DELETE 0x00000004
#define FILE_SHARE_READ 0x00000001
#define FILE_SHARE_WRITE 0x00000002
#define FILE_TYPE_CHAR 2
#define FILE_TYPE_DISK 1
#define FILE_TYPE_PIPE 3
#define FILE_TYPE_REMOTE 0x8000
#define FILE_TYPE_UNKNOWN 0
#define FIND_ACTCTX_SECTION_KEY_RETURN_HACTCTX 0x00000001
#define FORMAT_MESSAGE_ALLOCATE_BUFFER 0x00000100
#define FORMAT_MESSAGE_ARGUMENT_ARRAY 0x00002000
#define FORMAT_MESSAGE_FROM_HMODULE 0x00000800
#define FORMAT_MESSAGE_FROM_STRING 0x00000400
#define FORMAT_MESSAGE_FROM_SYSTEM 0x00001000
#define FORMAT_MESSAGE_IGNORE_INSERTS 0x00000200
#define FORMAT_MESSAGE_MAX_WIDTH_MASK 0x000000FF
#define FS_CASE_IS_PRESERVED 2
#define FS_CASE_SENSITIVE 1
#define FS_FILE_COMPRESSION 16
#define FS_PERSISTENT_ACLS 8
#define FS_UNICODE_STORED_ON_DISK 4
#define FS_VOL_IS_COMPRESSED 32768
#define GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS 0x00000004
#define GET_MODULE_HANDLE_EX_FLAG_PIN 0x00000001
#define GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT 0x00000002
#define GET_TAPE_DRIVE_INFORMATION 1
#define GET_TAPE_MEDIA_INFORMATION 0
#define GHND 66
#define GMEM_DDESHARE 8192
#define GMEM_DISCARDABLE 256
#define GMEM_DISCARDED 16384
#define GMEM_FIXED 0
#define GMEM_INVALID_HANDLE 32768
#define GMEM_LOCKCOUNT 255
#define GMEM_LOWER 4096
#define GMEM_MODIFY 128
#define GMEM_MOVEABLE 2
#define GMEM_NOCOMPACT 16
#define GMEM_NODISCARD 32
#define GMEM_NOT_BANKED 4096
#define GMEM_NOTIFY 16384
#define GMEM_SHARE 8192
#define GMEM_VALID_FLAGS 32626
#define GMEM_ZEROINIT 64
#define GPTR 64
#define HANDLE_FLAG_INHERIT 0x01
#define HANDLE_FLAG_PROTECT_FROM_CLOSE 0x02
#define HFILE_ERROR ((HFILE)-1)
#define HIGH_PRIORITY_CLASS 0x00000080
#define HINSTANCE_ERROR 32
#define HW_PROFILE_GUIDLEN 39
#define IDLE_PRIORITY_CLASS 0x00000040
#define IGNORE 0
#define INFINITE 0xFFFFFFFF
#define INVALID_ATOM ((ATOM)0)
#define INVALID_FILE_SIZE 0xFFFFFFFF
#define INVALID_HANDLE_VALUE 0xFFFFFFFF
#define INVALID_SET_FILE_POINTER ((DWORD)-1)
#define JobObjectAssociateCompletionPortInformation 7
#define JobObjectBasicLimitInformation 2
#define JobObjectBasicUIRestrictions 4
#define JobObjectEndOfJobTimeInformation 6
#define JobObjectExtendedLimitInformation 9
#define JobObjectSecurityLimitInformation 5
#define LHND 0x0042
#define LMEM_DISCARDABLE 3840
#define LMEM_DISCARDED 16384
#define LMEM_FIXED 0x0000
#define LMEM_INVALID_HANDLE 32768
#define LMEM_LOCKCOUNT 255
#define LMEM_MODIFY 128
#define LMEM_MOVEABLE 0x0002
#define LMEM_NOCOMPACT 16
#define LMEM_NODISCARD 32
#define LMEM_NONZEROLHND 2
#define LMEM_NONZEROLPTR 0
#define LMEM_ZEROINIT 0x0040
#define LOAD_LIBRARY_AS_DATAFILE 0x00000002
#define LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE 0x00000040
#define LOAD_WITH_ALTERED_SEARCH_PATH 0x00000008
#define LOGON32_LOGON_BATCH 4
#define LOGON32_LOGON_INTERACTIVE 2
#define LOGON32_LOGON_NETWORK 3
#define LOGON32_LOGON_NETWORK_CLEARTEXT 8
#define LOGON32_LOGON_NEW_CREDENTIALS 9
#define LOGON32_LOGON_SERVICE 5
#define LOGON32_LOGON_UNLOCK 7
#define LOGON32_PROVIDER_DEFAULT 0
#define LOGON32_PROVIDER_WINNT35 1
#define LOGON32_PROVIDER_WINNT40 2
#define LOGON32_PROVIDER_WINNT50 3
#define LOGON_NETCREDENTIALS_ONLY 0x00000002
#define LOGON_WITH_PROFILE 0x00000001
#define LPTR 0x0040
#define LUA_TOKEN 4
#define MARKPARITY 3
#define MAX_COMPUTERNAME_LENGTH 15
#define MAX_PROFILE_LEN 80
#define MAXIMUM_SUSPEND_COUNT 0x7F
#define MAXIMUM_WAIT_OBJECTS 64
#define MAXINTATOM 0xC000
#define MOVEFILE_COPY_ALLOWED 2
#define MOVEFILE_DELAY_UNTIL_REBOOT 4
#define MOVEFILE_REPLACE_EXISTING 1
#define MOVEFILE_WRITE_THROUGH 8
#define MS_CTS_ON 0x0010
#define MS_DSR_ON 0x0020
#define MS_RING_ON 0x0040
#define MS_RLSD_ON 0x0080
#define MUTEX_ALL_ACCESS 0x1f0001
#define MUTEX_MODIFY_STATE 1
#define NMPWAIT_NOWAIT 1
#define NMPWAIT_USE_DEFAULT_WAIT 0
#define NMPWAIT_WAIT_FOREVER ((DWORD)-1)
#define NONZEROLHND 2
#define NONZEROLPTR 0
#define NOPARITY 0
#define NORMAL_PRIORITY_CLASS 0x00000020
#define ODDPARITY 1
#define OF_CANCEL 2048
#define OF_CREATE 4096
#define OF_DELETE 512
#define OF_EXIST 16384
#define OF_PARSE 256
#define OF_PROMPT 8192
#define OF_READ 0
#define OF_READWRITE 2
#define OF_REOPEN 32768
#define OF_SHARE_COMPAT 0
#define OF_SHARE_DENY_NONE 64
#define OF_SHARE_DENY_READ 48
#define OF_SHARE_DENY_WRITE 32
#define OF_SHARE_EXCLUSIVE 16
#define OF_VERIFY 1024
#define OF_WRITE 1
#define OFS_MAXPATHNAME 128
#define ONE5STOPBITS 1
#define ONESTOPBIT 0
#define OPEN_ALWAYS 4
#define OPEN_EXISTING 3
#define PARITY_EVEN 0x0400
#define PARITY_MARK 0x0800
#define PARITY_NONE 0x0100
#define PARITY_ODD 0x0200
#define PARITY_SPACE 0x1000
#define PCF_16BITMODE 0x0200
#define PCF_DTRDSR 0x0001
#define PCF_INTTIMEOUTS 0x0080
#define PCF_PARITY_CHECK 0x0008
#define PCF_RLSD 0x0004
#define PCF_RTSCTS 0x0002
#define PCF_SETXCHAR 0x0020
#define PCF_SPECIALCHARS 0x0100
#define PCF_TOTALTIMEOUTS 0x0040
#define PCF_XONXOFF 0x0010
#define PIPE_ACCESS_DUPLEX 3
#define PIPE_ACCESS_INBOUND 1
#define PIPE_ACCESS_OUTBOUND 2
#define PIPE_CLIENT_END 0
#define PIPE_NOWAIT 1
#define PIPE_READMODE_BYTE 0
#define PIPE_READMODE_MESSAGE 2
#define PIPE_SERVER_END 1
#define PIPE_TYPE_BYTE 0
#define PIPE_TYPE_MESSAGE 4
#define PIPE_UNLIMITED_INSTANCES 255
#define PIPE_WAIT 0
#define PROCESS_DEP_DISABLE_ATL_THUNK_EMULATION 2
#define PROCESS_DEP_ENABLE 1
#define PROCESS_HEAP_ENTRY_BUSY 4
#define PROCESS_HEAP_ENTRY_DDESHARE 32
#define PROCESS_HEAP_ENTRY_MOVEABLE 16
#define PROCESS_HEAP_REGION 1
#define PROCESS_HEAP_UNCOMMITTED_RANGE 2
#define PROFILE_KERNEL 0x20000000
#define PROFILE_SERVER 0x40000000
#define PROFILE_USER 0x10000000
#define PROGRESS_CANCEL 1
#define PROGRESS_CONTINUE 0
#define PROGRESS_QUIET 3
#define PROGRESS_STOP 2
#define PST_FAX 0x00000021
#define PST_LAT 0x00000101
#define PST_MODEM 0x00000006
#define PST_NETWORK_BRIDGE 0x00000100
#define PST_PARALLELPORT 0x00000002
#define PST_RS232 0x00000001
#define PST_RS422 0x00000003
#define PST_RS423 0x00000004
#define PST_RS449 0x00000005
#define PST_SCANNER 0x00000022
#define PST_TCPIP_TELNET 0x00000102
#define PST_UNSPECIFIED 0x00000000
#define PST_X25 0x00000103
#define PURGE_RXABORT 0x0002
#define PURGE_RXCLEAR 0x0008
#define PURGE_TXABORT 0x0001
#define PURGE_TXCLEAR 0x0004
#define QUERY_ACTCTX_FLAG_ACTCTX_IS_ADDRESS 0x00000010
#define QUERY_ACTCTX_FLAG_ACTCTX_IS_HMODULE 0x00000008
#define QUERY_ACTCTX_FLAG_USE_ACTIVE_ACTCTX 0x00000004
#define REALTIME_PRIORITY_CLASS 0x00000100
#define REPLACEFILE_IGNORE_MERGE_ERRORS 0x00000002
#define REPLACEFILE_WRITE_THROUGH 0x00000001
#define RESMGR_BASE_OEM 0x00080000
#define RESMGR_IOSPACE 0x00002
#define RESMGR_IRQ 0x00001
#define RESMGR_MAX_OEM 0x000FFFFF
#define RTS_CONTROL_DISABLE 0x00
#define RTS_CONTROL_ENABLE 0x01
#define RTS_CONTROL_HANDSHAKE 0x02
#define RTS_CONTROL_TOGGLE 0x03
#define SANDBOX_INERT 2
#define SCS_32BIT_BINARY 0
#define SCS_64BIT_BINARY 6
#define SCS_DOS_BINARY 1
#define SCS_OS216_BINARY 5
#define SCS_PIF_BINARY 3
#define SCS_POSIX_BINARY 4
#define SCS_WOW_BINARY 2
#define SECURITY_ANONYMOUS (SecurityAnonymous<<16)
#define SECURITY_CONTEXT_TRACKING 0x40000
#define SECURITY_DELEGATION (SecurityDelegation<<16)
#define SECURITY_EFFECTIVE_ONLY 0x80000
#define SECURITY_IDENTIFICATION (SecurityIdentification<<16)
#define SECURITY_IMPERSONATION (SecurityImpersonation<<16)
#define SECURITY_SQOS_PRESENT 0x100000
#define SECURITY_VALID_SQOS_FLAGS 0x1F0000
#define SEM_FAILCRITICALERRORS 0x0001
#define SEM_NOALIGNMENTFAULTEXCEPT 0x0004
#define SEM_NOGPFAULTERRORBOX 0x0002
#define SEM_NOOPENFILEERRORBOX 0x8000
#define SEMAPHORE_ALL_ACCESS 0x1f0003
#define SEMAPHORE_MODIFY_STATE 2
#define SERIAL_LSR_FE 0x08
#define SET_TAPE_DRIVE_INFORMATION 1
#define SET_TAPE_MEDIA_INFORMATION 0
#define SETBREAK 8
#define SETDTR 5
#define SETRTS 3
#define SETXOFF 1
#define SETXON 2
#define SHUTDOWN_NORETRY 1
#define SLE_ERROR 1
#define SLE_MINORERROR 2
#define SLE_WARNING 3
#define SP_BAUD 0x0002
#define SP_DATABITS 0x0004
#define SP_HANDSHAKING 0x0010
#define SP_PARITY 0x0001
#define SP_PARITY_CHECK 0x0020
#define SP_RLSD 0x0040
#define SP_SERIALCOMM 1
#define SP_STOPBITS 0x0008
#define SPACEPARITY 4
#define STARTF_FORCEOFFFEEDBACK 0x00000080
#define STARTF_FORCEONFEEDBACK 0x00000040
#define STARTF_PREVENTPINNING 0x00002000
#define STARTF_RUNFULLSCREEN 0x00000020
#define STARTF_TITLEISAPPID 0x00001000
#define STARTF_TITLEISLINKNAME 0x00000800
#define STARTF_UNTRUSTEDSOURCE 0x00008000
#define STARTF_USECOUNTCHARS 0x00000008
#define STARTF_USEFILLATTRIBUTE 0x00000010
#define STARTF_USEHOTKEY 0x00000200
#define STARTF_USEPOSITION 0x00000004
#define STARTF_USESHOWWINDOW 0x00000001
#define STARTF_USESIZE 0x00000002
#define STARTF_USESTDHANDLES 0x00000100
#define STATUS_ABANDONED_WAIT_0 0x80
#define STATUS_ACCESS_VIOLATION 0xC0000005
#define STATUS_ARRAY_BOUNDS_EXCEEDED 0xC000008C
#define STATUS_BREAKPOINT 0x80000003
#define STATUS_CONTROL_C_EXIT 0xC000013A
#define STATUS_DATATYPE_MISALIGNMENT 0x80000002
#define STATUS_DLL_INIT_FAILED 0xC0000142
#define STATUS_DLL_INIT_FAILED_LOGOFF 0xC000026B
#define STATUS_FLOAT_DENORMAL_OPERAND 0xC000008D
#define STATUS_FLOAT_DIVIDE_BY_ZERO 0xC000008E
#define STATUS_FLOAT_INEXACT_RESULT 0xC000008F
#define STATUS_FLOAT_INVALID_OPERATION 0xC0000090
#define STATUS_FLOAT_OVERFLOW 0xC0000091
#define STATUS_FLOAT_STACK_CHECK 0xC0000092
#define STATUS_FLOAT_UNDERFLOW 0xC0000093
#define STATUS_GUARD_PAGE_VIOLATION 0x80000001
#define STATUS_ILLEGAL_INSTRUCTION 0xC000001D
#define STATUS_IN_PAGE_ERROR 0xC0000006
#define STATUS_INTEGER_DIVIDE_BY_ZERO 0xC0000094
#define STATUS_INTEGER_OVERFLOW 0xC0000095
#define STATUS_INVALID_DISPOSITION 0xC0000026
#define STATUS_INVALID_HANDLE 0xC0000008L
#define STATUS_NO_MEMORY 0xC0000017
#define STATUS_NONCONTINUABLE_EXCEPTION 0xC0000025
#define STATUS_PENDING 0x103
#define STATUS_PRIVILEGED_INSTRUCTION 0xC0000096
#define STATUS_SEGMENT_NOTIFICATION 0x40000005
#define STATUS_SINGLE_STEP 0x80000004
#define STATUS_STACK_OVERFLOW 0xC00000FD
#define STATUS_TIMEOUT 0x102
#define STATUS_USER_APC 0xC0
#define STATUS_WAIT_0 0
#define STD_ERROR_HANDLE (DWORD)(0xfffffff4)
#define STD_INPUT_HANDLE (DWORD)(0xfffffff6)
#define STD_OUTPUT_HANDLE (DWORD)(0xfffffff5)
#define STILL_ACTIVE 0x103
#define STOPBITS_10 0x0001
#define STOPBITS_15 0x0002
#define STOPBITS_20 0x0004
#define STREAM_CONTAINS_PROPERTIES 4
#define STREAM_CONTAINS_SECURITY 2
#define STREAM_MODIFIED_WHEN_READ 1
#define STREAM_NORMAL_ATTRIBUTE 0
#define SYMBOLIC_LINK_FLAG_DIRECTORY 0x1
#define TC_GP_TRAP 2
#define TC_HARDERR 1
#define TC_NORMAL 0
#define TC_SIGNAL 3
#define THREAD_PRIORITY_ABOVE_IDLE 6
#define THREAD_PRIORITY_ABOVE_NORMAL 1
#define THREAD_PRIORITY_BELOW_NORMAL -1
#define THREAD_PRIORITY_ERROR_RETURN 2147483647
#define THREAD_PRIORITY_HIGHEST 2
#define THREAD_PRIORITY_IDLE -15
#define THREAD_PRIORITY_LOWEST -2
#define THREAD_PRIORITY_NORMAL 0
#define THREAD_PRIORITY_TIME_CRITICAL 15
#define TIME_ZONE_ID_INVALID 0xFFFFFFFF
#define TLS_OUT_OF_INDEXES 0xFFFFFFFF
#define TRUNCATE_EXISTING 5
#define TWOSTOPBITS 2
#define VER_PLATFORM_WIN32s 0
#define VOLUME_NAME_DOS 0x0
#define VOLUME_NAME_GUID 0x1
#define VOLUME_NAME_NONE 0x4
#define VOLUME_NAME_NT 0x2
#define WAIT_ABANDONED 0x00000080L
#define WAIT_ABANDONED_0 128
#define WAIT_FAILED ((DWORD)0xFFFFFFFF)
#define WAIT_IO_COMPLETION 0x000000C0L
#define WAIT_OBJECT_0 0x00000000L
#define WAIT_TIMEOUT 258
#define WINADVAPI DECLSPEC_IMPORT
#define WINBASEAPI DECLSPEC_IMPORT
#define WRITE_RESTRICTED 8
#define WRITE_WATCH_FLAG_RESET 1
#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..599 */
#define UNICODE compile
#endif /* _WIN32_WCE */

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* CHECK_INVALIDGUID  [macro, function; ce-only] */
#define CHECK_INVALIDGUID(pguid) \
!~((pguid)->Data1&(pguid)->Data2&(pguid)->Data3&(pguid)->Data4);

/* CHECK_SYSTEMGUID  [macro, function; ce-only; Fsdbase.lib] */
#define CHECK_SYSTEMGUID(pguid) \
!((pguid)->Data1|(pguid)->Data2|(pguid)->Data3|(pguid)->Data4);

/* CONTEXT  [struct; shared] */

/* STORE_INFORMATION  [struct; ce-only] */

/* SYSTEM_POWER_STATUS_EX  [struct; ce-only] */

/* TypeFromPropID  [macro; ce-only; Fsdbase.lib] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CEDIRINFO  [struct; ce-only] */
typedef struct _CEDIRINFO {
 DWORD dwAttributes; 
 CEOID oidParent; 
 WCHAR szDirName[MAX_PATH]; 
} CEDIRINFO;
typedef CEDIRINFO *PCEDIRINFO, *LPCEDIRINFO;

/* CERECORDINFO  [struct; ce-only] */
typedef struct _CERECORDINFO {
 CEOID oidParent; 
} CERECORDINFO;
typedef CERECORDINFO *PCERECORDINFO, *LPCERECORDINFO;

/* COMMPROP  [struct; shared] */
typedef struct _COMMPROP {
 WORD wPacketLength;
 WORD wPacketVersion;
 DWORD dwServiceMask;
 DWORD dwReserved1;
 DWORD dwMaxTxQueue;
 DWORD dwMaxRxQueue;
 DWORD dwMaxBaud;
 DWORD dwProvSubType;
 DWORD dwProvCapabilities;
 DWORD dwSettableParams;
 DWORD dwSettableBaud;
 WORD wSettableData;
 WORD wSettableStopParity;
 WORD dwCurrentTxQueue;
 DWORD dwCurrentRxQueue;
 DWORD dwProvSpec1;
 DWORD dwProvSpec2;
 WCHAR wcProvChar[1];
} COMMPROP;
typedef COMMPROP *PCOMMPROP, *LPCOMMPROP;

/* COMMTIMEOUTS  [struct; shared] */
typedef struct _COMMTIMEOUTS {
 DWORD ReadIntervalTimeout;
 DWORD ReadTotalTimeoutMultiplier;
 DWORD ReadTotalTimeoutConstant;
 DWORD WriteTotalTimeoutMultiplier;
 DWORD WriteTotalTimeoutConstant;
} COMMTIMEOUTS,*LPCOMMTIMEOUTS;

/* COMSTAT  [struct; shared] */
typedef struct _COMSTAT {
 DWORD fCtsHold :1;
 DWORD fDsrHold :1;
 DWORD fRlsdHold :1;
 DWORD fXoffHold :1;
 DWORD fXoffSent :1;
 DWORD fEof :1;
 DWORD fTxim :1;
 DWORD fReserved :25;
 DWORD cbInQue;
 DWORD cbOutQue;
} COMSTAT, *LPCOMSTAT;

/* CREATE_PROCESS_DEBUG_INFO  [struct; shared] */
typedef struct _CREATE_PROCESS_DEBUG_INFO { 
 HANDLE hFile; 
 HANDLE hProcess; 
 HANDLE hThread; 
 LPVOID lpBaseOfImage; 
 DWORD dwDebugInfoFileOffset; 
 DWORD nDebugInfoSize; 
 LPVOID lpThreadLocalBase; 
 LPTHREAD_START_ROUTINE lpStartAddress;
 LPVOID lpImageName; 
 WORD fUnicode; 
} CREATE_PROCESS_DEBUG_INFO;
typedef CREATE_PROCESS_DEBUG_INFO *PCREATE_PROCESS_DEBUG_INFO, *LPCREATE_PROCESS_DEBUG_INFO;

/* CREATE_THREAD_DEBUG_INFO  [struct; shared] */
typedef struct _CREATE_THREAD_DEBUG_INFO { 
 HANDLE hThread; 
 LPVOID lpThreadLocalBase; 
 LPTHREAD_START_ROUTINE lpStartAddress; 
} CREATE_THREAD_DEBUG_INFO;
typedef CREATE_THREAD_DEBUG_INFO *PCREATE_THREAD_DEBUG_INFO, *LPCREATE_THREAD_DEBUG_INFO;

/* DCB  [struct; ce-only; harvest-kb; harvest-kb] */
typedef struct _DCB {
 DWORD DCBlength;
 DWORD BaudRate; 
 DWORD fBinary:1;
 DWORD fParity:1;
 DWORD fOutxCtsFlow:1;
 DWORD fOutxDsrFlow:1;
 DWORD fDtrControl:2;
 DWORD fDsrSensitivity:1;
 DWORD fTXContinueOnXoff:1;
 DWORD fOutX: 1;
 DWORD fInX: 1;
 DWORD fErrorChar:1;
 DWORD fNull:1; 
 DWORD fRtsControl:2; 
 DWORD fAbortOnError:1;
 DWORD fDummy2:17;
 WORD wReserved;
 WORD XonLim; 
 WORD XoffLim; 
 BYTE ByteSize; 
 BYTE Parity; 
 BYTE StopBits;
 char XonChar; 
 char XoffChar; 
 char ErrorChar;
 char EofChar; 
 char EvtChar; 
 WORD wReserved1; 
} DCB;
typedef DCB *PDCB, *LPDCB;

/* DeviceSearchType  [enum; ce-only] */
typedef enum {
 DeviceSearchByLegacyName, 
 DeviceSearchByDeviceName, 
 DeviceSearchByBusName, 
 DeviceSearchByGuid, 
 DeviceSearchByParent 
} DeviceSearchType;
typedef DeviceSearchType *PDeviceSearchType, *LPDeviceSearchType;

/* DEVMGR_DEVICE_INFORMATION  [struct; ce-only] */
typedef struct _DevmgrDeviceInformation_tag {
 DWORD dwSize;
 HANDLE hDevice;
 HANDLE hParentDevice;
 WCHAR szLegacyName[6];
 WCHAR szDeviceKey[MAX_PATH];
 WCHAR szDeviceName[MAX_PATH];
 WCHAR szBusName[MAX_PATH];
} DEVMGR_DEVICE_INFORMATION, *PDEVMGR_DEVICE_INFORMATION;

/* EXIT_PROCESS_DEBUG_INFO  [struct; shared] */
typedef struct _EXIT_PROCESS_DEBUG_INFO { 
 DWORD dwExitCode; 
} EXIT_PROCESS_DEBUG_INFO;
typedef EXIT_PROCESS_DEBUG_INFO *PEXIT_PROCESS_DEBUG_INFO, *LPEXIT_PROCESS_DEBUG_INFO;

/* EXIT_THREAD_DEBUG_INFO  [struct; shared] */
typedef struct _EXIT_THREAD_DEBUG_INFO { 
 DWORD dwExitCode; 
} EXIT_THREAD_DEBUG_INFO;
typedef EXIT_THREAD_DEBUG_INFO *PEXIT_THREAD_DEBUG_INFO, *LPEXIT_THREAD_DEBUG_INFO;

/* FINDEX_INFO_LEVELS  [enum; shared] */
typedef enum _FINDEX_INFO_LEVELS {
 FindExInfoStandard,
 FindExInfoMaxInfoLevel
} FINDEX_INFO_LEVELS;
typedef FINDEX_INFO_LEVELS *PFINDEX_INFO_LEVELS, *LPFINDEX_INFO_LEVELS;

/* FINDEX_SEARCH_OPS  [enum; shared] */
typedef enum _FINDEX_SEARCH_OPS { 
 FindExSearchNameMatch, 
 FindExSearchLimitToDirectories, 
 FindExSearchLimitToDevices 
} FINDEX_SEARCH_OPS;
typedef FINDEX_SEARCH_OPS *PFINDEX_SEARCH_OPS, *LPFINDEX_SEARCH_OPS;

/* GET_FILEEX_INFO_LEVELS  [enum; shared] */
typedef enum _GET_FILEEX_INFO_LEVELS { 
 GetFileExInfoStandard 
} GET_FILEEX_INFO_LEVELS;
typedef GET_FILEEX_INFO_LEVELS *PGET_FILEEX_INFO_LEVELS, *LPGET_FILEEX_INFO_LEVELS;

/* LOAD_DLL_DEBUG_INFO  [struct; shared] */
typedef struct _LOAD_DLL_DEBUG_INFO { 
 HANDLE hFile; 
 LPVOID lpBaseOfDll; 
 DWORD dwDebugInfoFileOffset; 
 DWORD nDebugInfoSize; 
 LPVOID lpImageName; 
 WORD fUnicode; 
} LOAD_DLL_DEBUG_INFO;
typedef LOAD_DLL_DEBUG_INFO *PLOAD_DLL_DEBUG_INFO, *LPLOAD_DLL_DEBUG_INFO;

/* MEMORYSTATUS  [struct; shared] */
typedef struct _MEMORYSTATUS {
 DWORD dwLength;
 DWORD dwMemoryLoad;
 DWORD dwTotalPhys;
 DWORD dwAvailPhys;
 DWORD dwTotalPageFile;
 DWORD dwAvailPageFile;
 DWORD dwTotalVirtual;
 DWORD dwAvailVirtual;
} MEMORYSTATUS, *LPMEMORYSTATUS;

/* OSVERSIONINFO  [struct; shared; A/W OSVERSIONINFOA,OSVERSIONINFOW (CE is W-side)] */
typedef struct _OSVERSIONINFO{
 DWORD dwOSVersionInfoSize;
 DWORD dwMajorVersion;
 DWORD dwMinorVersion;
 DWORD dwBuildNumber;
 DWORD dwPlatformId;
 TCHAR szCSDVersion[128];
} OSVERSIONINFO;
typedef OSVERSIONINFO *POSVERSIONINFO, *LPOSVERSIONINFO;

/* OUTPUT_DEBUG_STRING_INFO  [struct; shared] */
typedef struct _OUTPUT_DEBUG_STRING_INFO { 
 LPSTR lpDebugStringData; 
 WORD fUnicode; 
 WORD nDebugStringLength; 
} OUTPUT_DEBUG_STRING_INFO;
typedef OUTPUT_DEBUG_STRING_INFO *POUTPUT_DEBUG_STRING_INFO, *LPOUTPUT_DEBUG_STRING_INFO;

/* OVERLAPPED  [struct; shared] */
typedef struct _OVERLAPPED {
 ULONG_PTR Internal; 
 ULONG_PTR InternalHigh; 
 DWORD Offset; 
 DWORD OffsetHigh; 
 HANDLE hEvent; 
} OVERLAPPED;
typedef OVERLAPPED *POVERLAPPED, *LPOVERLAPPED;

/* SORTORDERSPEC  [struct; ce-only] */
typedef struct _SORTORDERSPEC {
 CEPROPID propid;
 DWORD dwFlags;
} SORTORDERSPEC;
typedef SORTORDERSPEC *PSORTORDERSPEC, *LPSORTORDERSPEC;

/* STORE_INFORMATION  [struct; ce-only; harvest-kb; harvest-kb] */
typedef struct STORE_INFORMATION {
 DWORD dwStoreSize;
 DWORD dwFreeSize;
} STORE_INFORMATION, *LPSTORE_INFORMATION;

/* SYSTEM_POWER_STATUS_EX2  [struct; ce-only] */
typedef struct _SYSTEM_POWER_STATUS_EX2 {
 BYTE ACLineStatus;
 BYTE BatteryFlag;
 BYTE BatteryLifePercent;
 BYTE Reserved1;
 DWORD BatteryLifeTime;
 DWORD BatteryFullLifeTime;
 BYTE Reserved2;
 BYTE BackupBatteryFlag;
 BYTE BackupBatteryLifePercent;
 BYTE Reserved3;
 DWORD BackupBatteryLifeTime;
 DWORD BackupBatteryFullLifeTime;
 DWORD BatteryVoltage;
 DWORD BatteryCurrent;
 DWORD BatteryAverageCurrent;
 DWORD BatteryAverageInterval;
 DWORD BatterymAHourConsumed;
 DWORD BatteryTemperature;
 DWORD BackupBatteryVoltage;
 BYTE BatteryChemistry;
 // Add any extra information after the BatteryChemistry member.
} SYSTEM_POWER_STATUS_EX2, *PSYSTEM_POWER_STATUS_EX2, *LPSYSTEM_POWER_STATUS_EX2;

/* TIME_ZONE_INFORMATION  [struct; shared] */
typedef struct _TIME_ZONE_INFORMATION {
 LONG Bias;
 WCHAR StandardName[32];
 SYSTEMTIME StandardDate;
 LONG StandardBias;
 WCHAR DaylightName[32];
 SYSTEMTIME DaylightDate;
 LONG DaylightBias;
} TIME_ZONE_INFORMATION;
typedef TIME_ZONE_INFORMATION *PTIME_ZONE_INFORMATION, *LPTIME_ZONE_INFORMATION;

/* UNLOAD_DLL_DEBUG_INFO  [struct; shared] */
typedef struct _UNLOAD_DLL_DEBUG_INFO { 
 LPVOID lpBaseOfDll; 
} UNLOAD_DLL_DEBUG_INFO;
typedef UNLOAD_DLL_DEBUG_INFO *PUNLOAD_DLL_DEBUG_INFO, *LPUNLOAD_DLL_DEBUG_INFO;

/* VS_FIXEDFILEINFO  [struct; shared] */
struct VS_FIXEDFILEINFO { 
DWORD dwSignature; 
DWORD dwStrucVersion; 
DWORD dwFileVersionMS; 
DWORD dwFileVersionLS; 
DWORD dwProductVersionMS; 
DWORD dwProductVersionLS; 
DWORD dwFileFlagsMask; 
DWORD dwFileFlags; 
DWORD dwFileOS; 
DWORD dwFileType; 
DWORD dwFileSubtype; 
DWORD dwFileDateMS; 
DWORD dwFileDateLS; };

/* WIN32_FILE_ATTRIBUTE_DATA  [struct; shared] */
typedef struct _WIN32_FILE_ATTRIBUTE_DATA{ 
 DWORD dwFileAttributes; 
 FILETIME ftCreationTime; 
 FILETIME ftLastAccessTime; 
 FILETIME ftLastWriteTime; 
 DWORD nFileSizeHigh; 
 DWORD nFileSizeLow; 
} WIN32_FILE_ATTRIBUTE_DATA, *LPWIN32_FILE_ATTRIBUTE_DATA;

/* WIN32_FIND_DATA  [struct; shared; A/W WIN32_FIND_DATAA,WIN32_FIND_DATAW (CE is W-side)] */
typedef struct _WIN32_FIND_DATA { 
 DWORD dwFileAttributes; 
 FILETIME ftCreationTime; 
 FILETIME ftLastAccessTime; 
 FILETIME ftLastWriteTime; 
 DWORD nFileSizeHigh; 
 DWORD nFileSizeLow; 
 DWORD dwOID; 
 TCHAR cFileName[MAX_PATH]; 
} WIN32_FIND_DATA;
typedef WIN32_FIND_DATA *PWIN32_FIND_DATA, *LPWIN32_FIND_DATA;

/* WIN32_FIND_DATAW  [struct; win32-spelling; unified-kb; unified-kb] */
typedef struct _WIN32_FIND_DATAW {
  DWORD    dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD    nFileSizeHigh;
  DWORD    nFileSizeLow;
  DWORD    dwReserved0;
  DWORD    dwReserved1;
  WCHAR    cFileName[MAX_PATH];
  WCHAR    cAlternateFileName[14];
  DWORD    dwFileType; // Obsolete. Do not use.
  DWORD    dwCreatorType; // Obsolete. Do not use
  WORD     wFinderFlags; // Obsolete. Do not use
} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;

/* BY_HANDLE_FILE_INFORMATION  [struct; shared] */
typedef struct _BY_HANDLE_FILE_INFORMATION { 
 DWORD dwFileAttributes; 
 FILETIME ftCreationTime; 
 FILETIME ftLastAccessTime; 
 FILETIME ftLastWriteTime; 
 DWORD dwVolumeSerialNumber; 
 DWORD nFileSizeHigh; 
 DWORD nFileSizeLow; 
 DWORD nNumberOfLinks; 
 DWORD nFileIndexHigh; 
 DWORD nFileIndexLow;
 DWORD dwOID;
} BY_HANDLE_FILE_INFORMATION;
typedef BY_HANDLE_FILE_INFORMATION *PBY_HANDLE_FILE_INFORMATION, *LPBY_HANDLE_FILE_INFORMATION;

/* CEFILEINFO  [struct; ce-only] */
typedef struct _CEFILEINFO {
 DWORD dwAttributes; 
 CEOID oidParent; 
 WCHAR szFileName[MAX_PATH]; 
 FILETIME ftLastChanged; 
 DWORD dwLength; 
} CEFILEINFO;
typedef CEFILEINFO *PCEFILEINFO, *LPCEFILEINFO;

/* COMMCONFIG  [struct; shared; entity-headers] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   dwSize */
/*   wVersion */
/*   wReserved */
/*   dcb */
/*   dwProviderSubType */
/*   dwProviderOffset */
/*   dwProviderSize */
/*   wcProviderData */

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* DebugBreak  [function; shared; unified-kb; unified-kb] */
void DebugBreak( void );

/* ExitProcess  [function; shared; unified-kb; unified-kb] */
VOID ExitProcess( 
 UINT uExitCode 
);

/* FindClosePartition  [function; ce-only; unified-kb; unified-kb] */
BOOL WINAPI FindClosePartition( 
 HANDLE hSearch 
);

/* FindCloseStore  [function; ce-only; unified-kb; unified-kb] */
BOOL WINAPI FindCloseStore( 
 HANDLE hSearch 
);

/* FindCloseUrlCache  [function; shared; unified-kb; unified-kb] */
BOOL FindCloseUrlCache( 
 HANDLE hEnumHandle
);

/* GetCurrentProcess  [function; shared; unified-kb; unified-kb] */
HANDLE GetCurrentProcess(void);

/* GetCurrentProcessId  [function; shared; unified-kb; unified-kb] */
DWORD GetCurrentProcessId(void);

/* GetCurrentThread  [function; shared; unified-kb; unified-kb] */
HANDLE GetCurrentThread(void);

/* GetCurrentThreadId  [function; shared; unified-kb; unified-kb] */
DWORD GetCurrentThreadId(void);

/* GlobalDeleteAtom  [function; shared; unified-kb; unified-kb] */
ATOM GlobalDeleteAtom( 
 ATOM nAtom 
);

/* ResetEvent  [function; shared; unified-kb; unified-kb] */
BOOL ResetEvent( 
 HANDLE hEvent 
);

/* SetEvent  [function; shared; unified-kb; unified-kb] */
BOOL SetEvent( 
 HANDLE hEvent 
);

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699 */

/* CheckPassword  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, Fspass.lib, fspass.lib] */
BOOL CheckPassword(
 LPWSTR lpszPassword 
);

/* GetStoreInformation  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL GetStoreInformation( 
 LPSTORE_INFORMATION lpsi 
);

/* GetTickCount  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
DWORD GetTickCount(void);

/* InterlockedTestExchange  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
LONG WINAPI InterlockedTestExchange(
 LPLONG Target,
 LONG OldValue,
 LONG NewValue
);

/* RegisterDevice  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, device.lib] */
HANDLE RegisterDevice(
 LPCWSTR lpszType,
 DWORD dwIndex,
 LPCWSTR lpszLib,
 DWORD dwInfo
);

/* SetDaylightTime  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
void SetDaylightTime(
 DWORD dst
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 1.0..199, 2.11..2.12, 3.0..699 */

/* CeCreateDatabase  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Fsdbase.lib, fsdbase.lib, Rapi.lib, rapi.lib] */
CEOID CeCreateDatabase(
 LPWSTR lpszName, 
 DWORD dwDbaseType, 
 WORD wNumSortOrder, 
 SORTORDERSPEC* rgSortSpecs
);

/* CeDeleteDatabase  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Fsdbase.lib, fsdbase.lib, Rapi.lib, rapi.lib] */
BOOL CeDeleteDatabase(
 CEOID oidDbase
);

/* CeDeleteRecord  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Fsdbase.lib, fsdbase.lib, Rapi.lib, rapi.lib] */
BOOL CeDeleteRecord(
 HANDLE hDatabase,
 CEOID oidRecord
);

/* CeFindFirstDatabase  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Fsdbase.lib, fsdbase.lib, Rapi.lib, rapi.lib] */
HANDLE CeFindFirstDatabase(
 DWORD dwDbaseType
);

/* CeFindNextDatabase  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Fsdbase.lib, fsdbase.lib, Rapi.lib, rapi.lib] */
CEOID CeFindNextDatabase(
 HANDLE hEnum
);

/* CeOpenDatabase  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Fsdbase.lib, fsdbase.lib, Rapi.lib, rapi.lib] */
HANDLE CeOpenDatabase(
 PCEOID poid, 
 LPWSTR lpszName, 
 CEPROPID propid, 
 DWORD dwFlags, 
 HWND hwndNotify
);

/* CeReadRecordProps  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Fsdbase.lib, fsdbase.lib, Rapi.lib, rapi.lib] */
CEOID CeReadRecordProps(
 HANDLE hDbase, 
 DWORD dwFlags, 
 LPWORD lpcPropID, 
 CEPROPID* rgPropID, 
 LPBYTE* lplpBuffer, 
 LPDWORD lpcbBuffer
);

/* CeSeekDatabase  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Fsdbase.lib, fsdbase.lib, Rapi.lib, rapi.lib] */
CEOID CeSeekDatabase(
 HANDLE hDatabase, 
 DWORD dwSeekType, 
 DWORD dwValue, 
 LPDWORD lpdwIndex
);

/* CreateFileForMapping  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
HANDLE CreateFileForMapping( 
 LPCTSTR lpFileName,
 DWORD dwDesiredAccess,
 DWORD dwShareMode,
 LPSECURITY_ATTRIBUTES lpSecurityAttributes,
 DWORD dwCreationDisposition,
 DWORD dwFlagsAndAttributes,
 HANDLE hTemplateFile
);

/* DeleteAndRenameFile  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Fsmain.lib, fsmain.lib] */
BOOL DeleteAndRenameFile( 
 LPCWSTR lpszDestFile, 
 LPCWSTR lpszSourceFile 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 1.0..199, 2.11..399, 5.0..699 */

/* Random  [function; ce-only; CE 1.0..199, 2.11..399, 5.0..699; Coredll.lib, coredll.lib] */
DWORD Random();
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..399, 5.0..699 */

/* CharLower  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coreloc.lib, coreloc.lib, locusa.lib; A/W CharLowerA,CharLowerW (CE is W-side)] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows Embedded CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
LPTSTR CharLower(
 LPTSTR lpsz
);

/* CharLowerBuff  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coreloc.lib, coreloc.lib, locusa.lib; A/W CharLowerBuffA,CharLowerBuffW (CE is W-side)] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows Embedded CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE Notes Supports only the Unicode version of this function. */
DWORD CharLowerBuff(
 LPTSTR lpsz,
 DWORD cchLength
);

/* CharNext  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Coreloc.lib, coreloc.lib, Locusa.lib, locusa.lib; A/W CharNextA,CharNextW (CE is W-side)] */
LPTSTR CharNext(
 LPCTSTR lpsz
);

/* CharPrev  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coreloc.lib, coreloc.lib, locusa.lib; A/W CharPrevA,CharPrevW (CE is W-side)] */
LPTSTR CharPrev(
 LPCTSTR lpszStart,
 LPCTSTR lpszCurrent
);

/* CharUpper  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coreloc.lib, coreloc.lib, locusa.lib; A/W CharUpperA,CharUpperW (CE is W-side)] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows Embedded CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
LPTSTR CharUpper(
 LPTSTR lpsz
);

/* CharUpperBuff  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coreloc.lib, coreloc.lib, locusa.lib; A/W CharUpperBuffA,CharUpperBuffW (CE is W-side)] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows Embedded CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE Notes Supports only the Unicode version of this function. */
DWORD CharUpperBuff(
 LPTSTR lpsz,
 DWORD cchLength
);

/* ClearCommBreak  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Serdev.lib, serdev.lib] */
BOOL ClearCommBreak(
 HANDLE hFile
);

/* ClearCommError  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Serdev.lib, serdev.lib] */
BOOL ClearCommError(
 HANDLE hFile,
 LPDWORD lpErrors,
 LPCOMSTAT lpStat
);

/* CompareFileTime  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coremain.lib, Nkstub.lib] */
LONG CompareFileTime( 
 const FILETIME* lpFileTime1,
 const FILETIME* lpFileTime2
);

/* ContinueDebugEvent  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL ContinueDebugEvent(
 DWORD dwProcessId,
 DWORD dwThreadId,
 DWORD dwContinueStatus
);

/* CreateEvent  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib; A/W CreateEventA,CreateEventW (CE is W-side)] */
HANDLE CreateEvent(
 LPSECURITY_ATTRIBUTES
 lpEventAttributes,
 BOOL bManualReset,
 BOOL InitialState,
 LPTSTR lpName
);

/* CreateMutex  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib; A/W CreateMutexA,CreateMutexW (CE is W-side)] */
HANDLE CreateMutex(
 LPSECURITY_ATTRIBUTES lpMutexAttributes,
 BOOL bInitialOwner,
 LPCTSTR lpName
);

/* CreateProcess  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib; A/W CreateProcessA,CreateProcessW (CE is W-side)] */
BOOL CreateProcess(
 LPCWSTR pszImageName,
 LPCWSTR pszCmdLine,
 LPSECURITY_ATTRIBUTES psaProcess,
 LPSECURITY_ATTRIBUTES psaThread,
 BOOL fInheritHandles,
 DWORD fdwCreate,
 LPVOID pvEnvironment,
 LPWSTR pszCurDir,
 LPSTARTUPINFOW psiStartInfo,
 LPPROCESS_INFORMATION pProcInfo
);

/* CreateThread  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
HANDLE CreateThread(
 LPSECURITY_ATTRIBUTES lpsa,
 DWORD cbStack,
 LPTHREAD_START_ROUTINE lpStartAddr,
 LPVOID lpvThreadParam,
 DWORD fdwCreate,
 LPDWORD lpIDThread
);

/* DebugActiveProcess  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
BOOL DebugActiveProcess( 
 DWORD dwProcessId 
);

/* DeleteCriticalSection  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coremain.lib, coremain.lib] */
void DeleteCriticalSection(
 LPCRITICAL_SECTION lpCriticalSection
);

/* DeviceIoControl  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Fsmain.lib, fsmain.lib] */
BOOL DeviceIoControl(
 HANDLE hDevice,
 DWORD dwIoControlCode,
 LPVOID lpInBuffer,
 DWORD nInBufferSize,
 LPVOID lpOutBuffer,
 DWORD nOutBufferSize,
 LPDWORD lpBytesReturned,
 LPOVERLAPPED lpOverlapped
);

/* DllMain  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib] */
BOOL WINAPI DllMain(
 HANDLE hinstDLL,
 DWORD dwReason,
 LPVOID lpvReserved
);

/* EnterCriticalSection  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coremain.lib, coremain.lib] */
void EnterCriticalSection(
 LPCRITICAL_SECTION lpCriticalSection
);

/* EscapeCommFunction  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Serdev.lib, serdev.lib] */
BOOL EscapeCommFunction(
 HANDLE hFile,
 DWORD dwFunc
);

/* ExitThread  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Coremain.lib, coremain.lib] */
VOID ExitThread(
 DWORD dwExitCode
);

/* FileTimeToLocalFileTime  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, coremain.lib] */
BOOL FileTimeToLocalFileTime(
 const FILETIME* lpFileTime,
 LPFILETIME lpLocalFileTime
);

/* FileTimeToSystemTime  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coremain.lib, Nkstub.lib] */
BOOL FileTimeToSystemTime(
 const FILETIME* lpFileTime,
 LPSYSTEMTIME lpSystemTime
);

/* FindResource  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib; A/W FindResourceA,FindResourceW (CE is W-side)] */
HRSRC FindResource( 
 HMODULE hModule, 
 LPCWSTR lpName, 
 LPCWSTR lpType 
);

/* FlushInstructionCache  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL FlushInstructionCache(
 HANDLE hProcess,
 LPCVOID lpBaseAddress,
 DWORD dwSize
);

/* FormatMessage  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Fmtmsg.lib, fmtmsg.lib; A/W FormatMessageA,FormatMessageW (CE is W-side)] */
DWORD FormatMessage(
 DWORD dwFlags, 
 LPCVOID lpSource, 
 DWORD dwMessageId, 
 DWORD dwLanguageId, 
 LPTSTR lpBuffer, 
 DWORD nSize, 
 va_list* Arguments
);

/* FreeLibrary  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
BOOL FreeLibrary(
 HMODULE hLibModule
);

/* GetCommMask  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Serdev.lib, serdev.lib] */
BOOL GetCommMask(
 HANDLE hFile,
 LPDWORD lpEvtMask
);

/* GetCommModemStatus  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Serdev.lib, serdev.lib] */
BOOL GetCommModemStatus(
 HANDLE hFile,
 LPDWORD lpModemStat
);

/* GetCommProperties  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Serdev.lib, serdev.lib] */
BOOL GetCommProperties(
 HANDLE hFile,
 LPCOMMPROP lpCommProp
);

/* GetCommState  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Serdev.lib, serdev.lib] */
BOOL GetCommState(
 HANDLE hFile,
 LPDCB lpDCB
);

/* GetCommTimeouts  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Serdev.lib, serdev.lib] */
BOOL GetCommTimeouts(
 HANDLE hFile,
 LPCOMMTIMEOUTS lpCommTimeouts
);

/* GetDiskFreeSpaceEx  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Fsmain.lib, fsmain.lib; A/W GetDiskFreeSpaceExA,GetDiskFreeSpaceExW (CE is W-side)] */
BOOL GetDiskFreeSpaceEx( 
 LPCWSTR lpDirectoryName, 
 PULARGE_INTEGER lpFreeBytesAvailableToCaller, 
 PULARGE_INTEGER lpTotalNumberOfBytes, 
 PULARGE_INTEGER lpTotalNumberOfFreeBytes 
);

/* GetExitCodeProcess  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
BOOL GetExitCodeProcess(
 HANDLE hProcess,
 LPDWORD lpExitCode
);

/* GetExitCodeThread  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
BOOL GetExitCodeThread(
 HANDLE hThread,
 LPDWORD lpExitCode
);

/* GetFileAttributes  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib; A/W GetFileAttributesA,GetFileAttributesW (CE is W-side)] */
DWORD GetFileAttributes(
 LPCTSTR lpFileName 
);

/* GetFileInformationByHandle  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL GetFileInformationByHandle( 
 HANDLE hFile, 
 LPBY_HANDLE_FILE_INFORMATION lpFileInformation
);

/* GetFileSize  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
DWORD GetFileSize( 
 HANDLE hFile, 
 LPDWORD lpFileSizeHigh
);

/* GetFileTime  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, fsmain.lib] */
BOOL GetFileTime(
 HANDLE hFile,
 LPFILETIME lpCreationTime,
 LPFILETIME lpLastAccessTime,
 LPFILETIME lpLastWriteTime
);

/* GetLastError  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib, Nkstub.lib] */
DWORD GetLastError(void);

/* GetLocalTime  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, coremain.lib] */
void GetLocalTime(
 LPSYSTEMTIME lpSystemTime
);

/* GetModuleFileName  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib; A/W GetModuleFileNameA,GetModuleFileNameW (CE is W-side)] */
WINAPI DWORD GetModuleFileName(
 HMODULE hModule,
 LPWSTR lpFilename,
 DWORD nSize
);

/* GetModuleHandle  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib; A/W GetModuleHandleA,GetModuleHandleW (CE is W-side)] */
HMODULE GetModuleHandle(
 LPCTSTR lpModuleName
);

/* GetProcAddress  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
FARPROC GetProcAddress(
 HMODULE hModule,
 LPCWSTR lpProcName
);

/* GetProcessHeap  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Lmem.lib, lmem.lib] */
HANDLE GetProcessHeap(VOID);

/* GetSystemInfo  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
VOID GetSystemInfo(
 LPSYSTEM_INFO lpSystemInfo
);

/* GetSystemPowerStatusEx2  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Getpower.lib, getpower.lib] */
DWORD GetSystemPowerStatusEx2(
 PSYSTEM_POWER_STATUS_EX2 pSystemPowerStatusEx2,
 DWORD dwLen, 
 BOOL fUpdate
);

/* GetSystemTime  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, coremain.lib] */
void GetSystemTime(
 LPSYSTEMTIME lpSystemTime
);

/* GetThreadPriority  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
int GetThreadPriority(
 HANDLE hThread
);

/* GetThreadTimes  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
BOOL GetThreadTimes (
 HANDLE hThread,
 LPFILETIME lpCreationTime,
 LPFILETIME lpExitTime,
 LPFILETIME lpKernelTime,
 LPFILETIME lpUserTime
);

/* GetTimeZoneInformation  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, coremain.lib] */
DWORD GetTimeZoneInformation(
 LPTIME_ZONE_INFORMATION lpTimeZoneInformation
);

/* GetVersionEx  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Coremain.lib, coremain.lib; A/W GetVersionExA,GetVersionExW (CE is W-side)] */
BOOL GetVersionEx( 
 LPOSVERSIONINFO lpVersionInformation
);

/* GlobalMemoryStatus  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
void GlobalMemoryStatus(
 LPMEMORYSTATUS lpBuffer
);

/* HeapAlloc  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, lmem.lib] */
LPVOID HeapAlloc(
 HANDLE hHeap,
 DWORD dwFlags,
 DWORD dwBytes
);

/* HeapCreate  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Lmem.lib, lmem.lib] */
HANDLE HeapCreate(
 DWORD flOptions,
 DWORD dwInitialSize,
 DWORD dwMaximumSize
);

/* HeapDestroy  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, lmem.lib] */
BOOL HeapDestroy(
 HANDLE hHeap
);

/* HeapFree  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Lmem.lib, lmem.lib] */
BOOL HeapFree(
 HANDLE hHeap,
 DWORD dwFlags,
 LPVOID lpMem 
);

/* HeapReAlloc  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Lmem.lib, lmem.lib] */
LPVOID HeapReAlloc(
 HANDLE hHeap,
 DWORD dwFlags,
 LPVOID lpMem,
 DWORD dwBytes
);

/* HeapSize  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Lmem.lib, lmem.lib] */
DWORD HeapSize(
 HANDLE hHeap,
 DWORD dwFlags,
 LPCVOID lpMem
);

/* InflateRect  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Rectapi.lib, rectapi.lib] */
BOOL InflateRect(
 LPRECT lprc, 
 int dx, 
 int dy
);

/* InitializeCriticalSection  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coremain.lib, coremain.lib] */
void InitializeCriticalSection(
 LPCRITICAL_SECTION lpCriticalSection
);

/* InterlockedDecrement  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
LONG InterlockedDecrement(
 LPLONG lpAddend
);

/* InterlockedExchange  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
LONG InterlockedExchange(
 LPLONG Target,
 LONG Value
);

/* InterlockedIncrement  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
LONG InterlockedIncrement(
 LPLONG lpAddend
);

/* IsBadCodePtr  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Lmem.lib, nk.lib] */
BOOL IsBadCodePtr(
 FARPROC lpfn
);

/* IsBadReadPtr  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
BOOL IsBadReadPtr(
 const void* lp,
 UINT ucb
);

/* IsBadWritePtr  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
BOOL IsBadWritePtr(
 LPVOID lp,
 UINT ucb
);

/* IsCharAlpha  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coreloc.lib; A/W IsCharAlphaA,IsCharAlphaW (CE is W-side)] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows Embedded CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE Notes Supports only the Unicode version of this function. */
BOOL IsCharAlpha(
 TCHAR ch
);

/* IsCharAlphaNumeric  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coreloc.lib; A/W IsCharAlphaNumericA,IsCharAlphaNumericW (CE is W-side)] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows Embedded CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE Notes Supports only the Unicode version of this function. */
BOOL IsCharAlphaNumeric(
 TCHAR ch
);

/* IsCharLower  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coreloc.lib; A/W IsCharLowerA,IsCharLowerW (CE is W-side)] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows Embedded CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE Notes Supports only the Unicode version of this function. */
BOOL IsCharLower(
 TCHAR ch
);

/* IsCharUpper  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coreloc.lib; A/W IsCharUpperA,IsCharUpperW (CE is W-side)] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows Embedded CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE Notes Supports only the Unicode version of this function. */
BOOL IsCharUpper(
 TCHAR ch
);

/* KillTimer  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; timer.lib] */
BOOL KillTimer(
 HWND hWnd, 
 UINT uIDEvent 
);

/* LeaveCriticalSection  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coremain.lib, coremain.lib] */
void LeaveCriticalSection(
 LPCRITICAL_SECTION lpCriticalSection
);

/* LoadFSD  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, device.lib] */
BOOL LoadFSD(
 HANDLE hDevice, 
 LPCWSTR lpFSDName
);

/* LoadLibrary  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib; A/W LoadLibraryA,LoadLibraryW (CE is W-side)] */
HINSTANCE LoadLibrary(
 LPCTSTR lpLibFileName
);

/* LoadResource  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
HGLOBAL LoadResource( 
 HMODULE hModule, 
 HRSRC hResInfo 
);

/* LoadString  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Loadstr.lib, loadstr.lib; A/W LoadStringA,LoadStringW (CE is W-side)] */
int LoadString(
 HINSTANCE hInstance,
 UINT uID,
 LPTSTR lpBuffer,
 int cchBufferMax
);

/* LocalAlloc  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Lmem.lib, lmem.lib] */
HLOCAL LocalAlloc(
 UINT uFlags,
 UINT uBytes
);

/* LocalFileTimeToFileTime  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, coremain.lib] */
BOOL LocalFileTimeToFileTime(
 const FILETIME* lpLocalFileTime,
 LPFILETIME lpFileTime
);

/* LocalFree  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Lmem.lib, lmem.lib] */
HLOCAL LocalFree(
 HLOCAL hMem
);

/* LocalReAlloc  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Lmem.lib, lmem.lib] */
HLOCAL LocalReAlloc(
 HLOCAL hMem,
 UINT uBytes,
 UINT fuFlags
);

/* LocalSize  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Lmem.lib, lmem.lib] */
UINT LocalSize(
 HLOCAL hMem
);

/* MapViewOfFile  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
LPVOID MapViewOfFile(
 HANDLE hFileMappingObject,
 DWORD dwDesiredAccess,
 DWORD dwFileOffsetHigh,
 DWORD dwFileOffsetLow,
 DWORD dwNumberOfBytesToMap
);

/* MessageBeep  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Msgbeep.lib, msgbeep.lib] */
BOOL
 MessageBeep(
 UINT
 uType
 );

/* MoveFile  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Fsmain.lib, fsmain.lib; A/W MoveFileA,MoveFileW (CE is W-side)] */
BOOL MoveFile(
 LPCTSTR lpExistingFileName, 
 LPCTSTR lpNewFileName
);

/* MsgWaitForMultipleObjects  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Msgque.lib, msgque.lib] */
DWORD MsgWaitForMultipleObjects(
 DWORD nCount, 
 LPHANDLE pHandles, 
 BOOL fWaitAll, 
 DWORD dwMilliseconds, 
 DWORD dwWakeMask 
);

/* MsgWaitForMultipleObjectsEx  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Msgque.lib, msgque.lib] */
DWORD MsgWaitForMultipleObjectsEx(
 DWORD nCount, 
 LPHANDLE pHandles, 
 DWORD dwMilliseconds, 
 DWORD dwWakeMask, 
 DWORD dwFlags 
);

/* OpenProcess  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, nk.lib] */
HANDLE OpenProcess(
 DWORD fdwAccess,
 BOOL fInherit,
 DWORD IDProcess
);

/* OutputDebugString  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Nk.lib, nk.lib; A/W OutputDebugStringA,OutputDebugStringW (CE is W-side)] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows Embedded CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE Notes Supports only the Unicode version of this function. */
void OutputDebugString(
 LPCTSTR lpOutputString 
);

/* PulseEvent  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL PulseEvent(
 HANDLE hEvent
);

/* PurgeComm  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Serdev.lib, serdev.lib] */
BOOL PurgeComm(
 HANDLE hFile,
 DWORD dwFlags
);

/* QueryPerformanceCounter  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, nk.lib] */
BOOL QueryPerformanceCounter(
 LARGE_INTEGER* lpPerformanceCount
);

/* QueryPerformanceFrequency  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, nk.lib] */
BOOL QueryPerformanceFrequency(
 LARGE_INTEGER* lpFrequency
);

/* RaiseException  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
void RaiseException(
 DWORD dwExceptionCode,
 DWORD dwExceptionFlags,
 DWORD nNumberOfArguments,
 const DWORD* lpArguments
);

/* ReadFile  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Fsmain.lib, fsmain.lib] */
BOOL ReadFile(
 HANDLE hFile,
 LPVOID lpBuffer,
 DWORD nNumberOfBytesToRead,
 LPDWORD lpNumberOfBytesRead,
 LPOVERLAPPED lpOverlapped
);

/* ReadProcessMemory  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
BOOL ReadProcessMemory(
 HANDLE hProcess,
 LPCVOID lpBaseAddress,
 LPVOID lpBuffer,
 DWORD nSize,
 LPDWORD lpNumberOfBytesRead
);

/* ReleaseMutex  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Nk.lib, nk.lib] */
BOOL ReleaseMutex(
 HANDLE hMutex
);

/* RemoveDirectory  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Fsmain.lib, fsmain.lib; A/W RemoveDirectoryA,RemoveDirectoryW (CE is W-side)] */
BOOL RemoveDirectory(
 LPCTSTR lpPathName
);

/* ResumeThread  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, nk.lib] */
DWORD ResumeThread(
 HANDLE hThread
);

/* SetCommBreak  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Serdev.lib, serdev.lib] */
BOOL SetCommBreak(
 HANDLE hFile
);

/* SetCommMask  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Serdev.lib, serdev.lib] */
BOOL SetCommMask(
 HANDLE hFile,
 DWORD dwEvtMask
);

/* SetCommState  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Serdev.lib, serdev.lib] */
BOOL SetCommState(
 HANDLE hFile,
 LPDCB lpDCB
);

/* SetCommTimeouts  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Serdev.lib, serdev.lib] */
BOOL SetCommTimeouts(
 HANDLE hFile,
 LPCOMMTIMEOUTS lpCommTimeouts
);

/* SetEndOfFile  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Fsmain.lib, fsmain.lib] */
BOOL SetEndOfFile( 
 HANDLE hFile
);

/* SetFileAttributes  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib; A/W SetFileAttributesA,SetFileAttributesW (CE is W-side)] */
BOOL SetFileAttributes(
 LPCTSTR lpFileName, 
 DWORD dwFileAttributes
);

/* SetFilePointer  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Fsmain.lib] */
DWORD SetFilePointer( 
 HANDLE hFile, 
 LONG lDistanceToMove, 
 PLONG lpDistanceToMoveHigh, 
 DWORD dwMoveMethod
);

/* SetFileTime  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, fsmain.lib] */
BOOL SetFileTime(
 HANDLE hFile,
 const FILETIME* lpCreationTime,
 const FILETIME* lpLastAccessTime,
 const FILETIME* lpLastWriteTime
);

/* SetLastError  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nkstub.lib] */
void SetLastError( 
 DWORD dwErrCode
);

/* SetLocalTime  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, coremain.lib] */
BOOL SetLocalTime( 
 const SYSTEMTIME* lpSystemTime
);

/* SetRect  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Rectapi.lib, rectapi.lib] */
BOOL SetRect(
 LPRECT lprc, 
 int xLeft, 
 int yTop, 
 int xRight, 
 int yBottom
);

/* SetSystemTime  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Coremain.lib, coremain.lib] */
BOOL SetSystemTime(
 const SYSTEMTIME* lpSystemTime
);

/* SetThreadPriority  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
BOOL SetThreadPriority(
 HANDLE hThread,
 int nPriority
);

/* SetTimeZoneInformation  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, coremain.lib] */
BOOL SetTimeZoneInformation(
 const TIME_ZONE_INFORMATION* lpTimeZoneInformation
);

/* SetupComm  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Serdev.lib, serdev.lib] */
BOOL SetupComm(
 HANDLE hFile,
 DWORD dwInQueue,
 DWORD dwOutQueue
);

/* SizeofResource  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
DWORD SizeofResource(
 HMODULE hModule, 
 HRSRC hResInfo 
);

/* Sleep  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, nk.lib, Nkstub.lib] */
void Sleep(
 DWORD dwMilliseconds
);

/* SuspendThread  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
DWORD SuspendThread(
 HANDLE hThread
);

/* SystemTimeToFileTime  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coremain.lib, Nkstub.lib] */
BOOL SystemTimeToFileTime(
 const SYSTEMTIME* lpSystemTime,
 LPFILETIME lpFileTime
);

/* TerminateProcess  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, nk.lib] */
BOOL TerminateProcess(
 HANDLE hProcess,
 DWORD uExitCode
);

/* TerminateThread  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, nk.lib] */
BOOL TerminateThread(
 HANDLE hThread,
 DWORD dwExitCode
);

/* TimerProc  [function, callback; shared; CE 2.11..2.12, 3.0..399, 5.0..699] */
void CALLBACK TimerProc(
 HWND hwnd, 
 UINT uMsg, 
 UINT idEvent, 
 DWORD dwTime 
);

/* TlsFree  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Coremain.lib] */
BOOL TlsFree(
 DWORD dwTlsIndex
);

/* TlsGetValue  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Coremain.lib, coremain.lib] */
LPVOID TlsGetValue(
 DWORD dwTlsIndex
);

/* TlsSetValue  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Coremain.lib, coremain.lib] */
BOOL TlsSetValue(
 DWORD dwTlsIndex,
 LPVOID lpTlsValue
);

/* TransmitCommChar  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Serdev.lib, serdev.lib] */
BOOL TransmitCommChar(
 HANDLE hFile,
 char cChar
);

/* UnmapViewOfFile  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, nk.lib] */
BOOL UnmapViewOfFile( 
 LPCVOID lpBaseAddress 
);

/* VirtualAlloc  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, nk.lib] */
LPVOID VirtualAlloc(
 LPVOID lpAddress,
 DWORD dwSize,
 DWORD flAllocationType,
 DWORD flProtect
);

/* VirtualFree  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, nk.lib] */
BOOL VirtualFree(
 LPVOID lpAddress,
 DWORD dwSize,
 DWORD dwFreeType
);

/* VirtualProtect  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, nk.lib] */
BOOL VirtualProtect(
 LPVOID lpAddress,
 DWORD dwSize,
 DWORD flNewProtect,
 PDWORD lpflOldProtect
);

/* VirtualQuery  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, nk.lib] */
DWORD VirtualQuery(
 LPCVOID lpAddress,
 PMEMORY_BASIC_INFORMATION lpBuffer,
 DWORD dwLength
);

/* WaitCommEvent  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Serdev.lib, serdev.lib] */
BOOL WaitCommEvent(
 HANDLE hFile,
 LPDWORD lpEvtMask,
 LPOVERLAPPED lpOverlapped
);

/* WaitForMultipleObjects  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Nk.lib, nk.lib] */
DWORD WaitForMultipleObjects(
 DWORD nCount,
 CONST HANDLE* lpHandles,
 BOOL fWaitAll,
 DWORD dwMilliseconds
);

/* WaitForSingleObject  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
DWORD WaitForSingleObject(
 HANDLE hHandle,
 DWORD dwMilliseconds
);

/* WriteFile  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Fsmain.lib, fsmain.lib] */
BOOL WriteFile( 
 HANDLE hFile, 
 LPCVOID lpBuffer, 
 DWORD nNumberOfBytesToWrite, 
 LPDWORD lpNumberOfBytesWritten, 
 LPOVERLAPPED lpOverlapped
);

/* WriteProcessMemory  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Nk.lib, nk.lib] */
BOOL WriteProcessMemory(
 HANDLE hProcess,
 LPVOID lpBaseAddress,
 LPVOID lpBuffer,
 DWORD nSize,
 LPDWORD lpNumberOfBytesWritten
);

/* wsprintf  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coreloc.lib; A/W wsprintfA,wsprintfW (CE is W-side)] */
/* Windows CE supports only the Unicode version of wsprintf. */
/* Windows CE supports only the Unicode version of wsprintf. */
/* Windows CE supports only the Unicode version of wsprintf. */
/* Windows Embedded CE supports only the Unicode version of wsprintf. */
/* Windows CE supports only the Unicode version of wsprintf. */
/* Windows CE Notes Supports only the Unicode version of this function. */
int wsprintf(
 LPTSTR lpOut,
 LPCTSTR lpFmt,
 ...
);

/* wvsprintf  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coreloc.lib; A/W wvsprintfA,wvsprintfW (CE is W-side)] */
/* Windows CE supports only the Unicode version of wvsprintf. */
/* Windows CE supports only the Unicode version of wvsprintf. */
/* Windows CE supports only the Unicode version of wvsprintf. */
/* Windows Embedded CE supports only the Unicode version of wvsprintf. */
/* Windows CE supports only the Unicode version of wvsprintf. */
/* Windows CE Notes Supports only the Unicode version of this function. */
int wvsprintf(
 LPTSTR lpOutput,
 LPCTSTR lpFormat,
 va_list ArgList
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..699 */

/* CeReadRecordPropsEx  [function; ce-only; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Fsdbase.lib, fsdbase.lib, Rapi.lib, rapi.lib] */
CEOID CeReadRecordPropsEx( 
 HANDLE hDbase, 
 DWORD dwFlags,
 LPWORD lpcPropID, 
 CEPROPID* rgPropID, 
 LPBYTE* lplpBuffer,
 LPDWORD lpcbBuffer, 
 HANDLE hHeap
);

/* CloseHandle  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib] */
BOOL CloseHandle(
 HANDLE hObject
);

/* CopyFile  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Fsmain.lib, fsmain.lib; A/W CopyFileA,CopyFileW (CE is W-side)] */
BOOL CopyFile(
 LPCTSTR lpExistingFileName, 
 LPCTSTR lpNewFileName, 
 BOOL bFailIfExists 
);

/* CreateDirectory  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Fsmain.lib, fsmain.lib; A/W CreateDirectoryA,CreateDirectoryW (CE is W-side)] */
BOOL CreateDirectory(
 LPCTSTR lpPathName, 
 LPSECURITY_ATTRIBUTES lpSecurityAttributes 
);

/* CreateFile  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, fsmain.lib; A/W CreateFileA,CreateFileW (CE is W-side)] */
HANDLE CreateFile(
 LPCTSTR lpFileName,
 DWORD dwDesiredAccess,
 DWORD dwShareMode,
 LPSECURITY_ATTRIBUTES lpSecurityAttributes,
 DWORD dwCreationDisposition,
 DWORD dwFlagsAndAttributes,
 HANDLE hTemplateFile
);

/* CreateFileMapping  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib; A/W CreateFileMappingA,CreateFileMappingW (CE is W-side)] */
HANDLE CreateFileMapping(
 HANDLE hFile,
 LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
 DWORD flProtect,
 DWORD dwMaximumSizeHigh,
 DWORD dwMaximumSizeLow,
 LPCTSTR lpName 
);

/* DeleteFile  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Fsmain.lib, fsmain.lib; A/W DeleteFileA,DeleteFileW (CE is W-side)] */
BOOL DeleteFile(
 LPCTSTR lpFileName
);

/* FindClose  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib] */
BOOL FindClose(
 HANDLE hFindFile
);

/* FindFirstFile  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Fsmain.lib, fsmain.lib; A/W FindFirstFileA,FindFirstFileW (CE is W-side)] */
HANDLE FindFirstFile(
 LPCTSTR lpFileName, 
 LPWIN32_FIND_DATA lpFindFileData 
);

/* FindNextFile  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Fsmain.lib, fsmain.lib; A/W FindNextFileA,FindNextFileW (CE is W-side)] */
BOOL FindNextFile( 
 HANDLE hFindFile, 
 LPWIN32_FIND_DATA lpFindFileData 
);

/* FlushFileBuffers  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Fsmain.lib, fsmain.lib] */
BOOL WINAPI FlushFileBuffers(
 HANDLE hFile 
);

/* FlushViewOfFile  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
BOOL FlushViewOfFile( 
 LPCVOID lpBaseAddress, 
 DWORD dwNumberOfBytesToFlush 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* ActivateDevice  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib, device.lib] */
HANDLE ActivateDevice(
 LPCWSTR lpszDevKey, 
 DWORD dwClientInfo
);

/* CeGetReplChangeMask  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeGetReplChangeMask(
 LPDWORD lpmask
);

/* CeGetThreadPriority  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
int CeGetThreadPriority(
 HANDLE hThread
);

/* CeGetThreadQuantum  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
DWORD CeGetThreadQuantum(
 HANDLE hThread
);

/* CeSetReplChangeMask  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeSetReplChangeMask(
 DWORD mask
);

/* CeSetThreadPriority  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, nk.lib] */
BOOL CeSetThreadPriority(
 HANDLE hThread,
 int nPriority
);

/* CeSetThreadQuantum  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
BOOL CeSetThreadQuantum(
 HANDLE hThread,
 DWORD dwTime
);

/* CreateSemaphore  [function; shared; CE 3.0..399, 5.0..699; Nk.lib, nk.lib; A/W CreateSemaphoreA,CreateSemaphoreW (CE is W-side)] */
HANDLE CreateSemaphore(
 LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
 LONG lInitialCount,
 LONG lMaximumCount,
 LPCTSTR lpName
);

/* DeactivateDevice  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib, device.lib] */
BOOL DeactivateDevice(
 HANDLE hDevice
);

/* DisableThreadLibraryCalls  [function; shared; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib] */
BOOL DisableThreadLibraryCalls(
 HMODULE hLibModule
);

/* GetCommandLine  [function; shared; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib; A/W GetCommandLineA,GetCommandLineW (CE is W-side)] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows Embedded CE supports only the Unicode version of this function. */
LPTSTR GetCommandLine(void);

/* GetFileAttributesEx  [function; shared; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib; A/W GetFileAttributesExA,GetFileAttributesExW (CE is W-side)] */
BOOL GetFileAttributesEx(
 LPCTSTR lpFileName, 
 GET_FILEEX_INFO_LEVELS fInfoLevelId, 
 LPVOID lpFileInformation 
);

/* GetFileVersionInfo  [function; shared; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib; A/W GetFileVersionInfoA,GetFileVersionInfoW (CE is W-side)] */
BOOL GetFileVersionInfo(
 LPTSTR lptstrFilename,
 DWORD dwHandle,
 DWORD dwLen,
 LPVOID lpData
);

/* GetFileVersionInfoSize  [function; shared; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib; A/W GetFileVersionInfoSizeA,GetFileVersionInfoSizeW (CE is W-side)] */
DWORD GetFileVersionInfoSize(
 LPTSTR lptstrFilename,
 LPDWORD lpdwHandle
);

/* GetIdleTime  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
DWORD GetIdleTime (void);

/* GetPasswordActive  [function; ce-only; CE 3.0..399, 5.0..699; fspass.lib] */
BOOL GetPasswordActive(void);

/* GetTempFileName  [function; shared; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib; A/W GetTempFileNameA,GetTempFileNameW (CE is W-side)] */
UINT GetTempFileName(
 LPCTSTR lpPathName, 
 LPCTSTR lpPrefixString, 
 UINT uUnique, 
 LPTSTR lpTempFileName
);

/* GetTempPath  [function; shared; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib; A/W GetTempPathA,GetTempPathW (CE is W-side)] */
DWORD GetTempPath(
 DWORD ccBuffer, 
 LPTSTR lpszBuffer
);

/* LoadFSDEx  [function; ce-only; CE 3.0..399, 5.0..699; Device.lib, device.lib] */
BOOL LoadFSDEx(
 HANDLE hDevice, 
 LPCWSTR lpFSDName, 
 DWORD dwFlag
);

/* LoadLibraryEx  [function; shared; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib, nk.lib; A/W LoadLibraryExA,LoadLibraryExW (CE is W-side)] */
HMODULE LoadLibraryEx(
 LPCTSTR lpLibFileName,
 HANDLE hFile,
 DWORD dwFlags
);

/* ReleaseSemaphore  [function; shared; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL ReleaseSemaphore(
 HANDLE hSemaphore,
 LONG lReleaseCount,
 LPLONG lpPreviousCount
);

/* SetPassword  [function; ce-only; CE 3.0..399, 5.0..699; fspass.lib] */
BOOL SetPassword(
 LPWSTR lpszOldPassword, 
 LPWSTR lpszNewPassword 
);

/* SetPasswordActive  [function; ce-only; CE 3.0..399, 5.0..699; fspass.lib] */
BOOL SetPasswordActive(
 BOOL bActive, 
 LPWSTR lpszPassword 
);

/* SignalStarted  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
VOID SignalStarted(
 DWORD dw
);

/* TryEnterCriticalSection  [function; shared; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL TryEnterCriticalSection(
 LPCRITICAL_SECTION lpCriticalSection
);

/* VerQueryValue  [function; shared; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib; A/W VerQueryValueA,VerQueryValueW (CE is W-side)] */
BOOL VerQueryValue(
 const LPVOID pBlock,
 LPTSTR lpSubBlock,
 LPVOID* lplpBuffer,
 PUINT puLen
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* CeResyncFilesys  [function; ce-only; CE 3.0..699; Device.lib, device.lib] */
BOOL CeResyncFilesys(
 HANDLE hDevice
);

/* FindFirstFileEx  [function; shared; CE 3.0..699; Coredll.lib, coredll.lib, Fsmain.lib, fsmain.lib; A/W FindFirstFileExA,FindFirstFileExW (CE is W-side)] */
HANDLE FindFirstFileEx(
 LPCTSTR lpFileName, 
 FINDEX_INFO_LEVELS fInfoLevelId, 
 LPVOID lpFindFileData, 
 FINDEX_SEARCH_OPS fSearchOp, 
 LPVOID lpSearchFilter, 
 DWORD dwAdditionalFlags 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* CeGenRandom  [function; ce-only; CE 4.0..699; Coredll.lib, coredll.lib] */
BOOL CeGenRandom(
 DWORD dwLen, 
 BYTE* pbBuffer 
);

/* CeGetFileNotificationInfo  [function; ce-only; CE 4.0..699; Coredll.lib, coredll.lib] */
BOOL CeGetFileNotificationInfo(
 HANDLE h,
 DWORD dwFlags,
 LPVOID lpBuffer,
 DWORD nBufferLength,
 LPDWORD lpBytesReturned,
 LPDWORD lpBytesAvailable
);

/* FindCloseChangeNotification  [function; shared; CE 4.0..699; Coredll.lib, coredll.lib] */
BOOL FindCloseChangeNotification(
 HANDLE hChangeHandle
);

/* FindFirstChangeNotification  [function; shared; CE 4.0..699; Coredll.lib, coredll.lib; A/W FindFirstChangeNotificationA,FindFirstChangeNotificationW (CE is W-side)] */
HANDLE FindFirstChangeNotification(
 LPCTSTR lpPathName,
 BOOL bWatchSubtree,
 DWORD dwNotifyFilter
);

/* FindNextChangeNotification  [function; shared; CE 4.0..699; Coredll.lib, coredll.lib] */
BOOL FindNextChangeNotification(
 HANDLE hChangeHandle
);

/* SetUserData  [function; ce-only; CE 4.0..699; Coredll.lib, coredll.lib] */
BOOL SetUserData( 
 LPBYTE lpbUserData, 
 DWORD dwDataSize 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* ActivateDeviceEx  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
HANDLE ActivateDeviceEx(
 LPCWSTR lpszDevKey, 
 LPCVOID lpRegEnts, 
 DWORD cRegEnts, 
 LPVOID lpvParam
);

/* CeFsIoControl  [function; ce-only; CE 5.0..699; Device.lib] */
BOOL CeFsIoControl(
 LPCWSTR pszDir,
 DWORD dwIoControlCode,
 LPVOID lpInBuffer,
 DWORD nInBufferSize,
 LPVOID lpOutBuffer,
 DWORD nOutBufferSize,
 LPDWORD lpBytesReturned,
 LPOVERLAPPED lpOverlapped
);

/* CeGetCanonicalPathName  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
DWORD CeGetCanonicalPathName(
 LPCWSTR lpPathName, 
 LPWSTR lpCanonicalPathName,
 DWORD cchCanonicalPathName,
 DWORD dwReserved
);

/* CeZeroPointer  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
LPVOID CeZeroPointer(
 LPVOID ptr
);

/* ConvertThreadToFiber  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib] */
LPVOID WINAPI ConvertThreadToFiber(
 LPVOID lpParameter
);

/* DeleteFiber  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib] */
VOID WINAPI DeleteFiber(
 LPVOID lpFiber
);

/* DuplicateHandle  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib; +not-umbrella] */
BOOL DuplicateHandle(
 HANDLE hSourceProcessHandle,
 HANDLE hSourceHandle,
 HANDLE hTargetProcessHandle,
 LPHANDLE lpTargetHandle,
 DWORD dwDesiredAccess,
 BOOL bInheritHandle,
 DWORD dwOptions
);

/* FindFirstDevice  [function; ce-only; CE 5.0..699] */
HANDLE FindFirstDevice(
 DeviceSearchType searchType,
 LPCVOID pvSearchParam,
 PDEVMGR_DEVICE_INFORMATION pdi
);

/* FindNextDevice  [function; ce-only; CE 5.0..699] */
BOOL FindNextDevice(
 HANDLE h,
 PDEVMGR_DEVICE_INFORMATION pdi
);

/* FreeLibraryAndExitThread  [function; shared; CE 5.0..699; Coredll.dll, coredll.dll] */
VOID FreeLibraryAndExitThread(
 HMODULE hModule,
 DWORD dwExitCode
);

/* GetCurrentFiber  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib] */
LPVOID GetCurrentFiber(void);

/* GetCurrentFT  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
void GetCurrentFT(
 LPFILETIME lpFileTime
);

/* GetDeviceInformationByDeviceHandle  [function; ce-only; CE 5.0..699] */
BOOL GetDeviceInformationByDeviceHandle(
 HANDLE hDevice,
 PDEVMGR_DEVICE_INFORMATION pdi
);

/* GetDeviceInformationByFileHandle  [function; ce-only; CE 5.0..699] */
BOOL GetDeviceInformationByFileHandle(
 HANDLE hFile,
 PDEVMGR_DEVICE_INFORMATION pdi
);

/* GetDllVersion  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
DWORD GetDllVersion(
 HMODULE hMod
);

/* GetFiberData  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib] */
LPVOID WINAPI GetFiberData(void);

/* GetProcessVersion  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib] */
DWORD GetProcessVersion(
 DWORD ProcessId
);

/* HeapCompact  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib] */
UINT HeapCompact(
 HANDLE hHeap,
 DWORD dwFlags
);

/* HeapValidate  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL HeapValidate(
 HANDLE hHeap,
 DWORD dwFlags,
 LPCVOID lpMem 
);

/* InterlockedCompareExchange  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib; +not-umbrella] */
LONG InterlockedCompareExchange(
 LPLONG Destination,
 LONG Exchange,
 LONG Comperand
);

/* InterlockedCompareExchangePointer  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib] */
PVOID InterlockedCompareExchangePointer(
 PVOID* Destination,
 PVOID ExChange,
 PVOID Comperand
);

/* InterlockedExchangeAdd  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib; +not-umbrella] */
LONG InterlockedExchangeAdd(
 LPLONG Addend,
 LONG Increment
);

/* InterlockedExchangePointer  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib] */
PVOID InterlockedExchangePointer(
 PVOID* Target,
 PVOID Value
);

/* IsProcessorFeaturePresent  [function; shared; CE 5.0..699; Coredll.dll, OEMMain.lib, OEMMain_StaticKITL.lib] */
BOOL IsProcessorFeaturePresent(
 DWORD dwProcessorFeature
);

/* LockFileEx  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL LockFileEx(
 HANDLE hFile, 
 DWORD dwFlags,
 DWORD dwReserved,
 DWORD nNumberOfBytesToLockLow,
 DWORD nNumberOfBytesToLockHigh,
 LPOVERLAPPED lpOverlapped
);

/* LockResource  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib, Nk.lib] */
LPVOID LockResource(
 HGLOBAL hResData 
);

/* OpenEvent  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib; A/W OpenEventA,OpenEventW (CE is W-side)] */
HANDLE OpenEvent(
 DWORD dwDesiredAccess,
 BOOL bInheritHandle,
 LPCTSTR lpName
);

/* QueryInstructionSet  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL QueryInstructionSet(
 DWORD dwInstructionSet,
 LPDWORD lpdwCurrentInstructionSet
);

/* ResourceCreateList  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL ResourceCreateList(
 DWORD dwResId, 
 DWORD dwMinimum, 
 DWORD dwCount
);

/* ResourceDestroyList  [function; ce-only; CE 5.0..699] */
BOOL ResourceDestroyList (
 DWORD dwResId
);

/* ResourceMarkAsShareable  [function; ce-only; CE 5.0..699] */
BOOL ResourceMarkAsShareable(
 DWORD dwResId,
 DWORD dwId,
 DWORD dwLen,
 BOOL fShareable
);

/* ResourceRelease  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL ResourceRelease(
 DWORD dwResId, 
 DWORD dwBase, 
 DWORD dwLen
);

/* ResourceRequest  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL ResourceRequest(
 DWORD dwResId, 
 DWORD dwBase, 
 DWORD dwLen
);

/* ResourceRequestEx  [function; ce-only; CE 5.0..699] */
BOOL ResourceRequestEx (
 DWORD dwResId,
 DWORD dwId,
 DWORD dwLen,
 DWORD dwFlags
);

/* StopDeviceNotifications  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL StopDeviceNotifications(
 HANDLE h
);

/* SwitchToFiber  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib] */
VOID WINAPI SwitchToFiber(
 LPVOID lpFiber
);

/* UnlockFileEx  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL UnlockFileEx(
 HANDLE hFile, 
 DWORD dwReserved,
 DWORD nNumberOfBytesToLockLow,
 DWORD nNumberOfBytesToLockHigh,
 LPOVERLAPPED lpOverlapped
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* DebugActiveProcessStop  [function; shared; CE 6.0..699; coredll.lib] */
BOOL DebugActiveProcessStop (
 DWORD dwProcessId
);

/* GetSystemTimeAsFileTime  [function; shared; CE 6.0..699; coredll.lib] */
void GetSystemTimeAsFileTime(
 LPFILETIME lpSystemTimeAsFileTime
);

/* IsDebuggerPresent  [function; shared; CE 6.0..699; coredll.lib] */
BOOL IsDebuggerPresent (void);

/* OpenThread  [function; shared; CE 6.0..699; coredll.lib] */
HANDLE OpenThread(
 DWORD dwDesiredAccess,
 BOOL bInheritHandle,
 DWORD dwThreadId
);

/* RemoveVectoredExceptionHandler  [function; shared; CE 6.0..699; coredll.lib] */
ULONG RemoveVectoredExceptionHandler(
 PVOID VectoredHandlerHandle
);

/* VirtualAllocEx  [function; shared; CE 6.0..699; coredll.lib] */
LPVOID VirtualAllocEx(
 HANDLE hProcess,
 LPVOID lpAddress,
 DWORD dwSize,
 DWORD flAllocationType,
 DWORD flProtect
);

/* VirtualFreeEx  [function; shared; CE 6.0..699; coredll.lib] */
BOOL VirtualFreeEx(
 HANDLE hProcess,
 LPVOID lpAddress,
 DWORD dwSize,
 DWORD dwFreeType
);

/* VirtualProtectEx  [function; shared; CE 6.0..699; coredll.lib] */
BOOL VirtualProtectEx(
 HANDLE hProcess,
 LPVOID lpAddress,
 DWORD dwSize,
 DWORD flNewProtect,
 PDWORD lpflOldProtect
);

/* VirtualQueryEx  [function; shared; CE 6.0..699; coredll.lib] */
DWORD VirtualQueryEx(
 HANDLE hProcess,
 LPCVOID lpAddress,
 PMEMORY_BASIC_INFORMATION lpBuffer,
 DWORD dwLength
);
#endif /* _WIN32_WCE */

#endif /* _WINBASE_ */
