#include <myl/bit.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("myl::byteswap", "[bit.hpp]") {
#ifndef MYL_NO_INTRINSICS
	SECTION("myl::byteswap - intrinsics") {
		myl::i8 i8 = myl::byteswap(static_cast<myl::i8>(0xA5));
		myl::u16 u16 = myl::byteswap(static_cast<myl::u16>(0xA5'E1));
		myl::u32 u32 = myl::byteswap(static_cast<myl::u32>(0xA5'E1'07'F2));
		myl::i64 i64 = myl::byteswap(static_cast<myl::i64>(0xA5'E1'07'F2'8B'CD'34'65));
		CHECK(i8 == static_cast<myl::i8>(0xA5));
		CHECK(u16 == static_cast<myl::u16>(0xE1'A5));
		CHECK(u32 == static_cast<myl::u32>(0xF2'07'E1'A5));
		CHECK(i64 == static_cast<myl::i64>(0x65'34'CD'8B'F2'07'E1'A5));
	}
#endif
	SECTION("myl::byteswap - no intrinsics") {
		constexpr myl::i8 i8   = myl::byteswap(static_cast<myl::i8>(0xA5));
		constexpr myl::u16 u16 = myl::byteswap(static_cast<myl::u16>(0xA5'E1));
		constexpr myl::u32 u32 = myl::byteswap(static_cast<myl::u32>(0xA5'E1'07'F2));
		constexpr myl::i64 i64 = myl::byteswap(static_cast<myl::i64>(0xA5'E1'07'F2'8B'CD'34'65));
		CHECK(i8 == static_cast<myl::i8>(0xA5));
		CHECK(u16 == static_cast<myl::u16>(0xE1'A5));
		CHECK(u32 == static_cast<myl::u32>(0xF2'07'E1'A5));
		CHECK(i64 == static_cast<myl::i64>(0x65'34'CD'8B'F2'07'E1'A5));
	}
}

TEST_CASE("myl::host_to_network", "[bit.hpp]") {
	myl::i32 input = 0xA5'E1'07'F2;
	myl::u32 output = std::bit_cast<myl::u32, myl::i32>(
		std::endian::native == std::endian::big ? 0xA5'E1'07'F2 : 0xF2'07'E1'A5);

	CHECK(myl::host_to_network(input) == output);
}

TEST_CASE("myl::network_to_host", "[bit.hpp]") {
	myl::u32 input = 0xA5'E1'07'F2;
	myl::i32 output = std::bit_cast<myl::i32, myl::u32>(
		std::endian::native == std::endian::big ? 0xA5'E1'07'F2 : 0xF2'07'E1'A5);

	CHECK(myl::network_to_host<myl::i32>(input) == output);
}
