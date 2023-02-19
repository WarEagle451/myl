#pragma once
#include <myl/math/vec4.hpp>

namespace myl {
	MYL_API MYL_NO_DISCARD constexpr auto vec4_to_u32(const f32vec4& color) -> u32 {
		return
			(static_cast<u32>(color.r * 255.f) << 24) |
			(static_cast<u32>(color.g * 255.f) << 16) |
			(static_cast<u32>(color.b * 255.f) << 8) |
			static_cast<u32>(color.a * 255.f);
	}

	MYL_API MYL_NO_DISCARD constexpr auto u32_to_vec4(const u32 color) -> f32vec4 {
		return {
			static_cast<f32>(color & 0xFF00'0000) / 255.f,
			static_cast<f32>(color & 0x00FF'0000) / 255.f,
			static_cast<f32>(color & 0x0000'FF00) / 255.f,
			static_cast<f32>(color & 0x0000'00FF) / 255.f };
	}

	MYL_API MYL_NO_DISCARD constexpr auto complement(const f32vec4& color) -> f32vec4 {
		return {
			1.f - color.r,
			1.f - color.g,
			1.f - color.b,
			color.a };
	}
}