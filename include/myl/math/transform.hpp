#pragma once
#include <myl/math/mat4x4.hpp>
#include <myl/math/trigonometry.hpp>
#include <myl/math/quaternion.hpp>
#include <myl/math/vec3.hpp>

/// MYTodo: Transform.hpp
/// pitch, yaw, roll
/// rotation, scale
/// shear
/// reflection
/// decompose with shear
/// decompose with quaternions

namespace myl {
	//@brief Extracts the translation from a transform matrix
	//@param transform: Matrix to extract the translation from 
	//@return The translation vector
	template<typename T>
	MYL_NO_DISCARD constexpr auto translation(const mat4x4<T>& transform) -> vec3<T> {
		return vec3<T>(transform[3]) / transform[3][3];
	}

	//@brief Decomposes a matrix into it's translation, rotation and scale vectors
	//@param transform: Transform to decompose
	//@param translation: Vector to assign the translation vector
	//@param rotation: Vector to assign the rotation vector
	//@param scale: Vector to assign the scale vector
	template<typename T>
	constexpr auto decompose(const mat4x4<T>& transform, vec3<T>* translation, vec3<T>* rotation, vec3<T>* scale) -> void {
		auto m = transform / transform[3][3]; // Normalize the matrix

		// Translation
		*translation = vec3<T>(m[3]);
		
		// Scale
		vec3<T> ca(m[0]);
		vec3<T> cb(m[1]);
		vec3<T> cc(m[2]);

		// Detect and correct negative scale
		if (vec3<T> v{ cross(cb, cc) }; dot(ca, v) < 0) {
			ca *= static_cast<T>(-1);
			cb *= static_cast<T>(-1);
			cc *= static_cast<T>(-1);
		}

		*scale = { length(ca), length(cb), length(cc) };
		
		// Rotation
		ca /= scale->x;
		cb /= scale->y;
		cc /= scale->z;
		
		T cy = asin(-ca.z);
		*rotation = cos(cy) == static_cast<T>(0) ?
			vec3<T>{ atan2(-cc.x, cb.y), cy, 0 } :
			vec3<T>{ atan2(cb.z, cc.z), cy, atan2(ca.y, ca.x) };
	}
	
	
	//@brief Translates a matrix by a vector
	//@param translation: The amount to translate by
	//@param m: The matrix to be translated
	//@return A translated matrix
	template<typename T>
	MYL_NO_DISCARD constexpr auto translate(const vec3<T>& translation, const mat4x4<T>& m = mat4x4<T>::identity()) -> mat4x4<T> {
		return mat4x4<T>{
				m[0],
				m[1],
				m[2],
				m[0] * translation[0] + m[1] * translation[1] + m[2] * translation[2] + m[3] };
	}

	//@brief Rotates a matrix by a vector in a left hand coordinate system
	//@param rotation: The amount to rotates by in radian euler angles
	//@param m: The matrix to be rotated
	//@return A rotated matrix
	template<typename T>
	MYL_NO_DISCARD constexpr auto rotate_lh(const vec3<T>& rotation, const mat4x4<T>& m = mat4x4<T>::identity()) -> mat4x4<T> {
		T cx = cos(rotation.x);
		T cy = cos(rotation.y);
		T cz = cos(rotation.z);
		T sx = sin(rotation.x);
		T sy = sin(rotation.y);
		T sz = sin(rotation.z);

		return m * mat4x4<T>(
			cy * cz, sx * sy * cz - cx * sz, cx * sy * cz + sx * sz, 0,
			cy * sz, sx * sy * sz + cx * cz, cx * sy * sz - sx * cz, 0,
			-sy, sx * cy, cx * cy, 0,
			0, 0, 0, 1);
	}

	//@brief Rotates a matrix by a vector in a right hand coordinate system
	//@param rotation: The amount to rotates by in radian euler angles
	//@param m: The matrix to be rotated
	//@return A rotated matrix
	template<typename T>
	MYL_NO_DISCARD constexpr auto rotate_rh(const vec3<T>& rotation, const mat4x4<T>& m = mat4x4<T>::identity()) -> mat4x4<T> {
		T cx = cos(rotation.x);
		T cy = cos(rotation.y);
		T cz = cos(rotation.z);
		T sx = sin(rotation.x);
		T sy = sin(rotation.y);
		T sz = sin(rotation.z);

		return m * mat4x4<T>(
			cy * cz, cy * sz, -sy, 0,
			sx * sy * cz - cx * sz, sx * sy * sz + cx * cz, sx * cy, 0,
			cx * sy * cz + sx * sz, cx * sy * sz - sx * cz, cx * cy, 0,
			0, 0, 0, 1);
	}

	//@brief Rotates a matrix by a vector
	//@param rotation: The amount to rotates by in radian euler angles
	//@param m: The matrix to be rotated
	//@return A rotated matrix
	template<typename T>
	MYL_NO_DISCARD inline constexpr auto rotate(const vec3<T>& rotation, const mat4x4<T>& m = mat4x4<T>::identity()) -> mat4x4<T> {
#ifdef MYL_FORCE_RIGHT_HANDED
		return rotate_rh(rotation, m);
#else
		return rotate_lh(rotation, m);
#endif
	}

	//@brief Scales a matrix by a vector
	//@param scale: The amount to scale by
	//@param m: The matrix to be scaled
	//@return A scaled matrix
	template<typename T>
	MYL_NO_DISCARD constexpr auto scale(const vec3<T>& scale, const mat4x4<T>& m = mat4x4<T>::identity()) -> mat4x4<T> {
		return mat4x4<T>{
			m[0] * scale[0],
			m[1] * scale[1],
			m[2] * scale[2],
			m[3] };
	}

	//@brief Construct a tranform matrix
	//@param translation: Matrix translation
	//@param rotation: Matrix rotation in radian euler angles
	//@param scale: Matrix scale
	//@return A tranform matrix
	template<typename T>
	MYL_NO_DISCARD constexpr auto transform(const vec3<T>& translation, const vec3<T>& rotation, const vec3<T>& scale) -> mat4x4<T> { /// MYTodo: There's probably a better way to do this
		return translate(translation) * rotate(rotation) * myl::scale(scale);
	}
}