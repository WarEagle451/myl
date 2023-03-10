#pragma once
#include <myl/version.hpp>

// Compiler detection macros

#if defined(_MSC_VER) /// MYTodo: Normalize like the others?
#	define MYL_COMPILER_MSVC _MSC_VER
#elif defined(__clang__) /// MYTodo: Distingish Apple clang (__apple_build_version__ ), llvm clang, ibm clang
#	define MYL_COMPILER_CLANG MYL_MAKE_VERSION(__clang_major__, __clang_minor__, __clang_patchlevel__)
#elif defined(__GNUC__)
#	if defined(__GNUC_PATCHLEVEL__)
#		define MYL_COMPILER_GCC MYL_MAKE_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#	else
#		define MYL_COMPILER_GCC MYL_MAKE_VERSION(__GNUC__, __GNUC_MINOR__, 0)
#	endif
#else
#	warning "Unknown compiler! Myl may not compile and some features may not work!"
#	define MYL_COMPILER_UNKNOWN
#endif

#ifdef MYL_COMPILER_MSVC
#	if _MSVC_LANG <= 202002L // MSVC for C++17
#		error "Compile for C++20 or higher!"
#	endif
#elif !defined(__cplusplus) || __cplusplus < 202202L // C++20
#	error "This project requires a compiler for C++20 or higher!"
#endif

// OS detection

#if defined(__ANDROID__)
#	define MYL_OS_ANDROID __ANDROID__
#elif defined(__APPLE__) || defined(macintosh) || defined(Macintosh) || defined(__MACH__)
#	include <TargetConditionals.h>
#	if defined(macintosh) || defined(Macintosh) || defined(__MACH__)
#		if defined(__APPLE__) && define(__MACH__)
#			define MYL_OS_MAC MYL_MAKE_VERSION(10, 0, 0)
#		else
#			define MYL_OS_MAC MYL_MAKE_VERSION(9, 0, 0)
#		endif
#	elif defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
#		define MYL_OS_IOS (__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ * 1000)
#	else
#		warning "Unknown Apple OS!"
#		define MYL_OS_APPLE_UNKNOWN
#	endif
#	ifdef(TARGET_OS_SIMULATOR) && TARGET_OS_SIMULATOR == 1
#		define MYL_OS_IOS_SIMULATOR
#	elif TARGET_OS_WIN32
#		define MYL_OS_WINDOWS
#	elif TARGET_OS_UNIX
#		define MYL_OS_UNIX
#	elif TARGET_OS_EMBEDDED
#		define MYL_OS_APPLE_EMBEDDED
#	endif
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
#	define MYL_OS_LINUX
#elif defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
#	define MYL_OS_UNIX
#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#	define MYL_OS_WINDOWS
#else
#	warning "Unknown OS!"
#	define MYL_OS_UNKNOWN
#endif

// Platform detection macros

#ifdef MYL_OS_IOS
#	if defined(TARGET_IPHONE_SIMULATOR) && (TARGET_IPHONE_SIMULATOR == 1)
#		define MYL_PLATFORM_IPHONE_SIMULATOR
#	elif defined(TARGET_OS_IPHONE)
#		define MYL_PLATFORM_IPHONE
#	else
#		warning "Unknown IOS platform!"
#		define MYL_PLATFORM_IOS_UNKNOWN
#	endif
#elif defined(MYL_OS_WINDOWS)
#	include <winapifamily.h>
#	if WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP
#		define MYL_PLATFORM_WINDOWS_DESKTOP
#	elif WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
#		define MYL_PLATFORM_WINDOWS_PHONE
#	elif WINAPI_FAMILY == WINAPI_FAMILY_SERVER
#		define MYL_PLATFORM_WINDOWS_SERVER
#	elif WINAPI_FAMILY == WINAPI_FAMILY_PC_APP
#		define MYL_PLATFORM_WINDOWS_STORE
#	elif WINAPI_FAMILY == WINAPI_FAMILY_SYSTEM
#		define MYL_PLATFORM_WINDOWS_SYSTEM
#	else
#		warning "Unknown Windows platform!"
#		define MYL_PLATFORM_WINDOWS_UNKNOWN
#	endif
#else
#	warning "Unknown platform!"
#	define MYL_PLATFORM_UNKNOWN
#endif

// Processor architecture detection

