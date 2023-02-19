#include <myl/exception.hpp>

#include <format>

namespace myl {
	constexpr exception::exception() noexcept
		: m_message("An exception occured!") {}

	constexpr exception::exception(std::string_view a_message)
		: m_message(a_message.data()) {}

	exception::exception(std::string_view a_prefix, std::string_view a_message)
		: m_message{ std::format("{}{}", a_prefix, a_message) } {}

	exception::exception(const std::source_location& a_src, std::string_view a_message)
		: m_message{ std::format("'{}::{}' @ [{}, {}] - {}", a_src.file_name(), a_src.function_name(), a_src.line(), a_src.column(), a_message) } {}

	constexpr auto exception::message() const -> const char* {
		return m_message.c_str();
	}
}