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
 * Global updating operator definitions
 */

#include "cla3p/virtuals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
template <typename T_Scalar, typename T_Object> class XxObject;
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/*
 * Combinations                   | Valid Op | Return Type
 * -------------------------------------------------------
 * XxObject += XxObject           | YES      | T_Object&
 * XxObject -= XxObject           | YES      | T_Object&
 *                                |          |
 * XxObject += VirtualEntity      | YES      | T_Object&
 * XxObject -= VirtualEntity      | YES      | T_Object&
 */

/**
 * @ingroup module_index_math_operators_update
 * @brief Update an object with another compatible object.
 *
 * Performs the operation <b>A = A + B</b>
 *
 * @param[in,out] A object to be updated.
 * @param[in] B The rhs object.
 */
template <typename T_Object>
void operator+=(
		cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& A,
		const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& B)
{
	cla3p::ops::update(1, B, A);
}

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
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B)
{
	cla3p::ops::update(1, B, A);
}

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_update
 * @brief Update an object with another compatible object.
 *
 * Performs the operation <b>A = A - B</b>
 *
 * @param[in,out] A object to be updated.
 * @param[in] B The rhs object.
 */
template <typename T_Object>
void operator-=(
		cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& A,
		const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& B)
{
	cla3p::ops::update(-1, B, A);
}

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
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B)
{
	cla3p::ops::update(-1, B, A);
}

/*-------------------------------------------------*/

/*
 * XxObject += VirtualEntity
 */
template <typename T_Object, typename T_Virtual> 
void operator+=(
		//const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& A,
		T_Object& A,
		const cla3p::VirtualEntity<T_Object,T_Virtual>& vB)
{
	vB.update(1, A);
}

/*-------------------------------------------------*/

/*
 * XxObject -= VirtualEntity
 */
template <typename T_Object, typename T_Virtual> 
void operator-=(
		//const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& A,
		T_Object& A,
		const cla3p::VirtualEntity<T_Object,T_Virtual>& vB)
{
	vB.update(-1, A);
}

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_UPDATE_HPP_
