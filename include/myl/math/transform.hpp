#pragma once
#include <myl/math/mat4x4.hpp>
#include <myl/math/vec3.hpp>

#include <cmath>

/// MYTodo: Transform.hpp
/// pitch, yaw, roll
/// rotation, scale
/// shear
/// reflection
/// decompose with shear
/// decompose with quaternions
/// rotate on an axis eg. axis (1, 1, 0) and rotate by 90 degrees, like glm

namespace myl {
    template<typename T>
    MYL_NO_DISCARD constexpr auto translation(const mat4<T>& transform) -> vec3<T> {
        return vec3<T>(transform[3]) / transform[3][3];
    }

    /// MYTODO: extracts rotation, should this output a quat?
    ///template<typename T>
    ///MYL_NO_DISCARD constexpr auto rotation(const mat4<T>& transform) -> vec3<T> {
    ///
    ///}
    
    /// MYTODO: extracts scale
    ///template<typename T>
    ///MYL_NO_DISCARD constexpr auto scale_factor(const mat4<T>& transform) -> vec3<T> {
    ///
    ///}

    template<typename T>
    constexpr auto decompose(const mat4<T>& transform, vec3<T>* out_translation, vec3<T>* out_rotation, vec3<T>* out_scale) -> void {
        // Normalize the matrix
        mat4<T> m = transform / transform[3][3];
        
        // Translation
        if (out_translation != nullptr)
            *out_translation = vec3<T>(m[3]);

        // Scale
        vec3<T> ca(m[0]);
        vec3<T> cb(m[1]);
        vec3<T> cc(m[2]);

        // Detect and correct negative scale
        if (vec3<T> v{ cross(cb, cc) }; dot(ca, v) < static_cast<T>(0)) {
            ca *= static_cast<T>(-1);
            cb *= static_cast<T>(-1);
            cc *= static_cast<T>(-1);
        }

        const T lca = length(ca);
        const T lcb = length(cb);
        const T lcc = length(cc);

        if (out_scale != nullptr)
            *out_scale = vec3<T>{ lca, lcb, lcc };

        // Rotation
        if (out_rotation != nullptr) {
            ca /= lca;
            cb /= lcb;
            cc /= lcc;

            T cy = std::asin(-ca.z);
            *out_rotation = std::cos(cy) == static_cast<T>(0) ?
                vec3<T>{ std::atan2(-cc.x, cb.y), cy, static_cast<T>(0) } :
                vec3<T>{ std::atan2(cb.z, cc.z), cy, std::atan2(ca.y, ca.x) };
        }
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto translate(const vec3<T>& translation, const mat4<T>& m = mat4<T>::identity()) -> mat4<T> {
        return mat4<T>(
            m[0],
            m[1],
            m[2],
            m[0] * translation[0] + m[1] * translation[1] + m[2] * translation[2] + m[3]
        );
    }

    /// rotation is in radian eler angles

    template<typename T>
    MYL_NO_DISCARD constexpr auto rotate_lh(const vec3<T>& rotation, const mat4<T>& m = mat4<T>::identity()) -> mat4<T> {
        const T cx = std::cos(rotation.x);
        const T cy = std::cos(rotation.y);
        const T cz = std::cos(rotation.z);
        const T sx = std::sin(rotation.x);
        const T sy = std::sin(rotation.y);
        const T sz = std::sin(rotation.z);

        return m * mat4<T>(
            cy * cz, sx * sy * cz - cx * sz, cx * sy * cz + sx * sz, 0,
            cy * sz, sx * sy * sz + cx * cz, cx * sy * sz - sx * cz, 0,
            -sy, sx * cy, cx * cy, 0,
            0, 0, 0, 1
        );
    }

    /// rotation is in radian eler angles

    template<typename T>
    MYL_NO_DISCARD constexpr auto rotate_rh(const vec3<T>& rotation, const mat4<T>& m = mat4<T>::identity()) -> mat4<T> {
        const T cx = std::cos(rotation.x);
        const T cy = std::cos(rotation.y);
        const T cz = std::cos(rotation.z);
        const T sx = std::sin(rotation.x);
        const T sy = std::sin(rotation.y);
        const T sz = std::sin(rotation.z);

        return m * mat4<T>(
            cy * cz, cy * sz, -sy, 0,
            sx * sy * cz - cx * sz, sx * sy * sz + cx * cz, sx * cy, 0,
            cx * sy * cz + sx * sz, cx * sy * sz - sx * cz, cx * cy, 0,
            0, 0, 0, 1
        );
    }

    /// rotation is in radian eler angles

    template<typename T>
    MYL_NO_DISCARD constexpr inline auto rotate(const vec3<T>& rotation, const mat4<T>& m = mat4<T>::identity()) -> mat4<T> {
#ifdef MYL_FORCE_RIGHT_HANDED
        return rotate_rh(rotation, m);
#else
        return rotate_lh(rotation, m);
#endif
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto scale(const vec3<T>& scale, const mat4<T>& m = mat4<T>::identity()) -> mat4<T> {
        return mat4<T>(
            m[0] * scale[0],
            m[1] * scale[1],
            m[2] * scale[2],
            m[3]
        );
    }

    /// rotation is in radian eler angles

    template<typename T>
    MYL_NO_DISCARD constexpr auto create_transform(const vec3<T>& translation, const vec3<T>& rotation, const vec3<T>& scale) -> mat4<T> {
        return translate(translation) * rotate(rotation) * myl::scale(scale);
    }
}
