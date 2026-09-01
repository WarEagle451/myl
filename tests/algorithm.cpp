#include <myl/algorithm.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("myl::median (iterator)", "[algorithm.hpp]") {
	std::list<float> l1{ 1, 2, 3, 4 };
	std::list<float> l2{ 1, 2, 3, 4, 5 };
	std::array<float, 9> a1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::array<float, 10> a2{ 1, 2.1, 2.2, 2.3, 5.9, 6, 7, 8, 9, 10 };
	l1.push_back(5);
	l2.push_front(-1);

	float v1 = myl::median(a1.begin(), a1.end());
	float v2 = myl::median(a2.begin(), a2.end());
	float v3 = myl::median(l1.begin(), l1.end());
	float v4 = myl::median(l2.begin(), l2.end());

	CHECK(myl::approx(v1, 5.f));
	CHECK(myl::approx(v2, 5.95f));
	CHECK(myl::approx(v3, 3.f));
	CHECK(myl::approx(v4, 2.5f));
}

TEST_CASE("myl::median (variadic)", "[algorithm.hpp]") {
	auto v1 = myl::median(1, 2, 3, 6, 7);
	auto v2 = myl::median(1, 2, 4.5, 7.f, 9, 10);
	CHECK(myl::approx(v1, 3.f));
	CHECK(myl::approx(v2, 5.75));
}

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
