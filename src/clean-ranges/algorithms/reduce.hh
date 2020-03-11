#pragma once

#include <clean-core/assert.hh>
#include <clean-core/identity.hh>
#include <clean-core/iterator.hh>

#include <clean-ranges/detail/call.hh>

namespace cr
{
/// a generic map-reduce operation (map via F, reduce via Op)
///
/// Computes (for range [e0, e1, ...])
///
///   auto v = f(e0);
///   v = op(v, f(e1));
///   v = op(v, f(e2));
///   ...
///   return v;
///
/// NOTE: requires a non-empty range
///       F can also be pointer-to-member or pointer-to-member-fun
template <class Range, class Op, class MapF = cc::identity>
[[nodiscard]] constexpr auto reduce(Range&& range, Op&& op, MapF&& f = {})
{
    auto it = cc::begin(range);
    auto end = cc::end(range);
    size_t idx = 0;
    CC_ASSERT(it != end && "requires non-empty range");

    auto s = cr::detail::call(idx, f, *it);
    ++it;
    ++idx;
    while (it != end)
    {
        s = op(s, cr::detail::call(idx, f, *it));
        ++it;
        ++idx;
    }

    return s;
}
}
