#pragma once
#include <myl/math/mat_common.hpp>
#include <myl/math/vec3.hpp>

namespace myl {
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

    template<typename T>
    struct mat<3, 3, T> {
        using value_type     = T;
        using column_type    = vec<3, value_type>;
        using row_type       = vec<3, value_type>;
        using transpose_type = mat<3, 3, value_type>;
    private:
        column_type m_data[3];
    public:
        // Utility

        MYL_NO_DISCARD static constexpr auto identity() noexcept -> mat {
            return mat(
                1, 0, 0,
                0, 1, 0,
                0, 0, 1
            );
        }

        // Constructor, Destructor

        MYL_NO_DISCARD constexpr mat() noexcept
            : mat(0) {}

        MYL_NO_DISCARD constexpr mat(const mat&) = default;
        MYL_NO_DISCARD constexpr mat(mat&&) = default;

        MYL_NO_DISCARD constexpr explicit mat(const value_type& scalar)
            : m_data{ column_type(scalar), column_type(scalar), column_type(scalar) } {}

        MYL_NO_DISCARD constexpr mat(
            const value_type& c0r0, const value_type& c1r0, const value_type& c2r0,
            const value_type& c0r1, const value_type& c1r1, const value_type& c2r1,
            const value_type& c0r2, const value_type& c1r2, const value_type& c2r2) noexcept
            : m_data{ column_type{ c0r0, c0r1, c0r2 }, column_type{ c1r0, c1r1, c1r2 }, column_type{ c2r0, c2r1, c2r2 } } {}

        MYL_NO_DISCARD constexpr mat(
            value_type&& c0r0, value_type&& c1r0, value_type&& c2r0,
            value_type&& c0r1, value_type&& c1r1, value_type&& c2r1,
            value_type&& c0r2, value_type&& c1r2, value_type&& c2r2) noexcept
            : m_data{ column_type{ std::move(c0r0), std::move(c0r1), std::move(c0r2) }, column_type{ std::move(c1r0), std::move(c1r1), std::move(c1r2) }, column_type{ std::move(c2r0), std::move(c2r1), std::move(c2r2) } } {}

        MYL_NO_DISCARD constexpr mat(const column_type& c0, const column_type& c1, const column_type& c2) noexcept
            : m_data{ c0, c1, c2 } {}

        MYL_NO_DISCARD constexpr mat(column_type&& c0, column_type&& c1, column_type&& c2)
            : m_data{ std::move(c0), std::move(c1), std::move(c2) } {}

        constexpr ~mat() = default;

        // Operators

        constexpr auto operator=(const mat&) -> mat& = default;
        constexpr auto operator=(mat&&) -> mat& = default;

        MYL_NO_DISCARD constexpr auto operator==(const mat& r) const noexcept -> bool {
            return m_data[0] == r[0] && m_data[1] == r[1] && m_data[2] == r[2];
        }

        MYL_NO_DISCARD constexpr operator bool() const {
            constexpr mat zero = mat(static_cast<value_type>(0));
            return *this != zero;
        }

        MYL_NO_DISCARD constexpr auto operator[](usize c) -> column_type& {
            MYL_ASSERT(c < 3);
            return m_data[c];
        }

        MYL_NO_DISCARD constexpr auto operator[](usize c) const -> const column_type& {
            MYL_ASSERT(c < 3);
            return m_data[c];
        }

#if defined(__cpp_multidimensional_subscript) && __cpp_multidimensional_subscript >= 202110L
        MYL_NO_DISCARD constexpr auto operator[][](usize c, usize r) -> value_type& {
            MYL_ASSERT(c < 3 && r < 3);
            return m_data[c][r];
        }

        MYL_NO_DISCARD constexpr auto operator[][](usize c, usize r) const -> const value_type& {
            MYL_ASSERT(c < 3 && r < 3);
            return m_data[c][r];
        }
#endif

        MYL_NO_DISCARD constexpr auto operator-() const -> mat { return mat{ -m_data[0], -m_data[1], -m_data[2] }; }

        // Scalar Operators

