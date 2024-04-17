#pragma once
#include <myl/algorithm.hpp>
#include <myl/shaping.hpp>
#include <myl/math/vec3.hpp>
#include <myl/math/vec4.hpp>

/// https://github.com/dmilos/color

/// MYTODO: color.hpp
/// - colors to hex, all versions if possible.
/// - finish color_cast
/// - tests
/// - add additional quick colors to colors namespace
/// - think about changing the colors namespace stuff to be in color
/// - should model be renamed to space?
/// - get inline constexpr on colors::color
/// - more color models
///     - YIQ
///     - YUV
///     - XYZ
///     - YCCK
///     - T41P
///     - UYVU
///     - YUY2
///     - YVU9
///     - YCC
///     - ARGB4
///     - IHS

namespace myl::color {
    enum class model {
        cmy,
        cmyk,
        hsl,
        hsv,
        lab,
        rgb,
        rgba
    };

    namespace details {
        template<model M> struct model_structure_impl { static_assert(false); };
        template<> struct model_structure_impl<model::cmy> { using type = f32vec3; };
        template<> struct model_structure_impl<model::cmyk> { using type = f32vec4; };
        template<> struct model_structure_impl<model::hsl> { using type = f32vec3; };
        template<> struct model_structure_impl<model::hsv> { using type = f32vec3; };
        template<> struct model_structure_impl<model::lab> { using type = f32vec3; };
        template<> struct model_structure_impl<model::rgb> { using type = f32vec3; };
        template<> struct model_structure_impl<model::rgba> { using type = f32vec4; };
    }

    template<model M> using model_structure = typename details::model_structure_impl<M>::type;

