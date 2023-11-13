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
#include "cla3p/bulk/dns_math.hpp"

// system

// 3rd

// cla3p
#include "cla3p/bulk/dns.hpp"
#include "cla3p/error/exceptions.hpp"
#include "cla3p/error/literals.hpp"
#include "cla3p/support/utils.hpp"
#include "cla3p/proxies/blas_proxy.hpp"
#include "cla3p/proxies/mkl_proxy.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace dns {
/*-------------------------------------------------*/
template <typename T_Scalar>
static void update_tmpl(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha, const T_Scalar *a, uint_t lda, T_Scalar *c, uint_t ldc)
{
	if(alpha == T_Scalar(0)) return;

	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, m, j);
		blas::axpy(ir.ilen, alpha, ptrmv(lda,a,ir.ibgn,j), 1, ptrmv(ldc,c,ir.ibgn,j), 1);
	} // j
}
/*-------------------------------------------------*/
void update(uplo_t uplo, uint_t m, uint_t n, real_t alpha, const real_t *a, uint_t lda, real_t *c, uint_t ldc)
{
	update_tmpl(uplo, m, n, alpha, a, lda, c, ldc);
}
/*-------------------------------------------------*/
void update(uplo_t uplo, uint_t m, uint_t n, real4_t alpha, const real4_t *a, uint_t lda, real4_t *c, uint_t ldc)
{
	update_tmpl(uplo, m, n, alpha, a, lda, c, ldc);
}
/*-------------------------------------------------*/
void update(uplo_t uplo, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, complex_t *c, uint_t ldc)
{
	update_tmpl(uplo, m, n, alpha, a, lda, c, ldc);
}
/*-------------------------------------------------*/
void update(uplo_t uplo, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, complex8_t *c, uint_t ldc)
{
	update_tmpl(uplo, m, n, alpha, a, lda, c, ldc);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
static void add_tmpl(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha, const T_Scalar *a, uint_t lda, 
		T_Scalar beta, const T_Scalar *b, uint_t ldb, T_Scalar *c, uint_t ldc)
{
	if(alpha == T_Scalar(0) && beta == T_Scalar(0)) {
		zero(uplo, m, n, c, ldc);
		return;
	} // alpha = 0 & beta = 0

	if(uplo == uplo_t::Full) {
		mkl::omatadd('C', 'N', 'N', m, n, alpha, a, lda, beta, b, ldb, c, ldc);
	} else {
		zero(uplo, m, n, c, ldc);
		update(uplo, m, n, alpha, a, lda, c, ldc);
		update(uplo, m, n, beta , b, ldb, c, ldc);
	} // uplo
}
/*-------------------------------------------------*/
void add(uplo_t uplo, uint_t m, uint_t n, real_t alpha, const real_t *a, uint_t lda, 
		real_t beta, const real_t *b, uint_t ldb, real_t *c, uint_t ldc) 
{
	add_tmpl(uplo, m, n, alpha, a, lda, beta, b, ldb, c, ldc); 
}
/*-------------------------------------------------*/
void add(uplo_t uplo, uint_t m, uint_t n, real4_t alpha, const real4_t *a, uint_t lda, 
		real4_t beta, const real4_t *b, uint_t ldb, real4_t *c, uint_t ldc) 
{
	add_tmpl(uplo, m, n, alpha, a, lda, beta, b, ldb, c, ldc); 
}
/*-------------------------------------------------*/
void add(uplo_t uplo, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, 
		complex_t beta, const complex_t *b, uint_t ldb, complex_t *c, uint_t ldc) 
{
	add_tmpl(uplo, m, n, alpha, a, lda, beta, b, ldb, c, ldc); 
}
/*-------------------------------------------------*/
void add(uplo_t uplo, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, 
		complex8_t beta, const complex8_t *b, uint_t ldb, complex8_t *c, uint_t ldc) 
{
	add_tmpl(uplo, m, n, alpha, a, lda, beta, b, ldb, c, ldc); 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
static void gem_x_vec_tmpl(op_t opA, uint_t m, uint_t n, T_Scalar alpha, const T_Scalar *a, uint_t lda, 
		const T_Scalar *x, T_Scalar beta, T_Scalar *y)
{
	blas::gemv(static_cast<char>(opA), m, n, alpha, a, lda, x, 1, beta, y, 1);
}
/*-------------------------------------------------*/
void gem_x_vec(op_t opA, uint_t m, uint_t n, real_t alpha, const real_t *a, uint_t lda, 
		const real_t *x, real_t beta, real_t *y)
{
	gem_x_vec_tmpl(opA, m, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void gem_x_vec(op_t opA, uint_t m, uint_t n, real4_t alpha, const real4_t *a, uint_t lda, 
		const real4_t *x, real4_t beta, real4_t *y)
{
	gem_x_vec_tmpl(opA, m, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void gem_x_vec(op_t opA, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, 
		const complex_t *x, complex_t beta, complex_t *y)
{
	gem_x_vec_tmpl(opA, m, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void gem_x_vec(op_t opA, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, 
		const complex8_t *x, complex8_t beta, complex8_t *y)
{
	gem_x_vec_tmpl(opA, m, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
static void sym_x_vec_tmpl(uplo_t uplo, uint_t n, T_Scalar alpha, const T_Scalar *a, uint_t lda, 
		const T_Scalar *x, T_Scalar beta, T_Scalar *y)
{
	blas::symv(static_cast<char>(uplo), n, alpha, a, lda, x, 1, beta, y, 1);
}
/*-------------------------------------------------*/
void sym_x_vec(uplo_t uplo, uint_t n, real_t alpha, const real_t *a, uint_t lda, 
		const real_t *x, real_t beta, real_t *y)
{
	sym_x_vec_tmpl(uplo, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void sym_x_vec(uplo_t uplo, uint_t n, real4_t alpha, const real4_t *a, uint_t lda, 
		const real4_t *x, real4_t beta, real4_t *y)
{
	sym_x_vec_tmpl(uplo, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void sym_x_vec(uplo_t uplo, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, 
		const complex_t *x, complex_t beta, complex_t *y)
{
	sym_x_vec_tmpl(uplo, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void sym_x_vec(uplo_t uplo, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, 
		const complex8_t *x, complex8_t beta, complex8_t *y)
{
	sym_x_vec_tmpl(uplo, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
static void hem_x_vec_tmpl(uplo_t uplo, uint_t n, T_Scalar alpha, const T_Scalar *a, uint_t lda, 
		const T_Scalar *x, T_Scalar beta, T_Scalar *y)
{
	blas::hemv(static_cast<char>(uplo), n, alpha, a, lda, x, 1, beta, y, 1);
}
/*-------------------------------------------------*/
void hem_x_vec(uplo_t, uint_t, real_t , const real_t* , uint_t, const real_t* , real_t , real_t* ) { throw err::Exception(msg::OpNotAllowed()); }
void hem_x_vec(uplo_t, uint_t, real4_t, const real4_t*, uint_t, const real4_t*, real4_t, real4_t*) { throw err::Exception(msg::OpNotAllowed()); }
/*-------------------------------------------------*/
void hem_x_vec(uplo_t uplo, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, 
		const complex_t *x, complex_t beta, complex_t *y)
{
	hem_x_vec_tmpl(uplo, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
void hem_x_vec(uplo_t uplo, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, 
		const complex8_t *x, complex8_t beta, complex8_t *y)
{
	hem_x_vec_tmpl(uplo, n, alpha, a, lda, x, beta, y);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
static void trm_x_vec_tmpl(uplo_t uplo, op_t opA, uint_t m, uint_t n, T_Scalar alpha, const T_Scalar *a, uint_t lda, 
		const T_Scalar *x, T_Scalar *y)
{
	if(alpha == T_Scalar(0)) {
		uint_t dimy = (opA == op_t::N ? m : n);
		zero(uplo_t::Full, dimy, 1, y, dimy);
		return;
	} // alpha = 0

	uint_t mindim = std::min(m,n);

	if(opA == op_t::N) {

		copy(uplo_t::Full, mindim, 1, x, mindim, y, mindim, alpha);
		if(m > n) zero(uplo_t::Full, m-n, 1, y + n, m-n);
		blas::trmv(static_cast<char>(uplo), static_cast<char>(opA), 'N', mindim, a, lda, y, 1);

		if(m > n && uplo == uplo_t::Lower) gem_x_vec(opA, m-n, n, alpha, ptrmv(lda,a,n,0), lda, x, 1, y + n);
		if(m < n && uplo == uplo_t::Upper) gem_x_vec(opA, m, n-m, alpha, ptrmv(lda,a,0,m), lda, x + m, 1, y);

	} else {

		copy(uplo_t::Full, mindim, 1, x, mindim, y, mindim, alpha);
		if(n > m) zero(uplo_t::Full, n-m, 1, y + m, n-m);
		blas::trmv(static_cast<char>(uplo), static_cast<char>(opA), 'N', mindim, a, lda, y, 1);

		if(m > n && uplo == uplo_t::Lower) gem_x_vec(opA, m-n, n, alpha, ptrmv(lda,a,n,0), lda, x + n, 1, y);
		if(m < n && uplo == uplo_t::Upper) gem_x_vec(opA, m, n-m, alpha, ptrmv(lda,a,0,m), lda, x, 1, y + m);

	} // opA
}
/*-------------------------------------------------*/
void trm_x_vec(uplo_t uplo, op_t opA, uint_t m, uint_t n, real_t alpha, const real_t *a, uint_t lda, 
		const real_t *x, real_t *y)
{
	trm_x_vec_tmpl(uplo, opA, m, n, alpha, a, lda, x, y);
}
/*-------------------------------------------------*/
void trm_x_vec(uplo_t uplo, op_t opA, uint_t m, uint_t n, real4_t alpha, const real4_t *a, uint_t lda, 
		const real4_t *x, real4_t *y)
{
	trm_x_vec_tmpl(uplo, opA, m, n, alpha, a, lda, x, y);
}
/*-------------------------------------------------*/
void trm_x_vec(uplo_t uplo, op_t opA, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, 
		const complex_t *x, complex_t *y)
{
	trm_x_vec_tmpl(uplo, opA, m, n, alpha, a, lda, x, y);
}
/*-------------------------------------------------*/
void trm_x_vec(uplo_t uplo, op_t opA, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, 
		const complex8_t *x, complex8_t *y)
{
	trm_x_vec_tmpl(uplo, opA, m, n, alpha, a, lda, x, y);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
static void gem_x_gem_tmpl(uint_t m, uint_t n, uint_t k, T_Scalar alpha, 
		op_t opA, const T_Scalar *a, uint_t lda, 
		op_t opB, const T_Scalar *b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc)
{
	blas::gemm(static_cast<char>(opA), static_cast<char>(opB), m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_gem(uint_t m, uint_t n, uint_t k, real_t alpha, op_t opA, const real_t *a, uint_t lda, 
		op_t opB, const real_t *b, uint_t ldb, real_t beta, real_t *c, uint_t ldc)
{
	gem_x_gem_tmpl(m, n, k, alpha, opA, a, lda, opB, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_gem(uint_t m, uint_t n, uint_t k, real4_t alpha, op_t opA, const real4_t *a, uint_t lda, 
		op_t opB, const real4_t *b, uint_t ldb, real4_t beta, real4_t *c, uint_t ldc)
{
	gem_x_gem_tmpl(m, n, k, alpha, opA, a, lda, opB, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_gem(uint_t m, uint_t n, uint_t k, complex_t alpha, op_t opA, const complex_t *a, uint_t lda, 
		op_t opB, const complex_t *b, uint_t ldb, complex_t beta, complex_t *c, uint_t ldc)
{
	gem_x_gem_tmpl(m, n, k, alpha, opA, a, lda, opB, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_gem(uint_t m, uint_t n, uint_t k, complex8_t alpha, op_t opA, const complex8_t *a, uint_t lda, 
		op_t opB, const complex8_t *b, uint_t ldb, complex8_t beta, complex8_t *c, uint_t ldc)
{
	gem_x_gem_tmpl(m, n, k, alpha, opA, a, lda, opB, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
static void sym_x_gem_tmpl(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha, const T_Scalar *a, uint_t lda, 
		const T_Scalar *b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc)
{
	blas::symm('L', static_cast<char>(uplo), m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void sym_x_gem(uplo_t uplo, uint_t m, uint_t n, real_t alpha, const real_t *a, uint_t lda, 
		const real_t *b, uint_t ldb, real_t beta, real_t *c, uint_t ldc)
{
	sym_x_gem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void sym_x_gem(uplo_t uplo, uint_t m, uint_t n, real4_t alpha, const real4_t *a, uint_t lda, 
		const real4_t *b, uint_t ldb, real4_t beta, real4_t *c, uint_t ldc)
{
	sym_x_gem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void sym_x_gem(uplo_t uplo, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, 
		const complex_t *b, uint_t ldb, complex_t beta, complex_t *c, uint_t ldc)
{
	sym_x_gem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void sym_x_gem(uplo_t uplo, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, 
		const complex8_t *b, uint_t ldb, complex8_t beta, complex8_t *c, uint_t ldc)
{
	sym_x_gem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
static void gem_x_sym_tmpl(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha, const T_Scalar *a, uint_t lda, 
		const T_Scalar *b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc)
{
	blas::symm('R', static_cast<char>(uplo), m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_sym(uplo_t uplo, uint_t m, uint_t n, real_t alpha, const real_t *a, uint_t lda, 
		const real_t *b, uint_t ldb, real_t beta, real_t *c, uint_t ldc)
{
	gem_x_sym_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_sym(uplo_t uplo, uint_t m, uint_t n, real4_t alpha, const real4_t *a, uint_t lda, 
		const real4_t *b, uint_t ldb, real4_t beta, real4_t *c, uint_t ldc)
{
	gem_x_sym_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_sym(uplo_t uplo, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, 
		const complex_t *b, uint_t ldb, complex_t beta, complex_t *c, uint_t ldc)
{
	gem_x_sym_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_sym(uplo_t uplo, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, 
		const complex8_t *b, uint_t ldb, complex8_t beta, complex8_t *c, uint_t ldc)
{
	gem_x_sym_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
static void hem_x_gem_tmpl(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha, const T_Scalar *a, uint_t lda, 
		const T_Scalar *b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc)
{
	blas::hemm('L', static_cast<char>(uplo), m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void hem_x_gem(uplo_t, uint_t, uint_t, real_t , const real_t* , uint_t, const real_t* , uint_t, real_t , real_t* , uint_t) { throw err::Exception(msg::OpNotAllowed()); }
void hem_x_gem(uplo_t, uint_t, uint_t, real4_t, const real4_t*, uint_t, const real4_t*, uint_t, real4_t, real4_t*, uint_t) { throw err::Exception(msg::OpNotAllowed()); }
/*-------------------------------------------------*/
void hem_x_gem(uplo_t uplo, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, 
		const complex_t *b, uint_t ldb, complex_t beta, complex_t *c, uint_t ldc)
{
	hem_x_gem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void hem_x_gem(uplo_t uplo, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, 
		const complex8_t *b, uint_t ldb, complex8_t beta, complex8_t *c, uint_t ldc)
{
	hem_x_gem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
static void gem_x_hem_tmpl(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha, const T_Scalar *a, uint_t lda, 
		const T_Scalar *b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc)
{
	blas::hemm('R', static_cast<char>(uplo), m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_hem(uplo_t, uint_t, uint_t, real_t , const real_t* , uint_t, const real_t* , uint_t, real_t , real_t* , uint_t) { throw err::Exception(msg::OpNotAllowed()); }
void gem_x_hem(uplo_t, uint_t, uint_t, real4_t, const real4_t*, uint_t, const real4_t*, uint_t, real4_t, real4_t*, uint_t) { throw err::Exception(msg::OpNotAllowed()); }
/*-------------------------------------------------*/
void gem_x_hem(uplo_t uplo, uint_t m, uint_t n, complex_t alpha, const complex_t *a, uint_t lda, 
		const complex_t *b, uint_t ldb, complex_t beta, complex_t *c, uint_t ldc)
{
	gem_x_hem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_hem(uplo_t uplo, uint_t m, uint_t n, complex8_t alpha, const complex8_t *a, uint_t lda, const complex8_t *b, uint_t ldb, complex8_t beta, complex8_t *c, uint_t ldc)
{
	gem_x_hem_tmpl(uplo, m, n, alpha, a, lda, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
void trm_x_gem_tmpl(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, T_Scalar alpha, const T_Scalar *a, uint_t lda, 
		const T_Scalar *b, uint_t ldb, T_Scalar *c, uint_t ldc)
{
	if(alpha == T_Scalar(0)) {
		zero(uplo_t::Full, m, n, c, ldc);
		return;
	} // alpha = 0

	uint_t mindim = std::min(m,k);

	copy(uplo_t::Full, mindim, n, b, ldb, c, ldc, alpha);
	if(m > k) zero(uplo_t::Full, m-k, n, ptrmv(ldc,c,k,0), ldc);
	blas::trmm('L', static_cast<char>(uplo), static_cast<char>(opA), 'N', mindim, n, 1, a, lda, c, ldc);

	if(opA == op_t::N) {
		if(m > k && uplo == uplo_t::Lower) gem_x_gem(m-k, n, k, alpha, opA, ptrmv(lda,a,k,0), lda, op_t::N,           b     , ldb, 1, ptrmv(ldc,c,k,0), ldc);
		if(m < k && uplo == uplo_t::Upper) gem_x_gem(m, n, k-m, alpha, opA, ptrmv(lda,a,0,m), lda, op_t::N, ptrmv(ldb,b,m,0), ldb, 1,           c     , ldc);
	} else {
		if(m > k && uplo == uplo_t::Upper) gem_x_gem(m-k, n, k, alpha, opA, ptrmv(lda,a,0,k), lda, op_t::N,           b     , ldb, 1, ptrmv(ldc,c,k,0), ldc);
		if(m < k && uplo == uplo_t::Lower) gem_x_gem(m, n, k-m, alpha, opA, ptrmv(lda,a,m,0), lda, op_t::N, ptrmv(ldb,b,m,0), ldb, 1,           c     , ldc);
	} // opA
}
/*-------------------------------------------------*/
void trm_x_gem(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, real_t alpha, const real_t *a, uint_t lda, 
		const real_t *b, uint_t ldb, real_t *c, uint_t ldc)
{
	trm_x_gem_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
void trm_x_gem(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, real4_t alpha, const real4_t *a, uint_t lda, 
		const real4_t *b, uint_t ldb, real4_t *c, uint_t ldc)
{
	trm_x_gem_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
void trm_x_gem(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, complex_t alpha, const complex_t *a, uint_t lda, 
		const complex_t *b, uint_t ldb, complex_t *c, uint_t ldc)
{
	trm_x_gem_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
void trm_x_gem(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, complex8_t alpha, const complex8_t *a, uint_t lda, 
		const complex8_t *b, uint_t ldb, complex8_t *c, uint_t ldc)
{
	trm_x_gem_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Scalar>
void gem_x_trm_tmpl(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, T_Scalar alpha, const T_Scalar *a, uint_t lda, 
		const T_Scalar *b, uint_t ldb, T_Scalar *c, uint_t ldc)
{
	if(alpha == T_Scalar(0)) {
		zero(uplo_t::Full, m, n, c, ldc);
		return;
	} // alpha = 0

	uint_t mindim = std::min(n,k);

	copy(uplo_t::Full, m, mindim, b, ldb, c, ldc, alpha);
	if(n > k) zero(uplo_t::Full, m, n-k, ptrmv(ldc,c,0,k), ldc);
	blas::trmm('R', static_cast<char>(uplo), static_cast<char>(opA), 'N', m, mindim, 1, a, lda, c, ldc);

	if(opA == op_t::N) {
		if(n > k && uplo == uplo_t::Upper) gem_x_gem(m, n-k, k, alpha, op_t::N,           b     , ldb, opA, ptrmv(lda,a,0,k), lda, 1, ptrmv(ldc,c,0,k), ldc);
		if(n < k && uplo == uplo_t::Lower) gem_x_gem(m, n, k-n, alpha, op_t::N, ptrmv(ldb,b,0,n), ldb, opA, ptrmv(lda,a,n,0), lda, 1,           c     , ldc);
	} else {
		if(n > k && uplo == uplo_t::Lower) gem_x_gem(m, n-k, k, alpha, op_t::N,           b     , ldb, opA, ptrmv(lda,a,k,0), lda, 1, ptrmv(ldc,c,0,k), ldc);
		if(n < k && uplo == uplo_t::Upper) gem_x_gem(m, n, k-n, alpha, op_t::N, ptrmv(ldb,b,0,n), ldb, opA, ptrmv(lda,a,0,n), lda, 1,           c     , ldc);
	} // opA
}
/*-------------------------------------------------*/
void gem_x_trm(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, real_t alpha, const real_t *a, uint_t lda, 
		const real_t *b, uint_t ldb, real_t *c, uint_t ldc)
{
	gem_x_trm_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_trm(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, real4_t alpha, const real4_t *a, uint_t lda, 
		const real4_t *b, uint_t ldb, real4_t *c, uint_t ldc)
{
	gem_x_trm_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_trm(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, complex_t alpha, const complex_t *a, uint_t lda, 
		const complex_t *b, uint_t ldb, complex_t *c, uint_t ldc)
{
	gem_x_trm_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
void gem_x_trm(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, complex8_t alpha, const complex8_t *a, uint_t lda, 
		const complex8_t *b, uint_t ldb, complex8_t *c, uint_t ldc)
{
	gem_x_trm_tmpl(uplo, opA, m, n, k, alpha, a, lda, b, ldb, c, ldc);
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/
