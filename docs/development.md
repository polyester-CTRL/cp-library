# Development and verification

Requirements: GCC and Clang with C++17, Bash, Python 3.11+, Git and network access.
No application server, CMake, or runtime dependencies are required.
From the repository root:

```sh
python3 -m venv .venv
. .venv/bin/activate
python -m pip install -r requirements-dev.txt
CXX=g++ bash scripts/test-unit.sh
CXX=clang++ bash scripts/test-unit.sh
git add include/cp verify/yosupo  # resolver discovers Git-managed files
bash scripts/verify.sh
python3 scripts/build-docs.py
```

The unit runner enables warnings as errors, tests constexpr and boundary behavior,
and links two translation units. It does not rely on assert/NDEBUG.
The verifier resolves `*.test.cpp` with the explicit TOML configuration and
uses Yosupo test data through online-judge-tools. `--check-error` propagates failures.
Do not treat skipped or undownloaded tests as passing. Generated result JSON and
build artifacts are ignored. Network access to GitHub, PyPI and judge.yosupo.jp
may be required; preserve TLS verification and configured proxy/CA settings.

The HTML generator uses Python's standard library, escapes source/document text,
and emits `site/index.html` plus `.nojekyll`; no Jekyll or external assets are used.
The CI workflow uploads this directory using the Pages artifact action. The deploy
job runs only on main after both compiler jobs and verification succeed; pull
requests never deploy. In Settings > Pages select Source: GitHub Actions. Ensure
Actions and Pages are enabled, and review the github-pages environment protection
rules. A local build does not prove remote deployment or Pages settings.

Add headers within the appropriate include/cp/ category; empty categories are
reserved with .gitkeep. Add tests under tests/unit and extend the runner as needed.
Add Yosupo programs under verify/yosupo with a PROBLEM macro and public includes.
Do not commit caches, downloaded judge data, binaries, or credentials.
