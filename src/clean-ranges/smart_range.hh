#pragma once

#include <type_traits>

#include <clean-core/constant_function.hh>
#include <clean-core/enable_if.hh>
#include <clean-core/forward.hh>
#include <clean-core/identity.hh>
#include <clean-core/is_range.hh>
#include <clean-core/iterator.hh>
#include <clean-core/move.hh>

namespace cr
{
/**
 * A smart_range is a wrapper around some container/range
 * and offers a variety of functional-inspired methods for working with collections
 *
 * NOTE: ContainerT can be a reference (making this a view)
 *                  or a value (making this owning)
 *       const-ness should be shown in ContainerT, not "const smart_range"
 *
 * IMPORTANT: to use the algorithms, either
 *            #include <clean-ranges/algorithms/MY_SPECIFIC_ALGO.hh> or
 *            #include <clean-ranges/algorithms.hh>
 *
 * TODO: how to extend smart_range? maybe via inheritance and CRTP?
 */
template <class ContainerT>
struct smart_range
{
    static constexpr bool is_owning = !std::is_lvalue_reference_v<ContainerT>;
    static constexpr bool is_view = std::is_lvalue_reference_v<ContainerT>;
    static constexpr bool is_readonly = std::is_const_v<std::remove_reference_t<ContainerT>>;
    static_assert(!std::is_rvalue_reference_v<ContainerT>, "cannot hold rvalue references");

    using element_t = decltype(*cc::begin(std::declval<ContainerT>()));
    using decayed_element_t = std::decay_t<element_t>;

    constexpr smart_range(ContainerT c) : _container(cc::forward<ContainerT>(c)) {}

    // pass-through collection
public:
    [[nodiscard]] constexpr auto begin() { return cc::begin(_container); }
    [[nodiscard]] constexpr auto begin() const { return cc::begin(_container); }
    [[nodiscard]] constexpr auto end() { return cc::end(_container); }
    [[nodiscard]] constexpr auto end() const { return cc::end(_container); }
    [[nodiscard]] constexpr decltype(auto) container() & { return _container; }
    [[nodiscard]] constexpr decltype(auto) container() const& { return _container; }
    [[nodiscard]] constexpr decltype(auto) container() && { return cc::move(_container); }
    [[nodiscard]] constexpr decltype(auto) container() const&& { return _container; }

    // algorithms
public:
    template <class MapF = cc::identity>
    [[nodiscard]] constexpr auto sum(MapF&& f = {});

    template <class Op, class MapF = cc::identity>
    [[nodiscard]] constexpr auto reduce(Op&& op, MapF&& f = {});

    template <class Predicate = cc::constant_function<true>>
    [[nodiscard]] constexpr decltype(auto) single(Predicate&& predicate = {});

    [[nodiscard]] constexpr decltype(auto) n_th(size_t idx);
    template <class T>
    [[nodiscard]] constexpr decltype(auto) n_th_or(size_t idx, T&& value);

private:
    ContainerT _container;
};
}
