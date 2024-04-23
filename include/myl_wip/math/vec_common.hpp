#pragma once
#include <myl/math/vec_common.hpp>

namespace myl {
    template<usize C, typename T>
    MYL_NO_DISCARD constexpr auto reflect(const vec<C, T>& incident, const vec<C, T>& normal) -> vec<C, T> {
        return incident - normal * (dot(normal, incident) * static_cast<T>(2));
    }

    template<usize C, typename T>
    MYL_NO_DISCARD constexpr auto refract(const vec<C, T>& incident, const vec<C, T>& normal, T eta) -> vec<C, T> {
        const T d = dot(normal, incident);
        const T k = static_cast<T>(1) - eta * eta * (static_cast<T>(1) - d * d);
        return k < static_cast<T>(0) ? vec<C, T>(static_cast<T>(0)) : (incident * eta) - (normal * (eta * d + std::sqrt(k)));
    }
}
