#pragma once
#include <myl/definitions.hpp>

#include <compare>
#include <memory>

/// MYTODO: myl::buffer
/// - Allocators

namespace myl {
    class buffer {
    public:
        using value_type = myl::u8;
        using size_type  = myl::usize;
        using pointer    = value_type*;
    private:
        pointer m_data = nullptr;
        size_type m_size = 0;
    public:
        MYL_NO_DISCARD constexpr buffer() noexcept = default;

        MYL_NO_DISCARD constexpr buffer(size_type bytes) {
            allocate(bytes);
        }

        constexpr ~buffer() {
            if (m_data)
                delete[] m_data;
        }

        MYL_NO_DISCARD constexpr auto data() noexcept -> pointer {
            return m_data;
        }

        MYL_NO_DISCARD constexpr auto data() const noexcept -> const pointer {
            return m_data;
        }

        template<typename As>
        MYL_NO_DISCARD constexpr auto as() noexcept -> As* {
            return reinterpret_cast<As*>(m_data);
        }

        MYL_NO_DISCARD constexpr auto size() const noexcept -> size_type {
            return m_size;
        }

        constexpr auto allocate(size_type bytes) -> void {
            MYL_ASSERT(m_data == nullptr, "Data has already been allocated");
            m_data = new value_type[bytes / sizeof(value_type)];
            m_size = bytes;
        }

        constexpr auto deallocate() -> void {
            MYL_ASSERT(m_data != nullptr, "Data is already deleted");
            delete[] m_data;
            m_size = 0;
            m_data = nullptr;
        }

        constexpr auto reallocate(size_type bytes) -> void {
            MYL_ASSERT(m_data != nullptr, "Data has not be allocated");
            if (m_size == bytes)
                return;

            delete[] m_data;
            m_data = new value_type[bytes / sizeof(value_type)];
            m_size = bytes;
        }

        MYL_NO_DISCARD constexpr auto operator[](size_type index) -> value_type& {
            MYL_ASSERT(index < m_size, "'index' is greater than the amount of bytes");
            return m_data[index];
        }

        MYL_NO_DISCARD constexpr auto operator[](size_type index) const -> const value_type& {
            MYL_ASSERT(index < m_size, "'index' is greater than the amount of bytes");
            return m_data[index];
        }
    };

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

        constexpr auto operator=(const pointer r) noexcept -> observer_ptr& {
            m_ptr = r;
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

        MYL_NO_DISCARD constexpr operator bool() const noexcept {
            return m_ptr != nullptr;
        }

        MYL_NO_DISCARD constexpr explicit operator pointer() const noexcept {
            return m_ptr;
        }
    };

    template<typename T>
    MYL_NO_DISCARD constexpr auto operator==(std::nullptr_t, const observer_ptr<T>& r) noexcept -> bool {
        return nullptr == r.operator->();
    }

    template<typename T, typename U>
    MYL_NO_DISCARD constexpr auto operator==(const observer_ptr<T>& l, const observer_ptr<U>& r) noexcept -> bool {
        return l.operator->() == r.operator->();
    }

    template<typename T, typename U>
    MYL_NO_DISCARD constexpr auto operator<=>(const observer_ptr<T>& l, const observer_ptr<U>& r) noexcept -> std::strong_ordering {
        return l.operator->() <=> r.operator->();
    }

    template<typename T, typename U>
    MYL_NO_DISCARD constexpr auto operator==(const observer_ptr<T>& l, std::nullptr_t) noexcept -> bool {
        return l.operator->() == nullptr;
    }

    template<typename T>
    MYL_NO_DISCARD constexpr auto operator<=>(const observer_ptr<T>& l, std::nullptr_t) noexcept -> std::strong_ordering {
        return l.operator->() <=> nullptr;
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
