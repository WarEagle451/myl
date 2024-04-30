#pragma once
#include <myl/definitions.hpp>

#include <memory>

// Use arg pack over initializer list to prevent unnecessary copies, moves and contructions

namespace myl {
    template<typename T, typename Allocator = std::allocator<T>>
    class ring_buffer {
        using altr = std::allocator_traits<>;
    public:
        using allocator_type         = Allocator;
        using value_type             = typename altr::value_type;
        using size_type              = usize;
        using difference_type        = typename altr::difference_type;
        using reference              = value_type&;
        using const_reference        = const value_type&;
        using pointer                = value_type*;
        using const_pointer          = const value_type*;
        using iterator               = circulator<ring_buffer>;
        using const_iterator         = const circulator<ring_buffer>;
        using reverse_iterator       = std::reverse_iterator<iterator>;
        using const_reverse_iterator = const std::reverse_iterator<iterator>;
    private:
        pointer m_begin  = nullptr;
        pointer m_end    = nullptr;
        pointer m_head   = nullptr;
        pointer m_tail   = nullptr;
        size_type m_size = 0; /// Needed?
    public:
        // Constructors, Destructor, Assignment

        MYL_NO_DISCARD constexpr ring_buffer() = default;
        
        //template<value_type... Args>
        //MYL_NO_DISCARD constexpr ring_buffer(Args&&... args);

        //MYL_NO_DISCARD constexpr explicit ring_buffer(size_type capacity) noexcept(noexcept(allocator_type()));

        //MYL_NO_DISCARD constexpr explicit ring_buffer(size_type count, const_reference value);

        //template<typename InputIt>
        //MYL_NO_DISCARD constexpr explicit ring_buffer(InputIt begin, InputIt end);

        //constexpr ~ring_buffer();

        // Iterators

        //MYL_NO_DISCARD constexpr auto begin() noexcept -> iterator;

        //MYL_NO_DISCARD constexpr auto begin() const noexcept -> const_iterator;

        //MYL_NO_DISCARD constexpr auto cbegin() const noexcept -> const_iterator;

        //MYL_NO_DISCARD constexpr auto end() noexcept -> iterator;

        //MYL_NO_DISCARD constexpr auto end() const noexcept -> const_iterator;

        //MYL_NO_DISCARD constexpr auto cend() const noexcept -> const_iterator;

        //MYL_NO_DISCARD constexpr auto rbegin() noexcept -> reverse_iterator;

        //MYL_NO_DISCARD constexpr auto rbegin() const noexcept -> const_reverse_iterator;

        //MYL_NO_DISCARD constexpr auto crbegin() const noexcept -> const_reverse_iterator;

        //MYL_NO_DISCARD constexpr auto rend() noexcept -> reverse_iterator;

        //MYL_NO_DISCARD constexpr auto rend() const noexcept -> const_reverse_iterator;

        //MYL_NO_DISCARD constexpr auto crend() const noexcept -> const_reverse_iterator;

        // Utilities

        //MYL_NO_DISCARD constexpr auto get_allocator() const -> allocator_type;

        MYL_NO_DISCARD constexpr auto data() const noexcept -> const_pointer {
            return m_begin;
        }

        MYL_NO_DISCARD constexpr auto data() noexcept -> pointer {
            return m_begin;
        }

        //MYL_NO_DISCARD constexpr auto max_size() noexcept -> size_type;

        //MYL_NO_DISCARD constexpr auto size() const noexcept -> size_type;

        MYL_NO_DISCARD constexpr auto capacity() const noexcept -> size_type {
            return static_cast<size_type>(m_end - m_begin);
        }

        MYL_NO_DISCARD constexpr auto offset() const noexcept -> size_type {
            return static_cast<size_type>(m_head - m_begin);
        }

        //MYL_NO_DISCARD constexpr auto linear() const noexcept -> bool;

        //MYL_NO_DISCARD constexpr auto empty() const noexcept -> bool;

        //MYL_NO_DISCARD constexpr auto full() const noexcept -> bool;

        // Access

        MYL_NO_DISCARD constexpr auto front() -> reference {
            MYL_ASSERT(m_head != nullptr);
            return *m_head;
        }

        MYL_NO_DISCARD constexpr auto front() const -> const_reference {
            MYL_ASSERT(m_head != nullptr);
            return *m_head;
        }

        MYL_NO_DISCARD constexpr auto back() -> reference {
            MYL_ASSERT(m_tail != nullptr);
            return *m_tail;
        }

        MYL_NO_DISCARD constexpr auto back() const -> const_reference {
            MYL_ASSERT(m_tail != nullptr);
            return *m_tail;
        }

        //MYL_NO_DISCARD constexpr auto at(size_type position) -> reference;

        //MYL_NO_DISCARD constexpr auto at(size_type position) const -> const_reference;

        //MYL_NO_DISCARD constexpr auto operator[](size_type index) -> reference;

        //MYL_NO_DISCARD constexpr auto operator[](size_type index) const -> const_reference;

        // Modifiers

        //constexpr auto clear() noexcept -> void;

        //constexpr auto fill(const_reference value) -> void;

        //constexpr auto fill_up(const_reference value) -> void;

        //template<typename InputIt>
        //constexpr auto assign(InputIt begin, InputIt end) -> void;

        //constexpr auto assign(size_type count, const_reference value) -> void;

        //template<value_type... Args>
        //constexpr auto assign(Args&&... args) -> void;

        //template<typename... Args>
        //constexpr auto emplace_back(Args&&... args) -> reference;

        //constexpr auto push_back(const_reference value) -> void;

        //constexpr auto push_back(value_type&& value) -> void;

        //constexpr auto pop_back() -> void;

        //constexpr auto pop_back(size_type count) -> void;

        //constexpr auto emplace_front(Args&&... args) -> reference;

        //constexpr auto push_front(const_reference value) -> void;

        //constexpr auto push_front(value_type&& value) -> void;

        //constexpr auto pop_front() -> void;

        //constexpr auto pop_front(size_type count) -> void;

        //constexpr auto resize(size_type size) -> void;

        //constexpr auto resize(size_type size, const_reference value) -> void;

        //constexpr auto reserve(size_type capacity) -> void;

        //constexpr auto shrink_to_fit() -> void;

        //constexpr auto rotate(pointer new_head) -> void;

        //constexpr auto rotate(difference_type offset) -> void;

        //constexpr auto align() -> void;
    };
}
