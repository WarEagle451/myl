#pragma once
#include <myl/iterative.hpp>

#include <algorithm>
#include <compare>
#include <initializer_list>
#include <memory>
#include <utility>

#ifndef MYL_NO_EXCEPTIONS
#   include <stdexcept>
#endif

/// MYTodo: static_vector.hpp
/// - Consider removing initializer_list, replace with parameter packs. Would reduce unnecessary copy and move ctors
///     MYL_NO_DISCARD constexpr static_vector(std::convertible_to<value_type> auto&&... args) requires(sizeof...(args) <= Capacity);
///     - m_begin{ args... }, causes unwanted default constructions
///     - Contructor where the first parameter in the pack is convertible to a int results in the (count, value) constructor being choosen
/// - const_casts should not be needed

namespace myl {
    template<typename T, usize Capacity>
    class static_vector {
    public:
        static_assert(Capacity != 0, "myl::static_vector cannot have 0 capacity");

        using value_type             = T;
        using size_type              = usize;
        using difference_type        = std::ptrdiff_t;
        using reference              = value_type&;
        using const_reference        = const value_type&;
        using pointer                = value_type*;
        using const_pointer          = const value_type*;
        using iterator               = contiguous_iterator<value_type>;
        using const_iterator         = contiguous_const_iterator<value_type>;
        using reverse_iterator       = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    private:
        // Members

        union { // Used to prevent the array object's constructors from running
            std::byte  m_dummy{ 0 };
            value_type m_begin[Capacity];
        };
        pointer m_end = m_begin;

        // Helpers

        static consteval auto error_str_out_of_bounds() -> const char* { return "Element is out of bounds of the container!"; }
        static consteval auto error_str_beyond_capacity() -> const char* { return "Container will be beyond capacity, increasing the size past capacity is illegal!"; }
        static consteval auto error_str_not_enough_elements() -> const char* { return "Container doesn't contain enough elements to pop!"; }
    public:
        // Constructors, Destructor, Assignment

        MYL_NO_DISCARD constexpr static_vector() noexcept = default;

        MYL_NO_DISCARD constexpr static_vector(const static_vector& other) noexcept(std::is_nothrow_copy_constructible_v<value_type>)
            : m_end{ std::uninitialized_copy(other.begin(), other.end(), m_begin) } {}

        MYL_NO_DISCARD constexpr static_vector(static_vector&& other) noexcept(std::is_nothrow_move_constructible_v<value_type>)
            : m_end{ std::uninitialized_move(other.m_begin, other.m_end, m_begin) } {}

        MYL_NO_DISCARD constexpr static_vector(size_type count, const value_type& value = value_type()) {
            MYL_ASSERT(count <= Capacity, error_str_beyond_capacity());
#ifndef MYL_NO_EXCEPTIONS
            if (count > Capacity)
                throw std::length_error(error_str_beyond_capacity());
#endif
            m_end = std::uninitialized_fill_n(m_begin, count, value);
        }

        template<std::input_iterator It>
        MYL_NO_DISCARD constexpr static_vector(It first, It last) {
            MYL_ASSERT(std::distance(first, last) <= static_cast<difference_type>(Capacity), error_str_beyond_capacity());
#ifndef MYL_NO_EXCEPTIONS
            if (std::distance(first, last) <= static_cast<difference_type>(Capacity))
                throw std::length_error(error_str_beyond_capacity());
#endif
            m_end = std::uninitialized_copy(first, last, m_begin);
        }

        MYL_NO_DISCARD constexpr static_vector(std::initializer_list<value_type> list)
            : static_vector(list.begin(), list.end()) {}

        template<usize N>
        MYL_NO_DISCARD constexpr static_vector(const static_vector<value_type, N>& other) noexcept(std::is_nothrow_copy_constructible_v<value_type>) requires(N < Capacity)
            : m_end{ std::uninitialized_copy(other.begin(), other.end(), m_begin) } {}

