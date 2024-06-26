cmake_minimum_required(VERSION 3.28.0)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(myl_unit_tests LANGUAGES CXX)

find_package(Catch2 3 QUIET)
if (Catch2_FOUND)
    message("STATUS Packaged version of Catch2 will be used")
else()
    message(STATUS "Bundled version of Catch2 will be used")
    include(FetchContent)
    FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.4
    )
    FetchContent_MakeAvailable(Catch2)
endif()

include("../cmake/utility.cmake")
set(MYL_INCLUDE_DIR "../include")
gather(MYL_FILES ${MYL_INCLUDE_DIR} "*.hpp;*.cpp")

set(MYL_TEST_SOURCES
    "algorithm.cpp"
    "bit.cpp"
    "wip/color.cpp"
    "io.cpp"
    "macro.cpp"
    "math/mat_common.cpp"
    "math/mat2x2.cpp"
    "math/mat2x3.cpp"
    "math/mat2x4.cpp"
    "math/mat3x2.cpp"
    "math/mat3x3.cpp"
    "math/mat3x4.cpp"
    "math/mat4x2.cpp"
    "math/mat4x3.cpp"
    "math/mat4x4.cpp"
    "math/exponential.cpp"
    "math/trigonometry.cpp"
    "math/vec_common.cpp"
    "math/vec2.cpp"
    "math/vec3.cpp"
    "math/vec4.cpp"
    "wip/ring_buffer.cpp"
    "shaping.cpp"
    "static_vector.cpp"
    "string.cpp"
    "type.cpp"
    "version.cpp"
)

enable_testing()

option(MYL_NO_EXCEPTIONS "Disable execeptions" OFF)

if (MYL_NO_EXCEPTIONS)
    add_compile_definitions("MYL_NO_EXCEPTIONS")
endif()

function(prepare_test target)
    add_executable(${target} ${MYL_INCLUDE_DIR} ${MYL_TEST_SOURCES})
    target_link_libraries(${target} PRIVATE Catch2::Catch2WithMain)
    target_include_directories(${target} PUBLIC "../include")

    add_test(NAME ${target} COMMAND ${target})
    set_tests_properties(${target} PROPERTIES RUN_SERIAL ON)
endfunction()

prepare_test(myl_tests)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(myl_tests)
