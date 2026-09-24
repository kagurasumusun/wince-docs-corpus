#!/usr/bin/env python3
"""Validate the corpus's structured source-level provenance records."""

import json
import re
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
RECORDS = ROOT / "data" / "sources" / "archive-sources.json"
REQUIRED = {
    "id", "archive_path", "provenance_path", "source_kind", "publisher",
    "source_locator", "source_artifact", "version_scope", "architecture_scope",
    "toolchain_scope", "access_recorded_at", "evidence_status", "authority",
    "independence", "directness", "confidence", "rights_status", "applicability",
    "known_limitations",
}
ENUMS = {
    "source_kind": {"archived_official_media", "official_download_archive"},
    "evidence_status": {"documented", "observed", "reproduced", "inferred",
                        "hypothesized", "contradicted", "unknown"},
    "authority": {"primary", "secondary", "community", "unknown"},
    "independence": {"independent", "derived", "unknown"},
    "directness": {"direct", "indirect", "unknown"},
    "confidence": {"high", "medium", "low", "unknown"},
    "rights_status": {"rights_unknown", "likely_permitted_but_verify",
                      "permission_required", "counsel_review",
                      "cleared_with_conditions", "cleared_for_intended_use"},
}


def fail(message):
    print(f"ERROR: {message}", file=sys.stderr)
    return 1


def main():
    try:
        document = json.loads(RECORDS.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as error:
        return fail(f"cannot read {RECORDS}: {error}")

    if document.get("schema_version") != 1:
        return fail("schema_version must be 1")
    records = document.get("records")
    if not isinstance(records, list) or not records:
        return fail("records must be a non-empty array")

    ids = set()
    errors = 0
    for position, record in enumerate(records, start=1):
        label = f"record {position}"
        missing = REQUIRED - record.keys()
        if missing:
            errors += fail(f"{label} lacks required fields: {', '.join(sorted(missing))}")
            continue
        if record["id"] in ids:
            errors += fail(f"duplicate id: {record['id']}")
        ids.add(record["id"])
        if not re.fullmatch(r"[a-z0-9]+(?:-[a-z0-9]+)*", record["id"]):
            errors += fail(f"{label} has a non-canonical id")
        for key, values in ENUMS.items():
            if record[key] not in values:
                errors += fail(f"{record['id']}: invalid {key}: {record[key]!r}")
        for key in ("version_scope", "architecture_scope", "toolchain_scope", "known_limitations"):
            if not isinstance(record[key], list) or not record[key] or not all(
                    isinstance(value, str) and value.strip() for value in record[key]):
                errors += fail(f"{record['id']}: {key} must be a non-empty string array")
        if not re.fullmatch(r"\d{4}-\d{2}-\d{2}", record["access_recorded_at"]):
            errors += fail(f"{record['id']}: access_recorded_at must be YYYY-MM-DD")
        if not record["source_locator"].startswith("https://"):
            errors += fail(f"{record['id']}: source_locator must use HTTPS")
        for key in ("archive_path", "provenance_path"):
            path = ROOT / record[key]
            if not path.exists():
                errors += fail(f"{record['id']}: missing {key}: {record[key]}")

    if errors:
        return 1
    print(f"OK: {len(records)} source records validated")
    return 0


if __name__ == "__main__":
    sys.exit(main())
