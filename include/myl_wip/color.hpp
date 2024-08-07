#pragma once
#include <myl/algorithm.hpp>
#include <myl/shaping.hpp>
#include <myl/math/vec3.hpp>
#include <myl/math/vec4.hpp>

/// https://github.com/dmilos/color

/// MYTODO: color.hpp
/// - colors to hex, all versions if possible.
/// - tests
/// - get inline constexpr on colors::color
/// 
/// need alhpa types for hsl and hsv

namespace myl {
    enum class color_model {
        rgb,
        rgba,
        cmy,
        cmyk,
        hsl,
        ///hsla,
        hsv
        ///hsva
    };

    namespace details {
        template<color_model M>
        struct color_model_type_impl {
            static_assert(false);
        };

        template<> struct color_model_type_impl<color_model::rgb>  { using type = myl::f32vec3; };
        template<> struct color_model_type_impl<color_model::rgba> { using type = myl::f32vec4; };
        template<> struct color_model_type_impl<color_model::cmy>  { using type = myl::f32vec3; };
        template<> struct color_model_type_impl<color_model::cmyk> { using type = myl::f32vec4; };
        template<> struct color_model_type_impl<color_model::hsl>  { using type = myl::f32vec3; };
        ///template<> struct color_model_type_impl<color_model::hsla> { using type = myl::f32vec4; };
        template<> struct color_model_type_impl<color_model::hsv>  { using type = myl::f32vec3; };
        ///template<> struct color_model_type_impl<color_model::hsva> { using type = myl::f32vec4; };
    }

    template<color_model M>
    using color_model_type = typename details::color_model_type_impl<M>::type;

    template<color_model To, color_model From>
    MYL_NO_DISCARD constexpr auto color_cast(const color_model_type<From>& color) -> color_model_type<To>;

