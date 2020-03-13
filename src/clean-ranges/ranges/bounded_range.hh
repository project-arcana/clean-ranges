#pragma once

#include <clean-core/move.hh>
#include <clean-core/sentinel.hh>

namespace cr
{
template <class ItT, class EndT>
struct bounded_range
{
    constexpr bounded_range(ItT it, EndT end) : it(cc::move(it)), end(cc::move(end)) {}



private:
    ItT it;
    EndT end;
};
}
