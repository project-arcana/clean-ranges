#pragma once

#include <type_traits>

#include <clean-core/forward.hh>

namespace cr::detail
{
template <class F, class Arg>
constexpr auto impl_obj_member_call(F&& fun, Arg&& arg) -> decltype(arg.*fun)
{
    return arg.*fun;
}
template <class F, class Arg>
constexpr auto impl_obj_member_call(F&& fun, Arg&& arg) -> decltype((*arg).*fun)
{
    return (*arg).*fun;
}

template <class F, class Arg>
constexpr auto impl_fun_member_call(F&& fun, Arg&& arg) -> decltype((arg.*fun)())
{
    return (arg.*fun)();
}
template <class F, class Arg>
constexpr auto impl_fun_member_call(F&& fun, Arg&& arg) -> decltype(((*arg).*fun)())
{
    return ((*arg).*fun)();
}

template <class F, class Arg>
constexpr decltype(auto) call(F&& fun, Arg&& arg)
{
    if constexpr (std::is_member_object_pointer_v<std::remove_reference_t<F>>)
        return impl_obj_member_call(cc::forward<F>(fun), cc::forward<Arg>(arg));
    else if constexpr (std::is_member_function_pointer_v<std::remove_reference_t<F>>)
        return impl_fun_member_call(cc::forward<F>(fun), cc::forward<Arg>(arg));
    else
        return fun(cc::forward<Arg>(arg));
}
}
