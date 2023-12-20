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
#include "cla3p/checks/csc_checks.hpp"

// system

// 3rd

// cla3p
#include "cla3p/error/exceptions.hpp"
#include "cla3p/error/literals.hpp"
#include "cla3p/checks/basic_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
void csc_consistency_check(uint_t m, uint_t n, uint_t nnz, const void *colptr, const void *rowidx, const void *values)
{
	if(!m || !n) {
		throw err::NoConsistency(msg::InvalidDimensions());
	}

	if(!colptr) {
		throw err::NoConsistency(msg::InvalidPointer());
	}

	if(nnz && !rowidx) {
		throw err::NoConsistency(msg::InvalidPointer());
	}

	if(nnz && !values) {
		throw err::NoConsistency(msg::InvalidPointer());
	}
}
/*-------------------------------------------------*/
void csc_consistency_check(const Property& prop, uint_t m, uint_t n, uint_t nnz, const void *colptr, const void *rowidx, const void *values)
{
	csc_consistency_check(m, n, nnz, colptr, rowidx, values);
	property_compatibility_check(prop, m, n);
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
