#pragma once
#include <myl/math/vec_common.hpp>

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
            value_type data[2]{ 0 };
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
                !(x == static_cast<value_type>(0) &&
                y == static_cast<value_type>(0));
        }

        MYL_NO_DISCARD constexpr auto operator[](usize i) -> value_type& { return data[i]; }
        MYL_NO_DISCARD constexpr auto operator[](usize i) const -> const value_type& { return data[i]; }

        MYL_NO_DISCARD constexpr auto operator-() const -> vec { return vec{ -x, -y }; }

        // Scalar Operators

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

    template<typename T>
    MYL_NO_DISCARD constexpr auto operator==(const vec2<T>& l, const vec2<T>& r) -> bool {
        return l.x == r.x && l.y == r.y;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto dot(const vec2<T>& a, const vec2<T>& b) -> T {
        return (a.x * b.x) + (a.y * b.y);
    }
}

#ifdef MTL_EXTEND_FORMAT
#   include <format>

/// MYTODO: Vec2 formatting of components
/// https://en.cppreference.com/w/cpp/utility/format/spec
/// - There has to be a way to extend formatter<T> to this formatter

namespace std {
    template<typename T>
    struct formatter<myl::vec2<T>> {
    private:
        enum : myl::u8 {
            none = 0,
            x = 1 << 0,
            y = 1 << 1
        };

        myl::u8 m_flags = none;
        myl::u8 m_component_count = 0;
        myl::u8 m_component_order[2]{ 0, 1 };
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
                    default: break;
                }

            return position;
        }

        template<typename FormatContext>
        constexpr auto format(const myl::vec2<T>& vec, FormatContext& context) const -> typename FormatContext::iterator {
            return m_component_count == 1 ?
                format_to(context.out(), "{}", vec[m_component_order[0]]) :
                format_to(context.out(), "[{}, {}]", vec[m_component_order[0]], vec[m_component_order[1]]);
        }
    };
}
#endif
