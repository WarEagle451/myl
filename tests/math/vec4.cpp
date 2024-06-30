#include <myl/math/vec2.hpp>
#include <myl/math/vec3.hpp>
#include <myl/math/vec4.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("vec4", "[vec4.hpp]") {
    SECTION("constructor") {
        SECTION("default") {
            CHECK(myl::i32vec4() == myl::i32vec4{ 0, 0, 0, 0 });
        }
        SECTION("copy") {
            myl::i32vec4 a{ 1, 2, 3, 4 };
            myl::i32vec4 b(a);
            CHECK(b == myl::i32vec4{ 1, 2, 3, 4 });
        }
        SECTION("move") {
            myl::i32vec4 a{ 1, 2, 3, 4 };
            myl::i32vec4 b(std::move(a));
            CHECK(b == myl::i32vec4{ 1, 2, 3, 4 });
        }
        SECTION("scalar") {
            CHECK(myl::i32vec4(2) == myl::i32vec4{ 2, 2, 2, 2 });
        }
        SECTION("4 scalar copy") {
            myl::i32 a = 4, b = 5, c = 1, d = 9;
            CHECK(myl::i32vec4(a, b, c, d) == myl::i32vec4{ 4, 5, 1, 9 });
        }
        SECTION("4 scalar move") {
            myl::i32 a = 4, b = 5, c = 1, d = 9;
            CHECK(myl::i32vec4(std::move(a), std::move(b), std::move(c), std::move(d)) == myl::i32vec4{ 4, 5, 1, 9 });
        }
        SECTION("vec2 xy scalar zw") {
            CHECK(myl::i32vec4(myl::i32vec2{ 2, 4 }, 1, 3) == myl::i32vec4{ 2, 4, 1, 3 });
        }
        SECTION("scalar x vec2 yz scalar w") {
            CHECK(myl::i32vec4(1, myl::i32vec2{ 2, 4 }, 3) == myl::i32vec4{ 1, 2, 4, 3 });
        }
        SECTION("scalar xy vec2 zw") {
            CHECK(myl::i32vec4(1, 3, myl::i32vec2{ 2, 4 }) == myl::i32vec4{ 1, 3, 2, 4 });
        }
        SECTION("vec3 xyz scalar w") {
            CHECK(myl::i32vec4(myl::i32vec3{ 2, 4, 3 }, 1) == myl::i32vec4{ 2, 4, 3, 1 });
        }
        SECTION("scalar x vec3 yzw") {
            CHECK(myl::i32vec4(1, myl::i32vec3{ 2, 4, 3 }) == myl::i32vec4{ 1, 2, 4, 3 });
        }
    }
    SECTION("assignment") {
        SECTION("copy") {
            myl::i32vec4 a{ 1, 2, 3, 4 };
            myl::i32vec4 b = a;
            CHECK(a == b);

        }
        SECTION("move") {
            myl::i32vec4 a{ 1, 2, 3, 4 };
            myl::i32vec4 b = std::move(a);
            CHECK(b == myl::i32vec4{ 1, 2, 3, 4 });
        }
    }
    SECTION("bool conversion") {
        CHECK(bool(myl::i32vec4{ 1, 2, 3, 4 }));
        CHECK_FALSE(bool(myl::i32vec4()));
    }
    SECTION("index") {
        {
            myl::i32vec4 a{ 1, 2, 3, 4 };
            myl::i32 b = a[0];
            myl::i32 c = a[1];
            myl::i32 d = a[2];
            myl::i32 e = a[3];
            CHECK(b == 1);
            CHECK(c == 2);
            CHECK(d == 3);
            CHECK(e == 4);
        }
        {
            myl::i32vec4 a{ 1, 2, 3, 4 };
            const myl::i32 b = a[0];
            const myl::i32 c = a[1];
            const myl::i32 d = a[2];
            const myl::i32 e = a[3];
            CHECK(b == 1);
            CHECK(c == 2);
            CHECK(d == 3);
            CHECK(e == 4);
        }
    }
    SECTION("negation") {
        CHECK(-myl::i32vec4{ 4, -5, 1, 0 } == myl::i32vec4{ -4, 5, -1, 0 });
    }
    SECTION("scalar arithmetic") {
        myl::i32vec4 a{ 2, 4, 6, 8 };

        CHECK(a + 2 == myl::i32vec4{ 4, 6, 8, 10 });
        CHECK(a - 2 == myl::i32vec4{ 0, 2, 4, 6 });
        CHECK(a * 2 == myl::i32vec4{ 4, 8, 12, 16 });
        CHECK(a / 2 == myl::i32vec4{ 1, 2, 3, 4 });
        CHECK(a % 3 == myl::i32vec4{ 2, 1, 0, 2 });

        myl::i32vec4 b = a;
        b += 2;
        CHECK(b == myl::i32vec4{ 4, 6, 8, 10 });

        b = a;
        b -= 2;
        CHECK(b == myl::i32vec4{ 0, 2, 4, 6 });

        b = a;
        b *= 2;
        CHECK(b == myl::i32vec4{ 4, 8, 12, 16 });

        b = a;
        b /= 2;
        CHECK(b == myl::i32vec4{ 1, 2, 3, 4 });

        b = a;
        b %= 3;
        CHECK(b == myl::i32vec4{ 2, 1, 0, 2 });
    }
    SECTION("vec2 arithmetic") {
        myl::i32vec4 a{ 2, 4, 6, 8 };
        myl::i32vec2 b{ 1, 2 };

        CHECK(a + b == myl::i32vec4{ 3, 6, 6, 8 });
        CHECK(a - b == myl::i32vec4{ 1, 2, 6, 8 });
        CHECK(a * b == myl::i32vec4{ 2, 8, 6, 8 });
        CHECK(a / b == myl::i32vec4{ 2, 2, 6, 8 });
        CHECK(a % b == myl::i32vec4{ 0, 0, 6, 8 });

        myl::i32vec4 c = a;
        c += b;
        CHECK(c == myl::i32vec4{ 3, 6, 6, 8 });

        c = a;
        c -= b;
        CHECK(c == myl::i32vec4{ 1, 2, 6, 8 });

        c = a;
        c *= b;
        CHECK(c == myl::i32vec4{ 2, 8, 6, 8 });

        c = a;
        c /= b;
        CHECK(c == myl::i32vec4{ 2, 2, 6, 8 });

        c = a;
        c %= b;
        CHECK(c == myl::i32vec4{ 0, 0, 6, 8 });
    }
    SECTION("vec3 arithmetic") {
        myl::i32vec4 a{ 2, 4, 6, 8 };
        myl::i32vec3 b{ 1, 2, 3 };

        CHECK(a + b == myl::i32vec4{ 3, 6, 9, 8 });
        CHECK(a - b == myl::i32vec4{ 1, 2, 3, 8 });
        CHECK(a * b == myl::i32vec4{ 2, 8, 18, 8 });
        CHECK(a / b == myl::i32vec4{ 2, 2, 2, 8 });
        CHECK(a % b == myl::i32vec4{ 0, 0, 0, 8 });

        myl::i32vec4 c = a;
        c += b;
        CHECK(c == myl::i32vec4{ 3, 6, 9, 8 });

        c = a;
        c -= b;
        CHECK(c == myl::i32vec4{ 1, 2, 3, 8 });

        c = a;
        c *= b;
        CHECK(c == myl::i32vec4{ 2, 8, 18, 8 });

        c = a;
        c /= b;
        CHECK(c == myl::i32vec4{ 2, 2, 2, 8 });

        c = a;
        c %= b;
        CHECK(c == myl::i32vec4{ 0, 0, 0, 8 });
    }
    SECTION("vec4 arithmetic") {
        myl::i32vec4 a{ 2, 4, 6, 8 };
        myl::i32vec4 b{ 1, 2, 3, 4 };

        CHECK(a + b == myl::i32vec4{ 3, 6, 9, 12 });
        CHECK(a - b == myl::i32vec4{ 1, 2, 3, 4 });
        CHECK(a * b == myl::i32vec4{ 2, 8, 18, 32 });
        CHECK(a / b == myl::i32vec4{ 2, 2, 2, 2 });
        CHECK(a % b == myl::i32vec4{ 0, 0, 0, 0 });

        myl::i32vec4 c = a;
        c += b;
        CHECK(c == myl::i32vec4{ 3, 6, 9, 12 });

        c = a;
        c -= b;
        CHECK(c == myl::i32vec4{ 1, 2, 3, 4 });

        c = a;
        c *= b;
        CHECK(c == myl::i32vec4{ 2, 8, 18, 32 });

        c = a;
        c /= b;
        CHECK(c == myl::i32vec4{ 2, 2, 2, 2 });

        c = a;
        c %= b;
        CHECK(c == myl::i32vec4{ 0, 0, 0, 0 });
    }
    SECTION("comparision") {
        CHECK(myl::i32vec4{ 5, 3, 7, 2 } == myl::i32vec4{ 5, 3, 7, 2 });
        CHECK(myl::i32vec4{ 5, 2, 7, 2 } != myl::i32vec4{ 5, 3, 3, 2 });
    }
}
