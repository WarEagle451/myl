#pragma once
#include <myl/definitions.hpp>

#include <limits>
#include <memory>
#include <stdexcept>
#include <utility>

// Use arg pack over initializer list to prevent unnecessary copies, moves and contructions

namespace myl {
    template<typename T, typename Allocator = std::allocator<T>>
    class ring_buffer {
        using altr = std::allocator_traits<Allocator>;
    public:
        using allocator_type         = Allocator;
        using value_type             = typename altr::value_type;
        using size_type              = usize;
        using difference_type        = typename altr::difference_type;
        using reference              = value_type&;
        using const_reference        = const value_type&;
        using pointer                = value_type*;
        using const_pointer          = const value_type*;
        ///using iterator               = circulator<ring_buffer>;
        ///using const_iterator         = const circulator<ring_buffer>;
        ///using reverse_iterator       = std::reverse_iterator<iterator>;
        ///using const_reverse_iterator = const std::reverse_iterator<iterator>;
    private:
        allocator_type m_allocator{};
        pointer m_begin  = nullptr;
        pointer m_end    = nullptr;
        pointer m_head   = nullptr;
        pointer m_tail   = nullptr;
        size_type m_size = 0;
    public:
        // Constructors, Destructor, Assignment

        MYL_NO_DISCARD constexpr ring_buffer() = default;
        
        //template<value_type... Elements>
        //MYL_NO_DISCARD constexpr ring_buffer(Elements&&... elements);

        MYL_NO_DISCARD constexpr explicit ring_buffer(size_type capacity) noexcept(noexcept(allocator_type())) {
            m_begin = altr::allocate(m_allocator, capacity);
            m_end = m_begin + capacity;
            m_head = m_begin;
            m_tail = m_head;
        }

        //MYL_NO_DISCARD constexpr explicit ring_buffer(size_type count, const_reference value);

        //template<typename InputIt>
        //MYL_NO_DISCARD constexpr explicit ring_buffer(InputIt begin, InputIt end);

        constexpr ~ring_buffer() {
            clear();
            altr::deallocate(m_allocator, m_begin, capacity());
        }

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

        MYL_NO_DISCARD constexpr auto get_allocator() const -> allocator_type {
            return m_allocator;
        }

        MYL_NO_DISCARD constexpr auto data() const noexcept -> const_pointer {
            return m_begin;
        }

        MYL_NO_DISCARD constexpr auto data() noexcept -> pointer {
            return m_begin;
        }

        MYL_NO_DISCARD constexpr auto max_size() noexcept -> difference_type {
            return std::numeric_limits<difference_type>::max();
        }

        MYL_NO_DISCARD constexpr auto size() const noexcept -> size_type {
            return m_size;
        }

        MYL_NO_DISCARD constexpr auto capacity() const noexcept -> size_type {
            return static_cast<size_type>(m_end - m_begin);
        }

        MYL_NO_DISCARD constexpr auto offset() const noexcept -> size_type {
            return static_cast<size_type>(m_head - m_begin);
        }

        MYL_NO_DISCARD constexpr auto linear() const noexcept -> bool {
            return m_head <= m_tail;
        }

        MYL_NO_DISCARD constexpr auto empty() const noexcept -> bool {
            return m_size == 0;
        }

        MYL_NO_DISCARD constexpr auto full() const noexcept -> bool {
            return m_size == capacity();
        }

        // Access

        MYL_NO_DISCARD constexpr auto front() -> reference {
            MYL_ASSERT(!empty(), "Dereferencing an element of a empty ring buffer is undefined behavior");
            return *m_head;
        }

        MYL_NO_DISCARD constexpr auto front() const -> const_reference {
            return front();
        }

        MYL_NO_DISCARD constexpr auto back() -> reference {
            MYL_ASSERT(!empty(), "Dereferencing an element of a empty ring buffer is undefined behavior");
            return *m_tail;
        }

