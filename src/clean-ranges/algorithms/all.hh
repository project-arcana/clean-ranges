#pragma once

#include <clean-core/constant_function.hh>
#include <clean-core/iterator.hh>

#include <clean-ranges/detail/call.hh>

namespace cr
{
/// returns true if all elements satisfy predicate
template <class Range, class Predicate>
[[nodiscard]] constexpr bool all(Range&& range, Predicate&& predicate)
{
    auto it = cc::begin(range);
    auto end = cc::end(range);
    size_t idx = 0;

    while (it != end)
    {
        if (!cr::detail::call(idx, predicate, *it))
            return false;

        ++it;
        ++idx;
    }

    return true;
}
}
