#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"
PIO="${ROOT}/.venv/bin/pio"
if [[ ! -x "$PIO" ]]; then
  echo "PlatformIO belum terpasang di venv proyek ini." >&2
  echo "Jalankan sekali:" >&2
  echo "  cd \"$ROOT\" && python3 -m venv .venv && .venv/bin/pip install -r requirements.txt" >&2
  exit 1
fi
"$PIO" run "$@"
"$PIO" run -t compiledb
