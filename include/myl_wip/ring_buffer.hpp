#pragma once
#include <myl/definitions.hpp>

#include <algorithm>
#include <limits>
#include <memory>
#include <stdexcept>
#include <utility>

namespace myl {
    template<typename Container> /// MYTODO: Make all this bs internal, also redo and do proper, ptr and has looped = true
    class circulator {
    public:
        using iterator_concept  = std::random_access_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = typename Container::value_type;
        using difference_type   = typename Container::difference_type;
        using pointer           = value_type*;
        using reference         = value_type&;
    private:
        const Container* m_container; /// MYTODO: remove this
        pointer m_ptr          = nullptr;
        bool m_has_looped      = false; /// THIS IN CONSTUUCTOR SHOULD HAVE A DEFAULT
    public:
        MYL_NO_DISCARD constexpr circulator() noexcept = default;

        MYL_NO_DISCARD constexpr circulator(pointer ptr, const Container* container, bool has_looped) /// MYTODO: Remove Container
            : m_container{ container }
            , m_ptr{ ptr }
            , m_has_looped{ has_looped } {}

        constexpr ~circulator() noexcept = default;

        MYL_NO_DISCARD constexpr auto operator*() -> reference {
            return *m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator*() const -> reference {
            return *m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator->() -> pointer {
            return m_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator->() const -> pointer {
            return m_ptr;
        }

        constexpr auto operator++() noexcept -> circulator& {
            m_container->increment_circulator(m_ptr, m_has_looped);
            return *this;
        }

        MYL_NO_DISCARD constexpr auto operator++(int) noexcept -> circulator& {
            circulator temp(*this);
            m_container->increment_circulator(m_ptr, m_has_looped);
            return temp;
        }

        constexpr auto operator--() noexcept -> circulator& {
            m_container->decrement_circulator(m_ptr, m_has_looped);
            return *this;
        }

        MYL_NO_DISCARD constexpr auto operator--(int) noexcept -> circulator& {
            circulator temp(*this);
            m_container->decrement_circulator(m_ptr, m_has_looped);
            return temp;
        }

        MYL_NO_DISCARD constexpr auto operator==(const circulator& r) const -> bool {
            return
                m_ptr == r.m_ptr &&
                m_container == r.m_container &&
                m_has_looped == r.m_has_looped;
        }
    };
}

/// MYTODO:
/// MYL_NO_DISCARD constexpr emplace() -> reference;
/// - expand_back(), expand_front(), works like push/emplace front but if the conatiner is full it expands it
/// - insert
/// - erase
/// std::swap
/// std::erase
/// std::erase_if
/// <=>

/// MYTODO: std::initializer_list<value_tyle> list vs template<value_type... Elements>

namespace myl {
    template<typename T, typename Allocator = std::allocator<T>>
    class ring_buffer {
        using altr = std::allocator_traits<Allocator>;
    public:
        using allocator_type         = Allocator;
        using value_type             = typename altr::value_type;
        using size_type              = typename altr::size_type;
        using difference_type        = typename altr::difference_type;
        using reference              = value_type&;
        using const_reference        = const value_type&;
        using pointer                = value_type*;
        using const_pointer          = const value_type*;
        using iterator               = circulator<ring_buffer>;
        using const_iterator         = const circulator<ring_buffer>;
        using reverse_iterator       = std::reverse_iterator<iterator>;
        using const_reverse_iterator = const std::reverse_iterator<iterator>;
    private:
        friend iterator;

        std::conditional_t<std::is_empty_v<allocator_type>, MYL_NO_UNIQUE_ADDRESS allocator_type, allocator_type> m_allocator{};
        pointer m_begin  = nullptr;
        pointer m_end    = nullptr;
        pointer m_head   = nullptr;
        pointer m_tail   = nullptr;
        size_type m_size = 0;
    public:
        // Constructors, Destructor, Assignment

        MYL_NO_DISCARD constexpr ring_buffer() = default;

        ///MYL_NO_DISCARD constexpr ring_buffer(const ring_buffer& other); // Allocator propagation

        ///MYL_NO_DISCARD constexpr ring_buffer(const ring_buffer&, const allocator_type& allocator);

        ///MYL_NO_DISCARD constexpr ring_buffer(ring_buffer&& other);

        ///MYL_NO_DISCARD constexpr ring_buffer(ring_buffer&&, const allocator_type& allocator);

        MYL_NO_DISCARD constexpr explicit ring_buffer(const allocator_type& allocator) noexcept
            : m_allocator{ allocator } {}
        
        ///template<value_type... Elements>
        ///MYL_NO_DISCARD constexpr ring_buffer(Elements&&... elements); /// const allocator_type& allocator??

        /// MYTEMP: ITS THIS CONSTRUCTOR OR THE ELEMENT ONE
        MYL_NO_DISCARD constexpr ring_buffer(std::initializer_list<value_type> list, const allocator_type& allocator = allocator_type())
            : m_allocator{ allocator } {
            const size_type size = list.size();
            m_begin = altr::allocate(m_allocator, size);
            std::uninitialized_move(list.begin(), list.end(), m_begin); /// MYTODO: Should this be a copy???

            m_end = m_begin + size;
            m_head = m_begin;
            m_tail = size == 0 ? m_begin : m_begin + size - 1;
            m_size = size;
        }

        MYL_NO_DISCARD constexpr explicit ring_buffer(size_type capacity, const allocator_type& allocator = allocator_type())
            : m_allocator{ allocator } {
            m_begin = altr::allocate(m_allocator, capacity);
            m_end = m_begin + capacity;
            m_head = m_begin;
            m_tail = m_head;
        }

        ///MYL_NO_DISCARD constexpr explicit ring_buffer(size_type count, const_reference value, const allocator_type& allocator = allocator_type());

        ///template<typename InputIt>
        ///MYL_NO_DISCARD constexpr explicit ring_buffer(InputIt begin, InputIt end, const allocator_type& allocator = allocator_type());

        constexpr ~ring_buffer() {
            clear();
            altr::deallocate(m_allocator, m_begin, capacity());
        }

        constexpr auto operator=(const ring_buffer& other) -> ring_buffer& {
            if (this == &other)
                return *this;

            clear();
            if constexpr (altr::propagate_on_container_copy_assignment::value) {
                if constexpr (!altr::is_always_equal::value) {
                    altr::deallocate(m_allocator, m_begin, capacity());
                    m_begin = nullptr;
                    m_end = nullptr;
                    m_head = nullptr;
                    m_tail = nullptr;
                    m_size = 0;
                }

                m_allocator = other.m_allocator;
            }

            reserve(other.m_size);
            if (linear())
                std::copy(other.m_head, other.m_tail + 1, m_begin);
            else {
                pointer next = std::copy(other.m_head, other.m_end, m_begin);
                std::copy(other.m_begin, other.m_tail + 1, next);
            }

            m_size = other.m_size;
            return *this;
        }

        constexpr auto operator=(ring_buffer&& other) noexcept(altr::propagate_on_container_move_assignment::value || altr::is_always_equal::value) -> ring_buffer& {
            if (this == &other)
                return *this;

            clear();
            if constexpr (altr::propagate_on_container_move_assignment::value) {
                altr::deallocate(m_allocator, m_begin, capacity());
                m_allocator = std::move(other.m_allocator);
            }
            else if constexpr (!altr::is_always_equal::value) {
                reserve(other.m_size);
                if (linear())
                    std::copy(other.m_head, other.m_tail + 1, m_begin);
                else {
                    pointer next = std::copy(other.m_head, other.m_end, m_begin);
                    std::copy(other.m_begin, other.m_tail + 1, next);
                }

                return *this;
            }
            else
                altr::deallocate(m_allocator, m_begin, capacity());

            m_begin = other.m_begin;
            m_end = other.m_end;
            m_head = other.m_head;
            m_tail = other.m_tail;
            m_size = other.m_size;

            other.m_begin = nullptr;
            other.m_end = nullptr;
            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = 0;

            return *this;
        }

        ///constexpr auto operator=(std::initializer_list<value_tyle> list) -> ring_buffer&;

        // Iterators

        MYL_NO_DISCARD constexpr auto begin() noexcept -> iterator {
            return iterator(m_head, this, empty());
        }

        MYL_NO_DISCARD constexpr auto begin() const noexcept -> const_iterator {
            return iterator(m_head, this, empty());
        }

        MYL_NO_DISCARD constexpr auto cbegin() const noexcept -> const_iterator {
            return begin();
        }

        MYL_NO_DISCARD constexpr auto end() noexcept -> iterator {
            return iterator(m_tail + 1, this, true);
        }

        MYL_NO_DISCARD constexpr auto end() const noexcept -> const_iterator {
            return iterator(m_tail + 1, this, true);
        }

        MYL_NO_DISCARD constexpr auto cend() const noexcept -> const_iterator {
            return end();
        }

        MYL_NO_DISCARD constexpr auto rbegin() noexcept -> reverse_iterator {
            return reverse_iterator(iterator(m_tail + 1, this, empty()));
        }

        MYL_NO_DISCARD constexpr auto rbegin() const noexcept -> const_reverse_iterator {
            return reverse_iterator(iterator(m_tail + 1, this, empty()));
        }

        MYL_NO_DISCARD constexpr auto crbegin() const noexcept -> const_reverse_iterator {
            return rbegin();
        }

        MYL_NO_DISCARD constexpr auto rend() noexcept -> reverse_iterator {
            return reverse_iterator(iterator(m_head, this, true));
        }

        MYL_NO_DISCARD constexpr auto rend() const noexcept -> const_reverse_iterator {
            return reverse_iterator(iterator(m_head, this, true));
        }

        MYL_NO_DISCARD constexpr auto crend() const noexcept -> const_reverse_iterator {
            return rend();
        }

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
            pointer ptr = m_begin + ((offset() + index) % capacity());
            MYL_ASSERT(!out_of_bounds(ptr), "Accessing an out of bounds element is undefined behavior");
            return *ptr;
        }

        MYL_NO_DISCARD constexpr auto operator[](size_type index) const -> const_reference {
            return (*this)[index];
        }

        // Modifiers

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

        constexpr auto push_front(const_reference value) -> void {
            emplace_front(value);
        }

        constexpr auto push_front(value_type&& value) -> void {
            emplace_front(std::move(value));
        }

        constexpr auto push_back(const_reference value) -> void {
            emplace_back(value);
        }

        constexpr auto push_back(value_type&& value) -> void {
            emplace_back(std::move(value));
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

        ///constexpr auto insert(const_iterator position, const value_type& value) -> iterator;

        ///constexpr auto insert(const_iterator position, value_type&& value) -> iterator;

        ///constexpr auto insert(const_iterator position, size_type count, const value_type& value) -> iterator;

        ///template<typename InputIt>
        ///constexpr auto insert(const_pointer position, InputIt first, InputIt last) -> iterator;

        ///template<value_type... Elements>
        ///constexpr auto insert(const_iterator position, Elements&&... elements) -> iterator;
        
        constexpr auto erase(const_iterator position) -> iterator { /// MYTODO: THIS SHOULD BE IMPROVED
            MYL_ASSERT(!out_of_bounds(position.operator->()), "Iterator out of bounds and not part of this container");
            if (m_size == 0)
                return end();

            MYL_ASSERT(position.operator->() != nullptr, "iterator must be dereferenceable");
            altr::destroy(m_allocator, position.operator->());
            --m_size;

            if (position.operator->() == m_head) {
                increment(m_head);
                return begin();
            }
            else if (position.operator->() == m_tail) {
                decrement(m_tail);
                return end();
            }
            else { // Iterator is somewhere in the middle
                /// Stitch the buffer back together
                /// --HX0XXT-- /// Head -> pos | pos + 1 -> tail + 1
                /// XXT----H0X /// Head -> pos | pos + 1 -> end | begin -> tail + 1
                /// X0T----HXX /// Head -> end | begin -> pos | pos + 1 -> tail + 1

                if (linear()) { /// --HX0XXT-- /// Head -> pos | pos + 1 -> tail + 1
                    /// MYTODO: std::move_backward may me better if head -> pos is smaller than pos -> tail
                    std::move(position.operator->() + 1, m_tail + 1, position.operator->());
                    return position;
                }
                else {
                    const size_type destroy_object_offset_from_head = std::distance(m_head, position.operator->());
                    size_type cap = capacity();
                    pointer new_begin = altr::allocate(m_allocator, cap);

                    if (m_head < position.operator->()) { /// XXT----H0X /// Head -> pos | pos + 1 -> end | begin -> tail + 1
                        pointer next1 = std::uninitialized_move(m_head, position.operator->(), new_begin);
                        pointer next2 = std::uninitialized_move(position.operator->() + 1, m_end, next1);
                        std::uninitialized_move(m_begin, m_tail + 1, next2);
                    }
                    else { /// X0T----HXX /// Head -> end | begin -> pos | pos + 1 -> tail + 1
                        pointer next1 = std::uninitialized_move(m_head, m_end, new_begin);
                        pointer next2 = std::uninitialized_move(m_begin, position.operator->(), next1);
                        std::uninitialized_move(position.operator->() + 1, m_tail + 1, next2);
                    }

                    altr::deallocate(m_allocator, m_begin, cap);
                    m_begin = new_begin;
                    m_end = new_begin + cap;
                    m_head = new_begin;
                    m_tail = new_begin + m_size - 1;

                    return iterator(m_head + destroy_object_offset_from_head, this, true);
                }
            }
        }

        ///constexpr auto erase(const_iterator first, const_iterator last) -> iterator;

        constexpr auto assign(size_type count, const_reference value) -> void {
            clear();
            if (count > capacity()) {
                altr::deallocate(m_allocator, count);
                m_begin = altr::allocate(m_allocator, count);
                m_end = m_begin + count;
            }

            m_size = count;
            for (pointer ptr = m_begin; count != 0; ++ptr, --count)
                altr::construct(m_allocator, ptr, value);

            m_head = m_begin;
            m_tail = m_begin + m_size - 1;
        }

        template<typename InputIt>
        constexpr auto assign(InputIt begin, InputIt end) -> void {
            clear();

            const size_type new_size = static_cast<size_type>(end - begin);
            if (new_size > capacity()) {
                altr::deallocate(m_allocator, m_begin, capacity());
                m_begin = altr::allocate(m_allocator, new_size);
                m_end = m_begin + new_size;
            }

            for (pointer ptr = m_begin; begin != end; ++ptr, ++begin)
                altr::construct(m_allocator, ptr, *begin);

            m_head = m_begin;
            m_tail = m_begin + new_size - 1;
            m_size = new_size;
        }

        ///template<value_type... Elements>
        ///constexpr auto assign(Elements&&... elements) -> void;

        constexpr auto clear() noexcept -> void {
            while (m_size != 0) { // Destroys elements tail to head
                altr::destroy(m_allocator, m_tail);
                decrement(m_tail);
                --m_size;
            }

            m_head = m_begin; // Align buffer while it's cheap
            m_tail = m_begin;
        }

        constexpr auto fill(const_reference value) -> void {
            clear();
            for (pointer ptr = m_begin; ptr != m_end; ++ptr)
                altr::construct(m_allocator, ptr, value);

            m_head = m_begin;
            m_tail = m_end - 1;
            m_size = capacity();
        }

        constexpr auto saturate(const_reference value) -> void {
            if (full())
                return;

            pointer ptr = m_tail;
            if (empty())
                altr::construct(m_allocator, ptr, value);
            increment(ptr);

            while (ptr != m_head) {
                altr::construct(m_allocator, ptr, value);
                increment(ptr);
            }

            decrement(ptr);
            m_tail = ptr;
            m_size = capacity();
        }

        constexpr auto reserve(size_type new_capacity) -> void {
            const size_type cap = capacity();
            if (cap == 0) {
                m_begin = altr::allocate(m_allocator, new_capacity);
                m_end = m_begin + new_capacity;
                m_head = m_begin;
                m_tail = m_begin;
            }
            else if (new_capacity > cap)
                reallocate(new_capacity);
        }

        constexpr auto shrink_to_fit() -> void {
            if (capacity() > m_size)
                reallocate(m_size);
        }

        /// RESIZE WITHOUT VALUE?

        constexpr auto resize(size_type new_size, const_reference value = value_type()) -> void {
            if (new_size < m_size)
                pop_back(m_size - new_size);
            else if (new_size > capacity()) {
                reserve(new_size);
                saturate(value);
            }
            else if (new_size > m_size) // Previous check ensures capacity >= new_size
                while (new_size != m_size)
                    push_back(value);
        }

        constexpr auto rotate(pointer new_head) -> void { /// MYTODO: Should be a iterator
            MYL_ASSERT(!out_of_bounds(new_head), "The ring buffer must contain the address of the new head");
            if (new_head == m_head)
                return;

            m_head = new_head;
            /// Is (offset % m_size) - 1 not good enough???
            m_tail = m_begin + ((offset() + m_size) % m_size) - 1;
        }

        constexpr auto rotate(difference_type offset) -> void { /// FIXING THIS WILL MESS UP OTHER TESTS
            /// MYTODO: This may have to reallocate, as rotate OHTO by 1 would result in OTHO,
            /// THIS IS NOT VALID
            /// CANT ROTATE EMPRTY
            if (offset == 0 || m_size == offset % m_size)
                return;

            if (full()) {
                m_head = m_begin + ((this->offset() + offset - 1) % m_size) + 1;
                m_tail = m_begin + ((this->offset() + m_size) % m_size) - 1; /// WTF, this is probably no good
            }
            else {
                const size_type cap = capacity();
                pointer new_begin = altr::allocate(m_allocator, cap);
                pointer new_head = m_begin + ((this->offset() + offset - 1) % m_size) + 1;

                bool need_thrid_copy = m_tail + 1 < new_head;
                pointer next = std::uninitialized_move(new_head, need_thrid_copy ? m_end : m_tail + 1, new_begin);
                if (need_thrid_copy)
                    next = std::uninitialized_move(m_begin, m_tail + 1, next);
                std::uninitialized_move(m_head, new_head > m_head ? new_head : m_end, next);

                altr::deallocate(m_allocator, m_begin, cap);
                m_begin = new_begin;
                m_end = m_begin + cap;
                m_head = m_begin;
                m_tail = m_begin + m_size - 1;

                //////offset = 2
                ///    OOHABTO | OO HA BT O -> BT
                ///    HABTOOO | HA BT  OOO -> BT
                ///    BTOOOHA | BT OOO  HA -> BT
                ///    TOOOHAB | T  OOO HAB -> BT
                /// 
                /// OHTO | O H T O -> THOO
                /// 
                ///        // copy 1 new_head to tail+1/end (which evercomes first)
                ///
                ///        /// confirm /m_end (which evercomes first) for copy 2
                ///        // copy 2 head -> new_head/m_end (which evercomes first) = array_2 /// only work if new_head is greater than head
                ///        // copy 3 if end in copy 1 : m_begin to tail + 1

               
            }
        }

        constexpr auto align() -> void {
            if (m_head == m_begin)
                return;

            if (m_size == 0) {
                m_head = m_begin;
                m_tail = m_begin;
                return;
            }

            size_type cap = capacity();
            pointer new_begin = altr::allocate(m_allocator, cap);
            pointer next = std::uninitialized_move(m_head, m_end, new_begin);
            std::uninitialized_move(m_begin, m_tail + 1, next);

            altr::deallocate(m_allocator, m_begin, cap);
            m_begin = new_begin;
            m_end = new_begin + cap;
            m_head = new_begin;
            m_tail = new_begin + m_size - 1; // This works because capacity = 0 was handled earlier
        }

        ///constexpr auto swap(ring_buffer& other) noexcept(altr::propagate_on_container_swap::value || altr::is_always_equal::value) -> void;
    private:
        inline constexpr auto increment(pointer& ptr) const noexcept -> void { /// Should be pointer of pointer to imply object is changed
            ptr == m_end - 1 ?
                ptr = m_begin : // Loop from the last to first element of the array
                ++ptr;
        }

        inline constexpr auto decrement(pointer& ptr) const noexcept -> void { /// Should be pointer of pointer to imply object is changed
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
            MYL_ASSERT(capacity() != 0);
            pointer new_begin = altr::allocate(m_allocator, new_capacity);

            if (linear())
                std::uninitialized_move(m_head, m_tail + 1, new_begin);
            else {
                pointer next = std::uninitialized_move(m_head, m_end, new_begin);
                std::uninitialized_move(m_begin, m_tail + 1, next);
            }

            altr::deallocate(m_allocator, m_begin, capacity());
            m_begin = new_begin;
            m_end = new_begin + new_capacity;
            m_head = new_begin;
            m_tail = new_begin + (m_size == 0 ? 0 : m_size - 1);
        }

        constexpr auto increment_circulator(pointer ptr, bool& has_looped) const -> void {
            if (ptr == m_tail)
                has_looped = true;
            ptr == m_tail ? ptr = m_head : ++ptr;
            if (ptr == m_end)
                ptr = m_begin;
        }

        constexpr auto decrement_circulator(pointer ptr, bool& has_looped) const -> void {
            if (ptr == m_head)
                has_looped = true;
            ptr == m_head ? ptr = m_tail : --ptr;
            if (ptr == m_begin - 1)
                ptr = m_end - 1;
        }
    };

    /// should this compare if they are aligned?
    template<typename T, typename A>
    MYL_NO_DISCARD constexpr auto operator==(const ring_buffer<T, A>& l, const ring_buffer<T, A>& r) -> bool {
        if (l.size() != r.size())
            return false;

        for (auto lit = l.cbegin(), rit = r.cbegin(), lend = l.cend(), rend = r.cend(); lit != lend && rit != rend; ++lit, ++rit)
            if (*lit != *rit)
                return false;
        return true;
    }

    /// <=>
}

namespace std {
    ///template<typename T, typename A>
    ///constexpr auto swap(myl::ring_buffer<T, A>& l, myl::ring_buffer<T, A>& r) noexcept(noexcept(l.swap(r))) -> void {
    ///    l.swap.r();
    ///}
    
    ///template<typename T, typename A, typename U>
    ///constexpr auto erase(myl::ring_buffer<T, A>& buffer, const U& value) -> typename myl::ring_buffer<T, A>::size_type {
    ///
    ///}
    
    ///template<typename T, typename A, typename Pred>
    ///constexpr auto erase_if(myl::ring_buffer<T, A>& buffer, Pred predicate) -> typename myl::ring_buffer<T, A>::size_type {
    ///
    ///}
}
