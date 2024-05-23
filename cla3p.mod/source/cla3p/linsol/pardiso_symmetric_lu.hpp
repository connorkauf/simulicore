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

#ifndef CLA3P_PARDISO_SYMMETRIC_LU_HPP_
#define CLA3P_PARDISO_SYMMETRIC_LU_HPP_

/**
 * @file
 */

#include "cla3p/linsol/pardiso_base.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

/**
 * @nosubgrouping
 * @brief The LU linear solver for structurally symmetric sparse matrices.
 */
template <typename T_Matrix>
class PardisoSymmetricLU : public PardisoBase<T_Matrix> {

	public:

		// no copy
		PardisoSymmetricLU(const PardisoSymmetricLU&) = delete;
		PardisoSymmetricLU& operator=(const PardisoSymmetricLU&) = delete;

		/**
		 * @copydoc cla3p::PardisoLLt::PardisoLLt()
		 */
		PardisoSymmetricLU() : PardisoBase<T_Matrix>(decomp_t::SymmetricLU) {}

		/**
		 * @copydoc cla3p::PardisoLLt::~PardisoLLt()
		 */
		~PardisoSymmetricLU() = default;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_PARDISO_SYMMETRIC_LU_HPP_
