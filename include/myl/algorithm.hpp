#pragma once
#include <myl/definitions.hpp>
#include <myl/type.hpp>

#include <cmath>
#include <limits>

/// MYTODO: variadic functions should be able to take common types like int and float

namespace myl {
    template<floating_point T>
    MYL_NO_DISCARD constexpr auto approx(const T& a, const T& b) -> bool { /// MYTODO: This doesn't always work, refer to color test
        return b == std::nextafter(a, b);
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto min(const T& a, const T& b) -> const T& {
        return a < b ? a : b;
    }

    template<typename T, same_as<T>... Args>
    MYL_NO_DISCARD constexpr auto min(const T& a, const T& b, const Args&... args) -> const T& {
        return min(min(a, b), args...);
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto max(const T& a, const T& b) -> const T& {
        return a > b ? a : b;
    }

    template<typename T, same_as<T>... Args>
    MYL_NO_DISCARD constexpr auto max(const T& a, const T& b, const Args&... args) -> const T& {
        return max(max(a, b), args...);
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto clamp(const T& v, const T& min, const T& max) -> const T& {
        return v < min ? min : v > max ? max : v;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto floor(const T& v, const T& floor) -> const T& {
        return v > floor ? v : floor;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto ceil(const T& v, const T& ceil) -> const T& {
        return v > ceil ? ceil : v;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto difference(const T& a, const T& b) -> T {
        return a > b ? a - b : b - a;
    }
}
