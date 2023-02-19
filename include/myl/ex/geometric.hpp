#pragma once
#include <myl/defines.hpp> /// MYTemp: For #ifdef MYL_EXPERIMENTAL
#ifdef MYL_EXPERIMENTAL

#include <myl/math/vec2.hpp>

namespace myl {
	template<typename T>
	MYL_NO_DISCARD constexpr auto slope(const vec2<T>& a, const vec2<T>& b) -> T {
		return (b.y - a.y) / (b.x - a.x);
	}
}
#endif