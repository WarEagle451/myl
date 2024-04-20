#include <myl/math/vec2.hpp>
#include <myl/math/vec3.hpp>
#include <myl/math/vec4.hpp>

#include <catch2/catch_all.hpp>

#include <utility>

TEST_CASE("vec2 - constructor: default", "[vec2.hpp]") {
    myl::i8vec2 a;
    bool result = (a.x == 0 && a.y == 0);
    CHECK(result);
}

TEST_CASE("vec2 - constructor: copy", "[vec2.hpp]") {
    myl::i8vec2 a{ 2, 1 };
    myl::i8vec2 b(a);
    bool result = (a == b);
    CHECK(result);
}

TEST_CASE("vec2 - constructor: move", "[vec2.hpp]") {
    myl::i8vec2 a{ 2, 1 };
    myl::i8vec2 b(std::move(a));
    bool result = (b.x == 2 && b.y == 1);
    CHECK(result);
}

TEST_CASE("vec2 - constructor: scalar copy", "[vec2.hpp]") {
    myl::i8vec2 a(2);
    bool result = (a.x == 2 && a.y == 2);
    CHECK(result);
}

TEST_CASE("vec2 - constructor: 2 scalars copy", "[vec2.hpp]") {
    myl::i8vec2 a(1, 4);
    bool result = (a.x == 1 && a.y == 4);
    CHECK(result);
}

TEST_CASE("vec2 - constructor: 2 scalar move", "[vec2.hpp]") {
    myl::i8 i0 = 1, i1 = 4;
    myl::i8vec2 a(std::move(i0), std::move(i1));
    bool result = (a.x == 1 && a.y == 4);
    CHECK(result);
}

TEST_CASE("vec2 - constructor: vec3", "[vec2.hpp]") {
    myl::i8vec3 a{ 1, 2, 3 };
    myl::i8vec2 b(a);
    bool result = (a.x == 1 && a.y == 2);
    CHECK(result);
}

TEST_CASE("vec2 - constructor: vec4", "[vec2.hpp]") {
    myl::i8vec4 a{ 1, 2, 3, 4 };
    myl::i8vec2 b(a);
    bool result = (a.x == 1 && a.y == 2);
    CHECK(result);
}

TEST_CASE("vec2 - assignment: copy", "[vec2.hpp]") {
    myl::i8vec2 a{ 1, 2 };
    myl::i8vec2 b = a;
    bool result = (a == b);
    CHECK(result);
}

TEST_CASE("vec2 - assignment: move", "[vec2.hpp]") {
    myl::i8vec2 a{ 1, 2 };
    myl::i8vec2 b = std::move(a);
    bool result = (b.x == 1 && b.y == 2);
    CHECK(result);
}

TEST_CASE("vec2 - implicit bool conversion", "[vec2.hpp]") {
    myl::i8vec2 a{ 1, 2 };
    myl::i8vec2 b;
    bool result = a && !b;
    CHECK(result);
}

TEST_CASE("vec2 - index", "[vec2.hpp]") {
    myl::i8vec2 a{ 1, 2 };
    myl::u8 b = a[0];
    myl::u8 c = a[1];
    bool result = (b == 1 && c == 2);
    CHECK(result);
}

TEST_CASE("vec2 - index: const", "[vec2.hpp]") {
    myl::i8vec2 a{ 1, 2 };
    const myl::u8 b = a[0];
    const myl::u8 c = a[1];
    bool result = (b == 1 && c == 2);
    CHECK(result);
}

TEST_CASE("vec2 - negation", "[vec2.hpp]") {
    myl::i32vec2 a = -myl::i32vec2{ 2, 4 };
    bool result = (a.x == -2 && a.y == -4);
    CHECK(result);
}

TEST_CASE("vec2 - add scalar", "[vec2.hpp]") {
    myl::u32vec2 a{ 2, 4 };
    myl::u32vec2 b = a + 2u;
    bool result = (b.x == 4 && b.y == 6);
    CHECK(result);
}

TEST_CASE("vec2 - subtract scalar", "[vec2.hpp]") {
    myl::u32vec2 a{ 2, 4 };
    myl::u32vec2 b = a - 2u;
    bool result = (b.x == 0 && b.y == 2);
    CHECK(result);
}

TEST_CASE("vec2 - multiply by scalar", "[vec2.hpp]") {
    myl::u32vec2 a{ 2, 4 };
    myl::u32vec2 b = a * 2u;
    bool result = (b.x == 4 && b.y == 8);
    CHECK(result);
}

TEST_CASE("vec2 - divide by scalar", "[vec2.hpp]") {
    myl::u32vec2 a{ 2, 4 };
    myl::u32vec2 b = a / 2u;
    bool result = (b.x == 1 && b.y == 2);
    CHECK(result);
}

