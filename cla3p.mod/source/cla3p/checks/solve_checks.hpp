/*
 * Copyright (c) 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
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

#ifndef CLA3P_SOLVE_CHECKS_HPP_
#define CLA3P_SOLVE_CHECKS_HPP_

#include "cla3p/error/error.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

template <typename T>
void default_solve_input_check(uint_t n, const T& rhs)
{
	bool supported_prop = rhs.prop().isGeneral();

	if(rhs.nrows() != n) {
		throw err::InvalidOp("Mismatching dimensions for linear solution stage");
	} // dim check

	if(rhs.empty()) {
		throw err::InvalidOp("Input rhs matrix is empty");
	} else if(!supported_prop) {
		throw err::InvalidOp(rhs.prop().name() + " not supported for rhs in linear solution stage");
	} // valid prop
}

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_SOLVE_CHECKS_HPP_
