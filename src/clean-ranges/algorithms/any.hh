#pragma once

#include <clean-core/constant_function.hh>
#include <clean-core/iterator.hh>

#include <clean-ranges/detail/call.hh>

namespace cr
{
/// returns true if there is at least one element where predicate(e) is true
template <class Range, class Predicate = cc::constant_function<true>>
[[nodiscard]] constexpr bool any(Range&& range, Predicate&& predicate = {})
{
    auto it = cc::begin(range);
    auto end = cc::end(range);

    while (it != end)
    {
        if (cr::detail::call(predicate, *it))
            return true;

        ++it;
    }

    return false;
}
}
