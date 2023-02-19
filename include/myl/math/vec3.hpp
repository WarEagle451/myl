#pragma once
#include <myl/math/vec.hpp>

#include <utility> // std::move

namespace myl {
	template<typename T>
	struct vec<3, T> {
		using value_type = T;

		union {
			value_type data[3];
			struct { value_type x, y, z; };
			struct { value_type r, g, b; };
			struct { value_type s, t, p; };
			struct { value_type u, v, w; };
		};

		// Constructors

		constexpr vec() = default;

		constexpr explicit vec(const value_type& scalar)
			: data{ scalar, scalar, scalar } {}

		constexpr vec(const value_type& x, const value_type& y, const value_type& z)
			: data{ x, y, z } {}

		constexpr vec(value_type&& x, value_type&& y, value_type&& z)
			: data{ std::move(x), std::move(y), std::move(z) } {}

		// Vector conversion constructors

		constexpr explicit vec(const vec<2, value_type>& v, const value_type& z)
			: data{ v.x, v.y, z } {}

		constexpr explicit vec(const value_type& x, const vec<2, value_type>& v)
			: data{ x, v.x, v.y } {}

		constexpr explicit vec(const vec<4, value_type>& v)
			: data{ v.x, v.y, v.z } {}

		// Access operators

		MYL_NO_DISCARD constexpr auto operator[](usize i) -> value_type& { return data[i]; }
		MYL_NO_DISCARD constexpr auto operator[](usize i) const -> const value_type& { return data[i]; }

		// Comparison operators

		MYL_NO_DISCARD constexpr auto operator==(const vec& rhs) const -> bool { return x == rhs.x && y == rhs.y && z == rhs.z; }

		// Unary operators

		MYL_NO_DISCARD constexpr auto operator-() const -> vec { return vec{ -x, -y, -z }; }

		// Scaler operators

		MYL_NO_DISCARD constexpr auto operator+(const value_type& rhs) const -> vec { return vec{ x + rhs, y + rhs, z + rhs }; }
		MYL_NO_DISCARD constexpr auto operator-(const value_type& rhs) const -> vec { return vec{ x - rhs, y - rhs, z - rhs }; }
		MYL_NO_DISCARD constexpr auto operator*(const value_type& rhs) const -> vec { return vec{ x * rhs, y * rhs, z * rhs }; }
		MYL_NO_DISCARD constexpr auto operator/(const value_type& rhs) const -> vec { return vec{ x / rhs, y / rhs, z / rhs }; }
		MYL_NO_DISCARD constexpr auto operator%(const value_type& rhs) const -> vec { return vec{ x % rhs, y % rhs, z % rhs }; }

		constexpr auto operator+=(const value_type& rhs) -> vec& { x += rhs; y += rhs; z += rhs; return *this; }
		constexpr auto operator-=(const value_type& rhs) -> vec& { x -= rhs; y -= rhs; z -= rhs; return *this; }
		constexpr auto operator*=(const value_type& rhs) -> vec& { x *= rhs; y *= rhs; z *= rhs; return *this; }
		constexpr auto operator/=(const value_type& rhs) -> vec& { x /= rhs; y /= rhs; z /= rhs; return *this; }
		constexpr auto operator%=(const value_type& rhs) -> vec& { x %= rhs; y %= rhs; z %= rhs; return *this; }

		// vec2 operators
		MYL_NO_DISCARD constexpr auto operator+(const vec<2, value_type>& rhs) const -> vec { return vec{ x + rhs.x, y + rhs.y, z }; }
		MYL_NO_DISCARD constexpr auto operator-(const vec<2, value_type>& rhs) const -> vec { return vec{ x - rhs.x, y - rhs.y, z }; }
		MYL_NO_DISCARD constexpr auto operator*(const vec<2, value_type>& rhs) const -> vec { return vec{ x * rhs.x, y * rhs.y, z }; }
		MYL_NO_DISCARD constexpr auto operator/(const vec<2, value_type>& rhs) const -> vec { return vec{ x / rhs.x, y / rhs.y, z }; }
		MYL_NO_DISCARD constexpr auto operator%(const vec<2, value_type>& rhs) const -> vec { return vec{ x % rhs.x, y % rhs.y, z }; }

