#pragma once
#include <myl/algorithm.hpp>

namespace myl {
	template<number A, number B, floating_point F = f32>
	MYL_NO_DISCARD constexpr auto lerp(A a, B b, F percentage) -> std::common_type_t<A, B, F> {
		using common = std::common_type_t<A, B, F>;

		const common ca = static_cast<common>(a);
		const common cb = static_cast<common>(b);
		const common cpercentage = static_cast<common>(percentage);

		return ca + ((cb - ca) * cpercentage);
	}

	template<number A, number B, floating_point F = f32>
	MYL_NO_DISCARD constexpr auto inverse_lerp(A a, B b, F value) -> std::common_type_t<A, B, F> {
		using common = std::common_type_t<A, B, F>;

		const common ca = static_cast<common>(a);
		const common cb = static_cast<common>(b);
		const common cvalue = static_cast<common>(value);

		return (cvalue - ca) / (cb - ca);
	}


	template<number T>
	MYL_NO_DISCARD constexpr auto step(T edge, T a) -> T {
		return edge > a ? 0 : 1;
	}

	template<number A, number B, floating_point F = f32>
	MYL_NO_DISCARD constexpr auto smoothstep(A edge0, B edge1, F x) -> std::common_type_t<A, B, F> {
		using common = std::common_type_t<A, B, F>;

		const common e0 = static_cast<common>(edge0);
		const common e1 = static_cast<common>(edge1);
		const common cf = static_cast<common>(x);

		const common t = clamp((x - e0) / (e1 - e0), static_cast<common>(0), static_cast<common>(1));
		return t * t * (static_cast<common>(3) - static_cast<common>(2) * t);
	}
}