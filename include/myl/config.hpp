#pragma once
// [NOTE]: The macros may be uncommented or passed into a build tool to enable their functionality.

//////////////////////////////////////// General Macros ////////////////////////////////////////

/* MYL_NO_DEPRECATED_WARNINGS
* When defined, disables the deprecated attribute for use in the MYL_DEPRECATED & MYL_DEPRECATED_M macros.
*/
//#define MYL_NO_DEPRECATED_WARNINGS

/* MYL_NO_ASSERT
* When defined, disables asserts for use with the MYL_ASSERT macro.
* Asserts aren't enabled during a non-debug build, if this functionality is needed use MYL_VERIFY.
*/
//#define MYL_NO_ASSERT

/* MYL_NO_VERIFY
* When defined, disables asserts for use with the MYL_VERIFY macro regardless of build type.
*/
//#define MYL_NO_VERIFY

/* MYL_NO_EXCEPTIONS
* When defined, disables MYL from using exceptions. A MYL_ASSERT will replace the MYL_THROW_IF marco
*/
//#define MYL_NO_EXCEPTIONS

/* MYL_NO_INTRINSICS
* When defined, disables MYL from defining macros related to intrinsics.
*/
//#define MYL_NO_INTRINSICS

/* MTL_EXTEND_FORMAT
* When defined extends std::format to the following types;
* - vec2
* - vec3
* - vec4
*/
//#define MTL_EXTEND_FORMAT

//////////////////////////////////////// Math Related Macros ////////////////////////////////////////
