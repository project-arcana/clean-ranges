#pragma once

#include <clean-core/assert.hh>
#include <clean-core/identity.hh>
#include <clean-core/iterator.hh>

#include <clean-ranges/detail/call.hh>
#include <clean-ranges/detail/type_or.hh>

namespace cr
{
/// computes the average of f(element)
/// NOTE:
///   - requires a non-empty range
///   - count type can be provided optionally
///   - returns sum(range, f) / static_cast<CountT>(count(v)) (i.e. requires operator/)
template <class CountT = void, class Range, class MapF = cc::identity>
[[nodiscard]] constexpr auto average(Range&& range, MapF&& f = {})
{
    auto it = cc::begin(range);
    auto end = cc::end(range);
    using T = cr::detail::type_or<CountT, size_t>;
    auto cnt = T(1);
    CC_ASSERT(it != end && "requires non-empty range");

    auto s = cr::detail::call(f, *it);
    ++it;
    while (it != end)
    {
        s = s + cr::detail::call(f, *it);
        ++it;
        ++cnt;
    }

    return s / cnt;
}
}
