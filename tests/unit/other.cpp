#include "cp/math/add.hpp"
#include "cp/data_structure/dsu.hpp"
std::int64_t add_from_other_translation_unit() { return cp::add(20, 22); }
bool dsu_from_other_translation_unit() {
    cp::dsu uf(3);
    return uf.merge(0, 2) && uf.same(2, 0) && uf.size(2) == 2 && !uf.same(0, 1);
}
