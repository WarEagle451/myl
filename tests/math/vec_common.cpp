#include <myl/algorithm.hpp>
#include <myl/math/vec2.hpp>
#include <myl/math/vec3.hpp>
#include <myl/math/vec4.hpp>

#include <catch2/catch_all.hpp>

static myl::i32vec2 i32v2a{ 4, 5 };
static myl::i32vec2 i32v2b{ 13, 8 };
static myl::i32vec3 i32v3a{ 2, 1, 6 };
static myl::i32vec3 i32v3b{ 9, 4, 2 };
static myl::i32vec4 i32v4a{ 7, 4, 8, 2 };
static myl::i32vec4 i32v4b{ 3, 8, 2, 0 };

static myl::f32vec2 f32v2a{ 4.f, 5.f };
static myl::f32vec2 f32v2b{ 9.f, 8.f };
static myl::f32vec3 f32v3a{ 2.f, 1.f, 6.f };
static myl::f32vec3 f32v3b{ 9.f, 4.f, 2.f };
static myl::f32vec4 f32v4a{ 7.f, 4.f, 8.f, 2.f };
static myl::f32vec4 f32v4b{ 3.f, 8.f, 2.f, 0.f };

TEST_CASE("myl::component_count", "vec_common.hpp") {
	CHECK(myl::component_count(i32v2a) == 2);
	CHECK(myl::component_count(i32v3a) == 3);
	CHECK(myl::component_count(i32v4a) == 4);
}

TEST_CASE("myl::dot", "vec_common.hpp") {
	CHECK(myl::dot(i32v2a, i32v2b) == 92);
	CHECK(myl::dot(i32v3a, i32v3b) == 34);
	CHECK(myl::dot(i32v4a, i32v4b) == 69);
}

TEST_CASE("myl::length", "vec_common.hpp") {
	CHECK(myl::approx(myl::length(f32v2a), 6.403124f));
	CHECK(myl::approx(myl::length(f32v3a), 6.403124f));
	CHECK(myl::approx(myl::length(f32v4a), 11.532562f));
}

TEST_CASE("myl::normalize", "vec_common.hpp") {
	CHECK(myl::approx(myl::length(myl::normalize(f32v2a)), 1.f));
	CHECK(myl::approx(myl::length(myl::normalize(f32v3a)), 1.f));
	CHECK(myl::approx(myl::length(myl::normalize(f32v4a)), 1.f));
}

TEST_CASE("myl::distance", "vec_common.hpp") {
	CHECK(myl::approx(myl::distance(f32v2a, f32v2b), 5.830951f));
	CHECK(myl::approx(myl::distance(f32v3a, f32v3b), 8.602325f));
	CHECK(myl::approx(myl::distance(f32v4a, f32v4b), 8.485280f));
}

TEST_CASE("myl::vec::<=>", "vec_common.hpp") {
	CHECK(i32v2a < i32v2b);
	CHECK(i32v2a <= i32v2b);
	CHECK(i32v2b > i32v2a);
	CHECK(i32v2b >= i32v2a);

	CHECK(i32v3a < i32v3b);
	CHECK(i32v3a <= i32v3b);
	CHECK(i32v3b > i32v3a);
	CHECK(i32v3b >= i32v3a);

	CHECK(i32v4a > i32v4b);
	CHECK(i32v4a >= i32v4b);
	CHECK(i32v4b < i32v4a);
	CHECK(i32v4b <= i32v4a);
}
