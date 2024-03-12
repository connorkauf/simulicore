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

#ifndef CLA3P_COO_CHECKS_HPP_
#define CLA3P_COO_CHECKS_HPP_

/**
 * @file
 */

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

void coo_consistency_check(const Property& prop, uint_t m, uint_t n);

template <typename T_Int>
void coo_check_coord(uint_t m, uint_t n, const Property& prop, const T_Int& i, const T_Int& j);

template <typename T_Int, typename T_Scalar>
void coo_check_triplet(uint_t m, uint_t n, const Property& prop, const T_Int& i, const T_Int& j, const T_Scalar& v);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_COO_CHECKS_HPP_
