"""gcc -fsyntax-only of a tiny CE app and driver against winsur/include."""

import os
import shutil
import subprocess
import tempfile
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(
    os.path.abspath(__file__))))
INCLUDE = os.path.join(ROOT, "winsur", "include")

APP = r'''
#define _WIN32_WCE 0x500
#include "Windows.h"
int WINAPI WinMain(HINSTANCE h, HINSTANCE p, LPWSTR cmd, int show) {
    MSG m;
    RECT r;
    PAINTSTRUCT ps;
    HANDLE f = CreateFile(TEXT("x"), GENERIC_READ, 0, NULL,
                          OPEN_EXISTING, 0, NULL);
    DWORD n = 0;
    ReadFile(f, &n, sizeof n, &n, NULL);
    WriteFile(f, &n, sizeof n, &n, NULL);
    GetMessage(&m, NULL, 0, 0);
    PeekMessage(&m, NULL, 0, 0, 0);
    BeginPaint(NULL, &ps);
    EndPaint(NULL, &ps);
    MessageBox(NULL, TEXT("hi"), TEXT("t"), 0);
    GetLastError();
    InitializeCriticalSection(NULL);
    Sleep(0);
    LoadLibrary(TEXT("x"));
    CreateProcess(NULL, TEXT("x"), NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL);
    FindFirstFile(TEXT("x"), NULL);
    SetTimer(NULL, 1, 0, NULL);
    CreateFontIndirect(NULL);
    SelectPalette(NULL, NULL, FALSE);
    CreateDIBSection(NULL, NULL, 0, NULL, NULL, 0);
    StretchDIBits(NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0);
    GetOpenFileName(NULL);
    ChooseColor(NULL);
    AppendMenu(NULL, 0, 0, NULL);
    CreateDialogParam(NULL, NULL, NULL, NULL, 0);
    EnumWindows(NULL, 0);
    EnumFontFamilies(NULL, NULL, NULL, 0);
    GetCommState(NULL, NULL);
    GetStoreInformation(NULL);
    GetDiskFreeSpaceEx(NULL, NULL, NULL, NULL);
    GetCommTimeouts(NULL, NULL);
    SetCommTimeouts(NULL, NULL);
    GetScrollInfo(NULL, 0, NULL);
    SetScrollInfo(NULL, 0, NULL, 0);
    BeginPaint(NULL, NULL);
    EndPaint(NULL, NULL);
    VirtualQuery(NULL, NULL, 0);
    GetCharABCWidths(NULL, 0, 0, NULL);
    GetObject(NULL, 0, NULL);
    SetEvent(NULL);
    ResetEvent(NULL);
    GetCurrentThread();
    GetCurrentProcess();
    {
        BLENDFUNCTION bf;
        bf.BlendOp = 0;
        bf.BlendFlags = 0;
        bf.SourceConstantAlpha = 0;
        bf.AlphaFormat = 0;
        AlphaBlend(NULL, 0, 0, 0, 0, NULL, 0, 0, 0, 0, bf);
    }
    DebugBreak();
    SetFilePointer(NULL, 0, NULL, 0);
    CommDlgExtendedError();
    RedrawWindow(NULL, NULL, NULL, 0);
    ExtTextOut(NULL, 0, 0, 0, NULL, NULL, 0, NULL);
    RegCopyFile(NULL);
    GetSystemInfo(NULL);
    FindCloseUrlCache(NULL);
    GetACP();
    GetOEMCP();
    IsDBCSLeadByte(0);
    IsDBCSLeadByteEx(0, 0);
    CreateToolhelp32Snapshot(0, 0);
    Process32First(NULL, NULL);
    SHGetSpecialFolderPath(NULL, NULL, 0, 0);
    PlaySound(NULL, NULL, 0);
    sndPlaySound(NULL, 0);
    timeGetTime();
    waveOutGetNumDevs();
    SHFullScreen(NULL, 0);
    OpenStore(NULL);
    FormatStore(NULL);
    FindCloseStore(NULL);
    CeSetUserNotification(NULL, NULL, NULL, NULL);
    WriteDebugLED(0, 0);
    AdjustWindowRectEx(NULL, 0, 0, 0);
    GetDoubleClickTime();
    IsFirewallEnabled(0);
    GetSystemPowerState(NULL, 0, NULL);
    SipShowIM(0);
    InitHTMLControl(NULL);
    GetServiceHandle(NULL, NULL, 0);
    ConnMgrApiReadyEvent();
    GPSOpenDevice(NULL, NULL, NULL, 0);
    GetDeviceUniqueID(NULL, 0, 1, NULL, NULL);
    CredFree(NULL);
    phoneConfigDialog(0, NULL, NULL);
    return 0;
}
'''

DRV = r'''
#define _WIN32_WCE 0x500
#include "Windows.h"
#include "CEDDK.h"
BOOL APIENTRY DllMain(HANDLE h, DWORD reason, LPVOID reserved) {
    PHYSICAL_ADDRESS a;
    a.QuadPart = 0;
    MmMapIoSpace(a, 0, FALSE);
    MmUnmapIoSpace(NULL, 0);
    HalGetBusData(0, 0, 0, NULL, 0);
    READ_PORT_UCHAR(NULL);
    WRITE_PORT_UCHAR(NULL, 0);
    return TRUE;
}
'''


@unittest.skipUnless(shutil.which("gcc"), "gcc not installed")
@unittest.skipUnless(os.path.isdir(INCLUDE), "winsur/include not generated")
class CompileSurfaceTests(unittest.TestCase):
    def _cc(self, source):
        with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False) as fh:
            fh.write(source)
            path = fh.name
        try:
            r = subprocess.run(
                ["gcc", "-fsyntax-only", "-std=c11", "-w",
                 "-Werror=implicit-function-declaration",
                 "-I", INCLUDE, "-D_WIN32_WCE=0x500", path],
                capture_output=True, text=True)
            self.assertEqual(r.returncode, 0, r.stderr)
        finally:
            os.unlink(path)

    def test_app(self):
        self._cc(APP)

    def test_driver(self):
        self._cc(DRV)


if __name__ == "__main__":
    unittest.main()
