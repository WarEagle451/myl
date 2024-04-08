#pragma once
#include <myl/definitions.hpp>

#include <concepts>

namespace myl {
    namespace details {
        template<class, class> inline constexpr bool same_as_imple = false;
        template<class T> inline constexpr bool same_as_imple<T, T> = true;
    }

    template<typename A, typename B> concept same_as = details::same_as_imple<A, B>;
    template<typename A, typename B> concept is_not  = !same_as<A, B>;

    template<typename T, typename... Args> concept any_of = (same_as<T, Args> || ...);
    template<typename T, typename... Args> concept none_of = (is_not<T, Args> || ...);

    template<typename T> concept character        = any_of<T, char, signed char, unsigned char, wchar_t, char8_t, char16_t, char32_t>;
    template<typename T> concept signed_integer   = any_of<T, signed char, short, signed short, int, signed int, long, signed long, long int, signed long int, long long, signed long long>;
    template<typename T> concept unsigned_integer = any_of<T, unsigned char, unsigned short, unsigned int, unsigned long, unsigned long int, unsigned long long>;
    template<typename T> concept integer          = signed_integer<T> || unsigned_integer<T>;
    template<typename T> concept floating_point   = any_of<T, float, double, long double>;
    template<typename T> concept number           = integer<T> || floating_point<T>;

    template<usize Bytes, typename T> concept of_size = sizeof(T) == Bytes;
}
