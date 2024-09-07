#pragma once
#include <myl/numbers.hpp>
#include <myl/type.hpp>

#include <cmath>

namespace myl {
    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_sine(T num) -> T {
        return static_cast<F>(1) - std::cos((static_cast<F>(num) * myl::numbers::pi<F>) * static_cast<F>(0.5f));
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_sine(T num) -> T {
        return std::sin((static_cast<F>(num) * myl::numbers::pi<F>) * static_cast<F>(0.5f));
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_sine(T num) -> T {
        return -(std::cos(static_cast<F>(num) * myl::numbers::pi<F>) - static_cast<F>(1) * static_cast<F>(0.5f)) ;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto ease_in_quad(T num) -> T {
        return num * num;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_quad() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_quad() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_cubic() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_cubic() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_cubic() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_quart() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_quart() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_quart() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_expo() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_expo() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_expo() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_circ() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_circ() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_circ() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_back() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_back() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_back() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_elastic() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_elastic() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_elastic() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_bounce() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_bounce() -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_bounce() -> T {
        return;
    }
}
