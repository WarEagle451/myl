#pragma once
#include <myl/algorithm.hpp>
#include <myl/type.hpp>

/// MYTODO: shaping.hpp
/// https://www.youtube.com/watch?v=YJB1QnEmlTs
/// - quadratic_ease_in
/// - quadratic_ease_out
/// - parabola
/// - triangle
/// - elastic_out
/// - elastic_in
/// - bounce_out
/// - bounce_in
/// - slerp

namespace myl {
    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto lerp(const T& a, const T& b, F percentage) -> T {
        return a + ((b - a) * percentage);
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto inverse_lerp(const T& a, const T& b, F value) -> T {
        return (value - a) / (b - a);
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto step(const T& edge, const T& value) -> T {
        return static_cast<T>(edge > value ? 0 : 1);
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto smoothstep(const T& edge0, const T& edge1, F value) -> T {
        const T t = clamp((value - edge0) / (edge1 - edge0), static_cast<T>(0), static_cast<T>(1));
        return t * t * (static_cast<T>(3) - static_cast<T>(2) * t);
    }
}
