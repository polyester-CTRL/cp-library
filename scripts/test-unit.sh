#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
cxx="${CXX:-g++}"
mkdir -p build/unit
extra_flags=()
read -r -a extra_flags <<< "${CXXFLAGS:-}"
for test in tests/unit/add_test.cpp tests/unit/*.test.cpp; do
    name="$(basename "$test" .cpp)"
    "$cxx" -std=c++17 -O2 -Wall -Wextra -Werror -pedantic-errors -Iinclude "${extra_flags[@]}" \
        "$test" tests/unit/other.cpp -o "build/unit/$name"
    "build/unit/$name"
done
