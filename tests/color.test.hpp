#pragma once
#include <myl_wip/color.hpp>

namespace myl::test {
    auto color_cast() ->  {
        using namespace color;
    
        color_cast<model::cmy, model::cmy>({ 0.f, 1.f, .4f });

        
        color_cast<model::cmy, model::cmyk>();
        color_cast<model::cmy, model::hsl>();
        color_cast<model::cmy, model::hsv>();
        color_cast<model::cmy, model::lab>();
        color_cast<model::cmy, model::rgb>();
        color_cast<model::cmy, model::rgba>();
        
        color_cast<model::cmyk, model::cmy>();
        color_cast<model::cmyk, model::cmyk>();
        color_cast<model::cmyk, model::hsl>();
        color_cast<model::cmyk, model::hsv>();
        color_cast<model::cmyk, model::lab>();
        color_cast<model::cmyk, model::rgb>();
        color_cast<model::cmyk, model::rgba>();
        
        color_cast<model::hsl, model::cmy>();
        color_cast<model::hsl, model::cmyk>();
        color_cast<model::hsl, model::hsl>();
        color_cast<model::hsl, model::hsv>();
        color_cast<model::hsl, model::lab>();
        color_cast<model::hsl, model::rgb>();
        color_cast<model::hsl, model::rgba>();
        
        color_cast<model::hsv, model::cmy>();
        color_cast<model::hsv, model::cmyk>();
        color_cast<model::hsv, model::hsl>();
        color_cast<model::hsv, model::hsv>();
        color_cast<model::hsv, model::lab>();
        color_cast<model::hsv, model::rgb>();
        color_cast<model::hsv, model::rgba>();
        
        color_cast<model::lab, model::cmy>();
        color_cast<model::lab, model::cmyk>();
        color_cast<model::lab, model::hsl>();
        color_cast<model::lab, model::hsv>();
        color_cast<model::lab, model::lab>();
        color_cast<model::lab, model::rgb>();
        color_cast<model::lab, model::rgba>();
        
        color_cast<model::rgb, model::cmy>();
        color_cast<model::rgb, model::cmyk>();
        color_cast<model::rgb, model::hsl>();
        color_cast<model::rgb, model::hsv>();
        color_cast<model::rgb, model::lab>();
        color_cast<model::rgb, model::rgb>();
        color_cast<model::rgb, model::rgba>();
        
        color_cast<model::rgba, model::cmy>();
        color_cast<model::rgba, model::cmyk>();
        color_cast<model::rgba, model::hsl>();
        color_cast<model::rgba, model::hsv>();
        color_cast<model::rgba, model::lab>();
        color_cast<model::rgba, model::rgb>();
        color_cast<model::rgba, model::rgba>();
    }
}
