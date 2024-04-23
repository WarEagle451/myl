#pragma once
#include <myl/definitions.hpp>

#include <compare>
#include <iterator>

namespace myl {
    template<typename Container>
    class contiguous_const_iterator {
        friend Container;
    public:
        using iterator_concept  = std::contiguous_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = typename Container::difference_type;
        using value_type        = typename Container::value_type;
        using pointer           = const value_type*;
        using reference         = const value_type&;
    protected:
        typename Container::pointer m_ptr = nullptr;
    public:
        MYL_NO_DISCARD constexpr contiguous_const_iterator() noexcept = default;
        MYL_NO_DISCARD constexpr contiguous_const_iterator(const contiguous_const_iterator&) noexcept = default;
        MYL_NO_DISCARD constexpr contiguous_const_iterator(contiguous_const_iterator&&) noexcept = default;

        MYL_NO_DISCARD constexpr contiguous_const_iterator(typename Container::pointer p) noexcept
            : m_ptr{ p } {}

        constexpr ~contiguous_const_iterator() = default;

        MYL_NO_DISCARD constexpr auto operator*() const noexcept -> reference {
            MYL_ASSERT(m_ptr != nullptr, "Can't dereference an invalidated iterator");
            return *m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator->() const noexcept -> pointer {
            return m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator[](const difference_type offset) const noexcept -> reference {
            return *(m_ptr + offset);
        }

        constexpr auto operator++() noexcept -> contiguous_const_iterator& {
            ++m_ptr;
            return *this;
        }

        constexpr auto operator--() noexcept -> contiguous_const_iterator& {
            --m_ptr;
            return *this;
        }

        MYL_NO_DISCARD constexpr auto operator++(int) noexcept -> contiguous_const_iterator {
            contiguous_const_iterator temp = *this;
            ++m_ptr;
            return temp;
        }

        MYL_NO_DISCARD constexpr auto operator--(int) noexcept -> contiguous_const_iterator {
            contiguous_const_iterator temp = *this;
            --m_ptr;
            return temp;
        }

        constexpr auto operator+=(const difference_type offset) noexcept -> contiguous_const_iterator& {
            m_ptr += offset;
            return *this;
        }

        constexpr auto operator-=(const difference_type offset) noexcept -> contiguous_const_iterator& {
            m_ptr -= offset;
            return *this;
        }
        
        MYL_NO_DISCARD constexpr auto operator+(const difference_type offset) const noexcept -> contiguous_const_iterator {
            return contiguous_const_iterator(m_ptr + offset);
        }

        MYL_NO_DISCARD constexpr auto operator-(const difference_type offset) const noexcept -> contiguous_const_iterator {
            return contiguous_const_iterator(m_ptr - offset);
        }

        MYL_NO_DISCARD constexpr auto operator-(const contiguous_const_iterator& r) const noexcept -> difference_type {
            return m_ptr - r.m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator==(const contiguous_const_iterator& r) const noexcept -> bool {
            return m_ptr == r.m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator<=>(const contiguous_const_iterator& r) const noexcept {
            return m_ptr <=> r.m_ptr;
        }
    };
    
    template<typename Container>
    class contiguous_iterator : public contiguous_const_iterator<Container> {
        friend Container;
        using base = contiguous_const_iterator<Container>;
    public:
        using iterator_concept  = std::contiguous_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = typename Container::difference_type;
        using value_type        = typename Container::value_type;
        using pointer           = value_type*;
        using reference         = value_type&;

        using base::base; // Use base's constructors

        MYL_NO_DISCARD constexpr contiguous_iterator(const base& b)
            : base{ b } {}

        MYL_NO_DISCARD constexpr auto operator*() const noexcept -> reference {
            return const_cast<reference>(base::operator*());
        }

        MYL_NO_DISCARD constexpr auto operator->() const noexcept -> pointer {
            return const_cast<pointer>(base::operator->());
        }

        MYL_NO_DISCARD constexpr auto operator[](const difference_type offset) const noexcept -> reference {
            return const_cast<reference>(base::operator[](offset));
        }

        constexpr auto operator++() noexcept -> contiguous_iterator& {
            base::operator++();
            return *this;
        }

        constexpr auto operator--() noexcept -> contiguous_iterator& {
            base::operator--();
            return *this;
        }

        MYL_NO_DISCARD constexpr auto operator++(int) noexcept -> contiguous_iterator {
            contiguous_iterator temp = *this;
            base::operator++();
            return temp;
        }

        MYL_NO_DISCARD constexpr auto operator--(int) noexcept -> contiguous_iterator {
            contiguous_iterator temp = *this;
            base::operator--();
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
    };
}