        MYL_NO_DISCARD constexpr auto back() const -> const_reference {
            return back();
        }

        MYL_NO_DISCARD constexpr auto at(size_type position) -> reference {
            pointer ptr = m_begin + ((offset() + position) % capacity());
            MYL_THROW_IF(out_of_bounds(ptr), std::out_of_range, "Accessing an out of bounds element is undefined behavior");
            return *ptr;
        }

        MYL_NO_DISCARD constexpr auto at(size_type position) const -> const_reference {
            return at(position);
        }

        MYL_NO_DISCARD constexpr auto operator[](size_type index) -> reference {
            MYL_ASSERT(!out_of_bounds(m_begin + index), "Accessing an out of bounds element is undefined behavior");
            return m_begin[index];
        }

        MYL_NO_DISCARD constexpr auto operator[](size_type index) const -> const_reference {
            return (*this)[index];
        }

        // Modifiers

        constexpr auto clear() noexcept -> void {
            while (m_size != 0) { // Destroys elements tail to head
                altr::destroy(m_allocator, m_tail);
                decrement(m_tail);
                --m_size;
            }

            m_tail = m_head; // Loop sets m_tail to m_head decremented by 1
        }

        constexpr auto fill(const_reference value) -> void {
            clear();
            for (pointer ptr = m_begin; ptr != m_end; ++ptr)
                altr::construct(m_allocator, ptr, value);

            m_head = m_begin;
            m_tail = m_end - 1;
            m_size = capacity();
        }

        constexpr auto fill_up(const_reference value) -> void {
            pointer ptr = m_tail;
            increment(ptr);

            while (ptr != m_head) {
                altr::construct(m_allocator, ptr, value);
                increment(ptr);
            }

            decrement(ptr);
            m_tail = ptr;
            m_size = capacity();
        }

        //template<typename InputIt>
        //constexpr auto assign(InputIt begin, InputIt end) -> void;

        //constexpr auto assign(size_type count, const_reference value) -> void;

        //template<value_type... Elements>
        //constexpr auto assign(Elements&&... elements) -> void;

        template<typename... Args>
        constexpr auto emplace_back(Args&&... args) -> reference {
            pointer new_back = m_tail;
            if (m_size != 0)
                increment(new_back);

            if (m_size == capacity()) {
                altr::destroy(m_allocator, m_head);
                increment(m_head);
            }
            else
                ++m_size;

            altr::construct(m_allocator, new_back, std::forward<Args>(args)...);
            m_tail = new_back;
            return *m_tail;
        }

        constexpr auto push_back(const_reference value) -> void {
            emplace_back(value);
        }

        constexpr auto push_back(value_type&& value) -> void {
            emplace_back(std::move(value));
        }

        constexpr auto pop_back() -> void {
            MYL_ASSERT(!empty(), "Attempting to destroy an element of an empty ring buffer is undefined behavior");
            altr::destroy(m_allocator, m_tail);
            --m_size;
            if (m_size != 0)
                decrement(m_tail);
        }

        constexpr auto pop_back(size_type count) -> void { /// MYTODO: This could be improved
            MYL_ASSERT(count <= m_size, "Popping more elements than the ring buffer contains is undefined behavior");
            while (count != 0) {
                pop_back();
                --count;
            }
       }

        template<typename... Args>
        constexpr auto emplace_front(Args&&... args) -> reference {
            pointer new_front = m_head;
            if (m_size != 0)
                decrement(new_front);

            if (m_size == capacity()) {
                altr::destroy(m_allocator, m_tail);
                decrement(m_tail);
            }
            else
                ++m_size;

            altr::construct(m_allocator, new_front, std::forward<Args>(args)...);
            m_head = new_front;
            return *m_head;
        }

        constexpr auto push_front(const_reference value) -> void {
            emplace_front(value);
        }

        constexpr auto push_front(value_type&& value) -> void {
            emplace_front(std::move(value));
        }

