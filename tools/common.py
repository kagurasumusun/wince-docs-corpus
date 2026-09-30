"""Shared layout constants and classification rules (single source of truth).

Repository layout rules (see docs/LAYOUT.md):
  corpus/<source-kind>/<product-or-capture>/<page-id>.html   harvested content
  meta/                                                      derived / descriptive data
  queues/                                                    URL work lists
  sources/                                                   scope definition (what to collect)
  tools/                                                     all code
"""
import os
import re
import subprocess
import urllib.parse

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

CORPUS = "corpus"
LEARN_DIR = f"{CORPUS}/learn"            # learn.microsoft.com previous-versions pages
WAYBACK_DIR = f"{CORPUS}/wayback"        # web.archive.org captures -> wayback/<host>-<yyyy>-<mm>/
CHM_DIR = f"{CORPUS}/chm-extracted"      # pages extracted from official CHM/HLP
ARCHIVE_DIR = f"{CORPUS}/archives"       # original binary documentation media
META = "meta"
QUEUES = "queues"
HARVEST_META = f"{META}/harvest"

TITLE_RE = re.compile(r"<title>(.*?)</title>", re.S | re.I)


def abspath(rel):
    return os.path.join(ROOT, rel)


def clean_title(t):
    return re.sub(r"\s*\|\s*Microsoft Learn\s*$", "", (t or "").strip())


# ---------------------------------------------------------------------------
# Product classification for Microsoft Learn "previous-versions" pages.
# First match wins; order matters. value None => Windows Mobile (version parsed).
# ---------------------------------------------------------------------------
PRODUCT_RULES = (
    (r"\(Windows CE \.NET[^)]*\)", "windows-ce-net-4x"),
    (r"\(Windows CE 5\.0\)", "windows-ce-5.0"),
    (r"\(Windows CE 4\.[0-2]\)", "windows-ce-net-4x"),
    (r"\(Windows CE 3\.0[^)]*\)", "windows-ce-3.0"),
    (r"\(Windows CE 2\.[0-9]+[^)]*\)", "windows-ce-2.x"),
    (r"\(Windows Embedded CE 6\.0[^)]*\)", "windows-embedded-ce-6.0"),
    (r"\(Microsoft\.RemoteToolSdk[^)]*\)", "windows-embedded-ce-6.0"),
    (r"\(Compact 7\)|\(Windows Embedded Compact 7[^)]*\)", "windows-embedded-compact-7"),
    (r"\(Compact 2013\)|\(Windows Embedded Compact 2013[^)]*\)", "windows-embedded-compact-2013"),
    (r"\(Windows Mobile[^)]*\)", None),
    (r"\(Pocket PC[^)]*\)", "pocket-pc"),
    (r"\(Smartphone[^)]*\)", "smartphone"),
    (r"\(Handheld PC[^)]*\)", "handheld-pc"),
    (r"\(Palm-size PC[^)]*\)", "palm-size-pc"),
    (r"\(Auto PC[^)]*\)", "auto-pc"),
    (r"\(SQL Server (?:Compact|CE)[^)]*\)", "sql-server-compact"),
    (r"\(eMbedded Visual[^)]*\)", "embedded-visual-tools"),
    (r"\((?:System|Microsoft)(?:\.[A-Za-z0-9_.]+)?\)$", "dotnet-compact-framework"),
    (r"\((?:Ws|Dpws|Microsoft\.SPOT)(?:\.[A-Za-z0-9_.]+)?\)$", "dotnet-micro-framework"),
    (r"\((?:[A-Za-z0-9_.]+ (?:Method|Property|Constructor|Field|Event|Class|"
     r"Structure|Interface|Enumeration|Delegate))$", "dotnet-compact-framework"),
)
BODY_MARKERS = (
    ("windows-ce-5.0", "Windows CE 5.0"),
    ("windows-embedded-ce-6.0", "Windows Embedded CE 6.0"),
    ("windows-ce-net-4x", "Windows CE .NET"),
    ("windows-embedded-compact-7", "Windows Embedded Compact 7"),
    ("windows-embedded-compact-2013", "Windows Embedded Compact 2013"),
)
_VER_TAG = re.compile(r'rel="canonical" href="[^"]*?\(v=([^)]+)\)"')


