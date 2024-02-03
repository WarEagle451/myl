#pragma once
namespace myl::numbers {
	template<typename T> inline constexpr T e					= static_cast<T>(2.7182818284590452353602874713526); //@brief Euler's number
	template<typename T> inline constexpr T euler				= static_cast<T>(0.5772156649015328606065120900824); //@brief Euler-mascheroni constant
	template<typename T> inline constexpr T egamma				= static_cast<T>(1.7810724179901979852365041031071); //@brief e^euler
	template<typename T> inline constexpr T golden_ratio		= static_cast<T>(1.6180339887498948482045868343656); //@brief Phi

	template<typename T> inline constexpr T half_pi				= static_cast<T>(1.5707963267948966192313216916397);
	template<typename T> inline constexpr T sqrt_half_pi		= static_cast<T>(1.2533141373155002512078826424055);
	template<typename T> inline constexpr T inverse_pi			= static_cast<T>(0.3183098861837906715377675267450);
	template<typename T> inline constexpr T inverse_sqrt_pi		= static_cast<T>(0.5641895835477562869480794515607);
	template<typename T> inline constexpr T pi					= static_cast<T>(3.1415926535897932384626433832795);
	template<typename T> inline constexpr T quater_pi			= static_cast<T>(0.7853981633974483096156608458198);
	template<typename T> inline constexpr T sqrt_pi				= static_cast<T>(1.7724538509055160272981674833411);
	template<typename T> inline constexpr T two_over_pi			= static_cast<T>(0.6366197723675813430755350534900);
	template<typename T> inline constexpr T two_over_sqrt_pi	= static_cast<T>(1.1283791670955125738961589031215);
	template<typename T> inline constexpr T tao					= static_cast<T>(6.2831853071795864769252867665590); //@brief 2pi
	template<typename T> inline constexpr T sqrt_tao			= static_cast<T>(2.5066282746310005024157652848110); //@brief square root of 2pi

	template<typename T> inline constexpr T cbrt2				= static_cast<T>(1.2599210498948731647672106072782); //@brief Cube root of 2
	template<typename T> inline constexpr T cbrt3				= static_cast<T>(1.4422495703074083823216383107801); //@brief Cube root of 3
	template<typename T> inline constexpr T inverse_sqrt2		= static_cast<T>(0.7071067811865475244008443621048); //@brief Inverse square root of 2
	template<typename T> inline constexpr T inverse_sqrt3		= static_cast<T>(0.5773502691896257645091487805019); //@brief Inverse square root of 3
	template<typename T> inline constexpr T ln2					= static_cast<T>(0.6931471805599453094172321214581); //@brief Natural log of 2
	template<typename T> inline constexpr T ln10				= static_cast<T>(2.3025850929940456840179914546843); //@brief Natural log of 2
	template<typename T> inline constexpr T log2e				= static_cast<T>(1.4426950408889634073599246810018);
	template<typename T> inline constexpr T log10e				= static_cast<T>(0.4342944819032518276511289189166);
	template<typename T> inline constexpr T sqrt2				= static_cast<T>(1.4142135623730950488016887242096); //@brief Square root of 2, Pythagoras constant
	template<typename T> inline constexpr T sqrt3				= static_cast<T>(1.7320508075688772935274463415058); //@brief Square root of 3, Theodorus' constant
	template<typename T> inline constexpr T sqrt5				= static_cast<T>(2.2360679774997896964091736687312); //@brief Square root of 5
	template<typename T> inline constexpr T twelfth_root_two	= static_cast<T>(1.0594630943592952645618252949463);
}