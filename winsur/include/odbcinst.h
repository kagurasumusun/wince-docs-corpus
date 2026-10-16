/* odbcinst.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 40 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _ODBCINST_
#define _ODBCINST_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define INSTAPI __stdcall
#define ODBC_ADD_DSN 1
#define ODBC_ADD_SYS_DSN 4
#define ODBC_BOTH_DSN 0
#define ODBC_CONFIG_DRIVER 3
#define ODBC_CONFIG_DRIVER_MAX 100
#define ODBC_CONFIG_DSN 2
#define ODBC_CONFIG_SYS_DSN 5
#define ODBC_ERROR_COMPONENT_NOT_FOUND 6
#define ODBC_ERROR_CREATE_DSN_FAILED 18
#define ODBC_ERROR_GENERAL_ERR 1
#define ODBC_ERROR_INVALID_BUFF_LEN 2
#define ODBC_ERROR_INVALID_DSN 9
#define ODBC_ERROR_INVALID_HWND 3
#define ODBC_ERROR_INVALID_INF 10
#define ODBC_ERROR_INVALID_KEYWORD_VALUE 8
#define ODBC_ERROR_INVALID_LOG_FILE 15
#define ODBC_ERROR_INVALID_NAME 7
#define ODBC_ERROR_INVALID_PARAM_SEQUENCE 14
#define ODBC_ERROR_INVALID_PATH 12
#define ODBC_ERROR_INVALID_REQUEST_TYPE 5
#define ODBC_ERROR_INVALID_STR 4
#define ODBC_ERROR_LOAD_LIB_FAILED 13
#define ODBC_ERROR_OUT_OF_MEM 21
#define ODBC_ERROR_OUTPUT_STRING_TRUNCATED 22
#define ODBC_ERROR_REMOVE_DSN_FAILED 20
#define ODBC_ERROR_REQUEST_FAILED 11
#define ODBC_ERROR_USAGE_UPDATE_FAILED 17
#define ODBC_ERROR_USER_CANCELED 16
#define ODBC_ERROR_WRITING_SYSINFO_FAILED 19
#define ODBC_INSTALL_COMPLETE 2
#define ODBC_INSTALL_DRIVER 1
#define ODBC_INSTALL_INQUIRY 1
#define ODBC_REMOVE_DEFAULT_DSN 7
#define ODBC_REMOVE_DRIVER 2
#define ODBC_REMOVE_DSN 3
#define ODBC_REMOVE_SYS_DSN 6
#define ODBC_SYSTEM_DSN 2
#define ODBC_USER_DSN 1
#define ODBCVER 0x0351

#endif /* _ODBCINST_ */
