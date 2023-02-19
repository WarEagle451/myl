#pragma once

namespace myl::constants {
	template<typename T> inline constexpr T e					= static_cast<T>(2.71828182845904523536); //@brief Euler's number
	template<typename T> inline constexpr T euler				= static_cast<T>(0.57721566490153286060); //@brief Euler-mascheroni constant
	template<typename T> inline constexpr T egamma				= static_cast<T>(1.78107241799019798523);
	template<typename T> inline constexpr T golden_ratio		= static_cast<T>(1.61803398874989484820); //@brief Phi

	template<typename T> inline constexpr T half_pi				= static_cast<T>(1.57079632679489661923);
	template<typename T> inline constexpr T inverse_pi			= static_cast<T>(0.31830988618379067153);
	template<typename T> inline constexpr T pi					= static_cast<T>(3.14159265358979323846);
	template<typename T> inline constexpr T quater_pi			= static_cast<T>(0.78539816339744830961);
	template<typename T> inline constexpr T two_over_pi			= static_cast<T>(0.63661977236758134308);
	template<typename T> inline constexpr T two_pi				= static_cast<T>(6.28318530717958647692); //@brief Tau

	template<typename T> inline constexpr T cbrt_three			= static_cast<T>(1.44224957030740838232); //@brief Cube root of 3
	template<typename T> inline constexpr T cbrt_two			= static_cast<T>(1.25992104989487316476); //@brief Cube root of 2
	template<typename T> inline constexpr T inverse_sqrt_three	= static_cast<T>(0.57735026918962576450); //@brief Inverse square root of 3
	template<typename T> inline constexpr T inverse_sqrt_two	= static_cast<T>(0.70710678118654752440); //@brief Inverse square root of 2
	template<typename T> inline constexpr T ln2					= static_cast<T>(0.69314718055994530941); //@brief Natural log of 2
	template<typename T> inline constexpr T sqrt_five			= static_cast<T>(2.23606797749978969640); //@brief Square root of 5
	template<typename T> inline constexpr T sqrt_three			= static_cast<T>(1.73205080756887729352); //@brief Square root of 3, Theodorus' constant
	template<typename T> inline constexpr T sqrt_two			= static_cast<T>(1.41421356237309504880); //@brief Square root of 2, Pythagoras constant
	template<typename T> inline constexpr T twelfth_root_two	= static_cast<T>(1.05946309435929526456);
}