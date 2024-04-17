#pragma once
#include <myl/definitions.hpp>

#include <string>
#include <string_view>

namespace myl {
    enum class uuid_version {
        unknown,
        time   = 0x10,
        dce    = 0x20,
        md5    = 0x30,
        random = 0x40,
        sha1   = 0x50,
    };

    enum class uuid_variant {
        unknown,
        ncs,
        rfc_4122,
        microsoft,
        reserved
    };

    class uuid {
        u8 m_bytes[16]{0}; // 128 bits
    public:
        // Constructors, Destructor, Assignment

        //MYL_NO_DISCARD constexpr uuid() noexcept = default;

        //MYL_NO_DISCARD constexpr uuid(uuid_version version);

        //MYL_NO_DISCARD constexpr uuid(std::string_view str);

        // Utilities

        //MYL_NO_DISCARD constexpr auto data() noexcept -> u8*;

        //MYL_NO_DISCARD constexpr auto data() const noexcept -> const u8*;

        //MYL_NO_DISCARD constexpr auto version() const noexcept -> uuid_version;

        //MYL_NO_DISCARD constexpr auto variant() const noexcept -> uuid_variant;

        //MYL_NO_DISCARD constexpr auto is_nil() const noexcept -> bool;

        //MYL_NO_DISCARD constexpr auto string(bool brackets = false, bool dashed = true) const -> std::string;

        // Comparision

        //MYL_NO_DISCARD constexpr auto operator<=>(const uuid& r) noexcept -> bool;
    };
}
