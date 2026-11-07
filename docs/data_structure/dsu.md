# DSU (Union Find)

`cp::dsu` maintains disjoint sets of vertices indexed from `0` to `n - 1`.
Include `cp/data_structure/dsu.hpp`. The implementation is original C++17,
header-only, self-contained, safe in multiple translation units, and dedicated
under CC0-1.0 (see [LICENSE](../../LICENSE)). Only standard headers are required.

```cpp
#include "cp/data_structure/dsu.hpp"

int main() {
    cp::dsu uf(5);
    bool joined = uf.merge(0, 3);  // true
    bool again = uf.merge(3, 0);  // false
    bool connected = uf.same(0, 3);  // true
    int count = uf.size(3);  // 2
    return joined && !again && connected && count == 2 ? 0 : 1;
}
```

Compile with `g++ -std=c++17 -Iinclude example.cpp` (or `clang++`).

| API | Result | Time |
| --- | --- | --- |
| `explicit dsu(int n = 0)` | Construct `n` singleton components | O(n) |
| `bool merge(int a, int b)` | Join the components; return true iff they were different | Amortized O(α(n)) |
| `bool same(int a, int b)` | Whether the vertices belong to the same component | Amortized O(α(n)) |
| `int size(int a)` | Number of vertices in the component containing `a` | Amortized O(α(n)) |

Construction requires `0 <= n <= INT_MAX` and enough memory for `n` integers.
An empty DSU is valid, but no vertex operation is valid on it. Every vertex
argument must satisfy `0 <= vertex < n`. Debug assertions check these
preconditions; violating them is unsupported when assertions are disabled.
Allocation failures propagate from `std::vector`.

Union by Size attaches the smaller tree to the larger one. Iterative full Path
Compression rewrites every traversed parent to the root. A sequence of operations
costs amortized O(α(n)) per operation; an individual operation can take O(log n).
Storage is O(n), with O(1) auxiliary space per operation. Queries also compress
paths, so `same` and `size` are non-const. Self merges and repeated merges return
false and preserve component sizes. There is no deletion or rollback operation.

Roots store negative component sizes in an `int`; other entries store parent
indices. A component size is at most `n <= INT_MAX`, so size addition and negation
are representable. The class does not promise support for more than `INT_MAX`
vertices, and no larger intermediate size is formed.

Verification uses [Library Checker: Unionfind](https://judge.yosupo.jp/problem/unionfind)
through `verify/yosupo/dsu.test.cpp` and competitive-verifier. Unit tests cover
empty/singleton sets, endpoints, self/repeated/reversed merges, unequal component
sizes, balanced trees, 200,000 vertices, repeated path compression, double inclusion,
and multiple translation units. Five fixed seeds drive 320,000 mixed operations
on `n = 1..64`; connectivity, sizes, and merge results are compared with an
independent O(n) label replacement implementation, including periodic all-pairs
checks. Tests use explicit failure checks and still run with `NDEBUG`.

From the repository root:

```sh
CXX=g++ bash scripts/test-unit.sh
CXX=clang++ bash scripts/test-unit.sh
CXX=clang++ CXXFLAGS='-O1 -g -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer' bash scripts/test-unit.sh
# Activate the development venv and git add the new header/verifier first.
bash scripts/verify.sh
python3 scripts/build-docs.py
```

The PR's CI run provides compiler, sanitizer, and official-case results; its
`verification-results` artifact contains the verifier target and result JSON.
These commands describe the checks, not a claim that an unexecuted run passed.
