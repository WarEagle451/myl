#pragma once
#include <myl/defines.hpp>

#include <string>
#include <vector>

namespace myl {
	class parser {
	public:
		struct parse_operator {
			u32 precedence;
			std::string name;
		};

		class builder {
		public:

		};
	private:
		std::vector<char> m_delimiters;
		std::vector<parse_operator> m_operators; /// MYTodo: maybe this should be a map
	public:

		MYL_NO_DISCARD constexpr auto parse() -> {
			while () {
				if (delimiter)
					++i;
			}
		}
	};
}