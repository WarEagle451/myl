#pragma once
#include <myl/defines.hpp>

namespace myl {
	//@brief Column major to follow mathmatical conventions
	template<usize Columns, usize Rows, typename Type> struct mat;

	template<usize C, usize R, typename T> MYL_NO_DISCARD constexpr auto determinant(const mat<C, R, T>&) -> T;
	template<usize C, usize R, typename T> MYL_NO_DISCARD constexpr auto inverse(const mat<C, R, T>&) -> T;

	template<usize C, usize R, typename T>
	MYL_NO_DISCARD constexpr auto transpose(const mat<C, R, T>& m) -> typename mat<C, R, T>::transpose_type {
		typename mat<C, R, T>::transpose_type transposed{};
		for (usize c = 0; c != C; ++c) // Tranverse columns
			for (usize r = 0; r != R; ++r) // Transverse rows
				transposed[r][c] = m[c][r];
		return transposed;
	}

	template<usize C, usize R, typename T>
	constexpr auto set_column(const mat<C, R, T>& m, usize i, typename mat<C, R, T>::col_type column) -> void {
		m[i] = column;
	}

	template<usize C, usize R, typename T> constexpr auto set_row(mat<C, R, T>&, usize, const typename mat<C, R, T>::row_type&) -> void;
}