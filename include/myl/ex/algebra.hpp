#pragma once
#include <myl/math/common.hpp>

namespace myl {
	template<typename T>
	MYL_NO_DISCARD constexpr auto quadratic_formula(T a, T b, T c) {
		struct results { T positive, negative };

		T sqrt_discrimiant = sqrt(b * b - static_cast<T>(4) * a * c);
		return results{
			.positive = (-b + sqrt_discrimiant) / (static_cast<T>(2) * a),
			.negative = (-b - sqrt_discrimiant) / (static_cast<T>(2) * a)
		};
	}
}