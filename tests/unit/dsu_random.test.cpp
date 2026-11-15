// SPDX-License-Identifier: CC0-1.0
#include "cp/data_structure/dsu.hpp"
#include "cp/data_structure/dsu.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

bool dsu_from_other_translation_unit();

namespace {
int current_n = 0;
std::uint32_t current_seed = 0;
int current_step = 0;

void check(bool ok, const char* message) {
    if (!ok) {
        std::cerr << "dsu: " << message << " (n=" << current_n
                  << ", seed=" << current_seed << ", step=" << current_step << ")\n";
        std::exit(1);
    }
}

// Independent O(n) label replacement oracle; no parent tree or path compression.
struct naive_dsu {
    std::vector<int> label;
    explicit naive_dsu(int n) : label(n) { std::iota(label.begin(), label.end(), 0); }
    bool same(int a, int b) const { return label[a] == label[b]; }
    int size(int a) const {
        return static_cast<int>(std::count(label.begin(), label.end(), label[a]));
    }
    bool merge(int a, int b) {
        const int from = label[b], to = label[a];
        if (from == to) return false;
        for (int& x : label) if (x == from) x = to;
        return true;
    }
};

void compare_all(cp::dsu& uf, const naive_dsu& expected, int n) {
    for (int a = 0; a < n; ++a) {
        check(uf.size(a) == expected.size(a), "component size");
        for (int b = 0; b < n; ++b)
            check(uf.same(a, b) == expected.same(a, b), "connectivity");
    }
}

void boundaries() {
    cp::dsu empty;
    cp::dsu zero(0);
    cp::dsu one(1);
    check(one.same(0, 0) && one.size(0) == 1, "singleton");
    check(!one.merge(0, 0) && one.size(0) == 1, "self merge");
    cp::dsu uf(8);
    check(!uf.same(0, 7), "initially separate endpoints");
    check(uf.merge(0, 7), "join endpoints");
    check(!uf.merge(7, 0) && uf.size(7) == 2, "repeated reversed merge");
    check(uf.merge(1, 2) && uf.merge(3, 4) && uf.merge(1, 3), "balanced merges");
    check(uf.merge(0, 1), "smaller first component");
    check(uf.merge(1, 5) && uf.merge(6, 0), "unequal sizes in both orders");
    for (int a = 0; a < 8; ++a)
        check(uf.same(a, 7) && uf.size(a) == 8, "all connected");
    check(dsu_from_other_translation_unit(), "multiple translation units");
}

void randomized() {
    constexpr std::uint32_t seeds[] = {0, 1, 42, 20261107, 0xffffffffU};
    for (int n = 0; n <= 64; ++n) {
        current_n = n;
        for (const auto seed : seeds) {
            current_seed = seed;
            current_step = 0;
            std::mt19937 rng(seed);
            cp::dsu uf(n);
            naive_dsu expected(n);
            compare_all(uf, expected, n);
            if (n == 0) continue;
            for (int step = 1; step <= 1000; ++step) {
                current_step = step;
                const int a = static_cast<int>(rng() % n);
                const int b = static_cast<int>(rng() % n);
                switch (rng() % 4) {
                case 0:
                    check(uf.merge(a, b) == expected.merge(a, b), "merge result");
                    break;
                case 1: check(uf.same(a, b) == expected.same(a, b), "same result"); break;
                case 2: check(uf.size(a) == expected.size(a), "size result"); break;
                default: check(!uf.merge(a, a), "random self merge"); break;
                }
                check(uf.size(a) == expected.size(a), "size after operation");
                if (step % 97 == 0) compare_all(uf, expected, n);
            }
            compare_all(uf, expected, n);
        }
    }
}

void large_patterns() {
    constexpr int n = 200000;
    current_n = n;
    cp::dsu chain(n);
    for (int a = 1; a < n; ++a) check(chain.merge(a, a - 1), "chain merge");
    for (int a = 0; a < n; ++a)
        check(chain.same(0, a) && chain.size(a) == n, "large chain");

    constexpr int m = 1 << 16;
    cp::dsu balanced(m);
    for (int width = 1; width < m; width *= 2)
        for (int a = 0; a < m; a += 2 * width)
            check(balanced.merge(a, a + width), "balanced merge");
    for (int pass = 0; pass < 3; ++pass)
        for (int a = m - 1; a >= 0; --a)
            check(balanced.same(a, 0) && balanced.size(a) == m, "compressed paths");
}
}  // namespace

int main() {
    boundaries();
    randomized();
    large_patterns();
    std::cout << "dsu: boundaries, 320000 random operations (5 seeds, n=1..64), "
                 "full oracle comparisons, large patterns and multiple TUs passed\n";
}
