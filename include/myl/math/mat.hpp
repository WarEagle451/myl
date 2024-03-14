#pragma once
#include <myl/definitions.hpp>

/// MYTODO: mat.hpp
/// - If possible multiplying a matrix by a row vector

// The following functions are implemented when possible in their respective mat file due to partial function specialization not being allowed;
// - determinant
// - inverse

namespace myl {
    template<usize Columns, usize Rows, typename T> struct mat;

    template<usize C, usize R, typename T>
    MYL_NO_DISCARD constexpr auto transpose(const mat<C, R, T>& m) -> typename mat<C, R, T>::transpose_type {
        typename mat<C, R, T>::transpose_type transposed{};
        for (usize c = 0; c != C; ++c) // Tranverse columns
            for (usize r = 0; r != R; ++r) // Transverse rows
                transposed[r][c] = m[c][r];
        return transposed;
    }

    template<usize C, usize R, typename T>
    constexpr auto set_column(mat<C, R, T>& m, usize column, const typename mat<C, R, T>::column_type& value) -> void {
        m[column] = value;
    }

    template<usize R, typename T>
    constexpr auto set_row(mat<2, R, T>& m, usize row, const typename mat<2, R, T>::row_type& value) -> void {
        MYL_ASSERT(row < R);
        m[0][row] = value[0];
        m[1][row] = value[1];
    }

    template<usize R, typename T>
    constexpr auto set_row(mat<3, R, T>& m, usize row, const typename mat<3, R, T>::row_type& value) -> void {
        MYL_ASSERT(row < R);
        m[0][row] = value[0];
        m[1][row] = value[1];
        m[2][row] = value[2];
    }

    template<usize R, typename T>
    constexpr auto set_row(mat<4, R, T>& m, usize row, const typename mat<4, R, T>::row_type& value) -> void {
        MYL_ASSERT(row < R);
        m[0][row] = value[0];
        m[1][row] = value[1];
        m[2][row] = value[2];
        m[3][row] = value[3];
    }
}
