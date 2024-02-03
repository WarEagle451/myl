cmake_minimum_required(VERSION 3.28.0)

# Setup project
include("cmake/files.cmake")
include("cmake/utility.cmake")

extract_version(MYL_VERSION "MYL_VERSION" "include/myl/version.hpp")
project(
    MYL
    VERSION ${MYL_VERSION}
    HOMEPAGE_URL "https://github.com/WarEagle451/myl"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)