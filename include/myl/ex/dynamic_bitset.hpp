#pragma once
#include <myl/defines.hpp>

#include <climits>
#include <memory>
#include <numeric>

/// Functions to set a block or takes a block pos and bit pos

namespace myl {
	template<unsigned_integer T = u32, typename Allocator = std::allocator<T>>
	class dynamic_bitset {
	public:
		using allocator_type = Allocator;
		using block_type = T;
		using size_type = usize;

		class reference {
			dynamic_bitset& m_bitset;
			size_type m_bit; /// MYTodo: Would probs be better if the block and bit positions were stored

			MYL_NO_DISCARD constexpr reference(dynamic_bitset& a_dynamic_bitset, size_type a_bit)
				: m_bitset{ a_dynamic_bitset }
				, m_bit{ a_bit } {}

			constexpr ~reference() = default;
		public:
			constexpr auto flip() noexcept -> void { m_bitset.flip(m_bit); }

			constexpr auto operator=(bool a_value) noexcept -> reference& { m_bitset[m_bit] = a_value; return *this; }
			constexpr auto operator=(const reference& a_ref) noexcept -> reference& { m_bitset[m_bit] = static_cast<bool>(a_ref); return *this; }

			///reference& operator|=(bool value);
			///reference& operator&=(bool value);
			///reference& operator^=(bool value);
			///reference& operator-=(bool value);
			MYL_NO_DISCARD constexpr auto operator~() const noexcept -> bool { return !static_cast<bool>(*this); }

			MYL_NO_DISCARD constexpr operator bool() const noexcept -> bool { return m_bitset[m_bit]; }
		};
	private:
		block_type* m_begin = nullptr;
		block_type* m_end = nullptr;
		size_type m_size = 0;
	public:
		// Constructors / Destructor
		
		MYL_NO_DISCARD constexpr dynamic_bitset() noexcept = default;

		/// Construct from values
		///MYL_NO_DISCARD constexpr dynamic_bitset();

		///explicit dynamic_bitset(const allocator_type& alloc = allocator_type());
		///
		///explicit dynamic_bitset(size_type num_bits, unsigned long value = 0, const allocator_type& alloc = allocator_type());
		///
		///template <typename CharT, typename Traits, typename Alloc>
		///explicit dynamic_bitset(const std::basic_string<CharT, Traits, Alloc>& s,
		///	typename std::basic_string<CharT, Traits, Alloc>::size_type pos = 0,
		///	typename std::basic_string<CharT, Traits, Alloc>::size_type n = std::basic_string<CharT, Traits, Alloc>::npos,
		///	const Allocator& alloc = Allocator());

		///template <typename BlockInputIterator>
		///dynamic_bitset(BlockInputIterator first, BlockInputIterator last, const Allocator& alloc = Allocator());

		constexpr ~dynamic_bitset() {

		}

		// Utilities

		MYL_NO_DISCARD constexpr static auto max_size() noexcept -> size_type { return std::numeric_limits<size_type>::max(); }

		MYL_NO_DISCARD constexpr auto get_allocator() const -> allocator_type { ///

		}

		MYL_NO_DISCARD constexpr auto size() const noexcept -> size_type { return m_size; }
		MYL_NO_DISCARD constexpr auto capacity() const noexcept -> size_type { return static_cast<size_type>(m_end - m_begin) * CHAR_BIT; }
		MYL_NO_DISCARD constexpr auto blocks() const noexcept -> size_type { return (m_end - m_begin) / sizeof(block_type); }
		MYL_NO_DISCARD constexpr auto empty() const noexcept -> bool { return m_begin == m_end; }


		MYL_NO_DISCARD constexpr auto all() const noexcept -> bool { ///

		}

		MYL_NO_DISCARD constexpr auto none() const noexcept -> bool { return !all(); }

		MYL_NO_DISCARD constexpr auto any() const noexcept -> bool { ///

		}

		MYL_NO_DISCARD constexpr auto count() const noexcept -> size_type { ///

		}

		MYL_NO_DISCARD constexpr auto test(size_type a_pos) const -> bool { /// throw out of range, /// assert within range
			return (*this)[a_pos];
		}

		constexpr auto swap(dynamic_bitset& a_other) -> void { ///

		}

		MYL_NO_DISCARD constexpr auto operator~() const -> dynamic_bitset {

		}

		// Iterators

		// Modifiers

		constexpr auto resize(size_type a_bits, bool a_value = false) -> void { ///

		}

		constexpr auto push() -> void { ///

		}

		//@brief Sets all bits to 1
		constexpr auto set() noexcept -> void {///

		}

		//@brief Sets a bit to a_value
		constexpr auto set(size_type a_pos, bool a_value = true) -> void {/// throw out of range, /// assert within range

		}

		//@brief Sets all bits to 0
		constexpr auto reset() noexcept -> void { ///

		}

		//@brief Sets A bit to 0
		constexpr auto reset(size_type a_pos) noexcept -> void {/// throw out of range, /// assert within range
			set(a_pos, false);
		}

		//@brief Flips all bits
		constexpr auto flip() noexcept -> void { /// Flip all

		}

		//@brief Flips a bit
		constexpr auto flip(size_type a_pos) -> void { /// throw out of range, /// assert within range
			const auto pos = calc_positions(a_pos);
			m_begin[pos.block] ^= 1 << pos.bit;
			return *this;
		}

		template<typename Iterator>
		constexpr auto append(Iterator a_begin, Iterator a_end) -> void { ///

		}

