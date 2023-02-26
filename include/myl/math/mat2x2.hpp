#pragma once
#include <myl/math/matrix.hpp>
#include <myl/math/vec2.hpp>

namespace myl {
	template<typename T>
	struct mat<2, 2, T> {
		using value_type = T;
		using transpose_type = mat<2, 2, value_type>;
		using col_type = vec<2, value_type>;
		using row_type = vec<2, value_type>;
	private:
		col_type m_data[2];
	public:
		// Utilities

		MYL_NO_DISCARD static constexpr auto identity() -> mat { return mat(1, 0, 0, 1); }

		// Constructors

		MYL_NO_DISCARD constexpr mat() : mat(0) {}

		MYL_NO_DISCARD constexpr explicit mat(const value_type& scalar)
			: m_data{ col_type{ scalar, 0 }, col_type{ 0, scalar } } {}

		MYL_NO_DISCARD constexpr mat(const value_type& x0, const value_type& x1, const value_type& y0, const value_type& y1)
			: m_data{ col_type{ x0, y0 }, col_type{ x1, y1 } } {}

		MYL_NO_DISCARD constexpr mat(const value_type&& x0, const value_type&& x1, const value_type&& y0, const value_type&& y1)
			: m_data{ col_type{ std::move(x0), std::move(y0) }, col_type{ std::move(x1), std::move(y1) } } {}

		MYL_NO_DISCARD constexpr mat(const col_type& c0, const col_type& c1)
			: m_data{ c0, c1 } {}

		MYL_NO_DISCARD constexpr mat(col_type&& c0, col_type&& c1)
			: m_data{ std::move(c0), std::move(c1) } {}

		// Access operators

		MYL_NO_DISCARD constexpr auto operator[](usize i) -> col_type& { return m_data[i]; }
		MYL_NO_DISCARD constexpr auto operator[](usize i) const -> const col_type& { return m_data[i]; }

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
		
		// vec2 operators

		MYL_NO_DISCARD constexpr auto operator*(const row_type& rhs) const -> col_type { m_data[0] * rhs[0] + m_data[1] * rhs[1]; }

		// mat2x2 operators

		MYL_NO_DISCARD constexpr auto operator+(const mat& rhs) const -> mat { return mat{ m_data[0] + rhs[0], m_data[1] + rhs[1] }; }
		MYL_NO_DISCARD constexpr auto operator-(const mat& rhs) const -> mat { return mat{ m_data[0] - rhs[0], m_data[1] - rhs[1] }; }

		MYL_NO_DISCARD constexpr auto operator*(const mat& rhs) const -> mat {
			return mat{
				m_data[0] * rhs[0][0] + m_data[1] * rhs[0][1],
				m_data[0] * rhs[1][0] + m_data[1] * rhs[1][1] };
		}

		MYL_NO_DISCARD constexpr auto operator/(const mat& rhs) const -> mat{ return *this * inverse(rhs); }

		constexpr auto operator+=(const mat& rhs) -> mat& { m_data[0] += rhs[0]; m_data[1] += rhs[1]; return *this; }
		constexpr auto operator-=(const mat& rhs) -> mat& { m_data[0] -= rhs[0]; m_data[1] -= rhs[1]; return *this; }
		constexpr auto operator*=(const mat& rhs) -> mat& { return *this = (*this * rhs); }
		constexpr auto operator/=(const mat& rhs) -> mat& { return *this *= inverse(rhs); }
	};

	template<typename T>
	constexpr auto set_row(mat<2, 2, T>& m, usize i, const typename mat<2, 2, T>::row_type& row) -> void {
		m[0][i] = row[0];
		m[1][i] = row[1];
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto determinant(const mat<2, 2, T>& m) -> T {
		//       | a b |
		// det = | c d | = ad - bc

		return m[0][0] * m[1][1] - m[1][0] * m[0][1];
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto inverse(const mat<2, 2, T>& m) -> mat<2, 2, T> {
		return mat<2, 2, T>(m[1][1], -m[0][1], -m[1][0], m[0][0]) / determinant(m);
	}

	template<typename T> using mat2x2 = mat<2, 2, T>;

	using i8mat2x2 = mat2x2<i8>;
	using i16mat2x2 = mat2x2<i16>;
	using i32mat2x2 = mat2x2<i32>;
	using i64mat2x2 = mat2x2<i64>;

	using u8mat2x2 = mat2x2<u8>;
	using u16mat2x2 = mat2x2<u16>;
	using u32mat2x2 = mat2x2<u32>;
	using u64mat2x2 = mat2x2<u64>;

	using f32mat2x2 = mat2x2<f32>;
	using f64mat2x2 = mat2x2<f64>;

	template<typename T> using mat2 = mat<2, 2, T>;

	using i8mat2 = mat2<i8>;
	using i16mat2 = mat2<i16>;
	using i32mat2 = mat2<i32>;
	using i64mat2 = mat2<i64>;

	using u8mat2 = mat2<u8>;
	using u16mat2 = mat2<u16>;
	using u32mat2 = mat2<u32>;
	using u64mat2 = mat2<u64>;

	using f32mat2 = mat2<f32>;
	using f64mat2 = mat2<f64>;
}

#ifdef MYL_DEFINE_TYPES
template<typename T> using mat2x2 = myl::mat2x2<T>;

using i8mat2x2 = myl::i8mat2x2;
using i16mat2x2 = myl::i16mat2x2;
using i32mat2x2 = myl::i32mat2x2;
using i64mat2x2 = myl::i64mat2x2;

using u8mat2x2 = myl::u8mat2x2;
using u16mat2x2 = myl::u16mat2x2;
using u32mat2x2 = myl::u32mat2x2;
using u64mat2x2 = myl::u64mat2x2;

using f32mat2x2 = myl::f32mat2x2;
using f64mat2x2 = myl::f64mat2x2;

template<typename T> using mat2 = myl::mat<2, 2, T>;

using i8mat2 = myl::i8mat2;
using i16mat2 = myl::i16mat2;
using i32mat2 = myl::i32mat2;
using i64mat2 = myl::i64mat2;

using u8mat2 = myl::u8mat2;
using u16mat2 = myl::u16mat2;
using u32mat2 = myl::u32mat2;
using u64mat2 = myl::u64mat2;

using f32mat2 = myl::f32mat2;
using f64mat2 = myl::f64mat2;
#endif