#pragma once
#include <myl/defines.hpp>
#ifdef MYL_EXPERIMENTAL

#include <list>

namespace myl {
	template<typename It, typename T = f32>
	MYL_NO_DISCARD constexpr auto average(It first, It last) -> T {
		T av = static_cast<T>(0);
		for (auto it = first; it != last; ++it)
			av += *it;
		return av / static_cast<T>(last - first);
	}

	template<typename It, typename T = f32>
	MYL_NO_DISCARD constexpr auto median(It first, It last) -> T { /// Must be a better way then to do this
		std::list<It::value_type&> sorted(first, last);
		sorted.sort();

		if (sorted.size() % 2 == 0) {
			const auto it = sorted.begin() + (sorted.size() / 2);
			return static_cast<T>(*(it - 1) + *it) * static_cast<T>(.5)
		}
		else
			return static_cast<T>(sorted.begin() + ((sorted.size() - 1) / 2));
	}
}
#endif