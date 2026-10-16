"""Tests for tools/header_map.py -- prefix / entity / library filing."""

import os
import sys
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                ".."))
import header_map  # noqa: E402


class ConstantHeaderTests(unittest.TestCase):
    def test_window_message(self):
        self.assertEqual(header_map.header_for_constant("WM_CREATE"),
                         "Winuser.h")

    def test_commctrl_notification_not_winuser(self):
        self.assertEqual(header_map.header_for_constant("LVN_BEGINDRAG"),
                         "Commctrl.h")
        self.assertEqual(header_map.header_for_constant("TVN_SELCHANGED"),
                         "Commctrl.h")

    def test_error_code(self):
        self.assertEqual(header_map.header_for_constant("ERROR_FILE_NOT_FOUND"),
                         "Winerror.h")

    def test_drawtext_not_modem(self):
        self.assertEqual(header_map.header_for_constant("DT_LEFT"),
                         "Winuser.h")
        self.assertIsNone(header_map.header_for_constant("DT_EXTERNAL_MODEM"))

    def test_button_vs_brush(self):
        self.assertEqual(header_map.header_for_constant("BS_PUSHBUTTON"),
                         "Winuser.h")
        self.assertEqual(header_map.header_for_constant("BS_SOLID"),
                         "Wingdi.h")

    def test_exact_hresult(self):
        self.assertEqual(header_map.header_for_constant("S_OK"), "Winerror.h")


class EntityHeaderTests(unittest.TestCase):
    def test_create_file(self):
        self.assertEqual(header_map.header_for_entity("CreateFile"),
                         "Winbase.h")

    def test_send_message(self):
        self.assertEqual(header_map.header_for_entity("SendMessage"),
                         "Winuser.h")

    def test_library(self):
        self.assertEqual(header_map.header_for_library("aygshell.lib"),
                         "Aygshell.h")
        self.assertIsNone(header_map.header_for_library("coredll.dll"))

    def test_enum_named_like_prefix(self):
        self.assertEqual(header_map.header_for_entity("CLSCTX", ["enum"]),
                         "Objbase.h")
        self.assertEqual(header_map.header_for_entity("ADVF", ["enum"]),
                         "Objidl.h")


if __name__ == "__main__":
    unittest.main()
