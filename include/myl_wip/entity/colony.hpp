#pragma once
#include <myl/definitions.hpp>

#include <cstdlib>
#include <memory>

#ifndef MYL_NO_EXCEPTIONS
#   include <stdexcept>
#endif

/// https://en.cppreference.com/cpp/container/hive
/// https://github.com/mattreecebentley/plf_colony

/// MYTodo:
/// - assign_range
/// - insert_range

namespace myl {
    
    template<typename T, bool IsConst>
    class colony_iterator {
    public:
        using iterator_concept  = std::bidirectional_iterator_tag;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = std::conditional_t<IsConst, const value_type*, value_type*>;
        using reference         = std::conditional_t<IsConst, const value_type&, value_type&>;
    private:
        pointer m_block_ptr = nullptr;
        pointer m_element_ptr = nullptr;
    public:
        // Constructors, Destructor, Assignment

        MYL_NO_DISCARD constexpr colony_iterator() noexcept = default;
        MYL_NO_DISCARD constexpr colony_iterator(const colony_iterator&) noexcept = default;
        MYL_NO_DISCARD constexpr colony_iterator(colony_iterator&&) noexcept = default;

        MYL_NO_DISCARD constexpr colony_iterator(const colony_iterator<value_type, false>& it) noexcept requires IsConst
            : m_block_ptr{ it.m_block_ptr }
            , m_element_ptr{ it.m_element_ptr } {}

        MYL_NO_DISCARD constexpr colony_iterator(colony_iterator<value_type, false> && it) noexcept requires IsConst
            : m_block_ptr{ std::move(it.m_block_ptr) }
            , m_element_ptr{ std::move(it.m_element_ptr) } {}

        ///MYL_NO_DISCARD constexpr colony_iterator(pointer ptr) noexcept {
        ///    
        ///}

        constexpr ~colony_iterator() = default;

        constexpr auto operator=(const colony_iterator& r) noexcept -> colony_iterator& {
            m_block_ptr = r.m_block_ptr;
            m_element_ptr = r.m_element_ptr;
            return *this;
        }

        constexpr auto operator=(colony_iterator&& r) noexcept -> colony_iterator& {
            m_block_ptr = std::move(r.m_block_ptr);
            m_element_ptr = std::move(r.m_element_ptr);
            return *this;
        }

        constexpr auto operator=(const colony_iterator<value_type, false>& r) noexcept -> colony_iterator& requires IsConst {
            m_block_ptr = r.m_block_ptr;
            m_element_ptr = r.m_element_ptr;
            return *this;
        }

        constexpr auto operator=(colony_iterator<value_type, false>&& r) noexcept -> colony_iterator& requires IsConst {
            m_block_ptr = std::move(r.m_block_ptr);
            m_element_ptr = std::move(r.m_element_ptr);
            return *this;
        }

        // Access
        
        MYL_NO_DISCARD constexpr auto operator*() const -> reference {
            MYL_ASSERT(m_element_ptr != nullptr, "Can't dereference an invalid iterator");
            return *m_element_ptr;

        }
        
        MYL_NO_DISCARD constexpr auto operator->() const noexcept -> pointer {
            return m_element_ptr;
        }

        // Traversal

        constexpr auto operator++() -> colony_iterator& {
            /// block pointer cant be null


        }
        
        MYL_NO_DISCARD constexpr auto operator++(int) -> colony_iterator {
            const colony_iterator temp(*this);
            ++(*this);
            return temp;
        }
        
        ///constexpr auto operator--() -> colony_iterator& {
        ///
        ///}
        
        MYL_NO_DISCARD constexpr auto operator--(int) -> colony_iterator {
            const colony_iterator temp(*this);
            --(*this);
            return temp;
        }
        
        ///MYL_NO_DISCARD constexpr auto operator+(const difference_type offset) const noexcept -> colony_iterator {
        ///
        ///}
        ///
        ///MYL_NO_DISCARD constexpr auto operator-(const difference_type offset) const noexcept -> colony_iterator {
        ///
        ///}
        ///
        ///MYL_NO_DISCARD constexpr auto operator-(const contiguous_iterator& r) const noexcept -> difference_type {
        ///
        ///}
        ///
        ///constexpr auto operator+=(const difference_type offset) noexcept -> colony_iterator& {
        ///
        ///}
        ///
        ///constexpr auto operator-=(const difference_type offset) noexcept -> colony_iterator& {
        ///
        ///}

        // Comparison

