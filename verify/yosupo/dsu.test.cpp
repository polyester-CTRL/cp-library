// SPDX-License-Identifier: CC0-1.0
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "cp/data_structure/dsu.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    if (!(std::cin >> n >> q)) return 1;
    cp::dsu uf(n);
    while (q--) {
        int t, u, v;
        std::cin >> t >> u >> v;
        if (t == 0) uf.merge(u, v);
        else std::cout << uf.same(u, v) << '\n';
    }
}
