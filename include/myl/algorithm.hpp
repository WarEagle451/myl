#pragma once
#include <myl/definitions.hpp>
#include <myl/type.hpp>

#include <array>
#include <cmath>
#include <iterator>
#include <limits>

namespace myl {
    template<std::input_iterator It>
    MYL_NO_DISCARD constexpr auto median(It begin, It end) -> std::common_type_t<typename It::value_type, float> {
        using output_t = std::common_type_t<typename It::value_type, float>;

        if (begin == end) // The median of an empty set is undefined, therefore return a quiet nan
            return std::numeric_limits<output_t>::quiet_NaN();

        if constexpr (std::contiguous_iterator<It>) {
#ifdef MYL_DEBUG
            MYL_ASSERT(begin < end, "Asserts when 'begin' comes after 'end', this is not valid with contiguous storage containers");
            if (begin > end)
                return std::numeric_limits<output_t>::signaling_NaN();
#endif
            const std::size_t container_size = end - begin;
            if (container_size % 2 == 0) {
                // Even
                const It over_mid_point = begin + (container_size / 2);
                return (static_cast<output_t>(*over_mid_point) + static_cast<output_t>(*(over_mid_point - 1))) / 2;
            }
            else // Odd
                return *(begin + (container_size - 1) / 2);
        }
        else {
            const std::size_t container_size = std::distance(begin, end);
            if (container_size % 2 == 0) {
                // Even
                const It over_mid_point = std::next(begin, container_size / 2);
                return (static_cast<output_t>(*over_mid_point) + static_cast<output_t>(*std::prev(over_mid_point))) / 2;
            }
            else // Odd
                return *std::next(begin, (container_size - 1) / 2);
        }
    }

    template<typename... Args>
    MYL_NO_DISCARD constexpr auto median(Args&&... args) -> std::common_type_t<float, Args...> {
        using value_type = std::common_type_t<float, Args...>;

        constexpr std::size_t size = sizeof...(args);
        const std::array<value_type, size> a{ std::forward<value_type>(args)... }; /// Is this undefined behaviour?
        return median(a.begin(), a.end());
    }

    template<floating_point T>
    MYL_NO_DISCARD constexpr auto approx(const T& a, const T& b) -> bool { /// MYTODO: This doesn't always work, refer to color test
        /// tolerance is std::abs(a - b) < epsilon
        return b == std::nextafter(a, b);
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto min(const T& a, const T& b) -> const T& {
        return a < b ? a : b;
    }

    template<typename T, same_as<T>... Args>
    MYL_NO_DISCARD constexpr auto min(const T& a, const T& b, const Args&... args) -> const T& {
        return min(min(a, b), args...);
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto max(const T& a, const T& b) -> const T& {
        return a > b ? a : b;
    }

    template<typename T, same_as<T>... Args>
    MYL_NO_DISCARD constexpr auto max(const T& a, const T& b, const Args&... args) -> const T& {
        return max(max(a, b), args...);
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto clamp(const T& v, const T& min, const T& max) -> const T& {
        return v < min ? min : v > max ? max : v;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto floor(const T& v, const T& floor) -> const T& {
        return v > floor ? v : floor;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto ceil(const T& v, const T& ceil) -> const T& {
        return v > ceil ? ceil : v;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto difference(const T& a, const T& b) -> T {
        return a > b ? a - b : b - a;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto sign(const T v) -> T {
        return (static_cast<T>(0) < v) - (v < static_cast<T>(0));
    }
}
