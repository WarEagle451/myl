#pragma once
#include <myl/defines.hpp>

#include <bit> /// Remove? for bit cast
#include <type_traits> /// For std::is_constant_evaluated() because if consteval {} else {} is a C++23 thing

#ifdef MYL_COMPILER_MSVC
#	include <intrin.h>
#endif

/// MYTodo: Change to bit,hpp??

namespace myl {
	template<typename T, usize Bytes>
	concept byte_size = sizeof(T) == Bytes;

	template<byte_size<1> T>
	MYL_NO_DISCARD constexpr auto byteswap(T v) -> T {
		return v;
	}

	template<byte_size<2> T>
	MYL_NO_DISCARD constexpr auto byteswap(T v) -> T {
#ifdef MYL_COMPILER_UNKNOWN
		return (v << 8) | (v >> 8);
#else
		return std::is_constant_evaluated() ?
			(v << 8) | (v >> 8) :
#	ifdef MYL_COMPILER_MSVC
		std::bit_cast<T, unsigned short>(_byteswap_ushort(std::bit_cast<unsigned short, T>(v)));
#	else
#		error "2 byte byteswap not implemented for known compiler!"
#	endif
#endif
	}
	
	template<byte_size<4> T>
	MYL_NO_DISCARD constexpr auto byteswap(T v) -> T {
#ifdef MYL_COMPILER_UNKNOWN
		return (v << 24) | ((v << 8) & 0x00FF'0000) | ((v >> 8) & 0x0000'FF00) | (v >> 24);
#else
		return std::is_constant_evaluated() ?
			(v << 24) | ((v << 8) & 0x00FF'0000) | ((v >> 8) & 0x0000'FF00) | (v >> 24) :
#	ifdef MYL_COMPILER_MSVC
			std::bit_cast<T, unsigned long>(_byteswap_ulong(std::bit_cast<unsigned long, T>(v)));
#	else
#		error "4 byte byteswap not implemented for known compiler!"
#	endif
#endif
	}

	template<byte_size<8> T>
	MYL_NO_DISCARD constexpr auto byteswap(T v) -> T {
#ifdef MYL_COMPILER_UNKNOWN
		return
			(v << 56) | ((v << 40) & 0x00FF'0000'0000'0000) | ((v << 24) & 0x0000'FF00'0000'0000)
			| ((v << 8) & 0x0000'00FF'0000'0000) | ((v >> 8) & 0x0000'0000'FF00'0000)
			| ((v >> 24) & 0x0000'0000'00FF'0000) | ((v >> 40) & 0x0000'0000'0000'FF00) | (v >> 56);
#else
		return std::is_constant_evaluated() ?
			(v << 56) | ((v << 40) & 0x00FF'0000'0000'0000) | ((v << 24) & 0x0000'FF00'0000'0000)
			| ((v << 8) & 0x0000'00FF'0000'0000) | ((v >> 8) & 0x0000'0000'FF00'0000)
			| ((v >> 24) & 0x0000'0000'00FF'0000) | ((v >> 40) & 0x0000'0000'0000'FF00) | (v >> 56) :
#	ifdef MYL_COMPILER_MSVC
			std::bit_cast<T, unsigned long long>(_byteswap_uint64(std::bit_cast<unsigned long long, T>(v)));
#	else
#		error "8 byte byteswap not implemented for known compiler!"
#	endif
#endif
	}

	MYL_NO_DISCARD constexpr auto hton(u16 v) -> u16 { return std::endian::native == std::endian::big ? v : byteswap(v); }
	MYL_NO_DISCARD constexpr auto hton(u32 v) -> u32 { return std::endian::native == std::endian::big ? v : byteswap(v); }
	MYL_NO_DISCARD constexpr auto hton(u64 v) -> u64 { return std::endian::native == std::endian::big ? v : byteswap(v); }

	MYL_NO_DISCARD constexpr auto htonf(f32 v) -> u32 { return std::endian::native == std::endian::big ? std::bit_cast<u32, f32>(v) : std::byteswap(std::bit_cast<u32, f32>(v)); }
	MYL_NO_DISCARD constexpr auto htonf(f64 v) -> u64 { return std::endian::native == std::endian::big ? std::bit_cast<u64, f64>(v) : std::byteswap(std::bit_cast<u64, f64>(v)); }

	MYL_NO_DISCARD constexpr auto ntoh(u16 v) -> u16 { return std::endian::native == std::endian::big ? v : byteswap(v); }
	MYL_NO_DISCARD constexpr auto ntoh(u32 v) -> u32 { return std::endian::native == std::endian::big ? v : byteswap(v); }
	MYL_NO_DISCARD constexpr auto ntoh(u64 v) -> u64 { return std::endian::native == std::endian::big ? v : byteswap(v); }

	MYL_API MYL_NO_DISCARD constexpr auto ntohf(u32 v) -> f32 { return std::endian::native == std::endian::big ? std::bit_cast<f32, u32>(v) : std::bit_cast<f32, u32>(std::byteswap(v)); }
	MYL_API MYL_NO_DISCARD constexpr auto ntohf(u64 v) -> f64 { return std::endian::native == std::endian::big ? std::bit_cast<f64, u64>(v) : std::bit_cast<f64, u64>(std::byteswap(v)); }
}