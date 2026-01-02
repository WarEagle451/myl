#pragma once
#include <myl/numbers.hpp>
#include <myl/type.hpp>

#include <cmath>

namespace myl {
    ///MYTODO: Enable simd

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_sine(T x) -> T {
        return static_cast<F>(1) - std::cos((static_cast<F>(x) * myl::numbers::pi<F>) * static_cast<F>(0.5f));
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_sine(T x) -> T {
        return std::sin((static_cast<F>(x) * myl::numbers::pi<F>) * static_cast<F>(0.5));
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_sine(T x) -> T {
        return -(std::cos(static_cast<F>(x) * myl::numbers::pi<F>) - static_cast<F>(1) * static_cast<F>(0.5)) ;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto ease_in_quad(T x) -> T {
        return x * x;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_quad(T x) -> T {
        return static_cast<F>(1) - (static_cast<F>(1) - x) * (static_cast<F>(1) - x);
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_quad(T x) -> T {
        return x < static_cast<F>(0.5) ?
            static_cast<F>(2) * ease_in_quad(x) :
            static_cast<F>(1) - std::pow<F, F>(static_cast<F>(-2) * x + static_cast<F>(2), static_cast<F>(2)) / static_cast<F>(2);
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto ease_in_cubic(T x) -> T {
        return x * x * x;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_cubic(T x) -> T {
        return static_cast<F>(1) - std::pow<F, F>(static_cast<F>(1) - x, static_cast<F>(3));
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_cubic(T x) -> T {
        return x < static_cast<F>(0.5) ?
            static_cast<F>(4) * ease_in_cubic(x) :
            static_cast<F>(1) - std::pow<F, F>(static_cast<F>(-2) * x + static_cast<F>(2), static_cast<F>(3)) / static_cast<F>(2);
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto ease_in_quart(T x) -> T {
        return x * x * x * x;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_quart(T x) -> T {
        return static_cast<F>(1) - std::pow<F, F>(static_cast<F>(1) - x, static_cast<F>(4));
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_quart(T x) -> T {
        return x < static_cast<F>(0.5) ?
            static_cast<F>(8) * ease_in_quart(x) :
            static_cast<F>(1) - std::pow<F, F>(static_cast<F>(-2) * x + static_cast<F>(2), static_cast<F>(4)) / static_cast<F>(2);
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto ease_in_quint(T x) -> T {
        return x * x * x * x * x;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_quint(T x) -> T {
        return static_cast<F>(1) - std::pow<F, F>(static_cast<F>(1) - x, static_cast<F>(5));
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_quint(T x) -> T {
        return x < static_cast<F>(0.5) ?
            static_cast<F>(16) * ease_in_quint(x) :
            static_cast<F>(1) - std::pow<F, F>(static_cast<F>(-2) * x + static_cast<F>(2), static_cast<F>(5)) / static_cast<F>(2);
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_expo(T x) -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_expo(T x) -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_expo(T x) -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_circ(T x) -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_circ(T x) -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_circ(T x) -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_back(T x) -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_back(T x) -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_back(T x) -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_elastic(T x) -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_elastic(T x) -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_elastic(T x) -> T {
        return;
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_bounce(T x) -> T {
        return static_cast<F>(1) - ease_out_bounce(static_cast<F>(1) - x);
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_out_bounce(T x) -> T {
        constexpr n = static_cast<F>(7.5625);
        constexpr d = static_cast<F>(2.75);

        if (x < static_cast<F>(1) / d)
            return n * x * x;
        else if (x < static_cast<F>(2) / d) {
            x -= static_cast<F>(1.5);
            return n * (x / d) * x + static_cast<F>(0.75);
        }
        else if (x < static_cast<F>(2.5) / d) {
            x -= static_cast<F>(2.25);
            return n * (x / d) * x + static_cast<F>(0.9375);
        }
        else {
            x -= static_cast<F>(2.625);
            return n * (x / d) * x + static_cast<F>(0.984375);
        }
    }

    template<typename T, floating_point F = f32>
    MYL_NO_DISCARD constexpr auto ease_in_out_bounce(T x) -> T {
        return;
    }
}
