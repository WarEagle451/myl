#pragma once
///#include <myl/definitions.hpp>
///
///#include <iostream>
///#include <source_location>
///#include <string_view>
///#include <type_traits>
///
///namespace myl::test {
///    struct trivial_int {
///        usize value;
///
///        constexpr trivial_int() = default;
///
///        constexpr trivial_int(const trivial_int&) = default;
///
///        constexpr trivial_int(trivial_int&&) = default;
///
///        constexpr explicit trivial_int(usize i)
///            : value{ i } {}
///
///        constexpr ~trivial_int() = default;
///
///        constexpr auto operator=(const trivial_int&) -> trivial_int& = default;
///
///        constexpr auto operator=(trivial_int&&) -> trivial_int& = default;
///
///        explicit operator usize() {
///            return value;
///        }
///    };
///
///    static_assert(std::is_trivial_v<trivial_int> && std::is_copy_constructible_v<trivial_int> && std::is_move_constructible_v<trivial_int>, "");
///
///    struct move_only_int {
///        usize value;
///
///        constexpr move_only_int() = default;
///
///        move_only_int(const move_only_int&) = delete;
///
///        constexpr move_only_int(move_only_int&&) = default;
///
///        constexpr explicit move_only_int(usize i)
///            : value{ i } {}
///
///        constexpr ~move_only_int() = default;
///
///        auto operator=(const move_only_int&) -> move_only_int& = delete;
///
///        constexpr auto operator=(move_only_int&&) -> move_only_int& = default;
///
///        explicit operator usize() {
///            return value;
///        }
///    };
///
///    static_assert(!std::is_trivial_v<move_only_int> && !std::is_copy_constructible_v<move_only_int> && std::is_move_constructible_v<move_only_int>, "");
///
///    class non_copyable_int {
///        usize m_value;
///    public:
///        non_copyable_int(const non_copyable_int&) = delete;
///
///        constexpr explicit non_copyable_int(usize i)
///            : m_value{ i } {}
///
///        constexpr non_copyable_int(non_copyable_int&& other) noexcept
///            : m_value(other.m_value) {
///        }
///
///        auto operator=(const non_copyable_int&) -> non_copyable_int& = delete;
///
///        constexpr auto operator=(non_copyable_int&& other) noexcept -> non_copyable_int& {
///            m_value = other.m_value;
///            other.m_value = 0;
///            return *this;
///        }
///
///        explicit operator usize() {
///            return m_value;
///        }
///    };
///
///    static_assert(, "");
///
///
///    /// PASS HERE IS EXPERIMENTAL
///
///    enum class result {
///        unknown,
///        pass,
///        fail
///    };
///
///    enum class result_behavior {
///        normal,
///        continue_on_fail,
///        expect_fail,
///        supress_fail
///    };
///
///    namespace details {
//////        inline constexpr auto generate_unique_test_name(const char* name, const std::source_location& sl = std::source_location::current()) noexcept -> const char* {
//////#ifdef __COUNTER__
//////            return name + __COUNTER__;
//////#else
//////            return name + sl.line();
//////#endif
//////        }
///    }
///
///    template<typename... Args>
///    struct check {
///        constexpr check(Args&&... args, const std::source_location& location = std::source_location::current()) {
///            try {
///
///            }
///            catch() {
///
///            }
///        }
///    };
///
///    template<typename... Args> check(Args&&... args) -> check<Args...>;
///}
///
//////#define MYL_TEST_CHECK(...)
//////#define MYL_TEST_CHECK_FAIL(...)
//////#define MYL_TEST_CHECK_THROWS(...)
//////#define MYL_TEST_CHECK_THROWS_AS(...)

/// above badd

#include <myl/definitions.hpp>
#include <myl/macro.hpp>

#include <functional>

// CONFIG

/*
* #define MYL_TEST_NO_COUNTER
*/

//

#if !defined(__COUNTER__)
#   define MYL_TEST_NO_COUNTER
#endif

#if defined(MYL_TEST_NO_COUNTER)
#   define MYL_TEST_INTERNAL_UNIQUE_ID(name) MYL_ARG_CONCAT(name, __LINE__)
#else
#   define MYL_TEST_INTERNAL_UNIQUE_ID(name) MYL_ARG_CONCAT(name, __COUNTER__)
#endif

///MYTODO: How does catch know that it needs ti run this function
#define MYL_TEST_INTERNAL_CASE(test_name, ...)\
    printf(MYL_STRINGIFY(test_name))

/// MYTODO: Replace
#define MAGIC_NUMBER 34523456789

#define MYL_TEST_CASE(...) MYL_TEST_INTERNAL_CASE(MYL_TEST_INTERNAL_UNIQUE_ID(MAGIC_NUMBER), __VA_ARGS__)

#define MYL_TEST_SUBCASE(...)

#define MYL_TEST_CHECK(...)


#define MYL_TEST_REQUIRE()
