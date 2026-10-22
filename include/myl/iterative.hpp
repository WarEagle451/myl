#pragma once
#include <myl/definitions.hpp>

#include <iterator>
#include <utility>

namespace myl {
    template<typename T, bool IsConst>
    class contiguous_iterator {
    public:
        using iterator_concept  = std::contiguous_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = std::conditional_t<IsConst, const value_type*, value_type*>;
        using reference         = std::conditional_t<IsConst, const value_type&, value_type&>;
    private:
        pointer m_ptr = nullptr;
    public:
        // Constructors, Destructor, Assignment

        MYL_NO_DISCARD constexpr contiguous_iterator() noexcept = default;
        MYL_NO_DISCARD constexpr contiguous_iterator(const contiguous_iterator&) noexcept = default;
        MYL_NO_DISCARD constexpr contiguous_iterator(contiguous_iterator&&) noexcept = default;

        MYL_NO_DISCARD constexpr contiguous_iterator(const contiguous_iterator<value_type, false>& it) noexcept requires IsConst
            : m_ptr{ it.m_ptr } {}

        MYL_NO_DISCARD constexpr contiguous_iterator(contiguous_iterator<value_type, false>&& it) noexcept requires IsConst
            : m_ptr{ std::move(it.m_ptr) } {}

        MYL_NO_DISCARD constexpr contiguous_iterator(pointer ptr) noexcept
            : m_ptr{ ptr } {}

        constexpr ~contiguous_iterator() = default;

        constexpr auto operator=(const contiguous_iterator& r) noexcept -> contiguous_iterator& {
            m_ptr = r.m_ptr;
            return *this;
        }

        constexpr auto operator=(contiguous_iterator&& r) noexcept -> contiguous_iterator& {
            m_ptr = std::move(r.m_ptr);
            return *this;
        }

        constexpr auto operator=(const contiguous_iterator<value_type, false>& r) noexcept -> contiguous_iterator& requires IsConst {
            m_ptr = r.m_ptr;
            return *this;
        }

        constexpr auto operator=(contiguous_iterator<value_type, false>&& r) noexcept -> contiguous_iterator& requires IsConst {
            m_ptr = std::move(r.m_ptr);
            return *this;
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

        constexpr auto operator++() noexcept -> contiguous_iterator& {
            ++m_ptr;
            return *this;
        }

        MYL_NO_DISCARD constexpr auto operator++(int) noexcept -> contiguous_iterator {
            contiguous_iterator temp{ *this };
            ++m_ptr;
            return temp;
        }

        constexpr auto operator--() noexcept -> contiguous_iterator& {
            --m_ptr;
            return *this;
        }

        MYL_NO_DISCARD constexpr auto operator--(int) noexcept -> contiguous_iterator {
            contiguous_iterator temp{ *this };
            --m_ptr;
            return temp;
        }

        MYL_NO_DISCARD constexpr auto operator+(const difference_type offset) const noexcept -> contiguous_iterator {
            return contiguous_iterator{ m_ptr + offset };
        }

        MYL_NO_DISCARD constexpr auto operator-(const difference_type offset) const noexcept -> contiguous_iterator {
            return contiguous_iterator{ m_ptr - offset };
        }

        MYL_NO_DISCARD constexpr auto operator-(const contiguous_iterator& r) const noexcept -> difference_type {
            return static_cast<difference_type>(m_ptr - r.m_ptr);
        }

        constexpr auto operator+=(const difference_type offset) noexcept -> contiguous_iterator& {
            m_ptr += offset;
            return *this;
        }

        constexpr auto operator-=(const difference_type offset) noexcept -> contiguous_iterator& {
            m_ptr -= offset;
            return *this;
        }

        // Comparison

        MYL_NO_DISCARD constexpr auto operator==(const contiguous_iterator& r) const noexcept -> bool {
            return m_ptr == r.m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator==(const contiguous_iterator<value_type, !IsConst>& r) const noexcept -> bool {
            return m_ptr == r.m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator<=>(const contiguous_iterator& r) const noexcept {
            return m_ptr <=> r.m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator<=>(const contiguous_iterator<value_type, !IsConst>& r) const noexcept {
            return m_ptr <=> r.m_ptr;
        }
    };
}
