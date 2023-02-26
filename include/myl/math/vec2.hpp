#pragma once
#include <myl/math/vec.hpp>

#include <utility> // std::move

namespace myl {
	template<typename T>
	struct vec<2, T> {
		using value_type = T;

		union {
			value_type data[2];
			struct { value_type x, y; };
			struct { value_type r, g; };
			struct { value_type s, t; };
			struct { value_type u, v; };
			struct { value_type w, h; };
		};

		// Constructors

		constexpr vec() = default;

		constexpr explicit vec(const value_type& scalar)
			: data{ scalar, scalar } {}

		constexpr vec(const value_type& x, const value_type& y)
			: data{ x, y } {}

		constexpr vec(value_type&& x, value_type&& y)
			: data{ std::move(x), std::move(y) } {}

		// Vector conversion constructors

		constexpr explicit vec(const vec<3, value_type>& v)
			: data{ v.x, v.y } {}

		constexpr explicit vec(const vec<4, value_type>& v)
			: data{ v.x, v.y } {}

		// Access operators

		MYL_NO_DISCARD constexpr auto operator[](usize i) -> value_type& { return data[i]; }
		MYL_NO_DISCARD constexpr auto operator[](usize i) const -> const value_type& { return data[i]; }

		// Comparison operators

		MYL_NO_DISCARD constexpr auto operator==(const vec& rhs) const -> bool { return x == rhs.x && y == rhs.y; }

		// Unary operators

		MYL_NO_DISCARD constexpr auto operator-() const -> vec { return vec{ -x, -y }; }

		// Scaler operators

		MYL_NO_DISCARD constexpr auto operator+(const value_type& rhs) const -> vec { return vec(x + rhs, y + rhs); }
		MYL_NO_DISCARD constexpr auto operator-(const value_type& rhs) const -> vec { return vec(x - rhs, y - rhs); }
		MYL_NO_DISCARD constexpr auto operator*(const value_type& rhs) const -> vec { return vec(x * rhs, y * rhs); }
		MYL_NO_DISCARD constexpr auto operator/(const value_type& rhs) const -> vec { return vec(x / rhs, y / rhs); }
		MYL_NO_DISCARD constexpr auto operator%(const value_type& rhs) const -> vec { return vec(x % rhs, y % rhs); }

		constexpr auto operator+=(const value_type& rhs) -> vec& { x += rhs; y += rhs; return *this; }
		constexpr auto operator-=(const value_type& rhs) -> vec& { x -= rhs; y -= rhs; return *this; }
		constexpr auto operator*=(const value_type& rhs) -> vec& { x *= rhs; y *= rhs; return *this; }
		constexpr auto operator/=(const value_type& rhs) -> vec& { x /= rhs; y /= rhs; return *this; }
		constexpr auto operator%=(const value_type& rhs) -> vec& { x %= rhs; y %= rhs; return *this; }

		// vec2 operators

		MYL_NO_DISCARD constexpr auto operator+(const vec& rhs) const -> vec { return vec(x + rhs.x, y + rhs.y); }
		MYL_NO_DISCARD constexpr auto operator-(const vec& rhs) const -> vec { return vec(x - rhs.x, y - rhs.y); }
		MYL_NO_DISCARD constexpr auto operator*(const vec& rhs) const -> vec { return vec(x * rhs.x, y * rhs.y); }
		MYL_NO_DISCARD constexpr auto operator/(const vec& rhs) const -> vec { return vec(x / rhs.x, y / rhs.y); }
		MYL_NO_DISCARD constexpr auto operator%(const vec& rhs) const -> vec { return vec(x % rhs.x, y % rhs.y); }

		constexpr auto operator+=(const vec& rhs) -> vec& { x += rhs.x; y += rhs.y; return *this; }
		constexpr auto operator-=(const vec& rhs) -> vec& { x -= rhs.x; y -= rhs.y; return *this; }
		constexpr auto operator*=(const vec& rhs) -> vec& { x *= rhs.x; y *= rhs.y; return *this; }
		constexpr auto operator/=(const vec& rhs) -> vec& { x /= rhs.x; y /= rhs.y; return *this; }
		constexpr auto operator%=(const vec& rhs) -> vec& { x %= rhs.x; y %= rhs.y; return *this; }

		// Implict conversion operators

		MYL_NO_DISCARD constexpr operator bool() const { return x == 0.f && y == 0.f; }
	};

	template<typename T>
	MYL_NO_DISCARD constexpr auto dot(const vec<2, T>& a, const vec<2, T>& b) -> T {
		return a.x * b.x + a.y * b.y;
	}

	template<typename T> MYL_NO_DISCARD constexpr auto operator<(const vec<2, T>& lhs, const vec<2, T>& rhs) -> bool { return dot(lhs, lhs) < dot(rhs, rhs); }
	template<typename T> MYL_NO_DISCARD constexpr auto operator>(const vec<2, T>& lhs, const vec<2, T>& rhs) -> bool { return dot(lhs, lhs) > dot(rhs, rhs); }
	template<typename T> MYL_NO_DISCARD constexpr auto operator<=(const vec<2, T>& lhs, const vec<2, T>& rhs) -> bool { return dot(lhs, lhs) <= dot(rhs, rhs); }
	template<typename T> MYL_NO_DISCARD constexpr auto operator>=(const vec<2, T>& lhs, const vec<2, T>& rhs) -> bool { return dot(lhs, lhs) >= dot(rhs, rhs); }

#ifdef MYL_ENABLE_COMPONENT_WISE
	template<typename T>
	MYL_NO_DISCARD constexpr auto min(const vec<2, T>& v) -> T {
		return min(v.x, v.y);
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto max(const vec<2, T>& v) -> T {
		return max(v.x, v.y);
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto component_add(const vec<2, T>& v) -> T {
		return v.x + v.y;
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto component_multiply(const vec<2, T>& v) -> T {
		return v.x * v.y;
	}
#endif

	template<typename T> using vec2 = vec<2, T>;

	using i8vec2 = vec2<i8>;
	using i16vec2 = vec2<i16>;
	using i32vec2 = vec2<i32>;
	using i64vec2 = vec2<i64>;

	using u8vec2 = vec2<u8>;
	using u16vec2 = vec2<u16>;
	using u32vec2 = vec2<u32>;
	using u64vec2 = vec2<u64>;

	using f32vec2 = vec2<f32>;
	using f64vec2 = vec2<f64>;
}

#ifdef MYL_DEFINE_TYPES
template<typename T> using vec2 = myl::vec2<T>;

using i8vec2 = myl::i8vec2;
using i16vec2 = myl::i16vec2;
using i32vec2 = myl::i32vec2;
using i64vec2 = myl::i64vec2;

using u8vec2 = myl::u8vec2;
using u16vec2 = myl::u16vec2;
using u32vec2 = myl::u32vec2;
using u64vec2 = myl::u64vec2;

using f32vec2 = myl::f32vec2;
using f64vec2 = myl::f64vec2;
#endif