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
/// - think about changing the colors namespace stuff to be in color
/// - get inline constexpr on colors::color

namespace myl {
    namespace color {
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
            template<model M> struct model_type_impl { static_assert(false); };
            template<> struct model_type_impl<model::cmy> { using type = f32vec3; };
            template<> struct model_type_impl<model::cmyk> { using type = f32vec4; };
            template<> struct model_type_impl<model::hsl> { using type = f32vec3; };
            template<> struct model_type_impl<model::hsv> { using type = f32vec3; };
            template<> struct model_type_impl<model::lab> { using type = f32vec3; };
            template<> struct model_type_impl<model::rgb> { using type = f32vec3; };
            template<> struct model_type_impl<model::rgba> { using type = f32vec4; };
        }

        template<model M> using model_type = typename details::model_type_impl<M>::type;
    }

    namespace colors {
        template<color::model M> static auto blue    = color_cast<color::model::rgb, M>(myl::f32vec3{ 0.f, 0.f, 1.f });
        template<color::model M> static auto cyan    = color_cast<color::model::rgb, M>(myl::f32vec3{ 0.f, 1.f, 1.f });
        template<color::model M> static auto green   = color_cast<color::model::rgb, M>(myl::f32vec3{ 0.f, .5f, 0.f });
        template<color::model M> static auto lime    = color_cast<color::model::rgb, M>(myl::f32vec3{ 0.f, 1.f, 0.f });
        template<color::model M> static auto magenta = color_cast<color::model::rgb, M>(myl::f32vec3{ 1.f, 0.f, 1.f });
        template<color::model M> static auto orange  = color_cast<color::model::rgb, M>(myl::f32vec3{ 1.f, .5f, 0.f });
        template<color::model M> static auto purple  = color_cast<color::model::rgb, M>(myl::f32vec3{ .5f, 0.f, .5f });
        template<color::model M> static auto red     = color_cast<color::model::rgb, M>(myl::f32vec3{ 1.f, 0.f, 0.f });
        template<color::model M> static auto yellow  = color_cast<color::model::rgb, M>(myl::f32vec3{ 1.f, 1.f, 0.f });

        template<color::model M> static auto black = color_cast<color::model::rgb, M>(myl::f32vec3(0.f));
        template<color::model M> static auto gray  = color_cast<color::model::rgb, M>(myl::f32vec3(.5f));
        template<color::model M> static auto white = color_cast<color::model::rgb, M>(myl::f32vec3(1.f));
    }

    template<color::model From, color::model To> MYL_NO_DISCARD constexpr auto color_cast(const color::model_type<From>& color) -> color::model_type<To>;

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::cmy, color::model::cmy>(const f32vec3& color) ->  f32vec3 {
        return color;
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::cmy, color::model::cmyk>(const f32vec3& color) -> f32vec4 {
        const f32 k = min(color[0], color[1], color[2]);
        return f32vec4{
            (color[0] - k) / (1.f - k),
            (color[1] - k) / (1.f - k),
            (color[2] - k) / (1.f - k),
            k
        };
    }

    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::cmy, color::model::hsl>(const f32vec3& color) -> f32vec3 { return color::cmy_to_hsl(color); }
    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::cmy, color::model::hsv>(const f32vec3& color) -> f32vec3 { return color::cmy_to_hsv(color); }
    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::cmy, color::model::lab>(const f32vec3& color) -> f32vec3 { return color::cmy_to_lab(color); }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::cmy, color::model::rgb>(const f32vec3& color) -> f32vec3 {
        return f32vec3{ 1.f - color[0], 1.f - color[1], 1.f - color[2] };
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::cmy, color::model::rgba>(const f32vec3& color) -> f32vec4 { 
        return f32vec4{ 1.f - color[0], 1.f - color[1], 1.f - color[2], 1.f };
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::cmyk, color::model::cmy>(const f32vec4& color) ->  f32vec3 {
        return f32vec3{
                color[0] * (1.f - color[3]) + color[3],
                color[1] * (1.f - color[3]) + color[3],
                color[2] * (1.f - color[3]) + color[3]
        };
    }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::cmyk, color::model::cmyk>(const f32vec4& color) -> f32vec4 {
        return color;
    }
    
    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::cmyk, color::model::hsl>(const f32vec4& color) -> f32vec3 { return color::cmyk_to_hsl(color); }
    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::cmyk, color::model::hsv>(const f32vec4& color) -> f32vec3 { return color::cmyk_to_hsv(color); }
    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::cmyk, color::model::lab>(const f32vec4& color) -> f32vec3 { return color::cmyk_to_lab(color); }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::cmyk, color::model::rgb>(const f32vec4& color) -> f32vec3 {
        return f32vec3{
                -(color[0] * (1.f - color[3]) - 1 + color[3]),
                -(color[1] * (1.f - color[3]) - 1 + color[3]),
                -(color[2] * (1.f - color[3]) - 1 + color[3])
        };
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::cmyk, color::model::rgba>(const f32vec4& color) -> f32vec4 {
        return f32vec4{
                -(color[0] * (1.f - color[3]) - 1 + color[3]),
                -(color[1] * (1.f - color[3]) - 1 + color[3]),
                -(color[2] * (1.f - color[3]) - 1 + color[3]),
                1.f
        };
    }

    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::hsl, color::model::cmy>(const f32vec3& color) -> f32vec3 { return color::hsl_to_cmy(color); }
    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::hsl, color::model::cmyk>(const f32vec3& color) -> f32vec4 { return color::hsl_to_cmyk(color); }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::hsl, color::model::hsl>(const f32vec3& color) ->  f32vec3 {
        return color;
    }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::hsl, color::model::hsv>(const f32vec3& color) -> f32vec3 {
        const f32 v = color[2] + color[1] * min(color[2], 1.f - color[2]);
        return f32vec3{
            color[0],
            v,
            v == 0.f ? 0.f : 2.f * (1.f - color[2] / v),
        };
    }

    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::hsl, color::model::lab>(const f32vec3& color) -> f32vec3 { return color::hsl_to_lab(color); }

    ///template<>
    ///MYL_NO_DISCARD constexpr auto color_cast<color::model::hsl, color::model::rgb>(const f32vec3& color) -> f32vec3 {
    ///    const f32 c = (1.f - std::abs(2.f * color[2] - 1.f)) * color[1];
    ///    const f32 x = c * (1.f - std::abs(std::fmod((color[0] / 60.f), 2.f) - 1));
    ///    const f32 m = color[2] - (c * .5f);
    ///    
    ///    f32vec3 rgb(m);
    ///    if (color[0] < 60.f)       rgb += { c, x, 0 };
    ///    else if (color[0] < 120.f) rgb += { x, c, 0 };
    ///    else if (color[0] < 180.f) rgb += { 0, c, x };
    ///    else if (color[0] < 240.f) rgb += { 0, x, c };
    ///    else if (color[0] < 300.f) rgb += { x, 0, c };
    ///    else if (color[0] < 360.f) rgb += { c, 0, x };
    ///    else
    ///        return f32vec3(1.f);
    ///
    ///    return rgb;
    ///}

    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::hsl, color::model::rgba>(const f32vec3& color) -> f32vec4 { return color::hsl_to_rgba(color); }

    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::hsv, color::model::cmy>(const f32vec3& color) -> f32vec3 { return color::hsv_to_cmy(color); }
    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::hsv, color::model::cmyk>(const f32vec3& color) -> f32vec4 { return color::hsv_to_cmyk(color); }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::hsv, color::model::hsl>(const f32vec3& color) -> f32vec3 {
        const f32 l = color[2] * (1.f - color[1] * .5f);
        return f32vec3{
            color[0],
            0.f < l && l < 1.f ? 0.f : (color[2] - 1.f) / min(l, 1.f - l),
            l
        };
    }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::hsv, color::model::hsv>(const f32vec3& color) ->  f32vec3 {
        return color;
    }
    
    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::hsv, color::model::lab>(const f32vec3& color) -> f32vec3 { return color::hsv_to_lab(color); }

    template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::hsv, color::model::rgb>(const f32vec3& color) -> f32vec3 {
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

    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::hsv, color::model::rgba>(const f32vec3& color) -> f32vec4 { return color::hsv_to_rgba(color); }

    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::lab, color::model::cmy>(const f32vec3& color) -> f32vec3 { return color::lab_to_cmy(color); }
    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::lab, color::model::cmyk>(const f32vec3& color) -> f32vec4 { return color::lab_to_cmyk(color); }
    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::lab, color::model::hsl>(const f32vec3& color) -> f32vec3 { return color::lab_to_hsl(color); }
    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::lab, color::model::hsv>(const f32vec3& color) -> f32vec3 { return color::lab_to_hsv(color); }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::lab, color::model::lab>(const f32vec3& color) -> f32vec3 {
        return color;
    }

    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::lab, color::model::rgb>(const f32vec3& color)->f32vec3;
    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::lab, color::model::rgba>(const f32vec3& color) -> f32vec4 { return color::lab_to_rgba(color); }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::rgb, color::model::cmy>(const f32vec3& color) -> f32vec3 {
        return f32vec3{ 1.f - color.r, 1.f - color.g, 1.f - color.b };
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::rgb, color::model::cmyk>(const f32vec3& color) -> f32vec4 {
        const f32 k = 1.f - max(color[0], color[1], color[2]);
        return f32vec4{
            (1.f - color[0] - k) / (1.f - k),
            (1.f - color[1] - k) / (1.f - k),
            (1.f - color[2] - k) / (1.f - k),
            k
        };
    }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::rgb, color::model::hsl>(const f32vec3& color) -> f32vec3 {
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

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::rgb, color::model::hsv>(const f32vec3& color) -> f32vec3 {
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

    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::rgb, color::model::lab>(const f32vec3& color) -> f32vec3 { return color::rgb_to_lab(color); }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::rgb, color::model::rgb>(const f32vec3& color) -> f32vec3 {
        return color;
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::rgb, color::model::rgba>(const f32vec3& color) -> f32vec4 {
        return f32vec4(color, 1.f);
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::rgba, color::model::cmy>(const f32vec4& color) -> f32vec3 {
        return f32vec3{ 1.f - color.r, 1.f - color.g, 1.f - color.b };
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::rgba, color::model::cmyk>(const f32vec4& color) -> f32vec4 {
        return color_cast<color::model::rgb, color::model::cmyk>({ color.r, color.g, color.b });
    }
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::rgba, color::model::hsl>(const f32vec4& color) -> f32vec3 {
        return color_cast<color::model::rgb, color::model::hsl>({ color.r, color.g, color.b });
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::rgba, color::model::hsv>(const f32vec4& color) -> f32vec3 {
        return color_cast<color::model::rgb, color::model::hsv>({ color.r, color.g, color.b });
    }

    ///template<> MYL_NO_DISCARD constexpr auto color_cast<color::model::rgba, color::model::lab>(const f32vec4& color) -> f32vec3 { return color::rgba_to_lab(color); }
    
    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::rgba, color::model::rgb>(const f32vec4& color) -> f32vec3 {
        return f32vec3{ color.r, color.g, color.b };
    }

    template<>
    MYL_NO_DISCARD constexpr auto color_cast<color::model::rgba, color::model::rgba>(const f32vec4& color) -> f32vec4 {
        return color;
    }

    namespace color {
        // Conversions

        MYL_NO_DISCARD constexpr auto cmy_to_cmyk(const f32vec3& color) -> f32vec4 { return color_cast<model::cmy, model::cmyk>(color); }
        ///MYL_NO_DISCARD constexpr auto cmy_to_hsl(const f32vec3& color) -> f32vec3 { return color_cast<model::cmy, model::hsl>(color); }
        ///MYL_NO_DISCARD constexpr auto cmy_to_hsv(const f32vec3& color) -> f32vec3 { return color_cast<model::cmy, model::hsv>(color); }
        ///MYL_NO_DISCARD constexpr auto cmy_to_lab(const f32vec3& color) -> f32vec3 { return color_cast<model::cmy, model::lab>(color); }
        MYL_NO_DISCARD constexpr auto cmy_to_rgb(const f32vec3& color) -> f32vec3 { return color_cast<model::cmy, model::rgb>(color); }
        MYL_NO_DISCARD constexpr auto cmy_to_rgba(const f32vec3& color) -> f32vec4 { return color_cast<model::cmy, model::rgba>(color); }

        MYL_NO_DISCARD constexpr auto cmyk_to_cmy(const f32vec4& color) -> f32vec3 { return color_cast<model::cmyk, model::cmy>(color); }
        ///MYL_NO_DISCARD constexpr auto cmyk_to_hsl(const f32vec4& color) -> f32vec3 { return color_cast<model::cmyk, model::hsl>(color); }
        ///MYL_NO_DISCARD constexpr auto cmyk_to_hsv(const f32vec4& color) -> f32vec3 { return color_cast<model::cmyk, model::hsv>(color); }
        ///MYL_NO_DISCARD constexpr auto cmyk_to_lab(const f32vec4& color) -> f32vec3 { return color_cast<model::cmyk, model::lab>(color); }
        MYL_NO_DISCARD constexpr auto cmyk_to_rgb(const f32vec4& color) -> f32vec3 { return color_cast<model::cmyk, model::rgb>(color); }
        MYL_NO_DISCARD constexpr auto cmyk_to_rgba(const f32vec4& color) -> f32vec4 { return color_cast<model::cmyk, model::rgba>(color); }

        ///MYL_NO_DISCARD constexpr auto hsl_to_cmy(const f32vec3& color) -> f32vec3 { return color_cast<model::hsl, model::cmy>(color); }
        ///MYL_NO_DISCARD constexpr auto hsl_to_cmyk(const f32vec3& color) -> f32vec4 { return color_cast<model::hsl, model::cmyk>(color); }
        MYL_NO_DISCARD constexpr auto hsl_to_hsv(const f32vec3& color) -> f32vec3 { return color_cast<model::hsl, model::hsv>(color); }
        ///MYL_NO_DISCARD constexpr auto hsl_to_lab(const f32vec3& color) -> f32vec3 { return color_cast<model::hsl, model::lab>(color); }
        ///MYL_NO_DISCARD constexpr auto hsl_to_rgb(const f32vec3& color) -> f32vec3 { return color_cast<model::hsl, model::rgb>(color); }
        ///MYL_NO_DISCARD constexpr auto hsl_to_rgba(const f32vec3& color) -> f32vec4 { return color_cast<model::hsl, model::rgba>(color); }

        ///MYL_NO_DISCARD constexpr auto hsv_to_cmy(const f32vec3& color) -> f32vec3 { return color_cast<model::hsv, model::cmy>(color); }
        ///MYL_NO_DISCARD constexpr auto hsv_to_cmyk(const f32vec3& color) -> f32vec4 { return color_cast<model::hsv, model::cmyk>(color); }
        MYL_NO_DISCARD constexpr auto hsv_to_hsl(const f32vec3& color) -> f32vec3 { return color_cast<model::hsv, model::hsl>(color); }
        ///MYL_NO_DISCARD constexpr auto hsv_to_lab(const f32vec3& color) -> f32vec3 { return color_cast<model::hsv, model::lab>(color); }
        MYL_NO_DISCARD constexpr auto hsv_to_rgb(const f32vec3& color) -> f32vec3 { return color_cast<model::hsv, model::rgb>(color); }
        ///MYL_NO_DISCARD constexpr auto hsv_to_rgba(const f32vec3& color) -> f32vec4 { return color_cast<model::hsv, model::rgba>(color); }

        ///MYL_NO_DISCARD constexpr auto lab_to_cmy(const f32vec3& color) -> f32vec3 { return color_cast<model::lab, model::cmy>(color); }
        ///MYL_NO_DISCARD constexpr auto lab_to_cmyk(const f32vec3& color) -> f32vec4 { return color_cast<model::lab, model::cmyk>(color); }
        ///MYL_NO_DISCARD constexpr auto lab_to_hsl(const f32vec3& color) -> f32vec3 { return color_cast<model::lab, model::hsl>(color); }
        ///MYL_NO_DISCARD constexpr auto lab_to_hsv(const f32vec3& color) -> f32vec3 { return color_cast<model::lab, model::hsv>(color); }
        ///MYL_NO_DISCARD constexpr auto lab_to_rgb(const f32vec3& color) -> f32vec3 { return color_cast<model::lab, model::rgb>(color); }
        ///MYL_NO_DISCARD constexpr auto lab_to_rgba(const f32vec3& color) -> f32vec4 { return color_cast<model::lab, model::rgba>(color); }

        MYL_NO_DISCARD constexpr auto rgb_to_cmy(const f32vec3& color) -> f32vec3 { return color_cast<model::rgb, model::cmy>(color); }
        MYL_NO_DISCARD constexpr auto rgb_to_cmyk(const f32vec3& color) -> f32vec4 { return color_cast<model::rgb, model::cmyk>(color); }
        MYL_NO_DISCARD constexpr auto rgb_to_hsl(const f32vec3& color) -> f32vec3 { return color_cast<model::rgb, model::hsl>(color); }
        MYL_NO_DISCARD constexpr auto rgb_to_hsv(const f32vec3& color) -> f32vec3 { return color_cast<model::rgb, model::hsv>(color); }
        ///MYL_NO_DISCARD constexpr auto rgb_to_lab(const f32vec3& color) -> f32vec3 { return color_cast<model::rgb, model::rgba>(color); }
        MYL_NO_DISCARD constexpr auto rgb_to_rgba(const f32vec3& color) -> f32vec4 { return color_cast<model::rgb, model::rgba>(color); }

        MYL_NO_DISCARD constexpr auto rgba_to_cmy(const f32vec4& color) -> f32vec3 { return color_cast<model::rgba, model::cmy>(color); }
        MYL_NO_DISCARD constexpr auto rgba_to_cmyk(const f32vec4& color) -> f32vec4 { return color_cast<model::rgba, model::cmyk>(color); }
        MYL_NO_DISCARD constexpr auto rgba_to_hsl(const f32vec4& color) -> f32vec3 { return color_cast<model::rgba, model::hsl>(color); }
        MYL_NO_DISCARD constexpr auto rgba_to_hsv(const f32vec4& color) -> f32vec3 { return color_cast<model::rgba, model::hsv>(color); }
        ///MYL_NO_DISCARD constexpr auto rgba_to_lab(const f32vec4& color) -> f32vec3 { return color_cast<model::rgba, model::lab>(color); }
        MYL_NO_DISCARD constexpr auto rgba_to_rgb(const f32vec4& color) -> f32vec3 { return color_cast<model::rgba, model::rgb>(color); }

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

        template<model M> MYL_NO_DISCARD constexpr auto blend(const model_type<M>& bg, const model_type<M>& fg) -> model_type<M>;

        ///template<> MYL_NO_DISCARD constexpr auto blend<model::cmy>(const f32vec3& bg, const f32vec3& fg) -> f32vec3;
        ///template<> MYL_NO_DISCARD constexpr auto blend<model::cmyk>(const f32vec4& bg, const f32vec4& fg) -> f32vec4;
        ///template<> MYL_NO_DISCARD constexpr auto blend<model::hsl>(const f32vec3& bg, const f32vec3& fg) -> f32vec3;
        ///template<> MYL_NO_DISCARD constexpr auto blend<model::hsv>(const f32vec3& bg, const f32vec3& fg) -> f32vec3;
        ///template<> MYL_NO_DISCARD constexpr auto blend<model::lab>(const f32vec3& bg, const f32vec3& fg) -> f32vec3;
        ///template<> MYL_NO_DISCARD constexpr auto blend<model::rgb>(const f32vec3& bg, const f32vec3& fg) -> f32vec3;
        
        template<>
        MYL_NO_DISCARD constexpr auto blend<model::rgba>(const f32vec4& bg, const f32vec4& fg) -> f32vec4 {
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
     
        template<model M> MYL_NO_DISCARD constexpr auto complement(const model_type<M>& color) -> model_type<M>;

        ///template<> MYL_NO_DISCARD constexpr auto complement<model::cmy>(const f32vec3& color) -> f32vec3;
        ///template<> MYL_NO_DISCARD constexpr auto complement<model::cmyk>(const f32vec4& color) -> f32vec4;
        ///template<> MYL_NO_DISCARD constexpr auto complement<model::hsl>(const f32vec3& color) -> f32vec3;
        ///template<> MYL_NO_DISCARD constexpr auto complement<model::hsv>(const f32vec3& color) -> f32vec3;
        ///template<> MYL_NO_DISCARD constexpr auto complement<model::lab>(const f32vec3& color) -> f32vec3;
        
        template<>
        MYL_NO_DISCARD constexpr auto complement<model::rgb>(const f32vec3& color) -> f32vec3 {
            return { 1.f - color.r, 1.f - color.g, 1.f - color.b };
        }

        template<>
        MYL_NO_DISCARD constexpr auto complement<model::rgba>(const f32vec4& color) -> f32vec4 {
            return f32vec4(complement<model::rgb>({ color.r, color.g, color.b }), color.a);
        }

        template<model M> MYL_NO_DISCARD constexpr auto grayscale(const model_type<M>& color) -> model_type<M>;

        ///template<> MYL_NO_DISCARD constexpr auto grayscale<model::cmy>(const f32vec3& color) -> f32vec3;
        ///template<> MYL_NO_DISCARD constexpr auto grayscale<model::cmyk>(const f32vec4& ccolor) -> f32vec4;
        ///template<> MYL_NO_DISCARD constexpr auto grayscale<model::hsl>(const f32vec3& color) -> f32vec3;
        ///template<> MYL_NO_DISCARD constexpr auto grayscale<model::hsv>(const f32vec3& color) -> f32vec3;
        ///template<> MYL_NO_DISCARD constexpr auto grayscale<model::lab>(const f32vec3& color) -> f32vec3;
        
        template<>
        MYL_NO_DISCARD constexpr auto grayscale<model::rgb>(const f32vec3& color) -> f32vec3 {
            constexpr f32 thrid = 1.f / 3.f;
            return f32vec3((color.r + color.g + color.b) * thrid);
        }

        template<>
        MYL_NO_DISCARD constexpr auto grayscale<model::rgba>(const f32vec4& color) -> f32vec4 {
            return f32vec4(grayscale<model::rgb>({ color.r, color.g, color.b }), color.a);
        }

        template<model M> MYL_NO_DISCARD constexpr auto mix(const model_type<M>& c1, const model_type<M>& c2, f32 percentage) -> model_type<M>;

        ///template<> MYL_NO_DISCARD constexpr auto mix<model::cmy>(const f32vec3& c1, const f32vec3& c2, f32 percentage) -> f32vec3;
        ///template<> MYL_NO_DISCARD constexpr auto mix<model::cmyk>(const f32vec4& c1, const f32vec4& c2, f32 percentage) -> f32vec4;
        ///template<> MYL_NO_DISCARD constexpr auto mix<model::hsl>(const f32vec3& c1, const f32vec3& c2, f32 percentage) -> f32vec3;
        ///template<> MYL_NO_DISCARD constexpr auto mix<model::hsv>(const f32vec3& c1, const f32vec3& c2, f32 percentage) -> f32vec3;
        ///template<> MYL_NO_DISCARD constexpr auto mix<model::lab>(const f32vec3& c1, const f32vec3& c2, f32 percentage) -> f32vec3;
        
        template<>
        MYL_NO_DISCARD constexpr auto mix<model::rgb>(const f32vec3& c1, const f32vec3& c2, f32 percentage) -> f32vec3 {
            return lerp(c1, c2, percentage);
        }

        template<>
        MYL_NO_DISCARD constexpr auto mix<model::rgba>(const f32vec4& c1, const f32vec4& c2, f32 percentage) -> f32vec4 {
            return lerp(c1, c2, percentage);
        }
    }
}
