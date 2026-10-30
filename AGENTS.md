# Contributor instructions
Use C++17, header-only implementations under include/cp/, and namespace cp.
Use only standard C++ library dependencies in public headers. Headers must be
self-contained and safe in multiple translation units. Write original implementations;
do not copy third-party code without explicit compatible permission and provenance.
Contributions are dedicated under CC0-1.0. Document preconditions, complexity,
indexing, and overflow behavior. Add unit and Yosupo tests for new algorithms.
Run CXX=g++ bash scripts/test-unit.sh, CXX=clang++ bash scripts/test-unit.sh,
and bash scripts/verify.sh. Report blocked or failed checks honestly.
Use the existing checkout; do not create worktrees unless requested.
Commit identity: polyester <56536708+polyester-CTRL@users.noreply.github.com>.
