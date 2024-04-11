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
 */

#include "cla3p/virtuals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns { template <typename T_Scalar, typename T_Vector> class XxVector; }
} // namespace cla3p
/*-------------------------------------------------*/

/* 
 * Combinations                  | Valid Op | Return Type
 * ------------------------------------------------------
 * XxVector * XxVector           | NO       | N/A
 * XxVector * VirtualVector      | YES      | VirtualProdMm
 * XxVector * VirtualProdMv      | NO       | N/A
 *                               |          |
 * VirtualVector * XxVector      | YES      | T_Scalar
 * VirtualVector * VirtualVector | NO       | N/A (ambiguous)
 * VirtualVector * VirtualProdMv | YES      | T_Scalar
 *                               |          |
 * VirtualProdMv * XxVector      | NO       | N/A
 * VirtualProdMv * VirtualVector | YES      | T_Matrix
 * VirtualProdMv * VirtualProdMv | NO       | N/A
 */

/*
 * XxVector * VirtualVector
 */
template <typename T_Vector>
cla3p::VirtualProdMm<typename cla3p::TypeTraits<T_Vector>::matrix_type> operator*(
	const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X, 
	const cla3p::VirtualVector<T_Vector>& vY) 
{ 
	using T_Matrix = typename cla3p::TypeTraits<T_Vector>::matrix_type;
	cla3p::VirtualMatrix<T_Matrix> vA(X.rmatrix().get());
	cla3p::VirtualMatrix<T_Matrix> vB(vY);
	cla3p::VirtualProdMm<T_Matrix> ret(vA,vB);
	return ret;
}

/*-------------------------------------------------*/

/*
 * VirtualVector * XxVector
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
 * VirtualVector * VirtualProdMv
 */
template <typename T_Matrix, typename T_Vector>
typename T_Vector::value_type operator*(
	const cla3p::VirtualVector<T_Vector>& vX, 
	const cla3p::VirtualProdMv<T_Matrix,T_Vector>& vY) 
{ 
	return (vX * vY.evaluate());
}

/*-------------------------------------------------*/

/*
 * VirtualProdMv * VirtualVector
 */
template <typename T_Matrix, typename T_Vector>
typename cla3p::TypeTraits<T_Vector>::matrix_type operator*(
	const cla3p::VirtualProdMv<T_Matrix,T_Vector>& vX, 
	const cla3p::VirtualVector<T_Vector>& vY) 
{ 
	return vY.evaluateOuter(vX.evaluate());
}

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_MULTVV_HPP_