        constexpr ~static_vector() {
            std::destroy(m_begin, m_end);
        }

        constexpr auto operator=(const static_vector& other) noexcept(std::is_nothrow_copy_assignable_v<value_type>) -> static_vector& {
            if (this == std::addressof(other))
                return *this;

            std::copy(other.begin(), other.end(), m_begin);
            m_end = m_begin + other.size();
            return *this;
        }

        constexpr auto operator=(static_vector&& other) noexcept(std::is_nothrow_move_assignable_v<value_type>) -> static_vector& {
            if (this == std::addressof(other))
                return *this;

            std::move(other.m_begin, other.m_end, m_begin);
            m_end = m_begin + other.size();
            return *this;
        }

        constexpr auto operator=(std::initializer_list<value_type> list) -> static_vector& {
            MYL_ASSERT(list.size() <= Capacity, error_str_beyond_capacity());
#ifndef MYL_NO_EXCEPTIONS
            if (list.size() > Capacity)
                throw std::length_error(error_str_beyond_capacity());
#endif
            std::copy(list.begin(), list.end(), m_begin);
            m_end = m_begin + list.size();
            return *this;
        }

        // Iterators

        MYL_NO_DISCARD constexpr auto begin() noexcept -> iterator {
            return iterator(m_begin);
        }

        MYL_NO_DISCARD constexpr auto begin() const noexcept -> const_iterator {
            return const_iterator(m_begin);
        }

        MYL_NO_DISCARD constexpr auto cbegin() const noexcept -> const_iterator {
            return begin();
        }

        MYL_NO_DISCARD constexpr auto end() noexcept -> iterator {
            return iterator(m_end);
        }

        MYL_NO_DISCARD constexpr auto end() const noexcept -> const_iterator {
            return const_iterator(m_end);
        }

        MYL_NO_DISCARD constexpr auto cend() const noexcept -> const_iterator {
            return end();
        }

        MYL_NO_DISCARD constexpr auto rbegin() noexcept -> reverse_iterator {
            return std::make_reverse_iterator(end());
        }

        MYL_NO_DISCARD constexpr auto rbegin() const noexcept -> const_reverse_iterator {
            return std::make_reverse_iterator(cend());
        }

        MYL_NO_DISCARD constexpr auto crbegin() const noexcept -> const_reverse_iterator {
            return rbegin();
        }

        MYL_NO_DISCARD constexpr auto rend() noexcept -> reverse_iterator {
            return std::make_reverse_iterator(begin());
        }

        MYL_NO_DISCARD constexpr auto rend() const noexcept -> const_reverse_iterator {
            return std::make_reverse_iterator(cbegin());
        }

        MYL_NO_DISCARD constexpr auto crend() const noexcept -> const_reverse_iterator {
            return rend();
        }

        // Utilities

        MYL_NO_DISCARD constexpr auto data() const noexcept -> const_pointer {
            return m_begin;
        }

        MYL_NO_DISCARD constexpr auto data() noexcept -> pointer {
            return m_begin;
        }

        MYL_NO_DISCARD consteval auto max_size() noexcept -> difference_type {
            return static_cast<difference_type>(Capacity);
        }

        MYL_NO_DISCARD constexpr auto size() const noexcept -> size_type {
            return static_cast<size_type>(m_end - m_begin);
        }

        MYL_NO_DISCARD consteval auto capacity() const noexcept -> size_type {
            return Capacity;
        }

        MYL_NO_DISCARD constexpr auto empty() const noexcept -> bool {
            return m_begin == m_end;
        }

        MYL_NO_DISCARD constexpr auto full() const noexcept -> bool {
            return m_end == m_begin + Capacity;
        }

        // Access

        MYL_NO_DISCARD constexpr auto front() -> reference {
            MYL_ASSERT(!empty(), "No front element exists!");
            return m_begin[0];
        }

        MYL_NO_DISCARD constexpr auto front() const -> const_reference {
            MYL_ASSERT(!empty(), "No front element exists!");
            return m_begin[0];
        }

