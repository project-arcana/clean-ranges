#pragma once

#include <clean-core/assert.hh>
#include <clean-core/has_operator.hh>
#include <clean-core/identity.hh>
#include <clean-core/iterator.hh>
#include <clean-core/move.hh>

#include <clean-ranges/detail/call.hh>

// TODO: custom comparator versions?

namespace detail_cr
{
template <class A, class B>
auto impl_min(A&& a, B&& b, cc::priority_tag<1>) -> decltype(a < b ? a : b)
{
    return a < b ? a : b;
}
template <class A, class B>
auto impl_min(A&& a, B&& b, cc::priority_tag<0>) -> decltype(min(a, b))
{
    return min(a, b);
}
template <class A, class B>
auto impl_max(A&& a, B&& b, cc::priority_tag<1>) -> decltype(a < b ? b : a)
{
    return a < b ? b : a;
}
template <class A, class B>
auto impl_max(A&& a, B&& b, cc::priority_tag<0>) -> decltype(max(a, b))
{
    return max(a, b);
}
}

namespace cr
{
/// returns the smallest f(element)
/// NOTE:
///   - supports pointer-to-member and pointer-to-member-fun
///   - preserves value category (i.e. can return a reference)
///   - requires either operator< or a free function min(a, b) via ADL
///   - calls f exactly once per element
///   - does not work on empty ranges
template <class Range, class MapF = cc::identity>
[[nodiscard]] constexpr decltype(auto) min(Range&& range, MapF&& f = {})
{
    auto it = cc::begin(range);
    auto end = cc::end(range);
    CC_ASSERT(it != end && "only non-empty ranges supported");

    using T = decltype(f(*it));
    using R = decltype(detail_cr::impl_min(std::declval<T>(), std::declval<T>(), cc::priority_tag<1>{}));

    if constexpr (std::is_lvalue_reference_v<R> && std::is_lvalue_reference_v<T>)
    {
        static_assert(std::is_same_v<R, T>, "min must return compatible type");
        std::remove_reference_t<R>* min_v = &f(*it);
        ++it;

        while (it != end)
        {
            min_v = &detail_cr::impl_min(*min_v, f(*it), cc::priority_tag<1>{});
            ++it;
        }

        return *min_v;
    }
    else // .. otherwise return by value
    {
        std::decay_t<T> min_v = f(*it);
        ++it;

        while (it != end)
        {
            min_v = detail_cr::impl_min(min_v, f(*it), cc::priority_tag<1>{});
            ++it;
        }

        return min_v;
    }
}

/// returns the element with the smallest key(element)
/// NOTE:
///   - supports pointer-to-member and pointer-to-member-fun
///   - preserves value category (i.e. can return a reference)
///   - requires either operator< on key(element)
///   - calls key exactly once per element
///   - does not work on empty ranges
template <class Range, class KeyF>
[[nodiscard]] constexpr decltype(auto) min_by(Range&& range, KeyF&& key)
{
    auto it = cc::begin(range);
    auto end = cc::end(range);
    CC_ASSERT(it != end && "only non-empty ranges supported");

    using T = decltype(key(*it));

    if constexpr (std::is_lvalue_reference_v<T>)
    {
        auto min_key = &key(*it);
        auto min_it = it;

        ++it;
        while (it != end)
        {
            auto k = &key(*it);
            if (*k < *min_key)
            {
                min_key = k;
                min_it = it;
            }
            ++it;
        }

        return *min_it;
    }
    else
    {
        auto min_key = key(*it);
        auto min_it = it;

        ++it;
        while (it != end)
        {
            auto k = key(*it);
            if (k < min_key)
            {
                min_key = cc::move(k);
                min_it = it;
            }
            ++it;
        }

        return *min_it;
    }
}

/// returns the largest f(element)
/// NOTE:
///   - supports pointer-to-member and pointer-to-member-fun
///   - preserves value category (i.e. can return a reference)
///   - requires either operator< or a free function max(a, b) via ADL
///   - calls f exactly once per element
///   - does not work on empty ranges
template <class Range, class MapF = cc::identity>
[[nodiscard]] constexpr decltype(auto) max(Range&& range, MapF&& f = {})
{
    auto it = cc::begin(range);
    auto end = cc::end(range);
    CC_ASSERT(it != end && "only non-empty ranges supported");

    using T = decltype(f(*it));
    using R = decltype(detail_cr::impl_max(std::declval<T>(), std::declval<T>(), cc::priority_tag<1>{}));

    if constexpr (std::is_lvalue_reference_v<R> && std::is_lvalue_reference_v<T>)
    {
        static_assert(std::is_same_v<R, T>, "max must return compatible type");
        std::remove_reference_t<R>* max_v = &f(*it);
        ++it;

        while (it != end)
        {
            max_v = &detail_cr::impl_max(*max_v, f(*it), cc::priority_tag<1>{});
            ++it;
        }

        return *max_v;
    }
    else // .. otherwise return by value
    {
        std::decay_t<T> max_v = f(*it);
        ++it;

        while (it != end)
        {
            max_v = detail_cr::impl_max(max_v, f(*it), cc::priority_tag<1>{});
            ++it;
        }

        return max_v;
    }
}

/// returns the element with the largest key(element)
/// NOTE:
///   - supports pointer-to-member and pointer-to-member-fun
///   - preserves value category (i.e. can return a reference)
///   - requires either operator< on key(element)
///   - calls key exactly once per element
///   - does not work on empty ranges
template <class Range, class KeyF>
[[nodiscard]] constexpr decltype(auto) max_by(Range&& range, KeyF&& key)
{
    auto it = cc::begin(range);
    auto end = cc::end(range);
    CC_ASSERT(it != end && "only non-empty ranges supported");

    using T = decltype(key(*it));

    if constexpr (std::is_lvalue_reference_v<T>)
    {
        auto max_key = &key(*it);
        auto max_it = it;

        ++it;
        while (it != end)
        {
            auto k = &key(*it);
            if (*max_key < *k)
            {
                max_key = k;
                max_it = it;
            }
            ++it;
        }

        return *max_it;
    }
    else
    {
        auto max_key = key(*it);
        auto max_it = it;

        ++it;
        while (it != end)
        {
            auto k = key(*it);
            if (max_key < k)
            {
                max_key = cc::move(k);
                max_it = it;
            }
            ++it;
        }

        return *max_it;
    }
}

template <class T>
struct minmax_t
{
    T min;
    T max;
};

/// returns the smallest and largest f(element)
/// NOTE:
///   - supports pointer-to-member and pointer-to-member-fun
///   - preserves value category (i.e. can return a reference)
///   - requires either operator< or a free functions min(a, b) and max(a, b) via ADL
///   - calls f exactly once per element
///   - does not work on empty ranges
template <class Range, class MapF = cc::identity>
[[nodiscard]] constexpr auto minmax(Range&& range, MapF&& f = {})
{
    auto it = cc::begin(range);
    auto end = cc::end(range);
    CC_ASSERT(it != end && "only non-empty ranges supported");

    using T = decltype(f(*it));
    using RMin = decltype(detail_cr::impl_min(std::declval<T>(), std::declval<T>(), cc::priority_tag<1>{}));
    using RMax = decltype(detail_cr::impl_max(std::declval<T>(), std::declval<T>(), cc::priority_tag<1>{}));
    static_assert(std::is_same_v<RMin, RMax>, "min and max types must be compatible");

    if constexpr (std::is_lvalue_reference_v<RMin> && std::is_lvalue_reference_v<T>)
    {
        static_assert(std::is_same_v<RMin, T>, "max must return compatible type");
        std::remove_reference_t<RMin>* min_v = &f(*it);
        std::remove_reference_t<RMin>* max_v = min_v;
        ++it;

        while (it != end)
        {
            decltype(auto) v = f(*it);
            min_v = &detail_cr::impl_min(*min_v, v, cc::priority_tag<1>{});
            max_v = &detail_cr::impl_max(*max_v, v, cc::priority_tag<1>{});
            ++it;
        }

        return minmax_t<RMin>{*min_v, *max_v};
    }
    else // .. otherwise return by value
    {
        std::decay_t<T> min_v = f(*it);
        std::decay_t<T> max_v = min_v;
        ++it;

        while (it != end)
        {
            decltype(auto) v = f(*it);
            min_v = detail_cr::impl_min(min_v, v, cc::priority_tag<1>{});
            max_v = detail_cr::impl_max(max_v, v, cc::priority_tag<1>{});
            ++it;
        }

        return minmax_t<std::decay_t<T>>{cc::move(min_v), cc::move(max_v)};
    }
}

/// returns the elements with the smallest and largest key(element)
/// NOTE:
///   - supports pointer-to-member and pointer-to-member-fun
///   - preserves value category (i.e. can return a reference)
///   - requires either operator< on key(element)
///   - calls key exactly once per element
///   - does not work on empty ranges
template <class Range, class KeyF>
[[nodiscard]] constexpr auto minmax_by(Range&& range, KeyF&& key)
{
    auto it = cc::begin(range);
    auto end = cc::end(range);
    CC_ASSERT(it != end && "only non-empty ranges supported");

    using T = decltype(key(*it));

    if constexpr (std::is_lvalue_reference_v<T>)
    {
        auto min_key = &key(*it);
        auto min_it = it;
        auto max_key = min_key;
        auto max_it = it;

        ++it;
        while (it != end)
        {
            auto k = &key(*it);
            if (*k < *min_key)
            {
                min_key = k;
                min_it = it;
            }
            if (*max_key < *k)
            {
                max_key = k;
                max_it = it;
            }
            ++it;
        }

        return minmax_t<decltype(*it)>{*min_it, *max_it};
    }
    else
    {
        auto max_key = key(*it);
        auto max_it = it;
        auto min_key = max_key;
        auto min_it = it;

        ++it;
        while (it != end)
        {
            auto k = key(*it);
            if (k < min_key)
            {
                min_key = cc::move(k);
                min_it = it;
            }
            if (max_key < k)
            {
                max_key = cc::move(k);
                max_it = it;
            }
            ++it;
        }

        return minmax_t<decltype(*it)>{*min_it, *max_it};
    }
}
}
