#include <myl/algorithm.hpp>
#include <myl/math/mat2x2.hpp>
#include <myl/math/mat2x3.hpp>
#include <myl/math/mat2x4.hpp>
#include <myl/math/mat3x2.hpp>
#include <myl/math/mat3x3.hpp>
#include <myl/math/mat3x4.hpp>
#include <myl/math/mat4x2.hpp>
#include <myl/math/mat4x3.hpp>
#include <myl/math/mat4x4.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("myl::transpose", "[mat_common.hpp]") {
	SECTION("2x2") {
		myl::i32mat2x2 m(
			0, 1,
			2, 3
		);
		decltype(m)::transpose_type t(
			0, 2,
			1, 3
		);
		CHECK(myl::transpose(m) == t);
	}
	SECTION("2x3") {
		myl::i32mat2x3 m(
			0, 1,
			2, 3,
			4, 5
		);
		decltype(m)::transpose_type t(
			0, 2, 4,
			1, 3, 5
		);
		CHECK(myl::transpose(m) == t);
	}
	SECTION("2x4") {
		myl::i32mat2x4 m(
			0, 1,
			2, 3,
			4, 5,
			6, 7
		);
		decltype(m)::transpose_type t(
			0, 2, 4, 6,
			1, 3, 5, 7
		);
		CHECK(myl::transpose(m) == t);
	}
	SECTION("3x2") {
		myl::i32mat3x2 m(
			0, 1, 2,
			3, 4, 5
		);
		decltype(m)::transpose_type t(
			0, 3,
			1, 4,
			2, 5
		);
		CHECK(myl::transpose(m) == t);
	}
	SECTION("3x3") {
		myl::i32mat3x3 m(
			0, 1, 2,
			3, 4, 5,
			6, 7, 8
		);
		decltype(m)::transpose_type t(
			0, 3, 6,
			1, 4, 7,
			2, 5, 8
		);
		CHECK(myl::transpose(m) == t);
	}
	SECTION("3x4") {
		myl::i32mat3x4 m(
			0, 1, 2,
			3, 4, 5,
			6, 7, 8,
			9, 10, 11
		);
		decltype(m)::transpose_type t(
			0, 3, 6, 9,
			1, 4, 7, 10,
			2, 5, 8, 11
		);
		CHECK(myl::transpose(m) == t);
	}
	SECTION("4x2") {
		myl::i32mat4x2 m(
			0, 1, 2, 3,
			4, 5, 6, 7
		);
		decltype(m)::transpose_type t(
			0, 4,
			1, 5,
			2, 6,
			3, 7
		);
		CHECK(myl::transpose(m) == t);
	}
	SECTION("4x3") {
		myl::i32mat4x3 m(
			0, 1, 2, 3,
			4, 5, 6, 7,
			8, 9, 10, 11
		);
		decltype(m)::transpose_type t(
			0, 4, 8,
			1, 5, 9,
			2, 6, 10,
			3, 7, 11
		);
		CHECK(myl::transpose(m) == t);
	}
	SECTION("4x4") {
		myl::i32mat4x4 m(
			0, 1, 2, 3,
			4, 5, 6, 7,
			8, 9, 10, 11,
			12, 13, 14, 15
		);
		decltype(m)::transpose_type t(
			0, 4, 8, 12,
			1, 5, 9, 13,
			2, 6, 10, 14,
			3, 7, 11, 15
		);
		CHECK(myl::transpose(m) == t);
	}
}

TEST_CASE("myl::set_column", "[mat_common.hpp]") {
	SECTION("2x2") {
		myl::i32mat2x2 m(0);
		myl::set_column(m, 1, decltype(m)::column_type(1));
		myl::i32mat2x2 t(
			0, 1,
			0, 1
		);
		CHECK(m == t);
	}
	SECTION("2x3") {
		myl::i32mat2x3 m(0);
		myl::set_column(m, 1, decltype(m)::column_type(1));
		myl::i32mat2x3 t(
			0, 1,
			0, 1,
			0, 1
		);
		CHECK(m == t);
	}
	SECTION("2x4") {
		myl::i32mat2x4 m(0);
		myl::set_column(m, 1, decltype(m)::column_type(1));
		myl::i32mat2x4 t(
			0, 1,
			0, 1,
			0, 1,
			0, 1
		);
		CHECK(m == t);
	}
	SECTION("3x2") {
		myl::i32mat3x2 m(0);
		myl::set_column(m, 2, decltype(m)::column_type(1));
		myl::i32mat3x2 t(
			0, 0, 1,
			0, 0, 1
		);
		CHECK(m == t);
	}
	SECTION("3x3") {
		myl::i32mat3x3 m(0);
		myl::set_column(m, 2, decltype(m)::column_type(1));
		myl::i32mat3x3 t(
			0, 0, 1,
			0, 0, 1,
			0, 0, 1
		);
		CHECK(m == t);
	}
	SECTION("3x4") {
		myl::i32mat3x4 m(0);
		myl::set_column(m, 2, decltype(m)::column_type(1));
		myl::i32mat3x4 t(
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1
		);
		CHECK(m == t);
	}
	SECTION("4x2") {
		myl::i32mat4x2 m(0);
		myl::set_column(m, 3, decltype(m)::column_type(1));
		myl::i32mat4x2 t(
			0, 0, 0, 1,
			0, 0, 0, 1
		);
		CHECK(m == t);
	}
	SECTION("4x3") {
		myl::i32mat4x3 m(0);
		myl::set_column(m, 3, decltype(m)::column_type(1));
		myl::i32mat4x3 t(
			0, 0, 0, 1,
			0, 0, 0, 1,
			0, 0, 0, 1
		);
		CHECK(m == t);
	}
	SECTION("4x4") {
		myl::i32mat4x4 m(0);
		myl::set_column(m, 3, decltype(m)::column_type(1));
		myl::i32mat4x4 t(
			0, 0, 0, 1,
			0, 0, 0, 1,
			0, 0, 0, 1,
			0, 0, 0, 1
		);
		CHECK(m == t);
	}
}

