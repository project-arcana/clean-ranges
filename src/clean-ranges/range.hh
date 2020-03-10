#pragma once

#include <initializer_list>

#include <clean-ranges/smart_range.hh>

namespace cr
{
template <class RangeT, cc::enable_if<cc::is_any_range<RangeT>> = true>
[[nodiscard]] constexpr auto range(RangeT&& r)
{
    if constexpr (std::is_rvalue_reference_v<RangeT>)
        return cr::smart_range<std::remove_reference_t<RangeT>>(cc::move(r));
    else
        return cr::smart_range<RangeT>(cc::forward<RangeT>(r));
}
template <class T>
[[nodiscard]] constexpr auto range(std::initializer_list<T> r)
{
    return cr::smart_range<std::initializer_list<T>>(r);
}
}
