#pragma once
#include <myl/defines.hpp>
#include <myl/iterative.hpp>

#include <memory>
/// be able to set the growth size of vector

/// MYTodo: Restructure cyclic_buffer like this

namespace myl {
	template<typename T, typename Allocator = std::allocator<T>>
	class vector {
	public:
		using value_type				= T;
		using allocator_type			= Allocator;
		using size_type					= usize;
		using difference_type			= typename std::allocator_traits<allocator_type>::difference_type;;
		using reference					= value_type&;
		using const_reference			= const value_type&;
		using pointer					= typename std::allocator_traits<allocator_type>::pointer;
		using const_pointer				= typename std::allocator_traits<allocator_type>::const_pointer;
		using iterator					= contiguous_iterator<vector>;
		using const_iterator			= const iterator;
		using reverse_iterator			= std::reverse_iterator<iterator>;
		using const_reverse_iterator	= const reverse_iterator;
	private:
		pointer m_begin = nullptr;
		pointer m_end = nullptr;
		pointer m_last = nullptr;
		size_type m_size = 0;
	public:
		// Constructors

		constexpr ~vector() {
			clear();
			allocator_type alloc = allocator_type();
			std::allocator_traits<allocator_type>::deallocate(alloc, m_begin, capacity());
		}

		// Utilities

		//@return The maximum size of the vector, limited by the underlying size type
		MYL_NO_DISCARD static constexpr auto max_size() const noexcept -> size_type { return static_cast<size_type>(~0); }

		//@return An instance of thr allocator type used in the vector
		MYL_NO_DISCARD constexpr auto get_allocator() const -> allocator_type { return allocator_type(); }

		//@return The data block used by the vector
		MYL_NO_DISCARD constexpr auto data() noexcept -> pointer { return m_begin; }

		//@return The data block used by the vector
		MYL_NO_DISCARD constexpr auto data() const noexcept -> const_pointer { return m_begin; }

		//@return If the vector is empty
		MYL_NO_DISCARD constexpr auto empty() const noexcept -> bool { return m_size == 0; }

		//@return The size of the vector
		MYL_NO_DISCARD constexpr auto size() const noexcept -> size_type { return m_size; }

		//@return The amount of elements the vector can hold before having to resize
		MYL_NO_DISCARD constexpr auto capacity() const noexcept -> size_type { return static_cast<size_type>(m_end - m_begin); }

		// Iterators

		//@return The first element of the vector as an interator
		MYL_NO_DISCARD constexpr auto begin() noexcept -> iterator { return iterator(m_begin); }

		//@return The first element of the vector as a const interator
		MYL_NO_DISCARD constexpr auto begin() const noexcept -> const_iterator { return begin(); }

		//@return The first element of the vector as a const interator
		MYL_NO_DISCARD constexpr auto cbegin() const noexcept -> const_iterator { return begin(); }

		//@return 1 past the last element of the vector as an iterator
		MYL_NO_DISCARD constexpr auto end() noexcept -> iterator { return iterator(m_last); }

		//@return 1 past the last element of the vector as a const iterator
		MYL_NO_DISCARD constexpr auto end() const noexcept -> const_iterator { return end(); }

		//@return 1 past the last element of the vector as a const iterator
		MYL_NO_DISCARD constexpr auto cend() const noexcept -> const_iterator { return end(); }

		//@return The last element of the vector as a reverse iterator
		MYL_NO_DISCARD constexpr auto rbegin() noexcept -> reverse_iterator { return reverse_iterator(iterator(m_last)); }

		//@return The last element of the vector as a const reverse iterator
		MYL_NO_DISCARD constexpr auto rbegin() const noexcept -> const_reverse_iterator { return rbegin(); }

		//@return The last element of the vector as a const reverse iterator
		MYL_NO_DISCARD constexpr auto crbegin() const noexcept -> const_reverse_iterator { return rbegin(); }

		//@return 1 before the first element of the vector as a reverse iterator
		MYL_NO_DISCARD constexpr auto rend() noexcept -> reverse_iterator { return reverse_iterator(iterator(m_begin - 1); }

		//@return 1 before the first element of the vector as a const reverse iterator
		MYL_NO_DISCARD constexpr auto rend() const noexcept -> const_reverse_iterator { return rend(); }

		//@return 1 before the first element of the vector as a const reverse iterator
		MYL_NO_DISCARD constexpr auto crend() const noexcept -> const_reverse_iterator { return rend(); }

		// Modifiers

		//@brief Removes all elements
		constexpr auto clear() noexcept -> void {
			allocator_type alloc = allocator_type();
			while (!empty()) {
				std::allocator_traits<allocator_type>::destroy(alloc, m_last);
				--m_last;
				--m_size;
			}

			m_last = m_begin; // Will set m_last to m_begin - 1
		}

		// Element access

		//@return The a reference to the first element
		MYL_NO_DISCARD constexpr auto front() -> reference { return *m_begin; }

		//@return The a reference to the first element
		MYL_NO_DISCARD constexpr auto front() const -> const_reference { return *m_begin; }

		//@return The a reference to the last element
		MYL_NO_DISCARD constexpr auto back() -> reference { return *m_last; }

		//@return The a reference to the last element
		MYL_NO_DISCARD constexpr auto back() const -> const_reference { return *m_last; }

		//@param a_position: The element's position in the vector
		MYL_NO_DISCARD constexpr auto at(size_type a_position) -> reference { return m_begin[a_position]; }

		//@param a_position: The element's position in the vector
		MYL_NO_DISCARD constexpr auto at(size_type a_position) const -> const_reference { return m_begin[a_position]; }

		//@param a_index: The index of the element. This does not consider element offset
		//@return Reference to the element
		MYL_NO_DISCARD constexpr auto operator[](size_type a_index) -> reference { return m_begin[a_index]; }

		//@param a_index: The index of the element. This does not consider element offset
		//@return Const reference to the element
		MYL_NO_DISCARD constexpr auto operator[](size_type a_index) const -> const_reference { return m_begin[a_index]; }
	};
}