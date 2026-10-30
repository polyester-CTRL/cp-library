#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
cxx="${CXX:-g++}"
mkdir -p build/unit
"$cxx" -std=c++17 -O2 -Wall -Wextra -Werror -pedantic-errors -Iinclude tests/unit/add_test.cpp tests/unit/other.cpp -o build/unit/add_test
build/unit/add_test
