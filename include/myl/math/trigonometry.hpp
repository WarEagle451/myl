#pragma once
#include <myl/numbers.hpp>

namespace myl {
    template<typename T>
    MYL_NO_DISCARD constexpr auto degrees(T radian) -> T {
        return radian * numbers::one_rad_in_degree<T>;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto radians(T degree) -> T {
        return degree * numbers::one_degree_in_rad<T>;
    }
}
