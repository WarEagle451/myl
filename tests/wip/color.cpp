#include <myl/algorithm.hpp> /// MYTODO: Fix myl::approx
#include <myl_wip/color.hpp>

/// MYTODO: Blend, Complement, Greyscale, Mix

#include <catch2/catch_all.hpp>

static myl::f32vec3 cmy{ .8f, .6f, .2f };
static myl::f32vec4 cmyk{ .75f, .5f, 0.f, .2f };
static myl::f32vec3 hsl{ 220, .60f, .50f };
static myl::f32vec3 hsv{ 220, .75f, .80f };
static myl::f32vec3 rgb{ .2f, .4f, .8f };
static myl::f32vec4 rgba{ .2f, .4f, .8f, 1.f };

static myl::u32 u32_rgb = 0x33'66'CC'00;
static myl::u32 u32_rgba = 0x33'66'CC'FF;

#define MYL_TEST_COLOR_CAST(c1, c2) {\
    decltype(c2) result = myl::color_cast<myl::color_model::c2, myl::color_model::c1>(c1);\
    SECTION(#c1" == "#c2) {\
        for (auto i = 0; i != myl::component_count(c2); i++)\
            CHECK_THAT(result[i], Catch::Matchers::WithinRel(c2[i]));\
        SUCCEED(#c1" == "#c2);\
    }\
}

#define MYL_TEST_COMPARE_COLOR(c1, c2) {\
    SECTION(#c1" == "#c2) {\
        for (auto i = 0; i != myl::component_count(c2); i++)\
            CHECK_THAT(c1[i], Catch::Matchers::WithinRel(c2[i]));\
        SUCCEED(#c1" == "#c2);\
    }\
}

TEST_CASE("myl::color_cast", "[color.hpp]") {
    MYL_TEST_COLOR_CAST(cmy, cmy);
    MYL_TEST_COLOR_CAST(cmy, cmyk);
    MYL_TEST_COLOR_CAST(cmy, hsl);
    MYL_TEST_COLOR_CAST(cmy, hsv);
    MYL_TEST_COLOR_CAST(cmy, rgb);
    MYL_TEST_COLOR_CAST(cmy, rgba);

    MYL_TEST_COLOR_CAST(cmyk, cmy);
    MYL_TEST_COLOR_CAST(cmyk, cmyk);
    MYL_TEST_COLOR_CAST(cmyk, hsl);
    MYL_TEST_COLOR_CAST(cmyk, hsv);
    MYL_TEST_COLOR_CAST(cmyk, rgb);
    MYL_TEST_COLOR_CAST(cmyk, rgba);

    MYL_TEST_COLOR_CAST(hsl, cmy);
    MYL_TEST_COLOR_CAST(hsl, cmyk);
    MYL_TEST_COLOR_CAST(hsl, hsl);
    MYL_TEST_COLOR_CAST(hsl, hsv);
    MYL_TEST_COLOR_CAST(hsl, rgb);
    MYL_TEST_COLOR_CAST(hsl, rgba);

    MYL_TEST_COLOR_CAST(hsv, cmy);
    MYL_TEST_COLOR_CAST(hsv, cmyk);
    MYL_TEST_COLOR_CAST(hsv, hsl);
    MYL_TEST_COLOR_CAST(hsv, hsv);
    MYL_TEST_COLOR_CAST(hsv, rgb);
    MYL_TEST_COLOR_CAST(hsv, rgba);

    MYL_TEST_COLOR_CAST(rgb, cmy);
    MYL_TEST_COLOR_CAST(rgb, cmyk);
    MYL_TEST_COLOR_CAST(rgb, hsl);
    MYL_TEST_COLOR_CAST(rgb, hsv);
    MYL_TEST_COLOR_CAST(rgb, rgb);
    MYL_TEST_COLOR_CAST(rgb, rgba);

    MYL_TEST_COLOR_CAST(rgba, cmy);
    MYL_TEST_COLOR_CAST(rgba, cmyk);
    MYL_TEST_COLOR_CAST(rgba, hsl);
    MYL_TEST_COLOR_CAST(rgba, hsv);
    MYL_TEST_COLOR_CAST(rgba, rgb);
    MYL_TEST_COLOR_CAST(rgba, rgba);
}

TEST_CASE("myl::rgb_to_u32", "[color.hpp]") {
    CHECK(myl::rgb_to_u32(rgb) == u32_rgb);
}

TEST_CASE("myl::rgba_to_u32", "[color.hpp]") {
    CHECK(myl::rgba_to_u32(rgba) == u32_rgba);
}

TEST_CASE("myl::u32_to_rgb", "[color.hpp]") {
    MYL_TEST_COMPARE_COLOR(myl::u32_to_rgb(u32_rgb), rgb);
}

TEST_CASE("myl::u32_to_rgba", "[color.hpp]") {
    MYL_TEST_COMPARE_COLOR(myl::u32_to_rgba(u32_rgba), rgba);
}
