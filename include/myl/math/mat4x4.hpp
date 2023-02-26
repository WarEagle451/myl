#pragma once
#include <myl/math/matrix.hpp>
#include <myl/math/vec4.hpp>

namespace myl {
	template<typename T>
	struct mat<4, 4, T> {
		using value_type = T;
		using transpose_type = mat<4, 4, value_type>;
		using col_type = vec<4, value_type>;
		using row_type = vec<4, value_type>;
	private:
		col_type m_data[4];
	public:
		// Utilities

		MYL_NO_DISCARD static constexpr auto identity() -> mat { return mat(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); }

		// Constructors

		MYL_NO_DISCARD constexpr mat() : mat(0) {}

		MYL_NO_DISCARD constexpr explicit mat(const value_type& scalar)
			: m_data{ col_type{ scalar, 0, 0, 0 }, col_type{ 0, scalar, 0, 0 }, col_type{ 0, 0, scalar, 0 }, col_type{ 0, 0, 0, scalar } } {}

		MYL_NO_DISCARD constexpr mat(const value_type& x0, const value_type& x1, const value_type& x2, const value_type& x3, const value_type& y0, const value_type& y1, const value_type& y2, const value_type& y3, const value_type& z0, const value_type& z1, const value_type& z2, const value_type& z3, const value_type& w0, const value_type& w1, const value_type& w2, const value_type& w3)
			: m_data{ col_type{ x0, y0, z0, w0 }, col_type{ x1, y1, z1, w1 }, col_type{ x2, y2, z2, w2 }, col_type{ x3, y3, z3, w3 } } {}

		MYL_NO_DISCARD constexpr mat(const value_type&& x0, const value_type&& x1, const value_type&& x2, const value_type&& x3, const value_type&& y0, const value_type&& y1, const value_type&& y2, const value_type&& y3, const value_type&& z0, const value_type&& z1, const value_type&& z2, const value_type&& z3, const value_type&& w0, const value_type&& w1, const value_type&& w2, const value_type&& w3)
			: m_data{ col_type{ std::move(x0), std::move(y0), std::move(z0), std::move(w0) }, col_type{ std::move(x1), std::move(y1), std::move(z1), std::move(w1) }, col_type{ std::move(x2), std::move(y2), std::move(z2), std::move(w2) }, col_type{ std::move(x3), std::move(y3), std::move(z3), std::move(w3) } } {}

		MYL_NO_DISCARD constexpr mat(const col_type& c0, const col_type& c1, const col_type& c2, const col_type& c3)
			: m_data{ c0, c1, c2, c3 } {}

		MYL_NO_DISCARD constexpr mat(col_type&& c0, col_type&& c1, col_type&& c2, col_type&& c3)
			: m_data{ std::move(c0), std::move(c1), std::move(c2), std::move(c3) } {}

		// Access operators

		MYL_NO_DISCARD constexpr auto operator[](usize i) -> col_type& { return m_data[i]; }
		MYL_NO_DISCARD constexpr auto operator[](usize i) const -> const col_type& { return m_data[i]; }

#if __cpp_multidimensional_subscript
		MYL_NO_DISCARD constexpr auto operator[](usize i, usize j) -> value_type& { return m_data[i][j]; }
		MYL_NO_DISCARD constexpr auto operator[](usize i, usize j) const -> const value_type& { return m_data[i][j]; }
#endif

		// Comparison operators

		MYL_NO_DISCARD constexpr auto operator==(const mat& rhs) const -> bool { return m_data[0] == rhs[0] && m_data[1] == rhs[1] && m_data[2] == rhs[2] && m_data[3] == rhs[3]; }

		// Unary operators

		MYL_NO_DISCARD constexpr auto operator-() const -> mat { return mat{ -m_data[0], -m_data[1], -m_data[2], -m_data[3] }; }

		// Scaler operators

