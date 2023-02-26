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

	template<typename T>
	MYL_NO_DISCARD constexpr auto orthographic_lh(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T> {
#ifdef MYL_FORCE_DEPTH_ZERO_TO_ONE
		return orthographic_lh_01(left, right, bottom, top, near, far);
#else
		return orthographic_lh_11(left, right, bottom, top, near, far);
#endif
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto orthographic_rh(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T> {
#ifdef MYL_FORCE_DEPTH_ZERO_TO_ONE
		return orthographic_rh_01(left, right, bottom, top, near, far);
#else
		return orthographic_rh_11(left, right, bottom, top, near, far);
#endif
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto perspective_lh(T fovy, T aspect, T near, T far) -> mat4x4<T> {
#ifdef MYL_FORCE_DEPTH_ZERO_TO_ONE
		return perspective_lh_01(fovy, aspect, near, far);
#else
		return perspective_lh_11(fovy, aspect, near, far);
#endif
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto perspective_rh(T fovy, T aspect, T near, T far) -> mat4x4<T> {
#ifdef MYL_FORCE_DEPTH_ZERO_TO_ONE
		return perspective_rh_01(fovy, aspect, near, far);
#else
		return perspective_rh_11(fovy, aspect, near, far);
#endif
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto orthographic_01(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T> {
#ifdef MYL_FORCE_RIGHT_HANDED
		return orthographic_rh_01(left, right, bottom, top, near, far);
#else
		return orthographic_lh_01(left, right, bottom, top, near, far);
#endif
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto orthographic_11(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T> {
#ifdef MYL_FORCE_RIGHT_HANDED
		return orthographic_rh_11(left, right, bottom, top, near, far);
#else
		return orthographic_lh_11(left, right, bottom, top, near, far);
#endif
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto perspective_01(T fovy, T aspect, T near, T far) -> mat4x4<T> {
#ifdef MYL_FORCE_RIGHT_HANDED
		return perspective_rh_01(fovy, aspect, near, far);
#else
		return perspective_lh_01(fovy, aspect, near, far);
#endif
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto perspective_11(T fovy, T aspect, T near, T far) -> mat4x4<T> {
#ifdef MYL_FORCE_RIGHT_HANDED
		return perspective_rh_11(fovy, aspect, near, far);
#else
		return perspective_lh_11(fovy, aspect, near, far);
#endif
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto orthographic(T left, T right, T bottom, T top, T near, T far) -> mat4x4<T> {
#ifdef MYL_FORCE_RIGHT_HANDED
		return orthographic_rh(left, right, bottom, top, near, far);
#else
		return orthographic_lh(left, right, bottom, top, near, far);
#endif
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto perspective(T fovy, T aspect, T near, T far) -> mat4x4<T> {
#ifdef MYL_FORCE_RIGHT_HANDED
		return perspective_rh(fovy, aspect, near, far);
#else
		return perspective_lh(fovy, aspect, near, far);
#endif
	}
}