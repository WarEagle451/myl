#pragma once
#include <myl/definitions.hpp>

#include <compare> /// MYTODO: WHY IS THIS HERE
#include <iterator>
#include <type_traits>
#include <utility>

/// DEFINE std::iterator_traits?

namespace myl {
    template<typename T, bool IsConst>
    class contiguous_iterator_base {
    public:
        using iterator_concept  = std::contiguous_iterator_tag;
        using iterator_category = std::contiguous_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = std::conditional_t<IsConst, const value_type*, value_type*>;
        using reference         = std::conditional_t<IsConst, const value_type*, value_type*>;
    private:
        value_type* m_ptr = nullptr;
    public:
        MYL_NO_DISCARD constexpr contiguous_iterator_base() noexcept = default;
        MYL_NO_DISCARD constexpr contiguous_iterator_base(const contiguous_iterator_base&) noexcept = default;
        MYL_NO_DISCARD constexpr contiguous_iterator_base(contiguous_iterator_base&&) noexcept = default;

        MYL_NO_DISCARD constexpr contiguous_iterator_base(const contiguous_iterator_base<T, IsConst>& other) noexcept
            : m_ptr{ other.m_ptr } {}

        MYL_NO_DISCARD constexpr contiguous_iterator_base(pointer ptr)
            : m_ptr{ ptr } {}

        constexpr ~contiguous_iterator_base() = default;

        constexpr auto operator=(const contiguous_iterator_base& r) noexcept -> contiguous_iterator_base& {
            m_ptr = r.m_ptr;
        }

        constexpr auto operator=(contiguous_iterator_base&& r) noexcept -> contiguous_iterator_base& {
            m_ptr = std::move(r.m_ptr);
        }

