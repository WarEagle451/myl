#pragma once
#include <myl/memory.hpp>

https://en.cppreference.com/w/cpp/named_req/Allocator
https://timsong-cpp.github.io/cppwp/n3337/allocator.requirements

https://en.cppreference.com/w/cpp/memory/allocator
/// Do I have to implement traits?

namespace myl {
    template<typename T>
    class tracking_allocator {
        & m_data;
    public:
        using value_type         = T;
        using size_type          = myl::usize;
        using difference_type    = ;

        MYL_NO_DISCARD constexpr tracking_allocator() noexcept;
        MYL_NO_DISCARD constexpr tracking_allocator(const tracking_allocator& other) noexcept;
        template<typename U> MYL_NO_DISCARD constexpr tracking_allocator(const tracking_allocator<U>& other) noexcept;

        constexpr tracking_allocator() = default;

        MYL_NO_DISCARD constexpr auto allocate(size_type n) -> pointer;
        MYL_NO_DISCARD constexpr auto allocate_at_least(size_type size_type n) -> std::allocation_result<pointer>;
        constexpr auto deallocate(pointer p, size_type n) -> void;
    };

    template<typename T, typename U>
    MYL_NO_DISCARD constexpr auto operator==(const tracking_allocator<T>& l, const tracking_allocator<T>& r) noexcept;
}
