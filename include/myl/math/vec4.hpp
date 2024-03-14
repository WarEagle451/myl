#pragma once
#include <myl/math/vec.hpp>

#include <utility>

namespace myl {
    template<typename T> using vec4 = vec<4, T>;

    using i8vec4 = vec4<i8>;
    using i16vec4 = vec4<i16>;
    using i32vec4 = vec4<i32>;
    using i64vec4 = vec4<i64>;

    using u8vec4 = vec4<u8>;
    using u16vec4 = vec4<u16>;
    using u32vec4 = vec4<u32>;
    using u64vec4 = vec4<u64>;

    using f32vec4 = vec4<f32>;
    using f64vec4 = vec4<f64>;

    template<typename T>
    struct vec<4, T> {
        using value_type = T;

        union {
            value_type data[4];
            struct { value_type x, y, z, w; };
            struct { value_type r, g, b, a; };
            struct { value_type s, t, p, q; };
        };

        // Constructors / Destructor

        MYL_NO_DISCARD constexpr vec() = default;
        MYL_NO_DISCARD constexpr vec(const vec& v) = default;
        MYL_NO_DISCARD constexpr vec(vec&& v) = default;

        MYL_NO_DISCARD constexpr explicit vec(const value_type& s)
            : data{ s, s, s, s } {}

        MYL_NO_DISCARD constexpr vec(const value_type& x, const value_type& y, const value_type& z, const value_type& w)
            : data{ x, y, z, w } {}

        MYL_NO_DISCARD constexpr vec(value_type&& x, value_type&& y, value_type&& z, value_type&& w)
            : data{ std::move(x), std::move(y), std::move(z), std::move(w) } {}
            
        MYL_NO_DISCARD constexpr vec(const vec<2, value_type>& xy, const value_type& z, const value_type& w)
            : data{ xy.x, xy.y, z, w } {}

        MYL_NO_DISCARD constexpr vec(const value_type& x, const vec<2, value_type>& yz, const value_type& w)
            : data{ x, yz.y, yz.z, w } {}

        MYL_NO_DISCARD constexpr vec(const value_type& x, const value_type& y, const vec<2, value_type>& zw)
            : data{ x, y, zw.z, zw.w } {}

        MYL_NO_DISCARD constexpr vec(const vec<2, value_type>& xy, const vec<2, value_type>& zw)
            : data{ xy.x, xy.y, zw.z, zw.w } {}

        MYL_NO_DISCARD constexpr vec(const vec<3, value_type>& xyz, const value_type& w)
            : data{ xyz.x, xyz.y, xyz.z, w } {}

        MYL_NO_DISCARD constexpr vec(const value_type& x, const vec<3, value_type>& yzw)
            : data{ x, yzw.y, yzw.z, yzw.w } {}

        // Operators

        constexpr auto operator=(const vec&) -> vec& = default;
        constexpr auto operator=(const vec&&) -> vec& = default;

        MYL_NO_DISCARD constexpr operator bool() const {
            return
                x == static_cast<value_type>(0) &&
                y == static_cast<value_type>(0) &&
                z == static_cast<value_type>(0) &&
                w == static_cast<value_type>(0);
        }

        MYL_NO_DISCARD constexpr auto operator[](usize i) -> value_type& { return data[i]; }
        MYL_NO_DISCARD constexpr auto operator[](usize i) const -> const value_type& { return data[i]; }

        MYL_NO_DISCARD constexpr auto operator-() const -> vec { return vec{ -x, -y, -z, -w }; }

        // Scaler Operators

        MYL_NO_DISCARD constexpr auto operator+(const value_type& s) const -> vec { return vec{ x + s, y + s, z + s, w + s }; }
        MYL_NO_DISCARD constexpr auto operator-(const value_type& s) const -> vec { return vec{ x - s, y - s, z - s, w - s }; }
        MYL_NO_DISCARD constexpr auto operator*(const value_type& s) const -> vec { return vec{ x * s, y * s, z * s, w * s }; }
        MYL_NO_DISCARD constexpr auto operator/(const value_type& s) const -> vec { return vec{ x / s, y / s, z / s, w / s }; }
        MYL_NO_DISCARD constexpr auto operator%(const value_type& s) const -> vec { return vec{ x % s, y % s, z % s, w % s }; }

        constexpr auto operator+=(const value_type& s) -> vec& { x += s; y += s; z += s; w += s; return *this; }
        constexpr auto operator-=(const value_type& s) -> vec& { x -= s; y -= s; z -= s; w -= s; return *this; }
        constexpr auto operator*=(const value_type& s) -> vec& { x *= s; y *= s; z *= s; w *= s; return *this; }
        constexpr auto operator/=(const value_type& s) -> vec& { x /= s; y /= s; z /= s; w /= s; return *this; }
        constexpr auto operator%=(const value_type& s) -> vec& { x %= s; y %= s; z %= s; w %= s; return *this; }
        
        // vec2 Operators

