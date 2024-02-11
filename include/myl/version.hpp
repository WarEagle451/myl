#pragma once
#include <myl/macro.hpp>

#define MYL_MAKE_VERSION(major, minor, patch) ((major << 24) + (minor << 16) + (patch))
#define MYL_MAKE_VERSION_STRING(major, minor, patch) (MYL_ARG_STRINGIFY(major) "." MYL_ARG_STRINGIFY(minor) "." MYL_ARG_STRINGIFY(patch))

#define MYL_VERSION_EXTRACT_MAJOR(version) ((version & 0xFF00'0000) >> 24)
#define MYL_VERSION_EXTRACT_MINOR(version) ((version & 0x00FF'0000) >> 16)
#define MYL_VERSION_EXTRACT_PATCH(version) ((version & 0x0000'FFFF))

#define MYL_VERSION_MAJOR 0
#define MYL_VERSION_MINOR 0
#define MYL_VERSION_PATCH 0
#define MYL_VERSION MYL_MAKE_VERSION(MYL_VERSION_MAJOR, MYL_VERSION_MINOR, MYL_VERSION_PATCH)
#define MYL_VERSION_STRING MYL_MAKE_VERSION_STRING(MYL_VERSION_MAJOR, MYL_VERSION_MINOR, MYL_VERSION_PATCH)
