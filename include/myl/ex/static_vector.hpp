#pragma once
/// https://pvs-studio.com/en/blog/posts/0989/#IDAD55A7674A
/// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0843r2.html
/// https://www.boost.org/doc/libs/1_59_0/doc/html/boost/container/static_vector.html

/// <=> op instead

#include <myl/iterative.hpp>

#include <stdexcept>
#include <initializer_list>
#include <memory>
#include <numeric>
#include <utility>

namespace myl {
	template<typename T, usize Capacity>
	class static_vector {
	public:
		static_assert(Capacity != 0, "A static vector with capacity 0 is invalid!");

		using value_type				= T;
		using size_type					= usize;
		using difference_type			= make_signed<size_type>;
		using reference					= value_type&;
		using const_reference			= const value_type&;
		using pointer					= value_type*;
		using const_pointer				= const value_type*;
		using iterator					= contiguous_iterator<static_vector>;
		using const_iterator			= const iterator;
		using reverse_iterator			= std::reverse_iterator<iterator>;
		using const_reverse_iterator	= const reverse_iterator;
	private:
		union {
			std::byte m_bytes[sizeof(value_type) * Capacity]; // This should never be accessed, is just a work around to prevent m_data constructors from triggering
			value_type m_data[Capacity];
		};

		pointer m_end = nullptr;
	public:
		// Constructors / Destructor

		MYL_NO_DISCARD constexpr static_vector() noexcept
			: m_end{ m_data } {}

		MYL_NO_DISCARD constexpr static_vector(size_type a_count, const value_type& a_value = value_type{})
			: m_end{ m_data } {
			MYL_ASSERT(Capacity >= a_count, "Constructing a static vector with more elements than it's capacity is undefined behavior!");
			assign(a_count, a_value);
		}

		MYL_NO_DISCARD constexpr static_vector(std::initializer_list<value_type> a_list)
			: m_end{ m_data } {
			MYL_ASSERT(Capacity >= a_list.size(), "Constructing a static vector with more elements than it's capacity is undefined behavior!");
			assign(a_list);
		}

		template<typename Iterator>
		MYL_NO_DISCARD constexpr static_vector(Iterator a_begin, Iterator a_end)
			: m_end{ m_data } {
			MYL_ASSERT(Capacity >= a_end - a_begin, "Constructing a static vector with more elements than it's capacity is undefined behavior!");
			assign(a_begin, a_end);
		}

		constexpr ~static_vector() {
			clear();
		}

		// Copy / Move Assignment

		///MYL_NO_DISCARD constexpr auto operator=(const static_vector&) -> static_vector& {
		///
		///}
		
		///MYL_NO_DISCARD constexpr auto operator=(static_vector&&) -> static_vector& {
		///
		///}
		
		///MYL_NO_DISCARD constexpr auto operator=(std::initializer_list<value_type>) -> static_vector& {
		///
		///}

		// Utilities

		MYL_NO_DISCARD constexpr static auto capacity() noexcept -> size_type { return Capacity; }
		MYL_NO_DISCARD constexpr static auto max_size() noexcept -> size_type { return std::numeric_limits<size_type>::max(); }

		MYL_NO_DISCARD constexpr auto size() const noexcept -> size_type { return m_end - m_data; }
		MYL_NO_DISCARD constexpr auto empty() const noexcept -> bool { return m_end == m_data; }
		MYL_NO_DISCARD constexpr auto full() const noexcept -> bool { return size() == Capacity; }

		MYL_NO_DISCARD constexpr auto data() noexcept -> pointer { return m_data; }
		MYL_NO_DISCARD constexpr auto data() const noexcept -> const_pointer { return m_data; }

		constexpr auto swap(static_vector& a_other) noexcept -> void {
			/// https://en.cppreference.com/w/cpp/container/vector/swap
			/// Do
		}

		// Iterators

