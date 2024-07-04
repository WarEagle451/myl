#pragma once
#include <myl/definitions.hpp>

#include <string>
#include <typeinfo>

#if defined(MYL_COMPILER_CLANG) || defined(MYL_COMPILER_GCC)
#	include <cstdlib>
#	include <cxxabi.h>
#endif

namespace myl {
    template<typename T>
    MYL_NO_DISCARD constexpr auto demangle() -> std::string {
#if defined(MYL_COMPILER_CLANG) || defined(MYL_COMPILER_GCC)
        int status{};
        size_t length = 0;
        char* name = abi::__cxa_demangle(typeid(T).name(), NULL, &length, &status);
        std::string demangled(name, name + length);
        std::free(name);
        return demangled;
///#elif defined(MYL_COMPILER_MSVC)
#else
#   warning "myl::demangle is not implemented for this compiler"
        return std::string(typeid(T).name());
#endif
    }
}
