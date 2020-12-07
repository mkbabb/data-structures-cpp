#include "src/data_structures/list/array_list.hpp"

#include <optional>

namespace ds { namespace list {

template<class T>
class sparse_list
{
private:
    array_list<T> data;
    array_list<std::optional<int>> data_map;

public:
    sparse_list(int capacity, std::optional<array_list<T>> data = {})
    {
        this->data = array_list<T>(capacity);
        this->data_map = array_list(capacity, std::optional<int>{});

        for (auto i : data.value_or({})) {
        }
    }

    auto to_sparse_index(int ix) -> std::optional<int>
    {
        return this->data_map[ix];
    }

    auto insert(int ix, T value)
    {
        if (auto six = to_sparse_index(ix); six) {
            this->data[six] = value;
        } else {
            this->data.append(value);
            this->data_map[ix] = this->data.size() - 1;
        }
    }

    auto pop(std::optional<int> ix = {}) -> T
    {
        if (auto six = to_sparse_index(ix.value_or(this->data.size() - 1)); six) {
            this->data_map[ix] = {};
            return this->data.pop(six);
        }
    }

    template<class S>
    auto operator[](S ix) -> std::optional<T>
    {
        if (auto six = to_sparse_index(ix); six) {
            return this->data[six];
        } else {
            return {};
        }
    }

    auto size()
    {
        return this->data.size();
    }
};

}}