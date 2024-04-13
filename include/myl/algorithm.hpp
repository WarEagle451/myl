#pragma once
#include <myl/definitions.hpp>
#include <myl/type.hpp>

#ifdef min // War on Microsoft's min macro
#   undef min
#endif

#ifdef max // War on Microsoft's max macro
#   undef max
#endif

namespace myl {
    template<typename T>
    MYL_NO_DISCARD constexpr auto min(const T a, const T b) -> T {
        return a < b ? a : b;
    }

    template<typename T, same_as<T>... Args>
    MYL_NO_DISCARD constexpr auto min(const T a, const T b, const Args... args) -> T {
        return min(min(a, b), args...);
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto max(const T a, const T b) -> T {
        return a > b ? a : b;
    }

    template<typename T, same_as<T>... Args>
    MYL_NO_DISCARD constexpr auto max(const T a, const T b, const Args... args) -> T {
        return max(max(a, b), args...);
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto clamp(const T v, const T min, const T max) -> T {
        return v < min ? min : v > max ? max : v;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto floor(const T v, const T floor) -> T {
        return v > floor ? v : floor;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto ceil(const T v, const T ceil) -> T {
        return v > ceil ? ceil : v;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto difference(const T a, const T b) -> T {
        return a > b ? a - b : b - a;
    }
}
