#pragma once
#include <myl/defines.hpp>

#include <format>
#include <source_location>
#include <string>

namespace myl {
	class exception {
	protected:
		std::string m_message = "";
	public:
		constexpr exception() noexcept
			: m_message("An exception occured!") {}

		constexpr exception(std::string_view a_message)
			: m_message(a_message.data()) {}

		exception(std::string_view a_prefix, std::string_view a_message)
			: m_message{ std::format("{}{}", a_prefix, a_message) } {}

		exception(const std::source_location& a_src, std::string_view a_message)
			: m_message{ std::format("'{}::{}' @ [{}, {}] - {}", a_src.file_name(), a_src.function_name(), a_src.line(), a_src.column(), a_message) } {}

		constexpr auto message() const -> const char* {
			return m_message.c_str();
		}
	};
}