#pragma once
#include <myl/config.hpp>

// Attributes

#if __has_cpp_attribute(assume)
#   define MYL_ASSUME(condition) [[assume(condition)]]
#else
#   define MYL_ASSUME(condition)
#endif

#if __has_cpp_attribute(carries_dependency)
#   define MYL_CARRIES_DEPENDENCY [[carries_dependency]]
#else
#   define MYL_CARRIES_DEPENDENCY
#endif

#if __has_cpp_attribute(deprecated) && !defined(MYL_NO_DEPRECATED_WARNINGS)
#   define MYL_DEPRECATED [[deprecated]]
#   define MYL_DEPRECATED_M(reason) [[deprecated(reason)]]
#else
#   define MYL_DEPRECATED
#   define MYL_DEPRECATED_M(reason)
#endif

#if __has_cpp_attribute(fallthrough)
#   define MYL_FALLTHROUGH [[fallthrough]]
#else
#   define MYL_FALLTHROUGH
#endif

#if __has_cpp_attribute(likely)
#   define MYL_LIKELY [[likely]]
#else
#   define MYL_LIKELY
#endif

#if __has_cpp_attribute(maybe_unused)
#   define MYL_MAYBE_UNUSED [[maybe_unused]]
#else
#   define MYL_MAYBE_UNUSED
#endif

#if __has_cpp_attribute(nodiscard)
#   define MYL_NO_DISCARD [[nodiscard]]
#   define MYL_NO_DISCARD_M(message) [[nodiscard(message)]]
#else
#   define MYL_NO_DISCARD
#   define MYL_NO_DISCARD_M(message)
#endif

#if __has_cpp_attribute(noreturn)
#   define MYL_NO_RETURN [[noreturn]]
#else
#   define MYL_NO_RETURN
#endif

#if __has_cpp_attribute(no_unique_address)
#   define MYL_NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#   define MYL_NO_UNIQUE_ADDRESS
#endif

#if __has_cpp_attribute(unlikely)
#   define MYL_UNLIKELY [[unlikely]]
#else
#   define MYL_UNLIKELY
#endif

// Debug Macros

#if defined(_DEBUG) || defined(_GLIBCXX_DEBUG)
#   define MYL_DEBUG
#endif

#include <myl/platform.hpp>
#if defined(MYL_COMPILER_MSVC)
#   define MYL_DEBUG_BREAK __debugbreak() 
#elif defined(MYL_COMPILER_CLANG)
#   define MYL_DEBUG_BREAK __builtin_trap()
#elif defined(MYL_COMPILER_GCC)
#   define MYL_DEBUG_BREAK __builtin_trap()
#elif defined(MYL_COMPILER_UNKNOWN)
#   include <signal.h>
#   ifdef SIGTRAP
#       define MYL_DEBUG_BREAK raise(SIGTRAP)
#   else
#       define MYL_DEBUG_BREAK raise(SIGABRT)
#   endif
#else
#   error "Compiler dependent macros are not implemented on known compiler"
#endif

// Asserts

#if defined(MYL_DEBUG) && !defined(MYL_NO_ASSERTS)
#   define MYL_ASSERT(condition, ...) { if (!(condition)) { MYL_DEBUG_BREAK; } }
#else
#   define MYL_ASSERT(condition, ...)
#endif

#ifndef MYL_NO_VERIFY
#   define MYL_VERIFY(condition, ...) { if (!(condition)) { MYL_DEBUG_BREAK; } }
#else
#   define MYL_VERIFY(condition, ...)
#endif

// Exceptions

#ifdef MYL_NO_EXCEPTIONS
#   define MYL_TRY
#   define MYL_CATCH(exception_statement, block)
#   define MYL_THROW(exception)
#   define MYL_THROW_IF(condition, exception, ...) MYL_ASSERT(!(condition), __VA_ARGS__)
#else
#   define MYL_TRY try
#   define MYL_CATCH(exception_statement, block) catch (exception_statement) block
#   define MYL_THROW(exception) throw exception
#   define MYL_THROW_IF(condition, exception, ...) if (condition) throw exception(__VA_ARGS__)
#endif

// Other Macros

#ifdef MYL_SHARED_LIBRARY
#   define MYL_API MYL_EXPORT
#else
#   define MYL_API MYL_IMPORT
#endif

// Shorthand Types

#include <cstddef>
#include <cstdint>

namespace myl {
    using i8 = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;

    using if8 = std::int_fast8_t;
    using if16 = std::int_fast16_t;
    using if32 = std::int_fast32_t;
    using if64 = std::int_fast64_t;

    using il8 = std::int_least8_t;
    using il16 = std::int_least16_t;
    using il32 = std::int_least32_t;
    using il64 = std::int_least64_t;

    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    using uf8 = std::uint_fast8_t;
    using uf16 = std::uint_fast16_t;
    using uf32 = std::uint_fast32_t;
    using uf64 = std::uint_fast64_t;

    using ul8 = std::uint_least8_t;
    using ul16 = std::uint_least16_t;
    using ul32 = std::uint_least32_t;
    using ul64 = std::uint_least64_t;

    using usize = std::size_t;

    using f32 = float;
    using f64 = double;
}
