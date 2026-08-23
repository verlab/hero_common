#!/bin/bash
set -e
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
PY="${ROOT}/.venv/bin/python"
if [ ! -x "$PY" ]; then
  PY=python3
fi
exec "$PY" "${ROOT}/scripts/genesis_engine.py" --vis --num-robots 20 --arena 0 --pattern circle --backend cpu --no-physics "$@"
