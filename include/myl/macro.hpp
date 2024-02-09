#pragma once
#define MYL_STRINGIFY(...) #__VA_ARGS__
#define MYL_STRINGIFY_ARG(x) MYL_STRINGIFY(x)

// Detection for C++20 or C++20 and MSVC's new preprocessor, which supports __VA_OPT__
#if __cplusplus >= 202002L || (defined(MYL_COMPILER_MSVC) && _MSVC_LANG >= 202002L && defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL == 0)
#   define MYL_VA_EMPTY(...) (1 __VA_OPT__(== 0))
#else
#   define MYL_VA_EMPTY(...) (sizeof((char[]){(#__VA_ARGS__)}) == 1)
#endif