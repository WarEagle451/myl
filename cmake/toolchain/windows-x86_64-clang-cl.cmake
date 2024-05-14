# Target Platform and Target Architecture
set(CMAKE_SYSTEM_NAME "Windows")
set(CMAKE_SYSTEM_PROCESSOR "AMD64")

# Compiler / Linker Binaries and Respective Flags
include("${CMAKE_CURRENT_LIST_DIR}/clang-cl.cmake")  # Setup Clang-CL and LLD for C and C++

include("${CMAKE_CURRENT_LIST_DIR}/windows.cmake")