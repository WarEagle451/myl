#include <myl/math/common.hpp>

#include <cmath>
#include <limits>

namespace myl {
	constexpr auto approx(f32 a, f32 b) -> bool { return abs(a - b) <= ((abs(a) < abs(b) ? abs(b) : abs(a)) * std::numeric_limits<f32>::epsilon()); }
	constexpr auto approx(f64 a, f64 b) -> bool { return abs(a - b) <= ((abs(a) < abs(b) ? abs(b) : abs(a)) * std::numeric_limits<f64>::epsilon()); }

	inline auto sqrt(f32 value) -> f32 { return std::sqrt(value); }
	inline auto sqrt(f64 value) -> f64 { return std::sqrt(value); }
}