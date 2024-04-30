#include <myl/math/mat3x4.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("mat3x4", "[mat3x4.hpp]") {
    SECTION("constructor") {
        SECTION("default") {
            CHECK(myl::i32mat3x4() == myl::i32mat3x4(0));
        }
        SECTION("copy") {
            myl::i32mat3x4 m(
                0, 1, 2,
                3, 4, 5,
                6, 7, 8,
                9, 10, 11
            );

            auto t = m;
            CHECK(t == m);
        }
        SECTION("move") {
            myl::i32mat3x4 m(
                0, 1, 2,
                3, 4, 5,
                6, 7, 8,
                9, 10, 11
            );

            myl::i32mat3x4 t = std::move(m);
            CHECK(t == myl::i32mat3x4(
                0, 1, 2,
                3, 4, 5,
                6, 7, 8,
                9, 10, 11
            ));
        }
        SECTION("scalar") {
            myl::i32mat3x4 m(
                2, 2, 2,
                2, 2, 2,
                2, 2, 2,
                2, 2, 2
            );

            CHECK(myl::i32mat3x4(2) == m);
        }
        SECTION("copy scalars") {
            myl::i32mat3x4 m(
                0, 1, 2,
                4, 5, 6,
                8, 9, 10,
                12, 13, 14
            );
            CHECK(myl::i32mat3x4(
                { 0, 4, 8, 12 },
                { 1, 5, 9, 13 },
                { 2, 6, 10, 14 }
            ) == m);
        }
        SECTION("move scalars") {
            myl::i32
                a = 0, b = 1, c = 2,
                d = 3, e = 4, f = 5,
                g = 6, h = 7, i = 8,
                j = 9, k = 10, l = 11;

            myl::i32mat3x4 t(
                a, b, c,
                d, e, f,
                g, h, i,
                j, k, l
            );

            CHECK(myl::i32mat3x4(
                std::move(a), std::move(b), std::move(c),
                std::move(d), std::move(e), std::move(f),
                std::move(g), std::move(h), std::move(i),
                std::move(j), std::move(k), std::move(l)
            ) == t);
        }
        SECTION("copy columns") {
            myl::i32vec4 a{ 0, 1, 2, 3 }, b{ 4, 5, 6, 7 }, c{ 8, 9, 0, -1 };
            myl::i32mat3x4 t(a, b, c);
            CHECK(myl::i32mat3x4(
                0, 4, 8,
                1, 5, 9,
                2, 6, 0,
                3, 7, -1
            ) == t);
        }
        SECTION("move columns") {
            myl::i32vec4 a{ 0, 1, 2, 3 }, b{ 4, 5, 6, 7 }, c{ 8, 9, 0, -1 };
            myl::i32mat3x4 t(a, b, c);
            CHECK(myl::i32mat3x4(std::move(a), std::move(b), std::move(c)) == t);
        }
    }
    SECTION("assignment") {
        SECTION("copy") {
            myl::i32mat3x4 m(
                0, 1, 2,
                3, 4, 5,
                6, 7, 8,
                9, 10, 11
            );

            auto t = m;
            CHECK(t == m);
        }
        SECTION("move") {
            myl::i32mat3x4 m(
                0, 1, 2,
                3, 4, 5,
                6, 7, 8,
                9, 10, 11
            );

            myl::i32mat3x4 t = std::move(m);
            CHECK(t == myl::i32mat3x4(
                0, 1, 2,
                3, 4, 5,
                6, 7, 8,
                9, 10, 11
            ));
        }
    }
    SECTION("comparision") {
        myl::i32mat3x4 m(
            0, 1, 2,
            3, 4, 5,
            6, 7, 8,
            9, 10, 11
        );

        decltype(m) t = -m;

        CHECK(m == m);
        CHECK_FALSE(m == t);
    }
    SECTION("bool conversion") {
        CHECK(bool(myl::i32mat3x4(2)));
        CHECK_FALSE(bool(myl::i32mat3x4(0)));
    }
    SECTION("index") {
        SECTION("column") {
            myl::i32vec4 a{ 1, 2, 3, 4 }, b{ 5, 6, 7, 8 }, c{ 9, 0, -1, -2 };
            myl::i32mat3x4 t(a, b, c);
            CHECK(t[0] == a);
            CHECK(t[1] == b);
            CHECK(t[2] == c);
        }
        SECTION("multi-dimension") {
            myl::i32mat3x4 m(
                0, 1, 2,
                3, 4, 5,
                6, 7, 8,
                9, 10, 11
            );

            CHECK(m[0][0] == 0);
            CHECK(m[1][0] == 1);
            CHECK(m[2][0] == 2);

            CHECK(m[0][1] == 3);
            CHECK(m[1][1] == 4);
            CHECK(m[2][1] == 5);

            CHECK(m[0][2] == 6);
            CHECK(m[1][2] == 7);
            CHECK(m[2][2] == 8);

            CHECK(m[0][3] == 9);
            CHECK(m[1][3] == 10);
            CHECK(m[2][3] == 11);
        }
    }
    SECTION("negation") {
        myl::i32mat3x4 m(
            0, 1, 2,
            3, 4, 5,
            6, 7, 8,
            9, 10, 11
        );

        myl::i32mat3x4 t(
            -0, -1, -2,
            -3, -4, -5,
            -6, -7, -8,
            -9, -10, -11
        );

        CHECK(-m == t);
    }
    SECTION("scalar arithmetic") {
        myl::i32mat3x4 t(
            0, -2, 2,
            8, 12, 6,
            14, 16, 20,
            -8, -10, -6
        );

        myl::i32mat3x4 add(
            2, 0, 4,
            10, 14, 8,
            16, 18, 22,
            -6, -8, -4
        );
        myl::i32mat3x4 sub(
            -2, -4, 0,
            6, 10, 4,
            12, 14, 18,
            -10, -12, -8
        );
        myl::i32mat3x4 mul(
            0, -4, 4,
            16, 24, 12,
            28, 32, 40,
            -16, -20, -12
        );
        myl::i32mat3x4 div(
            0, -1, 1,
            4, 6, 3,
            7, 8, 10,
            -4, -5, -3
        );
        myl::i32mat3x4 mod(
            0, -2 % 3, 2,
            2, 0, 0,
            2, 1, 2,
            -8 % 3, -10 % 3, -6 % 3
        );

        CHECK(t + 2 == add);
        CHECK(t - 2 == sub);
        CHECK(t * 2 == mul);
        CHECK(t / 2 == div);
        CHECK(t % 3 == mod);

        myl::i32mat3x4 m = t;
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
        myl::i32mat3x4 m(
            0, 1, 2,
            4, 5, 6,
            8, 9, 10,
            12, 13, 14
        );

        myl::i32vec3 v{ 2, 3, 4 };
        CHECK(m * v == myl::i32vec4{ 11, 47, 83, 119 });
    }
    SECTION("mat3x4 arithmetic") {
        myl::i32mat3x4 a(
            1, 2, 9,
            3, 7, 1,
            5, 7, 9,
            8, 9, 1
        );

        myl::i32mat3x4 b(
            3, 6, 6,
            9, 1, 4,
            2, 0, 8,
            3, 9, 5
        );

        myl::i32mat3x4 add(
            4, 8, 15,
            12, 8, 5,
            7, 7, 17,
            11, 18, 6
        );

        myl::i32mat3x4 sub(
            -2, -4, 3,
            -6, 6, -3,
            3, 7, 1,
            5, 0, -4
        );

        CHECK(a + b == add);
        CHECK(a - b == sub);

        myl::i32mat3x4 c = a;
        c += b;
        CHECK(c == add);

        c = a;
        c -= b;
        CHECK(c == sub);
    }
}
