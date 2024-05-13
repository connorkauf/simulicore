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
 */

#include "cla3p/virtuals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns { template <typename T_Scalar, typename T_Vector> class XxVector; }
namespace dns { template <typename T_Scalar, typename T_Matrix> class XxMatrix; }
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
template <typename T_Matrix, typename T_Vector>
T_Vector operator/(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& B);

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
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B); 

template <typename T_Matrix, typename T_Virtual>
typename T_Virtual::value_type operator/(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::VirtualEntity<typename T_Virtual::value_type,T_Virtual>& vB)
{
	return (A / vB.evaluate());
}

/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/

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
template <typename T_Vector, typename T_Matrix>
void operator/=(
		cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& B, 
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A);

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
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A);

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_LINSOL_HPP_
