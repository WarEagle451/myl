#pragma once
// [NOTE]: The macros may be uncommented or passed into a build tool to enable their functionality.

//////////////////////////////////////// General Macros ////////////////////////////////////////

/* MYL_DISABLE_DEPRECATED_WARNINGS
* When defined, disables the deprecated attribute for use in the MYL_DEPRECATED & MYL_DEPRECATED_M macros.
*/
//#define MYL_DISABLE_DEPRECATED_WARNINGS

/* MYL_DISABLE_ASSERT
* When defined, disables asserts for use with the MYL_ASSERT macro.
* Asserts aren't enabled during a non-debug build, if this functionality is needed use MYL_VERIFY.
*/
//#define MYL_DISABLE_ASSERT

/* MYL_DISABLE_VERIFY
* When defined, disables asserts for use with the MYL_VERIFY macro regardless of build type.
*/
//#define MYL_DISABLE_VERIFY

/* MYL_NO_INTRINSICS
* When defined, disables MYL from defining macros related to intrinsics.
*/
// #define MYL_NO_INTRINSICS

//////////////////////////////////////// Math Related Macros ////////////////////////////////////////
