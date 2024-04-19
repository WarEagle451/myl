#pragma once
#include <myl/intrinsic.hpp>
#include <myl/type.hpp>

#include <bit>
#include <type_traits>

namespace myl {
    namespace details {
        MYL_NO_DISCARD constexpr auto byteswap16_impl(u16 v) noexcept -> u16 {
#ifdef MYL_INTRINSIC_BYTESWAP16
            if constexpr (!std::is_constant_evaluated())
                return MYL_INTRINSIC_BYTESWAP16(v);
            else
#endif
                return (v << 8) | (v >> 8);
        }

        MYL_NO_DISCARD constexpr auto byteswap32_impl(u32 v) noexcept -> u32 {
#ifdef MYL_INTRINSIC_BYTESWAP32
            if constexpr (!std::is_constant_evaluated())
                return MYL_INTRINSIC_BYTESWAP32(v);
            else
#endif
                return
                    (v << 24) | ((v << 8) & 0x00FF'0000) |
                    ((v >> 8) & 0x0000'FF00) | (v >> 24);
        }

        MYL_NO_DISCARD constexpr auto byteswap64_impl(u64 v) noexcept -> u64 {
#ifdef MYL_INTRINSIC_BYTESWAP64
            if constexpr (!std::is_constant_evaluated())
                return MYL_INTRINSIC_BYTESWAP64(v);
            else
#endif
                return
                    (v << 56) | ((v << 40) & 0x00FF'0000'0000'0000) |
                    ((v << 24) &  0x0000'FF00'0000'0000) | ((v << 8) & 0x0000'00FF'0000'0000) |
                    ((v >> 8) & 0x0000'0000'FF00'0000) | ((v >> 24) & 0x0000'0000'00FF'0000) |
                    ((v >> 40) & 0x0000'0000'0000'FF00) | (v >> 56);
        }
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto byteswap(T v) noexcept -> T {
        if constexpr (sizeof(T) == 1)
            return v;
        else if constexpr (sizeof(T) == 2)
            return std::bit_cast<T, u16>(details::byteswap16_impl(std::bit_cast<u16, T>(v)));
        else if constexpr (sizeof(T) == 4)
            return std::bit_cast<T, u32>(details::byteswap32_impl(std::bit_cast<u32, T>(v)));
        else if constexpr (sizeof(T) == 8)
            return std::bit_cast<T, u64>(details::byteswap64_impl(std::bit_cast<u64, T>(v)));
        else
            static_assert(false, "Unexpected byte size, must be 8 or less");
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto host_to_network(T v) noexcept -> byte_count_to_uint<sizeof(T)> {
        using to = byte_count_to_uint<sizeof(T)>;
        if constexpr (std::endian::native == std::endian::big)
            if constexpr (same_as<to, T>)
                return v;
            else
                return std::bit_cast<to, T>(v);
        else
            return byteswap(v);
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto network_to_host(byte_count_to_uint<sizeof(T)> v) noexcept -> T {
        using from = byte_count_to_uint<sizeof(T)>;
        if constexpr (std::endian::native == std::endian::big)
            if constexpr (same_as<T, from>)
                return v;
            else
                return std::bit_cast<T, from>(v);
        else
            return byteswap(v);
    }
}
