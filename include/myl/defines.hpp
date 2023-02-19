#pragma once
#include <myl/config.hpp>

#define MYL_EXPAND_MACRO(x) x
#define MYL_STRINGIFY(x) #x
#define MYL_STRINGIFY_ARG(arg) MYL_STRINGIFY(arg)

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

#if __has_cpp_attribute(deprecated)
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
#ifdef MYL_EXPORT
#	ifdef MYL_COMPILER_MSVC
#		define MYL_API __declspec(dllexport)
#	else
#		define MYL_API __attribute__((visibility("default")))
#	endif
#else
#	ifdef MYL_COMPILER_MSVC
#		define MYL_API __declspec(dllimport)
#	else
#		define MYL_API
#	endif
#endif

#ifndef MYL_DEBUG
#	ifdef MYL_COMPILER_MSVC
#		ifdef _DEBUG
#			define MYL_DEBUG
#		endif
#	elif defined(MYL_COMPILER_CLANG) || defined(MYL_COMPILER_GCC
#		ifdef _GLIBCXX_DEBUG
#			define MYL_DEBUG
#		endif
#	else
/// MYTodo: Emit warning here: Unknown compiler! Define MYL_DEBUG if compiling a debug build!
#	endif
#endif

namespace myl {
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