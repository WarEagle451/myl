#pragma once
#include <myl/math/mat4x4.hpp>
#include <myl/math/trigonometry.hpp>
#include <myl/math/vec3.hpp>

/// MYTodo: look_at

namespace myl {
	//@brief Creates a left hand orthographic projection matrix. Near and far clip planes are in normalized device coordinates of 0 and 1
	template<typename T>
	MYL_NO_DISCARD constexpr auto orthographic_lh_01(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T> {
		const T rl = right - left;
		const T tb = top - bottom;
		const T fn = far - near;
		return mat4x4<T>(
			static_cast<T>(2) / rl, 0, 0, -(right + left) / rl,
			0, static_cast<T>(2) / tb, 0, -(top + bottom) / tb,
			0, 0, static_cast<T>(1) / fn, -near / fn,
			0, 0, 0, 1);
	}

	//@brief Creates a left hand orthographic projection matrix. Near and far clip planes are in normalized device coordinates of -1 and 1
	template<typename T>
	MYL_NO_DISCARD constexpr auto orthographic_lh_11(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T> {
		const T rl = right - left;
		const T tb = top - bottom;
		const T fn = far - near;
		return mat4x4<T>(
			static_cast<T>(2) / rl, 0, 0, -(right + left) / rl,
			0, static_cast<T>(2) / tb, 0, -(top + bottom) / tb,
			0, 0, static_cast<T>(2) / fn, -(far + near) / fn,
			0, 0, 0, 1);
	}

	//@brief Creates a right hand orthographic projection matrix. Near and far clip planes are in normalized device coordinates of 0 and 1
	template<typename T>
	MYL_NO_DISCARD constexpr auto orthographic_rh_01(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T> {
		const T rl = right - left;
		const T tb = top - bottom;
		const T fn = far - near;
		return mat4x4<T>(
			static_cast<T>(2) / rl, 0, 0, -(right + left) / rl,
			0, static_cast<T>(2) / tb, 0, -(top + bottom) / tb,
			0, 0, -static_cast<T>(1) / fn, -near / fn,
			0, 0, 0, 1);
	}

	//@brief Creates a right hand orthographic projection matrix. Near and far clip planes are in normalized device coordinates of -1 and 1
	template<typename T>
	MYL_NO_DISCARD constexpr auto orthographic_rh_11(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T> {
		const T rl = right - left;
		const T tb = top - bottom;
		const T fn = far - near;
		return mat4x4<T>(
			static_cast<T>(2) / rl, 0, 0, -(right + left) / rl,
			0, static_cast<T>(2) / tb, 0, -(top + bottom) / tb,
			0, 0, -static_cast<T>(2) / fn, -(far + near) / fn,
			0, 0, 0, 1);
	}

	//@param fovy: Radians
	//@brief Creates a left hand perspective projection matrix. Near and far clip planes are in normalized device coordinates of 0 and 1
	template<typename T>
	MYL_NO_DISCARD constexpr auto perspective_lh_01(T fovy, T aspect, T near, T far) -> mat4x4<T> {
		const T focal_length = static_cast<T>(1) / tan(fovy * static_cast<T>(.5));
		const T k = far / (far - near);
		return mat4x4<T>(
			focal_length / aspect, 0, 0, 0,
			0, focal_length, 0, 0,
			0, 0, k, -near * k,
			0, 0, 1, 0);
	}

	//@param fovy: Radians
	//@brief Creates a left hand perspective projection matrix. Near and far clip planes are in normalized device coordinates of -1 and 1
	template<typename T>
	MYL_NO_DISCARD constexpr auto perspective_lh_11(T fovy, T aspect, T near, T far) -> mat4x4<T> {
		const T focal_length = static_cast<T>(1) / tan(fovy * static_cast<T>(.5));
		const T fn = far - near;
		return mat4x4<T>(
			focal_length / aspect, 0, 0, 0,
			0, focal_length, 0, 0,
			0, 0, (far + near) / fn, -static_cast<T>(2) * far * near / fn,
			0, 0, 1, 0);
	}

	//@param fovy: Radians
	//@brief Creates a right hand perspective projection matrix. Near and far clip planes are in normalized device coordinates of 0 and 1
	template<typename T>
	MYL_NO_DISCARD constexpr auto perspective_rh_01(T fovy, T aspect, T near, T far) -> mat4x4<T> {
		const T focal_length = static_cast<T>(1) / tan(fovy * static_cast<T>(.5));
		return mat4x4<T>(
			focal_length / aspect, 0, 0, 0,
			0, focal_length, 0, 0,
			0, 0, far / (near - far), -far * near / (far - near),
			0, 0, -1, 0);
	}

	//@param fovy: Radians
	//@brief Creates a right hand perspective projection matrix. Near and far clip planes are in normalized device coordinates of -1 and 1
	template<typename T>
	MYL_NO_DISCARD constexpr auto perspective_rh_11(T fovy, T aspect, T near, T far) -> mat4x4<T> {
		const T focal_length = static_cast<T>(1) / tan(fovy * static_cast<T>(.5));
		const T fn = far - near;
		return mat4x4<T>(
			focal_length / aspect, 0, 0, 0,
			0, focal_length, 0, 0,
			0, 0, -(far + near) / fn, -static_cast<T>(2) * far * near / fn,
			0, 0, -1, 0);
	}

	///template<typename T>
	///MYL_NO_DISCARD constexpr auto look_at_lh(const vec3<T>& target, const vec3<T>& eye, const vec3<T>& up) -> mat4x4<T> {
	///
	///}
	
	///template<typename T>
	///MYL_NO_DISCARD constexpr auto look_at_rh(const vec3<T>& target, const vec3<T>& eye, const vec3<T>& up) -> mat4x4<T> {
	///
	///}

#ifdef MYL_FORCE_DEPTH_ZERO_TO_ONE
	template<typename T> MYL_NO_DISCARD constexpr auto orthographic_lh(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T>	{ return orthographic_lh_01(left, right, bottom, top, near, far); }
	template<typename T> MYL_NO_DISCARD constexpr auto perspective_lh(T fovy, T aspect, T near, T far) -> mat4x4<T>						{ return perspective_lh_01(fovy, aspect, near, far); }
	///template<typename T> MYL_NO_DISCARD constexpr auto look_at_lh(const vec3<T>& target, const vec3<T>& eye, const vec3<T>& up) -> mat4x4<T>	{ return look_at_lh_01(target, eye, up); }

	template<typename T> MYL_NO_DISCARD constexpr auto orthographic_rh(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T>	{ return orthographic_rh_01(left, right, bottom, top, near, far); }
	template<typename T> MYL_NO_DISCARD constexpr auto perspective_rh(T fovy, T aspect, T near, T far) -> mat4x4<T>						{ return perspective_rh_01(fovy, aspect, near, far); }
	///template<typename T> MYL_NO_DISCARD constexpr auto look_at_rh(const vec3<T>& target, const vec3<T>& eye, const vec3<T>& up) -> mat4x4<T>	{ return look_at_rh_01(target, eye, up); }
#else
	template<typename T> MYL_NO_DISCARD constexpr auto orthographic_lh(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T>	{ return orthographic_lh_11(left, right, bottom, top, near, far); }
	template<typename T> MYL_NO_DISCARD constexpr auto perspective_lh(T fovy, T aspect, T near, T far) -> mat4x4<T>						{ return perspective_lh_11(fovy, aspect, near, far); }
	///template<typename T> MYL_NO_DISCARD constexpr auto look_at_lh(const vec3<T>& target, const vec3<T>& eye, const vec3<T>& up) -> mat4x4<T>	{ return look_at_lh_11(target, eye, up); }

	template<typename T> MYL_NO_DISCARD constexpr auto orthographic_rh(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T>	{ return orthographic_rh_11(left, right, bottom, top, near, far); }
	template<typename T> MYL_NO_DISCARD constexpr auto perspective_rh(T fovy, T aspect, T near, T far) -> mat4x4<T>						{ return perspective_rh_11(fovy, aspect, near, far); }
	///template<typename T> MYL_NO_DISCARD constexpr auto look_at_rh(const vec3<T>& target, const vec3<T>& eye, const vec3<T>& up) -> mat4x4<T>	{ return look_at_rh_11(target, eye, up); }
#endif

#ifdef MYL_FORCE_RIGHT_HANDED
	template<typename T> MYL_NO_DISCARD constexpr auto orthographic_01(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T>	{ return orthographic_rh_01(left, right, bottom, top, near, far); }
	template<typename T> MYL_NO_DISCARD constexpr auto orthographic_11(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T>	{ return orthographic_rh_11(left, right, bottom, top, near, far); }

	template<typename T> MYL_NO_DISCARD constexpr auto perspective_01(T fovy, T aspect, T near, T far) -> mat4x4<T>	{ return perspective_rh_01(fovy, aspect, near, far); }
	template<typename T> MYL_NO_DISCARD constexpr auto perspective_11(T fovy, T aspect, T near, T far) -> mat4x4<T>	{ return perspective_rh_11(fovy, aspect, near, far); }

	template<typename T> MYL_NO_DISCARD constexpr auto orthographic(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T> 	{ return orthographic_rh(left, right, bottom, top, near, far); }
	template<typename T> MYL_NO_DISCARD constexpr auto perspective(T fovy, T aspect, T near, T far) -> mat4x4<T> 					{ return perspective_rh(fovy, aspect, near, far); }
	///template<typename T> MYL_NO_DISCARD constexpr auto look_at(const vec3<T>& target, const vec3<T>& eye, const vec3<T>& up) -> mat4x4<T> 	{ return look_at_rh(target, eye, up); }
#else
	template<typename T> MYL_NO_DISCARD constexpr auto orthographic_01(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T>	{ return orthographic_lh_01(left, right, bottom, top, near, far); }
	template<typename T> MYL_NO_DISCARD constexpr auto orthographic_11(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T>	{ return orthographic_lh_11(left, right, bottom, top, near, far); }

	template<typename T> MYL_NO_DISCARD constexpr auto perspective_01(T fovy, T aspect, T near, T far) -> mat4x4<T>	{ return perspective_lh_01(fovy, aspect, near, far); }
	template<typename T> MYL_NO_DISCARD constexpr auto perspective_11(T fovy, T aspect, T near, T far) -> mat4x4<T>	{ return perspective_lh_11(fovy, aspect, near, far); }

	template<typename T> MYL_NO_DISCARD constexpr auto orthographic(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T> 	{ return orthographic_lh(left, right, bottom, top, near, far); }
	template<typename T> MYL_NO_DISCARD constexpr auto perspective(T fovy, T aspect, T near, T far) -> mat4x4<T> 					{ return perspective_lh(fovy, aspect, near, far); }
	///template<typename T> MYL_NO_DISCARD constexpr auto look_at(const vec3<T>& target, const vec3<T>& eye, const vec3<T>& up) -> mat4x4<T> 	{ return look_at_lh(target, eye, up); }
#endif
}