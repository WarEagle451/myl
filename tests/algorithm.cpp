#include <myl/algorithm.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("myl::approx", "[algorithm.hpp]") {
	CHECK(myl::approx(4.2f * 6.7f, 28.14f));
}

TEST_CASE("myl::min", "[algorithm.hpp]") {
	CHECK(myl::min(5, -2) == -2);
	CHECK(myl::min(0, 0) == 0);
	CHECK(myl::min(2, -4, 8) == -4);
}

TEST_CASE("myl::max", "[algorithm.hpp]") {
	CHECK(myl::max(5, -2) == 5);
	CHECK(myl::max(0, 0) == 0);
	CHECK(myl::max(2, -4, 8) == 8);
}

TEST_CASE("myl::clamp", "[algorithm.hpp]") {
	CHECK(myl::clamp(5, -10, 10) == 5);
	CHECK(myl::clamp(20, -10, 10) == 10);
	CHECK(myl::clamp(-20, -10, 10) == -10);
}

TEST_CASE("myl::floor", "[algorithm.hpp]") {
	CHECK(myl::floor(5, 10) == 10);
	CHECK(myl::floor(15, 10) == 15);
}

TEST_CASE("myl::ceil", "[algorithm.hpp]") {
	CHECK(myl::ceil(5, 10) == 5);
	CHECK(myl::ceil(15, 10) == 10);
}

TEST_CASE("myl::difference", "[algorithm.hpp]") {
	CHECK(myl::difference(-2, 0) == 2);
	CHECK(myl::difference(-1, -4) == 3);
	CHECK(myl::difference(7, 3) == 4);
	CHECK(myl::difference(2, 2) == 0);
}

TEST_CASE("myl::sign", "[algorithm.hpp]") {
	CHECK(myl::sign(0) == 0);
	CHECK(myl::sign(2) == 1);
	CHECK(myl::sign(-2) == -1);
}
