// SPDX-License-Identifier: CC0-1.0
#ifndef CP_DATA_STRUCTURE_DSU_HPP
#define CP_DATA_STRUCTURE_DSU_HPP

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

namespace cp {
// Disjoint sets on [0, n). Precondition: 0 <= n <= INT_MAX.
// Construction: O(n) time and space. Each operation: amortized O(alpha(n)).
// Component sizes never exceed n, so internal int arithmetic cannot overflow.
class dsu {
public:
    explicit dsu(int n = 0) {
        assert(n >= 0);
        parent_or_size_.assign(n, -1);
    }

    // Precondition: a and b are in [0, n).
    // Returns true exactly when two different components were joined.
    bool merge(int a, int b) {
        a = leader(a);
        b = leader(b);
        if (a == b) return false;
        if (parent_or_size_[a] > parent_or_size_[b]) std::swap(a, b);
        parent_or_size_[a] += parent_or_size_[b];
        parent_or_size_[b] = a;
        return true;
    }

    // Precondition: a and b are in [0, n).
    bool same(int a, int b) { return leader(a) == leader(b); }

    // Precondition: a is in [0, n). Returns the component size, in [1, n].
    int size(int a) { return -parent_or_size_[leader(a)]; }

private:
    // A root stores minus its component size; other nodes store their parent.
    std::vector<int> parent_or_size_;

    int leader(int a) {
        assert(a >= 0 && static_cast<std::size_t>(a) < parent_or_size_.size());
        int root = a;
        while (parent_or_size_[root] >= 0) root = parent_or_size_[root];
        while (a != root) {
            const int next = parent_or_size_[a];
            parent_or_size_[a] = root;
            a = next;
        }
        return root;
    }
};
}  // namespace cp

#endif
