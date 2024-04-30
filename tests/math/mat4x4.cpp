#include <myl/math/mat4x4.hpp>

#include "../utility/matrix_approx.hpp"

#include <catch2/catch_all.hpp>

TEST_CASE("mat4x4", "[mat4x4.hpp]") {
    SECTION("indentity") {
        CHECK(myl::i32mat4x4::identity() == myl::i32mat4x4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ));
    }
    SECTION("constructor") {
        SECTION("default") {
            CHECK(myl::i32mat4x4() == myl::i32mat4x4(0));
        }
        SECTION("copy") {
            myl::i32mat4x4 m(
                0, 1, 2, 3,
                4, 5, 6, 7,
                8, 9, 10, 11,
                12, 13, 14, 15
            );

            auto t = m;
            CHECK(t == m);
        }
        SECTION("move") {
            myl::i32mat4x4 m(
                0, 1, 2, 3,
                4, 5, 6, 7,
                8, 9, 10, 11,
                12, 13, 14, 15
            );

            myl::i32mat4x4 t = std::move(m);
            CHECK(t == myl::i32mat4x4(
                0, 1, 2, 3,
                4, 5, 6, 7,
                8, 9, 10, 11,
                12, 13, 14, 15
            ));
        }
        SECTION("scalar") {
            myl::i32mat4x4 m(
                2, 2, 2, 2,
                2, 2, 2, 2,
                2, 2, 2, 2,
                2, 2, 2, 2
            );

            CHECK(myl::i32mat4x4(2) == m);
        }
        SECTION("copy scalars") {
            myl::i32mat4x4 m(
                0, 1, 2, 3,
                4, 5, 6, 7,
                8, 9, 10, 11,
                12, 13, 14, 15
            );
            CHECK(myl::i32mat4x4(
                { 0, 4, 8, 12 },
                { 1, 5, 9, 13 },
                { 2, 6, 10, 14 },
                { 3, 7, 11, 15 }
            ) == m);
        }
        SECTION("move scalars") {
            myl::i32
                a = 0, b = 1, c = 2, d = 3,
                e = 4, f = 5, g = 6, h = 7,
                i = 8, j = 9, k = 10, l = 11,
                m = 12, n = 13, o = 14, p = 15;

            myl::i32mat4x4 t(
                a, b, c, d,
                e, f, g, h,
                i, j, k, l,
                m, n, o, p
            );

            CHECK(myl::i32mat4x4(
                std::move(a), std::move(b), std::move(c), std::move(d),
                std::move(e), std::move(f), std::move(g), std::move(h),
                std::move(i), std::move(j), std::move(k), std::move(l),
                std::move(m), std::move(n), std::move(o), std::move(p)
            ) == t);
        }
        SECTION("copy columns") {
            myl::i32vec4 a{ 0, 1, 2, 3 }, b{ 4, 5, 6, 7 }, c{ 8, 9, 0, -1 }, d{ -2, -3, -4, -5 };
            myl::i32mat4x4 t(a, b, c, d);
            CHECK(myl::i32mat4x4(
                0, 4, 8, -2,
                1, 5, 9, -3,
                2, 6, 0, -4,
                3, 7, -1, -5
            ) == t);
        }
        SECTION("move columns") {
            myl::i32vec4 a{ 0, 1, 2, 3 }, b{ 4, 5, 6, 7 }, c{ 8, 9, 0, -1 }, d{ -2, -3, -4, -5 };
            myl::i32mat4x4 t(a, b, c, d);
            CHECK(myl::i32mat4x4(std::move(a), std::move(b), std::move(c), std::move(d)) == t);
        }
    }
    SECTION("assignment") {
        SECTION("copy") {
            myl::i32mat4x4 m(
                0, 1, 2, 3,
                4, 5, 6, 7,
                8, 9, 10, 11,
                12, 13, 14, 15
            );

            auto t = m;
            CHECK(t == m);
        }
        SECTION("move") {
            myl::i32mat4x4 m(
                0, 1, 2, 3,
                4, 5, 6, 7,
                8, 9, 10, 11,
                12, 13, 14, 15
            );

            myl::i32mat4x4 t = std::move(m);
            CHECK(t == myl::i32mat4x4(
                0, 1, 2, 3,
                4, 5, 6, 7,
                8, 9, 10, 11,
                12, 13, 14, 15
            ));
        }
    }
    SECTION("comparision") {
        myl::i32mat4x4 m(
            0, 1, 2, 3,
            4, 5, 6, 7,
            8, 9, 10, 11,
            12, 13, 14, 15
        );

        decltype(m) t = -m;

        CHECK(m == m);
        CHECK_FALSE(m == t);
    }
    SECTION("bool conversion") {
        CHECK(bool(myl::i32mat4x4::identity()));
        CHECK_FALSE(bool(myl::i32mat4x4(0)));
    }
    SECTION("index") {
        SECTION("column") {
            myl::i32vec4 a{ 1, 2, 3, 4 }, b{ 5, 6, 7, 8 }, c{ 9, 0, -1, -2 }, d{ -3, -4, -5, -6 };
            myl::i32mat4x4 t(a, b, c, d);
            CHECK(t[0] == a);
            CHECK(t[1] == b);
            CHECK(t[2] == c);
            CHECK(t[3] == d);
        }
        SECTION("multi-dimension") {
            myl::i32mat4x4 m(
                0, 1, 2, 3,
                4, 5, 6, 7,
                8, 9, 10, 11,
                12, 13, 14, 15
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

            CHECK(m[0][3] == 12);
            CHECK(m[1][3] == 13);
            CHECK(m[2][3] == 14);
            CHECK(m[3][3] == 15);
        }
    }
    SECTION("negation") {
        myl::i32mat4x4 m(
            0, 1, 2, 3,
            4, 5, 6, 7,
            8, 9, 10, 11,
            12, 13, 14, 15
        );

        myl::i32mat4x4 t(
            -0, -1, -2, -3,
            -4, -5, -6, -7,
            -8, -9, -10, -11,
            -12, -13, -14, -15
        );

        CHECK(-m == t);
    }
    SECTION("scalar arithmetic") {
        myl::i32mat4x4 t(
            0, -2, 2, 4,
            8, 12, 6, 10,
            14, 16, 20, -4,
            -8, -10, -6, -12
        );

        myl::i32mat4x4 add(
            2, 0, 4, 6,
            10, 14, 8, 12,
            16, 18, 22, -2,
            -6, -8, -4, -10
        );
        myl::i32mat4x4 sub(
            -2, -4, 0, 2,
            6, 10, 4, 8,
            12, 14, 18, -6,
            -10, -12, -8, -14
        );
        myl::i32mat4x4 mul(
            0, -4, 4, 8,
            16, 24, 12, 20,
            28, 32, 40, -8,
            -16, -20, -12, -24
        );
        myl::i32mat4x4 div(
            0, -1, 1, 2,
            4, 6, 3, 5,
            7, 8, 10, -2,
            -4, -5, -3, -6
        );
        myl::i32mat4x4 mod(
            0, -2 % 3, 2, 1,
            2, 0, 0, 1,
            2, 1, 2, -4 % 3,
            -8 % 3, -10 % 3, -6 % 3, -12 % 3
        );

        CHECK(t + 2 == add);
        CHECK(t - 2 == sub);
        CHECK(t * 2 == mul);
        CHECK(t / 2 == div);
        CHECK(t % 3 == mod);

        myl::i32mat4x4 m = t;
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
        myl::i32mat4x4 m(
            0, 1, 2, 3,
            4, 5, 6, 7,
            8, 9, 10, 11,
            12, 13, 14, 15
        );

        myl::i32vec4 v{ 2, 3, 4, 5 };
        CHECK(m * v == myl::i32vec4{ 26, 82, 138, 194 });
    }
    SECTION("mat4x4 arithmetic") {
        myl::i32mat4x4 a(
            1, 2, 9, 0,
            3, 7, 1, 2,
            5, 7, 9, 2,
            8, 9, 1, 3
        );

        myl::i32mat4x4 b(
            3, 6, 6, 7,
            9, 1, 4, 2,
            2, 0, 8, 2,
            3, 9, 5, 6
        );

        myl::i32mat4x4 add(
            4, 8, 15, 7,
            12, 8, 5, 4,
            7, 7, 17, 4,
            11, 18, 6, 9
        );

        myl::i32mat4x4 sub(
            -2, -4, 3, -7,
            -6, 6, -3, 0,
            3, 7, 1, 0,
            5, 0, -4, -3
        );

        myl::i32mat4x4 mul(
            39, 8, 86, 29,
            80, 43, 64, 49,
            102, 55, 140, 79,
            116, 84, 107, 94
        );

        myl::f32mat4x4 fa(
            1, 2, 9, 0,
            3, 7, 1, 2,
            5, 7, 9, 2,
            8, 9, 1, 3
        );

        myl::f32mat4x4 fb(
            3, 6, 6, 7,
            9, 1, 4, 2,
            2, 0, 8, 2,
            3, 9, 5, 6
        );

        myl::f32mat4x4 div(
            -901.f/650.f, -49.f/325.f, 1967.f/1300.f, 378.f/325.f,
            -57.f/65.f, 14.f/65.f, -21.f/130.f, 87.f/65.f,
            -566.f/325.f, 82.f/325.f, 361.f/325.f, 621.f/325.f,
            -332.f/325.f, 264.f/325.f, -331.f/650.f, 517.f/325.f
        );

        CHECK(a + b == add);
        CHECK(a - b == sub);
        CHECK(a * b == mul);
        CHECK(approx_fmat(fa / fb, div));

        myl::i32mat4x4 c = a;
        c += b;
        CHECK(c == add);

        c = a;
        c -= b;
        CHECK(c == sub);

        c = a;
        c *= b;
        CHECK(c == mul);

        myl::f32mat4x4 d = fa;
        d /= fb;
        CHECK(approx_fmat(d, div));
    }
}
