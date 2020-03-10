#pragma once

#include <clean-core/assert.hh>
#include <clean-core/constant_function.hh>
#include <clean-core/iterator.hh>

#include <clean-ranges/detail/call.hh>

namespace cr
{
/// returning the last element satisfying the predicate in the range
/// NOTE: does not work on empty ranges
/// Complexity: O(i) where i is the "index" of the returned element
template <class Range, class Predicate = cc::constant_function<true>>
[[nodiscard]] constexpr decltype(auto) last(Range&& range, Predicate&& predicate = {})
{
    auto it = cc::begin(range);
    auto end = cc::end(range);

    auto found = false;
    auto res_it = it;

    while (it != end)
    {
        if (cr::detail::call(predicate, *it))
        {
            res_it = it;
            found = true;
        }

        ++it;
    }

    CC_ASSERT(found && "no element satisfying the predicate found");
    return *res_it;
}
}
