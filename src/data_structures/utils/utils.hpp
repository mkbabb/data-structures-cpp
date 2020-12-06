#include <concepts>
#include <iterator>
#include <optional>
#include <ranges>

#pragma once

template<class Func>
struct y_combinator
{
    Func func;

    template<class... Args>
    decltype(auto) operator()(Args&&... args) const
    {
        return func(*this, std::forward<Args>(args)...);
    }
};

template<class T>
concept OrderedContainer = std::ranges::sized_range<T>&&
    std::ranges::random_access_range<T>&& std::totally_ordered<T>;

constexpr auto default_comparator = [](auto x, auto y) -> int {
    return x < y ? -1 : x > y ? 1 : 0;
};

template<
    OrderedContainer Container,
    class V = std::ranges::range_value_t<Container>,
    class Comparator = decltype(default_comparator)>
int
bisect(
    Container&& arr,
    V&& x,
    Comparator comparator = default_comparator,
    bool left = true,
    bool negate_found = true,
    std::optional<V> start = {},
    std::optional<V> stop = {})
{
    auto recurse = y_combinator([&](auto recurse, int low, int high) -> int {
        const int midpoint = (high + low) / 2;

        if (low <= high) {
            const auto midvalue = arr[midpoint];
            const auto comp = comparator(x, midvalue);

            if (comp < 0) {
                return recurse(low, midpoint - 1);
            } else if (comp > 0) {
                return recurse(midpoint + 1, high);
            } else {
                return left ? midpoint : midpoint + 1;
            }
        } else {
            return negate_found ? -1 * (low + 1) : low;
        }
    });

    return recurse(start.value_or(0), stop.value_or(arr.size() - 1));
}

// template<
//     OrderedContainer T,
//     class Comparator = decltype(default_comparator),
//     class V = std::ranges::range_value_t<T>>
// int
// bisect_left(
//     T arr,
//     V x,
//     Comparator comparator = default_comparator,
//     bool negate_found = true,
//     std::optional<V> start = {},
//     std::optional<V> stop = {})
// {
//     return bisect(
//         std::forward<T>(arr),
//         std::forward<V>(x),
//         std::forward<Comparator>(comp),
//         true,
//         start,
//         stop)
// }

bool
is_power_of(int n, int b)
{
    if (n <= 1) {
        return false;
    } else {
        while (n % b == 0) {
            n /= b;
        }
        return n == 1;
    }
}