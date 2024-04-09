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
#include "cla3p/checks/basic_checks.hpp"

// system

// 3rd

// cla3p
#include "cla3p/error/exceptions.hpp"
#include "cla3p/error/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
void square_check(uint_t m, uint_t n)
{
	if(m != n) {
		throw err::NoConsistency(msg::NeedSquareMatrix());
	}
}
/*-------------------------------------------------*/
void property_compatibility_check(const Property& prop, uint_t m, uint_t n)
{
	if(!prop.isValid()) {
		throw err::NoConsistency(msg::InvalidProperty());
	}

	if(prop.isSquare()) {
		square_check(m, n);
	}
}
/*-------------------------------------------------*/
void similarity_dim_check(uint_t n1, uint_t n2)
{
	if(n1 != n2) {
		throw err::NoConsistency(msg::InvalidDimensions());
	}
}
/*-------------------------------------------------*/
void similarity_check(
		const Property& prop1, uint_t nrows1, uint_t ncols1, 
		const Property& prop2, uint_t nrows2, uint_t ncols2)
{
	similarity_dim_check(nrows1, nrows2);
	similarity_dim_check(ncols1, ncols2);

	if(prop1 != prop2) {
		throw err::NoConsistency(msg::InvalidProperty());
	}
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