        MYL_NO_DISCARD constexpr auto operator==(const colony_iterator& r) const noexcept -> bool {
            return m_element_ptr == r.m_element_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator==(const colony_iterator<value_type, !IsConst>& r) const noexcept -> bool {
            return m_element_ptr == r.m_element_ptr;
        }

        MYL_NO_DISCARD constexpr auto operator<=>(const colony_iterator& r) const noexcept {

        }

        MYL_NO_DISCARD constexpr auto operator<=>(const colony_iterator<value_type, !IsConst>& r) const noexcept {

        }

    private:
        constexpr auto advance() -> void {

        }
    };

    struct colony_limits {
        usize min;
        usize max;

        MYL_NO_DISCARD constexpr colony_limits(const usize minimum, const usize maximum) noexcept
            : min{ minimum }
            , max{ maximum } {}
    };

    template<typename T, typename Allocator = std::allocator<T>>
    class colony {
        using altr = std::allocator_traits<Allocator>;
    public:
        // Member Types

        using value_type             = T;
        using allocator_type         = Allocator;
        using size_type              = usize;
        using difference_type        = std::ptrdiff_t;
        using reference              = value_type&;
        using const_reference        = const value_type&;
        using pointer                = value_type*;
        using const_pointer          = const value_type*;
        using iterator               = colony_iterator<value_type, false>;
        using const_iterator         = colony_iterator<value_type, true>;
        using reverse_iterator       = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    private:        
        // Data Structures

        struct block {
            block* next;
            block* prev;
            pointer data;
            size_type size;
            const size_type capacity;
            size_type skipfield_head; // Index of the last erased element of a group

            block() = delete;
            block(const block&) = delete;
            block(block&&) = delete;

            block& operator=(const block&) = delete;
            block& operator=(block&&) = delete;

            MYL_NO_DISCARD constexpr block(allocator_type alloc, size_type cap)
                : next{ nullptr }
                , prev{ nullptr }
                , data{ altr::allocate(alloc, cap) }
                , size{ 0 }
                , capacity{ cap }
                , skipfield_head{ 0 } {}

            ///constexpr ~block() {
            ///
            ///}
        };

        using block_allocator_type = altr::rebind_alloc<block>;
        using block_altr = std::allocator_traits<block_allocator_type>;

        // Members
        
        block* m_begin;
        block* m_erased_blocks;/// implement and understand // List of blocks that are available for re-use
        block* m_unused_blocks; // List of uninitiated blocks availble for use
        size_type m_size;
        size_type m_capacity;
        colony_limits m_block_limits;

        /// MYTODO: Why are these conditional
        std::conditional_t<std::is_empty_v<allocator_type>, MYL_NO_UNIQUE_ADDRESS allocator_type, allocator_type> m_element_allocator{};
        std::conditional_t<std::is_empty_v<block_allocator_type>, MYL_NO_UNIQUE_ADDRESS block_allocator_type, block_allocator_type> m_block_allocator{};
    public:
        // Constructors, Destructor, Assignment

        MYL_NO_DISCARD constexpr colony() noexcept(noexcept(allocator_type()))
            : colony(allocator_type()) {}

        MYL_NO_DISCARD constexpr explicit colony(const allocator_type& allocator) noexcept
            : m_begin{ nullptr }
            , m_erased_blocks{ nullptr }
            , m_unused_blocks{ nullptr }
            , m_size{ 0 }
            , m_capacity{ 0 }
            , m_block_limits{ block_capacity_default_limits()}
            , m_element_allocator{ allocator },
            , m_block_allocator{ block_allocator_type() } { }

        MYL_NO_DISCARD constexpr explicit colony(colony_limits block_limits)
            : colony(block_limits, allocator_type()) {}

        MYL_NO_DISCARD constexpr colony(colony_limits block_limits, const allocator_type& allocator)
            : m_begin{ nullptr }
            , m_erased_blocks{ nullptr }
            , m_unused_blocks{ nullptr }
            , m_size{ 0 }
            , m_capacity{ 0 }
            , m_block_limits{ block_limits }
            , m_element_allocator{ allocator },
            , m_block_allocator{ block_allocator_type() } {}
         