		MYL_NO_DISCARD constexpr auto begin() noexcept -> iterator { return iterator(m_data); }
		MYL_NO_DISCARD constexpr auto begin() const noexcept -> const_iterator { return begin(); }
		MYL_NO_DISCARD constexpr auto cbegin() const noexcept -> const_iterator { return begin(); }
		MYL_NO_DISCARD constexpr auto end() noexcept -> iterator { return iterator(m_end); }
		MYL_NO_DISCARD constexpr auto end() const noexcept -> const_iterator { return end(); }
		MYL_NO_DISCARD constexpr auto cend() const noexcept -> const_iterator { return end(); }
		MYL_NO_DISCARD constexpr auto rbegin() noexcept -> reverse_iterator { return reverse_iterator(end()); }
		MYL_NO_DISCARD constexpr auto rbegin() const noexcept -> const_reverse_iterator { return rbegin(); }
		MYL_NO_DISCARD constexpr auto crbegin() const noexcept -> const_reverse_iterator { return rbegin(); }
		MYL_NO_DISCARD constexpr auto rend() noexcept -> reverse_iterator { return reverse_iterator(begin()); }
		MYL_NO_DISCARD constexpr auto rend() const noexcept -> const_reverse_iterator { return rend(); }
		MYL_NO_DISCARD constexpr auto crend() const noexcept -> const_reverse_iterator { return rend(); }

		// Modifiers

		constexpr auto clear() noexcept -> void {
			if (!empty())
				pop_back(size()); // Need to call the destructors manually as the c-array within the union will not call them
		}

		constexpr auto fill(const value_type& a_value) noexcept -> void {
			clear();
			fill_up(a_value);
		}

		constexpr auto fill_up(const value_type& a_value) noexcept -> void {
			while (!full())
				push_back(a_value);
		}

		constexpr auto assign(size_type a_count, const value_type& a_value) -> void {
			MYL_ASSERT(Capacity >= a_count, "Constructing a static vector with more elements than it's capacity is undefined behavior!");
			clear();
			for (pointer ptr = m_data; a_count != 0; ++ptr, --a_count)
				call_constructor(ptr, a_value);
		}

		template<typename Iterator>
		constexpr auto assign(Iterator a_begin, Iterator a_end) -> void {
			MYL_ASSERT(Capacity >= a_end - a_begin, "Constructing a static vector with more elements than it's capacity is undefined behavior!");
			clear();
			for (pointer ptr = m_data; a_begin != a_end; ++ptr, ++a_begin)
				call_constructor(ptr, *a_begin);
		}

		constexpr auto assign(std::initializer_list<value_type> a_list) -> void {
			MYL_ASSERT(Capacity >= a_list.size(), "Constructing a static vector with more elements than it's capacity is undefined behavior!");
			assign(a_list.begin(), a_list.end()); /// MYTodo: does this have to move the elements?
		}

		template<typename... Args>
		constexpr auto emplace_back(Args&&... a_args) -> reference {
			MYL_ASSERT(!full(), "Adding an element to a full static vector is undefined behavior!");

			call_constructor(m_end, std::forward<Args>(a_args)...);

			pointer t = m_end;
			++m_end;
			return *t;
		}

		///template<typename... Args>
		///MYL_NO_DISCARD constexpr auto emplace(const_iterator, Args&&...) -> iterator {
		///	MYL_ASSERT(!full(), "Adding an element to a full static vector is undefined behavior!");
		///}

		constexpr auto push_back(value_type&& a_value) -> void {
			MYL_ASSERT(!full(), "Adding an element to a full static vector is undefined behavior!");
			*m_end = std::move(a_value);
			++m_end;
		}

		constexpr auto push_back(const value_type& a_value) -> void {
			MYL_ASSERT(!full(), "Adding an element to a full static vector is undefined behavior!");
			emplace_back(a_value);
		}

		constexpr auto pop_back() -> void {
			MYL_ASSERT(!empty(), "Calling pop back on an empty static vector is undefined behavior!");
			--m_end;
			m_end->~value_type();
		}

		constexpr auto pop_back(size_type a_count) -> void {
			MYL_ASSERT(a_count >= size(), "Popping more elements than the static vector holds is undefined behavior!");
			while (a_count != 0) {
				pop_back();
				--a_count;
			}
		}

		///MYL_NO_DISCARD constexpr auto insert(const_iterator, const value_type&) -> iterator {
		///	MYL_ASSERT(!full(), "Adding an element to a full static vector is undefined behavior!");
		///}
		
		///MYL_NO_DISCARD constexpr auto insert(const_iterator, value_type&&) -> iterator {
		///	MYL_ASSERT(!full(), "Adding an element to a full static vector is undefined behavior!");
		///}
		
		///MYL_NO_DISCARD constexpr auto insert(const_iterator, size_type, const value_type&) -> iterator {
		///	MYL_ASSERT(!full(), "Adding an element to a full static vector is undefined behavior!");
		///}
		
		///MYL_NO_DISCARD constexpr auto insert(const_iterator, std::initializer_list<value_type>) -> iterator {
		///	MYL_ASSERT(!full(), "Adding an element to a full static vector is undefined behavior!");
		///}
		
