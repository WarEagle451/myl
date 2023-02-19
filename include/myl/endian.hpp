#pragma once
#include <myl/defines.hpp>

namespace myl {
	MYL_API MYL_NO_DISCARD constexpr auto system_big_endian() -> const bool;
	MYL_API MYL_NO_DISCARD constexpr auto system_little_endian() -> const bool;

	MYL_API MYL_NO_DISCARD auto hton(u16) -> u16;
	MYL_API MYL_NO_DISCARD auto hton(u32) -> u32;
	MYL_API MYL_NO_DISCARD auto hton(u64) -> u64;
	MYL_API MYL_NO_DISCARD auto htonf(f32) -> u32;
	MYL_API MYL_NO_DISCARD auto htonf(f64) -> u64;
									
	MYL_API MYL_NO_DISCARD auto ntoh(u16) -> u16;
	MYL_API MYL_NO_DISCARD auto ntoh(u32) -> u32;
	MYL_API MYL_NO_DISCARD auto ntoh(u64) -> u64;
	MYL_API MYL_NO_DISCARD auto ntohf(u32) -> f32;
	MYL_API MYL_NO_DISCARD auto ntohf(u64) -> f64;
}