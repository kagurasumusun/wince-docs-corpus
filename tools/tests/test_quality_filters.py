"""Tests for tools/quality_filters.py."""

import os
import sys
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                ".."))
import quality_filters as q  # noqa: E402


class DefineTests(unittest.TestCase):
    def test_strips_html(self):
        line = q.sanitize_define_line(
            "#define MAKEINTRESOURCE(i) (LPTSTR) ((DWORD) ((WORD) (i))) </PRE>",
            "MAKEINTRESOURCE", "i",
            "(LPTSTR) ((DWORD) ((WORD) (i))) </PRE>")
        self.assertIsNotNone(line)
        self.assertNotIn("<", line)
        self.assertIn("MAKEINTRESOURCE", line)

    def test_missing_comma_between_params_is_broken(self):
        self.assertTrue(q.is_broken_c(
            "HRESULT CeOpenCallerBuffer(PVOID *ppDestMarshalled, PVOID pSrcUnmarshalled, "
            "DWORD cbSrc, DWORD ArgumentDescriptor BOOL ForceDuplicate);"))
        self.assertFalse(q.is_broken_c(
            "HANDLE GPSOpenDevice(HANDLE hNewLocationData, HANDLE hDeviceStateChange, "
            "const WCHAR *szDeviceName, DWORD dwFlags);"))

    def test_makelong_as_parameter_is_broken(self):
        self.assertTrue(q.is_broken_c(
            "void DateTime_SetMonthCalFont(HWND hwndDP, HFONT hFont, "
            "LPARAM MAKELONG(fRedraw, 0));"))

    def test_typedef_struct_glued_is_glued(self):
        self.assertTrue(q.is_glued_prototype("typedef_struct_RASENTRY { DWORD dwSize; }"))

    def test_message_crack_wparam_is_broken(self):
        self.assertTrue(q.is_broken_c(
            "TCM_REMOVEIMAGE | wParam = (WPARAM)(int) iImage;"))
        self.assertFalse(q.looks_like_c_declaration(
            "TCM_REMOVEIMAGE | wParam = (WPARAM)(int) iImage;"))

    def test_broken_assertmsg_define_dropped(self):
        self.assertIsNone(q.sanitize_define_line(
            "#define ASSERTMSG(\n message,\n Condition\n);",
            "ASSERTMSG", "message, Condition", ""))

    def test_rejects_sample_and_incomplete(self):
        self.assertIsNone(q.sanitize_define_line(
            "#define DEMO_COPY 1", "DEMO_COPY", "", "1"))
        self.assertIsNone(q.sanitize_define_line(
            "#define BOTTESINI \\", "BOTTESINI", "", "\\"))

    def test_keeps_windows_constant(self):
        line = q.sanitize_define_line(
            "#define WM_CREATE 0x0001", "WM_CREATE", "", "0x0001")
        self.assertEqual(line, "#define WM_CREATE 0x0001")

    def test_unassigned_keeps_api_style_only(self):
        self.assertTrue(q.is_keepable_unassigned_macro(
            "DMA_READ", "4", "#define DMA_READ 4"))
        self.assertFalse(q.is_keepable_unassigned_macro(
            "CARETHEIGHT", "15", "#define CARETHEIGHT 15"))
        self.assertFalse(q.is_keepable_unassigned_macro(
            "BLOCK_SIZE", "1000", "#define BLOCK_SIZE 1000"))


class DeclarationTests(unittest.TestCase):
    def test_rejects_assignment_snippet(self):
        self.assertFalse(q.looks_like_c_declaration(
            "pnmv = (NM_LISTVIEW FAR *) lParam;"))

    def test_accepts_prototype(self):
        self.assertTrue(q.looks_like_c_declaration(
            "LRESULT SendMessage(HWND hWnd, UINT Msg, "
            "WPARAM wParam, LPARAM lParam);"))

    def test_rejects_collapsed_prototype(self):
        self.assertFalse(q.looks_like_c_declaration(
            "BOOLCreateFile(LPCTSTRlpFileName);"))

    def test_rejects_sample_enum_name(self):
        self.assertIsNone(q.sanitize_declaration(
            "typedef enum myEnum { k=1 } myEnumv;", "myEnumv", "enum"))


