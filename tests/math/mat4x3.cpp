#include <myl/math/mat4x3.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("mat4x3", "[mat4x3.hpp]") {
    SECTION("constructor") {
        SECTION("default") {
            CHECK(myl::i32mat4x3() == myl::i32mat4x3(0));
        }
        SECTION("copy") {
            myl::i32mat4x3 m(
                0, 1, 2, 3,
                4, 5, 6, 7,
                8, 9, 10, 11
            );

            auto t = m;
            CHECK(t == m);
        }
        SECTION("move") {
            myl::i32mat4x3 m(
                0, 1, 2, 3,
                4, 5, 6, 7,
                8, 9, 10, 11
            );

            myl::i32mat4x3 t = std::move(m);
            CHECK(t == myl::i32mat4x3(
                0, 1, 2, 3,
                4, 5, 6, 7,
                8, 9, 10, 11
            ));
        }
        SECTION("scalar") {
            myl::i32mat4x3 m(
                2, 2, 2, 2,
                2, 2, 2, 2,
                2, 2, 2, 2
            );

            CHECK(myl::i32mat4x3(2) == m);
        }
        SECTION("copy scalars") {
            myl::i32mat4x3 m(
                0, 1, 2, 3,
                4, 5, 6, 7,
                8, 9, 10, 11
            );
            CHECK(myl::i32mat4x3(
                { 0, 4, 8 },
                { 1, 5, 9 },
                { 2, 6, 10 },
                { 3, 7, 11 }
            ) == m);
        }
        SECTION("move scalars") {
            myl::i32
                a = 0, b = 1, c = 2, d = 3,
                e = 4, f = 5, g = 6, h = 7,
                i = 8, j = 9, k = 10, l = 11;

            myl::i32mat4x3 t(
                a, b, c, d,
                e, f, g, h,
                i, j, k, l
            );

            CHECK(myl::i32mat4x3(
                std::move(a), std::move(b), std::move(c), std::move(d),
                std::move(e), std::move(f), std::move(g), std::move(h),
                std::move(i), std::move(j), std::move(k), std::move(l)
            ) == t);
        }
        SECTION("copy columns") {
            myl::i32vec3 a{ 0, 1, 2 }, b{ 3, 4, 5 }, c{ 6, 7, 8 }, d{ 9, 0, -1 };
            myl::i32mat4x3 t(a, b, c, d);
            CHECK(myl::i32mat4x3(
                0, 3, 6, 9,
                1, 4, 7, 0,
                2, 5, 8, -1
            ) == t);
        }
        SECTION("move columns") {
            myl::i32vec3 a{ 0, 1, 2 }, b{ 3, 4, 5 }, c{ 6, 7, 8 }, d{ 9, 0, -1 };
            myl::i32mat4x3 t(a, b, c, d);
            CHECK(myl::i32mat4x3(std::move(a), std::move(b), std::move(c), std::move(d)) == t);
        }
    }
    SECTION("assignment") {
        SECTION("copy") {
            myl::i32mat4x3 m(
                0, 1, 2, 3,
                4, 5, 6, 7,
                8, 9, 10, 11
            );

            auto t = m;
            CHECK(t == m);
        }
        SECTION("move") {
            myl::i32mat4x3 m(
                0, 1, 2, 3,
                4, 5, 6, 7,
                8, 9, 10, 11
            );

            myl::i32mat4x3 t = std::move(m);
            CHECK(t == myl::i32mat4x3(
                0, 1, 2, 3,
                4, 5, 6, 7,
                8, 9, 10, 11
            ));
        }
    }
    SECTION("comparision") {
        myl::i32mat4x3 m(
            0, 1, 2, 3,
            4, 5, 6, 7,
            8, 9, 10, 11
        );

        decltype(m) t = -m;

        CHECK(m == m);
        CHECK_FALSE(m == t);
    }
    SECTION("bool conversion") {
        CHECK(bool(myl::i32mat4x3(2)));
        CHECK_FALSE(bool(myl::i32mat4x3(0)));
    }
    SECTION("index") {
        SECTION("column") {
            myl::i32vec3 a{ 1, 2, 3 }, b{ 4, 5, 6 }, c{ 7, 8, 9 }, d{ 0, -1, -2 };
            myl::i32mat4x3 t(a, b, c, d);
            CHECK(t[0] == a);
            CHECK(t[1] == b);
            CHECK(t[2] == c);
            CHECK(t[3] == d);
        }
        SECTION("multi-dimension") {
            myl::i32mat4x3 m(
                0, 1, 2, 3,
                4, 5, 6, 7,
                8, 9, 10, 11
            );

            CHECK(m[0][0] == 0);
            CHECK(m[1][0] == 1);
            CHECK(m[2][0] == 2);
            CHECK(m[3][0] == 3);

            CHECK(m[0][1] == 4);
            CHECK(m[1][1] == 5);
            CHECK(m[2][1] == 6);
            CHECK(m[3][1] == 7);

            CHECK(m[0][2] == 8);
            CHECK(m[1][2] == 9);
            CHECK(m[2][2] == 10);
            CHECK(m[3][2] == 11);
        }
    }
    SECTION("negation") {
        myl::i32mat4x3 m(
            0, 1, 2, 3,
            4, 5, 6, 7,
            8, 9, 10, 11
        );

        myl::i32mat4x3 t(
            -0, -1, -2, -3,
            -4, -5, -6, -7,
            -8, -9, -10, -11
        );

        CHECK(-m == t);
    }
    SECTION("scalar arithmetic") {
        myl::i32mat4x3 t(
            0, -2, 2, 4,
            8, 12, 6, 10,
            14, 16, 20, -4
        );

        myl::i32mat4x3 add(
            2, 0, 4, 6,
            10, 14, 8, 12,
            16, 18, 22, -2
        );
        myl::i32mat4x3 sub(
            -2, -4, 0, 2,
            6, 10, 4, 8,
            12, 14, 18, -6
        );
        myl::i32mat4x3 mul(
            0, -4, 4, 8,
            16, 24, 12, 20,
            28, 32, 40, -8
        );
        myl::i32mat4x3 div(
            0, -1, 1, 2,
            4, 6, 3, 5,
            7, 8, 10, -2
        );
        myl::i32mat4x3 mod(
            0, -2 % 3, 2, 1,
            2, 0, 0, 1,
            2, 1, 2, -4 % 3
        );

        CHECK(t + 2 == add);
        CHECK(t - 2 == sub);
        CHECK(t * 2 == mul);
        CHECK(t / 2 == div);
        CHECK(t % 3 == mod);

        myl::i32mat4x3 m = t;
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
    SECTION("vec4 arithmetic") {
        myl::i32mat4x3 m(
            0, 1, 2, 3,
            4, 5, 6, 7,
            8, 9, 10, 11
        );

        myl::i32vec4 v{ 2, 3, 4, 5 };
        CHECK(m * v == myl::i32vec3{ 26, 82, 138 });
    }
    SECTION("mat4x3 arithmetic") {
        myl::i32mat4x3 a(
            1, 2, 9, 0,
            3, 7, 1, 2,
            5, 7, 9, 2
        );

        myl::i32mat4x3 b(
            3, 6, 6, 7,
            9, 1, 4, 2,
            2, 0, 8, 2
        );

        myl::i32mat4x3 add(
            4, 8, 15, 7,
            12, 8, 5, 4,
            7, 7, 17, 4
        );

        myl::i32mat4x3 sub(
            -2, -4, 3, -7,
            -6, 6, -3, 0,
            3, 7, 1, 0
        );

        CHECK(a + b == add);
        CHECK(a - b == sub);

        myl::i32mat4x3 c = a;
        c += b;
        CHECK(c == add);

        c = a;
        c -= b;
        CHECK(c == sub);
    }
}
