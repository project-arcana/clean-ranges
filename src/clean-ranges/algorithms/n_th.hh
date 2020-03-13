#pragma once

#include <clean-core/assert.hh>
#include <clean-core/constant_function.hh>
#include <clean-core/iterator.hh>

#include <clean-ranges/detail/call.hh>
#include <clean-ranges/smart_range.hh>

namespace cr
{
/// returns the element with the given index
/// NOTE: requires at least "idx + 1" many elements
/// Complexity: O(idx)
template <class Range>
[[nodiscard]] constexpr decltype(auto) n_th(Range&& range, size_t idx)
{
    auto it = cc::begin(range);
    auto end = cc::end(range);

    while (it != end)
    {
        if (idx == 0)
            return *it;

        ++it;
        --idx;
    }

    CC_UNREACHABLE("not enough elements");
}

/// returns the element with the given index
/// if not enough elements, returns value
/// NOTE: preserves value categories
/// Complexity: O(idx)
template <class Range, class T>
[[nodiscard]] constexpr decltype(auto) n_th_or(Range&& range, size_t idx, T&& value)
{
    auto it = cc::begin(range);
    auto end = cc::end(range);

    using R = decltype(true ? *it : cc::forward<T>(value));

    while (it != end)
    {
        if (idx == 0)
            return static_cast<R>(*it);

        ++it;
        --idx;
    }

    return static_cast<R>(cc::forward<T>(value));
}

// [smart_range implementation]
template <class ContainerT>
constexpr decltype(auto) smart_range<ContainerT>::n_th(size_t idx)
{
    return cr::n_th(_container, idx);
}
template <class ContainerT>
template <class T>
constexpr decltype(auto) smart_range<ContainerT>::n_th_or(size_t idx, T&& value)
{
    return cr::n_th_or(_container, idx, cc::forward<T>(value));
}
}
