#pragma once
#include <myl/definitions.hpp>

#include <concepts>
#include <limits>
#include <numeric>

/// MYTODO: type.hpp
/// - common concept, common type

namespace myl {
    namespace details {
        template<class, class> inline constexpr bool same_as_imple = false;
        template<class T> inline constexpr bool same_as_imple<T, T> = true;

        template<usize Count>
        consteval auto bits_size_to_uint_imple() {
            if constexpr (Count <= std::numeric_limits<u8>::max())
                return u8{};
            else if constexpr (Count <= std::numeric_limits<u16>::max())
                return u16{};
            else if constexpr (Count <= std::numeric_limits<u32>::max())
                return u32{};
            else if constexpr (Count <= std::numeric_limits<u64>::max())
                return u64{};
            else
                static_assert(false, "Unexpected bit size, must be 64 or less");
        }
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

    template<typename T, usize Bytes> concept of_size = sizeof(T) == Bytes;

    template<usize Bits> using bits_size_to_uint = decltype(details::bits_size_to_uint_imple<Bits>());
    template<usize Bytes> using byte_size_to_uint = decltype(details::bits_size_to_uint_imple<Bytes * CHAR_BIT>());
}
