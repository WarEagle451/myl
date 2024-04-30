#pragma once
#include <myl/math/mat_common.hpp>
#include <myl/math/vec4.hpp>

namespace myl {
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

    template<typename T>
    struct mat<4, 4, T> {
        using value_type     = T;
        using column_type    = vec<4, value_type>;
        using row_type       = vec<4, value_type>;
        using transpose_type = mat<4, 4, value_type>;
    private:
        column_type m_data[4];
    public:
        // Utility

        MYL_NO_DISCARD static constexpr auto identity() noexcept -> mat {
            return mat(
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            );
        }

        // Constructor, Destructor

        MYL_NO_DISCARD constexpr mat() noexcept
            : mat(0) {}

        MYL_NO_DISCARD constexpr mat(const mat&) = default;
        MYL_NO_DISCARD constexpr mat(mat&&) = default;

        MYL_NO_DISCARD constexpr explicit mat(const value_type& scalar)
            : m_data{ column_type(scalar), column_type(scalar), column_type(scalar), column_type(scalar) } {}

        MYL_NO_DISCARD constexpr mat(
            const value_type& c0r0, const value_type& c1r0, const value_type& c2r0, const value_type& c3r0,
            const value_type& c0r1, const value_type& c1r1, const value_type& c2r1, const value_type& c3r1,
            const value_type& c0r2, const value_type& c1r2, const value_type& c2r2, const value_type& c3r2,
            const value_type& c0r3, const value_type& c1r3, const value_type& c2r3, const value_type& c3r3) noexcept
            : m_data{ column_type{ c0r0, c0r1, c0r2, c0r3 }, column_type{ c1r0, c1r1, c1r2, c1r3 }, column_type{ c2r0, c2r1, c2r2, c2r3 }, column_type{ c3r0, c3r1, c3r2, c3r3 } } {}

        MYL_NO_DISCARD constexpr mat(
            value_type&& c0r0, value_type&& c1r0, value_type&& c2r0, value_type&& c3r0,
            value_type&& c0r1, value_type&& c1r1, value_type&& c2r1, value_type&& c3r1,
            value_type&& c0r2, value_type&& c1r2, value_type&& c2r2, value_type&& c3r2,
            value_type&& c0r3, value_type&& c1r3, value_type&& c2r3, value_type&& c3r3) noexcept
            : m_data{ column_type{ std::move(c0r0), std::move(c0r1), std::move(c0r2), std::move(c0r3) }, column_type{ std::move(c1r0), std::move(c1r1), std::move(c1r2), std::move(c1r3) }, column_type{ std::move(c2r0), std::move(c2r1), std::move(c2r2), std::move(c2r3) }, column_type{ std::move(c3r0), std::move(c3r1), std::move(c3r2), std::move(c3r3) } } {}

        MYL_NO_DISCARD constexpr mat(const column_type& c0, const column_type& c1, const column_type& c2, const column_type& c3) noexcept
            : m_data{ c0, c1, c2, c3 } {}

        MYL_NO_DISCARD constexpr mat(column_type&& c0, column_type&& c1, column_type&& c2, column_type&& c3)
            : m_data{ std::move(c0), std::move(c1), std::move(c2), std::move(c3) } {}

        constexpr ~mat() = default;

        // Operators

        constexpr auto operator=(const mat&) -> mat& = default;
        constexpr auto operator=(const mat&&) -> mat& = default;

        MYL_NO_DISCARD constexpr auto operator==(const mat& r) const noexcept -> bool {
            return m_data[0] == r[0] && m_data[1] == r[1] && m_data[2] == r[2] && m_data[3] == r[3];
        }

        MYL_NO_DISCARD constexpr operator bool() const {
            constexpr mat zero = mat(static_cast<value_type>(0));
            return *this != zero;
        }

        MYL_NO_DISCARD constexpr auto operator[](usize c) -> column_type& {
            MYL_ASSERT(c < 4);
            return m_data[c];
        }

        MYL_NO_DISCARD constexpr auto operator[](usize c) const -> const column_type& {
            MYL_ASSERT(c < 4);
            return m_data[c];
        }

#if __cpp_multidimensional_subscript
        MYL_NO_DISCARD constexpr auto operator[][](usize c, usize r) -> value_type& {
            MYL_ASSERT(c < 4 && r < 4);
            return m_data[c][r];
        }

        MYL_NO_DISCARD constexpr auto operator[][](usize c, usize r) const -> const value_type& {
            MYL_ASSERT(c < 4 && r < 4);
            return m_data[c][r];
        }
#endif

