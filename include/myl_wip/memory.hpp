#pragma once
#include <myl/memory.hpp>

/// https://en.cppreference.com/w/cpp/named_req/Allocator
/// https://timsong-cpp.github.io/cppwp/n3337/allocator.requirements

/// https://en.cppreference.com/w/cpp/memory/allocator
/// Do I have to implement traits?

#include <limits>
#include <new>
#include <type_traits>

namespace myl {
    struct tracking_allocator_data {
        usize allocation_calls   = 0;
        usize deallocation_calls = 0;
        usize construct_calls    = 0;
        usize destroy_calls      = 0;
        usize bytes_deallocated  = 0;
        usize bytes_allocated    = 0;
    };

    template<typename T, bool ExternalDataStorage>
    class tracking_allocator {
        using storage_type = typename std::conditional<ExternalDataStorage, tracking_allocator_data&, tracking_allocator_data>::type;
        storage_type m_data;
    public:
        using value_type      = T;
        using size_type       = usize;
        using difference_type = std::ptrdiff_t;
        using pointer         = value_type*;
        using const_pointer   = const value_type*;

        using propagate_on_container_copy_assignment = std::true_type;
        using propagate_on_container_move_assignment = std::true_type;
        using propagate_on_container_swap            = std::true_type;
        using is_always_equal                        = std::false_type;

        MYL_NO_DISCARD constexpr tracking_allocator() noexcept = default; /// enable if ExternalDataStorage == false

        MYL_NO_DISCARD constexpr tracking_allocator(tracking_allocator_data& data) noexcept
            : m_data{ data } {}

        MYL_NO_DISCARD constexpr tracking_allocator(const tracking_allocator& other) noexcept
            : m_data{ other.m_data } {}

        ///template<typename U>
        ///MYL_NO_DISCARD constexpr tracking_allocator(const tracking_allocator<U>& other) noexcept
        ///    : m_data{ other.m_data } {}

        constexpr ~tracking_allocator() = default;

        MYL_NO_DISCARD constexpr auto allocate(size_type count) -> pointer {
            MYL_THROW_IF(std::numeric_limits<size_type>::max() / sizeof(value_type) < count, std::bad_array_new_length);
            const size_type bytes = sizeof(value_type) * count;
            pointer block = static_cast<pointer>(::operator new(bytes));

            m_data.bytes_allocated += bytes;
            ++m_data.allocation_calls;
            return block;
        }

        constexpr auto deallocate(pointer ptr, size_type count) noexcept -> void {
            if (count == 0)
                return;

            const size_type bytes = sizeof(value_type) * count;
            ::operator delete(ptr, bytes);

            m_data.bytes_deallocated += bytes;
            ++m_data.deallocation_calls;
        }

        template<typename... Args>
        constexpr auto construct(pointer ptr, Args&&... args) -> void {
            std::construct_at(ptr, std::forward<Args>(args)...);
            ++m_data.construct_calls;
        }

        constexpr auto destroy(pointer ptr) -> void {
            std::destroy_at(ptr);
            ++m_data.destroy_calls;
        }

        /// select_on_container_copy_construction

        MYL_NO_DISCARD constexpr auto data() const noexcept -> const tracking_allocator_data& {
            return m_data;
        }
    };

    template<typename T, bool TEDS, typename U, bool UEDS>
    MYL_NO_DISCARD constexpr auto operator==(const tracking_allocator<T, TEDS>& l, const tracking_allocator<U, UEDS>& r) noexcept -> bool {
        if constexpr (TEDS == UEDS && TEDS == true)
            return std::addressof(l.data()) == std::addressof(r.data());
        else
            return false;
    }

    template<typename T> using shared_tracking_allocator = tracking_allocator<T, true>;
    template<typename T> using unique_tracking_allocator = tracking_allocator<T, false>;
}
