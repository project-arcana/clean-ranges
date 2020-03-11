#pragma once

#include <initializer_list>

#include <clean-ranges/smart_range.hh>

namespace cr
{
/// returns a smart range that iterates over the given range
template <class RangeT, cc::enable_if<cc::is_any_range<RangeT>> = true>
[[nodiscard]] constexpr auto range(RangeT&& r)
{
    if constexpr (std::is_rvalue_reference_v<RangeT>)
        return cr::smart_range<std::remove_reference_t<RangeT>>(cc::move(r));
    else
        return cr::smart_range<RangeT>(cc::forward<RangeT>(r));
}
/// returns a smart range that iterates over the given values
template <class T>
[[nodiscard]] constexpr auto range(std::initializer_list<T> r)
{
    return cr::smart_range<std::initializer_list<T>>(r);
}

/// returns a smart range that iterates from 0..end (exclusive)
/// e.g. useful in `for (auto i : cr::range(v.size()))` to get values up to v.size() - 1
template <class EndT, cc::enable_if<std::is_integral_v<EndT>> = true>
[[nodiscard]] constexpr auto range(EndT&& end_exclusive)
{
    // TODO
}

/// returns a smart_range that iterates from start..end (exclusive)
/// using `++v` to get to the next element
/// if `*v` is a valid expression, then it is returned, otherwise `v` directly (proper behavior on iterators)
template <class StartT, class EndT>
[[nodiscard]] constexpr auto range(StartT&& start, EndT&& end)
{
    // TODO
}
/// returns a smart_range that iterates from start..end (exclusive)
/// to get to the next value, the following expressions are used (priority top-down):
///   `v += inc`
///   `v = inc(v)`
///   `inc(v)`
/// if `*v` is a valid expression, then it is returned, otherwise `v` directly (proper behavior on iterators)
template <class StartT, class EndT, class IncT>
[[nodiscard]] constexpr auto range(StartT&& start, EndT&& end, IncT&& inc)
{
    // TODO
}

/// returns a smart_range that iterates endlessly from the start value
/// using `++v` to get to the next element
/// if `*v` is a valid expression, then it is returned, otherwise `v` directly (proper behavior on iterators)
template <class StartT, class EndT>
[[nodiscard]] constexpr auto inf_range(StartT&& start)
{
    // TODO
}
/// returns a smart_range that iterates endlessly from the start value
/// to get to the next value, the following expressions are used (priority top-down):
///   `v += inc`
///   `v = inc(v)`
///   `inc(v)`
/// if `*v` is a valid expression, then it is returned, otherwise `v` directly (proper behavior on iterators)
template <class StartT, class EndT, class IncT>
[[nodiscard]] constexpr auto inf_range(StartT&& start, IncT&& inc)
{
    // TODO
}
}
