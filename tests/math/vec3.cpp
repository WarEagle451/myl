#include <myl/math/vec2.hpp>
#include <myl/math/vec3.hpp>
#include <myl/math/vec4.hpp>

#include <catch2/catch_all.hpp>

#include <utility>

TEST_CASE("vec3", "[vec3.hpp]") {
    SECTION("constructor") {
        SECTION("default") {
            CHECK(myl::i32vec3() == myl::i32vec3{0, 0, 0});
        }
        SECTION("copy") {
            myl::i32vec3 a{ 3, 4, 5 };
            myl::i32vec3 b = a;
            CHECK(b == a);
        }
        SECTION("move") {
            myl::i32vec3 a{ 3, 4, 5 };
            myl::i32vec3 b = std::move(a);
            CHECK(b == myl::i32vec3{ 3, 4, 5 });
        }
        SECTION("scalar") {
            CHECK(myl::i32vec3(2) == myl::i32vec3{ 2, 2, 2 });
        }
        SECTION("3 scalar copy") {
            myl::i32 a = 4, b = 5, c = 1;
            CHECK(myl::i32vec3(a, b, c) == myl::i32vec3{ 4, 5, 1 });
        }
        SECTION("3 scalar move") {
            myl::i32 a = 4, b = 5, c = 1;
            CHECK(myl::i32vec3(std::move(a), std::move(b), std::move(c)) == myl::i32vec3{ 4, 5, 1});
        }
        SECTION("vec xy scalar z") {
            myl::i32vec2 a{ 4, 5 };
            CHECK(myl::i32vec3(a, 1) == myl::i32vec3{ 4, 5, 1 });
        }
        SECTION("scalar x vec yz") {
            myl::i32vec2 a{ 5, 1 };
            CHECK(myl::i32vec3(4, a) == myl::i32vec3{ 4, 5, 1 });
        }
        SECTION("vec4") {
            myl::i32vec4 a{ 4, 5, 1, 7 };
            CHECK(myl::i32vec3(a) == myl::i32vec3{ 4, 5, 1 });
        }
    }
    SECTION("assignment") {
        SECTION("copy") {
            myl::i32vec3 a{ 4, 5, 1 };
            myl::i32vec3 b = a;
            CHECK(a == b);
        }
        SECTION("move") {
            myl::i32vec3 a{ 4, 5, 1 };
            myl::i32vec3 b = std::move(a);
            CHECK(a == b);
        }
    }
    SECTION("bool conversion") {
        CHECK(bool(myl::i32vec3{ 4, 5, 1 }));
        CHECK_FALSE(bool(myl::i32vec3()));
    }
    SECTION("index") {
        {
            myl::i32vec3 a{ 1, 2, 3 };
            myl::i32 b = a[0];
            myl::i32 c = a[1];
            myl::i32 d = a[2];
            CHECK(b == 1);
            CHECK(c == 2);
            CHECK(d == 3);
        }
        {
            myl::i32vec3 a{ 1, 2, 3 };
            const myl::i32 b = a[0];
            const myl::i32 c = a[1];
            const myl::i32 d = a[2];
            CHECK(b == 1);
            CHECK(c == 2);
            CHECK(d == 3);
        }
    }
    SECTION("negation") {
        CHECK(-myl::i32vec3{ 4, -5, 1 } == myl::i32vec3{ -4, 5, -1 });
    }
    SECTION("scalar arithmetic") {
        myl::i32vec3 a{ 2, 4, 6 };

        CHECK(a + 2 == myl::i32vec3{ 4, 6, 8 });
        CHECK(a - 2 == myl::i32vec3{ 0, 2, 4 });
        CHECK(a * 2 == myl::i32vec3{ 4, 8, 12 });
        CHECK(a / 2 == myl::i32vec3{ 1, 2, 3 });
        CHECK(a % 3 == myl::i32vec3{ 2, 1, 0 });

        myl::i32vec3 b = a;
        b += 2;
        CHECK(b == myl::i32vec3{ 4, 6, 8 });

        b = a;
        b -= 2;
        CHECK(b == myl::i32vec3{ 0, 2, 4 });

        b = a;
        b *= 2;
        CHECK(b == myl::i32vec3{ 4, 8, 12 });

        b = a;
        b /= 2;
        CHECK(b == myl::i32vec3{ 1, 2, 3 });

        b = a;
        b %= 3;
        CHECK(b == myl::i32vec3{ 2, 1, 0 });
    }
    SECTION("vec2 arithmetic") {
        myl::i32vec3 a{ 2, 4, 6 };
        myl::i32vec2 b{ 1, 2 };

        CHECK(a + b == myl::i32vec3{ 3, 6, 6 });
        CHECK(a - b == myl::i32vec3{ 1, 2, 6 });
        CHECK(a * b == myl::i32vec3{ 2, 8, 6 });
        CHECK(a / b == myl::i32vec3{ 2, 2, 6 });
        CHECK(a % b == myl::i32vec3{ 0, 0, 6 });

        myl::i32vec3 c = a;
        c += b;
        CHECK(c == myl::i32vec3{ 3, 6, 6 });

        c = a;
        c -= b;
        CHECK(c == myl::i32vec3{ 1, 2, 6 });

        c = a;
        c *= b;
        CHECK(c == myl::i32vec3{ 2, 8, 6 });

        c = a;
        c /= b;
        CHECK(c == myl::i32vec3{ 2, 2, 6 });

        c = a;
        c %= b;
        CHECK(c == myl::i32vec3{ 0, 0, 6 });
    }
    SECTION("vec3 arithmetic") {
        myl::i32vec3 a{ 2, 4, 6 };
        myl::i32vec3 b{ 1, 2, 3 };

        CHECK(a + b == myl::i32vec3{ 3, 6, 9 });
        CHECK(a - b == myl::i32vec3{ 1, 2, 3 });
        CHECK(a * b == myl::i32vec3{ 2, 8, 18 });
        CHECK(a / b == myl::i32vec3{ 2, 2, 2 });
        CHECK(a % b == myl::i32vec3{ 0, 0, 0 });

        myl::i32vec3 c = a;
        c += b;
        CHECK(c == myl::i32vec3{ 3, 6, 9 });

        c = a;
        c -= b;
        CHECK(c == myl::i32vec3{ 1, 2, 3 });

        c = a;
        c *= b;
        CHECK(c == myl::i32vec3{ 2, 8, 18 });

        c = a;
        c /= b;
        CHECK(c == myl::i32vec3{ 2, 2, 2 });

        c = a;
        c %= b;
        CHECK(c == myl::i32vec3{ 0, 0, 0 });
    }
    SECTION("comparision") {
        CHECK(myl::i32vec3{ 5, 3, 7 } == myl::i32vec3{ 5, 3, 7 });
        CHECK(myl::i32vec3{ 5, 2, 7 } != myl::i32vec3{ 5, 3, 3 });
    }
}

TEST_CASE("myl::cross", "[vec3.hpp]") {
    myl::i32vec3 a = myl::cross<myl::i32>({ 7, 6, 1 }, { -2, 3, 5 });
    bool result = a.x == 27 && a.y == -37 && a.z == 33;
    CHECK(result);
}
