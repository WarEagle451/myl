#include <myl/algorithm.hpp>
#include <myl/shaping.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("myl::lerp", "[shaping.hpp]") {
	CHECK(myl::approx(myl::lerp(-100.f, 100.f, 0.f), -100.f));
	CHECK(myl::approx(myl::lerp(-100.f, 100.f, .5f), 0.f));
	CHECK(myl::approx(myl::lerp(-100.f, 100.f, 1.f), 100.f));
}

TEST_CASE("myl::inverse_lerp", "[shaping.hpp]") {
	CHECK(myl::approx(myl::inverse_lerp(-100.f, 10.f, 0.f), 0.f));
	CHECK(myl::approx(myl::inverse_lerp(-100.f, 10.f, .5f), 0.f));
	CHECK(myl::approx(myl::inverse_lerp(-100.f, 10.f, 1.f), 0.f));
}

TEST_CASE("myl::step", "[shaping.hpp]") {
	CHECK(myl::step(5, 3) == 0);
	CHECK(myl::step(5, 7) == 5);
}

TEST_CASE("myl::smoothstep", "[shaping.hpp]") {
	CHECK(myl::approx(myl::smoothstep(-100.f, 10.f, 0.f), 0.f));
	CHECK(myl::approx(myl::smoothstep(-100.f, 10.f, .5f), 0.f));
	CHECK(myl::approx(myl::smoothstep(-100.f, 10.f, 1.f), 0.f));
}
