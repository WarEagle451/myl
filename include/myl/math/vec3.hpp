#pragma once
#include <myl/math/vec_common.hpp>

#include <utility>

namespace myl {
    template<typename T> using vec3 = vec<3, T>;

    using i8vec3 = vec3<i8>;
    using i16vec3 = vec3<i16>;
    using i32vec3 = vec3<i32>;
    using i64vec3 = vec3<i64>;

    using u8vec3 = vec3<u8>;
    using u16vec3 = vec3<u16>;
    using u32vec3 = vec3<u32>;
    using u64vec3 = vec3<u64>;

    using f32vec3 = vec3<f32>;
    using f64vec3 = vec3<f64>;

    template<typename T>
    struct vec<3, T> {
        using value_type = T;

        union {
            value_type data[3]{ 0 };
            struct { value_type x, y, z; };
            struct { value_type r, g, b; };
            struct { value_type s, t, p; };
            struct { value_type u, v, w; };
        };

        // Constructors / Destructor

        MYL_NO_DISCARD constexpr vec() = default;
        MYL_NO_DISCARD constexpr vec(const vec& v) = default;
        MYL_NO_DISCARD constexpr vec(vec&& v) = default;

        MYL_NO_DISCARD constexpr explicit vec(const value_type& s)
            : data{ s, s, s } {}

        MYL_NO_DISCARD constexpr vec(const value_type& x, const value_type& y, const value_type& z)
            : data{ x, y, z } {}

        MYL_NO_DISCARD constexpr vec(value_type&& x, value_type&& y, value_type&& z)
            : data{ std::move(x), std::move(y), std::move(z) } {}

        MYL_NO_DISCARD constexpr vec(const vec<2, value_type>& xy, const value_type& z)
            : data{ xy.x, xy.y, z } {}

        MYL_NO_DISCARD constexpr vec(const value_type& x, const vec<2, value_type>& yz)
            : data{ x, yz.x, yz.y } {}

        MYL_NO_DISCARD constexpr explicit vec(const vec<4, value_type>& v)
            : data{ v.x, v.y, v.z } {}

        // Operators

        constexpr auto operator=(const vec&) -> vec& = default;
        constexpr auto operator=(vec&&) -> vec& = default;

        MYL_NO_DISCARD constexpr operator bool() const {
            return
                !(x == static_cast<value_type>(0) &&
                y == static_cast<value_type>(0) &&
                z == static_cast<value_type>(0));
        }

        MYL_NO_DISCARD constexpr auto operator[](usize i) noexcept -> value_type& {
            MYL_ASSERT(i < 3);
            return data[i];
        }

        MYL_NO_DISCARD constexpr auto operator[](usize i) const noexcept -> const value_type& {
            MYL_ASSERT(i < 3);
            return data[i];
        }

        MYL_NO_DISCARD constexpr auto operator-() const -> vec { return vec{ -x, -y, -z }; }

        // Scalar Operators

        MYL_NO_DISCARD constexpr auto operator+(const value_type& s) const -> vec { return vec{ x + s, y + s, z + s }; }
		MYL_NO_DISCARD constexpr auto operator-(const value_type& s) const -> vec { return vec{ x - s, y - s, z - s }; }
		MYL_NO_DISCARD constexpr auto operator*(const value_type& s) const -> vec { return vec{ x * s, y * s, z * s }; }
		MYL_NO_DISCARD constexpr auto operator/(const value_type& s) const -> vec { return vec{ x / s, y / s, z / s }; }
		MYL_NO_DISCARD constexpr auto operator%(const value_type& s) const -> vec { return vec{ x % s, y % s, z % s }; }

        constexpr auto operator+=(const value_type& s) -> vec& { x += s; y += s; z += s; return *this; }
		constexpr auto operator-=(const value_type& s) -> vec& { x -= s; y -= s; z -= s; return *this; }
		constexpr auto operator*=(const value_type& s) -> vec& { x *= s; y *= s; z *= s; return *this; }
		constexpr auto operator/=(const value_type& s) -> vec& { x /= s; y /= s; z /= s; return *this; }
		constexpr auto operator%=(const value_type& s) -> vec& { x %= s; y %= s; z %= s; return *this; }
        
        // vec2 Operators

        MYL_NO_DISCARD constexpr auto operator+(const vec<2, value_type>& r) const -> vec { return vec{ x + r.x, y + r.y, z }; }
		MYL_NO_DISCARD constexpr auto operator-(const vec<2, value_type>& r) const -> vec { return vec{ x - r.x, y - r.y, z }; }
		MYL_NO_DISCARD constexpr auto operator*(const vec<2, value_type>& r) const -> vec { return vec{ x * r.x, y * r.y, z }; }
		MYL_NO_DISCARD constexpr auto operator/(const vec<2, value_type>& r) const -> vec { return vec{ x / r.x, y / r.y, z }; }
		MYL_NO_DISCARD constexpr auto operator%(const vec<2, value_type>& r) const -> vec { return vec{ x % r.x, y % r.y, z }; }

