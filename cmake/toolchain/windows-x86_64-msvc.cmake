# Target Platform and Target Architecture
set(CMAKE_SYSTEM_NAME "Windows")
set(CMAKE_SYSTEM_PROCESSOR "AMD64")

# Compiler / Linker Binaries and Respective Flags
include("${CMAKE_CURRENT_LIST_DIR}/cl.cmake") # Setup CL and Link for C and C++

include("${CMAKE_CURRENT_LIST_DIR}/windows.cmake")