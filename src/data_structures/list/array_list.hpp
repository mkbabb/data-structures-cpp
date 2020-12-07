#include "src/data_structures/utils/range.hpp"

#include <exception>
#include <fmt/format.h>
#include <numeric>
#include <optional>
#include <range/v3/all.hpp>
#include <span>

#pragma once

namespace ds { namespace list {

struct slice
{
    std::optional<int> start, stop, stride;

    slice(
        std::optional<int> start = {},
        std::optional<int> stop = {},
        std::optional<int> stride = {1})
      : start{start}
      , stop{stop}
      , stride{stride}
    {}
};

template<class T>
class array_list
{
private:
    int capacity_, size_;
    std::unique_ptr<T[]> data;
    std::span<T> span;

    void update_span()
    {
        this->span = std::span(this->data.get(), this->size_);
    }

public:
    array_list(int capacity = 10)
    {
        this->capacity_ = capacity;
        this->size_ = 0;
        this->data = std::make_unique<T[]>(this->capacity_);

        this->update_span();
    }

    array_list(int capacity, T init_value)
      : array_list(capacity)
    {
        for (auto i : utils::range(capacity)) {
            this->append(init_value);
        }
    }

    array_list(std::initializer_list<T> list)
      : array_list(list.size())
    {
        for (auto i : list) {
            this->append(i);
        }
    }

    void grow()
    {
        if (this->size_ >= this->capacity_ - 1) {
            this->capacity_ *= 2;
            auto new_data = std::make_unique<T[]>(this->capacity_);
            std::copy(this->begin(), this->end(), new_data.get());

            this->data = std::move(new_data);
            this->update_span();
        }
    }

    auto check_index(int ix) -> void
    {
        if (ix > this->capacity_ or abs(ix) - 1 > this->capacity_) {
            throw std::domain_error("Invalid index");
        }
    }

    auto insert(int ix, T value)
    {
        this->grow();

        this->check_index(ix + 1);

        for (auto i : utils::range(this->size_, ix, -1)) {
            std::swap(this->data[i], this->data[i - 1]);
        }

        this->data[ix] = value;
        this->size_ += 1;
    }

    auto append(T value)
    {
        this->insert(this->size_, value);
    }

    auto pop(std::optional<int> ix = {}) -> T
    {
        this->check_index(ix);

        auto start = ix.value_or(this->size() - 1);

        for (auto i : utils::range(start, this->size() + 1)) {
            std::swap(this->data[i], this->data[i - 1]);
        }

        auto value = std::move(this->data[this->size_]);
        this->size_ -= 1;

        return value;
    }

    auto index(T value) -> std::optional<int>
    {
        for (const auto& [n, i] : ranges::views::enumerate(*this)) {
            if (i == value) {
                return n;
            }
        }
        return {};
    }

    auto operator[](int ix)
    {
        this->check_index(ix);
        return this->data[ix];
    }

    auto operator[](slice ix)
    {
        auto start = ix.start.value_or(0);
        auto stop = ix.stop.value_or(this->size());
        auto stride = ix.stride.value_or(1);

        auto count = (stop - start) / stride;

        array_list<T> out{count};

        for (auto i : utils::range(start, stop, stride)) {
            out.append(this->data[i]);
        }

        return out;
    }

    auto begin()
    {
        return this->span.begin();
    }

    auto end()
    {
        return this->span.end();
    }

    auto size() const
    {
        return this->size_;
    }

    auto capacity() const
    {
        return this->capacity_;
    }
};
}}