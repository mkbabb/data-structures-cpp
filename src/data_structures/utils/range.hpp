#include <numeric>

#pragma once

namespace ds { namespace utils {

template<typename T = int>
class range;

template<typename T = int>
class range_iterator : public std::iterator<std::forward_iterator_tag, T>
{
public:
    using iterator_category = std::forward_iterator_tag;
    using iterator_value = T;

    explicit range_iterator(range<T>& seq)
      : seq_(seq)
    {}

    auto operator++()
    {
        seq_.current += seq_.stride;
        return *this;
    }

    auto operator==(T rhs)
    {
        return seq_.current == rhs;
    }

    auto operator!=(T rhs)
    {
        return !(*this == rhs);
    }

    auto operator*() const
    {
        return seq_.current;
    }

private:
    range<T> seq_;
};

template<typename T>
class range
{
public:
    using iterator = range_iterator<T>;

    constexpr explicit range(T stop)
      : start(0)
      , stop(stop)
    {
        if (start > stop) {
            std::swap(start, stop);
        }
        stride = start > stop ? -1 : 1;
        current = start;
    }

    constexpr range(T start, T stop)
      : start(start)
      , stop(stop)
    {
        stride = start > stop ? -1 : 1;
        current = start;
    }

    constexpr range(T start, T stop, T stride)
      : start(start)
      , stop(stop)
      , stride(stride)
      , current(start)
    {}

    int size() const
    {
        return size_;
    }

    iterator begin()
    {
        return iterator(*this);
    }

    T end()
    {
        return stop;
    }

private:
    friend class range_iterator<T>;
    T start, stop, stride, current;
    int size_ = 0;
};
}}