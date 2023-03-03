#pragma once
#include <myl/numbers.hpp>

#include <cmath>
#include <limits>
#include <type_traits>

namespace myl {
	//@return Absolute value of v
	template<signed_number T>
	MYL_NO_DISCARD constexpr auto abs(T v) -> T {
		return v > static_cast<T>(0) ? v : -v;
	}

	//@return Absolute value of v
	template<unsigned_integer T>
	MYL_NO_DISCARD constexpr auto abs(T v) -> T {
		return v;
	}

	//@return Sign value as a integer
	template<signed_integer T>
	MYL_NO_DISCARD constexpr auto sign(const T v) -> T {
		return v == static_cast<T>(0) ? static_cast<T>(0) : v > static_cast<T>(0) ? static_cast<T>(1) : static_cast<T>(-1);
	}

	//@return Sign value as a integer
	template<unsigned_integer T>
	MYL_NO_DISCARD constexpr auto sign(const T v) -> T {
		return static_cast<T>(v != 0);
	}

	//@return Sign value as a floating pointer number
	template<floating_point T>
	MYL_NO_DISCARD constexpr auto sign(const T v) -> T { /// MYTodo: How to handle the i0, +0, -nan, +nan cases? plus approx?
		return static_cast<T>((0 < v) - (v < 0));
	}
	
	//@return If v is infinity
	template<floating_point T>
	MYL_NO_DISCARD constexpr auto is_infinity(T v) -> bool {
		return v == numbers::infinity<T> || v == numbers::negative_infinity<T>;
	}

	//@return If a is approximately b
	template<floating_point T>
	MYL_NO_DISCARD constexpr auto approx(T a, T b) -> bool {
		return abs(a - b) <= ((abs(a) < abs(b) ? abs(b) : abs(a)) * std::numeric_limits<T>::epsilon());
	}

	//@return If v is not a number
	template<floating_point T>
	MYL_NO_DISCARD constexpr auto is_nan(T v) -> bool {
		return std::isnan(v);
	}

	//@brief Calculates the greatest common divisor
	template<integer A, integer B>
	MYL_NO_DISCARD constexpr auto gcd(const A a, const B b) -> std::common_type_t<A, B> {
		using common = std::common_type_t<A, B>;
		using ucommon = make_unsigned<common>;

		ucommon ma = static_cast<ucommon>(abs(a));
		ucommon mb = static_cast<ucommon>(abs(b));

		if (ma == 0) return static_cast<common>(mb);
		if (mb == 0) return static_cast<common>(ma);

		while (mb != 0) {
			ucommon t = ma % mb;
			ma = mb;
			mb = t;
		}

		return ma;
	}

	//@brief Calculates the greatest common divisor
	template<integer A, integer B, integer... Args>
	MYL_NO_DISCARD constexpr auto gcd(const A a, const B b, const Args... args) -> std::common_type_t<A, B, Args...> {
		return gcd(gcd(a, b), args...);
	}

	//@brief Calculates the least common multible
	template<integer A, integer B>
	MYL_NO_DISCARD constexpr auto lcm(const A a, const B b) -> std::common_type_t<A, B> {
		using common = std::common_type_t<A, B>;
		using ucommon = make_unsigned<common>;

		const ucommon ma = static_cast<ucommon>(abs(a));
		const ucommon mb = static_cast<ucommon>(abs(b));
		if (ma == 0 || mb == 0)
			return 0;
		return static_cast<common>((ma / gcd(ma, mb)) * mb);
	}

	//@brief Calculates the least common multible
	template<integer A, integer B, integer... Args>
	MYL_NO_DISCARD constexpr auto lcm(const A a, const B b, const Args... args) -> std::common_type_t<A, B, Args...> {
		return lcm(lcm(a, b), args...);
	}
}