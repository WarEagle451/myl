#pragma once
#include <myl/math/matrix.hpp>
#include <myl/math/vec3.hpp>

namespace myl {
	template<typename T>
	struct mat<3, 3, T> {
		using value_type = T;
		using transpose_type = mat<3, 3, value_type>;
		using col_type = vec<3, value_type>;
		using row_type = vec<3, value_type>;
	private:
		col_type m_data[3];
	public:
		// Utilities

		MYL_NO_DISCARD static constexpr auto identity() -> mat { return mat(1, 0, 0, 0, 1, 0, 0, 0, 1); }

		// Constructors

		MYL_NO_DISCARD constexpr mat() : mat(0) {}

		MYL_NO_DISCARD constexpr explicit mat(const value_type& scalar)
			: m_data{ col_type{ scalar, 0, 0 }, col_type{ 0, scalar, 0 }, col_type{ 0, 0, scalar } } {}

		MYL_NO_DISCARD constexpr mat(const value_type& x0, const value_type& x1, const value_type& x2, const value_type& y0, const value_type& y1, const value_type& y2, const value_type& z0, const value_type& z1, const value_type& z2)
			: m_data{ col_type{ x0, y0, z0 }, col_type{ x1, y1, z1 }, col_type{ x2, y2, z2 } } {}

		MYL_NO_DISCARD constexpr mat(const value_type&& x0, const value_type&& x1, const value_type&& x2, const value_type&& y0, const value_type&& y1, const value_type&& y2, const value_type&& z0, const value_type&& z1, const value_type&& z2)
			: m_data{ col_type{ std::move(x0), std::move(y0), std::move(z0) }, col_type{ std::move(x1), std::move(y1), std::move(z1) }, col_type{ std::move(x2), std::move(y2), std::move(z2) } } {}

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

		// vec3 operators

		MYL_NO_DISCARD constexpr auto operator*(const row_type& rhs) const -> col_type { return m_data[0] * rhs[0] + m_data[1] * rhs[1] + m_data[2] * rhs[2]; }

		// mat3x3 operators

		MYL_NO_DISCARD constexpr auto operator+(const mat& rhs) const -> mat { return mat{ m_data[0] + rhs[0], m_data[1] + rhs[1], m_data[2] + rhs[2] }; }
		MYL_NO_DISCARD constexpr auto operator-(const mat& rhs) const -> mat { return mat{ m_data[0] - rhs[0], m_data[1] - rhs[1], m_data[2] - rhs[2] }; }

		MYL_NO_DISCARD constexpr auto operator*(const mat& rhs) const -> mat {
			return mat{
				m_data[0] * rhs[0][0] + m_data[1] * rhs[0][1] + m_data[2] * rhs[0][2],
				m_data[0] * rhs[1][0] + m_data[1] * rhs[1][1] + m_data[2] * rhs[1][2],
				m_data[0] * rhs[2][0] + m_data[1] * rhs[2][1] + m_data[2] * rhs[2][2] };
		}

		MYL_NO_DISCARD constexpr auto operator/(const mat& rhs) const -> mat { return *this * inverse(rhs); }

		constexpr auto operator+=(const mat& rhs) -> mat& { m_data[0] += rhs[0]; m_data[1] += rhs[1]; m_data[2] += rhs[2]; return *this; }
		constexpr auto operator-=(const mat& rhs) -> mat& { m_data[0] -= rhs[0]; m_data[1] -= rhs[1]; m_data[2] -= rhs[2]; return *this; }
		constexpr auto operator*=(const mat& rhs) -> mat& { return *this = (*this * rhs); }
		constexpr auto operator/=(const mat& rhs) -> mat& { return *this *= inverse(rhs); }
	};

	template<typename T>
	MYL_NO_DISCARD constexpr auto determinant(const mat<3, 3, T>& m) -> T {
		//     | a b c |       | e f |       | d f |       | d e |
		// det | d e f | = a * | h i | - b * | g i | + c * | g h |
		//     | g h i |          |             |             |
		// x = a(ei - fh) --------+             |             |
		// y = b(di - fg) ----------------------+             |
		// z = c(dh - eg) ------------------------------------+
		//
		// det = ax - by + cz

		return
			  m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
			- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
			+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto inverse(const mat<3, 3, T>& m) -> mat<3, 3, T> {
		return mat<3, 3, T>(
			 (m[1][1] * m[2][2] - m[1][2] * m[2][1]), //  (ei - hf)
			-(m[0][1] * m[2][2] - m[2][1] * m[0][2]), // -(di - fg)
			 (m[0][1] * m[1][2] - m[0][2] * m[1][1]), //  (dh - ge)
			-(m[1][0] * m[2][2] - m[1][2] * m[2][0]), // -(bi - hc)
			 (m[0][0] * m[2][2] - m[0][2] * m[2][0]), //  (ai - gc)
			-(m[0][0] * m[1][2] - m[0][2] * m[1][0]), // -(ah - gb)
			 (m[1][0] * m[2][1] - m[1][1] * m[2][0]), //  (bf - ec)
			-(m[0][0] * m[2][1] - m[0][1] * m[2][0]), // -(af - dc)
			 (m[0][0] * m[1][1] - m[0][1] * m[1][0])  //  (ae - db)
			) / determinant(m);
	}

	template<typename T> using mat3x3 = mat<3, 3, T>;

	using i8mat3x3 = mat3x3<i8>;
	using i16mat3x3 = mat3x3<i16>;
	using i32mat3x3 = mat3x3<i32>;
	using i64mat3x3 = mat3x3<i64>;

	using u8mat3x3 = mat3x3<u8>;
	using u16mat3x3 = mat3x3<u16>;
	using u32mat3x3 = mat3x3<u32>;
	using u64mat3x3 = mat3x3<u64>;

	using f32mat3x3 = mat3x3<f32>;
	using f64mat3x3 = mat3x3<f64>;

	template<typename T> using mat3 = mat<3, 3, T>;

	using i8mat3 = mat3<i8>;
	using i16mat3 = mat3<i16>;
	using i32mat3 = mat3<i32>;
	using i64mat3 = mat3<i64>;

	using u8mat3 = mat3<u8>;
	using u16mat3 = mat3<u16>;
	using u32mat3 = mat3<u32>;
	using u64mat3 = mat3<u64>;

	using f32mat3 = mat3<f32>;
	using f64mat3 = mat3<f64>;
}

#ifdef MYL_DEFINE_TYPES
template<typename T> using mat3x3 = myl::mat3x3<T>;

using i8mat3x3 = myl::i8mat3x3;
using i16mat3x3 = myl::i16mat3x3;
using i32mat3x3 = myl::i32mat3x3;
using i64mat3x3 = myl::i64mat3x3;

using u8mat3x3 = myl::u8mat3x3;
using u16mat3x3 = myl::u16mat3x3;
using u32mat3x3 = myl::u32mat3x3;
using u64mat3x3 = myl::u64mat3x3;

using f32mat3x3 = myl::f32mat3x3;
using f64mat3x3 = myl::f64mat3x3;

template<typename T> using mat3 = myl::mat<3, 3, T>;

using i8mat3 = myl::i8mat3;
using i16mat3 = myl::i16mat3;
using i32mat3 = myl::i32mat3;
using i64mat3 = myl::i64mat3;

using u8mat3 = myl::u8mat3;
using u16mat3 = myl::u16mat3;
using u32mat3 = myl::u32mat3;
using u64mat3 = myl::u64mat3;

using f32mat3 = myl::f32mat3;
using f64mat3 = myl::f64mat3;
#endif