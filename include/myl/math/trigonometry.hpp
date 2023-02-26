#pragma once
#include <myl/numbers.hpp>
#include <myl/math/exponential.hpp>

#include <cmath>

namespace myl {
	template<number T> MYL_NO_DISCARD constexpr auto degrees(T radian) -> T { return (static_cast<T>(180) / numbers::pi<T>) * radian; }
	template<number T> MYL_NO_DISCARD constexpr auto radians(T degree) -> T { return degree * (numbers::pi<T> / static_cast<T>(180)); }

	template<number T> MYL_NO_DISCARD constexpr auto sin(T radian) -> T { return std::sin(radian); }
	template<number T> MYL_NO_DISCARD constexpr auto cos(T radian) -> T { return std::cos(radian); }
	template<number T> MYL_NO_DISCARD constexpr auto tan(T radian) -> T { return std::tan(radian); }

	template<number T> MYL_NO_DISCARD constexpr auto asin(T arc) -> T { return std::asin(arc); }
	template<number T> MYL_NO_DISCARD constexpr auto acos(T arc) -> T { return std::acos(arc); }
	template<number T> MYL_NO_DISCARD constexpr auto atan(T arc) -> T { return std::atan(arc); }

	template<number T> MYL_NO_DISCARD constexpr auto sinh(T radian) -> T { return std::sinh(radian); }
	template<number T> MYL_NO_DISCARD constexpr auto cosh(T radian) -> T { return std::cosh(radian); }
	template<number T> MYL_NO_DISCARD constexpr auto tanh(T radian) -> T { return std::tanh(radian); }

	template<number T> MYL_NO_DISCARD constexpr auto asinh(T arc) -> T { return std::asinh(arc); }
	template<number T> MYL_NO_DISCARD constexpr auto acosh(T arc) -> T { return std::acosh(arc); }
	template<number T> MYL_NO_DISCARD constexpr auto atanh(T arc) -> T { return std::atanh(arc); }

	template<number T>
	MYL_NO_DISCARD constexpr auto hypotenuse(const T a, const T b) -> T {
		return sqrt(a * a + b * b);
	}
}