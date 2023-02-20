#pragma once
#include <myl/defines.hpp>

namespace myl {
	template<typename T>
	class circulator {
	public:
		using value_type = T;
		using size_type = u64;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
	private:
		pointer m_ptr = nullptr;
		pointer m_begin = nullptr;
		pointer m_end = nullptr;
		pointer m_head = nullptr;
		pointer m_tail = nullptr;
		bool m_has_looped = false;
	public:
		MYL_NO_DISCARD constexpr circulator() noexcept = default;
		MYL_NO_DISCARD constexpr circulator(pointer a_ptr, pointer a_begin, pointer a_end, pointer a_head, pointer a_tail, bool a_has_looped)
			: m_ptr(a_ptr)
			, m_begin(a_begin)
			, m_end(a_end)
			, m_head(a_head)
			, m_tail(a_tail)
			, m_has_looped(a_has_looped) {}

		constexpr ~circulator() noexcept {}

		MYL_NO_DISCARD constexpr auto operator*() -> reference { return *m_ptr; }
		MYL_NO_DISCARD constexpr auto operator*() const -> const_reference { return *m_ptr; }
		MYL_NO_DISCARD constexpr auto operator->() -> pointer { return m_ptr; }

		constexpr auto operator++() -> circulator& { increment(); return *this; }
		constexpr auto operator--() -> circulator& { decrement(); return *this; }
		constexpr auto operator++(int) -> circulator& { circulator temp(*this); increment(); return temp; }
		constexpr auto operator--(int) -> circulator& { circulator temp(*this); decrement(); return temp; }

		MYL_NO_DISCARD constexpr auto operator==(const circulator& a_rhs) const -> bool {
			return
				m_ptr == a_rhs.m_ptr &&
				m_begin == a_rhs.m_begin &&
				m_end == a_rhs.m_end &&
				m_head == a_rhs.m_head &&
				m_tail == a_rhs.m_tail &&
				m_has_looped == a_rhs.m_has_looped;
		}
	private:
		inline constexpr auto increment() -> void {
			if (m_ptr == m_tail) {
				m_ptr = m_head;
				m_has_looped = true;
			}
			else ++m_ptr;

			if (m_ptr == m_end)
				m_ptr = m_begin;
		}

		inline constexpr auto decrement() -> void{
			if (m_ptr == m_head) {
				m_ptr = m_tail;
				m_has_looped = true;
			}
			else --m_ptr;

			if (m_ptr == m_begin - 1)
				m_ptr = m_end - 1;
		}
	};

	template<typename Circulator>
	class reverse_circulator {
	public:
		using value_type = typename Circulator::value_type;
		using size_type = typename Circulator::size_type;
		using reference = typename Circulator::reference;
		using const_reference = typename Circulator::const_reference;
		using pointer = typename Circulator::pointer;
		using const_pointer = typename Circulator::const_pointer;
	private:
		Circulator m_rci;
	public:
		MYL_NO_DISCARD reverse_circulator() noexcept = default;
		MYL_NO_DISCARD constexpr reverse_circulator(pointer a_ptr, pointer a_begin, pointer a_end, pointer a_head, pointer a_tail, bool a_has_looped)
			: m_rci(a_ptr, a_begin, a_end, a_head, a_tail, a_has_looped) {}

		constexpr ~reverse_circulator() noexcept {}

		MYL_NO_DISCARD constexpr auto operator*() -> reference { return m_rci.operator*(); }
		MYL_NO_DISCARD constexpr auto operator*() const -> const_reference { return m_rci.operator*(); }
		MYL_NO_DISCARD constexpr auto operator->() -> pointer { return m_rci.operator->(); }

		constexpr auto operator++() -> reverse_circulator& { --m_rci; return *this; }
		constexpr auto operator--() -> reverse_circulator& { ++m_rci; return *this; }
		constexpr auto operator++(int) -> reverse_circulator& { reverse_circulator temp(*this); --m_rci(); return temp; }
		constexpr auto operator--(int) -> reverse_circulator& { reverse_circulator temp(*this); ++m_rci(); return temp; }

		MYL_NO_DISCARD constexpr auto operator==(const reverse_circulator& a_rhs) const -> bool { return m_rci == a_rhs.m_rci; }
	};
}