        ///constexpr explicit colony(size_type count, const allocator_type& allocator = allocator_type());
        ///constexpr colony(size_type count, colony_limits block_limits, const allocator_type& allocator = allocator_type());
        ///constexpr colony(size_type count, const value_type& value, const allocator_type& allocator = allocator_type());
        ///constexpr colony(size_type count, const value_type& value, colony_limits block_limits, const allocator_type& allocator = allocator_type());
        ///template<typename InputIt> constexpr colony(InputIt first, InputIt last, const allocator_type& allocator = allocator_type());
        ///template<typename InputIt> constexpr colony(InputIt first, InputIt last, colony_limits block_limits, const allocator_type& allocator = allocator_type());
        /// template< /*container-compatible-range*/<T> R > constexpr colony(std::from_range_t, R&& rg, const allocator_type& allocator = allocator_type());
        /// template< /*container-compatible-range*/<T> R > constexpr colony(std::from_range_t, R&& rg, colony_limits block_limits, const allocator_type& allocator = allocator_type());
        ///constexpr colony(const colony& other);
        ///constexpr colony(colony&& other) noexcept;
        ///constexpr colony(const colony& other, const std::type_identity_t<allocator_type>& allocator);
        ///constexpr colony(colony&& other, const type_identity_t<allocator_type>& allocator);
        
        //MYL_NO_DISCARD constexpr colony(std::initializer_list<value_type> list, const allocator_type& allocator = allocator_type())
        //    : colony(list, block_capacity_default_limits(), allocator)

        //MYL_NO_DISCARD constexpr colony(std::initializer_list<value_type> list, colony_limits block_limits, const allocator_type& allocator = allocator_type());

        ///constexpr auto ~colony();
        
        ///constexpr auto operator=(const colony& other) -> colony&;
        ///constexpr auto operator=(colony&& other) noexcept(/*See description*/) -> colony&;
        ///constexpr auto operator=(std::initializer_list<value_type> list) -> colony&;
        
        ///constexpr auto assign(size_type count, const value_type& value) -> void;
        ///template<typename InputIt> constexpr auto assign(InputIt first, InputIt last) -> void;
        ///constexpr auto assign(std::initializer_list<value_type> list) -> void;

        // Iterators

        ///constexpr auto begin() noexcept -> iterator;
        ///constexpr auto begin() const noexcept -> const_iterator;
        ///constexpr auto cbegin() const noexcept -> const_iterator { return begin(); }
        
        ///constexpr auto end() noexcept -> iterator;
        ///constexpr auto end() const noexcept -> const_iterator;
        ///constexpr auto cend() const noexcept -> const_iterator { return end(); }
        
        ///constexpr auto rbegin() noexcept -> reverse_iterator;
        ///constexpr auto rbegin() const noexcept -> const_reverse_iterator;
        ///constexpr auto crbegin() const noexcept -> const_reverse_iterator { return rbegin(); }
        
        ///constexpr auto rend() noexcept -> reverse_iterator;
        ///constexpr auto rend() const noexcept -> const_reverse_iterator;
        ///constexpr auto crend() const noexcept -> const_reverse_iterator { return rend(); }

        // Utilities

        MYL_NO_DISCARD constexpr auto get_allocator() const noexcept -> allocator_type {
            return m_element_allocator;
        }

        ///constexpr auto max_size() const noexcept -> size_type;

        MYL_NO_DISCARD constexpr auto size() const noexcept -> size_type {
            return m_size;
        }

        MYL_NO_DISCARD constexpr auto capacity() const noexcept -> size_type {
            return m_capacity;
        }

        constexpr auto block_capacity_limits() const noexcept -> colony_limits {
            return m_block_limits;
        }

        ///static constexpr auto block_capacity_hard_limits() noexcept -> colony_limits;

        static constexpr auto block_capacity_default_limits() noexcept -> colony_limits {
            return colony_limits{ /// MYTODO: Go look at https://github.com/mattreecebentley/plf_colony/blob/master/plf_colony.h#L425 for some complicated stuff
                .min = 8,
                .max = 256
            }
        }

        ///static constexpr auto is_within_hard_limits() noexcept -> bool;
        
        MYL_NO_DISCARD constexpr auto empty() const noexcept -> bool {
            return m_size == 0;
        }

        // Element Access

        ///constexpr auto get_iterator(const_pointer ptr) noexcept -> iterator;
        ///constexpr auto get_iterator(const_pointer ptr) const noexcept -> const_iterator;

        // Modifiers

        ///template<typename... Args> constexpr auto emplace(Args&&... args) -> iterator {
        ///
        ///}
        
        ///template<typename... Args> constexpr auto emplace_hint(const_iterator hint, Args&&... args) -> iterator;
         
        ///constexpr auto insert(const value_type& value) -> iterator {
        ///    return emplace(value);
        ///}
        ///
        ///constexpr auto insert(value_type&& value) -> iterator {
        ///    return emplace(std::move(value));
        ///}

