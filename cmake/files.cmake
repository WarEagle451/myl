set(MYL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

include("${CMAKE_CURRENT_LIST_DIR}/utility.cmake")
gather(MYL_HEADERS "include" "*.hpp") # MYL header files
gather(MYL_SOURCES "include" "*.cpp") # MYL source files

set(MYL_FILES ${MYL_HEADERS} ${MYL_SOURCES})