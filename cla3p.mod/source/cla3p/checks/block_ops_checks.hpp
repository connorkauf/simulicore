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

#ifndef CLA3P_BLOCK_OPS_CHECKS_HPP_
#define CLA3P_BLOCK_OPS_CHECKS_HPP_

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

Property block_op_consistency_check(const Property& prop, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

void      block_op_consistency_check(const Property& block_prop, const Property& prop, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
void real_block_op_consistency_check(const Property& block_prop, const Property& prop, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
void imag_block_op_consistency_check(const Property& block_prop, const Property& prop, uint_t nrows, uint_t ncols, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BLOCK_OPS_CHECKS_HPP_
