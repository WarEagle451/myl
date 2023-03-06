#pragma once
// This file contains macros that can be defined or undefined (commented out) that will change some behaviour of My Library.
// Additionally, if one of these macros should only be defined for a portion of code,
// one can define the macro before including the file and undef it at the end of that code

//////////////////////////////////////// General Macros ////////////////////////////////////////

/* MYL_DEFINE_TYPES:
* Defines the following types in the global namespace;
*	- i8, i16, i32, i64
*	- u8, u16, u32, u64
*	- f32, f64
*	- isize, usize
*	- vec2, vec3, vec4
*	- mat2x2, mat2x3, mat2x4, mat3x2, mat3x3, mat3x4, mat4x2, mat4x3, mat4x4
*	- quat
*/
//#define MYL_DEFINE_TYPES

/* MYL_TYPE_SIZE_CHECK:
* Checks using a static_assert that a type/class/struct is of a certain size in bytes.
*/
//#define MYL_TYPE_SIZE_CHECK

/* MYL_EXPERIMENTAL:
* Enables code in the myl/ex directory.
* [NOTE]: Much of this code may be unfinished, buggy or may not compile at all.
*/
//#define MYL_EXPERIMENTAL

/* MYL_ROUND_CONSTANTS
* Rounds the 32nd digit of constants if applicable.
*/
#define MYL_ROUND_CONSTANTS

/* MYL_ENABLE_DEPRECATED_WARNINGS
* Enables the deprecated attribute through the MYL_DEPRECATED and MYL_DEPRECATED_M macros.
*/
#define MYL_ENABLE_DEPRECATED_WARNINGS

/* MYL_DISABLE_ASSERTS
* Disables asserts regardless of build type
*/
//#define MYL_DISABLE_ASSERTS

//////////////////////////////////////// Math Related Macros ////////////////////////////////////////

/* MYL_FORCE_RIGHT_HANDED:
* Forces MYL to use right handed math when applicable.
* [NOTE]: The left/right handed functions are still available with the _lh/_rh suffixes.
*/
//#define MYL_FORCE_RIGHT_HANDED

/* MYL_FORCE_DEPTH_ZERO_TO_ONE:
* Forces MYL to use functions that are dependant on normalized device coordinates (NDC) of 0 to 1.
* [NOTE]: The negative 1 to 1 and 0 to 1 functions are still available with the _11/_01 suffixes.
*/
#define MYL_FORCE_DEPTH_ZERO_TO_ONE

/* MYL_COMPONENT_WISE
* Enables functions that involve component wise math on vectors.
*/
//#define MYL_ENABLE_COMPONENT_WISE