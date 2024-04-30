#include <myl/math/mat2x2.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("mat2x2", "[mat2x2.hpp]") {
    SECTION("indentity") {
        myl::i32mat2x2 t(
            1, 0,
            0, 1
        );

        CHECK(myl::i32mat2x2::identity() == t);
    }
    SECTION("constructor") {
        SECTION("default") {
            CHECK(myl::i32mat2x2() == myl::i32mat2x2(0));
        }
        SECTION("copy") {
            myl::i32mat2x2 m(
                1, 2,
                3, 4
            );

            myl::i32mat2x2 t = m;
            CHECK(m == t);
        }
        SECTION("move") {
            myl::i32mat2x2 m(
                1, 2,
                3, 4
            );

            myl::i32mat2x2 t = std::move(m);
            CHECK(t == myl::i32mat2x2(
                1, 2,
                3, 4
            ));
        }
        SECTION("scalar") {
            myl::i32mat2x2 t(
                2, 2,
                2, 2
            );

            CHECK(myl::i32mat2x2(2) == t);
        }
        SECTION("copy scalars") {
            myl::i32mat2x2 t(
                7, 2,
                5, 6
            );
            CHECK(myl::i32mat2x2(
                { 7, 5 },
                { 2, 6 }
            ) == t);
        }
        SECTION("move scalars") {
            myl::i32 a = 4, b = 5, c = 7, d = 9;
            myl::i32mat2x2 t(
                a, b,
                c, d
            );
            CHECK(myl::i32mat2x2(
                std::move(a), std::move(b),
                std::move(c), std::move(d)
            ) == t);
        }
        SECTION("copy columns") {
            myl::i32vec2 a{ 1, 2 }, b{ 3, 4 };
            myl::i32mat2x2 t(a, b);
            CHECK(myl::i32mat2x2(
                1, 3,
                2, 4) == t);
        }
        SECTION("move columns") {
            myl::i32vec2 a{ 1, 2 }, b{ 3, 4 };
            myl::i32mat2x2 t(a, b);
            CHECK(myl::i32mat2x2(std::move(a), std::move(b)) == t);
        }
    }
    SECTION("assignment") {
        SECTION("copy") {
            myl::i32mat2x2 m(
                1, 2,
                3, 4
            );

            myl::i32mat2x2 t = m;
            CHECK(t == m);
        }
        SECTION("move") {
            myl::i32mat2x2 m(
                1, 2,
                3, 4
            );
            myl::i32mat2x2 t = std::move(m);
            CHECK(t == myl::i32mat2x2(
                1, 2,
                3, 4
            ));
        }
    }
    SECTION("comparision") {
        myl::i32mat2x2 m(
            0, 1,
            3, 2
        );

        myl::i32mat2x2 t(
            7, 2,
            5, 6
        );

        CHECK(m == m);
        CHECK_FALSE(m == t);
    }
    SECTION("bool conversion") {
        CHECK(bool(myl::i32mat2x2::identity()));
        CHECK_FALSE(bool(myl::i32mat2x2(0)));
    }
    SECTION("index") {
        SECTION("column") {
            myl::i32vec2 a{ 1, 2 }, b{ 3, 4 };
            myl::i32mat2x2 t(a, b);
            CHECK(t[0] == a);
            CHECK(t[1] == b);
        }
        SECTION("multi-dimension") {
            myl::i32mat2x2 m(
                7, 2,
                5, 6
            );

            CHECK(m[0][0] == 7);
            CHECK(m[0][1] == 5);
            CHECK(m[1][0] == 2);
            CHECK(m[1][1] == 6);
        }
    }
    SECTION("negation") {
        myl::i32mat2x2 m(
            -7, 2,
            0, 6
        );
        myl::i32mat2x2 t(
            7, -2,
            0, -6
        );
        CHECK(-m == t);
    }
    SECTION("scalar arithmetic") {
        myl::i32mat2x2 t(
            4, -2,
            0, 6
        );

        CHECK(t + 2 == myl::i32mat2x2(6, 0, 2, 8));
        CHECK(t - 2 == myl::i32mat2x2(2, -4, -2, 4));
        CHECK(t * 2 == myl::i32mat2x2(8, -4, 0, 12));
        CHECK(t / 2 == myl::i32mat2x2(2, -1, 0, 3));
        CHECK(t % 3 == myl::i32mat2x2(1, -2, 0, 0));

        myl::i32mat2x2 m = t;
        m += 2;
        CHECK(m == myl::i32mat2x2(6, 0, 2, 8));

        m = t;
        m -= 2;
        CHECK(m == myl::i32mat2x2(2, -4, -2, 4));

        m = t;
        m *= 2;
        CHECK(m == myl::i32mat2x2(8, -4, 0, 12));

        m = t;
        m /= 2;
        CHECK(m == myl::i32mat2x2(2, -1, 0, 3));

        m = t;
        m %= 3;
        CHECK(m == myl::i32mat2x2(1, -2, 0, 0));
    }
    SECTION("vec2 arithmetic") {
        myl::i32mat2x2 a(
            4, -2,
            1, 6
        );

        myl::i32vec2 b{ 3, 6 };

        CHECK(a * b == myl::i32vec2{ 0, 39 });
    }
    SECTION("mat2x2 arithmetic") {
        myl::i32mat2x2 a(
            4, -2,
            0, 6
        );

        myl::i32mat2x2 b(
            -2, -1,
            0, 3
        );

        myl::i32mat2x2 add(
            2, -3,
            0, 9
        );

        myl::i32mat2x2 sub(
            6, -1,
            0, 3
        );

        myl::i32mat2x2 mul(
            -8, -10,
            0, 18
        );

        myl::i32mat2x2 div( /// MYTODO:
            3
        );

        CHECK(a + b == add);
        CHECK(a - b == sub);
        CHECK(a * b == mul);
        CHECK(a / b == div);

        myl::i32mat2x2 c = a;
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
