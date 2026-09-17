# Windows CE research log — 2026-09-18

## Purpose

Initial evidence collected while preparing the cross-repository Windows CE / LLVM agent instructions and implementation plan.

This file is an evidence index, not a claim that the entire Microsoft public Windows CE corpus has already been exhaustively reconciled. The implementation process must continue collecting and cross-checking sources until the coverage matrix is complete.

## Repository evidence

- `kagurasumusun/llvm-project`: default branch `LLVM-WinCE`; this is the compiler/toolchain/runtime side of the project.
- `kagurasumusun/cellvm-sdk`: default branch `main`; its Makefile identifies CE deployment checkpoints `0x420`, `0x500`, and `0x600` and enumerates a large Windows CE header set.
- `kagurasumusun/wince-docs-corpus`: current default branch is a generated/working branch; its README describes the corpus as Microsoft Learn/archived MSDN Windows CE 1.0–6.0 content.

## Primary Microsoft sources consulted

### Windows CE C run-time reference

1. `gets, _getws (Windows CE 5.0)`
   - Microsoft Learn archived Windows CE documentation.
   - Establishes CE-specific C run-time API behavior and versioned documentation.
   - https://learn.microsoft.com/en-us/previous-versions/windows/embedded/ms859647(v=msdn.10)

2. `malloc (Windows CE 5.0)`
   - Microsoft Learn archived Windows CE documentation.
   - Explicitly documents CE allocation semantics and the `coredll.dll` linkage.
   - https://learn.microsoft.com/en-us/previous-versions/windows/embedded/ms859665(v=msdn.10)

3. `setjmp (Windows CE 5.0)`
   - Microsoft Learn archived Windows CE documentation.
   - Documents CE availability from Windows CE 2.0 and the `stdlib.h` / `coredll.dll` interface.
   - https://learn.microsoft.com/en-us/previous-versions/windows/embedded/ms860366(v=msdn.10)

4. `getchar, getwchar (Windows CE 5.0)`
   - Microsoft Learn archived Windows CE documentation.
   - Documents CE availability and the `coredll.dll` linkage.
   - https://learn.microsoft.com/en-us/previous-versions/windows/embedded/ms859646(v=msdn.10)

5. `ungetc, ungetwc (Windows CE 5.0)`
   - Microsoft Learn archived Windows CE documentation.
   - Documents CE run-time behavior and support across CE C run-time versions.
   - https://learn.microsoft.com/en-us/previous-versions/windows/embedded/ms860479(v=msdn.10)

6. `memset, wmemset (Windows CE 5.0)`
   - Microsoft Learn archived Windows CE documentation.
   - Documents CE availability, header and `coredll.dll` linkage.
   - https://learn.microsoft.com/en-us/previous-versions/windows/embedded/ms859672(v=msdn.10)

### CE system-library model

7. `Mobilize: Explore The New Features In Windows Embedded CE 6.0`
   - Microsoft Learn / MSDN Magazine archive.
   - Documents CE 6.0 user/kernel system-library separation and identifies `coredll.dll` as the core user-mode system library.
   - https://learn.microsoft.com/en-us/archive/msdn-magazine/2006/december/mobilize-explore-the-new-features-in-windows-embedded-ce-6-0

8. `Windows CE: eMbedded Visual Tools 3.0 Provide a Flexible and Robust Development Environment`
   - Microsoft Learn / MSDN Magazine archive.
   - Describes the CE-specific DLL model and the difference from the desktop Windows DLL split.
   - https://learn.microsoft.com/en-us/archive/msdn-magazine/2001/january/windows-ce-embedded-visual-tools-3-0-provide-a-flexible-and-robust-development-environment

### CE safe-string API

9. `StringCbCopy`, `StringCbCopyEx`, `StringCchCopy`, `StringCchPrintf`, and related Windows CE 5.0 pages.
   - Microsoft Learn archived Windows CE documentation.
   - These pages explicitly identify CE version availability, header names and `strsafe.lib` linkage.
   - Example pages:
     - https://learn.microsoft.com/en-us/previous-versions/windows/embedded/ms860399(v=msdn.10)
     - https://learn.microsoft.com/en-us/previous-versions/windows/embedded/ms860400(v=msdn.10)
     - https://learn.microsoft.com/en-us/previous-versions/windows/embedded/ms860418(v=msdn.10)
     - https://learn.microsoft.com/en-us/previous-versions/windows/embedded/ms860433(v=msdn.10)

## LLVM sources consulted

10. LLVM libc++ platform documentation
    - Current libc++ documentation lists supported platforms and currently lists Windows 7+ rather than Windows CE.
    - https://libcxx.llvm.org/

11. LLVM libc++ vendor documentation
    - Describes current Windows/MinGW support assumptions for libc++.
    - https://libcxx.llvm.org/VendorDocumentation.html

12. LLVM libc++ Windows support design document
    - Describes assumptions of the current MSVC-mode Windows implementation, including VCRuntime/MSVC STL relationships.
    - This is useful as an implementation boundary reference, not as Windows CE API evidence.
    - https://libcxx.llvm.org/DesignDocs/WindowsSupport.html

13. LLVM libc platform support
    - States current platform-support scope and that Windows support is partial; it does not establish Windows CE support.
    - https://libc.llvm.org/platform_support.html

14. LLVM libc project overview
    - Describes LLVM libc as a separate C standard library implementation.
    - https://libc.llvm.org/

## Rules derived from the evidence

- Windows CE API ownership and availability must come from CE-specific Microsoft evidence.
- Desktop Windows API documentation is not a CE API specification.
- CE's system-library layout differs from desktop Windows; do not map CE symbols through a desktop CRT by name alone.
- Header and import-library ownership must be tracked independently.
- Generation/version requirements must be retained with each API record.
- LLVM libc++'s existing desktop Windows path is not evidence of CE support.
- `cellvm-sdk` must remain an interface/development package rather than an OS reimplementation.

## Next collection requirements

The following must be expanded before implementation is considered evidence-complete:

- complete CE 1.x–6.x API/header/library inventory;
- generation-specific differences for every symbol exposed by `cellvm-sdk`;
- architecture/ABI evidence for each supported LLVM target architecture;
- CE exception/unwind evidence;
- thread/TLS/atomic semantics;
- file/process/memory/synchronization APIs used by LLVM runtimes;
- C run-time coverage needed by libc++/compiler-rt/libunwind/libc++abi;
- complete import-library and DLL mapping;
- explicit evidence for any CE 7/8/Compact material that falls within the declared target scope, without merging it into earlier CE generations;
- CEGCC CE portions only as secondary cross-checks.
