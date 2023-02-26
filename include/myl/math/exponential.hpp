#pragma once
#include <myl/defines.hpp>

namespace myl {
	MYL_API MYL_NO_DISCARD auto gamma(i64) -> i64; /// MYTodo: Implement as template and using compiler intrinsics
	MYL_API MYL_NO_DISCARD auto gamma(f32) -> f32;
	MYL_API MYL_NO_DISCARD auto gamma(f64) -> f64;

	MYL_API MYL_NO_DISCARD auto log_gamma(i64) -> i64; /// MYTodo: Implement as template and using compiler intrinsics
	MYL_API MYL_NO_DISCARD auto log_gamma(f32) -> f32;
	MYL_API MYL_NO_DISCARD auto log_gamma(f64) -> f64;

	/// MYTodo: Constexpr
	MYL_API MYL_NO_DISCARD inline auto sqrt(f32) -> f32; /// MYTodo: Imple all types
	MYL_API MYL_NO_DISCARD inline auto sqrt(f64) -> f64;

	template<number T>
	MYL_NO_DISCARD constexpr auto factorial(T v) -> T {
		v > 0 ? v * gamma(v) : 0;
	}
}