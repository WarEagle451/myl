#pragma once
#include <myl/definitions.hpp>

#include <cctype>
#include <cwctype>
#include <string>

namespace myl {
    template<typename Char = char>
    MYL_NO_DISCARD constexpr auto to_upper(const std::basic_string<Char>& s) -> std::basic_string<Char> {
        std::basic_string<Char> out;
        out.reserve(s.size());
        for (Char c : s)
            out += static_cast<Char>(std::toupper(static_cast<unsigned char>(c)));
        return out;
    }

    template<>
    MYL_NO_DISCARD constexpr auto to_upper<wchar_t>(const std::wstring& s) -> std::wstring {
        std::wstring out;
        out.reserve(s.size());
        for (wchar_t c : s)
            out += static_cast<wchar_t>(std::towupper(static_cast<std::wint_t>(c)));
        return out;
    }

    template<typename Char = char>
    MYL_NO_DISCARD constexpr auto to_lower(const std::basic_string<Char>& s) -> std::basic_string<Char> {
        std::basic_string<Char> out;
        out.reserve(s.size());
        for (Char c : s)
            out += static_cast<Char>(std::tolower(static_cast<unsigned char>(c)));
        return out;
    }

    template<>
    MYL_NO_DISCARD constexpr auto to_lower<wchar_t>(const std::wstring& s) -> std::wstring {
        std::wstring out;
        out.reserve(s.size());
        for (wchar_t c : s)
            out += static_cast<wchar_t>(std::towlower(static_cast<std::wint_t>(c)));
        return out;
    }
}
