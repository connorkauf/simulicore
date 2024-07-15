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

#ifndef CLA3P_PERMS_HPP_
#define CLA3P_PERMS_HPP_

#include "cla3p/perms/pxmatrix.hpp"

namespace cla3p {
namespace prm {

/**
 * @ingroup cla3p_module_index_matrices_perm
 * @brief Integer Permutation Matrix.
 */
using PiMatrix = PxMatrix<int_t>;

} // namespace prm
} // namespace cla3p

#endif // CLA3P_PERMS_HPP_
