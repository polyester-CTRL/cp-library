# cp-library

Original, public-domain competitive programming library: C++17, header-only,
namespace `cp`, standard-library dependencies only. Licensed under [CC0-1.0](LICENSE).

```cpp
#include "cp/math/add.hpp"
static_assert(cp::add(2, 3) == 5);
```

Compile with `-std=c++17 -Iinclude`. `cp::add` requires its sum to fit `std::int64_t`.
[DSU (Union Find)](docs/data_structure/dsu.md) provides `merge`, `same`, and `size`
in amortized O(α(n)) time.

- `include/cp/{math,data_structure,graph,string,geometry,utility}/`: public headers
- `verify/yosupo/`: Library Checker verification programs
- `tests/unit/`: dependency-free unit tests
- [Build, verification and Pages setup](docs/development.md)
- [Contributing](CONTRIBUTING.md)

GitHub Actions tests GCC/Clang and runs competitive-verifier against Yosupo.
Static HTML documentation is deployed by the Pages workflow after successful CI
on main. Repository owners must select GitHub Actions as the Pages source.
