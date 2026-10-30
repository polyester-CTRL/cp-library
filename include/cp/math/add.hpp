#ifndef CP_MATH_ADD_HPP
#define CP_MATH_ADD_HPP
#include <cstdint>
namespace cp {
// Precondition: the mathematical sum is representable by std::int64_t.
// Time O(1), space O(1).
constexpr std::int64_t add(std::int64_t a, std::int64_t b) noexcept {
    return a + b;
}
}  // namespace cp
#endif
