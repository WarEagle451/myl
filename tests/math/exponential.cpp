#include <myl/algorithm.hpp>
#include <myl/math/exponential.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("myl::factorial", "[math/exponential.hpp]") {
	CHECK(myl::factorial(1) == 1);
	CHECK(myl::factorial(2) == 2);
	CHECK(myl::factorial(4) == 24);
	CHECK(myl::factorial(8) == 40320);
	CHECK(myl::approx(myl::factorial(4.5f), 52.34277f));
}