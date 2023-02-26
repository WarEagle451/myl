#pragma once
#include <myl/math/exponential.hpp>
#include <myl/math/mat3x3.hpp>
#include <myl/math/mat4x4.hpp>
#include <myl/math/trigonometry.hpp>

#include <utility> // std::move

/// MYTodo: Finish quaternion functions
/// - Normal
/// - Normalize
/// - Slerp
/// - cross
/// - Operators

namespace myl {
	template<typename T> struct quat {
		using value_type = T;

		union {
			value_type data[4];
			struct { value_type w, x, y, z; };
		};

		// Utilities

		MYL_NO_DISCARD static constexpr auto identity() -> quat { return quat{ 1, 0, 0, 0 }; }

		// Constructors

		MYL_NO_DISCARD constexpr quat()
			: quat(0) {}

		MYL_NO_DISCARD explicit constexpr quat(const value_type& scalar)
			: data{ scalar, 0, 0, 0 } {}

		MYL_NO_DISCARD constexpr quat(const value_type& w, const value_type& x, const value_type& y, const value_type& z)
			: data{ w, x, y, z } {}

		MYL_NO_DISCARD constexpr quat(value_type&& w, value_type&& x, value_type&& y, value_type&& z)
			: data{ std::move(w), std::move(x), std::move(y), std::move(z) } {}

		//@brief Constructs a quaternion from euler angles (pitch, yaw, roll) in radians
		MYL_NO_DISCARD explicit constexpr quat(const vec3<value_type>& euler) {
			value_type cx = cos(euler.x * static_cast<value_type>(.5));
			value_type cy = cos(euler.y * static_cast<value_type>(.5));
			value_type cz = cos(euler.z * static_cast<value_type>(.5));
			value_type sx = sin(euler.x * static_cast<value_type>(.5));
			value_type sy = sin(euler.y * static_cast<value_type>(.5));
			value_type sz = sin(euler.z * static_cast<value_type>(.5));

			w = cx * cy * cz + sx * sy * sz;
			x = sx * cy * cz - cx * sy * sz;
			y = cx * sy * cz + sx * cy * sz;
			z = cx * cy * sz - sx * sy * cz;
		}

		// Access operators

		MYL_NO_DISCARD constexpr auto operator[](usize i) -> value_type& { return data[i]; }
		MYL_NO_DISCARD constexpr auto operator[](usize i) const -> const value_type& { return data[i]; }

		// Comparison operators

		MYL_NO_DISCARD constexpr auto operator==(const quat& rhs) const -> bool { return w == rhs.w && x == rhs.x && y == rhs.y && z == rhs.z; }

		// Unary operators

		MYL_NO_DISCARD constexpr auto operator-() const -> quat { return quat{ -w, -x, -y, -z }; }

		// Scaler operators

		///MYL_NO_DISCARD constexpr auto operator+(const value_type& rhs) const -> quat { return; }
		///MYL_NO_DISCARD constexpr auto operator-(const value_type& rhs) const -> quat { return; }
		MYL_NO_DISCARD constexpr auto operator*(const value_type& rhs) const -> quat { return quat{ w * rhs, x * rhs, y * rhs, z * rhs }; }
		MYL_NO_DISCARD constexpr auto operator/(const value_type& rhs) const -> quat { return quat{ w / rhs, x / rhs, y / rhs, z / rhs }; }
		///MYL_NO_DISCARD constexpr auto operator%(const value_type& rhs) const -> quat { return; }

		///constexpr auto operator+=(const value_type& rhs) -> quat& { ; return *this; }
		///constexpr auto operator-=(const value_type& rhs) -> quat& { ; return *this; }
		constexpr auto operator*=(const value_type& rhs) -> quat& { w *= rhs; x *= rhs; y *= rhs; z *= rhs; return *this; }
		constexpr auto operator/=(const value_type& rhs) -> quat& { w /= rhs; x /= rhs; y /= rhs; z /= rhs; return *this; }
		///constexpr auto operator%=(const value_type& rhs) -> quat& { ; return *this; }

		// Vec3 operators

		///MYL_NO_DISCARD constexpr auto operator+(const vec3<value_type>& rhs) const -> vec3<value_type> { return; }
		///MYL_NO_DISCARD constexpr auto operator-(const vec3<value_type>& rhs) const -> vec3<value_type> { return; }
		MYL_NO_DISCARD constexpr auto operator*(const vec3<value_type>& rhs) const -> vec3<value_type> {
			vec3<value_type> quat_vec{ x, y, z };
			vec3<value_type> uv(cross(quat_vec, rhs));
			vec3<value_type> uuv(cross(quat_vec, uv));
			
			return rhs + (( uv * w) + uuv) * static_cast<value_type>(2);
		}

		///MYL_NO_DISCARD constexpr auto operator/(const vec3<value_type>& rhs) const -> vec3<value_type> { return; }
		///MYL_NO_DISCARD constexpr auto operator%(const vec3<value_type>& rhs) const -> vec3<value_type> { return; }

		// Vec4 operators

		///MYL_NO_DISCARD constexpr auto operator+(const vec4<value_type>& rhs) const -> vec4<value_type> { return; }
		///MYL_NO_DISCARD constexpr auto operator-(const vec4<value_type>& rhs) const -> vec4<value_type> { return; }
		MYL_NO_DISCARD constexpr auto operator*(const vec4<value_type>& rhs) const -> vec4<value_type> { return vec4<value_type>(*this * vec3<value_type>(rhs), rhs.w); }
		///MYL_NO_DISCARD constexpr auto operator/(const vec4<value_type>& rhs) const -> vec4<value_type> { return; }
		///MYL_NO_DISCARD constexpr auto operator%(const vec4<value_type>& rhs) const -> vec4<value_type> { return; }
		
		// Quaternion operators

		MYL_NO_DISCARD constexpr auto operator+(const quat& rhs) const -> quat { return quat{ w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z }; }
		MYL_NO_DISCARD constexpr auto operator-(const quat& rhs) const -> quat { return quat{ w - rhs.w, x - rhs.x, y - rhs.y, z - rhs.z }; }
		MYL_NO_DISCARD constexpr auto operator*(const quat& rhs) const -> quat {
			return quat{
				w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z,
				w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
				w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z,
				w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x };
		}

		///MYL_NO_DISCARD constexpr auto operator/(const quat& rhs) const -> quat { return; }
		///MYL_NO_DISCARD constexpr auto operator%(const quat& rhs) const -> quat { return; }

		constexpr auto operator+=(const quat& rhs) -> quat& { w += rhs.w; x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
		constexpr auto operator-=(const quat& rhs) -> quat& { w -= rhs.w; x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
		constexpr auto operator*=(const quat& rhs) -> quat& { return *this = (*this * rhs); }
		///constexpr auto operator/=(const quat& rhs) -> quat& { ; return *this; }
		///constexpr auto operator%=(const quat& rhs) -> quat& { ; return *this; }
	};

	template<typename T>
	MYL_NO_DISCARD constexpr auto conjugate(const quat<T>& q) -> quat<T> {
		return quat<T>{ q.w, -q.x, -q.y, -q.z };
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto dot(const quat<T>& a, const quat<T>& b) -> T {
		return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto length(const quat<T>& q) -> T {
		return sqrt(dot(q, q));
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto inverse(const quat<T>& q) -> quat<T> {
		return conjugate(q) * (static_cast<T>(1) / dot(q, q));
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto to_mat3(const quat<T>& q) -> mat3<T> {
		const T xx = q.x * q.x;
		const T yy = q.y * q.y;
		const T zz = q.z * q.z;
		const T xz = q.x * q.z;
		const T xy = q.x * q.y;
		const T yz = q.y * q.z;
		const T wx = q.w * q.x;
		const T wy = q.w * q.y;
		const T wz = q.w * q.z;
		
		return mat3<T>(
			static_cast<T>(1) - static_cast<T>(2) * (yy + zz), static_cast<T>(2) * (xy - wz), static_cast<T>(2) * (xz + wy),
			static_cast<T>(2) * (xy + wz), static_cast<T>(1) - static_cast<T>(2) * (xx + zz), static_cast<T>(2) * (yz - wx),
			static_cast<T>(2) * (xz - wy), static_cast<T>(2) * (yz + wx), static_cast<T>(1) - static_cast<T>(2) * (xx + yy));
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto to_mat4(const quat<T>& q) -> mat4<T> { /// MYTodo: let Matrix conversion constructors take care of it
		mat3<T> m(to_mat3(q));
		return mat4<T>{
			mat4<T>::col_type(m[0], 0),
			mat4<T>::col_type(m[1], 0),
			mat4<T>::col_type(m[2], 0),
			mat4<T>::col_type(0, 0, 0, 1) };
	}

	//@brief Rotate a vec3 by a quaternion
	template<typename T>
	MYL_NO_DISCARD constexpr auto rotate(const quat<T>& q, const vec3<T>& v) -> vec3<T> { return q * v; }

	//@brief Rotate a vec4 by a quaternion
	template<typename T>
	MYL_NO_DISCARD constexpr auto rotate(const quat<T>& q, const vec4<T>& v) -> vec3<T> { return q * v; }

	//@brief Extracts the right orientation from a quaternion
	template<typename T>
	MYL_NO_DISCARD constexpr auto right(const quat<T>& q) -> vec3<T> { return q * vec3<T>{ 1, 0, 0 }; }

	//@brief Extracts the left orientation from a quaternion
	template<typename T>
	MYL_NO_DISCARD constexpr auto left(const quat<T>& q) -> vec3<T> { return -right(q); }

	//@brief Extracts the up orientation from a quaternion
	template<typename T>
	MYL_NO_DISCARD constexpr auto up(const quat<T>& q) -> vec3<T> { return q * vec3<T>{ 0, 1, 0 }; }

	//@brief Extracts the down orientation from a quaternion
	template<typename T>
	MYL_NO_DISCARD constexpr auto down(const quat<T>& q) -> vec3<T> { return -up(q); }

	//@brief Extracts the forward orientation from a quaternion
	template<typename T>
	MYL_NO_DISCARD constexpr auto forward(const quat<T>& q) -> vec3<T> { return q * vec3<T>{ 0, 0, 1 }; }

	//@brief Extracts the backward orientation from a quaternion
	template<typename T>
	MYL_NO_DISCARD constexpr auto backward(const quat<T>& q) -> vec3<T> { return -forward(q); }
	
	using i8quat = quat<i8>;
	using i16quat = quat<i16>;
	using i32quat = quat<i32>;
	using i64quat = quat<i64>;

	using u8quat = quat<u8>;
	using u16quat = quat<u16>;
	using u32quat = quat<u32>;
	using u64quat = quat<u64>;

	using f32quat = quat<f32>;
	using f64quat = quat<f64>;
}

#ifdef MYL_DEFINE_TYPES
template<typename T> using quat = myl::quat<T>;

using i8quat = myl::i8quat;
using i16quat = myl::i16quat;
using i32quat = myl::i32quat;
using i64quat = myl::i64quat;

using u8quat = myl::u8quat;
using u16quat = myl::u16quat;
using u32quat = myl::u32quat;
using u64quat = myl::u64quat;

using f32quat = myl::f32quat;
using f64quat = myl::f64quat;
#endif