#define FMT_HEADER_ONLY

// #include "fmt/format.h"
// #include "range/v3/view/enumerate.hpp"
// #include "range/v3/view/iota.hpp"
#include "src/data_structures/tree/tree.hpp"
#include "src/data_structures/utils/pyrange.hpp"
#include "src/data_structures/utils/utils.hpp"

#include <iostream>
#include <vector>

int
main()
{
    auto n = 100000;
    std::vector<int> v;
    v.reserve(n);
    for (auto i = 0; i < n; i++) {
        v.push_back(i);
    }
    auto x = bisect(v, 0);

    for (auto i : pyrange(n)) {
        std::cout << "ok" << std::endl;
    }
    return 1;
}