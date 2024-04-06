#pragma once
#include <myl/numbers.hpp>

namespace myl {
    template<typename T>
    MYL_NO_DISCARD constexpr auto degrees(T radian) -> T {
        constexpr T radian_as_degrees = static_cast<T>(180) / numbers::pi<T>;
        return radian * radian_as_degrees;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto radians(T degree) -> T {
        constexpr T degree_as_radians = numbers::pi<T> / static_cast<T>(180);
        return degree * degree_as_radians;
    }
}
