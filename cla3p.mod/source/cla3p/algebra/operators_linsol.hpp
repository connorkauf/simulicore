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

#ifndef CLA3P_OPERATORS_LINSOL_HPP_
#define CLA3P_OPERATORS_LINSOL_HPP_

/**
 * @file
 * Global linear solution operator definitions
 */

#include "cla3p/linsol/dns_auto_lsolver.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
template <typename T_Scalar, typename T_Vector> class XxVector;
template <typename T_Scalar, typename T_Matrix> class XxMatrix;
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_linsol
 * @brief Solves a system of linear equations.
 *
 * Solves the  linear system <b>A X = B</b>
 *
 * Valid types for A:
 @verbatim
  A: General            
  A: Symmetric          
  A: Hermitian          
  A: Triangular (square)
 @endverbatim
 *
 * @param[in] A The lhs matrix.
 * @param[in] B The rhs vector.
 * @return The solution vector X.
 */
template <typename T_Matrix>
typename cla3p::TypeTraits<T_Matrix>::vector_type operator/(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		const typename cla3p::TypeTraits<T_Matrix>::vector_type& B)
{
	typename cla3p::TypeTraits<T_Matrix>::vector_type ret = B.copy();
	ret /= A;
	return ret;
}

/**
 * @ingroup module_index_math_operators_linsol
 * @brief Solves a system of linear equations.
 *
 * Solves the  linear system <b>A X = B</b>
 *
 * Valid type combinations:
 @verbatim
  A: General              B: General
  A: Symmetric            B: General
  A: Hermitian            B: General
  A: Triangular (square)  B: General
 @endverbatim
 *
 * @param[in] A The lhs matrix.
 * @param[in] B The rhs matrix.
 * @return The solution matrix X.
 */
template <typename T_Matrix>
T_Matrix operator/(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B) 
{
	T_Matrix ret = B.copy();
	ret /= A;
	return ret;
}

/**
 * @ingroup module_index_math_operators_linsol
 * @brief Overwrites rhs with the linear system solution.
 *
 * Solves the  linear system <b>A X = B</b>
 * replacing the rhs B with the solution X.
 *
 * Valid types for A:
 @verbatim
  A: General            
  A: Symmetric          
  A: Hermitian          
  A: Triangular (square)
 @endverbatim
 *
 * @param[in] B The rhs vector.
 * @param[in] A The lhs matrix.
 */
template <typename T_Matrix>
void operator/=(
		typename cla3p::TypeTraits<T_Matrix>::vector_type& B, 
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A)
{
	using T_Vector = typename cla3p::TypeTraits<T_Matrix>::vector_type;

	if(A.prop().isTriangular() && A.nrows() == A.ncols()) {

		cla3p::ops::trisol(cla3p::op_t::N, A, B);

	} else {

		T_Vector rhs = B.rcopy();
		cla3p::dns::default_linear_solver<T_Matrix,T_Vector>(A.self(), rhs);

	} // property case
}

/**
 * @ingroup module_index_math_operators_linsol
 * @brief Overwrites rhs with the linear system solution.
 *
 * Solves the  linear system <b>A X = B</b>
 * replacing the rhs B with the solution X. 
 *
 * Valid type combinations:
 @verbatim
  A: General              B: General
  A: Symmetric            B: General
  A: Hermitian            B: General
  A: Triangular (square)  B: General
 @endverbatim
 *
 * @param[in] B The rhs matrix.
 * @param[in] A The lhs matrix.
 */
template <typename T_Matrix>
void operator/=(
		cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B, 
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A)
{
	if(A.prop().isTriangular() && A.nrows() == A.ncols()) {

		cla3p::ops::trisol(1., cla3p::op_t::N, A, B);

	} else {

		T_Matrix rhs = B.rcopy();
		cla3p::dns::default_linear_solver<T_Matrix,T_Matrix>(A.self(), rhs);

	} // property case
}

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_LINSOL_HPP_
