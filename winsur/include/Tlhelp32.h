/* Tlhelp32.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 20 constants, 53 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _TLHELP32_
#define _TLHELP32_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define HF32_DEFAULT 1
#define HF32_SHARED 2
#define LF32_FIXED 0x1
#define LF32_FREE 0x2
#define LF32_MOVEABLE 0x4
#define LPMODULEENTRY32 LPMODULEENTRY32W
#define LPPROCESSENTRY32 LPPROCESSENTRY32W
#define MAX_MODULE_NAME32 255
#define MODULEENTRY32 MODULEENTRY32W
#define PMODULEENTRY32 PMODULEENTRY32W
#define PPROCESSENTRY32 PPROCESSENTRY32W
#define PROCESSENTRY32 PROCESSENTRY32W
#define TH32CS_GETALLMODS 0x80000000
#define TH32CS_INHERIT 0x80000000
#define TH32CS_SNAPALL (TH32CS_SNAPHEAPLIST|TH32CS_SNAPPROCESS|TH32CS_SNAPTHREAD|TH32CS_SNAPMODULE)
#define TH32CS_SNAPHEAPLIST 0x00000001
#define TH32CS_SNAPMODULE 0x00000008
#define TH32CS_SNAPMODULE32 0x00000010
#define TH32CS_SNAPPROCESS 0x00000002
#define TH32CS_SNAPTHREAD 0x00000004

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* HEAPENTRY32  [struct; shared] */
typedef struct tagHEAPENTRY32 {
 DWORD dwSize;
 HANDLE hHandle;
 DWORD dwAddress;
 DWORD dwBlockSize;
 DWORD dwFlags;
 DWORD dwLockCount;
 DWORD dwResvd;
 DWORD th32ProcessID;
 DWORD th32HeapID;
 } HEAPENTRY32;
 typedef HEAPENTRY32* PHEAPENTRY32;
typedef HEAPENTRY32* LPHEAPENTRY32;

/* HEAPLIST32  [struct; shared] */
typedef struct tagHEAPLIST32 { 
 DWORD dwSize; 
 DWORD th32ProcessID; 
 DWORD th32HeapID; 
 DWORD dwFlags; 
 } HEAPLIST32; 
 typedef HEAPLIST32* PHEAPLIST32; 
typedef HEAPLIST32* LPHEAPLIST32;

/* MODULEENTRY32  [struct; shared; A/W MODULEENTRY32W (CE is W-side)] */
typedef struct tagMODULEENTRY32 {
 DWORD dwSize;
 DWORD th32ModuleID;
 DWORD th32ProcessID;
 DWORD GlblcntUsage;
 DWORD ProccntUsage;
 BYTE *modBaseAddr;
 DWORD modBaseSize;
 HMODULE hModule;
 TCHAR szModule[MAX_PATH];
 TCHAR szExePath[MAX_PATH];
 DWORD dwFlags;
} MODULEENTRY32, *PMODULEENTRY32, *LPMODULEENTRY32;

/* PROCESSENTRY32  [struct; shared; A/W PROCESSENTRY32W (CE is W-side)] */
typedef struct tagPROCESSENTRY32 {
 DWORD dwSize;
 DWORD cntUsage;
 DWORD th32ProcessID;
 DWORD th32DefaultHeapID;
 DWORD th32ModuleID;
 DWORD cntThreads;
 DWORD th32ParentProcessID;
 LONG pcPriClassBase;
 DWORD dwFlags;
 TCHAR szExeFile[MAX_PATH];
 DWORD th32MemoryBase;
 DWORD th32AccessKey;
 } PROCESSENTRY32;
 typedef PROCESSENTRY32* PPROCESSENTRY32;
typedef PROCESSENTRY32* LPPROCESSENTRY32;

/* THREADENTRY32  [struct; shared] */
typedef struct tagTHREADENTRY32 {
 DWORD dwSize;
 DWORD cntUsage;
 DWORD th32ThreadID;
 DWORD th32OwnerProcessID;
 LONG tpBasePri;
 LONG tpDeltaPri;
 DWORD dwFlags;
 DWORD th32AccessKey;
 DWORD th32CurrentProcessID;
 } THREADENTRY32;
 typedef THREADENTRY32* PTHREADENTRY32;
typedef THREADENTRY32* LPTHREADENTRY32;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* CloseToolhelp32Snapshot  [function; ce-only; unified-kb; unified-kb] */
BOOL WINAPI CloseToolhelp32Snapshot( 
 HANDLE hSnapshot 
);

/* CreateToolhelp32Snapshot  [function; shared; unified-kb; unified-kb] */
HANDLE WINAPI CreateToolhelp32Snapshot( 
 DWORD dwFlags, 
 DWORD th32ProcessID 
);

/* Module32First  [function; shared; unified-kb; unified-kb] */
BOOL WINAPI Module32First( 
 HANDLE hSnapshot, 
 LPMODULEENTRY32 lpme 
);

/* Module32Next  [function; shared; unified-kb; unified-kb] */
BOOL WINAPI Module32Next( 
 HANDLE hSnapshot, 
 LPMODULEENTRY32 lpme 
);

/* Process32First  [function; shared; unified-kb; unified-kb] */
BOOL WINAPI Process32First( 
 HANDLE hSnapshot, 
 LPPROCESSENTRY32 lppe 
);

/* Process32Next  [function; shared; unified-kb; unified-kb] */
BOOL WINAPI Process32Next( 
 HANDLE hSnapshot, 
 LPPROCESSENTRY32 lppe 
);

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..399, 5.0..699 */

/* Heap32First  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Toolhelp.lib, toolhelp.lib] */
BOOL WINAPI Heap32First(
 HANDLE hSnapshot,
 LPHEAPENTRY32 lphe,
 DWORD th32ProcessID,
 DWORD th32HeapID
);

/* Heap32ListFirst  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Toolhelp.lib, toolhelp.lib] */
BOOL WINAPI Heap32ListFirst(
 HANDLE hSnapshot,
 LPHEAPLIST32 lphl
);

/* Heap32ListNext  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Toolhelp.lib, toolhelp.lib] */
BOOL WINAPI Heap32ListNext(
 HANDLE hSnapshot,
 LPHEAPLIST32 lphl
);

/* Heap32Next  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Toolhelp.lib, toolhelp.lib] */
BOOL WINAPI Heap32Next(
 HANDLE hSnapshot,
 LPHEAPENTRY32 lphe
);

/* Thread32First  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Toolhelp.lib, toolhelp.lib] */
BOOL WINAPI Thread32First(
 HANDLE hSnapshot,
 LPTHREADENTRY32 lpte
);

/* Thread32Next  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Toolhelp.lib, toolhelp.lib] */
BOOL WINAPI Thread32Next(
 HANDLE hSnapshot,
 LPTHREADENTRY32 lpte
);

/* Toolhelp32ReadProcessMemory  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Toolhelp.lib, toolhelp.lib] */
BOOL WINAPI Toolhelp32ReadProcessMemory(
 DWORD th32ProcessID,
 LPCVOID lpBaseAddress,
 LPVOID lpBuffer,
 DWORD cbRead,
 LPDWORD lpNumberOfBytesRead
);
#endif /* _WIN32_WCE */

#endif /* _TLHELP32_ */
