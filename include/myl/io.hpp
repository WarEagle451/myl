#pragma once
#include <myl/definitions.hpp>

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace myl {
    template<typename Char = char>
    MYL_NO_DISCARD auto load_into_memory(const std::filesystem::path& file) -> std::basic_string<Char> {
        if (std::basic_ifstream<Char> in(file, std::ios::binary); in) {
            std::basic_string<Char> content{};
            content.resize(std::filesystem::file_size(file));
            in.read(content.data(), content.size());
            return content;
        }

        return std::basic_string<Char>{};
    }

    template<typename Int = u8>
    MYL_NO_DISCARD auto load_binary_into_memory(const std::filesystem::path& file) -> std::vector<Int> {
        if (std::ifstream in(file, std::ios::binary); in) {
            std::vector<Int> binary{};
            auto size = std::filesystem::file_size(file);

            binary.resize(size / sizeof(Int));
            in.read(reinterpret_cast<std::ifstream::char_type*>(binary.data()), size);
            return binary;
        }

        return std::vector<Int>{};
    }
}
