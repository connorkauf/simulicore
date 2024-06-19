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

#ifndef CLA3P_BULK_CSC_MATH_HPP_
#define CLA3P_BULK_CSC_MATH_HPP_

/**
 * @file
 */

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace blk {
namespace csc {
/*-------------------------------------------------*/

//
// Update: cscC = alpha * cscA + cscB
// cscC(m x n)
//
template <typename T_Scalar>
void add(uint_t m, uint_t n, T_Scalar alpha,
		const int_t *colptrA, const int_t *rowidxA, const T_Scalar *valuesA,
		const int_t *colptrB, const int_t *rowidxB, const T_Scalar *valuesB,
		int_t **colptrC, int_t **rowidxC, T_Scalar **valuesC);

//
// Update: dnsY = beta * dnsY + alpha * op(cscA) * dnsX
// A(m x n)
//
template <typename T_Scalar>
void gem_x_vec(op_t opA, uint_t m, uint_t n, T_Scalar alpha, 
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values, 
		const T_Scalar *x, T_Scalar beta, T_Scalar *y);

//
// Update: dnsY = beta * dnsY + alpha * cscA * dnsX
// A(n x n)
//
template <typename T_Scalar>
void sym_x_vec(uplo_t uplo, uint_t n, T_Scalar alpha, 
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values, 
		const T_Scalar *x, T_Scalar beta, T_Scalar *y);

//
// Update: dnsY = beta * dnsY + alpha * cscA * dnsX
// A(n x n)
//
template <typename T_Scalar>
void hem_x_vec(uplo_t uplo, uint_t n, T_Scalar alpha, 
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values, 
		const T_Scalar *x, T_Scalar beta, T_Scalar *y);

//
// Update: dnsC = beta * dnsC + alpha * opA(cscA) * dnsB
// C(m x n)
//
template <typename T_Scalar>
void gem_x_gem(op_t opA, uint_t m, uint_t n, uint_t k, T_Scalar alpha,
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values, 
		const T_Scalar *b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc);

//
// Update: dnsC = beta * dnsC + alpha * cscA * dnsB
// C(m x n)
//
template <typename T_Scalar>
void sym_x_gem(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha,
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values, 
		const T_Scalar *b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc);

//
// Update: dnsC = beta * dnsC + alpha * cscA * dnsB
// C(m x n)
//
template <typename T_Scalar>
void hem_x_gem(uplo_t uplo, uint_t m, uint_t n, T_Scalar alpha,
		const int_t *colptr, const int_t *rowidx, const T_Scalar *values, 
		const T_Scalar *b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc);

//
// Update: dnsC = beta * dnsC + alpha * pA(cscA) * opB(cscB)
// C(m x n)
//
template <typename T_Scalar>
void gem_x_gem(uint_t m, uint_t n, uint_t k, T_Scalar alpha,
		op_t opA, const int_t *colptrA, const int_t *rowidxA, const T_Scalar *valuesA, 
		op_t opB, const int_t *colptrB, const int_t *rowidxB, const T_Scalar *valuesB, 
		T_Scalar beta, T_Scalar *c, uint_t ldc); 

//
// Update: cscC = opA(cscA) * opB(cscB)
// C(m x n)
//
template <typename T_Scalar>
void gem_x_gem(uint_t m, uint_t n, uint_t k,
		op_t opA, const int_t *colptrA, const int_t *rowidxA, const T_Scalar *valuesA, 
		op_t opB, const int_t *colptrB, const int_t *rowidxB, const T_Scalar *valuesB, 
		int_t **colptrC, int_t **rowidxC, T_Scalar **valuesC); 

/*-------------------------------------------------*/
} // namespace csc
} // namespace blk
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BULK_CSC_MATH_HPP_
