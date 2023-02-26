#pragma once
#include <myl/math/vec.hpp>

#include <utility> // std::move

namespace myl {
	template<typename T>
	struct vec<4, T> {
		using value_type = T;

		union {
			value_type data[4];
			struct { value_type x, y, z, w; };
			struct { value_type r, g, b, a; };
			struct { value_type s, t, p, q; };
		};

		// Constructors

		MYL_NO_DISCARD constexpr vec() = default;

		MYL_NO_DISCARD constexpr explicit vec(const value_type& scalar)
			: data{ scalar, scalar, scalar, scalar } {}

		MYL_NO_DISCARD constexpr vec(const value_type& x, const value_type& y, const value_type& z, const value_type& w)
			: data{ x, y, z, w } {}

		MYL_NO_DISCARD constexpr vec(value_type&& x, value_type&& y, value_type&& z, value_type&& w)
			: data{ std::move(x), std::move(y), std::move(z), std::move(w) } {}

		// Vector conversion constructors

		MYL_NO_DISCARD constexpr explicit vec(const vec<2, value_type>& a, const vec<2, value_type>& b)
			: data{ a.x, a.y, b.x, b.y } {}

		MYL_NO_DISCARD constexpr explicit vec(const vec<2, value_type>& v, const value_type& z, const value_type& w)
			: data{ v.x, v.y, z, w } {}

		MYL_NO_DISCARD constexpr explicit vec(const value_type& x, const vec<2, value_type>& v, const value_type& w)
			: data{ x, v.x, v.y, w } {}

		MYL_NO_DISCARD constexpr explicit vec(const value_type& x, const value_type& y, const vec<2, value_type>& v)
			: data{ x, y, v.x, v.y } {}

		MYL_NO_DISCARD constexpr explicit vec(const vec<3, value_type>& v, const value_type& w)
			: data{ v.x, v.y, v.z, w } {}

		MYL_NO_DISCARD constexpr explicit vec(const value_type& x, const vec<3, value_type>& v)
			: data{ x, v.x, v.y, v.z } {}

		// Access operators

		MYL_NO_DISCARD constexpr auto operator[](usize i) -> value_type& { return data[i]; }
		MYL_NO_DISCARD constexpr auto operator[](usize i) const -> const value_type& { return data[i]; }

		// Comparison operators

		MYL_NO_DISCARD constexpr auto operator==(const vec& rhs) const -> bool { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w; }

		// Unary operators

		MYL_NO_DISCARD constexpr auto operator-() const -> vec { return vec{ -x, -y, -z, -w }; }

		// Scaler operators

		MYL_NO_DISCARD constexpr auto operator+(const value_type& rhs) const -> vec { return vec{ x + rhs, y + rhs, z + rhs, w + rhs }; }
		MYL_NO_DISCARD constexpr auto operator-(const value_type& rhs) const -> vec { return vec{ x - rhs, y - rhs, z - rhs, w - rhs }; }
		MYL_NO_DISCARD constexpr auto operator*(const value_type& rhs) const -> vec { return vec{ x * rhs, y * rhs, z * rhs, w * rhs }; }
		MYL_NO_DISCARD constexpr auto operator/(const value_type& rhs) const -> vec { return vec{ x / rhs, y / rhs, z / rhs, w / rhs }; }
		MYL_NO_DISCARD constexpr auto operator%(const value_type& rhs) const -> vec { return vec{ x % rhs, y % rhs, z % rhs, w % rhs }; }

		constexpr auto operator+=(const value_type& rhs) -> vec& { x += rhs; y += rhs; z += rhs; w += rhs; return *this; }
		constexpr auto operator-=(const value_type& rhs) -> vec& { x -= rhs; y -= rhs; z -= rhs; w -= rhs; return *this; }
		constexpr auto operator*=(const value_type& rhs) -> vec& { x *= rhs; y *= rhs; z *= rhs; w *= rhs; return *this; }
		constexpr auto operator/=(const value_type& rhs) -> vec& { x /= rhs; y /= rhs; z /= rhs; w /= rhs; return *this; }
		constexpr auto operator%=(const value_type& rhs) -> vec& { x %= rhs; y %= rhs; z %= rhs; w %= rhs; return *this; }

