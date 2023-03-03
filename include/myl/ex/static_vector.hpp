#pragma once
/// https://pvs-studio.com/en/blog/posts/0989/#IDAD55A7674A
/// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0843r2.html
/// https://www.boost.org/doc/libs/1_59_0/doc/html/boost/container/static_vector.html

/// Restructure other containers like this

#include <myl/iterative.hpp>

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
		union { /// There has to be a better way to prevent the constructors in the C-array from being called
			std::byte m_bytes[sizeof(value_type) * Capacity]; // This should never be accessed, is just a work around
			value_type m_data[Capacity];
		};

		pointer m_end = nullptr;
	public:
		// Constructors / Destructor / Copy 

		MYL_NO_DISCARD constexpr static_vector() noexcept
			: m_end{ m_data } {}

		MYL_NO_DISCARD constexpr static_vector(size_type a_count, const value_type& a_value = value_type{})
			: m_end{ m_data } {
			/// Assert: cant construct a sv with more elements than capacity

			assign(a_count, a_value);
		}

		MYL_NO_DISCARD constexpr static_vector(std::initializer_list<value_type> a_list)
			: m_end{ m_data } {
			/// Assert list can not be bigger than cap
			assign(a_list);
		}

		///MYL_NO_DISCARD constexpr static_vector(const static_vector&);
		///MYL_NO_DISCARD constexpr static_vector(static_vector&&);
		///MYL_NO_DISCARD constexpr explicit static_vector(size_type);

		template<typename Iterator>
		MYL_NO_DISCARD constexpr static_vector(Iterator a_begin, Iterator a_end)
			: m_end{ m_data } {
			assign(a_begin, a_end);
		}

		constexpr ~static_vector() {
			clear();
		}

		// Copy / Move Assignment

		///MYL_NO_DISCARD constexpr auto operator=(const static_vector&)->static_vector&;
		///MYL_NO_DISCARD constexpr auto operator=(std::initializer_list<value_type>)->static_vector&;
		///MYL_NO_DISCARD constexpr auto operator=(static_vector&&)->static_vector&;

		// Utilities

		MYL_NO_DISCARD constexpr static auto capacity() noexcept -> size_type { return Capacity; }
		MYL_NO_DISCARD constexpr static auto max_size() noexcept -> size_type { return std::numeric_limits<size_type>::max(); }

		MYL_NO_DISCARD constexpr auto size() const noexcept -> size_type { return m_end - m_data; }
		MYL_NO_DISCARD constexpr auto empty() const noexcept -> bool { return m_end == m_data; }
		MYL_NO_DISCARD constexpr auto full() const noexcept -> bool { return size() == Capacity; }

		MYL_NO_DISCARD constexpr auto data() noexcept -> pointer { return m_data; }
		MYL_NO_DISCARD constexpr auto data() const noexcept -> const_pointer { return m_data; }

		constexpr auto swap(static_vector& a_other) -> void {
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
			// Need to call the destructors manually as the c-array within the union will not call them
			pop_back(size());
		}

		constexpr auto fill_up(const value_type& a_value) noexcept -> void { /// MYTodo: There must be a better way
			while (!full())
				push_back(a_value);
		}

		constexpr auto fill(const value_type& a_value) noexcept -> void {
			clear();
			fill_up(a_value);
		}

		///constexpr auto resize(size_type) -> void;
		///constexpr auto resize(size_type, const value_type & = value_type{}) -> void;

		template<typename Iterator>
		constexpr auto assign(Iterator, Iterator) -> void {
			/// Assert: Can't assign more elements than the capacity of a static vector
		}

		constexpr auto assign(std::initializer_list<value_type>) -> void {
			/// Assert: Can't assign more elements than the capacity of a static vector
		}

		constexpr auto assign(size_type, const value_type&) -> void {
			/// Assert: Can't assign more elements than the capacity of a static vector
		}

		template<typename... Args>
		constexpr auto emplace_back(Args&&... a_args) -> reference {
			/// Assert here if full

			call_constructor(m_end, std::forward<Args>(a_args)...);

			pointer t = m_end;
			++m_end;
			return *t;
		}

		///template<typename... Args>
		///constexpr auto emplace(const_iterator, Args&&...) -> iterator;

		constexpr auto push_back(value_type&& a_value) -> void {
			/// Assert here if full

			*m_end = std::move(a_value);
			++m_end;
		}

		constexpr auto push_back(const value_type& a_value) -> void {
			push_back(a_value);
		}

		constexpr auto pop_back() -> void {
			/// Assert if empty

			--m_end;
			call_destructor(m_end);
		}

		constexpr auto pop_back(size_type a_count) -> void {
			/// Assert if a_count > size

			while (a_count != 0) {
				pop_back();
				--a_count;
			}
		}

		///constexpr auto insert(const_iterator, const value_type&) -> iterator;
		///constexpr auto insert(const_iterator, value_type&&) -> iterator;
		///constexpr auto insert(const_iterator, size_type, const value_type&) -> iterator;
		///constexpr auto insert(const_iterator, std::initializer_list<value_type>) -> iterator;
		///template<typename Iterator>
		///constexpr auto insert(const_iterator, Iterator, Iterator) -> iterator;
		
		///constexpr auto erase(const_iterator) -> iterator;
		///constexpr auto erase(const_iterator, const_iterator) -> iterator;

		// Element access

		MYL_NO_DISCARD constexpr auto front() -> reference { return *m_data; }
		MYL_NO_DISCARD constexpr auto front() const -> const_reference { return front(); }
		MYL_NO_DISCARD constexpr auto back() -> reference { return *m_end; }
		MYL_NO_DISCARD constexpr auto back() const -> const_reference { return back(); }

		///MYL_NO_DISCARD constexpr auto at(size_type) -> reference;
		///MYL_NO_DISCARD constexpr auto at(size_type) const->const_reference;

		MYL_NO_DISCARD constexpr auto operator[](size_type a_pos) -> reference {
			/// Assert: check for out of bounds
			return m_data[a_pos];
		}

		MYL_NO_DISCARD constexpr auto operator[](size_type a_pos) const -> const_reference {
			/// Assert: check for out of bounds
			return operator[](a_pos);
		}
	private:
		template<typename... Args>
		inline constexpr auto call_constructor(pointer a_ptr, Args&&... a_args) -> void {
			/// Assert if the space is not empty

			std::construct_at(a_ptr, std::forward<Args>(a_args)...);
		}

		inline constexpr auto call_destructor(pointer a_ptr) -> void {
			/// Assert if ptr is null

			a_ptr->~value_type();
		}
	};

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

	template<typename T, usize C>
	constexpr auto swap(static_vector<T, C>& a, static_vector<T, C>& b) noexcept(noexcept(a.swap(b))) -> void {
		a.swap(b);
	}
}