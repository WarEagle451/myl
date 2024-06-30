#include <myl/definitions.hpp>
#include <myl/macro.hpp>

#include <catch2/catch_all.hpp>

#include <cstring>

TEST_CASE("MYL_STRINGIFY", "[macro.hpp]") {
	MYL_MAYBE_UNUSED int arg = 451;
	CHECK(std::strcmp(MYL_STRINGIFY(arg), "arg") == 0);
}

#define MYL_TEST_NUMBER 451
TEST_CASE("MYL_ARG_STRINGIFY", "[macro.hpp]") {
	CHECK(std::strcmp(MYL_ARG_STRINGIFY(MYL_TEST_NUMBER), "451") == 0);
}

TEST_CASE("MYL_ARG_DISCARD", "[macro.hpp]") {
	CHECK(MYL_ARG_DISCARD(1, 2) == 2);
}

TEST_CASE("MYL_ARG_X", "[macro.hpp]") {
	CHECK(MYL_ARG_1(1, 2, 3, 4, 5, 6, 7, 8, 9) == 1);
	CHECK(MYL_ARG_2(1, 2, 3, 4, 5, 6, 7, 8, 9) == 2);
	CHECK(MYL_ARG_3(1, 2, 3, 4, 5, 6, 7, 8, 9) == 3);
	CHECK(MYL_ARG_4(1, 2, 3, 4, 5, 6, 7, 8, 9) == 4);
	CHECK(MYL_ARG_5(1, 2, 3, 4, 5, 6, 7, 8, 9) == 5);
	CHECK(MYL_ARG_6(1, 2, 3, 4, 5, 6, 7, 8, 9) == 6);
	CHECK(MYL_ARG_7(1, 2, 3, 4, 5, 6, 7, 8, 9) == 7);
	CHECK(MYL_ARG_8(1, 2, 3, 4, 5, 6, 7, 8, 9) == 8);
	CHECK(MYL_ARG_9(1, 2, 3, 4, 5, 6, 7, 8, 9) == 9);
}

#define MYL_TEST_CHECK_MYL_VA_EMPTY(...) MYL_VA_EMPTY(__VA_ARGS__)

TEST_CASE("MYL_VA_EMPTY", "[macro.hpp]") {
	CHECK(MYL_TEST_CHECK_MYL_VA_EMPTY());
	CHECK_FALSE(MYL_TEST_CHECK_MYL_VA_EMPTY(true, false));
}