#if defined(__alpha__) || defined(__alpha) || defined(_M_ALPHA) /// MYTodo: REDO to version, https://www.boost.org/doc/libs/develop/boost/predef/architecture.h
#	if defined(__alpha_ev6__)
#		define MYL_ARCH_ALPHA __alpha_ev6__
#	elif defined(__alpha_ev5__)
#		define MYL_ARCH_ALPHA __alpha_ev5__
#	elif defined(__alpha_ev4__)
#		define MYL_ARCH_ALPHA __alpha_ev4__
#	else
#		warning "Unknown Alpha architecture!"
#		define MYL_ARCH_ALPHA_UNKNOWN
#	endif
#elif defined(__ARM_ARCH) || defined(__TARGET_ARCH_ARM) || defined(__TARGET_ARCH_THUMB) || defined(_M_ARM) || defined(__arm__) || defined(__arm64) || defined(__thumb__) || defined(_M_ARM64) || defined(__aarch64__) || defined(__AARCH64EL__)
#	define MYL_ARCH_ARM _M_ARM
#elif defined(__bfin__) || defined(__BFIN__) || defined(bfin) || defined(BFIN)
#	define MYL_ARCH_BLACKFIN
#elif defined(__convex__)
#	if defined(__convex_c1__)
#		define MYL_ARCH_CONVEX __convex_c1__
#	elif defined(__convex_c2__)
#		define MYL_ARCH_CONVEX __convex_c2__
#	elif defined(__convex_c32__)
#		define MYL_ARCH_CONVEX __convex_c32__
#	elif defined(__convex_c34__)
#		define MYL_ARCH_CONVEX __convex_c34__
#	elif defined(__convex_c38__)
#		define MYL_ARCH_CONVEX __convex_c38__
#	else
#		warning "Unknown Convex architecture!"
#		define MYL_ARCH_CONVEX_UNKNOWN
#	endif
#elif defined(__e2k__)
#	define MYL_ARCH_E2K __e2k__
#elif defined(__ia64__) || defined(_IA64) || defined(__IA64__) || defined(__ia64) || defined(_M_IA64) || defined(__itanium__)
#	define MYL_ARCH_INTEL_ITANIUM64
#elif defined(__m68k__) || defined(M68000)
#	define MYL_ARCH_M68K
#elif defined(__mips__) || defined(__mips) || defined(__MIPS__)
#	define MYL_ARCH_MIPS __mips
#elif defined(__hppa__) || defined(__hppa) || defined(__HPPA__)
#	define MYL_ARCH_PARISC
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__ppc64__) || defined(__PPC__) || defined(__PPC64__) || defined(_M_PPC) || defined(_ARCH_PPC) || defined(_ARCH_PPC64) || defined(__PPCGECKO__) || defined(__PPCBROADWAY__) || defined(_XENON) || defined(__ppc)
#	if defined(__powerpc64__) || defined(__ppc64__) || defined(__PPC64__) || defined(_ARCH_PPC64)
#		define MYL_ARCH_PPC_64
#	elif defined(__powerpc) || defined(__powerpc__)|| defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_M_PPC) || defined(_ARCH_PPC) || defined(__PPCGECKO__) || defined(__PPCBROADWAY__) || defined(_XENON) || defined(__ppc)
#		define MYL_ARCH_PPC
#	else
#		warning "Unknown PowerPC architecture!"
#		define MYL_ARCH_PPC_UNKNOWN
#	endif
#elif defined(__CUDA_ARCH__)
#	define MYL_ARCH_PTX __CUDA_ARCH__
#elif defined(pyr)
#	define MYL_ARCH_PYRAMID
#elif defined(__riscv)
#	define MYL_ARCH_RISCV
#elif defined(__THW_RS6000) || defined(_IBMR2) || defined(_POWER) || defined(_ARCH_PWR) || defined(_ARCH_PWR2)
#	define MYL_ARCH_RS6000
#elif defined(__sparc__) || defined(__sparc)
#	define MYL_ARCH_SPARC
#elif defined(__sh__)
#	define MYL_ARCH_SH
#elif defined(__370__) || defined(__THW_370__)
#	define MYL_ARCH_SYS370
#elif defined(__s390__) || defined(__s390x__)
#	define MYL_ARCH_SYS390
#elif defined(__SYSC_ZARCH__)
#	define MYL_ARCH_Z
#elif defined(i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || defined(__i386) || defined(_M_IX86) || defined(_X86_) || defined(__THW_INTEL__) || defined(__I86__) || defined(__INTEL__)
#	define MYL_ARCH_X86_32 __I86__
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64__) || defined(__amd64) || defined(_M_X64)
#	define MYL_ARCH_X86_64
#endif

// SIMD versions

#define MYL_SIMD_ARM_NEON_VERSION MYL_MAKE_VERSION(1, 0, 0)

#define MYL_SIMD_PPC_QPX_VERSION MYL_MAKE_VERSION(2, 0, 0)
#define MYL_SIMD_PPC_VSX_VERSION MYL_MAKE_VERSION(1, 1, 0)
#define MYL_SIMD_PPC_VMX_VERSION MYL_MAKE_VERSION(1, 0, 0)

#define MYL_SIMD_X86_ARM_XOP_VERSION MYL_MAKE_VERSION(5, 1, 1)
#define MYL_SIMD_X86_ARM_FMA4_VERSION MYL_MAKE_VERSION(5, 1, 0)
#define MYL_SIMD_X86_ARM_SSE4A_VERSION MYL_MAKE_VERSION(4, 0, 0)

