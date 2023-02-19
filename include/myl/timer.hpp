#pragma once
#include <myl/defines.hpp>

#include <chrono>
#include <concepts>

namespace myl {
	//@brief Constraints to std::duration specializations or equivalent 
	template<typename Unit>
	concept time_unit = requires(Unit a_unit) {
		typename Unit::period;
		a_unit.count();
	};

	template<typename Clock>
	class timer {
	public:
		using clock = Clock;
	private:
		std::chrono::time_point<clock> m_start;
	public:
		timer()
			: m_start{ clock::now() } {}

		auto reset() -> void { m_start = clock::now(); }

		template<time_unit TimeUnit = std::chrono::nanoseconds>
		MYL_NO_DISCARD auto elapsed() const -> TimeUnit {
			auto time = clock::now() - m_start;
			return std::chrono::duration_cast<TimeUnit>(time);
		}

		template<time_unit TimeUnit = std::chrono::seconds, typename FloatingPoint = f32>
		MYL_NO_DISCARD auto elapsed_pretty() const -> FloatingPoint {
			auto time = clock::now() - m_start;
			return std::chrono::duration<FloatingPoint, TimeUnit::period>(time).count();
		}
	};

	using high_resolution_timer = timer<std::chrono::high_resolution_clock>;
}