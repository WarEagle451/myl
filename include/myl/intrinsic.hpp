#pragma once
#include <myl/definitions.hpp>
#ifndef MYL_NO_INTRINSICS
#   ifdef _MSC_VER
#      include <cstdlib>
#      define MYL_INTRINSIC_BYTESWAP2(x) _byteswap_ushort(x)
#      define MYL_INTRINSIC_BYTESWAP4(x) _byteswap_ulong(x)
#      define MYL_INTRINSIC_BYTESWAP8(x) _byteswap_uint64(x)
#   elif defined(__clang__)
#      if __has_builtin(__builtin_bswap16)
#          define MYL_INTRINSIC_BYTESWAP2(x) __builtin_bswap16(x)
#      endif

#      define MYL_INTRINSIC_BYTESWAP4(x) __builtin_bswap32(x)
#      define MYL_INTRINSIC_BYTESWAP8(x) __builtin_bswap64(x)
#   elif defined(__GNUC__)
#      if __GNUC__ > 4 || (__GNUC__ == 4 && _GNUC_MINOR__ >= 8)
#          define MYL_INTRINSIC_BYTESWAP2(x) __builtin_bswap16(x)
#      endif

#      define MYL_INTRINSIC_BYTESWAP4(x) __builtin_bswap32(x)
#      define MYL_INTRINSIC_BYTESWAP8(x) __builtin_bswap64(x)
#   elif defined(__linux__)
#      include <byteswap.h>
#      define MYL_INTRINSIC_BYTESWAP2(x) bswap_16(x)
#      define MYL_INTRINSIC_BYTESWAP4(x) bswap_32(x)
#      define MYL_INTRINSIC_BYTESWAP8(x) bswap_64(x)
#   endif
#endif
