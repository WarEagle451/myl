#pragma once
#include <myl/iterative.hpp>

#include <stdexcept>
#include <initializer_list>
#include <memory>
#include <numeric>
#include <utility> // std::forward

namespace myl {
	template<typename T, typename Allocator = std::allocator<T>>
	class cyclic_buffer {
	public:
		using value_type				= T;
		using allocator_type			= Allocator;
		using size_type					= usize;
		using difference_type			= typename std::allocator_traits<allocator_type>::difference_type;
		using reference					= value_type&;
		using const_reference			= const value_type&;
		using pointer					= typename std::allocator_traits<allocator_type>::pointer;
		using const_pointer				= typename std::allocator_traits<allocator_type>::const_pointer;
		using iterator					= circulator<cyclic_buffer>;
		using const_iterator			= const iterator;
		using reverse_iterator			= std::reverse_iterator<iterator>;
		using const_reverse_iterator	= const reverse_iterator;
	private:
		pointer m_begin = nullptr;
		pointer m_end = nullptr;
		pointer m_head = nullptr;
		pointer m_tail = nullptr;
		size_type m_size = 0;
	public:
		// Constructors / Destructor / Copy 

		//@brief Constructs a empty cyclic buffer
		MYL_NO_DISCARD constexpr cyclic_buffer() = default;

		//@brief Constructs a cyclic buffer with values from an initializer list
		//@param a_list: The initializer list
		MYL_NO_DISCARD constexpr cyclic_buffer(std::initializer_list<value_type> a_list) {
			assign(a_list);
		}

		//@brief Allocates a cyclic buffer with a certain capacity
		//@param a_capacity: The capacity of the cyclic buffer
		MYL_NO_DISCARD constexpr explicit cyclic_buffer(size_type a_capacity) noexcept(noexcept(allocator_type())) {
			allocator_type alloc = allocator_type();
			m_begin = std::allocator_traits<allocator_type>::allocate(alloc, a_capacity);
			m_end = m_begin + a_capacity;
			m_head = m_begin;
			m_tail = m_head;
		}

		//@brief Constructs a cyclic buffer with a certain size filled with a certain value
		//@param a_count: The size of the cyclic buffer
		//@param a_value: The value to fill the cyclic buffer
		MYL_NO_DISCARD constexpr explicit cyclic_buffer(size_type a_count, const_reference a_value) {
			assign(a_count, a_value);
		}

		//@brief Constucts a cyclic buffer from a range for iterators
		//@param a_begin: The beginning of the range
		//@param a_end: The end of the range
		template<typename InputIt>
		MYL_NO_DISCARD constexpr explicit cyclic_buffer(InputIt a_begin, InputIt a_end) {
			assign(a_begin, a_end);
		}

		constexpr ~cyclic_buffer() {
			clear();
			allocator_type alloc = allocator_type();
			std::allocator_traits<allocator_type>::deallocate(alloc, m_begin, capacity());
		}

		// Utilities

		//@return The maximum size of the cyclic buffer, limited by the underlying size type
		MYL_NO_DISCARD static constexpr auto max_size() noexcept -> size_type { return std::numeric_limits<size_type>::max(); }

		//@return An instance of thr allocator type used in the cyclic buffer
		MYL_NO_DISCARD constexpr auto get_allocator() const -> allocator_type { return allocator_type(); }

		//@return The size of the cyclic buffer
		MYL_NO_DISCARD constexpr auto size() const noexcept -> size_type { return m_size; }

		//@return The amount of elements the cyclic buffer can hold before having to resize
		MYL_NO_DISCARD constexpr auto capacity() const noexcept -> size_type { return static_cast<size_type>(m_end - m_begin); }

		//@return The head's offset from the beginning of the data block
		MYL_NO_DISCARD constexpr auto offset() const noexcept -> difference_type { return static_cast<difference_type>(m_head - m_begin); }

		//@return If the cyclic buffer is empty
		MYL_NO_DISCARD constexpr auto empty() const noexcept -> bool { return m_size == 0; }

