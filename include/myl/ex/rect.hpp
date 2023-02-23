#pragma once
#include <myl/defines.hpp> ///m For #ifdef MYL_EXPERIMENTAL
#ifdef MYL_EXPERIMENTAL

#include <myl/math/vec2.hpp>

namespace myl {
	template<typename T>
	struct rect {
		vec2<T> p1{ 0, 0 }, p2{ 0, 0 };
	};

	/// tl, tr, bl, br

	template<typename T> MYL_NO_DISCARD constexpr auto center(const rect<T>& a_rect) -> vec2<T> { return (a_rect.p1 + a_rect.p2) / static_cast<T>(2); }

	template<typename T> MYL_NO_DISCARD constexpr auto width(const rect<T>& a_rect) -> T { return abs(p2.x - p1.x); }
	template<typename T> MYL_NO_DISCARD constexpr auto height(const rect<T>& a_rect) -> T { return abs(p2.y - p1.y); }
	template<typename T> MYL_NO_DISCARD constexpr auto area(const rect<T>& a_rect) -> T { return width(a_rect) * height(a_rect); }

	using i8rect = rect<i8>;
	using i16rect = rect<i16>;
	using i32rect = rect<i32>;
	using i64rect = rect<i64>;

	using u8rect = rect<u8>;
	using u16rect = rect<u16>;
	using u32rect = rect<u32>;
	using u64rect = rect<u64>;

	using f32rect = rect<f32>;
	using f64rect = rect<f64>;
}
#endif