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

// this file inc
#include "cla3p/checks/perm_checks.hpp"

// system

// 3rd

// cla3p
#include "cla3p/error/error.hpp"
#include "cla3p/error/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
void perm_op_consistency_check(uint_t nrows, uint_t ncols, uint_t np, uint_t nq)
{
	if(nrows != np || ncols != nq) {
		throw err::NoConsistency(msg::InvalidDimensions() + " for permute operation");
	}
}
/*-------------------------------------------------*/
void perm_ge_op_consistency_check(prop_t ptype, uint_t nrows, uint_t ncols, uint_t np, uint_t nq)
{
	if(ptype != prop_t::General) {
		throw err::InvalidOp("Right/Left sided permutations are applied on non-empty general matrices");
	}
	perm_op_consistency_check(nrows, ncols, np, nq);
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
