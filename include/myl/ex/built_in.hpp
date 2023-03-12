#pragma once
/// https://learn.microsoft.com/en-us/cpp/intrinsics/x86-intrinsics-list?view=msvc-170
/// https://learn.microsoft.com/en-us/cpp/intrinsics/x64-amd64-intrinsics-list?view=msvc-170
/// https://learn.microsoft.com/en-us/cpp/intrinsics/arm64-intrinsics?view=msvc-170
/// https://learn.microsoft.com/en-us/cpp/intrinsics/arm-intrinsics?view=msvc-170

/// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/rotl-rotl64-rotr-rotr64?view=msvc-170
/// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/lrotl-lrotr?view=msvc-170
/// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/floor-floorf-floorl?view=msvc-170
/// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/ceil-ceilf-ceill?view=msvc-170

/// https://learn.microsoft.com/en-us/cpp/intrinsics/alphabetical-listing-of-intrinsic-functions?view=msvc-170


/// https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#
/// https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
/// https://gcc.gnu.org/onlinedocs/gcc/Target-Builtins.html#Target-Builtins

#include <myl/platform.hpp>

#ifdef MYL_COMPILER_MSVC
#	include <intrin.h>
#	define MYL_BUILT_IN_BSWAP_16(x) _byteswap_ushort(x)
#	define MYL_BUILT_IN_BSWAP_32(x) _byteswap_ulong(x)
#	define MYL_BUILT_IN_BSWAP_64(x) _byteswap_uint64(x)

#	include <cstdlib>
#	define MYL_BUILT_IN_ABS_64(x) _abs64(x) /// MYTodo: Needed?

#	include <cmath>
#	define MYL_BUILT_IN_ABS_D(x) fabs(x)
#	define MYL_BUILT_IN_ABS_F(x) fabsf(x)
#	define MYL_BUILT_IN_ABS_L(x) labs(x)
#	define MYL_BUILT_IN_ABS_LD(x) fabsl(x)
#	define MYL_BUILT_IN_ABS_LL(x) llabs(x)
#	define MYL_BUILT_IN_ACOS_D(x) acos(x)
#	define MYL_BUILT_IN_ACOS_F(x) acosf(x)
#	define MYL_BUILT_IN_ACOS_LD(x) acosl(x)
#	define MYL_BUILT_IN_ASIN_D(x) asin(x)
#	define MYL_BUILT_IN_ASIN_F(x) asinf(x)
#	define MYL_BUILT_IN_ASIN_LD(x) asinl(x)
#	define MYL_BUILT_IN_ATAN_D(x) atan(x)
#	define MYL_BUILT_IN_ATAN_F(x) atanf(x)
#	define MYL_BUILT_IN_ATAN_LD(x) atanl(x)
#	define MYL_BUILT_IN_ATAN2_LD(x) atan2(x)
#	define MYL_BUILT_IN_ATAN2_LD(x) atan2f(x)
#	define MYL_BUILT_IN_ATAN2_LD(x) atan2l(x)
#	define MYL_BUILT_IN_COS_D(x) cos(x)
#	define MYL_BUILT_IN_COS_F(x) cosf(x)
#	define MYL_BUILT_IN_COS_LD(x) cosl(x)
#	define MYL_BUILT_IN_COSH_D(x) cosh(x)
#	define MYL_BUILT_IN_COSH_F(x) coshf(x)
#	define MYL_BUILT_IN_COSH_LD(x) coshl(x)
#	define MYL_BUILT_IN_EXP_D(x) exp(x)
#	define MYL_BUILT_IN_EXP_F(x) expf(x)
#	define MYL_BUILT_IN_EXP_LD(x) expl(x)
#	define MYL_BUILT_IN_LOG_D(x) log(x)
#	define MYL_BUILT_IN_LOG_F(x) logf(x)
#	define MYL_BUILT_IN_LOG_LD(x) logl(x)
#	define MYL_BUILT_IN_LOG10_D(x) log10(x)
#	define MYL_BUILT_IN_LOG10_F(x) log10f(x)
#	define MYL_BUILT_IN_LOG10_LD(x) log10l(x)
#	define MYL_BUILT_IN_MOD_D(x) fmod(x) 
#	define MYL_BUILT_IN_MOD_F(x) fmodf(x)
#	define MYL_BUILT_IN_MOD_LD(x) fmodl(x)
#	define MYL_BUILT_IN_POW_D(x) pow(x)
#	define MYL_BUILT_IN_POW_F(x) powf(x)
#	define MYL_BUILT_IN_POW_LD(x) powl(x)
#	define MYL_BUILT_IN_SIN_D(x) sin(x)
#	define MYL_BUILT_IN_SIN_F(x) sinf(x)
#	define MYL_BUILT_IN_SIN_LD(x) sinl(x)
#	define MYL_BUILT_IN_SINH_D(x) sinh(x)
#	define MYL_BUILT_IN_SINH_F(x) sinhf(x)
#	define MYL_BUILT_IN_SINH_LD(x) sinhl(x)
#	define MYL_BUILT_IN_SQRT_D(x) sqrt(x)
#	define MYL_BUILT_IN_SQRT_F(x) sqrtf(x)
#	define MYL_BUILT_IN_SQRT_LD(x) sqrtl(x)
#	define MYL_BUILT_IN_TAN_D(x) tan(x)
#	define MYL_BUILT_IN_TAN_F(x) tanf(x)
#	define MYL_BUILT_IN_TAN_LD(x) tanl(x)
#	define MYL_BUILT_IN_TANH_D(x) tanh(x)
#	define MYL_BUILT_IN_TANH_F(x) tanhf(x)
#	define MYL_BUILT_IN_TANH_LD(x) tanhl(x)

