#pragma once
#include <myl/math/mat.hpp>
#include <myl/math/vec2.hpp>
#include <myl/math/vec4.hpp>

namespace myl {
    template<typename T> using mat4x2 = mat<4, 2, T>;

    using i8mat4x2 = mat4x2<i8>;
    using i16mat4x2 = mat4x2<i16>;
    using i32mat4x2 = mat4x2<i32>;
    using i64mat4x2 = mat4x2<i64>;

    using u8mat4x2 = mat4x2<u8>;
    using u16mat4x2 = mat4x2<u16>;
    using u32mat4x2 = mat4x2<u32>;
    using u64mat4x2 = mat4x2<u64>;

    using f32mat4x2 = mat4x2<f32>;
    using f64mat4x2 = mat4x2<f64>;

    template<typename T>
    struct mat<4, 2, T> {
        using value_type     = T;
        using column_type    = vec<2, value_type>;
        using row_type       = vec<4, value_type>;
        using transpose_type = mat<2, 4, value_type>;
    private:
        column_type m_data[4];
    public:
        // Constructor, Destructor

        MYL_NO_DISCARD constexpr mat() noexcept
            : mat(0) {}

        MYL_NO_DISCARD constexpr explicit mat(const value_type& scalar)
            : m_data{ column_type(scalar), column_type(scalar), column_type(scalar), column_type(scalar) } {}

        MYL_NO_DISCARD constexpr mat(
            const value_type& c0r0, const value_type& c1r0, const value_type& c2r0, const value_type& c3r0,
            const value_type& c0r1, const value_type& c1r1, const value_type& c2r1, const value_type& c3r1) noexcept
            : m_data{ column_type{ c0r0, c0r1 }, column_type{ c1r0, c1r1 }, column_type{ c2r0, c2r1 }, column_type{ c3r0, c3r1 } } {}

        MYL_NO_DISCARD constexpr mat(
            value_type&& c0r0, value_type&& c1r0, value_type&& c2r0, value_type&& c3r0,
            value_type&& c0r1, value_type&& c1r1, value_type&& c2r1, value_type&& c3r1) noexcept
            : m_data{ column_type{ std::move(c0r0), std::move(c0r1) }, column_type{ std::move(c1r0), std::move(c1r1) }, column_type{ std::move(c2r0), std::move(c2r1) }, column_type{ std::move(c3r0), std::move(c3r1) } } {}

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
            return *this == zero;
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
            MYL_ASSERT(c < 4 && r < 2);
            return m_data[c][r];
        }

        MYL_NO_DISCARD constexpr auto operator[][](usize c, usize r) const -> const value_type& {
            MYL_ASSERT(c < 4 && r < 2);
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

        // mat4x2 Operators

        MYL_NO_DISCARD constexpr auto operator+(const mat& r) const -> mat { return mat{ m_data[0] + r[0], m_data[1] + r[1], m_data[2] + r[2], m_data[3] + r[3] }; }
        MYL_NO_DISCARD constexpr auto operator-(const mat& r) const -> mat { return mat{ m_data[0] - r[0], m_data[1] - r[1], m_data[2] - r[2], m_data[3] - r[3] }; }

        constexpr auto operator+=(const mat& r) -> mat& { m_data[0] += r[0]; m_data[1] += r[1]; m_data[2] += r[2]; m_data[3] += r[3]; return *this; }
        constexpr auto operator-=(const mat& r) -> mat& { m_data[0] -= r[0]; m_data[1] -= r[1]; m_data[2] -= r[2]; m_data[3] -= r[3]; return *this; }
    };
}