		// vec2 operators

		MYL_NO_DISCARD constexpr auto operator+(const vec<2, value_type>& rhs) const -> vec { return vec{ x + rhs.x, y + rhs.y, z, w }; }
		MYL_NO_DISCARD constexpr auto operator-(const vec<2, value_type>& rhs) const -> vec { return vec{ x - rhs.x, y - rhs.y, z, w }; }
		MYL_NO_DISCARD constexpr auto operator*(const vec<2, value_type>& rhs) const -> vec { return vec{ x * rhs.x, y * rhs.y, z, w }; }
		MYL_NO_DISCARD constexpr auto operator/(const vec<2, value_type>& rhs) const -> vec { return vec{ x / rhs.x, y / rhs.y, z, w }; }
		MYL_NO_DISCARD constexpr auto operator%(const vec<2, value_type>& rhs) const -> vec { return vec{ x % rhs.x, y % rhs.y, z, w }; }

		constexpr auto operator+=(const vec<2, value_type>& rhs) -> vec& { x += rhs.x; y += rhs.y; return *this; }
		constexpr auto operator-=(const vec<2, value_type>& rhs) -> vec& { x -= rhs.x; y -= rhs.y; return *this; }
		constexpr auto operator*=(const vec<2, value_type>& rhs) -> vec& { x *= rhs.x; y *= rhs.y; return *this; }
		constexpr auto operator/=(const vec<2, value_type>& rhs) -> vec& { x /= rhs.x; y /= rhs.y; return *this; }
		constexpr auto operator%=(const vec<2, value_type>& rhs) -> vec& { x %= rhs.x; y %= rhs.y; return *this; }

		// vec3 operators

		MYL_NO_DISCARD constexpr auto operator+(const vec<3, value_type>& rhs) const -> vec { return vec{ x + rhs.x, y + rhs.y, z + rhs.z, w }; }
		MYL_NO_DISCARD constexpr auto operator-(const vec<3, value_type>& rhs) const -> vec { return vec{ x - rhs.x, y - rhs.y, z - rhs.z, w }; }
		MYL_NO_DISCARD constexpr auto operator*(const vec<3, value_type>& rhs) const -> vec { return vec{ x * rhs.x, y * rhs.y, z * rhs.z, w }; }
		MYL_NO_DISCARD constexpr auto operator/(const vec<3, value_type>& rhs) const -> vec { return vec{ x / rhs.x, y / rhs.y, z / rhs.z, w }; }
		MYL_NO_DISCARD constexpr auto operator%(const vec<3, value_type>& rhs) const -> vec { return vec{ x % rhs.x, y % rhs.y, z % rhs.z, w }; }