        MYL_NO_DISCARD constexpr auto back() -> reference {
            MYL_ASSERT(!empty(), "No back element exists!");
            return *(m_end - 1);
        }

        MYL_NO_DISCARD constexpr auto back() const -> const_reference {
            MYL_ASSERT(!empty(), "No back element exists!");
            return *(m_end - 1);
        }

        MYL_NO_DISCARD constexpr auto at(size_type index) -> reference {
            MYL_ASSERT(index < size(), error_str_out_of_bounds());
#ifndef MYL_NO_EXCEPTIONS
            if (index >= size())
                throw std::out_of_range(error_str_out_of_bounds());
#endif
            return m_begin[index];
        }

        MYL_NO_DISCARD constexpr auto at(size_type index) const -> const_reference {
            MYL_ASSERT(index < size(), error_str_out_of_bounds());
#ifndef MYL_NO_EXCEPTIONS
            if (index >= size())
                throw std::out_of_range(error_str_out_of_bounds());
#endif
            return m_begin[index];
        }

        MYL_NO_DISCARD constexpr auto operator[](size_type index) -> reference {
            MYL_ASSERT(index < size(), error_str_out_of_bounds());
            return m_begin[index];
        }

        MYL_NO_DISCARD constexpr auto operator[](size_type index) const -> const_reference {
            MYL_ASSERT(index < size(), error_str_out_of_bounds());
            return m_begin[index];
        }

        // Modifiers

        template<typename... Args>
        constexpr auto emplace(const_iterator position, Args&&... args) -> iterator {
            pointer where = const_cast<pointer>(position.operator->());

            MYL_ASSERT(m_begin <= where && where <= m_end, error_str_out_of_bounds());
            MYL_ASSERT(!full(), error_str_beyond_capacity());
#ifndef MYL_NO_EXCEPTIONS
            if (m_begin > where || where > m_end)
                throw std::out_of_range(error_str_out_of_bounds());

            if (full())
                throw std::length_error(error_str_beyond_capacity());
#endif
            if (where == m_end)
                std::construct_at(m_end, std::forward<Args>(args)...);
            else {
                value_type temp(std::forward<Args>(args)...); // Strong exception guarantee
                std::move_backward(where, m_end, m_end + 1);
                std::construct_at(where, std::move(temp));
            }

            ++m_end;
            return position;
        }

        template<typename... Args>
        constexpr auto emplace_back(Args&&... args) -> reference {
            MYL_ASSERT(!full(), error_str_beyond_capacity());
#ifndef MYL_NO_EXCEPTIONS
            if (full())
                throw std::length_error(error_str_beyond_capacity());
#endif
            pointer out = std::construct_at(m_end, std::forward<Args>(args)...);
            ++m_end;
            return *out;
        }

        constexpr auto push_back(const value_type& value) -> void {
            emplace_back(value);
        }

        constexpr auto push_back(value_type&& value) -> void {
            emplace_back(std::move(value));
        }

        constexpr auto pop_back() -> void {
            MYL_ASSERT(!empty(), error_str_not_enough_elements());
#ifndef MYL_NO_EXCEPTIONS
            if (empty())
                throw std::underflow_error(error_str_not_enough_elements());
#endif
            std::destroy_at(m_end - 1);
            --m_end;
        }

        constexpr auto pop_back(size_type count) -> void {
            MYL_ASSERT(size() >= count, error_str_not_enough_elements());
#ifndef MYL_NO_EXCEPTIONS
            if (size() < count)
                throw std::underflow_error(error_str_not_enough_elements());
#endif
            std::destroy(m_end - count, m_end);
            m_end -= count;
        }

        constexpr auto insert(const_iterator position, const value_type& value) -> iterator {
            return emplace(position, value);
        }

        constexpr auto insert(const_iterator position, value_type&& value) -> iterator {
            return emplace(position, std::move(value));
        }

