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

#ifndef CLA3P_LAPACK_COMPLETE_LU_HPP_
#define CLA3P_LAPACK_COMPLETE_LU_HPP_

/**
 * @file
 */

#include "cla3p/linsol/lapack_base.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

/**
 * @nosubgrouping
 * @brief The complete pivoting LU linear solver for dense matrices.
 */
template <typename T_Matrix>
class LapackCompleteLU : public LapackBase<T_Matrix> {

	using T_Vector = typename TypeTraits<T_Matrix>::vector_type;

	public:

		// no copy
		LapackCompleteLU(const LapackCompleteLU&) = delete;
		LapackCompleteLU& operator=(const LapackCompleteLU&) = delete;

		/**
		 * @copydoc cla3p::LapackLLt::LapackLLt()
		 */
		LapackCompleteLU() : LapackBase<T_Matrix>(decomp_t::CompleteLU) {}

		/**
		 * @copydoc cla3p::LapackLLt::LapackLLt(uint_t n)
		 */
		LapackCompleteLU(uint_t n) : LapackBase<T_Matrix>(decomp_t::CompleteLU, n) {}

		/**
		 * @copydoc cla3p::LapackLLt::~LapackLLt()
		 */
		~LapackCompleteLU() = default;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_LAPACK_COMPLETE_HPP_
