#pragma once
#include <myl/definitions.hpp>

#include <cmath>

namespace myl {
    template<usize Components, typename Type> struct vec;

    template<usize C, typename T>
    MYL_NO_DISCARD consteval auto component_count(const vec<C, T>&) -> usize {
        return C;
    }
    
    template<usize C, typename T>
    MYL_NO_DISCARD constexpr auto dot(const vec<C, T>& a, const vec<C, T>& b) -> T;

    template<usize C, typename T>
    MYL_NO_DISCARD constexpr auto length(const vec<C, T>& v) -> T {
        return std::sqrt(dot(v, v));
    }

    template<usize C, typename T>
    MYL_NO_DISCARD constexpr auto normalize(const vec<C, T>& v) -> vec<C, T> {
        return v / length(v);
    }

    template<usize C, typename T>
    MYL_NO_DISCARD constexpr auto distance(const vec<C, T>& a, const vec<C, T>& b) -> T {
        return std::sqrt(dot(a, b));
    }
    
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

    ///template<usize C, typename T>
    ///MYL_NO_DISCARD constexpr auto operator<=>(const vec<C, T>& l, const vec<C, T>& r) -> bool {
    ///    return dot(l, l) <=> dot(r, r);
    ///}

    template<usize C, typename T>
    MYL_NO_DISCARD constexpr auto operator<(const vec<C, T>& l, const vec<C, T>& r) -> bool {
        return dot(l, l) < dot(r, r);
    }

    template<usize C, typename T>
    MYL_NO_DISCARD constexpr auto operator>(const vec<C, T>& l, const vec<C, T>& r) -> bool {
        return dot(l, l) > dot(r, r);
    }

    template<usize C, typename T>
    MYL_NO_DISCARD constexpr auto operator<=(const vec<C, T>& l, const vec<C, T>& r) -> bool {
        return dot(l, l) <= dot(r, r);
    }

    template<usize C, typename T>
    MYL_NO_DISCARD constexpr auto operator>=(const vec<C, T>& l, const vec<C, T>& r) -> bool {
        return dot(l, l) >= dot(r, r);
    }
}
