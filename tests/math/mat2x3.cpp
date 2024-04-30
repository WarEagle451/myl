#include <myl/math/mat2x3.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("mat2x3", "[mat2x3.hpp]") {
    SECTION("constructor") {
        SECTION("default") {
            CHECK(myl::i32mat2x3() == myl::i32mat2x3(0));
        }
        SECTION("copy") {
            myl::i32mat2x3 m(
                0, 1,
                2, 3,
                4, 5
            );

            auto t = m;
            CHECK(t == m);
        }
        SECTION("move") {
            myl::i32mat2x3 m(
                0, 1,
                2, 3,
                4, 5
            );

            myl::i32mat2x3 t = std::move(m);
            CHECK(t == myl::i32mat2x3(
                0, 1,
                2, 3,
                4, 5
            ));
        }
        SECTION("scalar") {
            myl::i32mat2x3 m(
                2, 2,
                2, 2,
                2, 2
            );

            CHECK(myl::i32mat2x3(2) == m);
        }
        SECTION("copy scalars") {
            myl::i32mat2x3 m(
                0, 1,
                4, 5,
                8, 9
            );
            CHECK(myl::i32mat2x3(
                { 0, 4, 8 },
                { 1, 5, 9 }
            ) == m);
        }
        SECTION("move scalars") {
            myl::i32
                a = 0, b = 1,
                c = 2, d = 3,
                e = 4, f = 5;

            myl::i32mat2x3 t(
                a, b,
                c, d,
                e, f
            );

            CHECK(myl::i32mat2x3(
                std::move(a), std::move(b),
                std::move(c), std::move(d),
                std::move(e), std::move(f)
            ) == t);
        }
        SECTION("copy columns") {
            myl::i32vec3 a{ 0, 1, 2 }, b{ 3, 4, 5 };
            myl::i32mat2x3 t(a, b);
            CHECK(myl::i32mat2x3(
                0, 3,
                1, 4,
                2, 5
            ) == t);
        }
        SECTION("move columns") {
            myl::i32vec3 a{ 0, 1, 2 }, b{ 3, 4, 5 };
            myl::i32mat2x3 t(a, b);
            CHECK(myl::i32mat2x3(std::move(a), std::move(b)) == t);
        }
    }
    SECTION("assignment") {
        SECTION("copy") {
            myl::i32mat2x3 m(
                0, 1,
                2, 3,
                4, 5
            );

            auto t = m;
            CHECK(t == m);
        }
        SECTION("move") {
            myl::i32mat2x3 m(
                0, 1,
                2, 3,
                4, 5
            );

            myl::i32mat2x3 t = std::move(m);
            CHECK(t == myl::i32mat2x3(
                0, 1,
                2, 3,
                4, 5
            ));
        }
    }
    SECTION("comparision") {
        myl::i32mat2x3 m(
            0, 1,
            2, 3,
            4, 5
        );

        decltype(m) t = -m;

        CHECK(m == m);
        CHECK_FALSE(m == t);
    }
    SECTION("bool conversion") {
        CHECK(bool(myl::i32mat2x3(2)));
        CHECK_FALSE(bool(myl::i32mat2x3(0)));
    }
    SECTION("index") {
        SECTION("column") {
            myl::i32vec3 a{ 1, 2, 3 }, b{ 4, 5, 6 };
            myl::i32mat2x3 t(a, b);
            CHECK(t[0] == a);
            CHECK(t[1] == b);
        }
        SECTION("multi-dimension") {
            myl::i32mat2x3 m(
                0, 1,
                2, 3,
                4, 5
            );

            CHECK(m[0][0] == 0);
            CHECK(m[1][0] == 1);

            CHECK(m[0][1] == 2);
            CHECK(m[1][1] == 3);

            CHECK(m[0][2] == 4);
            CHECK(m[1][2] == 5);
        }
    }
    SECTION("negation") {
        myl::i32mat2x3 m(
            0, 1,
            2, 3,
            4, 5
        );

        myl::i32mat2x3 t(
            -0, -1,
            -2, -3,
            -4, -5
        );

        CHECK(-m == t);
    }
    SECTION("scalar arithmetic") {
        myl::i32mat2x3 t(
            0, -2,
            8, 12,
            14, 16
        );

        myl::i32mat2x3 add(
            2, 0,
            10, 14,
            16, 18
        );
        myl::i32mat2x3 sub(
            -2, -4,
            6, 10,
            12, 14
        );
        myl::i32mat2x3 mul(
            0, -4,
            16, 24,
            28, 32
        );
        myl::i32mat2x3 div(
            0, -1,
            4, 6,
            7, 8
        );
        myl::i32mat2x3 mod(
            0, -2 % 3,
            2, 0,
            2, 1
        );

        CHECK(t + 2 == add);
        CHECK(t - 2 == sub);
        CHECK(t * 2 == mul);
        CHECK(t / 2 == div);
        CHECK(t % 3 == mod);

        myl::i32mat2x3 m = t;
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
    SECTION("vec2 arithmetic") {
        myl::i32mat2x3 m(
            0, 1,
            4, 5,
            8, 9
        );

        myl::i32vec2 v{ 2, 3 };
        CHECK(m * v == myl::i32vec3{ 3, 23, 43 });
    }
    SECTION("mat2x3 arithmetic") {
        myl::i32mat2x3 a(
            1, 2,
            3, 7,
            5, 7
        );

        myl::i32mat2x3 b(
            3, 6,
            9, 1,
            2, 0
        );

        myl::i32mat2x3 add(
            4, 8,
            12, 8,
            7, 7
        );

        myl::i32mat2x3 sub(
            -2, -4,
            -6, 6,
            3, 7
        );

        CHECK(a + b == add);
        CHECK(a - b == sub);

        myl::i32mat2x3 c = a;
        c += b;
        CHECK(c == add);

        c = a;
        c -= b;
        CHECK(c == sub);
    }
}
