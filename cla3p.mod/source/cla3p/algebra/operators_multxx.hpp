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

#ifndef CLA3P_OPERATORS_MULT_HPP_
#define CLA3P_OPERATORS_MULT_HPP_

/**
 * @file
 */

#include "cla3p/virtuals.hpp"

/*-------------------------------------------------*/

template <typename T_Lhs, typename T_Rhs>
cla3p::VirtualProd<T_Lhs,T_Rhs>
operator*(
		const cla3p::VirtualEntity<typename T_Lhs::value_type,T_Lhs>& vA,
		const cla3p::VirtualEntity<typename T_Rhs::value_type,T_Rhs>& vB)
{
	return cla3p::VirtualProd<T_Lhs,T_Rhs>(vA.self(),vB.self());
}

#endif // CLA3P_OPERATORS_MULT_HPP_
