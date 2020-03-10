#pragma once

#include <clean-core/assert.hh>
#include <clean-core/constant_function.hh>
#include <clean-core/iterator.hh>

#include <clean-ranges/detail/call.hh>

namespace cr
{
/// returning the one element satisfying the predicate in the range
/// asserts if no element or more than one found
template <class Range, class Predicate = cc::constant_function<true>>
[[nodiscard]] constexpr decltype(auto) single(Range&& range, Predicate&& predicate = {})
{
    auto it = cc::begin(range);
    auto end = cc::end(range);

    while (it != end)
    {
        decltype(auto) v = *it;
        if (cr::detail::call(predicate, v))
        {
#ifdef CC_ENABLE_ASSERTIONS
            ++it;
            while (it != end)
            {
                CC_ASSERT(!cr::detail::call(predicate, *it) && "is not actually the only element");
                ++it;
            }
#endif

            return v;
        }

        ++it;
    }

    CC_UNREACHABLE("no element satisfying the predicate found");
}
}
