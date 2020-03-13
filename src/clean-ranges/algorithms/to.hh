#pragma once

#include <clean-ranges/algorithms/collect.hh>

namespace cr
{
/// same as collect_into but creates and returns a new container
template <template <class...> class ContainerTemplate, class Range, class MapF = cc::identity>
[[nodiscard]] constexpr auto to(Range&& range, MapF&& f = {})
{
    using T = std::decay_t<decltype(cr::detail::call(size_t(0), f, *cc::begin(range)))>;

    ContainerTemplate<T> container;
    cr::collect(cc::forward<Range>(range), container, cc::forward<MapF>(f));
    return container;
}

/// same as collect_into but creates and returns a new container
template <class Container, class Range, class MapF = cc::identity>
[[nodiscard]] constexpr auto to(Range&& range, MapF&& f = {})
{
    Container container;
    cr::collect(cc::forward<Range>(range), container, cc::forward<MapF>(f));
    return container;
}
}
