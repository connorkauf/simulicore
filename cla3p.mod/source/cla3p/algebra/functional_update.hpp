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

#ifndef CLA3P_ALGEBRA_FUNCTIONAL_UPDATE_HPP_
#define CLA3P_ALGEBRA_FUNCTIONAL_UPDATE_HPP_

/**
 * @file
 */

#include "cla3p/dense.hpp"
#include "cla3p/sparse.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace ops {
/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_op_add
 * @brief Update a dense vector with a compatible scaled dense vector.
 *
 * Performs the operation <b>Y = Y + alpha * X</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] X The input dense vector.
 * @param[in,out] Y The dense vector to be updated.
 */
template <typename T_Vector>
void update(typename T_Vector::value_type alpha,
    const dns::XxVector<typename T_Vector::value_type,T_Vector>& X,
    dns::XxVector<typename T_Vector::value_type,T_Vector>& Y);

/**
 * @ingroup module_index_math_op_add
 * @brief Update a dense matrix with a compatible scaled dense matrix.
 *
 * Performs the operation <b>B = B + alpha * A</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] A The input dense matrix.
 * @param[in,out] B The dense matrix to be updated.
 */
template <typename T_Matrix>
void update(
    typename T_Matrix::value_type alpha,
    const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
    dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B);

/**
 * @ingroup module_index_math_op_add
 * @brief Update a sparse matrix with a compatible scaled sparse matrix.
 *
 * Performs the operation <b>B = B + alpha * A</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] A The input sparse matrix.
 * @param[in,out] B The sparse matrix to be updated.
 */
template <typename T_Matrix>
void update(
    typename T_Matrix::value_type alpha,
    const csc::XxMatrix<int_t,typename T_Matrix::value_type,T_Matrix>& A,
    csc::XxMatrix<int_t,typename T_Matrix::value_type,T_Matrix>& B);

/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ALGEBRA_FUNCTIONAL_UPDATE_HPP_
