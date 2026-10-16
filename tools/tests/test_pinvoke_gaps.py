"""MIT pinvoke gap-fill: CE-named, still unnumbered, integer only."""

import os
import sys
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                ".."))
import pinvoke_gaps  # noqa: E402
import w32api_gaps  # noqa: E402


class PinvokeGapsTests(unittest.TestCase):
    def test_skips_unknown_and_max_path(self):
        out = pinvoke_gaps.parse_constants(
            {"MAX_PATH", "NOT_A_REAL_CONSTANT_XYZ"}, set())
        self.assertNotIn("MAX_PATH", out)
        self.assertNotIn("NOT_A_REAL_CONSTANT_XYZ", out)

    def test_skips_already_numbered(self):
        ce = {"WM_USER", "SW_HIDE"}
        already = {"WM_USER"}
        out = pinvoke_gaps.parse_constants(ce, already)
        self.assertNotIn("WM_USER", out)
        if "SW_HIDE" in out:
            self.assertRegex(out["SW_HIDE"]["value"],
                             r"^(0x[0-9A-Fa-f]+|-?\d+)[uUlL]*$")
            self.assertEqual(out["SW_HIDE"]["source"]["license"],
                             "dotnet-pinvoke-mit")

    def test_never_overlays_types(self):
        out = pinvoke_gaps.parse_constants(w32api_gaps.NEVER, set())
        for name in w32api_gaps.NEVER:
            self.assertNotIn(name, out)


if __name__ == "__main__":
    unittest.main()
