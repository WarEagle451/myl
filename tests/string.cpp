#include <myl/string.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("myl::to_upper", "[string.hpp]") {
	std::string s = "abC123";
	CHECK(myl::to_upper(s) == "ABC123");

	std::wstring w = L"abC123";
	CHECK(myl::to_upper(w) == L"ABC123");
}

TEST_CASE("myl::to_lower", "[string.hpp]") {
	std::string s = "abC123";
	CHECK(myl::to_lower(s) == "abc123");

	std::wstring w = L"abC123";
	CHECK(myl::to_lower(w) == L"abc123");
}
