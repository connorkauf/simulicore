/*
 * Copyright 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// this file inc
#include "cla3p/bulk/csc.hpp"

// system
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>

// 3rd

// cla3p
#include "cla3p/error/exceptions.hpp"
#include "cla3p/support/utils.hpp"
#include "cla3p/proxies/blas_proxy.hpp"
#include "cla3p/checks/basic_checks.hpp"
#include "cla3p/support/utils.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace csc {
/*-------------------------------------------------*/
template <typename T_Int>
void roll(uint_t n, T_Int *colptr)
{
	for(uint_t j = 0; j < n; j++) {
		colptr[j+1] += colptr[j];
	} // j
}
/*-------------------------------------------------*/
template void roll(uint_t, int_t*);
template void roll(uint_t, uint_t*);
/*-------------------------------------------------*/
template <typename T_Int>
void unroll(uint_t n, T_Int *colptr)
{
	if(!n) return;

	for(T_Int j = n-1; j > 0; j--) {
		colptr[j] = colptr[j-1];
	} // j
	colptr[0] = 0;
}
/*-------------------------------------------------*/
template void unroll<int_t>(uint_t, int_t*);
template void unroll<uint_t>(uint_t, uint_t*);
/*-------------------------------------------------*/
template <typename T_Int>
uint_t maxrlen(uint_t n, const T_Int *colptr)
{
	T_Int ret = 0;

	for(uint_t j = 0; j < n; j++) {
		ret = std::max(ret, colptr[j+1] - colptr[j]);
	} // j

	if(ret < 0) {
		throw err::NoConsistency("Negative length found in column pointer array");
	}

	return static_cast<uint_t>(ret);
}
/*-------------------------------------------------*/
template uint_t maxrlen(uint_t, const int_t*);
template uint_t maxrlen(uint_t, const uint_t*);
/*-------------------------------------------------*/
template <typename T_Int>
void check(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const T_Int *colptr, const T_Int *rowidx)
{
	Property prop(ptype, uplo);

	if(colptr[0]) {
		throw err::NoConsistency("Column pointer array must contain a zero at position 0");
	}

	std::vector<bool> mark(m, false);

	for(T_Int j = 0; j < static_cast<T_Int>(n); j++) {

		T_Int ibgn = colptr[j];
		T_Int iend = colptr[j+1];

		if(iend < ibgn) {
			throw err::NoConsistency("Column pointer array must be in ascending order");
		}

		for(T_Int irow = ibgn; irow < iend; irow++) {

			T_Int i = rowidx[irow];

			if(i < static_cast<T_Int>(0)) {
				throw err::OutOfBounds("Negative row index detected: " + std::to_string(i));
			}

			if(i >= static_cast<T_Int>(m)) {
				throw err::OutOfBounds("Row index " + std::to_string(i) + " is greater than number of rows " + std::to_string(m));
			}

			if(prop.isLower() && i < j) {
				throw err::NoConsistency("Found coordinate " + coordToString(i,j) + " in upper part");
			}

			if(prop.isUpper() && i > j) {
				throw err::NoConsistency("Found coordinate " + coordToString(i,j) + " in lower part");
			}

			// TODO: perhaps check skew diagonals for values

			if(irow > ibgn) {
				T_Int i_prev = rowidx[irow - 1];
				if(i < i_prev) {
					throw err::NoConsistency("Column " + std::to_string(j) + " is not sorted");
				}
			}

			if(mark[i]) {
				throw err::NoConsistency("Duplicate entry detected at " + coordToString(i,j));
			}

			mark[i] = true;

		} // irow


		for(T_Int irow = ibgn; irow < iend; irow++) {
			mark[rowidx[irow]] = false;
		} // irow

	} // j
}
/*-------------------------------------------------*/
template void check(prop_t, uplo_t, uint_t, uint_t, const int_t*, const int_t*);
template void check(prop_t, uplo_t, uint_t, uint_t, const uint_t*, const uint_t*);
/*-------------------------------------------------*/
template <typename T_Int>
void sort(uint_t n, const T_Int *colptr, T_Int *rowidx)
{
	for(uint_t j = 0; j < n; j++) {

		T_Int ibgn = colptr[j];
		T_Int iend = colptr[j+1];
		T_Int ilen = iend - ibgn;

		if(ilen > 0) {
			std::sort(rowidx + ibgn, rowidx + iend);
		} // ilen

	} // j
}
/*-------------------------------------------------*/
template void sort(uint_t, const int_t*, int_t*);
template void sort(uint_t, const uint_t*, uint_t*);
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
class RowValuePair {
	public:
		RowValuePair() : i(0), v(0) {}
		~RowValuePair() = default;
		RowValuePair(const RowValuePair<T_Int,T_Scalar>& r) : i(r.i), v(r.v) {} // Removes ABI warning

