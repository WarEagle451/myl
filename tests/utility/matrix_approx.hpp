#pragma once
#include <myl/algorithm.hpp>
#include <myl/math/mat_common.hpp>

#include <catch2/catch_all.hpp>

template<myl::usize C, myl::usize R, typename T>
MYL_NO_DISCARD constexpr auto approx_fmat(const myl::mat<C, R, T>& l, const myl::mat<C, R, T>& r) -> bool {
	for (myl::usize col = 0; col != C; ++col)
		for (myl::usize row = 0; row != R; ++row)
			if (!myl::approx(l[col][row], r[col][row])) {
				UNSCOPED_INFO("[C,R]: [" << col << "," << row << "] | left: " << l[col][row] << " | right: " << r[col][row]);
				return false;
			}
	return true;
}
