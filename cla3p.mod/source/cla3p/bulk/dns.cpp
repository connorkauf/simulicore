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
#include "cla3p/bulk/dns.hpp"

// system
#include <functional>

// 3rd

// cla3p
#include "cla3p/types.hpp"

#include "cla3p/proxies/blas_proxy.hpp"
#include "cla3p/proxies/lapack_proxy.hpp"
#include "cla3p/proxies/mkl_proxy.hpp"
#include "cla3p/error/exceptions.hpp"
#include "cla3p/error/literals.hpp"
#include "cla3p/support/utils.hpp"
#include "cla3p/checks/basic_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace dns {
/*-------------------------------------------------*/
static inline uint_t recursive_min_dim()
{
	return 256;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void set_diag_zeros(prop_t ptype, uint_t n, T_Scalar *a, uint_t lda)
{
	if(ptype == prop_t::Hermitian) {
		for(uint_t i = 0; i < n; i++) {
			arith::setIm(entry(lda,a,i,i), 0);
		} // i
	} else if(ptype == prop_t::Skew) {
		for(uint_t i = 0; i < n; i++) {
			entry(lda,a,i,i) = 0;
		} // i
	}
}
/*-------------------------------------------------*/
template void set_diag_zeros(prop_t, uint_t, int_t     *, uint_t);
template void set_diag_zeros(prop_t, uint_t, uint_t    *, uint_t);
template void set_diag_zeros(prop_t, uint_t, real_t    *, uint_t);
template void set_diag_zeros(prop_t, uint_t, real4_t   *, uint_t);
template void set_diag_zeros(prop_t, uint_t, complex_t *, uint_t);
template void set_diag_zeros(prop_t, uint_t, complex8_t*, uint_t);
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
static void fill_std(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda, T_Scalar val, T_Scalar dval)
{
	if(!m || !n) return;

	if(m == lda && uplo == uplo_t::Full) {
		std::fill_n(a, m * n, val);
	} else {
		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, m, j);
			if(ir.ilen) {
				std::fill_n(ptrmv(lda,a,ir.ibgn,j), ir.ilen, val);
			} // ilen
		} // j
	} // m = lda

	for(uint_t j = 0; j < std::min(m,n); j++) {
		entry(lda,a,j,j) = dval;
	} // j
}
/*-------------------------------------------------*/
template <typename T_Scalar>
static void fill_lapack(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda, T_Scalar val, T_Scalar dval)
{
	if(!m || !n) return;

	int_t info = lapack::laset(static_cast<char>(uplo), m, n, val, dval, a, lda);

	if(info) {
		throw err::Exception(msg::LapackError() + " (info:" + std::to_string(info) + ")");
	} // info
}
/*-------------------------------------------------*/
template <> void fill(uplo_t uplo, uint_t m, uint_t n, int_t      *a, uint_t lda, int_t      val){ fill_std   (uplo, m, n, a, lda, val, val); }
template <> void fill(uplo_t uplo, uint_t m, uint_t n, uint_t     *a, uint_t lda, uint_t     val){ fill_std   (uplo, m, n, a, lda, val, val); }
template <> void fill(uplo_t uplo, uint_t m, uint_t n, real_t     *a, uint_t lda, real_t     val){ fill_lapack(uplo, m, n, a, lda, val, val); }
template <> void fill(uplo_t uplo, uint_t m, uint_t n, real4_t    *a, uint_t lda, real4_t    val){ fill_lapack(uplo, m, n, a, lda, val, val); }
template <> void fill(uplo_t uplo, uint_t m, uint_t n, complex_t  *a, uint_t lda, complex_t  val){ fill_lapack(uplo, m, n, a, lda, val, val); }
template <> void fill(uplo_t uplo, uint_t m, uint_t n, complex8_t *a, uint_t lda, complex8_t val){ fill_lapack(uplo, m, n, a, lda, val, val); }
/*-------------------------------------------------*/
template <> void fill(uplo_t uplo, uint_t m, uint_t n, int_t      *a, uint_t lda, int_t      val, int_t      dval){ fill_std   (uplo, m, n, a, lda, val, dval); }
template <> void fill(uplo_t uplo, uint_t m, uint_t n, uint_t     *a, uint_t lda, uint_t     val, uint_t     dval){ fill_std   (uplo, m, n, a, lda, val, dval); }
template <> void fill(uplo_t uplo, uint_t m, uint_t n, real_t     *a, uint_t lda, real_t     val, real_t     dval){ fill_lapack(uplo, m, n, a, lda, val, dval); }
template <> void fill(uplo_t uplo, uint_t m, uint_t n, real4_t    *a, uint_t lda, real4_t    val, real4_t    dval){ fill_lapack(uplo, m, n, a, lda, val, dval); }
template <> void fill(uplo_t uplo, uint_t m, uint_t n, complex_t  *a, uint_t lda, complex_t  val, complex_t  dval){ fill_lapack(uplo, m, n, a, lda, val, dval); }
template <> void fill(uplo_t uplo, uint_t m, uint_t n, complex8_t *a, uint_t lda, complex8_t val, complex8_t dval){ fill_lapack(uplo, m, n, a, lda, val, dval); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
void rand(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda, 
		typename TypeTraits<T_Scalar>::real_type lo, 
		typename TypeTraits<T_Scalar>::real_type hi) 
{
	if(!m || !n) return;

	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, m, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {
			entry(lda,a,i,j) = cla3p::rand<T_Scalar>(lo, hi);
		} // i
	} // j
}
/*-------------------------------------------------*/
template void rand(uplo_t, uint_t, uint_t, int_t     *, uint_t, int_t  , int_t  );
template void rand(uplo_t, uint_t, uint_t, uint_t    *, uint_t, uint_t , uint_t );
template void rand(uplo_t, uint_t, uint_t, real_t    *, uint_t, real_t , real_t );
template void rand(uplo_t, uint_t, uint_t, real4_t   *, uint_t, real4_t, real4_t);
template void rand(uplo_t, uint_t, uint_t, complex_t *, uint_t, real_t , real_t );
template void rand(uplo_t, uint_t, uint_t, complex8_t*, uint_t, real4_t, real4_t);
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
static void copy_lapack(uplo_t uplo, uint_t m, uint_t n, const T_Scalar *a, uint_t lda, T_Scalar *b, uint_t ldb, T_Scalar coeff)
{
	if(!m || !n) return;

	if(coeff == T_Scalar(0)) {
		zero(uplo, m, n, b, ldb);
		return;
	} // coeff = 0

	if(uplo == uplo_t::Full) {
		mkl::omatcopy('C', 'N', m, n, coeff, a, lda, b, ldb);
	} else {
		int_t info = lapack::lacpy(static_cast<char>(uplo), m, n, a, lda, b, ldb);
		if(info) {
			throw err::Exception(msg::LapackError() + " (info:" + std::to_string(info) + ")");
		} // info
		scale(uplo, m, n, b, ldb, coeff);
	} // uplo
}
/*-------------------------------------------------*/
template <typename T_Scalar>
static void copy_naive(uplo_t uplo, uint_t m, uint_t n, const T_Scalar *a, uint_t lda, T_Scalar *b, uint_t ldb, T_Scalar coeff)
{
	// 
	// TODO: more efficiently
	//
	if(!m || !n) return;

	if(coeff == T_Scalar(0)) {
		zero(uplo, m, n, b, ldb);
		return;
	} // coeff = 0

	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, m, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {
			entry(ldb,b,i,j) = coeff * entry(lda,a,i,j);
		} // i
	} // j
}
/*-------------------------------------------------*/
template <> void copy(uplo_t uplo, uint_t m, uint_t n, const int_t  *a, uint_t lda, int_t  *b, uint_t ldb, int_t  coeff) { copy_naive(uplo, m, n, a, lda, b, ldb, coeff); }
template <> void copy(uplo_t uplo, uint_t m, uint_t n, const uint_t *a, uint_t lda, uint_t *b, uint_t ldb, uint_t coeff) { copy_naive(uplo, m, n, a, lda, b, ldb, coeff); }
/*-------------------------------------------------*/
template <> void copy(uplo_t uplo, uint_t m, uint_t n, const real_t     *a, uint_t lda, real_t     *b, uint_t ldb, real_t     coeff) { copy_lapack(uplo, m, n, a, lda, b, ldb, coeff); }
template <> void copy(uplo_t uplo, uint_t m, uint_t n, const real4_t    *a, uint_t lda, real4_t    *b, uint_t ldb, real4_t    coeff) { copy_lapack(uplo, m, n, a, lda, b, ldb, coeff); }
template <> void copy(uplo_t uplo, uint_t m, uint_t n, const complex_t  *a, uint_t lda, complex_t  *b, uint_t ldb, complex_t  coeff) { copy_lapack(uplo, m, n, a, lda, b, ldb, coeff); }
template <> void copy(uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda, complex8_t *b, uint_t ldb, complex8_t coeff) { copy_lapack(uplo, m, n, a, lda, b, ldb, coeff); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
void get_real(uplo_t uplo, uint_t m, uint_t n, const T_Scalar *a, uint_t lda, 
		typename TypeTraits<T_Scalar>::real_type *b, uint_t ldb)
{
	using T_RScalar = typename TypeTraits<T_Scalar>::real_type;

	if(!m || !n) return;

	if(uplo == uplo_t::Full) {
		mkl::omatcopy('C', 'N', m, n, 1, reinterpret_cast<const T_RScalar*>(a), 2 * lda, 2, b, ldb, 1);
	} else {
		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, m, j);
			if(ir.ilen) {
				blas::copy(ir.ilen, reinterpret_cast<const T_RScalar*>(ptrmv(lda,a,ir.ibgn,j)), 2, ptrmv(ldb,b,ir.ibgn,j), 1);
			} // ilen
		} // j
	}
}
/*-------------------------------------------------*/
template void get_real(uplo_t, uint_t, uint_t, const complex_t *, uint_t, real_t *, uint_t);
template void get_real(uplo_t, uint_t, uint_t, const complex8_t*, uint_t, real4_t*, uint_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
void set_real(uplo_t uplo, uint_t m, uint_t n, 
		const typename TypeTraits<T_Scalar>::real_type *a, uint_t lda, T_Scalar *b, uint_t ldb)
{
	using T_RScalar = typename TypeTraits<T_Scalar>::real_type;

	if(!m || !n) return;

	if(uplo == uplo_t::Full) {
		mkl::omatcopy('C', 'N', m, n, 1, a, lda, 1, reinterpret_cast<T_RScalar*>(b), 2 * ldb, 2);
	} else {
		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, m, j);
			if(ir.ilen) {
				blas::copy(ir.ilen, ptrmv(lda,a,ir.ibgn,j), 1, reinterpret_cast<T_RScalar*>(ptrmv(ldb,b,ir.ibgn,j)), 2);
			} // ilen
		} // j
	}
}
/*-------------------------------------------------*/
template void set_real(uplo_t, uint_t, uint_t, const real_t *, uint_t, complex_t *, uint_t);
template void set_real(uplo_t, uint_t, uint_t, const real4_t*, uint_t, complex8_t*, uint_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
void get_imag(uplo_t uplo, uint_t m, uint_t n, const T_Scalar *a, uint_t lda, 
		typename TypeTraits<T_Scalar>::real_type *b, uint_t ldb)
{
	using T_RScalar = typename TypeTraits<T_Scalar>::real_type;

	if(!m || !n) return;

	if(uplo == uplo_t::Full) {
		mkl::omatcopy('C', 'N', m, n, 1, reinterpret_cast<const T_RScalar*>(a) + 1, 2 * lda, 2, b, ldb, 1);
	} else {
		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, m, j);
			if(ir.ilen) {
				blas::copy(ir.ilen, reinterpret_cast<const T_RScalar*>(ptrmv(lda,a,ir.ibgn,j)) + 1, 2, ptrmv(ldb,b,ir.ibgn,j), 1);
			} // ilen
		} // j
	}
}
/*-------------------------------------------------*/
template void get_imag(uplo_t, uint_t, uint_t, const complex_t *, uint_t, real_t *, uint_t);
template void get_imag(uplo_t, uint_t, uint_t, const complex8_t*, uint_t, real4_t*, uint_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
void set_imag(uplo_t uplo, uint_t m, uint_t n, 
		const typename TypeTraits<T_Scalar>::real_type *a, uint_t lda, T_Scalar *b, uint_t ldb)
{
	using T_RScalar = typename TypeTraits<T_Scalar>::real_type;

	if(!m || !n) return;

	if(uplo == uplo_t::Full) {
		mkl::omatcopy('C', 'N', m, n, 1, a, lda, 1, reinterpret_cast<T_RScalar*>(b) + 1, 2 * ldb, 2);
	} else {
		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, m, j);
			if(ir.ilen) {
				blas::copy(ir.ilen, ptrmv(lda,a,ir.ibgn,j), 1, reinterpret_cast<T_RScalar*>(ptrmv(ldb,b,ir.ibgn,j)) + 1, 2);
			} // ilen
		} // j
	}
}
/*-------------------------------------------------*/
template void set_imag(uplo_t, uint_t, uint_t, const real_t *, uint_t, complex_t *, uint_t);
template void set_imag(uplo_t, uint_t, uint_t, const real4_t*, uint_t, complex8_t*, uint_t);
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template<typename T_Scalar>
static void recursive_scale(uplo_t uplo, uint_t n, T_Scalar *a, uint_t lda, T_Scalar coeff)
{
	if(!n) return;

	if(n < recursive_min_dim()) {

		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, n, j);
			if(ir.ilen) {
				blas::scal(ir.ilen, coeff, ptrmv(lda,a,ir.ibgn,j), 1);
			} // ilen
		} // j

	} else {

		uint_t n0 = n/2;
		uint_t n1 = n - n0;

		recursive_scale(uplo, n0, ptrmv(lda,a, 0, 0), lda, coeff);
		recursive_scale(uplo, n1, ptrmv(lda,a,n0,n0), lda, coeff);

		if(uplo == uplo_t::Upper) scale(uplo_t::Full, n0, n1, ptrmv(lda,a,0,n0), lda, coeff);
		if(uplo == uplo_t::Lower) scale(uplo_t::Full, n1, n0, ptrmv(lda,a,n0,0), lda, coeff);

	} // dim check
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void scale(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda, T_Scalar coeff)
{
	if(!m || !n) return;

	if(coeff == T_Scalar(1)) {
		return;
	} // coeff = 1

	if(coeff == T_Scalar(0)) {
		zero(uplo, m, n, a, lda);
		return;
	} // coeff = 0
	
	if(uplo == uplo_t::Full) {

		if(m == 1) {

			blas::scal(n, coeff, a, lda);

		} else if(n == 1) {

			blas::scal(m, coeff, a, 1);

		} else {

			mkl::imatcopy('C', 'N', m, n, coeff, a, lda, lda);

		} // single dim check

	} else {

		uint_t k = std::min(m,n);

		recursive_scale(uplo, k, a, lda, coeff);

		if(uplo == uplo_t::Upper) scale(uplo_t::Full, m  , n-k, ptrmv(lda,a,0,k), lda, coeff);
		if(uplo == uplo_t::Lower) scale(uplo_t::Full, m-k, n  , ptrmv(lda,a,k,0), lda, coeff);

	} // uplo
}
/*-------------------------------------------------*/
template void scale(uplo_t, uint_t, uint_t, real_t    *, uint_t, real_t    );
template void scale(uplo_t, uint_t, uint_t, real4_t   *, uint_t, real4_t   );
template void scale(uplo_t, uint_t, uint_t, complex_t *, uint_t, complex_t );
template void scale(uplo_t, uint_t, uint_t, complex8_t*, uint_t, complex8_t);
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
void transpose(uint_t m, uint_t n, const T_Scalar *a, uint_t lda, T_Scalar *b, uint_t ldb, T_Scalar coeff)
{
	if(!m || !n) return;

	if(coeff == T_Scalar(0)) {
		zero(uplo_t::Full, n, m, b, ldb);
		return;
	} // coeff = 0

	mkl::omatcopy('C', 'T', m, n, coeff, a, lda, b, ldb);
}
/*-------------------------------------------------*/
template void transpose(uint_t, uint_t, const real_t    *, uint_t, real_t    *, uint_t, real_t    );
template void transpose(uint_t, uint_t, const real4_t   *, uint_t, real4_t   *, uint_t, real4_t   );
template void transpose(uint_t, uint_t, const complex_t *, uint_t, complex_t *, uint_t, complex_t );
template void transpose(uint_t, uint_t, const complex8_t*, uint_t, complex8_t*, uint_t, complex8_t);
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
void conjugate_transpose(uint_t m, uint_t n, const T_Scalar *a, uint_t lda, T_Scalar *b, uint_t ldb, T_Scalar coeff)
{
	if(!m || !n) return;

	if(coeff == T_Scalar(0)) {
		zero(uplo_t::Full, n, m, b, ldb);
		return;
	} // coeff = 0

	mkl::omatcopy('C', 'C', m, n, coeff, a, lda, b, ldb);
}
/*-------------------------------------------------*/
template void conjugate_transpose(uint_t, uint_t, const real_t    *, uint_t, real_t    *, uint_t, real_t    );
template void conjugate_transpose(uint_t, uint_t, const real4_t   *, uint_t, real4_t   *, uint_t, real4_t   );
template void conjugate_transpose(uint_t, uint_t, const complex_t *, uint_t, complex_t *, uint_t, complex_t );
template void conjugate_transpose(uint_t, uint_t, const complex8_t*, uint_t, complex8_t*, uint_t, complex8_t);
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template<typename T_Scalar>
static void recursive_conjugate(uplo_t uplo, uint_t n, T_Scalar *a, uint_t lda, T_Scalar coeff)
{
	if(!n) return;

	if(n < recursive_min_dim()) {

		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, n, j);
			if(ir.ilen) {
				mkl::imatcopy('C', 'R', ir.ilen, 1, coeff, ptrmv(lda,a,ir.ibgn,j), lda, lda);
			} // ilen
		} // j

	} else {

		uint_t n0 = n/2;
		uint_t n1 = n - n0;

		recursive_conjugate(uplo, n0, ptrmv(lda,a, 0, 0), lda, coeff);
		recursive_conjugate(uplo, n1, ptrmv(lda,a,n0,n0), lda, coeff);

		if(uplo == uplo_t::Upper) conjugate(uplo_t::Full, n0, n1, ptrmv(lda,a,0,n0), lda, coeff);
		if(uplo == uplo_t::Lower) conjugate(uplo_t::Full, n1, n0, ptrmv(lda,a,n0,0), lda, coeff);

	} // dim check
}
/*-------------------------------------------------*/
template <> void conjugate(uplo_t, uint_t, uint_t, real_t*, uint_t, real_t) {}
template <> void conjugate(uplo_t, uint_t, uint_t, real4_t*, uint_t, real4_t) {}
/*-------------------------------------------------*/
template <typename T_Scalar>
void conjugate(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda, T_Scalar coeff)
{
	if(!m || !n) return;

	if(coeff == T_Scalar(0)) {
		zero(uplo, m, n, a, lda);
		return;
	} // coeff = 0

	if(uplo == uplo_t::Full) {
		mkl::imatcopy('C', 'R', m, n, coeff, a, lda, lda);
	} else {
		uint_t k = std::min(m,n);
		recursive_conjugate(uplo, k, a, lda, coeff);
		if(uplo == uplo_t::Upper) conjugate(uplo_t::Full, m  , n-k, ptrmv(lda,a,0,k), lda, coeff);
		if(uplo == uplo_t::Lower) conjugate(uplo_t::Full, m-k, n  , ptrmv(lda,a,k,0), lda, coeff);
	} // lower
}
/*-------------------------------------------------*/
template void conjugate(uplo_t, uint_t, uint_t, complex_t *, uint_t, complex_t );
template void conjugate(uplo_t, uint_t, uint_t, complex8_t*, uint_t, complex8_t);
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
static void xx2ge_recursive(uplo_t uplo, uint_t n, T_Scalar *a, uint_t lda, prop_t ptype)
{
	if(!n) return;

	if(n < recursive_min_dim()) {

		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, n, j);
			for(uint_t i = ir.ibgn; i < ir.iend; i++) {
				if(i != j) {
					entry(lda,a,j,i) = opposite_element(entry(lda,a,i,j),ptype);
				} // off diagonals
			} // i
		} // j

		set_diag_zeros(ptype, n, a, lda);

	} else {

		uint_t n0 = n/2;
		uint_t n1 = n - n0;

		xx2ge_recursive(uplo, n0, ptrmv(lda,a, 0, 0), lda, ptype);
		xx2ge_recursive(uplo, n1, ptrmv(lda,a,n0,n0), lda, ptype);

		if(ptype == prop_t::Symmetric) {

			/**/ if(uplo == uplo_t::Upper) transpose(n0, n1, ptrmv(lda,a,0,n0), lda, ptrmv(lda,a,n0,0), lda);
			else if(uplo == uplo_t::Lower) transpose(n1, n0, ptrmv(lda,a,n0,0), lda, ptrmv(lda,a,0,n0), lda);

		} else if(ptype == prop_t::Hermitian) {

			/**/ if(uplo == uplo_t::Upper) conjugate_transpose(n0, n1, ptrmv(lda,a,0,n0), lda, ptrmv(lda,a,n0,0), lda);
			else if(uplo == uplo_t::Lower) conjugate_transpose(n1, n0, ptrmv(lda,a,n0,0), lda, ptrmv(lda,a,0,n0), lda);

		} else if(ptype == prop_t::Skew) {

			/**/ if(uplo == uplo_t::Upper) transpose(n0, n1, ptrmv(lda,a,0,n0), lda, ptrmv(lda,a,n0,0), lda, T_Scalar(-1));
			else if(uplo == uplo_t::Lower) transpose(n1, n0, ptrmv(lda,a,n0,0), lda, ptrmv(lda,a,0,n0), lda, T_Scalar(-1));

		} else {

			throw err::Exception();

		} // ptype

	} // dim check
}
/*-------------------------------------------------*/
template <typename T_Scalar>
static void xx2ge(uplo_t uplo, uint_t n, T_Scalar *a, uint_t lda, prop_t ptype)
{
	xx2ge_recursive(uplo, n, a, lda, ptype);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void sy2ge(uplo_t uplo, uint_t n, T_Scalar *a, uint_t lda) 
{ 
	xx2ge(uplo, n, a, lda, prop_t::Symmetric); 
}
/*-------------------------------------------------*/
template void sy2ge(uplo_t, uint_t, real_t    *, uint_t);
template void sy2ge(uplo_t, uint_t, real4_t   *, uint_t);
template void sy2ge(uplo_t, uint_t, complex_t *, uint_t);
template void sy2ge(uplo_t, uint_t, complex8_t*, uint_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
void he2ge(uplo_t uplo, uint_t n, T_Scalar *a, uint_t lda) 
{ 
	xx2ge(uplo, n, a, lda, prop_t::Hermitian); 
}
/*-------------------------------------------------*/
template void he2ge(uplo_t, uint_t, real_t    *, uint_t);
template void he2ge(uplo_t, uint_t, real4_t   *, uint_t);
template void he2ge(uplo_t, uint_t, complex_t *, uint_t);
template void he2ge(uplo_t, uint_t, complex8_t*, uint_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
void sk2ge(uplo_t uplo, uint_t n, T_Scalar *a, uint_t lda) 
{ 
	xx2ge(uplo, n, a, lda, prop_t::Skew); 
}
/*-------------------------------------------------*/
template void sk2ge(uplo_t, uint_t, real_t    *, uint_t);
template void sk2ge(uplo_t, uint_t, real4_t   *, uint_t);
template void sk2ge(uplo_t, uint_t, complex_t *, uint_t);
template void sk2ge(uplo_t, uint_t, complex8_t*, uint_t);
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
void tr2ge(uplo_t uplo, uint_t m, uint_t n, T_Scalar *a, uint_t lda)
{
	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange_complement(uplo, m, j);
		if(ir.ilen) {
			zero(uplo_t::Full, ir.ilen, 1, ptrmv(lda,a,ir.ibgn,j), lda);
		} // ilen
	} // j
}
/*-------------------------------------------------*/
template void tr2ge(uplo_t, uint_t, uint_t, real_t    *, uint_t);
template void tr2ge(uplo_t, uint_t, uint_t, real4_t   *, uint_t);
template void tr2ge(uplo_t, uint_t, uint_t, complex_t *, uint_t);
template void tr2ge(uplo_t, uint_t, uint_t, complex8_t*, uint_t);
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
typename TypeTraits<T_Scalar>::real_type
static norm_one_skew(uplo_t uplo, uint_t n, const T_Scalar *a, uint_t lda)
{
	using T_RScalar = typename TypeTraits<T_Scalar>::real_type;

	T_RScalar ret = 0;
	T_RScalar *tmp = alloc<T_RScalar>(n, 1, n, true);

	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange_strict(uplo, n, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {
			T_RScalar absAij = std::abs(entry(lda,a,i,j));
			tmp[i] += absAij;
			tmp[j] += absAij;
		} // i
	} // j

	for(uint_t j = 0; j < n; j++) {
		ret = std::max(ret,tmp[j]);
	} // j

	i_free(tmp);

	return ret;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
typename TypeTraits<T_Scalar>::real_type 
norm_one(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const T_Scalar *a, uint_t lda)
{
	using T_RScalar = typename TypeTraits<T_Scalar>::real_type;

	if(!m || !n) return 0.;

	Property prop(ptype, uplo);

	if(prop.isSquare()) {
		square_check(m, n);
	}

	if(prop.isGeneral()) {

		return lapack::lange('1', m, n, a, lda);

	} else if(prop.isSymmetric()) {

		return lapack::lansy('1', prop.cuplo(), n, a, lda);

	} else if(prop.isHermitian()) { 

		return lapack::lanhe('1', prop.cuplo(), n, a, lda);

	} else if(prop.isTriangular()) {

		return lapack::lantr('1', prop.cuplo(), 'N', std::min(m,n), n, a, lda);

	} else if(prop.isSkew()) {

		return norm_one_skew(uplo, n, a, lda);

	} // property
	
	throw err::Exception("Invalid property: " + prop.name());
	return T_RScalar(0);
}
/*-------------------------------------------------*/
template real_t  norm_one(prop_t, uplo_t, uint_t, uint_t, const real_t    *, uint_t);
template real4_t norm_one(prop_t, uplo_t, uint_t, uint_t, const real4_t   *, uint_t);
template real_t  norm_one(prop_t, uplo_t, uint_t, uint_t, const complex_t *, uint_t);
template real4_t norm_one(prop_t, uplo_t, uint_t, uint_t, const complex8_t*, uint_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
typename TypeTraits<T_Scalar>::real_type
norm_inf(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const T_Scalar *a, uint_t lda)
{
	if(!m || !n) return 0.;

	Property prop(ptype, uplo);

	if(prop.isSquare()) {
		square_check(m, n);
	}

	if(prop.isGeneral()) {

		return lapack::lange('I', m, n, a, lda);

	} else if(prop.isSymmetric()) {

		return lapack::lansy('I', prop.cuplo(), n, a, lda);

	} else if(prop.isHermitian()) { 

		return lapack::lanhe('I', prop.cuplo(), n, a, lda);

	} else if(prop.isTriangular()) {

		return lapack::lantr('I', prop.cuplo(), 'N', std::min(m,n), n, a, lda);

	} else if(prop.isSkew()) {

		return norm_one_skew(uplo, n, a, lda); // norms one & inf are the same

	} // property
	
	throw err::Exception("Invalid property: " + prop.name());
	return 0.;
}
/*-------------------------------------------------*/
template real_t  norm_inf(prop_t, uplo_t, uint_t, uint_t, const real_t    *, uint_t);
template real4_t norm_inf(prop_t, uplo_t, uint_t, uint_t, const real4_t   *, uint_t);
template real_t  norm_inf(prop_t, uplo_t, uint_t, uint_t, const complex_t *, uint_t);
template real4_t norm_inf(prop_t, uplo_t, uint_t, uint_t, const complex8_t*, uint_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
static typename TypeTraits<T_Scalar>::real_type
norm_max_skew(uplo_t uplo, uint_t n, const T_Scalar *a, uint_t lda)
{
	using T_RScalar = typename TypeTraits<T_Scalar>::real_type;

	T_RScalar ret = 0;

	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange_strict(uplo, n, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {
			ret = std::max(ret,std::abs(entry(lda,a,i,j)));
		} // i
	} // j

	return ret;
}
/*-------------------------------------------------*/
template <typename T_Scalar>
typename TypeTraits<T_Scalar>::real_type
norm_max(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const T_Scalar *a, uint_t lda)
{
	using T_RScalar = typename TypeTraits<T_Scalar>::real_type;

	if(!m || !n) return 0.;

	Property prop(ptype, uplo);

	if(prop.isSquare()) {
		square_check(m, n);
	}

	if(prop.isGeneral()) {

		return lapack::lange('M', m, n, a, lda);

	} else if(prop.isSymmetric()) {

		return lapack::lansy('M', prop.cuplo(), n, a, lda);

	} else if(prop.isHermitian()) { 

		return lapack::lanhe('M', prop.cuplo(), n, a, lda);

	} else if(prop.isTriangular()) {

		return lapack::lantr('M', prop.cuplo(), 'N', std::min(m,n), n, a, lda);

	} else if(prop.isSkew()) {

		return norm_max_skew(uplo, n, a, lda);

	} // property
	
	throw err::Exception("Invalid property: " + prop.name());
	return T_RScalar(0);
}
/*-------------------------------------------------*/
template real_t  norm_max(prop_t, uplo_t, uint_t, uint_t, const real_t    *, uint_t);
template real4_t norm_max(prop_t, uplo_t, uint_t, uint_t, const real4_t   *, uint_t);
template real_t  norm_max(prop_t, uplo_t, uint_t, uint_t, const complex_t *, uint_t);
template real4_t norm_max(prop_t, uplo_t, uint_t, uint_t, const complex8_t*, uint_t);
/*-------------------------------------------------*/
//
// fro norm for Symmetric/Hermitian wrong in lapack for n >= 128
// TODO: more efficient
//
template <typename T_Scalar>
static typename TypeTraits<T_Scalar>::real_type
naive_xx_norm_fro(uplo_t uplo, uint_t n, const T_Scalar *a, uint_t lda, prop_t ptype)
{
	using T_RScalar = typename TypeTraits<T_Scalar>::real_type;

	T_RScalar sum = 0;
	T_RScalar two = 2;

	if(ptype == prop_t::Symmetric) {

		for(uint_t j = 0; j < n; j++) {
			T_RScalar absAjj = std::abs(entry(lda,a,j,j));
			sum += absAjj * absAjj;
		} // j

	} else if(ptype == prop_t::Hermitian) {

		for(uint_t j = 0; j < n; j++) {
			T_RScalar absAjj = std::abs(arith::getRe(entry(lda,a,j,j)));
			sum += absAjj * absAjj;
		} // j

	} else if(ptype == prop_t::Skew) {

		// nothing to add

	} else {

		throw err::Exception();

	} // property

	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange_strict(uplo, n, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {
			T_RScalar aij = std::abs(entry(lda,a,i,j));
			sum += two * aij * aij;
		} // i
	} // j

	return std::sqrt(sum);
}
/*-------------------------------------------------*/
template <typename T_Scalar>
typename TypeTraits<T_Scalar>::real_type
norm_fro(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const T_Scalar *a, uint_t lda)
{
	using T_RScalar = typename TypeTraits<T_Scalar>::real_type;

	if(!m || !n) return 0;

	Property prop(ptype, uplo);

	if(prop.isSquare()) {
		square_check(m, n);
	}

	if(prop.isGeneral()) {

		return lapack::lange('F', m, n, a, lda);

	} else if(prop.isSymmetric()) {

		if(n >= 128) {
			return naive_xx_norm_fro(uplo, n, a, lda, prop.type());
		} else {
			return lapack::lansy('F', prop.cuplo(), n, a, lda);
		}

	} else if(prop.isHermitian()) { 

		if(n >= 128) {
			return naive_xx_norm_fro(uplo, n, a, lda, prop.type());
		} else {
			return lapack::lanhe('F', prop.cuplo(), n, a, lda);
		}

	} else if(prop.isTriangular()) {

		return lapack::lantr('F', prop.cuplo(), 'N', m, std::min(m,n), a, lda);

	} else if(prop.isSkew()) {

		return naive_xx_norm_fro(uplo, n, a, lda, prop.type());

	} // property
	
	throw err::Exception("Invalid property: " + prop.name());
	return T_RScalar(0);
}
/*-------------------------------------------------*/
template real_t  norm_fro(prop_t, uplo_t, uint_t, uint_t, const real_t    *, uint_t);
template real4_t norm_fro(prop_t, uplo_t, uint_t, uint_t, const real4_t   *, uint_t);
template real_t  norm_fro(prop_t, uplo_t, uint_t, uint_t, const complex_t *, uint_t);
template real4_t norm_fro(prop_t, uplo_t, uint_t, uint_t, const complex8_t*, uint_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
typename TypeTraits<T_Scalar>::real_type norm_euc(uint_t n, const T_Scalar *a) 
{ 
	return blas::nrm2(n, a, 1); 
}
/*-------------------------------------------------*/
template real_t  norm_euc(uint_t, const real_t    *);
template real4_t norm_euc(uint_t, const real4_t   *);
template real_t  norm_euc(uint_t, const complex_t *);
template real4_t norm_euc(uint_t, const complex8_t*);
/*-------------------------------------------------*/
template <typename T_Scalar>
static void permute_ge_left(uint_t m, uint_t n, const T_Scalar *a, uint_t lda, T_Scalar *b, uint_t ldb, const int_t *P)
{
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			entry(ldb, b, P[i], j) = entry(lda, a, i, j);
		} // i
	} // j
}
/*-------------------------------------------------*/
template <typename T_Scalar>
static void permute_ge_right(uint_t m, uint_t n, const T_Scalar *a, uint_t lda, T_Scalar *b, uint_t ldb, const int_t *Q)
{
	for(uint_t j = 0; j < n; j++) {
		copy(uplo_t::Full, m, 1, ptrmv(lda,a,0,Q[j]), lda, ptrmv(ldb,b,0,j), ldb);
	} // j
}
/*-------------------------------------------------*/
template <typename T_Scalar>
static void permute_ge_both(uint_t m, uint_t n, const T_Scalar *a, uint_t lda, T_Scalar *b, uint_t ldb, const int_t *P, const int_t *Q)
{
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			entry(ldb, b, P[i], j) = entry(lda, a, i, Q[j]);
		} // i
	} // j
}
/*-------------------------------------------------*/
template <typename T_Scalar>
static void permute_xx_mirror(uplo_t uplo, uint_t n, const T_Scalar *a, uint_t lda, T_Scalar *b, uint_t ldb, const int_t *P, prop_t ptype)
{
	uint_t Pi;
	uint_t Pj;

	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, n, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {

			Pi = P[i];
			Pj = P[j];

			if(uplo == uplo_t::Upper && Pj < Pi) {

				entry(ldb,b,Pj,Pi) = opposite_element(entry(lda,a,i,j),ptype);

			} else if(uplo == uplo_t::Lower && Pj > Pi) {

				entry(ldb,b,Pj,Pi) = opposite_element(entry(lda,a,i,j),ptype);

			} else {

				entry(ldb,b,Pi,Pj) = entry(lda,a,i,j);

			} // uplo switch

		} // i
	} // j
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void permute(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const T_Scalar *a, uint_t lda, 
		T_Scalar *b, uint_t ldb, const int_t *P, const int_t *Q)
{
	if(!m || !n) return;

	Property prop(ptype, uplo);

	if(prop.isSquare()) {
		square_check(m, n);
	}

	if(prop.isGeneral()) {

		/**/ if( P &&  Q) permute_ge_both (m, n, a, lda, b, ldb, P, Q);
		else if( P && !Q) permute_ge_left(m, n, a, lda, b, ldb, P);
		else if(!P &&  Q) permute_ge_right (m, n, a, lda, b, ldb, Q);
		else              copy(uplo_t::Full, m, n, a, lda, b, ldb);

	} else if(prop.isSymmetric() || prop.isHermitian() || prop.isSkew()) {

		if(P) {
			permute_xx_mirror(uplo, n, a, lda, b, ldb, P, prop.type());
		} else {
			copy(uplo, m, n, a, lda, b, ldb);
		} // P

	} else {

		throw err::Exception("Invalid property: " + prop.name());

	} // prop
}
/*-------------------------------------------------*/
#define instantiate_permute(T_Scl) \
template void permute(prop_t, uplo_t, uint_t, uint_t, const T_Scl*, uint_t, \
		T_Scl*, uint_t, const int_t*, const int_t*)
instantiate_permute(int_t);
instantiate_permute(uint_t);
instantiate_permute(real_t);
instantiate_permute(real4_t);
instantiate_permute(complex_t);
instantiate_permute(complex8_t);
#undef instantiate_permute
/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/