class GluedPrototypeTests(unittest.TestCase):
    def test_handle_createfile_is_glued(self):
        self.assertTrue(q.is_glued_prototype(
            "HANDLECreateFile(LPCTSTRlpFileName);"))
        self.assertFalse(q.looks_like_c_declaration(
            "HANDLECreateFile(LPCTSTRlpFileName);"))

    def test_spaced_createfile_ok(self):
        self.assertFalse(q.is_glued_prototype(
            "HANDLE CreateFile(LPCTSTR lpFileName);"))
        self.assertTrue(q.looks_like_c_declaration(
            "HANDLE CreateFile(LPCTSTR lpFileName);"))

    def test_placeholder_types_unusable(self):
        self.assertTrue(q.decl_unusable_for_c(
            "PCHAR CONTAINING_RECORD(PCHAR Address, TYPE Type, PCHAR Field);",
            "CONTAINING_RECORD"))
        self.assertTrue(q.is_broken_c("InterlockedExchangeAdd(\n PLONG Addend,\n LONG Increment\n);"))
        self.assertFalse(q.is_broken_c("HCURSOR GetCursor(void)"))
        self.assertTrue(q.looks_like_c_declaration("HCURSOR GetCursor(void)"))

    def test_boolean_param_is_not_glued(self):
        text = ("PVOID MmMapIoSpace(PHYSICAL_ADDRESS PhysicalAddress, "
                "ULONG NumberOfBytes, BOOLEAN CacheEnable);")
        self.assertFalse(q.is_glued_prototype(text))
        self.assertTrue(q.looks_like_c_declaration(text))

    def test_array_bound_is_not_sal_unusable(self):
        self.assertFalse(q.decl_unusable_for_c(
            "typedef struct _WIN32_FIND_DATA {\n"
            " DWORD dwFileAttributes;\n TCHAR cFileName[MAX_PATH];\n"
            "} WIN32_FIND_DATA;", "WIN32_FIND_DATA"))
        self.assertFalse(q.decl_unusable_for_c(
            "typedef struct tagLOGFONT {\n LONG lfHeight;\n"
            " TCHAR lfFaceName[LF_FACESIZE];\n} LOGFONT;", "LOGFONT"))

    def test_missing_semicolon_port_proto_is_kept(self):
        text = "UCHAR READ_PORT_UCHAR ( PUCHAR Port )"
        self.assertFalse(q.is_broken_c(text))
        self.assertTrue(q.looks_like_c_declaration(text))

    def test_hungarian_arg_as_type_is_broken(self):
        self.assertTrue(q.is_broken_c(
            "int CALLBACK EnumFontsProc(lplf lplf, lptm lptm, DWORD dwType, LPARAM lpData);"))

    def test_interface_type_is_not_glued(self):
        text = ("BOOL HalTranslateBusAddress(INTERFACE_TYPE InterfaceType, "
                "ULONG BusNumber, PHYSICAL_ADDRESS BusAddress, "
                "PULONG AddressSpace, PPHYSICAL_ADDRESS TranslatedAddress);")
        self.assertFalse(q.is_glued_prototype(text))
        self.assertTrue(q.looks_like_c_declaration(text))

    def test_ularge_integer_is_not_glued(self):
        text = ("typedef struct ULARGE_INTEGER {\n"
                " ULONGLONG QuadPart;\n} ULARGE_INTEGER;")
        self.assertFalse(q.is_glued_prototype(text))
        self.assertTrue(q.looks_like_c_declaration(text))

    def test_internet_name_is_not_glued(self):
        text = ("typedef struct { DWORD dwResult; DWORD dwError; } "
                "INTERNET_ASYNC_RESULT, *LPINTERNET_ASYNC_RESULT;")
        self.assertFalse(q.is_glued_prototype(text))
        self.assertTrue(q.looks_like_c_declaration(text))

    def test_interface_is_not_int_glued(self):
        text = "typedef interface IFoo { void x; } IFoo;"
        self.assertFalse(q.is_glued_prototype(text))

    def test_int_glued_to_hungarian_is_glued(self):
        text = "int MulDiv( int nNumber,  intnNumerator,  intnDenominator);"
        self.assertTrue(q.is_glued_prototype(text))
        self.assertFalse(q.looks_like_c_declaration(text))

    def test_spaced_intdecl_ok(self):
        text = "int MulDiv(int nNumber, int nNumerator, int nDenominator);"
        self.assertFalse(q.is_glued_prototype(text))
        self.assertTrue(q.looks_like_c_declaration(text))

    def test_capital_t_typedef_is_kept(self):
        text = ("Typedef struct _tagCOMPOSITIONFORM { DWORD dwStyle; "
                "POINT ptCurrentPos; RECT rcArea; } COMPOSITIONFORM;")
        self.assertTrue(q.looks_like_c_declaration(text))

    def test_dotted_member_name_is_broken(self):
        self.assertTrue(q.is_broken_c(
            "typedef struct { DWORD cbSize.; HWND hwndLastFocus.; } SHACTIVATEINFO;"))
        self.assertTrue(q.is_broken_c(
            "typedef struct { UINT fSipUp.:1; } SHACTIVATEINFO;"))

    def test_outline_dash_body_is_broken(self):
        self.assertTrue(q.is_broken_c("typedef struct _numberfmt {- };"))
        self.assertTrue(q.is_broken_c("typedef struct _SYSTEM_INFO {- // mbi"))

    def test_nested_struct_missing_semi_is_broken(self):
        text = ("typedef struct _SYSTEM_INFO {\n DWORD dwOemId;\n"
                " struct {\n WORD wProcessorArchitecture;\n"
                " WORD wReserved;\n } \n DWORD dwPageSize;\n"
                "} SYSTEM_INFO, *LPSYSTEM_INFO;")
        self.assertTrue(q.is_broken_c(text))

    def test_formatmessage_va_list_is_usable(self):
        text = ("DWORD FormatMessage(DWORD dwFlags, LPCVOID lpSource, "
                "DWORD dwMessageId, DWORD dwLanguageId, LPTSTR lpBuffer, "
                "DWORD nSize, va_list *Arguments);")
        self.assertFalse(q.decl_unusable_for_c(text, "FormatMessage"))
        self.assertTrue(q.looks_like_c_declaration(text))

    def test_wsprintf_is_kept(self):
        text = "int wsprintf(LPTSTR lpOut, LPCTSTR lpFmt, ...);"
        self.assertTrue(q.looks_like_c_declaration(text))
        self.assertIsNotNone(q.sanitize_declaration(text, "wsprintf", "function"))


