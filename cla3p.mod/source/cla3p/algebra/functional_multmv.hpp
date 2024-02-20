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

#ifndef CLA3P_ALGEBRA_FUNCTIONAL_MULTMV_HPP_
#define CLA3P_ALGEBRA_FUNCTIONAL_MULTMV_HPP_

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
 * @ingroup module_index_math_op_matvec
 * @brief Updates a vector with a matrix-vector product.
 *
 * Performs the operation <b>Y = Y + alpha * opA(A) * X</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A. If A is symmetric or hermitian, opA is ignored.
 * @param[in] A The input matrix.
 * @param[in] X The input vector.
 * @param[in,out] Y The vector to be updated.
 */

template <typename T_Vector, typename T_Matrix>
void mult(typename T_Vector::value_type alpha, op_t opA,
    const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
    const dns::XxVector<typename T_Vector::value_type,T_Vector>& X,
    dns::XxVector<typename T_Vector::value_type,T_Vector>& Y);

/**
 * @ingroup module_index_math_op_matvec
 * @brief Creates a vector from a matrix-vector product.
 *
 * Performs the operation <b>alpha * opA(A) * X</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A. If A is symmetric or hermitian, opA is ignored.
 * @param[in] A The input matrix.
 * @param[in] X The input vector.
 * @return The vector <b>(alpha * opA(A) * X)</b>.
 */
template <typename T_Vector, typename T_Matrix>
T_Vector mult(typename T_Vector::value_type alpha, op_t opA,
    const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
    const dns::XxVector<typename T_Vector::value_type,T_Vector>& X);

/**
 * @ingroup module_index_math_op_matvec
 * @brief Updates a vector with a matrix-vector product.
 *
 * Performs the operation <b>Y = Y + alpha * opA(A) * X</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A. If A is symmetric or hermitian, opA is ignored.
 * @param[in] A The input matrix.
 * @param[in] X The input vector.
 * @param[in,out] Y The vector to be updated.
 */

template <typename T_Vector, typename T_Matrix>
void mult(typename T_Vector::value_type alpha, op_t opA,
    const csc::XxMatrix<int_t,typename T_Matrix::value_type,T_Matrix>& A,
    const dns::XxVector<typename T_Vector::value_type,T_Vector>& X,
    dns::XxVector<typename T_Vector::value_type,T_Vector>& Y);

/**
 * @ingroup module_index_math_op_matvec
 * @brief Creates a vector from a matrix-vector product.
 *
 * Performs the operation <b>alpha * opA(A) * X</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A. If A is symmetric or hermitian, opA is ignored.
 * @param[in] A The input matrix.
 * @param[in] X The input vector.
 * @return The vector <b>(alpha * opA(A) * X)</b>.
 */
template <typename T_Vector, typename T_Matrix>
T_Vector mult(typename T_Vector::value_type alpha, op_t opA,
    const csc::XxMatrix<int_t,typename T_Matrix::value_type,T_Matrix>& A,
    const dns::XxVector<typename T_Vector::value_type,T_Vector>& X);

/**
 * @ingroup module_index_math_op_matvec
 * @brief Replaces a vector with a triangular matrix-vector product.
 *
 * Performs the operation <b>X := opA(A) * X</b>
 *
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 * @param[in,out] X The vector to be replaced.
 */
template <typename T_Vector, typename T_Matrix>
void trimult(op_t opA,
    const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
    dns::XxVector<typename T_Vector::value_type,T_Vector>& X);

/**
 * @ingroup module_index_math_op_matvec
 * @brief Replaces a vector with the solution of a triangular system.
 *
 * Solves the system <b>opA(A) * X = B</b>
 *
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 * @param[in,out] B On entry, the rhs, on exit the system solution X.
 */
template <typename T_Vector, typename T_Matrix>
void trisol(op_t opA,
    const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
    dns::XxVector<typename T_Vector::value_type,T_Vector>& B);

/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ALGEBRA_FUNCTIONAL_MULTMV_HPP_
