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

#ifndef CLA3P_ALGEBRA_FUNCTIONAL_MULTMM_HPP_
#define CLA3P_ALGEBRA_FUNCTIONAL_MULTMM_HPP_

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
 * @ingroup module_index_math_op_matmat
 * @brief Updates a general matrix with a matrix-matrix product.
 *
 * Performs the operation <b>C = C + alpha * opA(A) * opB(B)</b>@n
 * C can be General/Symmetric/Hermitian.@n
 * If C is Symmetric/Hermitian, it is assumed that the outcome of the operation <b>opA(A) * opB(B)</b> is also Symmetric/Hermitian
 * and only the corresponding part (upper/lower) will be calculated.
 *
 * Valid combinations are the following:
 @verbatim
  A: General     B: General     opA: unconstrained      opB: unconstrained      C: General/Symmetric/Hermitian
  A: Symmetric   B: General     opA: ignored            opB: must be set to N   C: General
  A: Hermitian   B: General     opA: ignored            opB: must be set to N   C: General
  A: Triangular  B: General     opA: unconstrained      opB: must be set to N   C: General
  A: General     B: Symmetric   opA: must be set to N   opB: ignored            C: General
  A: General     B: Hermitian   opA: must be set to N   opB: ignored            C: General
  A: General     B: Triangular  opA: must be set to N   opB: unconstrained      C: General
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input matrix.
 * @param[in] opB The operation to be performed for matrix B.
 * @param[in] B The input matrix.
 * @param[in,out] C The matrix to be updated.
 */
template <typename T_Matrix>
void mult(typename T_Matrix::value_type alpha,
    op_t opA, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
    op_t opB, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B,
    dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& C);

/**
 * @ingroup module_index_math_op_matmat
 * @brief Replaces a matrix with a scaled triangular matrix-matrix product.
 *
 * Performs the operation <b>B := alpha * opA(A) * B</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 * @param[in,out] B The matrix to be replaced.
 */
template <typename T_Matrix>
void trimult(typename T_Matrix::value_type alpha, op_t opA,
		const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B);

/**
 * @ingroup module_index_math_op_matmat
 * @brief Replaces a matrix with a scaled triangular matrix-matrix product.
 *
 * Performs the operation <b>B := alpha * B * opA(A)</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in,out] B The matrix to be replaced.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 */
template <typename T_Matrix>
void trimult(typename T_Matrix::value_type alpha,
		dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B,
		op_t opA, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A);

/**
 * @ingroup module_index_math_op_matmat
 * @brief Replaces a matrix with the scaled solution of a triangular system.
 *
 * Solves the system <b>opA(A) * X = alpha * B</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 * @param[in,out] B On entry, the rhs, on exit the system solution X.
 */
template <typename T_Matrix>
void trisol(typename T_Matrix::value_type alpha, op_t opA,
    const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
    dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B);

/**
 * @ingroup module_index_math_op_matmat
 * @brief Replaces a matrix with the scaled solution of a triangular system.
 *
 * Solves the system <b>X * opA(A) = alpha * B</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in,out] B On entry, the rhs, on exit the system solution X.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 */
template <typename T_Matrix>
void trisol(typename T_Matrix::value_type alpha,
    dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B,
    op_t opA, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A);

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_op_matmat
 * @brief Updates a general dense matrix with a sparse-dense matrix-matrix product.
 *
 * Performs the operation <b>C = C + alpha * opA(A) * B</b>@n
 *
 * Valid combinations are the following:
 @verbatim
  A: General     B: General     opA: unconstrained      C: General
  A: Symmetric   B: General     opA: ignored            C: General
  A: Hermitian   B: General     opA: ignored            C: General
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input sparse matrix.
 * @param[in] B The input dense matrix.
 * @param[in,out] C The dense matrix to be updated.
 */
template <typename T_CscMatrix, typename T_DnsMatrix>
void mult(typename T_CscMatrix::value_type alpha, op_t opA, 
		const csc::XxMatrix<typename T_CscMatrix::index_type,typename T_CscMatrix::value_type,T_CscMatrix>& A,
    const dns::XxMatrix<typename T_DnsMatrix::value_type,T_DnsMatrix>& B,
    dns::XxMatrix<typename T_DnsMatrix::value_type,T_DnsMatrix>& C);

/**
 * @ingroup module_index_math_op_matmat
 * @brief Updates a dense matrix with a sparse-sparse matrix-matrix product.
 *
 * Performs the operation <b>C = C + alpha * opA(A) * opB(B)</b>@n
 *
 * Valid combinations are the following:
 @verbatim
  A: General     B: General     opA: unconstrained      opB: unconstrained   
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input sparse matrix.
 * @param[in] opB The operation to be performed for matrix B.
 * @param[in] B The input dense matrix.
 * @param[in,out] C The dense matrix to be updated.
 */
template <typename T_CscMatrix, typename T_DnsMatrix>
void mult(typename T_CscMatrix::value_type alpha, 
		op_t opA, const csc::XxMatrix<typename T_CscMatrix::index_type,typename T_CscMatrix::value_type,T_CscMatrix>& A,
		op_t opB, const csc::XxMatrix<typename T_CscMatrix::index_type,typename T_CscMatrix::value_type,T_CscMatrix>& B,
    dns::XxMatrix<typename T_DnsMatrix::value_type,T_DnsMatrix>& C);

/**
 * @ingroup module_index_math_op_matmat
 * @brief Creates a general sparse matrix from a sparse-sparse matrix-matrix product.
 *
 * Performs the operation <b>alpha * opA(A) * opB(B)</b>@n
 *
 * Valid combinations are the following:
 @verbatim
  A: General     B: General     opA: unconstrained      opB: unconstrained   
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input sparse matrix.
 * @param[in] opB The operation to be performed for matrix B.
 * @param[in] B The input sparse matrix.
 * @return The matrix <b>(alpha * opA(A) * opB(B))</b>.
 */
template <typename T_Matrix>
T_Matrix mult(typename T_Matrix::value_type alpha, 
		op_t opA, const csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
    op_t opB, const csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B);

/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ALGEBRA_FUNCTIONAL_MULTMM_HPP_