        constexpr auto pop_front() -> void {
            MYL_ASSERT(!empty(), "Attempting to destroy an element of an empty ring buffer is undefined behavior");
            altr::destroy(m_allocator, m_head);
            --m_size;
            if (m_size != 0)
                increment(m_head);
        }

        constexpr auto pop_front(size_type count) -> void { /// MYTODO: This could be improved
            MYL_ASSERT(count <= m_size, "Popping more elements than the ring buffer contains is undefined behavior");
            while (count != 0) {
                pop_front();
                --count;
            }
        }

        constexpr auto resize(size_type new_size, const_reference value = value_type()) -> void {
            if (new_size < m_size)
                pop_back(m_size - new_size);
            else if (new_size > capacity()) {
                reallocate(new_size);
                fill_up();
            }
            else if (new_size > m_size)
                while (m_size != new_size) /// MYTODO: This could be improved
                    emplace_back(value);
        }

        constexpr auto reserve(size_type new_capacity) -> void {
            if (new_capacity > capacity())
                reallocate(new_capacity);
        }

        constexpr auto shrink_to_fit() -> void {
            if (capacity() > m_size)
                reallocate(m_size);
        }

        //constexpr auto rotate(pointer new_head) -> void;

        //constexpr auto rotate(difference_type offset) -> void;

        constexpr auto align() -> void {
            if (m_head == m_begin)
                return;

            if (m_size == 0) {
                m_head = m_begin;
                m_tail = m_begin;
                return;
            }

            size_type capacity = this->capacity();
            pointer new_begin = altr::allocate(m_allocator, capacity);

            const size_type head_to_end_count = static_cast<size_type>(m_end - m_head);
            std::memcpy(new_begin, m_head, sizeof(value_type) * head_to_end_count);
            std::memcpy(new_begin + head_to_end_count, m_begin, sizeof(value_type) * static_cast<size_type>(m_tail - m_begin));

            altr::deallocate(m_allocator, m_begin, capacity);
            m_begin = new_begin;
            m_end = new_begin + capacity;
            m_head = new_begin;
            m_tail = new_begin + m_size - 1; // This works because capacity = 0 was handled earlier
        }
    private:
        inline constexpr auto increment(pointer& ptr) const noexcept -> void {
            ptr == m_end - 1 ?
                ptr = m_begin : // Loop from the last to first element of the array
                ++ptr;
        }

        inline constexpr auto decrement(pointer& ptr) const noexcept -> void {
            ptr == m_begin ?
                ptr = m_end - 1 : // Loop from the first to last element of the array
                --ptr;
        }

        inline constexpr auto out_of_bounds(pointer ptr) const noexcept -> bool {
            /// MYTODO: figure out why this code was here
            /// m_begin > ptr || !(m_end > ptr) || (m_head > ptr && ptr > m_tail);
            return linear() ?
                m_head > ptr || ptr > m_tail : // Check before head or after tail
                m_head > ptr && ptr > m_tail; // Check before head and after tail
        }

        inline constexpr auto reallocate(size_type new_capacity) -> void {
            MYL_ASSERT(new_capacity != 0);
            pointer new_begin = altr::allocate(m_allocator, new_capacity);

            if (linear())
                std::memcpy(new_begin, m_head, sizeof(value_type) * m_size);
            else {
                const size_type head_to_end_count = static_cast<size_type>(m_end - m_head);
                std::memcpy(new_begin, m_head, sizeof(value_type) * head_to_end_count);
                std::memcpy(new_begin + head_to_end_count, m_begin, sizeof(value_type) * static_cast<size_type>(m_tail - m_begin));
            }

            altr::deallocate(m_allocator, m_begin, capacity());
            m_begin = new_begin;
            m_end = new_begin + new_capacity;
            m_head = new_begin;
            m_tail = new_begin + m_size - 1; // This works because new_capacity should not be 0
        }
    };
}
