#pragma once
/* This file contains commonly used compile time and platform dependant features.
*	- Macros
*	- Concepts
*	- Type definitions
*	- Meta programming templates
*/

#define MYL_EXPAND_MACRO(x) x
#define MYL_STRINGIFY(x) #x
#define MYL_STRINGIFY_ARG(arg) MYL_STRINGIFY(arg)

/// MYTodo: MYL_MAKE_VERSION_STRING outside of version.hpp is weird
#define MYL_MAKE_VERSION_STRING(major, minor, patch) (MYL_STRINGIFY_ARG(major) "." MYL_STRINGIFY_ARG(minor) "." MYL_STRINGIFY_ARG(patch))

#include <myl/version.hpp>
#define MYL_VERSION_STRING MYL_MAKE_VERSION_STRING(MYL_VERSION_MAJOR, MYL_VERSION_MINOR, MYL_VERSION_PATCH)

#if __has_cpp_attribute(assume)
#	define MYL_ASSUME(condition) [[assume(condition)]]
#else
#	define MYL_ASSUME(condition)
#endif

#if __has_cpp_attribute(carries_dependency)
#	define MYL_CARRIES_DEPENDENCY [[carries_dependency]]
#else
#	define MYL_CARRIES_DEPENDENCY
#endif

#if __has_cpp_attribute(deprecated) && defined(MYL_ENABLE_DEPRECATED_WARNINGS)
#	define MYL_DEPRECATED [[deprecated]]
#	define MYL_DEPRECATED_M(reason) [[deprecated(reason)]]
#else
#	define MYL_DEPRECATED
#	define MYL_DEPRECATED_M(reason)
#endif

#if __has_cpp_attribute(fallthrough)
#	define MYL_FALLTHROUGH [[fallthrough]]
#else
#	define MYL_FALLTHROUGH
#endif

#if __has_cpp_attribute(likely)
#	define MYL_LIKELY [[likely]]
#else
#	define MYL_LIKELY
#endif

#if __has_cpp_attribute(maybe_unused)
#	define MYL_MAYBE_UNUSED [[maybe_unused]]
#else
#	define MYL_MAYBE_UNUSED
#endif

#if __has_cpp_attribute(nodiscard)
#	define MYL_NO_DISCARD [[nodiscard]]
#	define MYL_NO_DISCARD_M(message) [[nodiscard(message)]]
#else
#	define MYL_NO_DISCARD
#	define MYL_NO_DISCARD_M(message)
#endif

#if __has_cpp_attribute(noreturn)
#	define MYL_NO_RETURN [[noreturn]]
#else
#	define MYL_NO_RETURN
#endif

#if __has_cpp_attribute(no_unique_address)
#	define MYL_NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#	define MYL_NO_UNIQUE_ADDRESS
#endif

#if __has_cpp_attribute(unlikely)
#	define MYL_UNLIKELY [[unlikely]]
#else
#	define MYL_UNLIKELY
#endif

#include <myl/platform.hpp>
#ifdef MYL_COMPILER_MSVC
#	define MYL_COMPILER_NAME "Visual Studio"
#elif defined(MYL_COMPILER_CLANG)
#	define MYL_COMPILER_NAME "Clang"
#elif defined(MYL_COMPILER_GCC)
#	define MYL_COMPILER_NAME "GCC"
#elif defined(MYL_COMPILER_UNKNOWN)
#	define MYL_COMPILER_NAME "Unknown"
#else
#	error "Bug! 'MYL_COMPILER_NAME' not defined for this known compiler!"
#endif

#ifdef MYL_COMPILER_MSVC
#	define MYL_EXPORT __declspec(dllexport)
#	define MYL_IMPORT __declspec(dllimport)
#	define MYL_LOCAL
#elif defined(MYL_COMPILER_CLANG) || defined(MYL_COMPILER_GCC)
#	define MYL_EXPORT __attribute__((visibility("default")))
#	define MYL_IMPORT __attribute__((visibility("default")))
#	define MYL_LOCAL __attribute__((visibility("hidden")))
#elif defined(MYL_COMPILER_UNKNOWN)
#	define MYL_EXPORT
#	define MYL_IMPORT
#	define MYL_LOCAL
#else
#	error "Bug! 'MYL_EXPORT', 'MYL_IMPORT' and 'MYL_LOCAL' not defined for this known compiler!"
#	define MYL_EXPORT
#	define MYL_IMPORT
#	define MYL_LOCAL
#endif

#include <myl/config.hpp>
#ifdef MYL_SHARED_LIBRARY
#	define MYL_API MYL_EXPORT
#else
#	define MYL_API MYL_IMPORT
#endif

#ifndef MYL_DEBUG
#	if defined(MYL_COMPILER_MSVC)
#		ifdef _DEBUG
#			define MYL_DEBUG
#		endif
#	elif defined(MYL_COMPILER_CLANG)
#		ifdef /// MYBug: What in the world is Clang's debug macro?
#			define MYL_DEBUG
#		endif
#	elif defined(MYL_COMPILER_GCC)
#		ifdef _GLIBCXX_DEBUG
#			define MYL_DEBUG
#		endif
#	elif  defined(MYL_COMPILER_UNKNOWN)
#		warning "Unknown compiler! Define 'MYL_DEBUG' if compiling a debug build!"
#	else
#		error "Bug! 'MYL_DEBUG' is not defined for this known compiler!"
#	endif
#endif

#if defined(MYL_COMPILER_MSVC)
#	define MYL_DEBUG_BREAK __debugbreak() 
#elif defined(MYL_COMPILER_CLANG) || defined(MYL_COMPILER_GCC)
#	define MYL_DEBUG_BREAK __builtin_trap()
#elif defined(MYL_COMPILER_UNKNOWN)
#	include <signal.h>
#	ifdef SIGTRAP
#		define MYL_DEBUG_BREAK raise(SIGTRAP)
#	else
#		define MYL_DEBUG_BREAK raise(SIGABRT)
#	endif
#else
#	error "Bug! 'MYL_DEBUG_BREAK' is not defined for this known compiler!"
#endif

