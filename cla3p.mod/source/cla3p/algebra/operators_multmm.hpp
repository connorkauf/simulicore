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
 * XxMatrix x XxMatrix           | YES      | VirtualPairMm
 * XxMatrix x VirtualMatrix      | YES      | VirtualPairMm
 * XxMatrix x VirtualPairMm      | YES      | T_Matrix
 *                               |          |
 * VirtualMatrix x XxMatrix      | YES      | VirtualPairMm
 * VirtualMatrix x VirtualMatrix | YES      | VirtualPairMm
 * VirtualMatrix x VirtualPairMm | YES      | T_Matrix
 *                               |          |
 * VirtualPairMm x XxMatrix      | YES      | T_Matrix
 * VirtualPairMm x VirtualMatrix | YES      | T_Matrix
 * VirtualPairMm x VirtualPairMm | YES      | T_Matrix
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
cla3p::VirtualPairMm<T_Matrix> operator*(
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B) 
{
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	cla3p::VirtualMatrix<T_Matrix> vB(B.self());
	cla3p::VirtualPairMm<T_Matrix> ret(vA,vB);
	return ret;
}

/*-------------------------------------------------*/

/*
 * XxMatrix x VirtualMatrix
 */
template <typename T_Matrix>
cla3p::VirtualPairMm<T_Matrix> operator*(
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::VirtualMatrix<T_Matrix>& vB) 
{ 
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	cla3p::VirtualPairMm<T_Matrix> ret(vA,vB);
	return ret;
}

/*-------------------------------------------------*/

/*
 * XxMatrix x VirtualPairMm
 */
template <typename T_Matrix>
T_Matrix operator*(
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::VirtualPairMm<T_Matrix>& vB) 
{ 
	return (A * vB.evaluate()).evaluate();
}

/*-------------------------------------------------*/

/*
 * VirtualMatrix x XxMatrix
 */
template <typename T_Matrix>
cla3p::VirtualPairMm<T_Matrix> operator*(
	const cla3p::VirtualMatrix<T_Matrix>& vA, 
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B) 
{ 
	cla3p::VirtualMatrix<T_Matrix> vB(B.self());
	cla3p::VirtualPairMm<T_Matrix> ret(vA,vB);
	return ret;
}

/*-------------------------------------------------*/

/*
 * VirtualMatrix x VirtualMatrix
 */
template <typename T_Matrix>
cla3p::VirtualPairMm<T_Matrix> operator*(
	const cla3p::VirtualMatrix<T_Matrix>& vA, 
	const cla3p::VirtualMatrix<T_Matrix>& vB) 
{ 
	cla3p::VirtualPairMm<T_Matrix> ret(vA,vB);
	return ret;
}

/*-------------------------------------------------*/

/*
 * VirtualMatrix x VirtualPairMm
 */
template <typename T_Matrix>
T_Matrix operator*(
	const cla3p::VirtualMatrix<T_Matrix>& vA, 
	const cla3p::VirtualPairMm<T_Matrix>& vB) 
{ 
	return (vA * vB.evaluate()).evaluate();
}

/*-------------------------------------------------*/

/*
 * VirtualPairMm x XxMatrix
 */
template <typename T_Matrix>
T_Matrix operator*(
	const cla3p::VirtualPairMm<T_Matrix>& vA, 
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B) 
{ 
	return (vA.evaluate() * B).evaluate();
}

/*-------------------------------------------------*/

/*
 * VirtualPairMm x VirtualMatrix
 */
template <typename T_Matrix>
T_Matrix operator*(
	const cla3p::VirtualPairMm<T_Matrix>& vA, 
	const cla3p::VirtualMatrix<T_Matrix>& vB) 
{ 
	return (vA.evaluate() * vB).evaluate();
}

/*-------------------------------------------------*/

/*
 * VirtualPairMm x VirtualPairMm
 */
template <typename T_Matrix>
T_Matrix operator*(
	const cla3p::VirtualPairMm<T_Matrix>& vA, 
	const cla3p::VirtualPairMm<T_Matrix>& vB) 
{ 
	return (vA.evaluate() * vB.evaluate()).evaluate();
}

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_MULTMM_HPP_
