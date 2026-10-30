#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
competitive-verifier oj-resolve --config .competitive-verifier/config.toml --include verify/yosupo > .competitive-verifier/verify_files.json
python3 - <<'CHECK'
import json
from pathlib import Path
files = json.loads(Path('.competitive-verifier/verify_files.json').read_text())['files']
if not any(f.get('verification') for f in files.values()):
    raise SystemExit('No verification targets; git add verify/yosupo first')
CHECK
competitive-verifier verify --verify-json .competitive-verifier/verify_files.json --check-error --output .competitive-verifier/result.json
