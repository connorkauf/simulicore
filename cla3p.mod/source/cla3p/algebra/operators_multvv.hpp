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

#ifndef CLA3P_OPERATORS_MULTVV_HPP_
#define CLA3P_OPERATORS_MULTVV_HPP_

/**
 * @file
 * Global multiplication operator definitions
 */

#include "cla3p/virtuals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
template <typename T_Scalar, typename T_Vector> class XxVector;
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/* 
 * Combinations                  | Valid Op | Return Type
 * ------------------------------------------------------
 * XxVector x XxVector           | NO       | N/A
 * XxVector x VirtualVector      | YES      | VirtualPairMm
 * XxVector x VirtualPairMv      | NO       | N/A
 *                               |          |
 * VirtualVector x XxVector      | YES      | T_Scalar
 * VirtualVector x VirtualVector | NO       | N/A (ambiguous)
 * VirtualVector x VirtualPairMv | YES      | T_Scalar
 *                               |          |
 * VirtualPairMv x XxVector      | NO       | N/A
 * VirtualPairMv x VirtualVector | YES      | T_Matrix
 * VirtualPairMv x VirtualPairMv | NO       | N/A
 */

/*
 * XxVector x VirtualVector
 */
template <typename T_Vector>
cla3p::VirtualPairMm<typename cla3p::TypeTraits<T_Vector>::matrix_type> operator*(
	const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X, 
	const cla3p::VirtualVector<T_Vector>& vY) 
{ 
	cla3p::VirtualMatrix<typename cla3p::TypeTraits<T_Vector>::matrix_type> vA(X.rmatrix());
	cla3p::VirtualMatrix<typename cla3p::TypeTraits<T_Vector>::matrix_type> vB = vY.asVirtualMatrix();
	cla3p::VirtualPairMm<T_Vector> ret(vA,vB);
	return ret;
}

/*-------------------------------------------------*/

/*
 * VirtualVector x XxVector
 */
template <typename T_Vector>
typename T_Vector::value_type operator*(
	const cla3p::VirtualVector<T_Vector>& vX, 
	const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& Y) 
{ 
	return vX.evaluateInner(Y.self());
}

/*-------------------------------------------------*/

/*
 * VirtualVector x VirtualPairMv
 */
template <typename T_Vector>
typename T_Vector::value_type operator*(
	const cla3p::VirtualVector<T_Vector>& vX, 
	const cla3p::VirtualPairMv<T_Vector>& vY) 
{ 
	return (vX * vY.evaluate());
}

/*-------------------------------------------------*/

/*
 * VirtualPairMv x VirtualVector
 */
template <typename T_Vector>
typename cla3p::TypeTraits<T_Vector>::matrix_type operator*(
	const cla3p::VirtualPairMv<T_Vector>& vX, 
	const cla3p::VirtualVector<T_Vector>& vY) 
{ 
	return vY.evaluateOuter(vX.evaluate());
}

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_MULTVV_HPP_
