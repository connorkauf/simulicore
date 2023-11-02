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

#ifndef CLA3P_DECOMP_LDLT_CHECKS_HPP_
#define CLA3P_DECOMP_LDLT_CHECKS_HPP_

#include "cla3p/error/error.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

template <typename T>
void ldlt_decomp_input_check(const T& mat)
{
	bool supported_prop = (mat.prop().isSymmetric() || mat.prop().isHermitian()); 

	if(mat.empty()) {
		throw err::InvalidOp("Input matrix is empty");
	} else if(!supported_prop) {
		throw err::InvalidOp("Matrices with property " + mat.prop().name() + " not supported for NPD Cholesky (LDL') decomposition");
	} // valid prop

	if(mat.nrows() != mat.ncols()) {
		throw err::InvalidOp("Only square matrices are supported for linear decomposition");
	} // square
}

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DECOMP_LDLT_CHECKS_HPP_