        constexpr auto insert(const_iterator position, size_type count, const value_type& value) -> iterator {
            pointer where = const_cast<pointer>(position.operator->());
            MYL_ASSERT(m_begin <= where && where <= m_end, error_str_out_of_bounds());

            MYL_ASSERT(count <= Capacity - size(), error_str_beyond_capacity());
#ifndef MYL_NO_EXCEPTIONS
            if (count > Capacity - size())
                throw std::length_error(error_str_beyond_capacity());
#endif
            if (count == 0)
                return position;

            if (where != m_end)
                std::move_backward(where, m_end, m_end + count);
            std::uninitialized_fill_n(where, count, value);
            m_end += count;
            return position;
        }

        template<std::input_iterator It>
        constexpr auto insert(const_iterator position, It first, It last) -> iterator {
            pointer where = const_cast<pointer>(position.operator->());
            MYL_ASSERT(m_begin <= where && where <= m_end, error_str_out_of_bounds());

            const size_type count = static_cast<size_type>(std::distance(first, last));
            MYL_ASSERT(count <= Capacity - size(), error_str_beyond_capacity());
#ifndef MYL_NO_EXCEPTIONS
            if (count > Capacity - size())
                throw std::length_error(error_str_beyond_capacity());
#endif
            if (first == last)
                return position;

            if (where != m_end)
                std::move_backward(where, m_end, m_end + count);
            std::uninitialized_copy(first, last, where);
            m_end += count;
            return position;
        }

        constexpr auto insert(const_iterator position, std::initializer_list<value_type> list) -> iterator {
            return insert(position, list.begin(), list.end());
        }

        constexpr auto erase(const_iterator position) -> iterator {
            pointer where = const_cast<pointer>(position.operator->());

            MYL_ASSERT(m_begin <= where && where < m_end, error_str_out_of_bounds());
            std::destroy_at(where);
            if (where != m_end)
                std::move(where + 1, m_end, where);
            --m_end;
            return position;
        }

        constexpr auto erase(const_iterator first, const_iterator last) -> iterator {
            pointer first_ptr = const_cast<pointer>(first.operator->());
            pointer last_ptr = const_cast<pointer>(last.operator->());
            
            MYL_ASSERT(m_begin <= first_ptr && first_ptr <= m_end, error_str_out_of_bounds());
            MYL_ASSERT(m_begin <= last_ptr && last_ptr <= m_end, error_str_out_of_bounds());
            
            const size_type count = static_cast<size_type>(std::distance(first, last));
            if (count == 0)
                return last;

            std::destroy(first, last);
            if (last_ptr != m_end)
                std::uninitialized_move(last_ptr, m_end, first_ptr);
            m_end -= count;
            return first; // Will be the new m_end or the value of what last + 1 was before calling erase
        }

        constexpr auto assign(size_type count, const value_type& value) -> void {
            MYL_ASSERT(count <= Capacity, error_str_beyond_capacity());
#ifndef MYL_NO_EXCEPTIONS
            if (count > Capacity)
                throw std::length_error(error_str_beyond_capacity());
#endif
            std::destroy(m_begin, m_end);
            m_end = std::uninitialized_fill_n(m_begin, count, value);
        }

        template<std::input_iterator It>
        constexpr auto assign(It first, It last) -> void {
            const size_type count = std::distance(first, last);
            MYL_ASSERT(count <= Capacity, error_str_beyond_capacity());
#ifndef MYL_NO_EXCEPTIONS
            if (count > Capacity)
                throw std::length_error(error_str_beyond_capacity());
#endif
            std::destroy(m_begin, m_end);
            m_end = std::uninitialized_copy(first, last, m_begin);
        }

        constexpr auto assign(std::initializer_list<value_type> list) -> void {
            assign(list.begin(), list.end());
        }

        constexpr auto clear() noexcept -> void {
            std::destroy(m_begin, m_end);
            m_end = m_begin;
        }

