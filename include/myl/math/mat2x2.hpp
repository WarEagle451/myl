#pragma once
#include <myl/math/mat_common.hpp>
#include <myl/math/vec2.hpp>

namespace myl {
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

    template<typename T>
    struct mat<2, 2, T> {
        using value_type     = T;
        using column_type    = vec<2, value_type>;
        using row_type       = vec<2, value_type>;
        using transpose_type = mat<2, 2, value_type>;
    private:
        column_type m_data[2];
    public:
        // Utility

        MYL_NO_DISCARD static constexpr auto identity() noexcept -> mat {
            return mat(
                1, 0,
                0, 1
            );
        }

        // Constructor, Destructor

        MYL_NO_DISCARD constexpr mat() noexcept
            : mat(0) {}

        MYL_NO_DISCARD constexpr mat(const mat&) = default;
        MYL_NO_DISCARD constexpr mat(mat&&) = default;

        MYL_NO_DISCARD constexpr explicit mat(const value_type& scalar)
            : m_data{ column_type(scalar), column_type(scalar) } {}

        MYL_NO_DISCARD constexpr mat(
            const value_type& c0r0, const value_type& c1r0,
            const value_type& c0r1, const value_type& c1r1) noexcept
            : m_data{ column_type{ c0r0, c0r1 }, column_type{ c1r0, c1r1 } } {}

        MYL_NO_DISCARD constexpr mat(
            value_type&& c0r0, value_type&& c1r0,
            value_type&& c0r1, value_type&& c1r1) noexcept
            : m_data{ column_type{ std::move(c0r0), std::move(c0r1) }, column_type{ std::move(c1r0), std::move(c1r1) } } {}

        MYL_NO_DISCARD constexpr mat(const column_type& c0, const column_type& c1) noexcept
            : m_data{ c0, c1 } {}

        MYL_NO_DISCARD constexpr mat(column_type&& c0, column_type&& c1)
            : m_data{ std::move(c0), std::move(c1) } {}

        constexpr ~mat() = default;

        // Operators

        constexpr auto operator=(const mat&) -> mat& = default;
        constexpr auto operator=(const mat&&) -> mat& = default;

        MYL_NO_DISCARD constexpr auto operator==(const mat& r) const noexcept -> bool {
            return m_data[0] == r[0] && m_data[1] == r[1];
        }

        MYL_NO_DISCARD constexpr operator bool() const {
            constexpr mat zero = mat(static_cast<value_type>(0));
            return *this != zero;
        }

        MYL_NO_DISCARD constexpr auto operator[](usize c) -> column_type& {
            MYL_ASSERT(c < 2);
            return m_data[c];
        }

        MYL_NO_DISCARD constexpr auto operator[](usize c) const -> const column_type& {
            MYL_ASSERT(c < 2);
            return m_data[c];
        }

#if __cpp_multidimensional_subscript
        MYL_NO_DISCARD constexpr auto operator[][](usize c, usize r) -> value_type& {
            MYL_ASSERT(c < 2 && r < 2);
            return m_data[c][r];
        }

        MYL_NO_DISCARD constexpr auto operator[][](usize c, usize r) const -> const value_type& {
            MYL_ASSERT(c < 2 && r < 2);
            return m_data[c][r];
        }
#endif

        MYL_NO_DISCARD constexpr auto operator-() const -> mat { return mat{ -m_data[0], -m_data[1] }; }

        // Scalar Operators

        MYL_NO_DISCARD constexpr auto operator+(const value_type& s) const -> mat { return mat{ m_data[0] + s, m_data[1] + s }; }
        MYL_NO_DISCARD constexpr auto operator-(const value_type& s) const -> mat { return mat{ m_data[0] - s, m_data[1] - s }; }
        MYL_NO_DISCARD constexpr auto operator*(const value_type& s) const -> mat { return mat{ m_data[0] * s, m_data[1] * s }; }
        MYL_NO_DISCARD constexpr auto operator/(const value_type& s) const -> mat { return mat{ m_data[0] / s, m_data[1] / s }; }
        MYL_NO_DISCARD constexpr auto operator%(const value_type& s) const -> mat { return mat{ m_data[0] % s, m_data[1] % s }; }

        constexpr auto operator+=(const value_type& s) -> mat& { m_data[0] += s; m_data[1] += s; return *this; }
        constexpr auto operator-=(const value_type& s) -> mat& { m_data[0] -= s; m_data[1] -= s; return *this; }
        constexpr auto operator*=(const value_type& s) -> mat& { m_data[0] *= s; m_data[1] *= s; return *this; }
        constexpr auto operator/=(const value_type& s) -> mat& { m_data[0] /= s; m_data[1] /= s; return *this; }
        constexpr auto operator%=(const value_type& s) -> mat& { m_data[0] %= s; m_data[1] %= s; return *this; }

        // vec2 Operators

        MYL_NO_DISCARD constexpr auto operator*(const row_type& r) const -> column_type { return m_data[0] * r[0] + m_data[1] * r[1]; }

        // mat2x2 Operators

        MYL_NO_DISCARD constexpr auto operator+(const mat& r) const -> mat { return mat{ m_data[0] + r[0], m_data[1] + r[1] }; }
        MYL_NO_DISCARD constexpr auto operator-(const mat& r) const -> mat { return mat{ m_data[0] - r[0], m_data[1] - r[1] }; }
        
        MYL_NO_DISCARD constexpr auto operator*(const mat& r) const -> mat {
            return mat {
                m_data[0] * r[0][0] + m_data[1] * r[0][1],
                m_data[0] * r[1][0] + m_data[1] * r[1][1]
            };
        }

        MYL_NO_DISCARD constexpr auto operator/(const mat& r) const -> mat { return *this * inverse(r); }

        constexpr auto operator+=(const mat& r) -> mat& { m_data[0] += r[0]; m_data[1] += r[1]; return *this; }
        constexpr auto operator-=(const mat& r) -> mat& { m_data[0] -= r[0]; m_data[1] -= r[1]; return *this; }
        constexpr auto operator*=(const mat& r) -> mat& { return *this = (*this * r); }
        constexpr auto operator/=(const mat& r) -> mat& { return *this *= inverse(r); }
    };

    template<typename T>
    MYL_NO_DISCARD constexpr auto determinant(const mat2<T>& m) -> T {
        //       | a b |
        // det = | c d | = ad - bc
        return m[0][0] * m[1][1] - m[1][0] * m[0][1];
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto inverse(const mat2<T>& m) -> mat2<T> {
        return mat2<T>(
            m[1][1], -m[1][0],
            -m[0][1], m[0][0]
        ) / determinant(m);
    }
}
