#define FMT_HEADER_ONLY

#include "fmt/format.h"
#include "range/v3/view/enumerate.hpp"
#include "range/v3/view/iota.hpp"
#include "src/data_structures/utils/pyrange.hpp"

#include <iostream>
#include <vector>

int
main()
{

    std::vector<int> v = {1, 2, 3, 4, 5, 6};

    for (auto i : pyrange(10)) {
        std::cout << "ok" << std::endl;
    }
    return 1;
}