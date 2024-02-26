#pragma once
#include <myl/math/vec.hpp>

#include <utility>

namespace myl {
    template<typename T> using vec2 = vec<2, T>;

    using i8vec2 = vec2<i8>;
    using i16vec2 = vec2<i16>;
    using i32vec2 = vec2<i32>;
    using i64vec2 = vec2<i64>;

    using u8vec2 = vec2<u8>;
    using u16vec2 = vec2<u16>;
    using u32vec2 = vec2<u32>;
    using u64vec2 = vec2<u64>;

    using f32vec2 = vec2<f32>;
    using f64vec2 = vec2<f64>;

    template<typename T>
    struct vec<2, T> {
        using value_type = T;

        union {
            value_type data[2];
            struct { value_type x, y; };
            struct { value_type r, g; };
            struct { value_type s, t; };
            struct { value_type u, v; };
            struct { value_type w, h; };
        };

        // Constructors / Destructor

        MYL_NO_DISCARD constexpr vec() = default;
        MYL_NO_DISCARD constexpr vec(const vec& v) = default;
        MYL_NO_DISCARD constexpr vec(vec&& v) = default;

        MYL_NO_DISCARD constexpr explicit vec(const value_type& s)
            : data{ s, s } {}

        MYL_NO_DISCARD constexpr vec(const value_type& x, const value_type& y)
            : data{ x, y } {}

        MYL_NO_DISCARD constexpr vec(value_type&& x, value_type&& y)
            : data{ std::move(x), std::move(y) } {}

        MYL_NO_DISCARD constexpr explicit vec(const vec<3, value_type>& v)
            : data{ v.x, v.y } {}

        MYL_NO_DISCARD constexpr explicit vec(const vec<4, value_type>& v)
            : data{ v.x, v.y } {}

        // Operators

        constexpr auto operator=(const vec&) -> vec& = default;
        constexpr auto operator=(const vec&&) -> vec& = default;

        MYL_NO_DISCARD constexpr operator bool() const {
            return
                x == static_cast<value_type>(0) &&
                y == static_cast<value_type>(0);
        }

        MYL_NO_DISCARD constexpr auto operator[](usize i) -> value_type& { return data[i]; }
        MYL_NO_DISCARD constexpr auto operator[](usize i) const -> const value_type& { return data[i]; }

        MYL_NO_DISCARD constexpr auto operator-() const -> vec { return vec{ -x, -y }; }

        // Scaler Operators

        MYL_NO_DISCARD constexpr auto operator+(const value_type& s) const -> vec { return vec{ x + s, y + s }; }
		MYL_NO_DISCARD constexpr auto operator-(const value_type& s) const -> vec { return vec{ x - s, y - s }; }
		MYL_NO_DISCARD constexpr auto operator*(const value_type& s) const -> vec { return vec{ x * s, y * s }; }
		MYL_NO_DISCARD constexpr auto operator/(const value_type& s) const -> vec { return vec{ x / s, y / s }; }
		MYL_NO_DISCARD constexpr auto operator%(const value_type& s) const -> vec { return vec{ x % s, y % s }; }

        constexpr auto operator+=(const value_type& s) -> vec& { x += s; y += s; return *this; }
		constexpr auto operator-=(const value_type& s) -> vec& { x -= s; y -= s; return *this; }
		constexpr auto operator*=(const value_type& s) -> vec& { x *= s; y *= s; return *this; }
		constexpr auto operator/=(const value_type& s) -> vec& { x /= s; y /= s; return *this; }
		constexpr auto operator%=(const value_type& s) -> vec& { x %= s; y %= s; return *this; }
        
        // vec2 Operators

        MYL_NO_DISCARD constexpr auto operator+(const vec& r) const -> vec { return vec{ x + r.x, y + r.y }; }
		MYL_NO_DISCARD constexpr auto operator-(const vec& r) const -> vec { return vec{ x - r.x, y - r.y }; }
		MYL_NO_DISCARD constexpr auto operator*(const vec& r) const -> vec { return vec{ x * r.x, y * r.y }; }
		MYL_NO_DISCARD constexpr auto operator/(const vec& r) const -> vec { return vec{ x / r.x, y / r.y }; }
		MYL_NO_DISCARD constexpr auto operator%(const vec& r) const -> vec { return vec{ x % r.x, y % r.y }; }

		constexpr auto operator+=(const vec& r) -> vec& { x += r.x; y += r.y; return *this; }
		constexpr auto operator-=(const vec& r) -> vec& { x -= r.x; y -= r.y; return *this; }
		constexpr auto operator*=(const vec& r) -> vec& { x *= r.x; y *= r.y; return *this; }
		constexpr auto operator/=(const vec& r) -> vec& { x /= r.x; y /= r.y; return *this; }
		constexpr auto operator%=(const vec& r) -> vec& { x %= r.x; y %= r.y; return *this; }
    };

    template<usize C, typename T>
    MYL_NO_DISCARD constexpr auto operator==(const vec<C, T>& l, const vec<C, T>& r) -> bool {
        return l.x == r.x && l.y == r.y;
    }

    template<typename T>
	MYL_NO_DISCARD constexpr auto dot(const vec2<T>& a, const vec2<T>& b) -> T {
		return a.x * b.x + a.y * b.y;
	}
}