        MYL_NO_DISCARD constexpr auto operator-() const -> mat { return mat{ -m_data[0], -m_data[1], -m_data[2], -m_data[3] }; }

        // Scalar Operators

        MYL_NO_DISCARD constexpr auto operator+(const value_type& s) const -> mat { return mat{ m_data[0] + s, m_data[1] + s, m_data[2] + s, m_data[3] + s }; }
        MYL_NO_DISCARD constexpr auto operator-(const value_type& s) const -> mat { return mat{ m_data[0] - s, m_data[1] - s, m_data[2] - s, m_data[3] - s }; }
        MYL_NO_DISCARD constexpr auto operator*(const value_type& s) const -> mat { return mat{ m_data[0] * s, m_data[1] * s, m_data[2] * s, m_data[3] * s }; }
        MYL_NO_DISCARD constexpr auto operator/(const value_type& s) const -> mat { return mat{ m_data[0] / s, m_data[1] / s, m_data[2] / s, m_data[3] / s }; }
        MYL_NO_DISCARD constexpr auto operator%(const value_type& s) const -> mat { return mat{ m_data[0] % s, m_data[1] % s, m_data[2] % s, m_data[3] % s }; }

        constexpr auto operator+=(const value_type& s) -> mat& { m_data[0] += s; m_data[1] += s; m_data[2] += s; m_data[3] += s; return *this; }
        constexpr auto operator-=(const value_type& s) -> mat& { m_data[0] -= s; m_data[1] -= s; m_data[2] -= s; m_data[3] -= s; return *this; }
        constexpr auto operator*=(const value_type& s) -> mat& { m_data[0] *= s; m_data[1] *= s; m_data[2] *= s; m_data[3] *= s; return *this; }
        constexpr auto operator/=(const value_type& s) -> mat& { m_data[0] /= s; m_data[1] /= s; m_data[2] /= s; m_data[3] /= s; return *this; }
        constexpr auto operator%=(const value_type& s) -> mat& { m_data[0] %= s; m_data[1] %= s; m_data[2] %= s; m_data[3] %= s; return *this; }

        // vec4 Operators

        MYL_NO_DISCARD constexpr auto operator*(const row_type& r) const -> column_type { return m_data[0] * r[0] + m_data[1] * r[1] + m_data[2] * r[2] + m_data[3] * r[3]; }

        // mat4x4 Operators

        MYL_NO_DISCARD constexpr auto operator+(const mat& r) const -> mat { return mat{ m_data[0] + r[0], m_data[1] + r[1], m_data[2] + r[2], m_data[3] + r[3] }; }
        MYL_NO_DISCARD constexpr auto operator-(const mat& r) const -> mat { return mat{ m_data[0] - r[0], m_data[1] - r[1], m_data[2] - r[2], m_data[3] - r[3] }; }

        MYL_NO_DISCARD constexpr auto operator*(const mat& r) const -> mat {
            return mat{
                m_data[0] * r[0][0] + m_data[1] * r[0][1] + m_data[2] * r[0][2] + m_data[3] * r[0][3],
                m_data[0] * r[1][0] + m_data[1] * r[1][1] + m_data[2] * r[1][2] + m_data[3] * r[1][3],
                m_data[0] * r[2][0] + m_data[1] * r[2][1] + m_data[2] * r[2][2] + m_data[3] * r[2][3],
                m_data[0] * r[3][0] + m_data[1] * r[3][1] + m_data[2] * r[3][2] + m_data[3] * r[3][3]
            };
        }

        MYL_NO_DISCARD constexpr auto operator/(const mat& r) const -> mat { return *this * inverse(r); }

        constexpr auto operator+=(const mat& r) -> mat& { m_data[0] += r[0]; m_data[1] += r[1]; m_data[2] += r[2]; m_data[3] += r[3]; return *this; }
        constexpr auto operator-=(const mat& r) -> mat& { m_data[0] -= r[0]; m_data[1] -= r[1]; m_data[2] -= r[2]; m_data[3] -= r[3]; return *this; }
        constexpr auto operator*=(const mat& r) -> mat& { return *this = (*this * r); }
        constexpr auto operator/=(const mat& r) -> mat& { return *this *= inverse(r); }
    };

    template<typename T>
    MYL_NO_DISCARD constexpr auto determinant(const mat4<T>& m) -> T {
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
    MYL_NO_DISCARD constexpr auto inverse(const mat4<T>& m) -> mat4<T> {
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
            { -m1,  n1, -o1,  p1 }
        ) / determinant(m);
    }
}