		constexpr auto operator+=(const vec<3, value_type>& rhs) -> vec& { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
		constexpr auto operator-=(const vec<3, value_type>& rhs) -> vec& { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
		constexpr auto operator*=(const vec<3, value_type>& rhs) -> vec& { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }
		constexpr auto operator/=(const vec<3, value_type>& rhs) -> vec& { x /= rhs.x; y /= rhs.y; z /= rhs.z; return *this; }
		constexpr auto operator%=(const vec<3, value_type>& rhs) -> vec& { x %= rhs.x; y %= rhs.y; z %= rhs.z; return *this; }

		// vec4 operators

		MYL_NO_DISCARD constexpr auto operator+(const vec& rhs) const -> vec { return vec{ x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w }; }
		MYL_NO_DISCARD constexpr auto operator-(const vec& rhs) const -> vec { return vec{ x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w }; }
		MYL_NO_DISCARD constexpr auto operator*(const vec& rhs) const -> vec { return vec{ x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w }; }
		MYL_NO_DISCARD constexpr auto operator/(const vec& rhs) const -> vec { return vec{ x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w }; }
		MYL_NO_DISCARD constexpr auto operator%(const vec& rhs) const -> vec { return vec{ x % rhs.x, y % rhs.y, z % rhs.z, w % rhs.w }; }

		constexpr auto operator+=(const vec& rhs) -> vec& { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this; }
		constexpr auto operator-=(const vec& rhs) -> vec& { x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return *this; }
		constexpr auto operator*=(const vec& rhs) -> vec& { x *= rhs.x; y *= rhs.y; z *= rhs.z; w *= rhs.w; return *this; }
		constexpr auto operator/=(const vec& rhs) -> vec& { x /= rhs.x; y /= rhs.y; z /= rhs.z; w /= rhs.w; return *this; }
		constexpr auto operator%=(const vec& rhs) -> vec& { x %= rhs.x; y %= rhs.y; z %= rhs.z; w %= rhs.w; return *this; }

		// Implict conversion operators

		MYL_NO_DISCARD constexpr operator vec<2, value_type>() const { return vec<2, value_type>{ x, y }; }
		MYL_NO_DISCARD constexpr operator vec<3, value_type>() const { return vec<3, value_type>{ x, y, z }; }
		MYL_NO_DISCARD constexpr operator bool() const { return x == 0.f && y == 0.f && z == 0.f && w == 0.f; }
	};

	template<typename T>
	MYL_NO_DISCARD constexpr auto dot(const vec<4, T>& a, const vec<4, T>& b) -> T {
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	template<typename T> MYL_NO_DISCARD constexpr auto operator<(const vec<4, T>& lhs, const vec<4, T>& rhs) -> bool { return dot(lhs, lhs) < dot(rhs, rhs); }
	template<typename T> MYL_NO_DISCARD constexpr auto operator>(const vec<4, T>& lhs, const vec<4, T>& rhs) -> bool { return dot(lhs, lhs) > dot(rhs, rhs); }
	template<typename T> MYL_NO_DISCARD constexpr auto operator<=(const vec<4, T>& lhs, const vec<4, T>& rhs) -> bool { return dot(lhs, lhs) <= dot(rhs, rhs); }
	template<typename T> MYL_NO_DISCARD constexpr auto operator>=(const vec<4, T>& lhs, const vec<4, T>& rhs) -> bool { return dot(lhs, lhs) >= dot(rhs, rhs); }

#ifdef MYL_ENABLE_COMPONENT_WISE
	template<typename T>
	MYL_NO_DISCARD constexpr auto min(const vec<4, T>& v) -> T {
		return min(v.x, v.y, v.z, v.w);
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto max(const vec<4, T>& v) -> T {
		return max(v.x, v.y, v.z, v.w);
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto component_add(const vec<4, T>& v) -> T {
		return v.x + v.y + v.z + v.w;
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto component_multiply(const vec<4, T>& v) -> T {
		return v.x * v.y * v.z * v.w;
	}
#endif

	template<typename T> using vec4 = vec<4, T>;

	using i8vec4 = vec4<i8>;
	using i16vec4 = vec4<i16>;
	using i32vec4 = vec4<i32>;
	using i64vec4 = vec4<i64>;

	using u8vec4 = vec4<u8>;
	using u16vec4 = vec4<u16>;
	using u32vec4 = vec4<u32>;
	using u64vec4 = vec4<u64>;

	using f32vec4 = vec4<f32>;
	using f64vec4 = vec4<f64>;
}

#ifdef MYL_DEFINE_TYPES
template<typename T> using vec4 = myl::vec4<T>;

using i8vec4 = myl::i8vec4;
using i16vec4 = myl::i16vec4;
using i32vec4 = myl::i32vec4;
using i64vec4 = myl::i64vec4;

using u8vec4 = myl::u8vec4;
using u16vec4 = myl::u16vec4;
using u32vec4 = myl::u32vec4;
using u64vec4 = myl::u64vec4;

using f32vec4 = myl::f32vec4;
using f64vec4 = myl::f64vec4;
#endif