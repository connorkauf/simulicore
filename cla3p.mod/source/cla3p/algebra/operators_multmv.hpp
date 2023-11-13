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

#ifndef CLA3P_OPERATORS_MULTMV_HPP_
#define CLA3P_OPERATORS_MULTMV_HPP_

/**
 * @file
 * Global multiplication operator definitions
 */

#include "cla3p/virtuals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
template <typename T_Scalar, typename T_Vector> class XxVector;
template <typename T_Scalar, typename T_Matrix> class XxMatrix;
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/* 
 * Combinations                  | Valid Op | Return Type
 * ------------------------------------------------------
 * XxMatrix x XxVector           | YES      | VirtualPairMv 
 * XxMatrix x VirtualVector      | YES      | VirtualPairMv
 * XxMatrix x VirtualPairMv      | YES      | T_Vector
 *                               |          |
 * VirtualMatrix x XxVector      | YES      | VirtualPairMv
 * VirtualMatrix x VirtualVector | YES      | VirtualPairMv
 * VirtualMatrix x VirtualPairMv | YES      | T_Vector
 *                               |          |
 * VirtualPairMm x XxVector      | YES      | T_Vector
 * VirtualPairMm x VirtualVector | YES      | T_Vector
 * VirtualPairMm x VirtualPairMv | YES      | T_Vector
 */

/**
 * @ingroup module_index_math_operators_mult
 * @brief Multiplies a matrix with a vector.
 *
 * Performs the operation <b>A * X</b>
 *
 * @param[in] A The input matrix.
 * @param[in] X The input vector.
 * @return The virtual product.
 */
template <typename T_Vector, typename T_Matrix>
cla3p::VirtualPairMv<T_Vector> operator*(
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X) 
{ 
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	cla3p::VirtualVector<T_Vector> vX(X.self());
	cla3p::VirtualPairMv<T_Vector> ret(vA,vX);
	return ret;
}

/*-------------------------------------------------*/

/*
 * XxMatrix x VirtualVector
 */
template <typename T_Vector, typename T_Matrix>
cla3p::VirtualPairMv<T_Vector> operator*(
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::VirtualVector<T_Vector>& vX) 
{ 
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	cla3p::VirtualPairMv<T_Vector> ret(vA,vX);
	return ret;
}

/*-------------------------------------------------*/

/*
 * XxMatrix x VirtualPairMv
 */
template <typename T_Vector, typename T_Matrix>
T_Vector operator*(
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::VirtualPairMv<T_Vector>& vX) 
{ 
	return (A * vX.evaluate()).evaluate();
}

/*-------------------------------------------------*/

/*
 * VirtualMatrix x XxVector
 */
template <typename T_Vector, typename T_Matrix>
cla3p::VirtualPairMv<T_Vector> operator*(
	const cla3p::VirtualMatrix<T_Matrix>& vA, 
	const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X) 
{ 
	cla3p::VirtualVector<T_Vector> vX(X.self());
	cla3p::VirtualPairMv<T_Vector> ret(vA,vX);
	return ret;
}

/*-------------------------------------------------*/

/*
 * VirtualMatrix x VirtualVector
 */
template <typename T_Vector, typename T_Matrix>
cla3p::VirtualPairMv<T_Vector> operator*(
	const cla3p::VirtualMatrix<T_Matrix>& vA, 
	const cla3p::VirtualVector<T_Vector>& vX) 
{ 
	cla3p::VirtualPairMv<T_Vector> ret(vA,vX);
	return ret;
}

/*-------------------------------------------------*/

/*
 * VirtualMatrix x VirtualPairMv
 */
template <typename T_Vector, typename T_Matrix>
T_Vector operator*(
	const cla3p::VirtualMatrix<T_Matrix>& vA, 
	const cla3p::VirtualPairMv<T_Vector>& vX) 
{ 
	return (vA * vX.evaluate()).evaluate();
}

/*-------------------------------------------------*/

/*
 * VirtualPairMm x XxVector
 */
template <typename T_Vector, typename T_Matrix>
T_Vector operator*(
	const cla3p::VirtualPairMm<T_Matrix>& vA, 
	const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X) 
{ 
	return (vA.evaluate() * X).evaluate();
}

/*-------------------------------------------------*/

/*
 * VirtualPairMm x VirtualVector
 */
template <typename T_Vector, typename T_Matrix>
T_Vector operator*(
	const cla3p::VirtualPairMm<T_Matrix>& vA, 
	const cla3p::VirtualVector<T_Vector>& vX) 
{ 
	return (vA.evaluate() * vX).evaluate();
}

/*-------------------------------------------------*/

/*
 * VirtualPairMm x VirtualPairMv
 */
template <typename T_Vector, typename T_Matrix>
T_Vector operator*(
	const cla3p::VirtualPairMm<T_Matrix>& vA, 
	const cla3p::VirtualPairMv<T_Vector>& vX) 
{ 
	return (vA.evaluate() * vX.evaluate()).evaluate();
}

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_MULTMV_HPP_