    MYL_NO_DISCARD constexpr auto blend(const f32vec4& bg, const f32vec4& fg) -> f32vec4 {
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

    MYL_NO_DISCARD constexpr auto complement(const f32vec3& color) -> f32vec3 {
        return { 1.f - color.r, 1.f - color.g, 1.f - color.b };
    }

    MYL_NO_DISCARD constexpr auto complement(const f32vec4& color) -> f32vec4 {
        return { 1.f - color.r, 1.f - color.g, 1.f - color.b, color.a };
    }

    MYL_NO_DISCARD constexpr auto grayscale(const f32vec3& color) -> f32vec3 {
        constexpr f32 thrid = 1.f / 3.f;
        return f32vec3((color.r + color.g + color.b) * thrid);
    }

    MYL_NO_DISCARD constexpr auto grayscale(const f32vec4& color) -> f32vec4 {
        return f32vec4((color.r + color.g + color.b + color.a) * .25f);
    }

    template<usize C>
    MYL_NO_DISCARD constexpr auto mix(const vec<C, f32>& c1, const vec<C, f32>& c2, f32 percentage = .5f) -> vec<C, f32> {
        return lerp(c1, c2, percentage);
    }

    // CMY

    MYL_NO_DISCARD constexpr auto cmy_to_cmyk(const f32vec3& color) -> f32vec4 {
        const f32 k = min(color[0], color[1], color[2]);
        return f32vec4{
            (color[0] - k) / (1.f - k),
            (color[1] - k) / (1.f - k),
            (color[2] - k) / (1.f - k),
            k
        };
    }

    MYL_NO_DISCARD constexpr auto cmy_to_hsl(const f32vec3& color) -> f32vec3 {
        return rgb_to_hsl(cmy_to_rgb(color));
    }

    MYL_NO_DISCARD constexpr auto cmy_to_hsv(const f32vec3& color) -> f32vec3 {
        return rgb_to_hsv({ 1.f - color.r, 1.f - color.g, 1.f - color.b });
    }

    //MYL_NO_DISCARD constexpr auto cmy_to_lab(const f32vec3& color) -> f32vec3;

    MYL_NO_DISCARD constexpr auto cmy_to_rgb(const f32vec3& color) -> f32vec3 {
        return f32vec3{ 1.f - color[0], 1.f - color[1], 1.f - color[2] };
    }

    MYL_NO_DISCARD constexpr auto cmy_to_rgba(const f32vec3& color) -> f32vec4 {
        return f32vec4{ 1.f - color[0], 1.f - color[1], 1.f - color[2], 1.f };
    }

    // CMYK

    MYL_NO_DISCARD constexpr auto cmyk_to_cmy(const f32vec4& color) -> f32vec3 {
        return f32vec3{
            color[0] * (1.f - color[3]) + color[3],
            color[1] * (1.f - color[3]) + color[3],
            color[2] * (1.f - color[3]) + color[3]
        };
    }

    MYL_NO_DISCARD constexpr auto cmyk_to_hsl(const f32vec4& color) -> f32vec3 {
        return rgb_to_hsl(cmyk_to_rgb(color));
    }

    MYL_NO_DISCARD constexpr auto cmyk_to_hsv(const f32vec4& color) -> f32vec3 {
        return rgb_to_hsv(cmyk_to_rgb(color));
    }

    //MYL_NO_DISCARD constexpr auto cmyk_to_lab(const f32vec4& color) -> f32vec3;

    MYL_NO_DISCARD constexpr auto cmyk_to_rgb(const f32vec4& color) -> f32vec3 {
        return f32vec3{
            -(color[0] * (1.f - color[3]) - 1 + color[3]),
            -(color[1] * (1.f - color[3]) - 1 + color[3]),
            -(color[2] * (1.f - color[3]) - 1 + color[3])
        };
    }

    MYL_NO_DISCARD constexpr auto cmyk_to_rgba(const f32vec4& color) -> f32vec4 {
        return f32vec4{
            -(color[0] * (1.f - color[3]) - 1 + color[3]),
            -(color[1] * (1.f - color[3]) - 1 + color[3]),
            -(color[2] * (1.f - color[3]) - 1 + color[3]),
            1.f
        };
    }

    // HSL

    //MYL_NO_DISCARD constexpr auto hsl_to_cmy(const f32vec3& color) -> f32vec3;
    //MYL_NO_DISCARD constexpr auto hsl_to_cmyk(const f32vec3& color) -> f32vec4;

    /// MYTODO: TESTTT////////////////////////////////
    MYL_NO_DISCARD constexpr auto hsl_to_hsv(const f32vec3& color) -> f32vec3 {
        const f32 v = color[2] + color[1] * min(color[2], 1.f - color[2]);
        return f32vec3 {
            color[0],
            v,
            v == 0.f ? 0.f : 2.f * (1.f - color[2] / v),
        };
    }

    //MYL_NO_DISCARD constexpr auto hsl_to_lab(const f32vec3& color) -> f32vec3;
    //MYL_NO_DISCARD constexpr auto hsl_to_rgb(const f32vec3& color) -> f32vec3;

    MYL_NO_DISCARD constexpr auto hsl_to_rgba(const f32vec3& color) -> f32vec4 {
        return f32vec4(hsl_to_rgb(color), 1.f);
    }

    // HSV

    MYL_NO_DISCARD constexpr auto hsv_to_cmy(const f32vec3& color) -> f32vec3 {
        return 1.f - hsv_to_rgb(color);
    }

    //MYL_NO_DISCARD constexpr auto hsv_to_cmyk(const f32vec3& color) -> f32vec4;

    /// MYTODO: TESTTT////////////////////////////////
    MYL_NO_DISCARD constexpr auto hsv_to_hsl(const f32vec3& color) -> f32vec3 {
        const f32 l = color[2] * (1.f - color[1] * .5f);
        return f32vec3 {
            color[0],
            0.f < l && l < 1.f ? 0.f : (color[2] - 1.f) / min(l, 1.f - l),
            l
        };
    }

    //MYL_NO_DISCARD constexpr auto hsv_to_lab(const f32vec3& color) -> f32vec3;
    //MYL_NO_DISCARD constexpr auto hsv_to_rgb(const f32vec3& color) -> f32vec3;

    MYL_NO_DISCARD constexpr auto hsv_to_rgba(const f32vec3& color) -> f32vec4 {
        return f32vec4(hsv_to_rgb(color), 1.f);
    }

    // LAB

    //MYL_NO_DISCARD constexpr auto lab_to_cmy(const f32vec3& color) -> f32vec3;
    //MYL_NO_DISCARD constexpr auto lab_to_cmyk(const f32vec3& color) -> f32vec4;
    //MYL_NO_DISCARD constexpr auto lab_to_hsl(const f32vec3& color) -> f32vec3;
    //MYL_NO_DISCARD constexpr auto lab_to_hsv(const f32vec3& color) -> f32vec3;
    //MYL_NO_DISCARD constexpr auto lab_to_rgb(const f32vec3& color) -> f32vec3;
    //MYL_NO_DISCARD constexpr auto lab_to_rgba(const f32vec3& color) -> f32vec4;

    // RGB

    MYL_NO_DISCARD constexpr auto rgb_to_cmy(const f32vec3& color) -> f32vec3 {
        return f32vec3{ 1.f - color.r, 1.f - color.g, 1.f - color.b };
    }
    
    MYL_NO_DISCARD constexpr auto rgb_to_cmyk(const f32vec3& color) -> f32vec4 {
        const f32 k = 1.f - max(color[0], color[1], color[2]);
        return f32vec4{
            (1.f - color[0] - k) / (1.f - k),
            (1.f - color[1] - k) / (1.f - k),
            (1.f - color[2] - k) / (1.f - k),
            k
        };
    }

    /// MYTODO: TEST THIS ////////////////////////////////////////////////////////////////////////////////////////////
    MYL_NO_DISCARD constexpr auto rgb_to_hsl(const f32vec3& color) -> f32vec3 {
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
            (chroma == 0.f ? 0.f : chroma / (1.f - std::abs(2.f * lightness - 1))) * 100.f,
            lightness * 100.f
        };
    }
    
