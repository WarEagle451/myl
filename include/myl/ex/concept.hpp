#pragma once
#include <myl/defines.hpp> /// MYTemp: For #ifdef MYL_EXPERIMENTAL
#ifdef MYL_EXPERIMENTAL
/// MYTodo: Get other concepts in here

namespace myl {
	template<typename T> concept signed_integer = ;
	template<typename T> concept unsigned_integer = ;
	template<typename T> concept floating_point = ;
	template<typename T> concept number = ;

	template<typename T> concept container = ;

	template<typename T> concept random_engine = ;

	template<typename T> concept iterator = ;

	template<typename T> concept singleton = ;
}
#endif