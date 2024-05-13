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

#ifndef CLA3P_DECOMP_AUTO_CHECKS_HPP_
#define CLA3P_DECOMP_AUTO_CHECKS_HPP_

/**
 * @file
 */

#include "cla3p/error/exceptions.hpp"
#include "cla3p/checks/decomp_xx_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

template <typename T_Matrix>
void auto_decomp_input_check(const T_Matrix& mat)
{
	decomp_generic_check(mat);

	bool supported_prop = (mat.prop().isGeneral() || mat.prop().isSymmetric() || mat.prop().isHermitian());

	if(!supported_prop) {
		throw err::InvalidOp("Matrices with property " + mat.prop().name() + " not supported for linear decomposition");
	} // valid prop
}

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DECOMP_AUTO_CHECKS_HPP_
