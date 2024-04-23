#include <myl/type.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("myl::same_as", "[type.hpp]") {
	CHECK(myl::same_as<int, int>);
	CHECK_FALSE(myl::same_as<short, int>);
}

TEST_CASE("myl::is_not", "[type.hpp]") {
	CHECK(myl::is_not<short, int>);
	CHECK_FALSE(myl::is_not<int, int>);
}

TEST_CASE("myl::any_of", "[type.hpp]") {
	CHECK(myl::any_of<short, int, short>);
	CHECK_FALSE(myl::any_of<bool, int, short>);
}

TEST_CASE("myl::none_of", "[type.hpp]") {
	CHECK(myl::none_of<short, int, unsigned long long>);
	CHECK_FALSE(myl::none_of<short, int, unsigned long long, short>);
}

TEST_CASE("myl::character", "[type.hpp]") {
	CHECK(myl::character<char>);
	CHECK_FALSE(myl::character<int>);
}

TEST_CASE("myl::signed_integer", "[type.hpp]") {
	CHECK(myl::signed_integer<int>);
	CHECK_FALSE(myl::signed_integer<char>);
}

TEST_CASE("myl::unsigned_integer", "[type.hpp]") {
	CHECK(myl::unsigned_integer<unsigned int>);
	CHECK_FALSE(myl::unsigned_integer<signed int>);
}

TEST_CASE("myl::integer", "[type.hpp]") {
	CHECK(myl::integer<int>);
	CHECK_FALSE(myl::integer<float>);
}

TEST_CASE("myl::floating_point", "[type.hpp]") {
	CHECK(myl::floating_point<double>);
	CHECK_FALSE(myl::floating_point<int>);
}

TEST_CASE("myl::number", "[type.hpp]") {
	CHECK(myl::number<double>);
	CHECK_FALSE(myl::number<char>);
}

TEST_CASE("myl::of_size", "[type.hpp]") {
	CHECK(myl::of_size<double, 8>);
	CHECK_FALSE(myl::of_size<float, 8>);
}

TEST_CASE("myl::bit_count_to_uint", "[type.hpp]") {
	CHECK(myl::same_as<myl::bit_count_to_uint<13>, myl::u16>);
	CHECK_FALSE(myl::same_as<myl::bit_count_to_uint<17>, myl::u16>);
}

TEST_CASE("myl::byte_count_to_uint", "[type.hpp]") {
	CHECK(myl::same_as<myl::byte_count_to_uint<2>, myl::u16>);
	CHECK_FALSE(myl::same_as<myl::byte_count_to_uint<3>, myl::u16>);
}