		//@return If the cyclic buffer is full
		MYL_NO_DISCARD constexpr auto full() const noexcept -> bool { return m_size == capacity(); }

		//@return If the cyclic buffer is linear. The cyclic buffer is linear when the head comes before or is equal to the tail in memory
		MYL_NO_DISCARD constexpr auto linear() const noexcept -> bool { return m_head <= m_tail; }

		//@return The underlying data block used by the cyclic buffer
		MYL_NO_DISCARD constexpr auto data() noexcept -> pointer { return m_begin; }

		//@return The underlying data block used by the cyclic buffer
		MYL_NO_DISCARD constexpr auto data() const noexcept -> const_pointer { return m_begin; }

		// Iterators

		//@return The head of the buffer as an circulator
		MYL_NO_DISCARD constexpr auto begin() noexcept -> iterator { return iterator(m_head, m_begin, m_end, m_head, m_tail, empty()); } // Must check if empty, will run if passed false

		//@return The head of the buffer as a const circulator
		MYL_NO_DISCARD constexpr auto begin() const noexcept -> const_iterator { return begin(); }

		//@return The head of the buffer as a const circulator
		MYL_NO_DISCARD constexpr auto cbegin() const noexcept -> const_iterator { return begin(); }

		//@return The tail of the buffer as an circulator
		MYL_NO_DISCARD constexpr auto end() noexcept -> iterator { return iterator(m_head, m_begin, m_end, m_head, m_tail, true); }

		//@return The tail of the buffer as a const circulator
		MYL_NO_DISCARD constexpr auto end() const noexcept -> const_iterator { return end(); }

		//@return The tail of the buffer as a const circulator
		MYL_NO_DISCARD constexpr auto cend() const noexcept -> const_iterator { return end(); }

		//@return The head as a reverse circulator
		MYL_NO_DISCARD constexpr auto rbegin() noexcept -> reverse_iterator { return reverse_iterator(iterator(m_head, m_begin, m_end, m_head, m_tail, empty())); } // Must check if empty, will run if passed false

		//@return The head as a const reverse circulator
		MYL_NO_DISCARD constexpr auto rbegin() const noexcept -> const_reverse_iterator { return rbegin(); }

		//@return The head as a const reverse circulator
		MYL_NO_DISCARD constexpr auto crbegin() const noexcept -> const_reverse_iterator { return rbegin(); }

		//@return The tail as a reverse circulator
		MYL_NO_DISCARD constexpr auto rend() noexcept -> reverse_iterator { return reverse_iterator(iterator(m_head, m_begin, m_end, m_head, m_tail, true)); }

		//@return The tail as a const reverse circulator
		MYL_NO_DISCARD constexpr auto rend() const noexcept -> const_reverse_iterator { return rend(); }

		//@return The tail as a const reverse circulator
		MYL_NO_DISCARD constexpr auto crend() const noexcept -> const_reverse_iterator { return rend(); }

		// Modifiers

		//@brief Removes all elements from the cyclic buffer
		constexpr auto clear() noexcept -> void {
			allocator_type alloc = allocator_type();
			while (!empty()) {
				std::allocator_traits<allocator_type>::destroy(alloc, m_tail);
				decrement(m_tail);
				--m_size;
			}

			m_tail = m_head; // Decrement will set m_tail to m_end - 1
		}

		//@brief Replace and fill the cyclic buffer
		//@param a_value: The value to fill the cyclic buffer
		constexpr auto fill(const_reference a_value) -> void {
			clear();
			allocator_type alloc = allocator_type();
			for (pointer ptr = m_begin; ptr != m_end; ++ptr)
				std::allocator_traits<allocator_type>::construct(alloc, ptr, a_value);

			m_head = m_begin;
			m_tail = m_end - 1;
			m_size = capacity();
		}

		//@brief Fills any unused capacity of the cyclic buffer
		//@param a_value: The value to fill the cyclic buffer
		constexpr auto fill_up(const_reference a_value) -> void {
			while (!full())
				push_back(a_value);
		}

