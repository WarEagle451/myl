#pragma once
#include <myl_wip/log/sink_base.hpp>

#include <format>
#include <utility>
#include <vector>

namespace myl::log {
    using sink_pool = std::vector<sink_ptr>;

    class logger {
        sink_pool m_sinks;
        std::string m_name;
        level m_level = default_level::trace;
    public:
        // Constructors, Destructor, Assignment

        logger() = delete;

        MYL_NO_DISCARD logger(std::string_view name)
            : m_name(name) {}

        template<typename It>
        MYL_NO_DISCARD logger(std::string_view name, It begin, It last)
            : m_sinks(begin, last)
            , m_name(name) {}

        ~logger() = default;

        // Utilities

        MYL_NO_DISCARD constexpr auto sinks() const noexcept -> const sink_pool& {
            return m_sinks;
        }

        template<typename... Args>
        auto log(level lvl, std::string_view msg, Args&&... args) -> void {
            if (lvl < m_level)
                return;

            payload pl{
                .level = lvl,
                .message = std::format(msg, std::forward<Args>(args)...)
            };

            for (auto& s : m_sinks)
                s->submit(pl);
        }

        template<typename T>
        auto log(level lvl, const T& value) -> void {
            log(lvl, "{}", value);
        }

        // Modifiers

        constexpr auto set_level(level lvl) noexcept -> void {
            m_level = lvl;
        }

        constexpr auto add(const sink_ptr& sink) -> void {
            m_sinks.emplace_back(sink);
        }
    };
}