#define MYL_SIMD_X86_MIC_VERSION MYL_MAKE_VERSION(9, 0, 0)
#define MYL_SIMD_AVX2_VERSION MYL_MAKE_VERSION(5, 3, 0)
#define MYL_SIMD_AVX_VERSION MYL_MAKE_VERSION(5, 0, 0)
#define MYL_SIMD_FMA3_VERSION MYL_MAKE_VERSION(5, 2, 0)
#define MYL_SIMD_SSE4_2_VERSION MYL_MAKE_VERSION(4, 2, 0)
#define MYL_SIMD_SSE4_1_VERSION MYL_MAKE_VERSION(4, 1, 0)
#define MYL_SIMD_SSSE3_VERSION MYL_MAKE_VERSION(3, 1, 0)
#define MYL_SIMD_SSE3_VERSION MYL_MAKE_VERSION(3, 0, 0)
#define MYL_SIMD_X86_SSE2_VERSION MYL_MAKE_VERSION(2, 0, 0)
#define MYL_SIMD_X86_SSE_VERSION MYL_MAKE_VERSION(1, 0, 0)
#define MYL_SIMD_X86_MMX_VERSION MYL_MAKE_VERSION(0, 99, 0)

// SIMD detection

#if defined(MYL_ARCH_ARM)
#	if defined(__ARM_NEON__) || defined(__aarch64__) || defined(_M_ARM) || defined(_M_ARM64) 
#		define MYL_SIMD_ARM MYL_SIMD_ARM_NEON_VERSION
#	endif
#elif defined(MYL_ARCH_PPC) || defined(MYL_ARCH_PPC_64)
#	if defined(__VECTOR4DOUBLE__)
#		define MYL_SIMD_PCC MYL_SIMD_PPC_QPX_VERSION
#	elif defined(__VSX__)
#		define MYL_SIMD_PCC MYL_SIMD_PPC_VSX_VERSION
#	elif defined(__ALTIVEC__) || defined(__VEC__)
#		define MYL_SIMD_PCC MYL_SIMD_PPC_VMX_VERSION
#	endif
#elif defined(MYL_ARCH_X86_32) || defined(MYL_ARCH_X86_64)
#	if defined(__XOP__)
#		define MYL_SIMD_X86_AMD MYL_SIMD_X86_ARM_XOP_VERSION
#	elif defined(__FMA4__)
#		define MYL_SIMD_X86_AMD MYL_SIMD_X86_ARM_FMA4_VERSION
#	elif defined(__SSE4A__)
#		define MYL_SIMD_X86_AMD MYL_SIMD_X86_ARM_SSE4A_VERSION
#	endif
#	if defined(__MIC__)
#		define MYL_SIMD_X86 MYL_SIMD_X86_MIC_VERSION
#	elif defined(__AVX2__)
#		define MYL_SIMD_X86 MYL_SIMD_AVX2_VERSION
#	elif defined(__AVX__)
#		define MYL_SIMD_X86 MYL_SIMD_AVX_VERSION
#	elif defined(__FMA__)
#		define MYL_SIMD_X86 MYL_SIMD_FMA3_VERSION
#	elif defined(__SSE4_2__)
#		define MYL_SIMD_X86 MYL_SIMD_SSE4_2_VERSION
#	elif defined(__SSE4_1__)
#		define MYL_SIMD_X86 MYL_SIMD_SSE4_1_VERSION
#	elif defined(__SSSE3__)
#		define MYL_SIMD_X86 MYL_SIMD_SSSE3_VERSION
#	elif defined(__SSE3__)
#		define MYL_SIMD_X86 MYL_SIMD_SSE3_VERSION
#	elif defined(__SSE2__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2)
#		define MYL_SIMD_X86 MYL_SIMD_X86_SSE2_VERSION
#	elif defined(__SSE__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1)
#		define MYL_SIMD_X86 MYL_SIMD_X86_SSE_VERSION
#	elif defined(__MMX__)
#		define MYL_SIMD_X86 MYL_SIMD_X86_MMX_VERSION
#	endif
#endif

#if defined(MYL_SIMD_ARM)
#	define MYL_SIMD MYL_SIMD_ARM
#elif defined(MYL_SIMD_PCC)
#	define MYL_SIMD MYL_SIMD_PCC
#elif defined(MYL_SIMD_X86_AMD) && defined(MYL_SIMD_X86)
#	if MYL_SIMD_X86 >= MYL_SIMD_X86_AMD
#		define MYL_SIMD MYL_SIMD_X86
#	else
#		define MYL_SIMD MYL_SIMD_X86_AMD
#	endif
#elif defined(MYL_SIMD_X86_AMD)
#	define MYL_SIMD MYL_SIMD_X86_AMD
#elif defined(MYL_SIMD_X86)
#	define MYL_SIMD MYL_SIMD_X86
#endif