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

#ifndef CLA3P_LAPACK_LLT_HPP_
#define CLA3P_LAPACK_LLT_HPP_

/**
 * @file
 */

#include "cla3p/linsol/lapack_base.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

/**
 * @nosubgrouping
 * @brief The definite Cholesky (LL') linear solver for dense matrices.
 */
template <typename T_Matrix>
class LapackLLt : public LapackBase<T_Matrix> {

	using T_Vector = typename TypeTraits<T_Matrix>::vector_type;

	public:

		// no copy
		LapackLLt(const LapackLLt&) = delete;
		LapackLLt& operator=(const LapackLLt&) = delete;

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty solver object.
		 */
		LapackLLt() : LapackBase<T_Matrix>(decomp_t::LLT) {}

		/**
		 * @brief The dimensional constructor.
		 * @param[in] n The expected problem dimension.
		 *
		 * Constructs a solver object with n<sup>2</sup> preallocated buffered size.
		 */
		LapackLLt(uint_t n) : LapackBase<T_Matrix>(decomp_t::LLT, n) {}

		/**
		 * @brief Destroys the solver.
		 *
		 * Clears all internal data and destroys the solver.
		 */
		~LapackLLt() = default;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_LAPACK_LLT_HPP_
