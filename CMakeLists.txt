cmake_minimum_required(VERSION 3.28.0)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include("cmake/utility.cmake")
set(MYL_INCLUDE_DIR "include")
gather(MYL_FILES ${MYL_INCLUDE_DIR} "*.hpp;*.cpp")

# Setup project
extract_version("MYL_VERSION" "include/myl/version.hpp" MYL_VERSION)
project(myl
    VERSION ${MYL_VERSION}
    HOMEPAGE_URL "https://github.com/WarEagle451/myl"
    LANGUAGES CXX
)
message(STATUS "Build myl: ${MYL_VERSION}")