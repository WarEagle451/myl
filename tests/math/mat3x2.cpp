#include <myl/math/mat3x2.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("mat3x2", "[mat3x2.hpp]") {
    SECTION("constructor") {
        SECTION("default") {
            CHECK(myl::i32mat3x2() == myl::i32mat3x2(0));
        }
        SECTION("copy") {
            myl::i32mat3x2 m(
                0, 1, 2,
                3, 4, 5
            );

            auto t = m;
            CHECK(t == m);
        }
        SECTION("move") {
            myl::i32mat3x2 m(
                0, 1, 2,
                3, 4, 5
            );

            myl::i32mat3x2 t = std::move(m);
            CHECK(t == myl::i32mat3x2(
                0, 1, 2,
                3, 4, 5
            ));
        }
        SECTION("scalar") {
            myl::i32mat3x2 m(
                2, 2, 2,
                2, 2, 2
            );

            CHECK(myl::i32mat3x2(2) == m);
        }
        SECTION("copy scalars") {
            myl::i32mat3x2 m(
                0, 1, 2,
                4, 5, 6
            );
            CHECK(myl::i32mat3x2(
                { 0, 4 },
                { 1, 5 },
                { 2, 6 }
            ) == m);
        }
        SECTION("move scalars") {
            myl::i32
                a = 0, b = 1, c = 2,
                d = 3, e = 4, f = 5;

            myl::i32mat3x2 t(
                a, b, c,
                d, e, f
            );

            CHECK(myl::i32mat3x2(
                std::move(a), std::move(b), std::move(c),
                std::move(d), std::move(e), std::move(f)
            ) == t);
        }
        SECTION("copy columns") {
            myl::i32vec2 a{ 0, 1 }, b{ 2, 3 }, c{ 4, 5 };
            myl::i32mat3x2 t(a, b, c);
            CHECK(myl::i32mat3x2(
                0, 2, 4,
                1, 3, 5
            ) == t);
        }
        SECTION("move columns") {
            myl::i32vec2 a{ 0, 1 }, b{ 2, 3 }, c{ 4, 5 };
            myl::i32mat3x2 t(a, b, c);
            CHECK(myl::i32mat3x2(std::move(a), std::move(b), std::move(c)) == t);
        }
    }
    SECTION("assignment") {
        SECTION("copy") {
            myl::i32mat3x2 m(
                0, 1, 2,
                3, 4, 5
            );

            auto t = m;
            CHECK(t == m);
        }
        SECTION("move") {
            myl::i32mat3x2 m(
                0, 1, 2,
                3, 4, 5
            );

            myl::i32mat3x2 t = std::move(m);
            CHECK(t == myl::i32mat3x2(
                0, 1, 2,
                3, 4, 5
            ));
        }
    }
    SECTION("comparision") {
        myl::i32mat3x2 m(
            0, 1, 2,
            3, 4, 5
        );

        decltype(m) t = -m;

        CHECK(m == m);
        CHECK_FALSE(m == t);
    }
    SECTION("bool conversion") {
        CHECK(bool(myl::i32mat3x2(2)));
        CHECK_FALSE(bool(myl::i32mat3x2(0)));
    }
    SECTION("index") {
        SECTION("column") {
            myl::i32vec2 a{ 1, 2 }, b{ 3, 4 }, c{ 5, 6 };
            myl::i32mat3x2 t(a, b, c);
            CHECK(t[0] == a);
            CHECK(t[1] == b);
            CHECK(t[2] == c);
        }
        SECTION("multi-dimension") {
            myl::i32mat3x2 m(
                0, 1, 2,
                3, 4, 5
            );

            CHECK(m[0][0] == 0);
            CHECK(m[1][0] == 1);
            CHECK(m[2][0] == 2);

            CHECK(m[0][1] == 3);
            CHECK(m[1][1] == 4);
            CHECK(m[2][1] == 5);
        }
    }
    SECTION("negation") {
        myl::i32mat3x2 m(
            0, 1, 2,
            3, 4, 5
        );

        myl::i32mat3x2 t(
            -0, -1, -2,
            -3, -4, -5
        );

        CHECK(-m == t);
    }
    SECTION("scalar arithmetic") {
        myl::i32mat3x2 t(
            0, -2, 2,
            8, 12, 6
        );

        myl::i32mat3x2 add(
            2, 0, 4,
            10, 14, 8
        );
        myl::i32mat3x2 sub(
            -2, -4, 0,
            6, 10, 4
        );
        myl::i32mat3x2 mul(
            0, -4, 4,
            16, 24, 12
        );
        myl::i32mat3x2 div(
            0, -1, 1,
            4, 6, 3
        );
        myl::i32mat3x2 mod(
            0, 1, 2,
            2, 0, 0
        );

        CHECK(t + 2 == add);
        CHECK(t - 2 == sub);
        CHECK(t * 2 == mul);
        CHECK(t / 2 == div);
        CHECK(t % 3 == mod);

        myl::i32mat3x2 m = t;
        m += 2;
        CHECK(m == add);

        m = t;
        m -= 2;
        CHECK(m == sub);

        m = t;
        m *= 2;
        CHECK(m == mul);

        m = t;
        m /= 2;
        CHECK(m == div);

        m = t;
        m %= 3;
        CHECK(m == mod);
    }
    SECTION("vec3 arithmetic") {
        myl::i32mat3x2 m(
            0, 1, 2,
            3, 4, 5
        );

        myl::i32vec3 v{ 2, 3, 4 };
        CHECK(m * v == myl::i32vec2{ 11, 38 });
    }
    SECTION("mat3x2 arithmetic") {
        myl::i32mat3x2 a(
            1, 2, 9,
            3, 7, 1
        );

        myl::i32mat3x2 b(
            3, 6, 6,
            9, 1, 4
        );

        myl::i32mat3x2 add(
            0
        );

        myl::i32mat3x2 sub(
            0
        );

        CHECK(a + b == add);
        CHECK(a - b == sub);

        myl::i32mat3x2 c = a;
        c += b;
        CHECK(c == add);

        c = a;
        c += b;
        CHECK(c == sub);
    }
}
