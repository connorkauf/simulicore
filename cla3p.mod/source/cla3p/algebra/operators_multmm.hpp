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

#ifndef CLA3P_OPERATORS_MULTMM_HPP_
#define CLA3P_OPERATORS_MULTMM_HPP_

/**
 * @file
 * Global multiplication operator definitions
 */

#include "cla3p/virtuals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
template <typename T_Scalar, typename T_Matrix> class XxMatrix;
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/*
 * Combinations                  | Valid Op | Return Type
 * ------------------------------------------------------
 * XxMatrix * XxMatrix           | YES      | VirtualProdMm
 * XxMatrix * VirtualMatrix      | YES      | VirtualProdMm
 * XxMatrix * VirtualProdMm      | YES      | T_Matrix
 *                               |          |
 * VirtualMatrix * XxMatrix      | YES      | VirtualProdMm
 * VirtualMatrix * VirtualMatrix | YES      | VirtualProdMm
 * VirtualMatrix * VirtualProdMm | YES      | T_Matrix
 *                               |          |
 * VirtualProdMm * XxMatrix      | YES      | T_Matrix
 * VirtualProdMm * VirtualMatrix | YES      | T_Matrix
 * VirtualProdMm * VirtualProdMm | YES      | T_Matrix
*/

/**
 * @ingroup module_index_math_operators_mult
 * @brief Multiplies a matrix with a matrix.
 *
 * Performs the operation <b>A * B</b>
 *
 * @param[in] A The lhs input matrix.
 * @param[in] B The rhs input matrix.
 * @return The virtual product.
 */
template <typename T_Matrix>
cla3p::VirtualProdMm<T_Matrix> operator*(
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B) 
{
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	cla3p::VirtualMatrix<T_Matrix> vB(B.self());
	cla3p::VirtualProdMm<T_Matrix> ret(vA,vB);
	return ret;
}

/*-------------------------------------------------*/

/*
 * XxMatrix * VirtualMatrix
 */
template <typename T_Matrix>
cla3p::VirtualProdMm<T_Matrix> operator*(
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::VirtualMatrix<T_Matrix>& vB) 
{ 
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	cla3p::VirtualProdMm<T_Matrix> ret(vA,vB);
	return ret;
}

/*-------------------------------------------------*/

/*
 * XxMatrix * VirtualProdMm
 */
template <typename T_Matrix>
T_Matrix operator*(
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::VirtualProdMm<T_Matrix>& vB) 
{ 
	return (A * vB.evaluate()).evaluate();
}

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_mult
 * @brief Multiplies a sparse matrix with a dense matrix.
 *
 * Performs the operation <b>A * B</b>
 *
 * @param[in] A The lhs input matrix.
 * @param[in] B The rhs input matrix.
 * @return The virtual product.
 */
template <typename T_CscMatrix, typename T_DnsMatrix>
T_DnsMatrix operator*(
	const cla3p::csc::XxMatrix<typename T_CscMatrix::index_type,typename T_CscMatrix::value_type,T_CscMatrix>& A, 
	const cla3p::dns::XxMatrix<typename T_DnsMatrix::value_type,T_DnsMatrix>& B) 
{
	using T_Scalar = typename T_CscMatrix::value_type;
	return cla3p::ops::mult(T_Scalar(1), cla3p::op_t::N, A, B);
}

/*-------------------------------------------------*/

/*
 * XxMatrix * VirtualMatrix
 */
template <typename T_Matrix>
T_Matrix operator*(
	const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::VirtualMatrix<T_Matrix>& vB) 
{ 
	return (A * vB.evaluate());
}

/*-------------------------------------------------*/

/*
 * XxMatrix * VirtualProdMm
 */
template <typename T_Matrix>
T_Matrix operator*(
	const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::VirtualProdMm<T_Matrix>& vB) 
{ 
	return (A * vB.evaluate());
}

/*-------------------------------------------------*/

/*
 * VirtualMatrix * XxMatrix
 */
template <typename T_Matrix>
cla3p::VirtualProdMm<T_Matrix> operator*(
	const cla3p::VirtualMatrix<T_Matrix>& vA, 
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B) 
{ 
	cla3p::VirtualMatrix<T_Matrix> vB(B.self());
	cla3p::VirtualProdMm<T_Matrix> ret(vA,vB);
	return ret;
}

/*-------------------------------------------------*/

/*
 * VirtualMatrix * VirtualMatrix
 */
template <typename T_Matrix>
cla3p::VirtualProdMm<T_Matrix> operator*(
	const cla3p::VirtualMatrix<T_Matrix>& vA, 
	const cla3p::VirtualMatrix<T_Matrix>& vB) 
{ 
	cla3p::VirtualProdMm<T_Matrix> ret(vA,vB);
	return ret;
}

/*-------------------------------------------------*/

/*
 * VirtualMatrix * VirtualProdMm
 */
template <typename T_Matrix>
T_Matrix operator*(
	const cla3p::VirtualMatrix<T_Matrix>& vA, 
	const cla3p::VirtualProdMm<T_Matrix>& vB) 
{ 
	return (vA * vB.evaluate()).evaluate();
}

/*-------------------------------------------------*/

/*
 * VirtualProdMm * XxMatrix
 */
template <typename T_Matrix>
T_Matrix operator*(
	const cla3p::VirtualProdMm<T_Matrix>& vA, 
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B) 
{ 
	return (vA.evaluate() * B).evaluate();
}

/*-------------------------------------------------*/

/*
 * VirtualProdMm * VirtualMatrix
 */
template <typename T_Matrix>
T_Matrix operator*(
	const cla3p::VirtualProdMm<T_Matrix>& vA, 
	const cla3p::VirtualMatrix<T_Matrix>& vB) 
{ 
	return (vA.evaluate() * vB).evaluate();
}

/*-------------------------------------------------*/

/*
 * VirtualProdMm * VirtualProdMm
 */
template <typename T_Matrix>
T_Matrix operator*(
	const cla3p::VirtualProdMm<T_Matrix>& vA, 
	const cla3p::VirtualProdMm<T_Matrix>& vB) 
{ 
	return (vA.evaluate() * vB.evaluate()).evaluate();
}

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_MULTMM_HPP_
