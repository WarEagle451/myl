#pragma once
#include <myl/math/matrix.hpp>
#include <myl/math/vec2.hpp>
#include <myl/math/vec4.hpp>

namespace myl {
	template<typename T>
	struct mat<2, 4, T> {
		using value_type = T;
		using transpose_type = mat<4, 2, value_type>;
		using col_type = vec<4, value_type>;
		using row_type = vec<2, value_type>;
	private:
		col_type m_data[2];
	public:
		// Constructors

		MYL_NO_DISCARD constexpr mat() : mat(0) {}

		MYL_NO_DISCARD constexpr explicit mat(const value_type& scalar)
			: m_data{ col_type(scalar), col_type(scalar) } {}

		MYL_NO_DISCARD constexpr mat(const value_type& x0, const value_type& x1, const value_type& y0, const value_type& y1, const value_type& z0, const value_type& z1, const value_type& w0, const value_type& w1)
			: m_data{ col_type{ x0, y0, z0, w0 }, col_type{ x1, y1, z1, w1 } } {}

		MYL_NO_DISCARD constexpr mat(const value_type&& x0, const value_type&& x1, const value_type&& y0, const value_type&& y1, const value_type&& z0, const value_type&& z1, const value_type&& w0, const value_type&& w1)
			: m_data{ col_type{ std::move(x0), std::move(y0), std::move(z0), std::move(w0) }, col_type{ std::move(x1), std::move(y1), std::move(z1), std::move(w1) } } {}

		MYL_NO_DISCARD constexpr mat(const col_type& c0, const col_type& c1)
			: m_data{ c0, c1 } {}

		MYL_NO_DISCARD constexpr mat(col_type&& c0, col_type&& c1)
			: m_data{ std::move(c0), std::move(c1) } {}

		// Access operators

		MYL_NO_DISCARD constexpr auto operator[](usizei) -> col_type& { return m_data[i]; }
		MYL_NO_DISCARD constexpr auto operator[](usizei) const -> const col_type& { return m_data[i]; }

#if __cpp_multidimensional_subscript
		MYL_NO_DISCARD constexpr auto operator[](usize i, usize j) -> value_type& { return m_data[i][j]; }
		MYL_NO_DISCARD constexpr auto operator[](usize i, usize j) const -> const value_type& { return m_data[i][j]; }
#endif

		// Comparison operators

		MYL_NO_DISCARD constexpr auto operator==(const mat& rhs) const -> bool { return m_data[0] == rhs[0] && m_data[1] == rhs[1]; }

		// Unary operators

		MYL_NO_DISCARD constexpr auto operator-() const -> mat { return mat{ -m_data[0], -m_data[1] }; }

		// Scaler operators

		MYL_NO_DISCARD constexpr auto operator+(const value_type& rhs) const -> mat { return mat{ m_data[0] + rhs, m_data[1] + rhs }; }
		MYL_NO_DISCARD constexpr auto operator-(const value_type& rhs) const -> mat { return mat{ m_data[0] - rhs, m_data[1] - rhs }; }
		MYL_NO_DISCARD constexpr auto operator*(const value_type& rhs) const -> mat { return mat{ m_data[0] * rhs, m_data[1] * rhs }; }
		MYL_NO_DISCARD constexpr auto operator/(const value_type& rhs) const -> mat { return mat{ m_data[0] / rhs, m_data[1] / rhs }; }
		MYL_NO_DISCARD constexpr auto operator%(const value_type& rhs) const -> mat { return mat{ m_data[0] % rhs, m_data[1] % rhs }; }

		constexpr auto operator+=(const value_type& rhs) -> mat& { m_data[0] += rhs; m_data[1] += rhs; return *this; }
		constexpr auto operator-=(const value_type& rhs) -> mat& { m_data[0] -= rhs; m_data[1] -= rhs; return *this; }
		constexpr auto operator*=(const value_type& rhs) -> mat& { m_data[0] *= rhs; m_data[1] *= rhs; return *this; }
		constexpr auto operator/=(const value_type& rhs) -> mat& { m_data[0] /= rhs; m_data[1] /= rhs; return *this; }
		constexpr auto operator%=(const value_type& rhs) -> mat& { m_data[0] %= rhs; m_data[1] %= rhs; return *this; }

		// mat2x4 operators

		MYL_NO_DISCARD constexpr auto operator+(const mat& rhs) const -> mat { return mat{ m_data[0] + rhs[0], m_data[1] + rhs[1] }; }
		MYL_NO_DISCARD constexpr auto operator-(const mat& rhs) const -> mat { return mat{ m_data[0] - rhs[0], m_data[1] - rhs[1] }; }

		constexpr auto operator+=(const mat& rhs) -> mat& { m_data[0] += rhs[0]; m_data[1] += rhs[1]; return *this; }
		constexpr auto operator-=(const mat& rhs) -> mat& { m_data[0] -= rhs[0]; m_data[1] -= rhs[1]; return *this; }
	};

	template<typename T>
	constexpr auto set_row(mat<4, 2, T>& m, usize i, const typename mat<4, 2, T>::row_type& row) -> void {
		m[0][i] = row[0];
		m[1][i] = row[1];
	}

	template<typename T> using mat2x4 = mat<4, 2, T>;

	using i8mat2x4 = mat2x4<i8>;
	using i16mat2x4 = mat2x4<i16>;
	using i32mat2x4 = mat2x4<i32>;
	using i64mat2x4 = mat2x4<i64>;

	using u8mat2x4 = mat2x4<u8>;
	using u16mat2x4 = mat2x4<u16>;
	using u32mat2x4 = mat2x4<u32>;
	using u64mat2x4 = mat2x4<u64>;

	using f32mat2x4 = mat2x4<f32>;
	using f64mat2x4 = mat2x4<f64>;
}

#ifdef MYL_DEFINE_TYPES
template<typename T> using mat2x4 = myl::mat2x4<T>;

using i8mat2x4 = myl::i8mat2x4;
using i16mat2x4 = myl::i16mat2x4;
using i32mat2x4 = myl::i32mat2x4;
using i64mat2x4 = myl::i64mat2x4;

using u8mat2x4 = myl::u8mat2x4;
using u16mat2x4 = myl::u16mat2x4;
using u32mat2x4 = myl::u32mat2x4;
using u64mat2x4 = myl::u64mat2x4;

using f32mat2x4 = myl::f32mat2x4;
using f64mat2x4 = myl::f64mat2x4;
#endif