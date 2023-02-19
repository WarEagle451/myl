#pragma once
#include <myl/math/matrix.hpp>
#include <myl/math/vec2.hpp>
#include <myl/math/vec3.hpp>

namespace myl {
	template<typename T>
	struct mat<2, 3, T> {
		using value_type = T;
		using transpose_type = mat<3, 2, value_type>;
		using col_type = vec<2, value_type>;
		using row_type = vec<3, value_type>;
	private:
		col_type m_data[3];
	public:
		// Constructors

		MYL_NO_DISCARD constexpr mat() : mat(0) {}

		MYL_NO_DISCARD constexpr explicit mat(const value_type& scalar)
			: m_data{ col_type(scalar), col_type(scalar), col_type(scalar) } {}

		MYL_NO_DISCARD constexpr mat(const value_type& x0, const value_type& x1, const value_type& x2, const value_type& y0, const value_type& y1, const value_type& y2)
			: m_data{ col_type{ x0, y0 }, col_type{ x1, y1 }, col_type{ x2, y2 } } {}

		MYL_NO_DISCARD constexpr mat(const value_type&& x0, const value_type&& x1, const value_type&& x2, const value_type&& y0, const value_type&& y1, const value_type&& y2)
			: m_data{ col_type{ std::move(x0), std::move(y0) }, col_type{ std::move(x1), std::move(y1) }, col_type{ std::move(x2), std::move(y2) } } {}

		MYL_NO_DISCARD constexpr mat(const col_type& c0, const col_type& c1, const col_type& c2)
			: m_data{ c0, c1, c2 } {}

		MYL_NO_DISCARD constexpr mat(col_type&& c0, col_type&& c1, col_type&& c2)
			: m_data{ std::move(c0), std::move(c1), std::move(c2) } {}

		// Access operators

		MYL_NO_DISCARD constexpr auto operator[](usize i) -> col_type& { return m_data[i]; }
		MYL_NO_DISCARD constexpr auto operator[](usize i) const -> const col_type& { return m_data[i]; }

#if __cpp_multidimensional_subscript
		MYL_NO_DISCARD constexpr auto operator[](usize i, usize j) -> value_type& { return m_data[i][j]; }
		MYL_NO_DISCARD constexpr auto operator[](usize i, usize j) const -> const value_type& { return m_data[i][j]; }
#endif

		// Comparison operators

		MYL_NO_DISCARD constexpr auto operator==(const mat& rhs) const -> bool { return m_data[0] == rhs[0] && m_data[1] == rhs[1] && m_data[2] == rhs[2]; }

		// Unary operators

		MYL_NO_DISCARD constexpr auto operator-() const -> mat { return mat{ -m_data[0], -m_data[1], -m_data[2] }; }

		// Scaler operators

		MYL_NO_DISCARD constexpr auto operator+(const value_type& rhs) const -> mat { return mat{ m_data[0] + rhs, m_data[1] + rhs, m_data[2] + rhs }; }
		MYL_NO_DISCARD constexpr auto operator-(const value_type& rhs) const -> mat { return mat{ m_data[0] - rhs, m_data[1] - rhs, m_data[2] - rhs }; }
		MYL_NO_DISCARD constexpr auto operator*(const value_type& rhs) const -> mat { return mat{ m_data[0] * rhs, m_data[1] * rhs, m_data[2] * rhs }; }
		MYL_NO_DISCARD constexpr auto operator/(const value_type& rhs) const -> mat { return mat{ m_data[0] / rhs, m_data[1] / rhs, m_data[2] / rhs }; }
		MYL_NO_DISCARD constexpr auto operator%(const value_type& rhs) const -> mat { return mat{ m_data[0] % rhs, m_data[1] % rhs, m_data[2] % rhs }; }

		constexpr auto operator+=(const value_type& rhs) -> mat& { m_data[0] += rhs; m_data[1] += rhs; m_data[2] += rhs; return *this; }
		constexpr auto operator-=(const value_type& rhs) -> mat& { m_data[0] -= rhs; m_data[1] -= rhs; m_data[2] -= rhs; return *this; }
		constexpr auto operator*=(const value_type& rhs) -> mat& { m_data[0] *= rhs; m_data[1] *= rhs; m_data[2] *= rhs; return *this; }
		constexpr auto operator/=(const value_type& rhs) -> mat& { m_data[0] /= rhs; m_data[1] /= rhs; m_data[2] /= rhs; return *this; }
		constexpr auto operator%=(const value_type& rhs) -> mat& { m_data[0] %= rhs; m_data[1] %= rhs; m_data[2] %= rhs; return *this; }

		// mat2x3 operators

		MYL_NO_DISCARD constexpr auto operator+(const mat& rhs) const -> mat { return mat{ m_data[0] + rhs[0], m_data[1] + rhs[1], m_data[2] + rhs[2] }; }
		MYL_NO_DISCARD constexpr auto operator-(const mat& rhs) const -> mat { return mat{ m_data[0] - rhs[0], m_data[1] - rhs[1], m_data[2] - rhs[2] }; }

		constexpr auto operator+=(const mat& rhs) -> mat& { m_data[0] += rhs[0]; m_data[1] += rhs[1]; m_data[2] += rhs[2]; return *this; }
		constexpr auto operator-=(const mat& rhs) -> mat& { m_data[0] -= rhs[0]; m_data[1] -= rhs[1]; m_data[2] -= rhs[2]; return *this; }
	};

	template<typename T> using mat2x3 = mat<2, 3, T>;

	using i8mat2x3 = mat2x3<i8>;
	using i16mat2x3 = mat2x3<i16>;
	using i32mat2x3 = mat2x3<i32>;
	using i64mat2x3 = mat2x3<i64>;

	using u8mat2x3 = mat2x3<u8>;
	using u16mat2x3 = mat2x3<u16>;
	using u32mat2x3 = mat2x3<u32>;
	using u64mat2x3 = mat2x3<u64>;

	using f32mat2x3 = mat2x3<f32>;
	using f64mat2x3 = mat2x3<f64>;
}

#ifdef MYL_DEFINE_TYPES
template<typename T> using mat2x3 = myl::mat2x3<T>;

using i8mat2x3 = myl::i8mat2x3;
using i16mat2x3 = myl::i16mat2x3;
using i32mat2x3 = myl::i32mat2x3;
using i64mat2x3 = myl::i64mat2x3;

using u8mat2x3 = myl::u8mat2x3;
using u16mat2x3 = myl::u16mat2x3;
using u32mat2x3 = myl::u32mat2x3;
using u64mat2x3 = myl::u64mat2x3;

using f32mat2x3 = myl::f32mat2x3;
using f64mat2x3 = myl::f64mat2x3;
#endif