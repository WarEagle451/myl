#pragma once
#define MYL_STRINGIFY(...) #__VA_ARGS__

#define MYL_ARG_STRINGIFY(x) MYL_STRINGIFY(x)
#define MYL_ARG_DISCARD(discard, ...) __VA_ARGS__

#define MYL_ARG_1(a1, ...) a1
#define MYL_ARG_2(a1, a2, ...) a2
#define MYL_ARG_3(a1, a2, a3, ...) a3
#define MYL_ARG_4(a1, a2, a3, a4, ...) a4
#define MYL_ARG_5(a1, a2, a3, a4, a5, ...) a5
#define MYL_ARG_6(a1, a2, a3, a4, a5, a6, ...) a6
#define MYL_ARG_7(a1, a2, a3, a4, a5, a6, a7, ...) a7
#define MYL_ARG_8(a1, a2, a3, a4, a5, a6, a7, a8, ...) a8
#define MYL_ARG_9(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) a9

// Detection for C++20 or C++20 and MSVC's new preprocessor, MSVC's old preprocessor doesn't support __VA_OPT__
#if __cplusplus >= 202002L || (defined(MYL_COMPILER_MSVC) && _MSVC_LANG >= 202002L && defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL == 0)
#   define MYL_VA_EMPTY(...) (1 __VA_OPT__(== 0))
#else
#   define MYL_VA_EMPTY(...) (sizeof((char[]){(#__VA_ARGS__)}) == 1)
#endif
