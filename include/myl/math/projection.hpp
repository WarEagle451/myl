#pragma once
#include <myl/math/mat4x4.hpp>

#include <cmath>

/// MYTodo: look_at

namespace myl {
    template<typename T>
    MYL_NO_DISCARD constexpr auto orthographic_lh_01(T left, T right, T bottom, T top, T z_near, T z_far) -> mat4<T> {
        const T rl = right - left;
        const T tb = top - bottom;
        const T fn = z_far - z_near;
        return mat4<T>(
            static_cast<T>(2) / rl, 0, 0, -(right + left) / rl,
            0, static_cast<T>(2) / tb, 0, -(top + bottom) / tb,
            0, 0, static_cast<T>(1) / fn, -z_near / fn,
            0, 0, 0, 1
        );
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto orthographic_lh_11(T left, T right, T bottom, T top, T z_near, T z_far) -> mat4<T> {
        const T rl = right - left;
        const T tb = top - bottom;
        const T fn = z_far - z_near;
        return mat4<T>(
            static_cast<T>(2) / rl, 0, 0, -(right + left) / rl,
            0, static_cast<T>(2) / tb, 0, -(top + bottom) / tb,
            0, 0, static_cast<T>(2) / fn, -(z_far + z_near) / fn,
            0, 0, 0, 1
        );
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto orthographic_rh_01(T left, T right, T bottom, T top, T z_near, T z_far) -> mat4<T> {
        const T rl = right - left;
        const T tb = top - bottom;
        const T fn = z_far - z_near;
        return mat4<T>(
            static_cast<T>(2) / rl, 0, 0, -(right + left) / rl,
            0, static_cast<T>(2) / tb, 0, -(top + bottom) / tb,
            0, 0, -static_cast<T>(1) / fn, -z_near / fn,
            0, 0, 0, 1
        );
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto orthographic_rh_11(T left, T right, T bottom, T top, T z_near, T z_far) -> mat4<T> {
        const T rl = right - left;
        const T tb = top - bottom;
        const T fn = z_far - z_near;
        return mat4<T>(
            static_cast<T>(2) / rl, 0, 0, -(right + left) / rl,
            0, static_cast<T>(2) / tb, 0, -(top + bottom) / tb,
            0, 0, -static_cast<T>(2) / fn, -(z_far + z_near) / fn,
            0, 0, 0, 1
        );
    }

    template<typename T>
    MYL_NO_DISCARD constexpr inline auto orthographic_lh(T left, T right, T bottom, T top, T z_near, T z_far) -> mat4<T> {
#ifdef MYL_FORCE_DEPTH_NEGATIVE_ONE_TO_ONE
        return orthographic_lh_11(left, right, bottom, top, z_near, z_far);
#else
        return orthographic_lh_01(left, right, bottom, top, z_near, z_far);
#endif
    }

    template<typename T>
    MYL_NO_DISCARD constexpr inline auto orthographic_rh(T left, T right, T bottom, T top, T z_near, T z_far) -> mat4<T> {
#ifdef MYL_FORCE_DEPTH_NEGATIVE_ONE_TO_ONE
        return orthographic_rh_11(left, right, bottom, top, z_near, z_far);
#else
        return orthographic_rh_01(left, right, bottom, top, z_near, z_far);
#endif
    }

    template<typename T>
    MYL_NO_DISCARD constexpr inline auto orthographic_01(T left, T right, T bottom, T top, T z_near, T z_far) -> mat4<T> {
#ifdef MYL_FORCE_RIGHT_HANDED
        return orthographic_rh_01(left, right, bottom, top, z_near, z_far);
#else
        return orthographic_lh_01(left, right, bottom, top, z_near, z_far);
#endif
    }

    template<typename T>
    MYL_NO_DISCARD constexpr inline auto orthographic_11(T left, T right, T bottom, T top, T z_near, T z_far) -> mat4<T> {
#ifdef MYL_FORCE_RIGHT_HANDED
        return orthographic_rh_11(left, right, bottom, top, z_near, z_far);
#else
        return orthographic_lh_11(left, right, bottom, top, z_near, z_far);
#endif
    }

    template<typename T>
    MYL_NO_DISCARD constexpr inline auto orthographic(T left, T right, T bottom, T top, T z_near, T z_far) -> mat4<T> {
#ifdef MYL_FORCE_RIGHT_HANDED
        return orthographic_rh(left, right, bottom, top, z_near, z_far);
#else
        return orthographic_lh(left, right, bottom, top, z_near, z_far);
#endif
    }

    /// fovy is radians

    template<typename T>
    MYL_NO_DISCARD constexpr auto perspective_lh_01(T fovy, T aspect, T z_near, T z_far) -> mat4<T> {
        const T focal_length = static_cast<T>(1) / std::tan(fovy * static_cast<T>(.5));
        const T k = z_far / (z_far - z_near);
        return mat4<T>(
            focal_length / aspect, 0, 0, 0,
            0, focal_length, 0, 0,
            0, 0, k, -z_near * k,
            0, 0, 1, 0
        );
    }

    /// fovy is radians

    template<typename T>
    MYL_NO_DISCARD constexpr auto perspective_lh_11(T fovy, T aspect, T z_near, T z_far) -> mat4<T> {
        const T focal_length = static_cast<T>(1) / std::tan(fovy * static_cast<T>(.5));
        const T fn = z_far - z_near;
        return mat4<T>(
            focal_length / aspect, 0, 0, 0,
            0, focal_length, 0, 0,
            0, 0, (z_far + z_near) / fn, -static_cast<T>(2) * z_far * z_near / fn,
            0, 0, 1, 0
        );
    }

    /// fovy is radians

    template<typename T>
    MYL_NO_DISCARD constexpr auto perspective_rh_01(T fovy, T aspect, T z_near, T z_far) -> mat4<T> {
        const T focal_length = static_cast<T>(1) / std::tan(fovy * static_cast<T>(.5));
        return mat4<T>(
            focal_length / aspect, 0, 0, 0,
            0, focal_length, 0, 0,
            0, 0, z_far / (z_near - z_far), -z_far * z_near / (z_far - z_near),
            0, 0, -1, 0
        );
    }

    /// fovy is radians

    template<typename T>
    MYL_NO_DISCARD constexpr auto perspective_rh_11(T fovy, T aspect, T z_near, T z_far) -> mat4<T> {
        const T focal_length = static_cast<T>(1) / std::tan(fovy * static_cast<T>(.5));
        const T fn = z_far - z_near;
        return mat4<T>(
            focal_length / aspect, 0, 0, 0,
            0, focal_length, 0, 0,
            0, 0, -(z_far + z_near) / fn, -static_cast<T>(2) * z_far * z_near / fn,
            0, 0, -1, 0
        );
    }

    /// fovy is radians

    template<typename T>
    MYL_NO_DISCARD constexpr inline auto perspective_lh(T fovy, T aspect, T z_near, T z_far) -> mat4<T> {
#ifdef MYL_FORCE_DEPTH_NEGATIVE_ONE_TO_ONE
        return perspective_lh_11(fovy, aspect, z_near, z_far);
#else
        return perspective_lh_01(fovy, aspect, z_near, z_far);
#endif
    }

    /// fovy is radians

    template<typename T>
    MYL_NO_DISCARD constexpr inline auto perspective_rh(T fovy, T aspect, T z_near, T z_far) -> mat4<T> {
#ifdef MYL_FORCE_DEPTH_NEGATIVE_ONE_TO_ONE
        return perspective_rh_11(fovy, aspect, z_near, z_far);
#else
        return perspective_rh_01(fovy, aspect, z_near, z_far);
#endif
    }

    /// fovy is radians

    template<typename T>
    MYL_NO_DISCARD constexpr inline auto perspective_01(T fovy, T aspect, T z_near, T z_far) -> mat4<T> {
#ifdef MYL_FORCE_RIGHT_HANDED
        return perspective_rh_01(fovy, aspect, z_near, z_far);
#else
        return perspective_lh_01(fovy, aspect, z_near, z_far);
#endif
    }

    /// fovy is radians

    template<typename T>
    MYL_NO_DISCARD constexpr inline auto perspective_11(T fovy, T aspect, T z_near, T z_far) -> mat4<T> {
#ifdef MYL_FORCE_RIGHT_HANDED
        return perspective_rh_11(fovy, aspect, z_near, z_far);
#else
        return perspective_lh_11(fovy, aspect, z_near, z_far);
#endif
    }

    /// fovy is radians

    template<typename T>
    MYL_NO_DISCARD constexpr inline auto perspective(T fovy, T aspect, T z_near, T z_far) -> mat4<T> {
#ifdef MYL_FORCE_RIGHT_HANDED
        return perspective_rh(fovy, aspect, z_near, z_far);
#else
        return perspective_lh(fovy, aspect, z_near, z_far);
#endif
    }
}
