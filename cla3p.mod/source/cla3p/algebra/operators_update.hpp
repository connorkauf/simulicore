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

#ifndef CLA3P_OPERATORS_UPDATE_HPP_
#define CLA3P_OPERATORS_UPDATE_HPP_

/**
 * @file
 */

#include "cla3p/virtuals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns { template <typename T_Scalar, typename T_Vector> class XxVector; }
namespace dns { template <typename T_Scalar, typename T_Matrix> class XxMatrix; }
namespace csc { template <typename T_Int, typename T_Scalar, typename T_Matrix> class XxMatrix; }
} // namespace cla3p
/*-------------------------------------------------*/

/*
 * Generic Update Operator
 */
template <typename T_Virtual> 
void operator+=(
		typename T_Virtual::value_type& A,
		const cla3p::VirtualEntity<typename T_Virtual::value_type,T_Virtual>& vB)
{
	vB.addToTarget(1, A);
}

/*
 * Generic Update Operator
 */
template <typename T_Virtual> 
void operator-=(
		typename T_Virtual::value_type& A,
		const cla3p::VirtualEntity<typename T_Virtual::value_type,T_Virtual>& vB)
{
	vB.scale(-1).addToTarget(1, A);
}

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_update
 * @brief Update a dense vector with another dense vector.
 *
 * Performs the operation <b>Y = Y + X</b>
 *
 * @param[in,out] Y vector to be updated.
 * @param[in] X The rhs vector.
 */
template <typename T_Vector>
void operator+=(
		cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& Y,
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X);

/**
 * @ingroup module_index_math_operators_update
 * @brief Update a dense vector with another dense vector.
 *
 * Performs the operation <b>Y = Y - X</b>
 *
 * @param[in,out] Y vector to be updated.
 * @param[in] X The rhs vector.
 */
template <typename T_Vector>
void operator-=(
		cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& Y,
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X);

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_update
 * @brief Update a dense matrix with another compatible dense matrix.
 *
 * Performs the operation <b>A = A + B</b>
 *
 * @param[in,out] A matrix to be updated.
 * @param[in] B The rhs matrix.
 */
template <typename T_Matrix>
void operator+=(
		cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B);

/**
 * @ingroup module_index_math_operators_update
 * @brief Update a dense matrix with another compatible dense matrix.
 *
 * Performs the operation <b>A = A - B</b>
 *
 * @param[in,out] A matrix to be updated.
 * @param[in] B The rhs matrix.
 */
template <typename T_Matrix>
void operator-=(
		cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B);

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_update
 * @brief Update a sparse matrix with another compatible sparse matrix.
 *
 * Performs the operation <b>A = A + B</b>
 *
 * @param[in,out] A sparse matrix to be updated.
 * @param[in] B The rhs sparse matrix.
 */
template <typename T_Matrix>
void operator+=(
		cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B);

/**
 * @ingroup module_index_math_operators_update
 * @brief Update a sparse matrix with another compatible sparse matrix.
 *
 * Performs the operation <b>A = A - B</b>
 *
 * @param[in,out] A sparse matrix to be updated.
 * @param[in] B The rhs sparse matrix.
 */
template <typename T_Matrix>
void operator-=(
		cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B);

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_UPDATE_HPP_