TEST_CASE("myl::set_row", "[mat_common.hpp]") {
	SECTION("2x2") {
		myl::i32mat2x2 m(0);
		myl::set_row(m, 1, decltype(m)::row_type(1));
		myl::i32mat2x2 t(
			0, 0,
			1, 1
		);
		CHECK(m == t);
	}
	SECTION("2x3") {
		myl::i32mat2x3 m(0);
		myl::set_row(m, 2, decltype(m)::row_type(1));
		myl::i32mat2x3 t(
			0, 0,
			0, 0,
			1, 1
		);
		CHECK(m == t);
	}
	SECTION("2x4") {
		myl::i32mat2x4 m(0);
		myl::set_row(m, 3, decltype(m)::row_type(1));
		myl::i32mat2x4 t(
			0, 0,
			0, 0,
			0, 0,
			1, 1
		);
		CHECK(m == t);
	}
	SECTION("3x2") {
		myl::i32mat3x2 m(0);
		myl::set_row(m, 1, decltype(m)::row_type(1));
		myl::i32mat3x2 t(
			0, 0, 0,
			1, 1, 1
		);
		CHECK(m == t);
	}
	SECTION("3x3") {
		myl::i32mat3x3 m(0);
		myl::set_row(m, 2, decltype(m)::row_type(1));
		myl::i32mat3x3 t(
			0, 0, 0,
			0, 0, 0,
			1, 1, 1
		);
		CHECK(m == t);
	}
	SECTION("3x4") {
		myl::i32mat3x4 m(0);
		myl::set_row(m, 3, decltype(m)::row_type(1));
		myl::i32mat3x4 t(
			0, 0, 0,
			0, 0, 0,
			0, 0, 0,
			1, 1, 1
		);
		CHECK(m == t);
	}
	SECTION("4x2") {
		myl::i32mat4x2 m(0);
		myl::set_row(m, 1, decltype(m)::row_type(1));
		myl::i32mat4x2 t(
			0, 0, 0, 0,
			1, 1, 1, 1
		);
		CHECK(m == t);
	}
	SECTION("4x3") {
		myl::i32mat4x3 m(0);
		myl::set_row(m, 2, decltype(m)::row_type(1));
		myl::i32mat4x3 t(
			0, 0, 0, 0,
			0, 0, 0, 0,
			1, 1, 1, 1
		);
		CHECK(m == t);
	}
	SECTION("4x4") {
		myl::i32mat4x4 m(0);
		myl::set_row(m, 3, decltype(m)::row_type(1));
		myl::i32mat4x4 t(
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			1, 1, 1, 1
		);
		CHECK(m == t);
	}
}

TEST_CASE("myl::determinant", "[mat_common.hpp]") {
	myl::i32mat2x2 m2x2(
		1, 2,
		3, 4
	);
	myl::i32mat3x3 m3x3(
		1, -2, 3,
		2, 0, 3,
		1, 5, 4
	);
	myl::i32mat4x4 m4x4(
		1, 3, 1, 4,
		3, 9, 5, 15,
		0, 2, 1, 1,
		0, 4, 2, 3
	);

	CHECK(myl::determinant(m2x2) == -2);
	CHECK(myl::determinant(m3x3) == 25);
	CHECK(myl::determinant(m4x4) == -4);
}

template<myl::usize C, myl::usize R, typename T>
MYL_NO_DISCARD constexpr auto compare_floating_point_mat(const myl::mat<C, R, T>& m0, const myl::mat<C, R, T>& m1) -> bool {
	for (myl::usize c = 0; c != C; ++c) // Tranverse columns
		for (myl::usize r = 0; r != R; ++r) // Transverse rows
			if (!myl::approx(m0[c][r], m1[c][r]))
				return false;
	return true;
}

TEST_CASE("myl::inverse", "[mat_common.hpp]") {
	myl::f32mat2x2 m2x2(
		0, 2,
		-1, -2
	);
	myl::f32mat3x3 m3x3(
		3, 0, 2, 
		2, 0, -2, 
		0, 1, 1
	);
	myl::f32mat4x4 m4x4(
		1, 1, 1, 0,
		0, 3, 1, 2,
		2, 3, 1, 0,
		1, 0, 2, 1
	);

	myl::f32mat2x2 i2x2(
		-1, -1,
		.5f, 0
	);
	myl::f32mat3x3 i3x3(
		.2f, .2f, 0,
		-.2f, .3f, 1,
		.2f, -.3f, 0
	);
	myl::f32mat4x4 i4x4(
		-3, -.5f, 1.5f, 1,
		1, .25f, -.25f, -.5f,
		3, .25f, -1.25f, -.5f,
		-3, 0, 1, 1
	);

	CHECK(compare_floating_point_mat(myl::inverse(m2x2), i2x2));
	CHECK(compare_floating_point_mat(myl::inverse(m3x3), i3x3));
	CHECK(compare_floating_point_mat(myl::inverse(m4x4), i4x4));
}
