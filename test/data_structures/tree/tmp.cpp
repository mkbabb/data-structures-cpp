#define FMT_HEADER_ONLY

#include "fmt/format.h"
#include "range/v3/view/enumerate.hpp"
#include "range/v3/view/iota.hpp"
#include "src/data_structures/list/array_list.hpp"
#include "src/data_structures/list/sparse_list.hpp"
#include "src/data_structures/tree/tree.hpp"
#include "src/data_structures/utils/range.hpp"

#include <iostream>
#include <vector>

int
main()
{
    using namespace ds;
    // auto n = 100000;
    // std::vector<int> v;
    // v.reserve(n);
    // for (auto i = 0; i < n; i++) {
    //     v.push_back(i);
    // }
    // auto x = bisect(v, 0);

    list::array_list<int> v({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

    auto vv = v[list::slice(1, 5)];

    auto z = utils::bisect(v, 0);

    auto x = v.index(10);
    auto y = v.index(99);

    return 1;
}