		constexpr auto push_block(block_type a_block) -> void { ///

		}

		//@brief Sets a block of bits to 1
		constexpr auto set_block(size_type a_pos) -> void {/// throw out of range, /// assert within range

		}

		//@brief Sets a block of bits to a_value
		constexpr auto set_block(size_type a_pos, block_type a_value) -> void {/// throw out of range, /// assert within range

		}

		//@brief Sets a block of bits to 0
		constexpr auto reset_block(size_type a_pos) -> void {
			set_block(a_pos, 0);
		}

		//@brief Flips all bits of a block
		constexpr auto flip_block(size_type a_pos) noexcept -> void { /// Flip block

		}

		///constexpr auto operator&=(const dynamic_bitset& b) -> dynamic_bitset&;
		///constexpr auto operator|=(const dynamic_bitset& b) -> dynamic_bitset&;
		///constexpr auto operator^=(const dynamic_bitset& b) -> dynamic_bitset&;
		///constexpr auto operator-=(const dynamic_bitset& b) -> dynamic_bitset&;
		///constexpr auto operator<<=(size_type n) -> dynamic_bitset&;
		///constexpr auto operator>>=(size_type n) -> dynamic_bitset&;
		///MYL_NO_DISCARD constexpr auto operator<<(size_type n) const -> dynamic_bitset;
		///MYL_NO_DISCARD constexpr auto operator>>(size_type n) const -> dynamic_bitset;

		// Element access

		MYL_NO_DISCARD constexpr auto operator[](size_type a_pos) const -> bool { /// assert within range
			const auto pos = calc_positions(a_pos);
			return static_cast<bool>(m_begin[pos.block] & pos.bit);
		}

		MYL_NO_DISCARD constexpr auto operator[](size_type a_pos) -> reference { /// assert within range

		}
	private:
		MYL_NO_DISCARD constexpr auto calc_positions(size_type a_pos) const noexcept {
			struct positions { u8 bit; size_type block; };
			const size_type bit = a_pos % CHAR_BIT;
			return positions{
				.bit = bit,
				.block = (a_pos - bit) / CHAR_BIT
			};
		}
	};

	///template <typename T, typename Allocator>
	///MYL_NO_DISCARD constexpr auto swap(const dynamic_bitset<T, Allocator>& l, const dynamic_bitset<T, Allocator>& r) -> void;

	///template <typename T, typename Allocator>
	///MYL_NO_DISCARD constexpr auto operator==(const dynamic_bitset<T, Allocator>& l, const dynamic_bitset<T, Allocator>& r) -> bool;
	///
	///template <typename T, typename Allocator>
	///MYL_NO_DISCARD constexpr auto operator!=(const dynamic_bitset<T, Allocator>& l, const dynamic_bitset<T, Allocator>& r) -> bool;
	///
	///template <typename T, typename Allocator>
	///MYL_NO_DISCARD constexpr auto operator<(const dynamic_bitset<T, Allocator>& l, const dynamic_bitset<T, Allocator>& r) -> bool;
	///
	///template <typename T, typename Allocator>
	///MYL_NO_DISCARD constexpr auto operator<=(const dynamic_bitset<T, Allocator>& l, const dynamic_bitset<T, Allocator>& r) -> bool;
	///
	///template <typename T, typename Allocator>
	///MYL_NO_DISCARD constexpr auto operator>(const dynamic_bitset<T, Allocator>& l, const dynamic_bitset<T, Allocator>& r) -> bool;
	///
	///template <typename T, typename Allocator>
	///MYL_NO_DISCARD constexpr auto operator>=(const dynamic_bitset<T, Allocator>& l, const dynamic_bitset<T, Allocator>& r) -> bool;
	///
	///template <typename T, typename Allocator>
	///MYL_NO_DISCARD constexpr auto operator&(const dynamic_bitset<T, Allocator>& l, const dynamic_bitset<T, Allocator>& r) -> dynamic_bitset<T, Allocator>;
	///
	///template <typename T, typename Allocator>
	///MYL_NO_DISCARD constexpr auto operator|(const dynamic_bitset<T, Allocator>& l, const dynamic_bitset<T, Allocator>& r) -> dynamic_bitset<T, Allocator>;
	///
	///template <typename T, typename Allocator>
	///MYL_NO_DISCARD constexpr auto operator^(const dynamic_bitset<T, Allocator>& l, const dynamic_bitset<T, Allocator>& r) -> dynamic_bitset<T, Allocator>;
	///
	///template <typename T, typename Allocator>
	///MYL_NO_DISCARD constexpr auto operator-(const dynamic_bitset<T, Allocator>& l, const dynamic_bitset<T, Allocator>& r) -> dynamic_bitset<T, Allocator>;
	///
	///template <typename T, typename Allocator, typename Char>
	///MYL_NO_DISCARD constexpr auto string_cast(const dynamic_bitset<T, Allocator>& b) -> std::basic_string<Char>;
	///
	///template <typename Char, typename Traits, typename T, typename Allocator>
	///constexpr auto operator<<(std::basic_ostream<Char, Traits>& os, const dynamic_bitset<T, Allocator>& b) -> std::basic_ostream<Char, Traits>&;
	///
	///template <typename Char, typename Traits, typename T, typename Allocator>
	///constexpr auto operator>>(std::basic_istream<Char, Traits>& is, dynamic_bitset<T, Allocator>& b) -> std::basic_istream<Char, Traits>&;
}