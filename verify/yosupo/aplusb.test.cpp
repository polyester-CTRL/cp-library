#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <cstdint>
#include <iostream>
#include "cp/math/add.hpp"
int main() {
    std::int64_t a, b;
    if (!(std::cin >> a >> b)) return 1;
    std::cout << cp::add(a, b) << '\n';
}