		constexpr auto operator+=(const vec<2, value_type>& r) -> vec& { x += r.x; y += r.y; return *this; }
		constexpr auto operator-=(const vec<2, value_type>& r) -> vec& { x -= r.x; y -= r.y; return *this; }
		constexpr auto operator*=(const vec<2, value_type>& r) -> vec& { x *= r.x; y *= r.y; return *this; }
		constexpr auto operator/=(const vec<2, value_type>& r) -> vec& { x /= r.x; y /= r.y; return *this; }
		constexpr auto operator%=(const vec<2, value_type>& r) -> vec& { x %= r.x; y %= r.y; return *this; }

        // vec3 Operators

        MYL_NO_DISCARD constexpr auto operator+(const vec& r) const -> vec { return vec{ x + r.x, y + r.y, z + r.z }; }
		MYL_NO_DISCARD constexpr auto operator-(const vec& r) const -> vec { return vec{ x - r.x, y - r.y, z - r.z }; }
		MYL_NO_DISCARD constexpr auto operator*(const vec& r) const -> vec { return vec{ x * r.x, y * r.y, z * r.z }; }
		MYL_NO_DISCARD constexpr auto operator/(const vec& r) const -> vec { return vec{ x / r.x, y / r.y, z / r.z }; }
		MYL_NO_DISCARD constexpr auto operator%(const vec& r) const -> vec { return vec{ x % r.x, y % r.y, z % r.z }; }

		constexpr auto operator+=(const vec& r) -> vec& { x += r.x; y += r.y; z += r.z; return *this; }
		constexpr auto operator-=(const vec& r) -> vec& { x -= r.x; y -= r.y; z -= r.z; return *this; }
		constexpr auto operator*=(const vec& r) -> vec& { x *= r.x; y *= r.y; z *= r.z; return *this; }
		constexpr auto operator/=(const vec& r) -> vec& { x /= r.x; y /= r.y; z /= r.z; return *this; }
		constexpr auto operator%=(const vec& r) -> vec& { x %= r.x; y %= r.y; z %= r.z; return *this; }
    };

    template<typename T>
    MYL_NO_DISCARD constexpr auto operator==(const vec3<T>& l, const vec3<T>& r) -> bool {
        return l.x == r.x && l.y == r.y && l.z == r.z;
    }

    template<typename T>
	MYL_NO_DISCARD constexpr auto dot(const vec3<T>& a, const vec3<T>& b) -> T {
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

    template<typename T>
	MYL_NO_DISCARD constexpr auto cross(const vec3<T>& a, const vec3<T>& b) -> vec<3, T> {
		return vec3<T>(
			a.y * b.z - b.y * a.z,
			a.z * b.x - b.z * a.x,
			a.x * b.y - b.x * a.y);
	}
}

#ifdef MYL_EXTEND_FORMAT
#   include <format>

/// MYTODO: Vec3 formatting of components

namespace std {
    template<typename T>
    struct formatter<myl::vec3<T>> {
    private:
        enum : myl::u8 {
            none = 0,
            x = 1 << 0,
            y = 1 << 1,
            z = 1 << 2
        };

        myl::u8 m_flags = none;
        myl::u8 m_component_count = 0;
        myl::u8 m_component_order[3]{ 0, 1, 2 };
    public:
        template<typename FormatParseContext>
        constexpr auto parse(FormatParseContext& context) -> typename FormatParseContext::iterator {
            auto position = context.begin();
            for (; position != context.end() && *position != '}'; ++position)
                switch(*position) {
                    case 'x':
                        m_component_order[m_component_count] = 0;
                        m_flags |= x;
                        ++m_component_count;
                        break;
                    case 'y':
                        m_component_order[m_component_count] = 1;
                        m_flags |= y;
                        ++m_component_count;
                        break;
                    case 'z':
                        m_component_order[m_component_count] = 2;
                        m_flags |= z;
                        ++m_component_count;
                        break;
                    default: break;
                }

            return position;
        }

        template<typename FormatContext>
        constexpr auto format(const myl::vec3<T>& vec, FormatContext& context) const -> typename FormatContext::iterator {
            switch (m_component_count) {
                case 1:  return format_to(context.out(), "{}", vec[m_component_order[0]]);
                case 2:  return format_to(context.out(), "[{}, {}]", vec[m_component_order[0]], vec[m_component_order[1]]);
                default: return format_to(context.out(), "[{}, {}, {}]", vec[m_component_order[0]], vec[m_component_order[1]], vec[m_component_order[2]]);
            }
        }
    };
}
#endif
