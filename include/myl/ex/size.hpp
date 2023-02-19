#pragma once
#include <myl/defines.hpp>
#ifdef MYL_EXPERIMENTAL

namespace myl {
	enum class size : u64 {
		bit			= 1,
		kilo_bit	= 1000,
		mega_bit	= 1'000'000,
		giga_bit	= 1'000'000'000,
		tera_bit	= 1'000'000'000'000,
		peta_bit	= 1'000'000'000'000'000,
		exa_bit		= 1'000'000'000'000'000'000,
		kili_bit	= 1024,
		megi_bit	= 1'048'576,
		gigi_bit	= 1'073'741'824,
		tebi_bit	= 1'099'511'627'776,
		pebi_bit	= 1'125'899'906'842'624,
		exbi_bit	= 1'152'921'504'606'846'976,

		byte		= 8,
		kilo_byte	= 8000,
		mega_byte	= 8'000'000,
		giga_byte	= 8'000'000'000,
		tera_byte	= 8'000'000'000'000,
		peta_byte	= 8'000'000'000'000'000,
		exa_byte	= 8'000'000'000'000'000'000,
		kili_byte	= 8192,
		megi_byte	= 8'388'608,
		gigi_byte	= 8'589'934'592,
		tebi_byte	= 8'796'093'022'208,
		pebi_byte	= 9'007'199'254'740'992,
		exbi_byte	= 9'223'372'036'854'775'808
	};

	MYL_API MYL_NO_DISCARD constexpr auto size_suffix(size size) -> const char* {
		switch (size) {
			using enum size;
			case bit:		return "bit";
			case kilo_bit:	return "K";
			case mega_bit:	return "M";
			case giga_bit:	return "G";
			case tera_bit:	return "T";
			case peta_bit:	return "P";
			case exa_bit:	return "E";
			case kili_bit:	return "Ki";
			case megi_bit:	return "Mi";
			case gigi_bit:	return "Gi";
			case tebi_bit:	return "Ti";
			case pebi_bit:	return "Pi";
			case exbi_bit:	return "Ei";
			case byte:		return "B";
			case kilo_byte:	return "KB";
			case mega_byte:	return "MB";
			case giga_byte:	return "GB";
			case tera_byte:	return "TB";
			case peta_byte:	return "PB";
			case exa_byte:	return "EB";
			case kili_byte:	return "KiB";
			case megi_byte:	return "MiB";
			case gigi_byte:	return "GiB";
			case tebi_byte:	return "TiB";
			case pebi_byte:	return "PiB";
			case exbi_byte:	return "EiB";
		}
	}
}
#endif