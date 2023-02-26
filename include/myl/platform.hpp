#pragma once
// Compiler detection macros

#if defined(_MSC_VER)
#	define MYL_COMPILER_MSVC _MSC_VER
#elif defined(__INTEL_COMPILER)
#	define MYL_COMPILER_INTEL __INTEL_LLVM_COMPILER
#elif defined(__NVCC__)
#	define MYL_COMPILER_NVCC (__CUDACC_VER_MAJOR__ * 10000 + __CUDACC_VER_MINOR__ * 100 + __CUDACC_VER_BUILD__)
#elif defined(__clang__)
#	define MYL_COMPILER_CLANG __clang_major__
#elif defined(__GNUC__)
#	define MYL_COMPILER_GCC (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#	warning "Unknown compiler!"
#	define MYL_COMPILER_UNKNOWN
#endif

// Processor architecture detection macros for:
// - SSE
// - SSE2
// - SSE3
// - SSSE3
// - SSE4.1
// - SSE4.2
// - SSE4a
// - AVX
// - AVX2
// - AVX512

#if defined(__SSE__)
#	define MYL_ARCHITECTURE_SSE __SSE__
#elif defined(_M_IX86_FP) && _M_IX86_FP == 1 // Visual Studio
#	define MYL_ARCHITECTURE_SSE 1
#else
#	define MYL_ARCHITECTURE_SSE 0
#endif

#if defined(__SSE2__)
#	define MYL_ARCHITECTURE_SSE2 __SSE2__
#elif defined(_M_IX86_FP) && _M_IX86_FP == 2 // Visual Studio
#	define MYL_ARCHITECTURE_SSE2 1
#else
#	define MYL_ARCHITECTURE_SSE2 0
#endif

#if defined(__SSE3__)
#	define MYL_ARCHITECTURE_SSE3 __SSE3__
#else
#	define MYL_ARCHITECTURE_SSE3 0
#endif

#if defined(__SSSE3__)
#	define MYL_ARCHITECTURE_SSSE3 __SSSE3__
#else
#	define MYL_ARCHITECTURE_SSSE3 0
#endif

#if defined(__SSE4_1__)
#	define MYL_ARCHITECTURE_SSE4_1 __SSE4_1__
#else
#	define MYL_ARCHITECTURE_SSE4_1 0
#endif

#if defined(__SSE4_2__)
#	define MYL_ARCHITECTURE_SSE4_2 __SSE4_2__
#else
#	define MYL_ARCHITECTURE_SSE4_2 0
#endif

#if defined(__SSE4_A__)
#	define MYL_ARCHITECTURE_SSE4A __SSE4_A__
#else
#	define MYL_ARCHITECTURE_SSE4A 0
#endif

#if defined(__AVX__)
#	define MYL_ARCHITECTURE_AVX __AVX__
#else
#	define MYL_ARCHITECTURE_AVX 0
#endif

#if defined(__AVX2__)
#	define MYL_ARCHITECTURE_AVX2 __AVX2__
#else
#	define MYL_ARCHITECTURE_AVX2 0
#endif

#if defined(__AVX512BW__)
#	define MYL_ARCHITECTURE_AVX512BW __AVX512BW__
#else
#	define MYL_ARCHITECTURE_AVX512BW 0
#endif

#if defined(__AVX512CD__)
#	define MYL_ARCHITECTURE_AVX512CD __AVX512CD__
#else
#	define MYL_ARCHITECTURE_AVX512CD 0
#endif

#if defined(__AVX512DQ__)
#	define MYL_ARCHITECTURE_AVX512DQ __AVX512DQ__
#else
#	define MYL_ARCHITECTURE_AVX512DQ 0
#endif

#if defined(__AVX512ER__)
#	define MYL_ARCHITECTURE_AVX512ER __AVX512ER__
#else
#	define MYL_ARCHITECTURE_AVX512ER 0
#endif

#if defined(__AVX512F__)
#	define MYL_ARCHITECTURE_AVX512F __AVX512F__
#else
#	define MYL_ARCHITECTURE_AVX512F 0
#endif

#if defined(__AVX512PF__)
#	define MYL_ARCHITECTURE_AVX512PF __AVX512PF__
#else
#	define MYL_ARCHITECTURE_AVX512PF 0
#endif

#if defined(__AVX512VL__)
#	define MYL_ARCHITECTURE_AVX512VL __AVX512VL__
#else
#	define MYL_ARCHITECTURE_AVX512VL 0
#endif

// Platform detection macros

#if defined(_WIN32) || defined(_WIN64) || defined(__TOS_WIN__)
#	define MYL_PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
#	define MYL_PLATFORM_APPLE
#	include <TargetConditionals.h>
#	if TARGET_IPHONE_SIMULATOR
#		define MYL_PLATFORM_IOS
#		define MYL_PLATFORM_IOS_SIMULATOR
#	elif TARGET_OS_IPHONE
#		define MYL_PLATFORM_IOS
#	elif TARGET_OS_MAC
#		define MYL_PLATFORM_MAC_OS
#	else
#		warning "Unknown Apple platform!"
#		define MYL_PLATFORM_APPLE_UNKNOWN
#	endif
#elif defined(__ANDROID__)
#	define MYL_PLATFORM_ANDROID
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_lineux__)
#	define MYL_PLATFORM_LINUX
#elif defined(unix) || defined(__unix) || defined(__unix__)
#	define MYL_PLATFORM_UNIX
#elif defined(_POSIX_VERSION)
#	define MYL_PLATFORM_POSIX
#else
#	warning "Unknown platform!"
#	define MYL_PLATFORM_UNKNOWN
#endif