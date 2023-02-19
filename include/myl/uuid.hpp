#pragma once
#include <myl/defines.hpp>

#include <string>

// RFC 4122 Complient UUIDs: https://datatracker.ietf.org/doc/html/rfc4122

namespace myl {
	enum class uuid_version {
		unknown,
		time	= 0x10,
		dce		= 0x20, // Creation not currently
		md5		= 0x30, // Creation not currently
		random	= 0x40,
		sha1	= 0x50 // Creation not currently
	};

	enum class uuid_variant {
		unknown,
		ncs,
		rfc_4122,
		microsoft,
		reserved
	};

	class MYL_API uuid {
		u8 m_bytes[16]{ 0 }; // 128 bits
	public:
		constexpr uuid() noexcept = default;
		uuid(uuid_version);
		constexpr uuid(u8(&)[16]);
		constexpr uuid(std::string_view);

		MYL_NO_DISCARD constexpr auto data() -> u8*;
		MYL_NO_DISCARD constexpr auto data() const -> const u8*;

		MYL_NO_DISCARD constexpr auto version() const -> uuid_version;
		MYL_NO_DISCARD constexpr auto variant() const -> uuid_variant;

		MYL_NO_DISCARD auto nil() const -> bool;

		MYL_NO_DISCARD constexpr auto string(bool a_brackets = false, bool a_dashed = true) const -> std::string;

		MYL_NO_DISCARD auto operator==(const uuid& rhs) const -> bool;
		MYL_NO_DISCARD auto operator<(const uuid& rhs) const -> bool;
		MYL_NO_DISCARD auto operator>(const uuid& rhs) const -> bool;
		MYL_NO_DISCARD auto operator<=(const uuid& rhs) const -> bool;
		MYL_NO_DISCARD auto operator>=(const uuid& rhs) const -> bool;
	};
}

#ifdef MYL_TYPE_SIZE_CHECK
static_assert(sizeof(myl::uuid) == 16, "Expected myl::uuid to be 16 bytes");
#endif