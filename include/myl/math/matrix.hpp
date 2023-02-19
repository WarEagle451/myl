#pragma once
#include <myl/defines.hpp>

/// MYTodo: Matrix conversion constructors

namespace myl {
	//@brief Column major to follow mathmatical conventions
	template<usize Rows, usize Columns, typename Type> struct mat;

	template<usize R, usize C, typename T> MYL_NO_DISCARD constexpr auto determinant(const mat<R, C, T>&) -> T;
	template<usize R, usize C, typename T> MYL_NO_DISCARD constexpr auto inverse(const mat<R, C, T>&) -> T;

	template<usize R, usize C, typename T>
	MYL_NO_DISCARD constexpr auto transpose(const mat<R, C, T>& m) -> typename mat<R, C, T>::transpose_type {
		typename mat<R, C, T>::transpose_type transposed{};
		for (usize c = 0; c != C; ++c) // Tranverse columns
			for (usize r = 0; r != R; ++r) // Transverse rows
				transposed[r][c] = m[c][r];
		return transposed;
	}
}