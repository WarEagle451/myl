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
}