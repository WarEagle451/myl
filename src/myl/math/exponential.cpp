#include <myl/math/exponential.hpp>

#include <cmath>

namespace myl {
	/// MYTodo: Imple custom gamma function refer to compiler intrinsics
	auto gamma(i64 v) -> i64 { return static_cast<i64>(std::tgamma(static_cast<f64>(v))); }
	auto gamma(f32 v) -> f32 { return std::tgammaf(v); }
	auto gamma(f64 v) -> f64 { return std::tgamma(v); }

	auto log_gamma(i64 v) -> i64 { return static_cast<i64>(std::lgamma(static_cast<f64>(v))); }
	auto log_gamma(f32 v) -> f32 { return std::lgammaf(v); }
	auto log_gamma(f64 v) -> f64 { return std::lgamma(v); }

	inline auto sqrt(f32 v) -> f32 { return std::sqrt(v); }
	inline auto sqrt(f64 v) -> f64 { return std::sqrt(v); }
}