        ///constexpr auto insert(const_iterator hint, const value_type& value) -> iterator;
        ///constexpr auto insert(const_iterator hint, value_type&& value) -> iterator;
        ///constexpr auto insert(std::initializer_list<value_type> list) -> void;
        ///template<typename InputIt> constexpr auto insert(InputIt first, InputIt last) -> void;
        ///constexpr auto insert(size_type count, const value_type& value) -> void;
        ///constexpr auto erase(const_iterator position) -> iterator;
        ///constexpr auto erase(const_iterator first, const_iterator last) -> iterator;
        ///template<typename BniaryPredicate = std::equal_to<value_type>> constexpr auto unique(BinaryPredicate binary_predicate = BinaryPredicate()) -> size_type;
         
        constexpr auto clear() noexcept -> void {
            if (m_size == 0)
                return;

            // Destroy all elements
            block* current_block = m_begin;
            while (true) {
                destroy_block_elements(current_block);
                if (current_block->next == nullptr)
                    break;

                current_block = current_block->next;
            }
            
            if (m_begin->next != nullptr) { // Only move blocks past the first block when there is more than 1 block
                current_block->next = m_unused_blocks; // Link up the previously destroyed blocks to the unused blocks
                m_unused_blocks = m_begin->next;
                // Decouple the m_begin and m_begin->next blocks
                m_begin->next = nullptr;
                m_unused_blocks->prev = nullptr;
            }

            m_size = 0;
        }

       constexpr auto reserve(size_type new_capacity) -> void {
            if (new_capacity <= m_capacity) // Sufficient memory is already allocated
                return;
#ifndef MYL_NO_EXCEPTIONS
            if (new_capacity > max_size())
                throw std::length_error("Capacity requested is greater than the max size");
#endif
            new_capacity -= m_capacity;
            auto [reserve_block_count, remainder] = std::div(new_capacity, m_block_limits.max);

            /// If a block + remainder < max block, maybe combined them. probs shuould only happen when that other block is unused

            if (remainder == 0) { // Should be unreachable given new_capacity == 0. Easier to always create the remainder block than sometimes
                remainder = m_block_limits.max;
                --reserve_block_count;
            }
            else if (remainder < m_block_limits.min)
                remainder = m_block_limits.min;

            // Create the remainder block
            block* current_block = allocate_new_block(remainder);
            block* new_unused_block_head = current_block;

            // Create the maxed capacity blocks
            while (reserve_block_count != 0) {
                current_block->next = allocate_new_block(m_block_limits.max);
                current_block = current_block->next;
                --reserve_block_count;
            }

            // Prepend to any existing unused blocks
            current_block->next = m_unused_blocks;
            m_unused_blocks = new_unused_block_head;
       }


        ///constexpr auto shrink_to_fit() -> void;
        ///constexpr auto trim() -> void;
        ///constexpr auto trim(size_type new_capacity) -> void;
        ///constexpr auto reshape(colony_limits block_limits) -> void;
        ////// google "c++ how to define std::swap for a custom type"
        ////// MYTODO: should modify other containers
        ///constexpr auto swap(colony& other) noexcept(/* see description*/) -> void;
        ///constexpr auto splice(colony& other) -> void;
        ///constexpr auto splice(colony&& other) -> void;
        ///template<typename Compare = std::less<value_type>> constexpr auto sort(Compare compare = Compare()) -> void;

        /// MYTODO: Confirm if this is the proper way
        // std:: algorithm specializations

        ///friend constexpr auto swap(colony& lhs, colony& rhs) noexcept(noexcept(lhs.swap(rhs))) -> void;
        ///template<typename T_, typename Allocator_, typename U = T_> friend constexpr auto erase(colony<T_, Allocator_>& c, const U& value) -> typename colony<T_, Allocator_>::size_type;      
        ///template<typename T_, typename Allocator_, typename Predicate> friend constexpr auto erase_if(colony<T_, Allocator_>& c, Predicate predicate) -> typename colony<T_, Allocator_>::size_type;      
    private:
        MYL_NO_DISCARD constexpr auto allocate_new_block(size_type capacity) -> block* {
            const block* new_block = block_altr::allocate(m_block_allocator, 1);
            block_altr::construct(m_block_allocator, new_block, m_element_allocator, capacity);
            m_capacity += capacity;

            return new_block;
        }

        constexpr auto destroy_block_elements(block* block) -> void {

        }
    };
}