        MYL_NO_DISCARD constexpr auto operator+(const vec<2, value_type>& r) const -> vec { return vec{ x + r.x, y + r.y, z, w }; }
        MYL_NO_DISCARD constexpr auto operator-(const vec<2, value_type>& r) const -> vec { return vec{ x - r.x, y - r.y, z, w }; }
        MYL_NO_DISCARD constexpr auto operator*(const vec<2, value_type>& r) const -> vec { return vec{ x * r.x, y * r.y, z, w }; }
        MYL_NO_DISCARD constexpr auto operator/(const vec<2, value_type>& r) const -> vec { return vec{ x / r.x, y / r.y, z, w }; }
        MYL_NO_DISCARD constexpr auto operator%(const vec<2, value_type>& r) const -> vec { return vec{ x % r.x, y % r.y, z, w }; }

        constexpr auto operator+=(const vec<2, value_type>& r) -> vec& { x += r.x; y += r.y; return *this; }
        constexpr auto operator-=(const vec<2, value_type>& r) -> vec& { x -= r.x; y -= r.y; return *this; }
        constexpr auto operator*=(const vec<2, value_type>& r) -> vec& { x *= r.x; y *= r.y; return *this; }
        constexpr auto operator/=(const vec<2, value_type>& r) -> vec& { x /= r.x; y /= r.y; return *this; }
        constexpr auto operator%=(const vec<2, value_type>& r) -> vec& { x %= r.x; y %= r.y; return *this; }

        // vec3 Operators

        MYL_NO_DISCARD constexpr auto operator+(const vec<3, value_type>& r) const -> vec { return vec{ x + r.x, y + r.y, x + r.z, w }; }
        MYL_NO_DISCARD constexpr auto operator-(const vec<3, value_type>& r) const -> vec { return vec{ x - r.x, y - r.y, x - r.z, w }; }
        MYL_NO_DISCARD constexpr auto operator*(const vec<3, value_type>& r) const -> vec { return vec{ x * r.x, y * r.y, x * r.z, w }; }
        MYL_NO_DISCARD constexpr auto operator/(const vec<3, value_type>& r) const -> vec { return vec{ x / r.x, y / r.y, x / r.z, w }; }
        MYL_NO_DISCARD constexpr auto operator%(const vec<3, value_type>& r) const -> vec { return vec{ x % r.x, y % r.y, x % r.z, w }; }

        constexpr auto operator+=(const vec<3, value_type>& r) -> vec& { x += r.x; y += r.y; z += r.z; return *this; }
        constexpr auto operator-=(const vec<3, value_type>& r) -> vec& { x -= r.x; y -= r.y; z -= r.z; return *this; }
        constexpr auto operator*=(const vec<3, value_type>& r) -> vec& { x *= r.x; y *= r.y; z *= r.z; return *this; }
        constexpr auto operator/=(const vec<3, value_type>& r) -> vec& { x /= r.x; y /= r.y; z /= r.z; return *this; }
        constexpr auto operator%=(const vec<3, value_type>& r) -> vec& { x %= r.x; y %= r.y; z %= r.z; return *this; }

        // vec4 Operators

        MYL_NO_DISCARD constexpr auto operator+(const vec& r) const -> vec { return vec{ x + r.x, y + r.y, x + r.z, w + r.w }; }
        MYL_NO_DISCARD constexpr auto operator-(const vec& r) const -> vec { return vec{ x - r.x, y - r.y, x - r.z, w - r.w }; }
        MYL_NO_DISCARD constexpr auto operator*(const vec& r) const -> vec { return vec{ x * r.x, y * r.y, x * r.z, w * r.w }; }
        MYL_NO_DISCARD constexpr auto operator/(const vec& r) const -> vec { return vec{ x / r.x, y / r.y, x / r.z, w / r.w }; }
        MYL_NO_DISCARD constexpr auto operator%(const vec& r) const -> vec { return vec{ x % r.x, y % r.y, x % r.z, w % r.w }; }

        constexpr auto operator+=(const vec& r) -> vec& { x += r.x; y += r.y; z += r.z; w += r.w; return *this; }
        constexpr auto operator-=(const vec& r) -> vec& { x -= r.x; y -= r.y; z -= r.z; w -= r.w; return *this; }
        constexpr auto operator*=(const vec& r) -> vec& { x *= r.x; y *= r.y; z *= r.z; w *= r.w; return *this; }
        constexpr auto operator/=(const vec& r) -> vec& { x /= r.x; y /= r.y; z /= r.z; w /= r.w; return *this; }
        constexpr auto operator%=(const vec& r) -> vec& { x %= r.x; y %= r.y; z %= r.z; w %= r.w; return *this; }
    };

    template<typename T>
    MYL_NO_DISCARD constexpr auto operator==(const vec4<T>& l, const vec4<T>& r) -> bool {
        return l.x == r.x && l.y == r.y && l.z == r.z && l.w == r.w;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto dot(const vec4<T>& a, const vec4<T>& b) -> T {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }
}
