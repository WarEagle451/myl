#pragma once
#include <myl/definitions.hpp>

#include <cmath>

namespace myl {
    template<typename T>
    MYL_NO_DISCARD constexpr auto factorial(T n) -> T {
        return std::tgamma(n + static_cast<T>(1));
    }
}
