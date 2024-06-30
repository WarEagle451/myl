#include <myl/math/vec2.hpp>
#include <myl/math/vec3.hpp>
#include <myl/math/vec4.hpp>

#include <catch2/catch_all.hpp>

#include <utility>

TEST_CASE("vec2", "[vec2.hpp]") {
    SECTION("constructor") {
        SECTION("default") {
            myl::i8vec2 a;
            CHECK(a == myl::i8vec2{ 0, 0 });
        }
        SECTION("copy") {
            myl::i8vec2 a{ 2, 1 };
            myl::i8vec2 b(a);
            CHECK(b == myl::i8vec2{ 2, 1 });
        }
        SECTION("move") {
            myl::i8vec2 a{ 2, 1 };
            myl::i8vec2 b(std::move(a));
            CHECK(b == myl::i8vec2{ 2, 1 });
        }
        SECTION("scalar copy") {
            myl::i8vec2 a(2);
            CHECK(a == myl::i8vec2{ 2, 2 });
        }
        SECTION("2 scalar copy") {
            myl::i8 a = 2, b = 1;
            CHECK(myl::i8vec2(a, b) == myl::i8vec2{ 2, 1 });
        }
        SECTION("2 scalar move") {
            myl::i8 a = 2, b = 1;
            CHECK(myl::i8vec2(std::move(a), std::move(b)) == myl::i8vec2{ 2, 1 });
        }
        SECTION("vec3") {
            myl::i8vec3 a{ 1, 2, 3 };
            myl::i8vec2 b(a);
            CHECK(a == myl::i8vec2{ 1, 2 });
        }
        SECTION("vec4") {
            myl::i8vec4 a{ 1, 2, 3, 4 };
            myl::i8vec2 b(a);
            CHECK(a == myl::i8vec2{ 1, 2 });
        }
    }
    SECTION("assignment") {
        SECTION("copy") {
            myl::i8vec2 a{ 1, 2 };
            myl::i8vec2 b = a;
            CHECK(b == myl::i8vec2{ 1, 2 });
        }
        SECTION("move") {
            myl::i8vec2 a{ 1, 2 };
            myl::i8vec2 b = std::move(a);
            CHECK(b == myl::i8vec2{ 1, 2 });
        }
    }
    SECTION("bool conversion") {
        CHECK(bool(myl::i8vec2{ 1, 2 }));
        CHECK_FALSE(bool(myl::i8vec2()));
    }
    SECTION("index") {
        {
            myl::i8vec2 a{ 1, 2 };
            myl::u8 b = a[0];
            myl::u8 c = a[1];
            CHECK(b == 1);
            CHECK(c == 2);
        }
        {
            myl::i8vec2 a{ 1, 2 };
            const myl::u8 b = a[0];
            const myl::u8 c = a[1];
            CHECK(b == 1);
            CHECK(c == 2);
        }
    }
    SECTION("negation") {
        CHECK(-myl::i32vec2{ 2, -4 } == myl::i32vec2{ -2, 4 });
    }
    SECTION("scalar arithmetic") {
        myl::i32vec2 a{ 2, 4 };

        CHECK(a + 2 == myl::i32vec2{ 4, 6 });
        CHECK(a - 2 == myl::i32vec2{ 0, 2 });
        CHECK(a * 2 == myl::i32vec2{ 4, 8 });
        CHECK(a / 2 == myl::i32vec2{ 1, 2 });
        CHECK(a % 3 == myl::i32vec2{ 2, 1 });

        myl::i32vec2 b = a;
        b += 2;
        CHECK(b == myl::i32vec2{ 4, 6 });

        b = a;
        b -= 2;
        CHECK(b == myl::i32vec2{ 0, 2 });

        b = a;
        b *= 2;
        CHECK(b == myl::i32vec2{ 4, 8 });

        b = a;
        b /= 2;
        CHECK(b == myl::i32vec2{ 1, 2 });

        b = a;
        b %= 2;
        CHECK(b == myl::i32vec2{ 0, 0 });
    }
    SECTION("vec2 arithmetic") {
        myl::i32vec2 a{ 2, 4 };
        myl::i32vec2 b{ 1, 2 };
        myl::i32vec2 c = a;

        CHECK(a + b == myl::i32vec2{ 3, 6 });
        CHECK(a - b == myl::i32vec2{ 1, 2 });
        CHECK(a * b == myl::i32vec2{ 2, 8 });
        CHECK(a / b == myl::i32vec2{ 2, 2 });
        CHECK(a % b == myl::i32vec2{ 0, 0 });

        c += b;
        CHECK(c == myl::i32vec2{ 3, 6 });

        c = a;
        c -= b;
        CHECK(c == myl::i32vec2{ 1, 2 });

        c = a;
        c *= b;
        CHECK(c == myl::i32vec2{ 2, 8 });

        c = a;
        c /= b;
        CHECK(c == myl::i32vec2{ 2, 2 });

        c = a;
        c %= b;
        CHECK(c == myl::i32vec2{ 0, 0 });
    }
    SECTION("comparision") {
        CHECK(myl::i32vec2{ 5, 3 } == myl::i32vec2{ 5, 3 });
        CHECK(myl::i32vec2{ 5, 2 } != myl::i32vec2{ 5, 3 });
    }
}
