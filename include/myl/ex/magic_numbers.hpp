#pragma once
#include <myl/defines.hpp>
#ifdef MYL_EXPERIMENTAL
/// chars
/// double float

namespace myl::magic_numbers {
	enum : i64 {
		i8_min  =                       -128,
		i16_min =                    -32'768,
		i32_min =             -2'147'483'648,
		i64_min = -9'223'372'036'854'775'808,

		i8_max  =                       127,
		i16_max =                    32'767,
		i32_max =             2'147'483'647,
		i64_max = 9'223'372'036'854'775'807,
	};

	enum : u64 {
		u8_min =  0,
		u16_min = 0,
		u32_min = 0,
		u64_min = 0,

		u8_max  =                        255,
		u16_max =                     65'535,
		u32_max =              4'294'967'295,
		u64_max = 18'446'744'073'709'551'615,
	};
}
#endif