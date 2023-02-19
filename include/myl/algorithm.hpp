#pragma once
#include <myl/defines.hpp>

/// Algorithm
/// - sign
/// - round

namespace myl {
	template<typename T>
	MYL_NO_DISCARD constexpr auto min(const T a, const T b) -> T {
		return a > b ? b : a;
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto max(const T a, const T b) -> T {
		return a > b ? a : b;
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto clamp(const T value, const T min, const T max) -> T {
		return value < min ? min : value > max ? max : value;
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto floor(const T value, const T floor) -> T {
		return value > floor ? value : floor;
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto ceil(const T value, const T ceil) -> T {
		return value > ceil ? ceil : value;
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto difference(const T a, const T b) -> T {
		return a > b ? a - b : b - a;
	}
}