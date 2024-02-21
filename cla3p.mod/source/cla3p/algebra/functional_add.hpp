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

#ifndef CLA3P_ALGEBRA_FUNCTIONAL_ADD_HPP_
#define CLA3P_ALGEBRA_FUNCTIONAL_ADD_HPP_

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
 * @brief Adds two compatible scaled dense vectors.
 *
 * Performs the operation <b>alpha * X + beta * Y</b>
 *
 * @param[in] alpha The scaling coefficient for X.
 * @param[in] X The first input dense vector.
 * @param[in] beta The scaling coefficient for Y.
 * @param[in] Y The second input dense vector.
 * @return The result of the operation <b>(alpha * X + beta * Y)</b>.
 */
template <typename T_Vector>
T_Vector add(
		typename T_Vector::value_type alpha, const dns::XxVector<typename T_Vector::value_type,T_Vector>& X,
		typename T_Vector::value_type beta , const dns::XxVector<typename T_Vector::value_type,T_Vector>& Y);

/**
 * @ingroup module_index_math_op_add
 * @brief Adds two compatible scaled dense matrices.
 *
 * Performs the operation <b>alpha * A + beta * B</b>
 *
 * @param[in] alpha The scaling coefficient for A.
 * @param[in] A The first input dense matrix.
 * @param[in] beta The scaling coefficient for B.
 * @param[in] B The second input dense matrix.
 * @return The result of the operation <b>(alpha * A + beta * B)</b>.
 */
template <typename T_Matrix>
T_Matrix add(
		typename T_Matrix::value_type alpha, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		typename T_Matrix::value_type beta , const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B);

/**
 * @ingroup module_index_math_op_add
 * @brief Adds two compatible sparse matrices.
 *
 * Performs the operation <b>alpha * A + B</b>
 *
 * @param[in] alpha The scaling coefficient for A.
 * @param[in] A The first input sparse matrix.
 * @param[in] B The second input sparse matrix.
 * @return The result of the operation <b>(alpha * A + B)</b>.
 */
template <typename T_Matrix>
T_Matrix add(typename T_Matrix::value_type alpha,
		const csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
		const csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B);

/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ALGEBRA_FUNCTIONAL_ADD_HPP_
