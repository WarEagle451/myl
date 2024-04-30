#include <myl/math/mat3x3.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("mat3x3", "[mat3x3.hpp]") {
    SECTION("indentity") {
        CHECK(myl::i32mat3x3::identity() == myl::i32mat3x3(
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
        ));
    }
    SECTION("constructor") {
        SECTION("default") {
            CHECK(myl::i32mat3x3() == myl::i32mat3x3(0));
        }
        SECTION("copy") {
            myl::i32mat3x3 m(
                1, 2, 3,
                4, 5, 6,
                7, 8, 9 
            );

            myl::i32mat3x3 t = m;
            CHECK(m == t);
        }
        SECTION("move") {
            myl::i32mat3x3 m(
                1, 2, 3,
                4, 5, 6,
                7, 8, 9
            );

            myl::i32mat3x3 t = std::move(m);
            CHECK(t == myl::i32mat3x3(
                1, 2, 3,
                4, 5, 6,
                7, 8, 9
            ));
        }
        SECTION("scalar") {
            myl::i32mat3x3 m(
                2, 2, 2,
                2, 2, 2,
                2, 2, 2
            );

            CHECK(myl::i32mat3x3(2) == m);
        }
        SECTION("copy scalars") {
            myl::i32mat3x3 t(
                1, 2, 3,
                4, 5, 6,
                7, 8, 9
            );
            CHECK(myl::i32mat3x3(
                { 1, 4, 7 },
                { 2, 5, 8 },
                { 3, 6, 9 }
            ) == t);
        }
        SECTION("move scalars") {
            myl::i32 a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7, h = 8, i = 9;
            myl::i32mat3x3 t(
                a, b, c,
                d, e, f,
                g, h, i
            );
            CHECK(myl::i32mat3x3(
                std::move(a), std::move(b), std::move(c),
                std::move(d), std::move(e), std::move(f),
                std::move(g), std::move(h), std::move(i)
            ) == t);
        }
        SECTION("copy columns") {
            myl::i32vec3 a{ 1, 2, 3 }, b{ 4, 5, 6 }, c{ 7, 8, 9 };
            myl::i32mat3x3 t(a, b, c);
            CHECK(myl::i32mat3x3(
                1, 4, 7,
                2, 5, 8,
                3, 6, 9) == t);
        }
        SECTION("move columns") {
            myl::i32vec3 a{ 1, 2, 3 }, b{ 4, 5, 6 }, c{ 7, 8, 9 };
            myl::i32mat3x3 t(a, b, c);
            CHECK(myl::i32mat3x3(std::move(a), std::move(b), std::move(c)) == t);
        }
    }
    SECTION("assignment") {
        SECTION("copy") {
            myl::i32mat3x3 t(
                1, 2, 3,
                4, 5, 6,
                7, 8, 9
            );

            myl::i32mat3x3 m = t;
            CHECK(t == m);
        }
        SECTION("move") {
            myl::i32mat3x3 t(
                1, 2, 3,
                4, 5, 6,
                7, 8, 9
            );

            myl::i32mat3x3 m = std::move(t);
            CHECK(m == myl::i32mat3x3(
                1, 2, 3,
                4, 5, 6,
                7, 8, 9
            ));
        }
    }
    SECTION("comparision") {
        myl::i32mat3x3 t(
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
        );

        myl::i32mat3x3 m(
            2, 3, 4,
            9, 8, 5,
            1, 7, 6
        );

        CHECK(m == m);
        CHECK_FALSE(m == t);
    }
    SECTION("bool conversion") {
        CHECK(bool(myl::i32mat3x3::identity()));
        CHECK_FALSE(bool(myl::i32mat3x3(0)));
    }
    SECTION("index") {
        SECTION("column") {
            myl::i32vec3 a{ 1, 2, 3 }, b{ 4, 5, 6 }, c{ 7, 8, 9 };
            myl::i32mat3x3 t(a, b, c);
            CHECK(t[0] == a);
            CHECK(t[1] == b);
            CHECK(t[2] == c);
        }
        SECTION("multi-dimension") {
            myl::i32mat3x3 m(
                1, 2, 3,
                4, 5, 6,
                7, 8, 9
            );

            CHECK(m[0][0] == 1);
            CHECK(m[1][0] == 2);
            CHECK(m[2][0] == 3);
            CHECK(m[0][1] == 4);
            CHECK(m[1][1] == 5);
            CHECK(m[2][1] == 6);
            CHECK(m[0][2] == 7);
            CHECK(m[1][2] == 8);
            CHECK(m[2][2] == 9);
        }
    }
    SECTION("negation") {
        myl::i32mat3x3 m(
            -1, 0, 3,
            4, 5, 6,
            7, 8, 9
        );

        myl::i32mat3x3 t(
            1, 0, -3,
            -4, -5, -6,
            -7, -8, -9
        );

        CHECK(-m == t);
    }
    SECTION("scalar arithmetic") {
        myl::i32mat3x3 t(
            0, -2, 2,
            4, 8, 12,
            10, 6, 14
        );

        CHECK(t + 2 == myl::i32mat3x3(2, 0, 4, 6, 10, 14, 12, 8, 16));
        CHECK(t - 2 == myl::i32mat3x3(-2, -4, 0, 2, 6, 10, 8, 4, 12));
        CHECK(t * 2 == myl::i32mat3x3(0, -4, 4, 8, 16, 24, 20, 12, 28));
        CHECK(t / 2 == myl::i32mat3x3(0, -1, 1, 2, 4, 6, 5, 3, 7));
        CHECK(t % 3 == myl::i32mat3x3(0, -2 % 3, 2, 1, 2, 0, 1, 0, 2));

        myl::i32mat3x3 m = t;
        m += 2;
        CHECK(m == myl::i32mat3x3(2, 0, 4, 6, 10, 14, 12, 8, 16));

        m = t;
        m -= 2;
        CHECK(m == myl::i32mat3x3(-2, -4, 0, 2, 6, 10, 8, 4, 12));

        m = t;
        m *= 2;
        CHECK(m == myl::i32mat3x3(0, -4, 4, 8, 16, 24, 20, 12, 28));

        m = t;
        m /= 2;
        CHECK(m == myl::i32mat3x3(0, -1, 1, 2, 4, 6, 5, 3, 7));

        m = t;
        m %= 3;
        CHECK(m == myl::i32mat3x3(0, -2 % 3, 2, 1, 2, 0, 1, 0, 2));
    }
    SECTION("vec3 arithmetic") {
        myl::i32mat3x3 t(
            0, -2, 2,
            4, 8, 12,
            10, 6, 14
        );

        myl::i32mat3x3::row_type v{ 2, 3, 4 };

        CHECK(t * v == myl::i32mat3x3::row_type{ 2, 80, 94 });
    }
    SECTION("mat3x3 arithmetic") {
        myl::i32mat3x3 a(
            0, -2, 2,
            4, 8, 12,
            10, 6, 14
        );

        myl::i32mat3x3 b(
            2, -1, 1,
            2, 4, 2,
            5, 3, 7
        );

        myl::i32mat3x3 add(
            2, -3, 3,
            6, 12, 14,
            15, 9, 21
        );

        myl::i32mat3x3 sub(
            -2, -1, 1,
            2, 4, 10,
            5, 3, 7
        );

        myl::i32mat3x3 mul(
            6, -2, 10,
            84, 64, 104,
            102, 56, 120
        );

        myl::i32mat3x3 div( /// MYTODO:
            3
        );

        CHECK(a + b == add);
        CHECK(a - b == sub);
        CHECK(a * b == mul);
        CHECK(a / b == div);

        myl::i32mat3x3 c = a;
        c += b;
        CHECK(c == add);

        c = a;
        c -= b;
        CHECK(c == sub);

        c = a;
        c *= b;
        CHECK(c == mul);

        c = a;
        c /= b;
        CHECK(c == div);
    }
}
