#pragma once
#include <myl/defines.hpp> /// For #ifdef MYL_EXPERIMENTAL
#ifdef MYL_EXPERIMENTAL
#include <type_traits>

#define MYL_DEFINE_ENUM_OPERATORS(Enum)\
	auto operator|(Enum lhs, Enum rhs) -> Enum { return std::underlying_type_t<Enum>(lhs) | std::underlying_type_t<Enum>(rhs); }\
	auto operator&(Enum lhs, Enum rhs) -> Enum { return std::underlying_type_t<Enum>(lhs) & std::underlying_type_t<Enum>(rhs); }\
	auto operator|=(Enum& lhs, Enum& rhs) -> Enum& { return std::underlying_type_t<Enum>(lhs) |= std::underlying_type_t<Enum>(rhs); }\
	auto operator&=(Enum& lhs, Enum& rhs) -> Enum& { return std::underlying_type_t<Enum>(lhs) &= std::underlying_type_t<Enum>(rhs); }
#endif