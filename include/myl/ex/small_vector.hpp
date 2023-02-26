#pragma once
#include <myl/defines.hpp>

#include <memory>

// https://pvs-studio.com/en/blog/posts/0989/#ID1BE23D29B4
/// combinatino of array and vector

namespace myl {
	template<typename T>
	class small_vector_iterator {
	public:

	private:

	public:

	};

	template<typename T>
	class reverse_small_vector_iterator {
	public:

	private:

	public:

	};

	template<typename T, usize S, typename Allocator = std::allocator<T>>
	class small_vector {
	public:
		using value_type				= T;
		using allocator_type			= Allocator;
		using size_type					= usize;
		using difference_type			= typename std::allocator_traits<allocator_type>::difference_type;
		using reference					= value_type&;
		using const_reference			= const value_type&;
		using pointer					= typename std::allocator_traits<allocator_type>::pointer;
		using const_pointer				= typename std::allocator_traits<allocator_type>::const_pointer;
		using iterator					= small_vector_iterator<value_type>;
		using const_iterator			= const iterator;
		using reverse_iterator			= reverse_small_vector_iterator<iterator>;
		using const_reverse_iterator	= const reverse_iterator;
	private:
		value_type m_block[S]{};
		pointer m_begin = nullptr;
		pointer m_end = nullptr;
		pointer m_insert = nullptr;
	public:

	};
}