		MYL_NO_DISCARD constexpr auto operator+(const value_type& rhs) const -> mat { return mat{ m_data[0] + rhs, m_data[1] + rhs, m_data[2] + rhs, m_data[3] + rhs }; }
		MYL_NO_DISCARD constexpr auto operator-(const value_type& rhs) const -> mat { return mat{ m_data[0] - rhs, m_data[1] - rhs, m_data[2] - rhs, m_data[3] - rhs }; }
		MYL_NO_DISCARD constexpr auto operator*(const value_type& rhs) const -> mat { return mat{ m_data[0] * rhs, m_data[1] * rhs, m_data[2] * rhs, m_data[3] * rhs }; }
		MYL_NO_DISCARD constexpr auto operator/(const value_type& rhs) const -> mat { return mat{ m_data[0] / rhs, m_data[1] / rhs, m_data[2] / rhs, m_data[3] / rhs }; }
		MYL_NO_DISCARD constexpr auto operator%(const value_type& rhs) const -> mat { return mat{ m_data[0] % rhs, m_data[1] % rhs, m_data[2] % rhs, m_data[3] % rhs }; }

		constexpr auto operator+=(const value_type& rhs) -> mat& { m_data[0] += rhs; m_data[1] += rhs; m_data[2] += rhs; m_data[3] += rhs; return *this; }
		constexpr auto operator-=(const value_type& rhs) -> mat& { m_data[0] -= rhs; m_data[1] -= rhs; m_data[2] -= rhs; m_data[3] -= rhs; return *this; }
		constexpr auto operator*=(const value_type& rhs) -> mat& { m_data[0] *= rhs; m_data[1] *= rhs; m_data[2] *= rhs; m_data[3] *= rhs; return *this; }
		constexpr auto operator/=(const value_type& rhs) -> mat& { m_data[0] /= rhs; m_data[1] /= rhs; m_data[2] /= rhs; m_data[3] /= rhs; return *this; }
		constexpr auto operator%=(const value_type& rhs) -> mat& { m_data[0] %= rhs; m_data[1] %= rhs; m_data[2] %= rhs; m_data[3] %= rhs; return *this; }

		// vec4 operators

		MYL_NO_DISCARD constexpr col_type operator*(const row_type& rhs) const { return m_data[0] * rhs[0] + m_data[1] * rhs[1] + m_data[2] * rhs[2] + m_data[3] * rhs[3]; }

		// mat4x4 operators

		MYL_NO_DISCARD constexpr auto operator+(const mat& rhs) const -> mat { return mat { m_data[0] + rhs[0], m_data[1] + rhs[1], m_data[2] + rhs[2], m_data[3] + rhs[3] }; }
		MYL_NO_DISCARD constexpr auto operator-(const mat& rhs) const -> mat { return mat { m_data[0] - rhs[0], m_data[1] - rhs[1], m_data[2] - rhs[2], m_data[3] - rhs[3] }; }

		MYL_NO_DISCARD constexpr auto operator*(const mat& rhs) const -> mat {
			return mat{
				m_data[0] * rhs[0][0] + m_data[1] * rhs[0][1] + m_data[2] * rhs[0][2] + m_data[3] * rhs[0][3],
				m_data[0] * rhs[1][0] + m_data[1] * rhs[1][1] + m_data[2] * rhs[1][2] + m_data[3] * rhs[1][3],
				m_data[0] * rhs[2][0] + m_data[1] * rhs[2][1] + m_data[2] * rhs[2][2] + m_data[3] * rhs[2][3],
				m_data[0] * rhs[3][0] + m_data[1] * rhs[3][1] + m_data[2] * rhs[3][2] + m_data[3] * rhs[3][3] };
		}

		MYL_NO_DISCARD constexpr auto operator/(const mat& rhs) const -> mat { return *this * inverse(rhs); }

		constexpr auto operator+=(const mat& rhs) -> mat& { m_data[0] += rhs[0]; m_data[1] += rhs[1]; m_data[2] += rhs[2]; m_data[3] += rhs[3]; return *this; }
		constexpr auto operator-=(const mat& rhs) -> mat& { m_data[0] -= rhs[0]; m_data[1] -= rhs[1]; m_data[2] -= rhs[2]; m_data[3] -= rhs[3]; return *this; }
		constexpr auto operator*=(const mat& rhs) -> mat& { return *this = (*this * rhs); }
		constexpr auto operator/=(const mat& rhs) -> mat& { return *this *= inverse(rhs); }
	};

