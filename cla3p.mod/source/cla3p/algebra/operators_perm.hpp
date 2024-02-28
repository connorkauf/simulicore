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

#ifndef CLA3P_OPERATORS_PERM_HPP_
#define CLA3P_OPERATORS_PERM_HPP_

/**
 * @file
 * Global permutation operator definitions
 */

#include "cla3p/virtuals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
template <typename T_Int> class PxMatrix;
namespace dns { template <typename T_Scalar, typename T_Vector> class XxVector; }
namespace dns { template <typename T_Scalar, typename T_Matrix> class XxMatrix; }
namespace csc { template <typename T_Int, typename T_Scalar, typename T_Matrix> class XxMatrix; }
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_perm
 * @brief Multiplies permutation matrix with a vector.
 *
 * Performs the operation <b>P * X</b>
 *
 * @param[in] P The input permutation matrix.
 * @param[in] X The input vector.
 * @return The permuted vector.
 */
template <typename T_Int, typename T_Vector>
T_Vector operator*(
		const cla3p::PxMatrix<T_Int>& P, 
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X);

/*-------------------------------------------------*/

template <typename T_Int, typename T_Vector>
T_Vector operator*(
		const cla3p::PxMatrix<T_Int>& P, 
		const cla3p::VirtualVector<T_Vector>& vX)
{
	return (P * vX.evaluate());
}

/*-------------------------------------------------*/

template <typename T_Int, typename T_Vector>
T_Vector operator*(
		const cla3p::PxMatrix<T_Int>& P, 
		const cla3p::VirtualProdMv<T_Vector>& vX)
{
	return (P * vX.evaluate());
}

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_perm
 * @brief Multiplies permutation matrix with a general dense matrix.
 *
 * Performs the operation <b>P * A</b>
 *
 * @param[in] P The input permutation matrix.
 * @param[in] A The input general matrix.
 * @return The permuted matrix.
 */
template <typename T_Int, typename T_Matrix>
T_Matrix operator*(
		const cla3p::PxMatrix<T_Int>& P, 
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A);

/*-------------------------------------------------*/

template <typename T_Int, typename T_Matrix>
T_Matrix operator*(
		const cla3p::PxMatrix<T_Int>& P, 
		const cla3p::VirtualMatrix<T_Matrix>& vA)
{
	return (P * vA.evaluate());
}

/*-------------------------------------------------*/

template <typename T_Int, typename T_Matrix>
T_Matrix operator*(
		const cla3p::PxMatrix<T_Int>& P, 
		const cla3p::VirtualProdMm<T_Matrix>& vA)
{
	return (P * vA.evaluate());
}

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_perm
 * @brief Multiplies permutation matrix with a general sparse matrix.
 *
 * Performs the operation <b>P * A</b>
 *
 * @param[in] P The input permutation matrix.
 * @param[in] A The input general matrix.
 * @return The permuted matrix.
 */
template <typename T_Int, typename T_Matrix>
T_Matrix operator*(
		const cla3p::PxMatrix<T_Int>& P, 
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A);

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_perm
 * @brief Multiplies general dense matrix with a permutation matrix.
 *
 * Performs the operation <b>A * P</b>
 *
 * @param[in] A The input general matrix.
 * @param[in] P The input permutation matrix.
 * @return The permuted matrix.
 */

template <typename T_Int, typename T_Matrix>
T_Matrix operator*(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
		const cla3p::PxMatrix<T_Int>& P);

/*-------------------------------------------------*/

template <typename T_Int, typename T_Matrix>
T_Matrix operator*(
		const cla3p::VirtualMatrix<T_Matrix>& vA,
		const cla3p::PxMatrix<T_Int>& P) 
{
	return (P * vA.evaluate());
}

/*-------------------------------------------------*/

template <typename T_Int, typename T_Matrix>
T_Matrix operator*(
		const cla3p::VirtualProdMm<T_Matrix>& vA,
		const cla3p::PxMatrix<T_Int>& P) 
{
	return (P * vA.evaluate());
}

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_perm
 * @brief Multiplies general sparse matrix with a permutation matrix.
 *
 * Performs the operation <b>A * P</b>
 *
 * @param[in] A The input general matrix.
 * @param[in] P The input permutation matrix.
 * @return The permuted matrix.
 */

template <typename T_Int, typename T_Matrix>
T_Matrix operator*(
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A, 
		const cla3p::PxMatrix<T_Int>& P);

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_perm
 * @brief Multiplies a permutation matrix with a permutation matrix.
 *
 * Performs the operation <b>P * Q</b>
 *
 * @param[in] P The input permutation matrix.
 * @param[in] Q The input permutation matrix.
 * @return The permuted permutation matrix.
 */
template <typename T_Int>
cla3p::PxMatrix<T_Int> operator*(
		const cla3p::PxMatrix<T_Int>& P,
		const cla3p::PxMatrix<T_Int>& Q);

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_PERM_HPP_
