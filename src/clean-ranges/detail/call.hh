#pragma once

#include <type_traits>

#include <clean-core/forward.hh>
#include <clean-core/priority_tag.hh>

namespace cr::detail
{
template <class F, class Arg>
constexpr auto impl_obj_member_call(F&& fun, Arg&& arg, cc::priority_tag<1>) -> decltype(arg.*fun)
{
    return arg.*fun;
}
template <class F, class Arg>
constexpr auto impl_obj_member_call(F&& fun, Arg&& arg, cc::priority_tag<0>) -> decltype((*arg).*fun)
{
    return (*arg).*fun;
}

template <class F, class Arg>
constexpr auto impl_fun_member_call(F&& fun, Arg&& arg, cc::priority_tag<1>) -> decltype((arg.*fun)())
{
    return (arg.*fun)();
}
template <class F, class Arg>
constexpr auto impl_fun_member_call(F&& fun, Arg&& arg, cc::priority_tag<0>) -> decltype(((*arg).*fun)())
{
    return ((*arg).*fun)();
}

template <class F, class Arg>
constexpr decltype(auto) call(F&& fun, Arg&& arg)
{
    if constexpr (std::is_member_object_pointer_v<std::remove_reference_t<F>>)
        return impl_obj_member_call(cc::forward<F>(fun), cc::forward<Arg>(arg), cc::priority_tag<1>{});
    else if constexpr (std::is_member_function_pointer_v<std::remove_reference_t<F>>)
        return impl_fun_member_call(cc::forward<F>(fun), cc::forward<Arg>(arg), cc::priority_tag<1>{});
    else
        return fun(cc::forward<Arg>(arg));
}
}
