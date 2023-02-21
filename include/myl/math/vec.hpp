#pragma once
#include <myl/math/common.hpp>

namespace myl {
	template<usize Size, typename Type> struct vec;

	template<usize S, typename T> MYL_NO_DISCARD constexpr auto dot(const vec<S, T>&, const vec<S, T>&) -> T;

	//@brief AKA magnitude
	template<usize S, typename T>
	MYL_NO_DISCARD constexpr auto length(const vec<S, T>& v) -> T {
		return myl::sqrt(dot(v, v));
	}

	template<usize S, typename T>
	MYL_NO_DISCARD constexpr auto distance(const vec<S, T>& a, const vec<S, T>& b) -> T {
		return myl::sqrt(dot(a, b));
	}

	template<usize S, typename T>
	MYL_NO_DISCARD constexpr auto normalize(const vec<S, T>& v) -> vec<S, T> {
		return v / length(v);
	}

	template<usize S, typename T>
	MYL_NO_DISCARD constexpr auto reflect(const vec<S, T>& incident, const vec<S, T>& normal) -> vec<S, T> {
		return incident - normal * (dot(normal, incident) * static_cast<T>(2));
	}

	template<usize S, typename T>
	MYL_NO_DISCARD constexpr auto reflect(const vec<S, T>& incident, const vec<S, T>& normal, T eta) -> vec<S, T> {
		const T d = dot(normal, incident);
		const T k = static_cast<T>(1) - eta * eta * (static_cast<T>(1) - d * d);
		return k < 0 ?
			vec<S, T>(0) :
			(incident * eta) - (normal * (eta * d + sqrt(k)));
	}
}