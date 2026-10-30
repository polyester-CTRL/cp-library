# Contributing
Submit small, focused pull requests with original C++17 implementations.
By contributing you dedicate your contribution under CC0-1.0 (see LICENSE).
Do not transplant third-party implementations without reviewing permissions and
recording provenance. Dependencies in public headers should be standard C++ only.

Follow AGENTS.md. Each header needs include guards, namespace cp, self-contained
includes, preconditions and complexity documentation. Test boundaries and multiple
translation units; add a Yosupo verifier when a suitable problem exists.
See [development commands](docs/development.md). All CI checks must pass before merge.
