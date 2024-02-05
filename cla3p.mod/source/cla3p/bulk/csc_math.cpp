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
#include "cla3p/bulk/csc_math.hpp"

// system

// 3rd

// cla3p
#include "cla3p/proxies/mkl_sparse_proxy.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace csc {
/*-------------------------------------------------*/
template <typename T_Scalar>
void add(uint_t m, uint_t n, T_Scalar alpha,
    const int_t *colptrA, const int_t *rowidxA, const T_Scalar *valuesA,
    const int_t *colptrB, const int_t *rowidxB, const T_Scalar *valuesB,
    int_t **colptrC, int_t **rowidxC, T_Scalar **valuesC)
{
	mkl::csc_add(m, n, alpha,
			colptrA, rowidxA, valuesA,
			colptrB, rowidxB, valuesB,
			colptrC, rowidxC, valuesC);
}
/*-------------------------------------------------*/
template void add(uint_t, uint_t, real_t    , const int_t*, const int_t*, const real_t    *, const int_t*, const int_t*, const real_t    *, int_t**, int_t**, real_t    **);
template void add(uint_t, uint_t, real4_t   , const int_t*, const int_t*, const real4_t   *, const int_t*, const int_t*, const real4_t   *, int_t**, int_t**, real4_t   **);
template void add(uint_t, uint_t, complex_t , const int_t*, const int_t*, const complex_t *, const int_t*, const int_t*, const complex_t *, int_t**, int_t**, complex_t **);
template void add(uint_t, uint_t, complex8_t, const int_t*, const int_t*, const complex8_t*, const int_t*, const int_t*, const complex8_t*, int_t**, int_t**, complex8_t**);
/*-------------------------------------------------*/
template <typename T_Scalar>
void gem_x_vec(op_t opA, uint_t m, uint_t n, T_Scalar alpha,
    const int_t *colptr, const int_t *rowidx, const T_Scalar *values,
    const T_Scalar *x, T_Scalar beta, T_Scalar *y)
{
	Property pr = Property(prop_t::General, uplo_t::Full);
	mkl::csc_mv(pr.type(), pr.uplo(), m, n, alpha, opA, colptr, rowidx, values, x, beta, y);
}
/*-------------------------------------------------*/
template void gem_x_vec(op_t, uint_t, uint_t, real_t    , const int_t*, const int_t*, const real_t    *, const real_t    *, real_t    , real_t    *);
template void gem_x_vec(op_t, uint_t, uint_t, real4_t   , const int_t*, const int_t*, const real4_t   *, const real4_t   *, real4_t   , real4_t   *);
template void gem_x_vec(op_t, uint_t, uint_t, complex_t , const int_t*, const int_t*, const complex_t *, const complex_t *, complex_t , complex_t *);
template void gem_x_vec(op_t, uint_t, uint_t, complex8_t, const int_t*, const int_t*, const complex8_t*, const complex8_t*, complex8_t, complex8_t*);
/*-------------------------------------------------*/
template <typename T_Scalar>
void sym_x_vec(uplo_t uplo, uint_t n, T_Scalar alpha,
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values,
		const T_Scalar *x, T_Scalar beta, T_Scalar *y)
{
	Property pr = Property(prop_t::Symmetric, uplo);
	mkl::csc_mv(pr.type(), pr.uplo(), n, n, alpha, op_t::N, colptr, rowidx, values, x, beta, y);
}
/*-------------------------------------------------*/
template void sym_x_vec(uplo_t, uint_t, real_t    , const int_t*, const int_t*, const real_t    *, const real_t    *, real_t    , real_t    *);
template void sym_x_vec(uplo_t, uint_t, real4_t   , const int_t*, const int_t*, const real4_t   *, const real4_t   *, real4_t   , real4_t   *);
template void sym_x_vec(uplo_t, uint_t, complex_t , const int_t*, const int_t*, const complex_t *, const complex_t *, complex_t , complex_t *);
template void sym_x_vec(uplo_t, uint_t, complex8_t, const int_t*, const int_t*, const complex8_t*, const complex8_t*, complex8_t, complex8_t*);
/*-------------------------------------------------*/
template <typename T_Scalar>
void hem_x_vec(uplo_t uplo, uint_t n, T_Scalar alpha,
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values,
		const T_Scalar *x, T_Scalar beta, T_Scalar *y)
{
	Property pr = sanitizeProperty<T_Scalar>(Property(prop_t::Hermitian, uplo));
	mkl::csc_mv(pr.type(), pr.uplo(), n, n, alpha, op_t::N, colptr, rowidx, values, x, beta, y);
}
/*-------------------------------------------------*/
template void hem_x_vec(uplo_t, uint_t, real_t    , const int_t*, const int_t*, const real_t    *, const real_t    *, real_t    , real_t    *);
template void hem_x_vec(uplo_t, uint_t, real4_t   , const int_t*, const int_t*, const real4_t   *, const real4_t   *, real4_t   , real4_t   *);
template void hem_x_vec(uplo_t, uint_t, complex_t , const int_t*, const int_t*, const complex_t *, const complex_t *, complex_t , complex_t *);
template void hem_x_vec(uplo_t, uint_t, complex8_t, const int_t*, const int_t*, const complex8_t*, const complex8_t*, complex8_t, complex8_t*);
/*-------------------------------------------------*/
template <typename T_Scalar>
void gem_x_gem(op_t opA, uint_t m, uint_t n, uint_t k, T_Scalar alpha,
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values,
		const T_Scalar *b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc)
{
	Property pr = Property(prop_t::General, uplo_t::Full);
	mkl::csc_mm(pr.type(), pr.uplo(), m, n, alpha, opA, colptr, rowidx, values, k, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
template void gem_x_gem(op_t, uint_t, uint_t, uint_t, real_t    , const int_t*, const int_t*, const real_t    *, const real_t    *, uint_t, real_t    , real_t    *, uint_t );
template void gem_x_gem(op_t, uint_t, uint_t, uint_t, real4_t   , const int_t*, const int_t*, const real4_t   *, const real4_t   *, uint_t, real4_t   , real4_t   *, uint_t );
template void gem_x_gem(op_t, uint_t, uint_t, uint_t, complex_t , const int_t*, const int_t*, const complex_t *, const complex_t *, uint_t, complex_t , complex_t *, uint_t );
template void gem_x_gem(op_t, uint_t, uint_t, uint_t, complex8_t, const int_t*, const int_t*, const complex8_t*, const complex8_t*, uint_t, complex8_t, complex8_t*, uint_t );
/*-------------------------------------------------*/
template <typename T_Scalar>
void sym_x_gem(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha,
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values,
		const T_Scalar *b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc)
{
	Property pr = Property(prop_t::Symmetric, uplo);
	mkl::csc_mm(pr.type(), pr.uplo(), m, m, alpha, op_t::N, colptr, rowidx, values, n, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
template void sym_x_gem(uplo_t, uint_t, uint_t, real_t    , const int_t*, const int_t*, const real_t    *, const real_t    *, uint_t, real_t    , real_t    *, uint_t);
template void sym_x_gem(uplo_t, uint_t, uint_t, real4_t   , const int_t*, const int_t*, const real4_t   *, const real4_t   *, uint_t, real4_t   , real4_t   *, uint_t);
template void sym_x_gem(uplo_t, uint_t, uint_t, complex_t , const int_t*, const int_t*, const complex_t *, const complex_t *, uint_t, complex_t , complex_t *, uint_t);
template void sym_x_gem(uplo_t, uint_t, uint_t, complex8_t, const int_t*, const int_t*, const complex8_t*, const complex8_t*, uint_t, complex8_t, complex8_t*, uint_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
void hem_x_gem(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha,
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values,
		const T_Scalar *b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc)
{
	Property pr = sanitizeProperty<T_Scalar>(Property(prop_t::Hermitian, uplo));
	mkl::csc_mm(pr.type(), pr.uplo(), m, m, alpha, op_t::N, colptr, rowidx, values, n, b, ldb, beta, c, ldc);
}
/*-------------------------------------------------*/
template void hem_x_gem(uplo_t, uint_t, uint_t, real_t    , const int_t*, const int_t*, const real_t    *, const real_t    *, uint_t, real_t    , real_t    *, uint_t);
template void hem_x_gem(uplo_t, uint_t, uint_t, real4_t   , const int_t*, const int_t*, const real4_t   *, const real4_t   *, uint_t, real4_t   , real4_t   *, uint_t);
template void hem_x_gem(uplo_t, uint_t, uint_t, complex_t , const int_t*, const int_t*, const complex_t *, const complex_t *, uint_t, complex_t , complex_t *, uint_t);
template void hem_x_gem(uplo_t, uint_t, uint_t, complex8_t, const int_t*, const int_t*, const complex8_t*, const complex8_t*, uint_t, complex8_t, complex8_t*, uint_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
void gem_x_gem(op_t opA, uint_t m, uint_t n, uint_t k,
    const int_t *colptrA, const int_t *rowidxA, const T_Scalar *valuesA,
    const int_t *colptrB, const int_t *rowidxB, const T_Scalar *valuesB,
    int_t **colptrC, int_t **rowidxC, T_Scalar **valuesC)
{
	uint_t mA = (opA == op_t::N ? m : k);
	uint_t nA = (opA == op_t::N ? k : m);
	uint_t mB = k;
	uint_t nB = n;

	mkl::csc_spmm(opA,
    mA, nA, colptrA, rowidxA, valuesA,
    mB, nB, colptrB, rowidxB, valuesB,
    colptrC, rowidxC,  valuesC);
}
/*-------------------------------------------------*/
template void gem_x_gem(op_t, uint_t, uint_t, uint_t, const int_t*, const int_t*, const real_t    *, const int_t*, const int_t*, const real_t    *, int_t**, int_t**, real_t    **);
template void gem_x_gem(op_t, uint_t, uint_t, uint_t, const int_t*, const int_t*, const real4_t   *, const int_t*, const int_t*, const real4_t   *, int_t**, int_t**, real4_t   **);
template void gem_x_gem(op_t, uint_t, uint_t, uint_t, const int_t*, const int_t*, const complex_t *, const int_t*, const int_t*, const complex_t *, int_t**, int_t**, complex_t **);
template void gem_x_gem(op_t, uint_t, uint_t, uint_t, const int_t*, const int_t*, const complex8_t*, const int_t*, const int_t*, const complex8_t*, int_t**, int_t**, complex8_t**);
/*-------------------------------------------------*/
} // namespace csc
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/
