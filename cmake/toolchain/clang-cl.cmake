# Setup Clang-CL and LLD for C and C++

# Should search for the correct location, This will fail for 32 bit
# BUG: This is a hack
# set(CMAKE_MT "C:/Program Files (x86)/Windows Kits/10/bin/10.0.19041.0/x64/mt.exe")

set(CMAKE_C_COMPILER "clang-cl")
set(CMAKE_C_FLAGS "/W4 /std:c${CMAKE_C_STANDARD}")
set(CMAKE_C_FLAGS_RELEASE        "/O2 /DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "/O2 /Zo /DDEBUG")
set(CMAKE_C_FLAGS_DEBUG          "/Od /Zi /DDEBUG")
set(CMAKE_C_FLAGS_MINSIZEREL     "/O1 /DNDEBUG")

set(CMAKE_CXX_COMPILER "clang-cl")
set(CMAKE_CXX_FLAGS "/W4 /std:c++${CMAKE_CXX_STANDARD}")
set(CMAKE_CXX_FLAGS_RELEASE        "/O2 /DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/O2 /Zo /DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG          "/Od /Zi /DDEBUG")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "/O1 /DNDEBUG")

set(CMAKE_LINKER "lld-link")

#vcvarsall.bat [arch] [platform_type] [winsdk_version] [-vcvars_ver=vc_version] [-vcvars_spectre_libs=spectre_mode]
#
#vcvarsall.bat x86_amd64
#vcvarsall.bat x86_amd64 10.0.10240.0
#vcvarsall.bat x86_arm uwp 10.0.10240.0
#vcvarsall.bat x86_arm onecore 10.0.10240.0 -vcvars_ver=14.0
#vcvarsall.bat x64 8.1
#vcvarsall.bat x64 store 8.1
#
#vcvarsall.bat ${CMAKE_SYSTEM_PROCESSOR} 