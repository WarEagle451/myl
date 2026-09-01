#pragma once
#include <cmath>
#include <cstdint>
#include <limits>

#include <myl/definitions.hpp>

namespace myl {
    template<typename T>
    struct basic_fraction { /// MAYBE MAke another type called mixed_fraction 
        using value_type = T;

        bool sign;
        value_type whole;
        value_type numerator;
        value_type denominator;



        /// MYTODO: Operatrors
        /// + - * / 
        /// unary -
        /// -- ++
        /// == != < <= > >=
        /// += -= *= /=
        /// =
        /// &&
        /// ||
        /// logical - / !
        /// %
        /// bitwise
        
        /// Make it so if the numerator is going to overflow that is will overflow into the whole

        MYL_NO_DISCARD constexpr operator bool() const {
            /// Should { true, 0, 1, 0 } be treated as true or false?
            return whole != 0 && numerator != 0;
        }

        MYL_NO_DISCARD constexpr operator float() const {
            if constexpr (std::numeric_limits<float>::is_iec559) {
                /// MYTODO
            }
            else
                return static_cast<float>(numerator) / static_cast<float>(denominator) * (sign ? -1.f : 1.f);
        }

        MYL_NO_DISCARD constexpr operator double() const {
            if constexpr (std::numeric_limits<double>::is_iec559) {
                /// MYTODO
            }
            else
                return static_cast<double>(numerator) / static_cast<double>(denominator) * (sign ? -1.0 : 1.0);
        }

        MYL_NO_DISCARD constexpr operator long double() const {
            if constexpr (std::numeric_limits<long double>::is_iec559) {
                /// MYTODO
            }
            else
                return static_cast<long double>(numerator) / static_cast<long double>(denominator) * static_cast<long double>(sign ? -1 : 1);
        }
    };

    using fraction = basic_fraction<std::uintmax_t>;
}

namespace std {
    template<>
    class numeric_limits<myl::fraction> {
    public:
        static constexpr bool is_specialized                          = true;
        static constexpr bool is_signed                               = true;
        static constexpr bool is_integer                              = false;
        static constexpr bool is_exact                                = true;
        static constexpr bool has_infinity                            = false;
        static constexpr bool has_quiet_NaN                           = false; ///a aaaaaaaaaaaaaaa
        static constexpr bool has_signaling_NaN                       = false; /// aaaaaaaaaaaaaaa
        MYL_DEPRECATED static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
        MYL_DEPRECATED static constexpr bool has_denorm_loss          = false;
        static constexpr float_round_style round_style                = float_round_style::round_indeterminate;
        static constexpr bool is_iec559                               = false;
        static constexpr bool is_bounded                              = true;
        static constexpr bool is_modulo                               = ;
        static constexpr int digits                                   = numeric_limits<int>::infinity();
        static constexpr int digits10                                 = ;
        static constexpr int max_digits10                             = 0;
        static constexpr int radix                                    = ;
        static constexpr int min_exponent                             = 0;
        static constexpr int min_exponent10                           = 0;
        static constexpr int max_exponent                             = 0;
        static constexpr int max_exponent10                           = 0;
        static constexpr bool traps                                   = true;
        static constexpr bool tinyness_before                         = false;

        MYL_NO_DISCARD static constexpr auto min() noexcept -> myl::fraction {
            return myl::fraction{ true, numeric_limits<myl::fraction::value_type>::max(), numeric_limits<myl::fraction::value_type>::max(), 1 };
        }

        MYL_NO_DISCARD static constexpr auto lowest() noexcept -> myl::fraction {
            return myl::fraction{ true, numeric_limits<myl::fraction::value_type>::max(), numeric_limits<myl::fraction::value_type>::max(), 1 };
        }

        MYL_NO_DISCARD static constexpr auto max() noexcept -> myl::fraction {
            return myl::fraction{ false, numeric_limits<myl::fraction::value_type>::max(), numeric_limits<myl::fraction::value_type>::max(), 1 };
        }

        MYL_NO_DISCARD static constexpr auto epsilon() noexcept -> myl::fraction {
            return myl::fraction{ false, 0, 0, 1 };
        }

        MYL_NO_DISCARD static constexpr auto round_error() noexcept -> myl::fraction {
            return myl::fraction{ false, 0, 0, 1 };
        }

        MYL_NO_DISCARD static constexpr auto infinity() noexcept -> myl::fraction {

        }

        MYL_NO_DISCARD static constexpr auto quiet_NaN() noexcept -> myl::fraction {

        }

        MYL_NO_DISCARD static constexpr auto signaling_NaN() noexcept -> myl::fraction {
            /// Should { true, 0, 1, 0 } be treated or something liek be treated as NaN
        }

        MYL_NO_DISCARD static constexpr auto denorm_min() noexcept -> myl::fraction {

        }
    };
}
