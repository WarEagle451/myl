#pragma once
#include <myl/defines.hpp>

#include <iterator>

namespace myl {
	template<typename Container>
	class circulator {
	public:
		using iterator_concept	= std::random_access_iterator_tag;
		using iterator_category = std::random_access_iterator_tag;
		using value_type		= typename Container::value_type;
		using difference_type	= typename Container::difference_type;
		using pointer			= value_type*;
		using reference			= value_type&;
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

		constexpr ~circulator() noexcept = default;

		MYL_NO_DISCARD constexpr auto operator*() -> reference { return *m_ptr; }
		MYL_NO_DISCARD constexpr auto operator*() const -> const reference { return *m_ptr; }
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
}