        constexpr auto fill(const value_type& value) -> void {
            std::destroy(m_begin, m_end);
            std::uninitialized_fill(m_begin, m_begin + Capacity, value);
            m_end = m_begin + Capacity;
        }

        constexpr auto saturate(const value_type& value) -> void {
            std::uninitialized_fill(m_end, m_begin + Capacity, value);
            m_end = m_begin + Capacity;
        }

        constexpr auto resize(size_type count) -> void {
            MYL_ASSERT(count <= Capacity, error_str_beyond_capacity());
#ifndef MYL_NO_EXCEPTIONS
            if (count > Capacity)
                throw std::length_error(error_str_beyond_capacity());
#endif
            const size_type s = size();
            if (count < s)
                erase(begin() + count, end());
            else if (count > s) {
                const size_type needed = count - s;
                std::uninitialized_default_construct_n(m_end, needed);
                m_end += needed;
            }
        }

        constexpr auto resize(size_type count, const value_type& value) -> void {
            MYL_ASSERT(count <= Capacity, error_str_beyond_capacity());
#ifndef MYL_NO_EXCEPTIONS
            if (count > Capacity)
                throw std::length_error(error_str_beyond_capacity());
#endif
            const size_type s = size();
            if (count < s)
                erase(begin() + count, end());
            else if (count > s) {
                const size_type needed = count - s;
                std::uninitialized_fill_n(m_end, needed, value);
                m_end += needed;
            }
        }

        constexpr auto swap(static_vector& other) noexcept(std::is_nothrow_swappable_v<value_type>) -> void {
            const size_type a = size();
            const size_type b = other.size();
            const size_type min = a > b ? b : a;

            for (size_type i = 0; i != min; ++i)
                std::swap(m_begin[i], other.m_begin[i]);

            if (min == a) {
                std::move(other.m_begin + min, other.m_end, m_begin + min);
                m_end = m_begin + b;
                other.m_end = other.m_begin + min;
            }
            else {
                std::move(m_begin + min, m_end, other.m_begin + min);
                m_end = m_begin + min;
                other.m_end = other.m_begin + a;
            }
        }
    };

    template<typename T, usize C>
    MYL_NO_DISCARD constexpr auto operator==(const static_vector<T, C>& l, const static_vector<T, C>& r) noexcept -> bool {
        if (l.size() != r.size())
            return false;

        for (auto lit = l.cbegin(), rit = r.cbegin(); lit != l.cend(); ++lit, ++rit)
            if (*lit != *rit)
                return false;
        return true;
    }

    template<typename T, usize C>
    MYL_NO_DISCARD constexpr auto operator<=>(const static_vector<T, C>& l, const static_vector<T, C>& r) {
        return std::lexicographical_compare_three_way(l.cbegin(), l.cend(), r.cbegin(), r.cend());
    }
}

namespace std {
    template<typename T, myl::usize C>
    constexpr auto swap(myl::static_vector<T, C>& l, myl::static_vector<T, C>& r) noexcept(noexcept(l.swap(r))) -> void {
        l.swap(r);
    }

    template<typename T, myl::usize C, typename U>
    constexpr auto erase(myl::static_vector<T, C>& v, const U& value) -> typename myl::static_vector<T, C>::size_type {
        typename myl::static_vector<T, C>::size_type old_size = v.size();
        for (auto it = v.rbegin(), end = v.rend(); it != end; ++it)
            if (*it == value)
                v.erase(it.base() - 1);
        return old_size - v.size();
    }

    template<typename T, myl::usize C, typename Pred>
    constexpr auto erase_if(myl::static_vector<T, C>& v, Pred predicate) -> typename myl::static_vector<T, C>::size_type {
        typename myl::static_vector<T, C>::size_type old_size = v.size();
        for (auto it = v.rbegin(), end = v.rend(); it != end; ++it)
            if (predicate(*it))
                v.erase(it.base() - 1);
        return old_size - v.size();
    }
}
