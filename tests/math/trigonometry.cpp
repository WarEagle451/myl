#include <myl/algorithm.hpp>
#include <myl/math/trigonometry.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("myl::degrees", "[trigonometry.hpp]") {
	CHECK(myl::approx(myl::degrees(2.2f), 126.050714f));
}

TEST_CASE("myl::radians", "[trigonometry.hpp]") {
	CHECK(myl::approx(myl::radians(90.f), 1.57079632f));
}
