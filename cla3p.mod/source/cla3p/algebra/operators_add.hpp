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

#ifndef CLA3P_OPERATORS_ADD_HPP_
#define CLA3P_OPERATORS_ADD_HPP_

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
 * Combinations                  | Valid Op | Return Type
 * ------------------------------------------------------
 * XxObject + XxObject           | YES      | T_Object
 * XxObject - XxObject           | YES      | T_Object
 *                               |          |
 * XxObject + VirtualEntity      | YES      | T_Object
 * XxObject - VirtualEntity      | YES      | T_Object
 *                               |          |
 * VirtualEntity + XxObject      | YES      | T_Object
 * VirtualEntity - XxObject      | YES      | T_Object
 *                               |          |
 * VirtualEntity + VirtualEntity | YES      | T_Object
 * VirtualEntity - VirtualEntity | YES      | T_Object
 */

/**
 * @ingroup module_index_math_operators_add
 * @brief Adds two compatible vectors.
 *
 * Performs the operation <b>A + B</b>
 *
 * @param[in] A The first vector.
 * @param[in] B The second vector.
 * @return The vector that is the sum of the two.
 */
template <typename T_Vector>
T_Vector operator+(
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& A,
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& B);

/**
 * @ingroup module_index_math_operators_add
 * @brief Adds two compatible matrices.
 *
 * Performs the operation <b>A + B</b>
 *
 * @param[in] A The first matrix.
 * @param[in] B The second matrix.
 * @return The matrix that is the sum of the two.
 */
template <typename T_Matrix>
T_Matrix operator+(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B);

/**
 * @ingroup module_index_math_operators_add
 * @brief Subtracts two compatible vectors.
 *
 * Performs the operation <b>A - B</b>
 *
 * @param[in] A The first vector.
 * @param[in] B The second vector.
 * @return The vector that is the difference of the two.
 */
template <typename T_Vector>
T_Vector operator-(
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& A,
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& B);

/**
 * @ingroup module_index_math_operators_add
 * @brief Subtracts two compatible matrices.
 *
 * Performs the operation <b>A - B</b>
 *
 * @param[in] A The first matrix.
 * @param[in] B The second matrix.
 * @return The matrix that is the difference of the two.
 */
template <typename T_Matrix>
T_Matrix operator-(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B);

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_add
 * @brief Adds two compatible sparse matrices.
 *
 * Performs the operation <b>A + B</b>
 *
 * @param[in] A The first sparse matrix.
 * @param[in] B The second sparse matrix.
 * @return The sparse matrix that is the sum of the two.
 */
template <typename T_Matrix>
T_Matrix operator+(
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B);

/**
 * @ingroup module_index_math_operators_add
 * @brief Subtracts two compatible sparse matrices.
 *
 * Performs the operation <b>A - B</b>
 *
 * @param[in] A The first sparse matrix.
 * @param[in] B The second sparse matrix.
 * @return The sparse matrix that is the difference of the two.
 */
template <typename T_Matrix>
T_Matrix operator-(
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B);

/*-------------------------------------------------*/

/*
 * XxObject + VirtualEntity
 */
template <typename T_Object, typename T_Virtual> 
T_Object operator+(
		const T_Object& A,
		const cla3p::VirtualEntity<T_Object,T_Virtual>& vB)
{
	T_Object ret = A.copy();
	ret += vB;
	return ret;
}

/*
 * XxObject - VirtualEntity
 */
template <typename T_Object, typename T_Virtual> 
T_Object operator-(
		const T_Object& A,
		const cla3p::VirtualEntity<T_Object,T_Virtual>& vB)
{
	T_Object ret = A.copy();
	ret -= vB;
	return ret;
}

/*-------------------------------------------------*/

/*
 * VirtualEntity + XxObject
 */
template <typename T_Object, typename T_Virtual>
T_Object operator+(
		const cla3p::VirtualEntity<T_Object,T_Virtual>& vA,
		const T_Object& B)
{
	T_Object ret = vA.evaluate();
	ret += B;
	return ret;
}

/*
 * VirtualEntity - XxObject
 */
template <typename T_Object, typename T_Virtual> 
T_Object operator-(
		const cla3p::VirtualEntity<T_Object,T_Virtual>& vA,
		const T_Object& B)
{
	T_Object ret = vA.evaluate();
	ret -= B;
	return ret;
}

/*-------------------------------------------------*/

/*
 * VirtualEntity + VirtualEntity
 */
template <typename T_Object, typename T_Virtual> 
T_Object operator+(
		const cla3p::VirtualEntity<T_Object,T_Virtual>& vA,
		const cla3p::VirtualEntity<T_Object,T_Virtual>& vB)
{
	T_Object ret = vA.evaluate();
	ret += vB;
	return ret;
}

/*
 * VirtualEntity - VirtualEntity
 */
template <typename T_Object, typename T_Virtual> 
T_Object operator-(
		const cla3p::VirtualEntity<T_Object,T_Virtual>& vA,
		const cla3p::VirtualEntity<T_Object,T_Virtual>& vB)
{
	T_Object ret = vA.evaluate();
	ret -= vB;
	return ret;
}

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_ADD_HPP_
