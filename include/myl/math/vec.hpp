#pragma once
#include <myl/math/common.hpp>
#include <myl/math/exponential.hpp>

#ifdef MYL_ENABLE_COMPONENT_WISE
#	include <myl/algorithm.hpp>
#endif

namespace myl {
	template<usize Components, typename Type> struct vec;

	template<usize C, typename T> MYL_NO_DISCARD constexpr auto dot(const vec<C, T>&, const vec<C, T>&) -> T;

#ifdef MYL_ENABLE_COMPONENT_WISE
	template<usize C, typename T> MYL_NO_DISCARD constexpr auto min(const vec<C, T>&) -> T;
	template<usize C, typename T> MYL_NO_DISCARD constexpr auto max(const vec<C, T>&) -> T;
	template<usize C, typename T> MYL_NO_DISCARD constexpr auto component_add(const vec<C, T>&) -> T;
	template<usize C, typename T> MYL_NO_DISCARD constexpr auto component_multiply(const vec<C, T>&) -> T;
#endif

	//@brief AKA magnitude
	template<usize C, typename T>
	MYL_NO_DISCARD constexpr auto length(const vec<C, T>& v) -> T {
		return myl::sqrt(dot(v, v));
	}

	template<usize C, typename T>
	MYL_NO_DISCARD constexpr auto distance(const vec<C, T>& a, const vec<C, T>& b) -> T {
		return myl::sqrt(dot(a, b));
	}

	template<usize C, typename T>
	MYL_NO_DISCARD constexpr auto normalize(const vec<C, T>& v) -> vec<C, T> {
		return v / length(v);
	}

	template<usize C, typename T>
	MYL_NO_DISCARD constexpr auto reflect(const vec<C, T>& incident, const vec<C, T>& normal) -> vec<C, T> {
		return incident - normal * (dot(normal, incident) * static_cast<T>(2));
	}

	template<usize C, typename T>
	MYL_NO_DISCARD constexpr auto refract(const vec<C, T>& incident, const vec<C, T>& normal, T eta) -> vec<C, T> {
		const T d = dot(normal, incident);
		const T k = static_cast<T>(1) - eta * eta * (static_cast<T>(1) - d * d);
		return k < 0 ?
			vec<C, T>(0) :
			(incident * eta) - (normal * (eta * d + sqrt(k)));
	}
}