	template<typename T>
	constexpr auto set_row(mat<4, 4, T>& m, usize i, const typename mat<4, 4, T>::row_type& row) -> void {
		m[0][i] = row[0];
		m[1][i] = row[1];
		m[2][i] = row[2];
		m[3][i] = row[3];
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto determinant(const mat<4, 4, T>& m) -> T {
		//     | a b c d |       | f g h |       | e g h |       | e f h |       | e f g |
		// det | e f g h | = a * | j k l | - b * | i k l | + c * | i j l | - d * | i j k |
		//     | i j k l |       | n o p |       | m o p |       | m n p |       | m n o |
		//     | m n o p |           |               |               |               |
		//                           |               |               |               |
		// w = f(kp - lo) - g(jp - ln) + h(jo - kn)  |               |               |
		// x = e(kp - lo) - g(ip - lm) + h(io - km) -+               |               |
		// y = e(jp - ln) - f(ip - lm) + h(in - jm) -----------------+               |
		// z = e(jo - kn) - f(io - km) + g(in - jm) ---------------------------------+
		//
		// det = aw - bx + cy - dz

		const T kplo = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		const T jpln = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		const T jokn = m[1][2] * m[2][3] - m[2][2] * m[1][3];
		const T iplm = m[0][2] * m[3][3] - m[3][2] * m[0][3];
		const T iokm = m[0][2] * m[2][3] - m[2][2] * m[0][3];
		const T injm = m[0][2] * m[1][3] - m[1][2] * m[0][3];

		return
			+ m[0][0] * (m[1][1] * kplo - m[2][1] * jpln + m[3][1] * jokn)
			- m[1][0] * (m[0][1] * kplo - m[2][1] * iplm + m[3][1] * iokm)
			+ m[2][0] * (m[0][1] * jpln - m[1][1] * iplm + m[3][1] * injm)
			- m[3][0] * (m[0][1] * jokn - m[1][1] * iokm + m[2][1] * injm);
	}

	template<typename T>
	MYL_NO_DISCARD constexpr auto inverse(const mat<4, 4, T>& m) -> mat<4, 4, T> {
		const T kplo = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		const T jpln = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		const T jokn = m[1][2] * m[2][3] - m[2][2] * m[1][3];
		const T lmip = m[3][2] * m[0][3] - m[0][2] * m[3][3];
		const T kmio = m[2][2] * m[0][3] - m[0][2] * m[2][3];
		const T injm = m[0][2] * m[1][3] - m[1][2] * m[0][3];
		const T gpho = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		const T fphn = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		const T fogn = m[1][1] * m[2][3] - m[2][1] * m[1][3];
		const T ephm = m[0][1] * m[3][3] - m[3][1] * m[0][3];
		const T eogm = m[0][1] * m[2][3] - m[2][1] * m[0][3];
		const T enfm = m[0][1] * m[1][3] - m[1][1] * m[0][3];
		const T glhk = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		const T flhj = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		const T fkgj = m[1][1] * m[2][2] - m[2][1] * m[1][2];
		const T elhi = m[0][1] * m[3][2] - m[3][1] * m[0][2];
		const T ekgi = m[0][1] * m[2][2] - m[2][1] * m[0][2];
		const T ejfi = m[0][1] * m[1][2] - m[1][1] * m[0][2];

		const T a1 = m[1][1] * kplo - m[2][1] * jpln + m[3][1] * jokn; // f(kp - lo) - g(jp - ln) + h(jo - kn)
		const T b1 = m[2][1] * lmip - m[3][1] * kmio + m[0][1] * kplo; // g(lm - ip) - h(km - io) + e(kp - lo)
		const T c1 = m[3][1] * injm + m[0][1] * jpln + m[1][1] * lmip; // h(in - jm) + e(jp - ln) + f(lm - ip)
		const T d1 = m[0][1] * jokn + m[1][1] * kmio + m[2][1] * injm; // e(jo - kn) + f(km - io) + g(in - jm)
		const T e1 = m[1][0] * kplo - m[2][0] * jpln + m[3][0] * jokn; // b(kp - lo) - c(jp - ln) + d(jo - kn)
		const T f1 = m[0][0] * kplo + m[2][0] * lmip - m[3][0] * kmio; // a(kp - lo) + c(lm - ip) - d(km - io)
		const T g1 = m[0][0] * jpln + m[1][0] * lmip + m[3][0] * injm; // a(jp - ln) + b(lm - ip) + d(in - jm)
		const T h1 = m[0][0] * jokn + m[1][0] * kmio + m[2][0] * injm; // a(jo - kn) + b(km - io) + c(in - jm)
		const T i1 = m[1][0] * gpho - m[2][0] * fphn + m[3][0] * fogn; // b(gp - ho) - c(fp - hn) + d(fo - gn)
		const T j1 = m[0][0] * gpho - m[2][0] * ephm + m[3][0] * eogm; // a(gp - ho) - c(ep - hm) + d(eo - gm)
		const T k1 = m[0][0] * fphn - m[1][0] * ephm + m[3][0] * enfm; // a(fp - hn) - b(ep - hm) + d(en - fm)
		const T l1 = m[0][0] * fogn - m[1][0] * eogm + m[2][0] * enfm; // a(fo - gn) - b(eo - gm) + c(en - fm)
		const T m1 = m[1][0] * glhk - m[2][0] * flhj + m[3][0] * fkgj; // b(gl - hk) - c(fl - hj) + d(fk - gj)
		const T n1 = m[0][0] * glhk - m[2][0] * elhi + m[3][0] * ekgi; // a(gl - hk) - c(el - hi) + d(ek - gi)
		const T o1 = m[0][0] * flhj - m[1][0] * elhi + m[3][0] * ejfi; // a(fl - hj) - b(el - hi) + d(ej - fi)
		const T p1 = m[0][0] * fkgj - m[1][0] * ekgi + m[2][0] * ejfi; // a(fk - gj) - b(ek - gi) + c(ej - fi)

		return mat<4, 4, T>(
			{  a1, -b1,  c1, -d1 },
			{ -e1,  f1, -g1,  h1 },
			{  i1, -j1,  k1, -l1 },
			{ -m1,  n1, -o1,  p1 }) / determinant(m);
	}

	template<typename T> using mat4x4 = mat<4, 4, T>;

	using i8mat4x4 = mat4x4<i8>;
	using i16mat4x4 = mat4x4<i16>;
	using i32mat4x4 = mat4x4<i32>;
	using i64mat4x4 = mat4x4<i64>;

	using u8mat4x4 = mat4x4<u8>;
	using u16mat4x4 = mat4x4<u16>;
	using u32mat4x4 = mat4x4<u32>;
	using u64mat4x4 = mat4x4<u64>;

	using f32mat4x4 = mat4x4<f32>;
	using f64mat4x4 = mat4x4<f64>;

	template<typename T> using mat4 = mat<4, 4, T>;

	using i8mat4 = mat4<i8>;
	using i16mat4 = mat4<i16>;
	using i32mat4 = mat4<i32>;
	using i64mat4 = mat4<i64>;

	using u8mat4 = mat4<u8>;
	using u16mat4 = mat4<u16>;
	using u32mat4 = mat4<u32>;
	using u64mat4 = mat4<u64>;

	using f32mat4 = mat4<f32>;
	using f64mat4 = mat4<f64>;
}

#ifdef MYL_DEFINE_TYPES
template<typename T> using mat4x4 = myl::mat4x4<T>;

using i8mat4x4 = myl::i8mat4x4;
using i16mat4x4 = myl::i16mat4x4;
using i32mat4x4 = myl::i32mat4x4;
using i64mat4x4 = myl::i64mat4x4;

using u8mat4x4 = myl::u8mat4x4;
using u16mat4x4 = myl::u16mat4x4;
using u32mat4x4 = myl::u32mat4x4;
using u64mat4x4 = myl::u64mat4x4;

using f32mat4x4 = myl::f32mat4x4;
using f64mat4x4 = myl::f64mat4x4;

template<typename T> using mat4 = myl::mat<4, 4, T>;

using i8mat4 = myl::i8mat4;
using i16mat4 = myl::i16mat4;
using i32mat4 = myl::i32mat4;
using i64mat4 = myl::i64mat4;

using u8mat4 = myl::u8mat4;
using u16mat4 = myl::u16mat4;
using u32mat4 = myl::u32mat4;
using u64mat4 = myl::u64mat4;

using f32mat4 = myl::f32mat4;
using f64mat4 = myl::f64mat4;
#endif