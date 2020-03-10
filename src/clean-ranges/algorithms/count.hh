#pragma once

#include <cstddef>

#include <clean-core/constant_function.hh>
#include <clean-core/iterator.hh>

#include <clean-ranges/detail/call.hh>

namespace cr
{
/// returns the number of elements in the range
template <class Range>
[[nodiscard]] constexpr size_t count(Range&& range)
{
    auto it = cc::begin(range);
    auto end = cc::end(range);

    size_t cnt = 0;
    while (it != end)
    {
        ++cnt;
        ++it;
    }
    return cnt;
}

/// returns the number of elements where (e == v)
template <class Range, class T>
[[nodiscard]] constexpr size_t count(Range&& range, T const& v)
{
    auto it = cc::begin(range);
    auto end = cc::end(range);

    size_t cnt = 0;
    while (it != end)
    {
        if (*it == v)
            ++cnt;
        ++it;
    }
    return cnt;
}

/// returns the number of elements where predicate(e) true ist
template <class Range, class Predicate>
[[nodiscard]] constexpr size_t count_if(Range&& range, Predicate&& predicate)
{
    auto it = cc::begin(range);
    auto end = cc::end(range);

    size_t cnt = 0;
    while (it != end)
    {
        if (cr::detail::call(predicate, *it))
            ++cnt;

        ++it;
    }
    return cnt;
}
}
