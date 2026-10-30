# cp-library

Original, public-domain competitive programming library: C++17, header-only,
namespace `cp`, standard-library dependencies only. Licensed under [CC0-1.0](LICENSE).

```cpp
#include "cp/math/add.hpp"
static_assert(cp::add(2, 3) == 5);
```

Compile with `-std=c++17 -Iinclude`. The initial implementation is intentionally
limited to `cp::add` to validate infrastructure. Its sum must fit `std::int64_t`.

- `include/cp/{math,data_structure,graph,string,geometry,utility}/`: public headers
- `verify/yosupo/`: Library Checker verification programs
- `tests/unit/`: dependency-free unit tests
- [Build, verification and Pages setup](docs/development.md)
- [Contributing](CONTRIBUTING.md)

GitHub Actions tests GCC/Clang and runs competitive-verifier against Yosupo.
Static HTML documentation is deployed by the Pages workflow after successful CI
on main. Repository owners must select GitHub Actions as the Pages source.
