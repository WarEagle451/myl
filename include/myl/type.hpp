#pragma once
#include <myl/definitions.hpp>

#include <concepts>
#include <limits>
#include <numeric>

/// MYTODO: type.hpp
/// - common concept, common type

namespace myl {
    namespace impl {
        template<class, class> inline constexpr bool _same_as = false;
        template<class T> inline constexpr bool _same_as<T, T> = true;

        template<usize Count>
        consteval auto _bit_count_to_uint() {
            if constexpr (Count <= CHAR_BIT)
                return u8{};
            else if constexpr (Count <= CHAR_BIT * 2)
                return u16{};
            else if constexpr (Count <= CHAR_BIT * 4)
                return u32{};
            else if constexpr (Count <= CHAR_BIT * 8)
                return u64{};
            else
                static_assert(false, "Unexpected bit size, must be 64 or less");
        }
    }

    template<typename A, typename B> concept same_as = impl::_same_as<A, B>;
    template<typename A, typename B> concept is_not = !same_as<A, B>;

    template<typename T, typename... Args> concept any_of = (same_as<T, Args> || ...);
    template<typename T, typename... Args> concept none_of = !(same_as<T, Args> || ...);

    template<typename T> concept character        = any_of<std::remove_cv_t<T>, char, signed char, unsigned char, wchar_t, char8_t, char16_t, char32_t>;
    template<typename T> concept integer          = std::numeric_limits<T>::is_specialized && std::numeric_limits<T>::is_integer;
    template<typename T> concept signed_integer   = integer<T> && std::numeric_limits<T>::is_signed;
    template<typename T> concept unsigned_integer = integer<T> && !std::numeric_limits<T>::is_signed;
    template<typename T> concept floating_point   = std::numeric_limits<T>::min() != std::numeric_limits<T>::lowest();
    template<typename T> concept number           = integer<T> || floating_point<T>;

    template<typename T, usize Bytes> concept of_size = sizeof(T) == Bytes;

    template<usize Bits> using bit_count_to_uint = decltype(impl::_bit_count_to_uint<Bits>());
    template<usize Bytes> using byte_count_to_uint = decltype(impl::_bit_count_to_uint<Bytes * CHAR_BIT>());
}