		///template<typename Iterator>
		///MYL_NO_DISCARD constexpr auto insert(const_iterator, Iterator, Iterator) -> iterator {
		///	MYL_ASSERT(!full(), "Adding an element to a full static vector is undefined behavior!");
		///}
		
		///MYL_NO_DISCARD constexpr auto erase(const_iterator a_it) -> iterator {
		///	Iterator following the last removed element.
		///	If pos refers to the last element, then the end() iterator is returned.
		///}
		
		///MYL_NO_DISCARD constexpr auto erase(const_iterator, const_iterator) -> iterator {
		/// Iterator following the last removed element.
		/// If last == end() prior to removal, then the updated end() iterator is returned.
		/// If[first, last) is an empty range, then last is returned.
		///}

		// Element access

		MYL_NO_DISCARD constexpr auto front() -> reference { return *m_data; }
		MYL_NO_DISCARD constexpr auto front() const -> const_reference { return front(); }
		MYL_NO_DISCARD constexpr auto back() -> reference { return *(m_end - 1); }
		MYL_NO_DISCARD constexpr auto back() const -> const_reference { return back(); }

		MYL_NO_DISCARD constexpr auto at(size_type a_pos) -> reference {
			MYL_ASSERT(!out_of_bounds(m_data + a_pos), "Accessing an out of bounds element is undefined behavior!");
			if (out_of_bounds(m_data + a_pos))
				throw std::out_of_range("Accessing an out of bounds element is undefined behavior!"); /// MYTodo: Should this call a myl::out_of_bounds exception?
			return (*this)[a_pos];
		}

		MYL_NO_DISCARD constexpr auto at(size_type a_pos) const-> const_reference {
			return at(a_pos);
		}

		MYL_NO_DISCARD constexpr auto operator[](size_type a_pos) -> reference {
			MYL_ASSERT(!out_of_bounds(m_data + a_pos), "Accessing an out of bounds element is undefined behavior!");
			return m_data[a_pos];
		}

		MYL_NO_DISCARD constexpr auto operator[](size_type a_pos) const -> const_reference {
			return (*this)[a_pos];
		}
	private:
		template<typename... Args>
		inline constexpr auto call_constructor(pointer a_ptr, Args&&... a_args) -> void {
			std::construct_at(a_ptr, std::forward<Args>(a_args)...);
		}

		inline constexpr auto out_of_bounds(pointer a_ptr) const noexcept -> bool {
			return !(a_ptr < m_end);
		}
	};

	/// https://en.cppreference.com/w/cpp/container/vector/operator_cmp

	template<typename T, usize C>
	MYL_NO_DISCARD constexpr auto operator==(const static_vector<T, C>& l, const static_vector<T, C>& r) -> bool {
		return l.m_data == r.m_data && l.m_end == r.m_end;
	}

	template<typename T, usize C>
	MYL_NO_DISCARD constexpr auto operator<(const static_vector<T, C>& l, const static_vector<T, C>& r) -> bool {
		return l.size() < r.size();
	}

	template<typename T, usize C>
	MYL_NO_DISCARD constexpr auto operator<=(const static_vector<T, C>& l, const static_vector<T, C>& r) -> bool {
		return l.size() <= r.size();
	}

	template<typename T, usize C>
	MYL_NO_DISCARD constexpr auto operator>(const static_vector<T, C>& l, const static_vector<T, C>& r) -> bool {
		return l.size() > r.size();
	}

	template<typename T, usize C>
	MYL_NO_DISCARD constexpr auto operator>=(const static_vector<T, C>& l, const static_vector<T, C>& r) -> bool {
		return l.size() >= r.size();
	}

	/// https://en.cppreference.com/w/cpp/container/vector/erase2

	///template<typename T, usize Capacity>
	///MYL_NO_DISCARD constexpr typename auto erase(static_vector<T, Capacity>& v, const T& value) -> static_vector<T, Capacity>::size_type {
	///
	///}
	
	///template<typename T, usize Capacity>
	///MYL_NO_DISCARD constexpr typename auto erase_if(static_vector<T, Capacity>& v, Pred pred) -> static_vector<T, Capacity>::size_type {
	///
	///}

	template<typename T, usize C>
	constexpr auto swap(static_vector<T, C>& a, static_vector<T, C>& b) noexcept(noexcept(a.swap(b))) -> void {
		a.swap(b);
	}
}