		//@brief Assigns a range of elements to the cyclic buffer. This is will replace the current elements
		//@param a_begin: The beginning of the range
		//@param a_end: The end of the range
		template<typename InputIt>
		constexpr auto assign(InputIt a_begin, InputIt a_end) -> void {
			clear();
			allocator_type alloc = allocator_type();
			const size_type new_size = static_cast<size_type>(a_end - a_begin);
			if (new_size > capacity()) { // Reallocate
				std::allocator_traits<allocator_type>::deallocate(alloc, m_begin, capacity());
				m_begin = std::allocator_traits<allocator_type>::allocate(alloc, new_size);
				m_end = m_begin + new_size;
			}

			for (pointer ptr = m_begin; a_begin != a_end; ++ptr, ++a_begin)
				std::allocator_traits<allocator_type>::construct(alloc, ptr, *a_begin);

			m_head = m_begin;
			m_tail = m_begin + new_size - 1;
			m_size = new_size;
		}

		//@brief Assigns a number of elements to the cyclic buffer. This is will replace the current elements
		//@param a_count: The amount of elements to be created
		//@param a_value: The value the elements shall be constructed with
		constexpr auto assign(size_type a_count, const_reference a_value) -> void {
			clear();
			allocator_type alloc = allocator_type();
			if (a_count > capacity()) { // Reallocate
				std::allocator_traits<allocator_type>::deallocate(alloc, m_begin, capacity());
				m_begin = std::allocator_traits<allocator_type>::allocate(alloc, a_count);
				m_end = m_begin + a_count;
			}

			m_size = a_count;
			for (pointer ptr = m_begin; a_count != 0; ++ptr, --a_count)
				std::allocator_traits<allocator_type>::construct(alloc, ptr, a_value);

			m_head = m_begin;
			m_tail = m_begin + m_size - 1;
		}

		//@brief Assigns an initializer list to the cyclic buffer
		//@param a_list: The initializer list
		constexpr auto assign(std::initializer_list<value_type> a_list) -> void {
			assign(a_list.begin(), a_list.end());  /// MYTodo: does this have to move the elements?
		}

		//@brief Constructs an element in the buffer from parameters at the tail of the buffer. If the buffer is full the element at the head will be overwritten
		//@param a_args: Parameters used to construct the element
		//@return A reference to the constructed element
		template<typename... Args>
		constexpr auto emplace_back(Args&&... a_args) -> reference {
			allocator_type alloc = allocator_type();
			if (!empty())
				increment(m_tail);

			if (full()) { // Overwrite head
				std::allocator_traits<allocator_type>::destroy(alloc, m_head);
				increment(m_head);
			}
			else ++m_size;

			std::allocator_traits<allocator_type>::construct(alloc, m_tail, std::forward<Args>(a_args)...);
			return *m_tail;
		}

		//@brief Adds a element from a const reference at the tail of the buffer. If the buffer is full the element at the head will be overwritten
		//@param a_value: The element to be added
		constexpr auto push_back(const_reference a_value) -> void { emplace_back(a_value); }

		//@brief Adds a element using move semantics at the tail of the buffer. If the buffer is full the element at the head will be overwritten
		//@param a_value: The element to be added
		constexpr auto push_back(value_type&& a_value) -> void { emplace_back(std::move(a_value)); }

		//@brief Destroys the element as the tail of the cyclic buffer
		constexpr auto pop_back() -> void {
			MYL_ASSERT(!empty(), "Calling pop back on an empty cyclic buffer is undefined behavior!");
			allocator_type alloc = allocator_type();
			std::allocator_traits<allocator_type>::destroy(alloc, m_tail);
			if (--m_size != 0)
				decrement(m_tail);
		}