/// This maybe should fall under simd
#ifdef MYL_ENABLE_SIMD
#endif

#	ifdef MYL_ARCH_X86_32
#		define MYL_BUILT_IN_///
#	elif defined(MYL_ARCH_X86_64)
#		define MYL_BUILT_IN_///
#	elif defined(MYL_ARCH_NEON64) && defined(MYL_ENABLE_NEON_INSTRUCTION_SET)
#		include <arm64_neon.h>
#		define MYL_BUILT_IN_///

#	elif defined(MYL_ARCH_NEON) && defined(MYL_ENABLE_NEON_INSTRUCTION_SET)
#		define MYL_BUILT_IN_///

#	endif
#elif defined(MYL_COMPILER_GCC)
#	define MYL_BUILT_IN_BSWAP_16(x) __builtin_bswap16(x)
#	define MYL_BUILT_IN_BSWAP_32(x) __builtin_bswap32(x)
#	define MYL_BUILT_IN_BSWAP_64(x) __builtin_bswap64(x)

#	define MYL_BUILT_IN_

_exit, alloca, bcmp, bzero, dcgettext, dgettext, dremf, dreml, drem, exp10f, exp10l, exp10, ffsll, ffsl, ffs, fprintf_unlocked, fputs_unlocked, gammaf, gammal, gamma, gammaf_r, gammal_r, gamma_r, gettext, index, isascii, j0f, j0l, j0, j1f, j1l, j1, jnf, jnl, jn, lgammaf_r, lgammal_r, lgamma_r, mempcpy, pow10f, pow10l, pow10, printf_unlocked, rindex, roundeven, roundevenf, roundevenl, scalbf, scalbl, scalb, signbit, signbitf, signbitl, signbitd32, signbitd64, signbitd128, significandf, significandl, significand, sincosf, sincosl, sincos, stpcpy, stpncpy, strcasecmp, strdup, strfmon, strncasecmp, strndup, strnlen, toascii, y0f, y0l, y0, y1f, y1l, y1, ynf, ynl, yn
_Exit, acoshf, acoshl, acosh, asinhf, asinhl, asinh, atanhf, atanhl, atanh, cabsf, cabsl, cabs, cacosf, cacoshf, cacoshl, cacosh, cacosl, cacos, cargf, cargl, carg, casinf, casinhf, casinhl, casinh, casinl, casin, catanf, catanhf, catanhl, catanh, catanl, catan, cbrtf, cbrtl, cbrt, ccosf, ccoshf, ccoshl, ccosh, ccosl, ccos, cexpf, cexpl, cexp, cimagf, cimagl, cimag, clogf, clogl, clog, conjf, conjl, conj, copysignf, copysignl, copysign, cpowf, cpowl, cpow, cprojf, cprojl, cproj, crealf, creall, creal, csinf, csinhf, csinhl, csinh, csinl, csin, csqrtf, csqrtl, csqrt, ctanf, ctanhf, ctanhl, ctanh, ctanl, ctan, erfcf, erfcl, erfc, erff, erfl, erf, exp2f, exp2l, exp2, expm1f, expm1l, expm1, fdimf, fdiml, fdim, fmaf, fmal, fmaxf, fmaxl, fmax, fma, fminf, fminl, fmin, hypotf, hypotl, hypot, ilogbf, ilogbl, ilogb, imaxabs, isblank, iswblank, lgammaf, lgammal, lgamma, llabs, llrintf, llrintl, llrint, llroundf, llroundl, llround, log1pf, log1pl, log1p, log2f, log2l, log2, logbf, logbl, logb, lrintf, lrintl, lrint, lroundf, lroundl, lround, nearbyintf, nearbyintl, nearbyint, nextafterf, nextafterl, nextafter, nexttowardf, nexttowardl, nexttoward, remainderf, remainderl, remainder, remquof, remquol, remquo, rintf, rintl, rint, roundf, roundl, round, scalblnf, scalblnl, scalbln, scalbnf, scalbnl, scalbn, snprintf, tgammaf, tgammal, tgamma, truncf, truncl, trunc, vfscanf, vscanf, vsnprintf vsscanf
acosf, acosl, asinf, asinl, atan2f, atan2l, atanf, atanl, ceilf, ceill, cosf, coshf, coshl, cosl, expf, expl, fabsf, fabsl, floorf, floorl, fmodf, fmodl, frexpf, frexpl, ldexpf, ldexpl, log10f, log10l, logf, logl, modfl, modff, powf, powl, sinf, sinhf, sinhl, sinl, sqrtf, sqrtl, tanf, tanhf, tanhl, tanl
iswalnum, iswalpha, iswcntrl, iswdigit, iswgraph, iswlower, iswprint, iswpunct, iswspace, iswupper, iswxdigit, towlower, towupper
abort, abs, acos, asin, atan2, atan, calloc, ceil, cosh, cos, exit, exp, fabs, floor, fmod, fprintf, fputs, free, frexp, fscanf, isalnum, isalpha, iscntrl, isdigit, isgraph, islower, isprint, ispunct, isspace, isupper, isxdigit, tolower, toupper, labs, ldexp, log10, log, malloc, memchr, memcmp, memcpy, memset, modf, pow, printf, putchar, puts, realloc, scanf, sinh, sin, snprintf, sprintf, sqrt, sscanf, strcat, strchr, strcmp, strcpy, strcspn, strlen, strncat, strncmp, strncpy, strpbrk, strrchr, strspn, strstr, tanh, tan, vfprintf, vprintf, vsprintf

#endif