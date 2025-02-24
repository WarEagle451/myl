#include <myl/definitions.hpp>
#include <myl/macro.hpp>

#include <catch2/catch_all.hpp>

#include <cstring>

#define MYL_TEST_NUMBER 451

TEST_CASE("MYL_STRINGIFY", "[macro.hpp]") {
	MYL_MAYBE_UNUSED int arg = 451;
	CHECK(std::strcmp(MYL_STRINGIFY(arg), "arg") == 0);
}

TEST_CASE("MYL_ARG_STRINGIFY", "[macro.hpp]") {
	CHECK(std::strcmp(MYL_ARG_STRINGIFY(MYL_TEST_NUMBER), "451") == 0);
}

TEST_CASE("MYL_CONCAT", "[macro.hpp]") {
	CHECK(MYL_CONCAT(4, 51) == 451);
}

TEST_CASE("MYL_ARG_CONCAT", "[macro.hpp]") {
	CHECK(MYL_ARG_CONCAT(2, MYL_TEST_NUMBER) == 2451);
}

TEST_CASE("MYL_IF", "[macro.hpp]") {
	CHECK(MYL_IF(0, false, true) == true);
	CHECK(MYL_IF(1, true, false) == true);
}

TEST_CASE("MYL_BOOL", "[macro.hpp]") {
	CHECK(MYL_BOOL(0) == 0);
	CHECK(MYL_BOOL(1) == 1);
	CHECK(MYL_BOOL(2) == 1);
	CHECK(MYL_BOOL(3) == 1);
}

TEST_CASE("MYL_NEGATE", "[macro.hpp]") {
	CHECK(MYL_NEGATE(0) == 1);
	CHECK(MYL_NEGATE(1) == 0);
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

TEST_CASE("MYL_VA_COUNT", "[macro.hpp]") {
	CHECK(MYL_VA_COUNT() == 0);	
	CHECK(MYL_VA_COUNT(1) == 1);	
	CHECK(MYL_VA_COUNT(1, 2) == 2);	
	CHECK(MYL_VA_COUNT(1, 2, 3) == 3);	
}

TEST_CASE("MYL_VA_EMPTY", "[macro.hpp]") {
	CHECK(MYL_VA_EMPTY() == 1);
	CHECK(MYL_VA_EMPTY(1) == 0);
	CHECK(MYL_VA_EMPTY(1, 2) == 0);
	CHECK(MYL_VA_EMPTY(1, 2, 3) == 0);
}
