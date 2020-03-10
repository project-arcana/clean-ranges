#pragma once

#include <clean-ranges/algorithms/reduce.hh>

namespace cr
{
/// computes the sum of f(element)
/// requires a non-empty range
template <class Range, class MapF = cc::identity>
[[nodiscard]] constexpr auto sum(Range&& range, MapF&& f = {})
{
    return cr::reduce(range, [](auto&& a, auto&& b) { return a + b; }, f);
}
}
