#pragma once
#include <myl/defines.hpp>
#include <myl/exception.hpp>

#include <bitset>

namespace myl {
	template<typename T>
	class unique_ptr {
	public:
		using value_type = T;
		using pointer = value_type*;
	private:
		pointer m_ptr = nullptr;
	public:
		MYL_NO_DISCARD constexpr unique_ptr() = default;

		MYL_NO_DISCARD constexpr unique_ptr(pointer a_ptr)
			: m_ptr{ a_ptr } {}

		constexpr ~unique_ptr() {
			if (m_ptr)
				delete m_ptr;
		}

		constexpr auto replace(pointer a_ptr) -> void {
			if (m_ptr)
				delete m_ptr;
			m_ptr = a_ptr;
		}

		auto operator->() -> pointer {
			return m_ptr;
		}

		auto operator*() -> value_type& {
			return *m_ptr;
		}

		explicit operator bool() const {
			return static_cast<bool>(m_ptr);
		}
	};

	//@tparam Size: The amount of memory blocks
	//@tparam T: The size of each memory block
	template<usize Size, unsigned_integer Block = u32>
	class static_allocator {
	public:
		using value_type	= Block;
		using size_type		= usize;
		using pointer		= value_type*;
		using const_pointer	= const value_type*;
	private:
		enum : bool { free = 0, used = 1 };

		Block m_data[Size];
		std::bitset<Size> m_flags; // Flags each block of memory as free or in use
	public:
		constexpr static_allocator() {

		}

		constexpr ~static_allocator() {

		}

		//@param a_size: Amount of bytes requested
		constexpr auto allocate(usize a_bytes) -> pointer { /// need to call constructors
			// Find free memory range
			pointer ptr = nullptr;
			for (usize i = 0, s = 0; s != a_bytes; ++i) { /// pretty sure this wont work
				m_flags.test(i) ? s = 0: s += sizeof(Block);
				if (s >= a_bytes) {
					ptr = m_data + i;
					mark(ptr, i, used);
					break;
				}
			}

			if (ptr == nullptr)
				throw exception("Static allocator out of memory!");
			return ptr;
		}

		constexpr auto deallocate(pointer a_ptr, usize a_size) -> void { /// need to call destructors
			mark(a_ptr, a_size, free);
		}
	private:
		constexpr auto mark(pointer a_ptr, usize a_size, bool a_state) -> void {
			for (usize i = 0; i != a_size; ++i)
				m_flags.set(a_ptr - m_data + i, a_state);
		}
	};
}