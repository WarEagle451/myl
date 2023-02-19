#pragma once
#include <myl/defines.hpp>

/// MYTodo: shape.hpp
/// https://iquilezles.org/articles/functions/

namespace myl {
	template<typename FloatingPoint, typename T>
	MYL_NO_DISCARD constexpr auto lerp(T a, T b, FloatingPoint percentage) -> FloatingPoint {
		return static_cast<FloatingPoint>(a) + static_cast<FloatingPoint>(b - a) * percentage;
	}

	template<typename FloatingPoint = f32, typename T>
	MYL_NO_DISCARD constexpr auto inverse_lerp(T a, T b, T value) -> FloatingPoint {
		return static_cast<FloatingPoint>(value - a) / static_cast<FloatingPoint>(b - a);
	}

	template<typename FloatingPoint = f32, typename T>
	MYL_NO_DISCARD constexpr auto smoothstep(T value) -> FloatingPoint {
		FloatingPoint a = static_cast<FloatingPoint>(value * value);
		FloatingPoint b = static_cast<FloatingPoint>(1) - (static_cast<FloatingPoint>(1) - static_cast<FloatingPoint>(value)) * (static_cast<FloatingPoint>(1) - static_cast<FloatingPoint>(value));
		return lerp<FloatingPoint>(a, b, value);
	}
}