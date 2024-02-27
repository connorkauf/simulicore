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

#ifndef CLA3P_MATRIX_MATH_CHECKS_HPP_
#define CLA3P_MATRIX_MATH_CHECKS_HPP_

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

void mult_dim_check(
		uint_t nrowsA, uint_t ncolsA, const Operation& opA, 
		uint_t nrowsB, uint_t ncolsB, const Operation& opB, 
		uint_t nrowsC, uint_t ncolsC);

void mat_x_vec_mult_check(const Operation& opA, 
		const Property& prA, uint_t nrowsA, uint_t ncolsA, 
		uint_t sizeX, uint_t sizeY);

#if 0
void mat_x_mat_mult_check(
		const Property& prA, uint_t nrowsA, uint_t ncolsA, const Operation& opA, 
		const Property& prB, uint_t nrowsB, uint_t ncolsB, const Operation& opB, 
		const Property& prC, uint_t nrowsC, uint_t ncolsC);
#endif

void trivec_mult_replace_check(const Property& prA, 
		uint_t nrowsA, uint_t ncolsA, const Operation& opA, 
		uint_t sizeX);

void trimat_mult_replace_check(side_t sideA, 
		const Property& prA, uint_t nrowsA, uint_t ncolsA, const Operation& opA, 
		const Property& prB, uint_t nrowsB, uint_t ncolsB);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_MATRIX_MATH_CHECKS_HPP_