        MYL_NO_DISCARD constexpr auto operator*() const -> reference {
            MYL_ASSERT(m_ptr != nullptr, "Can't dereference an invalid iterator");
            return *m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator->() -> pointer {
            return m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator[](const difference_type offset) -> reference {
            return *(m_ptr + offset);
        }

        constexpr auto operator++() -> contiguous_iterator_base& {
            ++m_ptr;
            return *this;
        }

        MYL_NO_DISCARD constexpr auto operator++(int) -> contiguous_iterator_base {
            contiguous_iterator_base temp{ *this };
            ++m_ptr;
            return temp;
        }

        constexpr auto operator--() -> contiguous_iterator_base& {
            --m_ptr;
            return *this;
        }

        MYL_NO_DISCARD constexpr auto operator--(int) -> contiguous_iterator_base {
            contiguous_iterator_base temp{ *this };
            --m_ptr;
            return temp;
        }

        friend MYL_NO_DISCARD constexpr auto operator+(difference_type offset, contiguous_iterator_base it) -> contiguous_iterator_base;

        MYL_NO_DISCARD constexpr auto operator+(const difference_type offset) const -> contiguous_iterator_base {
            return contiguous_iterator_base{ m_ptr + offset };
        }

        MYL_NO_DISCARD constexpr auto operator-(const difference_type offset) const -> contiguous_iterator_base {
            return contiguous_iterator_base{ m_ptr - offset };
        }

        MYL_NO_DISCARD constexpr auto operator-(const contiguous_iterator_base& r) const -> difference_type {
            return static_cast<difference_type>(m_ptr - r.m_ptr);
        }

        MYL_NO_DISCARD constexpr auto operator-(const contiguous_iterator_base<T, !IsConst>& r) const -> difference_type {
            return static_cast<difference_type>(m_ptr - r.m_ptr);
        }

        constexpr auto operator+=(const difference_type offset) -> contiguous_iterator_base& {
            m_ptr += offset;
            return *this;
        }

        constexpr auto operator-=(const difference_type offset) -> contiguous_iterator_base& {
            m_ptr -= offset;
            return *this;
        }

        MYL_NO_DISCARD constexpr auto operator==(const contiguous_iterator_base& r) const -> difference_type {
            return m_ptr == r.m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator==(const contiguous_iterator_base<T, !IsConst>& r) const -> difference_type {
            return m_ptr == r.m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator<=>(const contiguous_iterator_base& r) const -> difference_type {
            return m_ptr <=> r.m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator<=>(const contiguous_iterator_base<T, !IsConst>& r) const -> difference_type {
            return m_ptr <=> r.m_ptr;
        }

        friend constexpr auto std::swap(contiguous_iterator_base& l, contiguous_iterator_base& r) noexcept -> void;
    };

    template<typename T, bool IsConst>
    MYL_NO_DISCARD constexpr auto operator+(typename contiguous_iterator_base<T, IsConst>::difference_type offset, contiguous_iterator_base<T, IsConst> it) -> contiguous_iterator_base<T, IsConst> {
        return contiguous_iterator_base<T, IsConst>{ it.m_ptr + offset };
    }
    
    template<typename T> using contiguous_const_iterator = contiguous_iterator_base<T, true>;
    template<typename T> using contiguous_iterator       = contiguous_iterator_base<T, false>;
}

namespace std {
    template<typename T, bool IsConst>
    constexpr auto swap(contiguous_iterator_base<T, IsConst>& l, contiguous_iterator_base<T, IsConst>& r) noexcept -> void {
        auto temp_ptr = l.m_ptr;
        l.m_ptr = r.m_ptr;
        r.m_ptr = temp_ptr;
    }
}

///namespace myl {
    ///template<typename Container>
    ///class contiguous_const_iterator {
    ///    friend Container;
    ///public:
    ///    using iterator_concept  = std::contiguous_iterator_tag;
    ///    using iterator_category = std::random_access_iterator_tag;
    ///    using difference_type   = typename Container::difference_type;
    ///    using value_type        = typename Container::value_type;
    ///    using pointer           = const value_type*;
    ///    using reference         = const value_type&;
    ///protected:
    ///    typename Container::pointer m_ptr = nullptr;
    ///public:
    ///    MYL_NO_DISCARD constexpr contiguous_const_iterator() noexcept = default;
    ///    MYL_NO_DISCARD constexpr contiguous_const_iterator(const contiguous_const_iterator&) noexcept = default;
    ///    MYL_NO_DISCARD constexpr contiguous_const_iterator(contiguous_const_iterator&&) noexcept = default;
    ///
    ///    MYL_NO_DISCARD constexpr contiguous_const_iterator(typename Container::pointer p) noexcept
    ///        : m_ptr{ p } {}
    ///
    ///    constexpr ~contiguous_const_iterator() = default;
    ///
    ///    MYL_NO_DISCARD constexpr auto operator*() const noexcept -> reference {
    ///        MYL_ASSERT(m_ptr != nullptr, "Can't dereference an invalidated iterator");
    ///        return *m_ptr;
    ///    }
    ///
    ///    MYL_NO_DISCARD constexpr auto operator->() const noexcept -> pointer {
    ///        return m_ptr;
    ///    }
    ///
    ///    MYL_NO_DISCARD constexpr auto operator[](const difference_type offset) const noexcept -> reference {
    ///        return *(m_ptr + offset);
    ///    }
    ///
    ///    constexpr auto operator++() noexcept -> contiguous_const_iterator& {
    ///        ++m_ptr;
    ///        return *this;
    ///    }
    ///
    ///    constexpr auto operator--() noexcept -> contiguous_const_iterator& {
    ///        --m_ptr;
    ///        return *this;
    ///    }
    ///
    ///    MYL_NO_DISCARD constexpr auto operator++(int) noexcept -> contiguous_const_iterator {
    ///        contiguous_const_iterator temp = *this;
    ///        ++m_ptr;
    ///        return temp;
    ///    }
    ///
    ///    MYL_NO_DISCARD constexpr auto operator--(int) noexcept -> contiguous_const_iterator {
    ///        contiguous_const_iterator temp = *this;
    ///        --m_ptr;
    ///        return temp;
    ///    }
    ///
    ///    constexpr auto operator+=(const difference_type offset) noexcept -> contiguous_const_iterator& {
    ///        m_ptr += offset;
    ///        return *this;
    ///    }
    ///
    ///    constexpr auto operator-=(const difference_type offset) noexcept -> contiguous_const_iterator& {
    ///        m_ptr -= offset;
    ///        return *this;
    ///    }
    ///    
    ///    MYL_NO_DISCARD constexpr auto operator+(const difference_type offset) const noexcept -> contiguous_const_iterator {
    ///        return contiguous_const_iterator(m_ptr + offset);
    ///    }
    ///
    ///    MYL_NO_DISCARD constexpr auto operator-(const difference_type offset) const noexcept -> contiguous_const_iterator {
    ///        return contiguous_const_iterator(m_ptr - offset);
    ///    }
    ///
    ///    MYL_NO_DISCARD constexpr auto operator-(const contiguous_const_iterator& r) const noexcept -> difference_type {
    ///        return m_ptr - r.m_ptr;
    ///    }
    ///
    ///    MYL_NO_DISCARD constexpr auto operator==(const contiguous_const_iterator& r) const noexcept -> bool {
    ///        return m_ptr == r.m_ptr;
    ///    }
    ///
    ///    MYL_NO_DISCARD constexpr auto operator<=>(const contiguous_const_iterator& r) const noexcept {
    ///        return m_ptr <=> r.m_ptr;
    ///    }
    ///};
    ///
    ///template<typename Container>
    ///class contiguous_iterator : public contiguous_const_iterator<Container> {
    ///    friend Container;
    ///    using base = contiguous_const_iterator<Container>;
    ///public:
    ///    using iterator_concept  = std::contiguous_iterator_tag;
    ///    using iterator_category = std::random_access_iterator_tag;
    ///    using difference_type   = typename Container::difference_type;
    ///    using value_type        = typename Container::value_type;
    ///    using pointer           = value_type*;
    ///    using reference         = value_type&;
    ///
    ///    using base::base; // Use base's constructors
    ///
    ///    MYL_NO_DISCARD constexpr contiguous_iterator(const base& b)
    ///        : base{ b } {}
    ///
    ///    MYL_NO_DISCARD constexpr auto operator*() const noexcept -> reference {
    ///        return const_cast<reference>(base::operator*());
    ///    }
    ///
    ///    MYL_NO_DISCARD constexpr auto operator->() const noexcept -> pointer {
    ///        return const_cast<pointer>(base::operator->());
    ///    }
    ///
    ///    MYL_NO_DISCARD constexpr auto operator[](const difference_type offset) const noexcept -> reference {
    ///        return const_cast<reference>(base::operator[](offset));
    ///    }
    ///
    ///    constexpr auto operator++() noexcept -> contiguous_iterator& {
    ///        base::operator++();
    ///        return *this;
    ///    }
    ///
    ///    constexpr auto operator--() noexcept -> contiguous_iterator& {
    ///        base::operator--();
    ///        return *this;
    ///    }
    ///
    ///    MYL_NO_DISCARD constexpr auto operator++(int) noexcept -> contiguous_iterator {
    ///        contiguous_iterator temp = *this;
    ///        base::operator++();
    ///        return temp;
    ///    }
    ///
    ///    MYL_NO_DISCARD constexpr auto operator--(int) noexcept -> contiguous_iterator {
    ///        contiguous_iterator temp = *this;
    ///        base::operator--();
    ///        return temp;
    ///    }
    ///
    ///    constexpr auto operator+=(const difference_type offset) noexcept -> contiguous_iterator& {
    ///        base::operator+=(offset);
    ///        return *this;
    ///    }
    ///
    ///    constexpr auto operator-=(const difference_type offset) noexcept -> contiguous_iterator& {
    ///        base::operator-=(offset);
    ///        return *this;
    ///    }
    ///
    ///    MYL_NO_DISCARD constexpr auto operator+(const difference_type offset) const noexcept -> contiguous_iterator {
    ///        contiguous_iterator temp = *this;
    ///        temp += offset;
    ///        return temp;
    ///    }
    ///
    ///    MYL_NO_DISCARD constexpr auto operator-(const difference_type offset) const noexcept -> contiguous_iterator {
    ///        contiguous_iterator temp = *this;
    ///        temp -= offset;
    ///        return temp;
    ///    }
    ///};
///}
