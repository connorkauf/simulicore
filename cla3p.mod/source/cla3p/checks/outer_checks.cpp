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

// this file inc
#include "cla3p/checks/outer_checks.hpp"

// system

// 3rd

// cla3p
#include "cla3p/error/exceptions.hpp"
#include "cla3p/error/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
void outer_product_consistency_check(bool /*conjop*/, 
		uint_t nrowsA, uint_t ncolsA, const Property& prA, 
		uint_t sizeX, uint_t sizeY)
{
	if(nrowsA != sizeX || ncolsA != sizeY) {
		throw err::NoConsistency(msg::InvalidDimensions());
	}

	if(!(prA.isGeneral() || prA.isSymmetric() || prA.isHermitian())) {
		throw err::NoConsistency(msg::InvalidProperty());
	} // valid props

#if 0
	if(prA.isHermitian() && !conjop) {
		throw err::NoConsistency(msg::OpNotAllowed());
	}

	if(prA.isSymmetric() && conjop) {
		throw err::NoConsistency(msg::OpNotAllowed());
	}
#endif
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