class ToolchainCTests(unittest.TestCase):
    def test_keeps_c_messagebox(self):
        text = ("int MessageBox(HWND hWnd, LPCTSTR lpText, "
                "LPCTSTR lpCaption, UINT uType);")
        self.assertTrue(q.is_c_toolchain_declaration(text, "MessageBox",
                                                     "function"))

    def test_drops_csharp_and_cpp(self):
        self.assertFalse(q.is_c_toolchain_declaration(
            "int MessageBoxW(int hWnd, String text, String caption, uint type);",
            "MessageBoxW", "function"))
        self.assertFalse(q.is_c_toolchain_declaration(
            "virtual HRESULT STDMETHODCALLTYPE GetFocusedElement("
            "IXRFrameworkElement** ppFocused) = 0;",
            "GetFocusedElement", "function"))
        self.assertTrue(q.is_cpp_or_managed(
            "void ShowScrollBar(BOOL bShow = TRUE);", "ShowScrollBar"))
        self.assertFalse(q.is_c_toolchain_declaration(
            "VOID WINAPI GetDC_I(HWND hwndThis);", "GetDC_I", "function"))
        self.assertTrue(q.is_cpp_or_managed(
            "int GetMenuString(UINT nIDItem, LPTSTR lpString, "
            "int nMaxCount, UINT nFlags) const;", "GetMenuString"))
        self.assertTrue(q.is_cpp_or_managed("operator LPCTSTR();", "LPCTSTR"))

    def test_drops_glued_struct_and_unbalanced(self):
        self.assertTrue(q.is_broken_c(
            "typedef struct_IMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY { ULONG x;"))
        self.assertTrue(q.is_broken_c(
            "BOOL SEC_ENTRY ( IN LPTSTR pszUser );"))
        self.assertFalse(q.is_broken_c(
            "typedef struct _RECT { LONG left; LONG top; } RECT;"))

    def test_keeps_c_enum_zero(self):
        text = ("typedef enum _BUS_DATA_TYPE { "
                "ConfigurationSpaceUndefined = -1, Cmos } BUS_DATA_TYPE;")
        self.assertTrue(q.is_c_toolchain_declaration(
            text, "BUS_DATA_TYPE", "enum"))


if __name__ == "__main__":
    unittest.main()
