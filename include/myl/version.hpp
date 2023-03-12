#pragma once
#define MYL_VERSION_MAJOR 1
#define MYL_VERSION_MINOR 0
#define MYL_VERSION_PATCH 0

#define MYL_MAKE_VERSION(major, minor, patch) ((major << 24) + (minor << 16) + (patch))

#define MYL_VERSION_EXTRACT_MAJOR(version) ((version & 0xFF00'0000) >> 24)
#define MYL_VERSION_EXTRACT_MINOR(version) ((version & 0x00FF'0000) >> 16)
#define MYL_VERSION_EXTRACT_PATCH(version) ((version & 0x0000'FFFF))

#define MYL_VERSION MYL_MAKE_VERSION(MYL_VERSION_MAJOR, MYL_VERSION_MINOR, MYL_VERSION_PATCH)