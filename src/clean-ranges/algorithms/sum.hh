#pragma once

#include <clean-core/assert.hh>
#include <clean-core/identity.hh>
#include <clean-core/iterator.hh>

#include <clean-ranges/detail/call.hh>
#include <clean-ranges/detail/type_or.hh>

namespace cr
{
/// computes the sum of f(element)
/// NOTE:
///   - requires a non-empty range
///   - accumulation type can be optionally specified
template <class AccumT = void, class Range, class MapF = cc::identity>
[[nodiscard]] constexpr auto sum(Range&& range, MapF&& f = {})
{
    auto it = cc::begin(range);
    auto end = cc::end(range);
    using T = cr::detail::type_or<AccumT, decltype(cr::detail::call(f, *it))>;
    CC_ASSERT(it != end && "requires non-empty range");

    auto s = static_cast<T>(cr::detail::call(f, *it));
    ++it;
    while (it != end)
    {
        s = s + static_cast<T>(cr::detail::call(f, *it));
        ++it;
    }

    return s;
}
}
