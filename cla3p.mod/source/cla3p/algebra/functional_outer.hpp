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

#ifndef CLA3P_ALGEBRA_FUNCTIONAL_OUTER_HPP_
#define CLA3P_ALGEBRA_FUNCTIONAL_OUTER_HPP_

/**
 * @file
 */

#include "cla3p/dense.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace ops {
/*-------------------------------------------------*/

/**
 * @ingroup cla3p_module_index_math_op_vecvec
 * @brief Update a matrix with a vector outer product.
 *
 * Performs the operation <b>A = A + alpha * X Y<sup>T</sup></b>@n
 * A can be General/Symmetric/Hermitian.@n
 * If A is Symmetric/Hermitian, it is assumed that the outcome of the operation <b>X Y<sup>T</sup></b> is also Symmetric/Hermitian
 * and only the corresponding part (upper/lower) will be calculated.
 *
 * @param[in] alpha The update coefficient.
 * @param[in] X The input vector.
 * @param[in] Y The input vector.
 * @param[in,out] A The matrix to be updated.
 */
template <typename T_Vector, typename T_Matrix>
void outer(typename T_Vector::value_type alpha, const T_Vector& X, const T_Vector& Y, T_Matrix& A);

/**
 * @ingroup cla3p_module_index_math_op_vecvec
 * @brief Update a matrix with a conjugate vector outer product.
 *
 * Performs the operation <b>A = A + alpha * X Y<sup>H</sup></b>@n
 * A can be General/Symmetric/Hermitian.@n
 * If A is Symmetric/Hermitian, it is assumed that the outcome of the operation <b>X Y<sup>H</sup></b> is also Symmetric/Hermitian
 * and only the corresponding part (upper/lower) will be calculated.
 *
 * @param[in] alpha The update coefficient.
 * @param[in] X The input vector.
 * @param[in] Y The input vector.
 * @param[in,out] A The matrix to be updated.
 */
template <typename T_Vector, typename T_Matrix>
void outerc(typename T_Vector::value_type alpha, const T_Vector& X, const T_Vector& Y, T_Matrix& A);

/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ALGEBRA_FUNCTIONAL_OUTER_HPP_
