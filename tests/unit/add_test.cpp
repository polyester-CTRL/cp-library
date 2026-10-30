#include "cp/math/add.hpp"
#include "cp/math/add.hpp"
#include <cstdint>
#include <iostream>
#include <limits>
std::int64_t add_from_other_translation_unit();
static_assert(cp::add(1, 2) == 3);
int main() {
    const auto max = std::numeric_limits<std::int64_t>::max();
    const auto min = std::numeric_limits<std::int64_t>::min();
    const bool ok = cp::add(0, 0) == 0 && cp::add(-7, 3) == -4 &&
        cp::add(1000000000, 1000000000) == 2000000000 &&
        cp::add(max, 0) == max && cp::add(min, 0) == min &&
        cp::add(max, -1) == max - 1 && cp::add(min, 1) == min + 1 &&
        add_from_other_translation_unit() == 42;
    if (!ok) { std::cerr << "add test failed\n"; return 1; }
    std::cout << "add: 8 runtime cases and constexpr check passed\n";
}
