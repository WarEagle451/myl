#pragma once
#include <myl/defines.hpp>
#ifdef MYL_EXPERIMENTAL
#include <string>
#include <vector>

/// string cast needs to support all string types, wide, char, c8, c16, c32

namespace myl {
	template<typename T, typename CharType> MYL_NO_DISCARD constexpr auto string_cast(const T&) -> std::basic_string<CharType>;

	//template<> MYL_NO_DISCARD constexpr auto string_cast<i8, char>(const i8&) -> std::basic_string<char> { return; }
	//template<> MYL_NO_DISCARD constexpr auto string_cast<i16, char>(const i16&) -> std::basic_string<char> { return; }
	//template<> MYL_NO_DISCARD constexpr auto string_cast<i32, char>(const i32&) -> std::basic_string<char> { return; }
	//template<> MYL_NO_DISCARD constexpr auto string_cast<i64, char>(const i64&) -> std::basic_string<char> { return; }
	//
	//template<> MYL_NO_DISCARD constexpr auto string_cast<u8, char>(const u8&) -> std::basic_string<char> { return; }
	//template<> MYL_NO_DISCARD constexpr auto string_cast<u16, char>(const u16&) -> std::basic_string<char> { return; }
	//template<> MYL_NO_DISCARD constexpr auto string_cast<u32, char>(const u32&) -> std::basic_string<char> { return; }
	//template<> MYL_NO_DISCARD constexpr auto string_cast<u64, char>(const u64&) -> std::basic_string<char> { return; }
	//
	//template<> MYL_NO_DISCARD constexpr auto string_cast<f32, char>(const f32&) -> std::basic_string<char> { return; }
	//template<> MYL_NO_DISCARD constexpr auto string_cast<f64, char>(const f64&) -> std::basic_string<char> { return; }

	/// Really slow
	template<typename Elem = char, typename Traits = std::char_traits<Elem>, typename Alloc = std::allocator<Elem>>
	MYL_NO_DISCARD constexpr auto split(std::basic_string_view<Elem, Traits> view, const std::vector<Elem>& delimiters) -> std::vector<std::basic_string<Elem, Traits, Alloc>> {
		using string_type = std::basic_string<Elem, Traits, Alloc>;

		auto is_delimiter = [&delimiters](const Elem& e) -> bool {
			for (auto& d : delimiters)
				if (d == e)
					return true;
			return false;
		};

		std::vector<string_type> words{};
		for (typename string_type::size_type i = 0; i != view.size(); ++i) {
			typename string_type::size_type size = 0;
			while (i != view.size() && !is_delimiter(view[i])) {
				++size;
				++i;
			}

			if (size)
				words.push_back(string_type(view.substr(i - size, size)));
		}

		return words;
	}
}
#endif