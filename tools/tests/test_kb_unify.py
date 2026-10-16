"""Tests for the unified-KB chooser (CE value, not code-page columns)."""

import os
import sys
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                ".."))

import kb_unify  # noqa: E402
import page_parse  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(
    os.path.abspath(__file__))))


class ChooseConstantTests(unittest.TestCase):
    def test_charset_drops_code_page(self):
        records = [
            {"name": "ANSI_CHARSET", "value": "1252", "layer": "ce",
             "origin": "table"},
            {"name": "ANSI_CHARSET", "value": "0", "layer": "ce",
             "origin": "table"},
        ]
        value, layer, origin, discarded = kb_unify.choose_constant_value(records)
        self.assertEqual(str(value), "0")
        self.assertEqual(layer, "ce")
        self.assertTrue(any(d["reason"] == "code-page-column" for d in discarded))

    def test_ce_beats_win32(self):
        records = [
            {"name": "SOME_FLAG", "value": "2", "layer": "win32",
             "origin": "table"},
            {"name": "SOME_FLAG", "value": "1", "layer": "ce",
             "origin": "table"},
        ]
        value, layer, _, _ = kb_unify.choose_constant_value(records)
        self.assertEqual(str(value), "1")
        self.assertEqual(layer, "ce")

    def test_win32_fills_gap(self):
        records = [
            {"name": "WM_CREATE", "value": "0x0001", "layer": "win32",
             "origin": "define"},
        ]
        value, layer, _, _ = kb_unify.choose_constant_value(records)
        self.assertEqual(value, "0x0001")
        self.assertEqual(layer, "win32")

    def test_resolved_value_wins(self):
        records = [
            {"name": "NERR_DCNotFound", "value": "243", "layer": "ce",
             "origin": "table"},
            {"name": "NERR_DCNotFound", "value": "2453", "layer": "ce",
             "origin": "table"},
        ]
        value, _, _, _ = kb_unify.choose_constant_value(records, resolved="2453")
        self.assertEqual(str(value), "2453")

    def test_header_map_beats_wrong_file(self):
        header = kb_unify.choose_header(
            "ERROR_FILE_NOT_FOUND", ["wincrypt.h", "Winerror.h"])
        self.assertEqual(header.lower(), "winerror.h")


class KeepableValueTests(unittest.TestCase):
    def test_ctor_expression_kept(self):
        self.assertTrue(kb_unify.is_keepable_constant_value(
            "MAKE_D3DMHRESULT(2158)"))
        self.assertTrue(kb_unify.is_keepable_constant_value("RASBASE+1"))
        self.assertTrue(kb_unify.is_keepable_constant_value("0x0001"))

    def test_null_one_is_not_c_null(self):
        records = [
            {"name": "NULL", "value": "1", "layer": "ce", "origin": "table"},
        ]
        value, _, _, _ = kb_unify.choose_constant_value(records)
        self.assertIsNone(value)

    def test_sample_body_dropped(self):
        self.assertFalse(kb_unify.is_keepable_constant_value(
            "sizeof (hArray) / sizeof (HANDLE)"))
        self.assertFalse(kb_unify.is_keepable_constant_value(
            "(memset((</B><I>pguid</I><B>), -1, sizeof(CEGUID)))"))


class SyntaxDefineExpressionTests(unittest.TestCase):
    def test_d3dmerr_ctor_defines(self):
        path = os.path.join(
            ROOT, "corpus/chm/windows-ce-5.0/wced3dm5/html/"
            "wce50lrfDirect3DMobileErrorCodes.html")
        if not os.path.exists(path):
            raise unittest.SkipTest("D3DMERR page not committed")
        frag = page_parse.article_html(open(path, "rb").read())
        decls = page_parse.declarations(frag, page_title="D3DMERR Values")
        rows = page_parse.syntax_constant_rows(decls)
        out = {r["name"]: r.get("value") for r in rows}
        self.assertGreaterEqual(len(out), 20, sorted(out)[:10])
        self.assertEqual(out.get("D3DMERR_ALREADYLOCKED"),
                         "MAKE_D3DMHRESULT(2158)")
        self.assertEqual(out.get("D3DMERR_NOTFOUND"),
                         "MAKE_D3DMHRESULT(2150)")


class CorrespondenceTableTests(unittest.TestCase):
    def test_code_page_column_is_not_the_value(self):
        html = """
        <table>
        <tr><th>Character set</th><th>Value</th><th>Code page</th></tr>
        <tr><td>ANSI_CHARSET</td><td>0</td><td>1252</td></tr>
        <tr><td>DEFAULT_CHARSET</td><td>1</td><td>0</td></tr>
        </table>
        """
        rows = page_parse.constant_tables(html)
        out = {r["name"]: r.get("value") for r in rows}
        self.assertEqual(out.get("ANSI_CHARSET"), "0")
        self.assertNotEqual(out.get("ANSI_CHARSET"), "1252")

    def test_code_page_only_table_is_skipped(self):
        html = """
        <table>
        <tr><th>Character Sets</th><th>Code Pages</th><th>Font Signature</th></tr>
        <tr><td>ANSI_CHARSET</td><td>1252</td><td>FS_LATIN1</td></tr>
        </table>
        """
        rows = page_parse.constant_tables(html)
        names = {r["name"] for r in rows}
        self.assertNotIn("ANSI_CHARSET", names)


if __name__ == "__main__":
    unittest.main()
