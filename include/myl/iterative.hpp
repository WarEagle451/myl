#pragma once
#include <myl/definitions.hpp>

#include <iterator>
#include <utility>

/// MYTODO: Condense both iterator classes into one

namespace myl {
    template<typename T>
    class contiguous_const_iterator {
    public:
        using iterator_concept  = std::contiguous_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = const value_type*;
        using reference         = const value_type&;
    protected:
        pointer m_ptr = nullptr;
    public:
        // Constructors, Destructor, Assignment

        MYL_NO_DISCARD constexpr contiguous_const_iterator() noexcept = default;
        MYL_NO_DISCARD constexpr contiguous_const_iterator(const contiguous_const_iterator&) noexcept = default;
        MYL_NO_DISCARD constexpr contiguous_const_iterator(contiguous_const_iterator&&) noexcept = default;

        MYL_NO_DISCARD constexpr contiguous_const_iterator(pointer ptr) noexcept
            : m_ptr{ ptr } {}

        constexpr ~contiguous_const_iterator() = default;

        constexpr auto operator=(const contiguous_const_iterator& r) noexcept -> contiguous_const_iterator& {
            m_ptr = r.m_ptr;
        }

        constexpr auto operator=(contiguous_const_iterator&& r) noexcept -> contiguous_const_iterator& {
            m_ptr = std::move(r.m_ptr);
        }
        
        // Access

        MYL_NO_DISCARD constexpr auto operator*() const noexcept -> reference {
            MYL_ASSERT(m_ptr != nullptr, "Can't dereference an invalid iterator");
            return *m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator->() const noexcept -> pointer {
            return m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator[](const difference_type offset) const noexcept -> reference {
            return *(m_ptr + offset);
        }

        // Traversal

        constexpr auto operator++() noexcept -> contiguous_const_iterator& {
            ++m_ptr;
            return *this;
        }

        MYL_NO_DISCARD constexpr auto operator++(int) noexcept -> contiguous_const_iterator {
            contiguous_const_iterator temp{ *this };
            ++m_ptr;
            return temp;
        }

        constexpr auto operator--() noexcept -> contiguous_const_iterator& {
            --m_ptr;
            return *this;
        }

        MYL_NO_DISCARD constexpr auto operator--(int) noexcept -> contiguous_const_iterator {
            contiguous_const_iterator temp{ *this };
            --m_ptr;
            return temp;
        }

        MYL_NO_DISCARD constexpr auto operator+(const difference_type offset) const noexcept -> contiguous_const_iterator {
            return contiguous_const_iterator{ m_ptr + offset };
        }

        MYL_NO_DISCARD constexpr auto operator-(const difference_type offset) const noexcept -> contiguous_const_iterator {
            return contiguous_const_iterator{ m_ptr - offset };
        }

        MYL_NO_DISCARD constexpr auto operator-(const contiguous_const_iterator& r) const noexcept -> difference_type {
            return static_cast<difference_type>(m_ptr - r.m_ptr);
        }

        constexpr auto operator+=(const difference_type offset) noexcept -> contiguous_const_iterator& {
            m_ptr += offset;
            return *this;
        }

        constexpr auto operator-=(const difference_type offset) noexcept -> contiguous_const_iterator& {
            m_ptr -= offset;
            return *this;
        }

        // Comparison

        MYL_NO_DISCARD constexpr auto operator==(const contiguous_const_iterator& r) const noexcept -> bool {
            return m_ptr == r.m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator<=>(const contiguous_const_iterator& r) const noexcept {
            return m_ptr <=> r.m_ptr;
        }
    };

    template<typename T>
    class contiguous_iterator : public contiguous_const_iterator<T> {
        using base = contiguous_const_iterator<T>;
    public:
        using iterator_concept  = std::contiguous_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = value_type*;
        using reference         = value_type&;

        // Constructors, Destructor, Assignment

        using base::base; // Use contiguous_const_iterator's constructors

        MYL_NO_DISCARD constexpr contiguous_iterator(const base& b)
            : base{ b } {}

        // Access

        MYL_NO_DISCARD constexpr auto operator*() const noexcept -> reference {
            return const_cast<reference>(base::operator*());
        }

        MYL_NO_DISCARD constexpr auto operator->() const noexcept -> pointer {
            return const_cast<pointer>(base::operator->());
        }

        MYL_NO_DISCARD constexpr auto operator[](const difference_type offset) const noexcept -> reference {
            return const_cast<reference>(base::operator[](offset));
        }

        // Traversal

        constexpr auto operator++() noexcept -> contiguous_iterator& {
            base::operator++();
            return *this;
        }

        MYL_NO_DISCARD constexpr auto operator++(int) noexcept -> contiguous_iterator {
            contiguous_iterator temp = *this;
            base::operator++();
            return temp;
        }

        constexpr auto operator--() noexcept -> contiguous_iterator& {
            base::operator--();
            return *this;
        }

        MYL_NO_DISCARD constexpr auto operator--(int) noexcept -> contiguous_iterator {
            contiguous_iterator temp = *this;
            base::operator--();
            return temp;
        }

        MYL_NO_DISCARD constexpr auto operator+(const difference_type offset) const noexcept -> contiguous_iterator {
            contiguous_iterator temp = *this;
            temp += offset;
            return temp;
        }

        MYL_NO_DISCARD constexpr auto operator-(const difference_type offset) const noexcept -> contiguous_iterator {
            contiguous_iterator temp = *this;
            temp -= offset;
            return temp;
        }

        constexpr auto operator+=(const difference_type offset) noexcept -> contiguous_iterator& {
            base::operator+=(offset);
            return *this;
        }

        constexpr auto operator-=(const difference_type offset) noexcept -> contiguous_iterator& {
            base::operator-=(offset);
            return *this;
        }
    };
}
