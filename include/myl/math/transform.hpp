#pragma once
#include <myl/math/mat4x4.hpp>
#include <myl/math/trigonometry.hpp>
#include <myl/math/vec3.hpp>

/// MYTodo: Transform.hpp
/// pitch, yaw, roll
/// rotation, scale
/// shear
/// reflection
/// decompose with shear
/// decompose with quaternions

namespace myl {
	template<typename T>
	constexpr auto translation(const mat4x4<T>& transform) -> vec3<T> {
		return vec3<T>(transform[3]) / transform[3][3];
	}

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
	
	template<typename T>
	MYL_NO_DISCARD constexpr auto translate(const vec3<T>& translation, const mat4x4<T>& m = mat4x4<T>::identity()) -> mat4x4<T> {
		return mat4x4<T>{
				m[0],
				m[1],
				m[2],
				m[0] * translation[0] + m[1] * translation[1] + m[2] * translation[2] + m[3] };
	}

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

#ifdef MYL_FORCE_RIGHT_HANDED
	template<typename T> MYL_NO_DISCARD inline constexpr auto rotate(const vec3<T>& rotation, const mat4x4<T>& m = mat4x4<T>::identity()) -> mat4x4<T> { return rotate_rh(rotation, m); }
#else
	template<typename T> MYL_NO_DISCARD inline constexpr auto rotate(const vec3<T>& rotation, const mat4x4<T>& m = mat4x4<T>::identity()) -> mat4x4<T> { return rotate_lh(rotation, m); }
#endif

	template<typename T>
	MYL_NO_DISCARD constexpr auto scale(const vec3<T>& scale, const mat4x4<T>& m = mat4x4<T>::identity()) -> mat4x4<T> {
		return mat4x4<T>{
			m[0] * scale[0],
			m[1] * scale[1],
			m[2] * scale[2],
			m[3] };
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto transform(const vec3<T>& translation, const vec3<T>& rotation, const vec3<T>& scale) -> mat4x4<T> {
		return translate(translation) * rotate(rotation) * myl::scale(scale);
	}
}