def classify(title, head):
    """Map a Learn page (title + first ~16KB of HTML) to a product directory."""
    title = clean_title(title)
    for pattern, bucket in PRODUCT_RULES:
        if not re.search(pattern, title):
            continue
        if bucket is not None:
            return bucket
        wm = re.search(r"\(Windows Mobile ([0-9.]+)", title)
        return "windows-mobile-" + wm.group(1) if wm else "windows-mobile"
    best, best_i = None, 1 << 60
    for bucket, marker in BODY_MARKERS:
        i = head.find(marker)
        if 0 <= i < best_i:
            best, best_i = bucket, i
    if best:
        return best
    m = _VER_TAG.search(head)
    if m and m.group(1).startswith("vs.102") and re.search(r"\((?:Ws|Dpws)\.", title):
        return "dotnet-micro-framework"
    return "unclassified"


# ---------------------------------------------------------------------------
# URL -> (kind, page_id, extra)
# ---------------------------------------------------------------------------
LEARN_PATH = re.compile(r"/previous-versions/(?:windows/embedded|windows/mobile|[^/]+(?:/[^/]+)*)/"
                        r"([A-Za-z0-9_.\-]+)(?:\(v=([A-Za-z0-9.]+)\))?$")
WB_PATH = re.compile(
    r"^/web/(\d{4})(\d{2})\d*(?:id_)?/https?://(msdn\.microsoft\.com)/[a-z\-]+/library/"
    r"([A-Za-z0-9_.\-]+?)(?:\(v=([A-Za-z0-9.]+)\))?(?:\.aspx)?$")


def dest_for(url):
    """Return (kind, page_id, extra) or (None, None, None).

    kind 'learn'   extra = version tag or ''
    kind 'wayback' extra = 'YYYY-MM' capture month
    """
    p = urllib.parse.urlparse(url)
    if p.netloc.endswith("learn.microsoft.com"):
        last = urllib.parse.unquote(p.path.rstrip("/").split("/")[-1])
        m = re.match(r"([A-Za-z0-9_.\-]+)\(v=([A-Za-z0-9.]+)\)$", last)
        if not m:
            return None, None, None
        return "learn", m.group(1).lower(), m.group(2)
    if p.netloc == "web.archive.org":
        m = WB_PATH.match(urllib.parse.unquote(p.path))
        if not m:
            return None, None, None
        return "wayback", m.group(4).lower(), f"{m.group(1)}-{m.group(2)}"
    return None, None, None


def list_tracked(*subdirs):
    """Return tracked file paths under subdirs using git (works without checkout)."""
    try:
        out = subprocess.run(
            ["git", "-C", ROOT, "ls-tree", "-r", "--name-only", "-z", "HEAD", "--", *subdirs],
            check=True, capture_output=True).stdout.decode("utf-8", "replace")
        return [x for x in out.split("\0") if x]
    except (subprocess.CalledProcessError, OSError):
        paths = []
        for sd in subdirs:
            for r, _, fs in os.walk(abspath(sd)):
                paths += [os.path.relpath(os.path.join(r, f), ROOT) for f in fs]
        return paths


def build_have_index():
    """Set of already-harvested ids: 'pid' for learn, 'wb:pid' for wayback.

    Uses `git ls-tree` so a sparse / blobless checkout is enough (no 3.4GB checkout).
    """
    have = set()
    for p in list_tracked(LEARN_DIR, WAYBACK_DIR, CHM_DIR):
        parts = p.split("/")
        if not parts[-1].endswith(".html"):
            continue
        base = parts[-1][:-5]
        if parts[1] == "learn":
            have.add(base.lower())
            i = base.find("(v=")
            if i > 0:
                have.add(base[:i].lower())
        elif parts[1] == "wayback":
            have.add("wb:" + base.lower())
    return have
