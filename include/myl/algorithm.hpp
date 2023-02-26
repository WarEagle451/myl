#pragma once
#include <myl/defines.hpp>

#ifdef min // War on Microsof's min macro
#  undef min
#endif

#ifdef max // War on Microsof's max macro
#  undef max
#endif

namespace myl {
	//@return The smallest number
	template<comparable T>
	MYL_NO_DISCARD constexpr auto min(const T a, const T b) -> T {
		return a < b ? a : b;
	}

	//@return The smallest number
	template<comparable T, same_as<T>... Args>
	MYL_NO_DISCARD constexpr auto min(const T a, const T b, const Args... args) -> T {
		return min(min(a, b), args...);
	}

	//@return The biggest number
	template<comparable T>
	MYL_NO_DISCARD constexpr auto max(const T a, const T b) -> T {
		return a > b ? a : b;
	}

	//@return The biggest number
	template<comparable T, same_as<T>... Args>
	MYL_NO_DISCARD constexpr auto max(const T a, const T b, const Args... args) -> T {
		return max(max(a, b), args...);
	}

	//@return A number between min and max
	template<comparable T>
	MYL_NO_DISCARD constexpr auto clamp(const T v, const T min, const T max) -> T {
		return v < min ? min : v > max ? max : v;
	}

	//@return v if v > floor
	template<comparable T>
	MYL_NO_DISCARD constexpr auto floor(const T v, const T floor) -> T {
		return v > floor ? v : floor;
	}

	//@return v if v < ceil
	template<comparable T>
	MYL_NO_DISCARD constexpr auto ceil(const T v, const T ceil) -> T {
		return v > ceil ? ceil : v;
	}

	//@return the difference between 2 types
	template<typename T>
	MYL_NO_DISCARD constexpr auto difference(const T a, const T b) -> T {
		return a > b ? a - b : b - a;
	}
}