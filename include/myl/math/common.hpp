#pragma once
#include <myl/defines.hpp>

namespace myl {
	template<typename T>
	MYL_NO_DISCARD constexpr auto abs(const T s) -> T {
		return s > static_cast<T>(0) ? s : -s;
	}

	template<> MYL_NO_DISCARD constexpr auto abs<u8>(const u8 s) -> u8 { return s; }
	template<> MYL_NO_DISCARD constexpr auto abs<u16>(const u16 s) -> u16 { return s; }
	template<> MYL_NO_DISCARD constexpr auto abs<u32>(const u32 s) -> u32 { return s; }
	template<> MYL_NO_DISCARD constexpr auto abs<u64>(const u64 s) -> u64 { return s; }

	MYL_API MYL_NO_DISCARD auto approx(f32, f32) -> bool; /// MYTodo: Constexpr
	MYL_API MYL_NO_DISCARD auto approx(f64, f64) -> bool; /// MYTodo: Constexpr

	template<typename T>
	MYL_NO_DISCARD constexpr auto sign(const T s) -> T {
		return s == static_cast<T>(0) ? static_cast<T>(0) : s > static_cast<T>(0) ? static_cast<T>(1) : static_cast<T>(-1);
	}

	template<> MYL_NO_DISCARD constexpr auto sign<u8>(const u8 s) -> u8 { return static_cast<u8>(s != 0); }
	template<> MYL_NO_DISCARD constexpr auto sign<u16>(const u16 s) -> u16 { return static_cast<u16>(s != 0); }
	template<> MYL_NO_DISCARD constexpr auto sign<u32>(const u32 s) -> u32 { return static_cast<u32>(s != 0); }
	template<> MYL_NO_DISCARD constexpr auto sign<u64>(const u64 s) -> u64 { return static_cast<u64>(s != 0); }
	template<> MYL_NO_DISCARD constexpr auto sign<f32>(const f32 s) -> f32 { return static_cast<f32>((0.f < s) - (s < 0.f)); } /// MYTodo: How to handle the i0, +0, -nan, +nan cases? plus approx?
	template<> MYL_NO_DISCARD constexpr auto sign<f64>(const f64 s) -> f64 { return static_cast<f64>((0.0 < s) - (s < 0.0)); }

	/// MYTodo: Constexpr
	MYL_API MYL_NO_DISCARD inline auto sqrt(f32) -> f32; /// MYTodo: Imple all types
	MYL_API MYL_NO_DISCARD inline auto sqrt(f64) -> f64;
}