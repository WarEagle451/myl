#pragma once
//////////////////////////////////////// General Macros ////////////////////////////////////////

/* MYL_ENABLE_DEPRECATED_WARNINGS
* When defined, enables the deprecated attribute for use in the MYL_DEPRECATED & MYL_DEPRECATED_M macros.
*/
#define MYL_ENABLE_DEPRECATED_WARNINGS

/* MYL_ENABLE_ASSERT
* When defined, enables asserts for use with the MYL_ASSERT macro.
* Asserts aren't enabled during a non-debug build, if this functionality is needed use MYL_VERIFY.
*/
#define MYL_ENABLE_ASSERT

/* MYL_ENABLE_VERIFY
* When defined, enables asserts for use with the MYL_VERIFY macro regardless of build type.
*/
#define MYL_ENABLE_VERIFY

//////////////////////////////////////// Math Related Macros ////////////////////////////////////////
