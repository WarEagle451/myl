#pragma once
#include <myl/algorithm.hpp>

namespace myl {
    template<typename N, typename T = f32>
    MYL_NO_DISCARD constexpr auto lerp(N a, N b, T percentage) -> N {
        return a + ((b - a) * percentage);
    }

    template<typename N, typename T = f32>
    MYL_NO_DISCARD constexpr auto inverse_lerp(N a, N b, T value) -> N {
        return (value - a) / (b - a);
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto step(T edge, T value) -> T {
        return edge > value ? 0 : 1;
    }

    template<typename N, typename T = f32>
    MYL_NO_DISCARD constexpr auto smoothstep(N edge0, N edge1, T percentage) -> N {
        const N t = clamp((percentage - edge0) / (edge1 - edge0), 0, 1);
        return t * t * (static_cast<N>(3) - static_cast<N>(2) * t)
    }
}