    /// MYTODO: TEST THIS ////////////////////////////////////////////////////////////////////////////////////////////
    MYL_NO_DISCARD constexpr auto rgb_to_hsv(const f32vec3& color) -> f32vec3 {
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

    //MYL_NO_DISCARD constexpr auto rgb_to_lab(const f32vec3& color) -> f32vec3;

    MYL_NO_DISCARD constexpr auto rgb_to_rgba(const f32vec3& color) -> f32vec4 {
        return f32vec4(color, 1.f);
    }

    // RGBA

    MYL_NO_DISCARD constexpr auto rgba_to_cmy(const f32vec4& color) -> f32vec3 {
        return f32vec3{ 1.f - color.r, 1.f - color.g, 1.f - color.b };
    }

    MYL_NO_DISCARD constexpr auto rgba_to_cmyk(const f32vec4& color) -> f32vec4 {
        const f32 k = 1.f - max(color[0], color[1], color[2]);
        return f32vec4{
            (1.f - color[0] - k) / (1.f - k),
            (1.f - color[1] - k) / (1.f - k),
            (1.f - color[2] - k) / (1.f - k),
            k
        };
    }

    MYL_NO_DISCARD constexpr auto rgba_to_hsl(const f32vec4& color) -> f32vec3 {
        return rgb_to_hsl({ color.r, color.g, color.b });
    }

    MYL_NO_DISCARD constexpr auto rgba_to_hsv(const f32vec4& color) -> f32vec3 {
        return rgb_to_hsv({ color.r, color.g, color.b });
    }

    //MYL_NO_DISCARD constexpr auto rgba_to_lab(const f32vec4& color) -> f32vec3;

    MYL_NO_DISCARD constexpr auto rgba_to_rgb(const f32vec4& color) -> f32vec3 {
        return f32vec3(color.r, color.g, color.b);
    }

    // Conversions

    MYL_NO_DISCARD constexpr auto color_to_u32(const f32vec4& color) -> u32 {
        return
            (static_cast<u32>(color.r * 255.f) << 24) |
            (static_cast<u32>(color.g * 255.f) << 16) |
            (static_cast<u32>(color.b * 255.f) << 8) |
            static_cast<u32>(color.a * 255.f);
    }

    MYL_NO_DISCARD constexpr auto u32_to_color(const u32 color) -> f32vec4 {
        return {
            static_cast<f32>(color & 0xFF00'0000) / 255.f,
            static_cast<f32>(color & 0x00FF'0000) / 255.f,
            static_cast<f32>(color & 0x0000'FF00) / 255.f,
            static_cast<f32>(color & 0x0000'00FF) / 255.f
        };
    }

    template<model From, model To> MYL_NO_DISCARD constexpr auto color_cast(const model_structure<From>& color) -> model_structure<To>;
    
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::cmy, model::cmy>(const f32vec3& color) -> f32vec3 { return color; }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::cmy, model::cmyk>(const f32vec3& color) -> f32vec4 { return cmy_to_cmyk(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::cmy, model::hsl>(const f32vec3& color) -> f32vec3 { return cmy_to_hsl(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::cmy, model::hsv>(const f32vec3& color) -> f32vec3 { return cmy_to_hsv(color); }
    //template<> MYL_NO_DISCARD constexpr auto color_cast<model::cmy, model::lab>(const f32vec3& color) -> f32vec3 { return cmy_to_lab(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::cmy, model::rgb>(const f32vec3& color) -> f32vec3 { return cmy_to_rgb(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::cmy, model::rgba>(const f32vec3& color) -> f32vec4 { return cmy_to_rgba(color); }

    template<> MYL_NO_DISCARD constexpr auto color_cast<model::cmyk, model::cmy>(const f32vec4& color) -> f32vec3 { return cmyk_to_cmy(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::cmyk, model::cmyk>(const f32vec4& color) -> f32vec4 { return color; }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::cmyk, model::hsl>(const f32vec4& color) -> f32vec3 { return cmyk_to_hsl(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::cmyk, model::hsv>(const f32vec4& color) -> f32vec3 { return cmyk_to_hsv(color); }
    //template<> MYL_NO_DISCARD constexpr auto color_cast<model::cmyk, model::lab>(const f32vec4& color) -> f32vec3 { return cmyk_to_lab(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::cmyk, model::rgb>(const f32vec4& color) -> f32vec3 { return cmyk_to_rgb(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::cmyk, model::rgba>(const f32vec4& color) -> f32vec4 { return cmyk_to_rgba(color); }

    template<> MYL_NO_DISCARD constexpr auto color_cast<model::hsl, model::cmy>(const f32vec3& color) -> f32vec3 { return hsl_to_cmy(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::hsl, model::cmyk>(const f32vec3& color) -> f32vec4 { return hsl_to_cmyk(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::hsl, model::hsl>(const f32vec3& color) -> f32vec3 { return color; }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::hsl, model::hsv>(const f32vec3& color) -> f32vec3 { return hsl_to_hsv(color); }
    //template<> MYL_NO_DISCARD constexpr auto color_cast<model::hsl, model::lab>(const f32vec3& color) -> f32vec3 { return hsl_to_lab(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::hsl, model::rgb>(const f32vec3& color) -> f32vec3 { return hsl_to_rgb(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::hsl, model::rgba>(const f32vec3& color) -> f32vec4 { return hsl_to_rgba(color); }

    template<> MYL_NO_DISCARD constexpr auto color_cast<model::hsv, model::cmy>(const f32vec3& color) -> f32vec3 { return hsv_to_cmy(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::hsv, model::cmyk>(const f32vec3& color) -> f32vec4 { return hsv_to_cmyk(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::hsv, model::hsl>(const f32vec3& color) -> f32vec3 { return hsv_to_hsl(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::hsv, model::hsv>(const f32vec3& color) -> f32vec3 { return color; }
    //template<> MYL_NO_DISCARD constexpr auto color_cast<model::hsv, model::lab>(const f32vec3& color) -> f32vec3 { return hsv_to_lab(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::hsv, model::rgb>(const f32vec3& color) -> f32vec3 { return hsv_to_rgb(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::hsv, model::rgba>(const f32vec3& color) -> f32vec4 { return hsv_to_rgba(color); }

    //template<> MYL_NO_DISCARD constexpr auto color_cast<model::lab, model::cmy>(const f32vec3& color) -> f32vec3 { return lab_to_cmy(color); }
    //template<> MYL_NO_DISCARD constexpr auto color_cast<model::lab, model::cmyk>(const f32vec3& color) -> f32vec4 { return lab_to_cmyk(color); }
    //template<> MYL_NO_DISCARD constexpr auto color_cast<model::lab, model::hsl>(const f32vec3& color) -> f32vec3 { return lab_to_hsl(color); }
    //template<> MYL_NO_DISCARD constexpr auto color_cast<model::lab, model::hsv>(const f32vec3& color) -> f32vec3 { return lab_to_hsv(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::lab, model::lab>(const f32vec3& color) -> f32vec3 { return color; }
    //template<> MYL_NO_DISCARD constexpr auto color_cast<model::lab, model::rgb>(const f32vec3& color) -> f32vec3 { return lab_to_rgb(color); }
    //template<> MYL_NO_DISCARD constexpr auto color_cast<model::lab, model::rgba>(const f32vec3& color) -> f32vec4 { return lab_to_rgba(color); }

    template<> MYL_NO_DISCARD constexpr auto color_cast<model::rgb, model::cmy>(const f32vec3& color) -> f32vec3 { return rgb_to_cmy(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::rgb, model::cmyk>(const f32vec3& color) -> f32vec4 { return rgb_to_cmyk(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::rgb, model::hsl>(const f32vec3& color) -> f32vec3 { return rgb_to_hsl(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::rgb, model::hsv>(const f32vec3& color) -> f32vec3 { return rgb_to_hsv(color); }
    //template<> MYL_NO_DISCARD constexpr auto color_cast<model::rgb, model::lab>(const f32vec3& color) -> f32vec3 { return rgb_to_lab(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::rgb, model::rgb>(const f32vec3& color) -> f32vec3 { return color; }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::rgb, model::rgba>(const f32vec3& color) -> f32vec4 { return rgb_to_rgba(color); }

    template<> MYL_NO_DISCARD constexpr auto color_cast<model::rgba, model::cmy>(const f32vec4& color) -> f32vec3 { return rgba_to_cmy(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::rgba, model::cmyk>(const f32vec4& color) -> f32vec4 { return rgba_to_cmyk(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::rgba, model::hsl>(const f32vec4& color) -> f32vec3 { return rgba_to_hsl(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::rgba, model::hsv>(const f32vec4& color) -> f32vec3 { return rgba_to_hsv(color); }
    //template<> MYL_NO_DISCARD constexpr auto color_cast<model::rgba, model::lab>(const f32vec4& color) -> f32vec3 { return rgba_to_lab(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::rgba, model::rgb>(const f32vec4& color) -> f32vec3 { return rgba_to_rgb(color); }
    template<> MYL_NO_DISCARD constexpr auto color_cast<model::rgba, model::rgba>(const f32vec4& color) -> f32vec4 { return color; }
}

namespace myl::colors {
    template<color::model M> static auto blue    = color::color_cast<color::model::rgb, M>(myl::f32vec3{ 0.f, 0.f, 1.f });
    template<color::model M> static auto cyan    = color::color_cast<color::model::rgb, M>(myl::f32vec3{ 0.f, 1.f, 1.f });
    template<color::model M> static auto green   = color::color_cast<color::model::rgb, M>(myl::f32vec3{ 0.f, .5f, 0.f });
    template<color::model M> static auto lime    = color::color_cast<color::model::rgb, M>(myl::f32vec3{ 0.f, 1.f, 0.f });
    template<color::model M> static auto magenta = color::color_cast<color::model::rgb, M>(myl::f32vec3{ 1.f, 0.f, 1.f });
    template<color::model M> static auto orange  = color::color_cast<color::model::rgb, M>(myl::f32vec3{ 1.f, .5f, 0.f });
    template<color::model M> static auto purple  = color::color_cast<color::model::rgb, M>(myl::f32vec3{ .5f, 0.f, .5f });
    template<color::model M> static auto red     = color::color_cast<color::model::rgb, M>(myl::f32vec3{ 1.f, 0.f, 0.f });
    template<color::model M> static auto yellow  = color::color_cast<color::model::rgb, M>(myl::f32vec3{ 1.f, 1.f, 0.f });

    template<color::model M> static auto black = color::color_cast<color::model::rgb, M>(myl::f32vec3(0.f));
    template<color::model M> static auto gray  = color::color_cast<color::model::rgb, M>(myl::f32vec3(.5f));
    template<color::model M> static auto white = color::color_cast<color::model::rgb, M>(myl::f32vec3(1.f));
}
