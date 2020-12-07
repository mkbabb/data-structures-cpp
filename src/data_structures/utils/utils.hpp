#include <iterator>
#include <optional>

#pragma once

namespace ds { namespace utils {

template<class Func>
struct y_combinator_impl
{
    Func func;

    explicit y_combinator_impl(Func&& func)
      : func{std::forward<Func>(func)}
    {}

    template<class... Args>
    auto operator()(Args&&... args) const -> decltype(auto)
    {
        return func(*this, std::forward<Args>(args)...);
    }
};

constexpr auto
y_combinator(auto&& func)
{
    using Func = std::remove_cvref_t<decltype(func)>;
    return y_combinator_impl(std::forward<Func>(func));
}

// template<class T>
// concept OrderedContainer = std::ranges::sized_range<T>&&
//     std::ranges::random_access_range<T>&& std::totally_ordered<T>;

constexpr auto default_comparator = [](const auto& x, const auto& y) -> int {
    return x < y ? -1 : x > y ? 1 : 0;
};

template<class Container, class V, class Comparator = decltype(default_comparator)>
int
bisect(
    Container&& arr,
    const V&& x,
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

}}