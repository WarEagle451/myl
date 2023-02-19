#include <myl/endian.hpp>
#include <myl/platform.hpp>

#include <bit>

namespace myl {
	constexpr auto system_big_endian() -> const bool {
		return std::endian::native == std::endian::big;
	}

	constexpr auto system_little_endian() -> const bool {
		return std::endian::native == std::endian::little;
	}
}

/// MYTodo: Just write hton and ntoh exotic platforms will throw a preprocessor error

#ifdef MYL_PLATFORM_WINDOWS
#	include <WinSock2.h>

inline auto htonfloat(myl::f32 v) -> myl::u32 { return htonf(v); } /// MYTemp:
inline auto ntohfloat(myl::u32 v) -> myl::f32 { return ntohf(v); }

namespace myl {
	auto hton(u16 value) -> u16 { return htons(value); }
	auto hton(u32 value) -> u32 { return htonl(value); }
	auto hton(u64 value) -> u64 { return htonll(value); }
	auto htonf(f32 value) -> u32 { return htonfloat(value); }
	auto htonf(f64 value) -> u64 { return htond(value); }

	auto ntoh(u16 value) -> u16 { return ntohs(value); }
	auto ntoh(u32 value) -> u32 { return ntohl(value); }
	auto ntoh(u64 value) -> u64 { return ntohll(value); }
	auto ntohf(u32 value) -> f32 { return ntohfloat(value); }
	auto ntohf(u64 value) -> f64 { return ntohd(value); }
}
#else
#	error Unknown platform
#endif