    // color_cast rgb

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::rgb, color_model::rgb>(const f32vec3& color) -> f32vec3 {
        return color;
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::rgba, color_model::rgb>(const f32vec3& color) -> f32vec4 {
        return f32vec4(color, 1.f);
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::cmy, color_model::rgb>(const f32vec3& color) -> f32vec3 {
        return f32vec3{ 1.f - color.r, 1.f - color.g, 1.f - color.b };
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::cmyk, color_model::rgb>(const f32vec3& color) -> f32vec4 {
        const f32 k = 1.f - max(color[0], color[1], color[2]);
        return f32vec4{
            (1.f - color[0] - k) / (1.f - k),
            (1.f - color[1] - k) / (1.f - k),
            (1.f - color[2] - k) / (1.f - k),
            k
        };
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::hsl, color_model::rgb>(const f32vec3& color) -> f32vec3 {
        const f32 mn = min(color.r, color.g, color.b);
        const f32 mx = max(color.r, color.g, color.b);
        const f32 chroma = mx - mn;

        const f32 lightness = (mx + mn) * .5f;
        const f32 hue = chroma == 0.f ?
            0.f :
            mx == color.r ?
                (color.g - color.b) / chroma + color.g < color.b ? 6.f : 0.f :
                mx == color.g ?
                    (color.b - color.r) / chroma + 2 :
                    (color.r - color.g) / chroma + 4;

        return f32vec3{
            hue * 60.f,
            chroma == 0.f ? 0.f : chroma / (1.f - std::abs(2.f * lightness - 1)),
            lightness
        };
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::hsv, color_model::rgb>(const f32vec3& color) -> f32vec3 {
        const f32 mn = min(color.r, color.g, color.b);
        const f32 mx = max(color.r, color.g, color.b);
        const f32 chroma = mx - mn;

        const f32 hue = chroma == 0.f ?
            0.f :
            mx == color.r ?
                (color.g - color.b) / chroma + color.g < color.b ? 6.f : 0.f :
                mx == color.g ?
                    (color.b - color.r) / chroma + 2 :
                    (color.r - color.g) / chroma + 4;

        return f32vec3{
            hue * 60.f,
            chroma / mx,
            mx
        };
    }

    // color_cast rgba

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::rgb, color_model::rgba>(const f32vec4& color) -> f32vec3 {
        return f32vec3{ color.r, color.g, color.b };
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::rgba, color_model::rgba>(const f32vec4& color) -> f32vec4 {
        return color;
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::cmy, color_model::rgba>(const f32vec4& color) -> f32vec3 {
        return f32vec3{ 1.f - color.r, 1.f - color.g, 1.f - color.b };
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::cmyk, color_model::rgba>(const f32vec4& color) -> f32vec4 { /// MYBUG: THIS DOESNT TAKE IN AN ALPHA VALUE
        return color_cast<color_model::cmyk, color_model::rgb>({ color.r, color.g, color.b });
    }
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::hsl, color_model::rgba>(const f32vec4& color) -> f32vec3 {
        return color_cast<color_model::hsl, color_model::rgb>({ color.r, color.g, color.b });
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::hsv, color_model::rgba>(const f32vec4& color) -> f32vec3 {
        return color_cast<color_model::hsv, color_model::rgb>({ color.r, color.g, color.b });
    }

    // color_cast cmy

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::rgb, color_model::cmy>(const f32vec3& color) -> f32vec3 {
        return f32vec3{ 1.f - color[0], 1.f - color[1], 1.f - color[2] };
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::rgba, color_model::cmy>(const f32vec3& color) -> f32vec4 {
        return f32vec4{ 1.f - color[0], 1.f - color[1], 1.f - color[2], 1.f };
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::cmy, color_model::cmy>(const f32vec3& color) ->  f32vec3 {
        return color;
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::cmyk, color_model::cmy>(const f32vec3& color) -> f32vec4 {
        const f32 k = min(color[0], color[1], color[2]);
        return f32vec4{
            (color[0] - k) / (1.f - k),
            (color[1] - k) / (1.f - k),
            (color[2] - k) / (1.f - k),
            k
        };
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::hsl, color_model::cmy>(const f32vec3& color) -> f32vec3 {
        return color_cast<color_model::hsl, color_model::rgb>(color_cast<color_model::rgb, color_model::cmy>(color));
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::hsv, color_model::cmy>(const f32vec3& color) -> f32vec3 {
        return color_cast<color_model::hsv, color_model::rgb>(color_cast<color_model::rgb, color_model::cmy>(color));
    }

    // color_cast cmyk

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::rgb, color_model::cmyk>(const f32vec4& color) -> f32vec3 {
        return f32vec3{
            -(color[0] * (1.f - color[3]) - 1 + color[3]),
            -(color[1] * (1.f - color[3]) - 1 + color[3]),
            -(color[2] * (1.f - color[3]) - 1 + color[3])
        };
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::rgba, color_model::cmyk>(const f32vec4& color) -> f32vec4 { /// MYBUG: THIS DOESNT TAKE IN AN ALPHA VALUE
        return f32vec4{
            -(color[0] * (1.f - color[3]) - 1 + color[3]),
            -(color[1] * (1.f - color[3]) - 1 + color[3]),
            -(color[2] * (1.f - color[3]) - 1 + color[3]),
            1.f
        };
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::cmy, color_model::cmyk>(const f32vec4& color) ->  f32vec3 {
        return f32vec3{
            color[0] * (1.f - color[3]) + color[3],
            color[1] * (1.f - color[3]) + color[3],
            color[2] * (1.f - color[3]) + color[3]
        };
    }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::cmyk, color_model::cmyk>(const f32vec4& color) -> f32vec4 {
        return color;
    }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::hsl, color_model::cmyk>(const f32vec4& color) -> f32vec3 {
        return color_cast<color_model::hsl, color_model::rgba>(color_cast<color_model::rgba, color_model::cmyk>(color));
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::hsv, color_model::cmyk>(const f32vec4& color) -> f32vec3 {
        return color_cast<color_model::hsv, color_model::rgba>(color_cast<color_model::rgba, color_model::cmyk>(color));
    }

    // color_cast hsl

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::rgb, color_model::hsl>(const f32vec3& color) -> f32vec3 {
        const f32 c = (1.f - std::abs(2.f * color[2] - 1.f)) * color[1];
        const f32 x = c * (1.f - std::abs(std::fmod((color[0] / 60.f), 2.f) - 1));
        const f32 m = color[2] - (c * .5f);

        f32vec3 rgb(m);
        if (color[0] < 60.f)       rgb += { c, x, 0 };
        else if (color[0] < 120.f) rgb += { x, c, 0 };
        else if (color[0] < 180.f) rgb += { 0, c, x };
        else if (color[0] < 240.f) rgb += { 0, x, c };
        else if (color[0] < 300.f) rgb += { x, 0, c };
        else if (color[0] < 360.f) rgb += { c, 0, x };
        else
            return f32vec3(1.f);

        return rgb;
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::rgba, color_model::hsl>(const f32vec3& color) -> f32vec4 {
        return f32vec4(color_cast<color_model::rgb, color_model::hsl>(color), 1.f);
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::cmy, color_model::hsl>(const f32vec3& color) -> f32vec3 {
        return color_cast<color_model::cmy, color_model::rgb>(color_cast<color_model::rgb, color_model::hsl>(color));
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::cmyk, color_model::hsl>(const f32vec3& color) -> f32vec4 {
        return color_cast<color_model::cmyk, color_model::rgba>(color_cast<color_model::rgba, color_model::hsl>(color));
    }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::hsl, color_model::hsl>(const f32vec3& color) ->  f32vec3 {
        return color;
    }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::hsv, color_model::hsl>(const f32vec3& color) -> f32vec3 {
        const f32 v = color[2] + color[1] * min(color[2], 1.f - color[2]);
        return f32vec3{
            color[0],
            v == 0.f ? 0.f : 2.f * (1.f - color[2] / v),
            v
        };
    }

    // color_cast hsv

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::rgb, color_model::hsv>(const f32vec3& color) -> f32vec3 {
        const f32 c = color[2] * color[1];
        const f32 x = c * (1.f - std::fabs(std::fmod(color[0] / 60.f, 2.f) - 1.f));
        const f32 m = color[2] - c;

        f32vec3 rgb(m);
        if (color[0] < 60.f)       rgb += { c, x, 0.f };
        else if (color[0] < 120.f) rgb += { x, c, 0.f };
        else if (color[0] < 180.f) rgb += { 0.f, c, x };
        else if (color[0] < 240.f) rgb += { 0.f, x, c };
        else if (color[0] < 300.f) rgb += { x, 0.f, c };
        else if (color[0] < 360.f) rgb += { c, 0.f, x };
        else
            return f32vec3(1.f);

        return rgb;
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::rgba, color_model::hsv>(const f32vec3& color) -> f32vec4 {
        return f32vec4(color_cast<color_model::rgb, color_model::hsv>(color), 1.f);
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::cmy, color_model::hsv>(const f32vec3& color) -> f32vec3 {
        return color_cast<color_model::cmy, color_model::rgb>(color_cast<color_model::rgb, color_model::hsv>(color));
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::cmyk, color_model::hsv>(const f32vec3& color) -> f32vec4 {
        return color_cast<color_model::cmyk, color_model::rgba>(color_cast<color_model::rgba, color_model::hsv>(color));
    }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::hsl, color_model::hsv>(const f32vec3& color) -> f32vec3 {
        const f32 l = color[2] * (1.f - color[1] * .5f);
        return f32vec3{
            color[0],
            0.f >= l && l <= 1.f ? 0.f : (color[2] - l) / min(l, 1.f - l),
            l
        };
    }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color_model::hsv, color_model::hsv>(const f32vec3& color) ->  f32vec3 {
        return color;
    }

    // Color conversion functions

    MYL_NO_DISCARD constexpr auto rgb_to_rgba(const f32vec3& color) -> f32vec4 { return color_cast<color_model::rgba, color_model::rgb>(color); }
    MYL_NO_DISCARD constexpr auto rgb_to_cmy(const f32vec3& color) -> f32vec3  { return color_cast<color_model::cmy, color_model::rgb>(color); }
    MYL_NO_DISCARD constexpr auto rgb_to_cmyk(const f32vec3& color) -> f32vec4 { return color_cast<color_model::cmyk, color_model::rgb>(color); }
    MYL_NO_DISCARD constexpr auto rgb_to_hsl(const f32vec3& color) -> f32vec3  { return color_cast<color_model::hsl, color_model::rgb>(color); }
    MYL_NO_DISCARD constexpr auto rgb_to_hsv(const f32vec3& color) -> f32vec3  { return color_cast<color_model::hsv, color_model::rgb>(color); }

    MYL_NO_DISCARD constexpr auto rgba_to_rgb(const f32vec4& color) -> f32vec3  { return color_cast<color_model::rgb, color_model::rgba>(color); }
    MYL_NO_DISCARD constexpr auto rgba_to_cmy(const f32vec4& color) -> f32vec3  { return color_cast<color_model::cmy, color_model::rgba>(color); }
    MYL_NO_DISCARD constexpr auto rgba_to_cmyk(const f32vec4& color) -> f32vec4 { return color_cast<color_model::cmyk, color_model::rgba>(color); }
    MYL_NO_DISCARD constexpr auto rgba_to_hsl(const f32vec4& color) -> f32vec3  { return color_cast<color_model::hsl, color_model::rgba>(color); }
    MYL_NO_DISCARD constexpr auto rgba_to_hsv(const f32vec4& color) -> f32vec3  { return color_cast<color_model::hsv, color_model::rgba>(color); }

    MYL_NO_DISCARD constexpr auto cmy_to_rgb(const f32vec3& color) -> f32vec3  { return color_cast<color_model::rgb, color_model::cmy>(color); }
    MYL_NO_DISCARD constexpr auto cmy_to_rgba(const f32vec3& color) -> f32vec4 { return color_cast<color_model::rgba, color_model::cmy>(color); }
    MYL_NO_DISCARD constexpr auto cmy_to_cmyk(const f32vec3& color) -> f32vec4 { return color_cast<color_model::cmyk, color_model::cmy>(color); }
    MYL_NO_DISCARD constexpr auto cmy_to_hsl(const f32vec3& color) -> f32vec3  { return color_cast<color_model::hsl, color_model::cmy>(color); }
    MYL_NO_DISCARD constexpr auto cmy_to_hsv(const f32vec3& color) -> f32vec3  { return color_cast<color_model::hsv, color_model::cmy>(color); }

    MYL_NO_DISCARD constexpr auto cmyk_to_rgb(const f32vec4& color) -> f32vec3  { return color_cast<color_model::rgb, color_model::cmyk>(color); }
    MYL_NO_DISCARD constexpr auto cmyk_to_rgba(const f32vec4& color) -> f32vec4 { return color_cast<color_model::rgba, color_model::cmyk>(color); }
    MYL_NO_DISCARD constexpr auto cmyk_to_cmy(const f32vec4& color) -> f32vec3  { return color_cast<color_model::cmy, color_model::cmyk>(color); }
    MYL_NO_DISCARD constexpr auto cmyk_to_hsl(const f32vec4& color) -> f32vec3  { return color_cast<color_model::hsl, color_model::cmyk>(color); }
    MYL_NO_DISCARD constexpr auto cmyk_to_hsv(const f32vec4& color) -> f32vec3  { return color_cast<color_model::hsv, color_model::cmyk>(color); }

    MYL_NO_DISCARD constexpr auto hsl_to_rgb(const f32vec3& color) -> f32vec3  { return color_cast<color_model::rgb, color_model::hsl>(color); }
    MYL_NO_DISCARD constexpr auto hsl_to_rgba(const f32vec3& color) -> f32vec4 { return color_cast<color_model::rgba, color_model::hsl>(color); }
    MYL_NO_DISCARD constexpr auto hsl_to_cmy(const f32vec3& color) -> f32vec3  { return color_cast<color_model::cmy, color_model::hsl>(color); }
    MYL_NO_DISCARD constexpr auto hsl_to_cmyk(const f32vec3& color) -> f32vec4 { return color_cast<color_model::cmyk, color_model::hsl>(color); }
    MYL_NO_DISCARD constexpr auto hsl_to_hsv(const f32vec3& color) -> f32vec3  { return color_cast<color_model::hsv, color_model::hsl>(color); }

    MYL_NO_DISCARD constexpr auto hsv_to_rgb(const f32vec3& color) -> f32vec3  { return color_cast<color_model::rgb, color_model::hsv>(color); }
    MYL_NO_DISCARD constexpr auto hsv_to_rgba(const f32vec3& color) -> f32vec4 { return color_cast<color_model::rgba, color_model::hsv>(color); }
    MYL_NO_DISCARD constexpr auto hsv_to_cmy(const f32vec3& color) -> f32vec3  { return color_cast<color_model::cmy, color_model::hsv>(color); }
    MYL_NO_DISCARD constexpr auto hsv_to_cmyk(const f32vec3& color) -> f32vec4 { return color_cast<color_model::cmyk, color_model::hsv>(color); }
    MYL_NO_DISCARD constexpr auto hsv_to_hsl(const f32vec3& color) -> f32vec3  { return color_cast<color_model::hsl, color_model::hsv>(color); }

    MYL_NO_DISCARD constexpr auto rgb_to_u32(const f32vec3& color) -> u32 {
        return
            (static_cast<u32>(color.r * 255.f) << 24U) |
            (static_cast<u32>(color.g * 255.f) << 16U) |
            (static_cast<u32>(color.b * 255.f) << 8U);
    }

    MYL_NO_DISCARD constexpr auto rgba_to_u32(const f32vec4& color) -> u32 {
        return
            (static_cast<u32>(color.r * 255.f) << 24U) |
            (static_cast<u32>(color.g * 255.f) << 16U) |
            (static_cast<u32>(color.b * 255.f) << 8U) |
            static_cast<u32>(color.a * 255.f);
    }

    MYL_NO_DISCARD constexpr auto u32_to_rgba(const u32 color) -> f32vec4 {
        return f32vec4{
            static_cast<f32>((color & 0xFF00'0000U) >> 24U) / 255.f,
            static_cast<f32>((color & 0x00FF'0000U) >> 16U) / 255.f,
            static_cast<f32>((color & 0x0000'FF00U) >> 8U) / 255.f,
            static_cast<f32>(color & 0x0000'00FFU) / 255.f
        };
    }

    MYL_NO_DISCARD constexpr auto u32_to_rgb(const u32 color) -> f32vec3 {
        return f32vec3{
            static_cast<f32>((color & 0xFF00'0000U) >> 24U) / 255.f,
            static_cast<f32>((color & 0x00FF'0000U) >> 16U) / 255.f,
            static_cast<f32>((color & 0x0000'FF00U) >> 8U) / 255.f
        };
    }

    // Color Utility
    
    /// MYTODO: Blend should take into account alpha, mix should not, or something like that

    template<color_model M>
    MYL_NO_DISCARD constexpr auto blend(const color_model_type<M>& bg, const color_model_type<M>& fg) -> color_model_type<M>;

    ///template<> MYL_NO_DISCARD constexpr auto blend<color_model::rgb>(const f32vec3& bg, const f32vec3& fg) -> f32vec3;
    
    template<>
    MYL_NO_DISCARD constexpr auto blend<color_model::rgba>(const f32vec4& bg, const f32vec4& fg) -> f32vec4 {
        if (fg.a == 1.f || (fg.a == 0.f && bg.a == 0.f))
            return fg;

        const f32 a = 1.f - (1.f - fg.a) * (1.f - bg.a);
        const f32 alpha_adjusted = bg.a * (1.f - fg.a);
        return {
            ((fg.r * fg.a) + (bg.r * alpha_adjusted)) / a,
            ((fg.g * fg.a) + (bg.g * alpha_adjusted)) / a,
            ((fg.b * fg.a) + (bg.b * alpha_adjusted)) / a,
            a
        };
    }

    ///template<> MYL_NO_DISCARD constexpr auto blend<color_model::cmy>(const f32vec3& bg, const f32vec3& fg) -> f32vec3;
    ///template<> MYL_NO_DISCARD constexpr auto blend<color_model::cmyk>(const f32vec4& bg, const f32vec4& fg) -> f32vec4;
    ///template<> MYL_NO_DISCARD constexpr auto blend<color_model::hsl>(const f32vec3& bg, const f32vec3& fg) -> f32vec3;
    ///template<> MYL_NO_DISCARD constexpr auto blend<color_model::hsla>(const f32vec4& bg, const f32vec4& fg) -> f32vec4;
    ///template<> MYL_NO_DISCARD constexpr auto blend<color_model::hsv>(const f32vec3& bg, const f32vec3& fg) -> f32vec3;
    ///template<> MYL_NO_DISCARD constexpr auto blend<color_model::hsva>(const f32vec4& bg, const f32vec4& fg) -> f32vec4;
    
    template<color_model M>
    MYL_NO_DISCARD constexpr auto mix(const color_model_type<M>& c1, const color_model_type<M>& c2, f32 percentage) -> color_model_type<M>;

    template<>
    MYL_NO_DISCARD constexpr auto mix<color_model::rgb>(const f32vec3& c1, const f32vec3& c2, f32 percentage) -> f32vec3 {
        return lerp(c1, c2, percentage);
    }

    template<>
    MYL_NO_DISCARD constexpr auto mix<color_model::rgba>(const f32vec4& c1, const f32vec4& c2, f32 percentage) -> f32vec4 {
        return lerp(c1, c2, percentage);
    }

    ///template<> MYL_NO_DISCARD constexpr auto mix<color_model::cmy>(const f32vec3& c1, const f32vec3& c2, f32 percentage) -> f32vec3;
    ///template<> MYL_NO_DISCARD constexpr auto mix<color_model::cmyk>(const f32vec4& c1, const f32vec4& c2, f32 percentage) -> f32vec4;
    ///template<> MYL_NO_DISCARD constexpr auto mix<color_model::hsl>(const f32vec3& c1, const f32vec3& c2, f32 percentage) -> f32vec3;
    ///template<> MYL_NO_DISCARD constexpr auto mix<color_model::hsla>(const f32vec4& c1, const f32vec4& c2, f32 percentage) -> f32vec4;
    ///template<> MYL_NO_DISCARD constexpr auto mix<color_model::hsv>(const f32vec3& c1, const f32vec3& c2, f32 percentage) -> f32vec3;
    ///template<> MYL_NO_DISCARD constexpr auto mix<color_model::hsva>(const f32vec4& c1, const f32vec4& c2, f32 percentage) -> f32vec4;

    template<color_model M>
    MYL_NO_DISCARD constexpr auto complement(const color_model_type<M>& color) -> color_model_type<M>;

    template<>
    MYL_NO_DISCARD constexpr auto complement<color_model::rgb>(const f32vec3& color) -> f32vec3 {
        return { 1.f - color.r, 1.f - color.g, 1.f - color.b };
    }

    template<>
    MYL_NO_DISCARD constexpr auto complement<color_model::rgba>(const f32vec4& color) -> f32vec4 {
        return f32vec4(complement<color_model::rgb>({ color.r, color.g, color.b }), color.a);
    }

    ///template<> MYL_NO_DISCARD constexpr auto complement<color_model::cmy>(const f32vec3& color) -> f32vec3;
    ///template<> MYL_NO_DISCARD constexpr auto complement<color_model::cmyk>(const f32vec4& color) -> f32vec4;
    ///template<> MYL_NO_DISCARD constexpr auto complement<color_model::hsl>(const f32vec3& color) -> f32vec3;
    ///template<> MYL_NO_DISCARD constexpr auto complement<color_model::hsla>(const f32vec4& color) -> f32vec4;
    ///template<> MYL_NO_DISCARD constexpr auto complement<color_model::hsv>(const f32vec3& color) -> f32vec3;
    ///template<> MYL_NO_DISCARD constexpr auto complement<color_model::hsva>(const f32vec4& color) -> f32vec4;

    template<color_model M> MYL_NO_DISCARD constexpr auto grayscale(const color_model_type<M>& color) -> color_model_type<M>;

    template<>
    MYL_NO_DISCARD constexpr auto grayscale<color_model::rgb>(const f32vec3& color) -> f32vec3 {
        constexpr f32 thrid = 1.f / 3.f;
        return f32vec3((color.r + color.g + color.b) * thrid);
    }

    template<>
    MYL_NO_DISCARD constexpr auto grayscale<color_model::rgba>(const f32vec4& color) -> f32vec4 {
        return f32vec4(grayscale<color_model::rgb>({ color.r, color.g, color.b }), color.a);
    }

    ///template<> MYL_NO_DISCARD constexpr auto grayscale<color_model::cmy>(const f32vec3& color) -> f32vec3;
    ///template<> MYL_NO_DISCARD constexpr auto grayscale<color_model::cmyk>(const f32vec4& ccolor) -> f32vec4;
    ///template<> MYL_NO_DISCARD constexpr auto grayscale<color_model::hsl>(const f32vec3& color) -> f32vec3;
    ///template<> MYL_NO_DISCARD constexpr auto grayscale<color_model::hsla>(const f32vec4& color) -> f32vec4;
    ///template<> MYL_NO_DISCARD constexpr auto grayscale<color_model::hsv>(const f32vec3& color) -> f32vec3;
    ///template<> MYL_NO_DISCARD constexpr auto grayscale<color_model::hsva>(const f32vec4& color) -> f32vec4;

    namespace colors {
        template<color_model M> static auto blue    = color_cast<M, color_model::rgb>(myl::f32vec3{ 0.f, 0.f, 1.f });
        template<color_model M> static auto cyan    = color_cast<M, color_model::rgb>(myl::f32vec3{ 0.f, 1.f, 1.f });
        template<color_model M> static auto green   = color_cast<M, color_model::rgb>(myl::f32vec3{ 0.f, .5f, 0.f });
        template<color_model M> static auto lime    = color_cast<M, color_model::rgb>(myl::f32vec3{ 0.f, 1.f, 0.f });
        template<color_model M> static auto magenta = color_cast<M, color_model::rgb>(myl::f32vec3{ 1.f, 0.f, 1.f });
        template<color_model M> static auto orange  = color_cast<M, color_model::rgb>(myl::f32vec3{ 1.f, .5f, 0.f });
        template<color_model M> static auto purple  = color_cast<M, color_model::rgb>(myl::f32vec3{ .5f, 0.f, .5f });
        template<color_model M> static auto red     = color_cast<M, color_model::rgb>(myl::f32vec3{ 1.f, 0.f, 0.f });
        template<color_model M> static auto yellow  = color_cast<M, color_model::rgb>(myl::f32vec3{ 1.f, 1.f, 0.f });

        template<color_model M> static auto black = color_cast<M, color_model::rgb>(myl::f32vec3(0.f));
        template<color_model M> static auto gray  = color_cast<M, color_model::rgb>(myl::f32vec3(.5f));
        template<color_model M> static auto white = color_cast<M, color_model::rgb>(myl::f32vec3(1.f));
    }
}
