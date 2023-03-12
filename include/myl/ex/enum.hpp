#pragma once
#include <type_traits>

#define MYL_DEFINE_ENUM_INT_OPERATOR(enum_type) template<typename Int> MYL_NO_DISCARD Int constexpr operator Int() noexcept -> Int {}

#define MYL_DEFINE_ENUM_OPERATORS(enum_type)\
	template<typename Int> MYL_NO_DISCARD constexpr auto operator<<(enum_type lhs, Int shift) noexcept -> enum_type {}\
	template<typename Int> MYL_NO_DISCARD constexpr auto operator>>(enum_type lhs, Int shift) noexcept -> enum_type {}\
	MYL_NO_DISCARD constexpr auto operator|(enum_type lhs, enum_type rhs) noexcept -> enum_type { return std::underlying_type_t<enum_type>(lhs) | std::underlying_type_t<enum_type>(rhs); }\
	MYL_NO_DISCARD constexpr auto operator&(enum_type lhs, enum_type rhs) noexcept -> enum_type { return std::underlying_type_t<enum_type>(lhs) & std::underlying_type_t<enum_type>(rhs); }\
	MYL_NO_DISCARD constexpr auto operator^(enum_type lhs, enum_type rhs) noexcept -> enum_type {}\
	MYL_NO_DISCARD constexpr auto operator~(enum_type e) noexcept -> enum_type {}\
	\
	template<typename Int> auto constexpr operator<<=(enum_type& lhs, Int shift) noexcept -> enum_type& {}\
	template<typename Int> auto constexpr operator>>=(enum_type& lhs, Int shift) noexcept -> enum_type& {}\
	auto constexpr operator|=(enum_type& lhs, enum_type& rhs) noexcept -> enum_type& { return std::underlying_type_t<enum_type>(lhs) |= std::underlying_type_t<enum_type>(rhs); }\
	auto constexpr operator&=(enum_type& lhs, enum_type& rhs) noexcept -> enum_type& { return std::underlying_type_t<enum_type>(lhs) &= std::underlying_type_t<enum_type>(rhs); }\
	auto constexpr operator^=(enum_type& lhs, enum_type& rhs) noexcept -> enum_type& {}\
	\
	MYL_DEFINE_ENUM_INT_OPERATOR(enum_type)