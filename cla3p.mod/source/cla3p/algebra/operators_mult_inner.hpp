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

#ifndef CLA3P_OPERATORS_MULT_INNER_HPP_
#define CLA3P_OPERATORS_MULT_INNER_HPP_

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
 * VirtualRowVec x VirtualVector
 */
template <typename T_Vector>
typename T_Vector::value_type operator*(
		const cla3p::VirtualRowVec<T_Vector>& vX,
		const cla3p::VirtualVector<T_Vector>& vY)
{
	return vX.evaluateInner(vY);
}

/*
 * VirtualRowVec x Vector
 */
template <typename T_Vector>
typename T_Vector::value_type operator*(
		const cla3p::VirtualRowVec<T_Vector>& vX,
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& Y)
{
	cla3p::VirtualVector<T_Vector> vY(Y.self());
	return (vX * vY);
}

/*
 * VirtualRowVec x VirtualEntity
 */
template <typename T_Vector, typename T_Virtual>
typename T_Vector::value_type operator*(
		const cla3p::VirtualRowVec<T_Vector>& vX,
		const cla3p::VirtualEntity<typename T_Virtual::value_type,T_Virtual>& vY)
{
	return (vX * vY.evaluate());
}

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_MULT_INNER_HPP_
