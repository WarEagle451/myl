#pragma once
#include <myl/definitions.hpp>

#include <memory>
#include <string>
#include <string_view>

namespace myl::log {
    namespace default_level {
        enum type : myl::u32 {
            trace = 0,
            debug = 1,
            info  = 2,
            warn  = 3,
            error = 4,
            fatal = 5,
            none
        };
    } using level = default_level::type;

    struct payload {
        level level;
        std::string message;
    };

    class sink_base {
        std::string m_pattern;
    public:
        MYL_NO_DISCARD constexpr sink_base(std::string_view pattern)
            : m_pattern(pattern) {}

        constexpr ~sink_base() = default;

        constexpr auto set_pattern(std::string_view pattern) -> void {
            m_pattern = pattern;
        }

        virtual auto submit(const payload& payload) -> void = 0;
    };

    using sink_ptr = std::shared_ptr<sink_base>;
}
