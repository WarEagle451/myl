#include <myl/math/common.hpp>

#include <cmath>
#include <limits>

namespace myl {
	auto approx(f32 a, f32 b) -> bool { return std::abs(a - b) <= ((std::abs(a) < std::abs(b) ? std::abs(b) : std::abs(a)) * std::numeric_limits<f32>::epsilon()); }
	auto approx(f64 a, f64 b) -> bool { return std::abs(a - b) <= ((std::abs(a) < std::abs(b) ? std::abs(b) : std::abs(a)) * std::numeric_limits<f64>::epsilon()); }

	inline auto sqrt(f32 value) -> f32 { return std::sqrt(value); }
	inline auto sqrt(f64 value) -> f64 { return std::sqrt(value); }
}