		//@brief Constructs an element in the buffer from parameters at the head of the buffer. If the buffer is full the element at the tail will be overwritten
		//@param a_args: Parameters used to construct the element
		//@return A reference to the constructed element
		template<typename... Args>
		constexpr auto emplace_front(Args&&... a_args) -> reference {
			allocator_type alloc = allocator_type();
			if (!empty())
				decrement(m_head);

			if (full()) { // Overwrite tail
				std::allocator_traits<allocator_type>::destroy(alloc, m_tail);
				decrement(m_tail);
			}
			else ++m_size;

			std::allocator_traits<allocator_type>::construct(alloc, m_head, std::forward<Args>(a_args)...);
			return *m_head;
		}

		//@brief Adds a element from a const reference at the head of the buffer. If the buffer is full the element at the tail will be overwritten
		//@param a_value: The element to be added
		constexpr auto push_front(const_reference a_value) -> void { emplace_front(a_value); }

		//@brief Adds a element using move semantics at the head of the buffer. If the buffer is full the element at the tail will be overwritten
		//@param a_value: The element to be added
		constexpr auto push_front(value_type&& a_value) -> void { emplace_front(std::move(a_value)); }

		//@brief Destroys the element as the head of the cyclic buffer
		constexpr auto pop_front() -> void {
			MYL_ASSERT(!empty(), "Calling pop front on an empty cyclic buffer is undefined behavior!");
			allocator_type alloc = allocator_type();
			std::allocator_traits<allocator_type>::destroy(alloc, m_head);
			if (--m_size != 0)
				increment(m_head);
		}

		//@brief Chanes the amount of elements
		//@param a_size: The new size of the buffer
		//@param a_value: The value new elements will be
		constexpr auto resize(size_type a_size, const_reference a_value) -> void {
			if (a_size > m_size) {
				reserve(a_size);
				fill_out(a_value);
			}
			else if (a_size < m_size)
				while (m_size != a_size)
					pop_back();
		}

		//@brief Chanes the amount of elements
		//@param a_size: The new size of the buffer
		constexpr auto resize(size_type a_size) -> void {
			resize(a_size, value_type{});
		}

		//@brief Changes the capcity of the cyclic buffer. Can not reduce the capacity of the cyclic buffer
		//@param a_capacity: The new capacity
		constexpr auto reserve(size_type a_capacity) -> void {
			if (a_capacity > capacity()) {
				allocator_type alloc = allocator_type();
				pointer new_begin = std::allocator_traits<allocator_type>::allocate(alloc, a_capacity);

				if (linear())
					std::uninitialized_move(m_head, m_tail + 1, new_begin);
				else {
					auto next = std::uninitialized_move(m_head, m_end, new_begin);
					std::uninitialized_move(m_begin, m_tail + 1, next);
				}

				std::allocator_traits<allocator_type>::deallocate(alloc, m_begin, capacity());
				m_begin = new_begin;
				m_end = m_begin + a_capacity;
				m_head = m_begin;
				m_tail = m_head + m_size - 1;
			}
		}

		//@brief Removes unsed capacity
		constexpr auto shrink_to_fit() -> void {
			if (capacity() > m_size) {
				allocator_type alloc = allocator_type();
				pointer new_begin = std::allocator_traits<allocator_type>::allocate(alloc, m_size);

				if (linear())
					std::uninitialized_move(m_head, m_tail + 1, new_begin);
				else {
					auto next = std::uninitialized_move(m_head, m_end, new_begin);
					std::uninitialized_move(m_begin, m_tail + 1, next);
				}

				std::allocator_traits<allocator_type>::deallocate(alloc, m_begin, capacity());
				m_begin = new_begin;
				m_end = m_begin + m_size;
				m_head = m_begin;
				m_tail = m_head + m_size - 1;
			}
		}

		//@brief Changes the head of the buffer by rotating through the elements
		//@param a_new_head: The new head must be within the range of existing elements
		constexpr auto rotate(pointer a_new_head) -> void {
			MYL_ASSERT(!out_of_bounds(a_new_head), "The new head must be within the range of existing elements");
			m_head = a_new_head;
			m_tail = m_begin + ((offset() + m_size) % m_size) - 1;
		}

