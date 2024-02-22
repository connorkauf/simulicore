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

#ifndef CLA3P_BULK_DNS_MATH_HPP_
#define CLA3P_BULK_DNS_MATH_HPP_

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace dns {
/*-------------------------------------------------*/

//
// Update: C += alpha * A
// C(m x n)
//
template <typename T_Scalar>
void update(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha, const T_Scalar *a, uint_t lda, T_Scalar *c, uint_t ldc);

//
// Update: C = alpha * A + beta * B
// C(m x n)
//
template <typename T_Scalar>
void add(uplo_t uplo, uint_t m, uint_t n,
		T_Scalar alpha, const T_Scalar *a, uint_t lda,
		T_Scalar beta , const T_Scalar *b, uint_t ldb, T_Scalar *c, uint_t ldc);

//
// Update: y = beta * y + alpha * op(A) * x
// A(m x n)
//
template <typename T_Scalar>
void gem_x_vec(op_t opA, uint_t m, uint_t n, T_Scalar alpha, 
		const T_Scalar *a, uint_t lda, const T_Scalar *x, T_Scalar beta, T_Scalar *y);

//
// Update: y = beta * y + alpha * A * x
//
template <typename T_Scalar>
void sym_x_vec(uplo_t uplo, uint_t n, T_Scalar alpha, const T_Scalar *a, uint_t lda, 
		const T_Scalar *x, T_Scalar beta, T_Scalar *y);

//
// Update: y = beta * y + alpha * A * x
//
template <typename T_Scalar>
void hem_x_vec(uplo_t uplo, uint_t n, T_Scalar alpha, const T_Scalar *a, uint_t lda, 
		const T_Scalar *x, T_Scalar beta, T_Scalar *y);

//
// Update: y = alpha * opA(A) * x
//
template <typename T_Scalar>
void trm_x_vec(uplo_t uplo, op_t opA, uint_t m, uint_t n, T_Scalar alpha, 
		const T_Scalar *a, uint_t lda, const T_Scalar *x, T_Scalar *y);

//
// Update: C = beta * C + alpha * opA(A) * opB(B)
// C(m x n)
//
template <typename T_Scalar>
void gem_x_gem(uint_t m, uint_t n, uint_t k, T_Scalar alpha,
		op_t opA, const T_Scalar *a, uint_t lda,
		op_t opB, const T_Scalar *b, uint_t ldb,
		T_Scalar beta, T_Scalar *c, uint_t ldc);

//
// Update: C = beta * C + alpha * A * B
// C(m x n)
//
template <typename T_Scalar>
void sym_x_gem(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha,
		const T_Scalar *a, uint_t lda,
		const T_Scalar *b, uint_t ldb,
		T_Scalar beta, T_Scalar *c, uint_t ldc);

//
// Update: C = beta * C + alpha * B * A
// C(m x n)
//
template <typename T_Scalar>
void gem_x_sym(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha,
		const T_Scalar *a, uint_t lda,
		const T_Scalar *b, uint_t ldb,
		T_Scalar beta, T_Scalar *c, uint_t ldc);

//
// Update: C = beta * C + alpha * A * B
// C(m x n)
//
template <typename T_Scalar>
void hem_x_gem(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha,
		const T_Scalar *a, uint_t lda,
		const T_Scalar *b, uint_t ldb,
		T_Scalar beta, T_Scalar *c, uint_t ldc);

//
// Update: C = beta * C + alpha * B * A
// C(m x n)
//
template <typename T_Scalar>
void gem_x_hem(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha,
		const T_Scalar *a, uint_t lda,
		const T_Scalar *b, uint_t ldb,
		T_Scalar beta, T_Scalar *c, uint_t ldc);

//
// Update: C = alpha * opA(A) * B
// C(m x n)
//
template <typename T_Scalar>
void trm_x_gem(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, T_Scalar alpha,
		const T_Scalar *a, uint_t lda,
		const T_Scalar *b, uint_t ldb,
		T_Scalar *c, uint_t ldc);

//
// Update: C = alpha * B * opA(A)
// C(m x n)
//
template <typename T_Scalar>
void gem_x_trm(uplo_t uplo, op_t opA, uint_t m, uint_t n, uint_t k, T_Scalar alpha,
		const T_Scalar *a, uint_t lda,
		const T_Scalar *b, uint_t ldb,
		T_Scalar *c, uint_t ldc);

/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BULK_DNS_MATH_HPP_
