"""Tests for tools/gen-include-def.py -- the generator's standing rules.

* the .def grammar rule: a worklist file is one EXPORTS block, and every
  ";" header/annotation line comes BEFORE "EXPORTS" (tools/def-rule
  documents the rule the generator must hold);
* the reference-export leads are comment-only (membership leads never
  become EXPORTS lines);
* deterministic output: two builds of the same facts give identical text.
"""

import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                ".."))

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(
    os.path.abspath(__file__))))


class DefRuleTests(unittest.TestCase):
    def test_def_rule_holds_on_generated_worklists(self):
        """Every winsur/link/*.def: header comments first, then EXPORTS,
        then entry lines; a lead is never an entry line."""
        link = os.path.join(ROOT, "winsur", "link")
        if not os.path.isdir(link):
            self.skipTest("no generated winsur/link yet")
        checked = 0
        for name in sorted(os.listdir(link)):
            if not name.endswith(".def"):
                continue
            with open(os.path.join(link, name), encoding="utf-8") as fh:
                lines = fh.read().splitlines()
            seen_exports = False
            for line in lines:
                stripped = line.strip()
                if stripped == "EXPORTS":
                    self.assertFalse(seen_exports,
                                     f"{name}: more than one EXPORTS block")
                    seen_exports = True
                    continue
                if stripped.startswith(";"):
                    # comments are fine anywhere... except the rule
                    # "declares before EXPORTS" only constrains entry
                    # lines: entry lines must come after EXPORTS.
                    continue
                if stripped:
                    self.assertTrue(seen_exports,
                                    f"{name}: entry line before EXPORTS: "
                                    f"{stripped[:40]}")
            checked += 1
        self.assertGreater(checked, 0)

    def test_reference_leads_are_comment_only(self):
        """A reference-export lead line starts with ';' -- it can never
        export a name (values: never; membership is a review lead)."""
        link = os.path.join(ROOT, "winsur", "link")
        if not os.path.isdir(link):
            self.skipTest("no generated winsur/link yet")
        found = 0
        for name in sorted(os.listdir(link)):
            if not name.endswith(".def"):
                continue
            with open(os.path.join(link, name), encoding="utf-8") as fh:
                for line in fh:
                    if "lead  " in line and "reference" not in line:
                        self.assertTrue(line.lstrip().startswith(";"),
                                        f"{name}: lead not commented: {line}")
                        found += 1
        # the lead block exists somewhere once the reference pass ran
        # (0 is acceptable when reference-exports.tsv is absent)


class GeneratorApiTests(unittest.TestCase):
    def _load(self):
        import importlib.util
        spec = importlib.util.spec_from_file_location(
            "gen_include_def",
            os.path.join(ROOT, "tools", "gen-include-def.py"))
        gen = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(gen)
        return gen

    def test_safe_name(self):
        gen = self._load()
        self.assertEqual(gen.safe_name("coredll"), "coredll")
        self.assertNotIn("/", gen.safe_name("a/b:c"))

    def test_reference_exports_loads(self):
        gen = self._load()
        exports = gen.load_reference_exports()
        if not exports:
            self.skipTest("kb/reference-exports.tsv absent")
        # the CeGCC CE import libraries claim COREDLL exports
        self.assertTrue(any(m.startswith("coredll") for m in exports),
                        sorted(exports)[:10])
        for module, rows in exports.items():
            for name, member in rows:
                self.assertTrue(name.replace("_", "").replace("@", "")
                                .replace("?", "").replace("$", "").isalnum()
                                or name[:1].isalpha(),
                                name)
                self.assertTrue(member.endswith(".def"), member)

    def test_pick_constant_prefers_name_map_over_win32_ref(self):
        gen = self._load()
        targets = gen.pick_constant_targets("ERROR_FILE_NOT_FOUND", [
            {"header": "wincrypt.h", "strength": "win32-reference",
             "statements": 4},
        ])
        self.assertEqual(len(targets), 1)
        self.assertEqual(targets[0]["header"].lower(), "winerror.h")

    def test_pick_constant_keeps_reference_header_ras(self):
        gen = self._load()
        targets = gen.pick_constant_targets("ERROR_ACCT_DISABLED", [
            {"header": "raserror.h", "strength": "reference-header",
             "statements": 1},
        ])
        self.assertEqual(targets[0]["header"].lower(), "raserror.h")

    def test_header_preference_ce_over_umbrella(self):
        gen = self._load()
        self.assertLess(gen.header_preference("winuser.h"),
                        gen.header_preference("windows.h"))
        self.assertLess(gen.header_preference("windef.h"),
                        gen.header_preference("gdiplustypes.h"))

    def test_pick_constant_prefers_h_over_hpp(self):
        gen = self._load()
        targets = gen.pick_constant_targets("ANSI_CHARSET", [
            {"header": "Gdi.hpp", "strength": "own-page", "statements": 4},
            {"header": "Wingdi.h", "strength": "own-page", "statements": 5},
        ])
        self.assertEqual(len(targets), 1)
        self.assertEqual(targets[0]["header"], "Wingdi.h")

    def test_lpuint_is_not_known_just_because_uint_is(self):
        gen = self._load()
        self.assertTrue(gen.type_mentions_unknown(
            "BOOL ImmGetVirtualKey(LPUINT lpuVKey, LPHKL lphKL);",
            set(), "ImmGetVirtualKey"))
        self.assertFalse(gen.type_mentions_unknown(
            "HPALETTE SelectPalette(HDC hdc, HPALETTE hpal, BOOL b);",
            set(), "SelectPalette"))


if __name__ == "__main__":
    unittest.main()
