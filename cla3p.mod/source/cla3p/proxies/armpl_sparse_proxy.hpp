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

#ifndef CLA3P_ARMPL_SPARSE_PROXY_HPP_
#define CLA3P_ARMPL_SPARSE_PROXY_HPP_

/**
 * @file
 */

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace armpl {
/*-------------------------------------------------*/

// C(m x n)
template <typename T_Scalar>
void csc_add(uint_t m, uint_t n,
		T_Scalar alpha, op_t opA, const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA, 
		T_Scalar beta, op_t opB, const int_t* colptrB, const int_t* rowidxB, const T_Scalar* valuesB,
		int_t **colptrC, int_t **rowidxC, T_Scalar **valuesC);

// A(m x n)
template <typename T_Scalar>
void csc_mv(prop_t propA, uplo_t uploA, uint_t m, uint_t n, T_Scalar alpha, op_t opA,
		const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA, 
		const T_Scalar* x, T_Scalar beta, T_Scalar *y);

// A(m x n) B(? x k) C(? x k)
template <typename T_Scalar>
void csc_mm(prop_t propA, uplo_t uploA, uint_t m, uint_t n, T_Scalar alpha, op_t opA,
		const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA, 
		uint_t k, const T_Scalar* b, uint_t ldb, T_Scalar beta, T_Scalar *c, uint_t ldc);

// A(mA x nA) B(mB x nB) C(? x ?)
template <typename T_Scalar>
void csc_spmm(T_Scalar alpha,
    op_t opA, uint_t mA, uint_t nA, const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
    op_t opB, uint_t mB, uint_t nB, const int_t* colptrB, const int_t* rowidxB, const T_Scalar* valuesB,
    T_Scalar beta, T_Scalar *c, uint_t ldc);

// A(mA x nA) B(mB x nB) C(? x ?)
template <typename T_Scalar>
void csc_spmm(T_Scalar alpha,
    op_t opA, uint_t mA, uint_t nA, const int_t* colptrA, const int_t* rowidxA, const T_Scalar* valuesA,
    op_t opB, uint_t mB, uint_t nB, const int_t* colptrB, const int_t* rowidxB, const T_Scalar* valuesB,
    int_t** colptrC, int_t** rowidxC, T_Scalar** valuesC);

/*-------------------------------------------------*/
} // namespace armpl
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_MKL_SPARSE_PROXY_HPP_