        MYL_NO_DISCARD constexpr auto operator+(const value_type& s) const -> mat { return mat{ m_data[0] + s, m_data[1] + s, m_data[2] + s }; }
        MYL_NO_DISCARD constexpr auto operator-(const value_type& s) const -> mat { return mat{ m_data[0] - s, m_data[1] - s, m_data[2] - s }; }
        MYL_NO_DISCARD constexpr auto operator*(const value_type& s) const -> mat { return mat{ m_data[0] * s, m_data[1] * s, m_data[2] * s }; }
        MYL_NO_DISCARD constexpr auto operator/(const value_type& s) const -> mat { return mat{ m_data[0] / s, m_data[1] / s, m_data[2] / s }; }
        MYL_NO_DISCARD constexpr auto operator%(const value_type& s) const -> mat { return mat{ m_data[0] % s, m_data[1] % s, m_data[2] % s }; }

        constexpr auto operator+=(const value_type& s) -> mat& { m_data[0] += s; m_data[1] += s; m_data[2] += s; return *this; }
        constexpr auto operator-=(const value_type& s) -> mat& { m_data[0] -= s; m_data[1] -= s; m_data[2] -= s; return *this; }
        constexpr auto operator*=(const value_type& s) -> mat& { m_data[0] *= s; m_data[1] *= s; m_data[2] *= s; return *this; }
        constexpr auto operator/=(const value_type& s) -> mat& { m_data[0] /= s; m_data[1] /= s; m_data[2] /= s; return *this; }
        constexpr auto operator%=(const value_type& s) -> mat& { m_data[0] %= s; m_data[1] %= s; m_data[2] %= s; return *this; }

        // vec3 Operators

        MYL_NO_DISCARD constexpr auto operator*(const row_type& r) const -> column_type { return m_data[0] * r[0] + m_data[1] * r[1] + m_data[2] * r[2]; }

        // mat3x3 Operators

        MYL_NO_DISCARD constexpr auto operator+(const mat& r) const -> mat { return mat{ m_data[0] + r[0], m_data[1] + r[1], m_data[2] + r[2] }; }
        MYL_NO_DISCARD constexpr auto operator-(const mat& r) const -> mat { return mat{ m_data[0] - r[0], m_data[1] - r[1], m_data[2] - r[2] }; }

        MYL_NO_DISCARD constexpr auto operator*(const mat& r) const -> mat {
            return mat{
                m_data[0] * r[0][0] + m_data[1] * r[0][1] + m_data[2] * r[0][2],
                m_data[0] * r[1][0] + m_data[1] * r[1][1] + m_data[2] * r[1][2],
                m_data[0] * r[2][0] + m_data[1] * r[2][1] + m_data[2] * r[2][2]
            };
        }

        MYL_NO_DISCARD constexpr auto operator/(const mat& r) const -> mat { return *this * inverse(r); }

        constexpr auto operator+=(const mat& r) -> mat& { m_data[0] += r[0]; m_data[1] += r[1]; m_data[2] += r[2]; return *this; }
        constexpr auto operator-=(const mat& r) -> mat& { m_data[0] -= r[0]; m_data[1] -= r[1]; m_data[2] -= r[2]; return *this; }
        constexpr auto operator*=(const mat& r) -> mat& { return *this = (*this * r); }
        constexpr auto operator/=(const mat& r) -> mat& { return *this *= inverse(r); }
    };

    template<typename T>
    MYL_NO_DISCARD constexpr auto determinant(const mat3<T>& m) -> T {
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
    MYL_NO_DISCARD constexpr auto inverse(const mat3<T>& m) -> mat3<T> {
        return mat3<T>(
             (m[1][1] * m[2][2] - m[1][2] * m[2][1]), //  (ei - hf)
            -(m[1][0] * m[2][2] - m[1][2] * m[2][0]), // -(bi - hc)
             (m[1][0] * m[2][1] - m[1][1] * m[2][0]), //  (bf - ec)

            -(m[0][1] * m[2][2] - m[2][1] * m[0][2]), // -(di - fg)
             (m[0][0] * m[2][2] - m[0][2] * m[2][0]), //  (ai - gc)
            -(m[0][0] * m[2][1] - m[0][1] * m[2][0]), // -(af - dc)

             (m[0][1] * m[1][2] - m[0][2] * m[1][1]), //  (dh - ge)
            -(m[0][0] * m[1][2] - m[0][2] * m[1][0]), // -(ah - gb)
             (m[0][0] * m[1][1] - m[0][1] * m[1][0])  //  (ae - db)
        ) / determinant(m);
    }
}