		constexpr auto operator+=(const vec<2, value_type>& rhs) -> vec& { x += rhs.x; y += rhs.y; return *this; }
		constexpr auto operator-=(const vec<2, value_type>& rhs) -> vec& { x -= rhs.x; y -= rhs.y; return *this; }
		constexpr auto operator*=(const vec<2, value_type>& rhs) -> vec& { x *= rhs.x; y *= rhs.y; return *this; }
		constexpr auto operator/=(const vec<2, value_type>& rhs) -> vec& { x /= rhs.x; y /= rhs.y; return *this; }
		constexpr auto operator%=(const vec<2, value_type>& rhs) -> vec& { x %= rhs.x; y %= rhs.y; return *this; }

		// vec3 operators

		MYL_NO_DISCARD constexpr auto operator+(const vec& rhs) const -> vec { return vec{ x + rhs.x, y + rhs.y, z + rhs.z }; }
		MYL_NO_DISCARD constexpr auto operator-(const vec& rhs) const -> vec { return vec{ x - rhs.x, y - rhs.y, z - rhs.z }; }
		MYL_NO_DISCARD constexpr auto operator*(const vec& rhs) const -> vec { return vec{ x * rhs.x, y * rhs.y, z * rhs.z }; }
		MYL_NO_DISCARD constexpr auto operator/(const vec& rhs) const -> vec { return vec{ x / rhs.x, y / rhs.y, z / rhs.z }; }
		MYL_NO_DISCARD constexpr auto operator%(const vec& rhs) const -> vec { return vec{ x % rhs.x, y % rhs.y, z % rhs.z }; }

		constexpr auto operator+=(const vec& rhs) -> vec& { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
		constexpr auto operator-=(const vec& rhs) -> vec& { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
		constexpr auto operator*=(const vec& rhs) -> vec& { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }
		constexpr auto operator/=(const vec& rhs) -> vec& { x /= rhs.x; y /= rhs.y; z /= rhs.z; return *this; }
		constexpr auto operator%=(const vec& rhs) -> vec& { x %= rhs.x; y %= rhs.y; z %= rhs.z; return *this; }

		// Implict conversion operators

		MYL_NO_DISCARD constexpr operator vec<2, value_type>() const { return vec<2, value_type>{ x, y }; }
		MYL_NO_DISCARD constexpr operator bool() const { return x == 0.f && y == 0.f && z == 0.f; }
	};

	template<typename T>
	MYL_NO_DISCARD constexpr auto dot(const vec<3, T>& a, const vec<3, T>& b) -> T {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto cross(const vec<3, T>& a, const vec<3, T>& b) -> vec<3, T> {
		return vec<3, T>(
			a.y * b.z - b.y * a.z,
			a.z * b.x - b.z * a.x,
			a.x * b.y - b.x * a.y);
	}

	template<typename T> MYL_NO_DISCARD constexpr auto operator<(const vec<3, T>& lhs, const vec<3, T>& rhs) -> bool { return dot(lhs, lhs) < dot(rhs, rhs); }
	template<typename T> MYL_NO_DISCARD constexpr auto operator>(const vec<3, T>& lhs, const vec<3, T>& rhs) -> bool { return dot(lhs, lhs) > dot(rhs, rhs); }
	template<typename T> MYL_NO_DISCARD constexpr auto operator<=(const vec<3, T>& lhs, const vec<3, T>& rhs) -> bool { return dot(lhs, lhs) <= dot(rhs, rhs); }
	template<typename T> MYL_NO_DISCARD constexpr auto operator>=(const vec<3, T>& lhs, const vec<3, T>& rhs) -> bool { return dot(lhs, lhs) >= dot(rhs, rhs); }

	template<typename T> using vec3 = vec<3, T>;

	using i8vec3 = vec3<i8>;
	using i16vec3 = vec3<i16>;
	using i32vec3 = vec3<i32>;
	using i64vec3 = vec3<i64>;

	using u8vec3 = vec3<u8>;
	using u16vec3 = vec3<u16>;
	using u32vec3 = vec3<u32>;
	using u64vec3 = vec3<u64>;

	using f32vec3 = vec3<f32>;
	using f64vec3 = vec3<f64>;
}

#ifdef MYL_DEFINE_TYPES
template<typename T> using vec3 = myl::vec3<T>;

using i8vec3 = myl::i8vec3;
using i16vec3 = myl::i16vec3;
using i32vec3 = myl::i32vec3;
using i64vec3 = myl::i64vec3;

using u8vec3 = myl::u8vec3;
using u16vec3 = myl::u16vec3;
using u32vec3 = myl::u32vec3;
using u64vec3 = myl::u64vec3;

using f32vec3 = myl::f32vec3;
using f64vec3 = myl::f64vec3;
#endif