		//@brief Changes the head of the buffer by rotating through the elements
		//@param a_position: The new position of the head of the buffer relative to the current offset
		constexpr auto rotate(isize a_position) -> void {
			m_head = m_begin + ((offset() + a_position - 1) % m_size) + 1;
			m_tail = m_begin + ((offset() + m_size) % m_size) - 1;
		}

		//@brief Aligns elements to the beginning of the data block
		constexpr auto align() -> void {
			if (m_head == m_begin)
				return;

			if (empty()) {
				m_head = m_begin;
				m_tail = m_begin;
				return;
			}

			size_type cap = capacity();

			allocator_type alloc = allocator_type();
			pointer new_begin = std::allocator_traits<allocator_type>::allocate(alloc, cap);

			auto next = std::uninitialized_move(m_head, m_end, new_begin);
			std::uninitialized_move(m_begin, m_tail + 1, next);

			std::allocator_traits<allocator_type>::deallocate(alloc, m_begin, cap);
			m_begin = new_begin;
			m_end = m_begin + cap;
			m_head = m_begin;
			m_tail = m_head + m_size - 1;
		}

		// Element access

		//@return The a reference to the head of the buffer. This will not always be the same as the beginning of the data block
		MYL_NO_DISCARD constexpr auto front() -> reference { return *m_head; }

		//@return The a const reference to the head of the buffer. This will not always be the same as the beginning of the data block
		MYL_NO_DISCARD constexpr auto front() const -> const_reference { return *m_head; }

		//@return The a reference to the tail of the buffer. This will not always be the same as the end of the data block
		MYL_NO_DISCARD constexpr auto back() -> reference { return *m_tail; }

		//@return The a const reference to the tail of the buffer. This will not always be the same as the end of the data block
		MYL_NO_DISCARD constexpr auto back() const -> const_reference { return *m_tail; }

		//@param a_position: The element's position in the buffer
		//@return A reference an element in the position relative to the head of the cyclic buffer
		MYL_NO_DISCARD constexpr auto at(size_type a_position) -> reference {
			pointer ptr = &m_begin[(offset() + a_position) % capacity()];
			MYL_ASSERT(!out_of_bounds(ptr), "Accessing an out of bounds element is undefined behavior!");
			if (out_of_bounds(ptr))
				throw std::out_of_range("Accessing an out of bounds element is undefined behavior!");
			return *ptr;
		}

		//@param a_position: The element's position in the buffer
		//@return A const reference an element in the position relative to the head of the cyclic buffer
		MYL_NO_DISCARD constexpr auto at(size_type a_position) const -> const_reference {
			return at(a_position);
		}

		//@param a_index: The index of the element. This does not consider element offset
		//@return Reference to the element
		MYL_NO_DISCARD constexpr auto operator[](size_type a_index) -> reference {
			MYL_ASSERT(!out_of_bounds(&m_begin[a_index]), "Accessing an out of bounds element is undefined behavior!");
			return m_begin[a_index];
		}

		//@param a_index: The index of the element. This does not consider element offset
		//@return Const reference to the element
		MYL_NO_DISCARD constexpr auto operator[](size_type a_index) const -> const_reference {
			return (*this)[a_index];
		}
	private:
		inline constexpr auto increment(pointer& a_ptr) const noexcept -> void { a_ptr == m_end - 1 ? a_ptr = m_begin : ++a_ptr; }
		inline constexpr auto decrement(pointer& a_ptr) const noexcept -> void { a_ptr == m_begin ? a_ptr = m_end - 1 : --a_ptr; }

		inline constexpr auto out_of_bounds(pointer a_ptr) const noexcept -> bool {
			return linear() ?
				m_head > a_ptr || a_ptr > m_tail : // Not head -> tail
				m_begin > a_ptr || !(m_end > a_ptr) || (m_head > a_ptr && a_ptr > m_tail); // Not begin -> end - 1 and not between tail and head
		}
	};
}