#if defined(MYL_DEBUG) && !defined(MYL_DISABLE_ASSERTS)
#	define MYL_ASSERT(condition, msg) { if (!(condition)) { MYL_DEBUG_BREAK; } }
#else
#	define MYL_ASSERT(condition, msg)
#endif

namespace myl {
	// Fundamental Types

	using u8 = unsigned char;
	using u16 = unsigned short;
	using u32 = unsigned int;
	using u64 = unsigned long long;

	using i8 = signed char;
	using i16 = signed short;
	using i32 = signed int;
	using i64 = signed long long;

	using f32 = float;
	using f64 = double;

	using usize = u64;
	using isize = i64;

#ifdef MYL_TYPE_SIZE_CHECK
	static_assert(sizeof(u8) == 1, "Expected myl::u8 to be 1 byte");
	static_assert(sizeof(u16) == 2, "Expected myl::u16 to be 2 bytes");
	static_assert(sizeof(u32) == 4, "Expected myl::u32 to be 4 bytes");
	static_assert(sizeof(u64) == 8, "Expected myl::u64 to be 8 bytes");

	static_assert(sizeof(i8) == 1, "Expected myl::i8 to be 1 byte");
	static_assert(sizeof(i16) == 2, "Expected myl::i16 to be 2 bytes");
	static_assert(sizeof(i32) == 4, "Expected myl::i32 to be 4 bytes");
	static_assert(sizeof(i64) == 8, "Expected myl::i64 to be 8 bytes");

	static_assert(sizeof(f32) == 4, "Expected myl::f32 to be 4 bytes");
	static_assert(sizeof(f64) == 8, "Expected myl::f64 to be 8 bytes");
#endif

	// Meta Programming
	
	namespace meta {
		template<typename T> struct make_signed;
		template<> struct make_signed<i8> { using type = i8; };
		template<> struct make_signed<i16> { using type = i16; };
		template<> struct make_signed<i32> { using type = i32; };
		template<> struct make_signed<i64> { using type = i64; };

		template<> struct make_signed<u8> { using type = i8; };
		template<> struct make_signed<u16> { using type = i16; };
		template<> struct make_signed<u32> { using type = i32; };
		template<> struct make_signed<u64> { using type = i64; };

		template<typename T> struct make_unsigned;
		template<> struct make_unsigned<i8> { using type = u8; };
		template<> struct make_unsigned<i16> { using type = u16; };
		template<> struct make_unsigned<i32> { using type = u32; };
		template<> struct make_unsigned<i64> { using type = u64; };

		template<> struct make_unsigned<u8> { using type = u8; };
		template<> struct make_unsigned<u16> { using type = u16; };
		template<> struct make_unsigned<u32> { using type = u32; };
		template<> struct make_unsigned<u64> { using type = u64; };
	}

	template<typename T> using make_signed		= typename meta::make_signed<T>::type;
	template<typename T> using make_unsigned	= typename meta::make_unsigned<T>::type;

	// Concepts

	namespace meta {
		template<typename, typename> inline constexpr bool same_as = false;
		template<typename T> inline constexpr bool same_as<T, T> = true;
	}

	template<typename A, typename B> concept same_as = meta::same_as<A, B> && meta::same_as<B, A>;
	template<typename A, typename B> concept is_not = !same_as<A, B>;

	template<typename T, typename... Args> concept any_of	= (same_as<T, Args> || ...);
	template<typename T, typename... Args> concept none_of	= (is_not<T, Args> || ...);

	template<typename T> concept character			= any_of<T, char, signed char, unsigned char, wchar_t, char8_t, char16_t, char32_t>;
	template<typename T> concept floating_point		= any_of<T, f32, f64, long double>;
	template<typename T> concept signed_integer		= any_of<T, i8, i16, i32, i64>;
	template<typename T> concept unsigned_integer	= any_of<T, u8, u16, u32, u64>;

	template<typename T> concept integer		= signed_integer<T> || unsigned_integer<T>;
	template<typename T> concept number			= integer<T> || floating_point<T>;
	template<typename T> concept signed_number	= signed_integer<T> || floating_point<T>;

	template<typename T> concept fundamental = number<T> || character<T> || any_of<T, void, bool>;

	template<typename T> concept comparable_less_than	= requires(T a, T b) { a < b; };
	template<typename T> concept comparable_more_than	= requires(T a, T b) { a > b; };
	template<typename T> concept comparable_equality	= requires(T a, T b) { a == b; };
	template<typename T> concept comparable = comparable_less_than<T> && comparable_more_than<T> && comparable_equality<T>;

	template<typename A, typename B> concept comparable_less_than_with	= requires(A a, B b) { a > b; };
	template<typename A, typename B> concept comparable_more_than_with	= requires(A a, B b) { a < b; };
	template<typename A, typename B> concept comparable_equality_with	= requires(A a, B b) { a == b; };
	template<typename A, typename B> concept comparable_with = comparable_less_than_with<A, B> && comparable_more_than_with<A, B> && comparable_equality_with<A, B>;
}

#ifdef MYL_DEFINE_TYPES
using u8 = myl::u8;
using u16 = myl::u16;
using u32 = myl::u32;
using u64 = myl::u64;

using i8 = myl::i8;
using i16 = myl::i16;
using i32 = myl::i32;
using i64 = myl::i64;

using f32 = myl::f32;
using f64 = myl::f64;

using usize = myl::usize;
using isize = myl::isize;
#endif