TEST_CASE("vec2 - mod by scalar", "[vec2.hpp]") {
    myl::u32vec2 a{ 2, 5 };
    myl::u32vec2 b = a % 2u;
    bool result = (b.x == 0 && b.y == 1);
    CHECK(result);
}

TEST_CASE("vec2 - add to by scalar", "[vec2.hpp]") {
    myl::u32vec2 a{ 2, 4 };
    a += 2u;
    bool result = (a.x == 4 && a.y == 6);
    CHECK(result);
}

TEST_CASE("vec2 - subtract to by scalar", "[vec2.hpp]") {
    myl::u32vec2 a{ 2, 4 };
    a -= 2u;
    bool result = (a.x == 0 && a.y == 2);
    CHECK(result);
}

TEST_CASE("vec2 - multiply to by scalar", "[vec2.hpp]") {
    myl::u32vec2 a{ 2, 4 };
    a *= 2u;
    bool result = (a.x == 4 && a.y == 8);
    CHECK(result);
}

TEST_CASE("vec2 - divide to by scalar", "[vec2.hpp]") {
    myl::u32vec2 a{ 2, 4 };
    a /= 2u;
    bool result = (a.x == 1 && a.y == 2);
    CHECK(result);
}

TEST_CASE("vec2 - mod to by scalar", "[vec2.hpp]") {
    myl::u32vec2 a{ 2, 5 };
    a %= 2u;
    bool result = (a.x == 0 && a.y == 1);
    CHECK(result);
}

TEST_CASE("vec2 - add vec2", "[vec2.hpp]") {
    myl::i32vec2 a = myl::i32vec2{ 1, 2 } + myl::i32vec2{ 3, 4 };
    bool result = (a.x == 4 && a.y == 6);
    CHECK(result);
}

TEST_CASE("vec2 - subtract vec2", "[vec2.hpp]") {
    myl::i32vec2 a = myl::i32vec2{ 1, 2 } - myl::i32vec2{ 3, 4 };
    bool result = (a.x == -2 && a.y == -2);
    CHECK(result);
}

TEST_CASE("vec2 - multiply by vec2", "[vec2.hpp]") {
    myl::i32vec2 a = myl::i32vec2{ 1, 2 } * myl::i32vec2{ 3, 4 };
    bool result = (a.x == 3 && a.y == 8);
    CHECK(result);
}

TEST_CASE("vec2 - divide by vec2", "[vec2.hpp]") {
    myl::i32vec2 a = myl::i32vec2{ 4, 3 } / myl::i32vec2{ 2, 1 };
    bool result = (a.x == 2 && a.y == 3);
    CHECK(result);
}

TEST_CASE("vec2 - mod by vec2", "[vec2.hpp]") {
    myl::i32vec2 a = myl::i32vec2{ 5, 3 } % myl::i32vec2{ 2, 1 };
    bool result = (a.x == 1 && a.y == 0);
    CHECK(result);
}

TEST_CASE("vec2 - add to by vec2", "[vec2.hpp]") {
    myl::i32vec2 a{ 4, 3 };
    a += myl::i32vec2{ 2, 1 };
    bool result = (a.x == 6 && a.y == 4);
    CHECK(result);
}

TEST_CASE("vec2 - subtract to by vec2", "[vec2.hpp]") {
    myl::i32vec2 a{ 4, 3 };
    a -= myl::i32vec2{ 2, 1 };
    bool result = (a.x == 2 && a.y == 2);
    CHECK(result);
}

TEST_CASE("vec2 - multiply to by vec2", "[vec2.hpp]") {
    myl::i32vec2 a{ 4, 3 };
    a *= myl::i32vec2{ 2, 1 };
    bool result = (a.x == 8 && a.y == 3);
    CHECK(result);
}

TEST_CASE("vec2 - divide to by vec2", "[vec2.hpp]") {
    myl::i32vec2 a{ 4, 3 };
    a /= myl::i32vec2{ 2, 1 };
    bool result = (a.x == 2 && a.y == 3);
    CHECK(result);
}

TEST_CASE("vec2 - mod to by vec2", "[vec2.hpp]") {
    myl::i32vec2 a{ 5, 3 };
    a %= myl::i32vec2{ 2, 1 };
    bool result = (a.x == 1 && a.y == 0);
    CHECK(result);
}

TEST_CASE("vec2 - comparision", "[vec2.hpp]") {
    myl::i32vec2 a{ 5, 3 };
    myl::i32vec2 b{ 5, 3 };
    bool result = (a == b);
    CHECK(result);
}
