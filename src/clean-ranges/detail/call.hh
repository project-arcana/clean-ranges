#pragma once

#include <type_traits>

#include <clean-core/forward.hh>

namespace cr::detail
{
template <class F, class Arg>
constexpr decltype(auto) call(F&& fun, Arg&& arg)
{
    if constexpr (std::is_member_object_pointer_v<std::remove_reference_t<F>>)
    {
        if constexpr (std::is_pointer_v<std::remove_reference_t<Arg>>)
            return arg->*fun;
        else
            return arg.*fun;
    }
    else if constexpr (std::is_member_function_pointer_v<std::remove_reference_t<F>>)
    {
        if constexpr (std::is_pointer_v<std::remove_reference_t<Arg>>)
            return (arg->*fun)();
        else
            return (arg.*fun)();
    }
    else
        return fun(cc::forward<Arg>(arg));
}
}
