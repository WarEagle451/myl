#pragma once
#include <myl/definitions.hpp>

#include <compare>
#include <memory>
#include <utility>

namespace myl {
    template<typename Block, typename Allocator = std::allocator<Block>>
    class basic_buffer {
        using altr = std::allocator_traits<Allocator>;
    public:
        using allocator_type  = typename altr::allocator_type;
        using value_type      = typename altr::value_type;
        using size_type       = typename altr::size_type;
        using pointer         = typename std::allocator_traits<allocator_type>::pointer;
        using const_pointer   = typename std::allocator_traits<allocator_type>::const_pointer;
    private:
        allocator_type m_allocator;
        pointer        m_data = nullptr;
        size_type      m_capacity = 0;
    public:
        // Constructors, Destructor, Assignment

        MYL_NO_DISCARD constexpr basic_buffer() noexcept(noexcept(allocator_type()))
            : m_allocator() {}

        MYL_NO_DISCARD constexpr basic_buffer(const allocator_type& allocator) noexcept
            : m_allocator{ allocator } {}

        MYL_NO_DISCARD constexpr basic_buffer(const basic_buffer& other) noexcept
            : m_allocator() {
            allocate(other.m_capacity);
            std::memcpy(m_data, other.m_data, other.m_capacity);
        }

        MYL_NO_DISCARD constexpr basic_buffer(basic_buffer&& other)
            : m_allocator{ std::move(other.m_allocator) }
            , m_data{ std::move(other.m_data) }
            , m_capacity{ std::move(other.m_capacity) } {}

        MYL_NO_DISCARD constexpr explicit basic_buffer(size_type bytes, const allocator_type& allocator = allocator_type())
            : m_allocator{ allocator } {
            allocate(bytes);
        }

        constexpr ~basic_buffer() {
            if (m_data)
                deallocate();
        }

        constexpr auto operator=(const basic_buffer& other) -> basic_buffer& {
            if (this == &other)
                return;

            if (m_data)
                deallocate();

            if constexpr (altr::propagate_on_container_copy_assignment::value)
                m_allocator = other.m_allocator;

            allocate(other.m_capacity);
            std::memcpy(m_data, other.m_data, other.m_capacity);
            return *this;
        }

        constexpr auto operator=(basic_buffer&& other) noexcept(altr::propagate_on_container_move_assignment::value || altr::is_always_equal::value) -> basic_buffer& {
            if (this == &other)
                return;
            
            if (m_data)
                deallocate();

            if constexpr (altr::propagate_on_container_move_assignment::value)
                m_allocator = other.m_allocator;

            m_data = std::move(other.m_data);
            m_capacity = std::move(other.m_capacity);
            return *this;
        }

        // Utility

        MYL_NO_DISCARD constexpr auto get_allocator() const noexcept {
            return m_allocator;
        }

        MYL_NO_DISCARD constexpr auto capacity() const noexcept -> size_type {
            return m_capacity;
        }

        MYL_NO_DISCARD constexpr auto bytes() const noexcept -> size_type {
            return m_capacity * sizeof(value_type);
        }

        MYL_NO_DISCARD constexpr auto operator[](size_type index) -> value_type& {
            MYL_ASSERT(index < m_capacity, "'index' is greater than capacity");
            return m_data[index];
        }

        MYL_NO_DISCARD constexpr auto operator[](size_type index) const -> const value_type& {
            MYL_ASSERT(index < m_capacity, "'index' is greater than capacity");
            return m_data[index];
        }

        MYL_NO_DISCARD constexpr auto data() noexcept -> pointer {
            return m_data;
        }

        MYL_NO_DISCARD constexpr auto data() const noexcept -> const_pointer {
            return m_data;
        }

        template<typename As>
        MYL_NO_DISCARD constexpr auto as() noexcept -> As* {
            return reinterpret_cast<As*>(m_data);
        }

        // Modifiers

        constexpr auto allocate(size_type count) -> void {
            MYL_ASSERT(m_data == nullptr, "Data has already been allocated");
            m_data = altr::allocate(m_allocator, count);
            m_capacity = count;
        }

        constexpr auto deallocate() -> void {
            MYL_ASSERT(m_data != nullptr, "Data is already deleted");
            altr::deallocate(m_allocator, m_data, m_capacity);
            m_capacity = 0;
            m_data = nullptr;
        }

        constexpr auto reallocate(size_type count) -> void {
            MYL_ASSERT(m_data != nullptr, "Data has not be allocated");
            if (m_capacity == count)
                return;

            altr::deallocate(m_allocator, m_data, m_capacity);
            m_data = altr::allocate(m_allocator, count);
            m_capacity = count;
        }

        constexpr auto set(const value_type& value, size_type offset) -> void {
            MYL_ASSERT(offset < m_capacity, "Setting data will overflow the buffer!");
            std::memset(m_data + offset, value, sizeof(value_type));
        }

        constexpr auto set(const void* data, size_type element_count, size_type element_offset) -> void {
            MYL_ASSERT(element_count + element_offset <= m_capacity, "Setting data will overflow the buffer!");
            if (data == nullptr || element_count == 0)
                return;

            std::memcpy(m_data + element_offset, data, static_cast<size_t>(element_count));
        }

        constexpr auto zero() -> void {
            if (m_capacity == 0)
                return;
            std::memset(m_data, 0, m_capacity);
        }

        constexpr auto swap(basic_buffer& other) noexcept(altr::propagate_on_container_swap::value || altr::is_always_equal::value) -> void {
            if (this == &other)
                return;

            if constexpr (altr::propagate_on_container_swap::value) {
                allocator_type t_allocator = std::move(m_allocator);
                m_allocator = std::move(other.m_allocator);
                other.m_allocator = std::move(t_allocator);
            }
            
            pointer t_data = m_data;
            size_type t_capacity = m_capacity;

            m_data = other.m_data;
            m_capacity = other.m_capacity;

            other.m_data = t_data;
            other.m_capacity = t_capacity;
        }
    };   

    using i8buffer  = basic_buffer<myl::i8>;
    using i16buffer = basic_buffer<myl::i16>;
    using i32buffer = basic_buffer<myl::i32>;
    using i64buffer = basic_buffer<myl::i64>;
    using u8buffer  = basic_buffer<myl::u8>;
    using u16buffer = basic_buffer<myl::u16>;
    using u32buffer = basic_buffer<myl::u32>;
    using u64buffer = basic_buffer<myl::u64>;

    using buffer = u8buffer;

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
    constexpr auto swap(myl::basic_buffer<T>& l, myl::basic_buffer<T>& r) noexcept(noexcept(l.swap(r))) -> void {
        l.swap(r);
    }

    template<typename T>
    constexpr auto swap(myl::observer_ptr<T>& l, myl::observer_ptr<T>& r) noexcept(noexcept(l.swap(r))) -> void {
        l.swap(r);
    }
}
