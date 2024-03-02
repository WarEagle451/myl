#pragma once
#include <myl/definitions.hpp>

#include <chrono>
#include <concepts>

namespace myl {
    //@brief Constraints to std::duration specializations or equivalent 
    template<typename Duration>
    concept is_duration = requires(Duration a_duration) {
        typename Duration::period;
        a_duration.count();
    };

    template<typename Clock>
    class timer {
    public:
        using clock = Clock;
        using time_point = std::chrono::time_point<clock>;
    private:
        time_point m_start;
    public:
        MYL_NO_DISCARD timer()
            : m_start{ clock::now() } {}
    
        ~timer() = default;
    
        auto reset() -> void { m_start = clock::now(); }
    
        template<is_duration Duration = std::chrono::nanoseconds, typename T = i32>
        MYL_NO_DISCARD auto elapsed() const -> T {
            auto time = clock::now() - m_start;
            return std::chrono::duration_cast<std::chrono::duration<T, Duration::period>>(time).count();
        }
    };
    
    using high_resolution_timer = timer<std::chrono::high_resolution_clock>;

    template<typename Clock>
    class stopwatch {
    public:
        using clock            = Clock;
        using time_point    = typename clock::time_point;
    private:
        time_point m_total_time;
        time_point m_start_time;
        time_point m_pause_time;
        bool m_paused;
    public:
        MYL_NO_DISCARD stopwatch(bool a_start = true)
            : m_total_time{}
            , m_start_time{ a_start ? clock::now() : time_point{} }
            , m_pause_time{ a_start ? time_point{} : clock::now() }
            , m_paused{ !a_start } {}

        ~stopwatch() = default;

        MYL_NO_DISCARD constexpr auto paused() const noexcept -> bool { return m_paused; }

        auto pause() -> void { 
            if (m_paused)
                return;

            m_pause_time = clock::now();
            m_paused = true;

        }

        auto resume() -> void {
            if (!m_paused)
                return;

            auto now = clock::now();
            m_total_time += m_pause_time - m_start_time;
            m_start_time = now;
            m_pause_time = time_point{};
            m_paused = false;
        }

        auto reset() -> void {
            time_point now = clock::now();
            m_total_time = time_point{};
            m_start_time = m_paused ? time_point{} : now;
            m_pause_time = m_paused ? now : time_point{};
        }

        template<is_duration Duration = std::chrono::nanoseconds, typename T = i32>
        MYL_NO_DISCARD auto split() -> T {
            auto now_or_stopped = m_paused ? m_pause_time : clock::now();
            auto split_time = now_or_stopped - m_start_time;

            m_total_time += split_time;
            m_start_time = now_or_stopped;

            return std::chrono::duration_cast<std::chrono::duration<T, typename Duration::period>>(split_time).count();
        }

        template<is_duration Duration = std::chrono::nanoseconds, typename T = i32>
        MYL_NO_DISCARD auto elapsed() const -> T {
            /// MYHack: - time_point{} probably changes the type, but to what?
            auto time = (m_paused ? m_total_time : clock::now() - m_start_time + m_total_time) - time_point{};
            return std::chrono::duration_cast<std::chrono::duration<T, typename Duration::period>>(time).count();
        }
    };

    using high_resolution_stopwatch = stopwatch<std::chrono::high_resolution_clock>;
}
