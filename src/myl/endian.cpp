#include <myl/endian.hpp>

#include <bit>

namespace myl {
	constexpr auto system_big_endian() -> const bool {
		return std::endian::native == std::endian::big;
	}

	constexpr auto system_little_endian() -> const bool {
		return std::endian::native == std::endian::little;
	}

	constexpr auto hton(u16 v) -> u16 { return std::byteswap(v); }
	constexpr auto hton(u32 v) -> u32 { return std::byteswap(v); }
	constexpr auto hton(u64 v) -> u64 { return std::byteswap(v); }

	constexpr auto htonf(f32 v) -> u32 { return std::byteswap(std::bit_cast<u32, f32>(v)); }
	constexpr auto htonf(f64 v) -> u64 { return std::byteswap(std::bit_cast<u64, f64>(v)); }

	constexpr auto ntoh(u16 v) -> u16 { return std::byteswap(v); }
	constexpr auto ntoh(u32 v) -> u32 { return std::byteswap(v); }
	constexpr auto ntoh(u64 v) -> u64 { return std::byteswap(v); }

	constexpr auto ntohf(u32 v) -> f32 { return std::bit_cast<f32, u32>(std::byteswap(v)); }
	constexpr auto ntohf(u64 v) -> f64 { return std::bit_cast<f64, u64>(std::byteswap(v)); }
}