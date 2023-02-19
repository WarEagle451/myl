#pragma once
#include <myl/circulator.hpp>

#include <initializer_list>
#include <memory>
#include <utility> // std::forward

/// MYTodo: cyclic_buffer.hpp
/// For debug modes there should be some Asserts to verify that stuff is correct eg
/// cyclic_buffer<int> after pop_back you can still access that var, can only do this with std::vector when it is in release mode
/// resize, swap, insert, erase, push / emplace ranges
/// should there be a function that fills the rest of the buffer?

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
		using iterator					= circulator<value_type>;
		using const_iterator			= const iterator;
		using reverse_iterator			= reverse_circulator<iterator>;
		using const_reverse_iterator	= const reverse_iterator;
	private:
		pointer m_begin = nullptr;
		pointer m_end = nullptr;
		pointer m_head = nullptr;
		pointer m_tail = nullptr;
		size_type m_size = 0;
	public:
		MYL_NO_DISCARD constexpr cyclic_buffer() = default;

		MYL_NO_DISCARD constexpr cyclic_buffer(std::initializer_list<value_type> a_list) {
			assign(a_list);
		}

		MYL_NO_DISCARD constexpr explicit cyclic_buffer(size_type a_capacity) noexcept(noexcept(allocator_type())) {
			allocator_type alloc = allocator_type();
			m_begin = std::allocator_traits<allocator_type>::allocate(alloc, a_capacity);
			m_end = m_begin + a_capacity;
			m_head = m_begin;
			m_tail = m_head;
		}

		MYL_NO_DISCARD constexpr explicit cyclic_buffer(size_type a_count, const_reference a_value) {
			assign(a_count, a_value);
		}

		template<typename InputIt>
		MYL_NO_DISCARD constexpr explicit cyclic_buffer(InputIt a_begin, InputIt a_end) {
			assign(a_begin, a_end);
		}

		constexpr ~cyclic_buffer() {
			clear();
			allocator_type alloc = allocator_type();
			std::allocator_traits<allocator_type>::deallocate(alloc, m_begin, capacity());
		}

		MYL_NO_DISCARD constexpr auto get_allocator() const -> allocator_type { return allocator_type(); }
		MYL_NO_DISCARD constexpr auto size() const noexcept -> size_type { return m_size; }
		MYL_NO_DISCARD constexpr auto max_size() const noexcept -> size_type { return static_cast<size_type>(~0); }
		MYL_NO_DISCARD constexpr auto capacity() const noexcept -> size_type { return static_cast<size_type>(m_end - m_begin); }
		MYL_NO_DISCARD constexpr auto offset() const noexcept -> difference_type { return static_cast<difference_type>(m_head - m_begin); }
		MYL_NO_DISCARD constexpr auto empty() const noexcept -> bool { return m_size == 0; }
		MYL_NO_DISCARD constexpr auto full() const noexcept -> bool { return m_size == capacity(); }
		MYL_NO_DISCARD constexpr auto linear() const noexcept -> bool { return m_head <= m_tail; }

		MYL_NO_DISCARD constexpr auto data() noexcept -> pointer { return m_begin; }
		MYL_NO_DISCARD constexpr auto data() const noexcept -> const_pointer { return m_begin; }

		MYL_NO_DISCARD constexpr auto at(size_type a_position) -> reference { return m_begin[(offset() + a_position) % capacity()]; }
		MYL_NO_DISCARD constexpr auto at(size_type a_position) const -> const_reference { return at(a_position); }

		MYL_NO_DISCARD constexpr auto front() -> reference { return *m_head; }
		MYL_NO_DISCARD constexpr auto front() const -> const_reference { return *m_head; }
		MYL_NO_DISCARD constexpr auto back() -> reference { return *m_tail; }
		MYL_NO_DISCARD constexpr auto back() const -> const_reference { return *m_tail; }

		MYL_NO_DISCARD constexpr auto begin() noexcept -> iterator { return iterator(m_head, m_begin, m_end, m_head, m_tail, empty()); } // Must check if empty, will run if passed false
		MYL_NO_DISCARD constexpr auto begin() const noexcept -> const_iterator { return begin(); }
		MYL_NO_DISCARD constexpr auto cbegin() const noexcept -> const_iterator { return begin(); }
		MYL_NO_DISCARD constexpr auto end() noexcept -> iterator { return iterator(m_head, m_begin, m_end, m_head, m_tail, true); }
		MYL_NO_DISCARD constexpr auto end() const noexcept -> const_iterator { return end(); }
		MYL_NO_DISCARD constexpr auto cend() const noexcept -> const_iterator { return end(); }

		MYL_NO_DISCARD constexpr auto rbegin() noexcept -> reverse_iterator { return reverse_iterator(m_head, m_begin, m_end, m_head, m_tail, empty()); } // Must check if empty, will run if passed false
		MYL_NO_DISCARD constexpr auto rbegin() const noexcept -> const_reverse_iterator { return rbegin(); }
		MYL_NO_DISCARD constexpr auto crbegin() const noexcept -> const_reverse_iterator { return rbegin(); }
		MYL_NO_DISCARD constexpr auto rend() noexcept -> reverse_iterator { return reverse_iterator(m_head, m_begin, m_end, m_head, m_tail, true); }
		MYL_NO_DISCARD constexpr auto rend() const noexcept -> const_reverse_iterator { return rend(); }
		MYL_NO_DISCARD constexpr auto crend() const noexcept -> const_reverse_iterator { return rend(); }

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

		constexpr auto push_back(const_reference a_value) -> void { emplace_back(a_value); }
		constexpr auto push_back(value_type&& a_value) -> void { emplace_back(std::move(a_value)); }

		constexpr auto pop_back() -> void {
			allocator_type alloc = allocator_type();
			std::allocator_traits<allocator_type>::destroy(alloc, m_tail);
			if (--m_size != 0)
				decrement(m_tail);
		}

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

		constexpr auto push_front(const_reference a_value) -> void { emplace_front(a_value); }
		constexpr auto push_front(value_type&& a_value) -> void { emplace_front(std::move(a_value)); }

		constexpr auto pop_front() -> void {
			allocator_type alloc = allocator_type();
			std::allocator_traits<allocator_type>::destroy(alloc, m_head);
			if (--m_size != 0)
				increment(m_head);
		}

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
			m_tail = m_begin + m_size - 1;
			m_size = new_size;
		}

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

		constexpr auto assign(std::initializer_list<value_type> a_list) -> void {
			assign(a_list.begin(), a_list.end());
		}

		constexpr auto fill(const_reference a_value) -> void {
			clear();
			allocator_type alloc = allocator_type();
			for (pointer ptr = m_begin; ptr != m_end; ++ptr)
				std::allocator_traits<allocator_type>::construct(alloc, ptr, a_value);

			m_head = m_begin;
			m_tail = m_end - 1;
			m_size = capacity();
		}

		constexpr auto clear() noexcept -> void {
			allocator_type alloc = allocator_type();
			while (!empty()) {
				std::allocator_traits<allocator_type>::destroy(alloc, m_tail);
				decrement(m_tail);
				--m_size;
			}
		
			m_tail = m_head; // decrement will set m_tail to m_end - 1
		}

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

		constexpr auto rotate(pointer a_new_head) -> void {
			m_head = a_new_head;
			m_tail = m_begin + ((offset() + m_size) % m_size) - 1;
		}

		constexpr auto rotate(isize a_position) -> void {
			m_head = m_begin + ((offset() + a_position - 1) % m_size) + 1;
			m_tail = m_begin + ((offset() + m_size) % m_size) - 1;
		}

		constexpr auto align() -> void {
			reserve(capacity());
		}

		MYL_NO_DISCARD constexpr auto operator[](size_type a_index) -> reference { return m_begin[a_index]; }
		MYL_NO_DISCARD constexpr auto operator[](size_type a_index) const -> const_reference { return m_begin[a_index]; }
	private:
		constexpr auto increment(pointer& a_ptr) const noexcept -> void { a_ptr == m_end - 1 ? a_ptr = m_begin : ++a_ptr; }
		constexpr auto decrement(pointer& a_ptr) const noexcept -> void { a_ptr == m_begin ? a_ptr = m_end - 1 : --a_ptr; }
	};
}