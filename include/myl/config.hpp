#pragma once
// This file contains macros that can be defined or undefined (commented out) that will change some behaviour of My Library.

/* MYL_DEFINE_TYPES:
* Allows for certain types to be defined in the global namespace, they are the following;
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
#define MYL_TYPE_SIZE_CHECK

/* MYL_FORCE_RIGHT_HANDED:
* Forces MYL to use right handed math when applicable.
* [NOTE]: The left/right handed functions are still available with the _lh/_rh suffixes.
*/
//#define MYL_FORCE_RIGHT_HANDED

/* MYL_FORCE_DEPTH_ZERO_TO_ONE:
* Forces MYL to use functions that are dependant on normalized device coordinates (NDC).
* [NOTE]: The negative one to one/zero to one functions are still available with the _00/_01 suffixes.
*/
#define MYL_FORCE_DEPTH_ZERO_TO_ONE

/* MYL_EXPERIMENTAL:
* Enables code in the myl/ex directory.
* [NOTE]: Much of this code may be unfinished, buggy or may not compile at all.
*/
#define MYL_EXPERIMENTAL