#pragma once
#include <myl/definitions.hpp>

#include <compare>
#include <memory>

namespace myl {
    template<typename T>
    class observer_ptr {
    public:
        using pointer = T*;
        using element_type = T;
    private:
        pointer m_ptr = nullptr;
    public:
        MYL_NO_DISCARD constexpr observer_ptr() noexcept = default;

        MYL_NO_DISCARD constexpr observer_ptr(std::nullptr_t) noexcept
        : m_ptr{ nullptr } {}

        MYL_NO_DISCARD constexpr explicit observer_ptr(pointer ptr) noexcept
        : m_ptr{ ptr } {}

        MYL_NO_DISCARD constexpr observer_ptr(const observer_ptr& other) noexcept = default;

        MYL_NO_DISCARD constexpr observer_ptr(observer_ptr&& other) noexcept = default;

        constexpr ~observer_ptr() = default;

        constexpr auto reset(pointer ptr = nullptr) noexcept -> void {
            m_ptr = ptr;
        }

        constexpr auto release() noexcept -> pointer {
            pointer out = m_ptr;
            m_ptr = nullptr;
            return out;
        }

        MYL_NO_DISCARD constexpr auto get() const noexcept -> pointer {
            return m_ptr;
        }

        constexpr auto swap(observer_ptr& other) noexcept -> void {
            pointer temp = m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = temp;
        }

        MYL_NO_DISCARD constexpr auto operator*() const -> element_type& {
            return *m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator->() const noexcept -> pointer {
            return m_ptr;
        }

        constexpr auto operator=(std::nullptr_t) noexcept -> observer_ptr& {
            m_ptr = nullptr;
            return *this;
        }

        constexpr auto operator=(const observer_ptr& r) noexcept -> observer_ptr& {
            m_ptr = r.m_ptr;
            return *this;
        }

        constexpr auto operator=(observer_ptr&& r) noexcept -> observer_ptr& {
            m_ptr = r.m_ptr;
            r.m_ptr = nullptr;
            return *this;
        }

        MYL_NO_DISCARD constexpr explicit operator bool() const noexcept {
            return m_ptr != nullptr;
        }

        MYL_NO_DISCARD constexpr explicit operator pointer() const noexcept {
            return m_ptr;
        }
    };

    template<typename T, typename U>
    MYL_NO_DISCARD constexpr auto operator==(const observer_ptr<T>& l, const observer_ptr<U>& r) noexcept -> bool {
        return l.m_ptr == r.m_ptr;
    }

    template<typename T, typename U>
    MYL_NO_DISCARD constexpr auto operator<=>(const observer_ptr<T>& l, const observer_ptr<U>& r) noexcept -> std::strong_ordering {
        return l.m_ptr <=> r.m_ptr;
    }

    template<typename T, typename U>
    MYL_NO_DISCARD constexpr auto operator==(const observer_ptr<T>& l, std::nullptr_t) noexcept -> bool {
        return l.m_ptr == nullptr;
    }

    template<typename T, typename U>
    MYL_NO_DISCARD constexpr auto operator==(std::nullptr_t, const observer_ptr<U>& r) noexcept -> bool {
        return nullptr == r.m_ptr;
    }

    template<typename T, typename U>
    MYL_NO_DISCARD constexpr auto operator<=>(const observer_ptr<T>& l, std::nullptr_t) noexcept -> std::strong_ordering {
        return l.m_ptr <=> nullptr;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto make_observer(T* ptr) noexcept -> observer_ptr<T> {
        return observer_ptr(ptr);
    }

    template<typename T, typename D>
    MYL_NO_DISCARD constexpr auto make_observer(std::unique_ptr<T, D>& ptr) noexcept -> observer_ptr<T> {
        return observer_ptr(ptr.get());
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto make_observer(std::shared_ptr<T>& ptr) noexcept -> observer_ptr<T> {
        return observer_ptr(ptr.get());
    }
}

namespace std {
    template<typename T>
    constexpr auto swap(myl::observer_ptr<T>& l, myl::observer_ptr<T>& r) noexcept -> void {
        l.swap(r);
    }
}
