#pragma once
#include <myl/constants.hpp>
#include <myl/defines.hpp>

#include <cmath>

namespace myl {
	template<typename T> MYL_NO_DISCARD constexpr auto degrees(T radian) -> T { return (static_cast<T>(180) / constants::pi<T>) * radian; }
	template<typename T> MYL_NO_DISCARD constexpr auto radians(T degree) -> T { return degree * (constants::pi<T> / static_cast<T>(180)); }

	template<typename T> MYL_NO_DISCARD constexpr auto sin(T radian) -> T { return std::sin(radian); }
	template<typename T> MYL_NO_DISCARD constexpr auto cos(T radian) -> T { return std::cos(radian); }
	template<typename T> MYL_NO_DISCARD constexpr auto tan(T radian) -> T { return std::tan(radian); }

	template<typename T> MYL_NO_DISCARD constexpr auto asin(T arc) -> T { return std::asin(arc); }
	template<typename T> MYL_NO_DISCARD constexpr auto acos(T arc) -> T { return std::acos(arc); }
	template<typename T> MYL_NO_DISCARD constexpr auto atan(T arc) -> T { return std::atan(arc); }
}