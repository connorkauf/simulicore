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
 * Global addition/subtraction operator definitions
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
 * @brief Adds two compatible objects.
 *
 * Performs the operation <b>A + B</b>
 *
 * @param[in] A The first object.
 * @param[in] B The second object.
 * @return The object that is the sum of the two.
 */
template <typename T_Object>
T_Object operator+(
		const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& A,
		const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& B)
{
	return cla3p::ops::add(1, A, 1, B);
}

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_add
 * @brief Subtracts two compatible objects.
 *
 * Performs the operation <b>A - B</b>
 *
 * @param[in] A The first object.
 * @param[in] B The second object.
 * @return The object that is the difference of the two.
 */
template <typename T_Object>
T_Object operator-(
		const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& A,
		const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& B)
{
	return cla3p::ops::add(1, A, -1, B);
}

/*-------------------------------------------------*/

/*
 * XxObject + VirtualEntity
 */
template <typename T_Object, typename T_Virtual> 
T_Object operator+(
		//const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& A,
		const T_Object& A,
		const cla3p::VirtualEntity<T_Object,T_Virtual>& vB)
{
	T_Object ret = A.copy();
	ret += vB;
	return ret;
}

/*-------------------------------------------------*/

/*
 * XxObject - VirtualEntity
 */
template <typename T_Object, typename T_Virtual> 
T_Object operator-(
		//const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& A,
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
		//const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& B)
		const T_Object& B)
{
	T_Object ret = vA.evaluate();
	ret += B;
	return ret;
}

/*-------------------------------------------------*/

/*
 * VirtualEntity + XxObject
 */
template <typename T_Object, typename T_Virtual> 
T_Object operator-(
		const cla3p::VirtualEntity<T_Object,T_Virtual>& vA,
		//const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& B)
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

/*-------------------------------------------------*/

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
