#pragma once
#include <myl/algorithm.hpp>

namespace myl {
	template<typename T = f32>
	MYL_NO_DISCARD constexpr auto lerp(T a, T b, T percentage) -> T {
		return a + ((b - a) * percentage);
	}

	template<typename T = f32>
	MYL_NO_DISCARD constexpr auto inverse_lerp(T a, T b, T value) -> T {
		return (value - a) / (b - a);
	}


	template<typename T>
	MYL_NO_DISCARD constexpr auto step(T edge, T a) -> T {
		return edge > a ? 0 : 1;
	}

	template<typename T = f32>
	MYL_NO_DISCARD constexpr auto smoothstep(T edge0, T edge1, T c) -> T {
		const T t = clamp<T>((c - edge0) / (edge1 - edge0), static_cast<T>(0), static_cast<T>(1));
		return t * t * (static_cast<T>(3) - static_cast<T>(2) * t);
	}
}