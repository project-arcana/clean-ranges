#pragma once

#include <clean-core/assert.hh>
#include <clean-core/constant_function.hh>
#include <clean-core/iterator.hh>

#include <clean-ranges/detail/call.hh>

namespace cr
{
/// returns the last element satisfying the predicate in the range
/// NOTE: requires at least one matching element
/// Complexity: O(n)
template <class Range, class Predicate = cc::constant_function<true>>
[[nodiscard]] constexpr decltype(auto) last(Range&& range, Predicate&& predicate = {})
{
    auto it = cc::begin(range);
    auto end = cc::end(range);
    size_t idx = 0;

    auto found = false;
    auto res_it = it;

    while (it != end)
    {
        if (cr::detail::call(idx, predicate, *it))
        {
            res_it = it;
            found = true;
        }

        ++it;
        ++idx;
    }

    CC_ASSERT(found && "no element satisfying the predicate found");
    return *res_it;
}
}
