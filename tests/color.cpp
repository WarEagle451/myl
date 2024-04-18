#include <myl/algorithm.hpp>
#include <myl_wip/color.hpp>

/// MYTODO: Blend, Complement, Greyscale, Mix

#define CONFIG_CATCH_MAIN
#include <catch2/catch_all.hpp>

static myl::f32vec3 cmy{ .8f, .6f, .2f };
static myl::f32vec4 cmyk{ .75f, .5f, 0.f, .2f };
static myl::f32vec3 hsl{ 220, .60f, .50f };
static myl::f32vec3 hsv{ 220, .75f, .80f };
static myl::f32vec3 lab{ 45.03f, 18.71f, -57.85f };
static myl::f32vec3 rgb{ .2f, .4f, .8f };
static myl::f32vec4 rgba{ .2f, .4f, .8f, 1.f };

static myl::u32 u32_rgb = 0x33'66'CC'00;
static myl::u32 u32_rgba = 0x33'66'CC'FF;

#define MYL_COLOR_CAST_TEST(c1, c2) {\
    decltype(c2) result = myl::color_cast<myl::color::model::c1, myl::color::model::c2>(c1);\
    SECTION(#c1" == "#c2) {\
        for (auto i = 0; i != myl::component_count(c2); i++)\
            if (!myl::approx(result[i], c2[i]))\
                FAIL_CHECK("Component " << i << " is not equal");\
        SUCCEED(#c1" == "#c2);\
    }\
}

TEST_CASE("myl::color_cast", "[color.hpp]") {
    MYL_COLOR_CAST_TEST(cmy, cmy);
    MYL_COLOR_CAST_TEST(cmy, cmyk);
    //MYL_COLOR_CAST_TEST(cmy, hsl);
    //MYL_COLOR_CAST_TEST(cmy, hsv);
    //MYL_COLOR_CAST_TEST(cmy, lab);
    MYL_COLOR_CAST_TEST(cmy, rgb);
    MYL_COLOR_CAST_TEST(cmy, rgba);

    MYL_COLOR_CAST_TEST(cmyk, cmy);
    MYL_COLOR_CAST_TEST(cmyk, cmyk);
    //MYL_COLOR_CAST_TEST(cmyk, hsl);
    //MYL_COLOR_CAST_TEST(cmyk, hsv);
    //MYL_COLOR_CAST_TEST(cmyk, lab);
    MYL_COLOR_CAST_TEST(cmyk, rgb);
    MYL_COLOR_CAST_TEST(cmyk, rgba);

    //MYL_COLOR_CAST_TEST(hsl, cmy);
    //MYL_COLOR_CAST_TEST(hsl, cmyk);
    MYL_COLOR_CAST_TEST(hsl, hsl);
    MYL_COLOR_CAST_TEST(hsl, hsv);
    //MYL_COLOR_CAST_TEST(hsl, lab);
    //MYL_COLOR_CAST_TEST(hsl, rgb);
    //MYL_COLOR_CAST_TEST(hsl, rgba);

    //MYL_COLOR_CAST_TEST(hsv, cmy);
    //MYL_COLOR_CAST_TEST(hsv, cmyk);
    MYL_COLOR_CAST_TEST(hsv, hsl);
    MYL_COLOR_CAST_TEST(hsv, hsv);
    //MYL_COLOR_CAST_TEST(hsv, lab);
    //MYL_COLOR_CAST_TEST(hsv, rgb);
    //MYL_COLOR_CAST_TEST(hsv, rgba);

    //MYL_COLOR_CAST_TEST(lab, cmy);
    //MYL_COLOR_CAST_TEST(lab, cmyk);
    //MYL_COLOR_CAST_TEST(lab, hsl);
    //MYL_COLOR_CAST_TEST(lab, hsv);
    MYL_COLOR_CAST_TEST(lab, lab);
    //MYL_COLOR_CAST_TEST(lab, rgb);
    //MYL_COLOR_CAST_TEST(lab, rgba);

    MYL_COLOR_CAST_TEST(rgb, cmy);
    MYL_COLOR_CAST_TEST(rgb, cmyk);
    MYL_COLOR_CAST_TEST(rgb, hsl);
    MYL_COLOR_CAST_TEST(rgb, hsv);
    //MYL_COLOR_CAST_TEST(rgb, lab);
    MYL_COLOR_CAST_TEST(rgb, rgb);
    MYL_COLOR_CAST_TEST(rgb, rgba);

    MYL_COLOR_CAST_TEST(rgba, cmy);
    MYL_COLOR_CAST_TEST(rgba, cmyk);
    MYL_COLOR_CAST_TEST(rgba, hsl);
    MYL_COLOR_CAST_TEST(rgba, hsv);
    //MYL_COLOR_CAST_TEST(rgba, lab);
    MYL_COLOR_CAST_TEST(rgba, rgb);
    MYL_COLOR_CAST_TEST(rgba, rgba);
}

TEST_CASE("myl::rgb_to_u32", "[color.hpp]") {
    CHECK(myl::color::rgb_to_u32(rgb) == u32_rgb);
}

TEST_CASE("myl::rgba_to_u32", "[color.hpp]") {
    CHECK(myl::color::rgba_to_u32(rgba) == u32_rgba);
}

TEST_CASE("myl::u32_to_rgb", "[color.hpp]") {
    CHECK(myl::color::u32_to_rgb(u32_rgb) == rgb);
}

TEST_CASE("myl::u32_to_rgba", "[color.hpp]") {
    CHECK(myl::color::u32_to_rgba(u32_rgba) == rgba);
}
