#pragma once
#include <myl_wip/iterative.hpp>

#include <algorithm>
#include <compare>
#include <memory>
#include <utility>

#ifndef MYL_NO_EXCEPTIONS
#   include <stdexcept>
#endif

/// MYTodo: static_vector.hpp - Not yet
/// - Consider removing initializer_list, replace with parameter packs. Would reduce unnecessary copy and move ctors
///     MYL_NO_DISCARD constexpr static_vector(std::convertible_to<value_type> auto&&... args) requires(sizeof...(args) <= Capacity);
///     - m_begin{ args... }, causes unwanted default constructions
///     - Contructor where the first parameter in the pack is convertible to a int results in the (count, value) constructor being choosen
/// - Conditionally noexcept for back(), ==, <=>, others
/// - Specialization for pod types?

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
            u32        m_dummy = 0;
            value_type m_begin[Capacity];
        };
        pointer m_last = m_begin;

        // Helpers

        consteval const char* error_str_out_of_bounds       = "Element is out of bounds of the container!";
        consteval const char* error_str_beyond_capacity     = "Container will be beyond capacity, increasing the size past capacity is illegal!";
        consteval const char* error_str_not_enough_elements = "Container doesn't contain enough elements to pop!";
    public:
        // Constructors, Destructor, Assignment

        MYL_NO_DISCARD constexpr static_vector() noexcept = default;

        MYL_NO_DISCARD constexpr static_vector(const static_vector& other) noexcept(std::is_nothrow_copy_constructible_v<value_type>)
            : m_last{ std::uninitialized_copy(other.begin(), other.end(), m_begin) } {}

        MYL_NO_DISCARD constexpr static_vector(static_vector&& other) noexcept(std::is_nothrow_move_constructible_v<value_type>)
            : m_last{ std::uninitialized_move(other.begin(), other.end(), m_begin) } {}

        MYL_NO_DISCARD constexpr static_vector(size_type count, const value_type& value = value_type()) {
            MYL_ASSERT(count <= Capacity, error_str_beyond_capacity);
#ifndef MYL_NO_EXCEPTIONS
            if (count > Capacity)
                throw std::length_error(error_str_beyond_capacity);
#endif
            m_last = std::uninitialized_fill_n(m_begin, count, value);
        }

        template<std::input_iterator It>
        MYL_NO_DISCARD constexpr static_vector(It first, It last) {
            MYL_ASSERT(static_cast<size_type>(std::distance(first, last) <= Capacity, error_str_beyond_capacity);
#ifndef MYL_NO_EXCEPTIONS
            if (static_cast<size_type>(std::distance(first, last) > Capacity)
                throw std::length_error(error_str_beyond_capacity);
#endif
            m_last = std::uninitialized_copy(first, last, m_begin);
        }

        ///MYL_NO_DISCARD constexpr static_vector(std::initializer_list<value_type> list);

        template<usize N>
        MYL_NO_DISCARD constexpr static_vector(const static_vector<value_type, N>& other) noexcept(std::is_nothrow_copy_constructible_v<value_type>) requires(N < Capacity) {
            MYL_ASSERT(N <= Capacity, error_str_beyond_capacity);
#ifndef MYL_NO_EXCEPTIONS
            if (N > Capacity)
                throw std::length_error(error_str_beyond_capacity);
#endif
            m_last = std::uninitialized_copy(other.begin(), other.end(), m_begin);
        }

        constexpr ~static_vector() {
            std::destroy(m_begin, m_last);
        }

        constexpr auto operator=(const static_vector& other) noexcept(std::is_nothrow_copy_assignable_v<value_type>) -> static_vector& {
            if (this == &other)
                return *this;

            std::copy(other.begin(), other.end(), m_begin);
            m_last = m_begin + other.size();
            return *this;
        }

        constexpr auto operator=(static_vector&& other) noexcept(std::is_nothrow_move_assignable_v<value_type>) -> static_vector& {
            if (this == &other)
                return *this;

            std::move(other.begin(), other.end(), m_begin);
            m_last = m_begin + other.size();
            return *this;
        }

        ///constexpr auto operator=(std::initializer_list<value_type> list) -> static_vector&;

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
            return iterator(m_last);
        }

        MYL_NO_DISCARD constexpr auto end() const noexcept -> const_iterator {
            return const_iterator(m_last);
        }

        MYL_NO_DISCARD constexpr auto cend() const noexcept -> const_iterator {
            return end();
        }

        MYL_NO_DISCARD constexpr auto rbegin() noexcept -> reverse_iterator {
            return reverse_iterator(end());
        }

        MYL_NO_DISCARD constexpr auto rbegin() const noexcept -> const_reverse_iterator {
            return reverse_iterator(cend());
        }

        MYL_NO_DISCARD constexpr auto crbegin() const noexcept -> const_reverse_iterator {
            return rbegin();
        }

        MYL_NO_DISCARD constexpr auto rend() noexcept -> reverse_iterator {
            return reverse_iterator(begin());
        }

        MYL_NO_DISCARD constexpr auto rend() const noexcept -> const_reverse_iterator {
            return reverse_iterator(cbegin());
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

        MYL_NO_DISCARD constexpr auto max_size() noexcept -> difference_type { /// consteval?
            return static_cast<difference_type>(Capacity);
        }

        MYL_NO_DISCARD constexpr auto size() const noexcept -> size_type {
            return static_cast<size_type>(m_last - m_begin);
        }

        MYL_NO_DISCARD constexpr auto capacity() const noexcept -> size_type { /// consteval? if yes then use this over Capacity
            return Capacity;
        }

        MYL_NO_DISCARD constexpr auto empty() const noexcept -> bool {
            return m_begin == m_last;
        }

        MYL_NO_DISCARD constexpr auto full() const noexcept -> bool {
            return m_last == m_begin + Capacity;
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
            return *(m_last - 1);
        }

        MYL_NO_DISCARD constexpr auto back() const -> const_reference {
            MYL_ASSERT(!empty(), "No back element exists!");
            return *(m_last - 1);
        }

        MYL_NO_DISCARD constexpr auto at(size_type index) -> reference {
            MYL_ASSERT(index < size(), error_str_out_of_bounds);
#ifndef MYL_NO_EXCEPTIONS
            if (index >= size())
                throw std::out_of_range(error_str_out_of_bounds);
#endif
            return m_begin[index];
        }

        MYL_NO_DISCARD constexpr auto at(size_type index) const -> const_reference {
            MYL_ASSERT(index < size(), error_str_out_of_bounds);
#ifndef MYL_NO_EXCEPTIONS
            if (index >= size())
                throw std::out_of_range(error_str_out_of_bounds);
#endif
            return m_begin[index];
        }

        MYL_NO_DISCARD constexpr auto operator[](size_type index) -> reference {
            MYL_ASSERT(size() < index, error_str_out_of_bounds);
            return m_begin[index];
        }

        MYL_NO_DISCARD constexpr auto operator[](size_type index) const -> const_reference {
            MYL_ASSERT(size() < index, error_str_out_of_bounds);
            return m_begin[index];
        }

        // Modifiers

        template<typename... Args>
        constexpr auto emplace(const_iterator position, Args&&... args) -> iterator {
            MYL_ASSERT(m_begin <= position.operator->() && position.operator->() <= m_last, error_str_out_of_bounds);
            MYL_ASSERT(!full(), error_str_beyond_capacity);
#ifndef MYL_NO_EXCEPTIONS
            if (m_begin > position.operator->() || position.operator->() > m_last)
                throw std::out_of_range(error_str_out_of_bounds);

            if (full())
                throw std::length_error(error_str_beyond_capacity);
#endif
            if (position.operator->() == m_last)
                std::construct_at(m_last, std::forward<Args>(args)...);
            else {
                value_type temp(std::forward<Args>(args)...); // Strong exception guarantee
                std::move_backward(position.operator->(), m_last, m_last + 1);
                *(position.operator->()) = std::move(temp);
            }

            ++m_last;
            return position;
        }

        template<typename... Args>
        constexpr auto emplace_back(Args&&... args) -> reference {
            MYL_ASSERT(!full(), error_str_beyond_capacity);
#ifndef MYL_NO_EXCEPTIONS
            if (full())
                throw std::length_error(error_str_beyond_capacity);
#endif
            pointer out = std::construct_at(m_last, std::forward<Args>(args)...);
            ++m_last;
            return *out;
        }

        constexpr auto push_back(const value_type& value) -> void {
            emplace_back(value);
        }

        constexpr auto push_back(value_type&& value) -> void {
            emplace_back(std::move(value));
        }

        constexpr auto pop_back() -> void {
            MYL_ASSERT(!empty(), error_str_not_enough_elements);
#ifndef MYL_NO_EXCEPTIONS
            if (empty())
                throw std::underflow_error(error_str_not_enough_elements);
#endif
            std::destroy_at(m_last - 1);
            --m_last;
        }

        constexpr auto pop_back(size_type count) -> void {
            MYL_ASSERT(size() >= count, error_str_not_enough_elements);
#ifndef MYL_NO_EXCEPTIONS
            if (size() < count)
                throw std::underflow_error(error_str_not_enough_elements);
#endif
            std::destroy(m_last - count, m_last);
            m_last -= count;
        }

        constexpr auto insert(const_iterator position, const value_type& value) -> iterator {
            return emplace(position, value);
        }

        constexpr auto insert(const_iterator position, value_type&& value) -> iterator {
            return emplace(position, std::move(value));
        }

        ///constexpr auto insert(const_iterator position, size_type count, const value_type& value) -> iterator;

        ///template<std::input_iterator It>
        ///constexpr auto insert(const_iterator position, It first, It last) -> iterator;

        ///constexpr auto insert(const_iterator position, std::initializer_list<value_type> list) -> iterator;

        constexpr auto erase(const_iterator position) -> iterator {
            MYL_ASSERT(m_begin <= position.operator->() && position.operator->() <= m_last, error_str_out_of_bounds);
            std::destroy_at(position.operator->());
            --m_last;
            if (position.operator->() != m_last)
                move_range(position.operator->(), position.operator->() + 1, m_last);
            return position;
        }

        ///constexpr auto erase(const_iterator first, const_iterator last) -> iterator;

        constexpr auto assign(size_type count, const value_type& value) -> void {
            MYL_ASSERT(count <= Capacity, error_str_beyond_capacity);
#ifndef MYL_NO_EXCEPTIONS
            if (count > Capacity)
                throw std::length_error(error_str_beyond_capacity);
#endif
            std::destroy(m_begin, m_last);
            std::uninitialized_fill(m_begin, m_begin + count, value);
            m_last = m_begin;
        }

        ///template<std::input_iterator It>
        ///constexpr auto assign(It first, It last) -> void;

        ///constexpr auto assign(std::initializer_list<value_type> list) -> void;

        constexpr auto clear() noexcept -> void {
            std::destroy(m_begin, m_last);
            m_last = m_begin;
        }

        constexpr auto fill(const value_type& value) noexcept -> void { /// Only if the constructors of value type are noexcept
            std::destroy(m_begin, m_last);
            std::uninitialized_fill(m_begin, m_begin + Capacity, value);
            m_last = m_begin + Capacity;
        }

        constexpr auto saturate(const value_type& value) noexcept -> void { /// Only if the constructors of value type are noexcept
            std::uninitialized_fill(m_last, m_begin + Capacity, value);
            m_last = m_begin + Capacity;
        }

        ///constexpr auto resize(size_type count) -> void;

        ///constexpr auto resize(size_type count, const value_type& value) -> void;

        ///constexpr auto swap(static_vector& other) noexcept(std::is_nothrow_swappable_v<value_type>) -> void;
    };

    template<typename T, usize C>
    MYL_NO_DISCARD constexpr auto operator==(const static_vector<T, C>& l, const static_vector<T, C>& r) noexcept -> bool {
        if (l.size() != r.size())
            return false;

        for (auto lit = l.begin(), rit = r.begin(); lit != l.end(); ++lit, ++rit)
            if (*lit != *rit)
                return false;
        return true;
    }

    template<typename T, usize C>
    MYL_NO_DISCARD constexpr auto operator<=>(const static_vector<T, C>& l, const static_vector<T, C>& r) {
        return std::lexicographical_compare_three_way(l.begin(), l.end(), r.begin(), r.end());
    }
}

namespace std {
    ///template<typename T, usize C>
    ///constexpr auto swap(myl::static_vector<T, C>& l, myl::static_vector<T, C>& r) noexcept(noexcept(l.swap(r))) -> void {
    ///    l.swap(r);
    ///}

    template<typename T, usize C, typename U>
    constexpr auto erase(myl::static_vector<T, C>& v, const U& value) -> typename myl::static_vector<T, C>::size_type {
        typename myl::static_vector<T, C>::size_type old_size = v.size();
        for (auto it = v.rbegin(), end = v.rend(); it != end; ++it)
            if (*it == value)
                v.erase(it.operator->());
        return old_size - v.size();
    }

    template<typename T, usize C, typename Pred>
    constexpr auto erase_if(myl::static_vector<T, C>& v, Pred predicate) -> typename myl::static_vector<T, C>::size_type {
        typename myl::static_vector<T, C>::size_type old_size = v.size();
        for (auto it = v.rbegin(), end = v.rend(); it != end; ++it)
            if (predicate(*it))
                v.erase(it.operator->());
        return old_size - v.size();
    }
}