		T_Int    i;
		T_Scalar v;

		bool operator<(const RowValuePair<T_Int,T_Scalar>& other)
		{
			return (i < other.i);
		}
};
/*-------------------------------------------------*/
// 
// TODO: implement without extra storage
//
template <typename T_Int, typename T_Scalar>
void sort(uint_t n, const T_Int *colptr, T_Int *rowidx, T_Scalar *values)
{
	if(!n) return;

	uint_t milen = maxrlen(n, colptr);

	if(!milen) return;

	std::vector<RowValuePair<T_Int,T_Scalar>> row_pairs;
	row_pairs.reserve(milen);

	for(uint_t j = 0; j < n; j++) {

		T_Int ibgn = colptr[j];
		T_Int iend = colptr[j+1];
		T_Int ilen = iend - ibgn;

		if(ilen < 2) continue;

		row_pairs.resize(ilen);

		for(T_Int irow = ibgn; irow < iend; irow++) {
			row_pairs[irow - ibgn].i = rowidx[irow];
			row_pairs[irow - ibgn].v = values[irow];
		} // irow

		std::sort(row_pairs.begin(), row_pairs.end());

		for(T_Int irow = ibgn; irow < iend; irow++) {
			rowidx[irow] = row_pairs[irow - ibgn].i;
			values[irow] = row_pairs[irow - ibgn].v;
		} // irow

	} // j
}
/*-------------------------------------------------*/
template void sort(uint_t, const int_t *, int_t *, real_t    *);
template void sort(uint_t, const int_t *, int_t *, real4_t   *);
template void sort(uint_t, const int_t *, int_t *, complex_t *);
template void sort(uint_t, const int_t *, int_t *, complex8_t*);
template void sort(uint_t, const uint_t*, uint_t*, real_t    *);
template void sort(uint_t, const uint_t*, uint_t*, real4_t   *);
template void sort(uint_t, const uint_t*, uint_t*, complex_t *);
template void sort(uint_t, const uint_t*, uint_t*, complex8_t*);
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
std::string print_to_string(uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values, uint_t nsd)
{
	if(!n) return "";

	T_Int maxRowIdx = 0;
	for(T_Int k = 0; k < colptr[n]; k++) 
		maxRowIdx = std::max(maxRowIdx, rowidx[k]);

	ListPrinter listPrinter(nsd, maxRowIdx, n, colptr[n]);

	std::string ret = listPrinter.header();
	std::string entry;

	for(T_Int j = 0, cnt = 0; j < static_cast<T_Int>(n); j++) {

		T_Int ibgn = colptr[j];
		T_Int iend = colptr[j+1];

		for(T_Int irow = ibgn; irow < iend; irow++) {

			T_Int    i = rowidx[irow];
			T_Scalar v = values[irow];

			entry = listPrinter.tuple(cnt++, i, j, v);
			ret.append(entry);

		} // irow

	} // j

	return ret;
}
/*-------------------------------------------------*/
template std::string print_to_string(uint_t n, const int_t *, const int_t *, const real_t    *, uint_t);
template std::string print_to_string(uint_t n, const int_t *, const int_t *, const real4_t   *, uint_t);
template std::string print_to_string(uint_t n, const int_t *, const int_t *, const complex_t *, uint_t);
template std::string print_to_string(uint_t n, const int_t *, const int_t *, const complex8_t*, uint_t);
template std::string print_to_string(uint_t n, const uint_t*, const uint_t*, const real_t    *, uint_t);
template std::string print_to_string(uint_t n, const uint_t*, const uint_t*, const real4_t   *, uint_t);
template std::string print_to_string(uint_t n, const uint_t*, const uint_t*, const complex_t *, uint_t);
template std::string print_to_string(uint_t n, const uint_t*, const uint_t*, const complex8_t*, uint_t);
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
void print(uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values, uint_t nsd)
{
	std::string tmp = print_to_string(n, colptr, rowidx, values, nsd);
	std::cout << tmp;
}
/*-------------------------------------------------*/
template void print(uint_t, const int_t *, const int_t *, const real_t    *, uint_t);
template void print(uint_t, const int_t *, const int_t *, const real4_t   *, uint_t);
template void print(uint_t, const int_t *, const int_t *, const complex_t *, uint_t);
template void print(uint_t, const int_t *, const int_t *, const complex8_t*, uint_t);
template void print(uint_t, const uint_t*, const uint_t*, const real_t    *, uint_t);
template void print(uint_t, const uint_t*, const uint_t*, const real4_t   *, uint_t);
template void print(uint_t, const uint_t*, const uint_t*, const complex_t *, uint_t);
template void print(uint_t, const uint_t*, const uint_t*, const complex8_t*, uint_t);
/*-------------------------------------------------*/
template <typename T_Int>
static void transpose_colptr(uint_t m, uint_t n, const T_Int *colptr, const T_Int *rowidx, T_Int *colptr_out)
{
	for(uint_t j = 0; j < m+1; j++) {
		colptr_out[j] = 0;
	} // j

	for(uint_t j = 0; j < n; j++) {

		T_Int ibgn = colptr[j];
		T_Int iend = colptr[j+1];

		for(T_Int irow = ibgn; irow < iend; irow++) {
			colptr_out[rowidx[irow] + 1]++;
		} // irow

	} // j

	roll(m, colptr_out);
}
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
static void hybrid_transpose_tmpl(uint_t m, uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values, 
		T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out, T_Scalar coeff, bool conjop) 
{
	transpose_colptr(m, n, colptr, rowidx, colptr_out);

	for(uint_t j = 0; j < n; j++) {

		T_Int ibgn = colptr[j];
		T_Int iend = colptr[j+1];

		for(T_Int irow = ibgn; irow < iend; irow++) {

			T_Int    i = rowidx[irow];
			T_Scalar v = values[irow];

			rowidx_out[colptr_out[i]] = j;
			values_out[colptr_out[i]] = coeff * (conjop ? arith::conj(v) : v);

			colptr_out[i]++;

		} // irow

	} // j

	unroll(m, colptr_out);
}
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
void transpose(uint_t m, uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values,
		T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out, T_Scalar coeff)
{
	hybrid_transpose_tmpl(m, n, colptr, rowidx, values, colptr_out, rowidx_out, values_out, coeff, false);
}
/*-------------------------------------------------*/
template void transpose(uint_t, uint_t, const int_t *, const int_t *, const real_t    *, int_t *, int_t *, real_t    *, real_t    );
template void transpose(uint_t, uint_t, const int_t *, const int_t *, const real4_t   *, int_t *, int_t *, real4_t   *, real4_t   );
template void transpose(uint_t, uint_t, const int_t *, const int_t *, const complex_t *, int_t *, int_t *, complex_t *, complex_t );
template void transpose(uint_t, uint_t, const int_t *, const int_t *, const complex8_t*, int_t *, int_t *, complex8_t*, complex8_t);
template void transpose(uint_t, uint_t, const uint_t*, const uint_t*, const real_t    *, uint_t*, uint_t*, real_t    *, real_t    );
template void transpose(uint_t, uint_t, const uint_t*, const uint_t*, const real4_t   *, uint_t*, uint_t*, real4_t   *, real4_t   );
template void transpose(uint_t, uint_t, const uint_t*, const uint_t*, const complex_t *, uint_t*, uint_t*, complex_t *, complex_t );
template void transpose(uint_t, uint_t, const uint_t*, const uint_t*, const complex8_t*, uint_t*, uint_t*, complex8_t*, complex8_t);
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
void conjugate_transpose(uint_t m, uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values,
		T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out, T_Scalar coeff)
{
	hybrid_transpose_tmpl(m, n, colptr, rowidx, values, colptr_out, rowidx_out, values_out, coeff, true);
}
/*-------------------------------------------------*/
template void conjugate_transpose(uint_t, uint_t, const int_t *, const int_t *, const real_t    *, int_t *, int_t *, real_t    *, real_t    );
template void conjugate_transpose(uint_t, uint_t, const int_t *, const int_t *, const real4_t   *, int_t *, int_t *, real4_t   *, real4_t   );
template void conjugate_transpose(uint_t, uint_t, const int_t *, const int_t *, const complex_t *, int_t *, int_t *, complex_t *, complex_t );
template void conjugate_transpose(uint_t, uint_t, const int_t *, const int_t *, const complex8_t*, int_t *, int_t *, complex8_t*, complex8_t);
template void conjugate_transpose(uint_t, uint_t, const uint_t*, const uint_t*, const real_t    *, uint_t*, uint_t*, real_t    *, real_t    );
template void conjugate_transpose(uint_t, uint_t, const uint_t*, const uint_t*, const real4_t   *, uint_t*, uint_t*, real4_t   *, real4_t   );
template void conjugate_transpose(uint_t, uint_t, const uint_t*, const uint_t*, const complex_t *, uint_t*, uint_t*, complex_t *, complex_t );
template void conjugate_transpose(uint_t, uint_t, const uint_t*, const uint_t*, const complex8_t*, uint_t*, uint_t*, complex8_t*, complex8_t);
/*-------------------------------------------------*/
template <typename T_Int>
void uplo2ge_colptr(uplo_t uplo, uint_t n, const T_Int *colptr, const T_Int *rowidx, T_Int *colptr_out)
{
	if(uplo == uplo_t::Full) {
		std::copy(colptr, colptr + (n+1), colptr_out);
		return;
	}

	std::fill(colptr_out, colptr_out + (n+1), 0);

	for(T_Int j = 0; j < static_cast<T_Int>(n); j++) {

		T_Int ibgn = colptr[j];
		T_Int iend = colptr[j+1];

		for(T_Int irow = ibgn; irow < iend; irow++) {

			T_Int i = rowidx[irow];

			if(i == j) {
				colptr_out[j+1]++;
			} else if(uplo == uplo_t::Lower && i > j) {
				colptr_out[j+1]++;
				colptr_out[i+1]++;
			} else if(uplo == uplo_t::Upper && i < j) {
				colptr_out[j+1]++;
				colptr_out[i+1]++;
			} // lower/upper

		} // irow

	} // j

	roll(n, colptr_out);
}
/*-------------------------------------------------*/
template void uplo2ge_colptr(uplo_t, uint_t, const int_t*, const int_t*, int_t*);
template void uplo2ge_colptr(uplo_t, uint_t, const uint_t*, const uint_t*, uint_t*);
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
static inline void append_to_selected_part(uint_t i, uint_t j, T_Scalar v, T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out, bool conjop)
{
	// original part
	rowidx_out[colptr_out[j]] = i;
	values_out[colptr_out[j]] = v;
	colptr_out[j]++;

	// opposite part
	if(i != j) {
		rowidx_out[colptr_out[i]] = j;
		values_out[colptr_out[i]] = (conjop ? arith::conj(v) : v);
		colptr_out[i]++;
	} // strict part
}
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
void xx2ge(uplo_t uplo, uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values, 
		T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out, bool conjop) 
{
	uplo2ge_colptr(uplo, n, colptr, rowidx, colptr_out);

	for(T_Int j = 0; j < static_cast<T_Int>(n); j++) {

		T_Int ibgn = colptr[j];
		T_Int iend = colptr[j+1];

		for(T_Int irow = ibgn; irow < iend; irow++) {

			T_Int    i = rowidx[irow];
			T_Scalar v = values[irow];

			if(uplo == uplo_t::Lower && i >= j) {
				append_to_selected_part(i, j, v, colptr_out, rowidx_out, values_out, conjop);
			} else if(uplo == uplo_t::Upper && i <= j) {
				append_to_selected_part(i, j, v, colptr_out, rowidx_out, values_out, conjop);
			} // lower/upper

		} // irow

	} // j

	unroll(n, colptr_out);
}
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
void sy2ge(uplo_t uplo, uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values,
    T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out)
{
	xx2ge(uplo, n, colptr, rowidx, values, colptr_out, rowidx_out, values_out, false);
}
/*-------------------------------------------------*/
template void sy2ge(uplo_t, uint_t, const int_t *, const int_t *, const real_t    *, int_t *, int_t *, real_t    *);
template void sy2ge(uplo_t, uint_t, const int_t *, const int_t *, const real4_t   *, int_t *, int_t *, real4_t   *);
template void sy2ge(uplo_t, uint_t, const int_t *, const int_t *, const complex_t *, int_t *, int_t *, complex_t *);
template void sy2ge(uplo_t, uint_t, const int_t *, const int_t *, const complex8_t*, int_t *, int_t *, complex8_t*);
template void sy2ge(uplo_t, uint_t, const uint_t*, const uint_t*, const real_t    *, uint_t*, uint_t*, real_t    *);
template void sy2ge(uplo_t, uint_t, const uint_t*, const uint_t*, const real4_t   *, uint_t*, uint_t*, real4_t   *);
template void sy2ge(uplo_t, uint_t, const uint_t*, const uint_t*, const complex_t *, uint_t*, uint_t*, complex_t *);
template void sy2ge(uplo_t, uint_t, const uint_t*, const uint_t*, const complex8_t*, uint_t*, uint_t*, complex8_t*);
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
void he2ge(uplo_t uplo, uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values,
    T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out)
{
	xx2ge(uplo, n, colptr, rowidx, values, colptr_out, rowidx_out, values_out, true);
}
/*-------------------------------------------------*/
template void he2ge(uplo_t, uint_t, const int_t *, const int_t *, const real_t    *, int_t *, int_t *, real_t    *);
template void he2ge(uplo_t, uint_t, const int_t *, const int_t *, const real4_t   *, int_t *, int_t *, real4_t   *);
template void he2ge(uplo_t, uint_t, const int_t *, const int_t *, const complex_t *, int_t *, int_t *, complex_t *);
template void he2ge(uplo_t, uint_t, const int_t *, const int_t *, const complex8_t*, int_t *, int_t *, complex8_t*);
template void he2ge(uplo_t, uint_t, const uint_t*, const uint_t*, const real_t    *, uint_t*, uint_t*, real_t    *);
template void he2ge(uplo_t, uint_t, const uint_t*, const uint_t*, const real4_t   *, uint_t*, uint_t*, real4_t   *);
template void he2ge(uplo_t, uint_t, const uint_t*, const uint_t*, const complex_t *, uint_t*, uint_t*, complex_t *);
template void he2ge(uplo_t, uint_t, const uint_t*, const uint_t*, const complex8_t*, uint_t*, uint_t*, complex8_t*);
/*-------------------------------------------------*/
template <typename T_Scalar>
static inline void apply_op(T_Scalar& v, const T_Scalar& u, dup_t op)
{
	/**/ if(op == dup_t::Sum ) v += u;
	else if(op == dup_t::Prod) v *= u;
	else if(op == dup_t::Amax) v = std::max(std::abs(v), std::abs(u));
	else if(op == dup_t::Amin) v = std::max(std::abs(v), std::abs(u));
}
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
void remove_duplicates(uint_t n, T_Int *colptr, T_Int *rowidx, T_Scalar *values, dup_t op)
{
	for(uint_t j = 0; j < n; j++) {

		T_Int ibgn = colptr[j];
		T_Int iend = colptr[j+1];
		T_Int ilen = iend - ibgn;

		colptr[j] = (j > 0 ? colptr[j-1] : 0);

		if(!ilen) continue;

		T_Int iref = rowidx[ibgn];

		rowidx[colptr[j]] = rowidx[ibgn];
		values[colptr[j]] = values[ibgn];
		colptr[j]++;

		for(T_Int irow = ibgn + 1; irow < iend; irow++) {

			T_Int    i = rowidx[irow];
			T_Scalar v = values[irow];

			if(i == iref) {
				apply_op<T_Scalar>(values[colptr[j]-1], v, op);
			} else {
				rowidx[colptr[j]] = i;
				values[colptr[j]] = v;
				colptr[j]++;
				iref = i;
			} // dup check

		} // irow

	} // j

	colptr[n] = colptr[n-1];

	unroll(n, colptr);
}
/*-------------------------------------------------*/
template void remove_duplicates(uint_t, int_t *, int_t *, real_t    *, dup_t);
template void remove_duplicates(uint_t, int_t *, int_t *, real4_t   *, dup_t);
template void remove_duplicates(uint_t, int_t *, int_t *, complex_t *, dup_t);
template void remove_duplicates(uint_t, int_t *, int_t *, complex8_t*, dup_t);
template void remove_duplicates(uint_t, uint_t*, uint_t*, real_t    *, dup_t);
template void remove_duplicates(uint_t, uint_t*, uint_t*, real4_t   *, dup_t);
template void remove_duplicates(uint_t, uint_t*, uint_t*, complex_t *, dup_t);
template void remove_duplicates(uint_t, uint_t*, uint_t*, complex8_t*, dup_t);
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
typename TypeTraits<T_Scalar>::real_type
norm_one(prop_t ptype, uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values)
{
	using T_RScalar = typename TypeTraits<T_Scalar>::real_type;

  if(!n) return 0;

	std::vector<T_RScalar> col_norms(n, 0);

	for(T_Int j = 0; j < static_cast<T_Int>(n); j++) {

		T_Int ibgn = colptr[j];
		T_Int iend = colptr[j+1];

		for(T_Int irow = ibgn; irow < iend; irow++) {

			T_Int i = rowidx[irow];
			T_RScalar av = std::abs(values[irow]);

			col_norms[j] += av;

			if(ptype == prop_t::Symmetric || ptype == prop_t::Hermitian || ptype == prop_t::Skew) {
				if(i != j) {
					col_norms[i] += av;
				} // off diag
			} // ptype

		} // irow

	} // j

	return col_norms[blas::iamax(n,col_norms.data(),1)];
}
/*-------------------------------------------------*/
template real_t  norm_one(prop_t, uint_t, const int_t *, const int_t *, const real_t    *);
template real4_t norm_one(prop_t, uint_t, const int_t *, const int_t *, const real4_t   *);
template real_t  norm_one(prop_t, uint_t, const int_t *, const int_t *, const complex_t *);
template real4_t norm_one(prop_t, uint_t, const int_t *, const int_t *, const complex8_t*);
template real_t  norm_one(prop_t, uint_t, const uint_t*, const uint_t*, const real_t    *);
template real4_t norm_one(prop_t, uint_t, const uint_t*, const uint_t*, const real4_t   *);
template real_t  norm_one(prop_t, uint_t, const uint_t*, const uint_t*, const complex_t *);
template real4_t norm_one(prop_t, uint_t, const uint_t*, const uint_t*, const complex8_t*);
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
typename TypeTraits<T_Scalar>::real_type
norm_inf(prop_t ptype, uint_t m, uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values)
{
	using T_RScalar = typename TypeTraits<T_Scalar>::real_type;

  if(!m || !n) return 0;

	std::vector<T_RScalar> row_norms(m, 0);

	for(T_Int j = 0; j < static_cast<T_Int>(n); j++) {

		T_Int ibgn = colptr[j];
		T_Int iend = colptr[j+1];

		for(T_Int irow = ibgn; irow < iend; irow++) {

			T_Int i = rowidx[irow];
			T_RScalar av = std::abs(values[irow]);

			row_norms[i] += av;

			if(ptype == prop_t::Symmetric || ptype == prop_t::Hermitian || ptype == prop_t::Skew) {
				if(i != j) {
					row_norms[j] += av;
				} // off diag
			} // ptype

		} // irow

	} // j

	return row_norms[blas::iamax(m,row_norms.data(),1)];
}
/*-------------------------------------------------*/
template real_t  norm_inf(prop_t, uint_t, uint_t, const int_t *, const int_t *, const real_t    *);
template real4_t norm_inf(prop_t, uint_t, uint_t, const int_t *, const int_t *, const real4_t   *);
template real_t  norm_inf(prop_t, uint_t, uint_t, const int_t *, const int_t *, const complex_t *);
template real4_t norm_inf(prop_t, uint_t, uint_t, const int_t *, const int_t *, const complex8_t*);
template real_t  norm_inf(prop_t, uint_t, uint_t, const uint_t*, const uint_t*, const real_t    *);
template real4_t norm_inf(prop_t, uint_t, uint_t, const uint_t*, const uint_t*, const real4_t   *);
template real_t  norm_inf(prop_t, uint_t, uint_t, const uint_t*, const uint_t*, const complex_t *);
template real4_t norm_inf(prop_t, uint_t, uint_t, const uint_t*, const uint_t*, const complex8_t*);
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
typename TypeTraits<T_Scalar>::real_type
norm_max(uint_t n, const T_Int *colptr, const T_Scalar *values)
{
  if(!n) return 0;

	T_Scalar vamax = values[blas::iamax(colptr[n], values, 1)];

	return std::abs(vamax);
}
/*-------------------------------------------------*/
template real_t  norm_max(uint_t, const int_t *, const real_t    *);
template real4_t norm_max(uint_t, const int_t *, const real4_t   *);
template real_t  norm_max(uint_t, const int_t *, const complex_t *);
template real4_t norm_max(uint_t, const int_t *, const complex8_t*);
template real_t  norm_max(uint_t, const uint_t*, const real_t    *);
template real4_t norm_max(uint_t, const uint_t*, const real4_t   *);
template real_t  norm_max(uint_t, const uint_t*, const complex_t *);
template real4_t norm_max(uint_t, const uint_t*, const complex8_t*);
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
typename TypeTraits<T_Scalar>::real_type
norm_fro(prop_t ptype, uint_t n, const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values)
{
	using T_RScalar = typename TypeTraits<T_Scalar>::real_type;

  if(!n) return 0;

	T_RScalar ret = 0;

	for(T_Int j = 0; j < static_cast<T_Int>(n); j++) {

		T_Int ibgn = colptr[j];
		T_Int iend = colptr[j+1];

		for(T_Int irow = ibgn; irow < iend; irow++) {

			T_Int i = rowidx[irow];
			T_RScalar av = std::abs(values[irow]);
			T_RScalar av2 = av * av;

			if(ptype == prop_t::General || ptype == prop_t::Triangular) {

				ret += av2;

			} else if(ptype == prop_t::Symmetric || ptype == prop_t::Hermitian || ptype == prop_t::Skew) {

				ret += (i == j ? av2 : 2 * av2);

			} // ptype


		} // irow

	} // j

	return std::sqrt(ret);
}
/*-------------------------------------------------*/
template real_t  norm_fro(prop_t, uint_t, const int_t *, const int_t *, const real_t    *);
template real4_t norm_fro(prop_t, uint_t, const int_t *, const int_t *, const real4_t   *);
template real_t  norm_fro(prop_t, uint_t, const int_t *, const int_t *, const complex_t *);
template real4_t norm_fro(prop_t, uint_t, const int_t *, const int_t *, const complex8_t*);
template real_t  norm_fro(prop_t, uint_t, const uint_t*, const uint_t*, const real_t    *);
template real4_t norm_fro(prop_t, uint_t, const uint_t*, const uint_t*, const real4_t   *);
template real_t  norm_fro(prop_t, uint_t, const uint_t*, const uint_t*, const complex_t *);
template real4_t norm_fro(prop_t, uint_t, const uint_t*, const uint_t*, const complex8_t*);
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
static void permute_ge_both(uint_t /*m*/, uint_t n,
		const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values,
		T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out, const int_t *P, const int_t *Q)
{
	colptr_out[0] = 0;
	for(uint_t j = 0; j < n; j++) {
		colptr_out[j + 1] = colptr[Q[j]+1] - colptr[Q[j]];
	} // j

	roll(n, colptr_out);

	for(uint_t j = 0; j < n; j++) {
		for(T_Int irow = colptr[Q[j]]; irow < colptr[Q[j]+1]; irow++) {
			rowidx_out[colptr_out[j]] = P[rowidx[irow]];
			values_out[colptr_out[j]] = values[irow];
			colptr_out[j]++;
		} // irow
	} // j
	
	unroll(n, colptr_out);

	sort(n, colptr_out, rowidx_out, values_out);
}
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
static void permute_ge_left(uint_t /*m*/, uint_t n,
		const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values,
		T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out, const int_t *P)
{
	std::copy(colptr, colptr + n + 1, colptr_out);

	for(uint_t j = 0; j < n; j++) {
		for(T_Int irow = colptr[j]; irow < colptr[j+1]; irow++) {
			rowidx_out[colptr_out[j]] = P[rowidx[irow]];
			values_out[colptr_out[j]] = values[irow];
			colptr_out[j]++;
		} // irow
	} // j
	
	unroll(n, colptr_out);

	sort(n, colptr_out, rowidx_out, values_out);
}
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
static void permute_ge_right(uint_t /*m*/, uint_t n,
		const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values,
		T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out, const int_t *Q)
{
	colptr_out[0] = 0;
	for(uint_t j = 0; j < n; j++) {
		colptr_out[j + 1] = colptr[Q[j] + 1] - colptr[Q[j]];
	} // j

	roll(n, colptr_out);

	for(uint_t j = 0; j < n; j++) {
		std::copy(rowidx + colptr[Q[j]], rowidx + colptr[Q[j] + 1], rowidx_out + colptr_out[j]);
		std::copy(values + colptr[Q[j]], values + colptr[Q[j] + 1], values_out + colptr_out[j]);
	} // j
}
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
void permute_xx_mirror(prop_t ptype, uplo_t uplo, uint_t n,
		const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values,
		T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out, const int_t *P)
{
	T_Int Pi;
	T_Int Pj;

	for(uint_t j = 0; j < n + 1; j++) 
		colptr_out[j] = 0;

	for(uint_t j = 0; j < n; j++) {
		for(T_Int irow = colptr[j]; irow < colptr[j+1]; irow++) {
			Pi = P[rowidx[irow]];
			Pj = P[j];
			if(uplo == uplo_t::Upper && Pj < Pi) 
				colptr_out[Pi+1]++;
			else if(uplo == uplo_t::Lower && Pj > Pi) 
				colptr_out[Pi+1]++;
			else
				colptr_out[Pj+1]++;
		} // irow
	} // j

	roll(n, colptr_out);

	for(uint_t j = 0; j < n; j++) {
		for(T_Int irow = colptr[j]; irow < colptr[j+1]; irow++) {
			Pi = P[rowidx[irow]];
			Pj = P[j];
			if(uplo == uplo_t::Upper && Pj < Pi) {
				rowidx_out[colptr_out[Pi]] = Pj;
				values_out[colptr_out[Pi]] = opposite_element(values[irow],ptype);
				colptr_out[Pi]++;
			} else if(uplo == uplo_t::Lower && Pj > Pi) {
				rowidx_out[colptr_out[Pi]] = Pj;
				values_out[colptr_out[Pi]] = opposite_element(values[irow],ptype);
				colptr_out[Pi]++;
			} else {
				rowidx_out[colptr_out[Pj]] = Pi;
				values_out[colptr_out[Pj]] = values[irow];
				colptr_out[Pj]++;
			}
		} // irow
	} // j
	
	unroll(n, colptr_out);

	sort(n, colptr_out, rowidx_out, values_out);
}
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
void permute(prop_t ptype, uplo_t uplo, uint_t m, uint_t n,
		const T_Int *colptr, const T_Int *rowidx, const T_Scalar *values,
		T_Int *colptr_out, T_Int *rowidx_out, T_Scalar *values_out, const int_t *P, const int_t *Q)
{
	if(!m || !n) return;

	Property prop(ptype, uplo);

	if(prop.isSquare()) {
		square_check(m, n);
	}

	if(prop.isGeneral()) {

		if(P && Q) {

			permute_ge_both(m, n, colptr, rowidx, values, colptr_out, rowidx_out, values_out, P, Q);

		} else if(P && !Q) {

			permute_ge_left(m, n, colptr, rowidx, values, colptr_out, rowidx_out, values_out, P);

		} else if(!P && Q) { 

			permute_ge_right(m, n, colptr, rowidx, values, colptr_out, rowidx_out, values_out, Q);

		} else {

			std::copy(colptr, colptr + n + 1    , colptr_out);
			std::copy(rowidx, rowidx + colptr[n], rowidx_out);
			std::copy(values, values + colptr[n], values_out);

		} // P/Q

	} else if(prop.isSymmetric() || prop.isHermitian() || prop.isSkew()) {

		if(P) {

			permute_xx_mirror(ptype, uplo, n, colptr, rowidx, values, colptr_out, rowidx_out, values_out, P);

		} else {

			std::copy(colptr, colptr + n + 1    , colptr_out);
			std::copy(rowidx, rowidx + colptr[n], rowidx_out);
			std::copy(values, values + colptr[n], values_out);

		} // P

	} else {

		throw err::Exception("Invalid property: " + prop.name());

	} // prop
}
/*-------------------------------------------------*/
#define instantiate_permute(T_Int, T_Scl) \
template void permute(prop_t, uplo_t, uint_t, uint_t, \
    const T_Int*, const T_Int*, const T_Scl*, \
    T_Int*, T_Int*, T_Scl*, const int_t*, const int_t*)
instantiate_permute(int_t , real_t    );
instantiate_permute(int_t , real4_t   );
instantiate_permute(int_t , complex_t );
instantiate_permute(int_t , complex8_t);
instantiate_permute(uint_t, real_t    );
instantiate_permute(uint_t, real4_t   );
instantiate_permute(uint_t, complex_t );
instantiate_permute(uint_t, complex8_t);
#undef instantiate_permute
/*-------------------------------------------------*/
} // namespace csc
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/
