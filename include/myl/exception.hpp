#pragma once
#include <myl/defines.hpp>

#include <source_location>
#include <string>

namespace myl {
	class exception {
	protected:
		std::string m_message = "";
	public:
		MYL_API MYL_NO_DISCARD constexpr exception() noexcept;
		MYL_API MYL_NO_DISCARD constexpr explicit exception(std::string_view);
		MYL_API MYL_NO_DISCARD explicit exception(std::string_view a_prefix, std::string_view);
		MYL_API MYL_NO_DISCARD explicit exception(const std::source_location&, std::string_view = "");

		MYL_API MYL_NO_DISCARD constexpr auto message() const -> const char*;
	};
}